#ifndef G_TRACK_TRIM_H
#define G_TRACK_TRIM_H

#include <array>
#include <cstddef>
#include <string>
#include <vector>

#include "Garfield/Track.hh"

namespace Garfield {

class Sensor;
/// Generate tracks based on TRIM output files.
///  - http://www.srim.org

class TrackTrim : public Track {
 public:
  /// Default constructor
  TrackTrim();
  /// Constructor
  explicit TrackTrim(Sensor* sensor);
  explicit TrackTrim(std::nullptr_t) = delete;
  /// Destructor
  virtual ~TrackTrim() = default;

  /// Load data from an EXYZ.txt file.
  bool ReadFile(const std::string& file, const std::size_t nIons = 0,
                const std::size_t nSkip = 0);
  /// Print a summary of the available TRIM data.
  void Print();

  /// Set the projectile charge [-].
  void SetCharge(const double q);
  /// Set the W value [eV].
  void SetWorkFunction(const double w) { m_work = w; }
  /// Get the W value [eV].
  double GetWorkFunction() const { return m_work; }
  /// Set the Fano factor.
  void SetFanoFactor(const double f) {
    m_fano = f;
    m_fset = true;
  }
  /// Use the default Fano factor.
  void UnsetFanoFactor() { m_fset = false; }
  /// Get the Fano factor.
  double GetFanoFactor() const { return m_fano; }

  /// Set a max. distance between subsequent steps.
  void EnableStepSizeLimit(const double dmax) { m_maxStepSize = dmax; }
  /// Do not reduce the steps with respect to the TRIM input file (default).
  void DisableStepSizeLimit() { m_maxStepSize = -1.; }
  /// Set a max. energy loss per cluster.
  void EnableEnergyLossLimit(const double emax) { m_maxLossPerStep = emax; }
  /// Do not limit the energy loss per cluster (default).
  /// Each segment in the TRIM input file corresponds to one cluster.
  void DisableEnergyLossLimit() { m_maxLossPerStep = -1.; }

  void SetParticle(const std::string& part) override;

  struct Cluster {
    double x{0.};
    double y{0.};
    double z{0.};       ///< Location
    double t{0.};       ///< Time
    double energy{0.};  ///< Energy spent to make the cluster
    double ekin{0.};    ///< Ion energy when cluster was created
    int n{0};           ///< Number of electrons in this cluster
  };

  bool NewTrack(const double x0, const double y0, const double z0,
                const double t0, const double dx0, const double dy0,
                const double dz0) override;
  const std::vector<Cluster>& GetClusters() const { return m_clusters; }
  bool GetCluster(double& xc, double& yc, double& zc, double& tc, int& nc,
                  double& ec, double& extra);

 protected:
  /// Work function [eV] of the target.
  double m_work{-1.};
  /// Has the Fano factor been set?
  bool m_fset{false};
  /// Fano factor [-] of the target.
  double m_fano{-1.};

  /// Projectile energy [eV].
  double m_ekin{0.};
  /// List of tracks.
  std::vector<std::vector<std::array<float, 6> > > m_ions;
  /// Index of the current track.
  std::size_t m_ion{0};

  /// Clusters on the current track.
  std::vector<Cluster> m_clusters;
  /// Index of the next cluster to be returned.
  std::size_t m_cluster{0};

  /// Step size limit.
  double m_maxStepSize{-1.};
  /// Energy loss limit per step.
  double m_maxLossPerStep{-1.};

  void AddIon(const std::vector<float>& x, const std::vector<float>& y,
              const std::vector<float>& z, const std::vector<float>& dedx,
              const std::vector<float>& ekin);
};
}  // namespace Garfield

#endif
