#ifndef G_COMPONENT_GRID_H
#define G_COMPONENT_GRID_H

#include <array>
#include <cstddef>
#include <string>
#include <vector>

#include "Garfield/Component.hh"

namespace Garfield {

class Medium;
/// Component for interpolating field maps on a regular mesh.

class ComponentGrid : public Component {
 public:
  /// Constructor
  ComponentGrid();
  /// Destructor
  ~ComponentGrid() = default;

  /// Set the medium.
  void SetMedium(Medium* medium);

  /** Define the grid.
   * \param nx,ny,nz number of nodes along \f$x, y, z\f$.
   * \param xmin,xmax range along \f$x\f$.
   * \param ymin,ymax range along \f$y\f$.
   * \param zmin,zmax range along \f$z\f$.
   */
  bool SetMesh(const std::size_t nx, const std::size_t ny, const std::size_t nz,
               const double xmin, const double xmax, const double ymin,
               const double ymax, const double zmin, const double zmax);
  /// Retrieve the parameters of the grid.
  bool GetMesh(std::size_t& nx, std::size_t& ny, std::size_t& nz, double& xmin,
               double& xmax, double& ymin, double& ymax, double& zmin,
               double& zmax) const;
  /// Use Cartesian coordinates (default).
  void SetCartesianCoordinates() { m_coordinates = Coordinates::Cartesian; }
  /// Use cylindrical coordinates.
  void SetCylindricalCoordinates();

  void SetUniformElectricField(double ex, double ey, double ez);

  /** Import electric field and potential values from a file.
   * The file is supposed to contain one line for each grid point starting with
   *   - either two or three floating point numbers,
   *     specifying the coordinates (in cm) of the grid node or
   *   - two or three integers specifying the index of the node,
   *
   * followed by
   *   - two or three floating point numbers for the electric field (in V/cm),
   * and (depending on the value of withPotential and withFlag),
   *   - a floating point number specifying the potential (in V), and
   *   - an integer flag indicating whether the point is in an active region (1)
   *     or not (0).
   *
   * Format types are:
   *  - "xy", "xz", "xyz": nodes are specified by their coordinates
   *  - "ij", "ik", "ijk": nodes are specified by their indices
   *
   * If cylindrical coordinates are used, the first coordinate (x)
   * corresponds to the radial distance and the second coordinate (y)
   * corresponds to the azimuth (in radian).
   */
  bool LoadElectricField(const std::string& filename, const std::string& format,
                         const bool withPotential, const bool withFlag,
                         const double scaleX = 1., const double scaleE = 1.,
                         const double scaleP = 1.);

  /// Import (prompt) weighting field from file.
  bool LoadWeightingField(const std::string& filename,
                          const std::string& format, const bool withPotential,
                          const double scaleX = 1., const double scaleE = 1.,
                          const double scaleP = 1.);
  /// Import delayed weighting field from file.
  bool LoadWeightingField(const std::string& filename,
                          const std::string& format, const double time,
                          const bool withPotential, const double scaleX = 1.,
                          const double scaleE = 1., const double scaleP = 1.);
  /// Offset coordinates in the weighting field, such that the
  /// same numerical weighting field map can be used for electrodes at
  /// different positions.
  void SetWeightingFieldOffset(const double x, const double y, const double z);

  /// Import magnetic field values from a file.
  bool LoadMagneticField(const std::string& filename, const std::string& format,
                         const double scaleX = 1., const double scaleB = 1.);

  /** Export the electric field and potential of a component to a text file.
   * \param cmp Component object for which to export the field/potential
   * \param filename name of the text file
   * \param fmt format string, see @ref LoadElectricField
   */
  bool SaveElectricField(Component* cmp, const std::string& filename,
                         const std::string& fmt);

  bool SaveElectricFieldROOT(Component* cmp, const std::string& filename,
                             const std::string& fmt);

  /** Export the electric field and potential of a component.
   * \param cmp Component object for which to export the field/potential
   */
  bool SaveElectricField(Component* cmp);

  /** Export the weighting field and potential of a component to a text file.
   * \param cmp Component object for which to export the field/potential
   * \param id identifier of the weighting field
   * \param filename name of the text file
   * \param fmt format string, see @ref LoadElectricField
   */
  bool SaveWeightingField(Component* cmp, const std::string& id,
                          const std::string& filename, const std::string& fmt);

  /// Return the field at a given node.
  bool GetElectricField(const std::size_t i, const std::size_t j,
                        const std::size_t k, double& v, double& ex, double& ey,
                        double& ez) const;

  /// Get the medium.
  Medium* GetMedium() const { return m_medium; }

  /// Print information about the mesh and the available data.
  void Print();

