#ifndef POLYLINE_H
#define POLYLINE_H
#include <cmath>

#include "wcpplib/geometry/plane.h"
#include "wcpplib/geometry/straight.h"
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

/// Polyline.

class polyline : public absref {
 protected:
  int qpt;
  point* pt;
  int qsl;
  straight* sl;

 public:
  int Gqpt() const { return qpt; }
  point Gpt(int n) const {
    if (n >= qpt) {
      std::cerr << "error in polyline:Gpt(int n): n>qpt: n=" << n
                << " qpt=" << qpt << '\n';
      spexit(std::cerr);
    }
    return pt[n];
  }
  int Gqsl() const { return qsl; }
  straight Gsl(int n) const {
    if (n >= qsl) {
      std::cerr << "error in polyline:Gpt(int n): n>qsl: n=" << n
                << " qsl=" << qsl << '\n';
      spexit(std::cerr);
    }
    return sl[n];
  }

 protected:
  absref** aref;
  virtual absref_transmit get_components() override;

 public:
  /// Return whether a point is inside.
  /// 0 point is not in
  /// 1 point coincides with an edge
  /// 2 point is inside an interval
  int check_point_in(const point& fpt, double prec) const;

  /// If straight line goes exactly by segment of polyline,
  /// the fuction gives two end points of adjacent segments and the
  /// segment itself.
  /// If one of the points is common, it is given several times.
  /// For example, if line crosses break point the point is given two times.
  int cross(const straight& fsl, point* pc, int& qpc, polyline* pl, int& qpl,
            double prec) const;
  /// Distance between two intervals.
  double dist_two_inter(polyline& pl, double prec) const;
  double distance(const point& fpt) const;
  /// Distance between two points.
  double distance(const point& fpt, point& cpt) const;

 protected:
  void polyline_init(const point* fpt, int fqpt);
  void polyline_del() {
    if (pt) {
      delete[] pt;
      pt = NULL;
    }
    if (sl) {
      delete[] sl;
      sl = NULL;
    }
    if (aref) {
      delete[] aref;
      aref = NULL;
    }
  }

 public:
  polyline() {
    point ptl;
    polyline_init(&ptl, 0);
  }

  polyline(polyline& pl);
  polyline(const polyline& pl);

  polyline(const point* fpt, int fqpt);
  polyline(const point& fpt1, const point& fpt2);  // interval

  polyline& operator=(const polyline& fpl);

  ~polyline() { polyline_del(); }
  friend int plane::cross(const polyline& pll, point* crpt, int& qcrpt,
                          polyline* crpll, int& qcrpll, double prec) const;
};

}  // namespace Heed

#endif
