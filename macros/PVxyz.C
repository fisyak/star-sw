/*
  root.exe 11p5GeV.A+C.root PVxyz,C
*/
#include "TSystem.h"
#include "TROOT.h"
#include "TH1.h"
#include "TH2.h"
#include "TF1.h"
#include "TFile.h"
#include "Ask.h"
#include "TCanvas.h"
TCanvas *c1 = 0;
//________________________________________________________________________________
TF1 *FitGaus(TH1 *hist) {
  TF1 *gaus = 0;
  if (! hist) return gaus;
  Int_t iok = hist->Fit("gaus");
  if (iok) return gaus;
  if (c1) c1->Update();
  if (Ask()) return gaus;
  gaus = (TF1 *) hist->GetListOfFunctions()->FindObject("gaus");
  if (! gaus) return gaus;
  iok = hist->Fit(gaus,"ir","",
	    gaus->GetParameter(1)-2*gaus->GetParameter(2),
	    gaus->GetParameter(1)+2*gaus->GetParameter(2));
  if (iok) return 0;
  if (c1) c1->Update();
  if (Ask()) return gaus;
  return gaus;
}
//________________________________________________________________________________
void PVxyz() {
  c1 = (TCanvas *) gROOT->GetListOfCanvases()->FindObject("c1");
  if (! c1) c1 = new TCanvas("c1","c1");
  TString fName("PVxyz");
  TDirectory *dir = gDirectory;
  fName += gSystem->BaseName(dir->GetName());
  TFile *fOut = new TFile(fName,"recreate");
  TH1 *x = (TH1 *) dir->Get("/Particles/KFParticlesFinder/PrimaryVertexQA/x");
  if (x) x->Write();
  TF1 *gaus = FitGaus(x);
  TH1 *y = (TH1 *) dir->Get("/Particles/KFParticlesFinder/PrimaryVertexQA/y");
  if (y) y->Write();
  gaus = FitGaus(y);
  TH1 *z = (TH1 *) dir->Get("/Particles/KFParticlesFinder/PrimaryVertexQA/z");
  if (z) z->Write();
  gaus = FitGaus(z);
  TH1 *e = (TH1 *) dir->Get("/Tracks/hPVError");
  if (e) e->Write();
  TH2 *xy = (TH2 *) dir->Get("/Particles/KFParticlesFinder/PrimaryVertexQA/xy");
  if (xy) xy->Write();
}
