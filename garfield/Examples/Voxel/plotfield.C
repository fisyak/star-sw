#include <TApplication.h>

#include "Garfield/ComponentVoxel.hh"
#include "Garfield/MediumSilicon.hh"
#include "Garfield/Sensor.hh"
#include "Garfield/ViewField.hh"

using namespace Garfield;

int main(int argc, char *argv[]) {
  TApplication app("app", &argc, argv);

  // Define the medium.
  MediumSilicon si;

  // Setup the mesh.
  const std::size_t nX = 2 * 110 + 1;
  const std::size_t nY = 2 * 200 + 1;
  const double xMin = -0.5e-4;
  const double xMax = 110.5e-4;
  const double yMin = -0.5e-4;
  const double yMax = 200.5e-4;
  const double zMin = -100.e-4;
  const double zMax = 100.e-4;

  ComponentVoxel efield;
  efield.SetMesh(nX, nY, 1, xMin, xMax, yMin, yMax, zMin, zMax);
  // Load the field map.
  efield.LoadElectricField("Efield.txt", "XY", false, false, 1.0e-4);
  efield.EnablePeriodicityX();
  efield.SetMedium(0, &si);
  efield.PrintRegions();
  efield.EnableInterpolation();

  // Create a sensor.
  Sensor sensor(&efield);
  sensor.SetArea(0., 0., -100.e-4, 110.e-4, 200.e-4, 100.e-4);

  ViewField view(&sensor);
  view.SetElectricFieldRange(0.0, 200000.0);
  view.PlotContour("e");
  app.Run();
}
