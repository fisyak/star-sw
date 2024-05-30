// cat */*/IO/*W2S.h > W2S.h
/*
  root.exe ResultsW2S.C+
 */
#if !defined(__CINT__)
// code that should be seen ONLY by the compiler
#else
#if !defined(__CINT__) || defined(__MAKECINT__)
// code that should be seen by the compiler AND rootcint
#else
// code that should always be seen
#endif
#endif
//________________________________________________________________________________
#if !defined(__CINT__) || defined(__MAKECINT__)
#include "Riostream.h"
#include "TROOT.h"
#include "TSystem.h"
#include "TMath.h"
#include "TH1.h"
#include "TStyle.h"
#include "TGraph.h"
#include "TNtuple.h"
#include "TCanvas.h"
#include "TString.h"
#include "TLegend.h"
#include "TFile.h"
#include "TSystem.h"
//#include "W2SSectorParPass9.h"
//#include "W2SSectorParPass20.h"
//#include "W2SSectorPar.h"
#include "THStack.h"
#include "TPRegexp.h"
#endif
#include "StTpcAlignerMaker/SurveyPass.h"

SurveyPass_t Passes[] = {
  //#include "W2S_Pass21.h"
  //#include "W2S_Pass22.h"
  //#include "W2S_Pass22.h"
  //#include "StTpcAlignerMaker/W2S_Pass28.h"
#include "W2S.h"
};
const  Int_t NP = sizeof(Passes)/sizeof(SurveyPass_t);
TCanvas *c1 = 0;
THStack *hs[6];
TLegend *leg[6];
#include "DumpRes2Par.h"
//________________________________________________________________________________
void ResultsW2S(const Char_t *opt="") {
  gStyle->SetMarkerStyle(20);
  gStyle->SetOptStat(0);
  cout << "NP \t" << NP << endl;
  Int_t NPsel = 0;
  SurveyPass_t Pass[2];// 0 => sum FF, 1 => sum RF
  Int_t nFR[2] = {0};
  TString Opt(opt);
  TPRegexp Reg(opt);
  TArrayI PassFlag(NP+2);
  for (Int_t k = 0; k < NP; k++) {
    TString PassName(Passes[k].PassName);
    PassFlag[k] = -1;
    if (Opt != "" && Reg.MatchS(PassName)->GetLast() < 0) continue;
    Passes[k].FixErrors();
    PassFlag[k] = NPsel;
    if (Passes[k].GetField() == 1) {
      if (! nFR[0]) Pass[0]  = Passes[k];
      else          Pass[0] += Passes[k];
      nFR[0]++;
    } else if (Passes[k].GetField() == -1) {
      if (! nFR[1]) Pass[1]  = Passes[k];
      else          Pass[1] += Passes[k];
      nFR[1]++;
    }
    NPsel++;
  }
  if (NPsel <= 0) {
    cout << "No pass selected" << endl;
    return;
  }
  TString Out("ResultsW2S.");
  OutputName = Opt;
  OutputName.ReplaceAll("|","_");
  Out += OutputName;
  Out += ".root";
  TFile *fOut = new TFile(Out,"recreate");
  TH1::SetDefaultSumw2(kTRUE);
  c1 = new TCanvas("W2S","Tpc Sector to Sector alignment parameters",2400,1200);
  c1->Divide(3,2);
  Int_t NH = NP;
  if (nFR[0] > 0) NH++;
  if (nFR[1] > 0) NH++;
  TH1D ***dath = new TH1D**[NH]; 
  const Char_t *names[6] = {" #Deltax"," #Deltay"," #Deltaz"," #Delta #alpha"," #Delta #beta"," #Delta #gamma"};
  const Char_t *nameK[6] = {"Dx","Dy","Dz","Da",     "Db",    "Dg"};
  for (Int_t k = 0; k < NH; k++) {
    dath[k] = 0;
    if (PassFlag[k] < 0) continue;
    if (k < NP) {
      Passes[k].Print();
      dath[k] = Passes[k].GetHist(names, nameK);
    } else {
      Pass[k-NP].Print();
      dath[k] = Pass[k-NP].GetHist(names, nameK, k-NP+1, 20);
    }
  }
  for (Int_t i = 0; i < 6; i++) {
    hs[i] = new THStack(nameK[i],names[i]);
    Double_t ymin =  1e10;
    Double_t ymax = -1e10;
    TString Name;
    TString Title;
    if (! i)     {leg[i] = new TLegend(0.85,0.7-0.04*NH,0.98,0.7);
    }  else       leg[i] = 0;
    TString same("e");
    Int_t color = 1;
    Int_t nohist = 0;
    for (Int_t k = 0; k < NH; k++) {
      if (! dath[k]) continue;
      if (! dath[k][i]) continue;
      nohist++;
      hs[i]->Add(dath[k][i]);
      if (leg[i]) {
	if (k < NP) {
	  Int_t indx = TString(Passes[k].PassName).Index("Pass");
	  TString Label(Passes[k].PassName+indx);
	  Label.ReplaceAll("/IO","");
	  indx = Label.Index("/");
	  leg[i]->AddEntry(dath[k][i],Label.Data()+indx+1);
	} else if (k == NP && NH == NP + 1)  leg[i]->AddEntry(dath[k][i],"sum");
	else {
	  if (k == NP) leg[i]->AddEntry(dath[k][i],"sum over FF");
	  else         leg[i]->AddEntry(dath[k][i],"sum over RF");
	}
      }
    }
    c1->cd(i+1);
    if (! hs[i]) continue;
    ymax = hs[i]->GetMaximum("nostack");
    ymin = hs[i]->GetMinimum("nostack");
    TList *list = hs[i]->GetHists();
    TIter next(list);
    TH1 *h = 0;
    while ((h = (TH1*) next())) {
      h->GetYaxis()->SetTitleOffset(1.4);
      if (same == "e") {
	if (ymax > 0)     h->SetMaximum(1.1*ymax);
	else              h->SetMaximum(0.9*ymax);
	if (ymin < 0)     h->SetMinimum(1.1*ymin);
	else              h->SetMinimum(0.9*ymin);
      }
      TString hName(h->GetName());
      if (hName.BeginsWith("db",TString::kIgnoreCase)) h->Draw("same");
      else                                             h->Draw(same);
      same = "same";
    }
    if (leg[i]) leg[i]->Draw();
  }
  c1->Update();
  fOut->Write();
  DumpRes2Par("W2S_",Pass[0].StripPass(), Pass[1].StripPass()); 
}

