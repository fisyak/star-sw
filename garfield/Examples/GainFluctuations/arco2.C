#include <TApplication.h>
#include <TFile.h>
#include <TH1F.h>

#include <iostream>
#include <string>

#include "Garfield/AvalancheMicroscopic.hh"
#include "Garfield/ComponentConstant.hh"
#include "Garfield/MediumMagboltz.hh"
#include "Garfield/Sensor.hh"

using namespace Garfield;

int main() {
  TFile outfile("arco2.root", "RECREATE");

  // Electric field [kV / cm].
  double field = 20.;
  for (std::size_t i = 0; i < 8; ++i) {
    // Initial electron energy [eV].
    const double e0 = 1.;

    // Make a gas medium.
    MediumMagboltz gas("ar", 90., "co2", 10.);
    gas.SetTemperature(293.15);
    gas.SetPressure(760.);
    gas.SetMaxElectronEnergy(150.);
    // constexpr double scale = 1.;
    // gas.SetExcitationScaling(scale, "ar");
    gas.Initialise();

    // Adjust the gap size depending on the electric field.
    const double gap = 1. / (3.5 * field - 60.);
    // Make a component with constant drift field.
    ComponentConstant cmp;
    cmp.SetArea(-2., -2., 0., 2., 2., 2 * gap);
    cmp.SetMedium(&gas);
    cmp.SetElectricField(0, 0, field * 1.e3);

    // Make a sensor.
    Sensor sensor(&cmp);

    // Microscopic tracking.
    AvalancheMicroscopic aval(&sensor);

    // Histograms
    TH1::StatOverflows(true);
    TH1F hElectrons("hElectrons", "Avalanche Size", 200, 0, 2000);
    TH1F hIons("hIons", "Avalanche Size", 200, 0, 2000);
    TH1F hEnergy("hEnergy", "Energy Distribution", 500, 0., 50.);
    // Request the electron energy histogram to be filled.
    aval.EnableElectronEnergyHistogramming(&hEnergy);
    std::cout << field << " kV/cm\n";
    // Count the ionisations and excitations in the avalanche.
    std::size_t nIon = 0;
    std::size_t nExc = 0;
    constexpr std::size_t nEvents = 100;
    for (std::size_t j = 0; j < nEvents; ++j) {
      gas.ResetCollisionCounters();
      aval.AvalancheElectron(0, 0, gap, 0, e0, 0, 0, 0);
      int ne = 0, ni = 0;
      aval.GetAvalancheSize(ne, ni);
      if (j % 100 == 0) {
        std::cout << j << "/" << nEvents << "\n"
                  << "    " << ne << " electrons\n";
      }
      hElectrons.Fill(ne);
      hIons.Fill(ni);
      // Retrieve the number of collisions of each type.
      std::size_t nColl[6] = {0};
      std::size_t nTotal = gas.GetNumberOfElectronCollisions(
          nColl[0], nColl[1], nColl[2], nColl[3], nColl[4], nColl[5]);
      nIon += nColl[1];
      nExc += nColl[4];
    }
    outfile.cd();
    std::string dir = std::to_string(int(field));
    outfile.mkdir(dir.c_str());
    outfile.cd(dir.c_str());
    hElectrons.Write();
    hIons.Write();
    hEnergy.Write();

    const double mean = hElectrons.GetMean();
    const double rms = hElectrons.GetRMS();
    std::cout << " f = " << rms * rms / (mean * mean) << "\n";
    std::printf("    %20zu ionisations, %20zu excitations\n", nIon, nExc);
    field += 5.;
  }
  outfile.Close();
}
