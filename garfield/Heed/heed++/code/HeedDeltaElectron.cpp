#include "heed++/code/HeedDeltaElectron.h"

#include <iostream>

#include "Garfield/Random.hh"
#include "heed++/code/ElElasticScat.h"
#include "heed++/code/EnergyMesh.h"
#include "heed++/code/HeedDeltaElectronCS.h"
#include "heed++/code/HeedMatterDef.h"
#include "heed++/code/PairProd.h"
#include "wcpplib/clhep_units/WPhysicalConstants.h"
#include "wcpplib/math/lorgamma.h"
// 2003, I. Smirnov

#define USE_ADJUSTED_W
#define RANDOM_POIS

namespace {

long findInterval(Heed::EnergyMesh* emesh, const double energy) {
  const long n = emesh->get_interval_number_between_centers(energy);
  return std::min(std::max(n, 0L), emesh->get_q() - 2);
}

double interpolate(Heed::EnergyMesh* emesh, const double x,
                   const std::vector<double>& y) {
  const long n = findInterval(emesh, x);
  const double x1 = emesh->get_ec(n);
  const double x2 = emesh->get_ec(n + 1);
  const double y1 = y[n];
  const double y2 = y[n + 1];
  return y1 + (x - x1) * (y2 - y1) / (x2 - x1);
}

double sample_ctheta(const double sigma) {
  double ctheta = 0.;
  do {
    double y = Garfield::RndmUniform();
    while (y == 1.) {
      y = Garfield::RndmUniform();
    }
    const double x = sigma * (-log(1.0 - y));
    ctheta = 1. - x;
  } while (ctheta <= -1.0);
  return ctheta;
}

}  // namespace

