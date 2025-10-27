#include "Garfield/AvalancheGridSpaceCharge.hh"

#include <algorithm>
#include <cmath>
#include <fstream>
#include <iostream>
#include <numeric>

#include "Garfield/AvalancheMicroscopic.hh"
#include "Garfield/ComponentParallelPlate.hh"
#include "Garfield/Exceptions.hh"
#include "Garfield/GarfieldConstants.hh"
#include "Garfield/Medium.hh"
#include "Garfield/Random.hh"
#include "Garfield/Sensor.hh"

namespace {

double Mag(const double x, const double y) { return std::sqrt(x * x + y * y); }

// Get the gas gap number of a given layer, else -1.
int GetGasGapNumber(const std::vector<int> &gasLayers, const int layer) {
  auto it = std::find(gasLayers.begin(), gasLayers.end(), layer);
  return (it != gasLayers.end()) ? std::distance(gasLayers.begin(), it) : -1;
}

// Get size of avalanche when going from x to x+dx in Monte Carlo fashion
void GetAvalancheSizeFromStep(double dx, const long nEIn, const double alpha,
                              const double eta, long &nEOut, double &nPOut,
                              double &nNOut) {
  // Monte Carlo Avalanche gain per travelled distance dx (cm)
  nEOut = 0;
  nPOut = 0;
  nNOut = 0;

  if (std::abs(alpha - eta) < 1.e-8 && alpha > 1.e-8) {
    // alpha == eta
    if (nEIn < 1000L) {
      // Condition to which the random number will be compared.
      // If the number is smaller than the condition, nothing happens.
      // Otherwise, the single electron will be attached or retrieve
      // additional electrons from the gas.
      const double p = alpha * dx / (1. + alpha * dx);
      const double q = 1. + alpha * dx;
      const double f = 1. / log(p);
      // Running over all electrons in the avalanche.
      for (long i = 0; i < nEIn; i++) {
        // Draw a random number from the uniform distribution (0,1).
        const double s = Garfield::RndmUniformPos();
        // We (wrongly) assume if s >= prob only pos ions are created
        // else 1 neg ion.
        if (s >= p) {
          // Deviation/improvement wrt Lippmann?
          nEOut += (long)(log((1. - s) * q) * f);
        } else {
          nNOut += 1;
        }
      }
      // charge conservation
      nPOut = (nEOut - nEIn) + nNOut;

    } else {
      // Central limit theorem.
      const double sigma = sqrt(2 * alpha * dx * nEIn);
      nEOut = (long)Garfield::RndmGaussian(nEIn, sigma);

      // boundary conditions (alpha dx ElectronIn = dPosOut),
      //  the procedure guarantees positive values
      //  and net Nion = nPos - nNeg = nOut - nIn
      if (nEOut <= 0) nEOut = 0;  //< unphysical
      if (nEOut >= nEIn) {
        nNOut = std::expm1(eta * dx) * nEIn;  //< >= 0
        nPOut = (nEOut - nEIn) + nNOut;       //< >= 0
      } else {
        nPOut = std::expm1(alpha * dx) * nEIn;  //< >= 0
        nNOut = nPOut - (nEOut - nEIn);         //< >= 0
      }
    }
  } else if (alpha < 1.e-8 && eta > 1.e-8) {
    // alpha == 0, only attachment possible
    if (nEIn < 1000L) {
      const double p = exp(-eta * dx);
      for (long i = 0; i < nEIn; i++) {
        // Draw a random number from the uniform distribution (0,1).
        const double s = Garfield::RndmUniformPos();
        if (s >= p) {
          nNOut += 1;
        } else {
          nEOut += 1;
        }
      }
    } else {
      // Central limit theorem.
      const double ndx = exp(-eta * dx);
      const double mu = nEIn * ndx;
      const double sigma = std::sqrt(mu * ndx * (ndx - 1.));
      nEOut = (long)Garfield::RndmGaussian(mu, sigma);

      // boundary conditions
      if (nEOut <= 0) {
        // Unphysical
        nEOut = 0;
      } else if (nEOut > nEIn) {
        // Unphysical with alpha = 0
        nEOut = nEIn;
      }
      // Charge conservation
      nNOut = -(nEOut - nEIn);
    }
  } else {
    // alpha != 0 =! eta
    const double k = eta / alpha;
    const double ndx = exp((alpha - eta) * dx);

    if (nEIn < 1000L) {
      // Condition to which the random number will be compared.
      // If the number is smaller than the condition, nothing happens.
      // Otherwise, the single electron will be attached or retrieve
      // additional electrons from the gas.
      const double p = k * (ndx - 1.) / (ndx - k);
      const double q = (ndx - k) / (ndx * (1. - k));
      const double f = 1. / log(1. - (1. - k) / (ndx - k));
      // Running over all electrons in the avalanche.
      for (long i = 0; i < nEIn; i++) {
        // Draw a random number from the uniform distribution (0,1).
        const double s = Garfield::RndmUniformPos();
        if (s >= p) {
          // deviation/improvement wrt Lippmann?
          nEOut += (long)(1. + log((1. - s) * q) * f);
        } else {
          nNOut += 1;
        }
      }
      // charge conservation
      nPOut = (nEOut - nEIn) + nNOut;

    } else {
      // Central limit theorem.
      const double mu = nEIn * ndx;
      const double sigma = std::sqrt(mu * (1. + k) * (ndx - 1.) / (1. - k));
      nEOut = (long)Garfield::RndmGaussian(mu, sigma);

      // boundary conditions (alpha dx ElectronIn = dPosOut),
      //  the procedure guarantees positive values
      //  and netto Nion = nPos - nNeg = nOut - nIn
      if (nEOut <= 0) nEOut = 0;  //< unphysical

      // either the above has not been executed or nPOut was not positive
      if (nEOut >= nEIn) {
        nNOut = std::expm1(eta * dx) * nEIn;
        // nNOut = eta / (alpha - eta) * (nEOut - nEIn);
        nPOut = (nEOut - nEIn) + nNOut;
      } else {
        nPOut = std::expm1(alpha * dx) * nEIn;
        // nPOut = alpha / (alpha - eta) * (nEOut - nEIn);
        nNOut = nPOut - (nEOut - nEIn);
      }
    }
  }
}

// Get mean size of avalanche when going from x to x+dx
void GetMeanAvalancheSizeFromStep(double dx, const long nEIn,
                                  const double alpha, const double eta,
                                  long &nEOut, double &nPOut, double &nNOut) {
  // Mean size gain
  nPOut = 0;
  nNOut = 0;
  const double ndx = exp((alpha - eta) * dx);
  // for electrons
  nEOut = nEIn * ndx;
  if (nEOut <= 0) nEOut = 0;  //< unphysical

  // either the above has not been executed or nPOut was not positive
  if (nEOut >= nEIn) {
    nNOut = std::expm1(eta * dx) * nEIn;  //< >= 0
    nPOut = (nEOut - nEIn) + nNOut;       //< >= 0
  } else {
    nPOut = std::expm1(alpha * dx) * nEIn;  //< >= 0
    nNOut = nPOut - (nEOut - nEIn);         //< >= 0
  }
}

}  // namespace

