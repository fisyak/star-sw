#include "Garfield/AvalancheGrid.hh"

#include <cmath>
#include <iostream>

#include "Garfield/AvalancheMicroscopic.hh"
#include "Garfield/ComponentParallelPlate.hh"
#include "Garfield/Exceptions.hh"
#include "Garfield/Medium.hh"
#include "Garfield/Random.hh"
#include "Garfield/Sensor.hh"

namespace {

int AvalancheSize(const double dx, const int ni, const double alpha,
                  const double eta) {
  // Algorithm to get the size of the avalanche after it has propagated
  // over a distance dx.

  // Final size.
  int nf = 0;
  const double k = eta / alpha;
  const double ndx = exp((alpha - eta) * dx);
  // If the size is higher than 1000 the central limit theorem will be used
  // to describe the growth of the Townsend avalanche.
  if (ni < 1000) {
    // Condition to which the random number will be compared.
    // If the number is smaller than the condition, nothing happens.
    // Otherwise, the single electron will be attached or retrieve
    // additional electrons from the gas.
    const double prob = k * (ndx - 1) / (ndx - k);
    // Running over all electrons in the avalanche.
    for (int i = 0; i < ni; i++) {
      // Draw a random number from the uniform distribution (0,1).
      double s = Garfield::RndmUniformPos();
      if (s >= prob) {
        nf += (int)(1 + log((ndx - k) * (1 - s) / (ndx * (1 - k))) /
                            log(1 - (1 - k) / (ndx - k)));
      }
    }
  } else {
    // Central limit theorem.
    const double sigma = sqrt((1 + k) * ni * ndx * (ndx - 1) / (1 - k));
    nf = Garfield::RndmGaussian(ni * ndx, sigma);
  }
  return nf;
}

}  // namespace

