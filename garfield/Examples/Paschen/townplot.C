#include <TApplication.h>
#include <TCanvas.h>
#include <TGraph.h>
#include <TH1F.h>

#include <cmath>

#include "Garfield/MediumMagboltz.hh"
#include "Garfield/ViewBase.hh"

using namespace Garfield;

int main(int argc, char* argv[]) {
  TApplication app("app", &argc, argv);
  SetDefaultStyle(true);

  // Plot range.
  double emin = 4000.;
  double emax = 1000000.;
  const size_t nE = 200;

  std::vector<double> efield(nE, 0.);
  for (size_t i = 0; i < nE; ++i) {
    efield[i] = emin * pow(emax / emin, i / (nE - 1.));
  }
  // Read 99/1 transport table and extract Townsend coefficient
  MediumMagboltz gas;
  gas.LoadGasFile("ar-90-ic4h10-10-p1.gas");
  std::vector<double> a90_10(nE, 0.);
  for (size_t i = 0; i < nE; ++i) {
    gas.ElectronTownsend(efield[i], 0., 0., 0., 0., 0., a90_10[i]);
  }

  // Read 95/5 transport table and extract Townsend coefficient
  gas.LoadGasFile("ar-95-ic4h10-5-p1.gas");
  std::vector<double> a95_5(nE, 0.);
  for (size_t i = 0; i < nE; ++i) {
    gas.ElectronTownsend(efield[i], 0., 0., 0., 0., 0., a95_5[i]);
  }

  // Read 90/10 transport table and extract Townsend coefficient
  gas.LoadGasFile("ar-99-ic4h10-1-p1.gas");
  std::vector<double> a99_1(nE, 0.);
  for (size_t i = 0; i < nE; ++i) {
    gas.ElectronTownsend(efield[i], 0., 0., 0., 0., 0., a99_1[i]);
  }

  // Plot the Townsend coefficients.
  TCanvas c1("c1", "", 600, 600);
  c1.SetLogx();
  c1.SetLogy();
  TGraph g90(nE, efield.data(), a90_10.data());
  g90.SetLineWidth(3);
  g90.SetLineColor(kRed + 3);
  g90.Draw("al");
  g90.GetXaxis()->SetTitle("E [V/cm]");
  g90.GetYaxis()->SetTitle("#alpha [1/cm]");
  g90.GetXaxis()->SetLimits(efield.front(), efield.back());
  g90.GetHistogram()->SetMinimum(1.);
  g90.GetHistogram()->SetMaximum(15000.);
  TGraph g95(nE, efield.data(), a95_5.data());
  g95.SetLineColor(kRed + 1);
  g95.SetLineWidth(3);
  g95.Draw("lsame");
  TGraph g99(nE, efield.data(), a99_1.data());
  g99.SetLineColor(kOrange + 1);
  g99.SetLineWidth(3);
  g99.Draw("lsame");

  c1.SaveAs("townplot.pdf");
  app.Run();
  return 0;
}
