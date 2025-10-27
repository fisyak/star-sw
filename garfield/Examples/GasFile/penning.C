#include <TApplication.h>
#include <TCanvas.h>

#include "Garfield/MediumMagboltz.hh"

using namespace Garfield;

int main(int argc, char* argv[]) {
  TApplication app("app", &argc, argv);

  // Load a gas file which includes excitation and ionisation rates.
  MediumMagboltz gas;
  gas.LoadGasFile("ar_93_co2_7.gas");
  gas.PrintGas();

  // Plot the Townsend coefficient (without Penning transfer).
  TCanvas c1("c1", "", 600, 600);
  gas.PlotTownsend("e", &c1);

  // Switch on Penning transfer for all excitation levels in the mixture.
  gas.EnablePenningTransfer(0.42, 0.);
  // Plot the Townsend coefficient with Penning transfer.
  TCanvas c2("c2", "", 600, 600);
  gas.PlotTownsend("e", &c2);

  app.Run(true);
}
