#include <TApplication.h>

#include "Garfield/ComponentNeBem3d.hh"
#include "Garfield/GeometrySimple.hh"
#include "Garfield/MediumConductor.hh"
#include "Garfield/MediumMagboltz.hh"
#include "Garfield/MediumPlastic.hh"
#include "Garfield/SolidBox.hh"
#include "Garfield/ViewField.hh"
#include "Garfield/ViewGeometry.hh"

using namespace Garfield;

int main(int argc, char* argv[]) {
  TApplication app("app", &argc, argv);

  MediumMagboltz gas("He", 87.5, "CF4", 12.5);
  MediumConductor graphite;
  MediumPlastic glass;
  glass.SetDielectricConstant(10.0);

  // Geometry.
  GeometrySimple geo;

  SolidBox box1(0, 0, -0.52, 5, 5, 0.01);  // top graphite
  box1.SetBoundaryPotential(1000.);
  geo.AddSolid(&box1, &graphite);
  SolidBox box2(0, 0, -0.5, 5, 5, 0.1);  // top glass
  box2.SetBoundaryDielectric();
  geo.AddSolid(&box2, &glass);
  SolidBox box3(0, 0, 0.5, 5, 5, 0.1);  // bottom glass
  box3.SetBoundaryDielectric();
  geo.AddSolid(&box3, &glass);
  SolidBox box4(0, 0, 0.52, 5, 5, 0.01);  // bottom graphite
  box4.SetBoundaryPotential(-1000.);
  geo.AddSolid(&box4, &graphite);

  SolidBox box5(-5, 0, 0, 0.1, 5, 0.4);  // side spacer 1
  box5.SetBoundaryDielectric();
  geo.AddSolid(&box5, &glass);
  SolidBox box6(5, 0, 0, 0.1, 5, 0.4);  // side spacer 2
  box6.SetBoundaryDielectric();
  geo.AddSolid(&box6, &glass);
  SolidBox box7(0., -5., 0., 4.9, 0.1, 0.4);  // side spacer 3
  box7.SetBoundaryDielectric();
  geo.AddSolid(&box7, &glass);
  SolidBox box8(0., 5., 0., 4.9, 0.1, 0.4);  // side spacer 4
  box8.SetBoundaryDielectric();
  geo.AddSolid(&box8, &glass);

  ComponentNeBem3d nebem;
  nebem.SetGeometry(&geo);
  nebem.SetTargetElementSize(0.05);
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
  geomView2d.SetArea(-5, -5, -1, 5, 5, 1);
  geomView2d.SetPlane(0, 1, 0, 0, 0, 0.0);
  geomView2d.Plot2d();

  // Plot device geometry in 3D
  ViewGeometry geomView3d(&geo);
  geomView3d.Plot();

  // Plot potential contour
  ViewField potView;
  potView.SetComponent(&nebem);
  potView.SetArea(-5, -5, -1, 5, 5, 1);
  potView.SetPlane(0, 1, 0, 0, 0, 0.0);
  potView.PlotContour();

  // Plot potential contour
  ViewField fieldView(&nebem);
  fieldView.SetArea(-5, -5, -1, 5, 5, 1);
  fieldView.SetPlane(0, 1, 0, 0, 0, 0.0);
  fieldView.PlotContour("e");

  app.Run(true);
}
