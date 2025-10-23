#include "heed++/code/HeedParticle_BGM.h"

#include <iomanip>
#include <iostream>
#include <numeric>

#include "Garfield/Random.hh"
#include "heed++/code/BGMesh.h"
#include "heed++/code/EnTransfCS_BGM.h"
#include "heed++/code/EnergyMesh.h"
#include "heed++/code/HeedCluster.h"
#include "heed++/code/HeedMatterDef.h"
#include "heed++/code/HeedPhoton.h"
#include "wcpplib/clhep_units/WPhysicalConstants.h"
#include "wcpplib/math/kinem.h"
#include "wcpplib/math/tline.h"
#include "wcpplib/matter/MatterDef.h"

// 2003-2008, I. Smirnov

namespace Heed {

using CLHEP::c_light;
using CLHEP::c_squared;
using CLHEP::cm;
using CLHEP::electron_mass_c2;
using CLHEP::MeV;

HeedParticle_BGM::HeedParticle_BGM(manip_absvol* primvol, const point& pt,
                                   const vec& vel, double ftime,
                                   particle_def* fpardef, fieldmap* fm,
                                   const bool floss_only,
                                   const bool fprint_listing)
    : eparticle(primvol, pt, vel, ftime, fpardef, fm),
      m_loss_only(floss_only),
      m_particle_number(s_counter++) {}

void HeedParticle_BGM::physics(std::vector<gparticle*>& secondaries) {
  // Get the step.
  if (m_currpos.prange <= 0.0) return;
  const double stp = m_currpos.prange / cm;
  const vec dir = unit_vec(m_currpos.pt - m_prevpos.pt);
  // This approximation ignores curvature
  const double range = (m_currpos.pt - m_prevpos.pt).length();
  // Get local volume.
  const absvol* av = m_currpos.volume();
  auto etcs = dynamic_cast<const EnTransfCS_BGM*>(av);
  if (!etcs) return;
  HeedMatterDef* hmd = etcs->hmd;
  MatterDef* matter = hmd->matter;
  EnergyMesh* emesh = hmd->energy_mesh;
  const double* aetemp = hmd->energy_mesh->get_ae();
  PointCoorMesh<double, const double*> pcm_e(emesh->get_q() + 1, &(aetemp));
  // Particle mass, energy and momentum.
  const double mp = m_mass * c_squared;
  const double ep = mp + m_curr_ekin;
  const double bg = sqrt(m_curr_gamma_1 * (m_curr_gamma_1 + 2.0));
  // Electron mass.
  const double mt = electron_mass_c2;
  // Particle velocity.
  const double invSpeed = 1. / m_prevpos.speed;
  PointCoorMesh<double, std::vector<double> > pcm(etcs->mesh->q,
                                                  &(etcs->mesh->x));
  long n1, n2;
  double b1, b2;
  int s_ret = pcm.get_interval(bg, n1, b1, n2, b2);
  if (s_ret != 1) {
    std::cerr << "ERROR in void HeedParticle_BGM::physics()\n";
    std::cerr << "beta*gamma is outside range of cross-section table\n";
    std::streamsize old_prec = std::cerr.precision(15);
    std::cerr << "m_curr_gamma_1=" << m_curr_gamma_1 << ", bg=" << bg << '\n';
    std::cerr.precision(old_prec);
    std::cerr << "n1=" << n1 << ", n2=" << n2 << '\n';
    std::cerr << "b1=" << b1 << ", b2=" << b2 << '\n';
    std::cerr << "etcs->mesh=" << etcs->mesh << '\n';
    // std::cerr << "This particle is:\n";
    // print(std::cerr, 2);
    // std::cerr << "This volume is:\n";
    // av->print(std::cerr, 2);
    spexit(std::cerr);
    return;
  }

  const double f2 = (bg - b1) * (b2 - b1);
  const double f1 = 1. - f2;
  const long qa = matter->qatom();
  basis tempbas(m_currpos.dir);
  // Shorthand.
  const auto sampleTransfer =
      t_hisran_step_ar<double, std::vector<double>,
                       PointCoorMesh<double, const double*> >;
  for (long na = 0; na < qa; ++na) {
    long qs = hmd->apacs[na]->get_qshell();
    for (long ns = 0; ns < qs; ++ns) {
      const double y1 = etcs->etcs_bgm[n1].quan[na][ns];
      const double y2 = etcs->etcs_bgm[n2].quan[na][ns];
      const double mean_pois = f1 * y1 + f2 * y2;
      if (mean_pois <= 0.) continue;
      const long qt = Garfield::RndmPoisson(mean_pois * stp);
      if (qt <= 0) continue;
      for (long nt = 0; nt < qt; nt++) {
        // Sample the energy transfer in this collision.
        const double rn = Garfield::RndmUniform();
        const double r1 =
            sampleTransfer(pcm_e, etcs->etcs_bgm[n1].fadda[na][ns], rn);
        const double r2 =
            sampleTransfer(pcm_e, etcs->etcs_bgm[n2].fadda[na][ns], rn);
        const double r = f1 * r1 + f2 * r2;
        // Convert to internal units.
        const double et = r * MeV;
        m_edep += et;
        // Sample the position of the collision.
        const double arange = Garfield::RndmUniform() * range;
        point pt = m_prevpos.pt + dir * arange;
        if (m_loss_only) continue;
        m_clusterBank.push_back(HeedCluster(et, pt, na, ns));
        // Generate a virtual photon.
        double theta_p, theta_t;
        theta_two_part(ep, ep - et, mp, mt, theta_p, theta_t);
        vec vel;
        vel.random_conic_vec(fabs(theta_t));
        vel.down(&tempbas);  // direction is OK
        vel *= c_light;
        const double t = m_prevpos.time + arange * invSpeed;
        HeedPhoton* hp = new HeedPhoton(m_currpos.tid.eid[0], pt, vel, t,
                                        m_particle_number, et, m_fm);
        if (!hp->alive()) {
          delete hp;
          continue;
        }
        hp->m_photon_absorbed = true;
        hp->m_delta_generated = false;
        hp->m_na_absorbing = na;
        hp->m_ns_absorbing = ns;
        secondaries.push_back(hp);
      }
    }
  }
  if (m_edep >= m_curr_ekin) {
    // Accumulated energy loss exceeds the particle's kinetic energy.
    m_alive = false;
  }
}

}  // namespace Heed
