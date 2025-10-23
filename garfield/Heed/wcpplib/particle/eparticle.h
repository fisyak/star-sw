#ifndef EPARTICLE_H
#define EPARTICLE_H
#include "wcpplib/geometry/mparticle.h"
#include "wcpplib/particle/fieldmap.h"
#include "wcpplib/particle/particle_def.h"

// 1998 - 2004, I. Smirnov.

namespace Heed {

/// Charged particle. Combination of features of massive geometrical
/// particle and specification of concrete particle as one of types
/// known by science.

class eparticle : public mparticle /*, public particle_type*/ {
 public:
  /// Default constructor
  eparticle() = default;
  /// Constructor using velocity vector.
  eparticle(manip_absvol* primvol, const point& pt, const vec& vel, double time,
            particle_def* fpardef, fieldmap* fm);
  /// Destructor
  virtual ~eparticle() {}

 protected:
  /// Calculate force components.
  int force(const point& pt, vec& f, vec& f_perp, double& mrange) override;
  // mrange - distance at which the force should not change much
  particle_def* m_pardef = nullptr;
  /// Pointer to field map.
  fieldmap* m_fm = nullptr;
};
}  // namespace Heed

#endif
