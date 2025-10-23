#include "wcpplib/matter/AtomDef.h"

#include <iomanip>
#include <iostream>

#include "wcpplib/clhep_units/WPhysicalConstants.h"
#include "wcpplib/util/FunNameStack.h"

// 1998-2004, I. Smirnov.

namespace Heed {

using CLHEP::Avogadro;
using CLHEP::gram;
using CLHEP::mole;

AtomDef::AtomDef(const std::string& fnameh, const std::string& fnotationh,
                 int fZh, double fAh)
    : nameh(fnameh), notationh(fnotationh), Zh(fZh), Ah(fAh) {
  static constexpr int max_poss_atom_z = 100;
  check_econd21(fZh, < 1 ||, > max_poss_atom_z, std::cerr);
}

std::list<AtomDef> AtomDefs::atoms;

void AtomDefs::addAtom(const std::string& name, const std::string& notation,
                       int z, double a) {
  AtomDefs::atoms.push_back(AtomDef(name, notation, z, a));
}

const std::list<AtomDef>& AtomDefs::getAtoms() {
  if (!atoms.empty()) return atoms;
  addAtom("Hydrogen", "H", 1, 1.0);
  // addAtom("Hydrogen", "H", 1, 1.00794 * gram/mole));
  addAtom("Helium", "He", 2, 4.002602 * gram / mole);
  addAtom("Lithium", "Li", 3, 6.941 * gram / mole);
  addAtom("Beryllium", "Be", 4, 9.012182 * gram / mole);
  addAtom("Boron", "B", 5, 10.811 * gram / mole);
  addAtom("Carbon", "C", 6, 12.011 * gram / mole);
  addAtom("Nitrogen", "N", 7, 14.00674 * gram / mole);
  addAtom("Oxygen", "O", 8, 15.9994 * gram / mole);
  addAtom("Fluorine", "F", 9, 18.9984032 * gram / mole);
  addAtom("Neon", "Ne", 10, 20.1797 * gram / mole);
  addAtom("Sodium", "Na", 11, 22.989768 * gram / mole);
  addAtom("Magnesium", "Mg", 12, 24.3050 * gram / mole);
  addAtom("Aluminium", "Al", 13, 26.981539 * gram / mole);
  addAtom("Silicon", "Si", 14, 28.0855 * gram / mole);
  addAtom("Phosphorus", "P", 15, 30.973762 * gram / mole);
  addAtom("Sulfur", "S", 16, 32.066 * gram / mole);
  addAtom("Chlorine", "Cl", 17, 35.066 * gram / mole);
  addAtom("Argon", "Ar", 18, 39.948 * gram / mole);
  addAtom("Argon_without_K", "Ar_without_K", 16, 39.948 * gram / mole);
  addAtom("Potassium", "K", 19, 39.098 * gram / mole);
  addAtom("Calcium", "Ca", 20, 40.08 * gram / mole);
  addAtom("Scandium", "Sc", 21, 44.9559 * gram / mole);
  addAtom("Titanium", "Ti", 22, 47.867 * gram / mole);
  addAtom("Vanadium", "V", 23, 50.9414 * gram / mole);
  addAtom("Chromium", "Cr", 24, 51.996 * gram / mole);
  addAtom("Manganese", "Mn", 25, 54.9380 * gram / mole);
  addAtom("Iron", "Fe", 26, 55.845 * gram / mole);
  addAtom("Cobalt", "Co", 27, 58.9332 * gram / mole);
  addAtom("Nickel", "Ni", 28, 58.70 * gram / mole);
  addAtom("Copper", "Cu", 29, 63.546 * gram / mole);
  addAtom("Zinc", "Zn", 30, 65.38 * gram / mole);
  addAtom("Gallium", "Ga", 31, 69.72 * gram / mole);
  addAtom("Germanium", "Ge", 32, 72.59 * gram / mole);
  addAtom("Arsenic", "As", 33, 74.9216 * gram / mole);
  addAtom("Selenium", "Se", 34, 78.96 * gram / mole);
  addAtom("Bromine", "Br", 35, 79.904 * gram / mole);
  addAtom("Krypton", "Kr", 36, 83.80 * gram / mole);
  addAtom("Rubidium", "Rb", 37, 85.4673 * gram / mole);
  addAtom("Strontium", "Sr", 38, 87.62 * gram / mole);
  addAtom("Yttrium", "Y", 39, 88.9059 * gram / mole);
  addAtom("Zirconium", "Zr", 40, 91.22 * gram / mole);
  addAtom("Niobium", "Nb", 41, 92.9064 * gram / mole);
  addAtom("Molybdenum", "Mo", 42, 95.94 * gram / mole);
  addAtom("Technetium", "Tc", 43, 98 * gram / mole);
  addAtom("Ruthenium", "Ru", 44, 101.07 * gram / mole);
  addAtom("Rhodium", "Rh", 45, 102.9055 * gram / mole);
  addAtom("Palladium", "Pd", 46, 106.4 * gram / mole);
  addAtom("Silver", "Ag", 47, 107.868 * gram / mole);
  addAtom("Cadmium", "Cd", 48, 112.411 * gram / mole);
  addAtom("Indium", "In", 49, 114.818 * gram / mole);
  addAtom("Tin", "Sn", 50, 118.710 * gram / mole);
  addAtom("Antimony", "Sb", 51, 121.760 * gram / mole);
  addAtom("Tellurium", "Te", 52, 127.60 * gram / mole);
  addAtom("Iodine", "I", 53, 126.9045 * gram / mole);
  addAtom("Xenon", "Xe", 54, 131.293 * gram / mole);
  addAtom("Caesium", "Cs", 55, 132.9054519 * gram / mole);
  addAtom("Tungsten", "W", 74, 183.85 * gram / mole);
  addAtom("Mercury", "Hg", 80, 200.59 * gram / mole);
  addAtom("Bismuth", "Bi", 83, 208.9804 * gram / mole);
  addAtom("Uranium", "U", 92, 238.0289 * gram / mole);
  addAtom("Plutonium", "Pu", 94, 244.0 * gram / mole);
  return atoms;
}

const AtomDef* AtomDefs::getAtom(const std::string& fnotation) {
  for (const auto& atom : getAtoms()) {
    if (atom.notation() == fnotation) return &atom;
  }
  return nullptr;
}

double AtomDefs::getA(int fZ) {
  for (const auto& atom : getAtoms()) {
    if (atom.Z() == fZ) return atom.A();
  }
  std::cerr << "Atom is not found, Z=" << fZ << '\n';
  spexit(std::cerr);
  return 0.0;
}

const AtomDef* AtomDefs::getAtom(int fZ) {
  for (const auto& atom : getAtoms()) {
    if (atom.Z() == fZ) return &atom;
  }
  std::cerr << "Atom is not found, Z=" << fZ << '\n';
  spexit(std::cerr);
  return nullptr;
}

AtomMixDef::AtomMixDef(unsigned long fqatom,
                       const std::vector<std::string>& fatom_not,
                       const std::vector<double>& fweight_quan)
    : qatomh(fqatom),
      atomh(fqatom, nullptr),
      weight_quanh(fqatom, 0.0),
      weight_massh(fqatom, 0.0) {
  check_econd11(fqatom, <= 0, std::cerr);
  check_econd12(fqatom, >, fatom_not.size(), std::cerr);
  check_econd12(fqatom, >, fweight_quan.size(), std::cerr);

  for (long n = 0; n < qatomh; ++n) {
    auto ad = AtomDefs::getAtom(fatom_not[n]);
    if (!ad) {
      std::cerr << "cannot find atom with notation " << fatom_not[n]
                << "\nIn particular, check the sequence of initialization\n";
      spexit(std::cerr);
    }
    atomh[n] = ad;
  }
  double s = 0.0;
  for (long n = 0; n < qatomh; n++) {
    weight_quanh[n] = fweight_quan[n];
    check_econd11(weight_quanh[n], <= 0, std::cerr);
    s += weight_quanh[n];
  }
  check_econd11(s, <= 0, std::cerr);
  if (s != 1.0) {
    for (long n = 0; n < qatomh; n++) {
      weight_quanh[n] /= s;
    }
  }
  for (long n = 0; n < qatomh; n++) {
    weight_massh[n] = weight_quanh[n] * atomh[n]->A();
  }
  s = 0.0;
  for (long n = 0; n < qatomh; n++) {
    s += weight_massh[n];
  }
  check_econd11(s, <= 0, std::cerr);
  if (s != 1.0) {
    for (long n = 0; n < qatomh; n++) {
      weight_massh[n] /= s;
    }
  }
  for (long n = 0; n < qatomh; n++) {
    Z_meanh += atomh[n]->Z() * weight_quanh[n];
    A_meanh += atomh[n]->A() * weight_quanh[n];
    inv_A_meanh += (1.0 / atomh[n]->A()) * weight_quanh[n];
  }
  mean_ratio_Z_to_Ah = Z_meanh / A_meanh;
  NumberOfElectronsInGramh = mean_ratio_Z_to_Ah * (gram / mole) * Avogadro;
}

AtomMixDef::AtomMixDef(unsigned long fqatom,
                       const std::vector<std::string>& fatom_not,
                       const std::vector<long>& fweight_quan)
    : qatomh(fqatom),
      atomh(fqatom, nullptr),
      weight_quanh(fqatom, 0.0),
      weight_massh(fqatom, 0.0) {
  check_econd11(fqatom, <= 0, std::cerr);
  check_econd12(fqatom, >, fatom_not.size(), std::cerr);
  check_econd12(fqatom, >, fweight_quan.size(), std::cerr);

  for (long n = 0; n < qatomh; ++n) {
    auto ad = AtomDefs::getAtom(fatom_not[n]);
    if (!ad) {
      std::cerr << "cannot find atom with notation " << fatom_not[n]
                << "\nIn particular, check the sequence of initialization\n";
      spexit(std::cerr);
    }
    atomh[n] = ad;
  }
  double s = 0.0;
  for (long n = 0; n < qatomh; n++) {
    weight_quanh[n] = fweight_quan[n];
    check_econd11(weight_quanh[n], <= 0, std::cerr);
    s += weight_quanh[n];
  }
  check_econd11(s, <= 0, std::cerr);
  if (s != 1.0) {
    for (long n = 0; n < qatomh; n++) {
      weight_quanh[n] /= s;
    }
  }
  for (long n = 0; n < qatomh; n++) {
    weight_massh[n] = weight_quanh[n] * atomh[n]->A();
  }
  s = 0.0;
  for (long n = 0; n < qatomh; n++) {
    s += weight_massh[n];
  }
  check_econd11(s, <= 0, std::cerr);
  if (s != 1.0) {
    for (long n = 0; n < qatomh; n++) {
      weight_massh[n] /= s;
    }
  }
  for (long n = 0; n < qatomh; n++) {
    Z_meanh += atomh[n]->Z() * weight_quanh[n];
    A_meanh += atomh[n]->A() * weight_quanh[n];
    inv_A_meanh += (1.0 / atomh[n]->A()) * weight_quanh[n];
  }
  mean_ratio_Z_to_Ah = Z_meanh / A_meanh;
  NumberOfElectronsInGramh = mean_ratio_Z_to_Ah * (gram / mole) * Avogadro;
}

}  // namespace Heed
