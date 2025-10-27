#ifndef G_TRACK_PAI
#define G_TRACK_PAI

#include <array>
#include <cstddef>
#include <string>
#include <vector>

#include "Garfield/Track.hh"

namespace Garfield {

/// Energy loss calculation using the Photoabsorption-Ionisation Model.
class Medium;
class TrackPAI : public Track {
 public:
  struct Cluster {
    double x{0.};
    double y{0.};
    double z{0.};
    double t{0.};
    double energy{0.};
  };

  // Constructor
  TrackPAI();
  // Destructor
  virtual ~TrackPAI() = default;

  bool NewTrack(const double x0, const double y0, const double z0,
                const double t0, const double dx0, const double dy0,
                const double dz0) override;

  const std::vector<Cluster>& GetClusters() const { return m_clusters; }

  double GetClusterDensity() override;
  double GetStoppingPower() override;

 private:
  // Particle speed.
  double m_speed{0.};
  // Max. energy transfer in a collision
  double m_emax{0.};

  // Total inelastic mean free path
  double m_imfp{0.};
  // Stopping power
  double m_dedx{0.};

  // Dielectric function
  static constexpr std::size_t m_nSteps{1000};
  std::array<double, m_nSteps> m_eps1;
  std::array<double, m_nSteps> m_eps2;
  std::array<double, m_nSteps> m_epsInt;

  // Tables for interpolation of cumulative distribution functions
  std::array<double, m_nSteps> m_energies;
  std::array<double, m_nSteps> m_cdf;
  std::array<double, m_nSteps> m_rutherford;

  std::vector<Cluster> m_clusters;

  // Medium properties
  std::string m_mediumName;
  double m_mediumDensity{0.};
  double m_electronDensity{0.};

  bool SetupMedium(Medium* medium);
  bool SetupCrossSectionTable();

  double ComputeMaxTransfer() const;

  double ComputeCsTail(const double emin, const double emax);
  double ComputeDeDxTail(const double emin, const double emax);

  std::pair<double, double> SampleEnergyDeposit(const double u) const;
  double SampleAsymptoticCs(double u) const;
  double SampleAsymptoticCsSpinZero(const double emin, double u) const;
  double SampleAsymptoticCsSpinHalf(const double emin, double u) const;
  double SampleAsymptoticCsSpinOne(const double emin, double u) const;
  double SampleAsymptoticCsElectron(const double emin, double u) const;
  double SampleAsymptoticCsPositron(const double emin, double u) const;

  double LossFunction(const double eps1, const double eps2) const {
    const double eps = eps1 * eps1 + eps2 * eps2;
    return eps > 0. ? eps2 / eps : 0.;
  }
};
}  // namespace Garfield

#endif
