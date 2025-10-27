#include <TApplication.h>

#include "Garfield/ComponentAnsys123.hh"
#include "Garfield/MediumMagboltz.hh"
#include "Garfield/ViewField.hh"

using namespace Garfield;

int main(int argc, char* argv[]) {
  TApplication app("app", &argc, argv);

  MediumMagboltz gas("ar");

  // Load the main field map.
  ComponentAnsys123 fm;
  const std::string path = "fieldmaps/strips/";
  fm.Initialise(path + "ELIST.lis", path + "NLIST.lis", path + "MPLIST.lis",
                path + "field.lis", "mm");

  // Associate the gas with the corresponding field map material.
  fm.SetGas(&gas);

  // Load the weighting field maps.
  fm.SetWeightingField(path + "weight1.lis", "strip1");
  fm.SetWeightingField(path + "weight2.lis", "strip2");
  fm.SetWeightingField(path + "weight3.lis", "strip3");

  ViewField fieldView(&fm);
  fieldView.SetPlaneXZ();
  fieldView.PlotContourWeightingField("strip1", "v");

  app.Run();
}
