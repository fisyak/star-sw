/* 
   root.exe *.root 'lDb.C(0)' Adc2Sc.C+
 */
#if !defined(__CINT__) || defined(__MAKECINT__)
//#include <ostream>
#include "Riostream.h"
#include <stdio.h>
#include "TROOT.h"
#include "TSystem.h"
#include "TMath.h"
#include "TH1.h"
#include "TH2.h"
#include "TH3.h"
#include "TPaveStats.h"
#include "TStyle.h"
#include "TF1.h"
#include "TKey.h"
#include "TProfile.h"
#include "TTree.h"
#include "TChain.h"
#include "TDirectory.h"
#include "TFile.h"
#include "TNtuple.h"
#include "TCanvas.h"
#include "TString.h"
#include "TPRegexp.h"
#include "TList.h"
#include "TLegend.h"
#include "TPaveText.h"
#include "TList.h"
#include "TIterator.h"
#include "TF2.h"
#include "StDetectorDbMaker/St_tpcPadConfigC.h"
#if __GNUC__ < 7
#include "TQtZoomPadWidget.h"
#include "TQtCanvas2Html.h"
#endif
#include "TPolynomial.h"
#include "TROOT.h"
#endif
TObjArray FitFiles;
void DrawList() {} 
//________________________________________________________________________________
TF1 *GausP0(){
  static TF1 *f = 0;
  if (! f) {
    f = new TF1("gauspol0","gaus(0)+pol0(3)",-1,1);
  }
  //  f->SetParLimits(0,10.,1e10);
  f->SetParLimits(1,-0.5,0.5);
  f->SetParLimits(2,0.01,5.0);
  f->SetParameters(10., 0., 0.2, 0.);
  return  f;
}
//________________________________________________________________________________
TF1 *GausP2(){
  static TF1 *f = 0;
  if (! f) {
    f = new TF1("gauspol2","gaus(0)+pol2(3)",-1,1);
  }
  //  f->SetParLimits(0,10.,1e10);
  f->SetParLimits(1,-0.5,0.5);
  f->SetParLimits(2,0.01,5.0);
  f->SetParameters(10., 0., 0.2, 0., 0., 0.);
  return  f;
}
//________________________________________________________________________________
Double_t rowVolume(Double_t *x, Double_t *p) {
  Double_t z = x[0];
  Int_t row  = TMath::Abs(x[1]);
  Double_t Volume = 0.0;
  if (row == 0) return Volume;
  Double_t dZ = p[0];
  Double_t dY =  St_tpcPadConfigC::instance()->innerSectorRowPitch1(); // St_tpcPadConfigC::instance()->innerSectorPadLength(); //
  Double_t dX = St_tpcPadConfigC::instance()->padsPerRow(1,row)*St_tpcPadConfigC::instance()->innerSectorPadPitch();
  if (row > St_tpcPadConfigC::instance()->innerPadRows(20)) {
    dY = St_tpcPadConfigC::instance()->outerSectorRowPitch();; // St_tpcPadConfigC::instance()->outerSectorPadLength();//  
    dX = St_tpcPadConfigC::instance()->padsPerRow(1,row)*St_tpcPadConfigC::instance()->outerSectorPadPitch();
  }
  Volume = 12*dX*dY*dZ;
  return Volume;
}
//________________________________________________________________________________
Double_t AveragedRowRadius(Int_t rows) {
  Int_t row = TMath::Abs(rows);
  Double_t R = St_tpcPadConfigC::instance()->radialDistanceAtRow(1,row);
  if (R <= 0.0) return 0.0;
  return 1.01151*R; // Average over phi [-15, +15] decrees
#if 0
  Double_t dX = St_tpcPadConfigC::instance()->padsPerRow(1,row)*St_tpcPadConfigC::instance()->innerSectorPadPitch();
  if (row > St_tpcPadConfigC::instance()->innerPadRows(20)) {
    dX = St_tpcPadConfigC::instance()->padsPerRow(1,row)*St_tpcPadConfigC::instance()->outerSectorPadPitch();
  }
  return TMath::Sqrt(R*R + dX*dX/16.0);
#endif
}
//________________________________________________________________________________
double SpaceChargeRadialDependence(double Radius) {
  return ( 3191./(Radius*Radius) + 122.5/Radius - 0.395 ) / 15823. ; // ( 3191./(R*R) + 122.5/R - 0.395 ) / 15823.  => slope=  -1.63924e+00
}
double SpaceChargeFXTRadialDependenceEast(double Radius) {
  // normalized for integral[47.9,200.0] (2427.3/R + 42.2021) * R dR
  return ( 2427.3/Radius + 42.2021 ) / 1164374.8 ;// ( 2427.3/R + 42.2021 ) / 1164374.8   => slope = -4.00732e-01
}
double SpaceChargeFXTRadialDependenceWest(double Radius) {
  // normalized for integral[47.9,200.0] (5706.44/R + 16.2186) * R dR
  return ( 5706.44/Radius + 16.2186 ) / 1173715.5 ; //  ( 5706.44/R + 16.2186 ) / 1173715.5 => slope = -7.48119e-01
}
Double_t spaceChargeFunc(Double_t R, Double_t *p) {
  return p[1]*TMath::Exp(p[2]*TMath::Log(R)); 
}
//________________________________________________________________________________
Double_t SpaceCharge(Double_t *x, Double_t *p) {
  Int_t k = p[0];
  Double_t scale = p[1];
  Int_t row = TMath::Abs(TMath::Nint(x[0]));
  Double_t R = AveragedRowRadius(row);
  if (TMath::Abs(R) <= 40.0) return 0.0;
  if (k == 0) {// Collider
    return scale*SpaceChargeRadialDependence(R);
  } else if (k == 1) {
    if (x[0] > 0) {// Fixed Target west
      return scale*SpaceChargeFXTRadialDependenceWest(R);
    } else if (x[0] < 0) {// Fixed Target east
      return scale*SpaceChargeFXTRadialDependenceEast(R);
    }
  } else {
    return spaceChargeFunc(R, p);
  }
  return 0;
}
//________________________________________________________________________________
TF1 *SCFun() {
  static TF1 *f = 0;
  if (! f) {
    f = new TF1("SC", SpaceCharge, -72.5, 72.5, 3);
    f->SetNpx(145);
    f->SetParName(0,"case");
    f->FixParameter(0,0.0);
    f->SetParName(1,"scale");
    f->SetParameter(1, 1.0);
    f->SetParName(2,"slope");
    f->FixParameter(2, -2.0);
  }
  return f;
}
//________________________________________________________________________________
TF2 *RowVolume() {
  static TF2 *f = 0;
  if (! f) {
    f = new TF2("RowVolue", rowVolume, -210, 210, -72, 72, 1);
    f->SetNpx(210);
    f->SetNpy(145);
    f->SetParName(0,"dZ");
    f->SetParameter(0, 20);
  }
  return f;
}
      
