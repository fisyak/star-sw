#include <TApplication.h>

#include "Garfield/ComponentNeBem3d.hh"
#include "Garfield/GeometrySimple.hh"
#include "Garfield/MediumMagboltz.hh"
#include "Garfield/MediumSilicon.hh"
#include "Garfield/SolidBox.hh"
#include "Garfield/ViewField.hh"

using namespace Garfield;

int main(int argc, char* argv[]) {
  TApplication app("app", &argc, argv);

  MediumMagboltz gas("He", 87.5, "CF4", 12.5);
  MediumSilicon si;

  // Geometry.
  GeometrySimple geo;

  SolidBox box1(0, 0, -0.5, 5, 5, 0.1);
  box1.SetBoundaryPotential(1000.);
  SolidBox box2(0, 0, 0.5, 5, 5, 0.1);
  box2.SetBoundaryPotential(0.);
  geo.AddSolid(&box1, &si);
  geo.AddSolid(&box2, &si);

  ComponentNeBem3d nebem;
  nebem.SetGeometry(&geo);
  nebem.SetTargetElementSize(1.);
  nebem.EnableDebugging();
  nebem.Initialise();

  const auto efield = nebem.ElectricField(0, 0, 0);
  const double v = nebem.ElectricPotential(0, 0, 0);
  std::printf("E = (%15.8f, %15.8f %15.8f), V = %15.8f\n", efield[0], efield[1],
              efield[2], v);

  ViewField fieldView(&nebem);
  fieldView.SetArea(-10, -10, -1, 10, 10, 2);
  fieldView.SetPlane(0, 0, 1, 0, 0, 0.2);
  fieldView.PlotContour();

  app.Run(true);
}
