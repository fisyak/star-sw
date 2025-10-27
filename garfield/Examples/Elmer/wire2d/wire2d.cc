/**
 * wire2d.cc
 *
 * Demonstrates importing of a 2D Elmer finite element
 * field map.
 *
 */
#include <TApplication.h>
#include <TCanvas.h>

#include <cmath>
#include <iostream>

#include "Garfield/AvalancheMicroscopic.hh"
#include "Garfield/ComponentElmer2d.hh"
#include "Garfield/MediumMagboltz.hh"
#include "Garfield/Random.hh"
#include "Garfield/Sensor.hh"
#include "Garfield/ViewDrift.hh"
#include "Garfield/ViewFEMesh.hh"
#include "Garfield/ViewField.hh"

using namespace Garfield;

int main(int argc, char* argv[]) {
  TApplication app("app", &argc, argv);

  // Set relevant parameters.
  // Wire radius
  const double rwire = 1.0;
  // X-width of drift simulation will cover between +/- axis_x
  const double axis_x = 5;
  // Y-width of drift simulation will cover between +/- axis_y
  const double axis_y = 5;
  const double axis_z = 5;

  // Define the medium (Ar/CO2 70:30).
  MediumMagboltz gas("ar", 70., "co2", 30.);
  // Set the temperature (K).
  gas.SetTemperature(293.15);
  // Set the pressure (Torr).
  gas.SetPressure(740.);

  // Import an Elmer-created field map.
  ComponentElmer2d elm("wire2d/mesh.header", "wire2d/mesh.elements",
                       "wire2d/mesh.nodes", "wire2d/dielectrics.dat",
                       "wire2d/wire2d.result", "cm");
  elm.SetGas(&gas);
  elm.SetRangeZ(-5., 5.);

  // Set up a sensor object.
  Sensor sensor(&elm);
  sensor.SetArea(-axis_x, -axis_y, -axis_z, axis_x, axis_y, axis_z);

  // Create an avalanche object
  AvalancheMicroscopic aval(&sensor);

  // Set up the object for drift line visualization.
  ViewDrift viewDrift;
  viewDrift.SetArea(-axis_x, -axis_y, -axis_z, axis_x, axis_y, axis_z);
  aval.EnablePlotting(&viewDrift, 100);

  // Set the electron start parameters.
  const double zi = 1.0;
  double ri = rwire + 2.0;
  double thetai = RndmUniform() * TwoPi;
  double xi = ri * cos(thetai);
  double yi = ri * sin(thetai);
  // Calculate the avalanche.
  std::cout << "Avalanche of a single electron starting from (" << xi << ", "
            << yi << ", " << zi << ")..." << std::endl;
  aval.AvalancheElectron(xi, yi, zi, 0., 0., 0., 0., 0.);

  std::cout << "... avalanche complete with " << aval.GetElectrons().size()
            << " electron tracks.\n";

  // Plot the geometry, field and drift lines.
  TCanvas* cGeom = new TCanvas("geom", "Geometry/Avalanche/Fields");
  cGeom->SetLeftMargin(0.14);
  const bool plotContours = false;
  if (plotContours) {
    ViewField* vf = new ViewField(&sensor);
    vf->SetCanvas(cGeom);
    vf->SetArea(-axis_x, -axis_y, axis_x, axis_y);
    vf->SetNumberOfContours(40);
    vf->SetNumberOfSamples2d(30, 30);
    vf->SetPlane(0, 0, 1, 0, 0, 0);
    vf->PlotContour("v");
  }

  // Set up the object for FE mesh visualization.
  ViewFEMesh vFE(&elm);
  vFE.SetArea(-axis_x, -axis_z, -axis_y, axis_x, axis_z, axis_y);
  vFE.SetCanvas(cGeom);
  vFE.SetPlane(0, 0, 1, 0, 0, 0);
  vFE.SetFillMesh(true);
  vFE.SetColor(1, kGray);
  if (!plotContours) {
    vFE.EnableAxes();
    vFE.SetXaxisTitle("x (cm)");
    vFE.SetYaxisTitle("y (cm)");
  }
  vFE.SetViewDrift(&viewDrift);
  vFE.Plot();
  app.Run();
  return 0;
}
