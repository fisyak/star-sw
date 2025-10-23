#include "Garfield/TrackHeed.hh"

#include <algorithm>
#include <cmath>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "Garfield/Exceptions.hh"
#include "Garfield/GarfieldConstants.hh"
#include "Garfield/Medium.hh"
#include "Garfield/Random.hh"
#include "Garfield/Sensor.hh"
#include "HeedChamber.hh"
#include "HeedFieldMap.hh"
#include "heed++/code/ElElasticScat.h"
#include "heed++/code/EnergyMesh.h"
#include "heed++/code/HeedDeltaElectron.h"
#include "heed++/code/HeedMatterDef.h"
#include "heed++/code/HeedParticle.h"
#include "heed++/code/HeedPhoton.h"
#include "heed++/code/PairProd.h"
#include "heed++/code/PhotoAbsCS.h"
#include "heed++/code/PhotoAbsCSLib.h"
#include "wcpplib/matter/GasDef.h"
#include "wcpplib/matter/MatterDef.h"

namespace {

void ClearBank(std::vector<Heed::gparticle*>& bank) {
  for (auto particle : bank)
    if (particle) delete particle;
  bank.clear();
}

Heed::vec NormaliseDirection(const double dx0, const double dy0,
                             const double dz0) {
  double dx = dx0, dy = dy0, dz = dz0;
  const double d = sqrt(dx * dx + dy * dy + dz * dz);
  if (d < Garfield::Small) {
    // Null vector. Sample the direction isotropically.
    Garfield::RndmDirection(dx, dy, dz);
  } else {
    // Normalise the direction vector.
    const double scale = 1. / d;
    dx *= scale;
    dy *= scale;
    dz *= scale;
  }
  return Heed::vec(dx, dy, dz);
}

Heed::MolecPhotoAbsCS makeMPACS(const std::string& atom, const int n,
                                const double w = 0.) {
  return Heed::MolecPhotoAbsCS(Heed::PhotoAbsCSLib::getAPACS(atom), n, w);
}

Heed::MolecPhotoAbsCS makeMPACS(const std::string& atom1, const int n1,
                                const std::string& atom2, const int n2,
                                const double w = 0.) {
  return Heed::MolecPhotoAbsCS(Heed::PhotoAbsCSLib::getAPACS(atom1), n1,
                               Heed::PhotoAbsCSLib::getAPACS(atom2), n2, w);
}

Heed::MolecPhotoAbsCS makeMPACS(const std::string& atom1, const int n1,
                                const std::string& atom2, const int n2,
                                const std::string& atom3, const int n3,
                                const double w = 0.) {
  return Heed::MolecPhotoAbsCS(Heed::PhotoAbsCSLib::getAPACS(atom1), n1,
                               Heed::PhotoAbsCSLib::getAPACS(atom2), n2,
                               Heed::PhotoAbsCSLib::getAPACS(atom3), n3, w);
}

}  // namespace

// Actual class implementation

