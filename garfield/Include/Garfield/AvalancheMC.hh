#ifndef G_AVALANCHE_MC_H
#define G_AVALANCHE_MC_H

#include <array>
#include <cstddef>
#include <string>
#include <utility>
#include <vector>

#include "Garfield/ParticleTypes.hh"

namespace Garfield {

class Sensor;
class ViewDrift;
class Medium;
/// Calculate drift lines and avalanches based on macroscopic transport
/// coefficients, using Monte Carlo integration.
class AvalancheMC {
 public:
  /// Default constructor
  AvalancheMC() = default;
  /// Constructor
  explicit AvalancheMC(Sensor* sensor);
  explicit AvalancheMC(std::nullptr_t) = delete;
  /// Destructor
  ~AvalancheMC() = default;

  /// Set the sensor.
  void SetSensor(Sensor* s);

  /// Simulate the drift line of an electron from a given starting point.
  bool DriftElectron(const double x, const double y, const double z,
                     const double t, const std::size_t w = 1);
  /// Simulate the drift line of a hole from a given starting point.
  bool DriftHole(const double x, const double y, const double z, const double t,
                 const std::size_t w = 1);
  /// Simulate the drift line of an ion from a given starting point.
  bool DriftIon(const double x, const double y, const double z, const double t,
                const std::size_t w = 1);
  /// Simulate the drift line of a negative ion from a given starting point.
  bool DriftNegativeIon(const double x, const double y, const double z,
                        const double t, const std::size_t w = 1);
  /** Simulate an avalanche initiated by an electron at a given starting point.
   * \param x,y,z,t coordinates and time of the initial electron
   * \param hole simulate the hole component of the avalanche or not
   * \param w multiplicity of the initial electron
   */
  bool AvalancheElectron(const double x, const double y, const double z,
                         const double t, const bool hole = false,
                         const std::size_t w = 1);
  /// Simulate an avalanche initiated by a hole at a given starting point.
  bool AvalancheHole(const double x, const double y, const double z,
                     const double t, const bool electron = false,
                     const std::size_t w = 1);
  /// Simulate an avalanche initiated by an electron-hole pair.
  bool AvalancheElectronHole(const double x, const double y, const double z,
                             const double t, const std::size_t w = 1);

  /// Add an electron to the list of particles to be transported.
  void AddElectron(const double x, const double y, const double z,
                   const double t, const std::size_t w = 1);
  /// Add a hole to the list of particles to be transported.
  void AddHole(const double x, const double y, const double z, const double t,
               const std::size_t w = 1);
  /// Add an ion to the list of particles to be transported.
  void AddIon(const double x, const double y, const double z, const double t,
              const std::size_t w = 1);
  /// Add an negative ion to the list of particles to be transported.
  void AddNegativeIon(const double x, const double y, const double z,
                      const double t, const std::size_t w = 1);
  /// Resume the simulation from the current set of charge carriers.
  bool ResumeAvalanche(const bool electron = true, const bool hole = true);

  struct Point {
    double x{0.};
    double y{0.};
    double z{0.};
    double t{0.};
  };

  struct EndPoint {
    int status{0};            ///< Status flag.
    std::vector<Point> path;  ///< Drift line.
    std::size_t weight{0};    ///< Multiplicity.
  };

  struct Seed {
    Point pt;          ///< Starting point.
    Particle type;     ///< Particle type.
    std::size_t w{1};  ///< Multiplicity.
  };

  const std::vector<EndPoint>& GetElectrons() const { return m_electrons; }
  const std::vector<EndPoint>& GetHoles() const { return m_holes; }
  const std::vector<EndPoint>& GetIons() const { return m_ions; }
  const std::vector<EndPoint>& GetNegativeIons() const {
    return m_negativeIons;
  }

  /** Return the number of electron trajectories in the last
   * simulated avalanche (including captured electrons). */
  std::size_t GetNumberOfElectronEndpoints() const {
    return m_electrons.size();
  }
  /// Return the number of ion trajectories.
  std::size_t GetNumberOfIonEndpoints() const { return m_ions.size(); }

