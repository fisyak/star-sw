#include "Garfield/ComponentElmer.hh"

#include <fstream>
#include <iostream>
#include <string>

namespace {

void PrintErrorReadingFile(const std::string& hdr, const std::string& file,
                           const int line) {
  std::cerr << hdr << "\n    Error reading file " << file << " (line " << line
            << ").\n";
}

}  // namespace

namespace Garfield {

ComponentElmer::ComponentElmer() : ComponentFieldMap("Elmer") {}

ComponentElmer::ComponentElmer(const std::string& header,
                               const std::string& elist,
                               const std::string& nlist,
                               const std::string& mplist,
                               const std::string& volt, const std::string& unit)
    : ComponentFieldMap("Elmer") {
  Initialise(header, elist, nlist, mplist, volt, unit);
}

bool ComponentElmer::Initialise(const std::string& header,
                                const std::string& elist,
                                const std::string& nlist,
                                const std::string& mplist,
                                const std::string& volt,
                                const std::string& unit) {
  const std::string hdr = m_className + "::Initialise:";
  ComponentFieldMap::Reset();

  // Keep track of the success.
  bool ok = true;

  // Buffer for reading
  constexpr int size = 100;
  char line[size];

  // Open the header.
  std::ifstream fheader(header);
  if (!fheader) {
    PrintCouldNotOpen("Initialise", header);
    return false;
  }

  // Read the header to get the number of nodes and elements.
  fheader.getline(line, size, '\n');
  char* token = strtok(line, " ");
  bool readerror = false;
  const int nNodes = ReadInteger(token, 0, readerror);
  token = strtok(nullptr, " ");
  const int nElements = ReadInteger(token, 0, readerror);
  std::cout << hdr << "\n    Read " << nNodes << " nodes and " << nElements
            << " elements from file " << header << ".\n";
  if (readerror) {
    PrintErrorReadingFile(hdr, header, 0);
    fheader.close();
    return false;
  }

  // Close the header file.
  fheader.close();

  // Open the nodes list.
  std::ifstream fnodes(nlist);
  if (!fnodes) {
    PrintCouldNotOpen("Initialise", nlist);
    return false;
  }

  // Check the value of the unit.
  double funit = ScalingFactor(unit);
  if (funit <= 0.) {
    std::cerr << hdr << " Unknown length unit " << unit << ". Will use cm.\n";
    funit = 1.0;
  }
  if (m_debug) std::cout << hdr << " Unit scaling factor = " << funit << ".\n";

  // Read the nodes from the file.
  for (int il = 0; il < nNodes; il++) {
    // Get a line from the nodes file.
    fnodes.getline(line, size, '\n');

    // Ignore the first two characters.
    token = strtok(line, " ");
    token = strtok(nullptr, " ");

    // Get the node coordinates.
    token = strtok(nullptr, " ");
    double xnode = ReadDouble(token, -1, readerror);
    token = strtok(nullptr, " ");
    double ynode = ReadDouble(token, -1, readerror);
    token = strtok(nullptr, " ");
    double znode = ReadDouble(token, -1, readerror);
    if (readerror) {
      PrintErrorReadingFile(hdr, nlist, il);
      fnodes.close();
      return false;
    }

    // Set up and create a new node.
    Node node;
    node.x = xnode * funit;
    node.y = ynode * funit;
    node.z = znode * funit;
    m_nodes.push_back(std::move(node));
  }

  // Close the nodes file.
  fnodes.close();

  // Read the potentials.
  if (!LoadPotentials(volt, m_pot)) return false;

  // Open the materials file.
  std::ifstream fmplist(mplist);
  if (!fmplist) {
    PrintCouldNotOpen("Initialise", mplist);
    return false;
  }

  // Read the dielectric constants from the materials file.
  fmplist.getline(line, size, '\n');
  token = strtok(line, " ");
  if (readerror) {
    std::cerr << hdr << "\n    Error reading number of materials from "
              << mplist << ".\n";
    fmplist.close();
    return false;
  }
  const std::size_t nMaterials = ReadInteger(token, 0, readerror);
  m_materials.resize(nMaterials);
  for (auto& material : m_materials) {
    material.ohm = -1;
    material.eps = -1;
    material.medium = nullptr;
  }
  for (int il = 2; il < ((int)nMaterials + 2); il++) {
    fmplist.getline(line, size, '\n');
    token = strtok(line, " ");
    ReadInteger(token, -1, readerror);
    token = strtok(nullptr, " ");
    double dc = ReadDouble(token, -1.0, readerror);
    if (readerror) {
      PrintErrorReadingFile(hdr, mplist, il);
      fmplist.close();
      return false;
    }
    m_materials[il - 2].eps = dc;
    std::cout << "    Set material " << il - 2 << " of " << nMaterials
              << " to eps " << dc << ".\n";
  }

  // Close the materials file.
  fmplist.close();

  // Find lowest epsilon, check for eps = 0, set default drift medium.
  if (!SetDefaultDriftMedium()) return false;

  // Open the elements file.
  std::ifstream felems(elist);
  if (!felems) {
    PrintCouldNotOpen("Initialise", elist);
    return false;
  }

  // Read the elements and their material indices.
  for (int il = 0; il < nElements; il++) {
    // Get a line
    felems.getline(line, size, '\n');

    // Split into tokens.
    token = strtok(line, " ");
    // Read the 2nd-order element
    // Note: Ordering of Elmer elements can be described in the
    // ElmerSolver manual (appendix D. at the time of this comment)
    // If the order read below is compared to the shape functions used
    // eg. in ElectricField, the order is wrong, but note at the
    // end of this function the order of elements 5,6,7 will change to
    // 7,5,6 when actually recorded in element.emap to correct for this
    token = strtok(nullptr, " ");
    int imat = ReadInteger(token, -1, readerror) - 1;
    token = strtok(nullptr, " ");
    std::vector<int> inode;
    for (size_t k = 0; k < 10; ++k) {
      token = strtok(nullptr, " ");
      const int in = ReadInteger(token, -1, readerror);
      if (!readerror) inode.push_back(in);
    }

    if (inode.size() != 10) {
      PrintErrorReadingFile(hdr, elist, il);
      std::cerr << "    Read " << inode.size() << " node indices for element"
                << il << " (expected 10).\n";
      felems.close();
      return false;
    }

    if (m_debug && il < 10) {
      std::cout << "    Read nodes " << inode[0] << ", " << inode[1] << ", "
                << inode[2] << ", " << inode[3] << ", ... from element "
                << il + 1 << " of " << nElements << " with material " << imat
                << ".\n";
    }

    // Check the material number and ensure that epsilon is non-negative.
    if (imat < 0 || imat > (int)nMaterials) {
      std::cerr << hdr << "\n    Out-of-range material number on file " << elist
                << " (line " << il << ").\n"
                << "    Element: " << il << ", material: " << imat << ".\n";
      ok = false;
      break;
    }
    if (m_materials[imat].eps < 0) {
      std::cerr << hdr << "\n    Element " << il << " in " << elist << "\n"
                << "    uses material " << imat << " which does not have\n"
                << "    a positive permittivity in " << mplist << ".\n";
      ok = false;
      break;
    }

    // Check the node numbers.
    bool degenerate = false;
    for (size_t k = 0; k < 10; ++k) {
      if (inode[k] < 1) {
        std::cerr << hdr << "\n    Found a node number < 1 on file " << elist
                  << " (line " << il << ").\n    Element: " << il
                  << ", material: " << imat << ".\n";
        ok = false;
      }
      for (size_t kk = k + 1; kk < 10; ++kk) {
        if (inode[k] == inode[kk]) degenerate = true;
      }
    }
    // These elements must not be degenerate.
    if (degenerate) {
      std::cerr << hdr << "\n    Element " << il << " of file " << elist
                << " is degenerate,\n"
                << "    no such elements are allowed in this type of map.\n";
      ok = false;
    }
    if (!ok) break;
    Element element;
    // Store the material reference.
    element.matmap = imat;
    // Store the node references.
    element.emap[0] = inode[0] - 1;
    element.emap[1] = inode[1] - 1;
    element.emap[2] = inode[2] - 1;
    element.emap[3] = inode[3] - 1;
    element.emap[4] = inode[4] - 1;
    element.emap[7] = inode[5] - 1;
    element.emap[5] = inode[6] - 1;
    element.emap[6] = inode[7] - 1;
    element.emap[8] = inode[8] - 1;
    element.emap[9] = inode[9] - 1;
    m_elements.push_back(std::move(element));
  }
  m_degenerate.assign(m_elements.size(), false);

  // Close the elements file.
  felems.close();
  if (!ok) return false;

  // Set the ready flag.
  m_ready = true;
  std::cout << hdr << " Finished.\n";

  Prepare();
  return true;
}

bool ComponentElmer::SetWeightingField(const std::string& wvolt,
                                       const std::string& label) {
  const std::string hdr = m_className + "::SetWeightingField:";
  if (!m_ready) {
    PrintNotReady("SetWeightingField");
    std::cerr << "    Weighting field cannot be added.\n";
    return false;
  }

  std::cout << m_className << "::SetWeightingField:\n"
            << "    Loading field map for electrode " << label << ".\n";
  if (m_wpot.count(label) > 0) {
    std::cout << "    Replacing existing weighting field.\n";
    m_wpot[label].clear();
  }
  std::vector<double> pot(m_nodes.size(), 0.);
  if (!LoadPotentials(wvolt, pot)) return false;
  m_wpot[label] = std::move(pot);
  return true;
}

bool ComponentElmer::LoadPotentials(const std::string& volt,
                                    std::vector<double>& pot) {
  // Open the voltage list.
  std::ifstream fvolt(volt);
  if (!fvolt) {
    PrintCouldNotOpen("LoadPotentials", volt);
    return false;
  }
  pot.assign(m_nodes.size(), 0.);

  // Buffer for reading.
  constexpr int size = 100;
  char line[size];

  bool readstop = false;
  int il = 1;
  // Read past the header.
  while (!readstop && fvolt.getline(line, size, '\n')) {
    char* token = strtok(line, " ");
    if (token && strcmp(token, "Perm:") == 0) readstop = true;
    il++;
  }

  // Should have stopped: if not, print error message.
  if (!readstop) {
    std::cerr << m_className << "::LoadPotentials:\n"
              << "    Error reading past header of potentials file " << volt
              << ".\n";
    fvolt.close();
    return false;
  }

  // Read past the permutation map (number of lines = nNodes).
  const auto nNodes = m_nodes.size();
  for (size_t j = 0; j < nNodes; ++j) {
    fvolt.getline(line, size, '\n');
    il++;
  }

  // Read the potentials.
  for (size_t j = 0; j < nNodes; ++j) {
    fvolt.getline(line, size, '\n');
    char* token = strtok(line, " ");
    bool readerror = false;
    double v = ReadDouble(token, -1, readerror);
    if (readerror) {
      PrintErrorReadingFile(m_className + "::LoadPotentials", volt, il);
      fvolt.close();
      return false;
    }
    // Place the potential at its appropriate index.
    pot[j] = v;
  }

  // Close the file.
  fvolt.close();
  std::cout << "    Read potentials from file " << volt << ".\n";
  return true;
}

}  // namespace Garfield
