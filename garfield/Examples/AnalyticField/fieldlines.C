#include <TApplication.h>

#include "Garfield/ComponentAnalyticField.hh"
#include "Garfield/MediumMagboltz.hh"
#include "Garfield/ViewCell.hh"
#include "Garfield/ViewField.hh"

using namespace Garfield;

int main(int argc, char* argv[]) {
  TApplication app("app", &argc, argv);

  // Distance between rows of wires [cm].
  constexpr double gap = 0.2;
  // Periodicity (wire spacing) [cm].
  constexpr double period = 0.25;
  // Wire diameters [cm].
  constexpr double ds = 0.0020;  // sense wires
  constexpr double dc = 0.0075;  // cathode wires
  constexpr double dg = 0.0075;  // gate wires

  // Voltage settings [V].
  constexpr double vs = 1460.;  // sense wires
  constexpr double vg = -70.;   // gate wires

  // HV plane (drift field).
  constexpr double yHV = 249.7;
  constexpr double vHV = -100000;

  // Gas mixture.
  MediumMagboltz gas("ne", 85.72, "co2", 9.52, "n2", 4.76);

  // Define the cell layout.
  ComponentAnalyticField cmp;
  cmp.SetMedium(&gas);
  cmp.SetPeriodicityX(period);
  // Add the sense (anode) wires.
  constexpr double xs = 0.;
  constexpr double ys = gap;
  cmp.AddWire(xs, ys, ds, vs);
  // Add the cathode wires.
  constexpr double xc = 0.5 * period;
  constexpr double yc = 2 * gap;
  cmp.AddWire(xc, yc, dc, 0.);
  // Add the gate wires.
  constexpr double xg1 = 0.25 * period;
  constexpr double xg2 = 0.75 * period;
  constexpr double yg = 2. * gap + 0.3;
  cmp.AddWire(xg1, yg, dg, vg);
  cmp.AddWire(xg2, yg, dg, vg);
  // Add the planes.
  cmp.AddPlaneY(0., 0.);
  cmp.AddPlaneY(yHV, vHV);

  // Plot isopotential contours.
  ViewField fieldView(&cmp);
  constexpr double xmin = -3 * period;
  constexpr double xmax = 3 * period;
  fieldView.SetArea(xmin, 0., xmax, 5 * gap);
  fieldView.SetVoltageRange(-400., 1000.);
  fieldView.SetNumberOfContours(40);
  fieldView.Plot("v", "CONT1");
  // Plot field lines.
  std::vector<double> xf;
  std::vector<double> yf;
  std::vector<double> zf;
  fieldView.EqualFluxIntervals(xmin, 5 * gap, 0., xmax, 5 * gap, 0., xf, yf, zf,
                               50);
  fieldView.PlotFieldLines(xf, yf, zf, true, false);

  // Plot the cell layout.
  ViewCell cellView(&cmp);
  cellView.SetCanvas(fieldView.GetCanvas());
  cellView.SetArea(xmin, 0., xmax, 5 * gap);
  cellView.Plot2d();

  app.Run(true);
}
