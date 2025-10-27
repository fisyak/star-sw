#include <TApplication.h>
#include <TCanvas.h>
#include <TSystem.h>

#include <iostream>

#include "Garfield/AvalancheMC.hh"
#include "Garfield/ComponentAnalyticField.hh"
#include "Garfield/ComponentUser.hh"
#include "Garfield/MediumSilicon.hh"
#include "Garfield/Random.hh"
#include "Garfield/Sensor.hh"
#include "Garfield/TrackHeed.hh"
#include "Garfield/ViewDrift.hh"
#include "Garfield/ViewSignal.hh"

using namespace Garfield;

int main(int argc, char* argv[]) {
  TApplication app("app", &argc, argv);
  // plottingEngine.SetSerif();

  // Define the medium.
  MediumSilicon si;
  si.SetTemperature(293.);

  // Sensor thickness [cm]
  constexpr double d = 100.e-4;
  // Bias voltage [V]
  constexpr double vbias = -50.;
  // Make a component with linear drift field.
  auto eLinear = [](const double /*x*/, const double y, const double /*z*/,
                    double& ex, double& ey, double& ez) {
    // Depletion voltage [V]
    constexpr double vdep = -20.;
    ex = ez = 0.;
    ey = (vbias - vdep) / d + 2 * y * vdep / (d * d);
  };
  ComponentUser linearField;
  linearField.SetArea(-2 * d, 0., -2 * d, 2 * d, d, 2 * d);
  linearField.SetMedium(&si);
  linearField.SetElectricField(eLinear);

  // Make a component with analytic weighting field for a strip or pixel.
  constexpr double pitch = 55.e-4;
  ComponentAnalyticField wField;
  wField.SetMedium(&si);
  wField.AddPlaneY(0, vbias, "back");
  wField.AddPlaneY(d, 0, "front");
  wField.AddStripOnPlaneY('z', d, -0.5 * pitch, 0. * pitch, "strip");

  // Create a sensor.
  Sensor sensor(&linearField);
  // const std::string label = "strip";
  const std::string label = "front";
  sensor.AddElectrode(&wField, label);

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

  ViewDrift driftView;
  driftView.SetArea(-0.5 * d, 0, -0.5 * d, 0.5 * d, d, 0.5 * d);
  track.EnablePlotting(&driftView);
  drift.EnablePlotting(&driftView);

  ViewSignal signalView(&sensor);

  TCanvas canvas("c", "", 1400, 600);
  canvas.Divide(2, 1);
  auto pad1 = canvas.cd(1);
  auto pad2 = canvas.cd(2);
  driftView.SetCanvas((TPad*)canvas.cd(1));
  signalView.SetCanvas((TPad*)canvas.cd(2));

  // Flag to randomise the position of the track.
  constexpr bool smearx = true;
  // Simulate a charged-particle track.
  double xt = 0.;
  if (smearx) xt = -0.5 * pitch + RndmUniform() * pitch;
  track.NewTrack(xt, 0, 0, 0, 0, 1, 0);
  // Retrieve the clusters along the track.
  for (const auto& cluster : track.GetClusters()) {
    // Loop over the electrons in the cluster.
    for (const auto& electron : cluster.electrons) {
      drift.AddElectron(electron.x, electron.y, electron.z, electron.t);
      drift.AddHole(electron.x, electron.y, electron.z, electron.t);
    }
  }
  double t0 = 0.;
  double dt = 0.05;
  const std::size_t nFrames = 120;
  for (std::size_t i = 0; i < 120; ++i) {
    driftView.Clear();
    drift.SetTimeWindow(t0, t0 + dt);
    drift.ResumeAvalanche();
    driftView.Plot2d(true, true);
    signalView.PlotSignal(label);
    gSystem->ProcessEvents();
    constexpr bool gif = true;
    if (!gif) {
      char filename[50];
      snprintf(filename, 50, "frames/frame_%03zu.png", i);
      canvas.SaveAs(filename);
    } else {
      if (i == nFrames - 1) {
        canvas.Print("planar_movie.gif++");
      } else {
        canvas.Print("planar_movie.gif+3");
      }
    }
    t0 += dt;
  }
  std::cout << "Done.\n";
  // app.Run();
}
