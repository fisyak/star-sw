#include <TApplication.h>
#include <TAxis.h>
#include <TCanvas.h>
#include <TGraph.h>

#include <vector>

#include "Garfield/ComponentAnalyticField.hh"
#include "Garfield/MediumMagboltz.hh"

using namespace Garfield;

int main(int argc, char* argv[]) {
  TApplication app("app", &argc, argv);

  MediumMagboltz gas;

  // Setup the cell.
  ComponentAnalyticField cmp;
  cmp.SetMedium(&gas);
  cmp.AddPlaneY(0.375, -2000);
  cmp.AddPlaneY(-0.125, 0);
  cmp.AddWire(0, 0, 30.e-4, 3000., "s", 20., 60.);
  cmp.SetPeriodicityX(0.15);
  // cmp.PrintCell();

  // cmp.SetScanningAreaLargest();
  cmp.SetScanningArea(-0.01, 0.01, -0.01, 0.01);
  cmp.SetGravity(0, 1, 0);
  std::vector<double> csag;
  std::vector<double> xsag;
  std::vector<double> ysag;
  double stretch = 0.;
  cmp.WireDisplacement(0, true, csag, xsag, ysag, stretch);
  const std::size_t nPoints = csag.size();
  TGraph gSagY(nPoints);
  for (std::size_t i = 0; i < nPoints; ++i) {
    gSagY.SetPoint(i, csag[i], 1.e4 * ysag[i]);
  }
  TCanvas cSag("cSag", "", 600, 600);
  gSagY.SetLineWidth(4);
  gSagY.SetLineColor(kBlue + 2);
  gSagY.Draw("al");
  gSagY.GetXaxis()->SetTitle("#it{z} [cm]");
  gSagY.GetYaxis()->SetTitle("Sag [#mum]");
  cSag.Update();
  app.Run(true);
}
