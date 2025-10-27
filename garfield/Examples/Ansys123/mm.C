#include <TApplication.h>

#include "Garfield/ComponentAnsys123.hh"
#include "Garfield/MediumMagboltz.hh"
#include "Garfield/ViewField.hh"

using namespace Garfield;

int main(int argc, char* argv[]) {
  TApplication app("app", &argc, argv);

  MediumMagboltz gas("ar", 95., "cf4", 3., "ic4h10", 2.);

  // Load the field map.
  ComponentAnsys123 fm;
  const std::string path = "fieldmaps/micromegas/";
  fm.Initialise(path + "ELIST.lis", path + "NLIST.lis", path + "MPLIST.lis",
                path + "PRNSOL.lis", "micron");
  fm.EnableMirrorPeriodicityX();
  fm.EnableMirrorPeriodicityY();
  fm.PrintRange();

  // Associate the gas with the corresponding field map material.
  fm.SetGas(&gas);
  fm.PrintMaterials();

  // Get the pitch.
  double xmin, ymin, zmin, xmax, ymax, zmax;
  fm.GetElementaryCell(xmin, ymin, zmin, xmax, ymax, zmax);
  const double pitch = 2 * (xmax - xmin);

  ViewField fieldView(&fm);
  fieldView.SetPlaneXZ();
  fieldView.SetArea(-pitch, 0, pitch, zmax);
  fieldView.PlotContour();

  std::vector<double> xf;
  std::vector<double> yf;
  std::vector<double> zf;
  fieldView.EqualFluxIntervals(-pitch, 0, 0.95 * zmax, pitch, 0, 0.95 * zmax,
                               xf, yf, zf, 25);
  // fieldView.PlotFieldLines(xf, yf, zf);

  app.Run();
}
