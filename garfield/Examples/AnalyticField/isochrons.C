#include <TApplication.h>
#include <TCanvas.h>
#include <TStyle.h>

#include <array>
#include <vector>

#include "Garfield/ComponentAnalyticField.hh"
#include "Garfield/FundamentalConstants.hh"
#include "Garfield/MediumMagboltz.hh"
#include "Garfield/ViewCell.hh"
#include "Garfield/ViewIsochrons.hh"

using namespace Garfield;

int main(int argc, char* argv[]) {
  TApplication app("app", &argc, argv);
  gStyle->SetPadLeftMargin(0.15);

  // Make a gas medium.
  MediumMagboltz gas;
  gas.LoadGasFile("ar_50_c2h6_50_B_angle.gas");

  ComponentAnalyticField cmp;
  cmp.SetMedium(&gas);
  // Describe the cell layout.
  constexpr double h = 0.75;
  constexpr double ds = 20.e-4;
  constexpr double df = 120.e-4;
  constexpr double vs = 1700.;
  cmp.AddWire(0, 0, ds, vs, "s");
  cmp.AddWire(0, h, df, 0., "f");
  cmp.AddWire(h, 0, df, 0., "f");
  cmp.AddWire(h, h, df, 0., "f");
  cmp.SetPeriodicityX(2 * h);
  cmp.SetPeriodicityY(2 * h);

  const double xmin = -1.5 * h;
  const double xmax = 1.5 * h;
  const double ymin = -1.5 * h;
  const double ymax = 1.5 * h;

  ViewCell cellView(&cmp);
  cellView.SetArea(xmin, ymin, -10., xmax, ymax, 10.);

  ViewIsochrons isoView;
  isoView.SetComponent(&cmp);
  isoView.SetArea(xmin, ymin, -10., xmax, ymax, 10.);

  // Loop around the sense wire and make a list of
  // starting points of the drift lines.
  std::vector<std::array<double, 3> > points;
  std::size_t nPoints = 40;
  for (std::size_t i = 0; i < nPoints; ++i) {
    const double phi = i * TwoPi / nPoints;
    const double r0 = 0.51 * ds;
    const double x0 = r0 * cos(phi);
    const double y0 = r0 * sin(phi);
    std::array<double, 3> p0 = {x0, y0, 0.};
    points.push_back(std::move(p0));
  }

  TCanvas c1("c1", "", 600, 600);
  isoView.SetCanvas(&c1);
  // Calculate drift lines for positively charged electrons.
  isoView.DriftElectrons(true);
  // Plot isochron contour lines with 10 ns spacing.
  isoView.PlotIsochrons(10., points);
  cellView.SetCanvas(&c1);
  cellView.Plot2d();

  nPoints = 25;
  points.clear();
  // Make a list of starting points along a straight-line "track".
  for (std::size_t i = 0; i < nPoints; ++i) {
    const double x0 = 0.8 * h;
    const double y0 = ymin + i * (ymax - ymin) / nPoints;
    std::array<double, 3> p0 = {x0, y0, 0.};
    points.push_back(std::move(p0));
  }

  TCanvas c2("c2", "", 600, 600);
  isoView.SetCanvas(&c2);
  // Calculate drift lines for (negatively charged) electrons.
  isoView.DriftElectrons();
  // Measure the drift time from the endpoint of the drift lines.
  const bool reverse = true;
  isoView.PlotIsochrons(10., points, reverse);
  cellView.SetCanvas(&c2);
  cellView.Plot2d();

  app.Run(true);
}
