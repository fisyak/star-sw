#include "Garfield/TrackTrim.hh"

#include <array>
#include <cmath>
#include <fstream>
#include <iostream>
#include <numeric>

#include "Garfield/Exceptions.hh"
#include "Garfield/FundamentalConstants.hh"
#include "Garfield/GarfieldConstants.hh"
#include "Garfield/Medium.hh"
#include "Garfield/Random.hh"
#include "Garfield/Sensor.hh"
#include "Garfield/Utilities.hh"

namespace {

void Rotate(const std::array<double, 3>& f, const std::array<double, 3>& t,
            std::array<double, 3>& a) {
  // T. Moller and J. F. Hughes,
  // Efficiently Building a Matrix to Rotate One Vector to Another, 1999

  // We assume that f and t are unit vectors.
  // Calculate the cross-product.
  std::array<double, 3> v = {f[1] * t[2] - f[2] * t[1],
                             f[2] * t[0] - f[0] * t[2],
                             f[0] * t[1] - f[1] * t[0]};
  const auto v2 = std::inner_product(v.cbegin(), v.cend(), v.cbegin(), 0.);
  if (v2 < Garfield::Small) return;
  const double c = std::inner_product(f.cbegin(), f.cend(), t.cbegin(), 0.);
  const double h = (1. - c) / v2;
  std::array<std::array<double, 3>, 3> r;
  if (fabs(c) > 0.99) {
    // f and t are not parallel.
    r[0][0] = h * v[0] * v[0] + c;
    r[0][1] = h * v[0] * v[1] - v[2];
    r[0][2] = h * v[0] * v[2] + v[1];
    r[1][0] = h * v[0] * v[1] + v[2];
    r[1][1] = h * v[1] * v[1] + c;
    r[1][2] = h * v[1] * v[2] - v[0];
    r[2][0] = h * v[0] * v[2] - v[1];
    r[2][1] = h * v[1] * v[2] + v[0];
    r[2][2] = h * v[2] * v[2] + c;
  } else {
    // f and t are nearly parallel.
    std::array<double, 3> x = {0, 0, 0};
    if (fabs(f[0]) < fabs(f[1]) && fabs(f[0]) < fabs(f[2])) {
      x[0] = 1;
    } else if (fabs(f[1]) < fabs(f[0]) && fabs(f[1]) < fabs(f[2])) {
      x[1] = 1;
    } else {
      x[2] = 1;
    }
    const std::array<double, 3> u = {x[0] - f[0], x[1] - f[1], x[2] - f[2]};
    const std::array<double, 3> g = {x[0] - t[0], x[1] - t[1], x[2] - t[2]};
    const double u2 = std::inner_product(u.cbegin(), u.cend(), u.cbegin(), 0.);
    const double g2 = std::inner_product(g.cbegin(), g.cend(), g.cbegin(), 0.);
    const double ug = std::inner_product(u.cbegin(), u.cend(), g.cbegin(), 0.);
    const double c0 = -2. / u2;
    const double c1 = -2. / g2;
    const double c2 = 4. * ug / (u2 * g2);
    for (size_t i = 0; i < 3; ++i) {
      for (size_t j = 0; j < 3; ++j) {
        r[i][j] = c0 * u[i] * u[j] + c1 * g[i] * g[j] + c2 * g[i] * u[j];
        if (i == j) r[i][j] += 1.;
      }
    }
  }
  // Compute the rotated vector.
  std::array<double, 3> b = {0., 0., 0.};
  for (size_t i = 0; i < 3; ++i) {
    for (size_t j = 0; j < 3; ++j) {
      b[i] += r[i][j] * a[j];
    }
  }
  std::swap(a, b);
}

double Speed(const double ekin, const double mass) {
  const double rk = ekin / mass;
  const double gamma = 1. + rk;
  const double beta2 = rk > 1.e-5 ? 1. - 1. / (gamma * gamma) : 2. * rk;
  return sqrt(beta2) * Garfield::SpeedOfLight;
}

}  // namespace

