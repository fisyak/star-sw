#include <TApplication.h>
#include <TCanvas.h>
#include <TH1F.h>

#include <iostream>

#include "Garfield/Random.hh"

using namespace Garfield;

int main(int argc, char *argv[]) {
  // Application
  TApplication app("app", &argc, argv);

  // Run a couple of tests

  const double work = 30.;
  const double fano = 0.3;
  TH1F hwf("hwf", ";number of electrons;entries", 200, 0, 200);
  for (std::size_t i = 0; i < 10000000; ++i) {
    const double rnd = 1.e6 * (RndmHeedWF(1.e-6 * work, fano));
    hwf.Fill(rnd);
  }
  TCanvas chwf("chwf", "", 100, 100, 800, 800);
  chwf.cd();
  hwf.Draw();
  chwf.Update();

  double mean = hwf.GetMean();
  double rms = hwf.GetRMS();
  const double r = rms / mean;
  std::cout << "Histogram mean: " << mean << ", Fano: " << r * r << "\n";

  // Start loop
  app.Run();
  return 0;
}
