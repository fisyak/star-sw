// This script illustrates the simulation of VUV electroluminescence
// and its properties in pure noble gases (Ne, Ar, Kr and Xe).
// The program uses a uniform field created by two parallel metalic plates

// For further details see Phys. Lett. B, vol. 703, pp 217-222, 2011.
// Author: C. A. B. Oliveira
// email: carlos.oliveira@ua.pt

#include <TApplication.h>
#include <TH1D.h>

#include <iostream>
#include <vector>

#include "Garfield/AvalancheMicroscopic.hh"
#include "Garfield/ComponentAnalyticField.hh"
#include "Garfield/MediumMagboltz.hh"
#include "Garfield/Sensor.hh"

using namespace Garfield;

int main(int argc, char* argv[]) {
  TApplication app("app", &argc, argv);

  // Simulation parameters
  // Number of primary electrons (avalanches) to simulate
  constexpr std::size_t npe = 10;
  // Electric field [V cm-1]
  constexpr double ef = 8000.;
  // Width of the parallel gap [cm]
  constexpr double yGap = 0.7;

  // Make a gas medium.
  MediumMagboltz gas("xe");
  // Set temperature [K] and pressure [Torr].
  gas.SetTemperature(293.15);
  gas.SetPressure(760.);

  // Make a component with analytic electric field.
  ComponentAnalyticField comp;
  comp.AddPlaneY(0, 0, "b");
  comp.AddPlaneY(yGap, ef * yGap, "t");
  comp.SetMedium(&gas);

  // Make a sensor.
  Sensor sensor(&comp);
  sensor.SetArea();

  // Make a microscopic tracking class for electron transport.
  AvalancheMicroscopic aval(&sensor);
  // Make a histogram of the electron energy distribution.
  TH1D hEn("hEn", "energy distribution", 1000, 0., 100.);
  aval.EnableElectronEnergyHistogramming(&hEn);

  constexpr bool print = false;
  std::vector<std::size_t> nVUV;
  // Calculate a few avalanches.
  for (std::size_t i = 0; i < npe; ++i) {
    // Release the primary electron 0.2 cm away from the bottom electrode.
    const double x0 = 0.;
    const double y0 = 0.2;
    const double z0 = 0.;
    const double t0 = 0.;
    // Draw the initial energy [eV] from the energy distribution.
    const double e0 = i == 0 ? 1. : hEn.GetRandom();
    std::cout << "Avalanche " << i + 1 << " of " << npe << ".\n";
    if (print) {
      std::cout << "  Primary electron starts at (x, y, z) = (" << x0 << ", "
                << y0 << ", " << z0 << ") with an energy of " << e0 << " eV.\n";
    }
    // Simulate the avalanche
    aval.AvalancheElectron(x0, y0, z0, t0, e0, 0, 0, 0);
    // Get the number of electrons and ions.
    int ne = 0, ni = 0;
    aval.GetAvalancheSize(ne, ni);
    // Get information about all the electrons produced in the avalanche.
    std::size_t nBottomPlane = 0;
    std::size_t nTopPlane = 0;
    for (const auto& electron : aval.GetElectrons()) {
      if (electron.status == -5) {
        // The electron left the drift medium.
        if (electron.path.back().y < 0.0001) {
          ++nBottomPlane;
        } else if (electron.path.back().y > yGap - 0.0001) {
          ++nTopPlane;
        }
      } else {
        std::cout << "Unexpected status (" << electron.status << ").\n";
      }
    }
    std::size_t nEl = 0;
    std::size_t nIon = 0;
    std::size_t nAtt = 0;
    std::size_t nInel = 0;
    std::size_t nExc = 0;
    std::size_t nSup = 0;
    gas.GetNumberOfElectronCollisions(nEl, nIon, nAtt, nInel, nExc, nSup);
    gas.ResetCollisionCounters();
    nVUV.push_back(nExc + ni);
    if (!print) continue;
    std::cout << "  Number of electrons: " << ne << " (" << nTopPlane
              << " of them ended on the top electrode and " << nBottomPlane
              << " on the bottom electrode)\n"
              << "  Number of ions: " << ni << "\n"
              << "  Number of excitations: " << nExc << "\n";
  }

  // Fill distribution of the number of VUV photons.
  auto nMinVUV = *std::min_element(nVUV.cbegin(), nVUV.cend());
  auto nMaxVUV = *std::max_element(nVUV.cbegin(), nVUV.cend());
  TH1D hVUV("hVUV", "", nMaxVUV - nMinVUV, nMinVUV, nMaxVUV);
  hVUV.StatOverflows(true);
  for (const auto& n : nVUV) hVUV.Fill(n);
  std::cout << "\n\nAverage number of emitted VUV photons: " << hVUV.GetMean()
            << "\n";
  std::cout << "Determined value of J: "
            << (hVUV.GetRMS() * hVUV.GetRMS()) / hVUV.GetMean() << "\n";
  hVUV.Draw();

  app.Run(true);
}
