#ifndef G_COMPONENT_H
#define G_COMPONENT_H

#include <array>
#include <cstddef>
#include <string>
#include <vector>

#include "Garfield/Symmetry.hh"

namespace Garfield {

class ComponentGPU;
class Geometry;
class Medium;

/// Abstract base class for components.
class Component {
 public:
  /// Default constructor.
  Component() = delete;
  /// Constructor
  Component(const std::string& name);
  /// Constructor
  Component(const std::string& name, Geometry* sensor);
  /// Destructor
  virtual ~Component() = default;

  /// Define the geometry.
  virtual void SetGeometry(Geometry* geo);
  /// Reset.
  virtual void Clear();

  /// Get the medium at a given location (x, y, z).
  virtual Medium* GetMedium(const double x, const double y, const double z);

  /** Calculate the drift field at given point.
   *
   * \param x,y,z coordinates [cm].
   * \param ex,ey,ez components of the electric field [V/cm].
   * \param m pointer to the medium at this location.
   * \param status status flag
   *
   * Status flags:
   *
   *             0: Inside an active medium
   *           > 0: Inside a wire of type X
   *     -4 ... -1: On the side of a plane where no wires are
   *            -5: Inside the mesh but not in an active medium
   *            -6: Outside the mesh
   *           -10: Unknown potential type (should not occur)
   *         other: Other cases (should not occur)
   */
  virtual void ElectricField(const double x, const double y, const double z,
                             double& ex, double& ey, double& ez, Medium*& m,
                             int& status) = 0;
  /// Calculate the drift field [V/cm] and potential [V] at (x, y, z).
  virtual void ElectricField(const double x, const double y, const double z,
                             double& ex, double& ey, double& ez, double& v,
                             Medium*& m, int& status) = 0;

  /// Calculate the drift field [V/cm] at (x, y, z).
  std::array<double, 3> ElectricField(const double x, const double y,
                                      const double z);
  /// Calculate the (drift) electrostatic potential [V] at (x, y, z).
  virtual double ElectricPotential(const double x, const double y,
                                   const double z);
  /// Calculate the voltage range [V].
  virtual bool GetVoltageRange(double& vmin, double& vmax) = 0;

  /** Calculate the weighting field at a given point and for a given electrode.
   * \param x,y,z coordinates [cm].
   * \param wx,wy,wz components of the weighting field [1/cm].
   * \param label name of the electrode
   */
  virtual void WeightingField(const double x, const double y, const double z,
                              double& wx, double& wy, double& wz,
                              const std::string& label);
  /** Calculate the weighting potential at a given point.
   * \param x,y,z coordinates [cm].
   * \param label name of the electrode.
   * \return weighting potential [dimensionless].
   */
  virtual double WeightingPotential(const double x, const double y,
                                    const double z, const std::string& label);

  /// Return the time steps at which the delayed weighting potential/field are
  /// stored/evaluated.
  virtual const std::vector<double>& DelayedSignalTimes(
      const std::string& /*label*/) {
    return m_wdtimes;
  }
  /** Calculate the delayed weighting field at a given point and time
   * and for a given electrode.
   * \param x,y,z coordinates [cm].
   * \param t time [ns].
   * \param wx,wy,wz components of the weighting field [1/cm].
   * \param label name of the electrode
   */
  virtual void DelayedWeightingField(const double x, const double y,
                                     const double z, const double t, double& wx,
                                     double& wy, double& wz,
                                     const std::string& label);

  /** Calculate the delayed weighting potential at a given point and time and
   * for a given electrode.
   * \param x,y,z coordinates [cm].
   * \param t time [ns].
   * \param label name of the electrode
   */
  virtual double DelayedWeightingPotential(const double x, const double y,
                                           const double z, const double t,
                                           const std::string& label);

