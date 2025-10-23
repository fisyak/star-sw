#include <TApplication.h>
#include <TCanvas.h>
#include <TSystem.h>

#include <fstream>
#include <iostream>

#include "Garfield/AvalancheMC.hh"
#include "Garfield/ComponentAnalyticField.hh"
#include "Garfield/ComponentConstant.hh"
#include "Garfield/ComponentUser.hh"
#include "Garfield/MediumSilicon.hh"
#include "Garfield/Random.hh"
#include "Garfield/Sensor.hh"
#include "Garfield/TrackHeed.hh"
#include "Garfield/ViewDrift.hh"
#include "Garfield/ViewField.hh"

using namespace Garfield;

int main(int argc, char* argv[]) {
  TApplication app("app", &argc, argv);

  // Define the medium.
  MediumSilicon si;
  si.SetTemperature(293.);

  // Make a plot of the drift velocities.
  constexpr bool plotVelocity = true;
  if (plotVelocity) {
    si.PlotVelocity("eh", new TCanvas("cM", "", 600, 600));
  }

  // Sensor thickness [cm]
  constexpr double d = 100.e-4;

  // Make a component with constant drift field and weighting field.
  // Bias voltage [V]
  constexpr double vbias = -50.;
  ComponentConstant uniformField;
  uniformField.SetArea(-2 * d, 0., -2 * d, 2 * d, d, 2 * d);
  uniformField.SetMedium(&si);
  uniformField.SetElectricField(0, vbias / d, 0);
  uniformField.SetWeightingField(0, -1. / d, 0, "pad");

  // Depletion voltage [V]
  constexpr double vdep = -20.;
  // Make a component with linear drift field.
  auto eLinear = [d, vbias, vdep](const double /*x*/, const double y,
                                  const double /*z*/, double& ex, double& ey,
                                  double& ez) {
    ex = ez = 0.;
    ey = (vbias - vdep) / d + 2 * y * vdep / (d * d);
  };
  ComponentUser linearField;
  linearField.SetArea(-2 * d, 0., -2 * d, 2 * d, d, 2 * d);
  linearField.SetMedium(&si);
  linearField.SetElectricField(eLinear);
  // std::string efield = "ey = " + std::to_string((vbias - vdep) / d) +
  //                      " + 2 * y * " + std::to_string(vdep / (d * d));
  // linearField.SetElectricField(efield);

  // Make a component with analytic weighting field for a strip or pixel.
  constexpr double pitch = 55.e-4;
  constexpr double halfpitch = 0.5 * pitch;
  ComponentAnalyticField wField;
  wField.SetMedium(&si);
  wField.AddPlaneY(0, vbias, "back");
  wField.AddPlaneY(d, 0, "front");
  wField.AddStripOnPlaneY('z', d, -halfpitch, halfpitch, "strip");
  wField.AddPixelOnPlaneY(d, -halfpitch, halfpitch, -halfpitch, halfpitch,
                          "pixel");

  // Create a sensor.
  Sensor sensor(&linearField);
  const std::string label = "strip";
  sensor.AddElectrode(&wField, label);

  // Plot the drift field if requested.
  constexpr bool plotField = true;
  if (plotField) {
    ViewField* fieldView = new ViewField(&sensor);
    fieldView->SetArea(-0.5 * d, 0, 0.5 * d, d);
    fieldView->PlotContour("ey");
  }
  // Plot the weighting potential if requested.
  constexpr bool plotWeightingField = true;
  if (plotWeightingField) {
    ViewField* wfieldView = new ViewField(&wField);
    wfieldView->SetArea(-0.5 * d, 0, 0.5 * d, d);
    wfieldView->PlotContourWeightingField("strip", "v");
  }

  // Set the time bins.
  const std::size_t nTimeBins = 1000;
  const double tmin = 0.;
  const double tmax = 10.;
  const double tstep = (tmax - tmin) / nTimeBins;
  sensor.SetTimeWindow(tmin, tstep, nTimeBins);

  // Set up Heed.
  TrackHeed track(&sensor);
  // Set the particle type and momentum [eV/c].
  track.SetParticle("pion");
  track.SetMomentum(180.e9);

  // Simulate electron/hole drift lines using MC integration.
  AvalancheMC drift(&sensor);
  // Use steps of 1 micron.
  drift.SetDistanceSteps(1.e-4);

  // Plot the signal if requested.
  constexpr bool plotSignal = true;
  TCanvas* cSignal = nullptr;
  if (plotSignal) {
    cSignal = new TCanvas("cSignal", "", 600, 600);
  }

  constexpr bool plotDrift = true;
  ViewDrift* driftView = nullptr;
  TCanvas* cDrift = nullptr;
  if (plotDrift) {
    cDrift = new TCanvas("cDrift", "", 600, 600);
    driftView = new ViewDrift();
    driftView->SetArea(-0.5 * d, 0, -0.5 * d, 0.5 * d, d, 0.5 * d);
    driftView->SetCanvas(cDrift);
    track.EnablePlotting(driftView);
  }
  // Flag to randomise the position of the track.
  constexpr bool smearx = true;
  constexpr std::size_t nEvents = 10;
  // Flag to save the signal to a file.
  constexpr bool writeSignal = true;
  for (std::size_t i = 0; i < nEvents; ++i) {
    if (plotDrift) driftView->Clear();
    // Reset the signal.
    sensor.ClearSignal();
    if (i % 10 == 0) std::cout << i << "/" << nEvents << "\n";
    // Simulate a charged-particle track.
    double xt = 0.;
    if (smearx) xt = -0.5 * pitch + RndmUniform() * pitch;
    track.NewTrack(xt, 0, 0, 0, 0, 1, 0);
    // Retrieve the clusters along the track.
    for (const auto& cluster : track.GetClusters()) {
      // Loop over the electrons in the cluster.
      for (const auto& electron : cluster.electrons) {
        // Simulate the electron and hole drift lines.
        if (plotDrift) {
          drift.DisablePlotting();
          if (RndmUniform() < 0.01) drift.EnablePlotting(driftView);
        }
        drift.DriftElectron(electron.x, electron.y, electron.z, electron.t);
        drift.DriftHole(electron.x, electron.y, electron.z, electron.t);
      }
    }
    if (plotSignal) {
      sensor.PlotSignal(label, cSignal);
      cSignal->Update();
      gSystem->ProcessEvents();
    }
    if (plotDrift) {
      constexpr bool twod = true;
      driftView->Plot(twod);
      cDrift->Update();
      gSystem->ProcessEvents();
    }
    // Save the induced current signal to a file.
    if (writeSignal) {
      char filename[50];
      snprintf(filename, 50, "signal_%05zu.txt", i);
      std::ofstream outfile;
      outfile.open(filename, std::ios::out);
      for (std::size_t j = 0; j < nTimeBins; ++j) {
        const double t = (j + 0.5) * tstep;
        const double f = sensor.GetSignal(label, j);
        const double fe = sensor.GetElectronSignal(label, j);
        const double fh = sensor.GetIonSignal(label, j);
        outfile << t << "  " << f << "  " << fe << "  " << fh << "\n";
      }
      outfile.close();
    }
  }

  if (plotVelocity || plotSignal || plotDrift || plotField ||
      plotWeightingField) {
    app.Run();
  }
}
