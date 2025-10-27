#include "Garfield/TrackDegrade.hh"

#include <algorithm>
#include <array>
#include <cmath>
#include <iostream>
#include <string>

#include "Garfield/DegradeInterface.hh"
#include "Garfield/Exceptions.hh"
#include "Garfield/FundamentalConstants.hh"
#include "Garfield/GarfieldConstants.hh"
#include "Garfield/Medium.hh"
#include "Garfield/MediumMagboltz.hh"
#include "Garfield/Random.hh"
#include "Garfield/Sensor.hh"

namespace {

Garfield::TrackDegrade::Electron MakeElectron(const double energy,
                                              const double x, const double y,
                                              const double z, const double t,
                                              const double dx, const double dy,
                                              const double dz) {
  Garfield::TrackDegrade::Electron electron;
  electron.energy = energy;
  electron.x = x;
  electron.y = y;
  electron.z = z;
  electron.t = t;
  electron.dx = dx;
  electron.dy = dy;
  electron.dz = dz;
  return electron;
}

Garfield::TrackDegrade::Excitation MakeExcitation(const double energy,
                                                  const double x,
                                                  const double y,
                                                  const double z,
                                                  const double t) {
  Garfield::TrackDegrade::Excitation exc;
  exc.energy = energy;
  exc.x = x;
  exc.y = y;
  exc.z = z;
  exc.t = t;
  return exc;
}

}  // namespace

