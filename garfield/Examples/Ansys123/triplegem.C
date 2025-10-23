#include <TApplication.h>
#include <TFile.h>
#include <TH1F.h>

#include <ctime>
#include <iostream>
#include <string>

#include "Garfield/AvalancheMicroscopic.hh"
#include "Garfield/ComponentAnsys123.hh"
#include "Garfield/MediumMagboltz.hh"
#include "Garfield/Sensor.hh"

using namespace Garfield;

int main() {
  // Set up the gas.
  MediumMagboltz gas("ar", 45., "co2", 15., "cf4", 40.);
  gas.SetTemperature(293.15);
  gas.SetPressure(760.);
  gas.SetMaxElectronEnergy(200.);
  gas.EnablePenningTransfer(0.55, 0., "Ar");

  // Load the Ansys files.
  ComponentAnsys123 fm;
  const std::string path = "fieldmaps/triplegem/";
  fm.Initialise(path + "ELIST.lis", path + "NLIST.lis", path + "MPLIST.lis",
                path + "field.lis", "micron");
  fm.EnablePeriodicityX();
  fm.EnablePeriodicityY();
  fm.SetMagneticField(0, 0, 1.5);
  fm.SetGas(&gas);
  fm.PrintMaterials();

  Sensor sensor(&fm);

  AvalancheMicroscopic aval(&sensor);
  aval.EnableAvalancheSizeLimit(1000);

  TH1F hNelec("hNelec", "Number of electrons produced", 1000, -0.5, 999.5);
  for (int i = 0; i < 1000; i++) {
    const float timeused = (float)clock() / CLOCKS_PER_SEC;
    if (timeused > 25000.0) {
      std::cout << "Time limit (" << timeused << " s) reached.\n";
      break;
    }
    const double x0 = 0.007;
    const double y0 = 0.007;
    const double z0 = -0.3;
    const double e0 = 0.5;
    aval.AvalancheElectron(x0, y0, z0, 0, e0, 0, 0, 0);
    int ne, ni;
    aval.GetAvalancheSize(ne, ni);
    std::cout << "Avalanche " << i << ": " << ne << " electrons, " << ni
              << " ions.\n";
    hNelec.Fill(ne);
  }
  std::cout << "End of loop reached.\n";
  // Write out the histogram
  TFile f("aval.root", "update");
  f.cd();
  hNelec.Write();
  f.Close();
  std::cout << "End of program.\n";
}
