#include <TApplication.h>
#include <TH2D.h>
#include <TPad.h>

#include <vector>

#include "Garfield/ComponentAnalyticField.hh"
#include "Garfield/MediumMagboltz.hh"

using namespace Garfield;

int main(int argc, char* argv[]) {
  TApplication app("app", &argc, argv);

  // Make a gas medium.
  MediumMagboltz gas;

  // Setup the cell.
  ComponentAnalyticField cmp;
  cmp.SetMedium(&gas);
  cmp.AddPlaneY(-0.2, 0.);
  cmp.AddPlaneY(4.0, 0.);
  constexpr double d = 0.01;
  cmp.AddWire(0.0, 0.0, d, 2000., "s");
  cmp.AddWire(0.0, 0.2, d, 0.);
  cmp.AddWire(0.2, 0.2, d, 0.);

  cmp.SetPeriodicityX(0.4);
  cmp.PrintCell();

  const std::size_t nX = 25;
  const std::size_t nY = 25;
  cmp.SetScanningGrid(nX, nY);
  cmp.SetScanningArea(-0.15, 0.15, -0.15, 0.15);
  std::vector<double> x;
  std::vector<double> y;
  std::vector<std::vector<double> > fx;
  std::vector<std::vector<double> > fy;
  cmp.ForcesOnWire(0, x, y, fx, fy);

  TH2D hFY("hFY", "y-component;x [mm];y [mm];F_{y} [N]", nX, -1.5, 1.5, nY,
           -1.5, 1.5);
  for (std::size_t i = 0; i < nX; ++i) {
    for (std::size_t j = 0; j < nY; ++j) {
      hFY.SetBinContent(i, j, fy[i][j]);
    }
  }
  hFY.SetStats(false);
  hFY.SetTitleOffset(1.6, "X");
  hFY.SetTitleOffset(1.6, "Y");
  hFY.SetTitleOffset(1.6, "Z");
  hFY.Draw("surf3");
  gPad->Update();
  gPad->SetTopMargin(0.15);
  gPad->SetLeftMargin(0.15);
  gPad->SetBottomMargin(0.15);
  app.Run(true);
}
