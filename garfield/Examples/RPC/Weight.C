#include <TApplication.h>
#include <TCanvas.h>
#include <TSystem.h>

#include <ctime>
#include <iostream>
#include <vector>

#include "Garfield/AvalancheGrid.hh"
#include "Garfield/AvalancheMicroscopic.hh"
#include "Garfield/ComponentParallelPlate.hh"
#include "Garfield/MediumMagboltz.hh"
#include "Garfield/Sensor.hh"
#include "Garfield/TrackHeed.hh"
#include "Garfield/ViewSignal.hh"

#define LOG(x) std::cout << x << std::endl

using namespace Garfield;

int main(int argc, char *argv[]) {
  TApplication app("app", &argc, argv);

  const bool debug = true;
  constexpr bool plotSignal = true;

  // The geometry of the RPC.
  const int N = 15;  // Total amount of layers inside the geometry

  // Relative permitivity of the layers
  const double epMylar = 3.1;     // [1]
  const double epGlaverbel = 8.;  // [1]
  const double epWindow = 6.;     // [1]
  const double epGas = 1.;        // [1]

  std::vector<double> eps = {epMylar, epWindow,    epGas,  epGlaverbel,
                             epGas,   epGlaverbel, epGas,  epGlaverbel,
                             epGas,   epGlaverbel, epGas,  epGlaverbel,
                             epGas,   epWindow,    epMylar};

  // Thickness of the layers
  const double dMylar = 0.035;      // [cm]
  const double dGlaverbell = 0.07;  // [cm]
  const double dWindow = 0.12;      // [cm]
  const double dGas = 0.025;        // [cm]

  std::vector<double> thickness = {dMylar, dWindow,     dGas,  dGlaverbell,
                                   dGas,   dGlaverbell, dGas,  dGlaverbell,
                                   dGas,   dGlaverbell, dGas,  dGlaverbell,
                                   dGas,   dWindow,     dMylar};

  double totalThickness = 0.81;

  // Applied potential
  const double voltage = -15e3;  // [V]

  ComponentParallelPlate *RPC = new ComponentParallelPlate();
  RPC->Setup(N, eps, thickness, voltage);

  // Adding a readout structure.
  const std::string label = "ReadoutPlane";
  RPC->AddPlane(label);

  // Setup the gas, but one can also use a gasfile.
  MediumMagboltz gas;
  gas.LoadGasFile("c2h2f4_ic4h10_sf6.gas");  // c2h2f4/ic4h10/sf6 90/5/5.
  gas.Initialise(true);

  // Setting the drift medium.
  RPC->SetMedium(&gas);

  // Create the sensor.
  Sensor sensor(RPC);
  sensor.AddElectrode(RPC, label);

  // Set the time bins.
  const std::size_t nTimeBins = 200;
  const double tmin = 0.;
  const double tmax = 4;
  const double tstep = (tmax - tmin) / nTimeBins;
  sensor.SetTimeWindow(tmin, tstep, nTimeBins);

  // Create the AvalancheMicroscopic.
  AvalancheMicroscopic aval(&sensor);
  // Set time window where the calculations will be done microscopically.
  const double tMaxWindow = 0.1;
  aval.SetTimeWindow(0., tMaxWindow);

  // Create the AvalancheGrid for grid-based avalanche calculations that are
  // suited for constant drift fields. This class will take over the
  // calculations of the microscopic class after the set time-window.
  AvalancheGrid avalgrid(&sensor);

  int steps = totalThickness * 1e4;
  avalgrid.SetGrid(-0.05, 0.05, 5, 0.0, totalThickness, steps, -0.05, 0.05, 5);

  // Preparing the plotting of the induced charge and signal of the electrode
  // readout.
  ViewSignal *signalView = nullptr;
  TCanvas *cSignal = nullptr;
  if (plotSignal) {
    cSignal = new TCanvas("cSignal", "", 600, 600);
    signalView = new ViewSignal(&sensor);
    signalView->SetCanvas(cSignal);
  }

  ViewSignal *chargeView = nullptr;
  TCanvas *cCharge = nullptr;
  if (plotSignal) {
    cCharge = new TCanvas("cCharge", "", 600, 600);
    chargeView = new ViewSignal(&sensor);
    chargeView->SetCanvas(cCharge);
  }

  // Set up Heed.
  TrackHeed track(&sensor);
  // Set the particle type and momentum [eV/c].
  track.SetParticle("pion");
  track.SetMomentum(7.e9);

  // Setting the timer for the running time of the algorithm.
  std::clock_t start = std::clock();

  // Simulate a charged-particle track.
  track.NewTrack(0, totalThickness, 0, 0, 0, -1, 0);
  // Retrieve the clusters along the track.
  for (const auto &cluster : track.GetClusters()) {
    // Loop over the electrons in the cluster.
    for (const auto &electron : cluster.electrons) {
      // Simulate the electron track
      aval.AvalancheElectron(electron.x, electron.y, electron.z, electron.t,
                             0.1, 0., 0., 0.);
      // Stops calculation after tMaxWindow ns and import electrons in.
      avalgrid.AddElectrons(&aval);
    }
  }

  // Start grid based avalanche calculations starting from where the microsocpic
  // calculations stopped.
  LOG("Switching to grid based method.");
  avalgrid.StartGridAvalanche();
  // Stop timer.
  double duration = (std::clock() - start) / (double)CLOCKS_PER_SEC;

  LOG("Script: " << "Electrons have drifted. It took " << duration
                 << "s to run.");

  if (plotSignal) {
    // Plot signals
    signalView->PlotSignal(label);
    cSignal->Update();
    gSystem->ProcessEvents();

    sensor.ExportSignal(label, "Signal");
    // Plot induced charge
    sensor.IntegrateSignal(label);
    chargeView->PlotSignal(label);
    cCharge->Update();
    gSystem->ProcessEvents();
    // Export induced current data as an csv file.
    sensor.ExportSignal(label, "Charge");
  }
  LOG("Script: Total induced charge = " << sensor.GetTotalInducedCharge(label)
                                        << " [fC].");

  app.Run(true);
}
