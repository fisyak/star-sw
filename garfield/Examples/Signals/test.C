#include <TApplication.h>
#include <TCanvas.h>

#include <iostream>

#include "Garfield/AvalancheMC.hh"
#include "Garfield/AvalancheMicroscopic.hh"
#include "Garfield/ComponentAnalyticField.hh"
#include "Garfield/MediumMagboltz.hh"
#include "Garfield/MediumSilicon.hh"
#include "Garfield/Sensor.hh"

using namespace Garfield;

int main(int argc, char* argv[]) {
  TApplication app("app", &argc, argv);

  MediumMagboltz gas("ar", 90., "co2", 10.);
  // Parallel plate chamber.
  ComponentAnalyticField cmp;
  cmp.SetMedium(&gas);
  constexpr double gap = 100.e-4;
  constexpr double field = 1.e3;
  cmp.AddPlaneY(0., 0., "pad");
  cmp.AddPlaneY(gap, -field * gap);

  // Create a sensor.
  Sensor sensor(&cmp);
  sensor.AddElectrode(&cmp, "pad");
  const std::size_t nBins = 100;
  sensor.SetTimeWindow(0, 0.1, nBins);
  AvalancheMicroscopic aval(&sensor);
  aval.UseWeightingPotential(true);
  // sensor.EnableDebugging();
  bool done = false;
  while (!done) {
    sensor.ClearSignal();
    aval.DriftElectron(0., gap, 0., 0., 0.1, 0., -1., 0.);
    // Skip electrons lost due to attachment.
    if (aval.GetElectrons().front().status == -7) continue;
    const auto& p1 = aval.GetElectrons().front().path.back();
    // Skip electrons that backscattered.
    if (p1.y > gap - 1.e-4) continue;
    break;
  }
  TCanvas c1("c", "", 600, 600);
  sensor.PlotSignal("pad", &c1);

  sensor.IntegrateSignals();
  const double q1 = sensor.GetSignal("pad", nBins - 1) / ElementaryCharge;
  std::cout << "Induced charge: " << q1 << " e-\n";

  sensor.ClearSignal();
  MediumSilicon si;
  cmp.SetMedium(&si);
  AvalancheMC mc(&sensor);
  mc.DriftElectron(0., gap, 0., 0.);

  TCanvas c2("c", "", 600, 600);
  sensor.PlotSignal("pad", &c2);
  sensor.IntegrateSignals();
  const double q2 = sensor.GetSignal("pad", nBins - 1) / ElementaryCharge;
  std::cout << "Induced charge: " << q1 << " e-\n";

  app.Run(true);
}
