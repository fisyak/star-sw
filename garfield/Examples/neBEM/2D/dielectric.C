#include <TApplication.h>
#include <TCanvas.h>

#include <fstream>
#include <iomanip>

#include "Garfield/ComponentNeBem2d.hh"
#include "Garfield/MediumMagboltz.hh"
#include "Garfield/MediumPlastic.hh"
#include "Garfield/ViewCell.hh"
#include "Garfield/ViewField.hh"

using namespace Garfield;

int main(int argc, char* argv[]) {
  TApplication app("app", &argc, argv);

  MediumMagboltz gas("ar");
  ;

  MediumPlastic plastic;
  plastic.SetDielectricConstant(5.);

  ComponentNeBem2d cmp;
  cmp.SetMedium(&gas);
  cmp.SetNumberOfDivisions(10);
  constexpr double delta = 1.;
  constexpr double v = 100.;
  // Left conducting plate.
  const double xMin = -1.5 * delta;
  const double yMin = -10 * delta;
  const double yMax = 10 * delta;
  cmp.AddSegment(xMin, yMin, xMin, -delta, v);
  cmp.AddSegment(xMin, -delta, xMin, delta, v);
  cmp.AddSegment(xMin, delta, xMin, yMax, v);

  // Right conducting plate.
  const double xMax = 1.5 * delta;
  cmp.AddSegment(xMax, yMin, xMax, -delta, -v);
  cmp.AddSegment(xMax, -delta, xMax, delta, -v);
  cmp.AddSegment(xMax, delta, xMax, yMax, -v);

  // Dielectric.
  const double xD = 0.5 * delta;
  std::vector<double> xv = {-xD, -xD, xD, xD};
  std::vector<double> yv = {yMin, yMax, yMax, yMin};
  cmp.AddRegion(xv, yv, &plastic);

  // cmp.EnableDebugging();
  cmp.Initialise();

  const double eps2 = plastic.GetDielectricConstant();
  const double f1 = (2. * v / delta) / (2. + 1. / eps2);
  const double f2 = f1 / eps2;

  std::ofstream outfile;
  outfile.open("test.txt", std::ios::out);
  const int nSteps = 100;
  const double dx = 3. * delta / nSteps;
  for (int i = 1; i < nSteps; ++i) {
    const double x = xMin + i * dx;
    const double epot = cmp.ElectricPotential(x, 0., 0.);
    const std::array<double, 3> efld = cmp.ElectricField(x, 0., 0.);
    const double exact = x <= -xD ? f1 : x < xD ? f2 : f1;
    outfile << x << "  " << epot << "  " << std::setprecision(10) << efld[0]
            << "  " << efld[1] << "  " << std::setprecision(10) << exact
            << std::endl;
  }
  outfile.close();

  TCanvas canvas("c", "", 600, 600);
  ViewField fieldView(&cmp);
  fieldView.SetCanvas(&canvas);
  constexpr bool plotProfile = true;
  if (plotProfile) {
    fieldView.SetElectricFieldRange(0., 1.1 * f1);
    fieldView.PlotProfile(xMin, 0., 0., xMax, 0., 0., "ex");
  } else {
    fieldView.SetArea(1.1 * xMin, 1.1 * yMin, 1.1 * xMax, 1.1 * yMax);
    fieldView.PlotContour("ex");
    ViewCell cellView(&cmp);
    cellView.SetCanvas(&canvas);
    cellView.SetArea(1.1 * xMin, 1.1 * yMin, -1., 1.1 * xMax, 1.1 * yMax, 1.);
    cellView.Plot2d();
  }
  app.Run(true);
}
