#include "Garfield/ComponentComsol.hh"

#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>

#include "Garfield/KDTree.hh"

namespace {

bool ends_with(std::string s, std::string t) {
  if (!s.empty() && s.back() == '\r') s.pop_back();
  return s.size() >= t.size() && s.substr(s.size() - t.size(), t.size()) == t;
}

bool isComment(const std::string &line) {
  if (line.empty()) return false;
  if (line[0] == '%') return true;
  return false;
}

void PrintProgress(const double f) {
  if (f < 0.) return;
  constexpr std::size_t width = 70;
  const std::size_t n = static_cast<std::size_t>(std::floor(width * f));
  std::string bar = "[";
  if (n < 1) {
    bar += std::string(width, ' ');
  } else if (n >= width) {
    bar += std::string(width, '=');
  } else {
    bar += std::string(n, '=') + ">" + std::string(width - n - 1, ' ');
  }
  bar += "]";
  std::cout << bar << "\r" << std::flush;
}

}  // namespace

namespace Garfield {

ComponentComsol::ComponentComsol() : ComponentFieldMap("Comsol") {}

ComponentComsol::ComponentComsol(const std::string &mesh,
                                 const std::string &mplist,
                                 const std::string &field,
                                 const std::string &unit)
    : ComponentFieldMap("Comsol") {
  Initialise(mesh, mplist, field, unit);
}

bool ComponentComsol::Initialise(const std::string &mesh,
                                 const std::string &mplist,
                                 const std::string &field,
                                 const std::string &unit) {
  ComponentFieldMap::Reset();

  std::vector<int> nodeIndices;

  // Get the conversion factor to be applied to the coordinates.
  m_unit = ScalingFactor(unit);
  if (m_unit <= 0.) {
    std::cerr << m_className << "::Initialise:\n    Unknown length unit "
              << unit << ". Will use default (m).\n";
    m_unit = 100.;
  }
  // Open the materials file.
  m_materials.clear();
  std::ifstream fmplist(mplist);
  if (!fmplist) {
    PrintCouldNotOpen("Initialise", mplist);
    return false;
  }
  std::size_t nMaterials;
  fmplist >> nMaterials;
  for (std::size_t i = 0; i < nMaterials; ++i) {
    Material material;
    material.driftmedium = false;
    material.medium = nullptr;
    material.ohm = -1;
    fmplist >> material.eps;
    m_materials.push_back(std::move(material));
  }
  if (m_materials.empty()) {
    // Add default material
    Material material;
    material.driftmedium = false;
    material.medium = nullptr;
    material.eps = material.ohm = -1;
    m_materials.push_back(std::move(material));
    nMaterials = 1;
  }
  std::map<int, int> domain2material;
  int d2msize;
  fmplist >> d2msize;
  for (int i = 0; i < d2msize; ++i) {
    int domain, mat;
    fmplist >> domain >> mat;
    domain2material[domain] = mat;
  }
  fmplist.close();

  // Find lowest epsilon, check for eps = 0, set default drift medium.
  if (!SetDefaultDriftMedium()) return false;

  m_nodes.clear();
  std::ifstream fmesh(mesh);
  if (!fmesh) {
    PrintCouldNotOpen("Initialise", mesh);
    return false;
  }

  std::string line;
  do {
    if (!std::getline(fmesh, line)) {
      std::cerr << m_className << "::Initialise:\n"
                << "    Could not read number of nodes from " << mesh << ".\n";
      fmesh.close();
      return false;
    }
  } while (!ends_with(line, "# number of mesh points") &&
           !ends_with(line, "# number of mesh vertices"));

  const int nNodes = std::stoi(line);
  int nInRange = 0;
  std::cout << m_className << "::Initialise: " << nNodes << " nodes.\n";
  do {
    if (!std::getline(fmesh, line)) {
      std::cerr << m_className << "::Initialise:\n"
                << "    Error parsing " << mesh << ".\n";
      fmesh.close();
      return false;
    }
  } while (line.find("# Mesh point coordinates") == std::string::npos &&
           line.find("# Mesh vertex coordinates") == std::string::npos);

  std::vector<Node> allNodes;
  for (int i = 0; i < nNodes; ++i) {
    Node node;
    fmesh >> node.x >> node.y >> node.z;
    node.x *= m_unit;
    node.y *= m_unit;
    node.z *= m_unit;
    if (m_range.set) {
      allNodes.push_back(std::move(node));
      if (CheckInRange(node.x, node.y, node.z)) nInRange++;
    } else {
      m_nodes.push_back(std::move(node));
    }
  }

  m_elements.clear();
  do {
    if (!std::getline(fmesh, line)) {
      std::cerr << m_className << "::Initialise:\n"
                << "    Error parsing " << mesh << ".\n";
      fmesh.close();
      return false;
    }
  } while (line.find("4 tet2 # type name") == std::string::npos);
  do {
    if (!std::getline(fmesh, line)) {
      std::cerr << m_className << "::Initialise:\n"
                << "    Error parsing " << mesh << ".\n";
      fmesh.close();
      return false;
    }
  } while (!ends_with(line, "# number of elements"));

  const int nElements = std::stoi(line);
  std::cout << m_className << "::Initialise: " << nElements << " elements.\n";
  std::getline(fmesh, line);
  std::vector<Element> allElements;
  // Elements 6 & 7 are swapped due to differences in COMSOL and ANSYS
  // representation
  int perm[10] = {0, 1, 2, 3, 4, 5, 7, 6, 8, 9};
  for (int i = 0; i < nElements; ++i) {
    Element element;
    for (int j = 0; j < 10; ++j) {
      fmesh >> element.emap[perm[j]];
    }
    allElements.push_back(std::move(element));
  }

  do {
    if (!std::getline(fmesh, line)) {
      std::cerr << m_className << "::Initialise:\n"
                << "    Error parsing " << mesh << ".\n";
      fmesh.close();
      return false;
    }
  } while (line.find("# Geometric entity indices") == std::string::npos);
  for (auto &element : allElements) {
    int domain;
    fmesh >> domain;
    if (domain2material.count(domain) > 0) {
      element.matmap = domain2material[domain];
    } else {
      element.matmap = nMaterials - 1;
    }
  }
  fmesh.close();

  for (auto &element : allElements) {
    if (ElementInRange(element, allNodes)) {
      for (int j = 0; j < 10; j++) {
        nodeIndices.push_back(element.emap[j]);
      }
      m_elements.push_back(std::move(element));
    }
  }
  m_degenerate.assign(m_elements.size(), false);

  if (m_range.set) {
    std::vector<int> nodeMap(nNodes, -1);
    // Rearrange node indices and delete duplicates.
    std::sort(nodeIndices.begin(), nodeIndices.end());
    nodeIndices.erase(std::unique(nodeIndices.begin(), nodeIndices.end()),
                      nodeIndices.end());
    // Go over node indices and add the corresponding nodes to m_nodes.
    for (int i : nodeIndices) {
      m_nodes.push_back(allNodes[i]);
      // Update map to get correct node index.
      nodeMap[i] = m_nodes.size() - 1;
    }
    // Go over the elements and update the node indices
    // using the map you just created.
    for (Element &element : m_elements) {
      for (int j = 0; j < 10; ++j) {
        element.emap[j] = nodeMap[element.emap[j]];
        if (element.emap[j] == -1) return false;
      }
    }
  }

  std::ifstream ffield(field);
  if (!ffield) {
    PrintCouldNotOpen("Initialise", field);
    return false;
  }
  m_pot.resize(m_nodes.size());
  const std::string hdr1 =
      "% x                       y                        z                    "
      "    V (V)";

  const std::string hdr2 =
      "% x             y              z              V (V)";
  do {
    if (!std::getline(ffield, line)) {
      std::cerr << m_className << "::Initialise:\n"
                << "    Error parsing " << field << ".\n";
      ffield.close();
      return false;
    }
  } while (line.find(hdr1) == std::string::npos &&
           line.find(hdr2) == std::string::npos);
  std::istringstream sline(line);
  std::string token;
  sline >> token;  // %
  sline >> token;  // x
  sline >> token;  // y
  sline >> token;  // z
  sline >> token;  // V
  sline >> token;  // (V)
  std::vector<std::string> wfields;
  while (sline >> token) {
    std::cout << m_className << "::Initialise:\n"
              << "    Reading data for weighting field " << token << ".\n";
    wfields.push_back(token);
    m_wpot.emplace(token, std::vector<double>(m_nodes.size(), 0.));
    sline >> token;  // (V)
  }
  const size_t nWeightingFields = wfields.size();

  const std::size_t nPrint =
      std::pow(10, static_cast<std::size_t>(
                       std::max(std::floor(std::log10(nNodes)) - 1, 1.)));
  std::cout << m_className << "::Initialise: Reading potentials.\n";
  PrintProgress(0.);
  // Build a k-d tree from the node coordinates.
  std::vector<std::vector<double> > points;
  for (const auto &node : m_nodes) {
    std::vector<double> point = {node.x, node.y, node.z};
    points.push_back(std::move(point));
  }
  KDTree kdtree(points);

  const int usedSize = m_range.set ? m_nodes.size() : nNodes;
  std::vector<bool> used(usedSize, false);
  for (int i = 0; i < nNodes; ++i) {
    double x, y, z, v;
    ffield >> x >> y >> z >> v;
    x *= m_unit;
    y *= m_unit;
    z *= m_unit;
    std::vector<double> w;
    for (size_t j = 0; j < nWeightingFields; ++j) {
      double p;
      ffield >> p;
      w.push_back(p);
    }
    if (!CheckInRange(x, y, z)) continue;
    std::vector<KDTreeResult> res;
    kdtree.n_nearest({x, y, z}, 1, res);
    if (res.empty()) {
      std::cerr << m_className << "::Initialise:\n"
                << "    Could not find a matching mesh node for point (" << x
                << ", " << y << ", " << z << ")\n.";
      ffield.close();
      return false;
    }
    if (res[0].dis > MaxNodeDistance) continue;
    const size_t k = res[0].idx;
    used[k] = true;
    m_pot[k] = v;
    for (size_t j = 0; j < nWeightingFields; ++j) {
      m_wpot[wfields[j]][k] = w[j];
    }
    if ((i + 1) % nPrint == 0) PrintProgress(double(i + 1) / nNodes);
  }
  PrintProgress(1.);
  std::cout << std::string(72, ' ') << "\r";
  ffield.close();
  auto nMissing = std::count(used.begin(), used.end(), false);
  if (m_range.set) nMissing = nMissing - m_nodes.size() + nInRange;
  if (nMissing > 0) {
    std::cerr << m_className << "::Initialise:\n"
              << "    Missing potentials for " << nMissing << " nodes.\n";
    // return false;
  }

  m_ready = true;
  Prepare();
  std::cout << std::endl << m_className << "::Initialise: Done.\n";
  return true;
}

bool ComponentComsol::SetWeightingPotential(const std::string &field,
                                            const std::string &label) {
  if (!m_ready) {
    std::cerr << m_className << "::SetWeightingPotential:\n"
              << "    No valid field map is present.\n"
              << "    Weighting fields cannot be added.\n";
    return false;
  }

  std::cout << m_className << "::SetWeightingPotential:\n"
            << "    Reading field map for electrode " << label << ".\n";

  // Check if a weighting field with the same label already exists.
  if (m_wpot.count(label) > 0) {
    std::cout << "    Replacing existing weighting field.\n";
    m_wpot[label].clear();
  }

  std::vector<double> pot(m_nodes.size(), 0.);
  if (!LoadPotentials(field, pot)) return false;
  m_wpot[label] = pot;
  return true;
}

bool ComponentComsol::LoadPotentials(const std::string &field,
                                     std::vector<double> &pot) {
  // Open the file.
  std::ifstream ffield(field);
  if (!ffield) {
    PrintCouldNotOpen("LoadPotentials", field);
    return false;
  }
  // Build a k-d tree from the node coordinates.
  std::vector<std::vector<double> > points;
  for (const auto &node : m_nodes) {
    std::vector<double> point = {node.x, node.y, node.z};
    points.push_back(std::move(point));
  }
  KDTree kdtree(points);

  std::string line;
  int nLines = 1;
  const int nNodes = m_nodes.size();
  const std::size_t nPrint =
      std::pow(10, static_cast<std::size_t>(
                       std::max(std::floor(std::log10(nNodes)) - 1, 1.)));
  PrintProgress(0.);

  while (std::getline(ffield, line)) {
    // Skip empty lines.
    if (line.empty()) continue;
    // Skip comments.
    if (isComment(line)) continue;

    std::vector<double> pvect;

    std::istringstream data(line);
    double x = 0., y = 0., z = 0.;
    data >> x >> y >> z;
    x *= m_unit;
    y *= m_unit;
    z *= m_unit;
    if (!CheckInRange(x, y, z)) continue;
    std::vector<KDTreeResult> res;
    kdtree.n_nearest({x, y, z}, 1, res);
    if (res.empty()) {
      std::cerr << m_className << "::LoadPotentials:\n"
                << "    Could not find a matching mesh node for point (" << x
                << ", " << y << ", " << z << ")\n.";
      ffield.close();
      return false;
    }
    if (res[0].dis > MaxNodeDistance) continue;

    double p = 0.;
    data >> p;
    const size_t k = res[0].idx;
    pot[k] = p;

    if ((nLines + 1) % nPrint == 0) {
      PrintProgress(double(nLines + 1) / nNodes);
    }
    nLines++;
  }

  PrintProgress(1.);
  ffield.close();
  return true;
}

bool ComponentComsol::SetDynamicWeightingPotential(const std::string &field,
                                                   const std::string &label) {
  if (!m_ready) {
    std::cerr << m_className << "::SetDynamicWeightingPotential:\n"
              << "    No valid field map is present.\n"
              << "    Weighting fields cannot be added.\n";
    return false;
  }

  if (!m_timeset && !GetTimeInterval(field)) return false;

  if (!m_timeset) {
    std::cerr << m_className << "::SetDynamicWeightingPotential:\n"
              << "    No valid times slices of potential set.\n"
              << "    Please add the time slices.\n";
    return false;
  }

  const int T = m_wdtimes.size();

  // Open the voltage list.
  std::ifstream ffield(field);
  if (!ffield) {
    PrintCouldNotOpen("SetDynamicWeightingPotential", field);
    return false;
  }

  // Check if a weighting field with the same label already exists.
  if (m_wpot.count(label) > 0) {
    std::cout << m_className << "::SetDynamicWeightingPotential:\n"
              << "    Replacing existing weighting field " << label << ".\n";
    m_wpot[label].clear();
  }
  if (m_dwpot.count(label) > 0) {
    m_dwpot[label].clear();
  }

  std::vector<double> pot(m_nodes.size(), 0.);
  std::vector<std::vector<double> > dpot(m_nodes.size());

  // Build a k-d tree from the node coordinates.
  std::vector<std::vector<double> > points;
  for (const auto &node : m_nodes) {
    std::vector<double> point = {node.x, node.y, node.z};
    points.push_back(std::move(point));
  }
  KDTree kdtree(points);

  std::string line;
  int nLines = 1;
  const int nNodes = m_nodes.size();
  const std::size_t nPrint =
      std::pow(10, static_cast<std::size_t>(
                       std::max(std::floor(std::log10(nNodes)) - 1, 1.)));
  std::cout << m_className << "::SetDynamicWeightingPotential:\n"
            << "    Reading weighting potentials for " << label << ".\n";
  PrintProgress(0.);

  while (std::getline(ffield, line)) {
    // Skip empty lines.
    if (line.empty()) continue;
    // Skip comments.
    if (isComment(line)) continue;

    std::istringstream data(line);
    double x = 0., y = 0., z = 0.;
    data >> x >> y >> z;
    x *= m_unit;
    y *= m_unit;
    z *= m_unit;
    if (!CheckInRange(x, y, z)) continue;
    std::vector<KDTreeResult> res;
    kdtree.n_nearest({x, y, z}, 1, res);
    if (res.empty()) {
      std::cerr << m_className << "::SetDynamicWeightingPotential:\n"
                << "    Could not find a matching mesh node for point (" << x
                << ", " << y << ", " << z << ")\n.";
      ffield.close();
      return false;
    }
    if (res[0].dis > MaxNodeDistance) continue;

    double p = 0.;
    double p0 = 0.;
    std::vector<double> pvect;
    for (int i = 0; i < T; i++) {
      data >> p;
      if (i == 0) p0 = p;
      pvect.push_back(p - p0);
    }
    const size_t k = res[0].idx;
    dpot[k] = pvect;
    pot[k] = p0;

    if ((nLines + 1) % nPrint == 0) {
      PrintProgress(double(nLines + 1) / nNodes);
    }
    nLines++;
  }

  PrintProgress(1.);
  std::cout << std::endl
            << m_className << "::SetDynamicWeightingPotential: Done.\n";
  ffield.close();
  m_wpot[label] = std::move(pot);
  m_dwpot[label] = std::move(dpot);
  return true;
}

void ComponentComsol::SetTimeInterval(const double mint, const double maxt,
                                      const double stept) {
  std::cout << std::endl
            << m_className
            << "::SetTimeInterval: Overwriting time interval of weighting "
               "potential.\n";

  if (m_wdtimes.empty()) {
    double t = mint;
    while (t <= maxt) {
      m_wdtimes.push_back(t);
      t += stept;
    }
  }
  m_timeset = true;

  std::cout << std::endl
            << m_className
            << "::SetTimeInterval: Time of weighting potential set for t in ["
            << mint << "," << maxt << "].\n";
}

bool ComponentComsol::GetTimeInterval(const std::string &field) {
  if (!m_wdtimes.empty())
    std::cout << std::endl
              << m_className
              << "::GetTimeInterval: Overwriting time interval of weighting "
                 "potential.\n";

  std::ifstream ffield(field);
  if (!ffield) {
    PrintCouldNotOpen("GetTimeInterval", field);
    return false;
  }

  std::string strtime = "t=";

  std::string line;
  // Find first occurrence of "geeks"
  size_t found = 0;
  bool searching = true;
  while (std::getline(ffield, line)) {
    // Skip empty lines.
    if (line.empty()) continue;
    // Skip lines that are not comments.
    if (line[0] == '%' && line[2] != 'x') continue;

    while (searching) {
      found = line.find(strtime, found + 1);
      searching = false;
      if (found != std::string::npos) {
        searching = true;

        int i = 2;

        std::string holder = "";

        while (true) {
          holder += line[found + i];
          i++;

          if (found + i == line.size()) break;
          if (line[found + i] == ' ') break;
        }
        m_wdtimes.push_back(stod(holder));
      }
    }
    break;
  }

  m_timeset = true;

  std::cout << std::endl
            << m_className
            << "::GetTimeInterval: Time of weighting potential set for t in ["
            << m_wdtimes.front() << "," << m_wdtimes.back() << "].\n";

  ffield.close();

  return true;
}

}  // namespace Garfield
