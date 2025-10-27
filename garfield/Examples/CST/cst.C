#include <TApplication.h>
#include <TCanvas.h>

#include <iostream>

#include "Garfield/AvalancheMC.hh"
#include "Garfield/AvalancheMicroscopic.hh"
#include "Garfield/ComponentCST.hh"
#include "Garfield/MediumMagboltz.hh"
#include "Garfield/Random.hh"
#include "Garfield/Sensor.hh"
#include "Garfield/ViewDrift.hh"
#include "Garfield/ViewFEMesh.hh"
#include "Garfield/ViewField.hh"

using namespace Garfield;

int main(int argc, char* argv[]) {
  TApplication app("app", &argc, argv);

  // Load the field map.
  Garfield::ComponentCST fm;
  fm.Initialise("drift_std_200_320_2500.efm", "m");
  fm.EnableMirrorPeriodicityX();
  fm.EnableMirrorPeriodicityY();
  fm.PrintRange();

  // Dimensions of the GEM [cm]
  constexpr double pitch = 0.014;

  ViewField fieldView(&fm);
  constexpr bool plotField = true;
  if (plotField) {
    fieldView.SetPlaneXZ();
    // Set the plot limits in the current viewing plane.
    fieldView.SetArea(-0.5 * pitch, -0.02, 0.5 * pitch, 0.02);
    TCanvas* cf = new TCanvas("cf", "", 600, 600);
    cf->SetLeftMargin(0.16);
    fieldView.SetCanvas(cf);
    fieldView.PlotContour();
  }

  // Setup the gas.
  MediumMagboltz gas("ar", 95., "ch4", 5.);
  gas.SetTemperature(293.15);
  gas.SetPressure(760.);
  gas.Initialise();

  // Load the ion mobilities.
  gas.LoadIonMobility("IonMobility_Ar+_Ar.txt");
  // Associate the gas with the corresponding field map material.
  fm.SetGas(&gas);
  fm.PrintMaterials();

  // Create the sensor.
  Sensor sensor(&fm);
  sensor.SetArea(-5 * pitch, -5 * pitch, -0.01, 5 * pitch, 5 * pitch, 0.025);
  AvalancheMicroscopic aval(&sensor);

  AvalancheMC drift(&sensor);
  drift.SetDistanceSteps(2.e-4);

  ViewDrift driftView;
  constexpr bool plotDrift = true;
  if (plotDrift) {
    aval.EnablePlotting(&driftView);
    drift.EnablePlotting(&driftView);
  }

  constexpr std::size_t nEvents = 1;
  for (std::size_t i = 0; i < nEvents; ++i) {
    std::cout << i << "/" << nEvents << "\n";
    // Randomize the initial position.
    const double x0 = -0.5 * pitch + RndmUniform() * pitch;
    const double y0 = 0.;
    const double z0 = 0.02;
    const double t0 = 0.;
    const double e0 = 0.1;
    aval.AvalancheElectron(x0, y0, z0, t0, e0, 0., 0., 0.);
    for (const auto& electron : aval.GetElectrons()) {
      const auto& p0 = electron.path[0];
      drift.DriftIon(p0.x, p0.y, p0.z, p0.t);
    }
  }

  if (plotDrift) {
    TCanvas* cd = new TCanvas();
    constexpr bool plotMesh = true;
    if (plotMesh) {
      ViewFEMesh* meshView = new ViewFEMesh(&fm);
      meshView->SetArea(-2 * pitch, -2 * pitch, -0.02, 2 * pitch, 2 * pitch,
                        0.02);
      meshView->SetCanvas(cd);
      // x-z projection.
      meshView->SetPlane(0, -1, 0, 0, 0, 0);
      meshView->SetFillMesh(true);
      // Set the colors of the metal and the kapton.
      meshView->SetColor(1, kGray);
      meshView->SetColor(2, kYellow + 3);
      meshView->EnableAxes();
      meshView->SetViewDrift(&driftView);
      meshView->Plot();
    } else {
      driftView.SetPlaneXZ();
      driftView.SetArea(-2 * pitch, -0.02, 2 * pitch, 0.02);
      driftView.SetCanvas(cd);
      constexpr bool twod = true;
      driftView.Plot(twod);
    }
  }

  app.Run(true);
}
