#include "wcpplib/geometry/surface.h"

#include <iostream>

#include "wcpplib/geometry/circumf.h"
#include "wcpplib/geometry/polyline.h"
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

// **** splane ****
absref absref::* splane::aref_splane[2] = {(absref absref::*)&splane::pn,
                                           (absref absref::*)&splane::dir_ins};

absref_transmit splane::get_components() {
  return absref_transmit(2, aref_splane);
}

int splane::check_point_inside(const point& fpt, const vec& dir,
                               double fprec) const {
  if (dir == dv0) {
    // this is not useful
    if (fpt == pn.Gpiv()) return 1;
    vec v = fpt - pn.Gpiv();
    if (cos2vec(dir_ins, v) >= -vprecision) return 1;
    return 0;
  }
  if (pn.check_point_in(fpt, fprec) == 1) {
    double ca = cos2vec(dir, dir_ins);
    if (ca < 0) return 0;
    return 1;
  }
  vec v = fpt - pn.Gpiv();
  if (cos2vec(dir_ins, v) >= 0) return 1;
  return 0;
}

int splane::check_point_inside1(const point& fpt, int s_ext,
                                double fprec) const {
  if (pn.check_point_in(fpt, fprec) == 1) {
    if (s_ext == 1) return 0;
    return 1;
  }
  vec v = fpt - pn.Gpiv();
  if (cos2vec(dir_ins, v) > 0) return 1;
  return 0;
}

int splane::range(const trajestep& fts, double* crange, point* cpt,
                  int* s_ext) const {
  if (fts.s_range_cf == 0) {
    // straight line
    point pt = pn.cross(straight(fts.currpos, fts.dir));
    if (vecerror != 0) {
      vecerror = 0;
      return 0;
    }
    double rng = (pt - fts.currpos).length();
    if (pt == fts.currpos || check_par(pt - fts.currpos, fts.dir, 0.01) == 1) {
      //                                   looks like not matter ^
      // otherwise the point is behind plane
      if (fts.mrange >= rng) {
        // otherwise it can not reach the plane
        cpt[0] = pt;
        crange[0] = rng;
        double t = cos2vec(fts.dir, dir_ins);
        if (t < 0)
          s_ext[0] = 1;
        else if (t > 0)
          s_ext[0] = 0;
        else
          s_ext[0] = 2;
        return 1;
      }
      return 0;
    } else
      return 0;
  } else {
    point pt[2];
    circumf cf(fts.currpos + fts.relcen,
               fts.dir || fts.relcen,  // if to us, moving against clock
               fts.relcen.length());
    int q = cf.cross(pn, pt, 0.0);
    if (q == -1) {
      // total circle lies in the plane
      cpt[0] = fts.currpos;
      crange[0] = 0.0;
      s_ext[0] = 2;
      return 1;
    }
    if (q == 0) return 0;
    if (q == 1) {
      vec r1 = -fts.relcen;
      vec r2 = pt[0] - cf.Gpiv();
      double angle = ang2projvec(r1, r2, cf.Gdir());
      double rng = cf.Grad() * angle;
      if (fts.mrange >= rng) {
        cpt[0] = pt[0];
        crange[0] = rng;
        double c = cos2vec(dir_ins, fts.relcen);
        if (angle == 0.0) {
          // cross in the current point
          if (c > 0)
            s_ext[0] = 0;
          else if (c < 0)
            s_ext[0] = 1;
          else
            s_ext[0] = 2;
        } else {
          if (c > 0)
            s_ext[0] = 1;
          else if (c < 0)
            s_ext[0] = 0;
          else
            s_ext[0] = 2;
        }
        return 1;
      } else
        return 0;
    }
    if (q == 2) {
      int qq = 0;
      vec r = -fts.relcen;
      vec vcr[2];
      vcr[0] = pt[0] - cf.Gpiv();
      vcr[1] = pt[1] - cf.Gpiv();
      double angle[2];
      angle[0] = ang2projvec(r, vcr[0], cf.Gdir());
      angle[1] = ang2projvec(r, vcr[1], cf.Gdir());
      if (angle[0] > angle[1]) {  // ordering
        double a = angle[0];
        angle[0] = angle[1];
        angle[1] = a;
        point p = pt[0];
        pt[0] = pt[1];
        pt[1] = p;
      }
      double rng;
      rng = cf.Grad() * angle[0];
      if (fts.mrange >= rng) {
        // find out what the first point means
        int ins = 0;  // 1 if the point inside and exits
        vec td = fts.dir;
        td.turn(cf.Gdir(), angle[0]);  // local dir in the crossing point
        double t = cos2vec(td, dir_ins);
        if (t < 0)
          ins = 1;  // means the point was inside and now exiting
        else
          ins = 0;
        cpt[0] = pt[0];
        crange[0] = rng;
        s_ext[0] = ins;
        qq++;
        rng = cf.Grad() * angle[1];
        if (fts.mrange >= rng) {
          cpt[1] = pt[1];
          crange[1] = rng;
          s_ext[1] = (ins == 0 ? 1 : 0);
          qq++;
        }
      }
      return qq;
    }
  }
  return 0;
}

