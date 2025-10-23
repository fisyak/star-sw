#ifndef G_GEOMETRY_H
#define G_GEOMETRY_H

#include <cstddef>
#include <string>

namespace Garfield {

class Medium;
class Solid;

/// Abstract base class for geometry classes.
class Geometry {
 public:
  /// Default constructor.
  Geometry() = delete;
  /// Constructor
  Geometry(const std::string& name) : m_className(name) {}
  /// Destructor
  virtual ~Geometry() = default;

  /// Retrieve the medium at a given point.
  virtual Medium* GetMedium(const double x, const double y, const double z,
                            const bool tesselated = false) const = 0;

  /// Return the number of solids in the geometry.
  virtual std::size_t GetNumberOfSolids() const { return 0; }
  /// Get a solid from the list.
  virtual Solid* GetSolid(const std::size_t /*i*/) const { return nullptr; }
  /// Get a solid from the list, together with the associated medium.
  virtual Solid* GetSolid(const std::size_t /*i*/, Medium*& /*medium*/) const {
    return nullptr;
  }
  /// Check if a point is inside the geometry.
  virtual bool IsInside(const double x, const double y, const double z,
                        const bool tesselated = false) const = 0;

  /// Get the bounding box (envelope of the geometry).
  virtual bool GetBoundingBox(double& xmin, double& ymin, double& zmin,
                              double& xmax, double& ymax, double& zmax) = 0;

 protected:
  std::string m_className{"Geometry"};
};
}  // namespace Garfield

#endif
