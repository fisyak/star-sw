#include "wcpplib/geometry/straight.h"

#include <limits>

#include "wcpplib/geometry/plane.h"
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

// **** straight line ****

absref absref::* straight::aref[2] = {(absref absref::*)&straight::piv,
                                      (absref absref::*)&straight::dir};

absref_transmit straight::get_components() { return absref_transmit(2, aref); }

straight::straight(const plane pl1, const plane pl2) {
  pvecerror("straight::straight(const plane pl1, const plane pl2)");
  *this = pl1.cross(pl2);
}
int operator==(const straight& sl1, const straight& sl2) {
  pvecerror("int operator==(const straight &sl1, const straight &sl2)");

  if (!(sl1.dir == sl2.dir || sl1.dir == -sl2.dir)) return 0;
  if (sl1.piv == sl2.piv) return 1;
  if (sl1.check_point_in(sl2.piv, 0.0) == 1) return 1;
  return 0;
}

bool apeq(const straight& sl1, const straight& sl2, double prec) {
  pvecerror("bool apeq(const straight &sl1, const straight &sl2, double prec)");
  if (check_par(sl1.dir, sl2.dir, prec) == 0) return false;
  if (apeq(sl1.piv, sl2.piv, prec)) return true;
  return (sl1.check_point_in(sl2.piv, prec) == 1);
}

int straight::check_point_in(const point& fp, double prec) const {
  pvecerror("int straight::check_point_in(point fp, double prec)");
  double f = distance(fp);
  if (f <= prec) return 1;
  return 0;
}
point straight::cross(const straight& sl, double prec) const {
  pvecerror("point straight::cross(straight& sl, double prec)");
  point pt[2];
  int type_of_cross;
  double f = vecdistance(sl, type_of_cross, &pt[0]);
  point ptt(dv0);
  if (type_of_cross == 2 || type_of_cross == 3) {
    vecerror = type_of_cross;
    return ptt;
  }
  if (fabs(f) <= prec) {
    vecerror = 0;
    return pt[0];
  } else {
    vecerror = 1;
    return ptt;
  }
}

double straight::vecdistance(const straight& sl, int& type_of_cross,
                             point pt[2]) const {
  pvecerror(
      "double straight::vecdistance(const straight& sl, int& type_of_cross, "
      "point pt[2])");
  pt[0] = point();
  pt[1] = point();
  type_of_cross = 0;
  straight s1, s2;
  s1 = *this;
  s2 = sl;  // s2 may be changed
  if (s1.piv == s2.piv) {
    // the same origin point
    if (check_par(s1.dir, s2.dir, 0.0) != 0) {
      // parallel or anti-parallel
      type_of_cross = 3;
      return 0.0;  // coincidence
    } else {       // crossed in piv;
      return 0.0;
    }
  }
  if (check_par(s1.dir, s2.dir, 0.0) != 0) {
    // parallel or anti-parallel
    if (s1.check_point_in(s2.piv, 0.0) == 1) {
      // point in => the same line
      type_of_cross = 3;
      return 0.0;
    } else {
      // not crossed
      type_of_cross = 2;  // different parallel lines
      return s1.distance(s2.piv);
    }
  }  // now we know that the lines are not parallel

  basis bs(s1.dir, s2.dir);
  // ez is parallel to s1.dir,                        ez=unit_vec(s1.dir)
  // ey is perpendicular to plane which have s1.dir and s2.dir,
  //                                                 ey=unit_vec(ez||s2.dir)
  // ex is vector product of ey and ez,               ex=ey||ez
  fixsyscoor scl(&s1.piv, &bs);
  plane pn(point(0, 0, 0), vec(1, 0, 0));  // assumed to be in scl
                                           // This plane is defined by
  s2.up(&scl);
  pt[1] = pn.cross(s2);
  if (pt[1].v.y == 0) {
    pt[1].down(&scl);
    pt[0] = pt[1];
    return 0.0;
  } else {
    type_of_cross = 1;
    double d = pt[1].v.y;
    pt[0] = pt[1];
    pt[0].v.y = 0;
    pt[0].down(&scl);
    pt[1].down(&scl);
    return d;
  }
}

double straight::distance(const straight& sl, int& type_of_cross,
                          point pt[2]) const {
  return fabs(vecdistance(sl, type_of_cross, pt));
}

double straight::distance(const point& fpt) const {
  pvecerror("double straight::distance(point& fpt)");
  if (fpt == piv) return 0.0;
  vec v = fpt - piv;
  return v.length() * sin2vec(dir, v);  // should be positive
}

double straight::distance(const point& fpt, point& fcpt) const {
  pvecerror("double straight::distance(point& fpt, point& fcpt)");
  if (fpt == piv) {
    fcpt = piv;
    return 0.0;
  }
  vec v = fpt - piv;
  double len = v.length();
  fcpt = piv + len * cos2vec(dir, v) * dir;
  return v.length() * sin2vec(dir, v);
}

}  // namespace Heed