  /** Import electron attachment coefficients from a file.
   * \param fname name of the text file.
   * \param fmt format string, see @ref LoadElectricField.
   * \param col column in the file which has the attachment coefficient.
   * \param scaleX scaling factor to be applied to the coordinates.
   */
  bool LoadElectronAttachment(const std::string& fname, const std::string& fmt,
                              const std::size_t col, const double scaleX = 1.);
  /// Import hole attachment coefficients from a file.
  bool LoadHoleAttachment(const std::string& fname, const std::string& fmt,
                          const std::size_t col, const double scaleX = 1.);

  /** Import a map of electron drift velocities from a file.
   * \param fname name of the text file.
   * \param fmt format string, see @ref LoadElectricField
   * \param scaleX scaling factor to be applied to the coordinates.
   * \param scaleV scaling factor to be applied to the velocity components.
   */
  bool LoadElectronVelocity(const std::string& fname, const std::string& fmt,
                            const double scaleX = 1.,
                            const double scaleV = 1.e-9);
  /// Import a map of hole drift velocities from a file.
  bool LoadHoleVelocity(const std::string& fname, const std::string& fmt,
                        const double scaleX = 1., const double scaleV = 1.e-9);

  void AddIon(const double x, const double y, const double z,
              const double w = 1.0);
  void AddNegativeIon(const double x, const double y, const double z,
                      const double w = 1.0);
  void AddElectron(const double x, const double y, const double z,
                   const double w = 1.0);
  void AddHole(const double x, const double y, const double z,
               const double w = 1.0);
  void Clear() override { Reset(); }
  void ClearFields();
  void ElectricField(const double x, const double y, const double z, double& ex,
                     double& ey, double& ez, double& v, Medium*& m,
                     int& status) override;
  void ElectricField(const double x, const double y, const double z, double& ex,
                     double& ey, double& ez, Medium*& m, int& status) override;
  using Component::ElectricField;
  void WeightingField(const double x, const double y, const double z,
                      double& wx, double& wy, double& wz,
                      const std::string& label) override;
  double WeightingPotential(const double x, const double y, const double z,
                            const std::string& label) override;
  void DelayedWeightingField(const double x, const double y, const double z,
                             const double t, double& wx, double& wy, double& wz,
                             const std::string& label) override;
  double DelayedWeightingPotential(const double x, const double y,
                                   const double z, const double t,
                                   const std::string& label) override;
  void MagneticField(const double x, const double y, const double z, double& bx,
                     double& by, double& bz, int& status) override;

  Medium* GetMedium(const double x, const double y, const double z) override;

  bool GetVoltageRange(double& vmin, double& vmax) override;
  bool GetElectricFieldRange(double& exmin, double& exmax, double& eymin,
                             double& eymax, double& ezmin, double& ezmax);
  bool GetBoundingBox(double& xmin, double& ymin, double& zmin, double& xmax,
                      double& ymax, double& zmax) override;
  bool GetElementaryCell(double& xmin, double& ymin, double& zmin, double& xmax,
                         double& ymax, double& zmax) override;

  bool HasMagneticField() const override;

  bool HasAttachmentMap() const override {
    return !(m_eAttachment.empty() && m_hAttachment.empty());
  }
  bool ElectronAttachment(const double x, const double y, const double z,
                          double& att) override;
  bool HoleAttachment(const double x, const double y, const double z,
                      double& att) override;
  bool HasMobilityMap() const override {
    return !(m_eMobility.empty() && m_hMobility.empty());
  }
  bool ElectronMobility(const double x, const double y, const double z,
                        double& mu) override;
  bool HoleMobility(const double x, const double y, const double z,
                    double& mu) override;
  bool HasVelocityMap() const override {
    return !(m_eVelocity.empty() && m_hVelocity.empty());
  }
  bool ElectronVelocity(const double x, const double y, const double z,
                        double& vx, double& vy, double& vz) override;
  bool HoleVelocity(const double x, const double y, const double z, double& vx,
                    double& vy, double& vz) override;
  bool HasIonDensityMap() const override { return !(m_ionDensity.empty()); }
  bool IonDensity(const double x, const double y, const double z,
                  double& rho) override;
  bool HasNegativeIonDensityMap() const override {
    return !(m_negativeIonDensity.empty());
  }
  bool NegativeIonDensity(const double x, const double y, const double z,
                          double& rho) override;
  bool HasElectronDensityMap() const override {
    return !(m_electronDensity.empty());
  }
  bool ElectronDensity(const double x, const double y, const double z,
                       double& rho) override;
  bool HasHoleDensityMap() const override { return !(m_holeDensity.empty()); }
  bool HoleDensity(const double x, const double y, const double z,
                   double& rho) override;
  bool HasChargeDensityMap() const override {
    return !(m_chargeDensity.empty());
  }
  bool ChargeDensity(const double x, const double y, const double z, double& q);
  struct Node {
    double fx{0.};
    double fy{0.};
    double fz{0.};  ///< Field
    double v{0.};   ///< Potential
  };
  /// Get field values on all nodes
  void GetFieldOnGrid(
      std::vector<std::vector<std::vector<ComponentGrid::Node>>>& efields) {
    efields = m_efields;
  };
  /// Add the field values of cmp to current grid.
  bool AddElectricField(ComponentGrid* cmp, const double scale = 1.,
                        const double xShift = 0., const double yShift = 0.,
                        const double zShift = 0.);

