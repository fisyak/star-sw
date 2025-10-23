#ifndef VEC_H
#define VEC_H

/*
The base geometry file, determines class for geometrical conversions absref,
vectors (vec), bases, points, and coordinate systems.
Points differ from vectors in the conversions.
Point is a vector denoting the position with respect to the center of
coordinates. The vector is notation of direction. The vector is not
changed at parallel translations of basis or system of coordinates,
whereas the point is changed. Other explanations in my preprint
"SpaceMetricLib, geometrical class library for detector modeling in HEP"


Copyright (c) 2000 Igor B. Smirnov

The file can be used, copied, modified, and distributed
according to the terms of GNU Lesser General Public License version 2.1
as published by the Free Software Foundation,
and provided that the above copyright notice, this permission notice,
and notices about any modifications of the original text
appear in all copies and in supporting documentation.
The file is provided "as is" without express or implied warranty.
*/
#include <iostream>

#include "wcpplib/geometry/vfloat.h"
#include "wcpplib/util/FunNameStack.h"

#define pvecerror(string)                                          \
  if (vecerror != 0) {                                             \
    std::cerr << "vecerror is not zero, program is terminated\n"   \
              << " function detected error is " << string << '\n'; \
    spexit(std::cerr);                                             \
  }
#define pvecerrorp(string)                                         \
  if (vecerror != 0) {                                             \
    std::cerr << "vecerror is not zero, program is terminated\n"   \
              << " function detected error is " << string << '\n'; \
    spexit(std::cerr);                                             \
  }
// pvecerror is put after first line of function.
// It makes up stack of functions names if FUNNAMESTACK is defined.
// To work correctly stackline(string); should not be in any additional {}

// #include "wcpplib/geometry/vfloat.h"

namespace Heed {

extern int vecerror;

class vec;
class basis;  // It is ortogonal basis
class abssyscoor;
class point;

class absref_transmit;

/// Abstract reference, base class for any geometrical vector object.
/// Used for arranging of shift, turn and shange of coordinate system of
/// vector objects. Four functions down(), up(), turn(), and shift() do that
/// by calling of the same functions for any vector objects which are parts
/// of this class.
/// Address of parts lets known by virtual function get_components()
/// which is reloaded in any derivative class.
/// Class vec represents three-vectors and
/// reloads the functions down(), up(), turn() with proper functions
/// manipulating with three-vectors.
/// Function shift() is also reloaded and does nothing for 3-vector vec,
/// since it is assumed that 3-vector is characteristic of direction only,
/// not point in space. We can not shift direction.
/// For this reason, class point representing point in space
/// reloads functions down and up again, and, of course, reloads shift.
/// To make proper shift at switch to coordinate system with shifted center
/// the point::down() and point::up() functions apply point::shift() function
/// after or before vec::down() and vec::up().

class absref {
 public:
  /// Destructor
  virtual ~absref() {}
  /// Convert numbering representation of object to basical system of fasc
  virtual void down(const abssyscoor* fasc);
  /// Convert numbering representation of objects to new system
  virtual void up(const abssyscoor* fasc);
  /// Turn around axis doing via center of coordinate system along dir.
  virtual void turn(const vec& dir, double angle);
  virtual void shift(const vec& dir);

 private:
  virtual absref_transmit get_components();
};

/// Container for transmitting geometry transformations.
/// Three methods of transmission (fast, slower and slowest) are available.
class absref_transmit {
 public:
  absref_transmit() = default;
  // For transmitting the members of the class, when
  // their relative addresses are available.
  absref_transmit(int fqaref, absref absref::** faref)
      : qaref(fqaref), aref(faref) {}
  absref_transmit(int fqaref_pointer, absref** faref_pointer)
      : qaref_pointer(fqaref_pointer), aref_pointer(faref_pointer) {}

  absref_transmit(int fqaref, absref absref::** faref, int fqaref_pointer,
                  absref** faref_pointer)
      : qaref(fqaref),
        aref(faref),
        qaref_pointer(fqaref_pointer),
        aref_pointer(faref_pointer) {}
  /// Copy constructor.
  absref_transmit(const absref_transmit&) = default;
  /// Assignment operator.
  absref_transmit& operator=(const absref_transmit&) = default;
  /// Destructor.
  virtual ~absref_transmit() {}

