#include <TApplication.h>
#include <TAxis.h>
#include <TCanvas.h>
#include <TGraph.h>

#include "Garfield/MediumMagboltz.hh"
#include "Garfield/TrackDegrade.hh"

using namespace Garfield;

int main(int argc, char* argv[]) {
  TApplication app("app", &argc, argv);

  MediumMagboltz gas("ar");

  TrackDegrade track;

  std::vector<double> bg = {0.5, 0.8, 1., 2., 3., 4., 5., 8., 10.};

  const std::size_t nPoints = bg.size();
  TGraph gStoppingPower(nPoints);
  TGraph gClusterDensity(nPoints);
  for (std::size_t i = 0; i < nPoints; ++i) {
    track.SetBetaGamma(bg[i]);
    track.Initialise(&gas);
    const double dedx = track.GetStoppingPower();
    const double imfp = track.GetClusterDensity();
    gStoppingPower.SetPoint(i, bg[i], 1.e-3 * dedx);
    gClusterDensity.SetPoint(i, bg[i], imfp);
  }

  TCanvas cStoppingPower("cStoppingPower", "", 600, 600);
  cStoppingPower.cd();
  gStoppingPower.SetMarkerStyle(20);
  gStoppingPower.Draw("ap");
  gStoppingPower.GetXaxis()->SetTitle("#beta#gamma");
  gStoppingPower.GetYaxis()->SetTitle("d#it{E}/d#it{x} [keV/cm]");
  cStoppingPower.SetLogx();
  cStoppingPower.SetLogy();
  gStoppingPower.GetYaxis()->SetMoreLogLabels();
  cStoppingPower.Update();

  TCanvas cClusterDensity("cClusterDensity", "", 600, 600);
  cClusterDensity.cd();
  gClusterDensity.SetMarkerStyle(20);
  gClusterDensity.Draw("ap");
  gClusterDensity.GetXaxis()->SetTitle("#beta#gamma");
  gClusterDensity.GetYaxis()->SetTitle("cluster density [cm^{-1}]");
  cClusterDensity.SetLogx();
  cClusterDensity.Update();
  app.Run(true);
}