namespace Heed {

using CLHEP::c_light;
using CLHEP::c_squared;
using CLHEP::cm;
using CLHEP::degree;
using CLHEP::eV;
using CLHEP::keV;
using CLHEP::MeV;

bool HeedDeltaElectron::s_low_mult_scattering = true;
bool HeedDeltaElectron::s_high_mult_scattering = true;
bool HeedDeltaElectron::s_direct_low_if_little = true;

HeedDeltaElectron::HeedDeltaElectron(manip_absvol* primvol, const point& pt,
                                     const vec& vel, double ftime,
                                     long fparent_particle_number, fieldmap* fm,
                                     bool fprint_listing)
    : eparticle(primvol, pt, vel, ftime, &electron_def, fm),
      parent_particle_number(fparent_particle_number),
      m_particle_number(s_counter++) {}

void HeedDeltaElectron::physics_mrange(double& fmrange) {
  m_mult_low_path_length = false;
  m_q_low_path_length = 0.0;
  m_path_length = false;
  if (fmrange <= 0.0) return;
  if (m_curr_ekin <= 0.0) {
    fmrange = 0.0;
    return;
  }
  // Get local volume and convert it to a cross-section object.
  const absvol* av = m_currpos.volume();
  auto hdecs = dynamic_cast<const HeedDeltaElectronCS*>(av);
  if (!hdecs) return;
  const double ek = m_curr_ekin / MeV;
  // Get the dE/dx at this kinetic energy.
  EnergyMesh* emesh = hdecs->hmd->energy_mesh;
  const double dedx = interpolate(emesh, ek, hdecs->eLoss);
  // Min. loss 50 eV.
  double eloss = std::max(0.1 * ek, 0.00005);
  if (eloss > ek) {
    eloss = ek;
    m_stop_eloss = true;
  } else {
    m_stop_eloss = false;
  }
  fmrange = std::min(fmrange, (eloss / dedx) * cm);
  const double ek_restr = std::max(ek, 0.0005);

  double low_path_length = 0.;  // in internal units
  if (s_low_mult_scattering) {
    low_path_length = interpolate(emesh, ek_restr, hdecs->low_lambda) * cm;
    long qscat = hdecs->eesls->get_qscat();
    const double sigma_ctheta = hdecs->get_sigma(ek_restr, qscat);
    // Reduce the number of scatterings, if the angle is too large.
    if (sigma_ctheta > 0.3) qscat = long(qscat * 0.3 / sigma_ctheta);
    const double mult_low_path_length = qscat * low_path_length;
    if (fmrange > mult_low_path_length) {
      fmrange = mult_low_path_length;
      m_mult_low_path_length = true;
      m_q_low_path_length = hdecs->eesls->get_qscat();
      m_stop_eloss = false;
    } else {
      m_mult_low_path_length = false;
      m_q_low_path_length = fmrange / low_path_length;
    }
  }

  if (s_high_mult_scattering) {
    const double mean_path = interpolate(emesh, ek_restr, hdecs->lambda);
    const double path_length =
        -mean_path * cm * log(1.0 - Garfield::RndmUniform());
    if (fmrange > path_length) {
      fmrange = path_length;
      m_path_length = true;
      m_mult_low_path_length = true;
      if (s_low_mult_scattering) {
        m_q_low_path_length = fmrange / low_path_length;
      }
      m_stop_eloss = false;
    } else {
      m_path_length = false;
    }
  }
  m_phys_mrange = fmrange;
}

void HeedDeltaElectron::physics_after_new_speed(
    std::vector<gparticle*>& /*secondaries*/) {
  check_econd11(vecerror, != 0, std::cerr);
  if (m_currpos.prange <= 0.0) {
    if (m_curr_ekin <= 0.0) {
      // Get local volume.
      absvol* av = m_currpos.volume();
      if (av && av->s_sensitive && m_fm->inside(m_currpos.ptloc)) {
        conduction_electrons.emplace_back(
            HeedCondElectron(m_currpos.ptloc, m_currpos.time));
      }
      m_alive = false;
    }
    return;
  }
  // Get local volume and convert it to a cross-section object.
  const absvol* av = m_currpos.volume();
  auto hdecs = dynamic_cast<const HeedDeltaElectronCS*>(av);
  if (!hdecs) return;
  double ek = m_curr_ekin / MeV;
  // Calculate dE/dx and energy loss. Update the kinetic energy.
  double dedx;
  double Eloss = 0.;
  if (m_stop_eloss && m_phys_mrange == m_currpos.prange) {
    Eloss = m_curr_ekin;
    m_curr_ekin = 0.0;
    dedx = Eloss / m_currpos.prange / (MeV / cm);
  } else {
    EnergyMesh* emesh = hdecs->hmd->energy_mesh;
    dedx = interpolate(emesh, ek, hdecs->eLoss);
    Eloss = std::min(m_currpos.prange * dedx * MeV / cm, m_curr_ekin);
    m_total_eloss += Eloss;
    m_curr_ekin -= Eloss;
  }
  if (m_curr_ekin <= 0.0) {
    m_curr_ekin = 0.0;
    m_curr_gamma_1 = 0.0;
    m_currpos.speed = 0.0;
    m_alive = false;
  } else {
    const double resten = m_mass * c_squared;
    m_curr_gamma_1 = m_curr_ekin / resten;
    m_currpos.speed = c_light * lorbeta(m_curr_gamma_1);
  }
  absvol* vav = m_currpos.volume();
  if (vav && vav->s_sensitive) {
    if (Eloss > 0.0) ionisation(Eloss, dedx, hdecs->pairprod);
  }
  if (!m_alive) {
    // Done tracing the delta electron. Create the last conduction electron.
    vav = m_currpos.volume();
    if (vav && vav->s_sensitive && m_fm->inside(m_currpos.ptloc)) {
      conduction_electrons.emplace_back(
          HeedCondElectron(m_currpos.ptloc, m_currpos.time));
    }
    return;
  }

  double ek_restr = std::max(ek, 0.0005);
  if (m_currpos.prange < m_phys_mrange) {
    // recalculate scatterings
    m_path_length = false;
    if (s_low_mult_scattering) {
      EnergyMesh* emesh = hdecs->hmd->energy_mesh;
      const double low_path_length =
          interpolate(emesh, ek_restr, hdecs->low_lambda) * cm;
      m_mult_low_path_length = false;
      m_q_low_path_length = m_currpos.prange / low_path_length;
    }
  }
#ifdef RANDOM_POIS
  if (m_q_low_path_length > 0.0) {
    m_q_low_path_length = Garfield::RndmPoisson(m_q_low_path_length);
  }
#endif
  if (m_q_low_path_length > 0) {
    if (s_direct_low_if_little && m_q_low_path_length < 5) {
      // direct modeling
      EnergyMesh* emesh = hdecs->hmd->energy_mesh;
      const long n1r = findInterval(emesh, ek_restr);
      for (long nscat = 0; nscat < m_q_low_path_length; ++nscat) {
        const double theta =
            hdecs->low_angular_points_ran[n1r].ran(Garfield::RndmUniform()) *
            degree;
        turn(cos(theta), sin(theta));
      }
    } else {
      const double sigma = hdecs->get_sigma(ek_restr, m_q_low_path_length);
      // actually it is mean(1-cos(theta)) or
      // sqrt(mean(square(1-cos(theta)))) depending on USE_MEAN_COEF
      // Gauss:
      // double ctheta = 1.0 - fabs(Garfield::RndmGaussian() * sigma);
      // Exponential distribution fits better:
#ifdef USE_MEAN_COEF
      const double ctheta = sample_ctheta(sigma);
#else
      const double ctheta = sample_ctheta(sigma / sqrt(2.));
#endif
      const double theta = acos(ctheta);
      turn(ctheta, sin(theta));
    }
  }
  if (m_path_length) {
    EnergyMesh* emesh = hdecs->hmd->energy_mesh;
    const long n1r = findInterval(emesh, ek_restr);
    const double theta =
        hdecs->angular_points_ran[n1r].ran(Garfield::RndmUniform()) * degree;
    turn(cos(theta), sin(theta));
  }
}

void HeedDeltaElectron::ionisation(const double eloss, const double dedx,
                                   PairProd* pairprod) {
  if (eloss < m_necessary_energy) {
    m_necessary_energy -= eloss;
    return;
  }

  if (m_necessary_energy <= 0.0) {
#ifdef USE_ADJUSTED_W
    m_necessary_energy = pairprod->get_eloss(m_prev_ekin / eV) * eV;
#else
    m_necessary_energy = pairprod->get_eloss() * eV;
#endif
  }
  double eloss_left = eloss;
  point curpt = m_prevpos.pt;
  vec dir = m_prevpos.dir;  // this approximation ignores curvature
  double ekin = m_prev_ekin;
  while (eloss_left >= m_necessary_energy) {
    const double step_length = m_necessary_energy / (dedx * MeV / cm);
    curpt = curpt + dir * step_length;
    point ptloc = curpt;
    m_prevpos.tid.up_absref(&ptloc);
    if (m_fm->inside(ptloc)) {
      conduction_electrons.emplace_back(
          HeedCondElectron(ptloc, m_currpos.time));
      conduction_ions.emplace_back(HeedCondElectron(ptloc, m_currpos.time));
    }
    eloss_left -= m_necessary_energy;
    ekin -= m_necessary_energy;
    if (ekin < 0.) break;
    // Generate next random energy
#ifdef USE_ADJUSTED_W
    m_necessary_energy = eV * pairprod->get_eloss(ekin / eV);
#else
    m_necessary_energy = pairprod->get_eloss() * eV;
#endif
  }
  m_necessary_energy -= eloss_left;
}

}  // namespace Heed