  /// Number of vector objects which are the members of the class
  int qaref = 0;
  /// Reference to address of array containing their relative addresses
  /// as class members.
  absref absref::** aref;

  // When the relative addresses are not available, in particular
  // when the component object is located in heap memory:
  // Number of vector objects
  int qaref_pointer = 0;

  // Reference to address of array containing addresses of objects.
  absref** aref_pointer;

  // For any method of the object location the pointers can also be
  // transmitted through the function get_other(int n)
  // which receive the index of requested object and returns its address.
  // For this the user should determine the class derived
  // from absref_transmit. This is the slowest method of transmission.

  /// Number of objects available though virtual function GetOther.
  int qaref_other = 0;
  /// This function is meant to be redefined in derived classes to
  /// obtain additional address except those contained in aref and aref_pointer.
  /// This default version always returns NULL.
  virtual absref* get_other(int n);
};

#define ApplyAnyFunctionToVecElements(func)                        \
  {                                                                \
    auto aref_tran = get_components();                             \
    int q = aref_tran.qaref;                                       \
    for (int n = 0; n < q; n++) (this->*(aref_tran.aref[n])).func; \
    q = aref_tran.qaref_pointer;                                   \
    for (int n = 0; n < q; n++) aref_tran.aref_pointer[n]->func;   \
    q = aref_tran.qaref_other;                                     \
    for (int n = 0; n < q; n++) {                                  \
      absref* ar = aref_tran.get_other(n);                         \
      if (!ar) break;                                              \
      ar->func;                                                    \
    }                                                              \
  }

/// Vector.
/// Each vector is presented by three components and corresponds to some basis.
/// // The components are a projection of the vector to unit basis vectors.
/// If bas==NULL then it is the primary basis.
/// So the concept of vector is more primary concept with comparison of
/// basis, since one can not postulate basis while vectors do not exist.

class vec : public absref {
 public:
  /// Constructor.
  vec(double xx, double yy, double zz) {
    x = xx;
    y = yy;
    z = zz;
  }
  /// Default constructor.
  vec() = default;
  /// Destructor
  virtual ~vec() {}

  double x = 0.;
  double y = 0.;
  double z = 0.;

  double length() const { return sqrt(x * x + y * y + z * z); }
  double length2() const { return x * x + y * y + z * z; }

  vec down_new(const basis* fabas);
  vec up_new(const basis* fabas_new);

  void down(const basis* fabas);
  void up(const basis* fabas_new);

  vec down_new(const abssyscoor* fasc);
  vec up_new(const abssyscoor* fasc);

  void down(const abssyscoor* fasc) override;
  void up(const abssyscoor* fasc) override;

  /// Make new turned vector and leave this one unchanged.
  vec turn_new(const vec& dir, double angle);
  /// Turn this vector
  void turn(const vec& dir, double angle) override;
  void shift(const vec& dir) override;

  /// Generate random unit vector in plane perpendicular to z-axis.
  void random_round_vec();
  /// Generate random unit vector in any direction in conus
  /// with symmetry axis along z-axis and with angle theta (radian).
  void random_conic_vec(double theta);
  // Generate random unit vector in any direction in 3D space.
  void random_sfer_vec();

  friend vec operator*(const vec& v, double p) {
    return vec(v.x * p, v.y * p, v.z * p);
  }
  friend vec operator*=(vec& v, double p) {
    v = v * p;
    return v;
  }
  friend vec operator*(double p, const vec& v) {
    return vec(v.x * p, v.y * p, v.z * p);
  }
  vec operator/(double p) const { return vec(x / p, y / p, z / p); }
  friend vec operator/=(vec& v, double p) {
    v = v / p;
    return v;
  }
  friend vec operator+(const vec& r1, const vec& r2) {
    return vec(r1.x + r2.x, r1.y + r2.y, r1.z + r2.z);
  }
  friend vec& operator+=(vec& r1, const vec& r2) {
    r1 = r1 + r2;
    return r1;
  }
  friend vec operator-(const vec& r1, const vec& r2) {
    return vec(r1.x - r2.x, r1.y - r2.y, r1.z - r2.z);
  }
  friend vec operator-=(vec& r1, const vec& r2) {
    r1 = r1 - r2;
    return r1;
  }
  friend vec operator-(const vec& r) { return vec(-r.x, -r.y, -r.z); }
  friend double operator*(const vec& r1, const vec& r2) {
    return r1.x * r2.x + r1.y * r2.y + r1.z * r2.z;
  }
  /// Vector product.
  friend vec operator||(const vec& r1, const vec& r2) {
    return vec(r1.y * r2.z - r1.z * r2.y, r1.z * r2.x - r1.x * r2.z,
               r1.x * r2.y - r1.y * r2.x);
  }
  /// Return 1 if precisely the same vectors and 0 otherwise.
  friend inline int operator==(const vec& r1, const vec& r2) {
    if (r1.x == r2.x && r1.y == r2.y && r1.z == r2.z)
      return 1;
    else
      return 0;
  }
  /// Return 0 if precisely the same vectors and 1 otherwise.
  friend inline int operator!=(const vec& r1, const vec& r2) {
    if (r1 == r2)
      return 0;
    else
      return 1;
  }