//________________________________________________________________________________
void Adc2Sc(Int_t nx = 0, Int_t ny = 0){
  TString Out("Adc2Sc.data");
  ofstream out;
  if (gSystem->AccessPathName(Out)) out.open(Out, ios::out); //"Results.list",ios::out | ios::app);
  else                              out.open(Out, ios::app);
  //________________________________________________________________________________
  //  TH1::SetDefaultSumw2();
  Int_t NF = 0;
  TSeqCollection *files = gROOT->GetListOfFiles();
  gStyle->SetOptStat(0);
  if (! files) return;
  Int_t nn = files->GetSize();
  TFile **FitFiles = new TFile *[nn];
  if (nn < 1) return;
  TIter next(files);
  TFile *f = 0;
  while ( (f = (TFile *) next()) ) { 
    TH2F *dEOnTrack    = (TH2F*) f->Get("dEOnTrack"); 
    TH2F *dESC         = (TH2F*) f->Get("dESC"); 
    if (! dEOnTrack && ! dESC) continue;
    FitFiles[NF] = f;
    NF++;
  }
  if (NF < 1) return;
  if (! nx || ! ny) {
    ny = TMath::Ceil(TMath::Sqrt(NF));
    nx = NF/ny;
    if (nx*ny != NF) nx++;
    if (NF <= 3) {nx =1; ny = NF;} 
  }
  cout << "no. of histograms " << NF << " nx x ny " << nx << " x " << ny << endl;
  TString cTitle("dE");
  TCanvas *c = new TCanvas(cTitle,cTitle,600*nx,600*ny);
  c->Divide(nx,ny);

  Int_t pad = 0;
  for (Int_t k = 0; k < NF; k++) {
    f = FitFiles[k];
    f->cd();
    TString fileName(gSystem->BaseName(gDirectory->GetName()));
    fileName.ReplaceAll(".root","");
    fileName = fileName.Strip(TString::kLeading,'0');
    Double_t noEvents = 0;
    TH1F *Multiplicity = (TH1F*) gDirectory->Get("Multiplicity");
    TH2F *AdcSC        = (TH2F*) gDirectory->Get("AdcSC");     
    TH2F *AdcOnTrack   = (TH2F*) gDirectory->Get("AdcOnTrack");
    TH2F *dEOnTrack    = (TH2F*) gDirectory->Get("dEOnTrack"); 
    TH2F *dESC         = (TH2F*) gDirectory->Get("dESC"); 
    TH1D *dESCy        = 0;
    if (dESC) { // PHQMD ~/TPC/reco/TFG26m/2025/RF/PHQMD.3p85GeV_fixedTarget_2025/dESC_PHQMD.3p85GeV_fixedTarget_2025.root
      noEvents = 20046;
      TAxis *ax = dESC->GetXaxis();
      TAxis *ay = dESC->GetYaxis();
      Int_t nx = ax->GetNbins();
      Int_t ny = ay->GetNbins();
      dESCy = new TH1D("dESCy","<dE> [eV/cm^{3}/event] ; row (+W/-E)", ny, ay->GetXmin(), ay->GetXmax());
      for (Int_t iy = 1; iy <= ny; iy++) {
	Double_t row = ay->GetBinCenter(iy);
	Double_t dETavY = 0.0;
	Int_t nyentry = 0;
	for (Int_t ix = 1; ix <= nx; ix++) {
	  Double_t dE = dESC->GetBinContent(ix,iy);
	  if (dE <= 0.0) continue;
	  Double_t z = ax->GetBinCenter(ix);
	  Double_t vol = RowVolume()->Eval(z,row);
	  if (vol <= 0.0) continue;
	  Double_t dET = dE/vol; // keV/cm^3
	  nyentry++;
	  dETavY += dET;
	}
	if (nyentry > 0) {
	  dESCy->SetBinContent(iy, 1e3*dETavY/nyentry/noEvents);
	}
      }
     } else {    // Real Data
      if (! Multiplicity ||
	  ! AdcSC      ||
	  ! AdcOnTrack ||
	  ! dEOnTrack) continue;
      noEvents = Multiplicity->GetEntries();
      if (noEvents <= 0.0) continue;
      TAxis *ax = AdcSC->GetXaxis();
      TAxis *ay = AdcSC->GetYaxis();
      Int_t nx = ax->GetNbins();
      Int_t ny = ay->GetNbins();
      TH2F *dESC = new TH2F(*AdcSC);
      dESC->SetName("dESC");
      TString Title("dE [keV/cm^{3} ; Z [cm] ; row (+W/-E)");
      dESC->SetTitle(Title);
      dESC->Reset();
      dESCy = new TH1D("dESCy","<dE> [eV/cm^{3}/event] ; row (+W/-E)", ny, ay->GetXmin(), ay->GetXmax());
      for (Int_t iy = 1; iy <= ny; iy++) {
	Double_t row = ay->GetBinCenter(iy);
	Double_t dETavY = 0.0;
	Int_t nyentry = 0;
	for (Int_t ix = 1; ix <= nx; ix++) {
	  Double_t adcT = AdcSC->GetBinContent(ix,iy);
	  if (adcT <= 0.0) continue;
	  Double_t z = ax->GetBinCenter(ix);
	  Double_t vol = RowVolume()->Eval(z,row);
	  if (vol <= 0.0) continue;
	  Double_t dE = dEOnTrack->GetBinContent(ix,iy);
	  if (dE <= 0.0) continue;
	  Double_t adc = AdcOnTrack->GetBinContent(ix,iy);
	  if (adc <= 0.0) continue;
	  Double_t dET = adcT/adc*dE/vol; // keV/cm^3
	  nyentry++;
	  dETavY += dET;
	  dESC->SetBinContent(ix,iy,dET);
	}
	if (nyentry > 0) {
	  dESCy->SetBinContent(iy, 1e3*dETavY/nyentry/noEvents);
	}
      }
    }
    pad++;
    c->cd(pad);// ->SetLogz(1);
    dESCy->SetStats(0);
    dESCy->Draw();
    //    TPaveText *summary = new TPaveText(0.6,0.5,0.5,0.8);
    //    summary->SetTextAlign(12);
    //    summary->SetTextSize(0.08);
    //    summary->Draw();
    TLegend *l = new TLegend(0.1,0.85,0.95,0.9);
    TLegend *l2 = new TLegend(0.5,0.75,0.95,0.85);
    //    summary->AddText("R^{slope}");
    l->AddEntry(dESCy,fileName);
    TString Line(fileName);
    TF1 *SC = SCFun();
    SC->SetLineColor(1);
    SC->SetParameter(0,0);
    if (fileName.Contains("fixedTarget")) SC->SetParameter(0,1);
    Double_t east = dESCy->Integral(1,72);
    Double_t west = dESCy->Integral(73,145);
    SC->FixParameter(2,-2.0);
    SC->SetParameter(1,east);
    dESCy->Fit(SC,"er","",-72,-1);
    SC->SetParameter(1,west);
    dESCy->Fit(SC,"er+","",10,72);
    SC->SetLineColor(2);
    SC->SetParameter(0,2);
    SC->ReleaseParameter(2);
    dESCy->Fit(SC,"er+","",-72,-10);
    l2->AddEntry(SC,Form("East slope = %7.3f +/- %6.3f", SC->GetParameter(2), SC->GetParError(2))); 
    //    summary->AddText(Form("East slope = %7.3f +/- %6.3f", SC->GetParameter(2), SC->GetParError(2))); 
    Line += Form("\tEast slope = %7.3f +/- %6.3f", SC->GetParameter(2), SC->GetParError(2));
    SC->SetLineColor(3);
    dESCy->Fit(SC,"er+","",15,72);
    l2->AddEntry(SC,Form("West slope = %7.3f +/- %6.3f", SC->GetParameter(2), SC->GetParError(2))); 
    //    summary->AddText(Form("west slope = %7.3f +/- %6.3f", SC->GetParameter(2), SC->GetParError(2))); 
    Line += Form("\tWest slope = %7.3f +/- %6.3f", SC->GetParameter(2), SC->GetParError(2));
    l->Draw();
    l2->Draw();
    cout << Line.Data() << endl;
    out << Line.Data() << endl;
  }
  c->Update();
#if __GNUC__ < 7
  TQtZoomPadWidget *zoomer = new TQtZoomPadWidget();  // Create the Pad zoomer widget
  //  Double_t zoom = 1.;
  //  zoomer->SetZoomFactor(zoom);
  TQtCanvas2Html  TQtCanvas2Html(c,  900, 900, "./", zoomer);
  //  TQtCanvas2Html  TQtCanvas2Html(c, zoom, "./", zoomer);
#endif
  out.close();
}
#if 0
Collider                East slope        West slope
7p7GeV_2019	 -1.338 +/-  0.080 -1.419 +/-  0.082
7p7GeV_2021	 -1.345 +/-  0.011 -1.330 +/-  0.011
9p2GeV_2019	 -1.344 +/-  0.066 -1.377 +/-  0.068
9p2GeV_2020	 -1.335 +/-  0.037 -1.270 +/-  0.037
9p2GeVb_2020	 -1.341 +/-  0.011 -1.309 +/-  0.011
9p2GeVc_2020	 -1.333 +/-  0.007 -1.329 +/-  0.007
11p5GeV_2020	 -1.348 +/-  0.005 -1.340 +/-  0.005
14p5GeV_2019	 -1.400 +/-  0.025 -1.404 +/-  0.026
17p3GeV_2021	 -1.326 +/-  0.029 -1.308 +/-  0.028
19GeV_2019	 -1.369 +/-  0.031 -1.375 +/-  0.031
AuAu200GeV_2019	 -1.162 +/-  0.013 -1.227 +/-  0.014
AuAu_2023	 -1.192 +/-  0.003 -1.069 +/-  0.003
pp500_2022	 -0.674 +/-  0.008 -0.734 +/-  0.007


