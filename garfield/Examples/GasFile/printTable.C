#include <cmath>
#include <iostream>

#include "Garfield/FundamentalConstants.hh"
#include "Garfield/MediumMagboltz.hh"

using namespace Garfield;

int main(int argc, char* argv[]) {
  MediumMagboltz gas;
  gas.LoadGasFile("ar_80_co2_20_2T.gas");

  std::vector<double> efields;
  std::vector<double> bfields;
  std::vector<double> angles;
  gas.GetFieldGrid(efields, bfields, angles);
  const auto nE = efields.size();
  const auto nB = bfields.size();
  const auto nA = angles.size();

  for (size_t j = 0; j < nB; ++j) {
    for (size_t k = 0; k < nA; ++k) {
      std::cout << "B = " << bfields[j]
                << " T, theta = " << angles[k] * RadToDegree << " degree\n";
      std::cout << "   E [V/cm]     vE [cm/us]    alpha [1/cm]\n";
      for (size_t i = 0; i < nE; ++i) {
        double ve = 0.;
        gas.GetElectronVelocityE(i, j, k, ve);
        // Convert from cm/ns to cm/us.
        ve *= 1.e3;
        double alpha = 0.;
        gas.GetElectronTownsend(i, j, k, alpha);
        alpha = exp(alpha);
        std::printf("%10.3f    %10.3f    %10.3f\n", efields[i], ve, alpha);
      }
    }
  }
}
