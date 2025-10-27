#include <TApplication.h>
#include <TCanvas.h>

#include "Garfield/MediumMagboltz.hh"
#include "Garfield/ViewMedium.hh"

using namespace Garfield;

int main(int argc, char* argv[]) {
  TApplication app("app", &argc, argv);

  // Setup the gas.
  MediumMagboltz gas;
  gas.LoadGasFile("Ne_90_CO2_10_N2_5_with_mg.gas");
  // gas.PrintGas();
  std::vector<double> efields;
  std::vector<double> bfields;
  std::vector<double> angles;
  gas.GetFieldGrid(efields, bfields, angles);

  ViewMedium view(&gas);
  view.SetMagneticField(0.5);

  // Plot the velocity as function of electric field
  // at the first non-zero angle in the table.
  TCanvas c1("c1", "", 800, 600);
  view.SetCanvas(&c1);
  if (!angles.empty()) view.SetAngle(angles[1]);
  // Set the x-axis limits explicitly.
  view.EnableAutoRangeX(false);
  // Plot only the low-field part, using linear scale.
  view.SetRangeE(0., 1000., false);
  view.PlotElectronVelocity('e');

  // Plot the velocity as function of angle between E and B,
  // at E = 400 V / cm.
  TCanvas c2("c2", "", 800, 600);
  view.SetCanvas(&c2);
  view.SetElectricField(400.);
  view.SetRangeA(0., HalfPi, false);
  view.PlotElectronVelocity('a');

  app.Run();
}
