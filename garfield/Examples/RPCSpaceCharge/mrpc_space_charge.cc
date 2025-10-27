//
// Created by Dario Stocco (stoccod@ethz.ch) on 02.08.2023.
// Updated by Thomas Szwarcer on 26.08.2025.
//
#include <TApplication.h>
#include <TCanvas.h>
#include <TSystem.h>

#include <iostream>
#include <string>
#include <vector>

#include "Garfield/AvalancheGridSpaceCharge.hh"
#include "Garfield/AvalancheMicroscopic.hh"
#include "Garfield/ComponentParallelPlate.hh"
#include "Garfield/MediumMagboltz.hh"
#include "Garfield/Sensor.hh"
#include "Garfield/TrackHeed.hh"
#include "Garfield/ViewSignal.hh"

using namespace Garfield;

#define LOG(x) std::cout << x << std::endl;

int main(int argc, char *argv[]) {
  LOG("Start MRPC Double Gap RPC Space Charge Example")

  TApplication app("app", &argc, argv);

  double voltage = 2 * -9000.;

  MediumMagboltz gas;
  gas.EnableAutoEnergyLimit(false);
  gas.SetMaxElectronEnergy(100.);
  std::string path = "CO2_C2H2F4_isoC4H10_SF6_30_64.5_4.5_1_T_293_P_723.8.gas";
  gas.LoadGasFile(path);
  gas.Initialise(true);

  // MRPC dimensions (double gap)
  double d_bakelite = 0.2;  // (cm)
  double d_pet = 0.02;
  double d_gas = 0.2;
  double y_mid = 0.5 * (2 * d_pet + 3 * d_bakelite + 2 * d_gas);

  std::vector<double> layers = {d_pet, d_bakelite, d_gas, d_bakelite,
                                d_gas, d_bakelite, d_pet};

  double e_bakelite = 8.;
  double e_pet = 3.5;
  double e_gas = 1.;
  std::vector<double> eps = {e_pet, e_bakelite, e_gas, e_bakelite,
                             e_gas, e_bakelite, e_pet};

  // ComponentParallelPlate
  ComponentParallelPlate cmp;
  cmp.Setup(int(layers.size()), eps, layers, voltage, {});
  cmp.EnableDebugging();
  std::string label = "readout";
  cmp.AddPlane(label);
  cmp.SetMedium(&gas);

  // Sensor
  Sensor sens(&cmp);
  sens.AddElectrode(&cmp, label);
  sens.SetTimeWindow(0, (25. - 0) / 200., 200);

  // AvalancheGridSpaceCharge
  AvalancheGridSpaceCharge avalsc(&sens);
  avalsc.EnableDebugging();
  avalsc.EnableDiffusion(true);
  avalsc.EnableStickyAnode(true);
  avalsc.EnableAdaptiveTimeStepping(true);
  avalsc.SetStopAtK(true);
  avalsc.Set2dGrid(y_mid - (d_bakelite / 2 + d_gas) + 1.e-8,
                   y_mid + (d_bakelite / 2 + d_gas) - 1.e-8, 3 * 400, 0.05,
                   100);
  avalsc.EnableSpaceChargeEffect(true);
  // Mixed Method: AvalancheMicroscopic
  AvalancheMicroscopic avalmicro(&sens);
  avalmicro.SetTimeWindow(0., 0.5);

  LOG("Muon(100GeV) Interaction Start")

  // TrackHeed for primary ionization
  TrackHeed track(&sens);
  track.SetParticle("muon");
  track.SetMomentum(1.e11);  // 100GeV
  track.CrossInactiveMedia(true);
  track.NewTrack(0, y_mid + (d_bakelite / 2 + d_gas) - 1.e-6, 0, 0., 0., -1.,
                 0.);

  // Retrieve the clusters along the track.
  for (const auto &cluster : track.GetClusters()) {
    // Loop over the electrons in the cluster.
    for (const auto &electron : cluster.electrons) {
      // Propagate electrons microscopically
      avalmicro.AvalancheElectron(electron.x, electron.y, electron.z,
                                  electron.t, 0.1, 0., 0., 0.);
      // Add electrons to the grid.
      avalsc.AddElectrons(&avalmicro);
    }
  }

  LOG("Start Grid Calculation")

  avalsc.StartGridAvalanche();

  avalsc.ExportGrid("my_mrpc_grid");
  std::string filename = "my_signal";
  sens.ExportSignal(label, filename);

  // view recorded signals from plane electrode
  ViewSignal *signal_view = new ViewSignal();
  TCanvas *c_signal = new TCanvas(label.c_str(), label.c_str(), 600, 600);
  signal_view->SetCanvas(c_signal);
  signal_view->SetSensor(&sens);
  signal_view->PlotSignal(label);
  c_signal->SetTitle(label.c_str());
  gSystem->ProcessEvents();

  app.Run();
  return 0;
}
