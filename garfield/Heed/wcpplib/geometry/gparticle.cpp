#include "wcpplib/geometry/gparticle.h"

#include <atomic>
#include <limits>
/*
Copyright (c) 2000 Igor B. Smirnov

The file can be used, copied, modified, and distributed
according to the terms of GNU Lesser General Public License version 2.1
as published by the Free Software Foundation,
and provided that the above copyright notice, this permission notice,
and notices about any modifications of the original text
appear in all copies and in supporting documentation.
The file is provided "as is" without express or implied warranty.
*/

namespace Heed {

std::atomic<long> gparticle::s_counter{0L};

gparticle::gparticle(manip_absvol* primvol, const point& pt, const vec& vel,
                     double ftime)
    : m_prevpos(), m_nextpos() {
  primvol->m_find_embed_vol(pt, vel, &m_origin.tid);
  m_origin.pt = pt;
  if (vel == dv0) {
    m_origin.dir = dv0;
    m_origin.speed = 0.0;
  } else {
    m_origin.dir = unit_vec(vel);
    m_origin.speed = vel.length();
  }
  m_origin.ptloc = m_origin.pt;
  m_origin.tid.up_absref(&m_origin.ptloc);
  m_origin.dirloc = m_origin.dir;
  m_origin.tid.up_absref(&m_origin.dirloc);
  m_origin.time = ftime;
  m_origin.sb = 0;
  m_origin.s_ent = 1;
  if (m_origin.tid.eid.empty()) return;
  m_alive = true;
  m_currpos = m_origin;
  m_nextpos = m_currpos;
  m_nextpos.s_ent = 0;
}

void gparticle::step(std::vector<gparticle*>& secondaries) {
  // Make step to next point and calculate new step to border.
  m_prevpos = m_currpos;
  m_currpos = m_nextpos;
  m_total_range_from_origin += m_currpos.prange;
  m_nstep++;
  if (m_currpos.prange == 0) {
    m_nzero_step++;
    check_econd12a(m_nzero_step, >, m_max_qzero_step,
                   "too many zero steps, possible infinite loop\n", std::cerr);
  } else {
    m_nzero_step = 0;
  }
  physics_after_new_speed(secondaries);
  if (m_alive) {
    if (m_prevpos.tid != m_currpos.tid) change_vol();
    m_nextpos = calc_step_to_bord();
  }
}

void gparticle::curvature(bool& curved, vec& frelcen, double& fmrange,
                          double /*prec*/) {
  curved = false;
  frelcen.x = 0.;
  frelcen.y = 0.;
  frelcen.z = 0.;
  fmrange = std::numeric_limits<double>::max();
  /* The following is for debug
  vec field(0,1,0);
  double rad = 10;
  if (length(m_currpos.dir) > 0 && check_par(m_currpos.dir, field) == 0) {
    curved = true;
    double coef = sin2vec(m_currpos.dir, field);
    rad = rad / coef;
    frelcen = unit_vec(m_currpos.dir || field) * rad;
  }
  */
}

void gparticle::physics_mrange(double& /*fmrange*/) {}

stvpoint gparticle::calc_step_to_bord() {
  // Calculate next point as step to border.
  pvecerror("stvpoint gparticle::calc_step_to_bord()");
  if (m_currpos.sb > 0) {
    // Just switch to new volume.
    return switch_new_vol();
  }
  bool curved = false;
  vec relcen;
  double mrange;
  curvature(curved, relcen, mrange, m_max_straight_arange);
  if (mrange <= 0) {
    // Preserve current point for modification by physics.
    stvpoint temp(m_currpos);
    temp.s_ent = 0;
    return temp;
  }
  // Change to local system.
  m_currpos.tid.up_absref(&relcen);
  physics_mrange(mrange);
  trajestep ts(m_max_range, m_rad_for_straight, m_max_straight_arange,
               m_max_circ_arange, m_currpos.ptloc, m_currpos.dirloc, curved,
               relcen, mrange, m_currpos.tid.eid.back()->Gavol()->prec);
  if (ts.mrange <= 0) {
    stvpoint temp(m_currpos);
    temp.s_ent = 0;
    return temp;
  }
  // Here the range is calculated:
  int sb;
  manip_absvol* faeid = nullptr;
  m_currpos.volume()->range(ts, 1, sb, faeid);
  // 1 means inside the volume and makes
  // the program checking embraced volumes
  if (ts.s_prec == 0) {
    // Point is crossed.
    return stvpoint(m_currpos, ts, sb, 0, faeid);
  }
  return stvpoint(m_currpos, ts, ts.mrange, sb, 0, faeid);
}

void gparticle::turn(const double ctheta, const double stheta) {
  vec dir = m_currpos.dir;
  basis temp(dir);
  vec vturn;
  vturn.random_round_vec();
  vturn = vturn * stheta;
  vec new_dir(vturn.x, vturn.y, ctheta);
  new_dir.down(&temp);
  m_currpos.dir = new_dir;
  m_currpos.dirloc = m_currpos.dir;
  m_currpos.tid.up_absref(&m_currpos.dirloc);
}

stvpoint gparticle::switch_new_vol() {
  // Generate next position in new volume.
  manip_absvol_treeid tidl;
  manip_absvol* eidl = nullptr;
  stvpoint nextp = m_currpos;
  point pth = nextp.pt;
  // Search from primary
  // In this case it does not necessarily switch to encountered volume
  // namely nextp.next_eid
  // Borders of two volumes may coincide. Thus it should look for
  // the deepest volume at this point.
  bool ok = false;
  while (!ok) {
    nextp.tid.eid[0]->m_find_embed_vol(pth, nextp.dir, &tidl);
    if (tidl.eid.empty()) {
      m_alive = false;
      break;
    }
    // By default, assume switching to new volume.
    int s_e = 1;
    if (tidl == nextp.tid) {
      // Remains in the same old volume, may be numerical error
      // Will probably repeat attempt to switch at the same steps until ok.
      s_e = 0;
      double curprec = nextp.volume()->prec;
      if (m_currpos.prange <= curprec) {
        // very bad case, to repeat the trial.
        vec additional_dist = nextp.dir * curprec;
        pth = pth + additional_dist;
        tidl = manip_absvol_treeid();
        continue;
      }
    }
    return stvpoint(pth, nextp.dir, nextp.speed, tidl, 0.0, nextp.time, 0, s_e,
                    eidl);
  }
  return stvpoint();
}

}  // namespace Heed
