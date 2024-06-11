//   root.exe */*/IO/*W2S.root dTW2S.C+
#include "Ask.h"
#include "Riostream.h"
#include <stdio.h>
#include "TROOT.h"
#include "TSystem.h"
#include "TMath.h"
#include "TF1.h"
#include "TH1.h"
#include "TH2.h"
#include "TH3.h"
#include "TFile.h"
#include "TCanvas.h"
#include "PrintTH1.C"
//________________________________________________________________________________
void dTW2S() {
  Int_t NF = 0;
  TSeqCollection *files = gROOT->GetListOfFiles();
  if (! files) return;
  Int_t nn = files->GetSize();
  if (! nn) return;
  TIter next(files);
  TFile *f = 0;
  TCanvas *c1 = (TCanvas *) gROOT->GetListOfCanvases()->FindObject("c1");
  if (! c1 ) c1 = new TCanvas("c1","dT");
  c1->SetLogz(1);
  TF1::InitStandardFunctions();
  TF1 *pol0 = (TF1 *) gROOT->GetListOfFunctions()->FindObject("pol0");
  while ( (f = (TFile *) next()) ) { 
    f->cd();
    TString F(f->GetName());
    TH3 *dT = (TH3 *) gDirectory->Get("dTTpc");
    if (! dT) continue;
    if (dT->GetEntries() < 1e3) continue;
    c1->Clear();
    dT->Project3D("zx")->Draw("colz");
    TH2 *dT_zx = (TH2*) gDirectory->Get("dTTpc_zx");
    if (! dT_zx) continue;
    dT_zx->FitSlicesY();
    TH1 *dT_zx_1 = (TH1 *) gDirectory->Get("dTTpc_zx_1");
    TH1 *dT_zx_2 = (TH1 *) gDirectory->Get("dTTpc_zx_2");
    if (! dT_zx_1 || ! dT_zx_2 ) continue;
    Double_t dTs[2] = {0};
    Double_t ddTs[2] = {0};
    dT_zx_1->Draw("same");
    for (Int_t we = 0; we <2 ; we++) {
      if (we ==0) dT_zx_1->Fit(pol0,"er","same",0.5,12.5);
      else        dT_zx_1->Fit(pol0,"er+","same",12.5,24.5);
      pol0->Draw("same");
      if (! pol0) continue;
      dTs[we]  = pol0->GetParameter(0);
      ddTs[we] = pol0->GetParError(0);
    }
    c1->Update();
    Double_t dTAvD = 0.5*(dTs[0]-dTs[1]);
    Double_t dTAvS = 0.5*(dTs[0]+dTs[1]);
    cout << f->GetName() 
	 << "\tWest = " << dTs[0] << " +/- " << ddTs[0] 
	 << "\tEast = " << dTs[1] << " +/- " << ddTs[1] 
	 << "\tAverge Dif  = " << dTAvD << " Sum = " << dTAvS <<  endl;
    c1->Update();
    if (Ask()) break;
  }
}
