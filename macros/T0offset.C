#if !defined(__CINT__) || defined(__MAKECINT__)
//#include <map>
//#include <array>
#include "TROOT.h"
#include "TSystem.h"
#include "TMath.h"
#include "Riostream.h"
#include "TH1.h"
#include "TH2.h"
#include "TFile.h"
#include "TCanvas.h"
#include "TString.h"
#include "TLegend.h"
#endif
void T0offset() {
#if defined(__CINT__) && ! defined(__MAKECINT__)
  gROOT->LoadMacro("lBichsel.C");
  lBichsel();
  gROOT->LoadMacro("TpcT.C+");
  T0Offsets();
#else
  cout << " T0offset.C does not work with AClick" << endl;
#endif
}
void DrawdT(Int_t k = 0, Int_t group = 3) {
  if (k != 0 && k != 1) return;
  const Char_t *Bnames[2][3][2] = {
    {{"BI",     "BO"},    // uncorrected
     {"BIW",   "BOW"},
     {"BIE",   "BOE"}},
    {{"BCI",   "BCO"},    // corrected 
     {"BCIW",  "BCOW"},
     {"BCIE",  "BCOE"}}
  };
  TCanvas *c1 = (TCanvas *) gROOT->GetListOfCanvases()->FindObject("c1");
  if (c1) c1->Clear();
  else    c1 = new TCanvas("c1","dT");
  TCanvas *c2 = (TCanvas *) gROOT->GetListOfCanvases()->FindObject("c2");
  if (c2) c2->Clear();
  else    c2 = new TCanvas("c2","NoTbks",10,510,700,500);
  TString same1, same2;
  TObjArray *arr = new TObjArray(4);
  const Char_t *COR[2] {"","Corr"};
  const Char_t *IO[2] = {"Inner","Outer"};
  const Char_t *WE[3] = {"All","West","East"};
  TLegend *l1 = new TLegend(0.6,0.6,0.9,0.8);
  TLegend *l2 = new TLegend(0.6,0.6,0.9,0.8);
  for (Int_t j = 0; j < 2; j++) {
    for (Int_t i = 1; i < 3; i++) {
      Int_t color = 1  + 2*(i-1) + j;
      TH2 *h2 = (TH2 *) gDirectory->Get(Bnames[k][i][j]);
      if (! h2) continue;
      h2->SetYTitle("dT (MC - RC) (time buckets)");
      h2->SetXTitle("no. time buckets in cluster");
      TH1D *projX = h2->ProjectionX();
      projX->SetLineWidth(4);
      projX->SetLineColor(color);
      projX->SetStats(0);
      c2->cd();
      projX->Draw(same2);
      same2 = "sames";
      l2->AddEntry(projX,Form("%s %s %s",IO[j],COR[k],WE[i]));
      Int_t kx1 = projX->FindFirstBinAbove(100);
      Int_t kx2 = projX->FindLastBinAbove(100);
      if (group  == 3) 
	h2->FitSlicesY(0, kx1, kx2, 0, "QNRg3s", arr);
      else 
	h2->FitSlicesY(0, kx1, kx2, 0, "QNR", arr);
      TH1D *h1 = (TH1D *) (*arr)[1];
      h1->SetTitle("dT (MC-RC) versus no. time bucksets in cluster");
      h1->SetMarkerColor(color);
      c1->cd();
      h1->SetStats(0);
      h1->Draw(same1);
      same1 = "sames";
      l1->AddEntry(h1,Form("%s %s %s",IO[j],COR[k],WE[i]));
    }
  }
  c1->cd(); l1->Draw();
  c2->cd(); l2->Draw();
}