  /** Return the coordinates and time of start and end point of a given
   * electron drift line.
   * \param i index of the drift line
   * \param x0,y0,z0,t0 coordinates and time of the starting point
   * \param x1,y1,z1,t1 coordinates and time of the end point
   * \param status status code (see GarfieldConstants.hh)
   */
  void GetElectronEndpoint(const std::size_t i, double& x0, double& y0,
                           double& z0, double& t0, double& x1, double& y1,
                           double& z1, double& t1, int& status) const;
  void GetIonEndpoint(const std::size_t i, double& x0, double& y0, double& z0,
                      double& t0, double& x1, double& y1, double& z1,
                      double& t1, int& status) const;
  void GetNegativeIonEndpoint(const std::size_t i, double& x0, double& y0,
                              double& z0, double& t0, double& x1, double& y1,
                              double& z1, double& t1, int& status) const;

  /// Switch on drift line plotting.
  void EnablePlotting(ViewDrift* view);
  /// Switch off drift line plotting.
  void DisablePlotting() { m_viewer = nullptr; }

  /// Switch on storage of drift lines (default: off).
  void EnableDriftLines(const bool on = true) { m_storeDriftLines = on; }

  /// Switch calculation of induced currents on or off (default: enabled).
  void EnableSignalCalculation(const bool on = true) { m_doSignal = on; }
  /// Set the number of points to be used when averaging the
  /// signal vector over a time bin in the Sensor class.
  /// The averaging is done with a \f$2\times navg + 1\f$ point
  /// Newton-Raphson integration. Default: 1.
  void SetSignalAveragingOrder(const std::size_t navg) { m_navg = navg; }
  /// Use the weighting potential (as opposed to the weighting field)
  /// for calculating the induced signal.
  void UseWeightingPotential(const bool on = true) {
    m_useWeightingPotential = on;
  }

  /// Switch on calculation of induced charge (default: disabled).
  void EnableInducedChargeCalculation(const bool on = true) {
    m_doInducedCharge = on;
  }

  /** Switch on Runge-Kutta-Fehlberg stepping (as opposed to simple
   * straight-line steps. */
  void EnableRKFSteps(const bool on = true) { m_doRKF = on; }

  /** Switch on equilibration of multiplication and attachment
   * over the drift line (default: enabled). */
  void EnableProjectedPathIntegration(const bool on = true) {
    m_doEquilibration = on;
  }

  /// Switch diffusion on/off (default: enabled).
  void EnableDiffusion(const bool on = true) { m_useDiffusion = on; }
  /// Switch attachment on/off (default: enabled).
  void EnableAttachment(const bool on = true) { m_useAttachment = on; }
  /// Switch recombination on/off (default: disabled).
  void EnableRecombination(const bool on = true, double alpha = 0.) {
    m_useRecombination = on;
    m_alphaRecombination = alpha;
  }
  /// Switch multiplication on/off (default: enabled).
  void EnableMultiplication(const bool on = true) { m_useMultiplication = on; }

  /// Retrieve the Townsend coefficient from the component.
  void EnableTownsendMap(const bool on = true) { m_useTownsendMap = on; }
  /// Retrieve the attachment coefficient from the component.
  void EnableAttachmentMap(const bool on = true) { m_useAttachmentMap = on; }
  /// Retrieve the (low-field) mobility from the component.
  void EnableMobilityMap(const bool on = true) { m_useMobilityMap = on; }
  /// Retrieve the drift velocity from the component.
  void EnableVelocityMap(const bool on = true) { m_useVelocityMap = on; }
  /// Retrieve the densities from the component.
  void EnableDensityMap(const bool on = true) { m_useDensityMap = on; }

  /** Set a maximum avalanche size (ignore further multiplication
      once this size has been reached). */
  void EnableAvalancheSizeLimit(const std::size_t size) { m_sizeCut = size; }
  /// Do not limit the maximum avalanche size.
  void DisableAvalancheSizeLimit() { m_sizeCut = 0; }
  /// Return the currently set avalanche size limit.
  int GetAvalancheSizeLimit() const { return m_sizeCut; }

