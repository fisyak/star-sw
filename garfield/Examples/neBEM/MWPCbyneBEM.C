#include <TApplication.h>

#include "Garfield/ComponentNeBem3d.hh"
#include "Garfield/GeometrySimple.hh"
#include "Garfield/MediumConductor.hh"
#include "Garfield/MediumMagboltz.hh"
#include "Garfield/SolidBox.hh"
#include "Garfield/SolidWire.hh"
#include "Garfield/ViewField.hh"
#include "Garfield/ViewGeometry.hh"

using namespace Garfield;

int main(int argc, char* argv[]) {
  TApplication app("app", &argc, argv);

  MediumMagboltz gas("He", 87.5, "CF4", 12.5);
  MediumConductor Cu;

  // Geometry.
  GeometrySimple geo;

  SolidBox box1(0, 0, -0.5, 5., 5., 0.1);
  box1.SetBoundaryPotential(0.);
  SolidBox box2(0, 0, 0.5, 5., 5., 0.1);
  box2.SetBoundaryPotential(0.);
  geo.AddSolid(&box1, &Cu);
  geo.AddSolid(&box2, &Cu);

  const double radius = 0.1;
  const double halflength = 5.;

  std::vector<SolidWire*> wires(5, nullptr);
  for (int i = 0; i < 5; ++i) {
    int j = i - 2;
    double xpos = 0.0 + (double)j * 1.;
    wires[i] = new SolidWire(xpos, 0.0, 0.0, radius, halflength, 0, 1, 0);
    wires[i]->SetBoundaryPotential(1000.0);
    geo.AddSolid(wires[i], &Cu);
  }

  ComponentNeBem3d nebem;
  nebem.SetGeometry(&geo);
  nebem.SetTargetElementSize(0.1);
  nebem.SetMinMaxNumberOfElements(3, 15);
  nebem.EnableDebugging();
  nebem.Initialise();

  Medium* medium = nullptr;
  double ex = 0., ey = 0., ez = 0., v = 0.;
  int status = 0;
  nebem.ElectricField(0, 0, 0, ex, ey, ez, v, medium, status);
  std::printf("E = (%15.8f, %15.8f %15.8f), V = %15.8f, status = %d\n", ex, ey,
              ez, v, status);

  // Plot device geometry in 2D
  ViewGeometry geomView2d(&geo);
  geomView2d.SetArea(-10, -10, -1, 10, 10, 2);
  geomView2d.SetPlane(0, 1, 0, 0, 0, 0.0);
  geomView2d.Plot2d();

  // Plot device geometry in 3D
  ViewGeometry geomView3d(&geo);
  geomView3d.Plot();

  // Plot potential contour
  ViewField potView(&nebem);
  potView.SetArea(-5, -5, -.1, 5, 5, .1);
  potView.SetPlane(0, 1, 0, 0, 0, 0.0);
  potView.PlotContour();

  // Plot field contour
  ViewField fieldView(&nebem);
  fieldView.SetArea(-5, -5, -.1, 5, 5, .1);
  fieldView.SetPlane(0, 1, 0, 0, 0, 0.0);
  fieldView.PlotContour("e");

  app.Run(true);
}
