#ifndef G_SOLID_TUBE_H
#define G_SOLID_TUBE_H

#include <array>
#include <mutex>
#include <vector>

#include "Garfield/Solid.hh"

namespace Garfield {

/// Cylindrical tube.

class SolidTube : public Solid {
 public:
  /// Constructor from centre, outer radius, and half-length.
  SolidTube(const double cx, const double cy, const double cz, const double r,
            const double lz);
  /// Constructor from centre, outer radius, half-length and orientation.
  SolidTube(const double cx, const double cy, const double cz, const double r,
            const double lz, const double dx, const double dy, const double dz);
  /// Constructor from centre, inner radius, outer radius, and half-length.
  SolidTube(const double cx, const double cy, const double cz, const double ri,
            const double ro, const double lz);
  /// Constructor from centre, inner radius, outer radius, half-length
  /// and orientation.
  SolidTube(const double cx, const double cy, const double cz, const double ri,
            const double ro, const double lz, const double dx, const double dy,
            const double dz);
  /// Destructor
  ~SolidTube() = default;

  bool IsInside(const double x, const double y, const double z,
                const bool tesselated) const override;
  bool GetBoundingBox(double& xmin, double& ymin, double& zmin, double& xmax,
                      double& ymax, double& zmax) const override;
  bool IsTube() const override { return true; }

  /// Set the half-length of the tube.
  void SetHalfLength(const double lz);
  /// Set the outer radius.
  void SetRadius(const double r);
  /// Retrieve the half-length of the tube.
  double GetHalfLengthZ() const override { return m_lZ; }
  /// Retrieve the outer radius.
  double GetRadius() const override { return m_rO; }
  /// Retrieve the outer radius.
  double GetOuterRadius() const override { return m_rO; }
  /// Retrieve the inner radius.
  double GetInnerRadius() const override { return m_rI; }

  /// When calculating the surface panels, the cylinder is
  /// approximated as a polygon with a finite number of panels.
  /// The number of corners of the polygon equals \f$4(n - 1)\f$.
  /// Thus, \f$n = 2\f$ will produce a square, \f$n = 3\f$ an octagon etc.
  void SetSectors(const std::size_t n);
  /// Specify a rotation angle (radian) of the cylinder.
  /// Such a rotation is meaningful only if the number of sectors
  /// (when approximating the circle with a polygon) has been chosen small.
  void SetRotation(const double angle) { m_rot = angle; }
  /// By default, the polygon used for approximating the cylinder when
  /// calculating surface panels is inscribed in a circle
  /// of the specified radius. If the "average-radius" flag is activated,
  /// then the radius will be interpreted as the mean radius of the polygon
  /// that approximates the cylinder.
  void SetAverageRadius(const bool average) { m_average = average; }
  /// Request the cylinder to be closed with a (polygonal) lid at +z.
  void SetTopLid(const bool closed) { m_toplid = closed; }
  /// Request the cylinder to be closed with a (polygonal) lid at -z.
  void SetBottomLid(const bool closed) { m_botlid = closed; }

  /// Return the number of sectors.
  std::size_t GetSectors() const { return m_n; }
  /// Return the current rotation angle.
  double GetRotation() const { return m_rot; }
  /// Return the status of the "average-radius" flag.
  bool GetAverage() const { return m_average; }

  bool SolidPanels(std::vector<Panel>& panels) override;
  void SetDiscretisationLevel(const double dis) override { m_dis.fill(dis); }
  double GetDiscretisationLevel(const Panel& panel) override;

  void Cut(const double x0, const double y0, const double z0, const double xn,
           const double yn, const double zn,
           std::vector<Panel>& panels) override;

 private:
  /// Mutex.
  std::mutex m_mutex;

  /// Outer radius.
  double m_rO{0.};
  /// Inner radius.
  double m_rI{0.};
  /// Half-length
  double m_lZ{0.};

  /// Rotation angle
  double m_rot{0.};
  /// Number of sectors
  std::size_t m_n{2};
  /// Average chord over the sectors.
  bool m_average{false};
  /// Radius of the outer approximating polygon.
  double m_rpO{0.};
  /// Radius of the inner approximating polygon.
  double m_rpI{0.};
  /// Inradius of the outer approximating polygon.
  double m_riO{0.};
  /// Inradius of the inner approximating polygon.
  double m_riI{0.};
  /// X-coordinates of the outer approximating polygon.
  std::vector<double> m_xpO;
  /// Y-coordinates of the outer approximating polygon.
  std::vector<double> m_ypO;
  /// X-coordinates of the inner approximating polygon.
  std::vector<double> m_xpI;
  /// Y-coordinates of the inner approximating polygon.
  std::vector<double> m_ypI;

  /// Have a top lid?
  bool m_toplid{true};
  /// Have a bottom lid?
  bool m_botlid{true};

  /// Discretisation levels.
  std::array<double, 3> m_dis{{-1., -1., -1.}};

  void UpdatePolygon();
};
}  // namespace Garfield

#endif
