#include "Garfield/TrackElectron.hh"

#include <cmath>
#include <iostream>
#include <numeric>
#include <string>

#include "Garfield/Exceptions.hh"
#include "Garfield/FundamentalConstants.hh"
#include "Garfield/GarfieldConstants.hh"
#include "Garfield/Medium.hh"
#include "Garfield/Random.hh"
#include "Garfield/Sensor.hh"

namespace Garfield {

TrackElectron::TrackElectron() : Track("Electron") {
  // Setup the particle properties.
  m_q = -1;
  m_spin = 1;
  m_mass = ElectronMass;
  m_isElectron = true;
  SetBetaGamma(3.);
  m_particleName = "electron";
}

void TrackElectron::SetParticle(const std::string& particle) {
  if (particle != "electron" && particle != "e" && particle != "e-")
    throw Exception("Only electrons are allowed");
}

bool TrackElectron::NewTrack(const double x0, const double y0, const double z0,
                             const double t0, const double dx0,
                             const double dy0, const double dz0) {
  // Make sure the sensor has been set.
  if (!m_sensor) throw Exception("Sensor is not defined");
  // Reset the list of clusters.
  m_clusters.clear();

  // Make sure the medium at this location is an ionisable gas.
  Medium* medium = m_sensor->GetMedium(x0, y0, z0);
  if (!medium || !medium->IsIonisable() || !medium->IsGas())
    throw Exception("No ionisable gas medium at initial position");
  std::vector<Parameters> par;
  std::vector<double> frac;
  if (!Setup(medium, par, frac))
    throw Exception(std::string("Properties of " + medium->GetName() +
                                " are not implemented")
                        .c_str());
  const std::string mediumName = medium->GetName();
  const double density = medium->GetNumberDensity();

  const size_t nComponents = frac.size();
  std::vector<double> prob(nComponents, 0.);
  double mfp = 0., dedx = 0.;
  if (!Update(density, m_beta2, par, frac, prob, mfp, dedx))
    throw Exception("Cross-sections could not be calculated");
  m_mfp = mfp;
  m_dedx = dedx;

  double x = x0;
  double y = y0;
  double z = z0;
  double t = t0;
  double dx = dx0;
  double dy = dy0;
  double dz = dz0;
  const double d = sqrt(dx * dx + dy * dy + dz * dz);
  if (d < Small) {
    RndmDirection(dx, dy, dz);
  } else {
    // Normalize the direction vector.
    const double scale = 1. / d;
    dx *= scale;
    dy *= scale;
    dz *= scale;
  }
  const double dt = 1. / (sqrt(m_beta2) * SpeedOfLight);
  double e0 = ElectronMass * (sqrt(1. / (1. - m_beta2)) - 1.);
  while (e0 > 0.) {
    // Draw a step length and propagate the electron.
    const double step = -m_mfp * log(RndmUniformPos());
    x += step * dx;
    y += step * dy;
    z += step * dz;
    t += step * dt;

    medium = m_sensor->GetMedium(x, y, z);
    if (!medium || !medium->IsIonisable() || medium->GetName() != mediumName ||
        medium->GetNumberDensity() != density) {
      break;
    }
    Cluster cluster;
    cluster.x = x;
    cluster.y = y;
    cluster.z = z;
    cluster.t = t;
    const double r = RndmUniform();
    for (size_t i = 0; i < nComponents; ++i) {
      if (r > prob[i]) continue;
      // Sample secondary electron energy according to
      // Opal-Beaty-Peterson splitting function.
      cluster.esec = Esec(e0, par[i]);
      m_clusters.push_back(std::move(cluster));
      break;
    }
  }
  return true;
}

double TrackElectron::GetClusterDensity() {
  return m_mfp > 0. ? 1. / m_mfp : 0.;
}

double TrackElectron::GetStoppingPower() { return m_dedx; }

bool TrackElectron::Setup(Medium* gas, std::vector<Parameters>& par,
                          std::vector<double>& frac) {
  if (!gas) throw Exception("Medium is not defined");

  const size_t nComponents = gas->GetNumberOfComponents();
  if (nComponents == 0) throw Exception("Composition is not defined");
  par.resize(nComponents);
  frac.assign(nComponents, 0.);

  // Density correction parameters from
  //   R. M. Sternheimer, M. J. Berger, S. M. Seltzer,
  //   Atomic Data and Nuclear Data Tables 30 (1984), 261-271
  for (size_t i = 0; i < nComponents; ++i) {
    std::string gasname = "";
    gas->GetComponent(i, gasname, frac[i]);
    if (gasname == "CF4") {
      par[i].m2 = 7.2;
      par[i].cIon = 93.;
      par[i].x0 = 1.;
      par[i].x1 = 0.;
      par[i].cDens = 0.;
      par[i].aDens = 0.;
      par[i].mDens = 0.;
      par[i].ethr = 15.9;
      par[i].wSplit = 19.5;
    } else if (gasname == "Ar") {
      par[i].m2 = 3.593;
      par[i].cIon = 39.7;
      par[i].x0 = 1.7635;
      par[i].x1 = 4.4855;
      par[i].cDens = 11.9480;
      par[i].aDens = 0.19714;
      par[i].mDens = 2.9618;
      par[i].ethr = 15.75961;
      par[i].wSplit = 15.;
    } else if (gasname == "He") {
      par[i].m2 = 0.489;
      par[i].cIon = 5.5;
      par[i].x0 = 2.2017;
      par[i].x1 = 3.6122;
      par[i].cDens = 11.1393;
      par[i].aDens = 0.13443;
      par[i].mDens = 5.8347;
      par[i].ethr = 24.58739;
      par[i].wSplit = 10.5;
    } else if (gasname == "He-3") {
      par[i].m2 = 0.489;
      par[i].cIon = 5.5;
      par[i].x0 = 2.2017;
      par[i].x1 = 3.6122;
      par[i].cDens = 11.1393;
      par[i].aDens = 0.13443;
      par[i].mDens = 5.8347;
      par[i].ethr = 24.58739;
      par[i].wSplit = 10.5;
    } else if (gasname == "Ne") {
      par[i].m2 = 1.69;
      par[i].cIon = 17.8;
      par[i].x0 = 2.0735;
      par[i].x1 = 4.6421;
      par[i].cDens = 11.9041;
      par[i].aDens = 0.08064;
      par[i].mDens = 3.5771;
      par[i].ethr = 21.56454;
      par[i].wSplit = 19.5;
    } else if (gasname == "Kr") {
      par[i].m2 = 5.5;
      par[i].cIon = 56.9;
      par[i].x0 = 1.7158;
      par[i].x1 = 5.0748;
      par[i].cDens = 12.5115;
      par[i].aDens = 0.07446;
      par[i].mDens = 3.4051;
      par[i].ethr = 13.996;
      par[i].wSplit = 21.;
    } else if (gasname == "Xe") {
      par[i].m2 = 8.04;
      par[i].cIon = 75.25;
      par[i].x0 = 1.5630;
      par[i].x1 = 4.7371;
      par[i].cDens = 12.7281;
      par[i].aDens = 0.23314;
      par[i].mDens = 2.7414;
      par[i].ethr = 12.129843;
      par[i].wSplit = 23.7;
    } else if (gasname == "CH4") {
      par[i].m2 = 3.75;
      par[i].cIon = 42.5;
      par[i].x0 = 1.6263;
      par[i].x1 = 3.9716;
      par[i].cDens = 9.5243;
      par[i].aDens = 0.09253;
      par[i].mDens = 3.6257;
      par[i].ethr = 12.65;
      par[i].wSplit = 8.;
    } else if (gasname == "iC4H10") {
      par[i].m2 = 15.5;
      par[i].cIon = 160.;
      par[i].x0 = 1.3788;
      par[i].x1 = 3.7524;
      par[i].cDens = 8.5633;
      par[i].aDens = 0.10852;
      par[i].mDens = 3.4884;
      par[i].ethr = 10.67;
      par[i].wSplit = 7.;
    } else if (gasname == "CO2") {
      par[i].m2 = 5.6;
      par[i].cIon = 57.91;
      par[i].x0 = 1.6294;
      par[i].x1 = 4.1825;
      par[i].aDens = 0.11768;
      par[i].mDens = 3.3227;
      par[i].ethr = 13.777;
      par[i].wSplit = 13.;
    } else if (gasname == "N2") {
      par[i].m2 = 3.35;
      par[i].cIon = 38.1;
      par[i].x0 = 1.7378;
      par[i].x1 = 4.1323;
      par[i].cDens = 10.5400;
      par[i].aDens = 0.15349;
      par[i].mDens = 3.2125;
      par[i].ethr = 15.581;
      par[i].wSplit = 13.8;
    } else {
      std::cerr << "TrackElectron::Setup: Parameters for " << gasname
                << " are not implemented.\n";
      return false;
    }
  }
  return true;
}

bool TrackElectron::Update(const double density, const double beta2,
                           const std::vector<Parameters>& par,
                           const std::vector<double>& frac,
                           std::vector<double>& prob, double& mfp,
                           double& dedx) {
  if (beta2 <= 0.) return false;
  const double lnBg2 = log(beta2 / (1. - beta2));
  // Primary energy
  const double e0 = ElectronMass * (sqrt(1. / (1. - beta2)) - 1.);
  // Parameter X in the Sternheimer fit formula
  const double eta = density / LoschmidtNumber;
  const double x = 0.5 * (lnBg2 + log(eta)) / log(10.);

  const size_t n = par.size();
  prob.assign(n, 0.);
  dedx = 0.;
  for (size_t i = 0; i < n; ++i) {
    const double delta = Delta(x, par[i]);
    prob[i] = frac[i] * (par[i].m2 * (lnBg2 - beta2 - delta) + par[i].cIon);
    // Calculate the mean secondary electron energy.
    const double ew = (e0 - par[i].ethr) / (2 * par[i].wSplit);
    const double emean = (par[i].wSplit / (2 * atan(ew))) * log1p(ew * ew);
    dedx += prob[i] * emean;
  }
  // Normalise and add up the probabilities.
  const double psum = std::accumulate(prob.begin(), prob.end(), 0.);
  if (psum <= 0.) throw Exception("Total cross-section <= 0");
  const double scale = 1. / psum;
  for (size_t i = 0; i < n; ++i) {
    prob[i] *= scale;
    if (i > 0) prob[i] += prob[i - 1];
  }
  // Compute mean free path and stopping power.
  constexpr double prefactor =
      4 * Pi * HbarC * HbarC / (ElectronMass * ElectronMass);
  const double cs = prefactor * psum / beta2;
  mfp = 1. / (cs * density);
  dedx *= density * prefactor / beta2;
  return true;
}

double TrackElectron::Delta(const double x, const Parameters& par) {
  double delta = 0.;
  if (par.x0 < par.x1 && x >= par.x0) {
    delta = 2 * log(10.) * x - par.cDens;
    if (x < par.x1) {
      delta += par.aDens * pow(par.x1 - x, par.mDens);
    }
  }
  return delta;
}

double TrackElectron::Esec(const double e0, const Parameters& par) {
  double esec = par.wSplit *
                tan(RndmUniform() * atan((e0 - par.ethr) / (2. * par.wSplit)));
  return par.wSplit * pow(esec / par.wSplit, 0.9524);
}
}  // namespace Garfield
