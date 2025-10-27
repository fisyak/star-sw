#include <iostream>

#include "Garfield/ComponentAnalyticField.hh"

using namespace Garfield;

int main() {
  ComponentAnalyticField cmp;
  cmp.AddWire(+1., +1., 0.01, +1000.);
  cmp.AddWire(-1., -1., 0.01, -1000.);

  cmp.AddCharge(2., 2., 2., 1.0);
  cmp.AddCharge(3., 2., 3., 4.5);

  cmp.PrintCell();

  // Integrate around wire 1
  std::cout << "Charge on wire 1: "
            << cmp.IntegrateFluxCircle(1.1, 0.5, 0.8) * 1.e-3 << " pC/cm.\n";

  cmp.PrintCharges();
  constexpr std::size_t nI = 50;
  std::cout << "Both point charges: "
            << cmp.IntegrateFluxSphere(5, 2, 2.5, 3.5, nI) << " fC.\n";

  cmp.Clear();
  cmp.AddPlaneX(-1., -1000.);
  cmp.AddPlaneX(+1., +1000.);
  std::cout << "Flux = "
            << cmp.IntegrateFluxParallelogram(0, -1, -1, 0, 2, 0, 0, 0, 2)
            << " [V.cm]\n";
}
