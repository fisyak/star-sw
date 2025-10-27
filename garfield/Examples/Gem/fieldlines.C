#include <TApplication.h>

#include <vector>

#include "Garfield/ComponentAnsys123.hh"
#include "Garfield/MediumMagboltz.hh"
#include "Garfield/ViewField.hh"

using namespace Garfield;

int main(int argc, char* argv[]) {
  TApplication app("app", &argc, argv);

  // Load the field map.
  ComponentAnsys123 fm;
  fm.Initialise("ELIST.lis", "NLIST.lis", "MPLIST.lis", "PRNSOL.lis", "mm");
  fm.EnableMirrorPeriodicityX();
  fm.EnableMirrorPeriodicityY();
  fm.PrintRange();

  // Setup the gas.
  MediumMagboltz gas("ar", 80., "co2", 20.);

  // Associate the gas with the corresponding field map material.
  fm.SetGas(&gas);
  fm.PrintMaterials();

  // Dimensions of the GEM [cm]
  constexpr double pitch = 0.014;

  ViewField fieldView(&fm);
  fieldView.SetPlaneXZ();
  // Set the plot limits in the current viewing plane.
  const double xmin = -0.5 * pitch;
  const double xmax = 0.5 * pitch;
  const double zmin = -0.02;
  const double zmax = 0.02;
  fieldView.SetArea(xmin, zmin, xmax, zmax);
  fieldView.SetVoltageRange(-160., 160.);
  fieldView.GetCanvas()->SetLeftMargin(0.16);
  fieldView.Plot("v", "CONT1");

  std::vector<double> xf;
  std::vector<double> yf;
  std::vector<double> zf;
  fieldView.EqualFluxIntervals(xmin, 0, 0.99 * zmax, xmax, 0, 0.99 * zmax, xf,
                               yf, zf, 20);
  fieldView.PlotFieldLines(xf, yf, zf, true, false);
  app.Run(true);
}
