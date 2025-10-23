#include <TApplication.h>
#include <TCanvas.h>
#include <TSystem.h>

#include "Garfield/ComponentAnalyticField.hh"
#include "Garfield/MediumMagboltz.hh"
#include "Garfield/ViewCell.hh"
#include "Garfield/ViewField.hh"

using namespace Garfield;

int main(int argc, char* argv[]) {
  TApplication app("app", &argc, argv);

  // Setup the gas.
  MediumMagboltz gas("ar");

  // Setup the cell layout.
  ComponentAnalyticField cmp;
  cmp.SetMedium(&gas);
  cmp.AddPlaneY(-1., 0.);
  cmp.AddPlaneY(+1., 2000.);
  cmp.AddWire(0., 0., 1., 1000.);
  cmp.EnableDipoleTerms();
  cmp.PrintCell();

  // Plot the potential.
  TCanvas canvas("c", "", 600, 600);
  ViewCell cellView(&cmp);
  cellView.SetCanvas(&canvas);
  cellView.EnableWireMarkers(false);
  cellView.SetArea(-1.1, -1.1, 1.1, 1.1);
  ViewField fieldView(&cmp);
  fieldView.SetCanvas(&canvas);
  fieldView.SetArea(-1.1, -1.1, 1.1, 1.1);
  fieldView.Plot("v", "cont1z");
  cellView.Plot2d();
  gSystem->ProcessEvents();
  app.Run();
}
