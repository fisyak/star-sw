#include "Garfield/ComponentTcadBase.hh"

#include <algorithm>
#include <array>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <map>
#include <string>

#include "Garfield/Exceptions.hh"
#include "Garfield/GarfieldConstants.hh"
#include "Garfield/Medium.hh"
#include "Garfield/Utilities.hh"

namespace {

bool ExtractFromSquareBrackets(std::string& line) {
  const auto bra = line.find('[');
  const auto ket = line.find(']');
  if (ket < bra || bra == std::string::npos || ket == std::string::npos) {
    return false;
  }
  line = line.substr(bra + 1, ket - bra - 1);
  return true;
}

bool ExtractFromBrackets(std::string& line) {
  const auto bra = line.find('(');
  const auto ket = line.find(')');
  if (ket < bra || bra == std::string::npos || ket == std::string::npos) {
    return false;
  }
  line = line.substr(bra + 1, ket - bra - 1);
  return true;
}

void PrintError(const std::string& fcn, const std::string& filename,
                const std::size_t line) {
  std::cerr << fcn << ":\n"
            << "    Error reading file " << filename << " (line " << line
            << ").\n";
}
}  // namespace

namespace Garfield {

template <size_t N>
void ComponentTcadBase<N>::WeightingField(const double x, const double y,
                                          const double z, double& wx,
                                          double& wy, double& wz,
                                          const std::string& label) {
  wx = wy = wz = 0.;
  if (m_wfield[label].empty()) {
    std::cerr << m_className << "::WeightingField: No fieldmap for " << label
              << " available.\n";
    return;
  }
  double dx = 0., dy = 0., dz = 0.;
  if (!GetOffset(label, dx, dy, dz)) return;
  Interpolate(x - dx, y - dy, z - dz, m_wfield[label], wx, wy, wz);
}

template <size_t N>
double ComponentTcadBase<N>::WeightingPotential(const double x, const double y,
                                                const double z,
                                                const std::string& label) {
  if (m_wpot[label].empty()) {
    std::cerr << m_className << "::WeightingPotential: No fieldmap for "
              << label << " available.\n";
    return 0.;
  }
  double dx = 0., dy = 0., dz = 0.;
  if (!GetOffset(label, dx, dy, dz)) return 0.;
  double v = 0.;
  Interpolate(x - dx, y - dy, z - dz, m_wpot[label], v);
  return v;
}

template <size_t N>
void ComponentTcadBase<N>::DelayedWeightingField(const double x, const double y,
                                                 const double z, const double t,
                                                 double& wx, double& wy,
                                                 double& wz,
                                                 const std::string& label) {
  wx = wy = wz = 0.;

  if (m_dwf[label].empty()) {
    std::cerr << m_className << "::DelayedWeightingField: No fieldmap for "
              << label << " available.\n";
    return;
  }

  if (m_dwtf[label].empty()) return;
  if (t < m_dwtf[label].front() || t > m_dwtf[label].back()) return;

  double dx = 0., dy = 0., dz = 0.;
  if (!GetOffset(label, dx, dy, dz)) return;

  const auto it1 =
      std::upper_bound(m_dwtf[label].cbegin(), m_dwtf[label].cend(), t);
  const auto it0 = std::prev(it1);
  const double dt = t - *it0;
  const auto i0 = std::distance(m_dwtf[label].cbegin(), it0);
  double wx0 = 0., wy0 = 0., wz0 = 0.;
  Interpolate(x - dx, y - dy, z - dz, m_dwf[label][i0], wx0, wy0, wz0);
  if (dt < Small || it1 == m_dwtf[label].cend()) {
    wx = wx0;
    wy = wy0;
    wz = wz0;
    return;
  }
  const auto i1 = std::distance(m_dwtf[label].cbegin(), it1);
  double wx1 = 0., wy1 = 0., wz1 = 0.;
  Interpolate(x - dx, y - dy, z - dz, m_dwf[label][i1], wx1, wy1, wz1);
  const double f1 = dt / (*it1 - *it0);
  const double f0 = 1. - f1;
  wx = f0 * wx0 + f1 * wx1;
  wy = f0 * wy0 + f1 * wy1;
  wz = f0 * wz0 + f1 * wz1;
}

template <size_t N>
double ComponentTcadBase<N>::DelayedWeightingPotential(
    const double x, const double y, const double z, const double t,
    const std::string& label) {
  if (m_dwp[label].empty()) {
    std::cerr << m_className << "::DelayedWeightingPotential: No fieldmap for "
              << label << " available.\n";
    return 0.;
  }

  if (m_dwtp[label].empty()) return 0.;
  if (t < m_dwtp[label].front() || t > m_dwtp[label].back()) return 0.;

  double dx = 0., dy = 0., dz = 0.;
  if (!GetOffset(label, dx, dy, dz)) return 0.;

  const auto it1 =
      std::upper_bound(m_dwtp[label].cbegin(), m_dwtp[label].cend(), t);
  const auto it0 = std::prev(it1);
  const double dt = t - *it0;
  const auto i0 = std::distance(m_dwtp[label].cbegin(), it0);
  double v0 = 0.;
  Interpolate(x - dx, y - dy, z - dz, m_dwp[label][i0], v0);
  if (dt < Small || it1 == m_dwtp[label].cend()) return v0;

  const auto i1 = std::distance(m_dwtp[label].cbegin(), it1);
  double v1 = 0.;
  Interpolate(x - dx, y - dy, z - dz, m_dwp[label][i1], v1);
  const double f1 = dt / (*it1 - *it0);
  const double f0 = 1. - f1;
  return f0 * v0 + f1 * v1;
}

template <size_t N>
bool ComponentTcadBase<N>::GetOffset(const std::string& label, double& dx,
                                     double& dy, double& dz) const {
  if (m_wshift.count(label) == 0 || m_wshift.at(label).empty()) return false;

  dx = m_wshift.at(label)[0];
  dy = m_wshift.at(label)[1];
  dz = m_wshift.at(label)[2];

  return true;
}

template <size_t N>
bool ComponentTcadBase<N>::Initialise(const std::string& gridfilename,
                                      const std::string& datafilename) {
  m_ready = false;
  Cleanup();
  // Import mesh data from .grd file.
  if (!LoadGrid(gridfilename)) {
    std::cerr << m_className << "::Initialise:\n"
              << "    Importing mesh data failed.\n";
    Cleanup();
    return false;
  }
  // Import electric field, potential and other data from .dat file.
  if (!LoadData(datafilename)) {
    std::cerr << m_className << "::Initialise:\n"
              << "    Importing electric field and potential failed.\n";
    Cleanup();
    return false;
  }

  // Find min./max. coordinates and potentials.
  for (size_t i = 0; i < N; ++i) {
    m_bbMax[i] = m_vertices[m_elements[0].vertex[0]][i];
    m_bbMin[i] = m_bbMax[i];
  }
  const size_t nElements = m_elements.size();
  for (size_t i = 0; i < nElements; ++i) {
    Element& element = m_elements[i];
    std::array<double, N> xmin = m_vertices[element.vertex[0]];
    std::array<double, N> xmax = m_vertices[element.vertex[0]];
    const auto nV = ElementVertices(m_elements[i]);
    for (std::size_t j = 0; j < nV; ++j) {
      const auto& v = m_vertices[m_elements[i].vertex[j]];
      for (size_t k = 0; k < N; ++k) {
        xmin[k] = std::min(xmin[k], v[k]);
        xmax[k] = std::max(xmax[k], v[k]);
      }
    }
    constexpr double tol = 1.e-6;
    for (size_t k = 0; k < N; ++k) {
      m_elements[i].bbMin[k] = xmin[k] - tol;
      m_elements[i].bbMax[k] = xmax[k] + tol;
      m_bbMin[k] = std::min(m_bbMin[k], xmin[k]);
      m_bbMax[k] = std::max(m_bbMax[k], xmax[k]);
    }
  }
  m_pMin = *std::min_element(m_epot.begin(), m_epot.end());
  m_pMax = *std::max_element(m_epot.begin(), m_epot.end());

  std::cout << m_className << "::Initialise:\n"
            << "    Available data:\n";
  if (!m_epot.empty()) std::cout << "      Electrostatic potential\n";
  if (!m_efield.empty()) std::cout << "      Electric field\n";
  if (!m_eMobility.empty()) std::cout << "      Electron mobility\n";
  if (!m_hMobility.empty()) std::cout << "      Hole mobility\n";
  if (!m_eVelocity.empty()) std::cout << "      Electron velocity\n";
  if (!m_hVelocity.empty()) std::cout << "      Hole velocity\n";
  if (!m_eAlpha.empty()) std::cout << "      Electron impact ionisation\n";
  if (!m_hAlpha.empty()) std::cout << "      Hole impact ionisation\n";
  if (!m_eLifetime.empty()) std::cout << "      Electron lifetime\n";
  if (!m_hLifetime.empty()) std::cout << "      Hole lifetime\n";
  if (!m_donors.empty()) {
    std::cout << "      " << m_donors.size() << " donor-type traps\n";
  }
  if (!m_acceptors.empty()) {
    std::cout << "      " << m_acceptors.size() << " acceptor-type traps\n";
  }
  const std::array<std::string, 3> axes = {"x", "y", "z"};
  std::cout << "    Bounding box:\n";
  for (size_t i = 0; i < N; ++i) {
    std::cout << "      " << m_bbMin[i] << " < " << axes[i] << " [cm] < "
              << m_bbMax[i] << "\n";
  }
  std::cout << "    Voltage range:\n"
            << "      " << m_pMin << " < V < " << m_pMax << "\n";

  bool ok = true;

  // Count the number of elements belonging to a region.
  const auto nRegions = m_regions.size();
  std::vector<size_t> nElementsByRegion(nRegions, 0);
  // Keep track of elements that are not part of any region.
  std::vector<size_t> looseElements;

  // Count the different element shapes.
  std::map<int, std::size_t> nElementsByShape;
  if (N == 2) {
    nElementsByShape = {{0, 0}, {1, 0}, {2, 0}, {3, 0}};
  } else {
    nElementsByShape = {{0, 0}, {2, 0}, {5, 0}};
  }
  std::size_t nElementsOther = 0;

  // Keep track of degenerate elements.
  std::vector<size_t> degenerateElements;

  for (size_t i = 0; i < nElements; ++i) {
    const Element& element = m_elements[i];
    if (element.region < nRegions) {
      ++nElementsByRegion[element.region];
    } else {
      looseElements.push_back(i);
    }
    if (nElementsByShape.count(element.type) == 0) {
      ++nElementsOther;
      continue;
    }
    nElementsByShape[element.type] += 1;
    bool degenerate = false;
    const auto nV = ElementVertices(m_elements[i]);
    for (std::size_t j = 0; j < nV; ++j) {
      for (std::size_t k = j + 1; k < nV; ++k) {
        if (element.vertex[j] == element.vertex[k]) {
          degenerate = true;
          break;
        }
      }
      if (degenerate) break;
    }
    if (degenerate) {
      degenerateElements.push_back(i);
    }
  }

  if (!degenerateElements.empty()) {
    std::cerr << m_className << "::Initialise:\n"
              << "    The following elements are degenerate:\n";
    for (size_t i : degenerateElements) std::cerr << "      " << i << "\n";
    ok = false;
  }

  if (!looseElements.empty()) {
    std::cerr << m_className << "::Initialise:\n"
              << "    The following elements are not part of any region:\n";
    for (size_t i : looseElements) std::cerr << "      " << i << "\n";
    ok = false;
  }

  std::cout << m_className << "::Initialise:\n"
            << "    Number of regions: " << nRegions << "\n";
  for (size_t i = 0; i < nRegions; ++i) {
    std::cout << "      " << i << ": " << m_regions[i].name;
    if (!m_regions[i].material.empty()) {
      std::cout << " (" << m_regions[i].material << ")";
    }
    std::cout << ", " << nElementsByRegion[i] << " elements\n";
  }

  std::map<int, std::string> shapes = {{0, "points"},
                                       {1, "lines"},
                                       {2, "triangles"},
                                       {3, "rectangles"},
                                       {5, "tetrahedra"}};

  std::cout << "    Number of elements: " << nElements << "\n";
  for (const auto& n : nElementsByShape) {
    if (n.second > 0) {
      std::cout << "      " << n.second << " " << shapes[n.first] << "\n";
    }
  }
  if (nElementsOther > 0) {
    std::cerr << "      " << nElementsOther << " elements of unknown type.\n"
              << "      Program bug!\n";
    m_ready = false;
    Cleanup();
    return false;
  }

  std::cout << "    Number of vertices: " << m_vertices.size() << "\n";
  if (!ok) {
    m_ready = false;
    Cleanup();
    return false;
  }

  FillTree();

  m_ready = true;
  UpdatePeriodicity();
  std::cout << m_className << "::Initialise: Initialisation finished.\n";
  return true;
}

template <size_t N>
bool ComponentTcadBase<N>::GetVoltageRange(double& vmin, double& vmax) {
  if (!m_ready) return false;
  vmin = m_pMin;
  vmax = m_pMax;
  return true;
}

template <size_t N>
bool ComponentTcadBase<N>::SetWeightingField(const std::string& datfile1,
                                             const std::string& datfile2,
                                             const double dv,
                                             const std::string& label) {
  if (!m_ready) {
    std::cerr << m_className << "::SetWeightingField:\n"
              << "    Mesh is not available. Call Initialise first.\n";
    return false;
  }
  if (dv < Small) {
    std::cerr << m_className << "::SetWeightingField:\n"
              << "    Voltage difference must be > 0.\n";
    return false;
  }
  const double s = 1. / dv;

  // Check if a weighting field with the same label already exists.
  if (m_wfield.count(label) > 0) {
    std::cout << m_className << "::SetWeightingField:\n"
              << "    Replacing existing weighting field " << label << ".\n";
    m_wfield[label].clear();
    m_wpot[label].clear();
    m_wshift[label].clear();
  }
  if (m_dwf.count(label) > 0) {
    m_dwf[label].clear();
    m_dwp[label].clear();

    m_dwtf.clear();
    m_dwtp.clear();
  }

  // Load first the field/potential at nominal bias.
  std::vector<std::array<double, N> > wf1;
  std::vector<double> wp1;
  if (!LoadWeightingField(datfile1, wf1, wp1)) {
    std::cerr << m_className << "::SetWeightingField:\n"
              << "    Could not import data from " << datfile1 << ".\n";
    return false;
  }

  // Then load the field/potential for the configuration with the potential
  // at the electrode to be read out increased by small voltage dv.
  std::vector<std::array<double, N> > wf2;
  std::vector<double> wp2;
  if (!LoadWeightingField(datfile2, wf2, wp2)) {
    std::cerr << m_className << "::SetWeightingField:\n"
              << "    Could not import data from " << datfile2 << ".\n";
    return false;
  }
  const size_t nVertices = m_vertices.size();
  bool foundField = true;
  if (wf1.size() != nVertices || wf2.size() != nVertices) {
    foundField = false;
    std::cerr << m_className << "::SetWeightingField:\n"
              << "    Could not load electric field values.\n";
  }
  bool foundPotential = true;
  if (wp1.size() != nVertices || wp2.size() != nVertices) {
    foundPotential = false;
    std::cerr << m_className << "::SetWeightingField:\n"
              << "    Could not load electrostatic potentials.\n";
  }
  if (!foundField && !foundPotential) return false;
  if (foundField) {
    m_wfield[label].resize(nVertices);
    for (size_t i = 0; i < nVertices; ++i) {
      for (size_t j = 0; j < N; ++j) {
        m_wfield[label][i][j] = (wf2[i][j] - wf1[i][j]) * s;
      }
    }
  }
  if (foundPotential) {
    m_wpot[label].assign(nVertices, 0.);
    for (size_t i = 0; i < nVertices; ++i) {
      m_wpot[label][i] = (wp2[i] - wp1[i]) * s;
    }
  }

  m_wshift[label] = {0., 0., 0.};
  return true;
}

template <size_t N>
bool ComponentTcadBase<N>::SetDynamicWeightingPotential(
    const std::string& datfile1, const std::string& datfile2, const double dv,
    const double t, const std::string& label) {
  if (t < Small) {
    return SetWeightingField(datfile1, datfile2, dv, label);
  }

  if (!m_ready) {
    std::cerr << m_className << "::SetDynamicWeightingPotential:\n"
              << "    Mesh is not available. Call Initialise first.\n";
    return false;
  }
  if (dv < Small) {
    std::cerr << m_className << "::SetDynamicWeightingPotential:\n"
              << "    Voltage difference must be > 0.\n";
    return false;
  }
  const double s = 1. / dv;

  // Check if the prompt weighting potential with the same label already exists.
  if (m_wpot.count(label) == 0 || m_wpot[label].empty()) {
    std::cerr << m_className << "::SetDynamicWeightingPotential:\n"
              << "    Prompt component not present.\n"
              << "    Import the map for t = 0 first.\n";
    return false;
  }

  // Load the first map.
  std::vector<std::array<double, N> > wf1;
  std::vector<double> wp1;
  if (!LoadWeightingField(datfile1, wf1, wp1)) {
    std::cerr << m_className << "::SetDynamicWeightingPotential:\n"
              << "    Could not import data from " << datfile1 << ".\n";
    return false;
  }
  // Load the second map.
  std::vector<std::array<double, N> > wf2;
  std::vector<double> wp2;
  if (!LoadWeightingField(datfile2, wf2, wp2)) {
    std::cerr << m_className << "::SetDynamicWeightingPotential:\n"
              << "    Could not import data from " << datfile2 << ".\n";
    return false;
  }
  const size_t nVertices = m_vertices.size();
  if (wp1.size() != nVertices || wp2.size() != nVertices) {
    std::cerr << m_className << "::SetDynamicWeightingPotential:\n"
              << "    Could not load electrostatic potentials.\n";
    return false;
  }
  if (m_wpot[label].size() != nVertices) {
    std::cerr << m_className << "::SetDynamicWeightingPotential:\n"
              << "    Prompt weighting potential not present.\n";
    return false;
  }
  std::vector<double> wp(nVertices, 0.);
  for (size_t i = 0; i < nVertices; ++i) {
    wp[i] = (wp2[i] - wp1[i]) * s;
    // Subtract the prompt component.
    wp[i] -= m_wpot[label][i];
  }
  if (m_dwtp[label].empty() || t > m_dwtp[label].back()) {
    m_dwtp[label].push_back(t);
    m_dwp[label].push_back(std::move(wp));
  } else {
    const auto it =
        std::upper_bound(m_dwtp[label].begin(), m_dwtp[label].end(), t);
    const auto n = std::distance(m_dwtp[label].begin(), it);
    m_dwtp[label].insert(it, t);
    m_dwp[label].insert(m_dwp[label].begin() + n, std::move(wp));
  }
  return true;
}

template <size_t N>
bool ComponentTcadBase<N>::SetDynamicWeightingField(const std::string& datfile1,
                                                    const std::string& datfile2,
                                                    const double dv,
                                                    const double t,
                                                    const std::string& label) {
  if (t < Small) {
    return SetWeightingField(datfile1, datfile2, dv, label);
  }
  if (!m_ready) {
    std::cerr << m_className << "::SetDynamicWeightingField:\n"
              << "    Mesh is not available. Call Initialise first.\n";
    return false;
  }
  if (dv < Small) {
    std::cerr << m_className << "::SetDynamicWeightingField:\n"
              << "    Voltage difference must be > 0.\n";
    return false;
  }
  const double s = 1. / dv;

  // Check if the prompt weighting potential with the same label already exists.
  if (m_wfield.count(label) == 0 || m_wfield[label].empty()) {
    std::cerr << m_className << "::SetDynamicWeightingField:\n"
              << "    Prompt component not present.\n"
              << "    Import the map for t = 0 first.\n";
    return false;
  }

  // Load the first map.
  std::vector<std::array<double, N> > wf1;
  std::vector<double> wp1;
  if (!LoadWeightingField(datfile1, wf1, wp1)) {
    std::cerr << m_className << "::SetDynamicWeightingField:\n"
              << "    Could not import data from " << datfile1 << ".\n";
    return false;
  }
  // Load the second map.
  std::vector<std::array<double, N> > wf2;
  std::vector<double> wp2;
  if (!LoadWeightingField(datfile2, wf2, wp2)) {
    std::cerr << m_className << "::SetDynamicWeightingField:\n"
              << "    Could not import data from " << datfile2 << ".\n";
    return false;
  }
  const size_t nVertices = m_vertices.size();
  if (wf1.size() != nVertices || wf2.size() != nVertices) {
    std::cerr << m_className << "::SetDynamicWeightingField:\n"
              << "    Could not load electric field values.\n";
    return false;
  }
  if (m_wfield[label].size() != nVertices) {
    std::cerr << m_className << "::SetDynamicWeightingField:\n"
              << "    Prompt weighting field not present.\n";
    return false;
  }
  std::vector<std::array<double, N> > wf;
  wf.resize(nVertices);
  for (size_t i = 0; i < nVertices; ++i) {
    for (size_t j = 0; j < N; ++j) {
      wf[i][j] = (wf2[i][j] - wf1[i][j]) * s;
    }
  }
  if (m_dwtf[label].empty() || t > m_dwtf[label].back()) {
    m_dwtf[label].push_back(t);
    m_dwf[label].push_back(std::move(wf));
  } else {
    const auto it =
        std::upper_bound(m_dwtf[label].begin(), m_dwtf[label].end(), t);
    const auto n = std::distance(m_dwtf[label].begin(), it);
    m_dwtf[label].insert(it, t);
    m_dwf[label].insert(m_dwf[label].begin() + n, std::move(wf));
  }
  return true;
}

template <size_t N>
bool ComponentTcadBase<N>::SetWeightingFieldShift(const std::string& label,
                                                  const double x,
                                                  const double y,
                                                  const double z) {
  if ((m_wfield.count(label) == 0 || m_wfield[label].empty()) &&
      (m_wpot.count(label) == 0 || m_wpot[label].empty())) {
    std::cerr << m_className << "::SetWeightingFieldShift:\n"
              << "    No map of weighting potentials/fields loaded.\n";
    return false;
  }

  m_wshift[label] = {x, y, z};

  if (m_wshift.count(label) > 0) {
    std::cout << m_className << "::SetWeightingFieldShift:\n"
              << "    Changing offset of electrode \'" << label << "\' to ("
              << x << ", " << y << ", " << z << ") cm.\n";

  } else {
    std::cout << m_className << "::SetWeightingFieldShift:\n"
              << "    Adding electrode \'" << label << "\' with offset (" << x
              << ", " << y << ", " << z << ") cm.\n";
  }
  return true;
}

template <size_t N>
void ComponentTcadBase<N>::EnableVelocityMap(const bool on) {
  m_useVelocityMap = on;
  if (on && m_ready && (m_eVelocity.empty() && m_hVelocity.empty())) {
    std::cout << m_className << "::EnableVelocityMap:\n"
              << "    Warning: current map does not have velocity data.\n";
  }
}

template <size_t N>
void ComponentTcadBase<N>::EnableTrapOccupationMap(const bool on) {
  m_useTrapOccMap = on;
  if (on && m_ready && (m_acceptorOcc.empty() && m_donorOcc.empty())) {
    std::cout << m_className << "::EnableTrapOccupationMap:\n"
              << "    Warning: current map does not have "
              << " trap occupation probability data.\n";
  }
  UpdateAttachment();
}

template <size_t N>
void ComponentTcadBase<N>::EnableLifetimeMap(const bool on) {
  m_useLifetimeMap = on;
  if (on && m_ready && (m_eLifetime.empty() && m_hLifetime.empty())) {
    std::cout << m_className << "::EnableLifetimeMap:\n"
              << "    Warning: current map does not have lifetime data.\n";
  }
  UpdateAttachment();
}

template <size_t N>
bool ComponentTcadBase<N>::GetElementNodes(const size_t i,
                                           std::vector<size_t>& nodes) const {
  nodes.clear();
  if (i >= m_elements.size()) {
    std::cerr << m_className << "::GetElementNodes: Index out of range.\n";
    return false;
  }

  const Element& element = m_elements[i];
  const size_t nVertices = ElementVertices(element);
  for (size_t j = 0; j < nVertices; ++j) {
    nodes.push_back(element.vertex[j]);
  }
  return true;
}

template <size_t N>
bool ComponentTcadBase<N>::GetElementRegion(const size_t i, size_t& region,
                                            bool& drift) const {
  if (i >= m_elements.size()) {
    std::cerr << m_className << "::GetElementRegion: Index out of range.\n";
    return false;
  }
  region = m_elements[i].region;
  drift = m_regions[region].drift;
  return true;
}

template <size_t N>
bool ComponentTcadBase<N>::LoadGrid(const std::string& filename) {
  // Open the file containing the mesh description.
  std::ifstream gridfile(filename);
  if (!gridfile) {
    std::cerr << m_className << "::LoadGrid:\n"
              << "    Could not open file " << filename << ".\n";
    return false;
  }
  // Delete existing mesh information.
  Cleanup();
  // Count line numbers.
  std::size_t iLine = 0;
  // Get the number of regions.
  size_t nRegions = 0;
  // Read the file line by line.
  std::string line;
  while (std::getline(gridfile, line)) {
    ++iLine;
    // Strip white space from the beginning of the line.
    ltrim(line);
    if (line.empty()) continue;
    // Find entry 'nb_regions'.
    if (line.substr(0, 10) != "nb_regions") continue;
    const auto pEq = line.find('=');
    if (pEq == std::string::npos) {
      // No "=" sign found.
      std::cerr << m_className << "::LoadGrid:\n"
                << "    Could not read number of regions.\n";
      return false;
    }
    line = line.substr(pEq + 1);
    std::istringstream data(line);
    data >> nRegions;
    break;
  }
  if (gridfile.eof()) {
    // Reached end of file.
    std::cerr << m_className << "::LoadGrid:\n"
              << "    Could not find entry 'nb_regions' in file\n"
              << "    " << filename << ".\n";
    return false;
  } else if (gridfile.fail()) {
    // Error reading from the file.
    PrintError(m_className + "::LoadGrid", filename, iLine);
    return false;
  }
  m_regions.resize(nRegions);
  for (size_t j = 0; j < nRegions; ++j) {
    m_regions[j].name = "";
    m_regions[j].material = "";
    m_regions[j].drift = false;
    m_regions[j].medium = nullptr;
  }
  if (m_debug) {
    std::cout << m_className << "::LoadGrid:\n"
              << "    Found " << nRegions << " regions.\n";
  }
  // Get the region names.
  while (std::getline(gridfile, line)) {
    ++iLine;
    ltrim(line);
    if (line.empty()) continue;
    // Find entry 'regions'.
    if (line.substr(0, 7) != "regions") continue;
    // Get region names (given in brackets).
    if (!ExtractFromSquareBrackets(line)) {
      std::cerr << m_className << "::LoadGrid:\n"
                << "    Could not read region names.\n";
      return false;
    }
    std::istringstream data(line);
    for (size_t j = 0; j < nRegions; ++j) {
      data >> m_regions[j].name;
      data.clear();
      // Assume by default that all regions are active.
      m_regions[j].drift = true;
      m_regions[j].medium = nullptr;
    }
    break;
  }
  if (gridfile.eof()) {
    // Reached end of file.
    std::cerr << m_className << "::LoadGrid:\n"
              << "    Could not find entry 'regions' in file\n"
              << "    " << filename << ".\n";
    return false;
  } else if (gridfile.fail()) {
    // Error reading from the file.
    PrintError(m_className + "::LoadGrid", filename, iLine);
    return false;
  }

  // Get the materials.
  while (std::getline(gridfile, line)) {
    ++iLine;
    ltrim(line);
    if (line.empty()) continue;
    // Find entry 'materials'.
    if (line.substr(0, 9) != "materials") continue;
    // Get region names (given in brackets).
    if (!ExtractFromSquareBrackets(line)) {
      std::cerr << m_className << "::LoadGrid:\n"
                << "    Could not read materials.\n";
      return false;
    }
    std::istringstream data(line);
    for (size_t j = 0; j < nRegions; ++j) {
      data >> m_regions[j].material;
      data.clear();
    }
    break;
  }
  if (gridfile.eof()) {
    // Reached end of file.
    std::cerr << m_className << "::LoadGrid:\n"
              << "    Could not find entry 'materials' in file\n"
              << "    " << filename << ".\n";
  } else if (gridfile.fail()) {
    // Error reading from the file.
    PrintError(m_className + "::LoadGrid", filename, iLine);
  }

  // Get the vertices.
  size_t nVertices = 0;
  while (std::getline(gridfile, line)) {
    ++iLine;
    ltrim(line);
    if (line.empty()) continue;
    // Find section 'Vertices'.
    if (line.substr(0, 8) != "Vertices") continue;
    // Get number of vertices (given in brackets).
    if (!ExtractFromBrackets(line)) {
      std::cerr << m_className << "::LoadGrid:\n"
                << "    Could not read number of vertices.\n";
      return false;
    }
    std::istringstream data(line);
    data >> nVertices;
    m_vertices.resize(nVertices);
    // Get the coordinates of every vertex.
    for (size_t j = 0; j < nVertices; ++j) {
      for (size_t k = 0; k < N; ++k) {
        gridfile >> m_vertices[j][k];
        // Change units from micron to cm.
        m_vertices[j][k] *= 1.e-4;
      }
      ++iLine;
    }
    break;
  }
  if (gridfile.eof()) {
    std::cerr << m_className << "::LoadGrid:\n"
              << "    Could not find section 'Vertices' in file\n"
              << "    " << filename << ".\n";
    return false;
  } else if (gridfile.fail()) {
    PrintError(m_className + "::LoadGrid", filename, iLine);
    return false;
  }

  // Get the "edges" (lines connecting two vertices).
  size_t nEdges = 0;
  // Temporary arrays for storing edge points.
  std::vector<std::size_t> edgeP1;
  std::vector<std::size_t> edgeP2;
  while (std::getline(gridfile, line)) {
    ++iLine;
    ltrim(line);
    if (line.empty()) continue;
    // Find section 'Edges'.
    if (line.substr(0, 5) != "Edges") continue;
    // Get the number of edges (given in brackets).
    if (!ExtractFromBrackets(line)) {
      std::cerr << m_className << "::LoadGrid:\n"
                << "    Could not read number of edges.\n";
      return false;
    }
    std::istringstream data(line);
    data >> nEdges;
    edgeP1.resize(nEdges);
    edgeP2.resize(nEdges);
    // Get the indices of the two endpoints.
    for (size_t j = 0; j < nEdges; ++j) {
      gridfile >> edgeP1[j] >> edgeP2[j];
      ++iLine;
    }
    break;
  }
  if (gridfile.eof()) {
    std::cerr << m_className << "::LoadGrid:\n"
              << "    Could not find section 'Edges' in file\n"
              << "    " << filename << ".\n";
    return false;
  } else if (gridfile.fail()) {
    PrintError(m_className + "::LoadGrid", filename, iLine);
    return false;
  }

  for (size_t i = 0; i < nEdges; ++i) {
    // Make sure the indices of the edge endpoints are not out of range.
    if (edgeP1[i] >= nVertices || edgeP2[i] >= nVertices) {
      std::cerr << m_className << "::LoadGrid:\n"
                << "    Vertex index of edge " << i << " out of range.\n";
      return false;
    }
    // Make sure the edge is non-degenerate.
    if (edgeP1[i] == edgeP2[i]) {
      std::cerr << m_className << "::LoadGrid:\n"
                << "    Edge " << i << " is degenerate.\n";
      return false;
    }
  }

  // Get the "faces" (only for 3D maps).
  struct Face {
    // Indices of edges
    int edge[4];
    int type;
  };
  size_t nFaces = 0;
  std::vector<Face> faces;
  if (N == 3) {
    while (std::getline(gridfile, line)) {
      ++iLine;
      ltrim(line);
      if (line.empty()) continue;
      // Find section 'Faces'.
      if (line.substr(0, 5) != "Faces") continue;
      // Get the number of faces (given in brackets).
      if (!ExtractFromBrackets(line)) {
        std::cerr << m_className << "::LoadGrid:\n"
                  << "    Could not read number of faces.\n";
        return false;
      }
      std::istringstream data(line);
      data >> nFaces;
      faces.resize(nFaces);
      // Get the indices of the edges constituting this face.
      for (size_t j = 0; j < nFaces; ++j) {
        gridfile >> faces[j].type;
        if (faces[j].type != 3 && faces[j].type != 4) {
          std::cerr << m_className << "::LoadGrid:\n"
                    << "    Face with index " << j
                    << " has invalid number of edges, " << faces[j].type
                    << ".\n";
          return false;
        }
        for (int k = 0; k < faces[j].type; ++k) {
          gridfile >> faces[j].edge[k];
        }
      }
      iLine += nFaces - 1;
      break;
    }
    if (gridfile.eof()) {
      std::cerr << m_className << "::LoadGrid:\n"
                << "    Could not find section 'Faces' in file\n"
                << "    " << filename << ".\n";
      return false;
    } else if (gridfile.fail()) {
      PrintError(m_className + "::LoadGrid", filename, iLine);
      return false;
    }
  }

  // Get the elements.
  size_t nElements = 0;
  while (std::getline(gridfile, line)) {
    ++iLine;
    ltrim(line);
    if (line.empty()) continue;
    // Find section 'Elements'.
    if (line.substr(0, 8) != "Elements") continue;
    // Get number of elements (given in brackets).
    if (!ExtractFromBrackets(line)) {
      std::cerr << m_className << "::LoadGrid:\n"
                << "    Could not read number of elements.\n";
      return false;
    }
    std::istringstream data(line);
    data >> nElements;
    data.clear();
    // Resize the list of elements.
    m_elements.resize(nElements);
    // Get type and constituting edges of each element.
    for (size_t j = 0; j < nElements; ++j) {
      ++iLine;
      std::size_t type = 0;
      gridfile >> type;
      if (N == 2) {
        if (type == 0) {
          // Point
          std::size_t p = 0;
          gridfile >> p;
          // Make sure the index is not out of range.
          if (p >= nVertices) {
            PrintError(m_className + "::LoadGrid", filename, iLine);
            std::cerr << "    Vertex index out of range.\n";
            return false;
          }
          m_elements[j].vertex[0] = p;
        } else if (type == 1) {
          // Line
          for (size_t k = 0; k < 2; ++k) {
            int p = 0;
            gridfile >> p;
            if (p < 0) p = -p - 1;
            // Make sure the index is not out of range.
            if (p >= (int)nVertices) {
              PrintError(m_className + "::LoadGrid", filename, iLine);
              std::cerr << "    Vertex index out of range.\n";
              return false;
            }
            m_elements[j].vertex[k] = p;
          }
        } else if (type == 2) {
          // Triangle
          int p0 = 0, p1 = 0, p2 = 0;
          gridfile >> p0 >> p1 >> p2;
          // Negative edge index means that the sequence of the two points
          // is supposed to be inverted.
          // The actual index is then given by "-index - 1".
          if (p0 < 0) p0 = -p0 - 1;
          if (p1 < 0) p1 = -p1 - 1;
          if (p2 < 0) p2 = -p2 - 1;
          // Make sure the indices are not out of range.
          if (p0 >= (int)nEdges || p1 >= (int)nEdges || p2 >= (int)nEdges) {
            PrintError(m_className + "::LoadGrid", filename, iLine);
            std::cerr << "    Edge index out of range.\n";
            return false;
          }
          m_elements[j].vertex[0] = edgeP1[p0];
          m_elements[j].vertex[1] = edgeP2[p0];
          if (edgeP1[p1] != m_elements[j].vertex[0] &&
              edgeP1[p1] != m_elements[j].vertex[1]) {
            m_elements[j].vertex[2] = edgeP1[p1];
          } else {
            m_elements[j].vertex[2] = edgeP2[p1];
          }
          // Rearrange vertices such that point 0 is on the left.
          while (m_vertices[m_elements[j].vertex[0]][0] >
                     m_vertices[m_elements[j].vertex[1]][0] ||
                 m_vertices[m_elements[j].vertex[0]][0] >
                     m_vertices[m_elements[j].vertex[2]][0]) {
            const int tmp = m_elements[j].vertex[0];
            m_elements[j].vertex[0] = m_elements[j].vertex[1];
            m_elements[j].vertex[1] = m_elements[j].vertex[2];
            m_elements[j].vertex[2] = tmp;
          }
        } else if (type == 3) {
          // Rectangle
          for (size_t k = 0; k < 4; ++k) {
            int p = 0;
            gridfile >> p;
            // Make sure the index is not out of range.
            if (p >= (int)nEdges || -p - 1 >= (int)nEdges) {
              PrintError(m_className + "::LoadGrid", filename, iLine);
              std::cerr << "    Edge index out of range.\n";
              return false;
            }
            if (p >= 0) {
              m_elements[j].vertex[k] = edgeP1[p];
            } else {
              m_elements[j].vertex[k] = edgeP2[-p - 1];
            }
          }
          // Rearrange vertices such that point 0 is on the left.
          while (m_vertices[m_elements[j].vertex[0]][0] >
                     m_vertices[m_elements[j].vertex[1]][0] ||
                 m_vertices[m_elements[j].vertex[0]][0] >
                     m_vertices[m_elements[j].vertex[2]][0] ||
                 m_vertices[m_elements[j].vertex[0]][0] >
                     m_vertices[m_elements[j].vertex[3]][0]) {
            const int tmp = m_elements[j].vertex[0];
            m_elements[j].vertex[0] = m_elements[j].vertex[1];
            m_elements[j].vertex[1] = m_elements[j].vertex[2];
            m_elements[j].vertex[2] = m_elements[j].vertex[3];
            m_elements[j].vertex[3] = tmp;
          }
        } else {
          // Other element types are not permitted for 2d grids.
          PrintError(m_className + "::LoadGrid", filename, iLine);
          std::cerr << "    Invalid element type (" << type
                    << ") for 2d mesh.\n";
          return false;
        }
      } else if (N == 3) {
        if (type == 0) {
          // Point
          std::size_t p = 0;
          gridfile >> p;
          // Make sure the index is not out of range.
          if (p >= nVertices) {
            PrintError(m_className + "::LoadGrid", filename, iLine);
            std::cerr << "    Vertex index out of range.\n";
            return false;
          }
          m_elements[j].vertex[0] = p;
        } else if (type == 2) {
          // Triangle
          int edge0, edge1, edge2;
          gridfile >> edge0 >> edge1 >> edge2;
          // Get the vertices.
          // Negative edge index means that the sequence of the two points
          // is supposed to be inverted.
          // The actual index is then given by "-index - 1".
          // For our purposes, the orientation does not matter.
          if (edge0 < 0) edge0 = -edge0 - 1;
          if (edge1 < 0) edge1 = -edge1 - 1;
          if (edge2 < 0) edge2 = -edge2 - 1;
          // Make sure the indices are not out of range.
          if (edge0 >= (int)nEdges || edge1 >= (int)nEdges ||
              edge2 >= (int)nEdges) {
            PrintError(m_className + "::LoadGrid", filename, iLine);
            std::cerr << "    Edge index out of range.\n";
            return false;
          }
          m_elements[j].vertex[0] = edgeP1[edge0];
          m_elements[j].vertex[1] = edgeP2[edge0];
          if (edgeP1[edge1] != m_elements[j].vertex[0] &&
              edgeP1[edge1] != m_elements[j].vertex[1]) {
            m_elements[j].vertex[2] = edgeP1[edge1];
          } else {
            m_elements[j].vertex[2] = edgeP2[edge1];
          }
        } else if (type == 5) {
          // Tetrahedron
          // Get the faces.
          // Negative face index means that the sequence of the edges
          // is supposed to be inverted.
          // For our purposes, the orientation does not matter.
          int face0, face1, face2, face3;
          gridfile >> face0 >> face1 >> face2 >> face3;
          if (face0 < 0) face0 = -face0 - 1;
          if (face1 < 0) face1 = -face1 - 1;
          if (face2 < 0) face2 = -face2 - 1;
          if (face3 < 0) face3 = -face3 - 1;
          // Make sure the face indices are not out of range.
          if (face0 >= (int)nFaces || face1 >= (int)nFaces ||
              face2 >= (int)nFaces || face3 >= (int)nFaces) {
            PrintError(m_className + "::LoadGrid", filename, iLine);
            std::cerr << "    Face index out of range.\n";
            return false;
          }
          // Get the edges of the first face.
          int edge0 = faces[face0].edge[0];
          int edge1 = faces[face0].edge[1];
          int edge2 = faces[face0].edge[2];
          if (edge0 < 0) edge0 = -edge0 - 1;
          if (edge1 < 0) edge1 = -edge1 - 1;
          if (edge2 < 0) edge2 = -edge2 - 1;
          // Make sure the edge indices are not out of range.
          if (edge0 >= (int)nEdges || edge1 >= (int)nEdges ||
              edge2 >= (int)nEdges) {
            PrintError(m_className + "::LoadGrid", filename, iLine);
            std::cerr << "    Edge index out of range.\n";
            return false;
          }
          // Get the first three vertices.
          m_elements[j].vertex[0] = edgeP1[edge0];
          m_elements[j].vertex[1] = edgeP2[edge0];
          if (edgeP1[edge1] != m_elements[j].vertex[0] &&
              edgeP1[edge1] != m_elements[j].vertex[1]) {
            m_elements[j].vertex[2] = edgeP1[edge1];
          } else {
            m_elements[j].vertex[2] = edgeP2[edge1];
          }
          // Get the fourth vertex from face 1.
          edge0 = faces[face1].edge[0];
          edge1 = faces[face1].edge[1];
          edge2 = faces[face1].edge[2];
          if (edge0 < 0) edge0 = -edge0 - 1;
          if (edge1 < 0) edge1 = -edge1 - 1;
          if (edge2 < 0) edge2 = -edge2 - 1;
          const auto v0 = m_elements[j].vertex[0];
          const auto v1 = m_elements[j].vertex[1];
          const auto v2 = m_elements[j].vertex[2];
          if (edgeP1[edge0] != v0 && edgeP1[edge0] != v1 &&
              edgeP1[edge0] != v2) {
            m_elements[j].vertex[3] = edgeP1[edge0];
          } else if (edgeP2[edge0] != v0 && edgeP2[edge0] != v1 &&
                     edgeP2[edge0] != v2) {
            m_elements[j].vertex[3] = edgeP2[edge0];
          } else if (edgeP1[edge1] != v0 && edgeP1[edge1] != v1 &&
                     edgeP1[edge1] != v2) {
            m_elements[j].vertex[3] = edgeP1[edge1];
          } else if (edgeP2[edge1] != v0 && edgeP2[edge1] != v1 &&
                     edgeP2[edge1] != v2) {
            m_elements[j].vertex[3] = edgeP2[edge1];
          } else {
            PrintError(m_className + "::LoadGrid", filename, iLine);
            std::cerr << "    Face 1 of element " << j << " is degenerate.\n";
            return false;
          }
        } else {
          // Other element types are not allowed.
          PrintError(m_className + "::LoadGrid", filename, iLine);
          if (type == 0 || type == 1) {
            std::cerr << "    Invalid element type (" << type
                      << ") for 3d mesh.\n";
          } else {
            std::cerr << "    Element type " << type << " is not supported.\n"
                      << "    Remesh with option -t to create only"
                      << " triangles and tetrahedra.\n";
          }
          return false;
        }
      }
      m_elements[j].type = type;
      m_elements[j].region = m_regions.size();
    }
    break;
  }
  if (gridfile.eof()) {
    std::cerr << m_className << "::LoadGrid:\n"
              << "    Could not find section 'Elements' in file\n"
              << "    " << filename << ".\n";
    return false;
  } else if (gridfile.fail()) {
    PrintError(m_className + "::LoadGrid", filename, iLine);
    return false;
  }

  // Assign regions to elements.
  while (std::getline(gridfile, line)) {
    ltrim(line);
    if (line.empty()) continue;
    // Find section 'Region'.
    if (line.substr(0, 6) != "Region") continue;
    // Get region name (given in brackets).
    if (!ExtractFromBrackets(line)) {
      std::cerr << m_className << "::LoadGrid:\n"
                << "    Could not read region name.\n";
      return false;
    }
    std::istringstream data(line);
    ltrim(line);
    rtrim(line);
    const std::string name = line;
    // std::string name;
    // data >> name;
    // data.clear();
    const size_t index = FindRegion(name);
    if (index >= m_regions.size()) {
      // Specified region name is not in the list.
      std::cerr << m_className << "::LoadGrid:\n"
                << "    Unknown region " << name << ".\n";
      continue;
    }
    std::getline(gridfile, line);
    std::getline(gridfile, line);
    if (!ExtractFromBrackets(line)) {
      std::cerr << m_className << "::LoadGrid:\n"
                << "    Could not read number of elements in region " << name
                << ".\n";
      return false;
    }
    int nElementsRegion;
    data.str(line);
    data.clear();
    data >> nElementsRegion;
    for (int j = 0; j < nElementsRegion; ++j) {
      size_t iElement = 0;
      gridfile >> iElement;
      if (iElement >= m_elements.size()) {
        std::cerr << m_className << "::LoadGrid:\n"
                  << "    Error reading element indices for region " << name
                  << ".\n";
        return false;
      }
      m_elements[iElement].region = index;
    }
  }
  if (gridfile.fail() && !gridfile.eof()) {
    std::cerr << m_className << "::LoadGrid:\n"
              << "    Error reading file " << filename << ".\n";
    return false;
  }
  return true;
}

template <size_t N>
bool ComponentTcadBase<N>::LoadData(const std::string& filename) {
  std::ifstream datafile(filename);
  if (!datafile) {
    std::cerr << m_className << "::LoadData:\n"
              << "    Could not open file " << filename << ".\n";
    return false;
  }
  const size_t nVertices = m_vertices.size();
  std::vector<std::size_t> fillCount(nVertices, 0);

  std::array<double, N> zeros;
  zeros.fill(0.);
  // Read the file line by line.
  std::string line;
  while (std::getline(datafile, line)) {
    // Strip white space from the beginning of the line.
    ltrim(line);
    // Skip empty lines.
    if (line.empty()) continue;
    // Find data section.
    if (line.substr(0, 9) != "function ") continue;
    // Read type of data set.
    auto pEq = line.find('=');
    if (pEq == std::string::npos) {
      // No "=" found.
      std::cerr << m_className << "::LoadData:\n"
                << "    Error reading file " << filename << ".\n"
                << "    Line:\n    " << line << "\n";
      return false;
    }
    line = line.substr(pEq + 1);
    std::string dataset;
    std::istringstream data(line);
    data >> dataset;
    data.clear();
    std::getline(datafile, line);
    pEq = line.find('=');
    if (pEq == std::string::npos) {
      // No "=" found.
      std::cerr << m_className << "::LoadData:\n"
                << "    Error reading file " << filename << ".\n"
                << "    Line:\n    " << line << "\n";
      return false;
    }
    line = line.substr(pEq + 1);
    std::string dstype;
    data.str(line);
    data.clear();
    data >> dstype;
    if (m_debug && dataset != "[") {
      std::cout << m_className << "::LoadData: Found " << dstype << " dataset "
                << dataset << ".\n";
    }
    if (dstype == "scalar" &&
        (dataset == "ElectricField" || dataset == "eDriftVelocity" ||
         dataset == "hDriftVelocity")) {
      if (m_debug) std::cout << "    Skipping this dataset.\n";
      continue;
    }
    if (dataset == "ElectrostaticPotential") {
      if (m_epot.empty()) m_epot.assign(nVertices, 0.);
      if (!ReadDataset(datafile, dataset)) {
        m_epot.clear();
        return false;
      }
    } else if (dataset == "ElectricField") {
      if (m_efield.empty()) m_efield.assign(nVertices, zeros);
      if (!ReadDataset(datafile, dataset)) {
        m_efield.clear();
        return false;
      }
    } else if (dataset == "eDriftVelocity") {
      if (m_eVelocity.empty()) m_eVelocity.assign(nVertices, zeros);
      if (!ReadDataset(datafile, dataset)) {
        m_eVelocity.clear();
        return false;
      }
    } else if (dataset == "hDriftVelocity") {
      if (m_hVelocity.empty()) m_hVelocity.assign(nVertices, zeros);
      if (!ReadDataset(datafile, dataset)) {
        m_hVelocity.clear();
        return false;
      }
    } else if (dataset == "eMobility") {
      if (m_eMobility.empty()) m_eMobility.assign(nVertices, 0.);
      if (!ReadDataset(datafile, dataset)) {
        m_eMobility.clear();
        return false;
      }
    } else if (dataset == "hMobility") {
      if (m_hMobility.empty()) m_hMobility.assign(nVertices, 0.);
      if (!ReadDataset(datafile, dataset)) {
        m_hMobility.clear();
        return false;
      }
    } else if (dataset == "eAlphaAvalanche") {
      if (m_eAlpha.empty()) m_eAlpha.assign(nVertices, 0.);
      if (!ReadDataset(datafile, dataset)) {
        m_eAlpha.clear();
        return false;
      }
    } else if (dataset == "hAlphaAvalanche") {
      if (m_hAlpha.empty()) m_hAlpha.assign(nVertices, 0.);
      if (!ReadDataset(datafile, dataset)) {
        m_hAlpha.clear();
        return false;
      }
    } else if (dataset == "eLifetime") {
      if (m_eLifetime.empty()) m_eLifetime.assign(nVertices, 0.);
      if (!ReadDataset(datafile, dataset)) {
        m_eLifetime.clear();
        return false;
      }
    } else if (dataset == "hLifetime") {
      if (m_hLifetime.empty()) m_hLifetime.assign(nVertices, 0.);
      if (!ReadDataset(datafile, dataset)) {
        m_hLifetime.clear();
        return false;
      }
    } else if (dataset.substr(0, 14) == "TrapOccupation" &&
               dataset.substr(17, 2) == "Do") {
      if (!ReadDataset(datafile, dataset)) return false;
      Defect donor;
      donor.xsece = -1.;
      donor.xsech = -1.;
      donor.conc = -1.;
      m_donors.push_back(donor);
    } else if (dataset.substr(0, 14) == "TrapOccupation" &&
               dataset.substr(17, 2) == "Ac") {
      if (!ReadDataset(datafile, dataset)) return false;
      Defect acceptor;
      acceptor.xsece = -1.;
      acceptor.xsech = -1.;
      acceptor.conc = -1.;
      m_acceptors.push_back(acceptor);
    }
  }
  if (datafile.fail() && !datafile.eof()) {
    std::cerr << m_className << "::LoadData:\n"
              << "    Error reading file " << filename << "\n";
    return false;
  }
  if (m_useTrapOccMap || m_useLifetimeMap) UpdateAttachment();
  return true;
}

template <size_t N>
bool ComponentTcadBase<N>::ReadDataset(std::ifstream& datafile,
                                       const std::string& dataset) {
  if (!datafile.is_open()) return false;
  enum DataSet {
    ElectrostaticPotential,
    EField,
    eDriftVelocity,
    hDriftVelocity,
    eMobility,
    hMobility,
    eAlpha,
    hAlpha,
    eLifetime,
    hLifetime,
    DonorTrapOccupation,
    AcceptorTrapOccupation,
    Unknown
  };
  DataSet ds = Unknown;
  if (dataset == "ElectrostaticPotential") {
    ds = ElectrostaticPotential;
  } else if (dataset == "ElectricField") {
    ds = EField;
  } else if (dataset == "eDriftVelocity") {
    ds = eDriftVelocity;
  } else if (dataset == "hDriftVelocity") {
    ds = hDriftVelocity;
  } else if (dataset == "eMobility") {
    ds = eMobility;
  } else if (dataset == "hMobility") {
    ds = hMobility;
  } else if (dataset == "eAlphaAvalanche") {
    ds = eAlpha;
  } else if (dataset == "hAlphaAvalanche") {
    ds = hAlpha;
  } else if (dataset == "eLifetime") {
    ds = eLifetime;
  } else if (dataset == "hLifetime") {
    ds = hLifetime;
  } else if (dataset.substr(0, 14) == "TrapOccupation") {
    if (dataset.substr(17, 2) == "Do") {
      ds = DonorTrapOccupation;
    } else if (dataset.substr(17, 2) == "Ac") {
      ds = AcceptorTrapOccupation;
    }
  } else {
    std::cerr << m_className << "::ReadDataset:\n"
              << "    Unexpected dataset " << dataset << ".\n";
    return false;
  }
  bool isVector = false;
  if (ds == EField || ds == eDriftVelocity || ds == hDriftVelocity) {
    isVector = true;
  }
  std::string line;
  std::getline(datafile, line);
  std::getline(datafile, line);
  std::getline(datafile, line);
  // Get the region name (given in brackets).
  if (!ExtractFromSquareBrackets(line)) {
    std::cerr << m_className << "::ReadDataset:\n"
              << "    Cannot extract region name.\n"
              << "    Line:\n    " << line << "\n";
    return false;
  }
  std::string name;
  std::istringstream data(line);
  data >> name;
  data.clear();
  // Check if the region name matches one from the mesh file.
  const size_t index = FindRegion(name);
  if (index >= m_regions.size()) {
    std::cerr << m_className << "::ReadDataset:\n"
              << "    Unknown region " << name << ".\n";
    return false;
  }
  if (m_debug) {
    std::cout << m_className << "::ReadDataset:\n"
              << "    Reading dataset " << dataset << " for region " << name
              << ".\n";
  }
  // Get the number of values.
  std::getline(datafile, line);
  if (!ExtractFromBrackets(line)) {
    std::cerr << m_className << "::ReadDataset:\n"
              << "    Cannot extract number of values to be read.\n"
              << "    Line:\n    " << line << "\n";
    return false;
  }
  int nValues;
  data.str(line);
  data.clear();
  data >> nValues;
  if (isVector) nValues /= N;
  if (m_debug) std::cout << "    Expecting " << nValues << " values.\n";
  // Mark the vertices belonging to this region.
  const size_t nVertices = m_vertices.size();
  std::vector<bool> isInRegion(nVertices, false);
  size_t nVerticesInRegion = 0;
  size_t nElementsInRegion = 0;
  for (const auto& element : m_elements) {
    if (element.region != index) continue;
    ++nElementsInRegion;
    const std::size_t nV = ElementVertices(element);
    for (std::size_t k = 0; k < nV; ++k) {
      if (isInRegion[element.vertex[k]]) continue;
      isInRegion[element.vertex[k]] = true;
      ++nVerticesInRegion;
    }
  }
  if (m_debug) {
    std::cout << "    Region has " << nElementsInRegion << " elements and "
              << nVerticesInRegion << " vertices.\n";
  }
  std::size_t ivertex = 0;
  for (int j = 0; j < nValues; ++j) {
    // Read the next value.
    std::array<long double, N> val;
    if (isVector) {
      for (size_t k = 0; k < N; ++k) datafile >> val[k];
    } else {
      datafile >> val[0];
    }
    // Find the next vertex belonging to the region.
    while (ivertex < nVertices) {
      if (isInRegion[ivertex]) break;
      ++ivertex;
    }
    // Check if there is a mismatch between the number of vertices
    // and the number of potential values.
    if (ivertex >= nVertices) {
      std::cerr << m_className << "::ReadDataset:\n"
                << "    Dataset " << dataset << " has more values than "
                << "there are vertices in region " << name << "\n";
      return false;
    }

    switch (ds) {
      case ElectrostaticPotential:
        m_epot[ivertex] = val[0];
        break;
      case EField:
        for (size_t k = 0; k < N; ++k) m_efield[ivertex][k] = val[k];
        break;
      case eDriftVelocity:
        // Scale from cm/s to cm/ns.
        for (size_t k = 0; k < N; ++k) {
          m_eVelocity[ivertex][k] = val[k] * 1.e-9;
        }
        break;
      case hDriftVelocity:
        // Scale from cm/s to cm/ns.
        for (size_t k = 0; k < N; ++k) {
          m_hVelocity[ivertex][k] = val[k] * 1.e-9;
        }
        break;
      case eMobility:
        // Convert from cm2 / (V s) to cm2 / (V ns).
        m_eMobility[ivertex] = val[0] * 1.e-9;
        break;
      case hMobility:
        // Convert from cm2 / (V s) to cm2 / (V ns).
        m_hMobility[ivertex] = val[0] * 1.e-9;
        break;
      case eAlpha:
        m_eAlpha[ivertex] = val[0];
        break;
      case hAlpha:
        m_hAlpha[ivertex] = val[0];
        break;
      case eLifetime:
        // Convert from s to ns.
        m_eLifetime[ivertex] = val[0] * 1.e9;
        break;
      case hLifetime:
        // Convert from s to ns.
        m_hLifetime[ivertex] = val[0] * 1.e9;
        break;
      case DonorTrapOccupation:
        m_donorOcc[ivertex].push_back(val[0]);
        break;
      case AcceptorTrapOccupation:
        m_acceptorOcc[ivertex].push_back(val[0]);
        break;
      default:
        std::cerr << m_className << "::ReadDataset:\n"
                  << "    Unexpected dataset (" << ds << "). Program bug!\n";
        return false;
    }
    ++ivertex;
  }
  return true;
}

template <size_t N>
bool ComponentTcadBase<N>::LoadWeightingField(
    const std::string& filename, std::vector<std::array<double, N> >& wf,
    std::vector<double>& wp) {
  std::ifstream datafile(filename, std::ios::in);
  if (!datafile) {
    std::cerr << m_className << "::LoadWeightingField:\n"
              << "    Could not open file " << filename << ".\n";
    return false;
  }
  const size_t nVertices = m_vertices.size();
  std::array<double, N> zeros;
  zeros.fill(0.);
  bool ok = true;
  // Read the file line by line.
  std::string line;
  while (std::getline(datafile, line)) {
    // Strip white space from the beginning of the line.
    ltrim(line);
    if (line.empty()) continue;
    // Find data section.
    if (line.substr(0, 9) != "function ") continue;
    // Read type of data set.
    auto pEq = line.find('=');
    if (pEq == std::string::npos) {
      // No "=" found.
      std::cerr << m_className << "::LoadWeightingField:\n"
                << "    Error reading file " << filename << ".\n"
                << "    Line:\n    " << line << "\n";
      return false;
    }
    line = line.substr(pEq + 1);
    std::string dataset;
    std::istringstream data(line);
    data >> dataset;
    data.clear();
    if (dataset != "ElectrostaticPotential" && dataset != "ElectricField") {
      continue;
    }
    std::getline(datafile, line);
    pEq = line.find('=');
    if (pEq == std::string::npos) {
      // No "=" found.
      std::cerr << m_className << "::LoadWeightingField:\n"
                << "    Error reading file " << filename << ".\n"
                << "    Line:\n    " << line << "\n";
      return false;
    }
    line = line.substr(pEq + 1);
    std::string dstype;
    data.str(line);
    data.clear();
    data >> dstype;
    if (dstype == "scalar" && dataset == "ElectricField") {
      if (m_debug) {
        std::cout << m_className << "::LoadWeightingField:\n"
                  << "    Skipping scalar dataset " << dataset << ".\n";
      }
      continue;
    }
    bool field = false;
    if (dataset == "ElectricField") {
      if (wf.empty()) wf.assign(nVertices, zeros);
      field = true;
    } else {
      if (wp.empty()) wp.assign(nVertices, 0.);
    }
    std::getline(datafile, line);
    std::getline(datafile, line);
    std::getline(datafile, line);
    // Get the region name (given in brackets).
    if (!ExtractFromSquareBrackets(line)) {
      std::cerr << m_className << "::LoadWeightingField:\n"
                << "    Cannot extract region name.\n"
                << "    Line:\n    " << line << "\n";
      ok = false;
      break;
    }
    ltrim(line);
    rtrim(line);
    const std::string name = line;
    // Check if the region name matches one from the mesh file.
    const auto index = FindRegion(name);
    if (index >= m_regions.size()) {
      std::cerr << m_className << "::LoadWeightingField:\n"
                << "    Unknown region " << name << ".\n";
      ok = false;
      break;
    }
    // Get the number of values.
    std::getline(datafile, line);
    if (!ExtractFromBrackets(line)) {
      std::cerr << m_className << "::LoadWeightingField:\n"
                << "    Cannot extract number of values to be read.\n"
                << "    Line:\n    " << line << "\n";
      ok = false;
      break;
    }
    int nValues;
    data.str(line);
    data.clear();
    data >> nValues;
    if (field) nValues /= N;
    // Mark the vertices belonging to this region.
    std::vector<bool> isInRegion(nVertices, false);
    const size_t nElements = m_elements.size();
    for (size_t j = 0; j < nElements; ++j) {
      if (m_elements[j].region != index) continue;
      const std::size_t nV = ElementVertices(m_elements[j]);
      for (std::size_t k = 0; k < nV; ++k) {
        isInRegion[m_elements[j].vertex[k]] = true;
      }
    }
    std::size_t ivertex = 0;
    for (int j = 0; j < nValues; ++j) {
      // Read the next value.
      std::array<double, N> val;
      if (field) {
        for (size_t k = 0; k < N; ++k) datafile >> val[k];
      } else {
        datafile >> val[0];
      }
      // Find the next vertex belonging to the region.
      while (ivertex < nVertices) {
        if (isInRegion[ivertex]) break;
        ++ivertex;
      }
      // Check if there is a mismatch between the number of vertices
      // and the number of values.
      if (ivertex >= nVertices) {
        std::cerr << m_className << "::LoadWeightingField:\n"
                  << "    Dataset " << dataset
                  << " has more values than vertices in region " << name
                  << "\n";
        ok = false;
        break;
      }
      if (field) {
        wf[ivertex] = val;
      } else {
        wp[ivertex] = val[0];
      }
      ++ivertex;
    }
  }

  if (!ok || (datafile.fail() && !datafile.eof())) {
    std::cerr << m_className << "::LoadWeightingField:\n"
              << "    Error reading file " << filename << "\n";
    return false;
  }
  return true;
}

template <size_t N>
void ComponentTcadBase<N>::PrintRegions() const {
  if (m_regions.empty()) {
    std::cerr << m_className << "::PrintRegions:\n"
              << "    No regions are currently defined.\n";
    return;
  }

  const size_t nRegions = m_regions.size();
  std::cout << m_className << "::PrintRegions:\n"
            << "    Currently " << nRegions << " regions are defined.\n"
            << " Index   Name               Material            Medium\n";
  for (size_t i = 0; i < nRegions; ++i) {
    std::cout << std::setw(8) << std::right << i << " " << std::setw(20)
              << std::left << m_regions[i].name << " " << std::setw(18)
              << std::left << m_regions[i].material << " ";
    if (!m_regions[i].medium) {
      std::cout << std::setw(18) << "none";
    } else {
      std::cout << std::setw(18) << m_regions[i].medium->GetName();
    }
    if (m_regions[i].drift) {
      std::cout << " (active)\n";
    } else {
      std::cout << "\n";
    }
  }
}

template <size_t N>
void ComponentTcadBase<N>::GetRegion(const std::size_t i, std::string& name,
                                     bool& active) const {
  if (i >= m_regions.size()) {
    std::cerr << m_className << "::GetRegion: Index out of range.\n";
    return;
  }
  name = m_regions[i].name;
  active = m_regions[i].drift;
}

template <size_t N>
void ComponentTcadBase<N>::SetDriftRegion(const size_t i) {
  if (i >= m_regions.size()) {
    std::cerr << m_className << "::SetDriftRegion: Index out of range.\n";
    return;
  }
  m_regions[i].drift = true;
}

template <size_t N>
void ComponentTcadBase<N>::UnsetDriftRegion(const size_t i) {
  if (i >= m_regions.size()) {
    std::cerr << m_className << "::UnsetDriftRegion: Index out of range.\n";
    return;
  }
  m_regions[i].drift = false;
}

template <std::size_t N>
void ComponentTcadBase<N>::SetMedium(const std::size_t index, Medium* medium) {
  if (index >= m_regions.size())
    throw Exception("::SetMedium: Index out of range");
  if (!medium) throw Exception("::SetMedium: Null pointer");
  m_regions[index].medium = medium;
}

template <std::size_t N>
void ComponentTcadBase<N>::SetMedium(const std::string& material,
                                     Medium* medium) {
  if (!medium) throw Exception("::SetMedium: Null pointer");
  size_t nMatch = 0;
  const auto nRegions = m_regions.size();
  for (size_t i = 0; i < nRegions; ++i) {
    if (material != m_regions[i].material) continue;
    m_regions[i].medium = medium;
    std::cout << m_className << "::SetMedium: Associating region " << i << " ("
              << m_regions[i].name << ") with " << medium->GetName() << ".\n";
    ++nMatch;
  }
  if (nMatch == 0) {
    std::cerr << m_className << "::SetMedium: Found no region with material "
              << material << ".\n";
  }
}

template <size_t N>
bool ComponentTcadBase<N>::SetDonor(const size_t i, const double eXsec,
                                    const double hXsec, const double conc) {
  if (i >= m_donors.size()) {
    std::cerr << m_className << "::SetDonor: Index out of range.\n";
    return false;
  }
  m_donors[i].xsece = eXsec;
  m_donors[i].xsech = hXsec;
  m_donors[i].conc = conc;

  UpdateAttachment();
  return true;
}

template <size_t N>
bool ComponentTcadBase<N>::SetAcceptor(const size_t i, const double eXsec,
                                       const double hXsec, const double conc) {
  if (i >= m_acceptors.size()) {
    std::cerr << m_className << "::SetAcceptor: Index out of range.\n";
    return false;
  }
  m_acceptors[i].xsece = eXsec;
  m_acceptors[i].xsech = hXsec;
  m_acceptors[i].conc = conc;

  UpdateAttachment();
  return true;
}

template <size_t N>
bool ComponentTcadBase<N>::ElectronAttachment(const double x, const double y,
                                              const double z, double& eta) {
  Interpolate(x, y, z, m_eEta, eta);
  return true;
}

template <size_t N>
bool ComponentTcadBase<N>::HoleAttachment(const double x, const double y,
                                          const double z, double& eta) {
  Interpolate(x, y, z, m_hEta, eta);
  return true;
}

template <size_t N>
bool ComponentTcadBase<N>::ElectronTownsend(const double x, const double y,
                                            const double z, double& alpha) {
  Interpolate(x, y, z, m_eAlpha, alpha);
  return true;
}

template <size_t N>
bool ComponentTcadBase<N>::HoleTownsend(const double x, const double y,
                                        const double z, double& alpha) {
  Interpolate(x, y, z, m_hAlpha, alpha);
  return true;
}

template <size_t N>
bool ComponentTcadBase<N>::ElectronVelocity(const double x, const double y,
                                            const double z, double& vx,
                                            double& vy, double& vz) {
  return Interpolate(x, y, z, m_eVelocity, vx, vy, vz);
}

template <size_t N>
bool ComponentTcadBase<N>::HoleVelocity(const double x, const double y,
                                        const double z, double& vx, double& vy,
                                        double& vz) {
  return Interpolate(x, y, z, m_hVelocity, vx, vy, vz);
}

template <size_t N>
double ComponentTcadBase<N>::ElectronLifetime(const double x, const double y,
                                              const double z) {
  double tau = 0.;
  Interpolate(x, y, z, m_eLifetime, tau);
  return tau;
}

template <size_t N>
double ComponentTcadBase<N>::HoleLifetime(const double x, const double y,
                                          const double z) {
  double tau = 0.;
  Interpolate(x, y, z, m_hLifetime, tau);
  return tau;
}

template <size_t N>
bool ComponentTcadBase<N>::ElectronMobility(const double x, const double y,
                                            const double z, double& mu) {
  return Interpolate(x, y, z, m_eMobility, mu);
}

template <size_t N>
bool ComponentTcadBase<N>::HoleMobility(const double x, const double y,
                                        const double z, double& mu) {
  return Interpolate(x, y, z, m_hMobility, mu);
}

template <size_t N>
void ComponentTcadBase<N>::UpdatePeriodicity() {
  if (!m_ready) {
    std::cerr << m_className << "::UpdatePeriodicity:\n"
              << "    Field map not available.\n";
    return;
  }

  // Check for conflicts.
  for (size_t i = 0; i < 3; ++i) {
    const Symmetry sym = m_symmetries.GetSymmetries(i);
    if (sym.Has(Symmetry::Type::Periodic) && sym.Has(Symmetry::Type::Mirror)) {
      std::cerr << m_className << "::UpdatePeriodicity:\n"
                << "    Both simple and mirror periodicity requested. Reset.\n";
      m_symmetries.Deactivate(Symmetry::Type::Periodic);
      m_symmetries.Deactivate(Symmetry::Type::Mirror);
    }
  }
  if (m_symmetries.Has(Symmetry::Type::Axial)) {
    std::cerr << m_className << "::UpdatePeriodicity:\n"
              << "    Axial symmetry is not supported. Reset.\n";
    m_symmetries.Deactivate(Symmetry::Type::Axial);
  }
  if (m_symmetries.Has(Symmetry::Type::Rotation)) {
    std::cerr << m_className << "::UpdatePeriodicity:\n"
              << "    Rotation symmetry is not supported. Reset.\n";
    m_symmetries.Deactivate(Symmetry::Type::TriangleXZ);
  }

  // Triangle symmetry
  if constexpr (N == 2) {
    // No xz or yz planes in 2D.
    if (m_symmetries.Has(Symmetry::Type::TriangleXZ) ||
        m_symmetries.Has(Symmetry::Type::TriangleYZ)) {
      std::cerr << m_className << "::UpdatePeriodicity2d:\n"
                << "    Triangle periodicity does not allow\n"
                << "    for xz or yz planes; reset.\n";
      m_symmetries.Deactivate(Symmetry::Type::Triangle);
      m_symmetries.Deactivate(Symmetry::Type::Mirror);
      m_triangleSymmetricOct = 0;
    }
  }

  if constexpr (N == 3) {
    std::cout << "Check N = 3" << std::endl;
    const int triSymmN = m_symmetries.NumberOf(Symmetry::Type::Triangle);
    if (triSymmN == 1) {
      if (m_triangleSymmetricOct < 1 || m_triangleSymmetricOct > 8) {
        std::cerr << m_className << "::UpdatePeriodicity:\n"
                  << "    For triangle symmetry, octant must be in the range "
                     "1–8; reset.\n";
        m_symmetries.Deactivate(Symmetry::Type::Triangle);
        m_symmetries.Deactivate(Symmetry::Type::Mirror);
        m_triangleSymmetricOct = 0;
      } else {
        m_outsideCone = (m_triangleOctRules[0] == m_triangleSymmetricOct) ||
                        (m_triangleOctRules[1] == m_triangleSymmetricOct) ||
                        (m_triangleOctRules[2] == m_triangleSymmetricOct) ||
                        (m_triangleOctRules[3] == m_triangleSymmetricOct);
      }
    }

    if (triSymmN > 1) {
      std::cerr << m_className << "::UpdatePeriodicity:\n"
                << "    Only one triangle symmetry allowed; reset.\n";
      m_symmetries.Deactivate(Symmetry::Type::Triangle);
      m_symmetries.Deactivate(Symmetry::Type::Mirror);
      m_triangleSymmetricOct = 0;
    }
  }
}

template <size_t N>
void ComponentTcadBase<N>::Cleanup() {
  // Vertices
  m_vertices.clear();
  // Elements
  m_elements.clear();
  // Regions
  m_regions.clear();
  // Potential and electric field.
  m_epot.clear();
  m_efield.clear();
  // Weighting potential and field.
  m_wpot.clear();
  m_wfield.clear();
  m_wshift.clear();
  m_dwf.clear();
  m_dwp.clear();
  m_dwtp.clear();
  m_dwtf.clear();

  // Other data.
  m_eVelocity.clear();
  m_hVelocity.clear();
  m_eMobility.clear();
  m_hMobility.clear();
  m_eAlpha.clear();
  m_hAlpha.clear();
  m_eLifetime.clear();
  m_hLifetime.clear();
  m_donors.clear();
  m_acceptors.clear();
  m_donorOcc.clear();
  m_acceptorOcc.clear();
  m_eEta.clear();
  m_hEta.clear();
}

template <size_t N>
void ComponentTcadBase<N>::MapCoordinates(std::array<double, N>& x,
                                          std::array<bool, N>& mirr) const {
  mirr.fill(false);
  for (size_t i = 0; i < N; ++i) {
    const Symmetry sym = m_symmetries.GetSymmetries(i);
    // In case of periodicity, reduce to the cell volume.
    const double cellsx = m_bbMax[i] - m_bbMin[i];
    if (sym.Has(Symmetry::Type::Periodic)) {
      x[i] = m_bbMin[i] + fmod(x[i] - m_bbMin[i], cellsx);
      if (x[i] < m_bbMin[i]) x[i] += cellsx;
    } else if (sym.Has(Symmetry::Type::Mirror)) {
      double xNew = m_bbMin[i] + fmod(x[i] - m_bbMin[i], cellsx);
      if (xNew < m_bbMin[i]) xNew += cellsx;
      const int nx = int(floor(0.5 + (xNew - x[i]) / cellsx));
      if (nx != 2 * (nx / 2)) {
        xNew = m_bbMin[i] + m_bbMax[i] - xNew;
        mirr[i] = true;
      }
      x[i] = xNew;
    }
  }

  // Triangle symmetry
  if ((N >= 2) && m_symmetries.Has(Symmetry::Type::Triangle)) {
    // Decide which pair of coordinates participates in the swap.
    size_t a = 0, b = 1;  // defaults (x,y)
    if (m_symmetries.Has(
            Symmetry::Type::TriangleXY)) {  // symmetry around X: swap X <-> Y
      a = 0;
      b = 1;
    } else if (m_symmetries.Has(
                   Symmetry::Type::TriangleXZ)) {  // symmetry around Y: swap X
                                                   // <-> Z
      if (N < 3) return;
      a = 0;
      b = 2;
    } else {  // symmetry around Z: swap Y <-> Z
      if (N < 3) return;
      a = 1;
      b = 2;
    }

    double prefixH = (m_triangleSymmetricOct % 2 == 0) ? -1.0 : 1.0;

    const double shiftFromDiagonal = 0.25e-4;
    if (std::abs(x[a] - x[b]) < Small) x[a] += prefixH * shiftFromDiagonal;

    const double pa = x[a];
    const double pb = x[b];

    bool triSwap = false;

    if (m_outsideCone) {
      triSwap = std::abs(x[a]) < std::abs(x[b]);
    } else {
      prefixH *= -1;
      triSwap = std::abs(x[a]) > std::abs(x[b]);
    }

    if (triSwap) {
      x[a] = prefixH * pb;
      x[b] = prefixH * pa;
    }
  }
}

template <size_t N>
size_t ComponentTcadBase<N>::FindRegion(const std::string& name) const {
  const auto nRegions = m_regions.size();
  for (size_t j = 0; j < nRegions; ++j) {
    if (name == m_regions[j].name) return j;
  }
  return m_regions.size();
}

template <size_t N>
void ComponentTcadBase<N>::UpdateAttachment() {
  if (!m_useLifetimeMap && !m_useTrapOccMap) {
    m_eEta.clear();
    m_hEta.clear();
  }
  if (m_vertices.empty()) return;
  const size_t nVertices = m_vertices.size();
  m_eEta.assign(nVertices, 0.);
  m_hEta.assign(nVertices, 0.);
  if (m_useLifetimeMap) ComputeEtaFromLifetime();
  if (m_useTrapOccMap) ComputeEtaFromTraps();
}

template <size_t N>
void ComponentTcadBase<N>::ComputeEtaFromLifetime() {
  if (m_vertices.empty()) return;
  const size_t nVertices = m_vertices.size();
  if (!m_eLifetime.empty()) {
    for (size_t i = 0; i < nVertices; ++i) {
      if (m_eLifetime[i] > 0.) {
        m_eEta[i] = -1. / m_eLifetime[i];
      }
    }
  }
  if (!m_hLifetime.empty()) {
    for (size_t i = 0; i < nVertices; ++i) {
      if (m_hLifetime[i] > 0.) {
        m_hEta[i] = -1. / m_hLifetime[i];
      }
    }
  }
}

template <size_t N>
void ComponentTcadBase<N>::ComputeEtaFromTraps() {
  if (m_vertices.empty()) return;
  const size_t nVertices = m_vertices.size();

  const size_t nAcceptors = m_acceptors.size();
  for (size_t i = 0; i < nAcceptors; ++i) {
    const auto& defect = m_acceptors[i];
    if (defect.conc < 0.) continue;
    for (size_t j = 0; j < nVertices; ++j) {
      // Get the occupation probability.
      const double f = m_acceptorOcc[j][i];
      if (defect.xsece > 0.) {
        m_eEta[j] += defect.conc * defect.xsece * (1. - f);
      }
      if (defect.xsech > 0.) {
        m_hEta[j] += defect.conc * defect.xsech * f;
      }
    }
  }
  const size_t nDonors = m_donors.size();
  for (size_t i = 0; i < nDonors; ++i) {
    const auto& defect = m_donors[i];
    if (defect.conc < 0.) continue;
    for (size_t j = 0; j < nVertices; ++j) {
      const double f = m_donorOcc[j][i];
      if (defect.xsece > 0.) {
        m_eEta[j] += defect.conc * defect.xsece * f;
      }
      if (defect.xsech > 0.) {
        m_hEta[j] += defect.conc * defect.xsech * (1. - f);
      }
    }
  }
}

template class ComponentTcadBase<2>;
template class ComponentTcadBase<3>;
}  // namespace Garfield
