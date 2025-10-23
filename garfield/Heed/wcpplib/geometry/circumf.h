#ifndef CIRCUMF_H
#define CIRCUMF_H
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

class plane;

/// Circumference, determined by point (center), normal vector, and radius.
class circumf : public absref {
 public:
  /// Default constructor.
  circumf();
  /// Constructor.
  circumf(const point& fpiv, const vec& fdir, double frad);
  circumf(const circumf& f);
  circumf& operator=(const circumf& f) {
    piv = f.piv;
    dir = f.dir;
    rad = f.rad;
    return *this;
  }
  /// Destructor
  virtual ~circumf() {}
  friend int operator==(const circumf& f1, const circumf& f2);
  friend int operator!=(const circumf& f1, const circumf& f2) {
    return f1 == f2 ? 0 : 1;
  }
  friend bool apeq(const circumf& f1, const circumf& f2, double prec);

  point Gpiv() const { return piv; }
  vec Gdir() const { return dir; }
  double Grad() const { return rad; }

  /// Return 1 if point on the circumference.
  int check_point_in(const point& fp, double prec) const;
  // return number of crosses and calculates pt.
  // if total circle lies in the plane, it returns -1.
  // prec allow to switch to one point if it is almost one
  int cross(const plane& pn, point pt[2], double prec) const;

 protected:
  /// Central point, pivot.
  point piv;
  /// Normal direction, unit vector.
  /// Circles with dir and -dir are considered the same.
  vec dir;
  /// Radius, >0.
  double rad;

  virtual absref_transmit get_components() override;
  static absref absref::* aref[2];
};
}  // namespace Heed

#endif
