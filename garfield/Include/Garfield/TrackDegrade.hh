#ifndef G_TRACK_DEGRADE_H
#define G_TRACK_DEGRADE_H

#include <array>
#include <string>
#include <utility>
#include <vector>

#include "Garfield/Track.hh"

namespace Garfield {
class Sensor;
class Medium;

/// Interface to Degrade.

class TrackDegrade : public Track {
 public:
  struct Electron {
    double x{0.};
    double y{0.};
    double z{0.};
    double t{0.};
    double energy{0.};
    double dx{0.};
    double dy{0.};
    double dz{0.};
  };

  struct Excitation {
    double x{0.};
    double y{0.};
    double z{0.};
    double t{0.};
    double energy{0.};
  };

  struct Cluster {
    double x{0.};
    double y{0.};
    double z{0.};
    double t{0.};
    std::vector<Electron> deltaElectrons;
    std::vector<Electron> electrons;
    std::vector<Excitation> excitations;
  };

  /// Default constructor
  TrackDegrade();
  /// Constructor
  explicit TrackDegrade(Sensor* sensor);
  explicit TrackDegrade(std::nullptr_t) = delete;
  /// Destructor
  virtual ~TrackDegrade() = default;

  bool NewTrack(const double x0, const double y0, const double z0,
                const double t0, const double dx0, const double dy0,
                const double dz0) override;
  const std::vector<Cluster>& GetClusters() const { return m_clusters; }
  double GetClusterDensity() override;
  double GetStoppingPower() override;

  bool Initialise(Medium* medium, const bool verbose = false);

  /// Set the energy down to which electrons are tracked (default: 2 eV).
  void SetThresholdEnergy(const double eth);
  /// Store excitations in the cluster or not (off by default).
  void StoreExcitations(const bool on = true, const double thr = 4.);
  /// Enable or disable bremsstrahlung.
  void EnableBremsstrahlung(const bool on = true) { m_bremsStrahlung = on; }
  /// Enable or disable detailed simulation of the deexcitation cascade.
  void EnableFullCascade(const bool on = true) { m_fullCascade = on; }

  void SetParticle(const std::string& particle) override;

 protected:
  std::vector<Cluster> m_clusters;

  bool m_penning{true};
  bool m_bremsStrahlung{true};
  bool m_fullCascade{true};
  bool m_storeExcitations{false};
  // Energy threshold for storing excitations.
  double m_ethrExc{4.};
  // Energy threshold for tracking electrons.
  double m_ethr{2.};

  double m_pressure{-1.};
  double m_temperature{-1.};
  std::string m_mediumName;
  std::size_t m_nGas{0};

  double m_dedx{-1.};
  double m_clusterDensity{-1.};

  std::array<double, 6> m_rPenning;
  std::array<double, 6> m_dPenning;

  std::pair<std::vector<Electron>, std::vector<Excitation> >
  TransportDeltaElectron(const double x0, const double y0, const double z0,
                         const double t0, const double e0, const double dx,
                         const double dy, const double dz);

  void SetupPenning(Medium* medium, std::array<double, 6>& rP,
                    std::array<double, 6>& dP);
  bool IsInside(const double x, const double y, const double z);
};
}  // namespace Garfield

#endif
