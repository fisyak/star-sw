#include <TApplication.h>

#include <iostream>

#include "Garfield/ComponentConstant.hh"
#include "Garfield/DriftLineRKF.hh"
#include "Garfield/MediumSilicon.hh"
#include "Garfield/Sensor.hh"
#include "Garfield/TrackTrim.hh"
#include "Garfield/ViewDrift.hh"
#include "Garfield/ViewSignal.hh"

using namespace Garfield;

int main(int argc, char* argv[]) {
  // Application
  TApplication app("app", &argc, argv);

  // Define the medium.
  MediumSilicon si;

  // Define the geometry.
  ComponentConstant cmp;
  cmp.SetElectricField(0., 5000., 0.);
  // Thickness of the silicon layer [cm]
  constexpr double d = 100.e-4;
  cmp.SetArea(-d, 0., -d, d, d, d);
  cmp.SetMedium(&si);
  // Define the weighting field and weighting potential
  // (parallel-plate electrode at y = 0).
  cmp.SetWeightingField(0, 1. / d, 0., "readout");
  cmp.SetWeightingPotential(0, 0, 0, 1.);

  Sensor sensor(&cmp);
  sensor.AddElectrode(&cmp, "readout");
  // Set the time bins for the induced current.
  const std::size_t nTimeBins = 1000;
  const double tmin = 0.;
  const double tmax = 10.;
  const double tstep = (tmax - tmin) / nTimeBins;
  sensor.SetTimeWindow(tmin, tstep, nTimeBins);

  // Read the TRIM output file.
  TrackTrim tr(&sensor);
  const std::string filename = "EXYZ.txt";
  // Import the first 100 ions.
  if (!tr.ReadFile(filename, 100)) {
    std::cerr << "Reading TRIM EXYZ file failed.\n";
    return 1;
  }

  DriftLineRKF drift(&sensor);
  drift.SetMaximumStepSize(10.e-4);

  // Plot the track and the drift lines.
  ViewDrift driftView;
  tr.EnablePlotting(&driftView);
  drift.EnablePlotting(&driftView);

  // Simulate an ion track.
  tr.NewTrack(0., 0., 0., 0., 0., 1., 0.);
  // Loop over the clusters.
  for (const auto& cluster : tr.GetClusters()) {
    // Simulate electron and ion drift lines starting
    // from the cluster position.
    // Scale the induced current by the number of electron/ion pairs
    // in the cluster.
    drift.DriftElectron(cluster.x, cluster.y, cluster.z, cluster.t, cluster.n);
    drift.DriftHole(cluster.x, cluster.y, cluster.z, cluster.t, cluster.n);
  }
  driftView.SetArea(-2.e-4, 0., 2.e-4, 100.e-4);
  driftView.Plot(true);

  ViewSignal signalView(&sensor);
  signalView.PlotSignal("readout", "tei");

  app.Run();
  return 0;
}
