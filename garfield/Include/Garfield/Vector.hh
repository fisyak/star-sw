#ifndef G_VECTOR_H
#define G_VECTOR_H

#if defined(__NVCC__)
#include <cuda/std/array>
template <typename T, std::size_t D>
using GarfieldArray = cuda::std::array<T, D>;
#else
#include <array>
#if !defined(__device__)
#define __GARFIELD_DEFINED_DEVICE__
#define __device__
#define __host__
#endif
template <typename T, std::size_t D>
using GarfieldArray = std::array<T, D>;
#endif
#include <cstddef>

namespace Garfield {
template <typename type, std::size_t Dimension>
class Vector : public GarfieldArray<type, Dimension> {
 public:
  template <typename... Args>
  __host__ __device__ Vector(Args&&... args)
      : GarfieldArray<type, Dimension>({std::forward<Args>(args)...}) {}
  __host__ __device__ Vector() { this->fill(0.); }
  __host__ __device__ Vector operator*(const double& i) {
    Vector ret = *this;
    for (std::size_t j = 0; j != ret.size(); ++j) {
      ret[j] *= i;
    }
    return ret;
  }
  __host__ __device__ Vector operator/(const double& i) {
    Vector ret = *this;
    for (std::size_t j = 0; j != ret.size(); ++j) {
      ret[j] /= i;
    }
    return ret;
  }
  template <typename T, std::size_t D>
  __host__ __device__ Vector operator+(const Vector<T, D>& vec) {
    static_assert(Dimension == D, "The vectors don't have the same dimension!");
    Vector ret = *this;
    for (std::size_t j = 0; j != ret.size(); ++j) {
      ret[j] += vec[j];
    }
    return ret;
  }
  template <typename T, std::size_t D>
  __host__ __device__ Vector operator-(const Vector<T, D>& vec) {
    static_assert(Dimension == D, "The vectors don't have the same dimension!");
    Vector ret = *this;
    for (std::size_t j = 0; j != ret.size(); ++j) {
      ret[j] -= vec[j];
    }
    return ret;
  }
};

template <typename type>
class Vec1Impl : public Vector<type, 1> {
 public:
  Vec1Impl() = default;
  template <typename... xs>
  __host__ __device__ Vec1Impl(xs... values) : Vector<type, 3>({values...}) {}
  __host__ __device__ type& x() noexcept { return this->operator[](0); }
  __host__ __device__ type x() const noexcept { return this->operator[](0); }
};

template <typename type>
class Vec2Impl : public Vector<type, 2> {
 public:
  Vec2Impl() = default;
  template <typename... xs>
  __host__ __device__ Vec2Impl(xs... values) : Vector<type, 3>({values...}) {}
  __host__ __device__ type& x() noexcept { return this->operator[](0); }
  __host__ __device__ type x() const noexcept { return this->operator[](0); }
  __host__ __device__ type& y() noexcept { return this->operator[](1); }
  __host__ __device__ type y() const noexcept { return this->operator[](1); }
};

template <typename type>
class Vec3Impl : public Vector<type, 3> {
 public:
  Vec3Impl() = default;
  template <typename... xs>
  __host__ __device__ Vec3Impl(xs... values) : Vector<type, 3>({values...}) {}
  __host__ __device__ type& x() noexcept { return this->operator[](0); }
  __host__ __device__ type x() const noexcept { return this->operator[](0); }
  __host__ __device__ type& y() noexcept { return this->operator[](1); }
  __host__ __device__ type y() const noexcept { return this->operator[](1); }
  __host__ __device__ type& z() noexcept { return this->operator[](2); }
  __host__ __device__ type z() const noexcept { return this->operator[](2); }
};

using Vec3D = Vec3Impl<double>;
using Vec3F = Vec3Impl<float>;

}  // namespace Garfield

#if defined(__GARFIELD_DEFINED_DEVICE__)
#undef __device__
#undef __host__
#undef __GARFIELD_DEFINED_DEVICE__
#endif

#endif