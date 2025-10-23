#include <iomanip>
#include <iostream>
#ifdef VISUAL_STUDIO
#define _USE_MATH_DEFINES
// see comment in math.h:
/* Define _USE_MATH_DEFINES before including math.h to expose these macro
 * definitions for common math constants.  These are placed under an #ifdef
 * since these commonly-defined names are not part of the C/C++ standards.
 */
#endif
#include <cmath>

#include "Garfield/Random.hh"
#include "wcpplib/geometry/vec.h"

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

int vecerror = 0;

absref* absref_transmit::get_other(int /*n*/) { return NULL; }

// **** absref ****

void absref::down(const abssyscoor* fasc) {
  if (fasc == NULL) return;  // considered to be unchanged
  ApplyAnyFunctionToVecElements(down(fasc));
}

void absref::up(const abssyscoor* fasc) {
  if (fasc == NULL) return;  // considered to be unchanged
  ApplyAnyFunctionToVecElements(up(fasc));
}

void absref::turn(const vec& dir, double angle) {
  ApplyAnyFunctionToVecElements(turn(dir, angle));
}

void absref::shift(const vec& dir) {
  ApplyAnyFunctionToVecElements(shift(dir));
}

absref_transmit absref::get_components() { return absref_transmit(); }

// **** vector ****
double cos2vec(const vec& r1, const vec& r2) {
  // cosinus of angle between vectors
  // If one of vectors has zero length, it returns 2.
  pvecerror("double cos2vec(const vec& r1, const vec& r2)");
  double lr1 = r1.length2();
  double lr2 = r2.length2();
  if (lr1 == 0 || lr2 == 0) {
    vecerror = 1;
    return 0;
  }
  double cs = r1 * r2;
  int sign = 1;
  if (cs < 0) sign = -1;
  cs = cs * cs;
  cs = sign * sqrt(cs / (lr1 * lr2));
  return cs;
}

double ang2vec(const vec& r1, const vec& r2) {
  // angle between vectors
  // instead of return acos(cos2vec(r1,r2)); which produces NaN on linux at
  // parallel vectors
  double cs = cos2vec(r1, r2);
  if (vecerror != 0) return 0;
  if (cs > 0.707106781187 || cs < -0.707106781187) {  // 1.0/sqrt(2)
    // pass to sin, it will be more exactly
    double sn = sin2vec(r1, r2);
    if (vecerror != 0) return 0;
    if (cs > 0.0)
      return asin(sn);
    else
      return M_PI - asin(sn);
  }
  return acos(cs);
}

double sin2vec(const vec& r1, const vec& r2) {
  // sinus of angle between vectors
  pvecerror("double sin2vec(const vec& r1, const vec& r2)");
  double lr1 = r1.length2();
  double lr2 = r2.length2();
  if (lr1 == 0 || lr2 == 0) {
    vecerror = 1;
    return 0;
  }
  double sn = (r1 || r2).length();
  sn = sn * sn;
  sn = sqrt(sn / (lr1 * lr2));
  return sn;
}

vec project_to_plane(const vec& r, const vec& normal) {
  pvecerror("vec project_to_plane(const vec& r, const vec& normal)");
  vec per(normal || r);
  if (per == dv0) {
    // either one of vectors is 0 or they are parallel
    return dv0;
  }
  vec ax = unit_vec(per || normal);
  double v = ax * r;
  return v * ax;
}

double ang2projvec(const vec& r1, const vec& r2, const vec& normal) {
  pvecerror(
      "double ang2projvec(const vec& r1, const vec& r2, const vec& normal)");
  vec rt1 = project_to_plane(r1, normal);
  vec rt2 = project_to_plane(r2, normal);
  if (rt1 == dv0 || rt2 == dv0) {
    vecerror = 1;
    return 0;
  }
  double tang = ang2vec(rt1, rt2);
  if (tang == 0) return tang;  // projections are parallel
  vec at = rt1 || rt2;
  int i = check_par(at, normal, 0.0001);
  if (i == -1) return 2.0 * M_PI - tang;
  return tang;  // it works if angle <= PI
}

