#include <TApplication.h>

#include "Garfield/ComponentAnalyticField.hh"
#include "Garfield/MediumMagboltz.hh"
#include "Garfield/ViewCell.hh"
#include "Garfield/ViewField.hh"

using namespace Garfield;

int main(int argc, char* argv[]) {
  TApplication app("app", &argc, argv);

  MediumMagboltz gas("ar");

  ComponentAnalyticField cmp;
  // Outer radius [cm].
  const double ro = 1.;
  // Radial position of the wires [cm].
  const double rw = 0.5;
  // Number of wires.
  const std::size_t nWires = 10;
  const bool polar = false;
  if (polar) {
    // Describe the cell layout in polar coordinates.
    cmp.SetPolarCoordinates();
    cmp.AddPlaneR(ro, 0., "t");
    cmp.AddWire(rw, 0., 50.e-4, 500., "f");
    cmp.SetPeriodicityPhi(360. / nWires);
  } else {
    // Describe the cell layout in Cartesian coordinates,
    // using wires and a circular tube.
    cmp.AddTube(ro, 0., 0, "t");
    for (std::size_t i = 0; i < 10; ++i) {
      const double phi = i * TwoPi / nWires;
      cmp.AddWire(rw * cos(phi), rw * sin(phi), 50.e-4, 500., "f");
    }
  }

  // Plot the potential.
  ViewField fieldView(&cmp);
  fieldView.PlotContour();
  // Superimpose the cell layout.
  ViewCell cellView(&cmp);
  cellView.SetCanvas(fieldView.GetCanvas());
  cellView.Plot2d();
  app.Run();
}
