#include <cmath>
#include <cstddef>
#include <iostream>
#include <vector>

#include "Garfield/MediumGas.hh"
#include "TApplication.h"
#include "TCanvas.h"
#include "TGraph.h"
#include "TH1.h"
#include "TLegend.h"

using namespace Garfield;

int main(int argc, char* argv[]) {
  TApplication app("app", &argc, argv);

  // Read the gasfiles.
  MediumGas gas_0007mbar, gas_1013mbar;
  gas_0007mbar.LoadGasFile("ic4h10_0007mbar_100-25kVcm.gas");
  gas_1013mbar.LoadGasFile("ic4h10_1013mbar_100-100kVcm.gas");
  double density_0007mbar = gas_0007mbar.GetNumberDensity();
  double density_1013mbar = gas_1013mbar.GetNumberDensity();
  std::cout << "Loading GasFile 1 :: Gas Number Density = " << density_0007mbar
            << " cm-3" << std::endl;
  std::cout << "Loading GasFile 2 :: Gas Number Density = " << density_1013mbar
            << " cm-3" << std::endl;

  // Set the Extrapolation: allowed strings: "constant", "linear", "exponential"
  // - default = linear
  MediumGas gas_0007mbar_cte, gas_1013mbar_cte;
  gas_0007mbar_cte.LoadGasFile("ic4h10_0007mbar_100-25kVcm.gas");
  gas_1013mbar_cte.LoadGasFile("ic4h10_1013mbar_100-100kVcm.gas");
  gas_0007mbar_cte.SetExtrapolationMethodTownsend("constant", "constant");
  gas_1013mbar_cte.SetExtrapolationMethodTownsend("constant", "constant");
  MediumGas gas_0007mbar_lin, gas_1013mbar_lin;
  gas_0007mbar_lin.LoadGasFile("ic4h10_0007mbar_100-25kVcm.gas");
  gas_1013mbar_lin.LoadGasFile("ic4h10_1013mbar_100-100kVcm.gas");
  gas_0007mbar_lin.SetExtrapolationMethodTownsend("linear", "linear");
  gas_1013mbar_lin.SetExtrapolationMethodTownsend("linear", "linear");
  MediumGas gas_0007mbar_exp, gas_1013mbar_exp;
  gas_0007mbar_exp.LoadGasFile("ic4h10_0007mbar_100-25kVcm.gas");
  gas_1013mbar_exp.LoadGasFile("ic4h10_1013mbar_100-100kVcm.gas");
  gas_0007mbar_exp.SetExtrapolationMethodTownsend("exponential", "exponential");
  gas_1013mbar_exp.SetExtrapolationMethodTownsend("exponential", "exponential");
  // to be developed :: "logarithmic"

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  // PART 1 :: TGraph with Markers for the Field Grid Points
  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  // Get field grid
  // assume only electric field, no B-field
  std::vector<double> efields_0007mbar, efields_1013mbar;
  std::vector<double> bfields;
  std::vector<double> angles;
  gas_0007mbar.GetFieldGrid(efields_0007mbar, bfields, angles);
  const auto nE_0007mbar = efields_0007mbar.size();
  gas_1013mbar.GetFieldGrid(efields_1013mbar, bfields, angles);
  const auto nE_1013mbar = efields_1013mbar.size();

  std::vector<double> al_0007mbar, al_1013mbar;

  size_t i = 0;  // index for electric field
  size_t j = 0;  // index for magnetic field
  size_t k = 0;  // index for angle E^B

  for (i = 0; i < nE_0007mbar; ++i) {
    double alpha = 0.;
    gas_0007mbar.GetElectronTownsend(i, j, k, alpha);
    alpha = exp(alpha);
    alpha = alpha / density_0007mbar;  // alpha/N
    al_0007mbar.push_back(alpha);
  }

  for (i = 0; i < nE_1013mbar; ++i) {
    double alpha = 0.;
    gas_1013mbar.GetElectronTownsend(i, j, k, alpha);
    alpha = exp(alpha);
    alpha = alpha / density_1013mbar;  // alpha/N
    al_1013mbar.push_back(alpha);
  }

  // make TGraphs vs Electric Field for Field Grid Points
  TGraph* gr_al_0007mbar =
      new TGraph(nE_0007mbar, &efields_0007mbar[0], &al_0007mbar[0]);
  TGraph* gr_al_1013mbar =
      new TGraph(nE_1013mbar, &efields_1013mbar[0], &al_1013mbar[0]);

  gr_al_0007mbar->SetMarkerStyle(20);  // full circle
  gr_al_0007mbar->SetMarkerSize(1.25);
  gr_al_0007mbar->SetMarkerColor(kOrange + 7);
  gr_al_0007mbar->SetLineColor(kOrange + 7);
  gr_al_0007mbar->SetLineWidth(2);

  gr_al_1013mbar->SetMarkerStyle(20);  // full circle
  gr_al_1013mbar->SetMarkerSize(1.25);
  gr_al_1013mbar->SetMarkerColor(kOrange - 3);
  gr_al_1013mbar->SetLineColor(kOrange - 3);
  gr_al_1013mbar->SetLineWidth(2);

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  // PART 2 :: continuous TGraph for Intraplated / Extrapolated points
  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  // adequate range of points
  double xmin_lin = 100;
  double xmax_lin = 500E3;
  double xmin_log = log10(xmin_lin);
  double xmax_log = log10(xmax_lin);
  const int npoints =
      std::round(xmax_log - xmin_log) * 100;  // 100 datapoints / decade

  std::vector<double> xrange_10log, xrange_lin;
  for (int i = 0; i < npoints; ++i) {
    double newpoint = xmin_log + i * (xmax_log - xmin_log) / (npoints - 1);
    xrange_10log.push_back(newpoint);
    xrange_lin.push_back(pow(10, newpoint));
  }

  // get values of Townsend coefficient
  // make different curves for different extrapolation methods
  std::vector<double> al_0007mbar_smooth, al_1013mbar_smooth;
  std::vector<double> al_0007mbar_cte, al_1013mbar_cte;
  std::vector<double> al_0007mbar_lin, al_1013mbar_lin;
  std::vector<double> al_0007mbar_exp, al_1013mbar_exp;

  for (int i = 0; i < npoints; ++i) {
    double alpha = 0.;
    // 0007mbar default
    gas_0007mbar.ElectronTownsend(xrange_lin[i], 0, 0, 0, 0, 0,
                                  alpha);  // ey,ez,bx,by,bz = 0
    alpha = alpha / density_0007mbar;      // alpha/N
    al_0007mbar_smooth.push_back(alpha);
    // 0007mbar constant
    gas_0007mbar_cte.ElectronTownsend(xrange_lin[i], 0, 0, 0, 0, 0,
                                      alpha);  // ey,ez,bx,by,bz = 0
    alpha = alpha / density_0007mbar;          // alpha/N
    al_0007mbar_cte.push_back(alpha);
    // 0007mbar linear
    gas_0007mbar_lin.ElectronTownsend(xrange_lin[i], 0, 0, 0, 0, 0,
                                      alpha);  // ey,ez,bx,by,bz = 0
    alpha = alpha / density_0007mbar;          // alpha/N
    al_0007mbar_lin.push_back(alpha);
    // 0007mbar exponential
    gas_0007mbar_exp.ElectronTownsend(xrange_lin[i], 0, 0, 0, 0, 0,
                                      alpha);  // ey,ez,bx,by,bz = 0
    alpha = alpha / density_0007mbar;          // alpha/N
    al_0007mbar_exp.push_back(alpha);
    // 1013mbar default
    gas_1013mbar.ElectronTownsend(xrange_lin[i], 0, 0, 0, 0, 0, alpha);
    alpha = alpha / density_1013mbar;  // alpha/N
    al_1013mbar_smooth.push_back(alpha);
    // 1013mbar constant
    gas_1013mbar_cte.ElectronTownsend(xrange_lin[i], 0, 0, 0, 0, 0, alpha);
    alpha = alpha / density_1013mbar;  // alpha/N
    al_1013mbar_cte.push_back(alpha);
    // 1013mbar linear
    gas_1013mbar_lin.ElectronTownsend(xrange_lin[i], 0, 0, 0, 0, 0, alpha);
    alpha = alpha / density_1013mbar;  // alpha/N
    al_1013mbar_lin.push_back(alpha);
    // 1013mbar exponential
    gas_1013mbar_exp.ElectronTownsend(xrange_lin[i], 0, 0, 0, 0, 0, alpha);
    alpha = alpha / density_1013mbar;  // alpha/N
    al_1013mbar_exp.push_back(alpha);
  }

  // make TGraphs vs Electric Field for smooth curves
  TGraph* gr_al_0007mbar_smooth =
      new TGraph(npoints, &xrange_lin[0], &al_0007mbar_smooth[0]);
  TGraph* gr_al_1013mbar_smooth =
      new TGraph(npoints, &xrange_lin[0], &al_1013mbar_smooth[0]);
  gr_al_0007mbar_smooth->SetLineWidth(2);
  gr_al_0007mbar_smooth->SetLineColor(kOrange + 7);
  gr_al_1013mbar_smooth->SetLineWidth(2);
  gr_al_1013mbar_smooth->SetLineColor(kOrange - 3);

  // constant
  TGraph* gr_al_0007mbar_cte =
      new TGraph(npoints, &xrange_lin[0], &al_0007mbar_cte[0]);
  TGraph* gr_al_1013mbar_cte =
      new TGraph(npoints, &xrange_lin[0], &al_1013mbar_cte[0]);
  gr_al_0007mbar_cte->SetLineWidth(2);
  gr_al_0007mbar_cte->SetLineColor(kOrange + 7);
  gr_al_0007mbar_cte->SetLineStyle(7);
  gr_al_1013mbar_cte->SetLineWidth(2);
  gr_al_1013mbar_cte->SetLineColor(kOrange - 3);
  gr_al_1013mbar_cte->SetLineStyle(7);
  // linear
  TGraph* gr_al_0007mbar_lin =
      new TGraph(npoints, &xrange_lin[0], &al_0007mbar_lin[0]);
  TGraph* gr_al_1013mbar_lin =
      new TGraph(npoints, &xrange_lin[0], &al_1013mbar_lin[0]);
  gr_al_0007mbar_lin->SetLineWidth(2);
  gr_al_0007mbar_lin->SetLineColor(kOrange + 7);
  gr_al_0007mbar_lin->SetLineStyle(9);
  gr_al_1013mbar_lin->SetLineWidth(2);
  gr_al_1013mbar_lin->SetLineColor(kOrange - 3);
  gr_al_1013mbar_lin->SetLineStyle(9);
  // exponential
  TGraph* gr_al_0007mbar_exp =
      new TGraph(npoints, &xrange_lin[0], &al_0007mbar_exp[0]);
  TGraph* gr_al_1013mbar_exp =
      new TGraph(npoints, &xrange_lin[0], &al_1013mbar_exp[0]);
  gr_al_0007mbar_exp->SetLineWidth(2);
  gr_al_0007mbar_exp->SetLineColor(kOrange + 7);
  gr_al_0007mbar_exp->SetLineStyle(10);
  gr_al_1013mbar_exp->SetLineWidth(2);
  gr_al_1013mbar_exp->SetLineColor(kOrange - 3);
  gr_al_1013mbar_exp->SetLineStyle(10);

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  // PART 3 :: plot together
  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  TLegend* l1 = new TLegend(0.175, 0.80, 0.575, 0.90);
  l1->AddEntry(gr_al_0007mbar, "iC_{4}H_{10} (100%)     7 mbar", "PL");
  l1->AddEntry(gr_al_1013mbar, "iC_{4}H_{10} (100%) 1013 mbar", "PL");

  TLegend* l2 = new TLegend(0.175, 0.65, 0.575, 0.80);
  l2->AddEntry(gr_al_0007mbar_cte, "constant extrapolation", "L");
  l2->AddEntry(gr_al_0007mbar_lin, "linear extrapolation", "L");
  l2->AddEntry(gr_al_0007mbar_exp, "exponential extrapolation", "L");

  TCanvas* c1 = new TCanvas("c1", "c1", 800, 800);
  c1->SetLeftMargin(0.150);
  c1->SetLogy();
  c1->SetLogx();
  c1->cd();
  auto* h1 = c1->DrawFrame(90, 1e-24, 6.25e5, 1e-10);
  c1->Update();
  gr_al_0007mbar->Draw("P");
  gr_al_1013mbar->Draw("PSame");
  // gr_al_0007mbar_smooth->Draw("Lsame");
  // gr_al_1013mbar_smooth->Draw("Lsame");
  gr_al_0007mbar_cte->Draw("Lsame");
  gr_al_1013mbar_cte->Draw("Lsame");
  gr_al_0007mbar_lin->Draw("Lsame");
  gr_al_1013mbar_lin->Draw("Lsame");
  gr_al_0007mbar_exp->Draw("Lsame");
  gr_al_1013mbar_exp->Draw("Lsame");

  gr_al_0007mbar->Draw("PSame");
  gr_al_1013mbar->Draw("PSame");
  h1->GetXaxis()->SetTitle("Electric Field (V/cm)");
  h1->GetYaxis()->SetTitle("#alpha/N (cm^{2})");
  l1->Draw();
  l2->Draw();
  c1->Update();
  c1->SaveAs("Isobutane_Townsend_Extrapolated.pdf");

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  // PART 4 :: Plot vs Reduced Electric Field
  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  // Calibrate x-axis to Td
  std::vector<double> efields_0007mbar_Td, efields_1013mbar_Td;
  for (i = 0; i < nE_0007mbar; ++i) {
    efields_0007mbar_Td.push_back(efields_0007mbar[i] / density_0007mbar *
                                  1E17);
  }
  for (i = 0; i < nE_1013mbar; ++i) {
    efields_1013mbar_Td.push_back(efields_1013mbar[i] / density_1013mbar *
                                  1E17);
  }
  // Make new TGraphs
  TGraph* gr_al_Td_0007mbar =
      new TGraph(nE_0007mbar, &efields_0007mbar_Td[0], &al_0007mbar[0]);
  TGraph* gr_al_Td_1013mbar =
      new TGraph(nE_1013mbar, &efields_1013mbar_Td[0], &al_1013mbar[0]);

  gr_al_Td_0007mbar->SetMarkerStyle(20);  // full circle
  gr_al_Td_0007mbar->SetMarkerSize(1.25);
  gr_al_Td_0007mbar->SetMarkerColor(kOrange + 7);
  gr_al_Td_0007mbar->SetLineWidth(2);
  gr_al_Td_0007mbar->SetLineColor(kOrange + 7);

  gr_al_Td_1013mbar->SetMarkerStyle(20);  // full circle
  gr_al_Td_1013mbar->SetMarkerSize(1.25);
  gr_al_Td_1013mbar->SetMarkerColor(kOrange - 3);
  gr_al_Td_1013mbar->SetLineColor(kOrange - 3);
  gr_al_Td_1013mbar->SetLineWidth(2);

  // new range of points for Td
  std::vector<double> xrange_lin_td_0007mbar, xrange_lin_td_1013mbar;
  for (int i = 0; i < npoints; ++i) {
    xrange_lin_td_0007mbar.push_back(xrange_lin[i] / density_0007mbar * 1E17);
    xrange_lin_td_1013mbar.push_back(xrange_lin[i] / density_1013mbar * 1E17);
  }
  // Make new TGraphs
  TGraph* gr_al_Td_0007mbar_smooth =
      new TGraph(npoints, &xrange_lin_td_0007mbar[0], &al_0007mbar_smooth[0]);
  TGraph* gr_al_Td_1013mbar_smooth =
      new TGraph(npoints, &xrange_lin_td_1013mbar[0], &al_1013mbar_smooth[0]);
  gr_al_Td_0007mbar_smooth->SetLineWidth(2);
  gr_al_Td_0007mbar_smooth->SetLineColor(kOrange + 7);
  gr_al_Td_1013mbar_smooth->SetLineWidth(2);
  gr_al_Td_1013mbar_smooth->SetLineColor(kOrange - 3);

  // constant
  TGraph* gr_al_Td_0007mbar_cte =
      new TGraph(npoints, &xrange_lin_td_0007mbar[0], &al_0007mbar_cte[0]);
  TGraph* gr_al_Td_1013mbar_cte =
      new TGraph(npoints, &xrange_lin_td_1013mbar[0], &al_1013mbar_cte[0]);
  gr_al_Td_0007mbar_cte->SetLineWidth(2);
  gr_al_Td_0007mbar_cte->SetLineColor(kOrange + 7);
  gr_al_Td_0007mbar_cte->SetLineStyle(7);
  gr_al_Td_1013mbar_cte->SetLineWidth(2);
  gr_al_Td_1013mbar_cte->SetLineColor(kOrange - 3);
  gr_al_Td_1013mbar_cte->SetLineStyle(7);
  // linear
  TGraph* gr_al_Td_0007mbar_lin =
      new TGraph(npoints, &xrange_lin_td_0007mbar[0], &al_0007mbar_lin[0]);
  TGraph* gr_al_Td_1013mbar_lin =
      new TGraph(npoints, &xrange_lin_td_1013mbar[0], &al_1013mbar_lin[0]);
  gr_al_Td_0007mbar_lin->SetLineWidth(2);
  gr_al_Td_0007mbar_lin->SetLineColor(kOrange + 7);
  gr_al_Td_0007mbar_lin->SetLineStyle(9);
  gr_al_Td_1013mbar_lin->SetLineWidth(2);
  gr_al_Td_1013mbar_lin->SetLineColor(kOrange - 3);
  gr_al_Td_1013mbar_lin->SetLineStyle(9);
  // exponential
  TGraph* gr_al_Td_0007mbar_exp =
      new TGraph(npoints, &xrange_lin_td_0007mbar[0], &al_0007mbar_exp[0]);
  TGraph* gr_al_Td_1013mbar_exp =
      new TGraph(npoints, &xrange_lin_td_1013mbar[0], &al_1013mbar_exp[0]);
  gr_al_Td_0007mbar_exp->SetLineWidth(2);
  gr_al_Td_0007mbar_exp->SetLineColor(kOrange + 7);
  gr_al_Td_0007mbar_exp->SetLineStyle(10);
  gr_al_Td_1013mbar_exp->SetLineWidth(2);
  gr_al_Td_1013mbar_exp->SetLineColor(kOrange - 3);
  gr_al_Td_1013mbar_exp->SetLineStyle(10);

  TCanvas* c2 = new TCanvas("c2", "c2", 800, 800);
  c2->SetLeftMargin(0.150);
  c2->SetLogy();
  c2->SetLogx();
  c2->cd();
  auto* h2 = c2->DrawFrame(0.20, 1e-24, 525e3, 1e-10);
  c2->Update();
  gr_al_Td_0007mbar->Draw("P");
  gr_al_Td_1013mbar->Draw("PSame");
  // gr_al_Td_0007mbar_smooth->Draw("Lsame");
  // gr_al_Td_1013mbar_smooth->Draw("Lsame");
  gr_al_Td_0007mbar_cte->Draw("Lsame");
  gr_al_Td_1013mbar_cte->Draw("Lsame");
  gr_al_Td_0007mbar_lin->Draw("Lsame");
  gr_al_Td_1013mbar_lin->Draw("Lsame");
  gr_al_Td_0007mbar_exp->Draw("Lsame");
  gr_al_Td_1013mbar_exp->Draw("Lsame");
  gr_al_Td_0007mbar->Draw("PSame");
  gr_al_Td_1013mbar->Draw("PSame");
  h2->GetXaxis()->SetTitle("Reduced Electric Field (Td)");
  h2->GetYaxis()->SetTitle("#alpha/N (cm^{2})");
  l1->Draw();
  l2->Draw();
  c2->Update();
  c2->SaveAs("Isobutane_Townsend_Extrapolated_Td.pdf");

  app.Run();
}
