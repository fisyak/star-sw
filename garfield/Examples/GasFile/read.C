#include <TApplication.h>
#include <TCanvas.h>

#include "Garfield/MediumMagboltz.hh"
#include "Garfield/ViewMedium.hh"

using namespace Garfield;

int main(int argc, char* argv[]) {
  TApplication app("app", &argc, argv);

  // Setup the gas.
  MediumMagboltz gas;
  gas.LoadGasFile("ar_80_co2_20_2T.gas");
  gas.LoadIonMobility("IonMobility_Ar+_Ar.txt");
  gas.PrintGas();

  ViewMedium view(&gas);
  view.SetMagneticField(2.);

  TCanvas cV("cV", "", 600, 600);
  view.SetCanvas(&cV);
  view.PlotElectronVelocity();

  TCanvas cD("cD", "", 600, 600);
  view.SetCanvas(&cD);
  view.PlotElectronDiffusion();

  TCanvas cT("cT", "", 600, 600);
  view.SetCanvas(&cT);
  view.PlotElectronTownsend();

  TCanvas cA("cA", "", 600, 600);
  view.SetCanvas(&cA);
  view.PlotElectronAttachment();

  TCanvas cI("cI", "", 600, 600);
  view.SetCanvas(&cI);
  view.PlotIonVelocity();

  app.Run(true);
}
