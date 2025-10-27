#ifndef G_MEDIUM_SILICON_H
#define G_MEDIUM_SILICON_H

#include <array>
#include <mutex>
#include <string>
#include <vector>

#include "Garfield/Medium.hh"

namespace Garfield {
/// %Solid crystalline silicon

class MediumSilicon : public Medium {
 public:
  /// Constructor
  MediumSilicon();
  /// Destructor
  virtual ~MediumSilicon() = default;

  bool IsSemiconductor() const override { return true; }

  /// Set doping concentration [cm-3] and type ('i', 'n', 'p').
  void SetDoping(const char type, const double c);
  /// Retrieve doping concentration.
  void GetDoping(char& type, double& c) const;

  /// Trapping cross-sections for electrons and holes.
  void SetTrapCrossSection(const double ecs, const double hcs);
  /// Trap density [cm-3], by default set to zero.
  void SetTrapDensity(const double n);
  /// Set time constant for trapping of electrons and holes [ns].
  void SetTrappingTime(const double etau, const double htau);

  /// Specify the low field values of the electron and hole mobilities.
  void SetLowFieldMobility(const double mue, const double muh);
  /// Set the parameterisation to be used for calculating the
  /// lattice mobility model. The currently implemented models are
  /// - Sentaurus
  /// - Reggiani
  /// - Minimos
  /// The default is Sentaurus.
  void SetLatticeMobilityModel(const std::string& model);
  /// Calculate the lattice mobility using the Minimos model.
  void SetLatticeMobilityModelMinimos();
  /// Calculate the lattice mobility using the Sentaurus model (default).
  void SetLatticeMobilityModelSentaurus();
  /// Calculate the lattice mobility using the Reggiani model.
  void SetLatticeMobilityModelReggiani();

  /// Use the Minimos model for the doping-dependence of the mobility.
  void SetDopingMobilityModelMinimos();
  /// Use the Masetti model for the doping-dependence of the mobility (default).
  void SetDopingMobilityModelMasetti();

  /// Specify the saturation velocities of electrons and holes.
  void SetSaturationVelocity(const double vsate, const double vsath);
  /// Calculate the saturation velocities using the Minimos model.
  void SetSaturationVelocityModelMinimos();
  /// Calculate the saturation velocities using the Canali model (default).
  void SetSaturationVelocityModelCanali();
  /// Calculate the saturation velocities using the Reggiani model.
  void SetSaturationVelocityModelReggiani();

  /// Set the parameterisation to be used for the drift velocity as
  /// function of the electric field.
  /// The currently implemented models are
  ///  - Canali
  ///  - Reggiani
  ///  - Minimos
  ///  - Constant (velocity increases linearly with the electric field)
  /// The default is Canali.
  void SetHighFieldMobilityModel(const std::string& model);
  /// Parameterize the high-field mobility using the Minimos model.
  void SetHighFieldMobilityModelMinimos();
  /// Parameterize the high-field mobility using the Canali model (default).
  void SetHighFieldMobilityModelCanali();
  /// Parameterize the high-field mobility using the Reggiani model.
  void SetHighFieldMobilityModelReggiani();
  /// Make the velocity proportional to the electric field (no saturation).
  void SetHighFieldMobilityModelConstant();

  /// Set the parameterisation to be used for calculating the
  /// impact ionisation coefficient. The currently implemented models are
  ///  - van Overstraeten - de Man
  ///  - Okuto - Crowell
  ///  - Massey
  ///  - Grant
  /// The default is van Overstraeten - de Man.
  void SetImpactIonisationModel(const std::string& model);
  /// Calculate &alpha; using the van Overstraeten-de Man model (default).
  void SetImpactIonisationModelVanOverstraetenDeMan();
  /// Calculate &alpha; using the Grant model.
  void SetImpactIonisationModelGrant();
  /// Calculate &alpha; using the Massey model.
  void SetImpactIonisationModelMassey();
  /// Calculate &alpha; using the Okuto-Crowell model.
  void SetImpactIonisationModelOkutoCrowell();

  /// Apply a scaling factor to the diffusion coefficients.
  void SetDiffusionScaling(const double d) { m_diffScale = d; }

  // Microscopic transport properties
  bool SetMaxElectronEnergy(const double e);
  double GetMaxElectronEnergy() const { return m_cb[2].eFinal; }

  bool Initialise();

  // When enabled, the scattering rates table is written to file
  // when loaded into memory.
  void EnableScatteringRateOutput(const bool on = true) { m_cfOutput = on; }
  void EnableNonParabolicity(const bool on = true) { m_nonParabolic = on; }
  void EnableFullBandDensityOfStates(const bool on = true) {
    m_fullBandDos = on;
  }
  void EnableAnisotropy(const bool on = true) { m_anisotropic = on; }

