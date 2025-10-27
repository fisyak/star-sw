#include <TApplication.h>
#include <TFile.h>
#include <TH1F.h>

#include "Garfield/AvalancheMicroscopic.hh"
#include "Garfield/ComponentConstant.hh"
#include "Garfield/MediumMagboltz.hh"
#include "Garfield/Sensor.hh"

using namespace Garfield;

int main() {
  // Electric field [kV / cm].
  constexpr double field = 20.;
  // Gas gap [cm]
  constexpr double gap = 0.1;

  // Make a gas medium.
  MediumMagboltz gas("ar", 90., "co2", 10.);
  gas.SetTemperature(293.15);
  gas.SetPressure(760.);
  gas.SetMaxElectronEnergy(150.);
  gas.Initialise();

  // Make a component with constant drift field.
  ComponentConstant cmp;
  cmp.SetArea(-2., -2., 0., 2., 2., 2 * gap);
  cmp.SetMedium(&gas);
  cmp.SetElectricField(0, 0, field * 1.e3);

  // Make a sensor.
  Sensor sensor(&cmp);

  // Microscopic tracking.
  AvalancheMicroscopic aval(&sensor);

  // Histogram the distance (along z) between successive ioniations.
  TH1F hDeltaZ("hDeltaZ", "Distance between collisions", 150, 0., 150.e-4);
  aval.SetDistanceHistogram(&hDeltaZ, 'z');
  aval.EnableDistanceHistogramming(1);
  constexpr std::size_t nEvents = 10;
  for (std::size_t j = 0; j < nEvents; ++j) {
    // Initial electron energy [eV].
    constexpr double e0 = 1.;
    aval.AvalancheElectron(0, 0, gap, 0, e0, 0, 0, 0);
  }

  TFile outfile("dist.root", "RECREATE");
  outfile.cd();
  hDeltaZ.Write();
  outfile.Close();
}
