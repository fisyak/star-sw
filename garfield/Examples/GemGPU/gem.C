#include <TApplication.h>

#include <iostream>

#include "Garfield/AvalancheMC.hh"
#include "Garfield/AvalancheMicroscopic.hh"
#include "Garfield/ComponentAnsys123.hh"
#include "Garfield/MediumMagboltz.hh"
#include "Garfield/Random.hh"
#include "Garfield/RandomEngineRoot.hh"
#include "Garfield/Sensor.hh"
#include "Garfield/ViewField.hh"

using namespace Garfield;

int main(int argc, char* argv[]) {
  Garfield::RandomEngineRoot randomEngine(42);

  TApplication app("app", &argc, argv);

  app.GetOptions(&argc, argv);

  MPRunMode mode = MPRunMode::Normal;
  for (int i = 0; i < argc; ++i) {
    if (!strcmp(argv[i], "--gpu")) mode = MPRunMode::GPUExclusive;
  }

  // Setup the gas.
  MediumMagboltz gas("ar", 80., "co2", 20.);
  gas.SetTemperature(293.15);
  gas.SetPressure(760.);
  gas.SetMaxElectronEnergy(100.0);
  gas.Initialise(true);
  // Set the Penning transfer efficiency.
  constexpr double rPenning = 0.51;
  constexpr double lambdaPenning = 0.;
  // Penning transfer is not supported by the GPU - so disable for comparisons
  // gas.EnablePenningTransfer(rPenning, lambdaPenning, "ar");
  // Load the ion mobilities.
  gas.LoadIonMobility("IonMobility_Ar+_Ar.txt");

  // Load the field map.
  ComponentAnsys123 fm;
  fm.Initialise("ELIST.lis", "NLIST.lis", "MPLIST.lis", "PRNSOL.lis", "mm");
  fm.EnableMirrorPeriodicityX();
  fm.EnableMirrorPeriodicityY();
  fm.PrintRange();

  // Associate the gas with the corresponding field map material.
  fm.SetGas(&gas);
  fm.PrintMaterials();
  // fm.Check();

  // Dimensions of the GEM [cm]
  constexpr double pitch = 0.014;

  // Create the sensor.
  Sensor sensor;
  sensor.AddComponent(&fm);
  sensor.SetArea(-5 * pitch, -5 * pitch, -0.01, 5 * pitch, 5 * pitch, 0.025);

  AvalancheMicroscopic aval;
  aval.SetSensor(&sensor);
  aval.SetRunModeOptions(mode, 0);
  aval.SetShowProgress(false);
  aval.SetMaxNumShowerLoops(-1);

  const std::size_t nEvents = 10;
  // Use 1000 initial electrons where the GPU is better
  const std::size_t nInitElectrons = 1000;

  int total_endpoints = 0;
  for (std::size_t i = 0; i < nEvents; ++i) {
    std::cout << i << "/" << nEvents << "\n";
    const double z0 = 0.02;
    const double t0 = 0.;
    const double e0 = 0.1;
    // Allows for multiple electrons to start in a single event
    for (std::size_t j = 0; j < nInitElectrons; ++j) {
      // Randomize the initial position.
      double x0 = -0.5 * pitch + RndmUniform() * pitch;
      double y0 = -0.5 * pitch + RndmUniform() * pitch;
      aval.AddElectron(x0, y0, z0, t0, e0);
    }
    aval.ResumeAvalanche();
    // aval.AvalancheElectron(x0, y0, z0, t0, e0, 0., 0., 0.);
    int ne = 0, ni = 0;
    int endpoints = 0;
    if (mode == MPRunMode::Normal) {
      aval.GetAvalancheSize(ne, ni);
      endpoints = aval.GetNumberOfElectronEndpoints();
    } else if (mode == MPRunMode::GPUExclusive) {
      aval.GetAvalancheSizeGPU(ne, ni);
      endpoints = aval.GetNumberOfElectronEndpointsGPU();
    }
    std::cout << "Avalanche size = " << ne << ", " << ni << std::endl;
    std::cout << "Endpoints = " << endpoints << std::endl;

    double xe1, ye1, ze1, te1, e1;
    double xe2, ye2, ze2, te2, e2;
    int status;
    total_endpoints += endpoints;
    // Uncomment to print endpoints
    /*
    for (int j = 0; j < endpoints; ++j) {
      if (mode == MPRunMode::Normal) {
        aval.GetElectronEndpoint(j, xe1, ye1, ze1, te1, e1, xe2, ye2, ze2, te2,
                                 e2, status);
      } else if (mode == MPRunMode::GPUExclusive) {
        aval.GetElectronEndpointGPU(j, xe1, ye1, ze1, te1, e1, xe2, ye2, ze2,
                                    te2, e2, status);
      }
      std::cout << j << " -> " << xe2 << ", " << ye2 << ", " << ze2 << ", "
                << status << std::endl;
    }
    */
    std::size_t nEl = 0;
    std::size_t nIon = 0;
    std::size_t nAtt = 0;
    std::size_t nInel = 0;
    std::size_t nExc = 0;
    std::size_t nSup = 0;
    gas.GetNumberOfElectronCollisions(nEl, nIon, nAtt, nInel, nExc, nSup);
    gas.ResetCollisionCounters();

    // These stats are currently not available for the GPU
    if (mode == MPRunMode::Normal) {
      std::cout << "Gas collision params: nEl = " << nEl << ", nIon = " << nIon
                << ", nAtt = " << nAtt << ", nInel = " << nInel
                << ", nExc = " << nExc << ", nSup = " << nSup << std::endl;
    }
  }

  std::cout << "Mean endpoints = " << float(total_endpoints) / nEvents
            << std::endl;
}