  /// Add the field values of cmp to current grid.
  bool AddElectricField(Component* cmp, const double scale);

  /// Gives the closest node index (i, j, k) to coordinate (x, y, z).
  bool GetNodeIndex(double x, const double y, const double z, std::size_t& i,
                    std::size_t& j, std::size_t& k);

 private:
  enum class Format { Unknown, XY, XZ, XYZ, IJ, IK, IJK, YXZ };
  enum class Coordinates { Cartesian, Cylindrical };
  Coordinates m_coordinates{Coordinates::Cartesian};

  Medium* m_medium{nullptr};

  /// Electric field values and potentials.
  std::vector<std::vector<std::vector<Node>>> m_efields;
  /// Magnetic field values.
  std::vector<std::vector<std::vector<Node>>> m_bfields;
  /// Prompt weighting field values and potentials.
  std::vector<std::vector<std::vector<Node>>> m_wfields;
  /// Delayed weighting field values and potentials.
  std::vector<std::vector<std::vector<std::vector<Node>>>> m_wdfields;
  /// Attachment maps for electrons and holes.
  std::vector<std::vector<std::vector<double>>> m_eAttachment;
  std::vector<std::vector<std::vector<double>>> m_hAttachment;
  /// Mobility maps for electrons and holes.
  std::vector<std::vector<std::vector<double>>> m_eMobility;
  std::vector<std::vector<std::vector<double>>> m_hMobility;
  /// Velocity maps for electrons and holes.
  std::vector<std::vector<std::vector<Node>>> m_eVelocity;
  std::vector<std::vector<std::vector<Node>>> m_hVelocity;
  /// Maps for ions, negative ions, electrons and holes.
  std::vector<std::vector<std::vector<double>>> m_ionDensity;
  std::vector<std::vector<std::vector<double>>> m_negativeIonDensity;
  std::vector<std::vector<std::vector<double>>> m_electronDensity;
  std::vector<std::vector<std::vector<double>>> m_holeDensity;
  /// Charge density map
  std::vector<std::vector<std::vector<double>>> m_chargeDensity;
  /// Active medium flag.
  std::vector<std::vector<std::vector<bool>>> m_active;

  // Dimensions of the mesh
  std::array<std::size_t, 3> m_nX{{1, 1, 1}};
  std::array<double, 3> m_xMin{{0., 0., 0.}};
  std::array<double, 3> m_xMax{{0., 0., 0.}};
  std::array<double, 3> m_sX{{0., 0., 0.}};

  bool m_hasMesh{false};
  bool m_hasPotential{false};

  // Offset for weighting field
  std::array<double, 3> m_wFieldOffset{{0., 0., 0.}};

  // Voltage range
  double m_pMin{0.};
  double m_pMax{0.};

  /// Read/determine mesh parameters from file.
  bool LoadMesh(const std::string& filename, std::string format,
                const double scaleX);

  /// Read electric field and potential from file.
  bool LoadData(const std::string& filename, std::string format,
                const bool withPotential, const bool withFlag,
                const double scaleX, const double scaleF, const double scaleP,
                std::vector<std::vector<std::vector<Node>>>& field);
  /// Load scalar data (e. g. attachment coefficients) from file.
  bool LoadData(const std::string& filename, std::string format,
                const double scaleX,
                std::vector<std::vector<std::vector<double>>>& tab,
                const std::size_t col);

  void Reset() override;
  void UpdatePeriodicity() override;

  /// Interpolation of the field and potential at a given point.
  bool GetField(const double x, const double y, const double z,
                const std::vector<std::vector<std::vector<Node>>>& field,
                double& fx, double& fy, double& fz, double& p, bool& active);
  /// Interpolation in a table of scalars.
  bool GetData(const double x, const double y, const double z,
               const std::vector<std::vector<std::vector<double>>>& table,
               double& value);

  void AddParticle(double x, double y, double z, double w,
                   std::vector<std::vector<std::vector<double>>>& grid);

  /// Reduce a coordinate to the basic cell (in case of periodicity).
  double Reduce(const double xin, const double xmin, const double xmax,
                const Symmetry, bool& isMirrored) const;
  /// Set the dimensions of a table according to the mesh.
  void Initialise(std::vector<std::vector<std::vector<Node>>>& fields);
  /// Decode a format string.
  Format GetFormat(std::string fmt);
};
}  // namespace Garfield
#endif
