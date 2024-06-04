/*  Tpc Super Sector Position based on MuTpcG.C.check TFGflag in lDb.C
    root.exe 'lDb.C(0)' MakeTpcSuperSectorB.C+
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
#include <stdio.h>
#include <string.h>
#include "Riostream.h"
#include "TString.h"
#include "TMath.h"
#include "TROOT.h"
#include "TSystem.h"
#include "TH1.h"
#include "TStyle.h"
#include "TGraph.h"
#include "TNtuple.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TFile.h"
#include "TNamed.h"
#include "THStack.h"
#include "StChain.h"
#include "tables/St_Survey_Table.h"
#include "TGeoMatrix.h"
#include "StTpcDb/StTpcDb.h"
#include "StEvent/StEnumerations.h"
#include "StDetectorDbMaker/StTpcSurveyC.h"
#include "TGraphErrors.h"
#include "TMultiGraph.h"
#include "TGeoMatrix.h"
#endif
#include "StTpcAlignerMaker/SurveyPass.h"
const Int_t N = 24;
SurveyPass_t Passes[] = {
  //#include  "StTpcAlignerMaker/W2S_Pass28_Avg.h"
  //#include  "W2S_Pass30_Avg.h"
  //#include  "W2S_Pass32_Avg.h"
  //#include  "W2S_Pass33_Avg.h"
  //#include  "W2S_Pass34_Avg.h"
  //#include  "W2S_Pass36_Avg.h"
  //#include  "W2S_Pass37_Avg.h"
  //#include  "W2S_Pass40_Avg.h"
  //#include  "W2S_Pass41_Avg.h"
  //#include  "W2S_Pass42_Avg.h"
  //#include  "W2S_Pass51_Avg.h"
  //#include  "W2S_Pass51_Avg.h" /* __INVERSE_dR__ */
  //#include  "W2S_Pass60_Avg.h"   /* new transport Half step*/
  //#include  "W2S_Pass62_Avg.h"   /* new transport HalfStep*/
  //#include  "W2S_Pass60_Avg.h"   /* new transport Half step dR^-1*/
  //#include  "W2S_Pass64_Avg.h"   /* new transport Half step dR^-1*/
  //#include  "W2S_Pass68_Avg.h"   /* new transport dR^-1 * Flip^-1*/
  //#include  "W2S_Pass71_Avg.h"   /* new transport dR^-1 * Flip^-1*/
  //#include  "W2S_Pass68_Avg.h"   /* new transport dR * Flip^-1*/
  //#include  "W2S_Pass73_Avg.h"   /* new transport dR * Flip^-1*/
  //#include  "ResultsAlignerW2S.h"  /* Pass 68 LSF */
  //#include  "ResultsAlignerW2S.h"  /* Pass 75 LSF */
  //#include  "ResultsAlignerW2S.h"  /* Pass 78 LSF */
  //#include  "ResultsAlignerW2S.h"  /* Pass 80 LSF */
  //#include  "ResultsAlignerW2S.h"  /* Pass 81 LSF */
  //#include  "ResultsAlignerW2S.h"  /* Pass 82 LSF */
  //#include  "ResultsAlignerW2S.h"  /* Pass 83 LSF */
  //#include  "W2S_Pass124_Avg.h"  /* __SCALEbyHalf__ */
  //#include  "W2S_Pass125_Avg.h" /* ! __SCALEbyHalf__ */
  //#include  "W2S_Pass128_Avg.h"
  //#include  "W2S_2019_2020Pass129_Avg.h"
  //#include  "W2S_2021Pass129_Avg.h"
  //#include  "W2S_2022Pass129_Avg.h"
  //#include  "W2S_2023Pass129_Avg.h"
  //#include  "W2S_2024Pass129_Avg.h"
  //#include  "W2S_Pass131_Avg.h"
  //#include  "W2S_Pass131_Avg.h" /* __INVERSE_dR__  */
  //#include  "W2S_2019Pass131_Avg.h" /* __INVERSE_dR__  __SCALEbyHalf__ */
  //#include  "W2S_2020_2021Pass131_Avg.h" /* __INVERSE_dR__  __SCALEbyHalf__ */
  //#include  "W2S_2022Pass131_Avg.h"  /* __INVERSE_dR__  __SCALEbyHalf__ */
  //#include  "W2S_2023Pass131_Avg.h"  /* __INVERSE_dR__  __SCALEbyHalf__ */
  //#include  "W2S_2023Pass131_Avg.h"  /* __INVERSE_dR__  __SCALEbyHalf__ */

  //#include  "W2S_2019Pass137_Avg.h" /* __INVERSE_dR__  __SCALEbyHalf__ */
  //#include  "W2S_2020_2021Pass137_Avg.h" /* __INVERSE_dR__  __SCALEbyHalf__ */
  //#include  "W2S_2022Pass137_Avg.h"  /* __INVERSE_dR__  __SCALEbyHalf__ */
  //#include  "W2S_2023Pass137_Avg.h"  /* __INVERSE_dR__  __SCALEbyHalf__ */
  //#include  "W2S_2024Pass137_Avg.h"  /* __INVERSE_dR__  __SCALEbyHalf__ */

  //  #include  "W2S_2019Pass138_Avg.h" /* __INVERSE_dR__  __SCALEbyHalf__ */
  //#include  "W2S_2020_2021Pass138_Avg.h" /* __INVERSE_dR__  __SCALEbyHalf__ */
  //#include  "W2S_2022Pass138_Avg.h"  /* __INVERSE_dR__  __SCALEbyHalf__ */
  //#include  "W2S_2023Pass138_Avg.h"  /* __INVERSE_dR__  __SCALEbyHalf__ */
  //#include  "W2S_2024Pass138_Avg.h"  /* __INVERSE_dR__  __SCALEbyHalf__ */

  //#include  "W2S_2019Pass139_Avg.h" /* __INVERSE_dR__ __DONTSMOOTH__ */
  //#include  "W2S_2020_2021Pass139_Avg.h" /* __INVERSE_dR__ __DONTSMOOTH__ */
  //#include  "W2S_2022Pass139_Avg.h" /* __INVERSE_dR__ __DONTSMOOTH__ */
  //#include  "W2S_2023Pass139_Avg.h" /* __INVERSE_dR__ __DONTSMOOTH__ */