namespace Garfield {

AvalancheGridSpaceCharge::AvalancheGridSpaceCharge() {
  m_zGrid.reserve(5000);
  m_rGrid.reserve(1000);
}

AvalancheGridSpaceCharge::AvalancheGridSpaceCharge(Sensor *sensor)
    : AvalancheGridSpaceCharge() {
  SetSensor(sensor);
}

void AvalancheGridSpaceCharge::SetSensor(Sensor *sensor) {
  if (!sensor) throw Exception("Sensor can't be nullptr");
  m_sensor = sensor;
}

void AvalancheGridSpaceCharge::Reset() {
  m_time = 0.;
  m_dt = 0.;
  m_nEtot = 0;
  m_nPtot = 0;

  m_centre.clear();
  m_electrons.clear();
  m_evolution.resize(0);
  m_grid.clear();
  m_ezBkg = {0.};
  m_ezThr = {0.};
  m_medium = {nullptr};
  m_saturated = {false};

  m_bFieldK = false;

  std::cout << m_className << "::Reset: Instance reset, ready to use again.\n";
}

void AvalancheGridSpaceCharge::Set2dGrid(const double zmin, const double zmax,
                                         const int zsteps, const double rmax,
                                         const int rsteps) {
  if (zmin >= zmax || zsteps <= 0 || 0 >= rmax || rsteps <= 0) {
    throw Exception("Grid is not properly defined");
  }

  // set z grid
  m_zSteps = zsteps;
  m_zStepSize = (zmax - zmin) / zsteps;
  m_zInvStep = 1. / m_zStepSize;
  for (int i = 0; i < zsteps + 1; i++) {
    m_zGrid.push_back(zmin + i * m_zStepSize);
  }

  // set r grid
  m_rSteps = rsteps;
  m_rStepSize = rmax / rsteps;
  m_rInvStep = 1. / m_rStepSize;
  for (int i = 0; i < rsteps + 1; i++) {
    m_rGrid.push_back(0 + i * m_rStepSize);
  }

  if (m_bDebug) {
    std::cout << m_className << "::Set2dGrid: Grid created:\n"
              << "       z range = (" << zmin << "," << zmax << ").\n"
              << "       r range = (" << 0 << "," << rmax << ").\n";
  }
}

void AvalancheGridSpaceCharge::SetFieldCalculation(const std::string &option,
                                                   const int nof_approx) {
  std::string opt = option;
  std::transform(opt.begin(), opt.end(), opt.begin(), toupper);
  if (opt == "COULOMB") {
    m_fieldOption = FieldOption::Coulomb;
  } else if (opt == "MIRROR") {
    m_fieldOption = FieldOption::Mirror;
  } else {
    std::cerr << m_className << "::SetFieldCalculation: Unknown option "
              << option << ".\n";
  }
  m_iFieldApprox = nof_approx;
}

void AvalancheGridSpaceCharge::AddElectrons(AvalancheMicroscopic *avmc) {
  if (!avmc) return;

  if (m_bDebug) std::cout << m_className << "::AddElectrons:\n";
  for (const auto &electron : avmc->GetElectrons()) {
    // Skip "inactive" electrons, i. e. electrons that don't have
    // status code "outside time window".
    if (electron.status != StatusOutsideTimeWindow) {
      if (m_bDebug) {
        std::cout << "    Skipping electron with status " << electron.status
                  << ".\n";
      }
      continue;
    }
    Point pt{};
    pt.x = electron.path.back().x;
    pt.y = electron.path.back().y;
    pt.z = electron.path.back().z;
    pt.t = electron.path.back().t;
    pt.n = electron.weight;
    m_electrons.push_back(std::move(pt));

    if (m_bDebug)
      std::cout << m_className << "::AddElectrons: Electron added, y: "
                << electron.path.back().y << ".\n";
  }
}

void AvalancheGridSpaceCharge::AddElectron(const double x, const double y,
                                           const double z, const double t,
                                           const unsigned int n) {
  Point pt{};
  pt.x = x;
  pt.y = y;
  pt.z = z;
  pt.t = t;
  pt.n = n;
  m_electrons.push_back(std::move(pt));
}

void AvalancheGridSpaceCharge::StartGridAvalanche(double dtime) {
  // avalanche the electrons until a certain delta-time OR there are no
  // electrons left in the gap
  if (!m_sensor) return;

  if (m_nEtot > 0) {
    // There are still electrons on the mesh from a previous run.
    if (m_bDebug) {
      std::cout << m_className
                << "::StartGridAvalanche: Resuming from previous run.\n";
    }
  } else {
    if (!Prepare()) {
      std::cerr << m_className << "::StartGridAvalanche: Preparation failed.\n";
      return;
    }
    if (m_bDebug) {
      std::cout << m_className << "::StartGridAvalanche: Preparation ok.\n";
    }
    m_electrons.clear();
  }

  // Make sure there are electrons on the grid.
  if (m_nEtot <= 0) {
    std::cerr << m_className << "::StartGridAvalanche:\n"
              << "    There are no electrons on the grid. Cannot proceed.\n";
    return;
  }

  if (dtime > 0.) {
    const double tMax = m_time + dtime;
    while (m_time + m_dt < tMax) {
      if (!Step()) break;
    }
  } else {
    // Transport until there are no electrons left in gap or an error occurs.
    while (true) {
      if (!Step()) break;
    }
  }

  if (!m_evolution.empty()) {
    // determine maximal size of electron maxSize at time maxTime.
    auto maxSize = std::max_element(m_evolution.begin(), m_evolution.end(),
                                    [](const std::pair<double, long> &p1,
                                       const std::pair<double, long> &p2) {
                                      return p1.second < p2.second;
                                    });

    std::cout << m_className << "::StartGridAvalanche:\n"
              << "    Maximum avalanche (" << maxSize->second
              << " electrons) reached at " << maxSize->first << " ns.\n";
    std::cout << "    Avalanche ended at " << m_time << " ns.\n";
    std::cout << "    Final avalanche size (number of positive ions): "
              << m_nPtot << ".\n";
  }
}

void AvalancheGridSpaceCharge::ExportGrid(const std::string &filename) {
  std::ofstream fE(filename + "_electrons.csv");
  if (!fE.is_open()) throw Exception("Error opening e- file");
  for (int iz = 0; iz <= m_zSteps; iz++) {
    for (int ir = 0; ir <= m_rSteps; ir++) {
      fE << m_grid[iz][ir].nE << " ";
    }
    fE << "\n";
  }
  fE.close();

  std::ofstream fP(filename + "_posion.csv");
  if (!fP.is_open()) throw Exception("Error opening p+ file");
  for (int iz = 0; iz <= m_zSteps; iz++) {
    for (int ir = 0; ir <= m_rSteps; ir++) {
      fP << std::floor(m_grid[iz][ir].nP) << " ";
    }
    fP << "\n";
  }
  fP.close();

  std::ofstream fN(filename + "_negion.csv");
  if (!fN.is_open()) throw Exception("Error opening n- file");
  for (int iz = 0; iz <= m_zSteps; iz++) {
    for (int ir = 0; ir <= m_rSteps; ir++) {
      fN << std::floor(m_grid[iz][ir].nN) << " ";
    }
    fN << "\n";
  }
  fN.close();

  std::ofstream fZField(filename + "_eFieldZ.csv");
  if (!fZField.is_open()) throw Exception("Error opening E_z file");
  for (int iz = 0; iz <= m_zSteps; iz++) {
    for (int ir = 0; ir <= m_rSteps; ir++) {
      const double ez = -m_grid[iz][ir].emag * m_grid[iz][ir].ctheta;
      fZField << std::round(ez) << " ";
    }
    fZField << "\n";
  }
  fZField.close();

  std::ofstream fRField(filename + "_eFieldR.csv");
  if (!fRField.is_open()) throw Exception("Error opening E_r file");
  for (int iz = 0; iz <= m_zSteps; iz++) {
    for (int ir = 0; ir <= m_rSteps; ir++) {
      const double er = -m_grid[iz][ir].emag * m_grid[iz][ir].stheta;
      fRField << std::round(er) << " ";
    }
    fRField << "\n";
  }
  fRField.close();

  std::ofstream fMagField(filename + "_MagField.csv");
  if (!fMagField.is_open()) throw Exception("Error opening E_r file");
  for (int iz = 0; iz <= m_zSteps; iz++) {
    for (int ir = 0; ir <= m_rSteps; ir++) {
      fMagField << std::round(m_grid[iz][ir].emag) << " ";
    }
    fMagField << "\n";
  }
  fMagField.close();

  if (m_bDebug) {
    std::cout << m_className << "::ExportGrid: Grids exported.\n";
  }
}

bool AvalancheGridSpaceCharge::SnapToGrid(const double x, const double y,
                                          const double z, const long n,
                                          const int gap) {
  // Snap electron to the predefined grid
  if (m_grid.empty()) throw Exception("Grid is not defined");

  // Compute the radius.
  const double r = Mag(x - m_centre[gap][0], z - m_centre[gap][2]);
  int iZ = (int)std::round((y - m_zGrid.front()) * m_zInvStep);
  int iR = (int)std::round(r * m_rInvStep);

  if (m_bDebug) {
    std::cout << m_className << "::SnapToGrid: Adding point (" << y << ", " << r
              << ") to the grid.\n"
              << "    Nearest grid node is (" << iZ << ", " << iR << ").\n";
  }

  if (iZ < 0 || iZ > m_zSteps || iR < 0 || iR > m_rSteps) {
    if (m_bDebug) {
      std::cerr << m_className << "    Point is outside the grid.\n";
    }
    return false;
  }
  // Sanity check.
  if (m_grid[iZ][iR].gap != gap) {
    std::cerr << m_className
              << "::SnapToGrid: Gas layer index does not match.\n";
    return false;
  }

  // Add point to the grid.
  // When snapping the electron to the grid the distance traveled can yield
  // additional electrons or get attached. (depends on if against E field or
  // along ...). e-field is along y (micro)
  const double step = m_zGrid[iZ] - y;
  // determine if against (ok) or with e field (not ok):
  int against =
      (step > 0 && m_ezBkg[gap] < 0) || (step < 0 && m_ezBkg[gap] > 0);

  if (!against) {
    m_grid[iZ][iR].nE += n;
    m_nEtot += n;
    if (m_bDebug) std::cout << "    Snap along E-field.\n";
    return true;
  }

  // make step positive
  long nEOut;
  double nPOut, nNOut;
  GetAvalancheSizeFromStep(std::abs(step), n, m_grid[iZ][iR].alpha,
                           m_grid[iZ][iR].eta, nEOut, nPOut, nNOut);
  if (nEOut == 0) {
    if (m_bDebug)
      std::cerr << m_className << "::SnapToGrid: e- from " << n
                << " to 0 -> cancel.\n";
    return false;
  }

  m_grid[iZ][iR].nE += nEOut;
  m_grid[iZ][iR].nP += nPOut;
  m_grid[iZ][iR].nN += nNOut;
  m_nEtot += nEOut;
  m_nPtot += (long)nPOut;

  if (m_bDebug) {
    std::cout << m_className << "::SnapToGrid: e- from " << n << " to " << nEOut
              << " p+: " << nPOut << " n-: " << nNOut << ".\n"
              << "    Snapped to (z, r) = (" << y << " -> " << m_zGrid[iZ]
              << ", " << r << " -> " << m_rGrid[iR] << ").\n";
  }
  return true;
}

bool AvalancheGridSpaceCharge::Prepare() {
  if (!m_sensor) return false;
  // Determine if the sensor has a parallel-plate component.
  ComponentParallelPlate *pp = nullptr;
  const size_t nCmp = m_sensor->GetNumberOfComponents();
  for (size_t i = 0; i < nCmp; i++) {
    pp = dynamic_cast<ComponentParallelPlate *>(m_sensor->GetComponent(i));
    if (pp) break;
  }
  // Number of gas gaps.
  unsigned int nG = 1;
  std::vector<int> gasLayers;
  if (pp) {
    pp->IndexOfGasGaps(gasLayers);
    nG = gasLayers.size();
  }
  if (nG == 0) {
    std::cerr << "AvalancheGridSpaceCharge::Prepare:\n"
              << "    Geometry does not have any gas gaps.\n";
    return false;
  }
  // Assign the electrons to the respective gas gaps.
  std::vector<std::vector<Point> > electronsPerGap(nG);
  std::vector<std::size_t> nPerGap(nG, 0);
  m_centre.assign(nG, {0., 0., 0.});
  m_time = 0.;
  std::size_t nOutside = 0;
  for (const auto &pt : m_electrons) {
    int gap = 0;
    if (pp) {
      const int layer = pp->GetLayer(pt.y);
      if (layer < 0) {
        ++nOutside;
        continue;
      }
      gap = GetGasGapNumber(gasLayers, layer);
      if (gap < 0) {
        ++nOutside;
        continue;
      }
    } else {
      // TODO
      // Check if the point is inside a valid medium?
    }
    electronsPerGap[gap].push_back(pt);
    m_centre[gap][0] += pt.n * pt.x;
    m_centre[gap][1] += pt.n * pt.y;
    m_centre[gap][2] += pt.n * pt.z;
    m_time += pt.n * pt.t;
    nPerGap[gap] += pt.n;
  }

  if (nOutside > 0) {
    std::cerr << m_className << "::Prepare: Skipped " << nOutside
              << " electrons that are not in a gas gap.\n";
  }
  const size_t nTotal = std::accumulate(nPerGap.begin(), nPerGap.end(), 0);
  if (nTotal == 0) {
    std::cerr << m_className << "::Prepare: There are no active electrons.\n";
    return false;
  }
  // Set the start time.
  m_time = m_time / (double)nTotal;

  m_medium.assign(nG, nullptr);
  m_ezBkg.assign(nG, 0.);
  m_zBot.assign(nG, 0.);
  m_zTop.assign(nG, 0.);
  m_alpha12.assign(nG, 0.);
  m_saturated.assign(nG, false);
  std::vector<double> vd(nG, 0.), dL(nG, 0.), dT(nG, 0.);
  std::vector<double> wv(nG, 0.), wr(nG, 0.);
  std::vector<double> alphaPT(nG, 0.), etaPT(nG, 0.);
  // Iterate through the gas gaps.
  for (unsigned int k = 0; k < nG; k++) {
    if (electronsPerGap[k].empty()) continue;
    // Compute the centre-of-gravity of the electrons in the gap.
    const double s = 1. / nPerGap[k];
    m_centre[k][0] *= s;
    m_centre[k][1] *= s;
    m_centre[k][2] *= s;
    if (m_bDebug) {
      std::cout << m_className << "::Prepare: Electrons in gas gap " << k
                << " are centred at (" << m_centre[k][0] << ", "
                << m_centre[k][1] << ", " << m_centre[k][2] << ").\n";
    }
    // Calculate the mid-point of the gap.
    double zGap = 0.;
    if (pp) {
      const int layer = gasLayers[k];
      pp->getZBoundFromLayer(layer, m_zBot[k], m_zTop[k]);
      zGap = 0.5 * (m_zBot[k] + m_zTop[k]);
      // Get dielectric constant of the neighboring layer
      // (assume both layers have the same epsilon).
      const double eps = pp->GetPermittivityFromLayer(layer + 1);
      m_alpha12[k] = (1. - eps) / (1. + eps);
    } else {
      zGap = m_centre[k][1];
      // TODO
      // Get bounding box of the sensor.
    }

    // Get the medium and electric field.
    m_medium[k] = m_sensor->GetMedium(0., zGap, 0.);
    double e[3];
    int status = 0;
    Medium *m = nullptr;
    m_sensor->ElectricField(0., zGap, 0., e[0], e[1], e[2], m, status);

    if (status != 0) {
      std::cerr << m_className
                << "::Prepare: Cannot retrieve background field for gas gap "
                << k << ".\n";
    }

    // In ComponentParallelPlate the electric field is along the y-axis
    // which corresponds to the z-axis in our local (RZ) coordinate system.
    m_ezBkg[k] = e[1];
    // Set the threshold field for streamer formation.
    m_ezThr[k] = std::abs(m_ezBkg[k]) * (1. + m_fStreamerK);
    const double emag = std::abs(e[1]);
    GetSwarmParameters(m_medium[k], emag, vd[k], dL[k], dT[k], wv[k], wr[k],
                       alphaPT[k], etaPT[k]);

    // print-out to double-check the swarm parameters
    std::cout << m_className << "::Prepare:\n Gas gap " << k + 1 << ":\n";
    std::printf("     Electric field:              %15.6f V/cm\n", m_ezBkg[k]);
    std::printf("     Townsend coefficient (PT):   %15.6f 1/cm\n", alphaPT[k]);
    std::printf("     Attachment coefficient (PT): %15.6f 1/cm\n", etaPT[k]);
    std::printf("     Flux velocity:               %15.6f cm/ns\n", vd[k]);
    std::printf("     Bulk velocity:               %15.6f cm/ns\n", wr[k]);
  }

  // Set up the components for computing the space-charge field.
  const double hmax = m_rGrid.back();
  const double hmin = -1. * hmax;
  const double vmin = m_zGrid.front();
  const double vmax = m_zGrid.back();
  m_rings.clear();
  for (unsigned int k = 0; k < nG; ++k) {
    ComponentChargedRing rings;
    rings.SetMedium(m_medium[k]);
    rings.SetArea(hmin, vmin, hmin, hmax, vmax, hmax);
    if (m_bDebug) rings.EnableDebugging();
    m_rings.push_back(std::move(rings));
  }

  // Set up the mesh.
  m_grid.resize(m_zSteps + 1);
  m_izMin.assign(nG, m_zSteps);
  m_izMax.assign(nG, 0);
  for (int iz = 0; iz <= m_zSteps; iz++) {
    m_grid[iz].resize(m_rSteps + 1);
    // Determine the gas gap.
    int k = 0;
    if (pp) {
      const int layer = pp->GetLayer(m_zGrid[iz]);
      if (layer >= 0) k = GetGasGapNumber(gasLayers, layer);
    }
    if (k != -1) {
      if (iz < m_izMin[k]) m_izMin[k] = iz;
      if (iz > m_izMax[k]) m_izMax[k] = iz;
    }
    for (int ir = 0; ir <= m_rSteps; ir++) {
      // Set gas gap index.
      m_grid[iz][ir].gap = k;
      m_grid[iz][ir].anode = false;
      // Set the electric field.
      m_grid[iz][ir].emag = std::abs(m_ezBkg[k]);
      m_grid[iz][ir].ctheta = m_ezBkg[k] > 0. ? -1. : 1.;
      m_grid[iz][ir].stheta = 0.;
      // Continue if nodes are not in a gas gap.
      if (k < 0) continue;
      // Set swarm parameters.
      // Magnitude of the drift velocity
      // (direction is antiparallel to the electric field).
      m_grid[iz][ir].vd = vd[k];
      m_grid[iz][ir].dL = dL[k];
      m_grid[iz][ir].dT = dT[k];
      m_grid[iz][ir].wv = wv[k];
      m_grid[iz][ir].wr = wr[k];
      m_grid[iz][ir].alpha = alphaPT[k];
      m_grid[iz][ir].eta = etaPT[k];
    }
  }

  // Set the anode flags.
  for (unsigned int k = 0; k < nG; k++) {
    const int izAnode = (m_ezBkg[k] > 0) ? m_izMin[k] : m_izMax[k];
    for (int ir = 0; ir <= m_rSteps; ir++) {
      m_grid[izAnode][ir].anode = true;
    }
  }

  // we define the time step as dz / max(Wr)
  m_dt = m_zStepSize / *std::max_element(wr.begin(), wr.end());

  if (m_bDebug) {
    std::cout << m_className << "::Prepare: Time step per loop: " << m_dt
              << " ns.\n";
  }

  // Place the electrons onto the grid.
  for (unsigned int k = 0; k < nG; ++k) {
    for (const auto &electron : electronsPerGap[k]) {
      SnapToGrid(electron.x, electron.y, electron.z, electron.n, k);
    }
  }
  return true;
}

void AvalancheGridSpaceCharge::GetSwarmParameters(Medium *m, const double emag,
                                                  double &vd, double &dL,
                                                  double &dT, double &wv,
                                                  double &wr, double &alphaPT,
                                                  double &etaPT) const {
  if (m_bDebug && false)
    std::cerr << m_className
              << "::GetSwarmParameters: Getting parameters at "
                 "|E| = "
              << emag << ".\n";

  if (!m) return;

  double alphaSST = 0.;
  m->ElectronTownsend(0., emag, 0., 0., 0., 0., alphaSST);
  double etaSST = 0.;
  m->ElectronAttachment(0., emag, 0., 0., 0., 0., etaSST);
  double vx, vy, vz;
  m->ElectronVelocity(0., emag, 0., 0., 0., 0., vx, vy, vz);
  vd = std::sqrt(vx * vx + vy * vy + vz * vz);  //< Wv in Magboltz
  // wv, wr <- take only Wr and 'vd' for Wv
  wr = 0.;
  if (!m_bUseTOF ||
      !m->ElectronVelocityFluxBulk(0., emag, 0., 0., 0., 0., wv, wr) ||
      wr < Small) {
    wr = vd;
  }
  // rates, if not available we take (alpha-eta)SST and ratio of alpha/eta =
  // Rion/Ratt Rion-Ratt = Reff (tagashira eq.)
  //  -> Rion converged to a rate with Wr and DL (using the one equation),
  //  alphaSST is either from SST and if not converged from magboltz itself.
  alphaPT = alphaSST;
  etaPT = etaSST;
  if (m_bUseTOF) {
    double rion = 0.;
    if (m->ElectronTOFIonisation(0., emag, 0., 0., 0., 0., rion)) {
      alphaPT = rion / wr;
    } else if (m_bDebug) {
      std::cerr << m_className << "::GetSwarmParameters: "
                << "TOF ionization rate not available.\n";
    }
    double ratt = 0.;
    if (m->ElectronTOFAttachment(0., emag, 0., 0., 0., 0., ratt)) {
      etaPT = ratt / wr;
    } else if (m_bDebug) {
      std::cerr << m_className << "::GetSwarmParameters: "
                << "TOF attachment rate not available.\n";
    }
  }

  // Diffusion coefficients
  m->ElectronDiffusion(0., emag, 0., 0., 0., 0., dL, dT);

  // print (and information about units!)
  if (m_bDebug && false) {
    std::cout << m_className << "::GetSwarmParameters:\n";
    std::printf("     Townsend coefficient (SST):   %15.6f 1/cm\n", alphaSST);
    std::printf("     Townsend coefficient (PT):    %15.6f 1/cm\n", alphaPT);
    std::printf("     Attachment coefficient (SST): %15.6f 1/cm\n", etaSST);
    std::printf("     Attachment coefficient (PT):  %15.6f 1/cm\n", etaPT);
    std::printf("     Flux velocity:                %15.6f cm/ns\n", vd);
    std::printf("     Bulk velocity:                %15.6f cm/ns\n", wr);
    std::printf("     Longitudinal diffusion:       %15.6f sqrt(cm)\n", dL);
    std::printf("     Transverse diffusion:         %15.6f sqrt(cm)\n", dT);
  }
}

bool AvalancheGridSpaceCharge::Step() {
  // Propagate grid nodes by one time step with updated electric fields
  // (Lippmann et al. approach).
  if (m_nEtot <= 0) return false;

  if (m_bDebug) {
    std::cout << m_className << "::Step: Start time: " << m_time << " ns\n";
  }

  const auto nG = m_ezBkg.size();
  if (m_bSpaceCharge && m_nEtot > 1e5) {
    // Clear existing rings.
    for (auto &ringsystem : m_rings) {
      ringsystem.ClearActiveRings();
      ringsystem.UpdateCentre(0., 0.);
    }

    for (int iz = 0; iz <= m_zSteps; iz++) {
      for (int ir = 0; ir <= m_rSteps; ir++) {
        const double q =
            -m_grid[iz][ir].nE + m_grid[iz][ir].nP - m_grid[iz][ir].nN;
        // If there is enough charge, create a ring.
        if (std::abs(q) < 0.1) continue;
        const double zf = m_zGrid[iz];
        const double rf = m_rGrid[ir];
        const int gap = m_grid[iz][ir].gap;
        // Add a ring to the gas gap.
        // Direct charge interaction
        m_rings[gap].AddChargedRing(rf, zf, 0., q);

        if (m_fieldOption == FieldOption::Mirror) {
          // Assume symmetric single-layer RPC with resistive layers of
          // equal permittivity.
          if (nG > 1) {
            throw std::runtime_error(
                "::Step: Mirror charge option implemented but not tested for "
                "MRPC.");
          }

          // mirror charge interaction
          for (int i = 0; i < m_iFieldApprox; i++) {
            if (i == 0) {
              // 2a, alpha12 = delta_Q
              double zf0 = zf + 2. * (m_zTop[gap] - zf);
              m_rings[gap].AddChargedRing(rf, zf0, 0., q * m_alpha12[gap]);

              // -2a', alpha12 = delta_Q
              zf0 = zf + 2. * (m_zBot[gap] - zf);
              m_rings[gap].AddChargedRing(rf, zf0, 0., q * m_alpha12[gap]);
            } else {
              // TODO: higher order mirror charges
              continue;
            }
          }
        }
      }
    }
  }

  // choose MC or Mean version depending on m_bMC; total electron > 1e5
  std::function<void(double, const long, const double, const double, long &,
                     double &, double &)>
      AvalancheGain = GetAvalancheSizeFromStep;
  if (!m_bMC && m_nEtot > 1e5) {
    AvalancheGain = GetMeanAvalancheSizeFromStep;
    // TODO: Diffusion
  }

  if (m_bSpaceCharge && m_nEtot > 1e5) {
    // Update the space-charge field and the swarm parameters on the nodes.
    // MRPC: SC-effect only within each gas gap and option="coulomb"
    double dummy;  // dummy E field component as we are using a 2d grid
    Medium *m = nullptr;
    int stat;

    for (int iz = 0; iz <= m_zSteps; iz++) {
      double zi = m_zGrid[iz];
      // Continue if not in a gas gap.
      int gap = m_grid[iz][0].gap;
      if (gap == -1) continue;
      for (int ir = 0; ir <= m_rSteps; ir++) {
        double ri = m_rGrid[ir];
        auto &nd = m_grid[iz][ir];

        // Reset the fields at this node.
        nd.emag = m_ezBkg[gap];
        nd.stheta = 0.;
        nd.ctheta = m_ezBkg[gap] > 0. ? -1. : 1.;
        // Skip if there are no electrons or if we are at an anode.
        if (nd.nE < 1 || nd.anode) continue;

        // Get the space charge field on this node.
        double erS = 0., ezS = 0.;
        m_rings[gap].ElectricField(ri, zi, 0., erS, ezS, dummy, m, stat);
        nd.emag = Mag(ezS + m_ezBkg[gap], erS);
        if (nd.emag > 1.e-8) {
          const double einv = 1. / nd.emag;
          nd.ctheta = -(ezS + m_ezBkg[gap]) * einv;
          nd.stheta = -erS * einv;
        }
        if (nd.emag >= m_ezThr[gap] && !m_bFieldK) {
          std::cout << m_className << ":Step:\n"
                    << "    Space-charge field reached "
                    << std::to_string(int(m_fStreamerK * 100))
                    << "% of background field in gas gap " << gap + 1 << "\n";
          // TODO: Total electrons in gas gap
          m_lElectronsK = m_evolution.back().second;
          m_bFieldK = true;
        }

        // Calculate the swarm parameters.
        GetSwarmParameters(m_medium[gap], nd.emag, nd.vd, nd.dL, nd.dT, nd.wv,
                           nd.wr, nd.alpha, nd.eta);

        // Get the new step distance.
        double step = std::abs(nd.wr * m_dt);

        // adaptive time stepping (this routine takes the smallest dt needed for
        // the current sc-field)
        if (m_bAdaptiveTime && step >= 2. * m_zStepSize) {
          // reset dt
          double dtPrev = m_dt;
          m_dt = m_zStepSize / nd.wr;

          if (m_bDebug) {
            std::cout << m_className << "::Step: Changed dt from " << dtPrev
                      << " to: " << m_dt << "\n"
                      << "      due to step size: " << step
                      << " bulk velocity: " << nd.wr << "\n"
                      << "      electric field: " << nd.emag
                      << " alpha: " << nd.alpha << " eta: " << nd.eta << "\n"
                      << "      diffusion longitudinal/transversal: " << nd.dL
                      << " " << nd.dT << "\n";
            ExportGrid("TIME_STEP_ADAPTION_" + std::to_string(m_dt));
          }
        }
      }
    }
  }

  // finish if stop reached and set at 100 * K %
  if (m_bStopAtK && m_bFieldK) return false;

  // Propagate the electrons with the updated field, swarm parameters
  // and time step.
  for (int iz = 0; iz <= m_zSteps; iz++) {
    // continue if not in gas gap
    const int gap = m_grid[iz][0].gap;
    if (gap == -1) continue;
    for (int ir = 0; ir <= m_rSteps; ir++) {
      auto &nd = m_grid[iz][ir];
      // Skip if we are at the anode or if there are no electrons.
      if (nd.anode || nd.nE < 1) continue;
      // Calculate the step distance.
      double step = std::abs(nd.wr * m_dt);
      // Calculate the avalanche size after the step.
      long nEOut = 0;
      double nPOut = 0.;
      double nNOut = 0.;
      if (m_saturated[gap]) {
        // Saturated case, don't evolve electrons in size
        nEOut = nd.nE;
        nPOut = 0,
        nNOut = 0;  //< strictly this is completely wrong because
                    // SC-bremsung creates huge amounts of ions
      } else {
        AvalancheGain(step, nd.nE, nd.alpha, nd.eta, nEOut, nPOut, nNOut);
      }
      m_nPtot += std::round(nPOut);

      // calculate steps against electric field i.e. correct sign.
      double stepZ = step * nd.ctheta;
      const double stepR = step * nd.stheta;

      if (m_bDiffusion) {
        // correct the stepping from diffusion + charge distribution
        DiffuseTimeStep(step, nEOut, std::round(nPOut), std::round(nNOut), iz,
                        ir, gap);
      } else {
        // calculate steps and distribute charges (no diffusion)
        DistributeCharges(nEOut, std::round(nPOut), std::round(nNOut), iz, ir,
                          stepZ, stepR, gap);
      }

      if (m_sensor->GetNumberOfElectrodes() > 0) {
        // For now, use a single charge at phi = 0.
        // TODO:
        // - Discretize phi and add signal for each slice with nElectron / M.
        // - At anode, the signal from diffusion is due to bounded plane not
        //   net 0 because diffusion tends more backwards, since forward they
        //   reach the boundary at earlier distance.
        constexpr double cphi = 1.;
        constexpr double sphi = 0.;
        const double r0 = m_rGrid[ir];
        const double x0 = m_centre[gap][0] + r0 * cphi;
        const double y0 = m_zGrid[iz];
        const double z0 = m_centre[gap][2] - r0 * sphi;

        // z-step outside gap domain, resize to stepZ = Anode - Current
        const double zMin = m_zGrid[m_izMin[gap]];
        const double zMax = m_zGrid[m_izMax[gap]];
        if (m_zGrid[iz] + stepZ < zMin) {
          stepZ = zMin - m_zGrid[iz];
        } else if (m_zGrid[iz] + stepZ > zMax) {
          stepZ = zMax - m_zGrid[iz];
        }

        const double r1 = m_rGrid[ir] + stepR;
        const double x1 = m_centre[gap][0] + r1 * cphi;
        const double y1 = m_zGrid[iz] + stepZ;
        const double z1 = m_centre[gap][2] - r1 * sphi;

        // Induced current from flux drift velocity i.e. introduce weight factor
        //< 1 if (Wv = velocity): Wr = flux
        const double weight = nd.vd / nd.wr;
        m_sensor->AddSignalWeightingPotential(-weight, {m_time, m_time + m_dt},
                                              {{x0, y0, z0}, {x1, y1, z1}},
                                              {(double)nd.nE, (double)nEOut});
      }
    }
  }

  // Update the clock.
  m_time += m_dt;

  // Count the electrons in each gap.
  std::vector<long> nEinGap(nG, 0);

  // Update the nodes.
  for (int iz = 0; iz <= m_zSteps; iz++) {
    for (int ir = 0; ir <= m_rSteps; ir++) {
      auto &nd = m_grid[iz][ir];
      if (nd.anode && m_bStick) {
        // Sticky anode: add electrons to the node.
        nd.nE += nd.nEHolder;
      } else {
        // Update node with the new number of electrons.
        nd.nE = nd.nEHolder;
        nEinGap[nd.gap] += nd.nE;
      }
      // Ions add up, also at the anode.
      nd.nP += nd.nPHolder;
      nd.nN += nd.nNHolder;

      nd.nEHolder = 0;
      nd.nPHolder = 0;
      nd.nNHolder = 0;
    }
  }
  // Get the total number of electrons.
  m_nEtot = std::accumulate(nEinGap.begin(), nEinGap.end(), 0);
  m_evolution.push_back(std::make_pair(m_time, m_nEtot));

  // Determine which gaps are saturated.
  m_saturated.assign(nG, false);
  for (unsigned int k = 0; k < nG; ++k) {
    if (!m_bSpaceCharge && nEinGap[k] > m_lNCrit) {
      m_saturated[k] = true;
    }
    if (m_bDebug) {
      std::printf("  %12ld active electrons in gas gap %3d\n", nEinGap[k], k);
    }
  }

  return true;
}

void AvalancheGridSpaceCharge::DiffuseTimeStep(const double dx, const long nE,
                                               const double nP, const double nN,
                                               const int iz, const int ir,
                                               const int gap) {
  // Add diffusion onto the step dx

  // Minimum number of groups (same values as Lippmann).
  constexpr long nMinGroups = 50;
  // Same values as Lippmann & Riegler
  constexpr std::array<long, 10> groupSizes = {1500, 800, 400, 200, 100,
                                               50,   20,  10,  5,   2};

  // Split in at least nMinGroups groups of size groupSize.
  long rest = 0, groups = 0, groupSize = 0;
  for (const auto size : groupSizes) {
    if (nE > nMinGroups * size) {
      groupSize = size;                     //< size of a single group
      groups = std::floor(nE / groupSize);  //< real # groups
      rest = nE - groups * groupSize;       //< rest
      break;
    }
  }

  // If there are too few electrons we diffuse each electron individually.
  if (nE <= nMinGroups * groupSizes.back()) {
    groupSize = 1;
    groups = nE;
    rest = 0;
  }

  double f = (double)groupSize / (double)nE;
  // Calculate diffusion and add to transport step.
  const double r = m_rGrid[ir];
  const double sqrtdx = std::sqrt(dx);
  auto &nd = m_grid[iz][ir];
  for (int group = 0; group < groups; group++) {
    // In the last loop we add the rest to the groupSize.
    if (group == groups - 1) {
      groupSize += rest;
      f = (double)groupSize / (double)nE;
    }
    // Diffuse each group as if it is a particle.
    // Calculate a diffusion step in a local coordinate system (U,V,W)
    // where W is along the E field, V is along e_phi,
    // and U is perpendicular to V and W.
    const double dU = RndmGaussian(0, nd.dT * sqrtdx);
    const double dV = RndmGaussian(0, nd.dT * sqrtdx);
    const double dW = RndmGaussian(dx, nd.dL * sqrtdx);

    // Transform to avalanche coordinate system
    // (Z,R,Y) where R mimics an X axis and Y is perpendicular to R and Z
    const double dX = nd.ctheta * dU + nd.stheta * dW;
    // dY = dV
    // Sign seems correct due to sign in cos- and sinTheta
    const double dZ = nd.ctheta * dW - nd.stheta * dU;

    // calculate the change of radius
    // sign correct and stepR >= -r
    const double stepR = std::sqrt((r + dX) * (r + dX) + dV * dV) - r;

    // Distribute nodes and add electrons/ions to Holder.
    // Fractional ion number is allowed otherwise loss of ions.
    DistributeCharges(groupSize, nP * f, nN * f, iz, ir, dZ, stepR, gap);
  }
}

void AvalancheGridSpaceCharge::DistributeCharges(long nE, double nP, double nN,
                                                 int iz, int ir, double stepZ,
                                                 double stepR, int gap) {
  // distributes the charges from a movement in Z and R direction
  // Compute the effective step size in r-direction
  stepR = std::abs(m_rGrid[ir] + stepR) - m_rGrid[ir];
  double zRatio = (m_zGrid[iz] + stepZ - m_zGrid[0]) * m_zInvStep;
  double rRatio =
      std::abs(m_rGrid[ir] + stepR) * m_rInvStep;  // can travel through r=0

  int iz1, signZstep;
  if (stepZ < 0) {
    iz1 = (int)ceil(zRatio);
    signZstep = -1;
  } else if (stepZ == 0) {
    iz1 = iz;
    signZstep = 0;
  } else {
    iz1 = (int)floor(zRatio);
    signZstep = +1;
  }

  int ir1, signRstep;
  if (stepR < 0) {
    ir1 = (int)ceil(rRatio);
    if (ir1 == 0) {
      // otherwise it travels to ir = -1
      signRstep = +1;
    } else {
      signRstep = -1;
    }
  } else if (stepR == 0) {
    // no movement in r direction
    ir1 = ir;
    signRstep = 0;
  } else {
    ir1 = (int)floor(rRatio);
    signRstep = +1;
  }

  // 4 point approximation:
  int iz2 = iz1 + signZstep;
  // always: ir2 >= 0
  int ir2 = ir1 + signRstep;

  const double bz = std::abs(zRatio - (double)iz1);
  const double az = 1. - bz;
  const double br = std::abs(rRatio - (double)ir1);
  const double ar = 1. - br;

  if (az < 0 || az > 1) throw std::runtime_error("az not in range");
  if (bz < 0 || bz > 1) throw std::runtime_error("bz not in range");
  if (ar < 0 || ar > 1) throw std::runtime_error("ar not in range");
  if (br < 0 || br > 1) throw std::runtime_error("br not in range");

  // check if still in grid else place at boundaries (will be absorbed in next
  // step)?
  if (iz1 < m_izMin[gap]) iz1 = m_izMin[gap];
  if (iz2 < m_izMin[gap]) iz2 = m_izMin[gap];
  if (iz1 > m_izMax[gap]) iz1 = m_izMax[gap];
  if (iz2 > m_izMax[gap]) iz2 = m_izMax[gap];

  if (ir1 > m_rSteps) ir1 = m_rSteps;
  if (ir2 > m_rSteps) ir2 = m_rSteps;

  // add to the nodes the electrons travelled to (into nEHolder as they
  // will mix)
  if (nE > 200) {
    m_grid[iz1][ir1].nEHolder += (long)std::round(nE * az * ar);
    m_grid[iz1][ir2].nEHolder += (long)std::round(nE * az * br);
    m_grid[iz2][ir1].nEHolder += (long)std::round(nE * bz * ar);
    m_grid[iz2][ir2].nEHolder += (long)std::round(nE * bz * br);

    // add positive ions to the nodes (smeared values allowed)
    m_grid[iz1][ir1].nPHolder += nP * az * ar;
    m_grid[iz1][ir2].nPHolder += nP * az * br;
    m_grid[iz2][ir1].nPHolder += nP * bz * ar;
    m_grid[iz2][ir2].nPHolder += nP * bz * br;

    // add negative ions to the nodes (smeared values allowed)
    m_grid[iz1][ir1].nNHolder += nN * az * ar;
    m_grid[iz1][ir2].nNHolder += nN * az * br;
    m_grid[iz2][ir1].nNHolder += nN * bz * ar;
    m_grid[iz2][ir2].nNHolder += nN * bz * br;

  } else {
    // Too few electrons.
    // Only move them to 1 node (instead of 4).
    iz1 = (az >= bz) ? iz1 : iz2;
    ir1 = (ar >= br) ? ir1 : ir2;

    m_grid[iz1][ir1].nEHolder += nE;
    m_grid[iz1][ir1].nPHolder += nP;
    m_grid[iz1][ir1].nNHolder += nN;
  }
}

double AvalancheGridSpaceCharge::GetMeanDistance() {
  // Returns mean distance of electrons on the whole grid (doesn't work for
  // MRPCs)
  long nE = 0;
  double z = 0.;
  for (int iz = 0; iz <= m_zSteps; iz++) {
    for (int ir = 0; ir <= m_rSteps; ir++) {
      if (m_grid[iz][ir].nE < 1) continue;
      nE += m_grid[iz][ir].nE;
      z += m_zGrid[iz] * m_grid[iz][ir].nE;
    }
  }
  return z / (double)nE;
}

}  // namespace Garfield
