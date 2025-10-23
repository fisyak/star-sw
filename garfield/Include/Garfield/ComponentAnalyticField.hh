#ifndef G_COMPONENT_ANALYTIC_FIELD_H
#define G_COMPONENT_ANALYTIC_FIELD_H

#include <array>
#include <complex>
#include <cstddef>
#include <mutex>
#include <string>
#include <vector>

#include "Garfield/Component.hh"

class TPad;

namespace Garfield {

class Medium;

/// Semi-analytic calculation of two-dimensional configurations
/// consisting of wires, planes, and tubes.

class ComponentAnalyticField : public Component {
 public:
  /// Constructor
  ComponentAnalyticField();
  /// Destructor
  ~ComponentAnalyticField() = default;

  /// Set the medium inside the cell.
  void SetMedium(Medium* medium);
  /// Add a wire at (x, y) .
  void AddWire(const double x, const double y, const double diameter,
               const double voltage, const std::string& label = "",
               const double length = 100., const double tension = 50.,
               const double rho = 19.3, const int ntrap = 5);
  /// Add a tube.
  void AddTube(const double radius, const double voltage, const int nEdges,
               const std::string& label = "");
  /// Add a plane at constant x.
  void AddPlaneX(const double x, const double voltage,
                 const std::string& label = "");
  /// Add a plane at constant y.
  void AddPlaneY(const double y, const double voltage,
                 const std::string& label = "");
  /// Add a plane at constant radius.
  void AddPlaneR(const double r, const double voltage,
                 const std::string& label = "");
  /// Add a plane at constant phi.
  void AddPlanePhi(const double phi, const double voltage,
                   const std::string& label = "");
  /** Add a strip in the y or z direction on an existing plane at constant x.
   * \param direction 'y' or 'z'.
   * \param x coordinate of the plane.
   * \param smin lower limit of the strip in y or z.
   * \param smax upper limit of the strip in y or z.
   * \param label weighting field identifier.
   * \param gap distance to the opposite plane (optional).
   */
  void AddStripOnPlaneX(const char direction, const double x, const double smin,
                        const double smax, const std::string& label,
                        const double gap = -1.);
  /// Add a strip in the x or z direction on an existing plane at constant y.
  void AddStripOnPlaneY(const char direction, const double y, const double smin,
                        const double smax, const std::string& label,
                        const double gap = -1.);
  /// Add a strip in the phi or z direction on an existing plane at constant
  /// radius.
  void AddStripOnPlaneR(const char direction, const double r, const double smin,
                        const double smax, const std::string& label,
                        const double gap = -1.);
  /// Add a strip in the r or z direction on an existing plane at constant phi.
  void AddStripOnPlanePhi(const char direction, const double phi,
                          const double smin, const double smax,
                          const std::string& label, const double gap = -1.);
  /** Add a pixel on an existing plane at constant x.
   * \param x coordinate of the plane.
   * \param ymin lower limit of the pixel cell in y,
   * \param ymax upper limit of the pixel cell in y.
   * \param zmin lower limit of the pixel cell in z.
   * \param zmax upper limit of the pixel cell in z.
   * \param label weighting field identifier.
   * \param gap distance to the opposite plane (optional).
   * \param rot rotation angle (rad) of the pixel (optional).
   */
  void AddPixelOnPlaneX(const double x, const double ymin, const double ymax,
                        const double zmin, const double zmax,
                        const std::string& label, const double gap = -1.,
                        const double rot = 0.);
  /// Add a pixel on an existing plane at constant y.
  void AddPixelOnPlaneY(const double y, const double xmin, const double xmax,
                        const double zmin, const double zmax,
                        const std::string& label, const double gap = -1.,
                        const double rot = 0.);
  /// Add a pixel on an existing plane at constant radius.
  void AddPixelOnPlaneR(const double r, const double phimin,
                        const double phimax, const double zmin,
                        const double zmax, const std::string& label,
                        const double gap = -1.);
  /// Add a pixel on an existing plane at constant phi.
  void AddPixelOnPlanePhi(const double phi, const double rmin,
                          const double rmax, const double zmin,
                          const double zmax, const std::string& label,
                          const double gap = -1.);