#include  "W2S_2024Pass139_Avg.h" /* __INVERSE_dR__ __DONTSMOOTH__ */
};
//#define __SCALEbyHalf__
#define __INVERSE_dR__
const  Int_t NP = sizeof(Passes)/sizeof(SurveyPass_t);
  
//________________________________________________________________________________

TCanvas *c1 = 0;
StMaker *dbMk = 0;
StChain *chain = 0;
static THStack *hs[6];
static TLegend *leg[6];
#ifndef __SCALEbyHalf__
static const Double_t scale = 1.0;
#else
static const Double_t scale = 0.5;
#endif
static Int_t _debug = 1;
#define PrPP(B) if (_debug) {cout  << (#B) << " = \t";  (B).Print();}
#define PrPI(i,B) if (_debug) {cout  << (#B) << "( i = " << i << ")  = \t";  (B).Print();}
//________________________________________________________________________________
void MakeSuperSectorPositionBTable(SurveyPass_t Pass, TString opt = "B"){
  const Char_t *plots[3] = {"dXS","dYS","dZS"};
  St_SurveyC   *chair = 0;
  if      (opt == "B") chair = St_SurveyC::instance("TpcSuperSectorPosition");
  else if (opt == "D") chair = St_SurveyC::instance("TpcSuperSectorPositionD");
  if (! chair) {
    cout << "chair for TpcSuperSectorPosition" << opt.Data() << " has not been found" << endl;
    return;
  }
  St_Survey *TpcSuperSectorPositionB = (St_Survey *) chair->Table(); //chain->GetDataBase("Geometry/tpc/TpcSuperSectorPositionB");
  if (! TpcSuperSectorPositionB)  {cout << "TpcSuperSectorPosition" << opt.Data() << "  has not been found"  << endl; return;}
  Int_t Nrows = TpcSuperSectorPositionB->GetNRows();
  TpcSuperSectorPositionB->Print(0,Nrows);
  Survey_st *TpcSuperSectorOld         = TpcSuperSectorPositionB->GetTable();        
  Survey_st row[24];
  for (Int_t i = 0; i < 24; i++) {
    Int_t sector = i + 1;
    Int_t l = i;
    TGeoHMatrix GL;
    StBeamDirection part = east;
    if (i < 12) part = west;
    if (l < Nrows) {
      row[i] = TpcSuperSectorOld[i];
      GL.SetRotation(&TpcSuperSectorOld[i].r00);
      GL.SetTranslation(&TpcSuperSectorOld[i].t0); if (_debug) {cout << "s: " << i+1 << " GL\t"; GL.Print();}
    } else {
      GL = *gGeoIdentity;
    }
    Double_t dxyz[3], drot[3];
    dxyz[0] = 1e-4*Pass.Data[i].Dx;
    dxyz[1] = 1e-4*Pass.Data[i].Dy;
    dxyz[2] = 1e-4*Pass.Data[i].Dz;
    drot[0] = Pass.Data[i].Dalpha*1e-3;
    drot[1] = Pass.Data[i].Dbeta*1e-3; 
    drot[2] = Pass.Data[i].Dgamma*1e-3;
    memcpy(&row[l].sigmaRotX, drot, 3*sizeof(Double_t));
    memcpy(&row[l].sigmaTrX, dxyz, 3*sizeof(Double_t));
    Double_t xyz[3];
    xyz[0] = 1e-4*Pass.Data[i].x*scale;
    xyz[1] = 1e-4*Pass.Data[i].y*scale;
    xyz[2] = 1e-4*Pass.Data[i].z*scale;
    TGeoHMatrix dR;
#define __ROTATION__
#ifdef __ROTATION__
    dR.RotateX( TMath::RadToDeg()*Pass.Data[i].alpha*1e-3*scale);
    dR.RotateY( TMath::RadToDeg()*Pass.Data[i].beta*1e-3*scale); 
    dR.RotateZ( TMath::RadToDeg()*Pass.Data[i].gamma*1e-3*scale);
#endif /* __ROTATION__ */
    dR.SetTranslation(xyz);
    if (_debug) {
      cout << "Additional rotation for Super Sector: dR\t"; dR.Print();
    }
#ifndef __INVERSE_dR__
    TGeoHMatrix GLnew = GL*dR; cout << "GLNew = GL * dR "; GLnew.Print();
#else
    TGeoHMatrix GLnew = GL*dR.Inverse(); cout << "GLNew = Gl * dR^^-1 "; GLnew.Print();
#endif
    Double_t *R = GLnew.GetRotationMatrix();
    memcpy(&row[l].r00, R, 9*sizeof(Double_t));
    Double_t *tr = GLnew.GetTranslation();
    memcpy(&row[l].t0, tr, 3*sizeof(Double_t));
  }
  Int_t date = Pass.date;
  Int_t time = Pass.time;
  TString fOut =  Form("TpcSuperSectorPosition%s.%8i.%06i.C", opt.Data(), date, time);
  ofstream out;
  cout << "Create " << fOut.Data() << endl;
  out.open(fOut.Data());
  out << "TDataSet *CreateTable() {" << endl;
  out << "  if (!gROOT->GetClass(\"St_Survey\")) return 0;" << endl;
  out << "  Survey_st row[24] = {" << endl; 
  out << "    //             -gamma     beta    gamma            -alpha    -beta    alpha                x0       y0       z0" << endl;
  for (Int_t i = 0; i < 24; i++) {
    Int_t l = i;
    out << "    {" << Form("%2i",i+1) << ","; 
    Double_t *r = &(row[l].r00);
    //    cout << " ";
    for (Int_t j =  0; j <  9; j++) out << Form("%8.5f,",r[j]);
    //    cout << " ";
    for (Int_t j =  9; j < 12; j++) out << Form("%8.4f,",r[j]); 
    cout << " ";
    for (Int_t j = 12; j < 18; j++) out << Form("%8.5f,",r[j]);
    //    out << "\"" << Pass.PassName << "\"}";
    out << "\"" << Pass.Data[i].Comment << "\"}";
    if (i != 23) out << ",";
    out << endl;
  }
  cout << endl;
  out << "  };" << endl;
  out << "  St_Survey *tableSet = new St_Survey(\"TpcSuperSectorPosition" << opt.Data() << "\",24);" << endl; 
  out << "  for (Int_t i = 0; i < 24; i++) tableSet->AddAt(&row[i].Id);" << endl;
  out << "  return (TDataSet *)tableSet;" << endl;
  out << "}" << endl;
  out.close(); 
}
//________________________________________________________________________________
void MakeTpcSuperSectorB(const Char_t *opt="") {
  chain = (StChain *) StChain::GetChain();
  if (! chain) return;
  dbMk = chain->Maker("db");
  if (! dbMk) return;
  dbMk->SetDebug(1);
  gStyle->SetMarkerStyle(20);
  gStyle->SetOptStat(0);
  cout << "NP \t" << NP << endl;
  for (Int_t k = 0; k < NP; k++) {
    Passes[k].FixErrors();
  }
  Int_t NH = NP;
  if (NH == 2) NH += 2; // make average if we have only (FF + RF)/2 for SuperSector, and (FF - RF) for Inner Sector
  TH1D ***dath = new TH1D**[NH]; 
  for (Int_t p = 0; p < NH; p++) {dath[p] = new TH1D*[6]; memset(dath[p],0, 6*sizeof(TH1D*));}
  const Char_t *names[6] = {" #Deltax"," #Deltay"," #Deltaz"," #Delta #alpha"," #Delta #beta"," #Delta #gamma"};
  const Char_t *nameK[6] = {"Dx","Dy","Dz","Da",     "Db",    "Dg"};
  const Char_t *NameO[3] = {"", "sum", "dif"};
  TString Opt(opt);
  TFile *fOut = new TFile("MakeTpcSuperSectorB.root","recreate");
  for (Int_t i = 0; i < 6; i++) {
    hs[i] = new THStack(nameK[i],names[i]);
    fOut->Add(hs[i]);
#if 0
    if (i < 3) hs[i]->SetYTitle(Form("%s (#mum)",names[i]));
    else       hs[i]->SetYTitle(Form("%s (mrad)",names[i]));
    hs[i]->SetXTitle("sector");
#endif
    if (! i)     leg[i] = new TLegend(0.10,0.65,0.30,0.90);
    else         leg[i] = 0;
  }
  TString same("e");
  TH1::SetDefaultSumw2(kTRUE);
  for (Int_t k = 0; k < NP; k++) {
    if (_debug) {Passes[k].Print();}
    Int_t date = Passes[k].date;
    Int_t time = Passes[k].time;
    if (! dbMk) return;
    dbMk->SetDateTime(date,time);
    chain->MakeEvent();
  }
  SurveyPass_t PassSum(Passes[0]);
  SurveyPass_t PassDif(Passes[0]);
  if (NP > 1) {
    PassSum.Add2(Passes[1]);
    if (_debug) {
      cout << "PassSum" << endl;
      PassSum.Print();
    }
    PassDif.Sub2(Passes[1]);
    if (_debug) {
      cout << "PassDif" << endl;
      PassDif.Print();
    }
  }
  //  TCanvas *c0 = new TCanvas("c0","");
  for (Int_t k = 0; k < NH; k++) {
    SurveyPass_t *currPass = 0;
    Int_t color = k+1;
    TString Name;
    TString Title;
    Double_t ymin =  1e10;
    Double_t ymax = -1e10;
    Int_t m = 0;
    if (k < NP) {
      currPass = &Passes[k];
    } else if (k == NP) {
      m = 1;
      currPass = &PassSum;
    } else {
      m = 2;
      currPass = &PassDif;
    }
    currPass->Print();
    if (k < NP)     dath[k] = currPass->GetHist(names, nameK);
    else            dath[k] = currPass->GetHist(names, nameK, k-NP+1, 21);
    for (Int_t i = 0; i < 6; i++) {
      hs[i]->Add(dath[k][i]);
      if (leg[i]) {
	if      (k < NP)      leg[i]->AddEntry(dath[k][i],currPass->PassName);
	else if (k == NP)     leg[i]->AddEntry(dath[k][i],"(FF+RF)/2");
	else if (k == NP + 1) leg[i]->AddEntry(dath[k][i],"(FF-RF)/2");
      }
    }
  }
  c1 = new TCanvas("IO","Tpc Super Sector alignment parameters",1200,800);
  c1->Divide(3,2);
  for (Int_t i = 0; i < 6; i++) {
    c1->cd(i+1);
    if (! hs[i]) continue;
    TString same("e");
    Double_t ymax = hs[i]->GetMaximum("nostack");
    Double_t ymin = hs[i]->GetMinimum("nostack");
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
  MakeSuperSectorPositionBTable(PassSum,"B");
  MakeSuperSectorPositionBTable(PassDif,"D");
}
