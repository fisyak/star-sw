#include <TApplication.h>
#include <TCanvas.h>
#include <TH1F.h>

#include <iostream>

#include "Garfield/ComponentConstant.hh"
#include "Garfield/MediumSilicon.hh"
#include "Garfield/Sensor.hh"
#include "Garfield/TrackHeed.hh"

using namespace Garfield;

int main(int argc, char* argv[]) {
  TApplication app("app", &argc, argv);

  MediumSilicon si;

  // Make a component
  ComponentConstant cmp;
  constexpr double width = 50.e-4;
  cmp.SetArea(-2, -2, 0, 2, 2, width);
  cmp.SetMedium(&si);
  cmp.SetElectricField(0., 0., 20.);

  // Make a sensor
  Sensor sensor(&cmp);

  TH1::StatOverflows(true);
  TH1F hNe("hNe", ";deposited charge [electrons];entries", 150, 0., 15000.);
  TH1F hNc("hNc", ";number of clusters;entries", 350, -0.5, 349.5);

  TrackHeed track(&sensor);
  track.SetParticle("pion");
  track.SetBetaGamma(10.);
  track.Initialise(&si, true);
  const std::size_t nTracks = 10000;
  for (std::size_t i = 0; i < nTracks; ++i) {
    if (i % 1000 == 0) std::cout << "Track " << i << "\n";
    track.NewTrack(0., 0., 0., 0., 0., 0., 1.);
    std::size_t nsum = 0;
    std::size_t ncls = 0;
    for (const auto& cluster : track.GetClusters()) {
      nsum += cluster.electrons.size();
      ++ncls;
    }
    hNe.Fill(nsum);
    hNc.Fill(ncls);
  }

  TCanvas cNe("cNe", "", 600, 600);
  hNe.Draw();
  cNe.Update();
  TCanvas cNc("cNc", "", 600, 600);
  hNc.Draw();
  cNc.Update();
  app.Run(true);
}
