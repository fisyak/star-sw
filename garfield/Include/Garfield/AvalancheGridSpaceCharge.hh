#ifndef GARFIELD_AVALANCHEGRIDSPACECHARGE_HH
#define GARFIELD_AVALANCHEGRIDSPACECHARGE_HH

#include <array>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

#include "Garfield/ComponentChargedRing.hh"

namespace Garfield {
class Sensor;
class AvalancheMicroscopic;

/// Propagates avalanches with the 2d (axi-symmetric) space-charge routine from
/// Lippmann, Riegler (2004) in uniform background fields. Different options to
/// calculate space-charge-fields can be chosen.
class AvalancheGridSpaceCharge {
 public:
  /// Default constructor
  AvalancheGridSpaceCharge();
  /// Constructor
  explicit AvalancheGridSpaceCharge(Sensor *sensor);
  explicit AvalancheGridSpaceCharge(std::nullptr_t) = delete;
  /// Destructor
  ~AvalancheGridSpaceCharge() = default;

  /// Set the sensor (and determine if it includes a parallel-plate component).
  void SetSensor(Sensor *sensor);

  /// Reset the charges.
  void Reset();

  /// Enable/disable debugging (log messages) (default off)
  void EnableDebugging(const bool option = true) { m_bDebug = option; }

  /// Enable sticky anode (default on)
  void EnableStickyAnode(const bool option = true) { m_bStick = option; }

  /// Enable to use TOF swarm parameters (default on)
  void EnableTOF(const bool option = true) { m_bUseTOF = option; }

  /// Enable diffusion (default off)
  void EnableDiffusion(const bool option = true) { m_bDiffusion = option; }

  /// Enable space charge calculations (default on)
  void EnableSpaceChargeEffect(const bool on = true) { m_bSpaceCharge = on; }

  /// Enable adaptive time stepping (default on)
  void EnableAdaptiveTimeStepping(const bool option = true) {
    m_bAdaptiveTime = option;
  }

  /// Enable Monte Carlo (gain/diffusion) up to a certain total number of
  /// electrons e.g. (1e5) (default on)
  ///   if disabled: Mean values are considered instead of the statistical
  ///   processes
  void EnableMC(const bool option = true) { m_bMC = option; }

  /// Set electron saturation value applied for each gas gap if space charge
  /// effect is turned off (default 1e8)
  void SetNCrit(const long NCrit = 1e8) { m_lNCrit = NCrit; }

  /// Sets the method for calculating the space charge field.
  ///   Coulomb: free field approximation.
  ///   Mirror: symmetric three-layer single-gap RPC
  ///           (metal - resistive layer - gas - resistive layer - metal).
  void SetFieldCalculation(const std::string &option = "coulomb",
                           const int nof_approx = 1);

  /// Set the streamer-inception criterion constant K in the interval (0,
  /// &infin;) s.t. 1 = 100%
  void SetK(const double k = 0.95) { m_fStreamerK = k; }

  /// Stop the avalanche if K % field is reached
  void SetStopAtK(bool option = true) { m_bStopAtK = option; }

  /**
   *
   * @param zmin coordinate along direction of background field
   * @param zmax should more or less be at the end of the gap
   * @param zsteps number of steps
   * @param rmax coordinate perpendicular to background field
   * @param rsteps number of steps
   */
  void Set2dGrid(double zmin, double zmax, int zsteps, double rmax, int rsteps);

  /// Import electron (no ions) data from AvalancheMicroscopic class to
  /// axi-symmetric grid
  void AddElectrons(AvalancheMicroscopic *avmc);

  /// Set n electrons onto the grid
  void AddElectron(const double x, const double y, const double z,
                   const double t = 0., const unsigned int n = 1);

  /// Starts the simulation with the imported electrons for a time step dt
  /// (dt = -1 until there are no electrons left in the gap).
  void StartGridAvalanche(double dtime = -1);

  /// Returns the total positive charge in the gap's
  long GetAvalancheSize() const { return m_nPtot; }

  /// Return current mean distance of the electrons on the grid
  double GetMeanDistance();

  /// Returns if 100 * K % background charge has been reached
  [[nodiscard]] long ReachedKPercent() const {
    if (m_bFieldK)
      return m_lElectronsK;
    else
      return -1;
  }

  /// Returns the total electron number evolution
  [[nodiscard]] const std::vector<std::pair<double, long>> &
  GetElectronEvolution() const {
    return m_evolution;
  }

  /// Export the current grid to a txt file (electron, ions numbers and field
  /// magnitude)
  ///  Take care: only where electrons are located is the space-charge field
  ///  evaluated!
  void ExportGrid(const std::string &filename);

 private:
  struct GridNode {
    long nE{0};     ///< number of electrons
    double nP{0.};  ///< number of positive ions (smeared values allowed)
    double nN{0.};  ///< number of negative ions (smeared values allowed)
    // Electrons and ions at the next step in time:
    long nEHolder{0};     ///< at t+dt
    double nPHolder{0.};  ///< at t+dt
    double nNHolder{0.};  ///< at t+dt

