#include <TApplication.h>

#include "Garfield/ComponentGrid.hh"
#include "Garfield/MediumSilicon.hh"
#include "Garfield/Sensor.hh"
#include "Garfield/ViewField.hh"

using namespace Garfield;

int main(int argc, char *argv[]) {
  TApplication app("app", &argc, argv);

  // Define the medium.
  MediumSilicon si;

  // Load the field map.
  ComponentGrid efield;
  efield.LoadElectricField("Efield.txt", "XY", false, false, 1.e-4);
  efield.EnablePeriodicityX();
  efield.SetMedium(&si);

  // Create a sensor.
  Sensor sensor(&efield);

  ViewField view(&sensor);
  view.SetElectricFieldRange(0.0, 200000.0);
  // Get the mesh parameters.
  std::size_t nx = 0, ny = 0, nz = 0;
  double xMin = 0., yMin = 0., zMin = 0., xMax = 0., yMax = 0., zMax = 0.;
  efield.GetMesh(nx, ny, nz, xMin, xMax, yMin, yMax, zMin, zMax);
  view.SetArea(-xMax, yMin, xMax, yMax);
  view.PlotContour("e");
  app.Run(true);
}
