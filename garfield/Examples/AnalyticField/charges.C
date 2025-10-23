#include <TApplication.h>

#include "Garfield/ComponentAnalyticField.hh"
#include "Garfield/MediumMagboltz.hh"
#include "Garfield/ViewCell.hh"
#include "Garfield/ViewField.hh"

using namespace Garfield;

int main(int argc, char* argv[]) {
  TApplication app("app", &argc, argv);

  // Gas mixture.
  MediumMagboltz gas("Ar", 80., "CO2", 20.);

  // Define the cell layout.
  constexpr double gap = 0.1;
  ComponentAnalyticField cmp;
  cmp.SetMedium(&gas);
  cmp.AddPlaneY(0., 0.);
  cmp.AddPlaneY(gap, 10.e3);
  cmp.AddCharge(0., 0.5 * gap, 0., 5.e6 * ElementaryCharge);

  // Plot isopotential contours.
  ViewField fieldView(&cmp);
  constexpr double xmin = -gap;
  constexpr double xmax = +gap;
  fieldView.SetArea(xmin, 0., xmax, gap);
  fieldView.PlotContour();

  // Plot the cell layout.
  ViewCell cellView(&cmp);
  cellView.SetCanvas(fieldView.GetCanvas());
  cellView.SetArea(xmin, 0., xmax, gap);
  cellView.Plot2d();

  app.Run(true);
}
