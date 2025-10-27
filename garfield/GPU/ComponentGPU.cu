#include <iostream>

#include "ComponentGPU.h"
#include "GPUFunctions.h"
#include "Garfield/ComponentAnsys123.hh"
#include "Garfield/ComponentComsol.hh"
#include "Garfield/ComponentElmer.hh"
#include "Garfield/ComponentFieldMap.hh"
#include "Garfield/Medium.hh"

namespace Garfield {

// PART OF COMPONENT_FIELD_MAP
// This should be in a class  COMPONENT_FIELD_MAPGPU not ComponentGPU but
// because we don't want / can't have inherence now put that */@#$# here !
__device__ void ComponentGPU::ElectricField(const double xin, const double yin,
                                            const double zin, double& ex,
                                            double& ey, double& ez,
                                            MediumGPU*& m, int& status) {
  // Initial values
  ex = ey = ez = 0.;
  m = nullptr;
  int iel = -1;
  status = Field(xin, yin, zin, ex, ey, ez, iel, m_pot, m_numpot);

  if (status < 0 || iel < 0) {
    if (status == -10) { /*PrintNotReady("ElectricField");*/
    }
    return;
  }

  const auto& element = m_elements[iel];
  // Drift medium?
  if (element.matmap >= numMaterials) {
    status = -5;
    return;
  }

  const auto& mat = m_materials[element.matmap];
  m = mat.medium;
  status = -5;
  if (mat.driftmedium) {
    if (m && m->IsDriftable()) status = 0;
  }
}

int __device__ ComponentGPU::Field(const double xin, const double yin,
                                   const double zin, double& fx, double& fy,
                                   double& fz, int& imap, const double* pot,
                                   const int numPot) const {
  // Do not proceed if not properly initialised.
  if (!m_ready) return -10;
  // Copy the coordinates.
  double x = xin, y = yin;
  double z = m_is3d ? zin : 0.;
  // Map the coordinates onto field map coordinates
  bool xmirr, ymirr, zmirr;
  double rcoordinate, rotation;
  MapCoordinates(x, y, z, xmirr, ymirr, zmirr, rcoordinate, rotation);
  // TODO TN GPU: We don't support 2D field maps on the GPU yet and it will
  // silently ignore these
  // if (!m_is3d) {
  //  if (zin < m_minBoundingBox[2] || zin > m_maxBoundingBox[2]) {
  //    return -5;
  //  }
  //}

  // Find the element that contains this point.
  double t1 = 0., t2 = 0., t3 = 0., t4 = 0.;
  double jac[4][4];
  double det = 0.;
  imap = -1;
  if (m_elementType == ElementType::Serendipity) {
    // TODO TN GPU: ElementType::Serendipity not supported on GPU
    // imap = FindElement5(x, y, t1, t2, t3, t4, jac, det);
  } else if (m_elementType == ElementType::CurvedTetrahedron) {
    imap = FindElement13(x, y, z, t1, t2, t3, t4, jac, det);
  }
  // Stop if the point is not in the mesh.
  if (imap < 0) {
    return -6;
  }

  const Element& element = m_elements[imap];
  if (m_elementType == ElementType::Serendipity) {
    // TODO TN GPU: ElementType::Serendipity not supported (see above)
    // if (m_degenerate[imap]) {
    //  std::array<double, 6> v;
    //   for (size_t i = 0; i < 6; ++i) v[i] = pot[element.emap[i]];
    //  Field3(v, {t1, t2, t3}, jac, det, fx, fy);
    //} else {
    //  std::array<double, 8> v;
    //  for (size_t i = 0; i < 8; ++i) v[i] = pot[element.emap[i]];
    //  Field5(v, {t1, t2}, jac, det, fx, fy);
    // }
  } else if (m_elementType == ElementType::CurvedTetrahedron) {
    double v[10];
    // TODO TN GPU: Warning can not use size_t here for some reason...
    for (int i = 0; i < 10; ++i) v[i] = pot[element.emap[i]];
    // CUDA doesn't like passing initialiser list directly to method
    double t[4] = {t1, t2, t3, t4};
    Field13(v, t, jac, 4 * det, fx, fy, fz);
  }
  // Transform field to global coordinates.
  UnmapFields(fx, fy, fz, x, y, z, xmirr, ymirr, zmirr, rcoordinate, rotation);
  return 0;
}

__device__ void ComponentGPU::WeightingField(const double xin, const double yin,
                                             const double zin, double& wx,
                                             double& wy, double& wz,
                                             size_t label) {
  // Initial values.
  wx = wy = wz = 0;

  // Do not proceed if not properly initialised.
  if (!m_ready) return;
  int iel = -1;
  Field(xin, yin, zin, wx, wy, wz, iel, m_wpot[label],
        m_num_entries_wpot[label]);
}

__device__ void ComponentGPU::Field13(const double v[10], const double t[4],
                                      double jac[4][4], const double det,
                                      double& ex, double& ey, double& ez) {
  double g[4];
  g[0] = v[0] * (t[0] - 0.25) + v[4] * t[1] + v[5] * t[2] + v[6] * t[3];
  g[1] = v[1] * (t[1] - 0.25) + v[4] * t[0] + v[7] * t[2] + v[8] * t[3];
  g[2] = v[2] * (t[2] - 0.25) + v[5] * t[0] + v[7] * t[1] + v[9] * t[3];
  g[3] = v[3] * (t[3] - 0.25) + v[6] * t[0] + v[8] * t[1] + v[9] * t[2];
  double f[3] = {0., 0., 0.};
  for (int j = 0; j < 4; ++j) {
    for (int i = 0; i < 3; ++i) {
      f[i] += g[j] * jac[j][i + 1];
    }
  }
  ex = -f[0] * det;
  ey = -f[1] * det;
  ez = -f[2] * det;
}

__device__ int ComponentGPU::FindElement13(const double x, const double y,
                                           const double z, double& t1,
                                           double& t2, double& t3, double& t4,
                                           double jac[4][4],
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

  cuda_t xn[10];
  cuda_t yn[10];
  cuda_t zn[10];

  const int* tetList{nullptr};
  int tetListSize{0};
  if (m_useTetrahedralTree && m_octree) {
    m_octree->GetElementsInBlock(Vec3{x, y, z}, tetList, tetListSize);
  } else {
    tetList = m_elementIndices;
    tetListSize = numElements;
  }
  for (int teti = 0; teti < tetListSize; ++teti) {
    int i = tetList[teti];
    if (x < m_bbMin[i][0] || y < m_bbMin[i][1] || z < m_bbMin[i][2] ||
        x > m_bbMax[i][0] || y > m_bbMax[i][1] || z > m_bbMax[i][2]) {
      continue;
    }
    // TODO: GPU doesn't seem to like size_t, double check this
    for (int j = 0; j < 10; ++j) {
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
      return -1;
    }
    if (nfound > 1) {
      printf(
          "ComponentGPU::FindElement13:\n    Found %d elements matching point "
          "(%f, %f, %f).\n",
          nfound, x, y, z);
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
  return -1;
}

__device__ void ComponentGPU::Jacobian13(
    const double xn[10], const double yn[10], const double zn[10],
    const double fourt0, const double fourt1, const double fourt2,
    const double fourt3, double& det, double jac[4][4]) {
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

__device__ void ComponentGPU::Coordinates12(
    const double x, const double y, const double z, double& t1, double& t2,
    double& t3, double& t4, const double xn[10], const double yn[10],
    const double zn[10], const double w[4][3]) const {
  // Compute tetrahedral coordinates.
  t1 = (x - xn[1]) * w[0][0] + (y - yn[1]) * w[0][1] + (z - zn[1]) * w[0][2];
  t2 = (x - xn[2]) * w[1][0] + (y - yn[2]) * w[1][1] + (z - zn[2]) * w[1][2];
  t3 = (x - xn[3]) * w[2][0] + (y - yn[3]) * w[2][1] + (z - zn[3]) * w[2][2];
  t4 = (x - xn[0]) * w[3][0] + (y - yn[0]) * w[3][1] + (z - zn[0]) * w[3][2];
}

__device__ int ComponentGPU::Coordinates13(
    const double x, const double y, const double z, double& t1, double& t2,
    double& t3, double& t4, double jac[4][4], double& det, const double xn[10],
    const double yn[10], const double zn[10], cuda_t** w) const {
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
  double td[4] = {t1, t2, t3, t4};

  // Loop
  bool converged = false;
  for (int iter = 0; iter < 10; ++iter) {
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
    double sr{0};
    for (int i = 0; i < 4; ++i) {
      sr += td[i];
    }
    const double diff[4] = {1. - sr, x - xr, y - yr, z - zr};
    // Update the estimate.
    double corr[4] = {0., 0., 0., 0.};
    for (int l = 0; l < 4; ++l) {
      for (int k = 0; k < 4; ++k) {
        corr[l] += jac[l][k] * diff[k];
      }
      corr[l] *= det;
      td[l] += corr[l];
    }

    // Check for convergence.
    constexpr double tol = 1.e-5;
    if (fabs(corr[0]) < tol && fabs(corr[1]) < tol && fabs(corr[2]) < tol &&
        fabs(corr[3]) < tol) {
      converged = true;
      break;
    }
  }

  // No convergence reached.
  if (!converged) {
    const cuda_t xmin = fmin(fmin(fmin(xn[0], xn[1]), xn[2]), xn[3]);
    const cuda_t xmax = fmax(fmax(fmax(xn[0], xn[1]), xn[2]), xn[3]);
    const cuda_t ymin = fmin(fmin(fmin(yn[0], yn[1]), yn[2]), yn[3]);
    const cuda_t ymax = fmax(fmax(fmax(yn[0], yn[1]), yn[2]), yn[3]);
    const cuda_t zmin = fmin(fmin(fmin(zn[0], zn[1]), zn[2]), zn[3]);
    const cuda_t zmax = fmax(fmax(fmax(zn[0], zn[1]), zn[2]), zn[3]);
    if (x >= xmin && x <= xmax && y >= ymin && y <= ymax && z >= zmin &&
        z <= zmax) {
      printf(
          "ComponentGPU::Coordinates13:\n    No convergence achieved when "
          "refining internal isoparametric coordinates\n");
      t1 = t2 = t3 = t4 = -1;
      return 1;
    }
  }

  // Convergence reached.
  t1 = td[0];
  t2 = td[1];
  t3 = td[2];
  t4 = td[3];
  // Success
  return 0;
}

__device__ void ComponentGPU::MapCoordinates(double& xpos, double& ypos,
                                             double& zpos, bool& xmirrored,
                                             bool& ymirrored, bool& zmirrored,
                                             double& rcoordinate,
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
      prefixH = (m_triangleSymmetricOct % 2 == 0) ? 1 : -1;
      if (std::abs(xpos) < std::abs(ypos)) triSwap = true;
    } else {
      prefixH = (m_triangleSymmetricOct % 2 == 0) ? -1 : 1;
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

__device__ void ComponentGPU::UnmapFields(
    double& ex, double& ey, double& ez, const double xpos, const double ypos,
    const double zpos, const bool xmirrored, const bool ymirrored,
    const bool zmirrored, const double rcoordinate,
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

//////////////////////////////////

double Component::CreateGPUTransferObject(ComponentGPU*& comp_gpu) {
  // copy periodicity and min/max
  comp_gpu->m_symmetries = m_symmetries;
  comp_gpu->m_ready = m_ready;

  comp_gpu->m_ComponentType = ComponentGPU::ComponentType::Component;

  return 0;
}

double ComponentFieldMap::CreateGPUTransferObject(ComponentGPU*& comp_gpu) {
  double alloc{0};

  // Check if bounding boxes of elements have been computed
  if (!m_cacheElemBoundingBoxes) {
    std::cout << m_className << "::CreateGPUTransferObject:\n"
              << "    Caching the bounding boxes of all elements...";
    CalculateElementBoundingBoxes();
    std::cout << " done.\n";
    m_cacheElemBoundingBoxes = true;
  }

  // initialise the tetraheral tree
  if (m_useTetrahedralTree) {
    if (!m_octree) {
      if (!InitializeTetrahedralTree()) {
        std::cerr << m_className << "::FindElement13:\n";
        std::cerr << "    Tetrahedral tree initialization failed.\n";
        return alloc;
      }
    }
  }

  // copy periodicity and min/max
  for (int i = 0; i < 3; i++) {
    comp_gpu->m_mapmin[i] = m_mapmin[i];
    comp_gpu->m_mapmax[i] = m_mapmax[i];
    comp_gpu->m_mapamin[i] = m_mapamin[i];
    comp_gpu->m_mapamax[i] = m_mapamax[i];
  }

  // materials
  comp_gpu->numMaterials = m_materials.size();
  checkCudaErrors(cudaMallocManaged(
      &(comp_gpu->m_materials),
      sizeof(ComponentGPU::Material) * comp_gpu->numMaterials));
  alloc += sizeof(ComponentGPU::Material) * comp_gpu->numMaterials;

  for (int i = 0; i < comp_gpu->numMaterials; i++) {
    comp_gpu->m_materials[i].eps = m_materials[i].eps;
    comp_gpu->m_materials[i].ohm = m_materials[i].ohm;
    comp_gpu->m_materials[i].driftmedium = m_materials[i].driftmedium;

    if (m_materials[i].medium) {
      alloc += m_materials[i].medium->CreateGPUTransferObject(
          comp_gpu->m_materials[i].medium);
    }
  }

  // tetrahedral tree related things
  comp_gpu->m_checkMultipleElement = m_checkMultipleElement;
  comp_gpu->m_useTetrahedralTree = m_useTetrahedralTree;

  // elements
  comp_gpu->numElements = m_elements.size();
  checkCudaErrors(
      cudaMallocManaged(&(comp_gpu->m_elements),
                        sizeof(ComponentGPU::Element) * comp_gpu->numElements));
  alloc += sizeof(ComponentGPU::Element) * comp_gpu->numElements;

  checkCudaErrors(cudaMallocManaged(&(comp_gpu->m_degenerate),
                                    sizeof(bool) * comp_gpu->numElements));
  alloc += sizeof(bool) * comp_gpu->numElements;

  checkCudaErrors(cudaMallocManaged(&(comp_gpu->m_bbMin),
                                    sizeof(cuda_t*) * comp_gpu->numElements));
  checkCudaErrors(cudaMallocManaged(&(comp_gpu->m_bbMax),
                                    sizeof(cuda_t*) * comp_gpu->numElements));
  alloc += sizeof(cuda_t*) * comp_gpu->numElements * 2;

  for (int i = 0; i < comp_gpu->numElements; i++) {
    checkCudaErrors(
        cudaMallocManaged(&comp_gpu->m_bbMin[i], sizeof(cuda_t) * 3));
    checkCudaErrors(
        cudaMallocManaged(&comp_gpu->m_bbMax[i], sizeof(cuda_t) * 3));
    alloc += sizeof(cuda_t) * 3 * 2;
    for (int j = 0; j < 3; j++) {
      comp_gpu->m_bbMin[i][j] = m_bbMin[i][j];
      comp_gpu->m_bbMax[i][j] = m_bbMax[i][j];
    }
  }

  for (int i = 0; i < comp_gpu->numElements; i++) {
    for (int j = 0; j < 10; j++) {
      comp_gpu->m_elements[i].emap[j] = m_elements[i].emap[j];
    }
    comp_gpu->m_elements[i].matmap = m_elements[i].matmap;
    comp_gpu->m_degenerate[i] = m_degenerate[i];
  }

  comp_gpu->numNodes = m_nodes.size();
  checkCudaErrors(cudaMallocManaged(
      &(comp_gpu->m_nodes), sizeof(ComponentGPU::Node) * comp_gpu->numNodes));
  alloc += sizeof(ComponentGPU::Node) * comp_gpu->numNodes;

  for (int i = 0; i < comp_gpu->numNodes; i++) {
    comp_gpu->m_nodes[i].x = m_nodes[i].x;
    comp_gpu->m_nodes[i].y = m_nodes[i].y;
    comp_gpu->m_nodes[i].z = m_nodes[i].z;
  }

  comp_gpu->m_numpot = m_pot.size();
  checkCudaErrors(cudaMallocManaged(&(comp_gpu->m_pot),
                                    sizeof(double) * comp_gpu->m_numpot));
  alloc += sizeof(double) * comp_gpu->m_numpot;

  for (int i = 0; i < comp_gpu->m_numpot; i++) {
    comp_gpu->m_pot[i] = m_pot[i];
  }

  checkCudaErrors(cudaMallocManaged(&(comp_gpu->m_w12),
                                    sizeof(cuda_t**) * comp_gpu->numElements));
  alloc += sizeof(cuda_t**) * comp_gpu->numElements;

  for (int i = 0; i < comp_gpu->numElements; i++) {
    checkCudaErrors(
        cudaMallocManaged(&comp_gpu->m_w12[i], sizeof(cuda_t*) * 4));
    alloc += sizeof(cuda_t*) * 4;

    for (int j = 0; j < 4; j++) {
      checkCudaErrors(
          cudaMallocManaged(&comp_gpu->m_w12[i][j], sizeof(cuda_t) * 3));
      alloc += sizeof(cuda_t) * 3;

      for (int k = 0; k < 3; k++) {
        comp_gpu->m_w12[i][j][k] = m_w12[i][j][k];
      }
    }
  }

  // Weighting potentials
  // - Label information is not used here and instead we are relying on the map
  // being ordered
  comp_gpu->m_num_wpots = m_wpot.size();
  checkCudaErrors(cudaMallocManaged(&(comp_gpu->m_num_entries_wpot),
                                    sizeof(int) * comp_gpu->m_num_wpots));
  alloc += sizeof(int) * comp_gpu->m_num_wpots;
  checkCudaErrors(cudaMallocManaged(&(comp_gpu->m_wpot),
                                    sizeof(double*) * comp_gpu->m_num_wpots));
  alloc += sizeof(double*) * comp_gpu->m_num_wpots;
  size_t index = 0;
  for (const auto& data : m_wpot) {
    comp_gpu->m_num_entries_wpot[index] = data.second.size();
    checkCudaErrors(cudaMallocManaged(&(comp_gpu->m_wpot[index]),
                                      sizeof(double) * data.second.size()));
    alloc += sizeof(double) * data.second.size();
    for (size_t j = 0; j < data.second.size(); j++) {
      comp_gpu->m_wpot[index][j] = data.second.at(j);
    }
    ++index;
  }

  if (comp_gpu->m_useTetrahedralTree) {
    alloc += m_octree->CreateGPUTransferObject(comp_gpu->m_octree);
  }

  comp_gpu->numElements = m_elements.size();
  // TODO TN GPU: Fix type to CurvedTetrahedron, work out how to get this
  // from the CPU FieldMap in future
  comp_gpu->m_elementType = ComponentGPU::ElementType::CurvedTetrahedron;
  comp_gpu->m_is3d = m_is3d;

  comp_gpu->m_ComponentType = ComponentGPU::ComponentType::ComponentFieldMap;

  return alloc;
}

double ComponentAnsys123::CreateGPUTransferObject(ComponentGPU*& comp_gpu) {
  // create main sensor GPU class
  checkCudaErrors(cudaMallocManaged(&comp_gpu, sizeof(ComponentGPU)));
  double alloc{sizeof(ComponentGPU)};

  alloc += ComponentFieldMap::CreateGPUTransferObject(comp_gpu);
  alloc += Component::CreateGPUTransferObject(comp_gpu);

  comp_gpu->m_ComponentType = ComponentGPU::ComponentType::ComponentAnsys123;
  return alloc;
}

double ComponentElmer::CreateGPUTransferObject(ComponentGPU*& comp_gpu) {
  // create main sensor GPU class
  checkCudaErrors(cudaMallocManaged(&comp_gpu, sizeof(ComponentGPU)));
  double alloc{sizeof(ComponentGPU)};

  alloc += ComponentFieldMap::CreateGPUTransferObject(comp_gpu);
  alloc += Component::CreateGPUTransferObject(comp_gpu);

  comp_gpu->m_ComponentType = ComponentGPU::ComponentType::ComponentElmer;
  return alloc;
}

double ComponentComsol::CreateGPUTransferObject(ComponentGPU*& comp_gpu) {
  // create main sensor GPU class
  checkCudaErrors(cudaMallocManaged(&comp_gpu, sizeof(ComponentGPU)));
  double alloc{sizeof(ComponentGPU)};

  alloc += ComponentFieldMap::CreateGPUTransferObject(comp_gpu);
  alloc += Component::CreateGPUTransferObject(comp_gpu);

  comp_gpu->m_ComponentType = ComponentGPU::ComponentType::ComponentComsol;
  return alloc;
}
}  // namespace Garfield
