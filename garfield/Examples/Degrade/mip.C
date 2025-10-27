#include <TApplication.h>
#include <TCanvas.h>
#include <TH1F.h>

#include <iostream>

#include "Garfield/ComponentConstant.hh"
#include "Garfield/MediumMagboltz.hh"
#include "Garfield/Random.hh"
#include "Garfield/RandomEngineRoot.hh"
#include "Garfield/Sensor.hh"
#include "Garfield/TrackDegrade.hh"

using namespace Garfield;

int main(int argc, char* argv[]) {
  Garfield::RandomEngineRoot randomEngine(123456);
  Garfield::Random::SetEngine(randomEngine);
  TApplication app("app", &argc, argv);

  TH1F hElectrons("hElectrons", "Number of electrons;number of electrons", 200,
                  0, 200);
  TH1F hClusterSize("hClusterSize", "Cluster size;electrons / cluster", 100,
                    0.5, 100.5);

  MediumMagboltz gas("ar", 90., "co2", 10.);

  constexpr double width = 1.;
  // Make the active area a box with uniform electric field.
  ComponentConstant cmp;
  cmp.SetArea(0., -10., -10., width, 10., 10.);
  cmp.SetMedium(&gas);
  cmp.SetElectricField(100., 0., 0.);

  Sensor sensor(&cmp);

  TrackDegrade track(&sensor);
  track.SetBetaGamma(3.);
  track.Initialise(&gas, true);
  for (std::size_t i = 0; i < 1000; ++i) {
    if (i % 10 == 0) std::cout << "Track " << i << "...\n";
    track.NewTrack(0., 0., 0., 0., 1., 0., 0.);
    std::size_t nsum = 0;
    for (const auto& cluster : track.GetClusters()) {
      nsum += cluster.electrons.size();
      hClusterSize.Fill(cluster.electrons.size());
    }
    hElectrons.Fill(nsum);
  }

  TCanvas c1;
  hElectrons.Draw();
  c1.Update();

  TCanvas c2;
  hClusterSize.Draw();
  c2.SetLogy();
  c2.Update();

  app.Run(true);
}
