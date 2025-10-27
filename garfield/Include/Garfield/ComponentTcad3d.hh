#ifndef G_COMPONENT_TCAD_3D_H
#define G_COMPONENT_TCAD_3D_H

#include <array>
#include <cstddef>
#include <memory>
#include <string>
#include <vector>

#include "Garfield/ComponentTcadBase.hh"
#include "Garfield/TetrahedralTree.hh"

namespace Garfield {

class Medium;
/// Interpolation in a three-dimensional field map created by Sentaurus Device.

class ComponentTcad3d : public ComponentTcadBase<3> {
 public:
  /// Constructor
  ComponentTcad3d();
  /// Destructor
  ~ComponentTcad3d() = default;

  /** Retrieve the properties of an element.
   * \param i index of the element
   * \param vol volume
   * \param dmin smallest length in the element
   * \param dmax largest length in the element
   * \param type element type
   */
  bool GetElement(const std::size_t i, double& vol, double& dmin, double& dmax,
                  int& type) const;
  /// Get the coordinates of a mesh node.
  bool GetNode(const std::size_t i, double& x, double& y,
               double& z) const override;

  void ElectricField(const double x, const double y, const double z, double& ex,
                     double& ey, double& ez, double& v, Medium*& m,
                     int& status) override;
  void ElectricField(const double x, const double y, const double z, double& ex,
                     double& ey, double& ez, Medium*& m, int& status) override;
  using Component::ElectricField;
  Medium* GetMedium(const double x, const double y, const double z) override;
  void DelayedWeightingPotentials(const double x, const double y,
                                  const double z, const std::string& label,
                                  std::vector<double>& dwp) override;

  bool GetBoundingBox(double& xmin, double& ymin, double& zmin, double& xmax,
                      double& ymax, double& zmax) override;
  bool GetElementaryCell(double& xmin, double& ymin, double& zmin, double& xmax,
                         double& ymax, double& zmax) override;

 private:
  // Tetrahedral tree.
  std::unique_ptr<TetrahedralTree> m_tree;

  void Reset() override {
    Cleanup();
    m_ready = false;
  }

  std::size_t FindElement(const double x, const double y, const double z,
                          std::array<double, nMaxVertices>& w) const;
  bool InElement(const double x, const double y, const double z,
                 const Element& element,
                 std::array<double, nMaxVertices>& w) const;
  bool InTetrahedron(const double x, const double y, const double z,
                     const Element& element,
                     std::array<double, nMaxVertices>& w) const;
  bool InTriangle(const double x, const double y, const double z,
                  const Element& element,
                  std::array<double, nMaxVertices>& w) const;

  bool Interpolate(const double x, const double y, const double z,
                   const std::vector<double>& field, double& f) override;
  bool Interpolate(const double x, const double y, const double z,
                   const std::vector<std::array<double, 3> >& field, double& fx,
                   double& fy, double& fz) override;
  void FillTree() override;
};
}  // namespace Garfield
#endif
