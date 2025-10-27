#include <TApplication.h>
#include <TCanvas.h>
#include <TSystem.h>

#include "Garfield/ComponentAnalyticField.hh"
#include "Garfield/MediumSilicon.hh"
#include "Garfield/ViewField.hh"

using namespace Garfield;

int main(int argc, char* argv[]) {
  TApplication app("app", &argc, argv);

  MediumSilicon si;

  // Define the cell layout.
  ComponentAnalyticField cmp;
  cmp.SetMedium(&si);
  constexpr double d = 1.;
  cmp.AddPlaneX(0, 0.);
  cmp.AddPlaneX(d, 1.);
  // Pixel on the left-side plane.
  cmp.AddPixelOnPlaneX(0., -0.1, 0.1, -0.2, 0.2, "p1");
  // Pixel on the left-side plane, rotated by 45 degrees.
  cmp.AddPixelOnPlaneX(0., -0.1, 0.1, -0.2, 0.2, "p2", -1, 0.5 * HalfPi);

  // Plot the weighting potential.
  TCanvas canvas("canvas", "", 1000, 500);
  canvas.Divide(2, 1);
  ViewField fieldView(&cmp);
  fieldView.SetPlane(-1., 0., 0., 0.1 * d, 0., 0.);
  fieldView.SetArea(-0.25, -0.25, 0.25, 0.25);
  fieldView.SetCanvas((TPad*)canvas.cd(1));
  fieldView.PlotContourWeightingField("p1", "v");
  fieldView.SetCanvas((TPad*)canvas.cd(2));
  fieldView.PlotContourWeightingField("p2", "v");
  gSystem->ProcessEvents();
  app.Run(true);
}
