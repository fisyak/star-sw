#ifndef G_SYMMETRIES_H
#define G_SYMMETRIES_H
#include <cstddef>
#include <cstdint>
#if !defined(__NVCC__)
#include "Garfield/Exceptions.hh"
#if !defined(__device__)
#define __GARFIELD_DEFINED_DEVICE__
#define __device__
#define __host__
#endif
#endif

namespace Garfield {

class Symmetry {
 public:
  Symmetry() noexcept = default;
  ~Symmetry() noexcept = default;
  enum class Type : std::uint16_t {
    None = 0,
    /// Simple periodicity in x, y, z.
    PeriodicX = 1 << 0,
    PeriodicY = 1 << 1,
    PeriodicZ = 1 << 2,
    Periodic = (1 << 0) + (1 << 1) + (1 << 2),
    /// Mirror periodicity in x, y, z.
    MirrorX = 1 << 3,
    MirrorY = 1 << 4,
    MirrorZ = 1 << 5,
    Mirror = (1 << 3) + (1 << 4) + (1 << 5),
    /// Axial periodicity in x, y, z.
    AxialX = 1 << 6,
    AxialY = 1 << 7,
    AxialZ = 1 << 8,
    Axial = (1 << 6) + (1 << 7) + (1 << 8),
    /// Rotation symmetry around x-axis, y-axis, z-axis.
    RotationX = 1 << 9,
    RotationY = 1 << 10,
    RotationZ = 1 << 11,
    Rotation = (1 << 9) + (1 << 10) + (1 << 11),
    /// Triangle symmetric in the xy, xz, and yz plane.
    TriangleXY = 1 << 12,
    TriangleXZ = 1 << 13,
    TriangleYZ = 1 << 14,
    Triangle = (1 << 12) + (1 << 13) + (1 << 14),
    Error = 1 << 15  // FOR CUDA
  };
  __device__ __host__ void Activate(Type sym) {
    m_symmetries = static_cast<Type>(static_cast<std::uint64_t>(m_symmetries) |
                                     static_cast<std::uint64_t>(sym));
  }
  __device__ __host__ void Deactivate(Type sym) {
    m_symmetries = static_cast<Type>(static_cast<std::uint64_t>(m_symmetries) &
                                     ~static_cast<std::uint64_t>(sym));
  }
  __device__ __host__ void Set(Type sym, bool on = true) {
    if (on)
      Activate(sym);
    else
      Deactivate(sym);
  }
  __device__ __host__ void Reset() { m_symmetries = Type::None; }
  __device__ __host__ bool Has(Type sym) const {
    return static_cast<bool>(static_cast<std::uint16_t>(m_symmetries) &
                             static_cast<std::uint16_t>(sym));
  }
  __device__ __host__ std::size_t NumberOf(Type sym) const {
    std::uint16_t result = static_cast<std::uint16_t>(m_symmetries) &
                           static_cast<std::uint16_t>(sym);
    // Count the number of 1's in the result
    std::size_t count = 0;
    while (result) {
      count += result & 1;  // Add 1 if the least significant bit is 1
      result >>= 1;         // Right shift to check the next bit
    }
    return count;
  }
  /**
   * @brief Get the Symmmetries X object
   *
   * @return Return a Symmetry containing only the value with labels X :
   * PeriodicX, MirrorX, AxialX, RotationX, TriangleXY, TriangleXZ
   */
  __device__ __host__ Symmetry GetSymmetriesX() const noexcept {
    return Symmetry(
        static_cast<Type>(static_cast<std::uint16_t>(getXs) &
                          static_cast<std::uint16_t>(m_symmetries)));
  }
  __device__ __host__ Symmetry GetSymmetriesY() const noexcept {
    return Symmetry(
        static_cast<Type>(static_cast<std::uint16_t>(getYs) &
                          static_cast<std::uint16_t>(m_symmetries)));
  }
  __device__ __host__ Symmetry GetSymmetriesZ() const noexcept {
    return Symmetry(
        static_cast<Type>(static_cast<std::uint16_t>(getZs) &
                          static_cast<std::uint16_t>(m_symmetries)));
  }
  /**
   * @brief Get the Symmetries object
   *
   * @param i 0 for X, 1 for Y, 2 for Z
   * @return __device__
   */
  __device__ __host__ Symmetry GetSymmetries(const std::size_t i) const {
    switch (i) {
      case 0:
        return GetSymmetriesX();
      case 1:
        return GetSymmetriesY();
      case 2:
        return GetSymmetriesZ();
      default:  // CUDA makes us going back to Stone Age so just do Ugly C
                // trickery
      {
#if !defined(__NVCC__)
        throw Exception("i should be 0 (X),1 (Y) or 2 (z)");
#else
        return Symmetry(Type::Error);
#endif
      }
    }
  }

 private:
  __device__ __host__ explicit Symmetry(const Type syms) noexcept
      : m_symmetries(syms){};
  static constexpr const Type getXs{
      static_cast<std::uint16_t>(Type::PeriodicX) +
      static_cast<std::uint16_t>(Type::MirrorX) +
      static_cast<std::uint16_t>(Type::AxialX) +
      static_cast<std::uint16_t>(Type::RotationX) +
      static_cast<std::uint16_t>(Type::TriangleXY) +
      static_cast<std::uint16_t>(Type::TriangleXZ)};
  static constexpr const Type getYs{
      static_cast<std::uint16_t>(Type::PeriodicY) +
      static_cast<std::uint16_t>(Type::MirrorY) +
      static_cast<std::uint16_t>(Type::AxialY) +
      static_cast<std::uint16_t>(Type::RotationY) +
      static_cast<std::uint16_t>(Type::TriangleXY) +
      static_cast<std::uint16_t>(Type::TriangleYZ)};
  static constexpr const Type getZs{
      static_cast<std::uint16_t>(Type::PeriodicZ) +
      static_cast<std::uint16_t>(Type::MirrorZ) +
      static_cast<std::uint16_t>(Type::AxialZ) +
      static_cast<std::uint16_t>(Type::RotationZ) +
      static_cast<std::uint16_t>(Type::TriangleXZ) +
      static_cast<std::uint16_t>(Type::TriangleYZ)};
  Type m_symmetries{Type::None};
};

}  // namespace Garfield

#if defined(__GARFIELD_DEFINED_DEVICE__)
#undef __device__
#undef __host__
#undef __GARFIELD_DEFINED_DEVICE__
#endif

#endif