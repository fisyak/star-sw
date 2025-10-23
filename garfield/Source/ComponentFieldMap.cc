#include "Garfield/ComponentFieldMap.hh"

#include <TCanvas.h>
#include <TH1F.h>
#include <TMath.h>

#include <cstddef>
#include <iostream>
#include <numeric>
#include <string>
#include <vector>

#include "Garfield/Medium.hh"

namespace Garfield {

ComponentFieldMap::ComponentFieldMap(const std::string& name)
    : Component(name) {}

ComponentFieldMap::~ComponentFieldMap() = default;

void ComponentFieldMap::ElectricField(const double x, const double y,
                                      const double z, double& ex, double& ey,
                                      double& ez, double& volt, Medium*& m,
                                      int& status) {
  ElectricField(x, y, z, ex, ey, ez, m, status);
  volt = Potential(x, y, z, m_pot);
}

void ComponentFieldMap::ElectricField(const double xin, const double yin,
                                      const double zin, double& ex, double& ey,
                                      double& ez, Medium*& m, int& status) {
  // Initial values
  ex = ey = ez = 0.;
  m = nullptr;
  int iel = -1;
  status = Field(xin, yin, zin, ex, ey, ez, iel, m_pot);
  if (status < 0 || iel < 0) {
    if (status == -10) {
      PrintNotReady("ElectricField");
    }
    return;
  }
  const auto& element = m_elements[iel];
  // Drift medium?
  if (element.matmap >= m_materials.size()) {
    if (m_debug) {
      std::cout << m_className
                << "::ElectricField: " << "Out-of-range material number.\n";
    }
    status = -5;
    return;
  }
  const auto& mat = m_materials[element.matmap];
  if (m_debug) {
    std::cout << "    Material " << element.matmap << ", drift flag "
              << mat.driftmedium << ".\n";
  }
  m = mat.medium;
  status = -5;
  if (mat.driftmedium) {
    if (m && m->IsDriftable()) status = 0;
  }
}

int ComponentFieldMap::Field(const double xin, const double yin,
                             const double zin, double& fx, double& fy,
                             double& fz, int& imap,
                             const std::vector<double>& pot) const {
  // Do not proceed if not properly initialised.
  if (!m_ready) return -10;
  // Copy the coordinates.
  double x = xin, y = yin;
  double z = m_is3d ? zin : 0.;
  // Map the coordinates onto field map coordinates
  bool xmirr, ymirr, zmirr;
  double rcoordinate, rotation;
  MapCoordinates(x, y, z, xmirr, ymirr, zmirr, rcoordinate, rotation);

  if (!m_is3d) {
    if (zin < m_minBoundingBox[2] || zin > m_maxBoundingBox[2]) {
      return -5;
    }
  }

  // Find the element that contains this point.
  double t1 = 0., t2 = 0., t3 = 0., t4 = 0.;
  double jac[4][4];
  double det = 0.;
  imap = -1;
  if (m_elementType == ElementType::Serendipity) {
    imap = FindElement5(x, y, t1, t2, t3, t4, jac, det);
  } else if (m_elementType == ElementType::CurvedTetrahedron) {
    imap = FindElement13(x, y, z, t1, t2, t3, t4, jac, det);
  }
  // Stop if the point is not in the mesh.
  if (imap < 0) {
    if (m_debug) {
      std::cerr << m_className << "::Field: (" << x << ", " << y << ", " << z
                << ") is not in the mesh.\n";
    }
    return -6;
  }

  const Element& element = m_elements[imap];
  if (m_elementType == ElementType::Serendipity) {
    if (m_degenerate[imap]) {
      std::array<double, 6> v;
      for (size_t i = 0; i < 6; ++i) v[i] = pot[element.emap[i]];
      Field3(v, {t1, t2, t3}, jac, det, fx, fy);
    } else {
      std::array<double, 8> v;
      for (size_t i = 0; i < 8; ++i) v[i] = pot[element.emap[i]];
      Field5(v, {t1, t2}, jac, det, fx, fy);
    }
  } else if (m_elementType == ElementType::CurvedTetrahedron) {
    std::array<double, 10> v;
    for (size_t i = 0; i < 10; ++i) v[i] = pot[element.emap[i]];
    Field13(v, {t1, t2, t3, t4}, jac, 4 * det, fx, fy, fz);
  }
  if (m_debug) {
    PrintElement("Field", x, y, z, t1, t2, t3, t4, imap, pot);
  }
  // Transform field to global coordinates.
  UnmapFields(fx, fy, fz, x, y, z, xmirr, ymirr, zmirr, rcoordinate, rotation);
  return 0;
}

double ComponentFieldMap::Potential(const double xin, const double yin,
                                    const double zin,
                                    const std::vector<double>& pot) const {
  // Do not proceed if not properly initialised.
  if (!m_ready) return 0.;

  // Copy the coordinates.
  double x = xin, y = yin;
  double z = m_is3d ? zin : 0.;

  // Map the coordinates onto field map coordinates.
  bool xmirr, ymirr, zmirr;
  double rcoordinate, rotation;
  MapCoordinates(x, y, z, xmirr, ymirr, zmirr, rcoordinate, rotation);

  if (!m_is3d) {
    if (zin < m_minBoundingBox[2] || zin > m_maxBoundingBox[2]) {
      return 0.;
    }
  }

  // Find the element that contains this point.
  double t1 = 0., t2 = 0., t3 = 0., t4 = 0.;
  double jac[4][4];
  double det = 0.;
  int imap = -1;
  if (m_elementType == ElementType::Serendipity) {
    imap = FindElement5(x, y, t1, t2, t3, t4, jac, det);
  } else if (m_elementType == ElementType::CurvedTetrahedron) {
    imap = FindElement13(x, y, z, t1, t2, t3, t4, jac, det);
  }
  if (imap < 0) return 0.;

  double volt = 0.;
  const Element& element = m_elements[imap];
  if (m_elementType == ElementType::Serendipity) {
    if (m_degenerate[imap]) {
      std::array<double, 6> v;
      for (size_t i = 0; i < 6; ++i) v[i] = pot[element.emap[i]];
      volt = Potential3(v, {t1, t2, t3});
    } else {
      std::array<double, 8> v;
      for (size_t i = 0; i < 8; ++i) v[i] = pot[element.emap[i]];
      volt = Potential5(v, {t1, t2});
    }
  } else if (m_elementType == ElementType::CurvedTetrahedron) {
    std::array<double, 10> v;
    for (size_t i = 0; i < 10; ++i) v[i] = pot[element.emap[i]];
    volt = Potential13(v, {t1, t2, t3, t4});
  }
  if (m_debug) {
    PrintElement("Potential", x, y, z, t1, t2, t3, t4, imap, pot);
  }
  return volt;
}

void ComponentFieldMap::WeightingField(const double xin, const double yin,
                                       const double zin, double& wx, double& wy,
                                       double& wz, const std::string& label) {
  // Initial values.
  wx = wy = wz = 0;
  // Do not proceed if not properly initialised.
  if (!m_ready) return;
  // Do not proceed if the requested weighting field does not exist.
  if (m_wpot.count(label) == 0) return;
  if (m_wpot[label].empty()) return;
  int iel = -1;
  Field(xin, yin, zin, wx, wy, wz, iel, m_wpot[label]);
}

double ComponentFieldMap::WeightingPotential(double xin, double yin, double zin,
                                             const std::string& label0) {
  // Do not proceed if not properly initialised.
  if (!m_ready) return 0.;

  // TODO! From ComponentComsol:
  // if (!CheckInRange(xin, yin, zin)) return 0.;

  std::string label = label0;
  if (m_wfieldCopies.count(label0) > 0) {
    label = m_wfieldCopies[label0].source;
    TVectorD pos(3);
    pos(0) = xin;
    pos(1) = yin;
    pos(2) = zin;
    pos = m_wfieldCopies[label0].rot * pos + m_wfieldCopies[label0].trans;
    xin = pos(0);
    yin = pos(1);
    zin = pos(2);
  }
  // Do not proceed if the requested weighting field does not exist.
  if (m_wpot.count(label) == 0) return 0.;
  if (m_wpot[label].empty()) return 0.;

  return Potential(xin, yin, zin, m_wpot[label]);
}

double ComponentFieldMap::DelayedWeightingPotential(double xin, double yin,
                                                    double zin,
                                                    const double tin,
                                                    const std::string& label0) {
  if (m_wdtimes.empty()) return 0.;
  // Assume no weighting field for times outside the range of available maps.
  if (tin < m_wdtimes.front()) return 0.;
  double t = tin;
  if (tin > m_wdtimes.back()) t = m_wdtimes.back();

  // Do not proceed if not properly initialised.
  if (!m_ready) return 0.;

  std::string label = label0;
  if (m_wfieldCopies.count(label0) > 0) {
    label = m_wfieldCopies[label0].source;
    TVectorD pos(3);
    pos(0) = xin;
    pos(1) = yin;
    pos(2) = zin;
    pos = m_wfieldCopies[label0].rot * pos + m_wfieldCopies[label0].trans;
    xin = pos(0);
    yin = pos(1);
    zin = pos(2);
  }

  // Do not proceed if the requested weighting field does not exist.
  if (m_dwpot.count(label) == 0) return 0.;
  if (m_dwpot[label].empty()) return 0.;

  // Copy the coordinates.
  double x = xin, y = yin, z = zin;

  // Map the coordinates onto field map coordinates.
  bool xmirr, ymirr, zmirr;
  double rcoordinate, rotation;
  MapCoordinates(x, y, z, xmirr, ymirr, zmirr, rcoordinate, rotation);

  if (m_warning) PrintWarning("DelayedWeightingPotential");

  // Find the element that contains this point.
  double t1, t2, t3, t4, jac[4][4], det;

  int imap = -1;
  if (m_elementType == ElementType::Serendipity) {
    imap = FindElement5(x, y, t1, t2, t3, t4, jac, det);
  } else if (m_elementType == ElementType::CurvedTetrahedron) {
    imap = FindElement13(x, y, z, t1, t2, t3, t4, jac, det);
  }
  if (imap < 0) return 0.;

  // Linear interpolation between time slices
  int i0;
  int i1;
  double f0;
  double f1;

  TimeInterpolation(t, f0, f1, i0, i1);

  // Get potential value.
  double dp0 = 0;
  double dp1 = 0;
  const Element& element = m_elements[imap];
  if (m_elementType == ElementType::Serendipity) {
    if (m_degenerate[imap]) {
      std::array<double, 6> v0, v1;
      for (size_t i = 0; i < 6; ++i) {
        v0[i] = m_dwpot[label][element.emap[i]][i0];
        v1[i] = m_dwpot[label][element.emap[i]][i1];
      }
      dp0 = Potential3(v0, {t1, t2, t3});
      dp1 = Potential3(v1, {t1, t2, t3});
    } else {
      std::array<double, 8> v0, v1;
      for (size_t i = 0; i < 8; ++i) {
        v0[i] = m_dwpot[label][element.emap[i]][i0];
        v1[i] = m_dwpot[label][element.emap[i]][i1];
      }
      dp0 = Potential5(v0, {t1, t2});
      dp1 = Potential5(v1, {t1, t2});
    }
  } else if (m_elementType == ElementType::CurvedTetrahedron) {
    std::array<double, 10> v0, v1;
    for (size_t i = 0; i < 10; ++i) {
      v0[i] = m_dwpot[label][element.emap[i]][i0];
      v1[i] = m_dwpot[label][element.emap[i]][i1];
    }
    dp0 = Potential13(v0, {t1, t2, t3, t4});
    dp1 = Potential13(v1, {t1, t2, t3, t4});
  }

  return f0 * dp0 + f1 * dp1;
}

void ComponentFieldMap::DelayedWeightingPotentials(const double xin,
                                                   const double yin,
                                                   const double zin,
                                                   const std::string& label0,
                                                   std::vector<double>& dwp) {
  const size_t nt = m_wdtimes.size();
  dwp.assign(nt, 0.);

  // Do not proceed if not properly initialised.
  if (!m_ready) return;

  // Copy the coordinates.
  double x = xin, y = yin, z = zin;

  std::string label = label0;
  if (m_wfieldCopies.count(label0) > 0) {
    label = m_wfieldCopies[label0].source;
    TVectorD pos(3);
    pos(0) = xin;
    pos(1) = yin;
    pos(2) = zin;
    pos = m_wfieldCopies[label0].rot * pos + m_wfieldCopies[label0].trans;
    x = pos(0);
    y = pos(1);
    z = pos(2);
  }

  // Do not proceed if the requested weighting field does not exist.
  if (m_dwpot.count(label) == 0) return;
  if (m_dwpot[label].empty()) return;

  // Map the coordinates onto field map coordinates.
  bool xmirr, ymirr, zmirr;
  double rcoordinate, rotation;
  MapCoordinates(x, y, z, xmirr, ymirr, zmirr, rcoordinate, rotation);

  if (m_warning) PrintWarning("DelayedWeightingPotentials");

  // Find the element that contains this point.
  double t1, t2, t3, t4, jac[4][4], det;

  int imap = -1;
  if (m_elementType == ElementType::Serendipity) {
    imap = FindElement5(x, y, t1, t2, t3, t4, jac, det);
  } else if (m_elementType == ElementType::CurvedTetrahedron) {
    imap = FindElement13(x, y, z, t1, t2, t3, t4, jac, det);
  }
  if (imap < 0) return;

  // Get potential value.
  // TODO: reorder m_dwpot, first time, then nodes.
  const Element& element = m_elements[imap];
  if (m_elementType == ElementType::Serendipity) {
    if (m_degenerate[imap]) {
      std::array<double, 6> v;
      for (size_t i = 0; i < m_wdtimes.size(); ++i) {
        for (size_t j = 0; j < 6; ++j) {
          v[j] = m_dwpot[label][element.emap[j]][i];
        }
        dwp[i] = Potential3(v, {t1, t2, t3});
      }
    } else {
      std::array<double, 8> v;
      for (size_t i = 0; i < m_wdtimes.size(); ++i) {
        for (size_t j = 0; j < 8; ++j) {
          v[j] = m_dwpot[label][element.emap[j]][i];
        }
        dwp[i] = Potential5(v, {t1, t2});
      }
    }
  } else if (m_elementType == ElementType::CurvedTetrahedron) {
    std::array<double, 10> v;
    for (size_t i = 0; i < m_wdtimes.size(); ++i) {
      for (size_t j = 0; j < 10; ++j) {
        v[j] = m_dwpot[label][element.emap[j]][i];
      }
      dwp[i] = Potential13(v, {t1, t2, t3, t4});
    }
  }
}

Medium* ComponentFieldMap::GetMedium(const double xin, const double yin,
                                     const double zin) {
  // Copy the coordinates.
  double x = xin, y = yin;
  double z = m_is3d ? zin : 0.;

  // Map the coordinates onto field map coordinates.
  bool xmirr, ymirr, zmirr;
  double rcoordinate, rotation;
  MapCoordinates(x, y, z, xmirr, ymirr, zmirr, rcoordinate, rotation);

  if (!m_is3d) {
    if (zin < m_minBoundingBox[2] || z > m_maxBoundingBox[2]) {
      return nullptr;
    }
  }

  // Do not proceed if not properly initialised.
  if (!m_ready) {
    PrintNotReady("GetMedium");
    return nullptr;
  }
  if (m_warning) PrintWarning("GetMedium");

  // Find the element that contains this point.
  double t1 = 0., t2 = 0., t3 = 0., t4 = 0.;
  double jac[4][4];
  double det = 0.;
  int imap = -1;
  if (m_elementType == ElementType::Serendipity) {
    imap = FindElement5(x, y, t1, t2, t3, t4, jac, det);
  } else if (m_elementType == ElementType::CurvedTetrahedron) {
    imap = FindElement13(x, y, z, t1, t2, t3, t4, jac, det);
  }
  if (imap < 0) {
    if (m_debug) {
      std::cerr << m_className << "::GetMedium: (" << x << ", " << y << ", "
                << z << ") is not in the mesh.\n";
    }
    return nullptr;
  }
  const Element& element = m_elements[imap];
  if (element.matmap >= m_materials.size()) {
    if (m_debug) {
      std::cerr << m_className << "::GetMedium: Element " << imap
                << " has out-of-range material number " << element.matmap
                << ".\n";
    }
    return nullptr;
  }
  if (m_debug) {
    PrintElement("GetMedium", x, y, z, t1, t2, t3, t4, imap, m_pot);
  }

  // Assign a medium.
  return m_materials[element.matmap].medium;
}

bool ComponentFieldMap::Check() {
  // MAPCHK
  // Ensure there are some mesh elements.
  if (!m_ready) {
    PrintNotReady("Check");
    return false;
  }
  // Compute the range of volumes.
  const size_t nElements = m_elements.size();
  double vmin = 0., vmax = 0.;
  for (size_t i = 0; i < nElements; ++i) {
    const double v = GetElementVolume(i);
    if (i == 0) {
      vmin = vmax = v;
    } else {
      vmin = std::min(vmin, v);
      vmax = std::max(vmax, v);
    }
  }
  // Number of bins.
  constexpr int nBins = 100;
  double scale = 1.;
  std::string unit = "cm";
  if (m_is3d) {
    if (vmax < 1.e-9) {
      unit = "um";
      scale = 1.e12;
    } else if (vmax < 1.e-3) {
      unit = "mm";
      scale = 1.e3;
    }
  } else {
    if (vmax < 1.e-6) {
      unit = "um";
      scale = 1.e8;
    } else if (vmax < 1.e-2) {
      unit = "mm";
      scale = 1.e2;
    }
  }
  vmin *= scale;
  vmax *= scale;
  // Check we do have a range and round it.
  vmin = std::max(0., vmin - 0.1 * (vmax - vmin));
  vmax = vmax + 0.1 * (vmax - vmin);
  if (vmin == vmax) {
    vmin -= 1. + std::abs(vmin);
    vmax += 1. + std::abs(vmax);
  }
  // CALL ROUND(SMIN,SMAX,NCHA,'LARGER,COARSER',STEP)
  std::string title = m_is3d ? ";volume [" : ";surface [";
  if (unit == "um") {
    title += "#mum";
  } else {
    title += unit;
  }
  if (m_is3d) {
    title += "^{3}];";
  } else {
    title += "^{2}];";
  }
  TH1F hElementVolume("hElementVolume", title.c_str(), nBins, vmin, vmax);

  TH1F hAspectRatio("hAspectRatio", ";largest / smallest vertex distance;",
                    nBins, 0., 100.);

  // Loop over all mesh elements.
  size_t nZero = 0;
  double rmin = 0., rmax = 0.;
  for (size_t i = 0; i < nElements; ++i) {
    double v = 0., dmin = 0., dmax = 0.;
    if (!GetElement(i, v, dmin, dmax)) return false;
    // Check for null-sizes.
    if (dmin <= 0. && !m_degenerate[i]) {
      std::cerr << m_className << "::Check:\n"
                << "    Found element with zero-length vertex separation.\n";
      return false;
    }
    const double r = dmax / dmin;
    hAspectRatio.Fill(r);
    if (v <= 0.) ++nZero;
    v *= scale;
    hElementVolume.Fill(v);
    //  Update maxima and minima.
    if (i == 0) {
      vmin = vmax = v;
      rmin = rmax = r;
    } else {
      vmin = std::min(vmin, v);
      vmax = std::max(vmax, v);
      rmin = std::min(rmin, r);
      rmax = std::max(rmax, r);
    }
  }
  if (nZero > 0) {
    std::cerr << m_className << "::Check:\n";
    if (m_is3d) {
      std::cerr << "    Found " << nZero << " element(s) with zero volume.\n";
    } else {
      std::cerr << "    Found " << nZero << " element(s) with zero surface.\n";
    }
  }
  TCanvas* c1 = new TCanvas("cAspectRatio", "Aspect ratio", 600, 600);
  c1->cd();
  hAspectRatio.DrawCopy();
  c1->Update();
  TCanvas* c2 = new TCanvas("cElementVolume", "Element measure", 600, 600);
  c2->cd();
  hElementVolume.DrawCopy();
  c2->Update();

  // Printout.
  std::cout << m_className << "::Check:\n"
            << "                      Smallest     Largest\n";
  std::printf("    Aspect ratios:  %15.8f  %15.8f\n", rmin, rmax);
  if (m_is3d) {
    std::printf("    Volumes [%s3]:  %15.8f  %15.8f\n", unit.c_str(), vmin,
                vmax);
  } else {
    std::printf("    Surfaces [%s2]: %15.8f  %15.8f\n", unit.c_str(), vmin,
                vmax);
  }
  return true;
}

void ComponentFieldMap::PrintMaterials() {
  // Do not proceed if not properly initialised.
  if (!m_ready) PrintNotReady("PrintMaterials");

  if (m_materials.empty()) {
    std::cerr << m_className << "::PrintMaterials:\n"
              << "    No materials are currently defined.\n";
    return;
  }

  const size_t nMaterials = m_materials.size();
  std::cout << m_className << "::PrintMaterials:\n"
            << "    Currently " << nMaterials << " materials are defined.\n"
            << "      Index Permittivity  Resistivity Notes\n";
  for (size_t i = 0; i < nMaterials; ++i) {
    printf("      %5zu %12g %12g", i, m_materials[i].eps, m_materials[i].ohm);
    if (m_materials[i].medium) {
      std::string name = m_materials[i].medium->GetName();
      std::cout << " " << name;
      if (m_materials[i].medium->IsDriftable()) std::cout << ", drift medium";
      if (m_materials[i].medium->IsIonisable()) std::cout << ", ionisable";
    }
    if (m_materials[i].driftmedium) {
      std::cout << " (drift medium)\n";
    } else {
      std::cout << "\n";
    }
  }
}

void ComponentFieldMap::DriftMedium(const size_t imat) {
  // Do not proceed if not properly initialised.
  if (!m_ready) PrintNotReady("DriftMedium");

  // Check value
  if (imat >= m_materials.size()) {
    std::cerr << m_className << "::DriftMedium: Index out of range.\n";
    return;
  }

  // Make drift medium
  m_materials[imat].driftmedium = true;
}

void ComponentFieldMap::NotDriftMedium(const size_t imat) {
  // Do not proceed if not properly initialised.
  if (!m_ready) PrintNotReady("NotDriftMedium");

  // Check value
  if (imat >= m_materials.size()) {
    std::cerr << m_className << "::NotDriftMedium: Index out of range.\n";
    return;
  }

  // Make drift medium
  m_materials[imat].driftmedium = false;
}

double ComponentFieldMap::GetPermittivity(const size_t imat) const {
  if (imat >= m_materials.size()) {
    std::cerr << m_className << "::GetPermittivity: Index out of range.\n";
    return -1.;
  }
  return m_materials[imat].eps;
}

double ComponentFieldMap::GetConductivity(const size_t imat) const {
  if (imat >= m_materials.size()) {
    std::cerr << m_className << "::GetConductivity: Index out of range.\n";
    return -1.;
  }
  return m_materials[imat].ohm;
}

void ComponentFieldMap::SetMedium(const size_t imat, Medium* medium) {
  if (imat >= m_materials.size()) {
    std::cerr << m_className << "::SetMedium: Index out of range.\n";
    return;
  }
  if (!medium) {
    std::cerr << m_className << "::SetMedium: Null pointer.\n";
    return;
  }
  if (m_debug) {
    std::cout << m_className << "::SetMedium: Associated material " << imat
              << " with medium " << medium->GetName() << ".\n";
  }
  m_materials[imat].medium = medium;
}

Medium* ComponentFieldMap::GetMedium(const size_t imat) const {
  if (imat >= m_materials.size()) {
    std::cerr << m_className << "::GetMedium: Index out of range.\n";
    return nullptr;
  }
  return m_materials[imat].medium;
}

void ComponentFieldMap::SetGas(Medium* medium) {
  if (!medium) {
    std::cerr << m_className << "::SetGas: Null pointer.\n";
    return;
  }
  size_t nMatch = 0;
  const size_t nMaterials = m_materials.size();
  for (size_t i = 0; i < nMaterials; ++i) {
    if (fabs(m_materials[i].eps - 1.) > 1.e-4) continue;
    m_materials[i].medium = medium;
    std::cout << m_className << "::SetGas: Associating material " << i
              << " with " << medium->GetName() << ".\n";
    ++nMatch;
  }
  if (nMatch == 0) {
    std::cerr << m_className << "::SetGas: Found no material with eps = 1.\n";
  }
}

bool ComponentFieldMap::GetElement(const size_t i, double& vol, double& dmin,
                                   double& dmax) const {
  if (i >= m_elements.size()) {
    std::cerr << m_className << "::GetElement: Index out of range.\n";
    return false;
  }
  vol = GetElementVolume(i);
  GetAspectRatio(i, dmin, dmax);
  return true;
}

double ComponentFieldMap::GetElementVolume(const size_t i) const {
  if (i >= m_elements.size()) return 0.;

  const Element& element = m_elements[i];
  if (m_elementType == ElementType::CurvedTetrahedron) {
    const Node& n0 = m_nodes[element.emap[0]];
    const Node& n1 = m_nodes[element.emap[1]];
    const Node& n2 = m_nodes[element.emap[2]];
    const Node& n3 = m_nodes[element.emap[3]];
    // Uses formula V = |a (dot) b x c|/6
    // with a => "3", b => "1", c => "2" and origin "0"
    const double vol =
        (n3.x - n0.x) *
            ((n1.y - n0.y) * (n2.z - n0.z) - (n2.y - n0.y) * (n1.z - n0.z)) +
        (n3.y - n0.y) *
            ((n1.z - n0.z) * (n2.x - n0.x) - (n2.z - n0.z) * (n1.x - n0.x)) +
        (n3.z - n0.z) *
            ((n1.x - n0.x) * (n2.y - n0.y) - (n3.x - n0.x) * (n1.y - n0.y));
    return fabs(vol) / 6.;
  } else if (m_elementType == ElementType::Serendipity) {
    const Node& n0 = m_nodes[element.emap[0]];
    const Node& n1 = m_nodes[element.emap[1]];
    const Node& n2 = m_nodes[element.emap[2]];
    const Node& n3 = m_nodes[element.emap[3]];
    const double surf =
        0.5 *
        (fabs((n1.x - n0.x) * (n2.y - n0.y) - (n2.x - n0.x) * (n1.y - n0.y)) +
         fabs((n3.x - n0.x) * (n2.y - n0.y) - (n2.x - n0.x) * (n3.y - n0.y)));
    return surf;
  }
  return 0.;
}

void ComponentFieldMap::GetAspectRatio(const size_t i, double& dmin,
                                       double& dmax) const {
  if (i >= m_elements.size()) {
    dmin = dmax = 0.;
    return;
  }

  const Element& element = m_elements[i];
  if (m_elementType == ElementType::CurvedTetrahedron) {
    const int np = 4;
    // Loop over all pairs of vertices.
    for (int j = 0; j < np - 1; ++j) {
      const Node& nj = m_nodes[element.emap[j]];
      for (int k = j + 1; k < np; ++k) {
        const Node& nk = m_nodes[element.emap[k]];
        // Compute distance.
        const double dx = nj.x - nk.x;
        const double dy = nj.y - nk.y;
        const double dz = nj.z - nk.z;
        const double dist = sqrt(dx * dx + dy * dy + dz * dz);
        if (k == 1) {
          dmin = dmax = dist;
        } else {
          if (dist < dmin) dmin = dist;
          if (dist > dmax) dmax = dist;
        }
      }
    }
  } else if (m_elementType == ElementType::Serendipity) {
    const int np = 8;
    // Loop over all pairs of vertices.
    for (int j = 0; j < np - 1; ++j) {
      const Node& nj = m_nodes[element.emap[j]];
      for (int k = j + 1; k < np; ++k) {
        const Node& nk = m_nodes[element.emap[k]];
        // Compute distance.
        const double dx = nj.x - nk.x;
        const double dy = nj.y - nk.y;
        const double dist = sqrt(dx * dx + dy * dy);
        if (k == 1) {
          dmin = dmax = dist;
        } else {
          if (dist < dmin) dmin = dist;
          if (dist > dmax) dmax = dist;
        }
      }
    }
  }
}

bool ComponentFieldMap::GetElementNodes(const size_t i,
                                        std::vector<size_t>& nodes) const {
  if (i >= m_elements.size()) {
    std::cerr << m_className << "::GetElementNodes: Index out of range.\n";
    return false;
  }
  const auto& element = m_elements[i];
  size_t nNodes = 4;
  if (m_elementType == ElementType::Serendipity && m_degenerate[i]) {
    nNodes = 3;
  }
  nodes.resize(nNodes);
  for (size_t j = 0; j < nNodes; ++j) nodes[j] = element.emap[j];
  return true;
}

bool ComponentFieldMap::GetElementRegion(const size_t i, size_t& mat,
                                         bool& drift) const {
  if (i >= m_elements.size()) {
    std::cerr << m_className << "::GetElementRegion: Index out of range.\n";
    return false;
  }
  mat = m_elements[i].matmap;
  drift = m_materials[mat].driftmedium;
  return true;
}

bool ComponentFieldMap::GetNode(const size_t i, double& x, double& y,
                                double& z) const {
  if (i >= m_nodes.size()) {
    std::cerr << m_className << "::GetNode: Index out of range.\n";
    return false;
  }
  x = m_nodes[i].x;
  y = m_nodes[i].y;
  z = m_nodes[i].z;
  return true;
}

double ComponentFieldMap::GetPotential(const size_t i) const {
  return i >= m_pot.size() ? 0. : m_pot[i];
}

bool ComponentFieldMap::SetDefaultDriftMedium() {
  // Find lowest epsilon and set drift medium flags.
  const size_t nMaterials = m_materials.size();
  double epsmin = -1;
  size_t iepsmin = 0;
  for (size_t i = 0; i < nMaterials; ++i) {
    m_materials[i].driftmedium = false;
    if (m_materials[i].eps < 0) continue;
    // Check for eps == 0.
    if (m_materials[i].eps == 0) {
      std::cerr << m_className << "::SetDefaultDriftMedium:\n"
                << "    Material " << i << " has zero permittivity.\n";
      m_materials[i].eps = -1.;
    } else if (epsmin < 0. || epsmin > m_materials[i].eps) {
      epsmin = m_materials[i].eps;
      iepsmin = i;
    }
  }
  if (epsmin < 0.) {
    std::cerr << m_className << "::SetDefaultDriftMedium:\n"
              << "    Found no material with positive permittivity.\n";
    return false;
  }
  m_materials[iepsmin].driftmedium = true;
  return true;
}

double ComponentFieldMap::Potential3(const std::array<double, 6>& v,
                                     const std::array<double, 3>& t) {
  double sum = 0.;
  for (size_t i = 0; i < 3; ++i) {
    sum += v[i] * t[i] * (2 * t[i] - 1);
  }
  sum += 4 * (v[3] * t[0] * t[1] + v[4] * t[0] * t[2] + v[5] * t[1] * t[2]);
  return sum;
}

void ComponentFieldMap::Field3(const std::array<double, 6>& v,
                               const std::array<double, 3>& t, double jac[4][4],
                               const double det, double& ex, double& ey) {
  std::array<double, 3> g;
  g[0] = v[0] * (4 * t[0] - 1) + v[3] * 4 * t[1] + v[4] * 4 * t[2];
  g[1] = v[1] * (4 * t[1] - 1) + v[3] * 4 * t[0] + v[5] * 4 * t[2];
  g[2] = v[2] * (4 * t[2] - 1) + v[4] * 4 * t[0] + v[5] * 4 * t[1];
  const double invdet = 1. / det;
  ex = -(jac[0][1] * g[0] + jac[1][1] * g[1] + jac[2][1] * g[2]) * invdet;
  ey = -(jac[0][2] * g[0] + jac[1][2] * g[1] + jac[2][2] * g[2]) * invdet;
}

double ComponentFieldMap::Potential5(const std::array<double, 8>& v,
                                     const std::array<double, 2>& t) {
  return -v[0] * (1 - t[0]) * (1 - t[1]) * (1 + t[0] + t[1]) * 0.25 -
         v[1] * (1 + t[0]) * (1 - t[1]) * (1 - t[0] + t[1]) * 0.25 -
         v[2] * (1 + t[0]) * (1 + t[1]) * (1 - t[0] - t[1]) * 0.25 -
         v[3] * (1 - t[0]) * (1 + t[1]) * (1 + t[0] - t[1]) * 0.25 +
         v[4] * (1 - t[0]) * (1 + t[0]) * (1 - t[1]) * 0.5 +
         v[5] * (1 + t[0]) * (1 + t[1]) * (1 - t[1]) * 0.5 +
         v[6] * (1 - t[0]) * (1 + t[0]) * (1 + t[1]) * 0.5 +
         v[7] * (1 - t[0]) * (1 + t[1]) * (1 - t[1]) * 0.5;
}

void ComponentFieldMap::Field5(const std::array<double, 8>& v,
                               const std::array<double, 2>& t, double jac[4][4],
                               const double det, double& ex, double& ey) {
  std::array<double, 2> g;
  g[0] = (v[0] * (1 - t[1]) * (2 * t[0] + t[1]) +
          v[1] * (1 - t[1]) * (2 * t[0] - t[1]) +
          v[2] * (1 + t[1]) * (2 * t[0] + t[1]) +
          v[3] * (1 + t[1]) * (2 * t[0] - t[1])) *
             0.25 +
         v[4] * t[0] * (t[1] - 1) + v[5] * (1 - t[1]) * (1 + t[1]) * 0.5 -
         v[6] * t[0] * (1 + t[1]) + v[7] * (t[1] - 1) * (t[1] + 1) * 0.5;
  g[1] = (v[0] * (1 - t[0]) * (t[0] + 2 * t[1]) -
          v[1] * (1 + t[0]) * (t[0] - 2 * t[1]) +
          v[2] * (1 + t[0]) * (t[0] + 2 * t[1]) -
          v[3] * (1 - t[0]) * (t[0] - 2 * t[1])) *
             0.25 +
         v[4] * (t[0] - 1) * (t[0] + 1) * 0.5 - v[5] * (1 + t[0]) * t[1] +
         v[6] * (1 - t[0]) * (1 + t[0]) * 0.5 + v[7] * (t[0] - 1) * t[1];
  const double invdet = 1. / det;
  ex = -(g[0] * jac[0][0] + g[1] * jac[1][0]) * invdet;
  ey = -(g[0] * jac[0][1] + g[1] * jac[1][1]) * invdet;
}

double ComponentFieldMap::Potential13(const std::array<double, 10>& v,
                                      const std::array<double, 4>& t) {
  double sum = 0.;
  for (size_t i = 0; i < 4; ++i) {
    sum += v[i] * t[i] * (t[i] - 0.5);
  }
  sum *= 2;
  sum += 4 * (v[4] * t[0] * t[1] + v[5] * t[0] * t[2] + v[6] * t[0] * t[3] +
              v[7] * t[1] * t[2] + v[8] * t[1] * t[3] + v[9] * t[2] * t[3]);
  return sum;
}

void ComponentFieldMap::Field13(const std::array<double, 10>& v,
                                const std::array<double, 4>& t,
                                double jac[4][4], const double det, double& ex,
                                double& ey, double& ez) {
  std::array<double, 4> g;
  g[0] = v[0] * (t[0] - 0.25) + v[4] * t[1] + v[5] * t[2] + v[6] * t[3];
  g[1] = v[1] * (t[1] - 0.25) + v[4] * t[0] + v[7] * t[2] + v[8] * t[3];
  g[2] = v[2] * (t[2] - 0.25) + v[5] * t[0] + v[7] * t[1] + v[9] * t[3];
  g[3] = v[3] * (t[3] - 0.25) + v[6] * t[0] + v[8] * t[1] + v[9] * t[2];
  std::array<double, 3> f = {0., 0., 0.};
  for (size_t j = 0; j < 4; ++j) {
    for (size_t i = 0; i < 3; ++i) {
      f[i] += g[j] * jac[j][i + 1];
    }
  }
  ex = -f[0] * det;
  ey = -f[1] * det;
  ez = -f[2] * det;
}

int ComponentFieldMap::FindElement5(const double x, const double y, double& t1,
                                    double& t2, double& t3, double& t4,
                                    double jac[4][4], double& det) const {
  // Backup
  double jacbak[4][4], detbak = 1.;
  double t1bak = 0., t2bak = 0., t3bak = 0., t4bak = 0.;
  int imapbak = -1;

  // Initial values.
  t1 = t2 = t3 = t4 = 0;

  // Verify the count of volumes that contain the point.
  int nfound = 0;
  int imap = -1;
  std::array<double, 8> xn;
  std::array<double, 8> yn;
  const auto& elements = (m_useTetrahedralTree && m_octree)
                             ? m_octree->GetElementsInBlock(Vec3(x, y, 0.))
                             : m_elementIndices;
  for (const auto i : elements) {
    if (x < m_bbMin[i][0] || y < m_bbMin[i][1] || x > m_bbMax[i][0] ||
        y > m_bbMax[i][1])
      continue;
    const Element& element = m_elements[i];
    if (m_degenerate[i]) {
      // Degenerate element
      for (size_t j = 0; j < 6; ++j) {
        const auto& node = m_nodes[element.emap[j]];
        xn[j] = node.x;
        yn[j] = node.y;
      }
      if (Coordinates3(x, y, t1, t2, t3, t4, jac, det, xn, yn) != 0) {
        continue;
      }
      if (t1 < 0 || t1 > 1 || t2 < 0 || t2 > 1 || t3 < 0 || t3 > 1) continue;
    } else {
      // Non-degenerate element
      for (size_t j = 0; j < 8; ++j) {
        const auto& node = m_nodes[element.emap[j]];
        xn[j] = node.x;
        yn[j] = node.y;
      }
      if (Coordinates5(x, y, t1, t2, t3, t4, jac, det, xn, yn) != 0) {
        continue;
      }
      if (t1 < -1 || t1 > 1 || t2 < -1 || t2 > 1) continue;
    }
    ++nfound;
    imap = i;
    if (m_debug) {
      std::cout << m_className << "::FindElement5:\n";
      if (m_degenerate[i]) {
        std::cout << "    Found matching degenerate element ";
      } else {
        std::cout << "    Found matching non-degenerate element ";
      }
      std::cout << i << ".\n";
    }
    if (!m_checkMultipleElement) return i;
    for (int j = 0; j < 4; ++j) {
      for (int k = 0; k < 4; ++k) jacbak[j][k] = jac[j][k];
    }
    detbak = det;
    t1bak = t1;
    t2bak = t2;
    t3bak = t3;
    t4bak = t4;
    imapbak = imap;
  }

  // In checking mode, verify the element count.
  if (m_checkMultipleElement) {
    if (nfound < 1) {
      if (m_debug) {
        std::cout << m_className << "::FindElement5:\n"
                  << "    No element matching point (" << x << ", " << y
                  << ") found.\n";
      }
      return -1;
    }
    if (nfound > 1) {
      std::cout << m_className << "::FindElement5:\n"
                << "    Found " << nfound << " elements matching point (" << x
                << ", " << y << ").\n";
    }
    for (int j = 0; j < 4; ++j) {
      for (int k = 0; k < 4; ++k) jac[j][k] = jacbak[j][k];
    }
    det = detbak;
    t1 = t1bak;
    t2 = t2bak;
    t3 = t3bak;
    t4 = t4bak;
    imap = imapbak;
    return imap;
  }

  if (m_debug) {
    std::cout << m_className << "::FindElement5:\n"
              << "    No element matching point (" << x << ", " << y
              << ") found.\n";
  }
  return -1;
}

int ComponentFieldMap::FindElement13(const double x, const double y,
                                     const double z, double& t1, double& t2,
                                     double& t3, double& t4, double jac[4][4],
                                     double& det) const {
  // Backup
  double jacbak[4][4];
  double detbak = 1.;
  double t1bak = 0., t2bak = 0., t3bak = 0., t4bak = 0.;
  int imapbak = -1;

  // Initial values.
  t1 = t2 = t3 = t4 = 0.;

  // Verify the count of volumes that contain the point.
  int nfound = 0;
  int imap = -1;

  std::array<double, 10> xn;
  std::array<double, 10> yn;
  std::array<double, 10> zn;

  const auto& elements = (m_useTetrahedralTree && m_octree)
                             ? m_octree->GetElementsInBlock(Vec3(x, y, z))
                             : m_elementIndices;
  for (const auto i : elements) {
    if (x < m_bbMin[i][0] || y < m_bbMin[i][1] || z < m_bbMin[i][2] ||
        x > m_bbMax[i][0] || y > m_bbMax[i][1] || z > m_bbMax[i][2]) {
      continue;
    }
    for (size_t j = 0; j < 10; ++j) {
      const auto& node = m_nodes[m_elements[i].emap[j]];
      xn[j] = node.x;
      yn[j] = node.y;
      zn[j] = node.z;
    }
    if (Coordinates13(x, y, z, t1, t2, t3, t4, jac, det, xn, yn, zn,
                      m_w12[i]) != 0) {
      continue;
    }
    if (t1 < 0 || t1 > 1 || t2 < 0 || t2 > 1 || t3 < 0 || t3 > 1 || t4 < 0 ||
        t4 > 1) {
      continue;
    }
    if (m_debug) {
      std::cout << m_className << "::FindElement13:\n"
                << "    Found matching element " << i << ".\n";
    }
    if (!m_checkMultipleElement) return i;
    ++nfound;
    imap = i;
    for (int j = 0; j < 4; ++j) {
      for (int k = 0; k < 4; ++k) jacbak[j][k] = jac[j][k];
    }
    detbak = det;
    t1bak = t1;
    t2bak = t2;
    t3bak = t3;
    t4bak = t4;
    imapbak = imap;
  }

  // In checking mode, verify the tetrahedron/triangle count.
  if (m_checkMultipleElement) {
    if (nfound < 1) {
      if (m_debug) {
        std::cout << m_className << "::FindElement13:\n"
                  << "    No element matching point (" << x << ", " << y << ", "
                  << z << ") found.\n";
      }
      return -1;
    }
    if (nfound > 1) {
      std::cerr << m_className << "::FindElement13:\n"
                << "    Found << " << nfound << " elements matching point ("
                << x << ", " << y << ", " << z << ").\n";
    }
    for (int j = 0; j < 4; ++j) {
      for (int k = 0; k < 4; ++k) jac[j][k] = jacbak[j][k];
    }
    det = detbak;
    t1 = t1bak;
    t2 = t2bak;
    t3 = t3bak;
    t4 = t4bak;
    imap = imapbak;
    return imap;
  }
  if (m_debug) {
    std::cout << m_className << "::FindElement13:\n"
              << "    No element matching point (" << x << ", " << y << ", "
              << z << ") found.\n";
  }
  return -1;
}

int ComponentFieldMap::FindElementCube(const double x, const double y,
                                       const double z, double& t1, double& t2,
                                       double& t3, TMatrixD*& jac,
                                       std::vector<TMatrixD*>& dN) const {
  int imap = -1;
  const size_t nElements = m_elements.size();
  for (size_t i = 0; i < nElements; ++i) {
    const Element& element = m_elements[i];
    const Node& n3 = m_nodes[element.emap[3]];
    if (x < n3.x || y < n3.y || z < n3.z) continue;
    const Node& n0 = m_nodes[element.emap[0]];
    const Node& n2 = m_nodes[element.emap[2]];
    const Node& n7 = m_nodes[element.emap[7]];
    if (x < n0.x && y < n2.y && z < n7.z) {
      imap = i;
      break;
    }
  }

  if (imap < 0) {
    if (m_debug) {
      std::cout << m_className << "::FindElementCube:\n"
                << "    Point (" << x << "," << y << "," << z
                << ") not in the mesh, it is background or PEC.\n";
      const Node& first0 = m_nodes[m_elements.front().emap[0]];
      const Node& first2 = m_nodes[m_elements.front().emap[2]];
      const Node& first3 = m_nodes[m_elements.front().emap[3]];
      const Node& first7 = m_nodes[m_elements.front().emap[7]];
      std::cout << "    First node (" << first3.x << "," << first3.y << ","
                << first3.z << ") in the mesh.\n";
      std::cout << "  dx= " << (first0.x - first3.x)
                << ", dy= " << (first2.y - first3.y)
                << ", dz= " << (first7.z - first3.z) << "\n";
      const Node& last0 = m_nodes[m_elements.back().emap[0]];
      const Node& last2 = m_nodes[m_elements.back().emap[2]];
      const Node& last3 = m_nodes[m_elements.back().emap[3]];
      const Node& last5 = m_nodes[m_elements.back().emap[5]];
      const Node& last7 = m_nodes[m_elements.back().emap[7]];
      std::cout << "    Last node (" << last5.x << "," << last5.y << ","
                << last5.z << ") in the mesh.\n";
      std::cout << "  dx= " << (last0.x - last3.x)
                << ", dy= " << (last2.y - last3.y)
                << ", dz= " << (last7.z - last3.z) << "\n";
    }
    return -1;
  }
  CoordinatesCube(x, y, z, t1, t2, t3, jac, dN, m_elements[imap]);
  return imap;
}

void ComponentFieldMap::Jacobian3(const std::array<double, 8>& xn,
                                  const std::array<double, 8>& yn,
                                  const double u, const double v,
                                  const double w, double& det,
                                  double jac[4][4]) {
  // Shorthands.
  const double fouru = 4 * u;
  const double fourv = 4 * v;
  const double fourw = 4 * w;

  const double j10 = (-1 + fouru) * xn[0] + fourv * xn[3] + fourw * xn[4];
  const double j20 = (-1 + fouru) * yn[0] + fourv * yn[3] + fourw * yn[4];
  const double j11 = (-1 + fourv) * xn[1] + fouru * xn[3] + fourw * xn[5];
  const double j21 = (-1 + fourv) * yn[1] + fouru * yn[3] + fourw * yn[5];
  const double j12 = (-1 + fourw) * xn[2] + fouru * xn[4] + fourv * xn[5];
  const double j22 = (-1 + fourw) * yn[2] + fouru * yn[4] + fourv * yn[5];
  // Determinant of the quadratic triangular Jacobian
  det = -(j11 - j12) * j20 - (j10 - j11) * j22 + (j10 - j12) * j21;

  // Terms of the quadratic triangular Jacobian
  jac[0][0] = j11 * j22 - j12 * j21;
  jac[0][1] = j21 - j22;
  jac[0][2] = j12 - j11;
  jac[1][0] = j12 * j20 - j10 * j22;
  jac[1][1] = j22 - j20;
  jac[1][2] = j10 - j12;
  jac[2][0] = j10 * j21 - j11 * j20;
  jac[2][1] = j20 - j21;
  jac[2][2] = j11 - j10;
}

void ComponentFieldMap::Jacobian5(const std::array<double, 8>& xn,
                                  const std::array<double, 8>& yn,
                                  const double u, const double v, double& det,
                                  double jac[4][4]) {
  // Jacobian terms
  const double g0 = (1 - u) * (2 * v + u);
  const double g1 = (1 + u) * (2 * v - u);
  const double g2 = (1 + u) * (2 * v + u);
  const double g3 = (1 - u) * (2 * v - u);
  const double g4 = (1 - u) * (1 + u);
  const double g5 = (1 + u) * v;
  const double g7 = (1 - u) * v;
  jac[0][0] = 0.25 * (g0 * yn[0] + g1 * yn[1] + g2 * yn[2] + g3 * yn[3]) -
              0.5 * g4 * yn[4] - g5 * yn[5] + 0.5 * g4 * yn[6] - g7 * yn[7];
  jac[0][1] = -0.25 * (g0 * xn[0] + g1 * xn[1] + g2 * xn[2] + g3 * xn[3]) +
              0.5 * g4 * xn[4] + g5 * xn[5] - 0.5 * g4 * xn[6] + g7 * xn[7];
  const double h0 = (1 - v) * (2 * u + v);
  const double h1 = (1 - v) * (2 * u - v);
  const double h2 = (1 + v) * (2 * u + v);
  const double h3 = (1 + v) * (2 * u - v);
  const double h4 = (1 - v) * u;
  const double h5 = (1 - v) * (1 + v);
  const double h6 = (1 + v) * u;
  jac[1][0] = -0.25 * (h0 * yn[0] + h1 * yn[1] + h2 * yn[2] + h3 * yn[3]) +
              h4 * yn[4] - 0.5 * h5 * yn[5] + h6 * yn[6] + 0.5 * h5 * yn[7];
  jac[1][1] = 0.25 * (h0 * xn[0] + h1 * xn[1] + h2 * xn[2] + h3 * xn[3]) -
              h4 * xn[4] + 0.5 * h5 * xn[5] - h6 * xn[6] - 0.5 * h5 * xn[7];

  // Determinant.
  det = jac[0][0] * jac[1][1] - jac[0][1] * jac[1][0];
}

void ComponentFieldMap::Jacobian13(const std::array<double, 10>& xn,
                                   const std::array<double, 10>& yn,
                                   const std::array<double, 10>& zn,
                                   const double fourt0, const double fourt1,
                                   const double fourt2, const double fourt3,
                                   double& det, double jac[4][4]) {
  const double fourt0m1 = fourt0 - 1.;
  const double j10 =
      fourt0m1 * xn[0] + fourt1 * xn[4] + fourt2 * xn[5] + fourt3 * xn[6];
  const double j20 =
      fourt0m1 * yn[0] + fourt1 * yn[4] + fourt2 * yn[5] + fourt3 * yn[6];
  const double j30 =
      fourt0m1 * zn[0] + fourt1 * zn[4] + fourt2 * zn[5] + fourt3 * zn[6];

  const double fourt1m1 = fourt1 - 1.;
  const double j11 =
      fourt1m1 * xn[1] + fourt0 * xn[4] + fourt2 * xn[7] + fourt3 * xn[8];
  const double j21 =
      fourt1m1 * yn[1] + fourt0 * yn[4] + fourt2 * yn[7] + fourt3 * yn[8];
  const double j31 =
      fourt1m1 * zn[1] + fourt0 * zn[4] + fourt2 * zn[7] + fourt3 * zn[8];

  const double fourt2m1 = fourt2 - 1.;
  const double j12 =
      fourt2m1 * xn[2] + fourt0 * xn[5] + fourt1 * xn[7] + fourt3 * xn[9];
  const double j22 =
      fourt2m1 * yn[2] + fourt0 * yn[5] + fourt1 * yn[7] + fourt3 * yn[9];
  const double j32 =
      fourt2m1 * zn[2] + fourt0 * zn[5] + fourt1 * zn[7] + fourt3 * zn[9];

  const double fourt3m1 = fourt3 - 1.;
  const double j13 =
      fourt3m1 * xn[3] + fourt0 * xn[6] + fourt1 * xn[8] + fourt2 * xn[9];
  const double j23 =
      fourt3m1 * yn[3] + fourt0 * yn[6] + fourt1 * yn[8] + fourt2 * yn[9];
  const double j33 =
      fourt3m1 * zn[3] + fourt0 * zn[6] + fourt1 * zn[8] + fourt2 * zn[9];

  const double a1 = j10 * j21 - j20 * j11;
  const double a2 = j10 * j22 - j20 * j12;
  const double a3 = j10 * j23 - j20 * j13;
  const double a4 = j11 * j22 - j21 * j12;
  const double a5 = j11 * j23 - j21 * j13;
  const double a6 = j12 * j23 - j22 * j13;

  const double d1011 = j10 - j11;
  const double d1012 = j10 - j12;
  const double d1013 = j10 - j13;
  const double d1112 = j11 - j12;
  const double d1113 = j11 - j13;
  const double d1213 = j12 - j13;

  const double d2021 = j20 - j21;
  const double d2022 = j20 - j22;
  const double d2023 = j20 - j23;
  const double d2122 = j21 - j22;
  const double d2123 = j21 - j23;
  const double d2223 = j22 - j23;

  jac[0][0] = -a5 * j32 + a4 * j33 + a6 * j31;
  jac[0][1] = -d2123 * j32 + d2122 * j33 + d2223 * j31;
  jac[0][2] = d1113 * j32 - d1112 * j33 - d1213 * j31;
  jac[0][3] = -d1113 * j22 + d1112 * j23 + d1213 * j21;

  jac[1][0] = -a6 * j30 + a3 * j32 - a2 * j33;
  jac[1][1] = -d2223 * j30 + d2023 * j32 - d2022 * j33;
  jac[1][2] = d1213 * j30 - d1013 * j32 + d1012 * j33;
  jac[1][3] = -d1213 * j20 + d1013 * j22 - d1012 * j23;

  jac[2][0] = a5 * j30 + a1 * j33 - a3 * j31;
  jac[2][1] = d2123 * j30 + d2021 * j33 - d2023 * j31;
  jac[2][2] = -d1113 * j30 - d1011 * j33 + d1013 * j31;
  jac[2][3] = d1113 * j20 + d1011 * j23 - d1013 * j21;

  jac[3][0] = -a4 * j30 - a1 * j32 + a2 * j31;
  jac[3][1] = -d2122 * j30 - d2021 * j32 + d2022 * j31;
  jac[3][2] = d1112 * j30 + d1011 * j32 - d1012 * j31;
  jac[3][3] = -d1112 * j20 - d1011 * j22 + d1012 * j21;

  det = 1. /
        (jac[0][3] * j30 + jac[1][3] * j31 + jac[2][3] * j32 + jac[3][3] * j33);
}

void ComponentFieldMap::JacobianCube(const Element& element, const double t1,
                                     const double t2, const double t3,
                                     TMatrixD*& jac,
                                     std::vector<TMatrixD*>& dN) const {
  if (!jac) {
    std::cerr << m_className << "::JacobianCube:\n";
    std::cerr << "    Pointer to Jacobian matrix is empty!\n";
    return;
  }
  dN.clear();

  // Here the partial derivatives of the 8 shaping functions are calculated
  double N1[3] = {-1 * (1 - t2) * (1 - t3), (1 - t1) * -1 * (1 - t3),
                  (1 - t1) * (1 - t2) * -1};
  double N2[3] = {+1 * (1 - t2) * (1 - t3), (1 + t1) * -1 * (1 - t3),
                  (1 + t1) * (1 - t2) * -1};
  double N3[3] = {+1 * (1 + t2) * (1 - t3), (1 + t1) * +1 * (1 - t3),
                  (1 + t1) * (1 + t2) * -1};
  double N4[3] = {-1 * (1 + t2) * (1 - t3), (1 - t1) * +1 * (1 - t3),
                  (1 - t1) * (1 + t2) * -1};
  double N5[3] = {-1 * (1 - t2) * (1 + t3), (1 - t1) * -1 * (1 + t3),
                  (1 - t1) * (1 - t2) * +1};
  double N6[3] = {+1 * (1 - t2) * (1 + t3), (1 + t1) * -1 * (1 + t3),
                  (1 + t1) * (1 - t2) * +1};
  double N7[3] = {+1 * (1 + t2) * (1 + t3), (1 + t1) * +1 * (1 + t3),
                  (1 + t1) * (1 + t2) * +1};
  double N8[3] = {-1 * (1 + t2) * (1 + t3), (1 - t1) * +1 * (1 + t3),
                  (1 - t1) * (1 + t2) * +1};
  // Partial derivatives are stored in dN
  TMatrixD* m_N1 = new TMatrixD(3, 1, N1);
  *m_N1 = (1. / 8. * (*m_N1));
  dN.push_back(m_N1);
  TMatrixD* m_N2 = new TMatrixD(3, 1, N2);
  *m_N2 = (1. / 8. * (*m_N2));
  dN.push_back(m_N2);
  TMatrixD* m_N3 = new TMatrixD(3, 1, N3);
  *m_N3 = (1. / 8. * (*m_N3));
  dN.push_back(m_N3);
  TMatrixD* m_N4 = new TMatrixD(3, 1, N4);
  *m_N4 = (1. / 8. * (*m_N4));
  dN.push_back(m_N4);
  TMatrixD* m_N5 = new TMatrixD(3, 1, N5);
  *m_N5 = (1. / 8. * (*m_N5));
  dN.push_back(m_N5);
  TMatrixD* m_N6 = new TMatrixD(3, 1, N6);
  *m_N6 = (1. / 8. * (*m_N6));
  dN.push_back(m_N6);
  TMatrixD* m_N7 = new TMatrixD(3, 1, N7);
  *m_N7 = (1. / 8. * (*m_N7));
  dN.push_back(m_N7);
  TMatrixD* m_N8 = new TMatrixD(3, 1, N8);
  *m_N8 = (1. / 8. * (*m_N8));
  dN.push_back(m_N8);
  // Calculation of the jacobian using dN
  for (int j = 0; j < 8; ++j) {
    const Node& node = m_nodes[element.emap[j]];
    (*jac)(0, 0) += node.x * ((*dN.at(j))(0, 0));
    (*jac)(0, 1) += node.y * ((*dN.at(j))(0, 0));
    (*jac)(0, 2) += node.z * ((*dN.at(j))(0, 0));
    (*jac)(1, 0) += node.x * ((*dN.at(j))(1, 0));
    (*jac)(1, 1) += node.y * ((*dN.at(j))(1, 0));
    (*jac)(1, 2) += node.z * ((*dN.at(j))(1, 0));
    (*jac)(2, 0) += node.x * ((*dN.at(j))(2, 0));
    (*jac)(2, 1) += node.y * ((*dN.at(j))(2, 0));
    (*jac)(2, 2) += node.z * ((*dN.at(j))(2, 0));
  }

  // compute determinant
  if (m_debug) {
    std::cout << m_className << "::JacobianCube:" << std::endl;
    std::cout << "   Det.: " << jac->Determinant() << std::endl;
    std::cout << "   Jacobian matrix.: " << std::endl;
    jac->Print("%11.10g");
    std::cout << "   Hexahedral coordinates (t, u, v) = (" << t1 << "," << t2
              << "," << t3 << ")" << std::endl;
    std::cout << "   Node xyzV" << std::endl;
    for (int j = 0; j < 8; ++j) {
      const Node& node = m_nodes[element.emap[j]];
      std::cout << "         " << element.emap[j] << "          " << node.x
                << "         " << node.y << "         " << node.z << "         "
                << m_pot[element.emap[j]] << std::endl;
    }
  }
}

int ComponentFieldMap::Coordinates3(const double x, const double y, double& t1,
                                    double& t2, double& t3, double& t4,
                                    double jac[4][4], double& det,
                                    const std::array<double, 8>& xn,
                                    const std::array<double, 8>& yn) const {
  if (m_debug) {
    std::cout << m_className << "::Coordinates3:\n"
              << "   Point (" << x << ", " << y << ")\n";
  }

  // Provisional values
  t1 = t2 = t3 = t4 = 0;

  // Make a first order approximation, using the linear triangle.
  const double d1 =
      (xn[0] - xn[1]) * (yn[2] - yn[1]) - (xn[2] - xn[1]) * (yn[0] - yn[1]);
  const double d2 =
      (xn[1] - xn[2]) * (yn[0] - yn[2]) - (xn[0] - xn[2]) * (yn[1] - yn[2]);
  const double d3 =
      (xn[2] - xn[0]) * (yn[1] - yn[0]) - (xn[1] - xn[0]) * (yn[2] - yn[0]);
  if (d1 == 0 || d2 == 0 || d3 == 0) {
    std::cerr << m_className << "::Coordinates3:\n"
              << "    Calculation of linear coordinates failed; abandoned.\n";
    return 1;
  }
  t1 = ((x - xn[1]) * (yn[2] - yn[1]) - (y - yn[1]) * (xn[2] - xn[1])) / d1;
  t2 = ((x - xn[2]) * (yn[0] - yn[2]) - (y - yn[2]) * (xn[0] - xn[2])) / d2;
  t3 = ((x - xn[0]) * (yn[1] - yn[0]) - (y - yn[0]) * (xn[1] - xn[0])) / d3;

  // Start iterative refinement.
  double td1 = t1, td2 = t2, td3 = t3;
  bool converged = false;
  std::array<double, 6> f;
  for (int iter = 0; iter < 10; iter++) {
    if (m_debug) {
      std::cout << m_className << "::Coordinates3:\n";
      std::cout << "    Iteration " << iter << ":     (u, v, w) = (" << td1
                << ", " << td2 << ", " << td3 << "), sum = " << td1 + td2 + td3
                << "\n";
    }
    // Evaluate the shape functions.
    f[0] = td1 * (2 * td1 - 1);
    f[1] = td2 * (2 * td2 - 1);
    f[2] = td3 * (2 * td3 - 1);
    f[3] = 4 * td1 * td2;
    f[4] = 4 * td1 * td3;
    f[5] = 4 * td2 * td3;
    // Re-compute the (x,y) position for this coordinate.
    double xr = 0., yr = 0.;
    for (size_t i = 0; i < 6; ++i) {
      xr += xn[i] * f[i];
      yr += yn[i] * f[i];
    }
    const double sr = td1 + td2 + td3;
    // Compute the Jacobian.
    Jacobian3(xn, yn, td1, td2, td3, det, jac);
    // Compute the difference vector.
    const double diff[3] = {1 - sr, x - xr, y - yr};
    // Update the estimate.
    const double invdet = 1. / det;
    double corr[3] = {0., 0., 0.};
    for (size_t l = 0; l < 3; l++) {
      for (size_t k = 0; k < 3; k++) {
        corr[l] += jac[l][k] * diff[k];
      }
      corr[l] *= invdet;
    }
    // Debugging
    if (m_debug) {
      std::cout << m_className << "::Coordinates3:\n";
      std::cout << "    Difference vector:  (1, x, y)  = (" << diff[0] << ", "
                << diff[1] << ", " << diff[2] << ").\n";
      std::cout << "    Correction vector:  (u, v, w) = (" << corr[0] << ", "
                << corr[1] << ", " << corr[2] << ").\n";
    }
    // Update the vector.
    td1 += corr[0];
    td2 += corr[1];
    td3 += corr[2];
    // Check for convergence.
    constexpr double tol = 1.e-5;
    if (fabs(corr[0]) < tol && fabs(corr[1]) < tol && fabs(corr[2]) < tol) {
      if (m_debug) {
        std::cout << m_className << "::Coordinates3: Convergence reached.";
      }
      converged = true;
      break;
    }
  }
  // No convergence reached
  if (!converged) {
    const double xmin = std::min({xn[0], xn[1], xn[2]});
    const double xmax = std::max({xn[0], xn[1], xn[2]});
    const double ymin = std::min({yn[0], yn[1], yn[2]});
    const double ymax = std::max({yn[0], yn[1], yn[2]});
    if (x >= xmin && x <= xmax && y >= ymin && y <= ymax) {
      if (m_printConvergenceWarnings) {
        std::cout << m_className << "::Coordinates3:\n"
                  << "    No convergence achieved "
                  << "when refining internal isoparametric coordinates\n"
                  << "    at position (" << x << ", " << y << ").\n";
      }
      t1 = t2 = t3 = t4 = 0;
      return 1;
    }
  }

  // Convergence reached.
  t1 = td1;
  t2 = td2;
  t3 = td3;
  t4 = 0;
  if (m_debug) {
    std::cout << m_className << "::Coordinates3:\n";
    std::cout << "    Convergence reached at (t1, t2, t3) = (" << t1 << ", "
              << t2 << ", " << t3 << ").\n";
    // For debugging purposes, show position
    const double f0 = td1 * (2 * td1 - 1);
    const double f1 = td2 * (2 * td2 - 1);
    const double f2 = td3 * (2 * td3 - 1);
    const double f3 = 4 * td1 * td2;
    const double f4 = 4 * td1 * td3;
    const double f5 = 4 * td2 * td3;
    const double xr = xn[0] * f0 + xn[1] * f1 + xn[2] * f2 + xn[3] * f3 +
                      xn[4] * f4 + xn[5] * f5;
    const double yr = yn[0] * f0 + yn[1] * f1 + yn[2] * f2 + yn[3] * f3 +
                      yn[4] * f4 + yn[5] * f5;
    const double sr = td1 + td2 + td3;
    std::cout << m_className << "::Coordinates3:\n";
    std::cout << "    Position requested:     (" << x << ", " << y << ")\n";
    std::cout << "    Reconstructed:          (" << xr << ", " << yr << ")\n";
    std::cout << "    Difference:             (" << x - xr << ", " << y - yr
              << ")\n";
    std::cout << "    Checksum - 1:           " << sr - 1 << "\n";
  }

  // Success
  return 0;
}

int ComponentFieldMap::Coordinates4(const double x, const double y, double& t1,
                                    double& t2, double& t3, double& t4,
                                    double& det,
                                    const std::array<double, 8>& xn,
                                    const std::array<double, 8>& yn) const {
  if (m_debug) {
    std::cout << m_className << "::Coordinates4:\n"
              << "   Point (" << x << ", " << y << ")\n";
  }
  // Failure flag
  int ifail = 1;

  // Provisional values
  t1 = t2 = t3 = t4 = 0.;

  // Compute determinant.
  const double dd = -(xn[0] * yn[1]) + xn[3] * yn[2] - xn[2] * yn[3] +
                    x * (-yn[0] + yn[1] - yn[2] + yn[3]) + xn[1] * (yn[0] - y) +
                    (xn[0] + xn[2] - xn[3]) * y;
  det =
      -(-((xn[0] - xn[3]) * (yn[1] - yn[2])) +
        (xn[1] - xn[2]) * (yn[0] - yn[3])) *
          (2 * x * (-yn[0] + yn[1] + yn[2] - yn[3]) -
           (xn[0] + xn[3]) * (yn[1] + yn[2] - 2 * y) +
           xn[1] * (yn[0] + yn[3] - 2 * y) + xn[2] * (yn[0] + yn[3] - 2 * y)) +
      dd * dd;

  // Check that the determinant is non-negative
  // (this can happen if the point is out of range).
  if (det < 0) {
    if (m_debug) {
      std::cerr << m_className << "::Coordinates4:\n"
                << "    No solution found for isoparametric coordinates\n"
                << "    because the determinant " << det << " is < 0.\n";
    }
    return ifail;
  }

  // Vector products for evaluation of T1.
  double prod =
      ((xn[2] - xn[3]) * (yn[0] - yn[1]) - (xn[0] - xn[1]) * (yn[2] - yn[3]));
  if (prod * prod > 1.0e-12 *
                        ((xn[0] - xn[1]) * (xn[0] - xn[1]) +
                         (yn[0] - yn[1]) * (yn[0] - yn[1])) *
                        ((xn[2] - xn[3]) * (xn[2] - xn[3]) +
                         (yn[2] - yn[3]) * (yn[2] - yn[3]))) {
    t1 = (-(xn[3] * yn[0]) + x * yn[0] + xn[2] * yn[1] - x * yn[1] -
          xn[1] * yn[2] + x * yn[2] + xn[0] * yn[3] - x * yn[3] - xn[0] * y +
          xn[1] * y - xn[2] * y + xn[3] * y + sqrt(det)) /
         prod;
  } else {
    double xp = yn[0] - yn[1];
    double yp = xn[1] - xn[0];
    double dn = sqrt(xp * xp + yp * yp);
    if (dn <= 0) {
      std::cerr << m_className << "::Coordinates4:\n"
                << "    Element appears to be degenerate in the 1 - 2 axis.\n";
      return ifail;
    }
    xp = xp / dn;
    yp = yp / dn;
    double dpoint = xp * (x - xn[0]) + yp * (y - yn[0]);
    double dbox = xp * (xn[3] - xn[0]) + yp * (yn[3] - yn[0]);
    if (dbox == 0) {
      std::cerr << m_className << "::Coordinates4:\n"
                << "    Element appears to be degenerate in the 1 - 3 axis.\n";
      return ifail;
    }
    double t = -1 + 2 * dpoint / dbox;
    double xt1 = xn[0] + 0.5 * (t + 1) * (xn[3] - xn[0]);
    double yt1 = yn[0] + 0.5 * (t + 1) * (yn[3] - yn[0]);
    double xt2 = xn[1] + 0.5 * (t + 1) * (xn[2] - xn[1]);
    double yt2 = yn[1] + 0.5 * (t + 1) * (yn[2] - yn[1]);
    dn = (xt1 - xt2) * (xt1 - xt2) + (yt1 - yt2) * (yt1 - yt2);
    if (dn <= 0) {
      std::cout << m_className << "::Coordinates4:\n";
      std::cout
          << "    Coordinate requested at convergence point of element.\n";
      return ifail;
    }
    t1 = -1 + 2 * ((x - xt1) * (xt2 - xt1) + (y - yt1) * (yt2 - yt1)) / dn;
  }

  // Vector products for evaluation of T2.
  prod =
      ((xn[0] - xn[3]) * (yn[1] - yn[2]) - (xn[1] - xn[2]) * (yn[0] - yn[3]));
  if (prod * prod > 1.0e-12 *
                        ((xn[0] - xn[3]) * (xn[0] - xn[3]) +
                         (yn[0] - yn[3]) * (yn[0] - yn[3])) *
                        ((xn[1] - xn[2]) * (xn[1] - xn[2]) +
                         (yn[1] - yn[2]) * (yn[1] - yn[2]))) {
    t2 = (-(xn[1] * yn[0]) + x * yn[0] + xn[0] * yn[1] - x * yn[1] -
          xn[3] * yn[2] + x * yn[2] + xn[2] * yn[3] - x * yn[3] - xn[0] * y +
          xn[1] * y - xn[2] * y + xn[3] * y - sqrt(det)) /
         prod;
  } else {
    double xp = yn[0] - yn[3];
    double yp = xn[3] - xn[0];
    double dn = sqrt(xp * xp + yp * yp);
    if (dn <= 0) {
      std::cerr << m_className << "Coordinates4:\n"
                << "    Element appears to be degenerate in the 1 - 4 axis.\n";
      return ifail;
    }
    xp = xp / dn;
    yp = yp / dn;
    double dpoint = xp * (x - xn[0]) + yp * (y - yn[0]);
    double dbox = xp * (xn[1] - xn[0]) + yp * (yn[1] - yn[0]);
    if (dbox == 0) {
      std::cerr << m_className << "::Coordinates4:\n"
                << "    Element appears to be degenerate in the 1 - 2 axis.\n";
      return ifail;
    }
    double t = -1 + 2 * dpoint / dbox;
    double xt1 = xn[0] + 0.5 * (t + 1) * (xn[1] - xn[0]);
    double yt1 = yn[0] + 0.5 * (t + 1) * (yn[1] - yn[0]);
    double xt2 = xn[3] + 0.5 * (t + 1) * (xn[2] - xn[3]);
    double yt2 = yn[3] + 0.5 * (t + 1) * (yn[2] - yn[3]);
    dn = (xt1 - xt2) * (xt1 - xt2) + (yt1 - yt2) * (yt1 - yt2);
    if (dn <= 0) {
      std::cout
          << m_className << "::Coordinates4:\n"
          << "    Coordinate requested at convergence point of element.\n";
      return ifail;
    }
    t2 = -1 + 2 * ((x - xt1) * (xt2 - xt1) + (y - yt1) * (yt2 - yt1)) / dn;
  }
  if (m_debug) {
    std::cout << m_className << "::Coordinates4:\n";
    std::cout << "    Isoparametric (u, v):   (" << t1 << ", " << t2 << ").\n";
    // Re-compute the (x,y,z) position for this coordinate.
    const double f0 = (1 - t1) * (1 - t2) * 0.25;
    const double f1 = (1 + t1) * (1 - t2) * 0.25;
    const double f2 = (1 + t1) * (1 + t2) * 0.25;
    const double f3 = (1 - t1) * (1 + t2) * 0.25;
    const double xr = xn[0] * f0 + xn[1] * f1 + xn[2] * f2 + xn[3] * f3;
    const double yr = yn[0] * f0 + yn[1] * f1 + yn[2] * f2 + yn[3] * f3;
    std::cout << m_className << "::Coordinates4: \n";
    std::cout << "    Position requested:     (" << x << ", " << y << ")\n";
    std::cout << "    Reconstructed:          (" << xr << ", " << yr << ")\n";
    std::cout << "    Difference:             (" << x - xr << ", " << y - yr
              << ")\n";
  }

  // This should have worked if we get this far.
  ifail = 0;
  return ifail;
}

int ComponentFieldMap::Coordinates5(const double x, const double y, double& t1,
                                    double& t2, double& t3, double& t4,
                                    double jac[4][4], double& det,
                                    const std::array<double, 8>& xn,
                                    const std::array<double, 8>& yn) const {
  // Debugging
  if (m_debug) {
    std::cout << m_className << "::Coordinates5:\n"
              << "   Point (" << x << ", " << y << ")\n";
  }

  // Failure flag
  int ifail = 1;

  // Provisional values
  t1 = t2 = t3 = t4 = 0;

  // Make a first order approximation.
  if (Coordinates4(x, y, t1, t2, t3, t4, det, xn, yn) > 0) {
    if (m_debug) {
      std::cout << "    Failure to obtain linear estimate of isoparametric "
                   "coordinates\n.";
    }
    return ifail;
  }

  // Check whether the point is far outside.
  if (t1 < -1.5 || t1 > 1.5 || t2 < -1.5 || t2 > 1.5) {
    if (m_debug) {
      std::cout << "    Point far outside, (t1,t2) = (" << t1 << ", " << t2
                << ").\n";
    }
    return ifail;
  }

  // Start iteration
  double td1 = t1, td2 = t2;
  bool converged = false;
  std::array<double, 8> f;
  for (int iter = 0; iter < 10; iter++) {
    if (m_debug) {
      std::cout << "    Iteration " << iter << ":     (t1, t2) = (" << td1
                << ", " << td2 << ").\n";
    }
    // Re-compute the (x,y,z) position for this coordinate.
    f[0] = (-(1 - td1) * (1 - td2) * (1 + td1 + td2)) * 0.25;
    f[1] = (-(1 + td1) * (1 - td2) * (1 - td1 + td2)) * 0.25;
    f[2] = (-(1 + td1) * (1 + td2) * (1 - td1 - td2)) * 0.25;
    f[3] = (-(1 - td1) * (1 + td2) * (1 + td1 - td2)) * 0.25;
    f[4] = (1 - td1) * (1 + td1) * (1 - td2) * 0.5;
    f[5] = (1 + td1) * (1 + td2) * (1 - td2) * 0.5;
    f[6] = (1 - td1) * (1 + td1) * (1 + td2) * 0.5;
    f[7] = (1 - td1) * (1 + td2) * (1 - td2) * 0.5;
    double xr = 0., yr = 0.;
    for (size_t i = 0; i < 8; ++i) {
      xr += xn[i] * f[i];
      yr += yn[i] * f[i];
    }
    // Compute the Jacobian.
    Jacobian5(xn, yn, td1, td2, det, jac);
    // Compute the difference vector.
    double diff[2] = {x - xr, y - yr};
    // Update the estimate.
    double corr[2] = {0., 0.};
    const double invdet = 1. / det;
    for (size_t l = 0; l < 2; ++l) {
      for (size_t k = 0; k < 2; ++k) {
        corr[l] += jac[l][k] * diff[k];
      }
      corr[l] *= invdet;
    }
    // Debugging
    if (m_debug) {
      std::cout << "    Difference vector: (x, y)   = (" << diff[0] << ", "
                << diff[1] << ").\n";
      std::cout << "    Correction vector: (t1, t2) = (" << corr[0] << ", "
                << corr[1] << ").\n";
    }
    // Update the vector.
    td1 += corr[0];
    td2 += corr[1];
    // Check for convergence.
    constexpr double tol = 1.e-5;
    if (fabs(corr[0]) < tol && fabs(corr[1]) < tol) {
      if (m_debug) std::cout << "    Convergence reached.\n";
      converged = true;
      break;
    }
  }
  // No convergence reached.
  if (!converged) {
    double xmin = *std::min_element(xn.begin(), xn.end());
    double xmax = *std::max_element(xn.begin(), xn.end());
    double ymin = *std::min_element(yn.begin(), yn.end());
    double ymax = *std::max_element(yn.begin(), yn.end());
    if (x >= xmin && x <= xmax && y >= ymin && y <= ymax) {
      if (m_printConvergenceWarnings) {
        std::cout << m_className << "::Coordinates5:\n"
                  << "    No convergence achieved "
                  << "when refining internal isoparametric coordinates\n"
                  << "    at position (" << x << ", " << y << ").\n";
      }
      t1 = t2 = 0;
      return ifail;
    }
  }

  // Convergence reached.
  t1 = td1;
  t2 = td2;
  t3 = 0;
  t4 = 0;
  if (m_debug) {
    std::cout << "    Convergence reached at (t1, t2) = (" << t1 << ", " << t2
              << ").\n";
    // For debugging purposes, show position.
    f[0] = (-(1 - td1) * (1 - td2) * (1 + td1 + td2)) * 0.25;
    f[1] = (-(1 + td1) * (1 - td2) * (1 - td1 + td2)) * 0.25;
    f[2] = (-(1 + td1) * (1 + td2) * (1 - td1 - td2)) * 0.25;
    f[3] = (-(1 - td1) * (1 + td2) * (1 + td1 - td2)) * 0.25;
    f[4] = (1 - td1) * (1 + td1) * (1 - td2) * 0.5;
    f[5] = (1 + td1) * (1 + td2) * (1 - td2) * 0.5;
    f[6] = (1 - td1) * (1 + td1) * (1 + td2) * 0.5;
    f[7] = (1 - td1) * (1 + td2) * (1 - td2) * 0.5;
    double xr = 0., yr = 0.;
    for (size_t i = 0; i < 8; ++i) {
      xr += xn[i] * f[i];
      yr += yn[i] * f[i];
    }
    std::cout << "    Position requested:     (" << x << ", " << y << ")\n";
    std::cout << "    Reconstructed:          (" << xr << ", " << yr << ")\n";
    std::cout << "    Difference:             (" << x - xr << ", " << y - yr
              << ")\n";
  }

  // Success
  ifail = 0;
  return ifail;
}

std::array<std::array<double, 3>, 4> ComponentFieldMap::Weights12(
    const std::array<double, 10>& xn, const std::array<double, 10>& yn,
    const std::array<double, 10>& zn) {
  std::array<std::array<double, 3>, 4> w;
  w[0][0] =
      (yn[2] - yn[1]) * (zn[3] - zn[1]) - (yn[3] - yn[1]) * (zn[2] - zn[1]);
  w[0][1] =
      (zn[2] - zn[1]) * (xn[3] - xn[1]) - (zn[3] - zn[1]) * (xn[2] - xn[1]);
  w[0][2] =
      (xn[2] - xn[1]) * (yn[3] - yn[1]) - (xn[3] - xn[1]) * (yn[2] - yn[1]);
  const double s0 =
      1. / ((xn[0] - xn[1]) * w[0][0] + (yn[0] - yn[1]) * w[0][1] +
            (zn[0] - zn[1]) * w[0][2]);
  for (size_t i = 0; i < 3; ++i) w[0][i] *= s0;

  w[1][0] =
      (yn[0] - yn[2]) * (zn[3] - zn[2]) - (yn[3] - yn[2]) * (zn[0] - zn[2]);
  w[1][1] =
      (zn[0] - zn[2]) * (xn[3] - xn[2]) - (zn[3] - zn[2]) * (xn[0] - xn[2]);
  w[1][2] =
      (xn[0] - xn[2]) * (yn[3] - yn[2]) - (xn[3] - xn[2]) * (yn[0] - yn[2]);
  const double s1 =
      1. / ((xn[1] - xn[2]) * w[1][0] + (yn[1] - yn[2]) * w[1][1] +
            (zn[1] - zn[2]) * w[1][2]);
  for (size_t i = 0; i < 3; ++i) w[1][i] *= s1;

  w[2][0] =
      (yn[0] - yn[3]) * (zn[1] - zn[3]) - (yn[1] - yn[3]) * (zn[0] - zn[3]);
  w[2][1] =
      (zn[0] - zn[3]) * (xn[1] - xn[3]) - (zn[1] - zn[3]) * (xn[0] - xn[3]);
  w[2][2] =
      (xn[0] - xn[3]) * (yn[1] - yn[3]) - (xn[1] - xn[3]) * (yn[0] - yn[3]);
  const double s2 =
      1. / ((xn[2] - xn[3]) * w[2][0] + (yn[2] - yn[3]) * w[2][1] +
            (zn[2] - zn[3]) * w[2][2]);
  for (size_t i = 0; i < 3; ++i) w[2][i] *= s2;

  w[3][0] =
      (yn[2] - yn[0]) * (zn[1] - zn[0]) - (yn[1] - yn[0]) * (zn[2] - zn[0]);
  w[3][1] =
      (zn[2] - zn[0]) * (xn[1] - xn[0]) - (zn[1] - zn[0]) * (xn[2] - xn[0]);
  w[3][2] =
      (xn[2] - xn[0]) * (yn[1] - yn[0]) - (xn[1] - xn[0]) * (yn[2] - yn[0]);
  const double s3 =
      1. / ((xn[3] - xn[0]) * w[3][0] + (yn[3] - yn[0]) * w[3][1] +
            (zn[3] - zn[0]) * w[3][2]);
  for (size_t i = 0; i < 3; ++i) w[3][i] *= s3;
  return w;
}

void ComponentFieldMap::Coordinates12(
    const double x, const double y, const double z, double& t1, double& t2,
    double& t3, double& t4, const std::array<double, 10>& xn,
    const std::array<double, 10>& yn, const std::array<double, 10>& zn,
    const std::array<std::array<double, 3>, 4>& w) const {
  if (m_debug) {
    std::cout << m_className << "::Coordinates12:\n"
              << "   Point (" << x << ", " << y << ", " << z << ").\n";
  }

  // Compute tetrahedral coordinates.
  t1 = (x - xn[1]) * w[0][0] + (y - yn[1]) * w[0][1] + (z - zn[1]) * w[0][2];
  t2 = (x - xn[2]) * w[1][0] + (y - yn[2]) * w[1][1] + (z - zn[2]) * w[1][2];
  t3 = (x - xn[3]) * w[2][0] + (y - yn[3]) * w[2][1] + (z - zn[3]) * w[2][2];
  t4 = (x - xn[0]) * w[3][0] + (y - yn[0]) * w[3][1] + (z - zn[0]) * w[3][2];

  // Result.
  if (m_debug) {
    std::cout << "    Tetrahedral coordinates (t, u, v, w) = (" << t1 << ", "
              << t2 << ", " << t3 << ", " << t4
              << ") sum = " << t1 + t2 + t3 + t4 << ".\n";
    // Re-compute the (x,y,z) position for this coordinate.
    const double xr = xn[0] * t1 + xn[1] * t2 + xn[2] * t3 + xn[3] * t4;
    const double yr = yn[0] * t1 + yn[1] * t2 + yn[2] * t3 + yn[3] * t4;
    const double zr = zn[0] * t1 + zn[1] * t2 + zn[2] * t3 + zn[3] * t4;
    const double sr = t1 + t2 + t3 + t4;
    std::cout << "    Position requested:     (" << x << ", " << y << ", " << z
              << ")\n";
    std::cout << "    Reconstructed:          (" << xr << ", " << yr << ", "
              << zr << ")\n";
    std::cout << "    Difference:             (" << x - xr << ", " << y - yr
              << ", " << z - zr << ")\n";
    std::cout << "    Checksum - 1:           " << sr - 1 << "\n";
  }
}

int ComponentFieldMap::Coordinates13(
    const double x, const double y, const double z, double& t1, double& t2,
    double& t3, double& t4, double jac[4][4], double& det,
    const std::array<double, 10>& xn, const std::array<double, 10>& yn,
    const std::array<double, 10>& zn,
    const std::array<std::array<double, 3>, 4>& w) const {
  // Make a first order approximation.
  t1 = (x - xn[1]) * w[0][0] + (y - yn[1]) * w[0][1] + (z - zn[1]) * w[0][2];
  // Stop if we are far outside.
  if (t1 < -0.5 || t1 > 1.5) return 1;
  t2 = (x - xn[2]) * w[1][0] + (y - yn[2]) * w[1][1] + (z - zn[2]) * w[1][2];
  if (t2 < -0.5 || t2 > 1.5) return 1;
  t3 = (x - xn[3]) * w[2][0] + (y - yn[3]) * w[2][1] + (z - zn[3]) * w[2][2];
  if (t3 < -0.5 || t3 > 1.5) return 1;
  t4 = (x - xn[0]) * w[3][0] + (y - yn[0]) * w[3][1] + (z - zn[0]) * w[3][2];
  if (t4 < -0.5 || t4 > 1.5) return 1;

  // Start iteration.
  std::array<double, 4> td = {t1, t2, t3, t4};

  // Loop
  bool converged = false;
  for (int iter = 0; iter < 10; ++iter) {
    if (m_debug) {
      std::printf("    Iteration %4u: t = (%15.8f, %15.8f %15.8f %15.8f)\n",
                  iter, td[0], td[1], td[2], td[3]);
    }
    // Evaluate the shape functions and re-compute the (x,y,z) position
    // for this set of isoparametric coordinates.
    const double f0 = td[0] * (td[0] - 0.5);
    const double f1 = td[1] * (td[1] - 0.5);
    const double f2 = td[2] * (td[2] - 0.5);
    const double f3 = td[3] * (td[3] - 0.5);
    double xr = 2 * (f0 * xn[0] + f1 * xn[1] + f2 * xn[2] + f3 * xn[3]);
    double yr = 2 * (f0 * yn[0] + f1 * yn[1] + f2 * yn[2] + f3 * yn[3]);
    double zr = 2 * (f0 * zn[0] + f1 * zn[1] + f2 * zn[2] + f3 * zn[3]);
    const double fourt0 = 4 * td[0];
    const double fourt1 = 4 * td[1];
    const double fourt2 = 4 * td[2];
    const double fourt3 = 4 * td[3];
    const double f4 = fourt0 * td[1];
    const double f5 = fourt0 * td[2];
    const double f6 = fourt0 * td[3];
    const double f7 = fourt1 * td[2];
    const double f8 = fourt1 * td[3];
    const double f9 = fourt2 * td[3];
    xr += f4 * xn[4] + f5 * xn[5] + f6 * xn[6] + f7 * xn[7] + f8 * xn[8] +
          f9 * xn[9];
    yr += f4 * yn[4] + f5 * yn[5] + f6 * yn[6] + f7 * yn[7] + f8 * yn[8] +
          f9 * yn[9];
    zr += f4 * zn[4] + f5 * zn[5] + f6 * zn[6] + f7 * zn[7] + f8 * zn[8] +
          f9 * zn[9];
    // Compute the Jacobian.
    Jacobian13(xn, yn, zn, fourt0, fourt1, fourt2, fourt3, det, jac);
    // Compute the difference vector.
    const double sr = std::accumulate(td.cbegin(), td.cend(), 0.);
    const double diff[4] = {1. - sr, x - xr, y - yr, z - zr};
    // Update the estimate.
    double corr[4] = {0., 0., 0., 0.};
    for (size_t l = 0; l < 4; ++l) {
      for (size_t k = 0; k < 4; ++k) {
        corr[l] += jac[l][k] * diff[k];
      }
      corr[l] *= det;
      td[l] += corr[l];
    }

    // Debugging
    if (m_debug) {
      std::cout << "    Difference vector:  (1, x, y, z)  = (" << diff[0]
                << ", " << diff[1] << ", " << diff[2] << ", " << diff[3]
                << ").\n";
      std::cout << "    Correction vector:  (t1,t2,t3,t4) = (" << corr[0]
                << ", " << corr[1] << ", " << corr[2] << ", " << corr[3]
                << ").\n";
    }

    // Check for convergence.
    constexpr double tol = 1.e-5;
    if (fabs(corr[0]) < tol && fabs(corr[1]) < tol && fabs(corr[2]) < tol &&
        fabs(corr[3]) < tol) {
      if (m_debug) std::cout << "    Convergence reached.\n";
      converged = true;
      break;
    }
  }

  // No convergence reached.
  if (!converged) {
    const double xmin = std::min({xn[0], xn[1], xn[2], xn[3]});
    const double xmax = std::max({xn[0], xn[1], xn[2], xn[3]});
    const double ymin = std::min({yn[0], yn[1], yn[2], yn[3]});
    const double ymax = std::max({yn[0], yn[1], yn[2], yn[3]});
    const double zmin = std::min({zn[0], zn[1], zn[2], zn[3]});
    const double zmax = std::max({zn[0], zn[1], zn[2], zn[3]});
    if (x >= xmin && x <= xmax && y >= ymin && y <= ymax && z >= zmin &&
        z <= zmax) {
      if (m_printConvergenceWarnings) {
        std::cout << m_className << "::Coordinates13:\n"
                  << "    No convergence achieved "
                  << "when refining internal isoparametric coordinates\n"
                  << "    at position (" << x << ", " << y << ", " << z
                  << ").\n";
      }
      t1 = t2 = t3 = t4 = -1;
      return 1;
    }
  }

  // Convergence reached.
  t1 = td[0];
  t2 = td[1];
  t3 = td[2];
  t4 = td[3];
  if (m_debug) {
    std::cout << "    Convergence reached at (t1, t2, t3, t4) = (" << t1 << ", "
              << t2 << ", " << t3 << ", " << t4 << ").\n";
    // Re-compute the (x,y,z) position for this coordinate.
    const double f0 = td[0] * (td[0] - 0.5);
    const double f1 = td[1] * (td[1] - 0.5);
    const double f2 = td[2] * (td[2] - 0.5);
    const double f3 = td[3] * (td[3] - 0.5);
    double xr = 2 * (f0 * xn[0] + f1 * xn[1] + f2 * xn[2] + f3 * xn[3]);
    double yr = 2 * (f0 * yn[0] + f1 * yn[1] + f2 * yn[2] + f3 * yn[3]);
    double zr = 2 * (f0 * zn[0] + f1 * zn[1] + f2 * zn[2] + f3 * zn[3]);
    const double fourt0 = 4 * td[0];
    const double fourt1 = 4 * td[1];
    const double fourt2 = 4 * td[2];
    const double f4 = fourt0 * td[1];
    const double f5 = fourt0 * td[2];
    const double f6 = fourt0 * td[3];
    const double f7 = fourt1 * td[2];
    const double f8 = fourt1 * td[3];
    const double f9 = fourt2 * td[3];
    xr += f4 * xn[4] + f5 * xn[5] + f6 * xn[6] + f7 * xn[7] + f8 * xn[8] +
          f9 * xn[9];
    yr += f4 * yn[4] + f5 * yn[5] + f6 * yn[6] + f7 * yn[7] + f8 * yn[8] +
          f9 * yn[9];
    zr += f4 * zn[4] + f5 * zn[5] + f6 * zn[6] + f7 * zn[7] + f8 * zn[8] +
          f9 * zn[9];
    const double sr = std::accumulate(td.cbegin(), td.cend(), 0.);
    std::cout << "    Position requested:     (" << x << ", " << y << ", " << z
              << ")\n";
    std::cout << "    Reconstructed:          (" << xr << ", " << yr << ", "
              << zr << ")\n";
    std::cout << "    Difference:             (" << x - xr << ", " << y - yr
              << ", " << z - zr << ")\n";
    std::cout << "    Checksum - 1:           " << sr - 1 << "\n";
  }
  // Success
  return 0;
}

int ComponentFieldMap::CoordinatesCube(const double x, const double y,
                                       const double z, double& t1, double& t2,
                                       double& t3, TMatrixD*& jac,
                                       std::vector<TMatrixD*>& dN,
                                       const Element& element) const {
  /*
  global coordinates   7__ _ _ 6     t3    t2
                      /       /|     ^   /|
    ^ z              /       / |     |   /
    |               4_______5  |     |  /
    |              |        |  |     | /
    |              |  3     |  2     |/     t1
     ------->      |        | /       ------->
    /      y       |        |/       local coordinates
   /               0--------1
  /
 v x
 */

  const Node& n0 = m_nodes[element.emap[0]];
  const Node& n2 = m_nodes[element.emap[2]];
  const Node& n3 = m_nodes[element.emap[3]];
  const Node& n7 = m_nodes[element.emap[7]];

  // Compute hexahedral coordinates (t1->[-1,1],t2->[-1,1],t3->[-1,1]) and
  // t1 (zeta) is in y-direction
  // t2 (eta)  is in opposite x-direction
  // t3 (mu)   is in z-direction
  // Nodes are set in that way, that node [0] has always lowest x,y,z!
  t2 = (2. * (x - n3.x) / (n0.x - n3.x) - 1) * -1.;
  t1 = 2. * (y - n3.y) / (n2.y - n3.y) - 1;
  t3 = 2. * (z - n3.z) / (n7.z - n3.z) - 1;
  // Re-compute the (x,y,z) position for this coordinate.
  if (m_debug) {
    double n[8];
    n[0] = 1. / 8 * (1 - t1) * (1 - t2) * (1 - t3);
    n[1] = 1. / 8 * (1 + t1) * (1 - t2) * (1 - t3);
    n[2] = 1. / 8 * (1 + t1) * (1 + t2) * (1 - t3);
    n[3] = 1. / 8 * (1 - t1) * (1 + t2) * (1 - t3);
    n[4] = 1. / 8 * (1 - t1) * (1 - t2) * (1 + t3);
    n[5] = 1. / 8 * (1 + t1) * (1 - t2) * (1 + t3);
    n[6] = 1. / 8 * (1 + t1) * (1 + t2) * (1 + t3);
    n[7] = 1. / 8 * (1 - t1) * (1 + t2) * (1 + t3);

    double xr = 0;
    double yr = 0;
    double zr = 0;

    for (int i = 0; i < 8; i++) {
      const Node& node = m_nodes[element.emap[i]];
      xr += node.x * n[i];
      yr += node.y * n[i];
      zr += node.z * n[i];
    }
    double sr = n[0] + n[1] + n[2] + n[3] + n[4] + n[5] + n[6] + n[7];
    std::cout << m_className << "::CoordinatesCube:\n";
    std::cout << "    Position requested:     (" << x << "," << y << "," << z
              << ")\n";
    std::cout << "    Position reconstructed: (" << xr << "," << yr << "," << zr
              << ")\n";
    std::cout << "    Difference:             (" << (x - xr) << "," << (y - yr)
              << "," << (z - zr) << ")\n";
    std::cout << "    Hexahedral coordinates (t, u, v) = (" << t1 << "," << t2
              << "," << t3 << ")\n";
    std::cout << "    Checksum - 1:           " << (sr - 1) << "\n";
  }
  if (jac != 0) JacobianCube(element, t1, t2, t3, jac, dN);
  // This should always work.
  return 0;
}

void ComponentFieldMap::Reset() {
  m_ready = false;

  m_elements.clear();
  m_degenerate.clear();
  m_bbMin.clear();
  m_bbMax.clear();
  m_w12.clear();
  m_nodes.clear();
  m_pot.clear();
  m_wpot.clear();
  m_dwpot.clear();
  m_wfieldCopies.clear();
  m_materials.clear();
  m_hasBoundingBox = false;
  m_warning = false;
  m_nWarnings = 0;

  m_octree.reset(nullptr);
  m_cacheElemBoundingBoxes = false;
}

void ComponentFieldMap::Prepare() {
  // Establish the ranges.
  SetRange();
  UpdatePeriodicity();
  std::cout << m_className << "::Prepare:\n"
            << "    Caching the bounding boxes of all elements...";
  CalculateElementBoundingBoxes();
  std::cout << " done.\n";
  // Initialize the tetrahedral tree.
  if (InitializeTetrahedralTree()) {
    std::cout << "    Initialized tetrahedral tree.\n";
  }
  m_elementIndices.resize(m_elements.size());
  std::iota(m_elementIndices.begin(), m_elementIndices.end(), 0);
  // Precompute terms for interpolation in linear tetrahedra.
  if (m_elementType == ElementType::CurvedTetrahedron) {
    std::array<double, 10> xn;
    std::array<double, 10> yn;
    std::array<double, 10> zn;
    for (const auto& element : m_elements) {
      for (size_t j = 0; j < 10; ++j) {
        const auto& node = m_nodes[element.emap[j]];
        xn[j] = node.x;
        yn[j] = node.y;
        zn[j] = node.z;
      }
      m_w12.emplace_back(Weights12(xn, yn, zn));
    }
  }
}

void ComponentFieldMap::UpdatePeriodicityCommon() {
  // Check the required data is available.
  if (!m_ready) {
    PrintNotReady("UpdatePeriodicityCommon");
    return;
  }

  for (size_t i = 0; i < 3; ++i) {
    const Symmetry sym = m_symmetries.GetSymmetries(i);
    // No regular and mirror periodicity at the same time.
    if (sym.Has(Symmetry::Type::Periodic) && sym.Has(Symmetry::Type::Mirror)) {
      std::cerr << m_className << "::UpdatePeriodicityCommon:\n"
                << "    Both simple and mirror periodicity requested. Reset.\n";
      m_symmetries.Deactivate(static_cast<Symmetry::Type>(
          static_cast<std::size_t>(Symmetry::Type::PeriodicX) << i));
      m_symmetries.Deactivate(static_cast<Symmetry::Type>(
          static_cast<std::size_t>(Symmetry::Type::MirrorX) << i));
      m_warning = true;
    }
    // In case of axial periodicity,
    // the range must be an integral part of two pi.
    if (m_symmetries.Has(Symmetry::Type::Axial)) {
      if (m_mapamin[i] >= m_mapamax[i]) {
        m_mapna[i] = 0;
      } else {
        m_mapna[i] = TwoPi / (m_mapamax[i] - m_mapamin[i]);
      }
      if (fabs(m_mapna[i] - int(0.5 + m_mapna[i])) > 0.001 ||
          m_mapna[i] < 1.5) {
        std::cerr << m_className << "::UpdatePeriodicityCommon:\n"
                  << "    Axial symmetry has been requested but map does not\n"
                  << "    cover an integral fraction of 2 pi. Reset.\n";
        m_symmetries.Deactivate(static_cast<Symmetry::Type>(
            static_cast<std::size_t>(Symmetry::Type::AxialX) << i));
        m_warning = true;
      }
    }
  }

  // Not more than 1 rotational symmetry
  if (m_symmetries.NumberOf(Symmetry::Type::Mirror) > 1) {
    std::cerr << m_className << "::UpdatePeriodicityCommon:\n"
              << "    Only one rotational symmetry allowed; reset.\n";

    m_symmetries.Deactivate(Symmetry::Type::Rotation);
    m_warning = true;
  }

  // No rotational symmetry as well as axial periodicity
  if (m_symmetries.Has(Symmetry::Type::Rotation) &&
      m_symmetries.Has(Symmetry::Type::Axial)) {
    std::cerr << m_className << "::UpdatePeriodicityCommon:\n"
              << "    Not allowed to combine rotational symmetry\n"
              << "    and axial periodicity; reset.\n";
    m_symmetries.Deactivate(Symmetry::Type::Rotation);
    m_symmetries.Deactivate(Symmetry::Type::Axial);
    m_warning = true;
  }

  // In case of rotational symmetry, the x-range should not straddle 0.
  if (m_symmetries.Has(Symmetry::Type::Rotation)) {
    if (m_mapmin[0] * m_mapmax[0] < 0) {
      std::cerr << m_className << "::UpdatePeriodicityCommon:\n"
                << "    Rotational symmetry requested, \n"
                << "    but x-range straddles 0; reset.\n";
      m_symmetries.Deactivate(Symmetry::Type::Rotation);
      m_warning = true;
    }
  }

  // Triangle symmetry
  const std::size_t triSymmN = m_symmetries.NumberOf(Symmetry::Type::Triangle);
  // Check octant setting
  if (triSymmN == 1) {
    if (m_triangleSymmetricOct < 1 || m_triangleSymmetricOct > 8) {
      std::cerr << m_className << "::UpdatePeriodicityCommon:\n"
                << "    For triangle symmetry octant needs to be in "
                << "the range 1 - 8; reset.\n";
      m_symmetries.Deactivate(Symmetry::Type::Rotation);
      m_symmetries.Deactivate(Symmetry::Type::Triangle);
      m_triangleSymmetricOct = 0;
      m_warning = true;
    } else {
      m_outsideCone = (m_triangleOctRules[0] == m_triangleSymmetricOct) ||
                      (m_triangleOctRules[1] == m_triangleSymmetricOct) ||
                      (m_triangleOctRules[2] == m_triangleSymmetricOct) ||
                      (m_triangleOctRules[3] == m_triangleSymmetricOct);
    }
  }
  // Not more than 1 triangle symmetry
  if (triSymmN > 1) {
    std::cerr << m_className << "::UpdatePeriodicityCommon:\n"
              << "    Only one triangle symmetry allowed; reset.\n";
    m_symmetries.Deactivate(Symmetry::Type::Periodic);
    m_symmetries.Deactivate(Symmetry::Type::Triangle);
    m_triangleSymmetricOct = 0;
    m_warning = true;
  }

  // Recompute the cell ranges.
  for (size_t i = 0; i < 3; ++i) {
    m_minBoundingBox[i] = m_mapmin[i];
    m_maxBoundingBox[i] = m_mapmax[i];
    m_cells[i] = fabs(m_mapmax[i] - m_mapmin[i]);
  }
  for (size_t i = 0; i < 3; ++i) {
    const Symmetry sym = m_symmetries.GetSymmetries(i);
    if (!sym.Has(Symmetry::Type::Rotation)) continue;
    const double r = std::max(fabs(m_mapmin[0]), fabs(m_mapmax[0]));
    m_minBoundingBox.fill(-r);
    m_maxBoundingBox.fill(+r);
    m_minBoundingBox[i] = m_mapmin[1];
    m_maxBoundingBox[i] = m_mapmax[1];
    break;
  }

  if (m_symmetries.Has(Symmetry::Type::AxialX)) {
    const double yzmax = std::max({fabs(m_mapmin[1]), fabs(m_mapmax[1]),
                                   fabs(m_mapmin[2]), fabs(m_mapmax[2])});
    m_minBoundingBox[1] = -yzmax;
    m_maxBoundingBox[1] = +yzmax;
    m_minBoundingBox[2] = -yzmax;
    m_maxBoundingBox[2] = +yzmax;
  } else if (m_symmetries.Has(Symmetry::Type::AxialY)) {
    const double xzmax = std::max({fabs(m_mapmin[0]), fabs(m_mapmax[0]),
                                   fabs(m_mapmin[2]), fabs(m_mapmax[2])});
    m_minBoundingBox[0] = -xzmax;
    m_maxBoundingBox[0] = +xzmax;
    m_minBoundingBox[2] = -xzmax;
    m_maxBoundingBox[2] = +xzmax;
  } else if (m_symmetries.Has(Symmetry::Type::AxialZ)) {
    const double xymax = std::max({fabs(m_mapmin[0]), fabs(m_mapmax[0]),
                                   fabs(m_mapmin[1]), fabs(m_mapmax[1])});
    m_minBoundingBox[0] = -xymax;
    m_maxBoundingBox[0] = +xymax;
    m_minBoundingBox[1] = -xymax;
    m_maxBoundingBox[1] = +xymax;
  }

  for (size_t i = 0; i < 3; ++i) {
    const Symmetry sym = m_symmetries.GetSymmetries(i);
    if (sym.Has(Symmetry::Type::Periodic) || sym.Has(Symmetry::Type::Mirror)) {
      m_minBoundingBox[i] = -INFINITY;
      m_maxBoundingBox[i] = +INFINITY;
    }
  }

  // Display the range if requested.
  if (m_debug) PrintRange();
}

void ComponentFieldMap::UpdatePeriodicity2d() {
  // Check the required data is available.
  if (!m_ready) {
    PrintNotReady("UpdatePeriodicity2d");
    return;
  }

  // No z-periodicity in 2d
  if (m_symmetries.Has(Symmetry::Type::PeriodicZ) ||
      m_symmetries.Has(Symmetry::Type::MirrorZ)) {
    std::cerr << m_className << "::UpdatePeriodicity2d:\n"
              << "    Simple or mirror periodicity along z\n"
              << "    requested for a 2d map; reset.\n";
    m_symmetries.Deactivate(Symmetry::Type::PeriodicZ);
    m_symmetries.Deactivate(Symmetry::Type::MirrorZ);
    m_warning = true;
  }

  // Only z-axial periodicity in 2d maps
  if (m_symmetries.Has(Symmetry::Type::AxialX) ||
      m_symmetries.Has(Symmetry::Type::AxialY)) {
    std::cerr << m_className << "::UpdatePeriodicity2d:\n"
              << "    Axial symmetry has been requested \n"
              << "    around x or y for a 2d map; reset.\n";
    m_symmetries.Deactivate(Symmetry::Type::AxialX);
    m_symmetries.Deactivate(Symmetry::Type::AxialY);
    m_warning = true;
  }

  // No xz or yz-planes in 2d
  if (m_symmetries.Has(Symmetry::Type::TriangleXZ) ||
      m_symmetries.Has(Symmetry::Type::TriangleYZ)) {
    std::cerr << m_className << "::UpdatePeriodicity2d:\n"
              << "    triangle periodicity does not allow\n"
              << "    for xz or yz planes; reset.\n";
    m_symmetries.Deactivate(Symmetry::Type::Triangle);
    m_symmetries.Deactivate(Symmetry::Type::Periodic);
    m_triangleSymmetricOct = 0;
    m_warning = true;
  }
}

void ComponentFieldMap::SetRange() {
  // Initial values
  m_mapmin.fill(0.);
  m_mapmax.fill(0.);
  m_mapamin.fill(0.);
  m_mapamax.fill(0.);
  m_mapvmin = m_mapvmax = 0.;
  m_setang.fill(false);

  // Make sure the required data is available.
  if (!m_ready || m_nodes.empty()) {
    std::cerr << m_className << "::SetRange: Field map not yet set.\n";
    return;
  }

  m_mapvmin = *std::min_element(std::begin(m_pot), std::end(m_pot));
  m_mapvmax = *std::max_element(std::begin(m_pot), std::end(m_pot));

  // Loop over the nodes.
  m_mapmin[0] = m_mapmax[0] = m_nodes[0].x;
  m_mapmin[1] = m_mapmax[1] = m_nodes[0].y;
  m_mapmin[2] = m_mapmax[2] = m_nodes[0].z;

  for (const auto& node : m_nodes) {
    const std::array<double, 3> pos = {{node.x, node.y, node.z}};
    for (std::size_t i = 0; i < 3; ++i) {
      m_mapmin[i] = std::min(m_mapmin[i], pos[i]);
      m_mapmax[i] = std::max(m_mapmax[i], pos[i]);
    }

    if (node.y != 0 || node.z != 0) {
      const double ang = atan2(node.z, node.y);
      if (m_setang[0]) {
        m_mapamin[0] = std::min(m_mapamin[0], ang);
        m_mapamax[0] = std::max(m_mapamax[0], ang);
      } else {
        m_mapamin[0] = m_mapamax[0] = ang;
        m_setang[0] = true;
      }
    }

    if (node.z != 0 || node.x != 0) {
      const double ang = atan2(node.x, node.z);
      if (m_setang[1]) {
        m_mapamin[1] = std::min(m_mapamin[1], ang);
        m_mapamax[1] = std::max(m_mapamax[1], ang);
      } else {
        m_mapamin[1] = m_mapamax[1] = ang;
        m_setang[1] = true;
      }
    }

    if (node.x != 0 || node.y != 0) {
      const double ang = atan2(node.y, node.x);
      if (m_setang[2]) {
        m_mapamin[2] = std::min(m_mapamin[2], ang);
        m_mapamax[2] = std::max(m_mapamax[2], ang);
      } else {
        m_mapamin[2] = m_mapamax[2] = ang;
        m_setang[2] = true;
      }
    }
  }

  // Fix the angular ranges.
  for (std::size_t i = 0; i < 3; ++i) {
    if (m_mapamax[i] - m_mapamin[i] > Pi) {
      const double aux = m_mapamin[i];
      m_mapamin[i] = m_mapamax[i];
      m_mapamax[i] = aux + TwoPi;
    }
  }

  // Set provisional cell dimensions.
  m_minBoundingBox[0] = m_mapmin[0];
  m_maxBoundingBox[0] = m_mapmax[0];
  m_minBoundingBox[1] = m_mapmin[1];
  m_maxBoundingBox[1] = m_mapmax[1];
  if (m_is3d) {
    m_minBoundingBox[2] = m_mapmin[2];
    m_maxBoundingBox[2] = m_mapmax[2];
  } else {
    m_mapmin[2] = m_minBoundingBox[2];
    m_mapmax[2] = m_maxBoundingBox[2];
  }
  m_hasBoundingBox = true;

  // Display the range if requested.
  if (m_debug) PrintRange();
}

void ComponentFieldMap::PrintRange() {
  std::cout << m_className << "::PrintRange:\n";
  std::cout << "        Dimensions of the elementary block\n";
  printf("            %15g < x < %-15g cm,\n", m_mapmin[0], m_mapmax[0]);
  printf("            %15g < y < %-15g cm,\n", m_mapmin[1], m_mapmax[1]);
  printf("            %15g < z < %-15g cm,\n", m_mapmin[2], m_mapmax[2]);
  printf("            %15g < V < %-15g V.\n", m_mapvmin, m_mapvmax);

  std::cout << "        Periodicities\n";
  const std::array<std::string, 3> axes = {{"x", "y", "z"}};
  for (std::size_t i = 0; i < 3; ++i) {
    std::cout << "            " << axes[i] << ":";
    if (m_symmetries.Has(static_cast<Symmetry::Type>(
            static_cast<std::size_t>(Symmetry::Type::PeriodicX) << i))) {
      std::cout << " simple with length " << m_cells[i] << " cm";
    }
    if (m_symmetries.Has(static_cast<Symmetry::Type>(
            static_cast<std::size_t>(Symmetry::Type::MirrorX) << i))) {
      std::cout << " mirror with length " << m_cells[i] << " cm";
    }
    if (m_symmetries.Has(static_cast<Symmetry::Type>(
            static_cast<std::size_t>(Symmetry::Type::AxialX) << i))) {
      std::cout << " axial " << int(0.5 + m_mapna[i]) << "-fold repetition";
    }
    if (m_symmetries.Has(static_cast<Symmetry::Type>(
            static_cast<std::size_t>(Symmetry::Type::RotationX) << i)))
      std::cout << " rotational symmetry";
    if (!(m_symmetries.Has(static_cast<Symmetry::Type>(
              static_cast<std::size_t>(Symmetry::Type::PeriodicX) << i)) ||
          m_symmetries.Has(static_cast<Symmetry::Type>(
              static_cast<std::size_t>(Symmetry::Type::MirrorX) << i)) ||
          m_symmetries.Has(static_cast<Symmetry::Type>(
              static_cast<std::size_t>(Symmetry::Type::AxialX) << i)) ||
          m_symmetries.Has(static_cast<Symmetry::Type>(
              static_cast<std::size_t>(Symmetry::Type::RotationX) << i))))
      std::cout << " none";
    std::cout << "\n";
  }

  // triangle symmetry check
  if (m_symmetries.Has(Symmetry::Type::Triangle)) {
    const std::array<std::string, 3> planes = {{"xy", "xz", "yz"}};
    for (std::size_t i = 0; i < 3; ++i) {
      if (m_symmetries.Has(static_cast<Symmetry::Type>(
              static_cast<std::size_t>(Symmetry::Type::TriangleXY) << i))) {
        std::cout << "            " << planes[i] << "-plane:";
        std::cout << " triangle with right sides of " << m_cells[i] << " cm";
      }
    }
    std::cout << "\n";
  }
}

bool ComponentFieldMap::GetBoundingBox(double& xmin, double& ymin, double& zmin,
                                       double& xmax, double& ymax,
                                       double& zmax) {
  if (!m_ready) return false;

  xmin = m_minBoundingBox[0];
  xmax = m_maxBoundingBox[0];
  ymin = m_minBoundingBox[1];
  ymax = m_maxBoundingBox[1];
  zmin = m_minBoundingBox[2];
  zmax = m_maxBoundingBox[2];
  return true;
}

bool ComponentFieldMap::GetElementaryCell(double& xmin, double& ymin,
                                          double& zmin, double& xmax,
                                          double& ymax, double& zmax) {
  if (!m_ready) return false;
  xmin = m_mapmin[0];
  xmax = m_mapmax[0];
  ymin = m_mapmin[1];
  ymax = m_mapmax[1];
  zmin = m_mapmin[2];
  zmax = m_mapmax[2];
  return true;
}

void ComponentFieldMap::MapCoordinates(double& xpos, double& ypos, double& zpos,
                                       bool& xmirrored, bool& ymirrored,
                                       bool& zmirrored, double& rcoordinate,
                                       double& rotation) const {
  // Initial values
  rotation = 0;

  // If chamber is periodic, reduce to the cell volume.
  xmirrored = false;
  if (m_symmetries.Has(Symmetry::Type::PeriodicX)) {
    const double xrange = m_mapmax[0] - m_mapmin[0];
    xpos = m_mapmin[0] + fmod(xpos - m_mapmin[0], xrange);
    if (xpos < m_mapmin[0]) xpos += xrange;
  } else if (m_symmetries.Has(Symmetry::Type::MirrorX)) {
    const double xrange = m_mapmax[0] - m_mapmin[0];
    double xnew = m_mapmin[0] + fmod(xpos - m_mapmin[0], xrange);
    if (xnew < m_mapmin[0]) xnew += xrange;
    int nx = int(floor(0.5 + (xnew - xpos) / xrange));
    if (nx != 2 * (nx / 2)) {
      xnew = m_mapmin[0] + m_mapmax[0] - xnew;
      xmirrored = true;
    }
    xpos = xnew;
  }
  if (m_symmetries.Has(Symmetry::Type::AxialX) && (zpos != 0 || ypos != 0)) {
    const double auxr = sqrt(zpos * zpos + ypos * ypos);
    double auxphi = atan2(zpos, ypos);
    const double phirange = m_mapamax[0] - m_mapamin[0];
    const double phim = 0.5 * (m_mapamin[0] + m_mapamax[0]);
    rotation = phirange * floor(0.5 + (auxphi - phim) / phirange);
    if (auxphi - rotation < m_mapamin[0]) rotation -= phirange;
    if (auxphi - rotation > m_mapamax[0]) rotation += phirange;
    auxphi = auxphi - rotation;
    ypos = auxr * cos(auxphi);
    zpos = auxr * sin(auxphi);
  }

  ymirrored = false;
  if (m_symmetries.Has(Symmetry::Type::PeriodicY)) {
    const double yrange = m_mapmax[1] - m_mapmin[1];
    ypos = m_mapmin[1] + fmod(ypos - m_mapmin[1], yrange);
    if (ypos < m_mapmin[1]) ypos += yrange;
  } else if (m_symmetries.Has(Symmetry::Type::MirrorY)) {
    const double yrange = m_mapmax[1] - m_mapmin[1];
    double ynew = m_mapmin[1] + fmod(ypos - m_mapmin[1], yrange);
    if (ynew < m_mapmin[1]) ynew += yrange;
    int ny = int(floor(0.5 + (ynew - ypos) / yrange));
    if (ny != 2 * (ny / 2)) {
      ynew = m_mapmin[1] + m_mapmax[1] - ynew;
      ymirrored = true;
    }
    ypos = ynew;
  }
  if (m_symmetries.Has(Symmetry::Type::AxialY) && (xpos != 0 || zpos != 0)) {
    const double auxr = sqrt(xpos * xpos + zpos * zpos);
    double auxphi = atan2(xpos, zpos);
    const double phirange = (m_mapamax[1] - m_mapamin[1]);
    const double phim = 0.5 * (m_mapamin[1] + m_mapamax[1]);
    rotation = phirange * floor(0.5 + (auxphi - phim) / phirange);
    if (auxphi - rotation < m_mapamin[1]) rotation -= phirange;
    if (auxphi - rotation > m_mapamax[1]) rotation += phirange;
    auxphi = auxphi - rotation;
    zpos = auxr * cos(auxphi);
    xpos = auxr * sin(auxphi);
  }

  zmirrored = false;
  if (m_symmetries.Has(Symmetry::Type::PeriodicZ)) {
    const double zrange = m_mapmax[2] - m_mapmin[2];
    zpos = m_mapmin[2] + fmod(zpos - m_mapmin[2], zrange);
    if (zpos < m_mapmin[2]) zpos += zrange;
  } else if (m_symmetries.Has(Symmetry::Type::MirrorZ)) {
    const double zrange = m_mapmax[2] - m_mapmin[2];
    double znew = m_mapmin[2] + fmod(zpos - m_mapmin[2], zrange);
    if (znew < m_mapmin[2]) znew += zrange;
    int nz = int(floor(0.5 + (znew - zpos) / zrange));
    if (nz != 2 * (nz / 2)) {
      znew = m_mapmin[2] + m_mapmax[2] - znew;
      zmirrored = true;
    }
    zpos = znew;
  }
  if (m_symmetries.Has(Symmetry::Type::AxialZ) && (ypos != 0 || xpos != 0)) {
    const double auxr = sqrt(ypos * ypos + xpos * xpos);
    double auxphi = atan2(ypos, xpos);
    const double phirange = m_mapamax[2] - m_mapamin[2];
    const double phim = 0.5 * (m_mapamin[2] + m_mapamax[2]);
    rotation = phirange * floor(0.5 + (auxphi - phim) / phirange);
    if (auxphi - rotation < m_mapamin[2]) rotation -= phirange;
    if (auxphi - rotation > m_mapamax[2]) rotation += phirange;
    auxphi = auxphi - rotation;
    xpos = auxr * cos(auxphi);
    ypos = auxr * sin(auxphi);
  }

  // If we have a rotationally symmetric field map, store coordinates.
  rcoordinate = 0;
  double zcoordinate = 0;
  if (m_symmetries.Has(Symmetry::Type::RotationX)) {
    rcoordinate = sqrt(ypos * ypos + zpos * zpos);
    zcoordinate = xpos;
  } else if (m_symmetries.Has(Symmetry::Type::RotationY)) {
    rcoordinate = sqrt(xpos * xpos + zpos * zpos);
    zcoordinate = ypos;
  } else if (m_symmetries.Has(Symmetry::Type::RotationZ)) {
    rcoordinate = sqrt(xpos * xpos + ypos * ypos);
    zcoordinate = zpos;
  }

  if (m_symmetries.Has(Symmetry::Type::Rotation)) {
    xpos = rcoordinate;
    ypos = zcoordinate;
    zpos = 0;
  }

  if (m_symmetries.Has(Symmetry::Type::Triangle)) {
    const double pH[2] = {xpos, ypos};
    bool triSwap = false;
    double prefixH = 1.;

    if (m_outsideCone) {
      prefixH = (m_triangleSymmetricOct % 2 == 0) ? -1 : 1;
      if (std::abs(xpos) < std::abs(ypos)) triSwap = true;
    } else {
      prefixH = (m_triangleSymmetricOct % 2 == 0) ? 1 : -1;
      if (std::abs(xpos) > std::abs(ypos)) triSwap = true;
    }

    if (triSwap) {
      if (m_symmetries.Has(Symmetry::Type::TriangleXY)) {
        xpos = prefixH * ypos;
        ypos = prefixH * pH[0];
      } else if (m_symmetries.Has(Symmetry::Type::TriangleXZ)) {
        xpos = prefixH * zpos;
        zpos = prefixH * pH[0];
      } else {
        ypos = prefixH * zpos;
        zpos = prefixH * pH[1];
      }
    }
  }
}

void ComponentFieldMap::UnmapFields(double& ex, double& ey, double& ez,
                                    const double xpos, const double ypos,
                                    const double zpos, const bool xmirrored,
                                    const bool ymirrored, const bool zmirrored,
                                    const double rcoordinate,
                                    const double rotation) const {
  // Apply mirror imaging.
  if (xmirrored) ex = -ex;
  if (ymirrored) ey = -ey;
  if (zmirrored) ez = -ez;

  // Rotate the field.
  double er, theta;
  if (m_symmetries.Has(Symmetry::Type::AxialX)) {
    er = sqrt(ey * ey + ez * ez);
    theta = atan2(ez, ey);
    theta += rotation;
    ey = er * cos(theta);
    ez = er * sin(theta);
  }
  if (m_symmetries.Has(Symmetry::Type::AxialY)) {
    er = sqrt(ez * ez + ex * ex);
    theta = atan2(ex, ez);
    theta += rotation;
    ez = er * cos(theta);
    ex = er * sin(theta);
  }
  if (m_symmetries.Has(Symmetry::Type::AxialZ)) {
    er = sqrt(ex * ex + ey * ey);
    theta = atan2(ey, ex);
    theta += rotation;
    ex = er * cos(theta);
    ey = er * sin(theta);
  }

  // Take care of symmetry.
  double eaxis;
  er = ex;
  eaxis = ey;

  // Rotational symmetry
  if (m_symmetries.Has(Symmetry::Type::RotationX)) {
    if (rcoordinate <= 0) {
      ex = eaxis;
      ey = 0;
      ez = 0;
    } else {
      ex = eaxis;
      ey = er * ypos / rcoordinate;
      ez = er * zpos / rcoordinate;
    }
  }
  if (m_symmetries.Has(Symmetry::Type::RotationY)) {
    if (rcoordinate <= 0) {
      ex = 0;
      ey = eaxis;
      ez = 0;
    } else {
      ex = er * xpos / rcoordinate;
      ey = eaxis;
      ez = er * zpos / rcoordinate;
    }
  }
  if (m_symmetries.Has(Symmetry::Type::RotationZ)) {
    if (rcoordinate <= 0) {
      ex = 0;
      ey = 0;
      ez = eaxis;
    } else {
      ex = er * xpos / rcoordinate;
      ey = er * ypos / rcoordinate;
      ez = eaxis;
    }
  }
}

double ComponentFieldMap::ScalingFactor(std::string unit) {
  std::transform(unit.begin(), unit.end(), unit.begin(), toupper);
  if (unit == "MUM" || unit == "MICRON" || unit == "MICROMETER") {
    return 0.0001;
  } else if (unit == "MM" || unit == "MILLIMETER") {
    return 0.1;
  } else if (unit == "CM" || unit == "CENTIMETER") {
    return 1.0;
  } else if (unit == "M" || unit == "METER") {
    return 100.0;
  }
  return -1.;
}

int ComponentFieldMap::ReadInteger(char* token, int def, bool& error) {
  if (!token) {
    error = true;
    return def;
  }

  return atoi(token);
}

double ComponentFieldMap::ReadDouble(char* token, double def, bool& error) {
  if (!token) {
    error = true;
    return def;
  }
  return atof(token);
}

void ComponentFieldMap::CalculateElementBoundingBoxes() {
  // Do not proceed if not properly initialised.
  if (!m_ready) {
    PrintNotReady("CalculateElementBoundingBoxes");
    return;
  }

  // Calculate the bounding boxes of all elements.
  const size_t nElements = m_elements.size();
  m_bbMin.resize(nElements);
  m_bbMax.resize(nElements);
  for (size_t i = 0; i < nElements; ++i) {
    const auto& element = m_elements[i];
    const Node& n0 = m_nodes[element.emap[0]];
    const Node& n1 = m_nodes[element.emap[1]];
    const Node& n2 = m_nodes[element.emap[2]];
    const Node& n3 = m_nodes[element.emap[3]];
    m_bbMin[i][0] = std::min({n0.x, n1.x, n2.x, n3.x});
    m_bbMax[i][0] = std::max({n0.x, n1.x, n2.x, n3.x});
    m_bbMin[i][1] = std::min({n0.y, n1.y, n2.y, n3.y});
    m_bbMax[i][1] = std::max({n0.y, n1.y, n2.y, n3.y});
    m_bbMin[i][2] = std::min({n0.z, n1.z, n2.z, n3.z});
    m_bbMax[i][2] = std::max({n0.z, n1.z, n2.z, n3.z});
    // Add tolerances.
    constexpr double f = 0.2;
    const double tolx = f * (m_bbMax[i][0] - m_bbMin[i][0]);
    m_bbMin[i][0] -= tolx;
    m_bbMax[i][0] += tolx;
    const double toly = f * (m_bbMax[i][1] - m_bbMin[i][1]);
    m_bbMin[i][1] -= toly;
    m_bbMax[i][1] += toly;
    const double tolz = f * (m_bbMax[i][2] - m_bbMin[i][2]);
    m_bbMin[i][2] -= tolz;
    m_bbMax[i][2] += tolz;
  }
}

bool ComponentFieldMap::InitializeTetrahedralTree() {
  // Do not proceed if not properly initialised.
  if (!m_ready) {
    PrintNotReady("InitializeTetrahedralTree");
    return false;
  }

  if (m_debug) {
    std::cout << m_className << "::InitializeTetrahedralTree:\n"
              << "    About to initialize the tetrahedral tree.\n";
  }

  // Cache the bounding boxes if it has not been done yet.
  if (!m_cacheElemBoundingBoxes) CalculateElementBoundingBoxes();

  if (m_nodes.empty()) {
    std::cerr << m_className << "::InitializeTetrahedralTree: Empty mesh.\n";
    return false;
  }

  // Determine the bounding box
  auto xmin = m_nodes.front().x;
  auto ymin = m_nodes.front().y;
  auto zmin = m_nodes.front().z;
  auto xmax = xmin;
  auto ymax = ymin;
  auto zmax = zmin;
  for (const auto& node : m_nodes) {
    xmin = std::min(xmin, node.x);
    xmax = std::max(xmax, node.x);
    ymin = std::min(ymin, node.y);
    ymax = std::max(ymax, node.y);
    zmin = std::min(zmin, node.z);
    zmax = std::max(zmax, node.z);
  }

  if (m_debug) {
    std::cout << "    Bounding box:\n"
              << std::scientific << "\tx: " << xmin << " -> " << xmax << "\n"
              << std::scientific << "\ty: " << ymin << " -> " << ymax << "\n"
              << std::scientific << "\tz: " << zmin << " -> " << zmax << "\n";
  }

  const double hx = 0.5 * (xmax - xmin);
  const double hy = 0.5 * (ymax - ymin);
  const double hz = 0.5 * (zmax - zmin);
  m_octree.reset(new TetrahedralTree(Vec3(xmin + hx, ymin + hy, zmin + hz),
                                     Vec3(hx, hy, hz)));

  if (m_debug) std::cout << "    Tree instantiated.\n";

  // Insert all mesh nodes in the tree
  for (std::size_t i = 0; i < m_nodes.size(); i++) {
    const Node& n = m_nodes[i];
    m_octree->InsertMeshNode(Vec3(n.x, n.y, n.z), i);
  }

  if (m_debug) std::cout << "    Tree nodes initialized successfully.\n";

  // Insert all mesh elements (tetrahedrons) in the tree
  for (std::size_t i = 0; i < m_elements.size(); i++) {
    const double bb[6] = {m_bbMin[i][0], m_bbMin[i][1], m_bbMin[i][2],
                          m_bbMax[i][0], m_bbMax[i][1], m_bbMax[i][2]};
    m_octree->InsertMeshElement(bb, i);
  }
  return true;
}

void ComponentFieldMap::PrintWarning(const std::string& header) {
  if (!m_warning || m_nWarnings > 10) return;
  std::cerr << m_className << "::" << header << ":\n"
            << "    Warnings have been issued for this field map.\n";
  ++m_nWarnings;
}

void ComponentFieldMap::PrintNotReady(const std::string& header) const {
  std::cerr << m_className << "::" << header << ":\n"
            << "    Field map not yet initialised.\n";
}

void ComponentFieldMap::PrintCouldNotOpen(const std::string& header,
                                          const std::string& filename) const {
  std::cerr << m_className << "::" << header << ":\n"
            << "    Could not open file " << filename << " for reading.\n"
            << "    The file perhaps does not exist.\n";
}

void ComponentFieldMap::PrintElement(const std::string& header, const double x,
                                     const double y, const double z,
                                     const double t1, const double t2,
                                     const double t3, const double t4,
                                     const size_t i,
                                     const std::vector<double>& pot) const {
  std::cout << m_className << "::" << header << ":\n"
            << "    Global = (" << x << ", " << y << ", " << z << ")\n"
            << "    Local = (" << t1 << ", " << t2 << ", " << t3 << ", " << t4
            << ")\n";
  if (m_degenerate[i]) std::cout << "    Element is degenerate.\n";
  std::cout << " Node             x            y            z            V\n";
  std::size_t nN = 0;
  if (m_elementType == ElementType::Serendipity) {
    if (m_degenerate[i]) {
      nN = 6;
    } else {
      nN = 8;
    }
  } else if (m_elementType == ElementType::CurvedTetrahedron) {
    nN = 10;
  }
  const auto& element = m_elements[i];
  for (std::size_t ii = 0; ii < nN; ++ii) {
    const Node& node = m_nodes[element.emap[ii]];
    const double v = pot[element.emap[ii]];
    printf("      %-5d %12g %12g %12g %12g\n", element.emap[ii], node.x, node.y,
           node.z, v);
  }
}

void ComponentFieldMap::CopyWeightingPotential(
    const std::string& label, const std::string& labelSource, const double x,
    const double y, const double z, const double alpha, const double beta,
    const double gamma) {
  // Check if a weighting field with the same label already exists.
  if (m_wpot.count(label) > 0) {
    std::cout << m_className << "::CopyWeightingPotential:\n"
              << "    Electrode " << label << " exists already.\n";
    return;
  }
  if (m_wfieldCopies.count(label) > 0) {
    std::cout << m_className << "::CopyWeightingPotential:\n"
              << "    A copy named " << label << " exists already.\n";
    return;
  }

  if (m_wpot.count(labelSource) == 0) {
    std::cout << m_className << "::CopyWeightingPotential:\n"
              << "    Source electrode " << labelSource << " does not exist.\n";
    return;
  }

  WeightingFieldCopy wfieldCopy;
  wfieldCopy.source = labelSource;

  TMatrixD Rx(3, 3);  // Rotation around the y-axis.
  Rx(0, 0) = 1;
  Rx(1, 1) = TMath::Cos(-alpha);
  Rx(1, 2) = -TMath::Sin(-alpha);
  Rx(2, 1) = TMath::Sin(-alpha);
  Rx(2, 2) = TMath::Cos(-alpha);

  TMatrixD Ry(3, 3);  // Rotation around the y-axis.
  Ry(1, 1) = 1;
  Ry(0, 0) = TMath::Cos(-beta);
  Ry(2, 0) = -TMath::Sin(-beta);
  Ry(0, 2) = TMath::Sin(-beta);
  Ry(2, 2) = TMath::Cos(-beta);

  TMatrixD Rz(3, 3);  // Rotation around the z-axis.
  Rz(2, 2) = 1;
  Rz(0, 0) = TMath::Cos(-gamma);
  Rz(0, 1) = -TMath::Sin(-gamma);
  Rz(1, 0) = TMath::Sin(-gamma);
  Rz(1, 1) = TMath::Cos(-gamma);

  TVectorD trans(3);
  trans(0) = -x;
  trans(1) = -y;
  trans(2) = -z;
  wfieldCopy.rot = Rx * Ry * Rz;
  wfieldCopy.trans = trans;
  m_wfieldCopies[label] = wfieldCopy;

  std::cout << m_className << "::CopyWeightingPotential:\n"
            << "    Copy named " << label << " of weighting potential "
            << labelSource << " made.\n";
}

void ComponentFieldMap::TimeInterpolation(const double t, double& f0,
                                          double& f1, int& i0, int& i1) {
  const auto it1 = std::upper_bound(m_wdtimes.cbegin(), m_wdtimes.cend(), t);
  const auto it0 = std::prev(it1);

  const double dt = t - *it0;
  i0 = it0 - m_wdtimes.cbegin();
  i1 = it1 - m_wdtimes.cbegin();

  f1 = dt / (*it1 - *it0);
  f0 = 1. - f1;
}

#ifndef USEGPU
double ComponentFieldMap::CreateGPUTransferObject(ComponentGPU*& /*comp_gpu*/) {
  return 0;
}
#endif

}  // namespace Garfield
