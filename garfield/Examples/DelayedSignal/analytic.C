#include <TApplication.h>

#include <cmath>
#include <cstddef>
#include <vector>

#include "Garfield/AvalancheMC.hh"
#include "Garfield/ComponentUser.hh"
#include "Garfield/MediumSilicon.hh"
#include "Garfield/Sensor.hh"
#include "Garfield/ViewSignal.hh"

using namespace Garfield;

int main(int argc, char* argv[]) {
  TApplication app("app", &argc, argv);

  // Define the medium.
  MediumSilicon si;
  // Use the mobility values from Werner's paper.
  // si.SetLowFieldMobility(1.5e-6, 0.5e-6);
  // si.SetHighFieldMobilityModelConstant();

  /* std::vector<double> times = {
     0.02, 0.04, 0.06, 0.08, 0.10, 0.12, 0.14, 0.16, 0.18, 0.20,
     0.3,  0.4,  0.5,  0.6,  0.7,  0.8,  0.9,  1.,   2.,   3.,
     4.,   5.,   6.,   7.,   8.,   9.,  10.,  20.,  30.,  40.,
    50.,  60.,  70.,  80.,  90., 100.};
  */
  std::vector<double> times;
  for (size_t i = 0; i < 500; ++i) {
    times.push_back(0.1 * i);
  }
  // Sensor thickness.
  constexpr double d = 300.e-4;
  // Depleted depth.
  constexpr double d0 = 200.e-4;
  // Time constant.
  constexpr double tau = 7.9;

  ComponentUser cmp;
  cmp.SetArea(-d, 0., -d, d, d, d);
  cmp.SetMedium(&si);
  auto efield = [](const double /*x*/, const double y, const double /*z*/,
                   double& ex, double& ey, double& ez) {
    ex = ez = 0.;
    constexpr double v = -25.2;
    ey = y < d0 ? 2 * (v / d0) * (1. - y / d0) : 0.;
  };
  // cmp.SetElectricField(efield);
  cmp.SetElectricField(
      "ey = y < 200.e-4 ? 2 * (-25.2 / 200.e-4) * (1. - y / 200.e-4) : 0.;");

  auto wfield = [](const double /*x*/, const double y, const double /*z*/,
                   double& wx, double& wy, double& wz) {
    wx = wz = 0.;
    wy = 1. / d;
  };
  // cmp.SetWeightingField(wfield, "front");
  cmp.SetWeightingField("wy = 1. / 300.e-4", "front");

  auto wpot = [](const double /*x*/, const double y, const double /*z*/) {
    return 1. - y / d;
  };
  // cmp.SetWeightingPotential(wpot, "front");
  cmp.SetWeightingPotential("1. - y / 300.e-4", "front");

  auto dwfield = [](const double /*x*/, const double y, const double /*z*/,
                    const double t, double& wx, double& wy, double& wz) {
    wx = wz = 0.;
    wy = y < d0 ? ((d - d0) / (d * d0)) : (-1. / d);
    wy *= std::exp(-t / tau) / tau;
  };
  // cmp.SetDelayedWeightingField(dwfield, "front");
  cmp.SetDelayedWeightingField(
      "double d = 300.e-4; double d0 = 200.e-4; double tau = 7.9; wy = y < d0 "
      "? ((d - d0) / (d * d0)) : (-1. / d); wy *= exp(-t / tau) / tau",
      "front");

  auto dwpot = [](const double /*x*/, const double y, const double /*z*/,
                  const double t) {
    return y * ((d - d0) / (d * d0)) * (std::exp(-t / tau) - 1.);
  };
  // cmp.SetDelayedWeightingPotential(dwpot, "front");
  cmp.SetDelayedWeightingPotential(
      "double d = 300.e-4; double d0 = 200.e-4; double tau = 7.9; return y * "
      "((d - d0) / (d * d0)) * (exp(-t / tau) - 1.);",
      "front");
  cmp.SetDelayedSignalTimes(times);

  Sensor sensor(&cmp);
  // Use 2000 time bins with a width of 25 ps.
  sensor.SetTimeWindow(0., 0.025, 2000);
  sensor.AddElectrode(&cmp, "front");
  sensor.SetArea(-d, 0, -d, d, d0 - 1.e-6, d);
  sensor.EnableDelayedSignal();

  AvalancheMC drift(&sensor);
  // drift.UseWeightingPotential(false);
  drift.SetTimeSteps(0.1);
  drift.EnableDiffusion(false);

  drift.DriftElectron(0, 150.e-4, 0, 0);
  drift.DriftHole(0, 150.e-4, 0, 0);

  // Plot the signal.
  ViewSignal signalView(&sensor);
  signalView.PlotSignal("front", "t", "t", "t");
  app.Run(true);
}
