#include "wcpplib/particle/eparticle.h"

// 1998 - 2004,   I. Smirnov

namespace Heed {

eparticle::eparticle(manip_absvol* primvol, const point& pt, const vec& vel,
                     double ftime, particle_def* fpardef, fieldmap* fm)
    : mparticle(primvol, pt, vel, ftime, fpardef->mass),
      m_pardef(fpardef),
      m_fm(fm) {}

int eparticle::force(const point& pt, vec& f, vec& f_perp, double& mrange) {
  vec efield(0., 0., 0.);
  vec hfield(0., 0., 0.);
  if (!m_fm) {
    std::cerr << "Field map not defined.\n";
    return 1;
  }
  m_fm->evaluate(pt, efield, hfield, mrange);
  f = m_pardef->charge * efield;
  f_perp = m_pardef->charge * hfield;
  return 1;
}

}  // namespace Heed