  /// Calculate the delayed weighting potentials at a given point and for a
  /// given electrode, for a set of pre-defined times.
  virtual void DelayedWeightingPotentials(const double x, const double y,
                                          const double z,
                                          const std::string& label,
                                          std::vector<double>& dwp);
  /** Calculate the magnetic field at a given point.
   *
   * \param x,y,z coordinates [cm].
   * \param bx,by,bz components of the magnetic field [Tesla].
   * \param status status flag.
   */
  virtual void MagneticField(const double x, const double y, const double z,
                             double& bx, double& by, double& bz, int& status);
  /// Set a constant magnetic field.
  void SetMagneticField(const double bx, const double by, const double bz);

  /// Ready for use?
  virtual bool IsReady() { return m_ready; }
  /// Does the component have a 3D field (map)?
  virtual bool Is3d() { return true; }

  /// Get the bounding box coordinates.
  virtual bool GetBoundingBox(double& xmin, double& ymin, double& zmin,
                              double& xmax, double& ymax, double& zmax);

  /// Get the coordinates of the elementary cell.
  virtual bool GetElementaryCell(double& xmin, double& ymin, double& zmin,
                                 double& xmax, double& ymax, double& zmax);
  // Get the x-length of the elementary cell.
  double CellSizeX();
  // Get the y-length of the elementary cell.
  double CellSizeY();
  // Get the z-length of the elementary cell.
  double CellSizeZ();

  /// Return the number of mesh elements.
  virtual std::size_t GetNumberOfElements() const { return 0; }
  /// Get the indices of the nodes constituting a given element.
  virtual bool GetElementNodes(const std::size_t /*i*/,
                               std::vector<std::size_t>& /*nodes*/) const {
    return false;
  }
  /// Get the region/material of a mesh element and a flag whether it is
  /// associated to an active medium.
  virtual bool GetElementRegion(const std::size_t /*i*/, std::size_t& /*mat*/,
                                bool& /*drift*/) const {
    return false;
  }
  /// Return the number of mesh nodes.
  virtual std::size_t GetNumberOfNodes() const { return 0; }
  /// Get the coordinates of a mesh node.
  virtual bool GetNode(const std::size_t i, double& x, double& y,
                       double& z) const;

  /** Integrate the normal component of the electric field over a circle.
   * \param xc,yc centre of the circle [cm]
   * \param r radius [cm]
   * \param nI number of intervals for the integration
   *
   * \return charge enclosed in the circle [fC / cm]
   */
  double IntegrateFluxCircle(const double xc, const double yc, const double r,
                             const std::size_t nI = 50);
  /** Integrate the normal component of the electric field over a sphere.
   * \param xc,yc,zc centre of the sphere [cm]
   * \param r radius of the sphere [cm]
   * \param nI number of integration intervals in phi and theta
   *
   * \return charge enclosed in the sphere [fC]
   */
  double IntegrateFluxSphere(const double xc, const double yc, const double zc,
                             const double r, const std::size_t nI = 20);

  /** Integrate the normal component of the electric field over a parallelogram.
   * \param x0,y0,z0 coordinates of one of the corners [cm]
   * \param dx1,dy1,dz1 vector to one of the adjacent corners [cm]
   * \param dx2,dy2,dz2 vector to the other adjacent corner [cm]
   * \param nU,nV number of integration points in the two directions
   *
   * \return flux [V cm]
   */
  double IntegrateFluxParallelogram(const double x0, const double y0,
                                    const double z0, const double dx1,
                                    const double dy1, const double dz1,
                                    const double dx2, const double dy2,
                                    const double dz2, const std::size_t nU = 20,
                                    const std::size_t nV = 20);

  /// Integrate the normal component of the weighting field over a
  /// parallelogram.
  double IntegrateWeightingFluxParallelogram(
      const std::string& label, const double x0, const double y0,
      const double z0, const double dx1, const double dy1, const double dz1,
      const double dx2, const double dy2, const double dz2,
      const std::size_t nU = 20, const std::size_t nV = 20);

  /** Integrate the electric field flux through a line from
   * (x0,y0,z0) to (x1,y1,z1) along a direction (xp,yp,zp).
   * \param x0,y0,z0 coordinates of the starting point
   * \param x1,y1,z1 coordinates of the end point
   * \param xp,yp,zp normal vector
   * \param nI number of intervals for the integration
   * \param isign include both negative and positive contributions (0) or only
   * contributions with a given polarity (+1,-1)
   */
  double IntegrateFluxLine(const double x0, const double y0, const double z0,
                           const double x1, const double y1, const double z1,
                           const double xp, const double yp, const double zp,
                           const std::size_t nI, const int isign = 0);

