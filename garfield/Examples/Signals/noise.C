#include <TApplication.h>
#include <TCanvas.h>
#include <TH1D.h>
#include <TSystem.h>

#include <cmath>
#include <fstream>
#include <iostream>
#include <vector>

#include "Garfield/ComponentUser.hh"
#include "Garfield/FundamentalConstants.hh"
#include "Garfield/Sensor.hh"
#include "Garfield/Shaper.hh"
#include "Garfield/ViewSignal.hh"

using namespace Garfield;

bool readTransferFunction(Sensor& sensor) {
  std::ifstream infile;
  infile.open("ft.txt", std::ios::in);
  if (!infile) {
    std::cerr << "Could not read transfer function.\n";
    return false;
  }
  std::vector<double> times;
  std::vector<double> values;
  while (!infile.eof()) {
    double t = 0., f = 0.;
    infile >> t >> f;
    if (infile.eof() || infile.fail()) break;
    times.push_back(t);
    values.push_back(f);
  }
  infile.close();
  sensor.SetTransferFunction(times, values);
  return true;
}

int main(int argc, char* argv[]) {
  TApplication app("app", &argc, argv);

  constexpr double q = 1. / ElementaryCharge;

  // Make a dummy component.
  ComponentUser cmp;

  // Create a sensor.
  Sensor sensor;
  const std::string label = "pad";
  sensor.AddElectrode(&cmp, label);

  constexpr double noise = 1000.;

  // Set transfer function.
  Shaper shaper(1, 25., 1., "unipolar");
  // sensor.SetTransferFunction(shaper);
  auto fT = [](const double t) {
    constexpr double tau = 25.;
    return (t / tau) * std::exp(1 - t / tau);
  };
  sensor.SetTransferFunction(fT);
  // if (!readTransferFunction(sensor)) return 0;

  // Set the time bins.
  const std::size_t nTimeBins = 1000;
  const double tmin = 0.;
  const double tmax = 200.;
  const double tstep = (tmax - tmin) / nTimeBins;
  sensor.SetTimeWindow(tmin, tstep, nTimeBins);

  sensor.PlotTransferFunction();

  TH1F hN("Noise", ";signal [e^{-}];entries", 100, -5 * noise, 5 * noise);
  // Plot the signal if requested.
  constexpr bool plotSignal = false;
  ViewSignal signalView(&sensor);

  constexpr bool fft = false;
  constexpr std::size_t nEvents = 1000;
  for (std::size_t i = 0; i < nEvents; ++i) {
    // Reset the signal.
    sensor.ClearSignal();
    if (i % 10 == 0) std::cout << i << "/" << nEvents << "\n";
    // Add noise.
    sensor.AddWhiteNoise(noise, true, 1.);
    // Apply the transfer function.
    sensor.ConvoluteSignals(fft);
    if (plotSignal) {
      signalView.PlotSignal(label, "t");
      gSystem->ProcessEvents();
    }
    for (std::size_t j = 400; j < nTimeBins; ++j) {
      hN.Fill(q * sensor.GetSignal(label, j));
    }
  }
  TCanvas cN;
  hN.Draw("");
  hN.Fit("gaus");
  cN.Update();

  app.Run(true);
}
