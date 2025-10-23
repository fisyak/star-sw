/**
 * parallel_plate.cc
 * General program flow based on example code from the Garfield++ website.
 *
 * Demonstrates the importing of a parallel-plate capacitor field map
 * from Gmsh/Elmer into Garfield++.
 *
 */
#include <TApplication.h>
#include <TCanvas.h>

#include "Garfield/ComponentElmer.hh"
#include "Garfield/MediumMagboltz.hh"
#include "Garfield/Sensor.hh"
#include "Garfield/ViewFEMesh.hh"
#include "Garfield/ViewField.hh"

using namespace Garfield;

int main(int argc, char* argv[]) {
  TApplication app("app", &argc, argv);

  // Set relevant geometric parameters.
  const double ext_x = 1.0;  // external box x-width
  const double ext_y = 1.0;  // external box y-width
  const double ext_z = 1.0;  // external box z-width

  // Create a main canvas.
  TCanvas* c1 = new TCanvas();

  // Define the medium (Ar/CO2 70:30).
  MediumMagboltz gas("ar", 70., "co2", 30.);
  // Set the temperature [K] ad pressure [Torr].
  gas.SetTemperature(293.15);
  gas.SetPressure(740.);

  // Import an Elmer-created parallel plate field map.
  ComponentElmer elm(
      "parallel_plate/mesh.header", "parallel_plate/mesh.elements",
      "parallel_plate/mesh.nodes", "parallel_plate/dielectrics.dat",
      "parallel_plate/parallel_plate.result", "cm");
  elm.SetGas(&gas);

  // Set up a sensor object.
  Sensor sensor(&elm);
  sensor.SetArea(-ext_x, -ext_y, -ext_z, ext_x, ext_y, ext_z);

  // Set up the object for field visualization.
  ViewField vf(&sensor);
  vf.SetCanvas(c1);
  vf.SetArea(-ext_x, -ext_y, ext_x, ext_y);
  vf.SetNumberOfContours(20);
  vf.SetNumberOfSamples2d(30, 30);
  vf.SetPlane(0, -1, 0, 0, 0, 0);

  // Set up the object for FE mesh visualization.
  ViewFEMesh vFE(&elm);
  vFE.SetCanvas(c1);
  vFE.SetPlane(0, 0, -1, 0, 0, 0);
  vFE.SetFillMesh(true);
  vFE.SetColor(1, kBlue);

  // Create plots.
  vFE.SetArea(-ext_x, -ext_z, -ext_z, ext_x, ext_z, ext_z);
  vf.PlotContour("v");
  // vFE.Plot();

  app.Run();

  return 0;
}