  /** Determine whether the line between two points crosses a wire.
   * \param x0,y0,z0 first point [cm].
   * \param x1,y1,z1 second point [cm]
   * \param xc,yc,zc point [cm] where the line crosses the wire or the
   * coordinates of the wire centre.
   * \param centre flag whether to return the coordinates of the line-wire
   * crossing point or of the wire centre.
   * \param rc radius [cm] of the wire.
   */
  virtual bool CrossedWire(const double x0, const double y0, const double z0,
                           const double x1, const double y1, const double z1,
                           double& xc, double& yc, double& zc,
                           const bool centre, double& rc);
  /** Determine whether a particle is inside the trap radius of a wire.
   * \param q0 charge of the particle [in elementary charges].
   * \param x0,y0,z0 position [cm] of the particle.
   * \param xw,yw coordinates of the wire (if applicable).
   * \param rw radius of the wire (if applicable).
   */
  virtual bool InTrapRadius(const double q0, const double x0, const double y0,
                            const double z0, double& xw, double& yw,
                            double& rw);
  /// Determine whether the line between two points crosses a plane.
  virtual bool CrossedPlane(const double x0, const double y0, const double z0,
                            const double x1, const double y1, const double z1,
                            double& xc, double& yc, double& zc);

  /// Enable simple periodicity in the \f$x\f$ direction.
  void EnablePeriodicityX(const bool on = true) {
    m_symmetries.Set(Symmetry::Type::PeriodicX, on);
    UpdatePeriodicity();
  }
  /// Enable simple periodicity in the \f$y\f$ direction.
  void EnablePeriodicityY(const bool on = true) {
    m_symmetries.Set(Symmetry::Type::PeriodicY, on);
    UpdatePeriodicity();
  }
  /// Enable simple periodicity in the \f$z\f$ direction.
  void EnablePeriodicityZ(const bool on = true) {
    m_symmetries.Set(Symmetry::Type::PeriodicZ, on);
    UpdatePeriodicity();
  }
  /// Return periodicity flags.
  void IsPeriodic(bool& perx, bool& pery, bool& perz) {
    perx = m_symmetries.Has(Symmetry::Type::PeriodicX);
    pery = m_symmetries.Has(Symmetry::Type::PeriodicY);
    perz = m_symmetries.Has(Symmetry::Type::PeriodicZ);
  }

  /// Enable mirror periodicity in the \f$x\f$ direction.
  void EnableMirrorPeriodicityX(const bool on = true) {
    m_symmetries.Set(Symmetry::Type::MirrorX, on);
    UpdatePeriodicity();
  }
  /// Enable mirror periodicity in the \f$y\f$ direction.
  void EnableMirrorPeriodicityY(const bool on = true) {
    m_symmetries.Set(Symmetry::Type::MirrorY, on);
    UpdatePeriodicity();
  }
  /// Enable mirror periodicity in the \f$y\f$ direction.
  void EnableMirrorPeriodicityZ(const bool on = true) {
    m_symmetries.Set(Symmetry::Type::MirrorZ, on);
    UpdatePeriodicity();
  }
  /// Return mirror periodicity flags.
  void IsMirrorPeriodic(bool& perx, bool& pery, bool& perz) {
    perx = m_symmetries.Has(Symmetry::Type::MirrorX);
    pery = m_symmetries.Has(Symmetry::Type::MirrorY);
    perz = m_symmetries.Has(Symmetry::Type::MirrorZ);
  }