namespace Garfield {

TrackTrim::TrackTrim() : Track("Trim") { m_q = 1.; }

TrackTrim::TrackTrim(Sensor* sensor) : TrackTrim() { SetSensor(sensor); }

/// Set the projectile charge [-].
void TrackTrim::SetCharge(const double q) {
  if (fabs(q) > 0.) m_q = q;
}

void TrackTrim::SetParticle(const std::string& /*particle*/) {
  std::cerr << m_className << "::SetParticle: Not applicable.\n";
}

bool TrackTrim::ReadFile(const std::string& filename, const std::size_t nIons,
                         const std::size_t nSkip) {
  // TRMREE - Reads the TRIM EXYZ file.

  // Reset.
  m_ekin = 0.;
  m_ions.clear();
  m_ion = 0;
  m_clusters.clear();
  m_cluster = 0;

  std::ifstream infile(filename);
  if (!infile)
    throw Exception(
        std::string("Unable to open the EXYZ file (" + filename + ")").c_str());
  constexpr double Angstrom = 1.e-8;
  std::size_t nRead = 0;
  std::size_t ionNumber = 0;
  bool header = true;
  double mass = 0.;
  std::vector<float> x;
  std::vector<float> y;
  std::vector<float> z;
  std::vector<float> dedx;
  std::vector<float> ekin;
  for (std::string line; std::getline(infile, line);) {
    if (line.find("------- ") != std::string::npos) {
      // Reached the end of the header.
      header = false;
      continue;
    } else if (header) {
      if (line.find("Ion Data: ") != std::string::npos) {
        // Read the next line.
        std::getline(infile, line);
        auto words = tokenize(line);
        if (words.size() >= 3) {
          m_particleName = words[0];
          mass = std::stod(words[1]);
          auto pos = words[2].find("keV");
          if (pos != std::string::npos) {
            m_ekin = 1.e3 * std::stod(words[2].substr(0, pos));
          }
        }
      }
      // Otherwise, skip the header.
      continue;
    }
    auto words = tokenize(line);
    if (words.size() < 6) {
      std::cerr << m_className << "::ReadFile: Unexpected line:\n"
                << line << "\n";
      continue;
    }
    if (ionNumber != std::stoul(words[0])) {
      // New ion.
      if (ionNumber > 0) {
        if (nRead >= nSkip) AddIon(x, y, z, dedx, ekin);
        x.clear();
        y.clear();
        z.clear();
        dedx.clear();
        ekin.clear();
        ++nRead;
        // Stop if we are done reading the requested number of ions.
        if (nIons > 0 && m_ions.size() >= nIons) break;
      }
      ionNumber = std::stoi(words[0]);
    }
    if (nRead < nSkip) continue;
    // Convert coordinates to cm.
    x.push_back(std::stof(words[2]) * Angstrom);
    y.push_back(std::stof(words[3]) * Angstrom);
    z.push_back(std::stof(words[4]) * Angstrom);
    // Convert stopping power from eV/A to eV/cm.
    dedx.push_back(std::stof(words[5]) / Angstrom);
    // Convert ion energy from keV to eV.
    ekin.push_back(std::stof(words[1]) * 1.e3);
  }
  infile.close();
  AddIon(x, y, z, dedx, ekin);
  std::cout << m_className << "::ReadFile: Read energy vs position for "
            << m_ions.size() << " ions.\n";
  if (m_ekin > 0. && mass > 0.) {
    std::cout << "    Initial kinetic energy set to " << m_ekin * 1.e-3
              << " keV. Mass number: " << mass << ".\n";
    m_mass = AtomicMassUnitElectronVolt * mass;
    SetKineticEnergy(m_ekin);
  }
  return true;
}

void TrackTrim::AddIon(const std::vector<float>& x, const std::vector<float>& y,
                       const std::vector<float>& z,
                       const std::vector<float>& dedx,
                       const std::vector<float>& ekin) {
  const size_t nPoints = x.size();
  if (nPoints < 2) return;
  std::vector<std::array<float, 6> > path;
  for (size_t i = 0; i < nPoints - 1; ++i) {
    const float dx = x[i + 1] - x[i];
    const float dy = y[i + 1] - y[i];
    const float dz = z[i + 1] - z[i];
    const float dmag = sqrt(dx * dx + dy * dy + dz * dz);
    const float scale = dmag > 0. ? 1. / dmag : 1.;
    float eloss = 0.;
    if (i == 0 && dedx[i] > 10. * dedx[i + 1]) {
      eloss = dmag * dedx[i + 1];
    } else {
      eloss = dmag * dedx[i];
    }
    const float dekin = ekin[i] - ekin[i + 1];
    if (dekin > 0.) eloss = std::min(eloss, dekin);
    path.push_back({dx * scale, dy * scale, dz * scale, dmag, eloss, ekin[i]});
  }
  m_ions.push_back(std::move(path));
}

void TrackTrim::Print() {
  std::cout << m_className << "::Print:\n";
  if (m_ions.empty()) {
    std::cerr << "    No TRIM data present.\n";
    return;
  }
  std::cout << "    Projectile: " << m_particleName << ", " << m_ekin * 1.e-3
            << " keV\n"
            << "    Number of tracks: " << m_ions.size() << "\n";
  if (m_work > 0.) {
    std::cout << "    Work function: " << m_work << " eV\n";
  } else {
    std::cout << "    Work function: Automatic\n";
  }
  if (m_fset) {
    std::cout << "    Fano factor: " << m_fano << "\n";
  } else {
    std::cout << "    Fano factor: Automatic\n";
  }
}

bool TrackTrim::NewTrack(const double x0, const double y0, const double z0,
                         const double t0, const double dx0, const double dy0,
                         const double dz0) {
  // TRMGEN - Generates TRIM clusters

  if (m_ions.empty()) throw Exception("No TRIM data present");
  if (m_ion >= m_ions.size()) {
    // Rewind.
    std::cout << m_className << "::NewTrack: Rewinding.\n";
    m_ion = 0;
  }

  // Verify that a sensor has been set.
  if (!m_sensor) throw Exception("Sensor is not defined");
  // Set the initial direction.
  std::array<double, 3> v = {dx0, dy0, dz0};
  const double d0 = sqrt(dx0 * dx0 + dy0 * dy0 + dz0 * dz0);
  if (d0 < Small) {
    if (m_debug) {
      std::cout << m_className << "::NewTrack: Sampling initial direction.\n";
    }
    // Null vector. Sample the direction isotropically.
    RndmDirection(v[0], v[1], v[2]);
  } else {
    const double scale = 1. / d0;
    for (size_t i = 0; i < 3; ++i) v[i] *= scale;
  }

  Medium* medium = m_sensor->GetMedium(x0, y0, z0);
  if (!medium) throw Exception("No medium at initial point");
  double w = m_work > 0. ? m_work : medium->GetW();
  // Warn if the W value is not defined.
  if (w < Small) {
    std::cerr << m_className << "::NewTrack: "
              << "Work function at initial point is not defined.\n";
  }
  double fano = m_fset ? m_fano : medium->GetFanoFactor();
  fano = std::max(fano, 0.);

  // Charge-over-mass ratio.
  const double qoverm = m_mass > 0. ? m_q / m_mass : 0.;

  // Plot.
  if (m_viewer) PlotNewTrack(x0, y0, z0);

  // Reset the cluster count.
  m_cluster = 0;
  m_clusters.clear();

  // Pool of unused energy
  double epool = 0.0;

  const double ekin0 = GetKineticEnergy();

  const auto& path = m_ions[m_ion];
  const size_t nPoints = path.size();
  std::array<double, 3> x = {x0, y0, z0};
  double t = t0;
  for (size_t i = 0; i < nPoints; ++i) {
    // Skip points with kinetic energy below the initial one set by the user.
    double ekin = path[i][5];
    if (ekin > ekin0) continue;
    // Rotate the direction vector.
    if (i == 0) {
      Rotate({1, 0, 0}, {path[i][0], path[i][1], path[i][2]}, v);
    } else {
      Rotate({path[i - 1][0], path[i - 1][1], path[i - 1][2]},
             {path[i][0], path[i][1], path[i][2]}, v);
    }
    // Get the step length and energy loss.
    double dmag = path[i][3];
    double eloss = path[i][4];
    std::array<double, 3> d = {dmag * v[0], dmag * v[1], dmag * v[2]};
    // Subdivide the step if necessary.
    std::size_t nSteps = 1;
    if (m_maxStepSize > 0. && dmag > m_maxStepSize) {
      nSteps = std::ceil(dmag / m_maxStepSize);
    }
    if (m_maxLossPerStep > 0. && eloss > nSteps * m_maxLossPerStep) {
      nSteps = std::ceil(eloss / m_maxLossPerStep);
    }
    if (nSteps > 1) {
      const double scale = 1. / nSteps;
      for (size_t j = 0; j < 3; ++j) d[j] *= scale;
      dmag *= scale;
      eloss *= scale;
    }
    // Compute the particle velocity.
    const double vmag = Speed(ekin, m_mass);
    // Compute the timestep.
    const double dt = vmag > 0. ? dmag / vmag : 0.;
    for (std::size_t j = 0; j < nSteps; ++j) {
      Cluster cluster;
      if (m_sensor->HasMagneticField()) {
        double bx = 0., by = 0., bz = 0.;
        int status = 0;
        m_sensor->MagneticField(x[0], x[1], x[2], bx, by, bz, status);
        d = StepBfield(dt, qoverm, vmag, bx, by, bz, v);
      }
      cluster.x = x[0] + d[0];
      cluster.y = x[1] + d[1];
      cluster.z = x[2] + d[2];
      cluster.t = t + dt;
      x = {cluster.x, cluster.y, cluster.z};
      t = cluster.t;
      // Is this point inside an ionisable medium?
      medium = m_sensor->GetMedium(cluster.x, cluster.y, cluster.z);
      if (!medium || !medium->IsIonisable()) continue;
      if (m_work < Small) w = medium->GetW();
      if (w < Small) continue;
      if (fano < Small) {
        // No fluctuations.
        cluster.n = int((eloss + epool) / w);
        cluster.energy = w * cluster.n;
      } else {
        double ec = eloss + epool;
        cluster.n = 0;
        cluster.energy = 0.0;
        while (true) {
          const double er = RndmHeedWF(w, fano);
          if (er > ec) break;
          cluster.n++;
          cluster.energy += er;
          ec -= er;
        }
      }
      // TODO
      cluster.ekin = i < nPoints - 1 ? path[i + 1][5] : ekin;
      epool += eloss - cluster.energy;
      if (cluster.n == 0) continue;
      m_clusters.push_back(std::move(cluster));
      if (m_viewer) PlotCluster(cluster.x, cluster.y, cluster.z);
    }
  }
  // Move to the next ion in the list.
  ++m_ion;
  return true;
}

bool TrackTrim::GetCluster(double& xcls, double& ycls, double& zcls,
                           double& tcls, int& n, double& e, double& extra) {
  if (m_debug) {
    std::cout << m_className << "::GetCluster: Cluster " << m_cluster << " of "
              << m_clusters.size() << "\n";
  }
  // Stop if we have exhausted the list of clusters.
  if (m_cluster >= m_clusters.size()) return false;

  const auto& cluster = m_clusters[m_cluster];
  xcls = cluster.x;
  ycls = cluster.y;
  zcls = cluster.z;
  tcls = cluster.t;

  n = cluster.n;
  e = cluster.energy;
  extra = cluster.ekin;
  // Move to the next cluster.
  ++m_cluster;
  return true;
}
}  // namespace Garfield
