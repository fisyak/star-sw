#include "wcpplib/matter/MatterDef.h"

#include <iomanip>

#include "wcpplib/clhep_units/WPhysicalConstants.h"
#include "wcpplib/util/FunNameStack.h"

// 1998-2004 I. Smirnov

namespace Heed {

void MatterDef::calc_I_eff() { I_effh = Z_mean() * 12.0 * CLHEP::eV; }

MatterDef::MatterDef(const std::string& fname, const std::string& fnotation,
                     long fqatom, const std::vector<std::string>& fatom_not,
                     const std::vector<double>& fweight_quan, double fdensity,
                     double ftemperature)
    : AtomMixDef(fqatom, fatom_not, fweight_quan),
      nameh(fname),
      notationh(fnotation),
      temperatureh(ftemperature),
      densityh(fdensity) {
  calc_I_eff();
}

MatterDef::MatterDef(const std::string& fname, const std::string& fnotation,
                     const std::string& fatom_not, double fdensity,
                     double ftemperature)
    : MatterDef(fname, fnotation, 1, {fatom_not}, {1.}, fdensity,
                ftemperature) {}

MatterDef::MatterDef(const std::string& fname, const std::string& fnotation,
                     const std::string& fatom_not1, double fweight_quan1,
                     const std::string& fatom_not2, double fweight_quan2,
                     double fdensity, double ftemperature)
    : MatterDef(fname, fnotation, 2, {fatom_not1, fatom_not2},
                {fweight_quan1, fweight_quan2}, fdensity, ftemperature) {}

MatterDef::MatterDef(const std::string& fname, const std::string& fnotation,
                     const std::string& fatom_not1, double fweight_quan1,
                     const std::string& fatom_not2, double fweight_quan2,
                     const std::string& fatom_not3, double fweight_quan3,
                     double fdensity, double ftemperature)
    : MatterDef(fname, fnotation, 3, {fatom_not1, fatom_not2, fatom_not3},
                {fweight_quan1, fweight_quan2, fweight_quan3}, fdensity,
                ftemperature) {}

}  // namespace Heed