namespace Garfield {

TrackHeed::TrackHeed(Sensor* sensor) : TrackHeed() { m_sensor = sensor; }

TrackHeed::TrackHeed() : Track("Heed") { m_fieldMap.reset(new HeedFieldMap()); }

TrackHeed::~TrackHeed() {}

bool TrackHeed::NewTrack(const double x0, const double y0, const double z0,
                         const double t0, const double dx0, const double dy0,
                         const double dz0) {
  // Make sure the sensor has been set.
  if (!m_sensor) throw Exception("Sensor is not defined");
  m_hasActiveTrack = false;
  bool update = false;
  if (!UpdateBoundingBox(update)) return false;

  // Make sure the initial position is inside an ionisable medium.
  Medium* medium = m_sensor->GetMedium(x0, y0, z0);
  if (!medium || !medium->IsIonisable())
    throw Exception("No ionisable medium at initial position");

  // Check if the medium has changed since the last call.
  if (medium->GetName() != m_mediumName ||
      fabs(medium->GetMassDensity() - m_mediumDensity) > 1.e-9) {
    m_isChanged = true;
  }

  // If medium, particle or bounding box have changed,
  // update the cross-sections.
  if (m_isChanged) {
    if (!Initialise(medium)) return false;
    m_isChanged = false;
    m_mediumName = medium->GetName();
    m_mediumDensity = medium->GetMassDensity();
  }

  // Reset the list of clusters.
  m_clusters.clear();
  m_cluster = 0;

  // Set the velocity vector.
  Heed::vec velocity = NormaliseDirection(dx0, dy0, dz0);
  velocity = velocity * Heed::CLHEP::c_light * GetBeta();

  if (m_debug) {
    std::cout << m_className << "::NewTrack:\n    Track starts at (" << x0
              << ", " << y0 << ", " << z0 << ") at time " << t0 << "\n";
  }

  // Initial position (shift with respect to bounding box center and
  // convert from cm to mm).
  Heed::point p0((x0 - m_cX) * 10., (y0 - m_cY) * 10., (z0 - m_cZ) * 10.);

  // Setup the particle.
  Heed::particle_def* particleType = &Heed::muon_minus_def;
  if (m_particleName == "e-") {
    particleType = &Heed::electron_def;
  } else if (m_particleName == "e+") {
    particleType = &Heed::positron_def;
  } else if (m_particleName == "mu-") {
    particleType = &Heed::muon_minus_def;
  } else if (m_particleName == "mu+") {
    particleType = &Heed::muon_plus_def;
  } else if (m_particleName == "pi-") {
    particleType = &Heed::pi_minus_meson_def;
  } else if (m_particleName == "pi+") {
    particleType = &Heed::pi_plus_meson_def;
  } else if (m_particleName == "K-") {
    particleType = &Heed::K_minus_meson_def;
  } else if (m_particleName == "K+") {
    particleType = &Heed::K_plus_meson_def;
  } else if (m_particleName == "p") {
    particleType = &Heed::proton_def;
  } else if (m_particleName == "pbar") {
    particleType = &Heed::anti_proton_def;
  } else if (m_particleName == "d") {
    particleType = &Heed::deuteron_def;
  } else if (m_particleName == "alpha") {
    particleType = &Heed::alpha_particle_def;
  } else if (m_particleName == "exotic") {
    // User defined particle
    m_particle_def.reset(new Heed::particle_def(Heed::pi_plus_meson_def));
    m_particle_def->set_mass(m_mass * 1.e-6);
    m_particle_def->set_charge(m_q);
    particleType = m_particle_def.get();
  } else {
    // Not a predefined particle, use muon definition.
    if (m_q > 0.) {
      particleType = &Heed::muon_minus_def;
    } else {
      particleType = &Heed::muon_plus_def;
    }
  }

  Heed::HeedParticle particle(m_chamber.get(), p0, velocity, t0, particleType,
                              m_fieldMap.get(), m_coulombScattering);
  if (m_useBfieldAuto) {
    m_fieldMap->UseBfield(m_sensor->HasMagneticField());
  }
  // Set the step limits.
  particle.set_step_limits(m_maxStep * Heed::CLHEP::cm,
                           m_radStraight * Heed::CLHEP::cm,
                           m_stepAngleStraight * Heed::CLHEP::rad,
                           m_stepAngleCurved * Heed::CLHEP::rad);
  // Transport the particle.
  std::vector<Heed::gparticle*> particleBank;
  if (m_oneStepFly) {
    particle.fly(particleBank, true);
  } else {
    particle.fly(particleBank);
  }

  // Sort the clusters by time.
  std::sort(particleBank.begin(), particleBank.end(),
            [](Heed::gparticle* p1, Heed::gparticle* p2) {
              return p1->time() < p2->time();
            });
  // Loop over the clusters (virtual photons) created by the particle.
  for (auto gp : particleBank) {
    // Convert the particle to a (virtual) photon.
    Heed::HeedPhoton* virtualPhoton = dynamic_cast<Heed::HeedPhoton*>(gp);
    if (!virtualPhoton) {
      std::cerr << m_className << "::NewTrack:\n"
                << "    Particle is not a virtual photon. Program bug!\n";
      // Skip this one.
      continue;
    }
    if (!AddCluster(virtualPhoton, m_clusters)) {
      if (!m_crossInactiveMedia) break;
    }
  }
  ClearBank(particleBank);
  Heed::gparticle::reset_counter();
  m_cluster = m_clusters.size() + 2;

  m_hasActiveTrack = true;

  // Plot the track, if requested.
  if (m_viewer) {
    PlotNewTrack(x0, y0, z0);
    for (const auto& cluster : m_clusters) {
      PlotCluster(cluster.x, cluster.y, cluster.z);
    }
  }
  return true;
}

double TrackHeed::GetClusterDensity() {
  if (!m_transferCs)
    throw Exception("Ionisation cross-section is not available");
  return m_transferCs->quanC;
}

double TrackHeed::GetStoppingPower() {
  if (!m_transferCs)
    throw Exception("Ionisation cross-section is not available");
  return m_transferCs->meanC1 * 1.e6;
}

bool TrackHeed::AddCluster(Heed::HeedPhoton* virtualPhoton,
                           std::vector<Cluster>& clusters) {
  // Get the location of the interaction (convert from mm to cm
  // and shift with respect to bounding box center).
  const double xc = virtualPhoton->position().x * 0.1 + m_cX;
  const double yc = virtualPhoton->position().y * 0.1 + m_cY;
  const double zc = virtualPhoton->position().z * 0.1 + m_cZ;
  const double tc = virtualPhoton->time();

  // Make sure the clusters is inside the drift area and active medium.
  if (!IsInside(xc, yc, zc)) return false;

  Cluster cluster;
  cluster.x = xc;
  cluster.y = yc;
  cluster.z = zc;
  cluster.t = tc;
  // Get the transferred energy (convert from MeV to eV).
  cluster.energy = virtualPhoton->m_energy * 1.e6;
  cluster.extra = 0.;
  // Add the first ion (at the position of the cluster).
  Electron ion;
  ion.x = xc;
  ion.y = yc;
  ion.z = zc;
  ion.t = tc;
  cluster.ions.push_back(std::move(ion));

  // Transport the virtual photon.
  std::vector<Heed::gparticle*> secondaries;
  virtualPhoton->fly(secondaries);
  while (!secondaries.empty()) {
    std::vector<Heed::gparticle*> newSecondaries;
    // Loop over the secondaries.
    for (auto secondary : secondaries) {
      // Is the secondary a delta electron?
      auto delta = dynamic_cast<Heed::HeedDeltaElectron*>(secondary);
      if (delta) {
        cluster.extra += delta->kinetic_energy() * 1.e6;
        const double x = delta->position().x * 0.1 + m_cX;
        const double y = delta->position().y * 0.1 + m_cY;
        const double z = delta->position().z * 0.1 + m_cZ;
        if (!IsInside(x, y, z)) continue;
        if (m_doDeltaTransport) {
          // Transport the delta electron.
          delta->fly(newSecondaries);
          // Add the conduction electrons and ions to the list.
          AddElectrons(delta->conduction_electrons, cluster.electrons);
          AddElectrons(delta->conduction_ions, cluster.ions);
        } else {
          // Add the delta electron to the list, for later use.
          Electron deltaElectron;
          deltaElectron.x = delta->position().x * 0.1 + m_cX;
          deltaElectron.y = delta->position().y * 0.1 + m_cY;
          deltaElectron.z = delta->position().z * 0.1 + m_cZ;
          deltaElectron.t = delta->time();
          deltaElectron.e = delta->kinetic_energy() * 1.e6;
          deltaElectron.dx = delta->direction().x;
          deltaElectron.dy = delta->direction().y;
          deltaElectron.dz = delta->direction().z;
          cluster.electrons.push_back(std::move(deltaElectron));
        }
        continue;
      }
      // Is the secondary a real photon?
      auto photon = dynamic_cast<Heed::HeedPhoton*>(secondary);
      if (!photon) {
        std::cerr << m_className << "::AddCluster:\n"
                  << "    Particle is neither an electron nor a photon.\n";
        continue;
      }
      cluster.extra += photon->m_energy * 1.e6;
      const double x = photon->position().x * 0.1 + m_cX;
      const double y = photon->position().y * 0.1 + m_cY;
      const double z = photon->position().z * 0.1 + m_cZ;
      if (!IsInside(x, y, z)) continue;
      // Transport the photon.
      if (m_doPhotonReabsorption) {
        photon->fly(newSecondaries);
      } else {
        Photon unabsorbedPhoton;
        unabsorbedPhoton.x = photon->position().x * 0.1 + m_cX;
        unabsorbedPhoton.y = photon->position().y * 0.1 + m_cY;
        unabsorbedPhoton.z = photon->position().z * 0.1 + m_cZ;
        unabsorbedPhoton.t = photon->time();
        unabsorbedPhoton.e = photon->m_energy * 1.e6;
        unabsorbedPhoton.dx = photon->direction().x;
        unabsorbedPhoton.dy = photon->direction().y;
        unabsorbedPhoton.dz = photon->direction().z;
        cluster.photons.push_back(std::move(unabsorbedPhoton));
      }
    }
    for (auto secondary : secondaries)
      if (secondary) delete secondary;
    secondaries.clear();
    secondaries.swap(newSecondaries);
  }
  clusters.push_back(std::move(cluster));
  return true;
}

void TrackHeed::AddElectrons(
    const std::vector<Heed::HeedCondElectron>& conductionElectrons,
    std::vector<Electron>& electrons) {
  for (const auto& conductionElectron : conductionElectrons) {
    Electron electron;
    electron.x = conductionElectron.x * 0.1 + m_cX;
    electron.y = conductionElectron.y * 0.1 + m_cY;
    electron.z = conductionElectron.z * 0.1 + m_cZ;
    electron.t = conductionElectron.time;
    electrons.push_back(std::move(electron));
  }
}

bool TrackHeed::GetCluster(double& xc, double& yc, double& zc, double& tc,
                           int& ne, double& ec, double& extra) {
  int ni = 0, np = 0;
  return GetCluster(xc, yc, zc, tc, ne, ni, np, ec, extra);
}

bool TrackHeed::GetCluster(double& xc, double& yc, double& zc, double& tc,
                           int& ne, int& ni, double& ec, double& extra) {
  int np = 0;
  return GetCluster(xc, yc, zc, tc, ne, ni, np, ec, extra);
}

bool TrackHeed::GetCluster(double& xc, double& yc, double& zc, double& tc,
                           int& ne, int& ni, int& np, double& ec,
                           double& extra) {
  // Initialise.
  xc = yc = zc = tc = ec = extra = 0.;
  ne = ni = np = 0;

  if (m_clusters.empty()) return false;
  // Increment the cluster index.
  if (m_cluster < m_clusters.size()) {
    ++m_cluster;
  } else if (m_cluster > m_clusters.size()) {
    m_cluster = 0;
  }
  if (m_cluster >= m_clusters.size()) return false;

  ne = m_clusters[m_cluster].electrons.size();
  ni = m_clusters[m_cluster].ions.size();
  np = m_clusters[m_cluster].photons.size();
  xc = m_clusters[m_cluster].x;
  yc = m_clusters[m_cluster].y;
  zc = m_clusters[m_cluster].z;
  tc = m_clusters[m_cluster].t;
  ec = m_clusters[m_cluster].energy;
  extra = m_clusters[m_cluster].extra;
  return true;
}

bool TrackHeed::GetElectron(const std::size_t i, double& x, double& y,
                            double& z, double& t, double& e, double& dx,
                            double& dy, double& dz) {
  if (m_clusters.empty() || m_cluster >= m_clusters.size()) return false;
  // Make sure an electron with this number exists.
  if (i >= m_clusters[m_cluster].electrons.size())
    throw Exception("Index out of range");
  const auto& electron = m_clusters[m_cluster].electrons[i];
  x = electron.x;
  y = electron.y;
  z = electron.z;
  t = electron.t;
  e = electron.e;
  dx = electron.dx;
  dy = electron.dy;
  dz = electron.dz;
  return true;
}

bool TrackHeed::GetIon(const std::size_t i, double& x, double& y, double& z,
                       double& t) const {
  if (m_clusters.empty() || m_cluster >= m_clusters.size()) return false;
  // Make sure an ion with this index exists.
  if (i >= m_clusters[m_cluster].ions.size())
    throw Exception("Index out of range");
  const auto& ion = m_clusters[m_cluster].ions[i];
  x = ion.x;
  y = ion.y;
  z = ion.z;
  t = ion.t;
  return true;
}

bool TrackHeed::GetPhoton(const std::size_t i, double& x, double& y, double& z,
                          double& t, double& e, double& dx, double& dy,
                          double& dz) const {
  if (m_clusters.empty() || m_cluster >= m_clusters.size()) return false;
  // Make sure a photon with this index exists.
  if (i >= m_clusters[m_cluster].photons.size())
    throw Exception("Index out of range");
  const auto& photon = m_clusters[m_cluster].photons[i];
  x = photon.x;
  y = photon.y;
  z = photon.z;
  t = photon.t;
  e = photon.e;
  dx = photon.dx;
  dy = photon.dy;
  dz = photon.dz;
  return true;
}

TrackHeed::Cluster TrackHeed::TransportDeltaElectron(
    const double x0, const double y0, const double z0, const double t0,
    const double e0, const double dx0, const double dy0, const double dz0) {
  Cluster cluster;
  // Check if delta electron transport was disabled.
  if (!m_doDeltaTransport) {
    std::cerr << m_className << "::TransportDeltaElectron:\n"
              << "    Delta electron transport has been switched off.\n";
    return cluster;
  }

  // Make sure the sensor has been set.
  if (!m_sensor) {
    std::cerr << m_className << "::TransportDeltaElectron:\n"
              << "    Sensor is not defined.\n";
    return cluster;
  }

  bool update = false;
  if (!UpdateBoundingBox(update)) return cluster;

  // Make sure the initial position is inside an ionisable medium.
  Medium* medium = m_sensor->GetMedium(x0, y0, z0);
  if (!medium || !medium->IsIonisable()) {
    std::cerr << m_className << "::TransportDeltaElectron:\n"
              << "    No ionisable medium at initial position.\n";
    return cluster;
  }

  // Check if the medium has changed since the last call.
  if (medium->GetName() != m_mediumName ||
      fabs(medium->GetMassDensity() - m_mediumDensity) > 1.e-9) {
    m_isChanged = true;
    update = true;
    m_hasActiveTrack = false;
  }

  // If medium or bounding box have changed, update the "chamber".
  if (update) {
    if (!Initialise(medium)) return cluster;
    m_mediumName = medium->GetName();
    m_mediumDensity = medium->GetMassDensity();
  }

  // Initial position (shift with respect to bounding box center and
  // convert from cm to mm).
  Heed::point p0((x0 - m_cX) * 10., (y0 - m_cY) * 10., (z0 - m_cZ) * 10.);

  // Make sure the kinetic energy is positive.
  if (e0 <= 0.) {
    // Just create a conduction electron on the spot.
    Electron electron;
    electron.x = x0;
    electron.y = y0;
    electron.z = z0;
    electron.t = t0;
    cluster.electrons.push_back(std::move(electron));
    return cluster;
  }

  // Calculate the speed for the given kinetic energy.
  const double gamma = 1. + e0 / ElectronMass;
  const double beta = sqrt(1. - 1. / (gamma * gamma));
  const double speed = Heed::CLHEP::c_light * beta;
  // Set the velocity vector.
  Heed::vec velocity = NormaliseDirection(dx0, dy0, dz0) * speed;

  // Transport the electron.
  std::vector<Heed::gparticle*> secondaries;
  Heed::HeedDeltaElectron delta(m_chamber.get(), p0, velocity, t0, 0,
                                m_fieldMap.get());
  delta.fly(secondaries);
  ClearBank(secondaries);

  AddElectrons(delta.conduction_electrons, cluster.electrons);
  AddElectrons(delta.conduction_ions, cluster.ions);
  return cluster;
}

void TrackHeed::TransportDeltaElectron(const double x0, const double y0,
                                       const double z0, const double t0,
                                       const double e0, const double dx0,
                                       const double dy0, const double dz0,
                                       int& ne) {
  int ni = 0;
  return TransportDeltaElectron(x0, y0, z0, t0, e0, dx0, dy0, dz0, ne, ni);
}

void TrackHeed::TransportDeltaElectron(const double x0, const double y0,
                                       const double z0, const double t0,
                                       const double e0, const double dx0,
                                       const double dy0, const double dz0,
                                       int& ne, int& ni) {
  m_clusters.clear();
  m_cluster = 0;
  Cluster cluster = TransportDeltaElectron(x0, y0, z0, t0, e0, dx0, dy0, dz0);
  ne = cluster.electrons.size();
  ni = cluster.ions.size();
  m_clusters.push_back(std::move(cluster));
}

TrackHeed::Cluster TrackHeed::TransportPhoton(const double x0, const double y0,
                                              const double z0, const double t0,
                                              const double e0, const double dx0,
                                              const double dy0,
                                              const double dz0) {
  // Make sure the energy is positive.
  if (e0 <= 0.) throw Exception("Photon energy must be positive");
  // Make sure the sensor has been set.
  if (!m_sensor) throw Exception("Sensor is not defined");
  Cluster cluster;
  bool update = false;
  if (!UpdateBoundingBox(update)) return cluster;

  // Make sure the initial position is inside an ionisable medium.
  Medium* medium = m_sensor->GetMedium(x0, y0, z0);
  if (!medium || !medium->IsIonisable()) {
    std::cerr << m_className << "::TransportPhoton:\n"
              << "    No ionisable medium at initial position.\n";
    return cluster;
  }

  // Check if the medium has changed since the last call.
  if (medium->GetName() != m_mediumName ||
      fabs(medium->GetMassDensity() - m_mediumDensity) > 1.e-9) {
    m_isChanged = true;
    update = true;
  }

  // If medium or bounding box have changed, update the "chamber".
  if (update) {
    if (!Initialise(medium)) return cluster;
    m_mediumName = medium->GetName();
    m_mediumDensity = medium->GetMassDensity();
  }

  // Set the direction vector.
  Heed::vec velocity = NormaliseDirection(dx0, dy0, dz0);
  velocity = velocity * Heed::CLHEP::c_light;

  // Initial position (shift with respect to bounding box center and
  // convert from cm to mm).
  Heed::point p0((x0 - m_cX) * 10., (y0 - m_cY) * 10., (z0 - m_cZ) * 10.);

  // Create and transport the photon.
  Heed::HeedPhoton photon(m_chamber.get(), p0, velocity, t0, 0, e0 * 1.e-6,
                          m_fieldMap.get());
  std::vector<Heed::gparticle*> secondaries;
  photon.fly(secondaries);
  if (secondaries.empty()) {
    Photon unabsorbedPhoton;
    unabsorbedPhoton.x = photon.position().x * 0.1 + m_cX;
    unabsorbedPhoton.y = photon.position().y * 0.1 + m_cY;
    unabsorbedPhoton.z = photon.position().z * 0.1 + m_cZ;
    unabsorbedPhoton.t = photon.time();
    unabsorbedPhoton.e = photon.m_energy * 1.e6;
    unabsorbedPhoton.dx = photon.direction().x;
    unabsorbedPhoton.dy = photon.direction().y;
    unabsorbedPhoton.dz = photon.direction().z;
    cluster.photons.push_back(std::move(unabsorbedPhoton));
  }

  while (!secondaries.empty()) {
    std::vector<Heed::gparticle*> newSecondaries;
    // Loop over the particle bank and look for daughter particles.
    for (auto gp : secondaries) {
      // Is it a delta electron?
      auto delta = dynamic_cast<Heed::HeedDeltaElectron*>(gp);
      if (delta) {
        if (m_doDeltaTransport) {
          // Transport the delta electron.
          delta->fly(newSecondaries);
          // Add the conduction electrons and ions to the list.
          AddElectrons(delta->conduction_electrons, cluster.electrons);
          AddElectrons(delta->conduction_ions, cluster.ions);
        } else {
          // Add the delta electron to the list, for later use.
          Electron deltaElectron;
          deltaElectron.x = delta->position().x * 0.1 + m_cX;
          deltaElectron.y = delta->position().y * 0.1 + m_cY;
          deltaElectron.z = delta->position().z * 0.1 + m_cZ;
          deltaElectron.t = delta->time();
          deltaElectron.e = delta->kinetic_energy() * 1.e6;
          deltaElectron.dx = delta->direction().x;
          deltaElectron.dy = delta->direction().y;
          deltaElectron.dz = delta->direction().z;
          cluster.electrons.push_back(std::move(deltaElectron));
        }
        continue;
      }
      // Check if it is a fluorescence photon.
      auto fluorescencePhoton = dynamic_cast<Heed::HeedPhoton*>(gp);
      if (!fluorescencePhoton) {
        std::cerr << m_className << "::TransportPhoton:\n"
                  << "    Unknown secondary particle.\n";
        ClearBank(secondaries);
        ClearBank(newSecondaries);
        return cluster;
      }
      if (m_doPhotonReabsorption) {
        fluorescencePhoton->fly(newSecondaries);
      } else {
        Photon unabsorbedPhoton;
        unabsorbedPhoton.x = fluorescencePhoton->position().x * 0.1 + m_cX;
        unabsorbedPhoton.y = fluorescencePhoton->position().y * 0.1 + m_cY;
        unabsorbedPhoton.z = fluorescencePhoton->position().z * 0.1 + m_cZ;
        unabsorbedPhoton.t = fluorescencePhoton->time();
        unabsorbedPhoton.e = fluorescencePhoton->m_energy * 1.e6;
        unabsorbedPhoton.dx = fluorescencePhoton->direction().x;
        unabsorbedPhoton.dy = fluorescencePhoton->direction().y;
        unabsorbedPhoton.dz = fluorescencePhoton->direction().z;
        cluster.photons.push_back(std::move(unabsorbedPhoton));
      }
    }
    secondaries.swap(newSecondaries);
    ClearBank(newSecondaries);
  }
  ClearBank(secondaries);
  return cluster;
}

void TrackHeed::TransportPhoton(const double x0, const double y0,
                                const double z0, const double t0,
                                const double e0, const double dx0,
                                const double dy0, const double dz0, int& ne) {
  int ni = 0, np = 0;
  TransportPhoton(x0, y0, z0, t0, e0, dx0, dy0, dz0, ne, ni, np);
}

void TrackHeed::TransportPhoton(const double x0, const double y0,
                                const double z0, const double t0,
                                const double e0, const double dx0,
                                const double dy0, const double dz0, int& ne,
                                int& ni) {
  int np = 0;
  TransportPhoton(x0, y0, z0, t0, e0, dx0, dy0, dz0, ne, ni, np);
}

void TrackHeed::TransportPhoton(const double x0, const double y0,
                                const double z0, const double t0,
                                const double e0, const double dx0,
                                const double dy0, const double dz0, int& ne,
                                int& ni, int& np) {
  // Clusters from the current track will be lost.
  m_hasActiveTrack = false;
  m_clusters.clear();
  m_cluster = 0;
  Cluster cluster = TransportPhoton(x0, y0, z0, t0, e0, dx0, dy0, dz0);
  ne = cluster.electrons.size();
  ni = cluster.ions.size();
  np = cluster.photons.size();
  m_clusters.push_back(std::move(cluster));
}

void TrackHeed::EnableElectricField() { m_fieldMap->UseEfield(true); }
void TrackHeed::DisableElectricField() { m_fieldMap->UseEfield(false); }

void TrackHeed::EnableMagneticField() {
  m_fieldMap->UseBfield(true);
  m_useBfieldAuto = false;
}

void TrackHeed::DisableMagneticField() {
  m_fieldMap->UseBfield(false);
  m_useBfieldAuto = false;
}

void TrackHeed::SetEnergyMesh(const double e0, const double e1,
                              const int nsteps) {
  if (fabs(e1 - e0) < Small) {
    std::cerr << m_className << "::SetEnergyMesh:\n"
              << "    Invalid energy range:\n"
              << "    " << e0 << " < E [eV] < " << e1 << "\n";
    return;
  }

  if (nsteps <= 0) throw Exception("Number of intervals must be > 0");

  m_emin = 1.e-6 * std::min(e0, e1);
  m_emax = 1.e-6 * std::max(e0, e1);
  m_nEnergyIntervals = nsteps;
}

void TrackHeed::SetParticleUser(const double m, const double z) {
  if (fabs(z) < Small) throw Exception("Particle cannot have zero charge");
  if (m < Small) throw Exception("Particle mass must be greater than zero");
  m_q = z;
  m_mass = m;
  m_isElectron = false;
  m_spin = 0;
  m_particleName = "exotic";
}

bool TrackHeed::Initialise(Medium* medium, const bool verbose) {
  // Make sure the medium exists.
  if (!medium) throw Exception("Medium* is nullptr");
  // Make sure the path to the Heed database is known.
  std::string databasePath;
  char* dbPath = std::getenv("HEED_DATABASE");
  if (dbPath) {
    databasePath = dbPath;
  } else {
    // Try GARFIELD_INSTALL.
    dbPath = std::getenv("GARFIELD_INSTALL");
    if (dbPath) {
      databasePath = std::string(dbPath) + "/share/Heed/database";
    } else {
      // Try GARFIELD_HOME.
      dbPath = std::getenv("GARFIELD_HOME");
      if (dbPath) {
        databasePath = std::string(dbPath) + "/Heed/heed++/database";
      } else {
      }
    }
  }
  if (databasePath.empty()) {
    std::cerr << m_className << "::Initialise:\n"
              << "    Cannot retrieve database path (none of the"
              << " environment variables HEED_DATABASE, GARFIELD_INSTALL,"
              << " GARFIELD_HOME is defined).\n"
              << "    Cannot proceed.\n";
    return false;
  }
  if (databasePath.back() != '/') databasePath.append("/");

  if (m_debug || verbose) {
    std::cout << m_className << "::Initialise:\n"
              << "    Database path: " << databasePath << "\n";
  }

  // Setup the energy mesh.
  m_energyMesh.reset(new Heed::EnergyMesh(m_emin, m_emax, m_nEnergyIntervals));

  if (medium->IsGas()) {
    if (!SetupGas(medium)) return false;
  } else {
    if (!SetupMaterial(medium)) return false;
  }

  // Energy transfer cross-section
  // Set a flag indicating whether the primary particle is an electron.
  m_transferCs.reset(new Heed::EnTransfCS(1.e-6 * m_mass, GetGamma() - 1.,
                                          m_isElectron, m_matter.get(), m_q));
  if (!m_transferCs->m_ok) {
    std::cerr << m_className << "::Initialise:\n"
              << "    Problems occured when calculating the differential"
              << " cross-section table.\n"
              << "    Results will be inaccurate.\n";
  }
  if (!SetupDelta(databasePath)) return false;

  if (m_debug || verbose) {
    const double nc = m_transferCs->quanC;
    const double dedx = m_transferCs->meanC * 1.e3;
    const double dedx1 = m_transferCs->meanC1 * 1.e3;
    const double w = m_matter->W * 1.e6;
    const double f = m_matter->F;
    const double minI = m_matter->min_ioniz_pot * 1.e6;
    std::cout << m_className << "::Initialise:\n";
    std::cout << "    Cluster density:             " << nc << " cm-1\n";
    std::cout << "    Stopping power (restricted): " << dedx << " keV/cm\n";
    std::cout << "    Stopping power (incl. tail): " << dedx1 << " keV/cm\n";
    std::cout << "    W value:                     " << w << " eV\n";
    std::cout << "    Fano factor:                 " << f << "\n";
    std::cout << "    Min. ionization potential:   " << minI << " eV\n";
  }

  Heed::fixsyscoor primSys(Heed::point(0., 0., 0.), Heed::basis());
  m_chamber.reset(new HeedChamber(primSys, m_lX, m_lY, m_lZ,
                                  *m_transferCs.get(), *m_deltaCs.get()));
  m_fieldMap->SetSensor(m_sensor);
  return true;
}

bool TrackHeed::SetupGas(Medium* medium) {
  // Get temperature and pressure.
  double pressure = medium->GetPressure();
  pressure = (pressure / AtmosphericPressure) * Heed::CLHEP::atmosphere;
  double temperature = medium->GetTemperature();

  const std::size_t nComponents = medium->GetNumberOfComponents();
  if (nComponents < 1) {
    std::cerr << m_className << "::SetupGas:\n"
              << "    Gas " << medium->GetName() << " has zero constituents.\n";
    return false;
  }

  std::vector<Heed::MolecPhotoAbsCS> mpacs;
  std::vector<std::string> notations;
  std::vector<double> fractions;
  for (std::size_t i = 0; i < nComponents; ++i) {
    std::string gasname;
    double frac;
    medium->GetComponent(i, gasname, frac);
    if (gasname == "paraH2" || gasname == "orthoD2" || gasname == "D2") {
      gasname = "H2";
    } else if (gasname == "He-3") {
      gasname = "He";
    } else if (gasname == "CD4") {
      gasname = "CH4";
    } else if (gasname == "iC4H10" || gasname == "nC4H10") {
      gasname = "C4H10";
    } else if (gasname == "neoC5H12" || gasname == "nC5H12") {
      gasname = "C5H12";
    } else if (gasname == "cC3H6") {
      gasname = "C3H6";
    } else if (gasname == "nC3H7OH") {
      gasname = "C3H7OH";
    }
    // Assemble the molecular photoabsorption cross-section.
    if (gasname == "CF4") {
      mpacs.emplace_back(makeMPACS("C for CF4", 1, "F", 4));
    } else if (gasname == "Ar") {
      mpacs.emplace_back(makeMPACS("Ar", 1, 26.4e-6));
    } else if (gasname == "He" || gasname == "He-3") {
      mpacs.emplace_back(makeMPACS("He", 1, 41.3e-6));
    } else if (gasname == "Ne") {
      mpacs.emplace_back(makeMPACS("Ne", 1, 35.4e-6));
    } else if (gasname == "Kr") {
      mpacs.emplace_back(makeMPACS("Kr", 1, 24.4e-6));
    } else if (gasname == "Xe") {
      mpacs.emplace_back(makeMPACS("Xe", 1, 22.1e-6));
    } else if (gasname == "CH4" || gasname == "CD4") {
      mpacs.emplace_back(makeMPACS("C for CH4", 1, "H for CH4", 4, 27.3e-6));
    } else if (gasname == "C2H6") {
      mpacs.emplace_back(makeMPACS("C for C2H6", 2, "H for H2", 6, 25.0e-6));
    } else if (gasname == "C3H8") {
      mpacs.emplace_back(makeMPACS("C for CH4", 3, "H for H2", 8, 24.0e-6));
    } else if (gasname == "C4H10") {
      mpacs.emplace_back(makeMPACS("C for C4H10", 4, "H for H2", 10, 23.4e-6));
    } else if (gasname == "CO2") {
      mpacs.emplace_back(makeMPACS("C for CO2", 1, "O for CO2", 2, 33.0e-6));
    } else if (gasname == "C5H12") {
      mpacs.emplace_back(makeMPACS("C for C4H10", 5, "H for H2", 12, 23.2e-6));
    } else if (gasname == "Water" || gasname == "H2O") {
      mpacs.emplace_back(makeMPACS("H for H2", 2, "O", 1, 29.6e-6));
    } else if (gasname == "O2") {
      mpacs.emplace_back(makeMPACS("O", 2, 30.8e-6));
    } else if (gasname == "N2" || gasname == "N2 (Phelps)") {
      mpacs.emplace_back(makeMPACS("N", 2, 34.8e-6));
    } else if (gasname == "NO") {
      mpacs.emplace_back(makeMPACS("N", 1, "O", 1));
    } else if (gasname == "N2O") {
      mpacs.emplace_back(makeMPACS("N", 2, "O", 1, 34.8e-6));
    } else if (gasname == "C2H4") {
      mpacs.emplace_back(makeMPACS("C for C2H4", 2, "H for H2", 4, 25.8e-6));
    } else if (gasname == "C2H2") {
      mpacs.emplace_back(makeMPACS("C for CH4", 2, "H for H2", 2, 25.8e-6));
    } else if (gasname == "H2" || gasname == "D2") {
      mpacs.emplace_back(makeMPACS("H for H2", 2));
    } else if (gasname == "CO") {
      mpacs.emplace_back(makeMPACS("C for CO2", 1, "O", 1));
    } else if (gasname == "Methylal") {
      // W similar to C4H10
      mpacs.emplace_back(makeMPACS("O", 2, "C for Methylal", 3, "H for H2", 8,
                                   10.0e-6 * 23.4 / 10.55));
    } else if (gasname == "DME") {
      mpacs.emplace_back(makeMPACS("C for Methylal", 2, "H for H2", 6, "O", 1));
    } else if (gasname == "C2F6") {
      mpacs.emplace_back(makeMPACS("C for C2H6", 2, "F", 6));
    } else if (gasname == "SF6") {
      mpacs.emplace_back(makeMPACS("S", 1, "F", 6));
    } else if (gasname == "NH3") {
      mpacs.emplace_back(makeMPACS("N", 1, "H for NH4", 3, 26.6e-6));
    } else if (gasname == "C3H6" || gasname == "cC3H6") {
      mpacs.emplace_back(makeMPACS("C for C2H6", 3, "H for H2", 6));
    } else if (gasname == "CH3OH") {
      mpacs.emplace_back(
          makeMPACS("C for C2H6", 1, "H for H2", 4, "O", 1, 24.7e-6));
    } else if (gasname == "C2H5OH") {
      mpacs.emplace_back(
          makeMPACS("C for C2H6", 2, "H for H2", 6, "O", 1, 24.8e-6));
    } else if (gasname == "C3H7OH") {
      mpacs.emplace_back(makeMPACS("C for C2H6", 3, "H for H2", 8, "O", 1));
    } else if (gasname == "Cs") {
      mpacs.emplace_back(makeMPACS("Cs", 1));
    } else if (gasname == "F2") {
      mpacs.emplace_back(makeMPACS("F", 2));
    } else if (gasname == "CS2") {
      mpacs.emplace_back(makeMPACS("C for CO2", 1, "S", 2));
    } else if (gasname == "COS") {
      mpacs.emplace_back(makeMPACS("C for CO2", 1, "O", 1, "S", 1));
    } else if (gasname == "BF3") {
      mpacs.emplace_back(makeMPACS("B", 1, "F", 3));
    } else if (gasname == "C2HF5") {
      mpacs.emplace_back(makeMPACS("C for C2H6", 2, "H for H2", 1, "F", 5));
    } else if (gasname == "C2H2F4") {
      mpacs.emplace_back(makeMPACS("C for C2H6", 2, "F", 4, "H for H2", 2));
    } else if (gasname == "CHF3") {
      mpacs.emplace_back(makeMPACS("C for CF4", 1, "H for H2", 1, "F", 3));
    } else if (gasname == "CF3Br") {
      mpacs.emplace_back(makeMPACS("C for CF4", 1, "F", 3, "Br", 1));
    } else if (gasname == "C3F8") {
      mpacs.emplace_back(makeMPACS("C for CF4", 3, "F", 8));
    } else if (gasname == "O3") {
      mpacs.emplace_back(makeMPACS("O", 3));
    } else if (gasname == "Hg") {
      mpacs.emplace_back(makeMPACS("Hg", 1));
    } else if (gasname == "H2S") {
      mpacs.emplace_back(makeMPACS("H for H2", 2, "S", 1));
    } else if (gasname == "GeH4") {
      mpacs.emplace_back(makeMPACS("Ge", 1, "H for H2", 4));
    } else if (gasname == "SiH4") {
      mpacs.emplace_back(makeMPACS("Si", 1, "H for H2", 4));
    } else {
      std::cerr << m_className << "::SetupGas:\n"
                << "    Photoabsorption cross-section for " << gasname
                << " is not implemented.\n";
      return false;
    }
    notations.push_back(gasname);
    fractions.push_back(frac);
  }
  if (m_usePacsOutput) {
    std::ofstream pacsfile;
    pacsfile.open("heed_pacs.txt", std::ios::out);
    const int nValues = m_energyMesh->get_q();
    if (nValues > 0) {
      for (int i = 0; i < nValues; ++i) {
        double e = m_energyMesh->get_e(i);
        pacsfile << 1.e6 * e << "  ";
        for (std::size_t j = 0; j < nComponents; ++j) {
          pacsfile << mpacs[j].get_ACS(e) << "  " << mpacs[j].get_ICS(e)
                   << "  ";
        }
        pacsfile << "\n";
      }
    }
    pacsfile.close();
  }

  const std::string gasname = medium->GetName();
  m_gas.reset(new Heed::GasDef(gasname, gasname, nComponents, notations,
                               fractions, pressure, temperature, -1.));

  const double w = std::max(medium->GetW() * 1.e-6, 0.);
  double f = medium->GetFanoFactor();
  if (f <= 0.) f = Heed::standard_factor_Fano;

  m_matter.reset(
      new Heed::HeedMatterDef(m_energyMesh.get(), m_gas.get(), mpacs, w, f));
  return true;
}

bool TrackHeed::SetupMaterial(Medium* medium) {
  // Get temperature and density.
  double temperature = medium->GetTemperature();
  const double density =
      medium->GetMassDensity() * Heed::CLHEP::gram / Heed::CLHEP::cm3;

  const std::size_t nComponents = medium->GetNumberOfComponents();
  std::vector<Heed::AtomPhotoAbsCS*> atPacs(nComponents, nullptr);
  std::vector<std::string> notations;
  std::vector<double> fractions;
  for (std::size_t i = 0; i < nComponents; ++i) {
    std::string materialName;
    double frac;
    medium->GetComponent(i, materialName, frac);
    if (materialName == "C") {
      if (medium->GetName() == "Diamond") {
        atPacs[i] = Heed::PhotoAbsCSLib::getAPACS("Diamond");
      } else {
        atPacs[i] = Heed::PhotoAbsCSLib::getAPACS("C");
      }
    } else if (materialName == "Si") {
      atPacs[i] = Heed::PhotoAbsCSLib::getAPACS("Si crystal");
      // atPacs[i] = Heed::PhotoAbsCSLib::getAPACS("Si G4");
    } else if (materialName == "Ga") {
      atPacs[i] = Heed::PhotoAbsCSLib::getAPACS("Ga for GaAs");
    } else if (materialName == "Ge") {
      atPacs[i] = Heed::PhotoAbsCSLib::getAPACS("Ge crystal");
    } else if (materialName == "As") {
      atPacs[i] = Heed::PhotoAbsCSLib::getAPACS("As for GaAs");
    } else if (materialName == "Cd") {
      atPacs[i] = Heed::PhotoAbsCSLib::getAPACS("Cd for CdTe");
    } else if (materialName == "Te") {
      atPacs[i] = Heed::PhotoAbsCSLib::getAPACS("Te for CdTe");
    } else {
      std::cerr << m_className << "::SetupMaterial:\n"
                << "    Photoabsorption cross-section for " << materialName
                << " is not implemented.\n";
      return false;
    }
    notations.push_back(materialName);
    fractions.push_back(frac);
  }
  if (m_usePacsOutput) {
    std::ofstream pacsfile;
    pacsfile.open("heed_pacs.txt", std::ios::out);
    const int nValues = m_energyMesh->get_q();
    if (nValues > 0) {
      for (int i = 0; i < nValues; ++i) {
        double e = m_energyMesh->get_e(i);
        pacsfile << 1.e6 * e << "  ";
        for (std::size_t j = 0; j < nComponents; ++j) {
          pacsfile << atPacs[j]->get_ACS(e) << "  " << atPacs[j]->get_ICS(e)
                   << "  ";
        }
        pacsfile << "\n";
      }
    }
    pacsfile.close();
  }
  const std::string materialName = medium->GetName();
  m_material.reset(new Heed::MatterDef(materialName, materialName, nComponents,
                                       notations, fractions, density,
                                       temperature));

  double w = medium->GetW() * 1.e-6;
  if (w < 0.) w = 0.;
  double f = medium->GetFanoFactor();
  if (f <= 0.) f = Heed::standard_factor_Fano;

  m_matter.reset(new Heed::HeedMatterDef(m_energyMesh.get(), m_material.get(),
                                         atPacs, w, f));

  return true;
}

bool TrackHeed::SetupDelta(const std::string& databasePath) {
  // Load elastic scattering data.
  std::string filename = databasePath + "cbdel.dat";
  m_elScat.reset(new Heed::ElElasticScat(filename));

  filename = databasePath + "elastic_disp.dat";
  m_lowSigma.reset(new Heed::ElElasticScatLowSigma(m_elScat.get(), filename));

  // Load data for calculation of ionization.
  // Get W value and Fano factor.
  const double w = m_matter->W * 1.e6;
  const double f = m_matter->F;
  filename = databasePath + "delta_path.dat";
  m_pairProd.reset(new Heed::PairProd(filename, w, f));

  m_deltaCs.reset(new Heed::HeedDeltaElectronCS(
      m_matter.get(), m_elScat.get(), m_lowSigma.get(), m_pairProd.get()));
  return true;
}

double TrackHeed::GetW() const { return m_matter->W * 1.e6; }
double TrackHeed::GetFanoFactor() const { return m_matter->F; }

double TrackHeed::GetPhotoAbsorptionCrossSection(const double en) const {
  if (!m_matter) return 0.;
  // Convert eV to MeV.
  const double e = 1.e-6 * en;
  double cs = 0.;
  const auto n = m_matter->apacs.size();
  for (size_t i = 0; i < n; ++i) {
    const double w = m_matter->matter->weight_quan(i);
    cs += m_matter->apacs[i]->get_ACS(e) * w;
  }
  // Convert Mbarn to cm-2.
  return cs * 1.e-18;
}

bool TrackHeed::IsInside(const double x, const double y, const double z) {
  // Check if the point is inside the drift area.
  if (!m_sensor->IsInArea(x, y, z)) return false;
  // Check if the point is inside a medium.
  Medium* medium = m_sensor->GetMedium(x, y, z);
  if (!medium) return false;
  // Make sure the medium has not changed.
  if (medium->GetName() != m_mediumName ||
      fabs(medium->GetMassDensity() - m_mediumDensity) > 1.e-9 ||
      !medium->IsIonisable()) {
    return false;
  }
  return true;
}

bool TrackHeed::UpdateBoundingBox(bool& update) {
  // Get the bounding box.
  double xmin = 0., ymin = 0., zmin = 0.;
  double xmax = 0., ymax = 0., zmax = 0.;
  if (!m_sensor->GetArea(xmin, ymin, zmin, xmax, ymax, zmax)) {
    std::cerr << m_className << "::UpdateBoundingBox: Drift area is not set.\n";
    return false;
  }
  // Check if the bounding box has changed.
  const double lx = fabs(xmax - xmin);
  const double ly = fabs(ymax - ymin);
  const double lz = fabs(zmax - zmin);
  if (m_debug) {
    std::cout << m_className << "::UpdateBoundingBox:\n"
              << "    Bounding box dimensions:\n"
              << "      x: " << lx << " cm\n"
              << "      y: " << ly << " cm\n"
              << "      z: " << lz << " cm\n";
  }
  if (fabs(lx - m_lX) > Small || fabs(ly - m_lY) > Small ||
      fabs(lz - m_lZ) > Small) {
    m_lX = lx;
    m_lY = ly;
    m_lZ = lz;
    m_isChanged = true;
    update = true;
    m_hasActiveTrack = false;
  }
  // Update the center of the bounding box.
  m_cX = (std::isinf(xmin) || std::isinf(xmax)) ? 0. : 0.5 * (xmin + xmax);
  m_cY = (std::isinf(ymin) || std::isinf(ymax)) ? 0. : 0.5 * (ymin + ymax);
  m_cZ = (std::isinf(zmin) || std::isinf(zmax)) ? 0. : 0.5 * (zmin + zmax);
  if (m_debug) {
    std::cout << m_className << "::UpdateBoundingBox:\n"
              << "    Center of bounding box:\n"
              << "      x: " << m_cX << " cm\n"
              << "      y: " << m_cY << " cm\n"
              << "      z: " << m_cZ << " cm\n";
  }

  m_fieldMap->SetSensor(m_sensor);
  m_fieldMap->SetCentre(m_cX, m_cY, m_cZ);

  return true;
}
}  // namespace Garfield