namespace Garfield {

AvalancheGrid::AvalancheGrid(Sensor *sensor) { SetSensor(sensor); }

void AvalancheGrid::SetSensor(Sensor *sensor) {
  if (!sensor) throw Exception("sensor can't be nullptr");
  m_sensor = sensor;
}

void AvalancheGrid::SetElectronVelocity(const double vx, const double vy,
                                        const double vz) {
  double vel = std::sqrt(vx * vx + vy * vy + vz * vz);
  if (vel != std::abs(vx) && vel != std::abs(vy) && vel != std::abs(vz)) return;
  int nx = (int)vx / vel;
  int ny = (int)vy / vel;
  int nz = (int)vz / vel;
  m_velNormal = {nx, ny, nz};
  m_Velocity = -std::abs(vel);
}

void AvalancheGrid::SetGrid(const double xmin, const double xmax,
                            const int xsteps, const double ymin,
                            const double ymax, const int ysteps,
                            const double zmin, const double zmax,
                            const int zsteps) {
  m_gridset = true;

  if (zmin >= zmax || zsteps <= 0 || xmin > xmax || xsteps <= 0 ||
      ymin > ymax || ysteps <= 0)
    throw Exception("Grid is not properly defined");

  // Creating the z-coordinate grid.
  m_zStepSize = (zmax - zmin) / zsteps;
  m_zgrid.clear();
  for (int i = 0; i < zsteps; i++) {
    m_zgrid.push_back(zmin + i * m_zStepSize);
  }
  // Idem to for the y-coordinate grid.
  m_yStepSize = (ymax - ymin) / ysteps;
  if (m_yStepSize == 0) m_yStepSize = 1;
  m_ygrid.clear();
  for (int i = 0; i < ysteps; i++) {
    m_ygrid.push_back(ymin + i * m_yStepSize);
  }
  // Idem for the x-coordinate grid.
  m_xStepSize = (xmax - xmin) / xsteps;
  if (m_xStepSize == 0) m_xStepSize = 1;
  m_xgrid.clear();
  for (int i = 0; i < xsteps; i++) {
    m_xgrid.push_back(xmin + i * m_xStepSize);
  }

  if (m_debug) {
    std::cout << m_className << "::SetGrid: Grid created:\n"
              << "       x range = (" << xmin << "," << xmax << ").\n"
              << "       y range = (" << ymin << "," << ymax << ").\n"
              << "       z range = (" << zmin << "," << zmax << ").\n";
  }
}

bool AvalancheGrid::SnapToGrid(const double x, const double y, const double z,
                               const double /*v*/, const int n) {
  // Snap electron from AvalancheMicroscopic to the predefined grid.
  if (!m_gridset) throw Exception("Grid is not defined");
  // Finding the position on the grid.
  // TODO: Snap must be dependent on the direction of drift.
  int iX = round((x - m_xgrid.front()) / m_xStepSize);
  int iY = floor((y - m_ygrid.front()) / m_yStepSize);
  int iZ = round((z - m_zgrid.front()) / m_zStepSize);

  if (m_debug) {
    std::cout << m_className << "::SnapToGrid: ix = " << iX << ", iy = " << iY
              << ", iz = " << iZ << ".\n\n";
  }
  if (iX < 0 || (unsigned)iX >= m_xgrid.size() || iY < 0 ||
      (unsigned)iY >= m_ygrid.size() || iZ < 0 ||
      (unsigned)iZ >= m_zgrid.size()) {
    if (m_debug)
      std::cerr << m_className << "::SnapToGrid: Point is outside the grid.\n";
    return false;
  }

  AvalancheNode newNode;
  newNode.ix = iX;
  newNode.iy = iY;
  newNode.iz = iZ;
  if (!GetParameters(newNode)) {
    if (m_debug)
      std::cerr << m_className
                << "::SnapToGrid: Could not retrieve parameters from sensor.\n";
    return false;
  }

  // When snapping the electron to the grid the distance traveled can yield
  // additional electrons or attachment.
  double step = z - m_zgrid[iZ];
  if (newNode.velNormal[0] != 0) {
    step = x - m_xgrid[iX];
  } else if (newNode.velNormal[1] != 0) {
    step = y - m_ygrid[iY];
  }

  const int nn = AvalancheSize(step, n, newNode.townsend, newNode.attachment);
  if (nn == 0) {
    if (m_debug)
      std::cerr << m_className << "::SnapToGrid: n from 1 to 0 -> cancel.\n";
    return false;
  }

  newNode.n = nn < m_MaxSize ? nn : m_MaxSize;
  m_nTotal += newNode.n;

  bool alreadyExists = false;

  for (AvalancheNode &existingNode : m_activeNodes) {
    if (existingNode.ix == newNode.ix && existingNode.iy == newNode.iy &&
        existingNode.iz == newNode.iz) {
      alreadyExists = true;
      existingNode.n += newNode.n;
    }
  }

  // TODO: What if time changes as you are importing avalanches?
  newNode.time = m_time;
  if (!alreadyExists) m_activeNodes.push_back(std::move(newNode));

  if (m_debug) {
    std::cout << m_className << "::SnapToGrid: n from 1 to " << nn << ".\n"
              << "    Snapped to (x,y,z) = (" << x << " -> " << m_xgrid[iX]
              << ", " << y << " -> " << m_ygrid[iY] << ", " << z << " -> "
              << m_zgrid[iZ] << ").\n";
  }
  return true;
}

void AvalancheGrid::NextAvalancheGridPoint() {
  // This main function propagates the electrons and applies the avalanche
  // statistics.
  m_run = false;
  if (m_debug) std::cout << m_className << "::NextAvalancheGridPoint:\n";
  for (AvalancheNode &node : m_activeNodes) {  // For every avalanche node
    if (!node.active) continue;
    m_run = true;

    if (m_debug) {
      std::cout << "  Node (" << node.ix << "," << node.iy << "," << node.iz
                << ").\n";
    }
    // Get the initial avalanche size.
    const int ni = node.n;
    if (node.path.xs.empty()) {
      node.path.xs.push_back(
          {m_xgrid[node.ix], m_ygrid[node.iy], m_zgrid[node.iz]});
      node.path.ts.push_back(node.time + node.dt);
      node.path.qs.push_back(0.5 * ni);
    }
    // If empty go to next point.
    if (ni == 0) continue;
    // If the total avalanche size is smaller than the set saturation
    // limit the AvalancheSize function is utilized to obtain the size
    // after its propagation to the next z-coordinate grid point. Else,
    // the size will be kept constant under the propagation.
    const int nTot = m_nLayer.empty() ? m_nTotal : m_nLayer[node.layer - 1];
    if (nTot < m_MaxSize) {
      int nf = AvalancheSize(node.stepSize, ni, node.townsend, node.attachment);
      if (m_MaxSize - nTot < nf - ni) nf = m_MaxSize - nTot + ni;
      node.n = nf;
    } else {
      m_Saturated = true;
      if (m_SaturationTime == -1) m_SaturationTime = node.time + node.dt;
    }
    // Produce induced signal on readout electrodes.
    node.path.xs.push_back({m_xgrid[node.ix + node.velNormal[0]],
                            m_ygrid[node.iy + node.velNormal[1]],
                            m_zgrid[node.iz + node.velNormal[2]]});
    node.path.ts.push_back(node.time + node.dt);
    node.path.qs.push_back(0.5 * (ni + node.n));

    // Update total number of electrons.
    if (!m_nLayer.empty()) m_nLayer[node.layer - 1] += node.n - ni;
    m_nTotal += node.n - ni;

    if (m_debug) std::cerr << "n = " << ni << " -> " << node.n << ".\n";

    // Update position index.
    node.ix += node.velNormal[0];
    node.iy += node.velNormal[1];
    node.iz += node.velNormal[2];

    // After all active grid points have propagated, update the time.
    if (m_debug) std::cerr << "t = " << node.time << " -> ";
    node.time += node.dt;
    if (m_debug) std::cerr << node.time << ".\n";

    DeactivateNode(node);
  }
  if (m_debug) std::cerr << "N = " << m_nTotal << ".\n\n";
}

void AvalancheGrid::DeactivateNode(AvalancheNode &node) {
  if (node.n == 0) node.active = false;

  if (node.velNormal[2] != 0) {
    if ((node.velNormal[2] < 0 && node.iz == 0) ||
        (node.velNormal[2] > 0 && node.iz == m_zgrid.size() - 1))
      node.active = false;
  } else if (node.velNormal[1] != 0) {
    if ((node.velNormal[1] < 0 && node.iy == 0) ||
        (node.velNormal[1] > 0 && node.iy == m_ygrid.size() - 1))
      node.active = false;
  } else {
    if ((node.velNormal[0] < 0 && node.ix == 0) ||
        (node.velNormal[0] > 0 && node.ix == m_xgrid.size() - 1))
      node.active = false;
  }

  double e[3], v;
  int status;
  Medium *m = nullptr;
  m_sensor->ElectricField(m_xgrid[node.ix], m_ygrid[node.iy], m_zgrid[node.iz],
                          e[0], e[1], e[2], v, m, status);

  if (status == -5 || status == -6) {
    // If not inside a gas gap return false to terminate
    node.active = false;
  }

  if (!node.active) {
    // If node has terminated then the signal from the avalanche is calculated
    m_sensor->AddSignalWeightingPotential(-1, node.path.ts, node.path.xs,
                                          node.path.qs);
    if (m_debug) {
      std::cout << m_className << "::DeactivateNode: Node deactivated.\n";
    }
  }
}

void AvalancheGrid::StartGridAvalanche() {
  // Start the AvalancheGrid algorithm.
  if (!m_run || m_activeNodes.empty() || !m_sensor) return;

  std::cout << m_className
            << "::StartGridAvalanche: Starting grid based simulation with "
            << m_nTotal << " initial electrons.\n";
  if (m_nTotal <= 0) {
    std::cerr << m_className << "::StartGridAvalanche: Cancelled.\n";
    return;
  }

  // If the sensor contains a parallel plate component, assign the nodes
  // to a layer and initialize the per-layer avalanche size counters.
  const auto nComponents = m_sensor->GetNumberOfComponents();
  for (size_t i = 0; i < nComponents; ++i) {
    auto cmp = m_sensor->GetComponent(i);
    auto pp = dynamic_cast<ComponentParallelPlate *>(cmp);
    if (!pp) continue;
    m_nLayer.assign(pp->NumberOfLayers(), 0);
    for (auto &node : m_activeNodes) {
      const double y = m_ygrid[node.iy];
      const int im = pp->GetLayer(y);
      node.layer = im;
      m_nLayer[im - 1] += node.n;
    }
    break;
  }

  m_nestart = m_nTotal;

  // Main loop.
  while (m_run == true) {
    if (m_debug)
      std::cout
          << "============ \n"
          << m_className
          << "::StartGridAvalanche: Looping over nodes.\n ============ \n";
    NextAvalancheGridPoint();
  }

  std::vector<double> tlist = {};
  for (AvalancheNode &node : m_activeNodes) {
    tlist.push_back(node.time);
  }
  double maxTime = *max_element(std::begin(tlist), std::end(tlist));

  if (m_Saturated)
    std::cerr << m_className
              << "::StartGridAvalanche: Avalanche maximum size of " << m_MaxSize
              << " electrons reached at " << m_SaturationTime << " ns.\n";

  std::cerr << m_className
            << "::StartGridAvalanche: Final avalanche size = " << m_nTotal
            << " ended at t = " << maxTime << " ns.\n";

  return;
}

void AvalancheGrid::AddElectron(const double x, const double y, const double z,
                                const double t, const int n) {
  if (m_time == 0 && m_time != t && m_debug)
    std::cerr << m_className
              << "::AddElectron: Overwriting start time of avalanche for t "
                 "= 0 to "
              << t << ".\n";
  m_time = t;
  const bool ok = SnapToGrid(x, y, z, 0, n);
  if (ok && m_debug) {
    std::cout << m_className
              << "::AddElectron: Electron added at (t,x,y,z) =  (" << t << ","
              << x << "," << y << "," << z << ").\n";
  }
}

void AvalancheGrid::AddElectrons(AvalancheMicroscopic *avmc) {
  // Get the information of the electrons from the AvalancheMicroscopic class.
  if (!avmc) return;

  // Get initial positions of electrons
  for (const auto &electron : avmc->GetElectrons()) {
    // Skip electrons that are not stopped due to
    // the upper bound of the time range.
    if (electron.status != -17) continue;
    const auto &p1 = electron.path.at(0);
    const auto &p2 = electron.path.back();
    // HS: why use only the z component?
    const double vel = (p2.z - p1.z) / (p2.t - p1.t);
    m_time = p2.t;
    const bool ok = SnapToGrid(p2.x, p2.y, p2.z, vel);
    if (ok && m_debug) {
      std::cout << m_className
                << "::AddElectrons: Electron added at "
                   "(x,y,z) =  ("
                << p2.x << "," << p2.y << "," << p2.z << ").\n";
    }
  }
}

bool AvalancheGrid::GetParameters(AvalancheNode &node) {
  if (!m_sensor) return false;

  double x = m_xgrid[node.ix];
  double y = m_ygrid[node.iy];
  double z = m_zgrid[node.iz];

  if (m_debug) {
    std::cout << m_className
              << "::GetParameters: Getting parameters at "
                 "(x,y,z) =  ("
              << x << "," << y << "," << z << ").\n";
  }
  double e[3], v;
  int status;
  Medium *m = nullptr;
  m_sensor->ElectricField(x, y, z, e[0], e[1], e[2], v, m, status);

  if (m_debug) std::cout << "    Status = " << status << ".\n";
  // If not inside a gas gap return false to terminate
  if (status == -5 || status == -6) return false;

  if (m_Townsend >= 0) {
    node.townsend = m_Townsend;
  } else {
    // If Townsend coef. is not set by user, take it from the sensor.
    m->ElectronTownsend(e[0], e[1], e[2], 0., 0., 0., node.townsend);
  }

  if (m_Attachment >= 0) {
    node.attachment = m_Attachment;
  } else {
    // If attachment coef. is not set by user, take it from the sensor.
    m->ElectronAttachment(e[0], e[1], e[2], 0., 0., 0., node.attachment);
  }

  if (m_Velocity > 0) {
    node.velocity = m_Velocity;
    node.velNormal = m_velNormal;
  } else {
    // If velocity is not set by user, take it from the sensor.
    double vx, vy, vz;
    m->ElectronVelocity(e[0], e[1], e[2], 0., 0., 0., vx, vy, vz);

    double vel = sqrt(vx * vx + vy * vy + vz * vz);
    if (vel == 0.) return false;
    if (vel != std::abs(vx) && vel != std::abs(vy) && vel != std::abs(vz))
      return false;
    int nx = (int)round(vx / vel);
    int ny = (int)round(vy / vel);
    int nz = (int)round(vz / vel);

    node.velNormal = {nx, ny, nz};
    node.velocity = -std::abs(vel);
  }

  if (node.velNormal[0] != 0) {
    node.stepSize = m_xStepSize;
  } else if (node.velNormal[1] != 0) {
    node.stepSize = m_yStepSize;
  } else {
    node.stepSize = m_zStepSize;
  }

  if (m_debug) {
    std::cout << m_className << "::GetParameters:\n"
              << "    stepSize = " << node.stepSize << " [cm].\n"
              << "    velNormal = (" << node.velNormal[0] << ", "
              << node.velNormal[1] << ", " << node.velNormal[2] << ") [1].\n";
  }
  node.dt = std::abs(node.stepSize / node.velocity);

  // print
  if (m_debug || !m_printPar) {
    std::cout << m_className << "::GetParameters:\n"
              << "    Electric field = (" << 1.e-3 * e[0] << ", "
              << 1.e-3 * e[1] << ", " << 1.e-3 * e[2] << ") [kV/cm].\n"
              << "  Townsend = " << node.townsend
              << " [1/cm], Attachment = " << node.attachment
              << " [1/cm], Velocity = " << node.velocity << " [cm/ns].\n";
  }
  if (m_debug) std::cout << "    Time steps per loop " << node.dt << " ns.\n";
  m_printPar = true;
  return true;
}

void AvalancheGrid::Reset() {
  std::cout << m_className << "::Reset: Resetting AvalancheGrid.\n";
  m_time = 0.;
  m_nTotal = 0;
  m_run = true;

  m_Saturated = false;
  m_SaturationTime = -1;

  m_activeNodes.clear();
  m_nLayer.clear();
}

}  // namespace Garfield
