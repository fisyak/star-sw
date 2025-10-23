#include <TApplication.h>

#include "Garfield/ComponentNeBem3d.hh"
#include "Garfield/GeometrySimple.hh"
#include "Garfield/MediumSilicon.hh"
#include "Garfield/SolidBox.hh"
#include "Garfield/ViewField.hh"

using namespace Garfield;

int main(int argc, char* argv[]) {
  TApplication app("app", &argc, argv);

  MediumSilicon si;

  // Geometry.
  GeometrySimple geo;
  SolidBox box1(0, 0, -0.5, 5, 5, 0.1);
  box1.SetBoundaryPotential(1000.);
  box1.SetLabel("readout");
  SolidBox box2(0, 0, 0.5, 5, 5, 0.1);
  box2.SetBoundaryPotential(0.);
  geo.AddSolid(&box1, &si);
  geo.AddSolid(&box2, &si);

  ComponentNeBem3d nebem;
  nebem.SetGeometry(&geo);
  nebem.SetTargetElementSize(1.);
  nebem.EnableDebugging();
  nebem.Initialise();

  Medium* medium = nullptr;
  double ex = 0., ey = 0., ez = 0., v = 0.;
  int status = 0;
  nebem.ElectricField(0, 0, 0, ex, ey, ez, v, medium, status);
  std::printf("E = (%15.8f, %15.8f %15.8f), V = %15.8f, status = %d\n", ex, ey,
              ez, v, status);

  double wx, wy, wz;
  nebem.WeightingField(0, 0, 0, wx, wy, wz, "readout");
  std::printf("Ew = (%15.8f, %15.8f %15.8f)\n", wx, wy, wz);
  double vw = nebem.WeightingPotential(0, 0, 0, "readout");
  std::printf("Vw = %15.8f\n", vw);

  ViewField fieldView(&nebem);
  fieldView.SetArea(-10, -10, -1, 10, 10, 2);
  fieldView.SetPlane(0, 0, 1, 0, 0, 0.2);
  fieldView.PlotContourWeightingField("readout", "v");

  app.Run(true);
}
