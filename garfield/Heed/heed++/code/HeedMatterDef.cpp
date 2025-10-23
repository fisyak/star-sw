#include "heed++/code/HeedMatterDef.h"

#include <cmath>
#include <fstream>
#include <iostream>
#include <limits>

#include "heed++/code/EnergyMesh.h"
#include "heed++/code/PhotoAbsCS.h"
#include "heed++/code/PhysicalConstants.h"
#include "wcpplib/clhep_units/WPhysicalConstants.h"
#include "wcpplib/clhep_units/WSystemOfUnits.h"
#include "wcpplib/math/tline.h"
#include "wcpplib/matter/GasDef.h"
#include "wcpplib/matter/MatterDef.h"
// 2003, I. Smirnov

namespace Heed {

using CLHEP::Avogadro;
using CLHEP::cm3;
using CLHEP::electron_mass_c2;
using CLHEP::fine_structure_const;
using CLHEP::gram;
using CLHEP::mole;
using CLHEP::pi;

HeedMatterDef::HeedMatterDef(EnergyMesh* fenergy_mesh, MatterDef* amatter,
                             const std::vector<AtomPhotoAbsCS*>& faapacs,
                             double fW, double fF)
    : matter(amatter), W(fW), F(fF), energy_mesh(fenergy_mesh) {
  check_econd11(matter, == nullptr, std::cerr);
  check_econd11(matter->qatom(), <= 0, std::cerr);
  const long q = matter->qatom();
  apacs.resize(q, nullptr);
  for (long n = 0; n < q; ++n) {
    apacs[n] = faapacs[n];
    check_econd12(matter->atom(n)->Z(), !=, apacs[n]->get_Z(), std::cerr);
  }
  check_econd11(F, == 0.0, std::cerr);
  if (W == 0.0) {
#ifdef CALC_W_USING_CHARGES
    double mean_I = 0.0;
    double d = 0.0;
    for (long n = 0; n < q; ++n) {
      const double w = matter->weight_quan(n) * apacs[n]->get_Z();
      mean_I += w * apacs[n]->get_I_min();
      d += w;
    }
    W = coef_I_to_W * mean_I / d;
#else
    double mean_I = 0.0;
    for (long n = 0; n < q; ++n) {
      mean_I += matter->weight_quan(n) * apacs[n]->get_I_min();
    }
    W = coef_I_to_W * mean_I;
#endif
  }
  initialize();
}

HeedMatterDef::HeedMatterDef(EnergyMesh* fenergy_mesh, GasDef* agas,
                             std::vector<MolecPhotoAbsCS>& fampacs, double fW,
                             double fF)
    : matter(agas), W(fW), F(fF), energy_mesh(fenergy_mesh) {
  check_econd11(agas, == nullptr, std::cerr);
  check_econd11(agas->qmolec(), <= 0, std::cerr);
  const long qat = agas->qatom();
  apacs.resize(qat, nullptr);
  const long qmol = agas->qmolec();
  long nat = 0;
  for (long nmol = 0; nmol < qmol; ++nmol) {
    check_econd12(agas->molec(nmol)->tqatom(), !=, fampacs[nmol].get_qatom(),
                  std::cerr);
    // number of different atoms in molecule
    const long qa = agas->molec(nmol)->qatom();
    for (long na = 0; na < qa; ++na) {
      apacs[nat] = fampacs[nmol].get_atom(na);
      check_econd12(apacs[nat]->get_Z(), !=, agas->molec(nmol)->atom(na)->Z(),
                    std::cerr);
      nat++;
    }
  }
  if (F == 0.0) {
#ifdef CALC_W_USING_CHARGES
    double u = 0.0;
    double d = 0.0;
    for (long n = 0; n < qmol; ++n) {
      const double w = agas->weight_quan_molec(n) * fampacs[n].get_total_Z();
      u += w * fampacs[n].get_F();
      d += w;
    }
    F = u / d;
#else
    for (long n = 0; n < qmol; ++n) {
      F += agas->weight_quan_molec(n) * fampacs[n].get_F();
    }
#endif
  }

  if (W == 0.0) {
#ifdef CALC_W_USING_CHARGES
    double u = 0.0;
    double d = 0.0;
    for (long n = 0; n < qmol; ++n) {
      const double w = agas->weight_quan_molec(n) * fampacs[n].get_total_Z();
      u += w * fampacs[n].get_W();
      d += w;
    }
    W = u / d;
#else
    for (long n = 0; n < qmol; ++n) {
      W += agas->weight_quan_molec(n) * fampacs[n].get_W();
    }
#endif
  }
  initialize();
}

void HeedMatterDef::initialize() {
  const double amean = matter->A_mean() / (gram / mole);
  const double rho = matter->density() / (gram / cm3);
  eldens_cm_3 = matter->Z_mean() / amean * Avogadro * rho;
  eldens = eldens_cm_3 / pow(C1_MEV_CM, 3);
  xeldens = eldens * C1_MEV_CM;
  wpla = eldens * 4. * pi * fine_structure_const / electron_mass_c2;
  radiation_length = 0.0;
  double rms = 0.0;
  long qat = matter->qatom();
  for (long n = 0; n < qat; ++n) {
    rms += matter->atom(n)->A() * matter->weight_quan(n);
  }
  rms = rms / (gram / mole);

  std::vector<double> RLenAt(qat);
  std::vector<double> RuthAt(qat);
  for (long n = 0; n < qat; ++n) {
    const int z = matter->atom(n)->Z();
    RLenAt[n] = 716.4 * matter->atom(n)->A() / (gram / mole) /
                (z * (z + 1) * log(287. / sqrt(double(z))));
    RuthAt[n] = 4. * pi * z * z * fine_structure_const * fine_structure_const;
  }
  std::vector<double> rm(qat);
  for (long n = 0; n < qat; ++n) {
    rm[n] = matter->atom(n)->A() / (gram / mole) * matter->weight_quan(n) / rms;
  }
  for (long n = 0; n < qat; ++n) {
    radiation_length += rm[n] / RLenAt[n];
  }
  radiation_length = 1. / (rho * radiation_length);

  Rutherford_const = 0.0;
  for (long n = 0; n < qat; ++n) {
    Rutherford_const += matter->weight_quan(n) * RuthAt[n];
  }
  Rutherford_const *= rho * Avogadro / amean;

  min_ioniz_pot = std::numeric_limits<double>::max();
  for (long n = 0; n < qat; ++n) {
    if (min_ioniz_pot > apacs[n]->get_I_min()) {
      min_ioniz_pot = apacs[n]->get_I_min();
    }
  }
  long qe = energy_mesh->get_q();
  ACS.resize(qe);
  ICS.resize(qe);
  epsip.resize(qe);
  epsi1.resize(qe);
  epsi2.resize(qe);
  for (long ne = 0; ne < qe; ++ne) {
    double e1 = energy_mesh->get_e(ne);
    double e2 = energy_mesh->get_e(ne + 1);
    double sa = 0.0;
    double si = 0.0;
    for (int na = 0; na < qat; ++na) {
      const double ta = apacs[na]->get_integral_ACS(e1, e2);
      sa += matter->weight_quan(na) * ta / (e2 - e1);
      check_econd11a(ta, < 0,
                     "ACS: ne=" << ne << " e1=" << e1 << " e2=" << e2
                                << " na=" << na << '\n',
                     std::cerr);
      const double ti =
          s_use_mixture_thresholds == 1
              ? apacs[na]->get_integral_TICS(e1, e2, min_ioniz_pot)
              : apacs[na]->get_integral_ICS(e1, e2);
      si += matter->weight_quan(na) * ti / (e2 - e1);
      check_econd11a(ti, < 0,
                     "ICS: ne=" << ne << " e1=" << e1 << " e2=" << e2
                                << " na=" << na << '\n',
                     std::cerr);
    }
    ACS[ne] = sa;
    check_econd11a(ACS[ne], < 0, "ne=" << ne << '\n', std::cerr);
    ICS[ne] = si;
    check_econd11a(ICS[ne], < 0, "ne=" << ne << '\n', std::cerr);

    double ec = energy_mesh->get_ec(ne);
    double ec2 = ec * ec;
    epsip[ne] = -wpla / ec2;
    epsi2[ne] = sa * C1_MEV2_MBN / ec * eldens / matter->Z_mean();
  }

  // To do next loop we need all epsi2
  for (long ne = 0; ne < qe; ++ne) {
    double ec = energy_mesh->get_ec(ne);
    double ec2 = ec * ec;
    double s = 0;
    // integration of energy
    for (long m = 0; m < qe; ++m) {
      double em1 = energy_mesh->get_e(m);
      double em2 = energy_mesh->get_e(m + 1);
      double ecm = energy_mesh->get_ec(m);
      if (m != ne) {
        s += epsi2[m] * ecm * (em2 - em1) / (ecm * ecm - ec2);
      } else {
        double ee1 = 0.5 * (em1 + ecm);
        double ee2 = 0.5 * (em2 + ecm);
        double ep1, ep2;  // extrapolated values to points ee1 and ee2
        if (m == 0) {
          ep1 = epsi2[m] + (ee1 - ecm) * (epsi2[m + 1] - epsi2[m]) /
                               (energy_mesh->get_ec(m + 1) - ecm);
        } else {
          ep1 = epsi2[m - 1] + (ee1 - energy_mesh->get_ec(m - 1)) *
                                   (epsi2[m] - epsi2[m - 1]) /
                                   (ecm - energy_mesh->get_ec(m - 1));
        }
        if (m < qe - 1) {
          ep2 = epsi2[m] + (ee2 - ecm) * (epsi2[m + 1] - epsi2[m]) /
                               (energy_mesh->get_ec(m + 1) - ecm);
        } else {
          ep2 = epsi2[m] + (ee2 - ecm) * (epsi2[m] - epsi2[m - 1]) /
                               (ecm - energy_mesh->get_ec(m - 1));
        }
        s = s + ep1 * ee1 * (ecm - em1) / (ee1 * ee1 - ec2);
        s = s + ep2 * ee2 * (em2 - ecm) / (ee2 * ee2 - ec2);
      }
    }
    epsi1[ne] = (2. / pi) * s;
  }
}

void HeedMatterDef::replace_epsi12(const std::string& file_name) {
  std::ifstream file(file_name.c_str());
  if (!file) {
    std::cerr << "cannot open file " << file_name << std::endl;
    spexit(std::cerr);
  } else {
    std::cout << "file " << file_name << " is opened" << std::endl;
  }
  long qe = 0;  // number of points in input mesh
  file >> qe;
  check_econd11(qe, <= 2, std::cerr);

  std::vector<double> ener(qe);
  std::vector<double> eps1(qe);
  std::vector<double> eps2(qe);

  for (long ne = 0; ne < qe; ++ne) {
    file >> ener[ne] >> eps1[ne] >> eps2[ne];
    check_econd11(eps2[ne], < 0.0, std::cerr);
    if (ne > 0) {
      check_econd12(ener[ne], <, ener[ne - 1], std::cerr);
    }
  }

  PointCoorMesh<double, std::vector<double> > pcmd(qe, &(ener));
  double emin = ener[0] - 0.5 * (ener[1] - ener[0]);
  double emax = ener[qe - 1] + 0.5 * (ener[qe - 1] - ener[qe - 2]);

  qe = energy_mesh->get_q();
  const auto interpolate =
      t_value_straight_point_ar<double, std::vector<double>,
                                PointCoorMesh<double, std::vector<double> > >;
  for (long ne = 0; ne < qe; ++ne) {
    double ec = energy_mesh->get_ec(ne);
    // pcmd: dimension q; eps1, eps2: dimension q - 1.
    epsi1[ne] = interpolate(pcmd, eps1, ec, 0, 1, emin, 1, emax);
    epsi2[ne] = interpolate(pcmd, eps2, ec, 1, 1, emin, 1, emax);
  }
}

}  // namespace Heed
