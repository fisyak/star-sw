#include <TApplication.h>
#include <TCanvas.h>

#include <vector>

#include "Garfield/ComponentAnalyticField.hh"
#include "Garfield/MediumMagboltz.hh"
#include "Garfield/ViewCell.hh"
#include "Garfield/ViewField.hh"

using namespace Garfield;

int main(int argc, char* argv[]) {
  TApplication app("app", &argc, argv);

  MediumMagboltz gas("ar", 90., "ch4", 10.);

  // Setup the cell.
  ComponentAnalyticField cmp;
  cmp.SetMedium(&gas);

  const double gap = 0.5;
  cmp.AddPlaneY(0., 0.);
  cmp.AddPlaneY(gap, 0.);

  const double yw = 0.5 * gap;
  // Wire diameter [cm].
  const double dw = 30.e-4;
  // Potential of the wires [V].
  const double vw = 2650.;
  cmp.AddWire(0., yw, dw, vw, "s");
  // Set the periodic length.
  const double pitch = 0.2;
  cmp.SetPeriodicityX(pitch);
  cmp.PrintCell();

  // Plot the potential.
  ViewField fieldView(&cmp);
  const double xmin = -2.5 * pitch;
  const double xmax = 2.5 * pitch;
  fieldView.SetArea(xmin, 0., xmax, gap);

  TCanvas c1("c1", "", 600, 600);
  fieldView.SetCanvas(&c1);
  fieldView.PlotContour();

  ViewCell cellView(&cmp);
  cellView.SetCanvas(fieldView.GetCanvas());
  cellView.SetArea(xmin, 0., xmax, gap);
  cellView.Plot2d();

  // Plot field lines.
  TCanvas c2("c2", "", 600, 600);
  fieldView.SetCanvas(&c2);
  std::vector<double> xf;
  std::vector<double> yf;
  std::vector<double> zf;
  const double dx = 0.01 * (xmax - xmin);
  fieldView.EqualFluxIntervals(xmin + dx, gap, 0., xmax - dx, gap, 0., xf, yf,
                               zf, 50);
  fieldView.PlotFieldLines(xf, yf, zf, true, false);
  fieldView.EqualFluxIntervals(xmin + dx, 0., 0., xmax - dx, 0., 0., xf, yf, zf,
                               50);
  fieldView.PlotFieldLines(xf, yf, zf, true, false);
  cellView.SetCanvas(fieldView.GetCanvas());
  cellView.Plot2d();

  app.Run(true);
}
