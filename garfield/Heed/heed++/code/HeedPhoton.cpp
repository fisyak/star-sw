#include "heed++/code/HeedPhoton.h"

#include <algorithm>
#include <iostream>

#include "Garfield/Random.hh"
#include "heed++/code/EnTransfCS.h"
#include "heed++/code/HeedDeltaElectron.h"
#include "heed++/code/HeedDeltaElectronCS.h"
#include "heed++/code/HeedMatterDef.h"
#include "wcpplib/clhep_units/WPhysicalConstants.h"
#include "wcpplib/matter/MatterDef.h"
#include "wcpplib/random/chisran.h"

// 2003, I. Smirnov

namespace Heed {

using CLHEP::Avogadro;
using CLHEP::c_light;
using CLHEP::cm;
using CLHEP::cm3;
using CLHEP::electron_mass_c2;
using CLHEP::gram;
using CLHEP::mole;

HeedPhoton::HeedPhoton(manip_absvol* primvol, const point& pt, const vec& vel,
                       double ftime, long fparent_particle_number,
                       double fenergy, fieldmap* fm,
                       const bool fs_print_listing)
    : gparticle(primvol, pt, vel, ftime),
      m_particle_number(s_counter++),
      m_parent_particle_number(fparent_particle_number),
      m_energy(fenergy),
#ifdef SFER_PHOTOEL
      s_sfer_photoel(0),
#endif
      m_fm(fm) {
  double length_vel = vel.length();
  check_econd11(fabs(length_vel - c_light) / (length_vel + c_light), > 1.0e-10,
                std::cerr);
}

void HeedPhoton::physics(std::vector<gparticle*>& /*secondaries*/) {
  // Stop here if the photon has already been absorbed.
  if (m_photon_absorbed) return;
  if (m_nextpos.prange <= 0.0) return;
  // Get least address of volume
  const absvol* av = m_currpos.volume();
  HeedMatterDef* hmd = nullptr;
  auto etcs = dynamic_cast<const EnTransfCS*>(av);
  if (etcs) {
    hmd = etcs->hmd;
  } else {
    auto hdecs = dynamic_cast<const HeedDeltaElectronCS*>(av);
    if (hdecs) hmd = hdecs->hmd;
  }
  // Stop here if we couldn't retrieve the material definition.
  if (!hmd) return;
  // Sum up the cross-sections.
  std::vector<double> cs;
  std::vector<long> nat;
  std::vector<long> nsh;
  double s = 0.0;
  const long qa = hmd->matter->qatom();
  for (long na = 0; na < qa; na++) {
    const long qs = hmd->apacs[na]->get_qshell();
    const double awq = hmd->matter->weight_quan(na);
    for (long ns = 0; ns < qs; ns++) {
      cs.push_back(hmd->apacs[na]->get_ICS(ns, m_energy) * awq);
      // threshold is taken into account in apacs[na]->get_ACS(ns,..)
      nat.push_back(na);
      nsh.push_back(ns);
      s += cs.back();
    }
  }
  // Multiply with the density and calculate the path length.
  // s = s * hmd->eldens / hmd->matter->Z_mean() * C1_MEV_CM;
  s = s * 1.0e-18 * Avogadro / (hmd->matter->A_mean() / (gram / mole)) *
      hmd->matter->density() / (gram / cm3);
  const double path_length = 1.0 / s;  // cm
  // Draw a random step length.
  const double xleng = -path_length * log(1.0 - Garfield::RndmUniform());
  if (xleng * cm < m_nextpos.prange) {
    m_photon_absorbed = true;
#ifdef SFER_PHOTOEL
    // Assume that virtual photons are already
    // absorbed and s_sfer_photoel is 0 for them
    s_sfer_photoel = 1;
#endif
    // Sample the shell.
    chispre(cs);
    const double r = chisran(Garfield::RndmUniform(), cs);
    const long n = std::min(std::max(long(r), 0L), long(cs.size() - 1));
    m_na_absorbing = nat[n];
    m_ns_absorbing = nsh[n];
    m_nextpos.prange = xleng * cm;
    m_nextpos.pt = m_currpos.pt + m_nextpos.prange * m_currpos.dir;
    m_nextpos.ptloc = m_nextpos.pt;
    m_nextpos.tid.up_absref(&m_nextpos.ptloc);
  }
}

void HeedPhoton::physics_after_new_speed(std::vector<gparticle*>& secondaries) {
  // Stop if the photon has not been absorbed.
  if (!m_photon_absorbed) return;
  // Stop if the delta electrons have already been generated.
  if (m_delta_generated) return;
  // Get local volume.
  const absvol* av = m_currpos.volume();
  HeedMatterDef* hmd = nullptr;
  auto etcs = dynamic_cast<const EnTransfCS*>(av);
  if (etcs) {
    hmd = etcs->hmd;
  } else {
    auto hdecs = dynamic_cast<const HeedDeltaElectronCS*>(av);
    if (hdecs) hmd = hdecs->hmd;
  }
  // Stop here if we couldn't retrieve the material definition.
  if (!hmd) return;
  // Generate delta-electrons.
  std::vector<double> el_energy;
  std::vector<double> ph_energy;
  hmd->apacs[m_na_absorbing]->get_escape_particles(m_ns_absorbing, m_energy,
                                                   el_energy, ph_energy);
  const long qel = el_energy.size();
  for (long nel = 0; nel < qel; nel++) {
    vec vel = m_currpos.dir;
    if (nel == 0) {
      // The first in the list should be the photoelectron.
#ifdef SFER_PHOTOEL
      if (s_sfer_photoel == 1) {
        vel.random_sfer_vec();
      } else {
        vel = m_currpos.dir;
      }
#else
      vel = m_currpos.dir;  // direction is OK
#endif
    } else {
      vel.random_sfer_vec();
    }
    const double gam_1 = el_energy[nel] / electron_mass_c2;
    const double inv = 1.0 / (gam_1 + 1.0);
    const double beta = sqrt(1.0 - inv * inv);
    const double mod_v = beta * c_light;
    vel = vel * mod_v;
    HeedDeltaElectron* hd =
        new HeedDeltaElectron(m_currpos.tid.eid[0], m_currpos.pt, vel,
                              m_currpos.time, m_particle_number, m_fm);
    secondaries.push_back(hd);
  }
  const long qph = ph_energy.size();
  for (long nph = 0; nph < qph; nph++) {
    vec vel;
    vel.random_sfer_vec();
    vel *= c_light;
    HeedPhoton* hp =
        new HeedPhoton(m_currpos.tid.eid[0], m_currpos.pt, vel, m_currpos.time,
                       m_particle_number, ph_energy[nph], m_fm);
    secondaries.push_back(hp);
  }
  m_delta_generated = true;
  m_alive = false;
}

}  // namespace Heed