  /// Return true if two vectors are approximately the same.
  friend inline bool apeq(const vec& r1, const vec& r2, double prec) {
    return (apeq(r1.x, r2.x, prec) && apeq(r1.y, r2.y, prec) &&
            apeq(r1.z, r2.z, prec));
  }

  friend inline vec unit_vec(const vec& v) {
    // pvecerror("inline vec unit_vec(const vec &v)");
    const double len = v.length();
    if (len == 0) {
      std::cerr << "error in unit_vec: length(vec)=0\n";
      spexit(std::cerr);
    }
    return vec(v.x / len, v.y / len, v.z / len);
  }
  // cosinus of angle between vectors
  // If one of vectors has zero length, it makes vecerror=1 and returns 0.
  friend double cos2vec(const vec& r1, const vec& r2);
  //  angle between vectors, in interval [0, M_PI]
  // If one of vectors has zero length, it makes vecerror=1.
  friend double ang2vec(const vec& r1, const vec& r2);
  friend vec project_to_plane(const vec& r, const vec& normal);
  // angle between projections of 2 vectors on plane normal to vector normal
  // in interval [0, 2*M_PI]
  // If one of vectors has zero length, it makes vecerror=1.
  friend double ang2projvec(const vec& r1, const vec& r2, const vec& normal);
  // sinus of angle between vectors, 0 or positive.
  // If one of vectors has zero length, it makes vecerror=1.
  friend double sin2vec(const vec& r1, const vec& r2);

  /// Check whether two vectors are parallel, or anti-parallel.
  /// Returns: 1 - parallel, -1  - antiparallel, 0 not parallel.
  /// Also returns 0 if one or both vectors have zero length.
  /// Thus, if angle between vectors < prec, they are parallel.
  friend inline int check_par(const vec& r1, const vec& r2, double prec) {
    // 1 par, -1 antipar, 0 not parallel
    double a = ang2vec(r1, r2);
    if (vecerror != 0) {
      vecerror = 0;
      return 0;
    }
    if (a <= prec) return 1;
    if (a >= M_PI - std::max(prec, vprecision)) {
      // If without max(prec, vprecision) but with just -prec
      // Even for exactly parallel vectors this function
      // would never confirm this.
      if (prec < vprecision) {
        vec anti_r2 = -r2;         // reverse the vector
        a = ang2vec(r1, anti_r2);  // M_PI - old_a
        if (a <= prec) return -1;
      } else {
        return -1;
      }
    }
    return 0;
  }

  /// Check whether two vectors are perpendicular.
  /// Returns: 1 perpendicular, 0 not perpendicular.
  /// Also returns 0 if one or both vectors have zero length.
  /// Thus, if angle between vectors
  /// a > 0.5 * M_PI - max(prec, vprecision) and
  /// a < 0.5 * M_PI + max(prec, vprecision), they are perpendicular.
  friend inline int check_perp(const vec& r1, const vec& r2, double prec) {
    // returns 1 if perpendicular
    double a = ang2vec(r1, r2);
    if (vecerror != 0) {
      vecerror = 0;
      return 0;
    }
    if (apeq(a, 0.5 * M_PI, std::max(prec, vprecision))) return 1;
    // If without max(prec, vprecision) but with just prec
    // Event for exactly perpendicular vectors this function
    // would never confirm this.
    // if(a >= 0.5*M_PI - prec && a =< 0.5*M_PI + prec ) return 1;
    return 0;
  }
};

extern vec dex;  // unit vector by x
extern vec dey;  // unit vector by y
extern vec dez;  // unit vector by z
extern vec dv0;  // zero vector

/// Basis.
class basis : public absref {
 protected:
  /// Unit vectors giving directions of Cartesian axes.
  /// Supposed to be perpendicular, therefore not public.
  vec ex, ey, ez;

