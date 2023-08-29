/* 
   root.exe ../17p3GeV_2021_P23id.dEdx.root lBichsel.C DrawdEdx.C+
   root.exe ../17p3GeV_2021_P23id.dEdx.root lBichsel.C brtw.C+ ppbarM2.C+ DrawdEdx.C+ 
   root.exe ../17p3GeV_2021_P23id.dEdx.root DrawSignalBg7.C DrawSignalBg_HL34.C
 */
#ifndef __CINT__
#include "Riostream.h"
#include "TDirectory.h"
#include "TObjArray.h"
#include "TH1.h"
#include "TH2.h"
#include "TF1.h"
#include "TLine.h"
#include "TAxis.h"
#include "TCanvas.h"
#include "TROOT.h"
#include "TLegend.h"
#include "TStyle.h"
#include "bichselG10.C"
#endif
void DrawdEdx() {
  TCanvas *c3 = (TCanvas *) gROOT->GetListOfCanvases()->FindObject("c3");
  if (c3) c3->Clear();
  else    c3 = new TCanvas("c3","dE/dx",10,1100,900,500);
  //  gStyle->SetOptStat(0);
  c3->Divide(2,1);
  TH2F *pos = (TH2F *) gDirectory->Get("Tracks/hdEdXPos");
  if (pos) {
    c3->cd(1)->SetLogz(1);
    pos->Draw("colz");
    bichselG10("zN",12);
  }
  TH2F *neg = (TH2F *) gDirectory->Get("Tracks/hdEdXNeg");
  if (neg) {
    c3->cd(2)->SetLogz(1);
    neg->Draw("colz");
    bichselG10("zN",12);
  }
  c3->SaveAs("dEdx.png");
}
