#ifndef HEEDPHOTON_H
#define HEEDPHOTON_H

#include <vector>

#include "wcpplib/geometry/gparticle.h"

// #define SFER_PHOTOEL  // make direction of photoelectron absolutely random

namespace Heed {

class fieldmap;
/// Definition of the photon which can be emitted at atomic relaxation cascades
/// and traced through the geometry.
/// 2003, I. Smirnov

class HeedPhoton : public gparticle {
 public:
  /// Default constructor.
  HeedPhoton() = default;
  /// Constructor.
  HeedPhoton(manip_absvol* primvol, const point& pt, const vec& vel,
             double time, long fparent_particle_number, double fenergy,
             fieldmap* fm, const bool fs_print_listing = false);
  /// Destructor
  virtual ~HeedPhoton() {}

  long m_particle_number;
  long m_parent_particle_number;

  /// Photon energy [MeV]
  double m_energy;

  /// Flag whether the photon has been absorbed.
  /// Used in physics_after_new_speed.
  bool m_photon_absorbed = false;
  /// Index of absorbing atom.
  long m_na_absorbing = 0;
  /// Index of absorbing shell
  long m_ns_absorbing = 0;

#ifdef SFER_PHOTOEL
  int s_sfer_photoel;
#endif

  /// Flag that delta-electrons are already generated (or cannot be created).
  bool m_delta_generated = false;

 protected:
  void physics_after_new_speed(std::vector<gparticle*>& secondaries) override;
  void physics(std::vector<gparticle*>& secondaries) override;

 private:
  fieldmap* m_fm = nullptr;
};
}  // namespace Heed

#endif