  virtual absref_transmit get_components() override;

  static absref absref::* aref[3];

 public:
  vec Gex() const { return ex; }
  vec Gey() const { return ey; }
  vec Gez() const { return ez; }

  /// Nominal basis.
  basis();
  /// Longitudinal basis.
  /// z-axis is parallel to p.
  /// y-axis is vector product of z_new and z_old
  /// x-axis is vector product of y_new and z_new
  /// If p is parallel to z_old, the copy of old basis is created.
  /// If p is anti-parallel to z_old, the inverted copy of old basis is created.
  basis(const vec& p);

  /// More sophisticated basis.
  /// ez is parallel to p,                             ez=unit_vec(p)
  /// ey is perpendicular to plane which have p and c, ey=unit_vec(ez||c)
  /// ex is vector product of y and z,                 ex=ey||ez
  /// If p is parallel to c, or p is anti-parallel to c, vecerror=1
  /// if(length(p)==0||length(c)==0)) vecerror=1;
  basis(const vec& p, const vec& c);
  /// Direct definitions of basis by three perpendicular unit-length vectors.
  basis(const vec& pex, const vec& pey, const vec& pez);
  virtual ~basis() {}
};

/// Point.

class point : public absref {
 public:
  vec v;

 private:
  absref_transmit get_components() override;
  static absref absref::* aref;

 public:
  void down(const abssyscoor* fasc) override;
  void up(const abssyscoor* fasc) override;
  void shift(const vec& dir) override { v += dir; }
  /// Default constructor (coordinates are not initialised).
  point() : v() {}
  /// Constructor from vector.
  point(const vec& fv) : v(fv) {}
  /// Constructor from coordinates.
  point(const double fex, const double fey, const double fez)
      : v(fex, fey, fez) {}
  /// Copy constructor.
  point(const point& p) : v(p.v) {}
  /// Assignment operator.
  point& operator=(const point& fp) {
    v = fp.v;
    return *this;
  }
  vec operator-(const point& pp) const { return v - pp.v; }
  // creates vector from pp to p
  point operator+(const vec& fv) const { return point(v + fv); }
  friend int operator==(const point& p1, const point& p2) {
    return p1.v == p2.v ? 1 : 0;
  }
  friend int operator!=(const point& p1, const point& p2) {
    return p1.v != p2.v ? 1 : 0;
  }
  friend bool apeq(const point& p1, const point& p2, double prec) {
    return apeq(p1.v, p2.v, prec);
  }
  virtual ~point() {}
};

/// Coordinate system (centre, basis and mother coordinate system).
/// Take care: c.abas must be equal to abas->ex.abas.
/// If asc==NULL and abs(c)==0 than it is primary system of coordinate
/// and therefore c.abas and abas->ex.abas must be zero,
/// baz may be zero or pointer to unit basis.
class abssyscoor {
 public:
  virtual const point* Gapiv() const = 0;
  virtual const basis* Gabas() const = 0;
  abssyscoor() = default;
  virtual ~abssyscoor() {}
};

class fixsyscoor : public absref, public abssyscoor {
 public:
  const point* Gapiv() const override { return &piv; }
  const basis* Gabas() const override { return &bas; }
  void Ppiv(const point& fpiv);
  void Pbas(const basis& fbas);
  // nominal system
  fixsyscoor() = default;
  fixsyscoor(const point& fpiv, const basis& fbas)
      : abssyscoor(), piv(fpiv), bas(fbas) {}
  fixsyscoor(const point* const fapiv, const basis* const fabas)
      : abssyscoor(),
        piv((fapiv != NULL) ? (*fapiv) : point()),
        bas((fabas != NULL) ? (*fabas) : basis()) {}
  fixsyscoor(const abssyscoor& f)
      : abssyscoor(f),
        piv((f.Gapiv() != NULL) ? (*(f.Gapiv())) : point()),
        bas((f.Gabas() != NULL) ? (*(f.Gabas())) : basis()) {}
  virtual ~fixsyscoor() {}

 protected:
  absref_transmit get_components() override;
  static absref absref::* aref[2];

 private:
  point piv;
  basis bas;
};
}  // namespace Heed

#endif
