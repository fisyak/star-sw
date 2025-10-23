#include "wcpplib/geometry/polyline.h"

#include <iostream>
#include <limits>

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

// **** polyline  ****
absref_transmit polyline::get_components() {
  return absref_transmit(qpt + qsl, aref);
}

polyline::polyline(polyline& pl) : absref(pl) { polyline_init(pl.pt, pl.qpt); }
polyline::polyline(const polyline& pl) : absref(pl) {
  polyline_init(pl.pt, pl.qpt);
}
polyline::polyline(const point* fpt, int fqpt) { polyline_init(fpt, fqpt); }
polyline::polyline(const point& fpt1, const point& fpt2) {
  // interval
  point fpt[2];
  fpt[0] = fpt1;
  fpt[1] = fpt2;
  polyline_init(fpt, 2);
}

polyline& polyline::operator=(const polyline& fpl) {
  polyline_del();
  polyline_init(fpl.pt, fpl.qpt);
  return *this;
}

void polyline::polyline_init(const point* fpt, int fqpt) {
  check_econd11(fqpt, < 0, std::cerr) if (fqpt < 1) {
    qpt = 0;
    qsl = 0;
    pt = NULL;
    sl = NULL;
    aref = NULL;
    return;
  }
  pt = new point[fqpt];
  for (qpt = 0; qpt < fqpt; ++qpt) pt[qpt] = fpt[qpt];
  if (fqpt >= 2) {
    sl = new straight[qpt - 1];
    for (qsl = 0; qsl < qpt - 1; ++qsl) {
      sl[qsl] = straight(pt[qsl], pt[qsl + 1]);
    }
  } else {
    sl = NULL;
  }
  aref = new absref*[qpt + qsl];
  for (int n = 0; n < qpt; ++n) aref[n] = &pt[n];
  for (int n = 0; n < qsl; ++n) aref[n + qpt] = &sl[n];
}

int polyline::check_point_in(const point& fpt, double prec) const {
  pvecerror("int polyline::check_point_in(point& fpt, double prec)");
  for (int n = 0; n < qpt; ++n) {
    if (apeq(pt[n], fpt, prec)) return 1;
  }
  for (int n = 0; n < qsl; ++n) {
    if (sl[n].check_point_in(fpt, prec) == 1) {
      vec v1 = fpt - pt[n];
      vec v2 = fpt - pt[n + 1];
      if (check_par(v1, v2, prec) == -1) {
        // anti-parallel vectors, point inside borders
        return 2;
      }
    }
  }
  return 0;
}

int polyline::cross(const straight& fsl, point* pc, int& qpc, polyline* pl,
                    int& qpl, double prec) const {
  pvecerror("void polyline::cross(const straight& fsl, ...)");
  qpc = 0;
  qpl = 0;
  for (int n = 0; n < qsl; ++n) {
    pc[qpc] = sl[n].cross(fsl, prec);
    if (vecerror == 1 || vecerror == 2) {
      // lines do not cross
      vecerror = 0;
    } else if (vecerror == 3) {
      // the same straight line
      pl[qpl++] = polyline(&(pt[n]), 2);
    } else {
      vec v1 = pc[qpc] - pt[n];
      if (v1.length() < prec) {
        qpc++;
      } else {
        vec v2 = pc[qpc] - pt[n + 1];
        if (v2.length() < prec) {
          qpc++;
        } else if (check_par(v1, v2, prec) == -1) {
          // anti-parallel vectors, point inside borders
          qpc++;
        }
      }
    }
  }
  if (qpc > 0 || qpl > 0) return 1;
  return 0;
}

double polyline::dist_two_inter(polyline& pl2, double prec) const {
  pvecerror("double polyline::dist_two_inter(polyline& pl)");
  const polyline& pl1 = *this;
  check_econd11(pl1.Gqpt(), != 2, std::cerr);
  check_econd11(pl2.Gqpt(), != 2, std::cerr);
  point cpt[2];
  int type_of_cross;
  double sldist = pl1.Gsl(0).distance(pl2.Gsl(0), type_of_cross, cpt);
  if (type_of_cross == 2 || type_of_cross == 3) return sldist;
  if (pl1.check_point_in(cpt[0], prec) > 0 &&
      pl2.check_point_in(cpt[1], prec) > 0)
    return sldist;
  double mx = std::numeric_limits<double>::max();
  double r;
  if ((r = pl1.distance(pl2.Gpt(0))) < mx) mx = r;
  if ((r = pl1.distance(pl2.Gpt(1))) < mx) mx = r;
  if ((r = pl2.distance(pl1.Gpt(0))) < mx) mx = r;
  if ((r = pl2.distance(pl1.Gpt(1))) < mx) mx = r;
  return mx;
}

double polyline::distance(const point& fpt) const {
  pvecerror("double polyline::distance(const point& fpt) const");
  check_econd11(qsl, <= 0, std::cerr);
  double sldist;
  point cpt;
  double mx = std::numeric_limits<double>::max();
  int n;
  for (n = 0; n < qsl; n++) {
    sldist = sl[n].distance(fpt, cpt);
    vec v1 = cpt - pt[n];
    vec v2 = cpt - pt[n + 1];
    if (check_par(v1, v2, 0.01) ==
        -1) {  // anti-parallel vectors, point inside borders
      if (sldist < mx) mx = sldist;
    } else {
      if ((sldist = (fpt - pt[n]).length()) < mx) mx = sldist;
      if ((sldist = (fpt - pt[n + 1]).length()) < mx) mx = sldist;
    }
  }
  return mx;
}

double polyline::distance(const point& fpt, point& fcpt) const {
  pvecerror("double polyline::distance(const point& fpt) const");
  check_econd11(qsl, <= 0, std::cerr);
  double sldist;
  point cpt;
  double mx = std::numeric_limits<double>::max();
  int n;
  for (n = 0; n < qsl; n++) {
    sldist = sl[n].distance(fpt, cpt);
    vec v1 = cpt - pt[n];
    vec v2 = cpt - pt[n + 1];
    if (check_par(v1, v2, 0.01) ==
        -1) {  // anti-parallel vectors, point inside borders
      if (sldist < mx) {
        mx = sldist;
        fcpt = cpt;
      }
    } else {
      if ((sldist = (fpt - pt[n]).length()) < mx) {
        mx = sldist;
        fcpt = pt[n];
      }
      if ((sldist = (fpt - pt[n + 1]).length()) < mx) {
        mx = sldist;
        fcpt = pt[n + 1];
      }
    }
  }
  return mx;
}

}  // namespace Heed