  /// Enable axial periodicity in the \f$x\f$ direction.
  void EnableAxialPeriodicityX(const bool on = true) {
    m_symmetries.Set(Symmetry::Type::AxialX, on);
    UpdatePeriodicity();
  }
  /// Enable axial periodicity in the \f$y\f$ direction.
  void EnableAxialPeriodicityY(const bool on = true) {
    m_symmetries.Set(Symmetry::Type::AxialY, on);
    UpdatePeriodicity();
  }
  /// Enable axial periodicity in the \f$z\f$ direction.
  void EnableAxialPeriodicityZ(const bool on = true) {
    m_symmetries.Set(Symmetry::Type::AxialZ, on);
    UpdatePeriodicity();
  }
  /// Return axial periodicity flags.
  void IsAxiallyPeriodic(bool& perx, bool& pery, bool& perz) {
    perx = m_symmetries.Has(Symmetry::Type::AxialX);
    pery = m_symmetries.Has(Symmetry::Type::AxialY);
    perz = m_symmetries.Has(Symmetry::Type::AxialZ);
  }

  /// Enable rotation symmetry around the \f$x\f$ axis.
  void EnableRotationSymmetryX(const bool on = true) {
    m_symmetries.Set(Symmetry::Type::RotationX, on);
    UpdatePeriodicity();
  }
  /// Enable rotation symmetry around the \f$y\f$ axis.
  void EnableRotationSymmetryY(const bool on = true) {
    m_symmetries.Set(Symmetry::Type::RotationY, on);
    UpdatePeriodicity();
  }
  /// Enable rotation symmetry around the \f$z\f$ axis.
  void EnableRotationSymmetryZ(const bool on = true) {
    m_symmetries.Set(Symmetry::Type::RotationZ, on);
    UpdatePeriodicity();
  }
  /// Return rotation symmetry flags.
  void IsRotationSymmetric(bool& rotx, bool& roty, bool& rotz) {
    rotx = m_symmetries.Has(Symmetry::Type::RotationX);
    roty = m_symmetries.Has(Symmetry::Type::RotationY);
    rotz = m_symmetries.Has(Symmetry::Type::RotationZ);
  }

  /// Enable triangular periodicity in the \f$xy\f$ plane.
  void EnableTriangleSymmetricXY(const bool on = true, const int oct = 2) {
    m_symmetries.Set(Symmetry::Type::TriangleXY, on);
    m_symmetries.Set(Symmetry::Type::MirrorX, on);
    m_symmetries.Set(Symmetry::Type::MirrorY, on);
    m_triangleSymmetricOct = oct;
  }
  /// Enable triangular periodicity in the \f$xz\f$ plane.
  void EnableTriangleSymmetricXZ(const bool on = true, const int oct = 2) {
    m_symmetries.Set(Symmetry::Type::TriangleXZ, on);
    m_symmetries.Set(Symmetry::Type::MirrorX, on);
    m_symmetries.Set(Symmetry::Type::MirrorZ, on);
    m_triangleSymmetricOct = oct;
  }
  /// Enable triangular periodicity in the \f$yz\f$ plane.
  void EnableTriangleSymmetricYZ(const bool on = true, const int oct = 2) {
    m_symmetries.Set(Symmetry::Type::TriangleYZ, on);
    m_symmetries.Set(Symmetry::Type::MirrorY, on);
    m_symmetries.Set(Symmetry::Type::MirrorZ, on);
    m_triangleSymmetricOct = oct;
  }

  /// Switch on debugging messages.
  void EnableDebugging(const bool on = true) { m_debug = on; }
  /// Switch off debugging messages.
  void DisableDebugging() { m_debug = false; }

  /// Does the component have a non-zero magnetic field?
  virtual bool HasMagneticField() const;

  /// Does the component have maps of the Townsend coefficient?
  virtual bool HasTownsendMap() const { return false; }
  /// Does the component have maps of the attachment coefficient?
  virtual bool HasAttachmentMap() const { return false; }
  /// Does the component have maps of the low-field mobility?
  virtual bool HasMobilityMap() const { return false; }
  /// Does the component have velocity maps?
  virtual bool HasVelocityMap() const { return false; }
  /// Does the component have ion density maps?
  virtual bool HasIonDensityMap() const { return false; }
  /// Does the component have negative ion density maps?
  virtual bool HasNegativeIonDensityMap() const { return false; }
  /// Does the component have electron maps?
  virtual bool HasElectronDensityMap() const { return false; }
  /// Does the component have hole maps?
  virtual bool HasHoleDensityMap() const { return false; }
  /// Does the component have a charge density map?
  virtual bool HasChargeDensityMap() const { return false; }

