#include <TApplication.h>

#include "Garfield/AvalancheMC.hh"
#include "Garfield/ComponentTcad3d.hh"
#include "Garfield/FundamentalConstants.hh"
#include "Garfield/MediumSilicon.hh"
#include "Garfield/Random.hh"
#include "Garfield/Sensor.hh"
#include "Garfield/TrackHeed.hh"
#include "Garfield/ViewDrift.hh"
#include "Garfield/ViewField.hh"

using namespace Garfield;

int main(int argc, char* argv[]) {
  TApplication app("app", &argc, argv);

  // Create a drift medium.
  MediumSilicon si;
  // Set the temperature [K].
  si.SetTemperature(266.15);

  // Make a component with three-dimensional TCAD field map.
  ComponentTcad3d cmp;
  // Load the mesh (.grd file) and electric field profile (.dat).
  cmp.Initialise("diode_msh.grd", "diode_des.dat");
  // Associate all regions in the field map with silicon.
  auto nRegions = cmp.GetNumberOfRegions();
  for (size_t i = 0; i < nRegions; ++i) {
    cmp.SetMedium(i, &si);
  }

  // Make a sensor.
  Sensor sensor(&cmp);
  sensor.SetArea();

  // Plot the electrostatic potential.
  ViewField fieldView(&sensor);
  fieldView.SetPlaneXZ();
  fieldView.PlotContour();

  // Use MC transport for drifting the electrons and holes.
  AvalancheMC drift(&sensor);
  drift.SetDistanceSteps(1.e-4);

  // Visualize the drift lines.
  ViewDrift driftView;
  drift.EnablePlotting(&driftView);

  TrackHeed track(&sensor);
  track.SetParticle("pi");
  track.SetMomentum(3.e9);

  // Sample the inclination and starting point of the track.
  const double theta = (RndmUniform() - 0.5) * 20. * DegreeToRad;
  const double x0 = (RndmUniform() - 0.5) * 40.e-4;
  const double y0 = (RndmUniform() - 0.5) * 40.e-4;
  track.NewTrack(x0, y0, 0., 0., sin(theta), 0., cos(theta));
  // Retrieve the clusters along the track.
  for (const auto& cluster : track.GetClusters()) {
    // Retrieve the electrons in the cluster.
    for (const auto& electron : cluster.electrons) {
      // Simulate and plot only a small fraction of the drift lines.
      constexpr double fPlot = 0.01;
      if (RndmUniform() > fPlot) continue;
      drift.DriftElectron(electron.x, electron.y, electron.z, electron.t);
      drift.DriftHole(electron.x, electron.y, electron.z, electron.t);
    }
  }
  driftView.SetPlaneXZ();
  driftView.Plot2d(true);
  app.Run(true);
}