    /// Magnitude of the drift velocity [cm/ns]
    double vd{0.};
    /// Diffusion along E.
    double dL{0.};
    /// Diffusion transverse to E (radial, phi dir is net 0).
    double dT{0.};

    double wv{0.};  ///< flux drift velocity [cm/ns]
    double wr{0.};  ///< bulk drift velocity [cm/ns]
    /// Townsend coefficient from TOF experiment.
    double alpha{0.};
    /// Attachment coefficient from TOF experiment.
    double eta{0.};

    /// Magnitude of the electric field.
    double emag{0.};
    /// Direction vector.
    double ctheta{1.};
    double stheta{0.};

    bool anode{false};  ///< init the anode
    /// Gas gap index: -1 if not gas gap; starts with 0, 1, ...
    int gap{0};
  };

  struct Point {
    double x{0.};
    double y{0.};
    double z{0.};  ///< coordinates
    double t{0.};  ///< time
    size_t n{1};
  };

  // Prepare grid and place stored electrons.
  bool Prepare();

  // Assign electron to the closest grid point
  bool SnapToGrid(double x, double y, double z, long n = 1, int gasLayer = 0);

  // Propagate the electrons by one step.
  bool Step();

  // Diffuses the electrons/nodes a timestep
  void DiffuseTimeStep(const double dx, const long nE, const double nP,
                       const double nN, const int iz, const int ir,
                       const int gasGap);

  // Redistributes the charges
  void DistributeCharges(long nElectron, double nPosIon, double nNegIon, int iz,
                         int ir, double stepZ, double stepR, int gasGap);

  // Get swarm parameters.
  void GetSwarmParameters(Medium *medium, const double emag, double &vd,
                          double &dL, double &dT, double &wv, double &wr,
                          double &alphaPT, double &etaPT) const;

  std::string m_className{"AvalancheGridSpaceCharge"};

  bool m_bDebug{false};
  bool m_bDiffusion{false};
  bool m_bStick{true};
  long m_lNCrit = {100000000};
  bool m_bSpaceCharge{true};

  float m_fStreamerK{0.95};
  bool m_bStopAtK{false};
  bool m_bFieldK{false};
  long m_lElectronsK{0};

  bool m_bAdaptiveTime{true};
  /// Flag if TOF parameters should be used, else Magboltz
  /// drift and SST spatial coefficients
  bool m_bUseTOF{true};

  bool m_bMC{true};

  int m_iFieldApprox{1};  //< order of approximation in Set(1,2,3,...)

  Sensor *m_sensor{nullptr};

  std::vector<double> m_zGrid;  ///< Grid points of z-coordinate.
  int m_zSteps{0};              ///< Number of grid points.
  double m_zStepSize{0.};       ///< Distance between the grid points.
  double m_zInvStep{0.};        ///< Inverse of the grid spacing.

  std::vector<double> m_rGrid;  ///< Grid points of r-coordinate.
  int m_rSteps{0};              ///< Number of grid points
  double m_rStepSize{0.};       ///< Distance between the grid points.
  double m_rInvStep{0.};        ///< Inverse of the grid spacing.

  /// Total number of electrons.
  long m_nEtot{0};
  /// Total amount of charge (number of positive ions) created.
  long m_nPtot{0};

  double m_time{0.};  ///< Clock.
  double m_dt{0.};    ///< Time step.

  /// Grid.
  std::vector<std::vector<GridNode>> m_grid;
  /// Electrons to transfer onto the grid.
  std::vector<Point> m_electrons;

  std::vector<std::pair<double, long>> m_evolution;

  /// Axis centres of each gas gap.
  std::vector<std::array<double, 3>> m_centre;
  /// Boundaries of each gas gap.
  std::vector<double> m_zBot;
  std::vector<double> m_zTop;
  /// Smallest and largest z-grid index of each gas gap.
  std::vector<int> m_izMin;
  std::vector<int> m_izMax;
  std::vector<double> m_alpha12;

  /// Medium in each gas gap.
  std::vector<Medium *> m_medium = {nullptr};
  /// Uniform background field in z direction, can be negative.
  std::vector<double> m_ezBkg = {0.};
  /// Threshold field for streamer formation.
  std::vector<double> m_ezThr = {0.};
  /// Is the gas gap saturated?
  std::vector<bool> m_saturated = {false};

  enum class FieldOption { Coulomb, Mirror };
  FieldOption m_fieldOption{FieldOption::Coulomb};

  /// Vector of ComponentChargedRing objects
  /// We need one ring system per gas gap.
  std::vector<ComponentChargedRing> m_rings;
};

}  // namespace Garfield

#endif  // GARFIELD_AVALANCHEGRIDSPACECHARGE_HH