  /// Set the periodic length [cm] in the x-direction.
  void SetPeriodicityX(const double s);
  /// Set the periodic length [cm] in the y-direction.
  void SetPeriodicityY(const double s);
  /// Set the periodicity [degree] in phi.
  void SetPeriodicityPhi(const double phi);
  /// Get the periodic length in the x-direction.
  bool GetPeriodicityX(double& s);
  /// Get the periodic length in the y-direction.
  bool GetPeriodicityY(double& s);
  /// Get the periodicity [degree] in phi.
  bool GetPeriodicityPhi(double& s);

  /// Use Cartesian coordinates (default).
  void SetCartesianCoordinates();
  /// Use polar coordinates.
  void SetPolarCoordinates();
  /// Are polar coordinates being used?
  bool IsPolar() const { return m_polar; }

  /// Print all available information on the cell.
  void PrintCell();
  /// Make a plot of the cell layout.
  void PlotCell(TPad* pad);

  /// Add a point charge.
  void AddCharge(const double x, const double y, const double z,
                 const double q);
  /// Remove all point charges.
  void ClearCharges();
  /// Print a list of the point charges.
  void PrintCharges() const;

  /** Return the cell type.
   * Cells are classified according to the number
   * and orientation of planes, the presence of
   * periodicities and the location of the wires
   * as one of the following types:
   *
   * A    non-periodic cells with at most 1 x- and 1 y-plane
   * B1X  x-periodic cells without x-planes and at most 1 y-plane
   * B1Y  y-periodic cells without y-planes and at most 1 x-plane
   * B2X  cells with 2 x-planes and at most 1 y-plane
   * B2Y  cells with 2 y-planes and at most 1 x-plane
   * C1   doubly periodic cells without planes
   * C2X  doubly periodic cells with x-planes
   * C2Y  doubly periodic cells with y-planes
   * C3   double periodic cells with x- and y-planes
   * D1   round tubes without axial periodicity
   * D2   round tubes with axial periodicity
   * D3   polygonal tubes without axial periodicity
   */
  std::string GetCellType() {
    if (!m_cellset) {
      if (CellCheck()) CellType();
    }
    return GetCellType(m_cellType);
  }

  /// Request calculation of weighting field and potential
  /// for a given group of wires or planes.
  void AddReadout(const std::string& label, const bool silent = false);

  void SetNumberOfCellCopies(const std::size_t nfourier);

  /** Calculate multipole moments for a given wire.
   * \param iw Index of the wire.
   * \param order Order of the highest multipole moment.
   * \param print Print information about the fitting process.
   * \param plot Plot the potential and multipole fit around the wire.
   * \param rmult Distance in multiples of the wire radius
   *              at which the decomposition is to be carried out.
   * \param eps Used in the fit for calculating the covariance matrix.
   * \param nMaxIter Maximum number of iterations in the fit.
   **/
  bool MultipoleMoments(const std::size_t iw, const std::size_t order = 4,
                        const bool print = false, const bool plot = false,
                        const double rmult = 1., const double eps = 1.e-4,
                        const std::size_t nMaxIter = 20);
  /// Request dipole terms be included for each of the wires (default: off).
  void EnableDipoleTerms(const bool on = true);
  /// Check the quality of the capacitance matrix inversion (default: off).
  void EnableChargeCheck(const bool on = true) { m_chargeCheck = on; }

  /// Get the number of wires.
  std::size_t GetNumberOfWires() const { return m_nWires; }
  /// Retrieve the parameters of a wire.
  bool GetWire(const std::size_t i, double& x, double& y, double& diameter,
               double& voltage, std::string& label, double& length,
               double& charge, int& ntrap) const;

  /// Get the number of equipotential planes at constant x.
  std::size_t GetNumberOfPlanesX() const;
  /// Get the number of equipotential planes at constant y.
  std::size_t GetNumberOfPlanesY() const;
  /// Get the number of equipotential planes at constant radius.
  std::size_t GetNumberOfPlanesR() const;
  /// Get the number of equipotential planes at constant phi.
  std::size_t GetNumberOfPlanesPhi() const;
  /// Retrieve the parameters of a plane at constant x.
  bool GetPlaneX(const std::size_t i, double& x, double& voltage,
                 std::string& label) const;
  /// Retrieve the parameters of a plane at constant y.
  bool GetPlaneY(const std::size_t i, double& y, double& voltage,
                 std::string& label) const;
  /// Retrieve the parameters of a plane at constant radius.
  bool GetPlaneR(const std::size_t i, double& r, double& voltage,
                 std::string& label) const;
  /// Retrieve the parameters of a plane at constant phi.
  bool GetPlanePhi(const std::size_t i, double& phi, double& voltage,
                   std::string& label) const;
  /// Retrieve the tube parameters.
  bool GetTube(double& r, double& voltage, int& nEdges,
               std::string& label) const;

