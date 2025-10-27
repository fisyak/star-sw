#include <TApplication.h>

#include <iostream>

#include "Garfield/ComponentConstant.hh"
#include "Garfield/MediumSilicon.hh"
#include "Garfield/Sensor.hh"
#include "Garfield/TrackTrim.hh"
#include "Garfield/ViewDrift.hh"

using namespace Garfield;

int main(int argc, char* argv[]) {
  // Application
  TApplication app("app", &argc, argv);

  // Define the medium.
  MediumSilicon si;

  // Define the geometry.
  ComponentConstant cmp;
  cmp.SetElectricField(0., 1000., 0.);
  // Thickness of the silicon layer [cm]
  constexpr double d = 100.e-4;
  cmp.SetArea(-d, 0., -d, d, d, d);
  cmp.SetMedium(&si);
  // cmp.SetMagneticField(0., 0., 1.);

  // Make a sensor.
  Sensor sensor(&cmp);

  // Create a track class and connect it to a sensor.
  TrackTrim tr(&sensor);
  // Read the TRIM output file.
  const std::string filename = "EXYZ.txt";
  // Import 100 ions, skip the first 200 in the list.
  const std::size_t nIons = 100;
  const std::size_t nSkip = 200;
  if (!tr.ReadFile(filename, nIons, nSkip)) {
    std::cerr << "Reading TRIM EXYZ file failed.\n";
    return 1;
  }
  tr.Print();

  // Plot the tracks.
  ViewDrift driftView;
  tr.EnablePlotting(&driftView);

  // Generate tracks.
  for (std::size_t i = 0; i < nIons; ++i) {
    if (!tr.NewTrack(0., 0., 0., 0., 0., 1., 0.)) {
      std::cerr << "Generating clusters failed; skipping this track.\n";
      continue;
    }
    // Count the total number of electrons.
    std::size_t netot = 0;
    for (const auto& cluster : tr.GetClusters()) {
      netot += cluster.n;
    }
  }
  driftView.SetArea(-10.e-4, 0., 10.e-4, 50.e-4);
  driftView.Plot(true);

  app.Run();
  return 0;
}
