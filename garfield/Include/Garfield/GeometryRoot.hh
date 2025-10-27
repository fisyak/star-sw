#ifndef G_GEOMETRY_ROOT_H
#define G_GEOMETRY_ROOT_H

#include <TGeoManager.h>
#include <TGeoMaterial.h>

#include <cstddef>
#include <map>
#include <string>

#include "Garfield/Geometry.hh"

namespace Garfield {

/// Use a geometry defined using the ROOT TGeo package.

class GeometryRoot : public Geometry {
 public:
  /// Constructor
  GeometryRoot();
  /// Destructor
  ~GeometryRoot() = default;

  /// Set the geometry (pointer to ROOT TGeoManager).
  void SetGeometry(TGeoManager* geoman);
  /// Associate a ROOT material with a Garfield medium.
  void SetMedium(const std::size_t imat, Medium* medium);
  /// Associate a ROOT material with a Garfield medium.
  void SetMedium(const std::string& mat, Medium* medium);

  Medium* GetMedium(const double x, const double y, const double z,
                    const bool tesselated = false) const override;

  /// Get the number of materials defined in the ROOT geometry.
  std::size_t GetNumberOfMaterials();
  /// Get a pointer to the ROOT material with a given index.
  TGeoMaterial* GetMaterial(const std::size_t i);
  /// Get a pointer to the ROOT material with a given name.
  TGeoMaterial* GetMaterial(const char* name);

  bool IsInside(const double x, const double y, const double z,
                const bool tesselated = false) const override;
  bool GetBoundingBox(double& xmin, double& ymin, double& zmin, double& xmax,
                      double& ymax, double& zmax) override;

  /// Switch debugging and warning messages on/off.
  void EnableDebugging(const bool on = true) { m_debug = on; }

 protected:
  // ROOT geometry manager
  TGeoManager* m_geoManager{nullptr};

  // List of ROOT materials associated to Garfield media
  std::map<std::string, Medium*> m_materials;

  // Switch on/off debugging messages.
  bool m_debug{false};
};
}  // namespace Garfield

#endif