  /** Vary the potential of selected electrodes to match (a function of)
   * the potential or field along a given line to a target.
   * \param groups Identifier of the electrodes for which to vary
   *               the potential.
   * \param field_function A function of the coordinates (x, y or r, phi),
   *                       the electrostatic field (ex, ey, e) and
   *                       potential (v).
   * \param target Value of the field function to be reproduced.
   * \param x0,y0 Starting point of the line.
   * \param x1,y1 End point of the line.
   * \param nP Number of points on the line.
   * \param print Flag to print out information during each fit cycle.
   **/
  bool OptimiseOnTrack(const std::vector<std::string>& groups,
                       const std::string& field_function, const double target,
                       const double x0, const double y0, const double x1,
                       const double y1, const std::size_t nP = 20,
                       const bool print = true);
  /// Vary the potential of selected electrodes to match (a function of)
  /// the potential or field on an x-y (or r-phi) grid of points.
  bool OptimiseOnGrid(const std::vector<std::string>& groups,
                      const std::string& field_function, const double target,
                      const double x0, const double y0, const double x1,
                      const double y1, const std::size_t nX = 10,
                      const std::size_t nY = 10, const bool print = true);
  /// Vary the potential of selected electrodes to match (a function of)
  /// the potential or field on the surfaces of a set of wires.
  bool OptimiseOnWires(const std::vector<std::string>& groups,
                       const std::string& field_function, const double target,
                       const std::vector<std::size_t>& wires,
                       const bool print = true);

  /** Set the conditions at which to allow the iteration to stop.
   * \param dist Maximum deviation among all points
   *             between target and field function.
   * \param eps Relative change between iterations.
   * \param nMaxIter Maximum number of iterations.
   **/
  void SetOptimisationParameters(const double dist = 1.,
                                 const double eps = 1.e-4,
                                 const std::size_t nMaxIter = 10);

  /// Calculate the electric field at a given wire position, as if the wire
  /// itself were not there, but with the presence of its mirror images.
  bool ElectricFieldAtWire(const std::size_t iw, double& ex, double& ey);

  /// Set the number of grid lines at which the electrostatic force
  /// as function of the wire displacement is computed.
  void SetScanningGrid(const std::size_t nX, const std::size_t nY);
  /// Specify explicitly the boundaries of the the scanning area (i. e. the
  /// area in which the electrostatic force acting on a wire is computed).
  void SetScanningArea(const double xmin, const double xmax, const double ymin,
                       const double ymax);
  /// Set the scanning area to the largest area around each wire
  /// which is free from other cell elements.
  void SetScanningAreaLargest() { m_scanRange = ScanningRange::Largest; }
  /// Set the scanning area based on the zeroth-order estimates of the
  /// wire shift, enlarged by a scaling factor. This is the default behaviour.
  void SetScanningAreaFirstOrder(const double scale = 2.);
  /// Switch on/off extrapolation of electrostatic forces beyond the
  /// scanning area (default: off).
  void EnableExtrapolation(const bool on = true) { m_extrapolateForces = on; }

  /// Set the gravity orientation.
  void SetGravity(const double dx, const double dy, const double dz);
  /// Get the gravity orientation.
  void GetGravity(double& dx, double& dy, double& dz) const;
  /// Include gravity in the sag computation or not.
  void EnableGravity(const bool on = true) { m_useGravitationalForce = on; }
  /// Include the electrostatic force in the sag computation or not.
  void EnableElectrostaticForce(const bool on = true) {
    m_useElectrostaticForce = on;
  }
  /** Calculate a table of the forces acting on a wire.
   * \param iw index of the wire
   * \param xMap coordinates of the grid lines in x
   * \param yMap coordinates of the grid lines in y
   * \param fxMap x-components of the force at the grid points
   * \param fyMap y-components of the force at the grid points
   **/
  bool ForcesOnWire(const std::size_t iw, std::vector<double>& xMap,
                    std::vector<double>& yMap,
                    std::vector<std::vector<double> >& fxMap,
                    std::vector<std::vector<double> >& fyMap);
  /** Compute the sag profile of a wire.
    * \param iw index of the wire
    * \param detailed flag to request a detailed calculation of the profile
                      or only a fast one.
    * \param csag coordinate along the wire.
    * \param xsag x components of the sag profile.
    * \param ysag y components of the sag profile.
    * \param stretch relative elongation.
    * \param print flag to print the calculation results or not.
    **/
  bool WireDisplacement(const std::size_t iw, const bool detailed,
                        std::vector<double>& csag, std::vector<double>& xsag,
                        std::vector<double>& ysag, double& stretch,
                        const bool print = true);
  /// Set the number of shots used for numerically solving the wire sag
  /// differential equation.
  void SetNumberOfShots(const std::size_t n) { m_nShots = n; }
  /// Set the number of integration steps within each shot (must be >= 1).
  void SetNumberOfSteps(const std::size_t n);

