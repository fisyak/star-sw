//  cat */*/IO/*IO.h > IO.h
/*
  root.exe ResultsIO.C+
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
//#include "StTpcAlignerMaker/IOSectorPar.h"
//#include "StTpcAlignerMaker/IOSectorPar23.h"
//#include "StTpcAlignerMaker/IOSectorPar23Pass0.h"
//#include "StTpcAlignerMaker/IOSectorPar23Pass0Align.h"
//#include "StTpcAlignerMaker/IOSectorParPass2.h"
//#include "StTpcAlignerMaker/IOSectorParPass5.h"
//#include "StTpcAlignerMaker/IOSectorParPass5B.h"
//#include "StTpcAlignerMaker/IOSectorParPass6.h"
//#include "StTpcAlignerMaker/IOSectorParPass7.h"
//#include "StTpcAlignerMaker/IOSectorParPass8.h"
//#include "StTpcAlignerMaker/IOSectorParPass9.h"
//#include "StTpcAlignerMaker/IOSectorParPass10.h"
//#include "StTpcAlignerMaker/IOSectorParPass11.h" /* BackToIrakliParameters */
//#include "StTpcAlignerMaker/IOSectorParPass12.h" /* Repeat with Pass8 */
//#include "StTpcAlignerMaker/IOSectorParPass13.h"   /* TpcSurver_2024 */
//#include "StTpcAlignerMaker/IOSectorParPass14.h"   /* TpcSurver_2024 TpcOuterSectorPositionB_from_Pass13 */
//#include "StTpcAlignerMaker/IOSectorParPass15.h"   /* TpcSurver_2024 TpcOuterSectorPositionB_from_Pass14 no 1 mrad rotation for RunXXI */
//#include "StTpcAlignerMaker/IOSectorParPass16.h"   /* TpcSurver_2024x2 Ideal */
//#include "StTpcAlignerMaker/IOSectorParPass17.h"   
//#include "StTpcAlignerMaker/IOSectorParPass18.h"   /* Half step */
//#include "StTpcAlignerMaker/IOSectorParPass19.h"   /* Half step, no angles, from Pass16 */
//#include "StTpcAlignerMaker/IOSectorParPass20.h"   /* Half step, no angles, from Pass19 */
//#include "StTpcAlignerMaker/IOSectorParPass21.h"   /* Half step, with angles, from Pass20 */
//#include "StTpcAlignerMaker/IOSectorParPass22.h"   /* Half step, with angles, from Pass21 */
#endif
#include "THStack.h"
#include "Riostream.h"
#include "Rtypes.h"
#include "TString.h"
#include "TMath.h"
#include "SurveyPass.h"
const Int_t N = 24;
// /hlt/cephfs/reco/Pass22/
SurveyPass_t Passes[] = {
  //#include "StTpcAlignerMaker/IOSectorParPass28.h"   /* SuperSector Alignment from Pass22 */
// #include "2019/FF/IO/Results.IO_Aligner_IO.h"
// #include "2019/RF/IO/Results.IO_Aligner_IO.h"
// #include "2020/RF/IO/Results.IO_Aligner_IO.h"
// #include "2021/FF/IO/Results.IO_Aligner_IO.h"
// #include "2021/RF/IO/Results.IO_Aligner_IO.h"
// #include "2022/FF/IO/Results.IO_Aligner_IO.h"
// #include "2022/RF/IO/Results.IO_Aligner_IO.h"
// #include "2023/FF/IO/Results.IO_Aligner_IO.h"
// #include "2023/RF/IO/Results.IO_Aligner_IO.h"
#include "IO.h"
};
const  Int_t NP = sizeof(Passes)/sizeof(SurveyPass_t);
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
void ResultsIO(const Char_t *opt="") {
  gStyle->SetMarkerStyle(20);
  gStyle->SetOptStat(0);
  cout << "NP \t" << NP << endl;
  Int_t NH = NP;
  TString Opt(opt);
  if (Opt == "") {
    if (NH == 2) NH++; // make average if we have only FF + RF
    else if (NP > 2) NH = NP + 2; // make average for FF and RF
  }
  TH1D ***dath = new TH1D**[NH]; 
  for (Int_t p = 0; p < NH; p++) {dath[p] = new TH1D*[6]; memset(dath[p],0, 6*sizeof(TH1D*));}
  const Char_t *names[6] = {" #Deltax"," #Deltay"," #Deltaz"," #Delta #alpha"," #Delta #beta"," #Delta #gamma"};
  const Char_t *nameK[6] = {"Dx","Dy","Dz","Da",     "Db",    "Dg"};
  TFile *fOut = new TFile("ResultsIO.root","recreate");
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
    if (! i)     {leg[i] = new TLegend(0.85,0.7-0.04*NH,0.98,0.7);
    }  else       leg[i] = 0;
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
      if      (TString(Passes[k].PassName).Contains("2020")) color = 2;
      else if (TString(Passes[k].PassName).Contains("2021")) color = 3;
      else if (TString(Passes[k].PassName).Contains("2022")) color = 4;
      else if (TString(Passes[k].PassName).Contains("2023")) color = 6;
      else if (TString(Passes[k].PassName).Contains("2024")) color = 7;
      dath[k][i]->SetMarkerColor(color);
      dath[k][i]->SetLineColor(color);
      dath[k][i]->SetMarkerSize(2);
      dath[k][i]->SetMarkerStyle(22);
      if (k < NP) {
	if (TString(Passes[k].PassName).Contains("RF") || 
	    Opt != "" && TString(Passes[k].PassName).Contains(Opt)) {
	  dath[k][i]->SetMarkerStyle(23);
	} else if (TString(Passes[k].PassName).Contains("MF") ||
		   TString(Passes[k].PassName).Contains("ZF") ) {
	  dath[k][i]->SetMarkerStyle(21);
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
	  secs = Passes[k].Data[l].sector;
	  if (Passes[k].Data[l].X()[2*i+1] == 0.0) Passes[k].Data[l].X()[2*i+1] = 0.01;
	  if (Passes[k].Data[l].GoodMeasurement(i)) {
	    Double_t *X = Passes[k].Data[l].X();
	    val = X[2*i];
	    err = X[2*i+1];
	  } else {continue;}
	} else if (NP == 2 && k == NP && NH == NP + 1) { // Average FF+RF
	  if (Passes[0].Data[l].GoodMeasurement(i) &&
	      Passes[1].Data[l].GoodMeasurement(i)) {
	    Double_t *X0 = Passes[0].Data[l].X();
	    Double_t *X1 = Passes[1].Data[l].X();
	    secs = Passes[0].Data[l].sector;
	    val = 0.5*(X0[2*i] + X1[2*i]);
	    dath[k][i]->SetBinContent(secs,val);
	    err = TMath::Sqrt(X0[2*i+1]*X0[2*i+1]+X1[2*i+1]*X1[2*i+1])/2;
	  } else {continue;}
	} else {// Average over all FF and RF
	  Double_t valW = 0, errW = 0;
	  secs = Passes[0].Data[l].sector;
	  for (Int_t p = 0; p < NP; p++) {
	    TString RF((k == NP) ? "FF": "RF");
	    TString Name(Passes[p].PassName);
	    if (! Name.Contains(RF)) continue;
	    if (! Passes[p].Data[l].GoodMeasurement(i)) continue;
	    Double_t *X = Passes[p].Data[l].X();
	    val = X[2*i];
	    err = X[2*i+1];
	    if (err == 0.0) err = 0.01;
	    Double_t err2 = err*err;
	    valW += val/err2;
	    errW +=  1./err2;
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
	if (k < NP) {
#if 1
	  Int_t indx = TString(Passes[k].PassName).Index("Pass");
	  TString Label(Passes[k].PassName+indx);
	  Label.ReplaceAll("/IO","");
	  indx = Label.Index("/");
	  leg[i]->AddEntry(dath[k][i],Label.Data()+indx+1);
#else
	  leg[i]->AddEntry(dath[k][i],Passes[k].PassName);
#endif
	}
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
  TString Out("IOSectorPar");
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
