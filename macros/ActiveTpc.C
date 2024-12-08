#include "Ask.h"
#include "Riostream.h"
#include "TSystem.h"
#include "TFile.h"
#include "TH3.h"
#include "TString.h"
#include "TCanvas.h"
//________________________________________________________________________________
void DrawPng(TCanvas *c) {
  static Int_t nPng = 0;
  if (! c) return;
  TString pngName("");
  c->Update(); pngName = c->GetTitle();
  pngName.ReplaceAll(".root","");
  pngName.ReplaceAll(" ","_");
  pngName.ReplaceAll("(","_");
  pngName.ReplaceAll(")","_");
  pngName.ReplaceAll("{","_");
  pngName.ReplaceAll("}","_");
  pngName.ReplaceAll("<","lt");
  pngName.ReplaceAll(">","gt");
  pngName.ReplaceAll("old_new_","");
  pngName.ReplaceAll("old_new","");
  pngName.ReplaceAll("Old_New_","");
  pngName.ReplaceAll("Old_New","");
  pngName.ReplaceAll("GeV/c","");
  pngName.ReplaceAll(".","_");
  pngName.ReplaceAll("/","_");
  pngName.ReplaceAll("^","_");
  pngName.ReplaceAll("__","_");
  pngName.ReplaceAll("__","_");
  pngName.ReplaceAll("#","");
  //  pngName += ".png"; 
  pngName += ".png"; 
  c->SaveAs(pngName);
  nPng++;
  cout << "Draw #\t" << nPng << "\t" << pngName << endl;
#ifdef __SAVE_ROOT_PICTURES_
  //  pngName.ReplaceAll(".png",".root");
  pngName.ReplaceAll(".png",".root");
  c->SaveAs(pngName);
#endif
}
//________________________________________________________________________________
void ActiveTpc() {
  TSeqCollection *files = gROOT->GetListOfFiles();
  if (! files) return;
  TIter next(files);
  TFile *f = 0;
  TString Title;
  Int_t i = 0;
  while ( (f = (TFile *) next()) ) { 
    f->cd();
    TString F(f->GetName());
    TH3F * AlivePads = (TH3F *) gDirectory->Get("AlivePads");
    TH3F * AlivePadsdEdx = (TH3F *) gDirectory->Get("AlivePadsdEdx");
    if (! AlivePads && ! AlivePadsdEdx) continue;
    i++;
    TCanvas *c1 = new TCanvas(Form("c%i",i),F, 600, 1200);
    c1->Divide(1,2);
    c1->cd(1); if (AlivePads) {AlivePads->Project3D("yx")->Draw("colz");}
    c1->cd(2); if (AlivePadsdEdx) {AlivePadsdEdx->Project3D("yx")->Draw("colz");}
    c1->Update();
    cout << F.Data() << endl;
    DrawPng(c1);
    if (! gROOT->IsBatch() && Ask()) return;
  }
}
