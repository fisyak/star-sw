#ifndef G_TRACK_ELECTRON
#define G_TRACK_ELECTRON

#include <string>
#include <vector>

#include "Garfield/Track.hh"

namespace Garfield {
class Medium;

/// [WIP] Ionization calculation based on MIP program (S. Biagi).

class TrackElectron : public Track {
 public:
  struct Cluster {
    double x{0.};
    double y{0.};
    double z{0.};
    double t{0.};
    double esec{0.};
  };

  /// Constructor
  TrackElectron();
  /// Destructor
  virtual ~TrackElectron() = default;

  void SetParticle(const std::string& particle) override;

  bool NewTrack(const double x0, const double y0, const double z0,
                const double t0, const double dx0, const double dy0,
                const double dz0) override;

  const std::vector<Cluster>& GetClusters() const { return m_clusters; }

  double GetClusterDensity() override;
  double GetStoppingPower() override;

 private:
  struct Parameters {
    // Dipole moment
    double m2{0.};
    // Constant in ionisation cross-section
    double cIon{0.};
    // Density correction term
    double x0{0.};
    double x1{0.};
    double cDens{0.};
    double aDens{0.};
    double mDens{0.};
    // Opal-Beaty-Peterson splitting factor
    double wSplit{0.};
    // Ionisation threshold
    double ethr{0.};
  };

  std::vector<Cluster> m_clusters;

  // Mean free path
  double m_mfp{0.};
  // Stopping power
  double m_dedx{0.};

  static bool Setup(Medium* gas, std::vector<Parameters>& par,
                    std::vector<double>& frac);
  static bool Update(const double density, const double beta2,
                     const std::vector<Parameters>& par,
                     const std::vector<double>& frac, std::vector<double>& prob,
                     double& mfp, double& dedx);
  static double Delta(const double x, const Parameters& par);
  static double Esec(const double e0, const Parameters& par);
};
}  // namespace Garfield

#endif
