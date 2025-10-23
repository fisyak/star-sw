#ifndef TLINE_H
#define TLINE_H
#include <iostream>
/*
Copyright (c) 2005 Igor B. Smirnov

The file can be used, copied, modified, and distributed
according to the terms of GNU Lesser General Public License version 2.1
as published by the Free Software Foundation,
and provided that the above copyright notice, this permission notice,
and notices about any modifications of the original text
appear in all copies and in supporting documentation.
The file is provided "as is" without express or implied warranty.
*/

#include <vector>

#include "wcpplib/math/minmax.h"
#include "wcpplib/util/FunNameStack.h"

// #define TLINE_REDUCE_TO_RAW_ARR  // useful for acceleration of PointCoorMesh
//  if the type D keeps elements in consecutive array
//  whose address can be obtained as address of the first element.
//  In PointCoorMesh this all is switched by the following way:
// #ifndef TLINE_REDUCE_TO_RAW_ARR
//   D* amesh;
// #else
//   T* amesh;
// #endif
//  In constructors the assignment is switched by the following way:
// #ifndef TLINE_REDUCE_TO_RAW_ARR
//   amesh = famesh;
//   xmin = (*amesh)[0];
//   xmax = (*amesh)[q-1];
// #else
//   amesh = &((*famesh)[0]);
//   xmin = amesh[0];
//   xmax = amesh[q-1];
// #endif
//  Note that in both cases only the address is kept in this class and the
//  corresponding object is not copied.
//  If Copying is necessary, one can use CopiedPointCoorMesh.
//  Note that class CopiedPointCoorMesh, based on DynLinArr,
//  also provides acceleration based on the use of raw array
//  address and switched on by TLINE_REDUCE_TO_RAW_ARR.
//  Note that this class does not use .acu() functions of DynLinArr,
//  allowing for the use of unchecked fast access
//  (since these functions were written after tline was done).

namespace Heed {

template <class T, class D>
// D is anything allowing indexing
long t_find_interval(double x, long q, const D& coor) {
  long n1, n2, n3;
#ifndef TLINE_REDUCE_TO_RAW_ARR
  if (q <= 1) return -1;
  if (x < coor[0] || x > coor[q - 1]) return -1;
  if (x < coor[1]) return 0;
  if (x >= coor[q - 2]) return q - 2;
  n1 = 0;
  n2 = q - 1;
  while (n2 - n1 > 1) {
    n3 = n1 + (n2 - n1) / 2;
    if (x < coor[n3])
      n2 = n3;
    else
      n1 = n3;
  }
  return n1;
#else
  T* arr = &(coor[0]);  // take the address of the first element
  if (q <= 1) return -1;
  if (x < arr[0] || x > arr[q - 1]) return -1;
  if (x < arr[1]) return 0;
  if (x >= arr[q - 2]) return q - 2;
  n1 = 0;
  n2 = q - 1;
  while (n2 - n1 > 1) {
    n3 = n1 + (n2 - n1) / 2;
    if (x < arr[n3])
      n2 = n3;
    else
      n1 = n3;
  }
  return n1;

#endif
}

// Use (scan) only end of the array starting from index n_start
// as if it is 0
// The return index:
// -1 if less than corr[n_start] or more than coor[q-1]
// Index if inside

template <class T, class D>
long t_find_interval_end(double x, long q, const D& coor, long n_start) {
  long n1, n2, n3;
  if (n_start < 0 || n_start > q - 1) {
    std::cerr << " ERROR in t_find_interval_end(...):\n";
    std::cerr << "n_start < 0 || n_start > q-1\n";
    std::cerr << "n_start=" << n_start << ", q=" << q << '\n';
    spexit(std::cerr);
  }
#ifndef TLINE_REDUCE_TO_RAW_ARR
  // if(q <= 1) return -1;
  if (q - n_start <= 1) return -1;
  if (x < coor[n_start] || x > coor[q - 1]) return -1;
  if (x < coor[n_start + 1]) return n_start;
  if (x >= coor[q - 2]) return q - 2;
  n1 = n_start;
  n2 = q - 1;
  while (n2 - n1 > 1) {
    n3 = n1 + (n2 - n1) / 2;
    if (x < coor[n3])
      n2 = n3;
    else
      n1 = n3;
  }
  return n1;
#else
  T* arr = &(coor[0]);  // take the address of the first element
  // if(q <= 1) return -1;
  if (q - n_start <= 1) return -1;
  if (x < arr[n_start] || x > arr[q - 1]) return -1;
  if (x < arr[n_start + 1]) return n_start;
  if (x >= arr[q - 2]) return q - 2;
  n1 = n_start;
  n2 = q - 1;
  while (n2 - n1 > 1) {
    n3 = n1 + (n2 - n1) / 2;
    if (x < arr[n3])
      n2 = n3;
    else
      n1 = n3;
  }
  return n1;

#endif
}

/// Generic mesh with arbitrary steps.
/// The array determining the step edges is located somewhere outside.
/// In object of this class only the raw pointer is contained with consequences:

/*
Attention, here there is a raw pointer to mesh.
It is not possible to use the passive pointer since
if D is plain array, the reference cannot be registered.
This is deviation from methodology, but it is not clear what can
be done here. The mesh cannot be copyed or deleted after the PointCoorMesh
is initialized. Obviously, the latter should be initialized immidiately
before the use and not keept permanentely.
Obviously again, that sooner or later the user can forget about this
(the author also once almost forgot and was at the edge of error)
and try to initialize it permanantely and then copy together with the mesh.
This would be an error, which again confirms the correctness of the
object management methodology, which forbids to place the raw pointers
in classes. This class (below) may be understood as a temporary exclusion,
which should be treated with great care.
At construction q has meaning of number of points.
 */

template <class T, class D>
class PointCoorMesh {
 public:
  inline long get_qi() const { return q - 1; }
  inline T get_xmin() const { return xmin; }
  inline T get_xmax() const { return xmax; }
  inline void get_scoor(long n, T& b) const {
#ifndef TLINE_REDUCE_TO_RAW_ARR
    b = (*amesh)[n];
#else
    b = amesh[n];
#endif
  }