// **** ulsvolume ****
absref_transmit ulsvolume::get_components() {
  for (int n = 0; n < qsurf; n++) adrsurf[n] = surf[n].get();
  return absref_transmit(qsurf, (absref**)adrsurf);
}

int ulsvolume::check_point_inside(const point& fpt, const vec& dir) const {
  check_econd11(qsurf, <= 0, std::cerr);
  for (int n = 0; n < qsurf; n++) {
    if (!(surf[n].get()->check_point_inside(fpt, dir, prec))) {
      return 0;
    }
  }
  return 1;
}

int ulsvolume::range_ext(trajestep& fts, int s_ext) const {
  check_econd11(qsurf, <= 0, std::cerr);
  constexpr int pqcrossurf = 4;
  double crange[pqcrossurf];
  point cpt[pqcrossurf];
  int fs_ext[pqcrossurf];
  int n, m, nc;
  int s = 0;  // sign of crossing
  if (s_ext == 1) {
    for (n = 0; n < qsurf; n++) {
      int qc = surf[n].get()->range(fts, crange, cpt, fs_ext);
      for (m = 0; m < qc; m++) {
        if (fs_ext[m] == 1) {
          s = 1;
          // The last minute change, it was 0 somewhy instead of m
          fts.mrange = crange[m];  // reduce the range
          fts.mpoint = cpt[m];
          break;  // take only the first exit point, it should be closest
        } else if (fs_ext[m] == 0) {
          if (!(surf[n].get()->check_point_inside(fts.currpos, fts.dir,
                                                  prec))) {
            std::cerr
                << "\nshould never happen\n"
                << "It may happen if you  call this function with s_ext==1\n"
                << "for point outside the volume\n";
            spexit(std::cerr);
          }
        } else if (fs_ext[m] == 2)
          break;  // don't know what to do, safe to ignore
      }
    }

    if (s == 1) {
      fts.s_prec = 0;
    }
    return s;
  } else {       // for if(s_ext==1)
    int ss = 0;  // sign that there is cross with any of the surfaces
    for (n = 0; n < qsurf; n++) {
      int qc = surf[n].get()->range(fts, crange, cpt, fs_ext);
      for (nc = 0; nc < qc; nc++)  // loop by crossing points
      {
        if (fs_ext[nc] == 0)  // thus ignoring exitted surfaces
        {
          s = 1;
          for (m = 0; m < qsurf; m++)  // scan other surfaces and verify that
          {                            // the crossing point is inside
            if (m != n) {
              if (surf[m].get()->check_point_inside1(cpt[nc], fs_ext[nc],
                                                     prec) == 0) {
                s = 0;
                break;
              }
            }
          }
          if (s == 1) {
            ss = 1;
            fts.mrange = crange[nc];
            fts.mpoint = cpt[nc];
            break;  // since points are ordered, go to next surface,
                    // may be there is nearer crossing point
          }
        }
      }
    }
    if (ss == 1) {
      fts.s_prec = 0;
    }
    return ss;
  }
}
/*
// Old comment, may be not valid, or not at the right place:
// Straight track:
//Two variants of behavior:
//From outside:
//1. For each cross section from right side to check if the crossing point is
// from internal side from each other surfaces
//2. Find the most father point of cross section  for right side
// and to check if it is  from internal side for all other surfaces.

//From inside:
//1. For each cross section from right side to check if the crossing point is
// from internal side from each other surfaces
//2. Find the nearest point of cross section  for right side
//there is no need to check: cross point must exist.

//I choose number 2. Reason: for outside number 1 the number of checking is
//proportional  number_of_surf**2
*/

void ulsvolume::ulsvolume_init(
    const std::vector<std::shared_ptr<surface> >& fsurf, double fprec) {
  prec = fprec;
  if (qsurf > 0) {
    for (int n = 0; n < qsurf; ++n) surf[n].reset();
  }
  qsurf = fsurf.size();
  for (int n = 0; n < qsurf; ++n) {
    surf[n] = fsurf[n];
  }
}

ulsvolume::ulsvolume(const std::vector<std::shared_ptr<surface> >& fsurf,
                     double fprec)
    : qsurf(fsurf.size()) {
  check_econd12(qsurf, >, pqqsurf, std::cerr);
  prec = fprec;
  for (int n = 0; n < qsurf; ++n) surf[n] = fsurf[n];
}

ulsvolume::ulsvolume(ulsvolume& f) : absref(f), absvol(f), qsurf(f.qsurf) {
  check_econd12(f.qsurf, >, pqqsurf, std::cerr);
  prec = f.prec;
  for (int n = 0; n < qsurf; ++n) surf[n] = f.surf[n];
}

ulsvolume::ulsvolume(const ulsvolume& f)
    : absref(f), absvol(f), qsurf(f.qsurf) {
  check_econd12(f.qsurf, >, pqqsurf, std::cerr);
  prec = f.prec;
  for (int n = 0; n < qsurf; ++n) surf[n] = f.surf[n];
}

}  // namespace Heed