  /// Use fixed-time steps (default 20 ps).
  void SetTimeSteps(const double d = 0.02);
  /// Use fixed distance steps (default 10 um).
  void SetDistanceSteps(const double d = 0.001);
  /** Use exponentially distributed time steps with mean equal
   * to the specified multiple of the collision time (default model).*/
  void SetCollisionSteps(const std::size_t n = 100);
  /// Retrieve the step distance from a user-supplied function.
  void SetStepDistanceFunction(double (*f)(double x, double y, double z));

  /// Define a time interval (only carriers inside the interval are drifted).
  void SetTimeWindow(const double t0, const double t1);
  /// Do not limit the time interval within which carriers are drifted.
  void UnsetTimeWindow() { m_hasTimeWindow = false; }

  /// Set multiplication factor for the signal induced by electrons.
  void SetElectronSignalScalingFactor(const double scale) { m_scaleE = scale; }
  /// Set multiplication factor for the signal induced by holes.
  void SetHoleSignalScalingFactor(const double scale) { m_scaleH = scale; }
  /// Set multiplication factor for the signal induced by ions.
  void SetIonSignalScalingFactor(const double scale) { m_scaleI = scale; }

  /// Return the number of electrons and ions/holes in the avalanche.
  void GetAvalancheSize(std::size_t& ne, std::size_t& ni) const;
  /// Return the number of electrons and ions/holes in the avalanche.
  std::pair<std::size_t, std::size_t> GetAvalancheSize() const;
  /// Switch debugging messages on/off (default: off).
  void EnableDebugging(const bool on = true) { m_debug = on; }

 private:
  std::string m_className{"AvalancheMC"};

  Sensor* m_sensor{nullptr};

  enum class StepModel {
    FixedTime,
    FixedDistance,
    CollisionTime,
    UserDistance
  };
  /// Step size model.
  StepModel m_stepModel{StepModel::CollisionTime};

  /// Fixed time step
  double m_tMc{0.02};
  /// Fixed distance step
  double m_dMc{0.001};
  /// Sample step size according to collision time
  std::size_t m_nMc{100};
  /// User function returning the step size
  double (*m_fStep)(double x, double y, double z) = nullptr;

  /// Flag whether a time window should be used.
  bool m_hasTimeWindow{false};
  /// Lower limit of the time window.
  double m_tMin{0.};
  /// Upper limit of the time window.
  double m_tMax{0.};

  /// Max. avalanche size.
  std::size_t m_sizeCut{0};

  /// Number of electrons produced
  std::size_t m_nElectrons{0};
  /// Number of holes produced
  std::size_t m_nHoles{0};
  /// Number of ions produced
  std::size_t m_nIons{0};
  /// Number of negative ions produced
  std::size_t m_nNegativeIons{0};

  /// Start/end points of all electrons in the avalanche
  /// (including captured ones).
  std::vector<EndPoint> m_electrons;
  /// Start/end points of all holes in the avalanche
  /// (including captured ones).
  std::vector<EndPoint> m_holes;
  /// Start/end points of all positive ions in the avalanche.
  std::vector<EndPoint> m_ions;
  /// Start/end points of all negative ions in the avalanche.
  std::vector<EndPoint> m_negativeIons;

  ViewDrift* m_viewer{nullptr};

  bool m_storeDriftLines{false};
  bool m_doSignal{true};
  std::size_t m_navg{1};
  bool m_useWeightingPotential{true};
  bool m_doInducedCharge{false};
  bool m_doEquilibration{true};
  bool m_doRKF{false};
  bool m_useDiffusion{true};
  bool m_useAttachment{true};
  bool m_useRecombination{true};
  bool m_useMultiplication{true};
  /// Scaling factor for electron signals.
  double m_scaleE{1.};
  /// Scaling factor for hole signals.
  double m_scaleH{1.};
  /// Scaling factor for ion signals.
  double m_scaleI{1.};

