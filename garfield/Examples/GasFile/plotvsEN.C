#include <cmath>
#include <cstddef>
#include <iostream>
#include <vector>

#include "Garfield/MediumGas.hh"
#include "Garfield/ViewMedium.hh"
#include "TApplication.h"
#include "TCanvas.h"
#include "TGaxis.h"
#include "TGraph.h"
#include "TH1.h"
#include "TLegend.h"
#include "TStyle.h"
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

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  // PART 1 :: Plot information from two gasfiles in a single plot
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

  std::vector<double> ve_0007mbar, ve_1013mbar;
  std::vector<double> al_0007mbar, al_1013mbar;

  size_t i = 0;  // index for electric field
  size_t j = 0;  // index for magnetic field
  size_t k = 0;  // index for angle E^B

  // Markers for the grid points
  for (i = 0; i < nE_0007mbar; ++i) {
    double ve = 0.;
    gas_0007mbar.GetElectronVelocityE(i, j, k, ve);
    // Convert from cm/ns to cm/us.
    ve *= 1.e3;
    double alpha = 0.;
    gas_0007mbar.GetElectronTownsend(i, j, k, alpha);
    alpha = exp(alpha);
    ve_0007mbar.push_back(ve);
    al_0007mbar.push_back(alpha);
  }

  for (i = 0; i < nE_1013mbar; ++i) {
    double ve = 0.;
    gas_1013mbar.GetElectronVelocityE(i, j, k, ve);
    // Convert from cm/ns to cm/us.
    ve *= 1.e3;
    double alpha = 0.;
    gas_1013mbar.GetElectronTownsend(i, j, k, alpha);
    alpha = exp(alpha);
    ve_1013mbar.push_back(ve);
    al_1013mbar.push_back(alpha);
  }

  // - - - - - - - - - - - - - - - - - -
  // Electron Energy calculated by Magboltz
  // - - - - - - - - - - - - - - - - - -
  // read from Magboltz logfiles - this information is not saved in the gastable
  // - also uncertainties are not saved in gastable
  const int nef_0007mbar = 15;
  std::vector<double> ef_0007mbar = {100,     148.348, 220.071, 326.471,
                                     484.313, 718.468, 1065.83, 1581.14,
                                     2345.59, 3479.63, 5161.96, 7657.65,
                                     11360,   16852.3, 25000};  // units: V/cm
  std::vector<double> ee_0007mbar = {1.6898,  2.3188,  3.0607,  3.8370,
                                     4.6023,  5.4482,  6.4786,  7.8224,
                                     9.7010,  12.5488, 17.2406, 25.7509,
                                     43.9548, 97.8900, 384.3224};  // units: eV
  const int nef_1013mbar = 20;
  std::vector<double> ef_1013mbar = {
      100,     143.845, 206.914, 297.635, 428.133, 615.848, 885.867,
      1274.27, 1832.98, 2636.65, 3792.69, 5455.59, 7847.6,  11288.4,
      16237.8, 23357.2, 33598.2, 48329.3, 69519.3, 100000};
  std::vector<double> ee_1013mbar = {0.0402, 0.0426, 0.0467, 0.0536, 0.0643,
                                     0.0808, 0.1059, 0.1413, 0.1893, 0.2581,
                                     0.3725, 0.5783, 0.9085, 1.3440, 1.8614,
                                     2.4684, 3.1642, 3.8817, 4.5844, 5.3569};

  // - - - - - - - - - - - - - - - - - -
  // Plots vs Electric Field E
  // - - - - - - - - - - - - - - - - - -
  // make TGraphs vs Electric Field
  TGraph* gr_ve_0007mbar =
      new TGraph(nE_0007mbar, &efields_0007mbar[0], &ve_0007mbar[0]);
  TGraph* gr_ve_1013mbar =
      new TGraph(nE_1013mbar, &efields_1013mbar[0], &ve_1013mbar[0]);
  TGraph* gr_al_0007mbar =
      new TGraph(nE_0007mbar, &efields_0007mbar[0], &al_0007mbar[0]);
  TGraph* gr_al_1013mbar =
      new TGraph(nE_1013mbar, &efields_1013mbar[0], &al_1013mbar[0]);
  TGraph* gr_ee_0007mbar =
      new TGraph(nef_0007mbar, &ef_0007mbar[0], &ee_0007mbar[0]);
  TGraph* gr_ee_1013mbar =
      new TGraph(nef_1013mbar, &ef_1013mbar[0], &ee_1013mbar[0]);

  gr_ve_0007mbar->SetMarkerStyle(24);  // open circle
  gr_ve_1013mbar->SetMarkerStyle(20);  // full circle
  gr_ve_0007mbar->SetMarkerColor(kOrange + 7);
  gr_ve_0007mbar->SetLineColor(kOrange + 7);
  gr_ve_0007mbar->SetLineStyle(7);
  gr_ve_1013mbar->SetMarkerColor(kOrange - 3);
  gr_ve_1013mbar->SetLineColor(kOrange - 3);
  gr_ve_1013mbar->SetLineStyle(9);

  gr_al_0007mbar->SetMarkerStyle(24);  // open circle
  gr_al_1013mbar->SetMarkerStyle(20);  // full circle
  gr_al_0007mbar->SetMarkerColor(kOrange + 7);
  gr_al_0007mbar->SetLineColor(kOrange + 7);
  gr_al_0007mbar->SetLineStyle(7);
  gr_al_1013mbar->SetMarkerColor(kOrange - 3);
  gr_al_1013mbar->SetLineColor(kOrange - 3);
  gr_al_1013mbar->SetLineStyle(9);

  gr_ee_0007mbar->SetMarkerStyle(24);  // open circle
  gr_ee_1013mbar->SetMarkerStyle(20);  // full circle
  gr_ee_0007mbar->SetMarkerColor(kOrange + 7);
  gr_ee_0007mbar->SetLineColor(kOrange + 7);
  gr_ee_0007mbar->SetLineStyle(7);
  gr_ee_1013mbar->SetMarkerColor(kOrange - 3);
  gr_ee_1013mbar->SetLineColor(kOrange - 3);
  gr_ee_1013mbar->SetLineStyle(9);

  TLegend* l2 = new TLegend(0.40, 0.15, 0.80, 0.30);
  l2->AddEntry(gr_ve_0007mbar, "iC_{4}H_{10} (100%)     7 mbar", "PL");
  l2->AddEntry(gr_ve_1013mbar, "iC_{4}H_{10} (100%) 1013 mbar", "PL");

  TLegend* l3 = new TLegend(0.15, 0.70, 0.55, 0.85);
  l3->AddEntry(gr_al_0007mbar, "iC_{4}H_{10} (100%)     7 mbar", "PL");
  l3->AddEntry(gr_al_1013mbar, "iC_{4}H_{10} (100%) 1013 mbar", "PL");

  TCanvas* c2 = new TCanvas("c2", "c2", 800, 800);
  c2->SetLeftMargin(0.125);
  c2->SetLogy();
  c2->SetLogx();
  c2->cd();
  auto* h2 = c2->DrawFrame(90, 1e-1, 1.25e5, 1000);
  c2->Update();
  gr_ve_0007mbar->Draw("PC");
  gr_ve_1013mbar->Draw("PCSame");
  h2->GetXaxis()->SetTitle("Electric Field (V/cm)");
  h2->GetYaxis()->SetTitle("Electron Drift Velocity (cm/us)");
  l2->Draw();
  c2->Update();
  c2->SaveAs("Isobutane_ElectronVelocity.pdf");

  TCanvas* c3 = new TCanvas("c3", "c3", 800, 800);
  c3->SetLeftMargin(0.125);
  c3->SetLogy();
  c3->SetLogx();
  c3->cd();
  auto* h3 = c3->DrawFrame(90, 1e-5, 1.25e5, 2000);
  c3->Update();
  gr_al_0007mbar->Draw("PC");
  gr_al_1013mbar->Draw("PCSame");
  h3->GetXaxis()->SetTitle("Electric Field (V/cm)");
  h3->GetYaxis()->SetTitle("Townsend Coefficient (cm^{-1})");
  l2->Draw();
  c3->Update();
  c3->SaveAs("Isobutane_Townsend.pdf");

  TCanvas* c4 = new TCanvas("c4", "c4", 800, 800);
  c4->SetLeftMargin(0.125);
  c4->SetLogy();
  c4->SetLogx();
  c4->cd();
  auto* h4 = c4->DrawFrame(90, 1e-3, 1.25e5, 1000);
  gr_ee_0007mbar->Draw("PC");
  gr_ee_1013mbar->Draw("PCSame");
  h4->GetXaxis()->SetTitle("Electric Field (V/cm)");
  h4->GetYaxis()->SetTitle("Electron Energy (eV)");
  l2->Draw();
  c4->Update();
  c4->SaveAs("Isobutane_ElectronEnergy.pdf");

  // - - - - - - - - - - - - - - - - - -
  // Plots vs Reduced Electric Field E/N
  // - - - - - - - - - - - - - - - - - -
  // original unit: V/cm/cm-3 = Vcm2
  // plasma physics unit: 1 Td = 1E-17 Vcm2
  std::vector<double> en_0007mbar_Td, en_1013mbar_Td;
  for (i = 0; i < nE_0007mbar; ++i) {
    en_0007mbar_Td.push_back(efields_0007mbar[i] / density_0007mbar * 1E17);
  }
  for (i = 0; i < nE_1013mbar; ++i) {
    en_1013mbar_Td.push_back(efields_1013mbar[i] / density_1013mbar * 1E17);
  }
  // plot also Townsend alpha/N
  std::vector<double> an_0007mbar, an_1013mbar;
  for (i = 0; i < nE_0007mbar; ++i) {
    an_0007mbar.push_back(al_0007mbar[i] / density_0007mbar);
  }
  for (i = 0; i < nE_1013mbar; ++i) {
    an_1013mbar.push_back(al_1013mbar[i] / density_1013mbar);
  }

  // make TGraphs vs Reduced Electric Field
  TGraph* gr_ve_0007mbar_Td =
      new TGraph(nE_0007mbar, &en_0007mbar_Td[0], &ve_0007mbar[0]);
  TGraph* gr_ve_1013mbar_Td =
      new TGraph(nE_1013mbar, &en_1013mbar_Td[0], &ve_1013mbar[0]);
  TGraph* gr_al_0007mbar_Td =
      new TGraph(nE_0007mbar, &en_0007mbar_Td[0], &an_0007mbar[0]);
  TGraph* gr_al_1013mbar_Td =
      new TGraph(nE_1013mbar, &en_1013mbar_Td[0], &an_1013mbar[0]);
  TGraph* gr_ee_0007mbar_Td =
      new TGraph(nE_0007mbar, &en_0007mbar_Td[0], &ee_0007mbar[0]);
  TGraph* gr_ee_1013mbar_Td =
      new TGraph(nE_1013mbar, &en_1013mbar_Td[0], &ee_1013mbar[0]);

  gr_ve_0007mbar_Td->SetMarkerStyle(24);  // open circle
  gr_ve_1013mbar_Td->SetMarkerStyle(20);  // full circle
  gr_ve_0007mbar_Td->SetMarkerColor(kOrange + 7);
  gr_ve_0007mbar_Td->SetLineColor(kOrange + 7);
  gr_ve_0007mbar_Td->SetLineStyle(7);
  gr_ve_1013mbar_Td->SetMarkerColor(kOrange - 3);
  gr_ve_1013mbar_Td->SetLineColor(kOrange - 3);
  gr_ve_1013mbar_Td->SetLineStyle(9);

  gr_al_0007mbar_Td->SetMarkerStyle(24);  // open circle
  gr_al_1013mbar_Td->SetMarkerStyle(20);  // full circle
  gr_al_0007mbar_Td->SetMarkerColor(kOrange + 7);
  gr_al_0007mbar_Td->SetLineColor(kOrange + 7);
  gr_al_0007mbar_Td->SetLineStyle(7);
  gr_al_1013mbar_Td->SetMarkerColor(kOrange - 3);
  gr_al_1013mbar_Td->SetLineColor(kOrange - 3);
  gr_al_1013mbar_Td->SetLineStyle(9);

  gr_ee_0007mbar_Td->SetMarkerStyle(24);  // open circle
  gr_ee_1013mbar_Td->SetMarkerStyle(20);  // full circle
  gr_ee_0007mbar_Td->SetMarkerColor(kOrange + 7);
  gr_ee_0007mbar_Td->SetLineColor(kOrange + 7);
  gr_ee_0007mbar_Td->SetLineStyle(7);
  gr_ee_1013mbar_Td->SetMarkerColor(kOrange - 3);
  gr_ee_1013mbar_Td->SetLineColor(kOrange - 3);
  gr_ee_1013mbar_Td->SetLineStyle(9);

  TCanvas* c5 = new TCanvas("c5", "c5", 800, 800);
  c5->SetLeftMargin(0.135);
  c5->SetBottomMargin(0.135);
  c5->SetTopMargin(0.135);
  c5->SetLogy();
  c5->SetLogx();
  c5->cd();
  gStyle->SetPadTickX(1);
  gStyle->SetPadTickY(1);
  auto* h5 = c5->DrawFrame(0.1, 0.1, 3e4, 1000);
  c5->Update();
  gr_ve_0007mbar_Td->Draw("PC");  // drop "A" drawoption if one uses DrawFrame
  gr_ve_1013mbar_Td->Draw("PCSame");
  h5->GetXaxis()->SetTitle("E/#it{N} (Td)");
  h5->GetYaxis()->SetTitle("Electron Drift Velocity (cm/us)");
  l2->Draw();
  TGaxis* axis05 =
      new TGaxis(0.1, 1000, 3e4, 1000, 0.1 * density_1013mbar / 1E17,
                 3e4 * density_1013mbar / 1E17, 510, "GL+=");
  axis05->SetTextFont(gStyle->GetTextFont());
  axis05->SetLabelFont(gStyle->GetLabelFont("X"));
  axis05->SetLabelOffset(-0.075);
  axis05->SetTitleOffset(1.25);
  axis05->SetTitle("Electric Field at 1 atm (V/cm)");
  axis05->Draw();
  c5->Update();
  c5->SaveAs("Isobutane_ElectronVelocity_Td.pdf");

  TCanvas* c6 = new TCanvas("c6", "c6", 800, 800);
  c6->SetLeftMargin(0.135);
  c6->SetBottomMargin(0.135);
  c6->SetTopMargin(0.135);
  c6->SetLogy();
  c6->SetLogx();
  c6->cd();
  auto* h6 = c6->DrawFrame(0.1, 1e-24, 3e4, 5e-15);
  gr_al_0007mbar_Td->Draw("PC");  // drop "A" drawoption if one uses DrawFrame
  gr_al_1013mbar_Td->Draw("PCSame");
  h6->GetXaxis()->SetTitle("E/#it{N} (Td)");
  h6->GetYaxis()->SetTitle("#it{#alpha}/#it{N} (cm^{2})");
  l3->Draw();
  TGaxis* axis06 =
      new TGaxis(0.1, 2000, 3e4, 2000, 0.1 * density_1013mbar / 1E17,
                 3e4 * density_1013mbar / 1E17, 510, "GL+=");
  axis06->SetTextFont(gStyle->GetTextFont());
  axis06->SetLabelFont(gStyle->GetLabelFont("X"));
  axis06->SetLabelOffset(-0.075);
  axis06->SetTitleOffset(1.25);
  axis06->SetTitle("Electric Field at 1 atm (V/cm)");
  axis06->Draw();
  c6->Update();
  c6->SaveAs("Isobutane_Townsend_Td.pdf");

  TCanvas* c7 = new TCanvas("c7", "c7", 800, 800);
  c7->SetLeftMargin(0.135);
  c7->SetBottomMargin(0.135);
  c7->SetTopMargin(0.135);
  c7->SetLogy();
  c7->SetLogx();
  c7->cd();
  auto* h7 = c7->DrawFrame(0.1, 0.01, 3e4, 1000);
  gr_ee_0007mbar_Td->Draw("PC");  // drop "A" drawoption if one uses DrawFrame
  gr_ee_1013mbar_Td->Draw("PCSame");
  h7->GetXaxis()->SetTitle("E/#it{N} (Td)");
  h7->GetYaxis()->SetTitle("Electron Energy (eV)");
  l2->Draw();
  TGaxis* axis07 =
      new TGaxis(0.1, 1000, 3e4, 1000, 0.1 * density_1013mbar / 1E17,
                 3e4 * density_1013mbar / 1E17, 510, "GL+=");
  axis07->SetTextFont(gStyle->GetTextFont());
  axis07->SetLabelFont(gStyle->GetLabelFont("X"));
  axis07->SetLabelOffset(-0.075);
  axis07->SetTitleOffset(1.25);
  axis07->SetTitle("Electric Field at 1 atm (V/cm)");
  axis07->Draw();
  c7->Update();
  c7->SaveAs("Isobutane_ElectronEnergy_Td.pdf");

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  // PART 2 :: Use the built-in option to plot vs Reduced Efield (E/N and E/P)
  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  ViewMedium view(&gas_0007mbar);

  // Plot Drift Velocity vs E/N
  TCanvas cV("cV", "", 600, 600);
  view.SetCanvas(&cV);
  view.PlotElectronVelocity('r');

  // Plot Diffusion vs E/N
  TCanvas cD("cD", "", 600, 600);
  view.SetCanvas(&cD);
  view.PlotElectronDiffusion('r');

  // Plot Alpha vs E/N
  TCanvas cT("cT", "", 600, 600);
  view.SetCanvas(&cT);
  view.PlotElectronTownsend('r');

  // Plot Alpha vs E/P
  TCanvas cP("cP", "", 600, 600);
  view.SetCanvas(&cP);
  view.PlotElectronTownsend('p');

  // Plot Alpha/N vs E/N
  TCanvas cAN("cAN", "", 600, 600);
  view.SetCanvas(&cAN);
  view.PlotElectronReducedTownsendN('r');

  // Plot Alpha/p vs E/p
  TCanvas cAP("cAP", "", 600, 600);
  view.SetCanvas(&cAP);
  view.PlotElectronReducedTownsendP('p');

  app.Run();
}
