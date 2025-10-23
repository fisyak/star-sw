// -*- C++ -*-
// $Id: SystemOfUnits.h,v 1.12 2002/03/30 15:02:06 evc Exp $
// ----------------------------------------------------------------------
// HEP coherent system of Units
//
// This file has been provided to CLHEP by Geant4 (simulation toolkit for HEP).
//
// The basic units are :
// millimeter              (millimeter)
// nanosecond              (nanosecond)
// Mega electron Volt      (MeV)
// positron charge         (eplus)
// degree Kelvin           (kelvin)
// the amount of substance (mole)
// luminous intensity      (candela)
// radian                  (radian)
// steradian               (steradian)
//
// Below is a non exhaustive list of derived and practical units
// (i.e. mostly the SI units).
// You can add your own units.
//
// The SI numerical value of the positron charge is defined here,
// as it is needed for conversion factor : positron charge = e_SI (coulomb)
//
// The others physical constants are defined in the header file :
// PhysicalConstants.h
//
// Authors: M.Maire, S.Giani
//
// History:
//
// 06.02.96   Created.
// 28.03.96   Added miscellaneous constants.
// 05.12.97   E.Tcherniaev: Redefined pascal (to avoid warnings on WinNT)
// 20.05.98   names: meter, second, gram, radian, degree
//            (from Brian.Lasiuk@yale.edu (STAR)). Added luminous units.
// 05.08.98   angstrom, picobarn, microsecond, picosecond, petaelectronvolt
// 01.03.01   parsec

#ifndef HEED_SYSTEM_OF_UNITS_H
#define HEED_SYSTEM_OF_UNITS_H

namespace Heed {

namespace CLHEP {

//
//
//
static constexpr double pi = 3.14159265358979323846;
static constexpr double twopi = 2 * pi;
static constexpr double halfpi = pi / 2;
static constexpr double pi2 = pi * pi;

//
// Length [L]
//
static constexpr double millimeter = 1.;
static constexpr double millimeter2 = millimeter * millimeter;
static constexpr double millimeter3 = millimeter * millimeter * millimeter;

static constexpr double centimeter = 10. * millimeter;
static constexpr double centimeter2 = centimeter * centimeter;
static constexpr double centimeter3 = centimeter * centimeter * centimeter;

static constexpr double meter = 1000. * millimeter;
static constexpr double meter2 = meter * meter;
static constexpr double meter3 = meter * meter * meter;

// symbols

static constexpr double cm = centimeter;
static constexpr double cm2 = centimeter2;
static constexpr double cm3 = centimeter3;

static constexpr double m = meter;
static constexpr double m2 = meter2;
static constexpr double m3 = meter3;

//
// Angle
//
static constexpr double radian = 1.;
static constexpr double degree = (3.14159265358979323846 / 180.0) * radian;

// symbols
static constexpr double rad = radian;

//
// Time [T]
//
static constexpr double nanosecond = 1.;
static constexpr double second = 1.e+9 * nanosecond;

// symbols
static constexpr double ns = nanosecond;
static constexpr double s = second;

//
// Electric charge [Q]
//
static constexpr double eplus = 1.;             // positron charge
static constexpr double e_SI = 1.60217733e-19;  // positron charge in coulomb
static constexpr double coulomb =
    eplus / e_SI;  // coulomb = 6.24150 e+18 * eplus

//
// Energy [E]
//
static constexpr double megaelectronvolt = 1.;
static constexpr double electronvolt = 1.e-6 * megaelectronvolt;
static constexpr double kiloelectronvolt = 1.e-3 * megaelectronvolt;
static constexpr double gigaelectronvolt = 1.e+3 * megaelectronvolt;

static constexpr double joule =
    electronvolt / e_SI;  // joule = 6.24150 e+12 * MeV

// symbols
static constexpr double MeV = megaelectronvolt;
static constexpr double eV = electronvolt;
static constexpr double keV = kiloelectronvolt;
static constexpr double GeV = gigaelectronvolt;

//
// Mass [E][T^2][L^-2]
//
static constexpr double kilogram = joule * second * second / (meter * meter);
static constexpr double gram = 1.e-3 * kilogram;
static constexpr double milligram = 1.e-3 * gram;

// symbols
static constexpr double kg = kilogram;
static constexpr double g = gram;
static constexpr double mg = milligram;

//
// Force [E][L^-1]
//
static constexpr double newton =
    joule / meter;  // newton = 6.24150 e+9 * MeV/mm

//
// Pressure [E][L^-3]
//
#define pascal hep_pascal                      // a trick to avoid warnings
static constexpr double pascal = newton / m2;  // pascal = 6.24150 e+3 * MeV/mm3
static constexpr double bar =
    100000 * pascal;  // bar    = 6.24150 e+8 * MeV/mm3
static constexpr double atmosphere =
    101325 * pascal;  // atm    = 6.32420 e+8 * MeV/mm3

//
// Electric current [Q][T^-1]
//
static constexpr double ampere =
    coulomb / second;  // ampere = 6.24150 e+9 * eplus/ns

//
// Electric potential [E][Q^-1]
//
static constexpr double megavolt = megaelectronvolt / eplus;
static constexpr double kilovolt = 1.e-3 * megavolt;
static constexpr double volt = 1.e-6 * megavolt;

//
// Electric resistance [E][T][Q^-2]
//
static constexpr double ohm =
    volt / ampere;  // ohm = 1.60217e-16*(MeV/eplus)/(eplus/ns)

//
// Magnetic Flux [T][E][Q^-1]
//
static constexpr double weber = volt * second;  // weber = 1000*megavolt*ns

//
// Magnetic Field [T][E][Q^-1][L^-2]
//
static constexpr double tesla =
    volt * second / meter2;  // tesla =0.001*megavolt*ns/mm2

static constexpr double gauss = 1.e-4 * tesla;
static constexpr double kilogauss = 1.e-1 * tesla;

//
// Inductance [T^2][E][Q^-2]
//
static constexpr double henry =
    weber / ampere;  // henry = 1.60217e-7*MeV*(ns/eplus)**2

//
// Temperature
//
static constexpr double kelvin = 1.;

//
// Amount of substance
//
static constexpr double mole = 1.;

}  // namespace CLHEP

}  // namespace Heed

#endif /* HEED_SYSTEM_OF_UNITS_H */