  // Electron transport parameters
  bool ElectronVelocity(const double ex, const double ey, const double ez,
                        const double bx, const double by, const double bz,
                        double& vx, double& vy, double& vz) override;
  bool ElectronTownsend(const double ex, const double ey, const double ez,
                        const double bx, const double by, const double bz,
                        double& alpha) override;
  bool ElectronAttachment(const double ex, const double ey, const double ez,
                          const double bx, const double by, const double bz,
                          double& eta) override;
  double ElectronMobility() override { return m_eMu; }
  bool ElectronDiffusion(const double ex, const double ey, const double ez, 
                         const double bx, const double by, const double bz, 
                         double& dl, double& dt) override;

  // Hole transport parameters
  bool HoleVelocity(const double ex, const double ey, const double ez,
                    const double bx, const double by, const double bz,
                    double& vx, double& vy, double& vz) override;
  bool HoleTownsend(const double ex, const double ey, const double ez,
                    const double bx, const double by, const double bz,
                    double& alpha) override;
  bool HoleAttachment(const double ex, const double ey, const double ez,
                      const double bx, const double by, const double bz,
                      double& eta) override;
  double HoleMobility() override { return m_hMu; }
  bool HoleDiffusion(const double ex, const double ey, const double ez, 
                     const double bx, const double by, const double bz, 
                     double& dl, double& dt) override;
  // Get the electron energy (and its gradient)
  // for a given (crystal) momentum
  double GetElectronEnergy(const double px, const double py, const double pz,
                           double& vx, double& vy, double& vz,
                           const int band = 0) override;
  // Get the electron (crystal) momentum for a given kinetic energy
  void GetElectronMomentum(const double e, double& px, double& py, double& pz,
                           int& band) override;

  // Get the null-collision rate [ns-1]
  double GetElectronNullCollisionRate(const int band) override;
  // Get the (real) collision rate [ns-1] at a given electron energy
  double GetElectronCollisionRate(const double e, const int band) override;
  // Sample the collision type
  bool ElectronCollision(const double e, int& type, int& level, double& e1,
                         double& dx, double& dy, double& dz,
                         std::vector<Secondary>& secondaries,
                         int& band) override;

  // Reset the collision counters
  void ResetCollisionCounters();
  // Get the total number of electron collisions
  std::size_t GetNumberOfElectronCollisions() const;
  // Get number of scattering rate terms
  std::size_t GetNumberOfLevels() const;
  // Get number of collisions for a specific level
  std::size_t GetNumberOfElectronCollisions(const std::size_t level) const;

  std::size_t GetNumberOfElectronBands() const;
  int GetElectronBandPopulation(const int band);

  bool GetOpticalDataRange(double& emin, double& emax,
                           const std::size_t i = 0) override;
  bool GetDielectricFunction(const double e, double& eps1, double& eps2,
                             const std::size_t i = 0) override;

  void ComputeSecondaries(const double e0, double& ee, double& eh);

 private:
  enum class LatticeMobility { Sentaurus = 0, Minimos, Reggiani };
  enum class DopingMobility { Minimos = 0, Masetti };
  enum class SaturationVelocity { Minimos = 0, Canali, Reggiani };
  enum class HighFieldMobility { Minimos = 0, Canali, Reggiani, Constant };
  enum class ImpactIonisation { VanOverstraeten = 0, Grant, Massey, Okuto };

  std::mutex m_mutex;

  // Diffusion scaling factor
  double m_diffScale{1.};

  double m_bandGap{1.12};
  // Doping
  char m_dopingType{'i'};
  // Doping concentration
  double m_cDop{0.};

  // Lattice mobility
  double m_eMuLat{1.35e-6};
  double m_hMuLat{0.45e-6};
  // Low-field mobility
  double m_eMu{1.35e-6};
  double m_hMu{0.45e-6};
  // High-field mobility parameters
  double m_eBetaCanali{1.109};
  double m_hBetaCanali{1.213};
  double m_eBetaCanaliInv{1. / 1.109};
  double m_hBetaCanaliInv{1. / 1.213};
  // Saturation velocity
  double m_eVs{1.02e-2};
  double m_hVs{0.72e-2};
  // Ratio between low-field mobility and saturation velocity
  double m_eRs{1.35e-6 / 1.02e-2};
  double m_hRs{0.45e-6 / 0.72e-2};
  // Hall factor
  double m_eHallFactor{1.15};
  double m_hHallFactor{0.7};

  // Trapping parameters
  double m_eTrapCs{1.e-15};
  double m_hTrapCs{1.e-15};
  double m_eTrapDensity{0.};
  double m_hTrapDensity{0.};
  double m_eTrapTime{0.};
  double m_hTrapTime{0.};
  double m_eTrapRate{0.};
  double m_hTrapRate{0.};
  int m_trappingModel{0};