  /// Take Townsend coefficients from the component.
  bool m_useTownsendMap{false};
  /// Take attachment coefficients from the component.
  bool m_useAttachmentMap{false};
  /// Take mobility coefficients from the component.
  bool m_useMobilityMap{false};
  /// Take the drift velocities from the component.
  bool m_useVelocityMap{false};
  /// Take the densities from the component.
  bool m_useDensityMap{false};

  /// Recombination coefficient in cm3/ns.
  double m_alphaRecombination{0.};

  bool m_debug{false};

  /// Compute a single drift line.
  int DriftLine(const Seed& seed, std::vector<Point>& path,
                std::vector<Seed>& secondaries, const bool aval,
                const bool signal) const;
  /// Compute an avalanche.
  bool TransportParticles(std::vector<Seed>& stack, const bool withElectrons,
                          const bool withHoles, const bool aval);

  /// Compute electric and magnetic field at a given position.
  int GetField(const std::array<double, 3>& x, std::array<double, 3>& e,
               std::array<double, 3>& b, Medium*& medium) const;
  /// Retrieve the low-field mobility.
  double GetMobility(const Particle particle, Medium* medium,
                     const std::array<double, 3>& x) const;
  /// Compute the drift velocity.
  bool GetVelocity(const Particle particle, Medium* medium,
                   const std::array<double, 3>& x,
                   const std::array<double, 3>& e,
                   const std::array<double, 3>& b,
                   std::array<double, 3>& v) const;
  /// Compute the diffusion coefficients.
  bool GetDiffusion(const Particle particle, Medium* medium,
                    const std::array<double, 3>& e,
                    const std::array<double, 3>& b, double& dl,
                    double& dt) const;
  /// Compute the attachment coefficient.
  double GetAttachment(const Particle particle, Medium* medium,
                       const std::array<double, 3>& x,
                       const std::array<double, 3>& e,
                       const std::array<double, 3>& b) const;
  /// Compute the ion density.
  double GetIonDensity(const std::array<double, 3>& x) const;
  /// Compute the negative ion density.
  double GetNegativeIonDensity(const std::array<double, 3>& x) const;
  /// Compute the Townsend coefficient.
  double GetTownsend(const Particle particle, Medium* medium,
                     const std::array<double, 3>& x,
                     const std::array<double, 3>& e,
                     const std::array<double, 3>& b) const;
  /// Compute end point and effective velocity for a step.
  void StepRKF(const Particle particle, const std::array<double, 3>& x0,
               const std::array<double, 3>& v0, const double dt,
               std::array<double, 3>& xf, std::array<double, 3>& vf,
               int& status) const;
  /// Add a diffusion step.
  void AddDiffusion(const double step, const double dl, const double dt,
                    std::array<double, 3>& x,
                    const std::array<double, 3>& v) const;
  /// Terminate a drift line close to the boundary.
  void Terminate(const std::array<double, 3>& x0, const double t0,
                 std::array<double, 3>& x, double& t) const;
  /// Compute multiplication and losses along the current drift line.
  bool ComputeGainLoss(const Particle ptype, const size_t w,
                       std::vector<Point>& path, int& status,
                       std::vector<Seed>& secondaries,
                       const bool semiconductor = false) const;
  /// Compute Townsend and attachment coefficients along the current drift line.
  bool ComputeAlphaEta(const Particle ptype, std::vector<Point>& path,
                       std::vector<double>& alphas,
                       std::vector<double>& etas) const;
  bool Equilibrate(std::vector<double>& alphas) const;
  /// Compute the induced signal for the current drift line.
  void ComputeSignal(const double q, const std::vector<Point>& path) const;
  /// Compute the induced charge for the current drift line.
  void ComputeInducedCharge(const double q,
                            const std::vector<Point>& path) const;
  void PrintError(const std::string& fcn, const std::string& par,
                  const Particle particle,
                  const std::array<double, 3>& x) const;
};
}  // namespace Garfield

#endif
