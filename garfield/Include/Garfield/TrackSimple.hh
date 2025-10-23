#ifndef G_TRACK_SIMPLE_H
#define G_TRACK_SIMPLE_H

#include <vector>

#include "Garfield/Track.hh"

namespace Garfield {

class Sensor;
/// Generate tracks based on a cluster density given by the user.
class TrackSimple : public Track {
 public:
  struct Cluster {
    double x{0.};
    double y{0.};
    double z{0.};
    double t{0.};
    double energy{0.};
  };

  /// Default constructor
  TrackSimple();
  /// Constructor
  explicit TrackSimple(Sensor* sensor);
  explicit TrackSimple(std::nullptr_t) = delete;
  /// Destructor
  virtual ~TrackSimple() = default;

  /// Constant distance between clusters.
  void SetEqualSpacing() { m_useEqualSpacing = true; }
  /// Exponentially distributed distance between clusters.
  void SetExponentialSpacing() { m_useEqualSpacing = false; }

  /// Set the cluster density (inverse mean free path).
  void SetClusterDensity(const double d);
  double GetClusterDensity() override;
  /// Set the stopping power (dE/dx).
  void SetStoppingPower(const double dedx);
  double GetStoppingPower() override;

  bool NewTrack(const double x0, const double y0, const double z0,
                const double t0, const double dx0, const double dy0,
                const double dz0) override;
  const std::vector<Cluster>& GetClusters() const { return m_clusters; }

 protected:
  // Mean free path (mean spacing between adjacent clusters)
  double m_mfp{0.04};
  // Average energy per cluster
  double m_eloss{2530.};

  bool m_useEqualSpacing{false};

  std::vector<Cluster> m_clusters;
};
}  // namespace Garfield

#endif
