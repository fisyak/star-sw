#include <TApplication.h>

#include <iostream>

#include "Garfield/ComponentAnalyticField.hh"
#include "Garfield/MediumMagboltz.hh"
#include "Garfield/ViewField.hh"

using namespace Garfield;

int main(int argc, char* argv[]) {
  TApplication app("app", &argc, argv);

  MediumMagboltz gas;

  // Setup the cell.
  ComponentAnalyticField cmp;
  cmp.SetMedium(&gas);
  cmp.AddPlaneY(0., 0., "p");
  cmp.AddPlaneY(2., -250., "q");
  const double ds = 20.e-4;
  const double df = 125.e-4;
  const double dc = 67.e-4;
  const double dg = 67.e-4;
  cmp.AddWire(0.0, 0.4, 0.5 * ds, 1400., "s");
  cmp.AddWire(0.2, 0.4, 0.5 * df, 0., "f");
  for (int i = 0; i < 4; ++i) {
    cmp.AddWire(0.1 * i, 0.8, 0.5 * dc, 0., "c");
  }
  for (int i = 0; i < 2; ++i) {
    cmp.AddWire(0.2 * i, 1.4, 0.5 * dg, 0., "g");
  }
  cmp.SetPeriodicityX(0.4);

  cmp.OptimiseOnTrack({"q"}, "e", 125., -0.2, 1.9, 0.2, 1.9);
  // cmp.OptimiseOnGrid({"q"}, "e", 125., -0.2, 1.9, 0.2, 2.1);

  const auto efield = cmp.ElectricField(0., 1.9, 0.);
  const double emag = sqrt(efield[0] * efield[0] + efield[1] * efield[1]);
  std::cout << "Drift field after optimisation: " << emag << "\n";

  ViewField view(&cmp);
  view.PlotProfile(0.05, 0., 0., 0.05, 2., 0., "e", false);
  app.Run();
}