namespace Garfield {

TrackDegrade::TrackDegrade() : Track("Degrade") {
  m_q = -1;
  m_spin = 1;
  m_mass = ElectronMass;
  m_isElectron = true;
  SetBetaGamma(3.);
  m_particleName = "electron";
}

TrackDegrade::TrackDegrade(Sensor* sensor) : TrackDegrade() {
  if (!sensor) throw Exception("Sensor* is nullptr");
  m_sensor = sensor;
}

void TrackDegrade::SetThresholdEnergy(const double ethr) {
  if (ethr < Small) throw Exception("Threshold energy must be > 0");
  m_ethr = ethr;
}

void TrackDegrade::StoreExcitations(const bool on, const double thr) {
  m_storeExcitations = on;
  m_ethrExc = std::max(thr, 1.e-3);
}

bool TrackDegrade::NewTrack(const double x0, const double y0, const double z0,
                            const double t0, const double dx0, const double dy0,
                            const double dz0) {
  // Make sure the sensor is defined.
  if (!m_sensor) throw Exception("Sensor is not defined");
  m_clusters.clear();
  // Make sure we are inside a medium.
  Medium* medium = m_sensor->GetMedium(x0, y0, z0);
  if (!medium) throw Exception("No medium at initial position");
  // Check if the medium has changed since the last call.
  if (medium->GetName() != m_mediumName ||
      fabs(medium->GetPressure() - m_pressure) > 1.e-4 ||
      fabs(medium->GetTemperature() - m_temperature) > 1.e-4) {
    m_isChanged = true;
  }
  if (m_isChanged) {
    if (!Initialise(medium, m_debug)) return false;
    m_isChanged = false;
  }
  SetupPenning(medium, m_rPenning, m_dPenning);
  const double eMinIon = Degrade::ionpot();
  if (m_debug) {
    std::cout << "    Ionisation potential: " << eMinIon << " eV.\n";
  }
  double xp = x0;
  double yp = y0;
  double zp = z0;
  double tp = t0;

  // Normalise the direction.
  double dxp = dx0;
  double dyp = dy0;
  double dzp = dz0;
  const double dp = sqrt(dxp * dxp + dyp * dyp + dzp * dzp);
  if (dp < Small) {
    // Choose a random direction.
    RndmDirection(dxp, dyp, dzp);
  } else {
    const double scale = 1. / dp;
    dxp *= scale;
    dyp *= scale;
    dzp *= scale;
  }
  // Get the total collision rate.
  int64_t ie = 20000;
  double tcf = Degrade::gettcf(&ie);
  // Convert to ns-1.
  tcf *= 1.e3;
  double beta = GetBeta();
  double gamma = GetGamma();
  double ep = GetKineticEnergy();
  if (m_debug) {
    std::cout << m_className << "::NewTrack:\n"
              << "    Particle energy: " << ep << " eV\n"
              << "    Collision rate: " << tcf << " / ns\n"
              << "    Collisions / cm: " << tcf / (SpeedOfLight * beta) << "\n";
  }
  bool ok = true;
  while (ok) {
    // Draw a time step.
    double dt = -log(RndmUniformPos()) / tcf;
    const double step = SpeedOfLight * beta * dt;
    xp += dxp * step;
    yp += dyp * step;
    zp += dzp * step;
    tp += dt;
    if (!IsInside(xp, yp, zp)) break;
    // Reset the scattering angle.
    double cthetap = -99.;
    double sthetap = -99.;
    // Determine the type of interaction.
    double r1 = RndmUniform();
    int64_t izbr = 0;
    double rgas = 0.;
    double ein = 0.;
    int64_t ia = 0;
    double wpl = 0.;
    int64_t index = 0;
    double an = 0.;
    double ps = 0.;
    double wklm = 0.;
    int64_t nc0 = 0;
    double ec0 = 0.;
    int64_t ng2 = 0;
    double eg2 = 0.;
    int64_t ng1 = 0;
    double eg1 = 0.;
    double dstfl = 0.;
    int64_t ipn = 0;
    int64_t kg1 = 0;
    int64_t lg1 = 0;
    int64_t igshel = 0;
    int64_t ionmodel = 0;
    int64_t ilvl = 0;
    Degrade::getlevel(&ie, &r1, &izbr, &rgas, &ein, &ia, &wpl, &index, &an, &ps,
                      &wklm, &nc0, &ec0, &ng1, &eg1, &ng2, &eg2, &dstfl, &ipn,
                      &kg1, &lg1, &igshel, &ionmodel, &ilvl);
    // Bremsstrahlung?
    if (izbr != 0 && m_bremsStrahlung) {
      double eout = 0., egamma = 0.;
      double dxe = 0., dye = 0., dze = 0.;
      double dxg = 0., dyg = 0., dzg = 0.;
      Degrade::brems(&izbr, &ep, &dxp, &dyp, &dzp, &eout, &dxe, &dye, &dze,
                     &egamma, &dxg, &dyg, &dzg);
      // TODO
      // ep = eout;
      dxp = dxe;
      dyp = dye;
      dzp = dze;
      continue;
    }
    if (ia == 2 || ia == 7 || ia == 12 || ia == 17 || ia == 22 || ia == 27) {
      Cluster cluster;
      cluster.x = xp;
      cluster.y = yp;
      cluster.z = zp;
      cluster.t = tp;
      // Ionisation
      double esec = wpl * tan(RndmUniform() * atan((ep - ein) / (2. * wpl)));
      esec = wpl * pow(esec / wpl, 0.9524);
      // TODO: while esec > ECUT?
      // Calculate primary scattering angle.
      if (index == 1) {
        cthetap = 1. - RndmUniform() * an;
        if (RndmUniform() > ps) cthetap = -cthetap;
      } else if (index == 2) {
        const double ctheta0 = 1. - 2 * RndmUniform();
        cthetap = (ctheta0 + ps) / (1. + ps * ctheta0);
      } else {
        cthetap = 1. - 2. * RndmUniform();
      }
      sthetap = sin(acos(cthetap));
      const double gammas = (ElectronMass + esec) / ElectronMass;
      // Calculate secondary recoil angle from free kinematics.
      const double sthetas =
          std::min(sthetap * sqrt(ep / esec) * gamma / gammas, 1.);
      double thetas = asin(sthetas);
      double phis = TwoPi * RndmUniform();
      // Calculate new direction cosines from initial values and
      // scattering angles.
      double dxs = 0., dys = 0., dzs = 0.;
      Degrade::drcos(&dxp, &dyp, &dzp, &thetas, &phis, &dxs, &dys, &dzs);
      // Add the secondary to the list.
      cluster.deltaElectrons.emplace_back(
          MakeElectron(esec, xp, yp, zp, tp, dxs, dys, dzs));
      // Calculate possible shell emissions (Auger or fluorescence).
      if (wklm > 0.0 && RndmUniform() < wklm) {
        // Auger emission and fluorescence.
        if (ng2 > 0) {
          const double eavg = eg2 / ng2;
          for (int64_t j = 0; j < ng2; ++j) {
            // Random emission angle.
            const double ctheta = 1. - 2. * RndmUniform();
            const double stheta = sin(acos(ctheta));
            const double phi = TwoPi * RndmUniform();
            const double dx = cos(phi) * stheta;
            const double dy = sin(phi) * stheta;
            const double dz = ctheta;
            cluster.deltaElectrons.emplace_back(
                MakeElectron(eavg, xp, yp, zp, tp, dx, dy, dz));
          }
        }
        if (ng1 > 0) {
          const double eavg = eg1 / ng1;
          // Fluorescence absorption distance.
          double dfl = -log(RndmUniformPos()) * dstfl;
          for (int64_t j = 0; j < ng1; ++j) {
            // Random emission angle.
            const double ctheta = 1. - 2. * RndmUniform();
            const double stheta = sin(acos(ctheta));
            const double phi = TwoPi * RndmUniform();
            const double dx = cos(phi) * stheta;
            const double dy = sin(phi) * stheta;
            const double dz = ctheta;
            const double cthetafl = 1. - 2. * RndmUniform();
            const double sthetafl = sin(acos(cthetafl));
            const double phifl = TwoPi * RndmUniform();
            const double xs = dfl * sthetafl * cos(phifl);
            const double ys = dfl * sthetafl * sin(phifl);
            const double zs = dfl * cthetafl;
            const double ts = dfl / SpeedOfLight;
            cluster.deltaElectrons.emplace_back(
                MakeElectron(eavg, xs, ys, zs, ts, dx, dy, dz));
          }
        }
      } else {
        // Auger emission without fluorescence.
        const double eavg = ec0 / nc0;
        for (int64_t j = 0; j < nc0; ++j) {
          // Random emission angle.
          const double ctheta = 1. - 2. * RndmUniform();
          const double stheta = sin(acos(ctheta));
          const double phi = TwoPi * RndmUniform();
          const double dx = cos(phi) * stheta;
          const double dy = sin(phi) * stheta;
          const double dz = ctheta;
          cluster.deltaElectrons.emplace_back(
              MakeElectron(eavg, xp, yp, zp, tp, dx, dy, dz));
        }
      }
      m_clusters.push_back(std::move(cluster));
    } else if (ia == 4 || ia == 9 || ia == 14 || ia == 19 || ia == 24 ||
               ia == 29) {
      // Excitation.
      const double eExc = rgas * ein;
      // Find the gas in which the excitation occured.
      int64_t igas = Degrade::getgas(&ilvl);
      if (igas <= 0 || igas >= 6) {
        std::cerr << m_className << "::NewTrack: "
                  << "Could not retrieve gas index.\n";
        igas = 0;
      } else {
        igas -= 1;
      }
      const double penfra1 = m_rPenning[igas];
      const double penfra2 = m_dPenning[igas];
      constexpr double penfra3 = 0.;
      const bool penning =
          m_penning && eExc > eMinIon && penfra1 > 0. && m_nGas > 1;
      if (penning && RndmUniform() < penfra1) {
        // Penning transfer
        Cluster cluster;
        cluster.x = xp;
        cluster.y = yp;
        cluster.z = zp;
        cluster.t = tp;
        // Random emission angle.
        const double ctheta = 1. - 2. * RndmUniform();
        const double stheta = sin(acos(ctheta));
        const double phi = TwoPi * RndmUniform();
        const double dx = cos(phi) * stheta;
        const double dy = sin(phi) * stheta;
        const double dz = ctheta;
        // Penning transfer distance.
        double asign = 1.;
        if (RndmUniform() < 0.5) asign = -asign;
        const double xs = xp - log(RndmUniformPos()) * penfra2 * asign;
        if (RndmUniform() < 0.5) asign = -asign;
        const double ys = yp - log(RndmUniformPos()) * penfra2 * asign;
        if (RndmUniform() < 0.5) asign = -asign;
        const double zs = zp - log(RndmUniformPos()) * penfra2 * asign;
        const double ts = tp - log(RndmUniformPos()) * penfra3;
        // Fix Penning electron energy to 4 eV.
        cluster.deltaElectrons.emplace_back(
            MakeElectron(4., xs, ys, zs, ts, dx, dy, dz));
        m_clusters.push_back(std::move(cluster));
      } else {
        if (m_storeExcitations && eExc > m_ethrExc) {
          Cluster cluster;
          cluster.x = xp;
          cluster.y = yp;
          cluster.z = zp;
          cluster.t = tp;
          cluster.excitations.emplace_back(
              MakeExcitation(eExc, xp, yp, zp, tp));
          m_clusters.push_back(std::move(cluster));
        }
      }
    }
    double s1 = 1. + gamma * (rgas - 1.);
    double s2 = (s1 * s1) / (s1 - 1.);
    if (cthetap < -1.) {
      if (index == 1) {
        // Anisotropic scattering
        cthetap = 1. - RndmUniform() * an;
        if (RndmUniform() > ps) cthetap = -cthetap;
      } else if (index == 2) {
        // Anisotropic scattering
        const double ctheta0 = 1. - 2 * RndmUniform();
        cthetap = (ctheta0 + ps) / (1. + ps * ctheta0);
      } else {
        // Isotropic scattering
        cthetap = 1. - 2. * RndmUniform();
      }
      sthetap = sin(acos(cthetap));
    }
    double phi0 = TwoPi * RndmUniform();
    double sphi0 = sin(phi0);
    double cphi0 = cos(phi0);
    if (ep < ein) ein = 0.;
    double arg1 = std::max(1. - s1 * ein / ep, 1.e-20);
    const double d = 1. - cthetap * sqrt(arg1);
    double e1 = std::max(ep * (1. - ein / (s1 * ep) - 2. * d / s2), 1.e-20);
    const double q = std::min(sqrt((ep / e1) * arg1) / s1, 1.);
    const double theta = asin(q * sthetap);
    double ctheta = cos(theta);
    if (cthetap < 0.) {
      const double u = (s1 - 1.) * (s1 - 1.) / arg1;
      if (cthetap * cthetap > u) ctheta = -ctheta;
    }
    const double stheta = sin(theta);
    double dx1 = dxp;
    double dy1 = dyp;
    double dz1 = std::min(dzp, 1.);
    double argz = sqrt(dx1 * dx1 + dy1 * dy1);
    if (argz == 0.) {
      dzp = ctheta;
      dxp = cphi0 * stheta;
      dyp = sphi0 * stheta;
    } else {
      dzp = dz1 * ctheta + argz * stheta * sphi0;
      dyp = dy1 * ctheta + (stheta / argz) * (dx1 * cphi0 - dy1 * dz1 * sphi0);
      dxp = dx1 * ctheta - (stheta / argz) * (dy1 * cphi0 + dx1 * dz1 * sphi0);
    }
    // TODO
    // ep = e1;
  }
  if (m_debug) std::cout << "    " << m_clusters.size() << " clusters.\n";
  for (auto& cluster : m_clusters) {
    for (const auto& delta : cluster.deltaElectrons) {
      auto secondaries =
          TransportDeltaElectron(delta.x, delta.y, delta.z, delta.t,
                                 delta.energy, delta.dx, delta.dy, delta.dz);
      cluster.electrons.insert(cluster.electrons.end(),
                               secondaries.first.begin(),
                               secondaries.first.end());
      cluster.excitations.insert(cluster.excitations.end(),
                                 secondaries.second.begin(),
                                 secondaries.second.end());
    }
  }
  return true;
}

bool TrackDegrade::Initialise(Medium* medium, const bool verbose) {
  if (!medium) throw Exception("Medium is nullptr");
  if (!medium->IsGas())
    throw Exception(
        std::string("Medium " + medium->GetName() + " is not a gas").c_str());
  // Get temperature and pressure.
  double pressure = medium->GetPressure();
  double temperature = medium->GetTemperature() - ZeroCelsius;
  // Get the gas composition.
  std::array<int64_t, 6> ngas;
  std::array<double, 6> frac;
  const std::size_t nComponents = medium->GetNumberOfComponents();
  if (nComponents < 1) throw Exception("Invalid gas mixture");
  std::vector<std::size_t> notdone = {13, 17, 20, 22, 24, 26, 27, 28,
                                      32, 33, 37, 38, 39, 40, 41, 42,
                                      43, 50, 51, 53, 54, 55, 56, 57};
  for (std::size_t i = 0; i < nComponents; ++i) {
    std::string name;
    double f;
    medium->GetComponent(i, name, f);
    ngas[i] = MediumMagboltz::GetGasNumberMagboltz(name);
    if (std::find(notdone.begin(), notdone.end(), ngas[i]) != notdone.end()) {
      std::cerr << m_className << "::Initialise:\n"
                << "    Cross-sections for " << name
                << " are not yet implemented.\n";
      return false;
    }
    frac[i] = 100. * f;
  }

  int64_t ng = nComponents;
  int64_t ne = 1;
  int64_t mip = 1;
  int64_t idvec = 1;
  int32_t iseed = 0;
  double e0 = GetKineticEnergy();
  double et = m_ethr;
  double ec = 10000.;
  double etot = 100.;
  double btot = 0.;
  double bang = 90.;
  int64_t jcmp = 1;
  int64_t jray = 1;
  int64_t jpap = 1;
  int64_t jbrm = m_bremsStrahlung ? 1 : 0;
  int64_t jecasc = m_fullCascade ? 1 : 0;
  int64_t iverb = verbose ? 1 : 0;
  Degrade::deginit(&ng, &ne, &mip, &idvec, &iseed, &e0, &et, &ec, &ngas[0],
                   &ngas[1], &ngas[2], &ngas[3], &ngas[4], &ngas[5], &frac[0],
                   &frac[1], &frac[2], &frac[3], &frac[4], &frac[5],
                   &temperature, &pressure, &etot, &btot, &bang, &jcmp, &jray,
                   &jpap, &jbrm, &jecasc, &iverb);

  m_mediumName = medium->GetName();
  m_pressure = medium->GetPressure();
  m_temperature = medium->GetTemperature();
  m_nGas = nComponents;
  m_isChanged = false;
  m_dedx = -1.;
  m_clusterDensity = -1.;
  return true;
}

double TrackDegrade::GetClusterDensity() {
  if (m_isChanged) return 0.;
  if (m_clusterDensity < 0.) {
    // Compute dE/dx and cluster density.
    Degrade::getdedx(&m_dedx, &m_clusterDensity);
  }
  return m_clusterDensity;
}

double TrackDegrade::GetStoppingPower() {
  if (m_isChanged) return 0.;
  if (m_dedx < 0.) {
    // Compute dE/dx and cluster density.
    Degrade::getdedx(&m_dedx, &m_clusterDensity);
  }
  return m_dedx;
}

void TrackDegrade::SetParticle(const std::string& particle) {
  if (particle != "electron" && particle != "e" && particle != "e-")
    throw Exception("Only electrons are allowed");
}

std::pair<std::vector<TrackDegrade::Electron>,
          std::vector<TrackDegrade::Excitation> >
TrackDegrade::TransportDeltaElectron(const double x0, const double y0,
                                     const double z0, const double t0,
                                     const double e0, const double dx0,
                                     const double dy0, const double dz0) {
  if (!m_sensor) throw Exception("Sensor is not defined");
  // Based on MONTEFE subroutine.
  std::vector<Electron> thermalisedElectrons;
  std::vector<Excitation> excitations;

  const double eMinIon = Degrade::ionpot();
  if (m_debug) {
    std::cout << "    Ionisation potential: " << eMinIon << " eV.\n";
  }

  // Calculate maximum collision frequency.
  double flim = 0.;
  for (int64_t j = 1; j <= 20000; ++j) {
    double tcf = Degrade::gettcf(&j);
    double tcfn = Degrade::gettcfn(&j);
    flim = std::max(flim, tcf + tcfn);
  }
  // Convert to ns-1.
  flim *= 1.e3;
  std::vector<Electron> deltas;
  deltas.emplace_back(MakeElectron(e0, x0, y0, z0, t0, dx0, dy0, dz0));
  std::vector<Electron> newDeltas;

  while (!deltas.empty()) {
    for (const auto& delta : deltas) {
      double x1 = delta.x;
      double y1 = delta.y;
      double z1 = delta.z;
      double t1 = delta.t;
      double e1 = delta.energy;
      double dx1 = delta.dx;
      double dy1 = delta.dy;
      double dz1 = delta.dz;

      bool attached = false;
      double tdash = 0.;
      while (1) {
        if (e1 <= m_ethr) break;
        bool ionised = false;
        size_t jsec = 0;
        double esec = 0.;
        const double dt = tdash - log(RndmUniformPos()) / flim;
        tdash = dt;
        const double gamma1 = (ElectronMass + e1) / ElectronMass;
        const double beta1 = sqrt(1. - 1. / (gamma1 * gamma1));
        // Energy after the free-flight step.
        // TODO: electric field.
        double e2 = e1;
        if (e2 < 0.) e2 = 0.001;
        int64_t ie = Degrade::getie(&e2);
        // Test for real or null collision.
        double tcf = Degrade::gettcf(&ie);
        // Convert to ns-1.
        tcf *= 1.e3;
        const double r5 = RndmUniform();
        if (r5 > tcf / flim) {
          // Null collision
          // TODO: molecular light emission from null excitations.
          continue;
        }
        tdash = 0.;
        // Compute direction and position at the instant before the collision.
        // TODO: electric and magnetic field.
        const double gamma2 = (ElectronMass + e2) / ElectronMass;
        // const double gamma12 = 0.5 * (gamma1 + gamma2);
        const double beta2 = sqrt(1. - 1. / (gamma2 * gamma2));
        const double c6 = beta1 / beta2;
        double dx2 = dx1 * c6;
        double dy2 = dy1 * c6;
        double dz2 = dz1 * c6;
        const double a = dt * SpeedOfLight * beta1;
        double x2 = x1 + dx1 * a;
        double y2 = y1 + dy1 * a;
        double z2 = z1 + dz1 * a;
        double t2 = t1 + dt;

        if (!IsInside(x2, y2, z2)) {
          // Endpoint of the free-flight step is outside the active area.
          break;
        }
        x1 = x2;
        y1 = y2;
        z1 = z2;
        t1 = t2;

        // Determine the real collision type.
        double r2 = RndmUniform();
        int64_t izbr = 0;
        double rgas = 0.;
        double ein = 0.;
        int64_t ia = 0;
        double wpl = 0.;
        int64_t index = 0;
        double an = 0.;
        double ps = 0.;
        double wklm = 0.;
        int64_t nc0 = 0;
        double ec0 = 0.;
        int64_t ng2 = 0;
        double eg2 = 0.;
        int64_t ng1 = 0;
        double eg1 = 0.;
        double dstfl = 0.;
        int64_t ipn = 0;
        int64_t kg1 = 0;
        int64_t lg1 = 0;
        int64_t igshel = 0;
        int64_t ionmodel = 0;
        int64_t ilvl = 0;
        Degrade::getlevel(&ie, &r2, &izbr, &rgas, &ein, &ia, &wpl, &index, &an,
                          &ps, &wklm, &nc0, &ec0, &ng1, &eg1, &ng2, &eg2,
                          &dstfl, &ipn, &kg1, &lg1, &igshel, &ionmodel, &ilvl);
        // Bremsstrahlung?
        if (izbr != 0 && m_bremsStrahlung) {
          int64_t kg = 0;
          for (kg = 1; kg <= 6; ++kg) {
            if (ia == (kg * 5) - 1) break;
          }
          kg -= 1;
          double dxe = 0., dye = 0., dze = 0.;
          double dxg = 0., dyg = 0., dzg = 0.;
          double eout = 0., egamma = 0.;
          Degrade::brems(&izbr, &e2, &dx2, &dy2, &dz2, &eout, &dxe, &dye, &dze,
                         &egamma, &dxg, &dyg, &dzg);
          // TODO: counters.
          // NBREM[kg] += 1;
          // EBRTOT[kg] += egamma;
          // Update direction and energy of the electron.
          e1 = eout;
          dx1 = dxe;
          dy1 = dye;
          dz1 = dze;
          // Run bremsstrahlung gamma through cascade.
          int64_t j11 = 1;
          int64_t ilow = 0;
          Degrade::bremscasc(&j11, &egamma, &x1, &y1, &z1, &t1, &dxg, &dyg,
                             &dzg, &ilow);
          // If bremsstrahlung energy is not too low to ionise,
          // retrieve the secondary electrons.
          if (ilow != 0) {
            for (int64_t k = 0; k <= 400; ++k) {
              int64_t iok = 0;
              double ee = 0., xe = 0., ye = 0., ze = 0., te = 0.;
              Degrade::getebrem(&k, &ee, &xe, &ye, &ze, &te, &dxe, &dye, &dze,
                                &iok);
              if (iok != 1) break;
              newDeltas.emplace_back(
                  MakeElectron(ee, xe, ye, ze, te, dxe, dye, dze));
            }
          }
          continue;
        }
        if (e2 < ein) ein = e2 - 0.0001;
        if (ipn == -1) {
          // Attachment.
          attached = true;
          break;
        } else if (ipn == 0) {
          // Excitation.
          const double eExc = rgas * ein;
          // Find the gas in which the excitation occured.
          int64_t igas = Degrade::getgas(&ilvl);
          if (igas <= 0 || igas >= 6) {
            std::cerr << m_className << "::TransportDeltaElectron: "
                      << "Could not retrieve gas index.\n";
            igas = 0;
          } else {
            igas -= 1;
          }
          const double penfra1 = m_rPenning[igas];
          const double penfra2 = m_dPenning[igas];
          constexpr double penfra3 = 0.;
          const bool penning =
              m_penning && eExc > eMinIon && penfra1 > 0. && m_nGas > 1;
          if (penning && RndmUniform() < penfra1) {
            // Penning transfer.
            double xs = x2;
            double ys = y2;
            double zs = z2;
            if (penfra2 > 0.) {
              double asign = 1.;
              if (RndmUniform() < 0.5) asign = -asign;
              xs -= log(RndmUniformPos()) * penfra2 * asign;
              if (RndmUniform() < 0.5) asign = -asign;
              ys -= log(RndmUniformPos()) * penfra2 * asign;
              if (RndmUniform() < 0.5) asign = -asign;
              zs -= log(RndmUniformPos()) * penfra2 * asign;
            }
            double ts = t2 - log(RndmUniformPos()) * penfra3;
            // Assign excess energy of 1 eV to Penning electron.
            newDeltas.emplace_back(
                MakeElectron(1., xs, ys, zs, ts, dx1, dy1, dz1));
          } else {
            if (eExc > m_ethrExc) {
              // Store excitation.
              if (m_storeExcitations) {
                excitations.emplace_back(MakeExcitation(eExc, x2, y2, z2, t2));
              }
            }
          }
        } else if (ipn == 1) {
          const double eistr = ein;
          if (ionmodel > 0) {
            // Calculate secondary energy in ionising collision using
            // five different models.
            Degrade::ionsplit(&ilvl, &e2, &ein, &esec);
          } else {
            // Use Opal, Peterson and Beaty splitting factor.
            esec = wpl * tan(RndmUniform() * atan((e2 - ein) / (2. * wpl)));
            esec = wpl * pow(esec / wpl, 0.9524);
          }
          ein += esec;
          // Store secondary ionisation electron.
          newDeltas.emplace_back(
              MakeElectron(esec, x2, y2, z2, t2, dx2, dy2, dz2));
          ionised = true;
          jsec = newDeltas.size() - 1;
          if (m_fullCascade && lg1 != 0) {
            // Use complete cascade for electron ionisation.
            int64_t j11 = 1;
            Degrade::cascadee(&j11, &kg1, &lg1, &x2, &y2, &z2, &t2, &esec,
                              &igshel);
            // Retrieve electrons.
            for (int64_t k = 1; k <= 400; ++k) {
              int64_t iok = 0;
              double ee = 0., xe = 0., ye = 0., ze = 0., te = 0.;
              double dxe = 0., dye = 0., dze = 0.;
              Degrade::getecasc(&k, &ee, &xe, &ye, &ze, &te, &dxe, &dye, &dze,
                                &iok);
              if (iok != 1) break;
              newDeltas.emplace_back(
                  MakeElectron(ee, xe, ye, ze, te, dxe, dye, dze));
            }
          } else {
            // Store possible shell emissions.
            if (eistr > 30.0) {
              // Test if fluorescence emission.
              if (wklm > 0.0 && RndmUniform() < wklm) {
                // Auger emission and fluorescence.
                if (ng2 > 0) {
                  const double eav = eg2 / ng2;
                  for (int64_t j = 0; j < ng2; ++j) {
                    const double ctheta = 1. - 2. * RndmUniform();
                    const double stheta = sin(acos(ctheta));
                    const double phi = TwoPi * RndmUniform();
                    const double dx = cos(phi) * stheta;
                    const double dy = sin(phi) * stheta;
                    const double dz = ctheta;
                    newDeltas.emplace_back(
                        MakeElectron(eav, x2, y2, z2, t2, dx, dy, dz));
                  }
                }
                if (ng1 > 0) {
                  const double eav = eg1 / ng1;
                  const double dfl = -log(RndmUniformPos()) * dstfl;
                  for (int64_t j = 0; j < ng1; ++j) {
                    const double cthetafl = 1. - 2. * RndmUniform();
                    const double sthetafl = sin(acos(cthetafl));
                    const double phifl = TwoPi * RndmUniform();
                    const double xs = x2 + dfl * sthetafl * cos(phifl);
                    const double ys = y2 + dfl * sthetafl * sin(phifl);
                    const double zs = z2 + dfl * cthetafl;
                    const double ts = t2;
                    const double ctheta = 1. - 2. * RndmUniform();
                    const double stheta = sin(acos(ctheta));
                    const double phi = TwoPi * RndmUniform();
                    const double dx = cos(phi) * stheta;
                    const double dy = sin(phi) * stheta;
                    const double dz = ctheta;
                    newDeltas.emplace_back(
                        MakeElectron(eav, xs, ys, zs, ts, dx, dy, dz));
                  }
                }
              } else {
                // Auger emission without fluorescence.
                const double eav = ec0 / nc0;
                for (int64_t j = 0; j < nc0; ++j) {
                  const double ctheta = 1. - 2. * RndmUniform();
                  const double stheta = sin(acos(ctheta));
                  const double phi = TwoPi * RndmUniform();
                  const double dx = cos(phi) * stheta;
                  const double dy = sin(phi) * stheta;
                  const double dz = ctheta;
                  newDeltas.emplace_back(
                      MakeElectron(eav, x2, y2, z2, t2, dx, dy, dz));
                }
              }
            }
          }
        }
        // Generate scattering angles and update direction after collision.
        const double s1 = 1. + gamma2 * (rgas - 1.);
        const double s2 = (s1 * s1) / (s1 - 1.);
        double ctheta0 = 0.;
        if (index == 1) {
          // Anisotropic scattering
          ctheta0 = 1. - RndmUniform() * an;
          if (RndmUniform() > ps) ctheta0 = -ctheta0;
        } else if (index == 2) {
          // Anisotropic scattering
          ctheta0 = 1. - 2 * RndmUniform();
          ctheta0 = (ctheta0 + ps) / (1. + ps * ctheta0);
        } else {
          // Isotropic scattering
          ctheta0 = 1. - 2. * RndmUniform();
        }
        const double theta0 = acos(ctheta0);
        const double phi0 = TwoPi * RndmUniform();
        const double sphi0 = sin(phi0);
        const double cphi0 = cos(phi0);
        if (e2 < ein) ein = 0.;
        const double arg1 = std::max(1. - s1 * ein / e2, 1.e-20);
        const double d = 1. - ctheta0 * sqrt(arg1);
        // Update electron energy.
        e1 = std::max(e2 * (1. - ein / (s1 * e2) - 2. * d / s2), 1.e-20);
        const double q = std::min(sqrt((e2 / e1) * arg1) / s1, 1.);
        const double theta = asin(q * sin(theta0));
        double ctheta = cos(theta);
        if (ctheta0 < 0.) {
          const double u = (s1 - 1.) * (s1 - 1.) / arg1;
          if (ctheta0 * ctheta0 > u) ctheta = -ctheta;
        }
        double stheta = sin(theta);
        dz2 = std::min(dz2, 1.);
        const double argz = sqrt(dx2 * dx2 + dy2 * dy2);
        if (argz > 0.) {
          dz1 = dz2 * ctheta + argz * stheta * sphi0;
          dy1 = dy2 * ctheta +
                (stheta / argz) * (dx2 * cphi0 - dy2 * dz2 * sphi0);
          dx1 = dx2 * ctheta -
                (stheta / argz) * (dy2 * cphi0 + dx2 * dz2 * sphi0);
          if (ionised) {
            // Use free kinematics for ionisation secondary angles.
            double sthetas = std::min(stheta * sqrt(e1 / esec), 1.);
            double cthetas = cos(asin(sthetas));
            if (ctheta < 0.0) cthetas = -cthetas;
            double phis = phi0 + Pi;
            if (phis > TwoPi) phis = phi0 - TwoPi;
            const double sphis = sin(phis);
            const double cphis = cos(phis);
            newDeltas[jsec].dz = dz2 * cthetas + argz * sthetas * sphis;
            newDeltas[jsec].dy =
                dy2 * cthetas +
                (sthetas / argz) * (dx2 * cphis - dy2 * dz2 * sphis);
            newDeltas[jsec].dx =
                dx2 * cthetas -
                (sthetas / argz) * (dy2 * cphis + dx2 * dz2 * sphis);
          }
        } else {
          dz1 = ctheta;
          dx1 = cphi0 * stheta;
          dy1 = sphi0 * stheta;
          if (ionised) {
            // Use free kinematics for ionisation secondary angles.
            double sthetas = std::min(stheta * sqrt(e1 / esec), 1.);
            double cthetas = cos(asin(sthetas));
            if (ctheta < 0.) cthetas = -cthetas;
            double phis = phi0 + Pi;
            if (phis > TwoPi) phis = phi0 - TwoPi;
            newDeltas[jsec].dz = cthetas;
            newDeltas[jsec].dx = cos(phis) * sthetas;
            newDeltas[jsec].dy = sin(phis) * sthetas;
          }
        }
      }
      if (attached) continue;
      thermalisedElectrons.emplace_back(
          MakeElectron(e1, x1, y1, z1, t1, dx1, dy1, dz1));
    }
    deltas.swap(newDeltas);
    newDeltas.clear();
  }
  return std::make_pair(thermalisedElectrons, excitations);
}

void TrackDegrade::SetupPenning(Medium* medium, std::array<double, 6>& rP,
                                std::array<double, 6>& dP) {
  rP.fill(0.);
  dP.fill(0.);
  auto gas = dynamic_cast<MediumGas*>(medium);
  if (!gas) return;
  const std::size_t nComponents = medium->GetNumberOfComponents();
  if (m_debug) std::cout << m_className << "::SetupPenning:\n";
  for (std::size_t i = 0; i < nComponents; ++i) {
    std::string name;
    double f;
    medium->GetComponent(i, name, f);
    gas->GetPenningTransfer(name, rP[i], dP[i]);
    if (m_debug) std::printf("  %-15s %5.3f\n", name.c_str(), rP[i]);
  }
}

bool TrackDegrade::IsInside(const double x, const double y, const double z) {
  // Check if the point is inside the drift area.
  if (!m_sensor->IsInArea(x, y, z)) return false;
  // Check if the point is inside a medium.
  Medium* medium = m_sensor->GetMedium(x, y, z);
  if (!medium) return false;
  // Make sure the medium has not changed.
  if (medium->GetName() != m_mediumName ||
      fabs(medium->GetPressure() - m_pressure) > 1.e-4 ||
      fabs(medium->GetTemperature() - m_temperature) > 1.e-4 ||
      !medium->IsIonisable() || !medium->IsGas()) {
    return false;
  }
  return true;
}

}  // namespace Garfield