  Medium* GetMedium(const double x, const double y, const double z) override;
  void ElectricField(const double x, const double y, const double z, double& ex,
                     double& ey, double& ez, Medium*& m, int& status) override;

  void ElectricField(const double x, const double y, const double z, double& ex,
                     double& ey, double& ez, double& v, Medium*& m,
                     int& status) override;

  using Component::ElectricField;
  bool GetVoltageRange(double& pmin, double& pmax) override;

  void WeightingField(const double x, const double y, const double z,
                      double& wx, double& wy, double& wz,
                      const std::string& label) override {
    wx = wy = wz = 0.;
    if (!m_sigset) PrepareSignals();
    Wfield(x, y, z, wx, wy, wz, label);
  }
  double WeightingPotential(const double x, const double y, const double z,
                            const std::string& label) override {
    if (!m_sigset) PrepareSignals();
    return Wpot(x, y, z, label);
  }

  bool GetBoundingBox(double& x0, double& y0, double& z0, double& x1,
                      double& y1, double& z1) override;
  bool GetElementaryCell(double& x0, double& y0, double& z0, double& x1,
                         double& y1, double& z1) override;

  bool CrossedWire(const double x0, const double y0, const double z0,
                   const double x1, const double y1, const double z1,
                   double& xc, double& yc, double& zc, const bool centre,
                   double& rc) override;

  bool InTrapRadius(const double q0, const double x0, const double y0,
                    const double z0, double& xw, double& yx,
                    double& rw) override;

  bool CrossedPlane(const double x0, const double y0, const double z0,
                    const double x1, const double y1, const double z1,
                    double& xc, double& yc, double& zc) override;

  enum Cell {
    A00,
    B1X,
    B1Y,
    B2X,
    B2Y,
    C10,
    C2X,
    C2Y,
    C30,
    D10,
    D20,
    D30,
    D40,
    Unknown
  };

  double StepSizeHint() override;

 private:
  std::mutex m_mutex;

  Medium* m_medium{nullptr};

  bool m_chargeCheck{false};

  bool m_cellset{false};
  bool m_sigset{false};

  bool m_polar{false};

  // Cell type.
  Cell m_cellType{Unknown};

  // Bounding box
  double m_xmin{0.};
  double m_xmax{0.};
  double m_ymin{0.};
  double m_ymax{0.};
  double m_zmin{0.};
  double m_zmax{0.};

  // Voltage range
  double m_vmin{0.};
  double m_vmax{0.};

  // Periodicities
  bool m_perx{false};
  bool m_pery{false};
  double m_sx{0.};
  double m_sy{0.};

  // Signals
  int m_nFourier{1};
  Cell m_cellTypeFourier{A00};
  bool m_fperx{false};
  bool m_fpery{false};
  int m_mxmin{0};
  int m_mxmax{0};
  int m_mymin{0};
  int m_mymax{0};
  int m_mfexp{0};

  std::vector<std::string> m_readout;

  // Wires
  std::size_t m_nWires{0};
  struct Wire {
    double x{0.};
    double y{0.};      ///< Location.
    double r{0.};      ///< Radius.
    double v{0.};      ///< Potential.
    double e{0.};      ///< Charge.
    std::string type;  ///< Label.
    double u{0.};      ///< Length.
    int ind{0};        ///< Readout group.
    /// Trap radius. Particle is "trapped" if within nTrap * radius of wire.
    int nTrap{0};
    double tension{0.};  ///< Stretching weight.
    double density{0.};  ///< Density.
  };
  std::vector<Wire> m_w;

  // Option for computation of dipole terms
  bool m_dipole{false};
  // Dipole angle and amplitude
  std::vector<double> m_cosph2;
  std::vector<double> m_sinph2;
  std::vector<double> m_amp2;