  int get_interval(T x, long& n1, T& b1, long& n2, T& b2) const;

  int get_interval_extrap(T x, long& n1, T& b1, long& n2, T& b2) const;

  PointCoorMesh(long fq,     // number of points, number of intervals
                             // is fq - 1.
                D* famesh);  // dimension is fq and the last index is fq-1
                             // This is the end point of the last interval

 private:
  long q{0};  // the number of points
              // The number of intervals is q-1.
              // Therefore q has to be 2 or more
#ifndef TLINE_REDUCE_TO_RAW_ARR
  D* amesh{nullptr};
#else
  T* amesh{nullptr};
#endif
  T xmin{0};
  T xmax{0};
  // auxiliary thing to accelerate finding intervals
  mutable T x_old{0};      // previous x for finding interval
  mutable long n_old{-1};  // -1 if there is nothing
};

template <class T, class D>
PointCoorMesh<T, D>::PointCoorMesh(long fq, D* famesh)
    : q(fq), x_old(0), n_old(-1) {
  if (q <= 1) {
    std::cerr << "ERROR in PointCoorMesh<T,D>::PointCoorMesh<T,D>:\n"
              << "q <= 1\n";
    std::cerr << "q=" << q << '\n';
    spexit(std::cerr);
  }
#ifndef TLINE_REDUCE_TO_RAW_ARR
  // amesh.put( famesh );
  amesh = famesh;
  xmin = (*amesh)[0];
  xmax = (*amesh)[q - 1];
#else
  amesh = &((*famesh)[0]);
  xmin = amesh[0];
  xmax = amesh[q - 1];
#endif
  // check consistence
  if (xmin > xmax) {
    std::cerr << "ERROR in PointCoorMesh<T,D>::PointCoorMesh<T,D>:\n"
              << "xmin > xmax\n";
    std::cerr << "xmin=" << xmin << ", xmax=" << xmax << '\n';
    spexit(std::cerr);
  }
}

template <class T, class D>
int PointCoorMesh<T, D>::get_interval(T x, long& n1, T& b1, long& n2,
                                      T& b2) const {
  if (x < xmin || x >= xmax) {
    n1 = 0;
    n2 = 0;
    b1 = 0;
    b2 = 0;
    return 0;
  }
#ifndef TLINE_REDUCE_TO_RAW_ARR
  if (n_old >= 0 && x_old <= x) {
    n1 = t_find_interval_end<T, D>(x, q, *amesh, n_old);
  } else {
    n1 = t_find_interval<T, D>(x, q, *amesh);
  }
// n1 = t_find_interval< T , D >(x, q, amesh);
#else
  if (n_old >= 0 && x_old <= x) {
    n1 = t_find_interval_end<T, T*>(x, q, amesh, n_old);
  } else {
    n1 = t_find_interval<T, T*>(x, q, amesh);
  }
// n1 = t_find_interval< T , T* >(x, q, &amesh);
#endif
  n2 = n1 + 1;
  if (n1 < 0 || n1 >= q || n2 < 0 || n2 >= q) {
    std::cerr << "ERROR in PointCoorMesh<T,D>::get_interval:\n"
              << "n1 < 0 || n1 >= q || n2 < 0 || n2 >= q\n";
    std::cerr << "n1=" << n1 << ", n2=" << n2 << '\n';
    spexit(std::cerr);
  }
#ifndef TLINE_REDUCE_TO_RAW_ARR
  b1 = (*amesh)[n1];
  b2 = (*amesh)[n2];
#else
  b1 = amesh[n1];
  b2 = amesh[n2];
#endif
  if (b1 < xmin || b1 > xmax || b2 < xmin || b2 > xmax) {
    std::cerr << "ERROR in PointCoorMesh<T,D>::get_interval:\n"
              << "b1 < xmin || b1 > xmax || b2 < xmin || b2 > xmax\n";
    std::cerr << "b1=" << b1 << ", b2=" << b2 << '\n';
    spexit(std::cerr);
  }
  n_old = n1;
  x_old = x;
  return 1;
}

template <class T, class D>
int PointCoorMesh<T, D>::get_interval_extrap(T x, long& n1, T& b1, long& n2,
                                             T& b2) const {
  int i_ret = 1;

  if (x < xmin) {
    i_ret = 0;
    n1 = 0;
    n2 = 1;
    b1 = xmin;
#ifndef TLINE_REDUCE_TO_RAW_ARR
    b2 = (*amesh)[1];
#else
    b2 = amesh[1];
#endif
  } else if (x >= xmax) {
    i_ret = 2;
    n1 = q - 2;
    n2 = q - 1;
#ifndef TLINE_REDUCE_TO_RAW_ARR
    b1 = (*amesh)[q - 2];
#else
    b1 = amesh[q - 2];
#endif
    b2 = xmax;
  } else {
#ifndef TLINE_REDUCE_TO_RAW_ARR
    if (n_old >= 0 && x_old <= x) {
      n1 = t_find_interval_end<T, D>(x, q, *amesh, n_old);
    } else {
      n1 = t_find_interval<T, D>(x, q, *amesh);
    }
// n1 = t_find_interval< T , D >(x, q, amesh);
#else
    if (n_old >= 0 && x_old <= x) {
      n1 = t_find_interval_end<T, T*>(x, q, amesh, n_old);
    } else {
      n1 = t_find_interval<T, T*>(x, q, amesh);
    }
// n1 = t_find_interval< T , T* >(x, q, &amesh);
#endif
    n2 = n1 + 1;
    if (n1 < 0 || n1 >= q || n2 < 0 || n2 >= q) {
      std::cerr << "ERROR in PointCoorMesh<T,D>::get_interval:\n"
                << "n1 < 0 || n1 >= q || n2 < 0 || n2 >= q\n";
      std::cerr << "n1=" << n1 << ", n2=" << n2 << '\n';
      spexit(std::cerr);
    }
#ifndef TLINE_REDUCE_TO_RAW_ARR
    b1 = (*amesh)[n1];
    b2 = (*amesh)[n2];
#else
    b1 = amesh[n1];
    b2 = amesh[n2];
#endif
    if (b1 < xmin || b1 > xmax || b2 < xmin || b2 > xmax) {
      std::cerr << "ERROR in PointCoorMesh<T,D>::get_interval:\n"
                << "b1 < xmin || b1 > xmax || b2 < xmin || b2 > xmax\n";
      std::cerr << "b1=" << b1 << ", b2=" << b2 << '\n';
      spexit(std::cerr);
    }
    n_old = n1;
    x_old = x;
  }
  return i_ret;
}

// The following program the same as previous, but
// considers the array already integrated.
// The algorithm is then much faster, since it uses binary search.
// It is used, in particular, for random numbers generation.

template <class T, class D, class M>
T t_find_x_for_already_integ_step_ar(const M& mesh,
                                     const D& y,  // array of function values
                                     T integ, int* s_err)  // for power = 0 only
{
  *s_err = 0;
  // check_econd11(xpower , != 0 , std::cerr);
  check_econd11(integ, < 0.0, std::cerr);
  long qi = mesh.get_qi();
  check_econd12(qi, <, 1, std::cerr);
  // if(x1 > x2) return 0.0;
  double xmin = mesh.get_xmin();
  double xmax = mesh.get_xmax();
  if (integ == 0.0) return xmin;
  if (integ > y[qi - 1]) {
    *s_err = 1;
    return xmax;
  }
  if (integ == y[qi - 1]) return xmax;
  if (integ < y[0]) {  // answer in the first bin
    T xp1(0.0);
    T xp2(0.0);
    mesh.get_scoor(0, xp1);
    mesh.get_scoor(1, xp2);
    return xp1 + (xp2 - xp1) * integ / y[0];
  }
  // binary search
  long nl = 0;
  long nr = qi - 1;
  long nc;
  while (nr - nl > 1) {
    nc = (nr + nl) / 2;
    if (integ < y[nc])
      nr = nc;
    else
      nl = nc;
  }
  T xl(0.0);
  T xr(0.0);
  mesh.get_scoor(nl + 1, xl);
  mesh.get_scoor(nr + 1, xr);
  // Note "+1" in the previous two expressions.
  // This arises from the fact that the nl'th element of
  // y-array contains integral of nl'th bin plus all previous bins.
  // So y[nl] is related to x of nl+1.
  T a = (xr - xl) / (y[nr] - y[nl]);
  T ret = xl + a * (integ - y[nl]);

  return ret;
}

// generate random number

template <class T, class D, class M>
T t_hisran_step_ar(const M& mesh, const D& integ_y, T rannum) {
  // check_econd11(xpower , != 0 , std::cerr);
  long qi = mesh.get_qi();
  long s_same = apeq_mant(integ_y[qi - 1], 1.0, 1.0e-12);
  check_econd11a(s_same, != 1.0, "integ_y[qi-1]=" << integ_y[qi - 1] << '\n',
                 std::cerr);

  // check_econd11(integ_y[qi-1] , != 1.0 , std::cerr);
  int s_err;

  T ret = t_find_x_for_already_integ_step_ar(mesh,     // dimension q
                                             integ_y,  // dimension q-1
                                             rannum, &s_err);
  // TODO (HS)!!
  // check_econd11a(s_err, != 0, "mesh=" << mesh << " integ_y=" << integ_y
  //                                     << " rannum=" << rannum << '\n',
  //                std::cerr);
  return ret;
  // return  t_find_x_for_already_integ_step_ar
  // (mesh,               // dimension q
  //  integ_y,                  // dimension q-1
  //  rannum,
  //  &s_err);
}

template <class T>
T t_value_straight_2point(T x1, T y1, T x2, T y2, T x, int s_ban_neg) {
  check_econd12(x1, ==, x2, std::cerr);

  T a = (y2 - y1) / (x2 - x1);
  // Less numerical precision
  // T b = y[n1];
  // T res = a * ( x - x1) + b;
  // More numerical precision (although it is not proved),
  // starting from what is closer to x
  T res;
  T dx1 = x - x1;
  T adx1 = (dx1 > 0) ? dx1 : -dx1;  // absolute value
  // if(dx1 > 0)
  //  adx1 = dx1;
  // else
  //  adx1 = -dx1;
  T dx2 = x - x2;
  T adx2 = (dx2 > 0) ? dx2 : -dx2;  // absolute value
  // if(dx2 > 0)
  //  adx2 = dx2;
  // else
  //  adx2 = -dx2;
  if (adx1 < adx2)  // x is closer to x1
  {
    res = a * dx1 + y1;
  } else {
    res = a * dx2 + y2;
  }
  if (s_ban_neg == 1 && res < 0.0) res = 0.0;
  return res;
}

template <class T>
T t_integ_straight_2point(T x1, T y1, T x2, T y2, T xl, T xr,
                          int xpower,  // currently 0 or 1
                          int s_ban_neg)
// 0 - not include, 1 - include
{
  check_econd12(x1, ==, x2, std::cerr);

  T a = (y2 - y1) / (x2 - x1);
  T b = y1;
  T yl = a * (xl - x1) + b;
  T yr = a * (xr - x1) + b;
  if (s_ban_neg == 1) {
    if (yl <= 0.0 && yr <= 0.0) return 0.0;
    if (yl < 0.0 || yr < 0.0) {
      T xz = x1 - b / a;
      if (yl < 0.0) {
        xl = xz;
        yl = 0.0;
      } else {
        xr = xz;
        yr = 0.0;
      }
    }
  }
  T res;
  if (xpower == 0)
    res = 0.5 * a * (xr * xr - xl * xl) + (b - a * x1) * (xr - xl);
  else
    res = a * (xr * xr * xr - xl * xl * xl) / 3.0 +
          0.5 * (b - a * x1) * (xr * xr - xl * xl);

  return res;
}

// Extract value defined by this array for abscissa x
// y have dimension q or qi+1.
template <class T, class D, class M>
T t_value_straight_point_ar(const M& mesh,
                            const D& y,  // array of function values
                            T x, int s_ban_neg, int s_extrap_left, T left_bond,
                            int s_extrap_right, T right_bond) {
  // 0 - not include, 1 - include
  double xmin = mesh.get_xmin();
  double xmax = mesh.get_xmax();
  if (x < left_bond) return 0.0;
  if (x > right_bond) return 0.0;
  if (x < xmin && s_extrap_left == 0) return 0.0;
  if (x > xmax && s_extrap_right == 0) return 0.0;
  long n1, n2;
  T b1, b2;
  mesh.get_interval_extrap(x, n1, b1, n2, b2);
  T x1;
  mesh.get_scoor(n1, x1);
  T x2;
  mesh.get_scoor(n2, x2);
  return t_value_straight_2point(x1, y[n1], x2, y[n2], x, s_ban_neg);
}

// Extract value defined by this array for abscissa x
template <class T, class D, class M>
T t_value_generic_point_ar(
    const M& mesh, const D& y,  // array of function values
    T (*funval)(T xp1, T yp1, T xp2, T yp2, T xmin,
                T xmax,  // may be necessary for shape determination
                T x),
    T x, int s_extrap_left, T left_bond, int s_extrap_right, T right_bond) {
  // 0 - not include, 1 - include
  double xmin = mesh.get_xmin();
  double xmax = mesh.get_xmax();
  if (x < left_bond) return 0.0;
  if (x > right_bond) return 0.0;
  if (x < xmin && s_extrap_left == 0) return 0.0;
  if (x > xmax && s_extrap_right == 0) return 0.0;
  long n1, n2;
  T b1, b2;
  mesh.get_interval_extrap(x, n1, b1, n2, b2);
  T x1;
  mesh.get_scoor(n1, x1);
  T x2;
  mesh.get_scoor(n2, x2);
  return funval(x1, y[n1], x2, y[n2], left_bond, right_bond, x);
}

// power function x^pw

// not debugged
// No, perhaps already  checked in some application.
// If power function cannot be drawn, it exits.

template <class T>
T t_value_power_2point(T x1, T y1, T x2, T y2, T x) {
  check_econd11(y1, <= 0.0, std::cerr);
  check_econd11(y2, <= 0.0, std::cerr);
  check_econd12(y1, ==, y2, std::cerr);
  check_econd12(x1, ==, x2, std::cerr);
  T res = y1;
  if (x1 <= 0.0 && x2 >= 0.0) {
    std::cerr << "T t_value_power_2point(...): \n";
    std::cerr << "x's are of different sign, power cannot be drawn\n";
    spexit(std::cerr);
  } else {
    T pw = log(y1 / y2) / log(x1 / x2);
    // check_econd11(pw , == -1.0 , std::cerr);
    res = y1 * pow(x, pw) / pow(x1, pw);
  }
  return res;
}

template <class T>
T t_integ_power_2point(T x1, T y1, T x2, T y2, T xl, T xr)
// 0 - not include, 1 - include
{
  check_econd11(y1, <= 0.0, std::cerr);
  check_econd11(y2, <= 0.0, std::cerr);
  check_econd12(y1, ==, y2, std::cerr);
  check_econd12(x1, ==, x2, std::cerr);
  T pw = log(y1 / y2) / log(x1 / x2);
  check_econd11(pw, == -1.0, std::cerr);
  T k = y1 * pow(x1, -pw);
  T t = k / (1 + pw) * (pow(xr, (pw + 1)) - pow(xl, (pw + 1)));
  return t;
}

template <class T, class D, class M>
T t_integ_generic_point_ar(const M& mesh, const D& y,  // array of function
                                                       // values GENERICFUN fun,
                           T (*fun)(T xp1, T yp1, T xp2, T yp2, T xmin, T xmax,
                                    T x1, T x2),
                           T x1, T x2, int s_extrap_left, T left_bond,
                           int s_extrap_right, T right_bond) {
  check_econd12(x1, >, x2, std::cerr);
  long qi = mesh.get_qi();
  check_econd12(qi, <, 1, std::cerr);
  // if(x1 > x2) return 0.0;
  double xmin = mesh.get_xmin();
  double xmax = mesh.get_xmax();
  if (x2 <= xmin && s_extrap_left == 0) return 0.0;
  if (x1 >= xmax && s_extrap_right == 0) return 0.0;
  if (x2 <= left_bond) return 0.0;
  if (x1 >= right_bond) return 0.0;
  // long istart, iafterend; // indexes to sum total intervals
  if (x1 < left_bond) x1 = left_bond;
  if (x2 > right_bond) x2 = right_bond;
  if (x1 <= xmin && s_extrap_left == 0) x1 = xmin;
  if (x2 > xmax && s_extrap_left == 0) x2 = xmax;
  long np1, np2;
  T bp1, bp2;
  int i_ret = 0;
  // restore the interval in which x1 reside
  i_ret = mesh.get_interval_extrap(x1, np1, bp1, np2, bp2);
  // restore the x-coordinates of given points
  T xp1;
  mesh.get_scoor(np1, xp1);
  T xp2;
  mesh.get_scoor(np2, xp2);
  T res;
  T yp1 = y[np1];
  T yp2 = y[np2];
  if (i_ret == 2 || x2 <= xp2)  // then all in one interval
  {
    res = fun(xp1, yp1, xp2, yp2, xmin, xmax, x1, x2);
  } else {
    // integrate only till end of the current interval
    T x1i = x1;
    T x2i = xp2;
    res = fun(xp1, yp1, xp2, yp2, xmin, xmax, x1i, x2i);
    // x2i = x1;  // prepere for loop
    int s_stop = 0;
    do {
      np1 = np2;
      np2++;
      xp1 = xp2;
      mesh.get_scoor(np2, xp2);
      x1i = x2i;
      if (xp2 >= x2) {
        x2i = x2;  // till end of integral
        s_stop = 1;
      } else {
        if (np2 == qi)  // end of the mesh, but x2 is farther
        {
          x2i = x2;  // till end of integral
          s_stop = 1;
        } else {
          x2i = xp2;  // till end of current interval
          s_stop = 0;
        }
      }
      yp1 = yp2;
      yp2 = y[np2];
      res += fun(xp1, yp1, xp2, yp2, xmin, xmax, x1i, x2i);

    } while (s_stop == 0);
  }
  return res;
}

}  // namespace Heed

#endif
