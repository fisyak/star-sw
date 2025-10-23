#include "Garfield/SolidTube.hh"

#include <cmath>
#include <iostream>

#include "Garfield/Exceptions.hh"
#include "Garfield/FundamentalConstants.hh"
#include "Garfield/Polygon.hh"

namespace Garfield {

SolidTube::SolidTube(const double cx, const double cy, const double cz,
                     const double rt, const double lz)
    : SolidTube(cx, cy, cz, 0., rt, lz) {}

SolidTube::SolidTube(const double cx, const double cy, const double cz,
                     const double rt, const double lz, const double dx,
                     const double dy, const double dz)
    : SolidTube(cx, cy, cz, rt, lz) {
  SetDirection(dx, dy, dz);
}

SolidTube::SolidTube(const double cx, const double cy, const double cz,
                     const double ri, const double ro, const double lz)
    : Solid(cx, cy, cz, "SolidTube"), m_rO(ro), m_rI(ri), m_lZ(lz) {
  UpdatePolygon();
}

SolidTube::SolidTube(const double cx, const double cy, const double cz,
                     const double ri, const double ro, const double lz,
                     const double dx, const double dy, const double dz)
    : SolidTube(cx, cy, cz, ri, ro, lz) {
  SetDirection(dx, dy, dz);
}

void SolidTube::UpdatePolygon() {
  std::lock_guard<std::mutex> guard(m_mutex);
  const std::size_t nP = 4. * (m_n - 1);
  const double alpha = Pi / nP;
  const double calpha = cos(alpha);
  // Set the radius of the approximating polygon.
  m_rpO = m_rO;
  m_rpI = m_rI;
  if (m_average) {
    const double f = 2. / (1. + asinh(tan(alpha)) * calpha / tan(alpha));
    m_rpO *= f;
    m_rpI *= f;
  }
  // Set the inradius of the polygon.
  m_riO = m_rpO * calpha;
  m_riI = m_rpI * calpha;
  // Set the coordinates of the polygon corners.
  m_xpO.clear();
  m_ypO.clear();
  m_xpI.clear();
  m_ypI.clear();
  for (std::size_t i = 0; i < nP; ++i) {
    const double phi = m_rot + HalfPi * i / (m_n - 1.);
    const double cphi = cos(phi);
    const double sphi = sin(phi);
    m_xpO.push_back(m_rpO * cphi);
    m_ypO.push_back(m_rpO * sphi);
    if (m_rpI > 0.) {
      m_xpI.push_back(m_rpI * cphi);
      m_ypI.push_back(m_rpI * sphi);
    }
  }
}

bool SolidTube::IsInside(const double x, const double y, const double z,
                         const bool tesselated) const {
  // Transform the point to local coordinates.
  double u = x, v = y, w = z;
  ToLocal(x, y, z, u, v, w);

  if (fabs(w) > m_lZ) return false;

  const double rho = sqrt(u * u + v * v);
  if (!tesselated) return (rho <= m_rO && rho >= m_rI);

  if (rho > m_rpO || rho < m_riI) return false;
  if (rho < m_riO && rho > m_rpI) return true;
  bool inside = false;
  bool edge = false;
  Polygon::Inside(m_xpO, m_ypO, u, v, inside, edge);
  if (inside && !m_xpI.empty()) {
    Polygon::Inside(m_xpI, m_ypI, u, v, inside, edge);
    return !inside;
  }
  return inside;
}

bool SolidTube::GetBoundingBox(double& xmin, double& ymin, double& zmin,
                               double& xmax, double& ymax, double& zmax) const {
  if (m_cTheta == 1. && m_cPhi == 1.) {
    xmin = m_cX - m_rO;
    xmax = m_cX + m_rO;
    ymin = m_cY - m_rO;
    ymax = m_cY + m_rO;
    zmin = m_cZ - m_lZ;
    zmax = m_cZ + m_lZ;
    return true;
  }

  const double dd = sqrt(m_rO * m_rO + m_lZ * m_lZ);
  xmin = m_cX - dd;
  xmax = m_cX + dd;
  ymin = m_cY - dd;
  ymax = m_cY + dd;
  zmin = m_cZ - dd;
  zmax = m_cZ + dd;
  return true;
}

void SolidTube::SetRadius(const double r) {
  if (r <= 0.) throw Exception("Radius must be > 0");
  m_rO = r;
  UpdatePolygon();
}

void SolidTube::SetHalfLength(const double lz) {
  if (lz <= 0.) throw Exception("Half-length must be > 0");
  m_lZ = lz;
  UpdatePolygon();
}

void SolidTube::SetSectors(const std::size_t n) {
  if (n < 1) throw Exception("Number must be > 0");
  m_n = n;
  UpdatePolygon();
}

bool SolidTube::SolidPanels(std::vector<Panel>& panels) {
  const auto id = GetId();
  const auto nPanels = panels.size();
  // Direction vector.
  const double fnorm = sqrt(m_dX * m_dX + m_dY * m_dY + m_dZ * m_dZ);
  if (fnorm <= 0)
    throw Exception("Zero norm direction vector; no panels generated");
  const std::size_t nPoints = 4 * (m_n - 1);
  // Create the top lid(s).
  if (m_toplid) {
    const double a = m_cPhi * m_sTheta;
    const double b = m_sPhi * m_sTheta;
    const double c = m_cTheta;
    if (m_rI > 0.) {
      double alpha = m_rot;
      double calpha = cos(alpha);
      double salpha = sin(alpha);
      double xv0, yv0, zv0;
      ToGlobal(m_rpI * calpha, m_rpI * salpha, +m_lZ, xv0, yv0, zv0);
      double xv1, yv1, zv1;
      ToGlobal(m_rpO * calpha, m_rpO * salpha, +m_lZ, xv1, yv1, zv1);
      // Go around the cylinder.
      for (std::size_t i = 0; i < nPoints; ++i) {
        alpha += HalfPi / (m_n - 1.);
        calpha = cos(alpha);
        salpha = sin(alpha);
        double xv2, yv2, zv2;
        ToGlobal(m_rpO * calpha, m_rpO * salpha, +m_lZ, xv2, yv2, zv2);
        double xv3, yv3, zv3;
        ToGlobal(m_rpI * calpha, m_rpI * salpha, +m_lZ, xv3, yv3, zv3);
        std::vector<double> xv = {xv0, xv1, xv2, xv3};
        std::vector<double> yv = {yv0, yv1, yv2, yv3};
        std::vector<double> zv = {zv0, zv1, zv2, zv3};
        Panel panel;
        panel.a = a;
        panel.b = b;
        panel.c = c;
        panel.xv = xv;
        panel.yv = yv;
        panel.zv = zv;
        panel.colour = m_colour;
        panel.volume = id;
        panels.push_back(std::move(panel));
        // Shift.
        xv0 = xv3;
        yv0 = yv3;
        zv0 = zv3;
        xv1 = xv2;
        yv1 = yv2;
        zv1 = zv2;
      }
    } else {
      std::vector<double> xv;
      std::vector<double> yv;
      std::vector<double> zv;
      const double r = m_rpO;
      for (std::size_t i = 1; i <= nPoints; i++) {
        const double alpha = m_rot + HalfPi * (i - 1.) / (m_n - 1.);
        // Rotate into place.
        double x, y, z;
        ToGlobal(r * cos(alpha), r * sin(alpha), m_lZ, x, y, z);
        xv.push_back(x);
        yv.push_back(y);
        zv.push_back(z);
      }
      Panel panel;
      panel.a = a;
      panel.b = b;
      panel.c = c;
      panel.xv = xv;
      panel.yv = yv;
      panel.zv = zv;
      panel.colour = m_colour;
      panel.volume = id;
      panels.push_back(std::move(panel));
    }
  }
  // Create the bottom lid(s).
  if (m_botlid) {
    const double a = -m_cPhi * m_sTheta;
    const double b = -m_sPhi * m_sTheta;
    const double c = -m_cTheta;
    if (m_rI > 0.) {
      double alpha = m_rot;
      double calpha = cos(alpha);
      double salpha = sin(alpha);
      double xv0, yv0, zv0;
      ToGlobal(m_rpI * calpha, m_rpI * salpha, -m_lZ, xv0, yv0, zv0);
      double xv1, yv1, zv1;
      ToGlobal(m_rpO * calpha, m_rpO * salpha, -m_lZ, xv1, yv1, zv1);
      // Go around the cylinder.
      for (std::size_t i = 0; i < nPoints; ++i) {
        alpha += HalfPi / (m_n - 1.);
        calpha = cos(alpha);
        salpha = sin(alpha);
        double xv2, yv2, zv2;
        ToGlobal(m_rpO * calpha, m_rpO * salpha, -m_lZ, xv2, yv2, zv2);
        double xv3, yv3, zv3;
        ToGlobal(m_rpI * calpha, m_rpI * salpha, -m_lZ, xv3, yv3, zv3);
        std::vector<double> xv = {xv0, xv1, xv2, xv3};
        std::vector<double> yv = {yv0, yv1, yv2, yv3};
        std::vector<double> zv = {zv0, zv1, zv2, zv3};
        Panel panel;
        panel.a = a;
        panel.b = b;
        panel.c = c;
        panel.xv = xv;
        panel.yv = yv;
        panel.zv = zv;
        panel.colour = m_colour;
        panel.volume = id;
        panels.push_back(std::move(panel));
        // Shift.
        xv0 = xv3;
        yv0 = yv3;
        zv0 = zv3;
        xv1 = xv2;
        yv1 = yv2;
        zv1 = zv2;
      }
    } else {
      std::vector<double> xv;
      std::vector<double> yv;
      std::vector<double> zv;
      const double r = m_rpO;
      for (std::size_t i = 1; i <= nPoints; i++) {
        const double alpha = m_rot + HalfPi * (i - 1.) / (m_n - 1.);
        // Rotate into place.
        double x, y, z;
        ToGlobal(r * cos(alpha), r * sin(alpha), -m_lZ, x, y, z);
        xv.push_back(x);
        yv.push_back(y);
        zv.push_back(z);
      }
      Panel panel;
      panel.a = a;
      panel.b = b;
      panel.c = c;
      panel.xv = xv;
      panel.yv = yv;
      panel.zv = zv;
      panel.colour = m_colour;
      panel.volume = id;
      panels.push_back(std::move(panel));
    }
  }
  // Create the side panels.
  const std::size_t n = m_rpI > 0. ? 2 : 1;
  for (std::size_t j = 0; j < n; ++j) {
    const double r = j == 0 ? m_rpO : m_rpI;
    double u = r * cos(m_rot);
    double v = r * sin(m_rot);
    // Rotate into place.
    double xv0, yv0, zv0;
    ToGlobal(u, v, -m_lZ, xv0, yv0, zv0);
    double xv1, yv1, zv1;
    ToGlobal(u, v, +m_lZ, xv1, yv1, zv1);
    // Go around the cylinder.
    for (std::size_t i = 2; i <= nPoints + 1; i++) {
      // Bottom and top of the line along the axis of the cylinder.
      double alpha = m_rot + HalfPi * (i - 1.) / (m_n - 1.);
      u = r * cos(alpha);
      v = r * sin(alpha);
      // Rotate into place.
      double xv2, yv2, zv2;
      ToGlobal(u, v, +m_lZ, xv2, yv2, zv2);
      double xv3, yv3, zv3;
      ToGlobal(u, v, -m_lZ, xv3, yv3, zv3);
      // Store the plane.
      Panel panel;
      alpha = m_rot + HalfPi * (i - 1.5) / (m_n - 1.);
      const double cAlpha = cos(alpha);
      const double sAlpha = sin(alpha);
      panel.a = m_cPhi * m_cTheta * cAlpha - m_sPhi * sAlpha;
      panel.b = m_sPhi * m_cTheta * cAlpha + m_cPhi * sAlpha;
      panel.c = -m_sTheta * cAlpha;
      if (j == 1) {
        panel.a *= -1.;
        panel.b *= -1.;
        panel.c *= -1.;
      }
      panel.xv = {xv0, xv1, xv2, xv3};
      panel.yv = {yv0, yv1, yv2, yv3};
      panel.zv = {zv0, zv1, zv2, zv3};
      panel.colour = m_colour;
      panel.volume = id;
      panels.push_back(std::move(panel));
      // Shift the points.
      xv0 = xv3;
      yv0 = yv3;
      zv0 = zv3;
      xv1 = xv2;
      yv1 = yv2;
      zv1 = zv2;
    }
  }
  std::cout << "SolidTube::SolidPanels: " << panels.size() - nPanels
            << " panels.\n";
  return true;
}

double SolidTube::GetDiscretisationLevel(const Panel& panel) {
  // Transform the normal vector to local coordinates.
  double u = 0., v = 0., w = 0.;
  VectorToLocal(panel.a, panel.b, panel.c, u, v, w);
  // Identify the vector.
  if (w > std::max(std::abs(u), std::abs(v))) {
    return m_dis[0];
  } else if (w < -std::max(std::abs(u), std::abs(v))) {
    return m_dis[1];
  }
  return m_dis[2];
}

void SolidTube::Cut(const double x0, const double y0, const double z0,
                    const double xn, const double yn, const double zn,
                    std::vector<Panel>& panels) {
  // -----------------------------------------------------------------------
  //    PLACYC - Cuts cylinder with a plane.
  // -----------------------------------------------------------------------
  std::vector<double> xv;
  std::vector<double> yv;
  std::vector<double> zv;
  double r = m_rpO;
  const std::size_t nPoints = 4 * (m_n - 1);
  const double dphi = HalfPi / (m_n - 1.);
  // Go through the lines of the top and bottom lids.
  for (const auto zLid : {-m_lZ, +m_lZ}) {
    double x1, y1, z1;
    ToGlobal(r * cos(m_rot), r * sin(m_rot), zLid, x1, y1, z1);
    // Loop over the points.
    for (std::size_t i = 2; i <= nPoints + 1; ++i) {
      const double phi = m_rot + (i - 1.) * dphi;
      double x2, y2, z2;
      ToGlobal(r * cos(phi), r * sin(phi), zLid, x2, y2, z2);
      // Cut with the plane.
      double xc, yc, zc;
      if (Intersect(x1, y1, z1, x2, y2, z2, x0, y0, z0, xn, yn, zn, xc, yc,
                    zc)) {
        xv.push_back(xc);
        yv.push_back(yc);
        zv.push_back(zc);
      }
      // Shift the coordinates.
      x1 = x2;
      y1 = y2;
      z1 = z2;
    }
  }
  // Go through the ribs.
  for (std::size_t i = 2; i <= nPoints + 1; ++i) {
    // Bottom and top of the line along the axis of the cylinder.
    const double phi = m_rot + (i - 1.) * dphi;
    const double u = r * cos(phi);
    const double v = r * sin(phi);
    double x1, y1, z1;
    ToGlobal(u, v, +m_lZ, x1, y1, z1);
    double x2, y2, z2;
    ToGlobal(u, v, -m_lZ, x2, y2, z2);
    // Cut with the plane.
    double xc, yc, zc;
    if (Intersect(x1, y1, z1, x2, y2, z2, x0, y0, z0, xn, yn, zn, xc, yc, zc)) {
      xv.push_back(xc);
      yv.push_back(yc);
      zv.push_back(zc);
    }
  }
  // Get rid of butterflies.
  Polygon::EliminateButterflies(xv, yv, zv);

  if (xv.size() >= 3) {
    Panel panel;
    panel.a = xn;
    panel.b = yn;
    panel.c = zn;
    panel.xv = xv;
    panel.yv = yv;
    panel.zv = zv;
    panel.colour = m_colour;
    panel.volume = GetId();
    panels.push_back(std::move(panel));
  }
}

}  // namespace Garfield