vec vec::down_new(const basis* fabas) {
  // pvecerror("vec vec::down_new(void)");
  vec r;
  vec ex = fabas->Gex();
  vec ey = fabas->Gey();
  vec ez = fabas->Gez();
  r.x = x * ex.x + y * ey.x + z * ez.x;
  r.y = x * ex.y + y * ey.y + z * ez.y;
  r.z = x * ex.z + y * ey.z + z * ez.z;
  return r;
}

void vec::down(const basis* fabas) { *this = this->down_new(fabas); }

vec vec::up_new(const basis* fabas_new) {
  // it is assumed that fabas_new is derivative from old
  pvecerrorp("vec vec::up_new((const basis *pbas)");
  vec r;
  // check_econd11(fabas_new , ==NULL, std::cerr);
  // not compiled in IRIX, reason is unkown
  if (fabas_new == NULL) {
    std::cerr << "fabas_new==NULL\n";
    spexit(std::cerr);
  }
  vec ex = fabas_new->Gex();
  vec ey = fabas_new->Gey();
  vec ez = fabas_new->Gez();
  r.x = x * ex.x + y * ex.y + z * ex.z;
  r.y = x * ey.x + y * ey.y + z * ey.z;
  r.z = x * ez.x + y * ez.y + z * ez.z;
  return r;
}

void vec::up(const basis* fabas_new) { *this = this->up_new(fabas_new); }

vec vec::turn_new(const vec& dir, double angle) {
  pvecerror("vec turn(vec& dir, double& angle)");
  if ((*this).length() == 0) return vec(0, 0, 0);
  if (check_par(*this, dir, 0.0) != 0) {
    // parallel vectors are not changed
    return *this;
  }
  double dirlen = dir.length();
  check_econd11a(dirlen, == 0, "cannot turn around zero vector", std::cerr);
  vec u = dir / dirlen;  // unit vector
  vec constcomp = u * (*this) * u;
  vec ort1 = unit_vec(u || (*this));
  vec ort2 = ort1 || u;
  vec perpcomp = ort2 * (*this) * ort2;
  double len = perpcomp.length();
  ort1 = sin(angle) * len * ort1;
  ort2 = cos(angle) * len * ort2;
  return constcomp + ort1 + ort2;
}

void vec::turn(const vec& dir, double angle) {
  *this = this->turn_new(dir, angle);
}

void vec::shift(const vec& /*dir*/) {
  // Not defined for vectors
}

vec vec::down_new(const abssyscoor* fasc) { return down_new(fasc->Gabas()); }
void vec::down(const abssyscoor* fasc) { down(fasc->Gabas()); }
vec vec::up_new(const abssyscoor* fasc) { return up_new(fasc->Gabas()); }
void vec::up(const abssyscoor* fasc) { up(fasc->Gabas()); }

void vec::random_round_vec() {
  const double phi = M_PI * 2.0 * Garfield::RndmUniform();
  x = sin(phi);
  y = cos(phi);
  z = 0;
}

void vec::random_conic_vec(double theta) {
  double phi = M_PI * 2.0 * Garfield::RndmUniform();
  double stheta = sin(theta);
  x = sin(phi) * stheta;
  y = cos(phi) * stheta;
  z = cos(theta);
}

void vec::random_sfer_vec() {
  double cteta = 2.0 * Garfield::RndmUniform() - 1.0;
  random_round_vec();
  double steta = sqrt(1.0 - cteta * cteta);
  *this = (*this) * steta;
  z = cteta;
}

vec dex(1, 0, 0);
vec dey(0, 1, 0);
vec dez(0, 0, 1);
vec dv0(0, 0, 0);

// **** basis ****

absref absref::* basis::aref[3] = {
    reinterpret_cast<absref absref::*>(static_cast<vec absref::*>(&basis::ex)),
    reinterpret_cast<absref absref::*>(static_cast<vec absref::*>(&basis::ey)),
    reinterpret_cast<absref absref::*>(static_cast<vec absref::*>(&basis::ez))};

absref_transmit basis::get_components() { return absref_transmit(3, aref); }

