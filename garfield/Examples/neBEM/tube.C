#include <TApplication.h>

#include "Garfield/ComponentNeBem3d.hh"
#include "Garfield/GeometrySimple.hh"
#include "Garfield/MediumConductor.hh"
#include "Garfield/MediumMagboltz.hh"
#include "Garfield/SolidTube.hh"
#include "Garfield/SolidWire.hh"
#include "Garfield/ViewField.hh"

using namespace Garfield;

int main(int argc, char* argv[]) {
  TApplication app("app", &argc, argv);

  MediumMagboltz gas("ar");
  MediumConductor metal;

  // Geometry.
  GeometrySimple geo;
  const double rTube = 1.;
  const double lTube = 2.;
  SolidTube tube(0, 0, 0, rTube, 0.5 * lTube, 0, 1, 0);
  tube.SetBoundaryPotential(0.);
  const bool closed = true;
  tube.SetTopLid(closed);
  tube.SetBottomLid(closed);
  const double rWire = 25.e-4;
  const double lWire = 0.9 * lTube;
  SolidWire wire(0, 0, 0, rWire, 0.5 * lWire, 0, 1, 0);
  wire.SetBoundaryPotential(2500.);
  geo.AddSolid(&tube, &metal);
  geo.AddSolid(&wire, &metal);
  geo.SetMedium(&gas);

  ComponentNeBem3d nebem;
  nebem.SetGeometry(&geo);
  nebem.SetTargetElementSize(0.1);
  nebem.UseSVDInversion();
  nebem.Initialise();

  ViewField fieldView(&nebem);
  fieldView.SetArea(-1.1 * rTube, -0.6 * lTube, -1.1 * rTube, 1.1 * rTube,
                    0.6 * lTube, 1.1 * rTube);
  fieldView.SetPlaneXY();
  fieldView.Plot("v", "colz");

  app.Run(true);
}
