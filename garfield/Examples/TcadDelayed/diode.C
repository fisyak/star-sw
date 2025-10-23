#include <TApplication.h>
#include <TCanvas.h>
#include <TSystem.h>

#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

#include "Garfield/AvalancheMC.hh"
#include "Garfield/ComponentTcad2d.hh"
#include "Garfield/MediumSilicon.hh"
#include "Garfield/Sensor.hh"
#include "Garfield/ViewSignal.hh"

using namespace Garfield;

int main(int argc, char* argv[]) {
  TApplication app("app", &argc, argv);

  // Define the geometrical size of the diode
  double w = 0.2;
  double xP = -0.0500;
  double xN = 0.0490;

  // Retrieve the data file prefix
  argc = app.Argc();
  argv = app.Argv();

  std::string data_file_prefix;
  if (argc >= 2) {
    data_file_prefix = argv[1];
  } else {
    std::cerr << "Missing weighting vector data file prefix!" << std::endl;
    std::cerr << "Usage: ./diode [FIELD-PATH-PREFIX]" << std::endl;
    return -1;
  }

  ComponentTcad2d diode;
  diode.Initialise(data_file_prefix + "_steady_dut_des.grd",
                   data_file_prefix + "_steady_dut_des.dat");
  diode.SetRangeZ(-0.5 * w, 0.5 * w);

  // Load the prompt weighting field
  diode.SetWeightingField(data_file_prefix + "_steady_dut_des.dat",
                          data_file_prefix + "_pulse_dut_des.dat", 1.0, "N");

  // Add the delayed weighting field components
  // Times as defined in `plot_times.txt`
  std::vector<double> times = {
      400e-12, 500e-12, 700e-12, 1e-9,   2e-9,   3e-9,   4e-9,   6e-9,
      8e-9,    10e-9,   15e-9,   20e-9,  25e-9,  30e-9,  40e-9,  50e-9,
      60e-9,   70e-9,   80e-9,   90e-9,  100e-9, 120e-9, 140e-9, 160e-9,
      180e-9,  200e-9,  220e-9,  240e-9, 270e-9, 300e-9};
  for (int tt = 0; tt < times.size(); tt++) {
    std::stringstream decay_file;
    decay_file << data_file_prefix << "_decay_" << std::setfill('0')
               << std::setw(4) << tt << "_dut_des.dat";

    diode.SetDynamicWeightingField(data_file_prefix + "_steady_dut_des.dat",
                                   decay_file.str(), 1.0 * 150e-12 * 1e9,
                                   times[tt] * 1e9, "N");
  }

  // Define and set the medium.
  MediumSilicon si;
  si.SetTemperature(293.);
  diode.SetMedium("Silicon", &si);

  // Create a sensor.
  Sensor sensor(&diode);
  sensor.AddElectrode(&diode, "N");

  // This is necessary to enable the delayed signal
  // Defining to few `delay_times` leads to an imprecise calculation of the
  // delayed signal.
  std::vector<double> delay_times;
  for (int tt = 0; tt < 100; tt++) {
    delay_times.push_back(tt);
  }
  sensor.SetDelayedSignalTimes(delay_times);
  sensor.EnableDelayedSignal(true);

  // Restrict drift to P-side!
  // If not done, the simulation will deadlock, as charges are never removed
  // from the simulation!
  sensor.SetArea(xP, -0.5 * w, -0.5 * w, 0, 0.5 * w, 0.5 * w);

  // Set the time bins.
  const std::size_t nTimeBins = 1000;
  const double tmin = 0.;
  const double tmax = 100.;
  const double tstep = (tmax - tmin) / nTimeBins;
  sensor.SetTimeWindow(tmin, tstep, nTimeBins);

  // Simulate electron/hole drift lines using MC integration.
  AvalancheMC drift(&sensor);
  drift.SetDistanceSteps(1.e-4);

  // Force the use of the weighting field instead of the weighing potential.
  drift.UseWeightingPotential(false);

  // Drift some electrons and holes
  // Alpha-like deposite close to the P-side surface
  // Leads primarily electron signal
  for (int dd = 0; dd < 100; dd++) {
    drift.DriftElectron(-0.0480, 0, 0, 0);
    drift.DriftHole(-0.0480, 0, 0, 0);
  }

  // Plot the signal
  TCanvas* cSignal = new TCanvas("cSignal", "", 600, 600);
  ViewSignal* signalView = new ViewSignal(&sensor);
  signalView->SetCanvas(cSignal);
  signalView->PlotSignal("N", "te", "", "e");

  cSignal->Update();
  gSystem->ProcessEvents();

  // Save the signals to a CSV file
  sensor.ExportSignal("N", "Signal_WField", true);

  app.Run();
}
