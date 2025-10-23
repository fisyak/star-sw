#include <TApplication.h>
#include <TCanvas.h>
#include <TH1F.h>

#include <iostream>

#include "Garfield/ComponentConstant.hh"
#include "Garfield/MediumSilicon.hh"
#include "Garfield/Random.hh"
#include "Garfield/RandomEngineRoot.hh"
#include "Garfield/Sensor.hh"
#include "Garfield/TrackBichsel.hh"

using namespace Garfield;

int main(int argc, char* argv[]) {
  RandomEngineRoot randomEngine(123456);
  Random::SetEngine(randomEngine);

  TApplication app("app", &argc, argv);

  // Histograms
  TH1::StatOverflows(true);
  TH1F hEdep("hEdep", "Energy Loss", 100, 0., 10.);

  MediumSilicon si;

  constexpr double width = 10.e-4;

  // Make the active area a box with uniform electric field.
  ComponentConstant cmp;
  cmp.SetArea(0., -10., -10., width, 10., 10.);
  cmp.SetMedium(&si);
  cmp.SetElectricField(100., 0., 0.);

  Sensor sensor(&cmp);

  TrackBichsel track(&sensor);
  track.EnableDebugging();
  track.SetParticle("pi");
  track.SetBetaGamma(10.);
  track.Initialise();
  track.ComputeCrossSection();
  track.DisableDebugging();
  const int nEvents = 10000;
  for (int i = 0; i < nEvents; ++i) {
    if (i % 1000 == 0) std::cout << i << "/" << nEvents << "\n";
    // Initial position and direction
    double x0 = 0., y0 = 0., z0 = 0., t0 = 0.;
    double dx0 = 1., dy0 = 0., dz0 = 0.;
    track.NewTrack(x0, y0, z0, t0, dx0, dy0, dz0);
    // Loop over the clusters.
    double esum = 0.;
    for (const auto& cluster : track.GetClusters()) {
      esum += cluster.energy;
    }
    hEdep.Fill(esum * 1.e-3);
  }

  TCanvas c1;
  hEdep.GetXaxis()->SetTitle("energy loss [keV]");
  hEdep.Draw();
  c1.SaveAs("edep.pdf");

  app.Run(true);
}
