#include <TApplication.h>

#include "Garfield/ComponentAnalyticField.hh"
#include "Garfield/MediumMagboltz.hh"
#include "Garfield/ViewCell.hh"
#include "Garfield/ViewField.hh"

using namespace Garfield;

int main(int argc, char* argv[]) {
  TApplication app("app", &argc, argv);

  // Setup the gas.
  MediumMagboltz gas("ne", 85.72, "co2", 9.52, "n2", 4.76);

  // Describe the cell layout.
  ComponentAnalyticField cmp;
  cmp.SetMedium(&gas);
  cmp.SetPolarCoordinates();
  cmp.AddPlaneR(2., 0.);
  cmp.AddPlanePhi(0, 0.);
  cmp.AddPlanePhi(60., 0.);
  cmp.AddWire(1.5, 30., 50.e-4, 500.);
  cmp.PrintCell();

  // Plot the potential.
  ViewField fieldView(&cmp);
  const double xmin = -2.1;
  const double xmax = 2.1;
  const double ymin = -2.1;
  const double ymax = 2.1;
  fieldView.SetArea(xmin, ymin, xmax, ymax);
  fieldView.PlotContour();
  ViewCell cellView(&cmp);
  cellView.SetCanvas(fieldView.GetCanvas());
  cellView.SetArea(xmin, ymin, -1., xmax, ymax, 1.);
  cellView.Plot2d();

  app.Run(true);
}
