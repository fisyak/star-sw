#include "wcpplib/geometry/box.h"

#include <array>
#include <cmath>
#include <iostream>
#include <memory>

#include "wcpplib/geometry/polyline.h"
#include "wcpplib/geometry/surface.h"
#include "wcpplib/geometry/trajestep.h"
/*
Copyright (c) 2000 Igor B. Smirnov

The file can be used, copied, modified, and distributed
according to the terms of GNU Lesser General Public License version 2.1
as published by the Free Software Foundation,
and provided that the above copyright notice, this permission notice,
and notices about any modifications of the original text
appear in all copies and in supporting documentation.
The file is provided "as is" without express or implied warranty.
*/

namespace Heed {

absref_transmit box::get_components() {
  std::cerr << "one should not call this function, since this object cannot be "
               "modified\n";
  spexit(std::cerr);
  return absref_transmit();
}

box::box() : m_dx(0), m_dy(0), m_dz(0), m_dxh(0), m_dyh(0), m_dzh(0) {
  init_prec();
  init_planes();
}

box::box(double fdx, double fdy, double fdz) {
  pvecerror("box(double fdx, double fdy, double fdz, const string &fname)");
  m_dx = fabs(fdx);
  m_dy = fabs(fdy);
  m_dz = fabs(fdz);
  m_dxh = 0.5 * m_dx;
  m_dyh = 0.5 * m_dy;
  m_dzh = 0.5 * m_dz;
  init_prec();
  init_planes();
}

box::box(box& fb) : absref(fb), absvol(fb) {
  pvecerror("box(box& fb)");
  m_dx = fb.m_dx;
  m_dy = fb.m_dy;
  m_dz = fb.m_dz;
  m_dxh = 0.5 * m_dx;
  m_dyh = 0.5 * m_dy;
  m_dzh = 0.5 * m_dz;
  prec = fb.prec;
  init_planes();
}

box::box(const box& fb) : absref(fb), absvol(fb) {
  pvecerror("box(const box& fb)");
  m_dx = fb.m_dx;
  m_dy = fb.m_dy;
  m_dz = fb.m_dz;
  m_dxh = 0.5 * m_dx;
  m_dyh = 0.5 * m_dy;
  m_dzh = 0.5 * m_dz;
  prec = fb.prec;
  init_planes();
}

void box::init_prec() {
  double sum = 0.;
  int n = 0.;
  if (std::isfinite(m_dxh)) {
    sum += m_dxh;
    n += 1;
  }
  if (std::isfinite(m_dyh)) {
    sum += m_dyh;
    n += 1;
  }
  if (std::isfinite(m_dzh)) {
    sum += m_dzh;
    n += 1;
  }
  if (n > 0) {
    prec = sum / n;
  }
  prec *= vprecision;
}

void box::init_planes() {
  std::vector<std::shared_ptr<surface> > fsurf(6);
  fsurf[0] = std::make_shared<splane>(plane(point(m_dxh, 0, 0), vec(-1, 0, 0)),
                                      vec(-1, 0, 0));
  fsurf[1] = std::make_shared<splane>(plane(point(-m_dxh, 0, 0), vec(+1, 0, 0)),
                                      vec(+1, 0, 0));
  fsurf[2] = std::make_shared<splane>(plane(point(0, m_dyh, 0), vec(0, -1, 0)),
                                      vec(0, -1, 0));
  fsurf[3] = std::make_shared<splane>(plane(point(0, -m_dyh, 0), vec(0, +1, 0)),
                                      vec(0, +1, 0));
  fsurf[4] = std::make_shared<splane>(plane(point(0, 0, m_dzh), vec(0, 0, -1)),
                                      vec(0, 0, -1));
  fsurf[5] = std::make_shared<splane>(plane(point(0, 0, -m_dzh), vec(0, 0, +1)),
                                      vec(0, 0, +1));
  m_ulsv.ulsvolume_init(fsurf, prec);
}

int box::check_point_inside(const point& fpt, const vec& dir) const {
  if (dir == dv0) {
    if (fabs(fpt.v.x) <= m_dxh && fabs(fpt.v.y) <= m_dyh &&
        fabs(fpt.v.z) <= m_dzh) {
      return 1;
    }
    return 0;
  }
  if (fabs(fpt.v.x) <= m_dxh - prec && fabs(fpt.v.y) <= m_dyh - prec &&
      fabs(fpt.v.z) <= m_dzh - prec) {
    return 1;
  }
  if (fabs(fpt.v.x) > m_dxh + prec || fabs(fpt.v.y) > m_dyh + prec ||
      fabs(fpt.v.z) > m_dzh + prec) {
    return 0;
  }
  // What remains is point belonging to border.
  // Below we detect cases when particle is exiting, leaving the
  // case when it is entering
  if (fabs(fpt.v.x) > m_dxh - prec) {
#ifdef IMPROVED_BOUNDARY
    if (dir.x == 0.0) return 0;
#endif
    if ((fpt.v.x > 0 && dir.x > 0) || (fpt.v.x < 0 && dir.x < 0)) {
      return 0;
    }
  }
  if (fabs(fpt.v.y) > m_dyh - prec) {
#ifdef IMPROVED_BOUNDARY
    if (dir.y == 0.0) return 0;
#endif
    if ((fpt.v.y > 0 && dir.y > 0) || (fpt.v.y < 0 && dir.y < 0)) {
      return 0;
    }
  }
  if (fabs(fpt.v.z) > m_dzh - prec) {
#ifdef IMPROVED_BOUNDARY
    if (dir.z == 0.0) return 0;
#endif
    if ((fpt.v.z > 0 && dir.z > 0) || (fpt.v.z < 0 && dir.z < 0)) {
      return 0;
    }
  }
  return 1;
}

int box::range_ext(trajestep& fts, int s_ext) const {
  if (s_ext == 0) {
    if (fabs(fts.currpos.v.x) > m_dxh + fts.mrange) return 0;
    if (fabs(fts.currpos.v.y) > m_dyh + fts.mrange) return 0;
    if (fabs(fts.currpos.v.z) > m_dzh + fts.mrange) return 0;
  } else {
    if (fabs(fts.currpos.v.x) < m_dxh - fts.mrange &&
        fabs(fts.currpos.v.y) < m_dyh - fts.mrange &&
        fabs(fts.currpos.v.z) < m_dzh - fts.mrange) {
      return 0;
    }
  }
  return m_ulsv.range_ext(fts, s_ext);
}

void box::income(gparticle* /*gp*/) {}

}  // namespace Heed
