#ifndef G_VIEW_GEOMETRY
#define G_VIEW_GEOMETRY

#include <memory>
#include <vector>

#include "Garfield/ViewBase.hh"

class TGeoVolume;
class TGeoMedium;
class TGeoManager;

namespace Garfield {

class GeometrySimple;

/// Visualize a geometry defined using the "native" shapes.

class ViewGeometry : public ViewBase {
 public:
  /// Default constructor.
  ViewGeometry();
  /// Constructor.
  explicit ViewGeometry(GeometrySimple* geometry);
  explicit ViewGeometry(std::nullptr_t) = delete;
  /// Destructor.
  ~ViewGeometry();

  /// Set the geometry to be drawn.
  void SetGeometry(GeometrySimple* geometry);
  /// Draw the geometry.
  void Plot(const bool twod = false);
  /// Draw a cut through the geometry at the current viewing plane.
  void Plot2d();
  /// Draw a three-dimensional view of the geometry.
  void Plot3d();
  /// Draw the surface panels.
  void PlotPanels();

 private:
  GeometrySimple* m_geometry{nullptr};

  std::vector<TGeoVolume*> m_volumes;
  std::vector<TGeoMedium*> m_media;

  std::unique_ptr<TGeoManager> m_geoManager;

  void Reset();
};
}  // namespace Garfield
#endif
