#include <TApplication.h>
#include <TCanvas.h>

#include <iostream>

#include "Garfield/AvalancheMC.hh"
#include "Garfield/AvalancheMicroscopic.hh"
#include "Garfield/ComponentAnsys123.hh"
#include "Garfield/MediumMagboltz.hh"
#include "Garfield/Random.hh"
#include "Garfield/Sensor.hh"
#include "Garfield/ViewDrift.hh"
#include "Garfield/ViewFEMesh.hh"
#include "Garfield/ViewField.hh"

using namespace Garfield;

int main(int argc, char* argv[]) {
  TApplication app("app", &argc, argv);

  // Setup the gas.
  MediumMagboltz gas("ar", 80., "co2", 20.);
  gas.SetTemperature(293.15);
  gas.SetPressure(760.);
  gas.Initialise(true);
  // Set the Penning transfer efficiency.
  constexpr double rPenning = 0.51;
  constexpr double lambdaPenning = 0.;
  gas.EnablePenningTransfer(rPenning, lambdaPenning, "ar");
  // Load the ion mobilities.
  gas.LoadIonMobility("IonMobility_Ar+_Ar.txt");

  // Load the field map.
  ComponentAnsys123 fm;
  fm.Initialise("ELIST.lis", "NLIST.lis", "MPLIST.lis", "PRNSOL.lis", "mm");
  fm.EnableMirrorPeriodicityX();
  fm.EnableMirrorPeriodicityY();
  fm.PrintRange();

  // Associate the gas with the corresponding field map material.
  fm.SetGas(&gas);
  fm.PrintMaterials();
  // fm.Check();

  // Dimensions of the GEM [cm]
  constexpr double pitch = 0.014;

  ViewField fieldView(&fm);
  ViewFEMesh meshView(&fm);
  constexpr bool plotField = true;
  if (plotField) {
    // Set the normal vector of the viewing plane (xz plane).
    fieldView.SetPlane(0, -1, 0, 0, 0, 0);
    // Set the plot limits in the current viewing plane.
    fieldView.SetArea(-0.5 * pitch, -0.02, 0.5 * pitch, 0.02);
    fieldView.SetVoltageRange(-160., 160.);
    TCanvas* cf = new TCanvas("cf", "", 600, 600);
    cf->SetLeftMargin(0.16);
    fieldView.SetCanvas(cf);
    fieldView.PlotContour();

    meshView.SetArea(-0.5 * pitch, -0.02, 0.5 * pitch, 0.02);
    meshView.SetCanvas(cf);
    meshView.SetPlane(0, -1, 0, 0, 0, 0);
    meshView.SetFillMesh(true);
    meshView.SetColor(2, kGray);
    meshView.Plot(true);
  }

  // Create the sensor.
  Sensor sensor(&fm);
  sensor.SetArea(-5 * pitch, -5 * pitch, -0.01, 5 * pitch, 5 * pitch, 0.025);

  AvalancheMicroscopic aval(&sensor);

  AvalancheMC drift(&sensor);
  drift.SetDistanceSteps(2.e-4);

  ViewDrift driftView;
  constexpr bool plotDrift = true;
  if (plotDrift) {
    // Plot every tenth collision.
    aval.EnablePlotting(&driftView, 10);
    drift.EnablePlotting(&driftView);
  }

  // Count the total number of ions produced the back-flowing ions.
  std::size_t nTotal = 0;
  std::size_t nBF = 0;
  constexpr std::size_t nEvents = 10;
  for (std::size_t i = 0; i < nEvents; ++i) {
    std::cout << i << "/" << nEvents << "\n";
    // Randomize the initial position.
    const double x0 = -0.5 * pitch + RndmUniform() * pitch;
    const double y0 = -0.5 * pitch + RndmUniform() * pitch;
    const double z0 = 0.02;
    const double t0 = 0.;
    const double e0 = 0.1;
    aval.AvalancheElectron(x0, y0, z0, t0, e0, 0., 0., 0.);
    int ne = 0, ni = 0;
    aval.GetAvalancheSize(ne, ni);
    for (const auto& electron : aval.GetElectrons()) {
      const auto& p0 = electron.path[0];
      drift.DriftIon(p0.x, p0.y, p0.z, p0.t);
      ++nTotal;
      const auto& endpoint = drift.GetIons().front().path.back();
      if (endpoint.z > 0.005) ++nBF;
    }
  }
  std::cout << "Fraction of back-flowing ions: " << double(nBF) / double(nTotal)
            << "\n";
  if (plotDrift) {
    TCanvas* cd = new TCanvas();
    constexpr bool plotMesh = true;
    if (plotMesh) {
      meshView.SetCanvas(cd);
      meshView.SetComponent(&fm);
      constexpr bool twod = true;
      // x-z projection.
      meshView.SetPlane(0, -1, 0, 0, 0, 0);
      if (twod) {
        meshView.SetArea(-2 * pitch, -0.02, 2 * pitch, 0.02);
      } else {
        meshView.SetArea(-0.5 * pitch, -0.5 * pitch, -0.02, 0.5 * pitch,
                         0.5 * pitch, 0.02);
      }
      meshView.SetFillMesh(true);
      meshView.SetColor(0, kGray);
      // Set the color of the kapton.
      meshView.SetColor(2, kYellow + 3);
      meshView.EnableAxes();
      meshView.SetViewDrift(&driftView);
      const bool outline = twod ? false : true;
      meshView.Plot(twod, outline);
    } else {
      driftView.SetPlane(0, -1, 0, 0, 0, 0);
      driftView.SetArea(-2 * pitch, -0.02, 2 * pitch, 0.02);
      driftView.SetCanvas(cd);
      constexpr bool twod = true;
      driftView.Plot(twod);
    }
  }

  app.Run();
}
