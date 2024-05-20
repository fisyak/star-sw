//  cat */*/IO/*IO.h > IO.h
/*
  root.exe ResultsIO.C+
  root.exe 'ResultsIO.C+("2019|2020|2021")'
  root.exe 'ResultsIO.C+("2022")'
  root.exe 'ResultsIO.C+("2023|2024")'
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
#include "TArrayI.h"
#include "TPRegexp.h"
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
TCanvas *c1 = 0;
THStack *hs[6];
TLegend *leg[6];
TString OutputName;
void DumpRes2Par(
		 TString optFF = "2019_FF+2021_FF+2022_FF+2023_FF+2024_FF",
		 TString optRF = "2019_RF+2020_RF+2021_RF+2022_RF+2023_RF+2024_RF") {
		 
  TH1D *hist[2][6] = {0};
  TString RF[2] = {optFF, optRF};
  RF[0].ReplaceAll("/","_");
  RF[1].ReplaceAll("/","_");
  const Char_t *nameK[6] = {"Dx","Dy","Dz","Da",     "Db",    "Dg"};
  for (Int_t f = 0; f < 2; f++) 
    for (Int_t k = 0; k < 6; k++) {
      TString Name(Form("%s%s",nameK[k],RF[f].Data()));
      hist[f][k] = (TH1D *) gDirectory->Get(Name);
      if (! hist[f][k]) {
	cout << "Hisogram " << Name.Data() << " is missing" << endl;
	return;
      } else {
	cout << "Hisogram " << Name.Data() << " is loaded" << endl;
      }
    }
  TString Out("IOSectorPar");
  Out += OutputName;
  Out += gSystem->BaseName(gSystem->WorkingDirectory());
  Out += "_Avg.h";
  ofstream outC;
  outC.open(Out.Data(), ios::out);
  Int_t d = 20190101;
  Int_t t =        1;
  if        (RF[0].BeginsWith("2019") || RF[1].BeginsWith("2019")) {
  } else if (RF[0].BeginsWith("2020") || RF[1].BeginsWith("2020")) {d = 20191125; t = 202022;
  } else if (RF[0].BeginsWith("2021") || RF[1].BeginsWith("2021")) {d = 20210129; t =  41915;
  } else if (RF[0].BeginsWith("2022") || RF[1].BeginsWith("2022")) {d = 20211110; t = 215909;
  } else if (RF[0].BeginsWith("2023") || RF[1].BeginsWith("2023")) {d = 20230507; t =  55732;
  } else if (RF[0].BeginsWith("2024") || RF[1].BeginsWith("2024")) {d = 20240403; t =  20814;
  }
  for (Int_t f = 0; f < 2; f++) {
    outC << Form("  {%8i,%6i",d,t) << ", \"" << gSystem->BaseName(gSystem->WorkingDirectory()) << "/" << RF[f].Data() <<  "\", //" << endl;
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
//________________________________________________________________________________
void ResultsIO(const Char_t *opt="") {
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
  TString Out("ResultsIO.");
  OutputName = Opt;
  OutputName.ReplaceAll("|","_");
  Out += OutputName;
  Out += ".root";
  TFile *fOut = new TFile(Out,"recreate");
  TH1::SetDefaultSumw2(kTRUE);
  c1 = new TCanvas("IO","Tpc Outer to Inner alignment parameters",1200,800);
  c1->Divide(2,2);
  Int_t NH = NP;
  if (nFR[0] > 1) NH++;
  if (nFR[1] > 1) NH++;
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
      dath[k] = Pass[k-NP].GetHist(names, nameK, k-NP+1, 24);
    }
  }
  for (Int_t i = 0; i < 6; i++) {
    if (i == 3 || i == 4) continue;
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
	}
	else if (k == NP && NH == NP + 1)  leg[i]->AddEntry(dath[k][i],"sum");
	else {
	  if (k == NP) leg[i]->AddEntry(dath[k][i],"sum over FF");
	  else         leg[i]->AddEntry(dath[k][i],"sum over RF");
	}
      }
    }
    Int_t kk = i + 1;
    if (i > 2) kk = 4;
    c1->cd(kk);
    if (! hs[i]) continue;
#if 0
    hs[i]->Draw();
#else
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
#endif
    if (leg[i]) leg[i]->Draw();
  }
  c1->Update();
  fOut->Write();
  DumpRes2Par(Pass[0].StripPass(), Pass[1].StripPass()); 
}
