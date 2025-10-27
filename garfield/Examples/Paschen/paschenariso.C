#include <TApplication.h>
#include <TCanvas.h>
#include <TGraph.h>
#include <TH1F.h>
#include <TLegend.h>
#include <TStyle.h>

#include <cmath>

#include "Garfield/MediumMagboltz.hh"

using namespace Garfield;

int main(int argc, char* argv[]) {
  TApplication app("app", &argc, argv);

  gStyle->SetLabelFont(132, "xyz");
  gStyle->SetTitleFont(132, "xyz");
  gStyle->SetLegendFont(132);
  gStyle->SetTitleSize(0.044, "xyz");
  gStyle->SetLabelSize(0.038, "xyz");
  gStyle->SetTickLength(0.035, "xyz");

  // Open a canvas with a frame
  TCanvas c1("c1", "Paschen curves for Ar/iC_{4}H_{10}", 21, 28, 500, 527);
  c1.SetLogx();
  c1.SetLogy();
  c1.SetGrid();
  c1.SetTicks();
  c1.SetRightMargin(0.02);
  c1.SetLeftMargin(0.12);
  c1.SetTopMargin(0.02);
  c1.SetBottomMargin(0.09);

  auto hframe = c1.DrawFrame(3.e-4, 100., 1., 10000.,
                             ";d #upoint p [cm #upoint bar];V_{B} [V]");
  hframe->GetXaxis()->SetLabelOffset(0.007);
  hframe->GetXaxis()->SetTitleOffset(1.04);
  hframe->GetYaxis()->SetLabelOffset(0.003);

  // Create a legend box.
  TLegend* leg = new TLegend(0.14, 0.48, 0.7, 0.97);
  leg->SetHeader("Paschen curves in Ar/iC_{4}H_{10}");

  // Paschen curve Townsend parametrisation for Ar
  for (int ig = -3; ig < 0; ig++) {
    const double gamma = pow(10.0, ig);
    const double A_ar = 8.63 * 1000.0;   // 1/Pa.m
    const double B_ar = 132.0 * 1000.0;  // V/Pa.m
    const double pdmin = 1.01 * log1p(1. / gamma) / A_ar;
    const double pdmax = 1.;

    double pd1[200], vb1[200];
    for (int i = 0; i < 200; i++) {
      pd1[i] = pdmin * pow(pdmax / pdmin, i / 199.0);
      vb1[i] = B_ar * pd1[i] / (log(A_ar / log1p(1. / gamma)) + log(pd1[i]));
    }
    TGraph* g1 = new TGraph(200, pd1, vb1);
    g1->SetLineColor(kAzure + (ig + 1));
    g1->SetLineWidth(2);
    g1->Draw("lsame");
    char buf[100];
    snprintf(buf, 100, "Townsend, Pure Ar, #gamma = 10^{%d}", ig);
    leg->AddEntry(g1, buf, "l");
  }

  // Curves from M.J. Druyvesteyn and F.M. Penning, Rev Mod Phys 12 (1940)
  // 87-176. The Mechanism of Electrical Discharges in Gases of Low Pressure.
  std::vector<double> pdFe = {0.71755, 0.9843,  1.42324, 1.95233, 2.93121,
                              4.88989, 9.77222, 19.5293, 29.3212, 48.9141,
                              97.7525, 195.354, 237.575};
  std::vector<double> vbFe = {277.775, 261.486, 259.518, 267.479, 286.297,
                              330.484, 427.263, 600.244, 747.254, 1010.87,
                              1602.59, 2618.59, 3000};
  std::vector<double> pdNi = {0.97692, 1.42324, 1.96708, 2.93121,
                              4.92683, 9.77222, 19.5293, 29.3212,
                              48.9141, 97.7525, 195.354, 237.575};
  std::vector<double> vbNi = {194.76,  202.257, 216.486, 244.299,
                              299.572, 414.545, 595.726, 747.254,
                              1010.87, 1602.59, 2618.59, 3000};
  std::vector<double> pdPt = {0.77948, 0.9843,  1.40198, 1.95233, 2.93121,
                              4.88989, 9.77222, 19.3829, 22.873};
  std::vector<double> vbPt = {196.237, 191.84,  194.76,  206.893, 229.972,
                              279.882, 384.384, 552.382, 614};
  std::vector<double> pdBa = {0.97692, 1.36041, 1.95233, 2.93121,
                              4.92683, 9.77222, 19.5293, 29.3212,
                              48.9141, 98.4909, 195.354, 210.623};
  std::vector<double> vbBa = {115.646, 127.579, 146.161, 173.896,
                              226.524, 330.484, 493.206, 642.472,
                              909.426, 1485.98, 2465.03, 2579.33};
  std::vector<double> pdNa = {0.50378, 0.70683, 0.99173, 1.42324, 1.98194,
                              2.93121, 4.92683, 9.77222, 19.5293, 29.3212,
                              48.9141, 98.4909, 195.354, 210.623};
  std::vector<double> vbNa = {90.1294, 91.5014, 98.6813, 113.912, 133.495,
                              162.466, 216.486, 325.528, 493.206, 642.472,
                              909.426, 1485.98, 2465.03, 2579.33};

  const double scale = 1. / 760.;
  for (auto& pd : pdFe) pd *= scale;
  for (auto& pd : pdNi) pd *= scale;
  for (auto& pd : pdPt) pd *= scale;
  for (auto& pd : pdBa) pd *= scale;
  for (auto& pd : pdNa) pd *= scale;

  TGraph* gFe = new TGraph(pdFe.size(), pdFe.data(), vbFe.data());
  gFe->SetLineColor(kGreen + 0);
  gFe->SetLineWidth(3);
  leg->AddEntry(gFe, "Druyvesteyn + Penning, Ar on Fe", "l");
  gFe->Draw("lsame");

  TGraph* gNi = new TGraph(pdNi.size(), pdNi.data(), vbNi.data());
  gNi->SetLineColor(kGreen + 1);
  gNi->SetLineWidth(3);
  leg->AddEntry(gNi, "Druyvesteyn + Penning, Ar on Ni", "l");
  gNi->Draw("lsame");

  TGraph* gPt = new TGraph(pdPt.size(), pdPt.data(), vbPt.data());
  gPt->SetLineColor(kGreen + 2);
  gPt->SetLineWidth(3);
  leg->AddEntry(gPt, "Druyvesteyn + Penning, Ar on Pt", "l");
  gPt->Draw("lsame");

  TGraph* gBa = new TGraph(pdBa.size(), pdBa.data(), vbBa.data());
  gBa->SetLineColor(kGreen + 3);
  gBa->SetLineWidth(3);
  leg->AddEntry(gBa, "Druyvesteyn + Penning, Ar on Ba", "l");
  gBa->Draw("lsame");

  TGraph* gNa = new TGraph(pdNa.size(), pdNa.data(), vbNa.data());
  gNa->SetLineColor(kGreen + 4);
  gNa->SetLineWidth(3);
  leg->AddEntry(gNa, "Druyvesteyn, Ar on Na", "l");
  gNa->Draw("lsame");

  // Read the Magboltz transport tables
  MediumMagboltz gas;
  const double gamma = 1.e-2;
  const double p = 1.;

  std::vector<int> fIso = {1, 5, 10};
  for (int i = 0; i < fIso.size(); ++i) {
    const int fAr = 100 - fIso[i];
    std::string gasfile = "ar-" + std::to_string(fAr) + "-ic4h10-" +
                          std::to_string(fIso[i]) + "-p1.gas";
    gas.LoadGasFile(gasfile);

    std::vector<double> efields, bfields, angles;
    gas.GetFieldGrid(efields, bfields, angles);

    const size_t nE = efields.size();
    std::vector<double> dvec(nE, 0.);
    std::vector<double> vbvec(nE, 0.);
    for (size_t j = 0; j < nE; j++) {
      double logalpha;
      gas.GetElectronTownsend(j, 0, 0, logalpha);
      const double alpha = exp(logalpha);
      const double d = log1p(1.0 / gamma) / alpha;
      dvec[j] = d * p;
      vbvec[j] = efields[j] * d;
    }

    TGraph* g = new TGraph(nE, dvec.data(), vbvec.data());
    g->SetLineColor(90 + 4 * i);
    g->SetLineWidth(2);
    g->Draw("lsame");
    char buf[100];
    snprintf(buf, 100, "Magboltz, Ar-iC_{4}H_{10} %d-%d, #gamma = 10^{%g}", fAr,
             fIso[i], log10(gamma));
    leg->AddEntry(g, buf, "l");
  }

  leg->Draw();
  c1.Print("paschenariso.ps");
  app.Run();
  return 0;
}
