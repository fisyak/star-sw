//
// Created by Dario Stocco (stoccod@ethz.ch) on 02.08.2023.
// Updated by Thomas Szwarcer on 26.08.2025.
//
// Note that ComponentChargedRing should not be added as a component to Sensor,
// as the electric field is handled internally by AvalancheGridSpaceCharge.
// ComponentParallelPlate is added to Sensor as a component because
// AvalancheGridSpaceCharge looks for a parallel plate to get the background
// field.
//
#include <TApplication.h>
#include <TCanvas.h>
#include <TSystem.h>

#include <iostream>
#include <string>
#include <vector>

#include "Garfield/AvalancheGridSpaceCharge.hh"
#include "Garfield/ComponentParallelPlate.hh"
#include "Garfield/MediumMagboltz.hh"
#include "Garfield/Sensor.hh"
#include "Garfield/ViewSignal.hh"

using namespace Garfield;

int main(int argc, char *argv[]) {
  std::cout << "Start RPC Space Charge Example\n";

  TApplication app("app", &argc, argv);

  double voltage = 9000;

  MediumMagboltz gas;
  gas.EnableAutoEnergyLimit(false);
  gas.SetMaxElectronEnergy(100.);
  std::string path = "CO2_C2H2F4_isoC4H10_SF6_30_64.5_4.5_1_T_293_P_723.8.gas";
  gas.LoadGasFile(path);
  gas.Initialise(true);

  // Dimensions of RPC
  double d_bakelite = 0.2;  // (cm)
  double d_pet = 0.02;
  double d_gas = 0.2;
  std::vector<double> layers = {d_pet, d_bakelite, d_gas, d_bakelite, d_pet};
  double y_mid = d_pet + d_bakelite + d_gas / 2;

  double e_bakelite = 8.;
  double e_pet = 3.5;
  double e_gas = 1.;
  std::vector<double> eps = {e_pet, e_bakelite, e_gas, e_bakelite, e_pet};

  ComponentParallelPlate cmp;
  cmp.Setup(int(layers.size()), eps, layers, voltage, {});
  std::string label = "readout";
  cmp.AddPlane(label);
  cmp.SetMedium(&gas);

  // Sensor
  Sensor sens(&cmp);
  sens.AddElectrode(&cmp, label);
  const std::size_t nBins = 200;
  const double tMax = 25.;
  sens.SetTimeWindow(0., tMax / nBins, nBins);

  AvalancheGridSpaceCharge avalsc(&sens);
  avalsc.EnableDebugging();
  avalsc.EnableDiffusion(true);
  avalsc.EnableStickyAnode(true);
  avalsc.EnableAdaptiveTimeStepping(true);
  avalsc.SetStopAtK(true);
  std::string fieldOption = "mirror";
  avalsc.SetFieldCalculation(fieldOption);
  // Set the grid.
  avalsc.Set2dGrid(y_mid - 0.5 * d_gas + 1.e-8, y_mid + 0.5 * d_gas - 1.e-8,
                   400, 0.05, 100);
  avalsc.EnableSpaceChargeEffect(true);
  // Place 1000 electrons in the middle of the gas gap.
  avalsc.AddElectron(0., y_mid, 0., 0., 1000.);
  avalsc.StartGridAvalanche();
  // Export grid.
  avalsc.ExportGrid("my_rpc_grid");

  // View recorded signals from plane electrode.
  ViewSignal *signal_view = new ViewSignal(&sens);
  TCanvas *c_signal = new TCanvas(label.c_str(), label.c_str(), 600, 600);
  signal_view->SetCanvas(c_signal);
  signal_view->PlotSignal(label);
  gSystem->ProcessEvents();

  app.Run(true);

  return 0;
}