  // Parameters for B2 type cells
  std::vector<double> m_b2sin;
  // Parameters for C type cells
  int m_mode{0};
  std::complex<double> m_zmult;
  double m_p1{0.};
  double m_p2{0.};
  double m_c1{0.};
  // Parameters for D3 type cells
  // Wire positions in conformal mapping
  std::vector<std::complex<double> > m_zw;
  double m_kappa{0.};

  // Reference potential
  double m_v0{0.};
  double m_corvta{0.};
  double m_corvtb{0.};
  double m_corvtc{0};

  // Planes
  // Existence
  bool m_ynplan[4]{false, false, false, false};
  bool m_ynplax{false};
  bool m_ynplay{false};
  // Coordinates
  double m_coplan[4];
  double m_coplax{0.};
  double m_coplay{0.};
  // Voltages
  double m_vtplan[4]{0., 0., 0., 0.};

  struct Strip {
    std::string type;  ///< Label.
    int ind{0};        ///< Readout group.
    double smin{0.};
    double smax{0.};  ///< Coordinates.
    double gap{0.};   ///< Distance to the opposite electrode.
  };

  struct Pixel {
    std::string type;  ///< Label.
    int ind{0};        ///< Readout group.
    double smin{0.};
    double smax{0.};  ///< Coordinates in x/y.
    double zmin{0.};
    double zmax{0.};  ///< Coordinates in z.
    double gap{-1.};  ///< Distance to the opposite electrode.
    double cphi{1.};  ///< Rotation.
    double sphi{0.};  ///< Rotation.
  };

  struct Plane {
    std::string type;  ///< Label.
    int ind{0};        ///< Readout group.
    double ewxcor{0.};
    double ewycor{0.};           ///< Background weighting fields
    std::vector<Strip> strips1;  ///< x/y strips.
    std::vector<Strip> strips2;  ///< z strips.
    std::vector<Pixel> pixels;   ///< Pixels.
  };
  std::array<Plane, 5> m_planes;

  // Tube
  bool m_tube{false};
  int m_mtube{0};
  int m_ntube{1};
  double m_cotube{1.};
  double m_cotube2{1.};
  double m_vttube{0.};

  // Smallest dimension.
  double m_dmin{-1.};

  // Wire weighting charges.
  std::vector<std::vector<std::vector<double> > > m_qwire;
  // Plane weighting charges.
  std::vector<std::vector<std::vector<double> > > m_qplane;

  // Point charges
  struct Charge3d {
    double x{0.};
    double y{0.};
    double z{0.};  ///< Coordinates.
    double e{0.};  ///< Charge.
  };
  std::vector<Charge3d> m_ch3d;
  std::size_t m_nTermBessel{10};
  std::size_t m_nTermPoly{100};

  bool m_useElectrostaticForce{true};
  bool m_useGravitationalForce{true};
  // Gravity
  std::array<double, 3> m_down{{0, 0, 1}};
  // Number of shots used for solving the wire sag differential equations
  std::size_t m_nShots{2};
  // Number of integration steps within each shot.
  std::size_t m_nSteps{20};
  // Options for setting the range of wire shifts
  // for which the forces are computed.
  enum class ScanningRange { Largest = 0, FirstOrder, User };
  ScanningRange m_scanRange{ScanningRange::FirstOrder};
  // Limits of the user-specified scanning range.
  double m_xScanMin{0.};
  double m_xScanMax{0.};
  double m_yScanMin{0.};
  double m_yScanMax{0.};
  // Scaling factor for first-order estimate of the scanning range.
  double m_scaleRange{2.};
  // Number of grid lines at which the forces are stored.
  std::size_t m_nScanX{11};
  std::size_t m_nScanY{11};
  // Extrapolate beyond the scanning range or not.
  bool m_extrapolateForces{false};

  // Maximum deviation between target and field function at which
  // to allow the iteration to stop.
  double m_optDist{1.};
  // Relative change in Euclidean distance between target and
  // field function at which to allow the iteration to stop.
  double m_optEps{1.e-4};
  // Maximum number of iterations in the optimisation fit.
  std::size_t m_optNitmax{10};

  void UpdatePeriodicity() override;
  void Reset() override {
    CellInit();
    m_medium = nullptr;
  }

  void CellInit();
  bool Prepare();
  bool CellCheck();
  bool WireCheck() const;
  bool CellType();
  std::string GetCellType(const Cell) const;
  bool PrepareStrips();
  bool PrepareSignals();
  bool SetupWireSignals();
  bool SetupPlaneSignals();

