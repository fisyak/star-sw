#include "heed++/code/HeedParticle.h"

#include <iomanip>
#include <numeric>

#include "Garfield/Random.hh"
#include "heed++/code/EnTransfCS.h"
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

HeedParticle::HeedParticle(manip_absvol* primvol, const point& pt,
                           const vec& vel, double ftime, particle_def* fpardef,
                           fieldmap* fm, const bool fcoulomb_scattering,
                           const bool floss_only, const bool fprint_listing)
    : eparticle(primvol, pt, vel, ftime, fpardef, fm),
      m_coulomb_scattering(fcoulomb_scattering),
      m_loss_only(floss_only),
      m_particle_number(s_counter++) {}

void HeedParticle::physics(std::vector<gparticle*>& secondaries) {
  // Get the step.
  if (m_currpos.prange <= 0.0) return;
  const double stp = m_currpos.prange / cm;
  const vec dir = unit_vec(m_currpos.pt - m_prevpos.pt);
  const double range = (m_currpos.pt - m_prevpos.pt).length();
  // Get local volume.
  const absvol* av = m_currpos.volume();
  auto etcs = dynamic_cast<const EnTransfCS*>(av);
  if (!etcs) return;
  HeedMatterDef* hmd = etcs->hmd;
  MatterDef* matter = hmd->matter;
  EnergyMesh* emesh = hmd->energy_mesh;
  const double* aetemp = emesh->get_ae();
  PointCoorMesh<double, const double*> pcm(emesh->get_q() + 1, &(aetemp));
  basis tempbas(m_currpos.dir);
  // Particle mass and energy.
  const double mp = m_mass * c_squared;
  const double ep = mp + m_curr_ekin;
  // Electron mass.
  const double mt = electron_mass_c2;
  // Particle velocity.
  const double invSpeed = 1. / m_prevpos.speed;
  // Shorthand.
  const auto sampleTransfer =
      t_hisran_step_ar<double, std::vector<double>,
                       PointCoorMesh<double, const double*> >;
  const long qa = matter->qatom();
  for (long na = 0; na < qa; ++na) {
    const long qs = hmd->apacs[na]->get_qshell();
    for (long ns = 0; ns < qs; ++ns) {
      if (etcs->quan[na][ns] <= 0.0) continue;
      // Sample the number of collisions for this shell.
      const long qt = Garfield::RndmPoisson(etcs->quan[na][ns] * stp);
      if (qt <= 0) continue;
      for (long nt = 0; nt < qt; ++nt) {
        // Sample the energy transfer in this collision.
        const double r =
            sampleTransfer(pcm, etcs->fadda[na][ns], Garfield::RndmUniform());
        // Convert to internal units.
        const double et = r * MeV;
        m_edep += et;
        // Sample the position of the collision.
        const double arange = Garfield::RndmUniform() * range;
        point pt = m_prevpos.pt + dir * arange;
        if (m_loss_only) continue;
        if (m_store_clusters) {
          m_clusterBank.emplace_back(HeedCluster(et, pt, na, ns));
        }
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

  if (m_coulomb_scattering) {
    if (hmd->radiation_length > 0.) {
      const double x = range / hmd->radiation_length;
      const double sigma = etcs->sigma_ms * sqrt(x);
      double theta = sigma * Garfield::RndmGaussian();
      turn(cos(theta), sin(theta));
    }
  }
}

void HeedParticle::physics_mrange(double& fmrange) {
  if (!m_coulomb_scattering) return;
  // Get local volume and convert it to a cross-section object.
  const absvol* av = m_currpos.volume();
  auto etcs = dynamic_cast<const EnTransfCS*>(av);
  if (!etcs) return;
  if (etcs->quanC > 0.) {
    // Make sure the step is smaller than the mean free path between
    // ionising collisions.
    fmrange = std::min(fmrange, 0.1 / etcs->quanC);
  }
}

}  // namespace Heed
