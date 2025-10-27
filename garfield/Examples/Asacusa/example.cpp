#include <TApplication.h>
#include <TCanvas.h>
#include <TStyle.h>

#include <iostream>

#include "Garfield/AvalancheMicroscopic.hh"
#include "Garfield/ComponentAnalyticField.hh"
#include "Garfield/MediumMagboltz.hh"
#include "Garfield/Sensor.hh"
#include "Garfield/TrackHeed.hh"
#include "Garfield/ViewDrift.hh"
#include "Garfield/ViewField.hh"

using namespace Garfield;

int main(int argc, char* argv[]) {
  TApplication app("app", &argc, argv);

  // Set the gas mixture.
  MediumMagboltz gas("ar", 90., "c4h10", 10.);

  // Build the Micromegas geometry.
  // We use separate components for drift and amplification regions.
  ComponentAnalyticField cmpD;
  ComponentAnalyticField cmpA;
  cmpD.SetMedium(&gas);
  cmpA.SetMedium(&gas);
  // Set the magnetic field [Tesla].
  constexpr double bfield = 2.;
  cmpD.SetMagneticField(0, 0, bfield);
  cmpA.SetMagneticField(0, 0, bfield);

  // 100 um amplification gap.
  constexpr double yMesh = 0.01;
  constexpr double vMesh = -500.;
  cmpA.AddPlaneY(yMesh, vMesh, "mesh");
  cmpA.AddPlaneY(0., 0., "bottom");

  // 3 mm drift gap.
  constexpr double yDrift = yMesh + 0.3;
  constexpr double vDrift = -3000.;
  cmpD.AddPlaneY(yDrift, vDrift, "top");
  cmpD.AddPlaneY(yMesh, vMesh, "mesh");

  // We place three strips along z direction on the anode plane
  // in order to be able to resolve the avalanche signal.
  // Strip pitch [cm].
  constexpr double pitch = 0.07;
  // Distance between two strips [cm].
  constexpr double interstrip = 0.01;
  // Half-width of a strip.
  constexpr double hw = 0.5 * (pitch - interstrip);
  const double xStrip1 = hw;
  cmpA.AddStripOnPlaneY('z', 0., xStrip1 - hw, xStrip1 + hw, "strip1");
  const double xStrip2 = xStrip1 + pitch;
  cmpA.AddStripOnPlaneY('z', 0., xStrip2 - hw, xStrip2 + hw, "strip2");
  const double xStrip3 = xStrip2 + pitch;
  cmpA.AddStripOnPlaneY('z', 0., xStrip3 - hw, xStrip3 + hw, "strip3");

  // Assemble a sensor.
  Sensor sensor;
  sensor.AddComponent(&cmpD);
  sensor.AddComponent(&cmpA);
  sensor.SetArea(0., 0., -1., 5 * pitch, yDrift, 1.);

  // Request signal calculation for the strip electrodes.
  sensor.AddElectrode(&cmpA, "strip1");
  sensor.AddElectrode(&cmpA, "strip2");
  sensor.AddElectrode(&cmpA, "strip3");

  // Set the time window [ns] for the signal calculation.
  const double tMin = 0.;
  const double tMax = 100.;
  const double tStep = 0.05;
  const int nTimeBins = int((tMax - tMin) / tStep);
  sensor.SetTimeWindow(0., tStep, nTimeBins);

  // We use microscopic tracking for simulating the electron avalanche.
  AvalancheMicroscopic aval(&sensor);

  // Simulate an ionizing particle (negative pion) using Heed.
  TrackHeed track(&sensor);
  track.SetParticle("pi-");
  constexpr double momentum = 300.e6;  // [eV / c]
  track.SetMomentum(momentum);
  track.EnableMagneticField();
  // track.EnableElectricField();

  // Construct a viewer to visualise the drift lines.
  ViewDrift driftView;
  track.EnablePlotting(&driftView);
  aval.EnablePlotting(&driftView);
  aval.EnableExcitationMarkers(false);
  aval.EnableIonisationMarkers(false);

  // Set the starting point of the incoming ionising track.
  double xt = 0.05;  // [cm]
  double yt = yDrift;
  double zt = 0.0;

  // Now simulate a track.
  track.NewTrack(xt, yt, zt, 0, 0, -1, 0);
  // Loop over the clusters.
  for (const auto& cluster : track.GetClusters()) {
    for (const auto& electron : cluster.electrons) {
      // Simulate the drift/avalanche of this electron.
      aval.AvalancheElectron(electron.x, electron.y, electron.z, electron.t,
                             0.1, 0., 0., 0.);
      // Get the end point of the initial electron's trajectory.
      const auto& p1 = aval.GetElectrons().front().path.back();
      // Skip electrons that didn't hit the mesh plane.
      if (fabs(p1.y - yMesh) > 1.e-6) continue;
      // Move the electron into the amplification gap.
      aval.AvalancheElectron(p1.x, yMesh - 1.e-6, p1.z, p1.t, p1.energy, 0, -1.,
                             0.);
    }
  }

  // Calculate the accumulated charge on each strip.
  sensor.IntegrateSignals();
  const double q1 = sensor.GetSignal("strip1", nTimeBins - 1);
  const double q2 = sensor.GetSignal("strip2", nTimeBins - 1);
  const double q3 = sensor.GetSignal("strip3", nTimeBins - 1);

  // Now calculate the reconstructed pion position in the Micromegas
  // using the weighted average of the strip signals.
  const double sum = q1 + q2 + q3;
  double mean = (q1 * xStrip1 + q2 * xStrip2 + q3 * xStrip3) / sum;
  const double res = fabs(xt - mean) * 10000.0;
  std::cout << "---------------------------\n";
  std::cout << "XMean: " << mean << " cm, XTrue: " << xt << " cm\n";
  std::cout << "XTrue - XMean: " << res << " um\n";
  std::cout << "---------------------------\n";

  // Plotting
  // This canvas will be used to display the drift lines and the field
  gStyle->SetPadRightMargin(0.15);
  TCanvas* c1 = new TCanvas("c1", "", 1400, 600);
  c1->Divide(2, 1);

  // Plot the drift lines.
  driftView.SetArea(0.0, 0.0, 0.2, yDrift);
  driftView.SetClusterMarkerSize(0.1);
  driftView.SetCollisionMarkerSize(0.5);
  driftView.SetCanvas((TPad*)c1->cd(1));
  driftView.Plot(true);
  // Plot the potential.
  ViewField fieldView(&sensor);
  fieldView.SetCanvas((TPad*)c1->cd(2));
  fieldView.Plot("v", "cont1z");

  c1->SaveAs("plot.pdf");
  app.Run();
  return 0;
}