  // Calculation of charges
  bool Setup();
  bool Update(const std::vector<double>& vw, const std::array<double, 5>& vp);
  bool SetupA00();
  bool SetupB1X();
  bool SetupB1Y();
  bool SetupB2X();
  bool SetupB2Y();
  bool SetupC10();
  bool SetupC2X();
  bool SetupC2Y();
  bool SetupC30();
  bool SetupD10();
  bool SetupD20();
  bool SetupD30();

  bool IprA00(const int mx, const int my,
              std::vector<std::vector<std::complex<double> > >& mat);
  bool IprB2X(const int my,
              std::vector<std::vector<std::complex<double> > >& mat);
  bool IprB2Y(const int mx,
              std::vector<std::vector<std::complex<double> > >& mat);
  bool IprC2X(std::vector<std::vector<std::complex<double> > >& mat);
  bool IprC2Y(std::vector<std::vector<std::complex<double> > >& mat);
  bool IprC30(std::vector<std::vector<std::complex<double> > >& mat);
  bool IprD10(std::vector<std::vector<std::complex<double> > >& mat);
  bool IprD30(std::vector<std::vector<std::complex<double> > >& mat);

  bool SetupDipoleTerms();

  // Inversion of the capacitance matrix
  bool Charge(std::vector<std::vector<double> >& mat);

  // Evaluation of the electric field
  int Field(const double xin, const double yin, const double zin, double& ex,
            double& ey, double& ez, double& volt, const bool opt);
  void FieldA00(const double xpos, const double ypos, double& ex, double& ey,
                double& volt, const bool opt) const;
  void FieldB1X(const double xpos, const double ypos, double& ex, double& ey,
                double& volt, const bool opt) const;
  void FieldB1Y(const double xpos, const double ypos, double& ex, double& ey,
                double& volt, const bool opt) const;
  void FieldB2X(const double xpos, const double ypos, double& ex, double& ey,
                double& volt, const bool opt) const;
  void FieldB2Y(const double xpos, const double ypos, double& ex, double& ey,
                double& volt, const bool opt) const;
  void FieldC10(const double xpos, const double ypos, double& ex, double& ey,
                double& volt, const bool opt) const;
  void FieldC2X(const double xpos, const double ypos, double& ex, double& ey,
                double& volt, const bool opt) const;
  void FieldC2Y(const double xpos, const double ypos, double& ex, double& ey,
                double& volt, const bool opt) const;
  void FieldC30(const double xpos, const double ypos, double& ex, double& ey,
                double& volt, const bool opt) const;
  void FieldD10(const double xpos, const double ypos, double& ex, double& ey,
                double& volt, const bool opt) const;
  void FieldD20(const double xpos, const double ypos, double& ex, double& ey,
                double& volt, const bool opt) const;
  void FieldD30(const double xpos, const double ypos, double& ex, double& ey,
                double& volt, const bool opt) const;

