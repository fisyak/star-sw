/*
  root.exe Results.C+
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
//#include "IOSectorPar.h"
//#include "IOSectorPar23.h"
//#include "IOSectorPar23Pass0.h"
//#include "IOSectorPar23Pass0Align.h"
//#include "IOSectorParPass2.h"
//#include "IOSectorParPass5.h"
//#include "IOSectorParPass5B.h"
//#include "IOSectorParPass6.h"
//#include "IOSectorParPass7.h"
//#include "IOSectorParPass8.h"
//#include "IOSectorParPass9.h"
//#include "IOSectorParPass10.h"
//#include "IOSectorParPass11.h" /* BackToIrakliParameters */
//#include "IOSectorParPass12.h" /* Repeat with Pass8 */
//#include "IOSectorParPass13.h"   /* TpcSurver_2024 */
//#include "IOSectorParPass14.h"   /* TpcSurver_2024 TpcOuterSectorPositionB_from_Pass13 */
//#include "IOSectorParPass15.h"   /* TpcSurver_2024 TpcOuterSectorPositionB_from_Pass14 no 1 mrad rotation for RunXXI */
//#include "IOSectorParPass16.h"   /* TpcSurver_2024 Ideal */
//#include "IOSectorParPass17.h"   
//#include "IOSectorParPass18.h"   /* Half step */
#include "IOSectorParPass19.h"   /* Half step, no angles, from Pass16 */
#include "THStack.h"
#endif
//#define __DB__
#ifdef __DB__
struct db_t {
  Int_t sector;
  Double_t x, gamma;
  const Char_t *comment;
};
db_t Db[24] = {
  { 1,  48.00,   0.56, "2000-05-01 00:00:05"},
  { 2,-241.00,  -0.73, "2000-05-01 00:00:05"},
  { 3, -28.00,  -0.19, "2000-05-01 00:00:05"},
  { 4,  -6.00,  -0.17, "2000-05-01 00:00:05"},
  { 5, 151.00,   0.11, "2000-05-01 00:00:05"},
  { 6, 181.00,  -0.20, "2000-05-01 00:00:05"},
  { 7,   5.00,  -0.34, "2000-05-01 00:00:05"},
  { 8, 360.00,  -0.20, "2000-05-01 00:00:05"},
  { 9,-202.00,  -0.47, "2000-05-01 00:00:05"},
  {10, 108.00,   0.20, "2000-05-01 00:00:05"},
  {11, 108.00,  -0.17, "2000-05-01 00:00:05"},
  {12,  75.00,   0.17, "2000-05-01 00:00:05"},
  {13,  76.00,  -0.26, "2000-05-01 00:00:05"},
  {14, 364.00,  -0.10, "2000-05-01 00:00:05"},
  {15, 190.00,   0.06, "2000-05-01 00:00:05"},
  {16,  50.00,  -0.05, "2000-05-01 00:00:05"},
  {17,-143.00,  -0.08, "2000-05-01 00:00:05"},
  {18,-146.00,   0.15, "2000-05-01 00:00:05"},
  {19,-207.00,  -0.51, "2000-05-01 00:00:05"},
  {20,-213.00,  -0.37, "2000-05-01 00:00:05"},
  {21,-133.00,   0.41, "2000-05-01 00:00:05"},
  {22,  -5.00,   0.35, "2000-05-01 00:00:05"},
  {23,-316.00,  -0.13, "2000-05-01 00:00:05"},
  {24,  29.00,  -0.48, "2000-05-01 00:00:05"} 
};
#endif /* __DB__ */
TCanvas *c1 = 0;
THStack *hs[6];
TLegend *leg[6];
//________________________________________________________________________________
void Results(const Char_t *opt="") {
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
  TFile *fOut = new TFile("Results.root","recreate");
#ifdef __DB__
  TH1D *dbh[6]; memset(dbh, 0, sizeof(dbh));
  for (Int_t i = 0; i < 6; i++) {
    if ( ! (i == 0) && !(i == 5)) continue;
    dbh[i] = (TH1D *) gDirectory->Get(Form("Db%s",nameK[i]));
    if (dbh[i]) delete dbh[i];
    dbh[i] = new TH1D(Form("Db%s",nameK[i]),Form("Alignment from Db for %s",names[i]), 24, 0.5, 24.5);
    dbh[i]->SetLineColor(2);
    dbh[i]->SetMarkerStyle(1);
    cout << "Create: " << dbh[i]->GetName() << "\t" << dbh[i]->GetTitle() << endl;
    Int_t m = 0;
    if (i == 5) m = 1;
    for (Int_t j = 0; j < 24; j++) {
      Double_t *XX = &Db[j].x;
      Double_t s = 1;
      if (Db[j].sector > 12) s = -1;
      dbh[i]->SetBinContent(Db[j].sector,s*XX[m]);
    }
    dbh[i]->SetLineColor(1);
    dbh[i]->SetMarkerColor(1);
  }
#endif
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
	} else if (TString(Passes[k].PassName).Contains("FF.1mrad")) {
	  color++;
	  dath[k][i]->SetMarkerStyle(24);
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
#ifdef __DB__
    if (dbh[i]) {
      if (dbh[i]->GetMaximum() > ymax) ymax = dbh[i]->GetMaximum();
      if (dbh[i]->GetMinimum() < ymin) ymin = dbh[i]->GetMinimum();
      //      dbh[i]->Draw("same"); //dbh[i]->Draw("samee");
      hs[i]->Add(dbh[i]);
      if (leg[i]) leg[i]->AddEntry(dbh[i],"DB 05/01/00");
    }
#endif
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
