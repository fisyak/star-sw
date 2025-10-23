#ifndef STRAIGHT_H
#define STRAIGHT_H

/* Copyright (c) 2000 Igor B. Smirnov

The file can be used, copied, modified, and distributed
according to the terms of GNU Lesser General Public License version 2.1
as published by the Free Software Foundation,
and provided that the above copyright notice, this permission notice,
and notices about any modifications of the original text
appear in all copies and in supporting documentation.
The file is provided "as is" without express or implied warranty.
*/

#include "wcpplib/geometry/vec.h"

namespace Heed {

class plane;

/// Straight line, as combination of vector and point.

class straight : public absref {
 protected:
  /// Origin point, pivot.
  point piv;
  /// Direction, unit vector
  vec dir;

 public:
  point Gpiv() const { return piv; }
  vec Gdir() const { return dir; }

 protected:
  virtual absref_transmit get_components() override;
  static absref absref::* aref[2];

 public:
  straight() : piv(), dir() {}
  straight(const point& fpiv, const vec& fdir)
      : piv(fpiv), dir(unit_vec(fdir)) {}
  straight(const point& fp1, const point& fp2) : piv(fp1), dir() {
    pvecerror("straight::straight(const point& fp1, const point& fp2)");
    if (fp1 == fp2) spexit(std::cout);
    dir = unit_vec(fp2 - fp1);
  }
  straight(const plane pl1, const plane pl2);
  // different parallel     vecerror=2
  // the same planes        vecerror=3

  /// Copy assignment operator.
  straight& operator=(const straight& fsl) {
    piv = fsl.piv;
    dir = fsl.dir;
    return *this;
  }
  /// Copy constructor.
  straight(const straight& s) : piv(s.piv), dir(s.dir) {}

  // The same line can have different piv's along it, and different vec's:
  // dir or -dir.
  friend int operator==(const straight& sl1, const straight& sl2);
  friend int operator!=(const straight& sl1, const straight& sl2) {
    return sl1 == sl2 ? 0 : 1;
  }
  friend bool apeq(const straight& sl1, const straight& sl2, double prec);

  /// Calculate distance of a point from the line and compare it with prec.
  /// Return 1 if the point is on the line.
  int check_point_in(const point& fp, double prec) const;

  /** Figure out whether the line crosses another straight line
   * (within a precision prec).
   * - Lines cross in one point (with precision prec) vecerror = 0
   * - Lines do not cross                             vecerror = 1
   * - Lines are parallel                             vecerror = 2
   * - Lines are identical                            vecerror = 3
   */
  point cross(const straight& sl, double prec) const;

  /// Shortest distance between two lines, may be negative.
  double vecdistance(const straight& sl, int& type_of_cross, point pt[2]) const;
  // type_of_cross has same meaning as vecerror from previous function,
  // But the precision is assumed to be 0.
  // pt inited only for type_of_cross == 1 and 0.
  // For type_of_cross == 0 pt[0]==pt[1]
  // pt[0] is point on this line. pt[1] it point on line sl.
  // It draws
  // ez = unit_vec(this->dir)
  // ey = unit_vec(this->dir || sl.dir)
  // ex = ey || ez
  // and declares syscoor with this->piv.
  // vecdistance is just y-coordinate of point of crossing of sl converting
  // to new syscoor with plane (ey, ez).

  double distance(const straight& sl, int& type_of_cross, point pt[2]) const;
  // shortest distance between lines, always positive.
  // type_of_cross has same meaning as vecerror from previous function
  // But the precision is assumed to be 0.
  // pt is inited only for type_of_cross == 1 and 0.
  // For type_of_cross == 0 pt[0]==pt[1]
  // pt[0] is point on this line. pt[1] is point on line sl.
  // It is absolute value of vecdistance

  double distance(const point& fpt) const;
  double distance(const point& fpt, point& fcpt) const;
  // calculates closest point on the line
};

}  // namespace Heed

#endif
