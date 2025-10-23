// X-ray conversion
// -------------------------------------------------------------------
// Simulate the Fe55 spectrum
//
// Thanks to Dorothea Pfeiffer and Heinrich Schindler from CERN for their help.
// -------------------------------------------------------------------
// Lucian Scharenberg
// scharenberg@physik.uni-bonn.de
// 05 APR 2018

#include <TApplication.h>
#include <TCanvas.h>
#include <TH1F.h>

#include <iostream>

#include "Garfield/ComponentConstant.hh"
#include "Garfield/GeometrySimple.hh"
#include "Garfield/MediumMagboltz.hh"
#include "Garfield/Random.hh"
#include "Garfield/Sensor.hh"
#include "Garfield/SolidTube.hh"
#include "Garfield/TrackHeed.hh"

using namespace Garfield;

int main(int argc, char* argv[]) {
  TApplication app("app", &argc, argv);

  // Make a gas medium.
  MediumMagboltz gas("Ar", 70., "CO2", 30.);
  gas.SetTemperature(293.15);
  gas.SetPressure(AtmosphericPressure);

  // Create a cylinder in which the x-rays can convert.
  // Diameter [cm]
  constexpr double diameter = 7.8;
  // Half-length of the cylinder [cm].
  constexpr double length = 10.;
  SolidTube tube(0, 0, 0, 0.5 * diameter, length);

  // Combine gas and box to a simple geometry.
  GeometrySimple geo;
  geo.AddSolid(&tube, &gas);

  // Make a component with constant electric field.
  ComponentConstant field;
  field.SetGeometry(&geo);
  field.SetElectricField(0., 0., 500.);

  // Make a sensor.
  Sensor sensor(&field);

  // Use Heed for simulating the photon absorption.
  TrackHeed track(&sensor);
  // Histogram
  const int nBins = 500;
  TH1::StatOverflows(true);
  TH1F hElectrons("hElectrons", ";Number of electrons;", nBins, -0.5,
                  nBins - 0.5);
  const std::size_t nEvents = 100000;
  for (std::size_t i = 0; i < nEvents; ++i) {
    if (i % 1000 == 0) std::cout << i << "/" << nEvents << "\n";
    // Initial coordinates of the photon.
    const double x0 = 0.;
    const double y0 = 0.;
    const double z0 = 0.;
    const double t0 = 0.;
    // Sample the photon energy, using the relative intensities according to
    // XDB.
    const double r = 167. * RndmUniform();
    const double egamma = r < 100. ? 5898.8 : r < 150. ? 5887.6 : 6490.4;
    auto cluster = track.TransportPhoton(x0, y0, z0, t0, egamma, 0., 0., 1.);
    hElectrons.Fill(cluster.electrons.size());
  }

  TCanvas c("c", "", 600, 600);
  c.cd();
  hElectrons.SetFillColor(kBlue + 2);
  hElectrons.SetLineColor(kBlue + 2);
  hElectrons.Draw();
  c.Update();
  app.Run(true);
}
