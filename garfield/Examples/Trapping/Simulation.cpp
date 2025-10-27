#include <TApplication.h>

#include <fstream>

#include "Garfield/AvalancheMC.hh"
#include "Garfield/ComponentGrid.hh"
#include "Garfield/MediumSilicon.hh"
#include "Garfield/Sensor.hh"
#include "Garfield/TrackHeed.hh"
#include "Garfield/ViewSignal.hh"

using namespace Garfield;

int main(int argc, char* argv[]) {
  TApplication app("app", &argc, argv);

  constexpr double d = 199.5e-04;
  constexpr double pitch = 55e-4;
  // Define the medium.
  MediumSilicon si;
  si.SetTemperature(293.);

  ComponentGrid efield;
  efield.LoadElectricField("Efield.txt", "XY", true, false);
  efield.EnablePeriodicityX();
  efield.SetMedium(&si);

  efield.LoadElectronAttachment("Attachment.txt", "XY", 2);
  efield.LoadHoleAttachment("Attachment.txt", "XY", 3);

  ComponentGrid wfield;
  wfield.LoadWeightingField("Wfield.txt", "XY", true);

  wfield.Print();
  Sensor sensor(&efield);
  const std::string label = "pixel";
  sensor.AddElectrode(&wfield, label);

  // Set the time bins.
  const std::size_t nTimeBins = 1000;
  const double tmin = 0.;
  const double tmax = 10.;
  const double tstep = (tmax - tmin) / nTimeBins;
  sensor.SetTimeWindow(tmin, tstep, nTimeBins);

  // Set up Heed.
  TrackHeed track(&sensor);
  // Set the particle type and momentum [eV/c].
  track.SetParticle("pion");
  track.SetMomentum(180.e9);

  // Simulate electron/hole drift lines using MC integration.
  AvalancheMC drift(&sensor);
  // Use steps of 1 micron.
  drift.SetDistanceSteps(1.e-4);
  drift.EnableAttachmentMap();

  double x0 = pitch * 1.5, y0 = 5.e-5, z0 = 0., t0 = 0.;
  double dx = 0., dy = 1., dz = 0.;
  track.NewTrack(x0, y0, z0, t0, dx, dy, dz);
  // Retrieve the clusters along the track.
  for (const auto& cluster : track.GetClusters()) {
    // Loop over the electrons in the cluster.
    for (const auto& electron : cluster.electrons) {
      // Simulate the electron and hole drift lines.
      drift.DriftElectron(electron.x, electron.y, electron.z, electron.t);
      drift.DriftHole(electron.x, electron.y, electron.z, electron.t);
    }
  }
  constexpr bool plotSignal = true;
  ViewSignal signalView(&sensor);
  signalView.PlotSignal("pixel", "t");

  std::ofstream outfile;
  outfile.open("signal.txt", std::ios::out);
  for (std::size_t i = 0; i < nTimeBins; ++i) {
    const double t = (i + 0.5) * tstep;
    const double f = sensor.GetSignal(label, i);
    const double fe = sensor.GetElectronSignal(label, i);
    const double fh = sensor.GetIonSignal(label, i);
    outfile << t << "  " << f << "  " << fe << "  " << fh << "\n";
  }
  outfile.close();
  if (plotSignal) app.Run();
}
