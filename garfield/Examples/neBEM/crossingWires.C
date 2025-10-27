#include <TApplication.h>

#include "Garfield/ComponentNeBem3d.hh"
#include "Garfield/GeometrySimple.hh"
#include "Garfield/MediumConductor.hh"
#include "Garfield/MediumMagboltz.hh"
#include "Garfield/SolidWire.hh"
#include "Garfield/ViewField.hh"

using namespace Garfield;

int main(int argc, char* argv[]) {
  TApplication app("app", &argc, argv);

  MediumMagboltz gas("ar");
  MediumConductor metal;

  // Geometry.
  GeometrySimple geo;
  const double radius = 0.01;
  const double halflength = 1.;
  SolidWire wire1(0, 0, -0.05, radius, halflength, 1, 0, 0);
  SolidWire wire2(0, 0, +0.05, radius, halflength, 0, 1, 0);
  wire1.SetBoundaryPotential(-1.);
  wire2.SetBoundaryPotential(+1.);
  geo.AddSolid(&wire1, &metal);
  geo.AddSolid(&wire2, &metal);
  geo.SetMedium(&gas);

  ComponentNeBem3d nebem;
  nebem.SetGeometry(&geo);
  nebem.SetTargetElementSize(0.01);
  nebem.UseSVDInversion();
  nebem.Initialise();

  ViewField fieldView(&nebem);
  fieldView.SetArea(-0.25, -0.25, -0.25, 0.25, 0.25, 0.25);
  fieldView.SetPlaneXY();
  fieldView.PlotContour("e");

  app.Run(true);
}