  /// Get the electron attachment coefficient.
  virtual bool ElectronAttachment(const double /*x*/, const double /*y*/,
                                  const double /*z*/, double& eta) {
    eta = 0;
    return false;
  }
  /// Get the hole attachment coefficient.
  virtual bool HoleAttachment(const double /*x*/, const double /*y*/,
                              const double /*z*/, double& eta) {
    eta = 0;
    return false;
  }

  virtual bool IonDensity(const double /*x*/, const double /*y*/,
                          const double /*z*/, double& rho) {
    rho = 0.;
    return false;
  }
  virtual bool NegativeIonDensity(const double /*x*/, const double /*y*/,
                                  const double /*z*/, double& rho) {
    rho = 0.;
    return false;
  }
  virtual bool ElectronDensity(const double /*x*/, const double /*y*/,
                               const double /*z*/, double& rho) {
    rho = 0.;
    return false;
  }
  virtual bool HoleDensity(const double /*x*/, const double /*y*/,
                           const double /*z*/, double& rho) {
    rho = 0.;
    return false;
  }

  // Get the electron mobility coefficient.
  virtual bool ElectronMobility(const double /*x*/, const double /*y*/,
                                const double /*z*/, double& mu) {
    mu = 0;
    return false;
  }
  /// Get the hole Mobility coefficient.
  virtual bool HoleMobility(const double /*x*/, const double /*y*/,
                            const double /*z*/, double& mu) {
    mu = 0;
    return false;
  }

  /// Get the electron Townsend coefficient.
  virtual bool ElectronTownsend(const double /*x*/, const double /*y*/,
                                const double /*z*/, double& alpha) {
    alpha = 0;
    return false;
  }
  /// Get the hole Townsend coefficient.
  virtual bool HoleTownsend(const double /*x*/, const double /*y*/,
                            const double /*z*/, double& alpha) {
    alpha = 0;
    return false;
  }
  /// Get the electron drift velocity.
  virtual bool ElectronVelocity(const double /*x*/, const double /*y*/,
                                const double /*z*/, double& vx, double& vy,
                                double& vz) {
    vx = vy = vz = 0;
    return false;
  }
  /// Get the hole drift velocity.
  virtual bool HoleVelocity(const double /*x*/, const double /*y*/,
                            const double /*z*/, double& vx, double& vy,
                            double& vz) {
    vx = vy = vz = 0;
    return false;
  }

  virtual double StepSizeHint() { return -1.; }

  /// Create and initialise GPU Transfer class
  virtual double CreateGPUTransferObject(ComponentGPU*& comp_gpu);

 protected:
  /// Class name.
  std::string m_className{"Component"};

  /// Pointer to the geometry.
  Geometry* m_geometry{nullptr};

  /// Constant magnetic field.
  std::array<double, 3> m_b0 = {{0., 0., 0.}};
  /// Ready for use?
  bool m_ready{false};

  /// Switch on/off debugging messages
  bool m_debug{false};

  Symmetry m_symmetries;
  /// Triangle symmetric octant of imported map (0 < phi < Pi/4 --> octant 1).
  int m_triangleSymmetricOct = 0;
  /// Octants where |x| >= |y|
  const std::array<int, 4> m_triangleOctRules = {1, 4, 5, 8};
  bool m_outsideCone = false;
  /// Time steps at which the delayed weighting potentials/fields are stored.
  std::vector<double> m_wdtimes;

  /// Reset the component.
  virtual void Reset() = 0;
  /// Verify periodicities.
  virtual void UpdatePeriodicity() = 0;

 private:
  double IntegrateFluxParallelogram(const double x0, const double y0,
                                    const double z0, const double dx1,
                                    const double dy1, const double dz1,
                                    const double dx2, const double dy2,
                                    const double dz2, const std::size_t nU,
                                    const std::size_t nV, const bool wfield,
                                    const std::string& label);
};

}  // namespace Garfield
#endif
