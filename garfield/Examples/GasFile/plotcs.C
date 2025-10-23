#include "Garfield/FundamentalConstants.hh"
#include "Garfield/MediumMagboltz.hh"
#include "TCanvas.h"

using namespace Garfield;

int main(int argc, char* argv[]) {
  const double pressure = AtmosphericPressure;
  const double temperature = 293.15;

  // Setup the gas mixture.
  MediumMagboltz gas("N2", 80.1, "O2", 19.9);
  gas.SetTemperature(temperature);
  gas.SetPressure(pressure);
  gas.Initialise();
  // Plot the cross-sections of the first component.
  TCanvas* c1 = new TCanvas("c1", "c1", 800, 800);
  gas.PlotElectronCrossSections(0, c1);
  c1->SaveAs("DryAir_CrossSections_N2.png");
  // Plot the cross-sections of the second component.
  gas.PlotElectronCrossSections(1, c1);
  c1->SaveAs("DryAir_CrossSections_O2.png");
  // Plot the collision rates.
  gas.PlotElectronCollisionRates(c1);
  c1->SaveAs("DryAir_CollisionRates.png");
}
