#include <TApplication.h>
#include <TCanvas.h>
#include <TH1F.h>

#include <iostream>

#include "Garfield/ComponentConstant.hh"
#include "Garfield/MediumMagboltz.hh"
#include "Garfield/Random.hh"
#include "Garfield/RandomEngineRoot.hh"
#include "Garfield/Sensor.hh"
#include "Garfield/TrackHeed.hh"

using namespace Garfield;

int main(int argc, char* argv[]) {
  Garfield::RandomEngineRoot randomEngine(123456);
  Garfield::Random::SetEngine(randomEngine);
  TApplication app("app", &argc, argv);

  // Histograms
  TH1::StatOverflows(true);
  TH1F hElectrons("hElectrons", "Number of electrons", 200, 0, 200);
  TH1F hEdep("hEdep", "Energy Loss", 100, 0., 10.);
  TH1F hClusterSize("hClusterSize", "Cluster size", 100, 0.5, 100.5);

  // Make a medium
  MediumMagboltz gas("ar", 90., "co2", 10.);
  gas.SetTemperature(293.15);
  gas.SetPressure(760.);

  // Thickness of the gas gap [cm]
  constexpr double width = 1.;

  // Make a component.
  ComponentConstant cmp;
  cmp.SetArea(0., -10., -10., width, 10., 10.);
  cmp.SetMedium(&gas);
  cmp.SetElectricField(100., 0., 0.);

  // Make a sensor.
  Sensor sensor(&cmp);

  // Setup HEED.
  TrackHeed track(&sensor);
  // Set the particle type and momentum [eV/c].
  track.SetParticle("pi");
  track.SetMomentum(120.e9);
  constexpr bool verbose = true;
  track.Initialise(&gas, verbose);
  const int nEvents = 10000;
  for (int i = 0; i < nEvents; ++i) {
    if (i % 1000 == 0) std::cout << i << "/" << nEvents << "\n";
    // Initial position and direction
    double x0 = 0., y0 = 0., z0 = 0., t0 = 0.;
    double dx0 = 1., dy0 = 0., dz0 = 0.;
    track.NewTrack(x0, y0, z0, t0, dx0, dy0, dz0);
    // Total energy loss along the track
    double esum = 0.;
    // Total number of electrons produced along the track
    int nsum = 0;
    // Loop over the clusters.
    for (const auto& cluster : track.GetClusters()) {
      esum += cluster.energy;
      nsum += cluster.electrons.size();
      hClusterSize.Fill(cluster.electrons.size());
    }
    hElectrons.Fill(nsum);
    hEdep.Fill(esum * 1.e-3);
  }

  TCanvas c1;
  hElectrons.GetXaxis()->SetTitle("number of electrons");
  hElectrons.Draw();
  c1.SaveAs("ne.pdf");

  TCanvas c2;
  hEdep.GetXaxis()->SetTitle("energy loss [keV]");
  hEdep.Draw();
  c2.SaveAs("edep.pdf");

  TCanvas c3;
  hClusterSize.GetXaxis()->SetTitle("electrons / cluster");
  hClusterSize.Draw();
  c3.SetLogy();
  c3.SaveAs("clusterSizeDistribution.pdf");

  app.Run(true);
}