  // Field due to point charges
  void Field3dA00(const double x, const double y, const double z, double& ex,
                  double& ey, double& ez, double& volt) const;
  void Field3dB2X(const double x, const double y, const double z, double& ex,
                  double& ey, double& ez, double& volt) const;
  void Field3dB2Y(const double x, const double y, const double z, double& ex,
                  double& ey, double& ez, double& volt) const;
  void Field3dD10(const double x, const double y, const double z, double& ex,
                  double& ey, double& ez, double& volt) const;
  // Evaluation of the weighting field
  bool Wfield(const double x, const double y, const double z, double& ex,
              double& ey, double& ez, const std::string& label) const;
  void WfieldWireA00(const double x, const double y, double& ex, double& ey,
                     const int mx, const int my,
                     const std::vector<double>& qw) const;
  void WfieldWireB2X(const double x, const double y, double& ex, double& ey,
                     const int my, const std::vector<double>& qw) const;
  void WfieldWireB2Y(const double x, const double y, double& ex, double& ey,
                     const int mx, const std::vector<double>& qw) const;
  void WfieldWireC2X(const double x, const double y, double& ex, double& ey,
                     const std::vector<double>& qw) const;
  void WfieldWireC2Y(const double x, const double y, double& ex, double& ey,
                     const std::vector<double>& qw) const;
  void WfieldWireC30(const double x, const double y, double& ex, double& ey,
                     const std::vector<double>& qw) const;
  void WfieldWireD10(const double x, const double y, double& ex, double& ey,
                     const std::vector<double>& qw) const;
  void WfieldWireD30(const double x, const double y, double& ex, double& ey,
                     const std::vector<double>& qw) const;
  void WfieldPlaneA00(const double x, const double y, double& ex, double& ey,
                      const int mx, const int my,
                      const std::vector<double>& qp) const;
  void WfieldPlaneB2X(const double x, const double y, double& ex, double& ey,
                      const int my, const std::vector<double>& qp) const;
  void WfieldPlaneB2Y(const double x, const double ypos, double& ex, double& ey,
                      const int mx, const std::vector<double>& qp) const;
  void WfieldPlaneC2X(const double x, const double y, double& ex, double& ey,
                      const std::vector<double>& qp) const;
  void WfieldPlaneC2Y(const double x, const double y, double& ex, double& ey,
                      const std::vector<double>& qp) const;
  void WfieldPlaneC30(const double x, const double y, double& ex, double& ey,
                      const std::vector<double>& qp) const;
  void WfieldPlaneD10(const double x, const double y, double& ex, double& ey,
                      const std::vector<double>& qp) const;
  void WfieldPlaneD30(const double x, const double y, double& ex, double& ey,
                      const std::vector<double>& qp) const;
  void WfieldStripZ(const double x, const double y, double& ex, double& ey,
                    const int ip, const Strip& strip) const;
  void WfieldStripXy(const double x, const double y, const double z, double& ex,
                     double& ey, double& ez, const int ip,
                     const Strip& strip) const;
  void WfieldStrip(const double x, const double y, const double g,
                   const double w, double& fx, double& fy) const;
  void WfieldPixel(const double x, const double y, const double z, double& ex,
                   double& ey, double& ez, const int ip,
                   const Pixel& pixel) const;

  // Evaluation of the weighting potential.
  double Wpot(const double x, const double y, const double z,
              const std::string& label) const;
  double WpotWireA00(const double x, const double y, const int mx, const int my,
                     const std::vector<double>& qw) const;
  double WpotWireB2X(const double x, const double y, const int my,
                     const std::vector<double>& qw) const;
  double WpotWireB2Y(const double x, const double y, const int mx,
                     const std::vector<double>& qw) const;
  double WpotWireC2X(const double x, const double y,
                     const std::vector<double>& qw) const;
  double WpotWireC2Y(const double x, const double y,
                     const std::vector<double>& qw) const;
  double WpotWireC30(const double x, const double y,
                     const std::vector<double>& qw) const;
  double WpotWireD10(const double x, const double y,
                     const std::vector<double>& qw) const;
  double WpotWireD30(const double x, const double y,
                     const std::vector<double>& qw) const;
  double WpotPlaneA00(const double x, const double y, const int mx,
                      const int my, const std::vector<double>& qp) const;
  double WpotPlaneB2X(const double x, const double y, const int my,
                      const std::vector<double>& qp) const;
  double WpotPlaneB2Y(const double x, const double y, const int mx,
                      const std::vector<double>& qp) const;
  double WpotPlaneC2X(const double x, const double y,
                      const std::vector<double>& qp) const;
  double WpotPlaneC2Y(const double x, const double y,
                      const std::vector<double>& qp) const;
  double WpotPlaneC30(const double x, const double y,
                      const std::vector<double>& qp) const;
  double WpotPlaneD10(const double x, const double y,
                      const std::vector<double>& qp) const;
  double WpotPlaneD30(const double x, const double y,
                      const std::vector<double>& qp) const;
  double WpotStripZ(const double x, const double y, const int ip,
                    const Strip& strip) const;
  double WpotStripXy(const double x, const double y, const double z,
                     const int ip, const Strip& strip) const;
  double WpotPixel(const double x, const double y, const double z, const int ip,
                   const Pixel& pixel) const;

