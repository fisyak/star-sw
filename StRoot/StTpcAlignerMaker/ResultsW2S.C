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
//________________________________________________________________________________
void ResultsW2S(const Char_t *opt="") {
  gStyle->SetMarkerStyle(20);
  gStyle->SetOptStat(0);
  cout << "NP \t" << NP << endl;
  Int_t NH = NP;
  TString Opt(opt);
  if (Opt == "") {
    if (NH == 2) NH++; // make average if we have only FF + RF
    else if (NP > 2) NH = NP + 2; // make average for FFF and RF
  }
  TH1D ***dath = new TH1D**[NH]; 
  for (Int_t p = 0; p < NH; p++) {dath[p] = new TH1D*[6]; memset(dath[p],0, 6*sizeof(TH1D*));}
  const Char_t *names[6] = {" #Deltax"," #Deltay"," #Deltaz"," #Delta #alpha"," #Delta #beta"," #Delta #gamma"};
  const Char_t *nameK[6] = {"Dx","Dy","Dz","Da",     "Db",    "Dg"};
  TFile *fOut = new TFile("ResultsW2S.root","recreate");
  c1 = new TCanvas("IO","Tpc Outer to Inner alignment parameters",2400,1200);
  c1->Divide(3,2);
  for (Int_t i = 0; i < 6; i++) {
    hs[i] = new THStack(nameK[i],names[i]);
#if 0
    if (i < 3) hs[i]->SetYTitle(Form("%s (#mum)",names[i]));
    else       hs[i]->SetYTitle(Form("%s (mrad)",names[i]));
    hs[i]->SetXTitle("sector");
#endif
    Double_t ymin =  1e10;
    Double_t ymax = -1e10;
    TString Name;
    TString Title;
    if (! i)     {
      if (Opt == "") 	leg[i] = new TLegend(0.85,0.5-0.04*NH,0.98,0.5);
      else              leg[i] = new TLegend(0.85,0.5-0.08,   0.98,0.5);
    }     else         leg[i] = 0;
    TString same("e");
    Int_t color = 1;
    TH1::SetDefaultSumw2(kTRUE);
    Int_t nohist = 0;
    for (Int_t k = 0; k < NH; k++) {
      if (k < NP) {
	if (i == 0 && k < NP) Passes[k].Print();
	Name = Form("%s%s",nameK[i],Passes[k].PassName);
	Name.ReplaceAll("/","_");
	if (Opt != "" && ! Name.Contains(Opt,TString::kIgnoreCase)) continue;
	Title = Form("Alignment fit for  %s %s",names[i],Passes[k].PassName);
	nohist++;
      } else { // Average
	if (NH == NP + 1) {
	  Name = Form("%s_%s_%s",nameK[i],Passes[0].PassName,Passes[1].PassName);
	  Name.ReplaceAll("/","_");
	  if (Opt != "" && ! Name.Contains(Opt,TString::kIgnoreCase)) continue;
	  Title = Form("Alignment fit for %s sum %s %s",names[i],Passes[0].PassName,Passes[1].PassName);
	} else {
	  TString RF((k == NP) ? "FF": "RF");
	  Name = Form("%s%s",nameK[i],RF.Data());
	  if (Opt != "" && ! Name.Contains(Opt,TString::kIgnoreCase)) continue;
	  Title = Form("Alignment fit for %s sum over %s",names[i],RF.Data());
	}
      }
      //      cout << Name.Data() << "\t" << Title.Data() << "\ti\t" << i << "\tk\t" << k << endl;
      dath[k][i] = (TH1D *) gDirectory->Get(Name);
      if (dath[k][i]) delete dath[k][i];
      
      dath[k][i] = new TH1D(Name,Title, 24, 0.5, 24.5);
      //      cout << "Create: " << dath[k][i]->GetName() << "\t" << dath[k][i]->GetTitle() << endl;
      dath[k][i]->SetMarkerColor(color);
      dath[k][i]->SetLineColor(color);
      dath[k][i]->SetMarkerSize(2);
      dath[k][i]->SetMarkerStyle(22);
      if (k < NP) {
	if (TString(Passes[k].PassName).Contains("RF")) {
	  color++;
	  dath[k][i]->SetMarkerStyle(23);
	}
      } else       if (k >= NP && NH == NP + 2)  {
	Int_t c = 1;
	if (k == NP+1) c = 2;
	dath[k][i]->SetMarkerColor(c);
	dath[k][i]->SetLineColor(c);
	dath[k][i]->SetMarkerStyle(20);
	//	dath[k][i]->SetMarkerSize(3);
      }
      dath[k][i]->SetXTitle("sector");
      if (i < 3) dath[k][i]->SetYTitle(Form("%s (#mum)",names[i]));
      else       dath[k][i]->SetYTitle(Form("%s (mrad)",names[i]));
      for (Int_t l = 0; l < 24; l++) {
	Int_t secs;
	Double_t val = 0, err = 0;
	if (k < NP) {
	  Double_t *X = &Passes[k].Data[l].x;
	  secs = Passes[k].Data[l].sector;
	  if (X[2*i+1] >= 0 && X[2*i+1] < 99) {
	    val = X[2*i];
	    err = X[2*i+1];
	  } else {continue;}
	} else if (k == NP && NH == NP + 1) { // Average FF+RF
	  Double_t *X0 = &Passes[0].Data[l].x;
	  Double_t *X1 = &Passes[1].Data[l].x;
	  secs = Passes[0].Data[l].sector;
	  if (X0[2*i+1] >= 0 && X0[2*i+1] < 99 &&
	      X1[2*i+1] >= 0 && X1[2*i+1] < 99) {
	    val = 0.5*(X0[2*i] + X1[2*i]);
	    dath[k][i]->SetBinContent(secs,val);
	    err = TMath::Sqrt(X0[2*i+1]*X0[2*i+1]+X1[2*i+1]*X1[2*i+1])/2;
	  } else {continue;}
	} else {// Average of all FF and RF
	  Double_t valW = 0, errW = 0;
	  secs = Passes[0].Data[l].sector;
	  for (Int_t p = 0; p < NP; p++) {
	    TString RF((k == NP) ? "FF": "RF");
	    TString Name(Passes[p].PassName);
	    if (! Name.Contains(RF)) continue;
	    Double_t *X = &Passes[p].Data[l].x;
	    if (X[2*i+1] >= 0 && X[2*i+1] < 99) {
	      val = X[2*i];
	      err = X[2*i+1];
	      if (err == 0.0) err = 0.01;
	      Double_t err2 = err*err;
	      valW += val/err2;
	      errW +=  1./err2;
	    } 
	  }
	  if (errW <= 0) continue;
	  val = valW/errW;
	  err = 1./TMath::Sqrt(errW);
	} 
	if (err < 0.001) err = 0.001;
	dath[k][i]->SetBinContent(secs,val);
	dath[k][i]->SetBinError(secs,err);
	if (ymin > val - err) ymin = val - err;
	if (ymax < val + err) ymax = val + err;
      }
      hs[i]->Add(dath[k][i]);
      if (leg[i]) {
	if (k < NP) leg[i]->AddEntry(dath[k][i],Passes[k].PassName);
	else if (k == NP && NH == NP + 1)  leg[i]->AddEntry(dath[k][i],"sum");
	else {
	  if (k == NP) leg[i]->AddEntry(dath[k][i],"sum over FF");
	  else         leg[i]->AddEntry(dath[k][i],"sum over RF");
	}
      }
    }
#if 0
    if (ymax > 0)     dath[kk][i]->SetMaximum(1.1*ymax);
    else              dath[kk][i]->SetMaximum(0.9*ymax);
    if (ymin < 0)     dath[kk][i]->SetMinimum(1.1*ymin);
    else              dath[kk][i]->SetMinimum(0.9*ymin);
#endif 
    c1->cd(i+1);
    if (! hs[i]) continue;
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
}
//________________________________________________________________________________
void DumpRes2Par() {
  TH1D *hist[2][6] = {0};
  const Char_t *RF[2] = {"FF","RF"};
  const Char_t *nameK[6] = {"Dx","Dy","Dz","Da",     "Db",    "Dg"};
  for (Int_t f = 0; f < 2; f++) 
    for (Int_t k = 0; k < 6; k++) {
      TString Name(Form("%s%s",nameK[k],RF[f]));
      hist[f][k] = (TH1D *) gDirectory->Get(Name);
      if (! hist[f][k]) {
	cout << "Hisogram " << Name.Data() << " is missing" << endl;
      } else {
	cout << "Hisogram " << Name.Data() << " is loaded" << endl;
      }
    }
  TString Out("W2S_");
  Out += gSystem->BaseName(gSystem->WorkingDirectory());
  Out += "_Avg.h";
  ofstream outC;
  outC.open(Out.Data(), ios::out);
  for (Int_t f = 0; f < 2; f++) {
    outC << "  {20190101,    1, \"" << gSystem->BaseName(gSystem->WorkingDirectory()) << "/" << RF[f] <<  "\", //" << endl;
    outC << "{" << endl;
    for (Int_t sector = 1; sector <= 24; sector++) {
      TString lineC("");
      lineC = Form("\t{%2i",sector);
      for (Int_t k = 0; k < 6; k++) {
	TH1D *fit = hist[f][k];
	Double_t val      = fit->GetBinContent(sector);
	Double_t valError = fit->GetBinError(sector);
	lineC += Form(",%8.2f,%5.2f", val,TMath::Min(99.99,valError)); 
      }
      lineC += ",\""; lineC += RF[f]; lineC += "\"},";
      outC << lineC << endl;
    }
    outC << "    }" << endl;
    outC << "  }," << endl;
  }
  outC.close();
}
