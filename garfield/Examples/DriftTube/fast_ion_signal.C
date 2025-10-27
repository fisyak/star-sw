#include <TApplication.h>

#include "Garfield/AvalancheMC.hh"
#include "Garfield/ComponentAnalyticField.hh"
#include "Garfield/MediumMagboltz.hh"
#include "Garfield/Random.hh"
#include "Garfield/Sensor.hh"
#include "Garfield/TrackHeed.hh"
#include "Garfield/ViewSignal.hh"

using namespace Garfield;

// Contributed by Terry Buck.

// Finds ion creation time based on distance from the electron cluster
// to the wire (found by fitting the ion creation time of many avalanches)
double IonTiming(const double dist) {
  constexpr double p0 = 1.49880e-13;
  constexpr double p1 = 2.09250e+02;
  constexpr double p2 = 2.61998e+02;
  constexpr double p3 = -1.24766e+02;

  return p0 + p1 * dist + p2 * dist * dist + p3 * dist * dist * dist;
}

int main(int argc, char* argv[]) {
  TApplication app("app", &argc, argv);

  // Make a gas medium
  MediumMagboltz gas;
  gas.LoadIonMobility("IonMobility_Ar+_Ar.txt");

  ComponentAnalyticField cmp;
  cmp.SetMedium(&gas);

  const double dWire = 50.e-4;
  const double vWire = 3270.;
  cmp.AddWire(0., 0., dWire, vWire, "s", 100., 50., 19.3);
  const double rTube = 1.46;
  cmp.AddTube(rTube, 0., 0);

  Sensor sensor(&cmp);
  sensor.AddElectrode(&cmp, "s");
  const double tmin = 0.;
  const double tstep = 1.;
  const int nTimeBins = 1000;
  sensor.SetTimeWindow(tmin, tstep, nTimeBins);

  AvalancheMC drift(&sensor);
  drift.SetDistanceSteps(2.e-4);

  TrackHeed track(&sensor);
  track.SetParticle("muon");
  track.SetEnergy(170.e9);

  // Simulate a muon track.
  double x0 = 1.2;
  double y0 = -sqrt(rTube * rTube - x0 * x0);
  double z0 = 0.;
  double t0 = 0.;
  track.NewTrack(x0, y0, z0, t0, 0., 1., 0.);
  // Loop over all clusters created by the muon.
  for (const auto& cluster : track.GetClusters()) {
    // Compute the radial location of the cluster.
    const double r = sqrt(cluster.x * cluster.x + cluster.y * cluster.y);
    // Find the creation time of the ions produced in the
    // avalanches of the electrons in the cluster.
    const double time = IonTiming(r);
    const size_t nc = cluster.electrons.size();
    for (size_t i = 0; i < nc; ++i) {
      // Average ion creation point.
      constexpr double xIon = 0.00253;
      // Draw the avalanche size from a Polya distribution.
      constexpr double gain = 1190;
      constexpr double theta = 0.2654;
      // Scale the effect of the ion induced signal by the avalanche size.
      double np = gain * RndmPolya(theta);
      // Drift one highly charged ion to estimate the signal.
      drift.DriftIon(xIon, 0., 0., time, np);
    }
  }
  ViewSignal signalView(&sensor);
  signalView.PlotSignal("s");
  app.Run();
}
