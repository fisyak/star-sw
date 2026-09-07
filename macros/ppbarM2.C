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
#endif
void ppbarM2() {
  const Char_t *BEtof[2] = {"hTofPID","hETofPID"};
  const Char_t *ppbar[2] = {"/Tracks/p","/Tracks/p-"};
  const Char_t *ppbarName[2] = {"p","pbar"};
  TCanvas *c2 = (TCanvas *) gROOT->GetListOfCanvases()->FindObject("c2");
  if (c2) c2->Clear();
  else    c2 = new TCanvas("c2","ppbarM2",10,150,2*700,3*500);
  c2->Divide(2,3);
  //  gStyle->SetOptStat(0);
  TF1 *func = new TF1("func","[0]*(1+[1]+[2]*x)",-0.5,0.5);
  Double_t m2P = 0.9382723*0.9382723;
  TLine *line = new TLine(-0.5, m2P, 0.5, m2P);
  func->SetParameters(0,0,0);
  func->FixParameter(0,m2P);
  TLegend *l[2][3] = {0};
  for (Int_t be = 0; be < 2; be++) {// BTof & ETOF
    TH2F* p2[2] = {0};
    TH1D* m2p[2] = {0};
    TH1F *frame = 0;
    TString same;
    for (Int_t i = 0; i < 2; i++) {
      Int_t ipad = 2*i + be + 1;
      c2->cd(ipad)->SetLogz(1);
      TString path(ppbar[i]);
      path +=  "/";
      path +=  BEtof[be];
      p2[i] = (TH2F *) gDirectory->Get(path);
      if (! p2[i]) {
	cout << "Cpundn't find histogram: " << path.Data() << endl;
	continue;
      }
      p2[i]->Draw("colz");
      l[be][i] = new TLegend(0.1,0.8,0.2,0.9);
      l[be][i]->AddEntry(p2[i],ppbarName[i]);
      l[be][i]->Draw();
      TH2F *h2 = new TH2F(*p2[i]);
      h2->SetName(Form("%sCopy",p2[i]->GetName()));
      TAxis *y = h2->GetYaxis();
      Int_t i1 = y->FindBin(m2P-0.3);
      Int_t i2 = y->FindBin(m2P+0.3);
      y->SetRange(i1,i2);
      TObjArray* arr =  new TObjArray(4);
      h2->FitSlicesY(0, 0, -1, 0, "QNR", arr);
      m2p[i] = (TH1D *) (*arr)[1]; 
      m2p[i]->SetName(ppbarName[i]);
      m2p[i]->SetMarkerColor(i+1); 
      m2p[i]->SetMarkerStyle(20);
      //      m2p[i]->SetName("m2p");
      m2p[i]->SetStats(0);
      c2->cd(5+be);
      m2p[i]->Fit("func");
    }
    frame = c2->cd(5+be)->DrawFrame(-0.5,0.70,0.5,1.00);
    frame->SetTitle("p/pbar Mass^{2} versus log_{10}P");
    frame->SetXTitle("log_{10}(p[GeV/c])");
    frame->SetYTitle("M^{2}"); //[GeV/c^{2}]^{2}");
    l[be][2] = new TLegend(0.2,0.2,0.6,0.4);
    for (Int_t i = 0; i < 2; i++) {
      TF1 *func = (TF1*) m2p[i]->GetListOfFunctions()->FindObject("func");
      if (func->GetParameter(2) < 1.0) {
	TString Title = Form("%4s: %4.1f + %4.1f log_{10}P(%%)",ppbarName[i],100*func->GetParameter(1), 100*func->GetParameter(2));
	l[be][2]->AddEntry(m2p[i],Title);
	m2p[i]->Draw("same");
      } else {
	m2p[i] = 0;
      }
    }
    line->Draw();
    l[be][2]->Draw();
    for (Int_t i = 0; i < 2; i++) {
      Int_t ipad = 2*i + be + 1;
      c2->cd(ipad)->SetLogz(1);
      if (m2p[i]) m2p[i]->Draw("same");
   }
  }
  c2->Update();
  c2->SaveAs("ppbarM2.png");
}