  // Impact ionisation parameters
  double m_eImpactA0{3.318e5};
  double m_eImpactA1{0.703e6};
  double m_eImpactA2{0.};
  double m_eImpactB0{1.135e6};
  double m_eImpactB1{1.231e6};
  double m_eImpactB2{0.};
  double m_hImpactA0{1.582e6};
  double m_hImpactA1{0.671e6};
  double m_hImpactB0{2.036e6};
  double m_hImpactB1{1.693e6};

  // Models
  bool m_hasUserMobility{false};
  bool m_hasUserSaturationVelocity{false};
  LatticeMobility m_latticeMobilityModel{LatticeMobility::Sentaurus};
  DopingMobility m_dopingMobilityModel{DopingMobility::Masetti};
  SaturationVelocity m_saturationVelocityModel{SaturationVelocity::Canali};
  HighFieldMobility m_highFieldMobilityModel{HighFieldMobility::Canali};
  ImpactIonisation m_impactIonisationModel{ImpactIonisation::VanOverstraeten};

  // Options
  bool m_cfOutput{false};
  bool m_nonParabolic{true};
  bool m_fullBandDos{false};
  bool m_anisotropic{true};

  struct Band {
    int nEnergySteps{2000};
    double eStep{0.};
    double invStep{0.};
    // Energy range of scattering rates.
    double eFinal{0.};
    // Energy offset [eV].
    double eMin{0.};
    // Index corresponding to the energy offset.
    int iMin{0};
    // Density of states.
    std::vector<double> dos;
    // Multiplicity (number of valleys).
    int nValleys{1};
    // Longitudinal mass.
    double mL{1.};
    // Transverse mass.
    double mT{1.};
    // Conduction effective mass.
    double mC{1.};
    // Non-parabolicity parameter [1/eV].
    double alpha{0.};
    // Null-collision rate.
    double cfNull{0.};
    // Total scattering rate.
    std::vector<double> cfTot;
    // Scattering rates.
    std::vector<std::vector<double> > cf;
    std::vector<double> energyLoss;
    // Cross-section type.
    std::vector<int> scatType;
    // Number of scattering terms.
    int nLevels{0};
  };

  // Conduction bands.
  std::array<Band, 3> m_cb;
  std::vector<std::size_t> m_cbIndex;
  // Valence band.
  Band m_vb;

  // Collision counters
  std::size_t m_nCollElectronAcoustic{0};
  std::size_t m_nCollElectronOptical{0};
  std::size_t m_nCollElectronIntervalley{0};
  std::size_t m_nCollElectronImpurity{0};
  std::size_t m_nCollElectronIonisation{0};
  std::vector<std::size_t> m_nCollElectronDetailed;
  std::vector<std::size_t> m_nCollElectronBand;

  // Density of states tables
  double m_eStepDos{0.};
  double m_invStepDos{0.};
  std::vector<double> m_fbDosV;
  std::vector<double> m_fbDosC;
  double m_fbDosMaxV{0.};
  double m_fbDosMaxC{0.};

  // Optical data
  enum class optical_data : std::size_t {
    Egamma = 0,
    Eps1,
    Eps2,
  };
  static constexpr std::size_t m_optical_data_size{1127};
  static const std::array<std::array<double, 4>, m_optical_data_size>
      m_optical_data;

  bool Update();
  void UpdateLatticeMobility();

  void UpdateDopingMobilityMinimos();
  void UpdateDopingMobilityMasetti();

  void UpdateSaturationVelocity();

  void UpdateHighFieldMobilityCanali();

  void UpdateImpactIonisation();

  double ElectronMobility(const double e) const;
  double ElectronAlpha(const double e) const;

  double HoleMobility(const double e) const;
  double HoleAlpha(const double e) const;

  bool ElectronScatteringRates();
  bool HoleScatteringRates();
  bool AcousticScatteringRates(const double rho, const double kbt,
                               const double dp, Band& band);
  bool OpticalScatteringRates(const double rho, const double kbt,
                              const double dtk, const double eph, Band& band);
  bool IntervalleyScatteringRates(const double rho, const double kbt,
                                  const double dtk, const double eph,
                                  Band& bndI, Band& bndF, const double zF,
                                  const int collType);
  bool IonisationRates(const std::vector<double>& p,
                       const std::vector<double>& eth,
                       const std::vector<double>& b, Band& band);
  bool ImpurityScatteringRates(const double kbt, Band& band);

  void InitialiseDOS();
  void ComputeDOS();
};
}  // namespace Garfield

#endif
