#ifndef G_AVALANCHE_GRID_H
#define G_AVALANCHE_GRID_H

#include <array>
#include <string>
#include <vector>

namespace Garfield {

class Sensor;
class AvalancheMicroscopic;
// class ComponentParallelPlate;

/// Calculate avalanches in a uniform electric field using avalanche statistics.
class AvalancheGrid {
 public:
  /// Default constructor
  AvalancheGrid() = default;
  /// Constructor
  explicit AvalancheGrid(Sensor *sensor);
  explicit AvalancheGrid(std::nullptr_t) = delete;
  /// Destructor
  ~AvalancheGrid() = default;

  /// Set the sensor.
  void SetSensor(Sensor *sensor);

  /// Start grid based avalanche simulation.
  void StartGridAvalanche();
  /// Set the electron drift velocity (in cm / ns).
  void SetElectronVelocity(const double vx, const double vy, const double vz);
  /// Set the electron Townsend coefficient (in 1 / cm).
  void SetElectronTownsend(const double town) { m_Townsend = town; }
  /// Set the electron attachment coefficient (in 1 / cm).
  void SetElectronAttachment(const double att) { m_Attachment = att; }
  /// Set the maximum avalanche size (1e7 by default).
  void SetMaxAvalancheSize(const double size) { m_MaxSize = size; }

  /** Add an electron to the initial configuration.
   *
   * \param x x-coordinate of initial electron.
   * \param y y-coordinate of initial electron.
   * \param z t-coordinate of initial electron.
   * \param t starting time of avalanche.
   * \param n number of electrons at this point.
   */
  void AddElectron(const double x, const double y, const double z,
                   const double t = 0, const int n = 1);
  /// Import electrons from AvalancheMicroscopic object.
  void AddElectrons(AvalancheMicroscopic *avmc);

  /** Set the grid.
   *
   * \param xmin,xmax x-coordinate range of the grid [cm].
   * \param xsteps number of x-coordinate points in the grid.
   * \param ymin,ymax y-coordinate range of the grid [cm].
   * \param ysteps number of y-coordinate points in the grid.
   * \param zmin,zmax z-coordinate range of the grid [cm].
   * \param zsteps number of z-coordinate points in the grid.
   */
  void SetGrid(const double xmin, const double xmax, const int xsteps,
               const double ymin, const double ymax, const int ysteps,
               const double zmin, const double zmax, const int zsteps);

  /// Returns the initial number of electrons in the avalanche.
  int GetAmountOfStartingElectrons() { return m_nestart; }
  /// Returns the final number of electrons in the avalanche.
  int GetAvalancheSize() { return m_nTotal; }

  void EnableDebugging() { m_debug = true; }

  void Reset();

 private:
  bool m_debug{false};

  double m_Townsend{-1};  // [1/cm]

  double m_Attachment{-1};  // [1/cm]

  double m_Velocity{0.};  // [cm/ns]

  std::vector<int> m_velNormal = {0, 0, 0};

  double m_MaxSize{1.6e7};  // Saturations size
  // Check if avalanche has reached maximum size
  bool m_Saturated{false};
  // Time when the avalanche has reached maximum size
  double m_SaturationTime{-1.};

  int m_nestart{0};

  std::vector<double> m_nLayer;

  std::string m_className{"AvalancheGrid"};

  Sensor *m_sensor{nullptr};

  bool m_printPar{false};

  std::vector<double> m_zgrid;  ///< Grid points of z-coordinate.
  double m_zStepSize{0.};       ///< Distance between the grid points.

  std::vector<double> m_ygrid;  ///< Grid points of y-coordinate.
  double m_yStepSize{0.};       ///< Distance between the grid points.

  std::vector<double> m_xgrid;  ///< Grid points of x-coordinate.
  double m_xStepSize{0.};       ///< Distance between the grid points.

  bool m_gridset{false};  ///< Keeps track if the grid has been defined.
  int m_nTotal{0};        ///< Total amount of charge.
  double m_time{0.};      ///< Clock.
  bool m_run{true};  ///< Tracking if the charges are still in the drift gap.

  struct Path {
    std::vector<double> ts;
    std::vector<std::array<double, 3> > xs;
    std::vector<double> qs;
  };

  struct AvalancheNode {
    double ix{0.};
    double iy{0.};
    double iz{0.};

    int n{1};

    int layer{0};

    double townsend{0.};
    double attachment{0.};
    double velocity{0.};

    double stepSize{0.};
    std::vector<int> velNormal = {0, 0, 0};

    double time{0.};  ///< Clock.
    double dt{-1.};   ///< time step.

    bool active{true};

    Path path;
  };

  std::vector<AvalancheNode> m_activeNodes;

  // Assign electron to the closest grid point.
  bool SnapToGrid(const double x, const double y, const double z,
                  const double v, const int n = 1);
  // Go to next time step.
  void NextAvalancheGridPoint();
  // Obtain the Townsend coef., Attachment coef. and velocity vector from
  // sensor class.
  bool GetParameters(AvalancheNode &node);

  void DeactivateNode(AvalancheNode &node);
};
}  // namespace Garfield

#endif
