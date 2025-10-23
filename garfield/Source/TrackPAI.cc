#include "Garfield/TrackPAI.hh"

#include <algorithm>
#include <cmath>
#include <fstream>
#include <iostream>

#include "Garfield/Exceptions.hh"
#include "Garfield/GarfieldConstants.hh"
#include "Garfield/Medium.hh"
#include "Garfield/Random.hh"
#include "Garfield/Sensor.hh"

namespace Garfield {

TrackPAI::TrackPAI() : Track("PAI") {}

bool TrackPAI::NewTrack(const double x0, const double y0, const double z0,
                        const double t0, const double dx0, const double dy0,
                        const double dz0) {
  // Make sure the sensor has been set.
  if (!m_sensor) throw Exception("Sensor is not defined");
  m_clusters.clear();
  // Make sure there is an "ionisable" medium at this location.
  Medium* medium = m_sensor->GetMedium(x0, y0, z0);
  if (!medium || !medium->IsIonisable())
    throw Exception("No ionisable medium at initial position");

  if (medium->GetName() != m_mediumName ||
      medium->GetNumberDensity() != m_mediumDensity) {
    m_isChanged = true;
    if (!SetupMedium(medium)) {
      std::cerr << m_className << "::NewTrack:\n    Properties of medium "
                << medium->GetName() << " are not available.\n";
      return false;
    }
    m_mediumName = medium->GetName();
    m_mediumDensity = medium->GetNumberDensity();
  }

  if (m_isChanged) {
    if (!SetupCrossSectionTable())
      throw Exception("Calculation of ionisation cross-section failed");
    m_isChanged = false;
  }

  double x = x0;
  double y = y0;
  double z = z0;
  double t = t0;
  double dx = dx0;
  double dy = dy0;
  double dz = dz0;
  const double d = sqrt(dx * dx + dy * dy + dz * dz);
  if (d < Small) {
    // Null vector. Choose a random direction.
    RndmDirection(dx, dy, dz);
  } else {
    // Normalize the direction vector.
    const double scale = 1. / d;
    dx *= scale;
    dy *= scale;
    dz *= scale;
  }
  double ekin = GetKineticEnergy();
  while (ekin > 0.) {
    // Draw a step length and propagate the particle.
    const double step = -m_imfp * log(RndmUniformPos());
    x += step * dx;
    y += step * dy;
    z += step * dz;
    t += step / m_speed;

    medium = m_sensor->GetMedium(x, y, z);
    if (!medium || !medium->IsIonisable() ||
        medium->GetName() != m_mediumName ||
        medium->GetNumberDensity() != m_mediumDensity) {
      break;
    }

    // Sample the energy deposit.
    std::pair<double, double> edep = SampleEnergyDeposit(RndmUniform());
    // Update the particle energy.
    ekin -= edep.first;

    Cluster cluster;
    cluster.x = x;
    cluster.y = y;
    cluster.z = z;
    cluster.t = t;
    cluster.energy = edep.first;
    m_clusters.push_back(std::move(cluster));
  }
  return true;
}

std::pair<double, double> TrackPAI::SampleEnergyDeposit(const double u) const {
  if (u > m_cdf.back()) {
    // Use the free-electron differential cross-section.
    return std::make_pair(SampleAsymptoticCs(u), 1.);
  }

  if (u <= m_cdf[0]) return std::make_pair(m_energies[0], 0.);
  if (u >= 1.) return std::make_pair(m_energies.back(), 0.);

  // Find the energy loss by interpolation
  // from the cumulative distribution table.
  const auto begin = m_cdf.cbegin();
  const auto it1 = std::upper_bound(begin, m_cdf.cend(), u);
  if (it1 == m_cdf.cbegin()) return std::make_pair(m_energies[0], 0.);
  const auto it0 = std::prev(it1);
  const double c0 = *it0;
  const double c1 = *it1;
  const double e0 = m_energies[it0 - begin];
  const double e1 = m_energies[it1 - begin];
  const double r0 = m_rutherford[it0 - begin];
  const double r1 = m_rutherford[it1 - begin];
  if (e0 < 100.) {
    const double f1 = (u - c0) / (c1 - c0);
    const double f0 = 1. - f1;
    return std::make_pair(f0 * e0 + f1 * e1, f0 * r0 + f1 * r1);
  }
  const double loge0 = log(e0);
  const double loge1 = log(e1);
  const double logc0 = log(c0);
  const double logc1 = log(c1);
  const double f1 = (log(u) - logc0) / (logc1 - logc0);
  const double f0 = 1. - f1;
  const double edep = exp(f0 * loge0 + f1 * loge1);
  return std::make_pair(edep, f0 * r0 + f1 * r1);
}

bool TrackPAI::SetupMedium(Medium* medium) {
  // Make sure that the medium is defined.
  if (!medium) throw Exception("Medium* is nullptr");

  // Get the density and effective Z.
  m_electronDensity = medium->GetNumberDensity() * medium->GetAtomicNumber();
  if (m_electronDensity <= 0.)
    throw Exception(std::string("Unphysical electron density (" +
                                std::to_string(m_electronDensity) + ")")
                        .c_str());

  // Get the dielectric function.
  double emin, emax;
  if (!medium->GetOpticalDataRange(emin, emax))
    throw Exception(
        std::string("Could not load optical data for medium " + m_mediumName)
            .c_str());
  // Make sure the minimum energy is positive.
  if (emin < Small) emin = Small;

  // Reset the arrays.
  m_energies.fill(0.);
  m_eps1.fill(0.);
  m_eps2.fill(0.);
  m_epsInt.fill(0.);

  // Use logarithmically spaced energy steps.
  const double r = pow(emax / emin, 1. / double(m_nSteps));
  double eC = 0.5 * emin * (1. + r);
  for (size_t i = 0; i < m_nSteps; ++i) {
    double eps1 = 0., eps2 = 0.;
    medium->GetDielectricFunction(eC, eps1, eps2);
    m_eps1[i] = eps1;
    m_eps2[i] = eps2;
    m_energies[i] = eC;
    eC *= r;
  }

  // Compute the integral of loss function times energy.
  m_epsInt[0] = 0.;
  double integral = 0.;
  double f1 = m_energies[0] * LossFunction(m_eps1[0], m_eps2[0]);
  double f2 = f1;
  for (size_t i = 1; i < m_nSteps; ++i) {
    f2 = m_energies[i] * LossFunction(m_eps1[i], m_eps2[i]);
    const double eM = 0.5 * (m_energies[i - 1] + m_energies[i]);
    double eps1 = 0., eps2 = 0.;
    medium->GetDielectricFunction(eM, eps1, eps2);
    const double fM = eM * LossFunction(eps1, eps2);
    // Simpson's rule
    integral += (f1 + 4 * fM + f2) * (m_energies[i] - m_energies[i - 1]) / 6.;
    m_epsInt[i] = integral;
    f1 = f2;
  }

  // Check the consistency of the optical data by means of the TRK sum rule
  const double trk = 2 * Pi2 * FineStructureConstant * pow(HbarC, 3) *
                     m_electronDensity / ElectronMass;
  if (fabs(integral - trk) > 0.2 * trk) {
    std::cerr << m_className << "::SetupMedium:\n"
              << "    Deviation from Thomas-Reiche-Kuhn sum rule by > 20%.\n"
              << "    Optical data are probably incomplete or erroneous!\n";
  }
  return true;
}

double TrackPAI::GetClusterDensity() {
  if (m_isChanged) {
    if (SetupCrossSectionTable()) {
      m_isChanged = false;
    } else
      throw Exception("Ionisation cross-section could not be calculated");
  }
  return 1. / m_imfp;
}

double TrackPAI::GetStoppingPower() {
  if (m_isChanged) {
    if (SetupCrossSectionTable()) {
      m_isChanged = false;
    } else
      throw Exception("Ionisation cross-section could not be calculated");
  }
  return m_dedx;
}

bool TrackPAI::SetupCrossSectionTable() {
  // TODO!
  /*
  if (!m_ready) {
    std::cerr << m_className << "::SetupCrossSectionTable:\n"
              << "    Medium not set up.\n";
    return false;
  }
  */
  const double c1 = 2. * Pi2 * FineStructureConstant * pow(HbarC, 3) *
                    m_electronDensity / ElectronMass;
  const double c2 = m_q * m_q * FineStructureConstant / (m_beta2 * Pi * HbarC);

  // Get the max. allowed energy transfer.
  m_emax = ComputeMaxTransfer();

  std::ofstream outfile;
  if (m_debug) outfile.open("dcs.txt", std::ios::out);

  // Compute the differential cross-section.
  std::vector<double> dcs;
  m_rutherford.fill(0.);
  for (size_t i = 0; i < m_nSteps; ++i) {
    // Define shorthand variables for photon energy and dielectric function.
    const double egamma = m_energies[i];
    const double eps1 = m_eps1[i];
    const double eps2 = m_eps2[i];
    const double integral = m_epsInt[i];

    // First, calculate the distant-collision terms.
    double dcsLog = 0., dcsDensity = 0., dcsCher = 0.;
    if (eps2 > 0.) {
      // Normal case (loss function > 0).
      const double lf = LossFunction(eps1, eps2);
      // Non-relativistic logarithmic term.
      dcsLog = lf * log(2 * ElectronMass * m_beta2 / egamma);
      // Relativistic logarithmic term (density effect)
      const double u = 1. - m_beta2 * eps1;
      const double v = m_beta2 * eps2;
      dcsDensity = -0.5 * lf * log(u * u + v * v);
      // "Cherenkov" term
      dcsCher = (m_beta2 - eps1 / (eps1 * eps1 + eps2 * eps2)) *
                (HalfPi - atan(u / v));
    } else if (eps1 > 1. / m_beta2) {
      // Imaginary part is zero, only the Cerenkov term contributes.
      dcsCher = Pi * (m_beta2 - 1. / eps1);
    }

    // Calculate the close-collision term (quasi-free scattering)
    double dcsRuth = 0.;
    double f = 0.;
    if (egamma > 0. && integral > 0.) {
      dcsRuth = integral / (egamma * egamma);
      f = dcsRuth / (dcsLog + dcsDensity + dcsCher);
    }
    m_rutherford[i] = f;
    dcs.push_back(dcsLog + dcsDensity + dcsCher + dcsRuth);
    // If requested, write the cross-section terms to file.
    if (m_debug) {
      outfile << egamma << "  " << eps1 << "  " << eps2 << "  " << dcsLog * c2
              << "  " << dcsDensity * c2 << "  " << dcsCher * c2 << "  "
              << dcsRuth * c2 << "\n";
    }
  }
  if (m_debug) outfile.close();

  // Compute the cumulative distribution,
  // total cross-section and stopping power.
  m_cdf.fill(0.);
  m_dedx = 0.;
  double cs = 0.;
  for (size_t i = 1; i < m_nSteps; ++i) {
    const double e0 = m_energies[i - 1];
    const double e1 = m_energies[i];
    const double de = e1 - e0;
    const double dcs0 = dcs[i - 1];
    const double dcs1 = dcs[i];
    cs += 0.5 * (dcs0 + dcs1) * de;
    m_cdf[i] = cs;
    m_dedx += 0.5 * (dcs0 * e0 + dcs1 * e1) * de;
  }

  // Add the contribution of high energy transfers to the stopping power
  // and the total cross-section
  const double elim = m_energies.back();
  if (elim < m_emax) {
    cs += c1 * ComputeCsTail(elim, m_emax);
    m_dedx += c1 * ComputeDeDxTail(elim, m_emax);
  } else {
    std::cerr << m_className << "::SetupCrossSectionTable:\n";
    std::cerr << "    Max. energy transfer lower than optical data range.\n";
  }

  if (cs <= 0.) throw Exception("Total cross-section <= 0");
  // Normalise the cumulative distribution.
  for (size_t i = 0; i < m_nSteps; ++i) m_cdf[i] /= cs;

  cs *= c2;
  m_dedx *= c2;

  // Compute the inelastic mean free path
  m_imfp = 1. / cs;

  return true;
}

double TrackPAI::ComputeMaxTransfer() const {
  if (m_isElectron) {
    // Max. transfer for electrons is half the kinetic energy.
    return 0.5 * (m_energy - m_mass);
  }

  // Other particles.
  const double bg2 = m_beta2 / (1. - m_beta2);
  const double mass2 = m_mass * m_mass;

  return 2. * mass2 * ElectronMass * bg2 /
         (mass2 + ElectronMass * ElectronMass + 2. * m_energy * ElectronMass);
}

double TrackPAI::ComputeCsTail(const double emin, const double emax) {
  if (m_isElectron) {
    // Electrons
    const double ek = m_energy - m_mass;
    return 1. / emin - 1. / emax - 2 * emin / (ek * ek) -
           emin * emin / ((ek - emin) * ek * ek);
  } else if (fabs(m_mass - ElectronMass) < 0.1) {
    // Positrons
    const double ek = m_energy - m_mass;
    return 1. / emin - 1. / emax + 3 * (emax - emin) / (ek * ek) -
           (emax - emin) *
               (ek * (emax + emin) +
                (emin * emin + emin * emax + emax * emax) / 3.) /
               pow(ek, 4) -
           (2. / ek) * log(emax / emin);
  }

  switch (m_spin) {
    case 0:
      // Spin 0
      return 1. / emin - 1. / emax - m_beta2 * log(emax / emin) / emax;
    case 1:
      // Spin 1/2
      return 1. / emin - 1. / emax - m_beta2 * log(emax / emin) / emax +
             (emax - emin) / (2 * m_energy * m_energy);
    case 2: {
      // Spin 1
      const double e2 = 2 * m_energy * m_energy;
      const double ec = m_mass * m_mass / ElectronMass;
      const double a = 1. / (3 * ec);
      const double b = (emax - emin);
      return 1. / emin - 1. / emax + a * b * (emin + e2 + emax) / e2 -
             m_beta2 * a * b / emax + (a - m_beta2 / emax) * log(emax / emin);
    }
    default:
      break;
  }
  // Rutherford type cross-section
  return 1. / emin - 1. / emax;
}

double TrackPAI::ComputeDeDxTail(const double emin, const double emax) {
  if (m_isElectron) {
    const double ek = m_energy - m_mass;
    return -log(emin * (ek - emin) / (ek * ek)) +
           (1. / (8 * (emin - ek) * ek * ek)) *
               (-4 * pow(emin, 3) + 4 * emin * emin * ek +
                emin * ek * ek * (17. - 16. * CLog2) +
                pow(ek, 3) * (-9. + 16. * CLog2));
  } else if (fabs(m_mass - ElectronMass) < 0.1) {
    // Positron
    const double ek = m_energy - m_mass;
    return log(ek / emin) -
           (ek - emin) * (ek - emin) *
               (3. * emin * emin - 2. * emin * ek + 11. * ek * ek) /
               (12. * pow(ek, 4));
  }

  switch (m_spin) {
    case 0:
      return log(emax / emin) - m_beta2 * (emax - emin) / emax;
    case 1:
      // Spin 1/2
      return log(emax / emin) - m_beta2 * (emax - emin) / emax +
             (emax * emax - emin * emin) / (2 * m_energy * m_energy);
    case 2: {
      // Spin 1
      double e2 = m_energy * m_energy;
      double ec = m_mass * m_mass / ElectronMass;
      return log(emax / emin) + (pow(emax, 3) - pow(emin, 3)) / (9. * e2 * ec) +
             (emax * emax - emin * emin) / (6. * e2) +
             (emax - emin) *
                 (2. - (1. + emin / emax + 6 * ec / emax) * m_beta2) /
                 (6. * ec);
    }
    default:
      break;
  }

  // Rutherford cross-section
  return log(emax / emin);
}

double TrackPAI::SampleAsymptoticCs(double u) const {
  const double emin = m_energies.back();
  // Rescale the random number
  u = (u - m_cdf.back()) / (1. - m_cdf.back());

  if (m_isElectron) {
    return SampleAsymptoticCsElectron(emin, u);
  } else if (fabs(m_mass - ElectronMass) < 0.1) {
    return SampleAsymptoticCsPositron(emin, u);
  }

  switch (m_spin) {
    case 0:
      // Spin 0
      return SampleAsymptoticCsSpinZero(emin, u);
    case 1:
      // Spin 1/2
      return SampleAsymptoticCsSpinHalf(emin, u);
    case 2:
      // Spin 1
      return SampleAsymptoticCsSpinOne(emin, u);
    default:
      break;
  }
  // Rutherford cross-section (analytic inversion)
  return emin * m_emax / (u * emin + (1. - u) * m_emax);
}

double TrackPAI::SampleAsymptoticCsSpinZero(const double emin, double u) const {
  const double a = emin / m_emax;
  const double b = m_beta2 * a;
  u *= (1. - a + b * log(a));
  double eLow = emin, eUp = m_emax;
  while (eUp - eLow > 1.) {
    const double eM = 0.5 * (eUp + eLow);
    if (u >= 1. - emin / eM - b * log(eM / emin)) {
      eLow = eM;
    } else {
      eUp = eM;
    }
  }

  return 0.5 * (eLow + eUp);
}

double TrackPAI::SampleAsymptoticCsSpinHalf(const double emin, double u) const {
  const double a = emin / m_emax;
  const double b = m_beta2 * a;
  const double c = emin / (2. * m_energy * m_energy);
  u *= 1. - a + b * log(a) + (m_emax - emin) * c;
  double eLow = emin, eUp = m_emax;
  while (eUp - eLow > 1.) {
    const double eM = 0.5 * (eUp + eLow);
    if (u >= 1. - emin / eM - b * log(eM / emin) + (eM - emin) * c) {
      eLow = eM;
    } else {
      eUp = eM;
    }
  }

  return 0.5 * (eLow + eUp);
}

double TrackPAI::SampleAsymptoticCsSpinOne(const double emin, double u) const {
  const double e2 = 2 * m_energy * m_energy;
  const double ec = m_mass * m_mass / ElectronMass;
  const double a = 2 * ec / e2 - m_beta2 / m_emax;
  const double b = 1.5 * ec / emin;
  const double c = 1. - 1.5 * ec * m_beta2 / m_emax;
  u *= (m_emax - emin) * (0.5 * (emin + m_emax) / e2 + a + b / m_emax) +
       c * log(m_emax / emin);
  double eLow = emin, eUp = m_emax;
  while (eUp - eLow > 1.) {
    const double eM = 0.5 * (eUp + eLow);
    if (u >=
        (eM - emin) * ((emin + eM) / e2 + a + b / eM) + c * log(eM / emin)) {
      eLow = eM;
    } else {
      eUp = eM;
    }
  }

  return 0.5 * (eLow + eUp);
}

double TrackPAI::SampleAsymptoticCsElectron(const double emin, double u) const {
  const double ek = m_energy - m_mass;
  const double ek2 = ek * ek;
  const double a = ek / (emin * (ek - emin));
  const double norm = 1. / emin - 0.5 / ek - emin * emin / ((ek - emin) * ek2) -
                      2. * emin / ek2;
  u *= norm;
  double eLow = emin, eUp = m_emax;
  while (eUp - eLow > 1.) {
    const double eM = 0.5 * (eUp + eLow);
    if (u >= a - 1. / eM + (eM - emin) / ek2 + 1. / (ek - eM)) {
      eLow = eM;
    } else {
      eUp = eM;
    }
  }
  return 0.5 * (eLow + eUp);
}

double TrackPAI::SampleAsymptoticCsPositron(const double emin, double u) const {
  const double ek = m_energy - m_mass;
  const double ek2 = ek * ek;
  const double ek3 = ek2 * ek;
  const double ek4 = 3 * ek3 * ek;
  const double emin2 = emin * emin;
  const double a = 1. / emin;
  const double b = 3. / ek2;
  const double c = 2. / ek;
  u *= 1. / emin - 1. / m_emax + 3 * (m_emax - emin) / ek2 -
       (m_emax - emin) * (m_emax + emin) / ek3 +
       (m_emax - emin) * (emin * emin + emin * m_emax + m_emax * m_emax) / ek4 -
       (2. / ek) * log(m_emax / emin);
  double eLow = emin, eUp = m_emax;
  while (eUp - eLow > 1.) {
    const double eM = 0.5 * (eUp + eLow);
    const double eM2 = eM * eM;
    if (u >= a - 1. / eM + b * (eM - emin) - (eM2 - emin2) / ek3 +
                 (eM - emin) * (emin2 + emin * eM + eM2) / ek4 -
                 c * log(eM / emin)) {
      eLow = eM;
    } else {
      eUp = eM;
    }
  }

  return 0.5 * (eLow + eUp);
}
}  // namespace Garfield