fixed Targer
3p85GeV_fixedTarget_2025_PHQMD	East slope =  -1.777 +/-  0.081	West slope =  -1.736 +/-  0.119
3p85GeV_fixedTarget_2021	East slope =  -0.954 +/-  0.023	West slope =  -1.451 +/-  0.021
3p85GeV_fixedTarget_2021	East slope =  -0.954 +/-  0.023	West slope =  -1.451 +/-  0.021
4p59GeV_fixedTarget_2019	East slope =  -1.035 +/-  0.038	West slope =  -1.476 +/-  0.040
5p75GeV_fixedTarget_2020	East slope =  -1.064 +/-  0.043	West slope =  -1.486 +/-  0.045
7.3GeV_fixedTarget_2019	East slope =  -1.142 +/-  0.048	West slope =  -1.509 +/-  0.052
7p3GeV_fixedTarget_2020	East slope =  -1.155 +/-  0.037	West slope =  -1.485 +/-  0.040
8p65GeV_fixedTarget_2026	East slope =  -1.414 +/-  0.011	West slope =  -1.204 +/-  0.011
9p8GeV_fixedTarget_2020	East slope =  -1.310 +/-  0.030	West slope =  -1.484 +/-  0.035
9p8GeV_fixedTarget_2026	East slope =  -0.699 +/-  0.007	West slope =  -0.189 +/-  0.009
9p8GeV_fixedTarget_2026a	East slope =   0.096 +/-  0.024	West slope =  -0.522 +/-  0.029
9p8GeV_fixedTarget_2026b	East slope =  -1.248 +/-  0.013	West slope =  -0.865 +/-  0.014
13p5GeV_fixedTarget_2020	East slope =  -1.435 +/-  0.039	West slope =  -1.513 +/-  0.046
13p5GeV_fixedTarget_2026	East slope =  -1.823 +/- 122959.646	West slope =  -1.174 +/-  0.010
19p5GeV_fixedTarget_2020	East slope =  -1.359 +/-  0.039	West slope =  -1.556 +/-  0.044
26p5GeV_fixedTarget_2020	East slope =  -1.442 +/-  0.040	West slope =  -1.541 +/-  0.047
26p5GeV_fixedTarget_2021	East slope =  -1.270 +/-  0.102	West slope =  -1.575 +/-  0.107
31GeV_fixedTarget_2019	East slope =  -1.071 +/-  0.066	West slope =  -1.539 +/-  0.086
31p2GeV_fixedTarget_2020	East slope =  -1.336 +/-  0.032	West slope =  -1.529 +/-  0.040
44p5GeV_fixedTarget_2021	East slope =  -1.145 +/-  0.085	West slope =  -1.454 +/-  0.106
70GeV_fixedTarget_2021	East slope =  -1.049 +/-  0.109	West slope =  -1.419 +/-  0.131
100GeV_fixedTarget_2021	East slope =  -1.051 +/-  0.111	West slope =  -1.435 +/-  0.137

#endif
