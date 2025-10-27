#include <TApplication.h>
#include <TCanvas.h>

#include "Garfield/ComponentAnalyticField.hh"
#include "Garfield/DriftLineRKF.hh"
#include "Garfield/MediumMagboltz.hh"
#include "Garfield/Random.hh"
#include "Garfield/Sensor.hh"
#include "Garfield/ViewCell.hh"
#include "Garfield/ViewDrift.hh"
#include "Garfield/ViewField.hh"
#include "Garfield/ViewSignal.hh"

using namespace Garfield;

// Impulse response of the PASA.
double transfer(double t) {
  constexpr double tau = 160;
  constexpr double fC_to_mV = 12.7;
  return fC_to_mV * exp(4) * pow((t / tau), 4) * exp(-4 * t / tau);
}

int main(int argc, char* argv[]) {
  TApplication app("app", &argc, argv);

  // Switch between IROC and OROC.
  constexpr bool iroc = false;

  // Distance between rows of wires [cm].
  constexpr double gap = iroc ? 0.2 : 0.3;

  // Periodicity (wire spacing) [cm].
  constexpr double period = 0.25;

  // Wire diameters [cm]
  // Sense wires.
  constexpr double ds = 0.0020;
  // Cathode wires.
  constexpr double dc = 0.0075;
  // Gate wires.
  constexpr double dg = 0.0075;

  // Voltage settings [V].
  // Sense wires.
  constexpr double vs = iroc ? 1460. : 1570.;
  // Gate wires.
  constexpr double vg = -70.;
  constexpr double deltav = 90.;  // for closed gate mode

  // HV plane (drift field).
  constexpr double yHV = 249.7;
  constexpr double vHV = -100000;

  // Setup the gas.
  MediumMagboltz gas("ne", 85.72, "co2", 9.52, "n2", 4.76);
  // Set the temperature [K] and pressure [Torr].
  gas.SetTemperature(293.15);
  gas.SetPressure(750.);
  // Read the electron transport coefficients from a .gas file.
  gas.LoadGasFile("Ne_90_CO2_10_N2_5_with_mg.gas");
  // Read the ion mobility table.
  gas.LoadIonMobility("IonMobility_Ne+_Ne.txt");

  // Setup the electric field.
  ComponentAnalyticField cmp;
  cmp.SetMedium(&gas);
  cmp.SetPeriodicityX(period);
  // Add the sense (anode) wires.
  constexpr double xs = 0.;
  constexpr double ys = gap;
  cmp.AddWire(xs, ys, ds, vs, "s", 100., 50., 19.3, 1);

  // Add the cathode wires.
  constexpr double xc = 0.5 * period;
  constexpr double yc = 2 * gap;
  cmp.AddWire(xc, yc, dc, 0., "c", 100., 50., 19.3, 1);

  // Add the gate wires.
  constexpr double xg1 = 0.25 * period;
  constexpr double xg2 = 0.75 * period;
  constexpr double yg = 2. * gap + 0.3;
  constexpr bool gating = true;
  if (gating) {
    cmp.AddWire(xg1, yg, dg, vg + deltav, "g+", 100., 50., 19.3, 1);
    cmp.AddWire(xg2, yg, dg, vg - deltav, "g-", 100., 50., 19.3, 1);
  } else {
    cmp.AddWire(xg1, yg, dg, vg, "g", 100., 50., 19.3, 1);
    cmp.AddWire(xg2, yg, dg, vg, "g", 100., 50., 19.3, 1);
  }

  // Add the planes.
  cmp.AddPlaneY(0., 0., "pad_plane");
  cmp.AddPlaneY(yHV, vHV);

  // Set the magnetic field [T].
  cmp.SetMagneticField(0, 0.5, 0);

  // Make a sensor.
  Sensor sensor(&cmp);
  sensor.AddElectrode(&cmp, "pad_plane");
  // Change the time window for less/better resolution in time
  // (effect on convolution can be important).
  sensor.SetTimeWindow(0., 1, 50000);
  constexpr double xmin = -3 * period;
  constexpr double xmax = 3 * period;
  sensor.SetArea(xmin, 0., -1., xmax, yHV, 1.);

  // Plot isopotential contours.
  ViewField fieldView(&sensor);
  fieldView.SetArea(xmin, 0., xmax, 5 * gap);
  fieldView.SetVoltageRange(-400., 1000.);
  fieldView.PlotContour();

  // Calculate ion drift lines using the RKF method.
  DriftLineRKF driftline(&sensor);

  // Plot the drift line.
  ViewDrift driftView;
  // Comment this out when calculating many drift lines.
  driftline.EnablePlotting(&driftView);

  // const int nIons = 10000;
  const int nIons = 10;
  // Count the number of ions that drift to
  // plane, cathode, gate or drift volume, respectively.
  int plane = 0, cathode = 0, gate = 0, escape = 0;
  for (int i = 0; i < nIons; i++) {
    // Sample the starting point of the ion around the sense wire.
    constexpr double r = 0.003;
    const double angle = RndmGaussian(0, 1.4);
    driftline.DriftIon(r * sin(angle), gap + r * cos(angle), 0, 0);
    double x1 = 0., y1 = 0., z1 = 0., t1 = 0.;
    int status = 0;
    driftline.GetEndPoint(x1, y1, z1, t1, status);
    if (y1 < 0.5 * gap) {
      // Ion drifted to the pad plane.
      ++plane;
    } else if (y1 > 1.5 * gap && y1 < 2.5 * gap) {
      // Ion drifted to a cathode wire.
      ++cathode;
    } else if (y1 > 2.5 * gap && y1 < 2 * gap + 0.3 * 1.5) {
      // Ion drifted to the gating grid.
      ++gate;
    } else {
      // Ion escaped to the drift volume.
      ++escape;
    }
  }

  // Plot the drift lines on top of the cell layout.
  ViewCell cellView(&cmp);
  cellView.SetArea(xmin, 0., xmax, 5 * gap);
  cellView.Plot2d();
  driftView.SetArea(xmin, 0., xmax, 5 * gap);
  driftView.SetCanvas(cellView.GetCanvas());
  driftView.Plot(true, false);

  // Plot the induced current.
  ViewSignal signalView(&sensor);
  TCanvas c1("c1", "", 800, 600);
  signalView.SetCanvas(&c1);
  signalView.PlotSignal("pad_plane");
  // Convolute with the transfer function and plot again.
  sensor.SetTransferFunction(transfer);
  constexpr bool fft = true;
  sensor.ConvoluteSignals(fft);
  TCanvas c2("c2", "", 800, 600);
  signalView.SetCanvas(&c2);
  signalView.SetLabelY("signal [mV]");
  signalView.PlotSignal("pad_plane");
  app.Run(true);
}