basis::basis() : ex(1, 0, 0), ey(0, 1, 0), ez(0, 0, 1) {}

basis::basis(const vec& p) {
  pvecerror("basis::basis(vec &p)");
  // vec dex(1, 0, 0);
  // vec dey(0, 1, 0);
  // vec dez(0, 0, 1);
  if (p.length() == 0) {
    vecerror = 1;
    ex = dex;
    ey = dey;
    ez = dez;
  }
  double ca = cos2vec(p, dez);
  if (ca == 1) {
    ex = dex;
    ey = dey;
    ez = dez;
  } else if (ca == -1) {
    ex = -dex;
    ey = -dey;
    ez = -dez;
  } else {
    ez = unit_vec(p);
    ey = unit_vec(ez || dez);
    ex = ey || ez;
  }
}

basis::basis(const vec& p, const vec& c) {
  pvecerror("basis::basis(vec &p, vec &c, char pname[12])");

  if (p.length() == 0 || c.length() == 0) {
    vecerror = 1;
    ex = dex;
    ey = dey;
    ez = dez;
  }
  double ca = cos2vec(p, c);
  if (ca == 1) {
    vecerror = 1;
    ex = dex;
    ey = dey;
    ez = dez;
  } else if (ca == -1) {
    vecerror = 1;
    ex = dex;
    ey = dey;
    ez = dez;
  } else {
    ez = unit_vec(p);
    ey = unit_vec(ez || c);
    ex = ey || ez;
  }
}

basis::basis(const vec& pex, const vec& pey, const vec& pez) {
  pvecerror("basis::basis(vec &pex, vec &pey, vec &pez, char pname[12])");
  if (!check_perp(pex, pey, vprecision) || !check_perp(pex, pez, vprecision) ||
      !check_perp(pey, pez, vprecision)) {
    std::cerr << "ERROR in basis::basis(vec &pex, vec &pey, vec &pez) : \n"
              << "the vectors are not perpendicular\n";
    std::cerr << " pex,pey,pez:\n";
    // std::cerr << pex << pey << pez;
    spexit(std::cerr);
  }
  if (!apeq(pex.length(), double(1.0)) || !apeq(pey.length(), double(1.0)) ||
      !apeq(pez.length(), double(1.0))) {
    std::cerr << "ERROR in basis::basis(vec &pex, vec &pey, vec &pez) : \n"
              << "the vectors are not of unit length\n";
    std::cerr << " pex,pey,pez:\n";
    // std::cerr << pex << pey << pez;
    spexit(std::cerr);
  }
  if (!apeq(pex || pey, pez, vprecision)) {
    std::cerr << "ERROR in basis::basis(vec &pex, vec &pey, vec &pez) : \n";
    std::cerr << "wrong direction of pez\n";
    std::cerr << " pex,pey,pez:\n";
    // std::cerr << pex << pey << pez;
    spexit(std::cerr);
  }
  ex = pex;
  ey = pey;
  ez = pez;
}

// **** point ****

absref absref::* point::aref =
    reinterpret_cast<absref absref::*>(static_cast<vec absref::*>(&point::v));

absref_transmit point::get_components() { return absref_transmit(1, &aref); }

void point::down(const abssyscoor* fasc) {
  v.down(fasc);
  shift(fasc->Gapiv()->v);
}
void point::up(const abssyscoor* fasc) {
  shift(-fasc->Gapiv()->v);
  v.up(fasc);
}

// **** system of coordinates ****

absref absref::* fixsyscoor::aref[2] = {
    reinterpret_cast<absref absref::*>(
        static_cast<point absref::*>(&fixsyscoor::piv)),
    reinterpret_cast<absref absref::*>(
        static_cast<basis absref::*>(&fixsyscoor::bas))};

absref_transmit fixsyscoor::get_components() {
  return absref_transmit(2, aref);
}

void fixsyscoor::Ppiv(const point& fpiv) { piv = fpiv; }
void fixsyscoor::Pbas(const basis& fbas) { bas = fbas; }

}  // namespace Heed
