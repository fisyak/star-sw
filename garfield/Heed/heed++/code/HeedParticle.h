#ifndef HEEDPARTICLE_H
#define HEEDPARTICLE_H

#include <vector>

#include "HeedCluster.h"
#include "wcpplib/particle/eparticle.h"

namespace Heed {

/// Charged particle which can be traced through the geometry.
///
/// 2003, I. Smirnov

class HeedParticle : public eparticle {
 public:
  /// Default constructor
  HeedParticle() : eparticle() {}
  /// Constructor.
  /// If fs_loss_only == false only transferred energy
  /// is simulated: no deposition of clusters,
  /// no generation of virtual photons.
  HeedParticle(manip_absvol* primvol, const point& pt, const vec& vel,
               double time, particle_def* fpardef, fieldmap* fm,
               const bool fcoulomb_scattering = false,
               const bool floss_only = false,
               const bool fprint_listing = false);
  /// Destructor
  virtual ~HeedParticle() {}

 protected:
  void physics(std::vector<gparticle*>& secondaries) override;
  void physics_mrange(double& fmrange) override;

 private:
  bool m_coulomb_scattering = false;
  bool m_loss_only = false;
  bool m_store_clusters = false;

  long m_particle_number = 0;

  double m_edep = 0.;

  std::vector<HeedCluster> m_clusterBank;
};
}  // namespace Heed

#endif
