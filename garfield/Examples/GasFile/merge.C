#include "Garfield/MediumMagboltz.hh"

using namespace Garfield;

int main() {
  MediumMagboltz gas;
  gas.LoadGasFile("ar_80_co2_20_0T.gas");
  // In case of overlaps, use the values from the file being added.
  constexpr bool replaceOld = true;
  gas.MergeGasFile("ar_80_co2_20_2T.gas", replaceOld);
  gas.WriteGasFile("merged.gas");
}
