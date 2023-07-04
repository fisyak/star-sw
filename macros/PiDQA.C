#if !defined(__CINT__) || defined(__MAKECINT__)
#include "Riostream.h"
#include "TROOT.h"
#include "TSystem.h"
#include "TMath.h"
#include "TH1.h"
#include "TH2.h"
#include "TH3.h"
#include "TLegend.h"
#include "TObjArray.h"
#include "TCanvas.h"
#include "TGraphErrors.h"
#include "TMultiGraph.h"
#include "TStyle.h"
#include "TArrayD.h"
#include "TPaveLabel.h"
#include "TString.h"
#include "TFile.h"
#endif
#include "Ask.h"
TMultiGraph *mg = 0;
TMultiGraph *sg = 0;
TMultiGraph *mgE = 0;
TMultiGraph *sgE = 0;
TMultiGraph *mgPion = 0;
TMultiGraph *sgPion = 0;
TMultiGraph *mgProton = 0;
TMultiGraph *sgProton = 0;
TFile *fOut = 0;
TFile *_file0 = 0;
void PiDQA(const Char_t *histN="dEdx", Int_t NN = 8, Bool_t bg = kFALSE, const Char_t *opt = "qeg3s") {
  TString xTitle = "log_{10} (#beta #gamma)";
  if (! bg) xTitle = "log_{10} (p [GeV/c])";
  const Int_t N = 18;
  struct Part_t {
    const Char_t *dir;
    Double_t      mass;
  };
  Part_t Particles[N] = {
    {"/PiDQA/gamma/e+",    0.51099907e-3},   
    {"/PiDQA/gamma/e-",    0.51099907e-3},
    {"/PiDQA/Ks/pi+",      0.1395699},    
    {"/PiDQA/Ks/pi-",      0.1395699},    
    {"/PiDQA/Lambdab/pi+", 0.1395699},
    {"/PiDQA/Lambda/pi-",  0.1395699},
    {"/PiDQA/Lambda/p",    0.9382723},
    {"/PiDQA/Lambdab/p-",  0.9382723}, // 8
    {"/PiDQA/e+",          0.51099907e-3},   
    {"/PiDQA/e-",          0.51099907e-3},
    {"/PiDQA/pi+",         0.1395699},    
    {"/PiDQA/pi-",         0.1395699},    
    {"/PiDQA/K+",          0.493677},
    {"/PiDQA/K-",          0.493677},
    {"/PiDQA/p",           0.9382723},
    {"/PiDQA/p-",          0.9382723},
    {"/PiDQA/d",           1.875613},
    {"/PiDQA/d-",          1.875613}
  };
#if 1
  TCanvas *c1 = (TCanvas *) gROOT->GetListOfCanvases()->FindObject("c1");
  if (c1) c1->Clear();
  else    c1 = new TCanvas("c1","c1",600,600);
  c1->SetLogz(1);
#endif
  if (! _file0) _file0 = gFile;
  _file0->cd();
  TString FOutName("Graph_");
  if (bg) FOutName += "bg";
  else    FOutName += "p";
  FOutName += Form("%s_%s",histN,gSystem->BaseName(_file0->GetName()));
  if (fOut) {delete fOut;}
  fOut = new TFile(FOutName,"recreate");
  _file0->cd();
  TGraphErrors *grmu[N] = {0};
  TGraphErrors *grsigma[N] = {0};
  mg = new TMultiGraph(Form("DEV_%s",histN),Form("#mu for %s",histN));
  sg = new TMultiGraph(Form("SigmaV_%s",histN),Form("#sigma for %s",histN));
  mgE = new TMultiGraph(Form("EDEV_%s",histN),Form("#mu for %s",histN));
  sgE = new TMultiGraph(Form("ESigmaV_%s",histN),Form("#sigma for %s",histN));
  mgPion = new TMultiGraph(Form("PionDEV_%s",histN),Form("#mu for %s",histN));
  sgPion = new TMultiGraph(Form("PionSigmaV_%s",histN),Form("#sigma for %s",histN));
  mgProton = new TMultiGraph(Form("ProtonDEV_%s",histN),Form("#mu for %s",histN));
  sgProton = new TMultiGraph(Form("ProtonSigmaV_%s",histN),Form("#sigma for %s",histN));
  TLegend *l, *ls;
  if (! bg) {
      l = new TLegend(0.6,0.6,0.9,0.9);
      ls = new TLegend(0.6,0.6,0.9,0.9);
    } else {
      l = new TLegend(0.4,0.6,0.7,0.9);
      ls = new TLegend(0.4,0.6,0.7,0.9);
    }
  TPaveLabel pl;
  Float_t x1=0.3, y1=0.8, x2=0.75, y2=0.85;
  TString HistName(histN);
  Bool_t idEdx = HistName.Contains("dEdx");
  Bool_t iBTof = HistName.Contains("BTof");
  if (NN < 0 || NN > N) NN = N;
  for (Int_t i = 0; i < NN; i++) {
    TString dir(Particles[i].dir);
    //    dir += opt;
    if (! gDirectory->cd(dir)) continue;
    //    TCanvas *c1 = new TCanvas(Form("c%i",i),dir);
    c1->Clear();
    c1->SetTitle(dir);
    c1->SetLogz(1);
    TString name(histN);
    TH2F *h2 = (TH2F *) gDirectory->Get(name);
    cout << "Histmogram " << dir << "/" << name.Data();
    if (! h2) {
      cout  << " has not been found" << endl;
      continue;
    }
    cout << " has been found" << endl;
    Double_t sum = h2->GetEntries();
    if (sum < 1e3) {
      cout << h2->GetName() << " has only " << sum << " entries. Skipped !" << endl;
      continue;
    }
#if 0
    if (iBTof && dir.Contains("Lambdab/pi+")) {
      cout << "restrict y range for " <<  dir.Data() << endl;
      Int_t ny = h2->GetNbinsY();
      Int_t iy = h2->GetYaxis()->FindBin(-0.1);
      h2->GetYaxis()->SetRange(iy,ny);
    }
#endif
    TObjArray *arr = new TObjArray(4);
    TH1D *h1 = h2->ProjectionX();
    Double_t ymax = h1->GetMaximum();
    //    h2->FitSlicesY(0,0,-1,200,"iqeg5s",arr);
    //    h2->FitSlicesY(0,0,-1,200,opt,arr);
    h2->FitSlicesY(0,0,-1,0,opt,arr);
    // h2->FitSlicesY(0,0,-1,0,"qe",arr);
    TH1D *mu = (TH1D *) arr->At(1);
    TH1D *sigma = (TH1D *) arr->At(2);
    if (mu && sigma) {
      h2->Draw("colz");
      //      pl.DrawPaveLabel(x1,y1,x2,y2,dir,"brNDC");
      pl.DrawPaveLabel(x1,y1,x2,y2,gDirectory->GetPath(),"brNDC");
      //      c1->Update();
      mu->Draw("same");
      //      c1->Update();
      sigma->Draw("same");
      c1->Update();
      Int_t nx = mu->GetNbinsX();
      TArrayD X(nx);  Double_t *x = X.GetArray();
      TArrayD Y(nx);  Double_t *y = Y.GetArray();
      TArrayD E(nx);  Double_t *e = E.GetArray();
      TArrayD S(nx);  Double_t *s = S.GetArray();
      TArrayD SE(nx); Double_t *se = SE.GetArray();
      Int_t np = 0;
      for (Int_t j = 1; j <= nx; j++) {
	//	if (h1->GetBinContent(j) < 0.25*ymax) continue;
	if (sigma->GetBinContent(j) <= 0.0 || sigma->GetBinContent(j) > 3) continue;
	Double_t err = mu->GetBinError(j);
	Double_t yyy = mu->GetBinContent(j);
	//	if (idEdx) yyy += 1.6185e-02 ;
	if (err <= 0.0 || err > 0.02) continue;
	if (TMath::Abs(yyy) > 10.0) continue;
	//	x[np] = mu->GetBinCenter(j);
	x[np] = mu->GetBinCenter(j); 
	if (! bg) x[np] +=  TMath::Log10(Particles[i].mass);
	y[np] = yyy;
	e[np] = err;
	s[np] = sigma->GetBinContent(j);
	se[np] = sigma->GetBinError(j);
	np++;
      }
      grmu[i] = new TGraphErrors(np, x, y, 0, e);
      Int_t color = i%8 + 1;
      grmu[i]->SetLineColor(color);
      grmu[i]->SetMarkerColor(color);
      grsigma[i] = new TGraphErrors(np, x, s, 0, se);
      grsigma[i]->SetLineColor(color);
      grsigma[i]->SetMarkerColor(color);
      TString Dir(dir);
      Int_t marker = 20;
      if (Dir.EndsWith("e+") || Dir.EndsWith("e-")) marker = 21;
      if (Dir.EndsWith("p") || Dir.EndsWith("p-")) marker = 22;
      grmu[i]->SetMarkerStyle(marker);
      mg->Add(grmu[i]);
      l->AddEntry(grmu[i],dir,"p");
      grsigma[i]->SetMarkerStyle(marker);
      sg->Add(grsigma[i]);
      ls->AddEntry(grsigma[i],dir,"p");
      if      (dir.Contains("/e")     )  {mgE->Add(grmu[i]);      sgE->Add(grsigma[i]);}
      else if (dir.Contains("/pi")    )  {mgPion->Add(grmu[i]);   sgPion->Add(grsigma[i]);}
      else if (dir.Contains("/p")     )  {mgProton->Add(grmu[i]); sgProton->Add(grsigma[i]);}
    }
    if (! gROOT->IsBatch() && Ask()) return;
  }
  if (! mg->GetListOfGraphs()) return;
  if (mg->GetListOfGraphs()->GetSize() <= 0) return;
  TString ctitle(Form("mu%s%s",histN,opt));
  TCanvas *cr = new TCanvas(ctitle,ctitle,200,100,1600,800);
  mg->Draw("ap");
  mg->GetHistogram()->SetXTitle(xTitle);
  mg->Draw("p");
  l->Draw();
  cr->Update();
  if (fOut) {
    fOut->cd(); 
    mg->Write(); 
    sg->Write();
    mgE->Write(); 
    sgE->Write();
    mgPion->Write(); 
    sgPion->Write();
    mgProton->Write(); 
    sgProton->Write();
    _file0->cd();
  }
  TString File;
  //  File += gSystem->BaseName(gFile->GetName());
  File += FOutName;
  File.ReplaceAll(".root",".png");
  TString pngFile = ctitle + File;
  cr->SaveAs(pngFile);
  ctitle = Form("sigma%s%s",histN,opt);
  if (bg) ctitle += "bg";
  TCanvas *csigma = new TCanvas(ctitle,ctitle,200,1000,1600,800);
  sg->Draw("axp");
  sg->GetHistogram()->SetXTitle(xTitle);
  sg->Draw("axp");
  ls->Draw();
  csigma->Update();
  pngFile = ctitle + File;
  csigma->SaveAs(pngFile);
}
//________________________________________________________________________________
void PlotArmeteros() {
  const Char_t *Path[4][2] = {
    {"/PiDQA/gamma",   "/Particles/KFParticlesFinder/Particles/gamma/Parameters"},
    {"/PiDQA/Ks",      "/Particles/KFParticlesFinder/Particles/Ks/Parameters"},
    {"/PiDQA/Lambda",  "/Particles/KFParticlesFinder/Particles/Lambda/Parameters"},
    {"/PiDQA/Lambdab", "/Particles/KFParticlesFinder/Particles/Lambdab/Parameters"}
  };
  TCanvas *c1 = (TCanvas *) gROOT->GetListOfCanvases()->FindObject("c1");
  if (c1) c1->Clear();
  else    c1 = new TCanvas("c1","c1",1000,1600);
  c1->Divide(2,4);
  for (Int_t ix = 1; ix <= 2; ix++) {
    for (Int_t iy = 1; iy <= 4; iy++) {
      gDirectory->cd(Path[iy-1][2-ix]);
      TH2F *h2 = (TH2F *) gDirectory->Get("Armenteros");
      if (! h2) continue;
      Int_t i = ix + 2*(iy-1);
      c1->cd(i)->SetLogz(1);
      h2->Draw("colz");
      TLegend *l = new TLegend(0.1,0.7,0.8,0.8);
      TString Title(Path[iy-1][2-ix]);
      Title.ReplaceAll("/PiDQA/", "Unique ");
      Title.ReplaceAll("/Particles/KFParticlesFinder/Particles/", "All ");
      Title.ReplaceAll("/Parameters","");
      l->AddEntry(h2,Title);
      l->Draw();
    }
  }
}
