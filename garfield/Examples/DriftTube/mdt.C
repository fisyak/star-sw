#include <TApplication.h>
#include <TCanvas.h>

#include <fstream>
#include <iostream>
#include <vector>

#include "Garfield/ComponentAnalyticField.hh"
#include "Garfield/DriftLineRKF.hh"
#include "Garfield/MediumMagboltz.hh"
#include "Garfield/Sensor.hh"
#include "Garfield/TrackHeed.hh"
#include "Garfield/ViewDrift.hh"

using namespace Garfield;

bool readTransferFunction(Sensor& sensor) {
  std::ifstream infile;
  infile.open("mdt_elx_delta.txt", std::ios::in);
  if (!infile) {
    std::cerr << "Could not read delta response function.\n";
    return false;
  }
  std::vector<double> times;
  std::vector<double> values;
  while (!infile.eof()) {
    double t = 0., f = 0.;
    infile >> t >> f;
    if (infile.eof() || infile.fail()) break;
    times.push_back(1.e3 * t);
    values.push_back(f);
  }
  infile.close();
  sensor.SetTransferFunction(times, values);
  return true;
}

int main(int argc, char* argv[]) {
  TApplication app("app", &argc, argv);

  // Make a gas medium.
  MediumMagboltz gas;
  gas.LoadGasFile("ar_93_co2_7_3bar.gas");
  gas.LoadIonMobility("IonMobility_Ar+_Ar.txt");

  // Make a component with analytic electric field.
  ComponentAnalyticField cmp;
  cmp.SetMedium(&gas);
  // Wire radius [cm]
  const double rWire = 25.e-4;
  // Outer radius of the tube [cm]
  const double rTube = 0.71;
  // Voltages
  const double vWire = 2730.;
  const double vTube = 0.;
  // Add the wire in the centre.
  cmp.AddWire(0, 0, 2 * rWire, vWire, "s");
  // Add the tube.
  cmp.AddTube(rTube, vTube, 0);

  // Make a sensor.
  Sensor sensor(&cmp);
  sensor.AddElectrode(&cmp, "s");
  // Set the signal time window.
  const double tstep = 0.5;
  const double tmin = -0.5 * tstep;
  const std::size_t nbins = 1000;
  sensor.SetTimeWindow(tmin, tstep, nbins);
  // Set the delta reponse function.
  if (!readTransferFunction(sensor)) return 0;
  sensor.ClearSignal();

  // Set up Heed.
  TrackHeed track(&sensor);
  track.SetParticle("muon");
  track.SetEnergy(170.e9);

  // RKF integration.
  DriftLineRKF drift(&sensor);
  drift.SetGainFluctuationsPolya(0., 20000.);

  TCanvas* cD = nullptr;
  ViewDrift driftView;
  constexpr bool plotDrift = true;
  if (plotDrift) {
    cD = new TCanvas("cD", "", 600, 600);
    driftView.SetCanvas(cD);
    drift.EnablePlotting(&driftView);
    track.EnablePlotting(&driftView);
  }

  TCanvas* cS = nullptr;
  constexpr bool plotSignal = true;
  if (plotSignal) cS = new TCanvas("cS", "", 600, 600);

  const double rTrack = 0.3;
  const double x0 = rTrack;
  const double y0 = -sqrt(rTube * rTube - rTrack * rTrack);
  const std::size_t nTracks = 1;
  for (std::size_t j = 0; j < nTracks; ++j) {
    sensor.ClearSignal();
    track.NewTrack(x0, y0, 0, 0, 0, 1, 0);
    for (const auto& cluster : track.GetClusters()) {
      for (const auto& electron : cluster.electrons) {
        drift.DriftElectron(electron.x, electron.y, electron.z, electron.t);
      }
    }
    if (plotDrift) {
      cD->Clear();
      cmp.PlotCell(cD);
      constexpr bool twod = true;
      constexpr bool drawaxis = false;
      driftView.Plot(twod, drawaxis);
    }
    sensor.ConvoluteSignals();
    int nt = 0;
    if (!sensor.ComputeThresholdCrossings(-2., "s", nt)) continue;
    if (plotSignal) sensor.PlotSignal("s", cS);
  }

  app.Run(kTRUE);
}