  // Functions for calculating the electric field at a given wire position,
  // as if the wire itself were not there but with the presence
  // of its mirror images.
  void FieldAtWireA00(const double xpos, const double ypos, double& ex,
                      double& ey, const std::vector<bool>& cnalso) const;
  void FieldAtWireB1X(const double xpos, const double ypos, double& ex,
                      double& ey, const std::vector<bool>& cnalso) const;
  void FieldAtWireB1Y(const double xpos, const double ypos, double& ex,
                      double& ey, const std::vector<bool>& cnalso) const;
  void FieldAtWireB2X(const double xpos, const double ypos, double& ex,
                      double& ey, const std::vector<bool>& cnalso) const;
  void FieldAtWireB2Y(const double xpos, const double ypos, double& ex,
                      double& ey, const std::vector<bool>& cnalso) const;
  void FieldAtWireC10(const double xpos, const double ypos, double& ex,
                      double& ey, const std::vector<bool>& cnalso) const;
  void FieldAtWireC2X(const double xpos, const double ypos, double& ex,
                      double& ey, const std::vector<bool>& cnalso) const;
  void FieldAtWireC2Y(const double xpos, const double ypos, double& ex,
                      double& ey, const std::vector<bool>& cnalso) const;
  void FieldAtWireC30(const double xpos, const double ypos, double& ex,
                      double& ey, const std::vector<bool>& cnalso) const;
  void FieldAtWireD10(const double xpos, const double ypos, double& ex,
                      double& ey, const std::vector<bool>& cnalso) const;
  void FieldAtWireD20(const double xpos, const double ypos, double& ex,
                      double& ey, const std::vector<bool>& cnalso) const;
  void FieldAtWireD30(const double xpos, const double ypos, double& ex,
                      double& ey, const std::vector<bool>& cnalso) const;

  void DipoleFieldA00(const double xpos, const double ypos, double& ex,
                      double& ey, double& volt, const bool opt) const;
  void DipoleFieldB1X(const double xpos, const double ypos, double& ex,
                      double& ey, double& volt, const bool opt) const;
  void DipoleFieldB1Y(const double xpos, const double ypos, double& ex,
                      double& ey, double& volt, const bool opt) const;
  void DipoleFieldB2X(const double xpos, const double ypos, double& ex,
                      double& ey, double& volt, const bool opt) const;
  void DipoleFieldB2Y(const double xpos, const double ypos, double& ex,
                      double& ey, double& volt, const bool opt) const;

  // Auxiliary functions for C type cells
  double Ph2(const double xpos, const double ypos) const;
  double Ph2Lim(const double radius) const;
  void E2Sum(const double xpos, const double ypos, double& ex,
             double& ey) const;

  // Mapping function for D30 type cells
  void ConformalMap(const std::complex<double>& z, std::complex<double>& ww,
                    std::complex<double>& wd) const;

  static bool InTube(const double x0, const double y0, const double a,
                     const int n);

  bool SagDetailed(const Wire& wire, const std::vector<double>& xMap,
                   const std::vector<double>& yMap,
                   const std::vector<std::vector<double> >& fxMap,
                   const std::vector<std::vector<double> >& fyMap,
                   std::vector<double>& csag, std::vector<double>& xsag,
                   std::vector<double>& ysag) const;
  bool GetForceRatio(const Wire& wire, const double coor,
                     const std::array<double, 2>& bend,
                     const std::array<double, 2>& dbend,
                     std::array<double, 2>& f, const std::vector<double>& xMap,
                     const std::vector<double>& yMap,
                     const std::vector<std::vector<double> >& fxMap,
                     const std::vector<std::vector<double> >& fyMap) const;
  bool FindZeroes(const Wire& wire, const double h, std::vector<double>& x,
                  const std::vector<double>& xMap,
                  const std::vector<double>& yMap,
                  const std::vector<std::vector<double> >& fxMap,
                  const std::vector<std::vector<double> >& fyMap) const;
  bool StepRKN(const Wire& wire, const double h, double& x,
               std::array<double, 2>& y, std::array<double, 2>& yp,
               const std::vector<double>& xMap, const std::vector<double>& yMap,
               const std::vector<std::vector<double> >& fxMap,
               const std::vector<std::vector<double> >& fyMap) const;
  bool Trace(const Wire& wire, const double h, const std::vector<double>& xx,
             std::vector<double>& f, const std::vector<double>& xMap,
             const std::vector<double>& yMap,
             const std::vector<std::vector<double> >& fxMap,
             const std::vector<std::vector<double> >& fyMap) const;
  std::size_t SignalLayer(const int mx, const int my) const;

  void InitialiseFitParameters(
      const std::vector<std::string>& groups, std::vector<double>& vw0,
      std::array<double, 5>& vp0, std::vector<double>& aFit,
      std::vector<std::vector<std::size_t> >& wiresInGroup,
      std::vector<std::vector<std::size_t> >& planesInGroup);
};
}  // namespace Garfield

#endif
