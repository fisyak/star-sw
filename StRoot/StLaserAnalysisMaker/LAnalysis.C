//  root.exe 'Chain.C+("*.laser.root","laser")' 'LAnalysis.C+(tChain)'
// $Log: Laser.C,v $
// Revision 1.5  2007/12/10 19:54:02  fisyak
// Add Id and Log, correct spelling error in README
//
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
#include "TStyle.h"
#include "TF1.h"
#include "TProfile.h"
#include "TTree.h"
#include "TChain.h"
#include "TFile.h"
#include "TNtuple.h"
#include "TCanvas.h"
#include "TString.h"
#include "TList.h"
#include "TLegend.h"
#include "TChain.h"
#endif
static Int_t run = 0;
static Int_t date = 0;
static Int_t Time = 0;
//             Delta/dv  All,West,East
static Double_t  DVAll[2][3];
static Double_t dDVAll[2][3];
static TChain *laser = 0;
//________________________________________________________________________________
void dPhi() {
  if (! laser) return;
  //  laser->Draw("fTracks.dPhi:fTracks.mSector>>hdPhi(12,1,25,100,-.15,0.15)","fTracks.Flag>1","colz");
  //  laser->Draw("TMath::ATan2(fTracks.Laser.dirU.mX2, fTracks.Laser.dirU.mX2)-TMath::ATan2(fTracks.dirPU.mX2,fTracks.dirPU.mX1):fTracks.mSector>>hdPhi(12,1,25,100,-.15,0.15)","fTracks.Flag>1","colz");
  laser->Draw(
	      "atan(fTracks.Laser.dirU.mX2/fTracks.Laser.dirU.mX1)-atan(fTracks.dirPU.mX2/fTracks.dirPU.mX1):fTracks.mSector>>hdPhi(12,1,25,100,-.15,0.15)",
	      "fTracks.Flag>1&&abs(fTracks.dU.mX1)<1&&abs(fTracks.dU.mX2)<1","colz");
  TH2D *dPhi = (TH2D *) gDirectory->Get("dPhi");
  if (! dPhi) return;
  dPhi->FitSlicesY();
  TH1D *dPhi_1 = (TH1D *) gDirectory->Get("dPhi_1");
  dPhi_1->SetMarkerStyle(20);
  dPhi_1->Draw("same");
  for (Int_t bin = 1; bin <= 12; bin++) {
    cout << "sector: " << 2*bin << " dPhi: " << 1e3*dPhi_1->GetBinContent(bin) << " +/- " 
	 << 1e3*dPhi_1->GetBinError(bin) << "(mrad)" << endl;
  }
}  
//________________________________________________________________________________
void dTheta() {
  if (! laser) return;
  laser->Draw("atan(fTracks.Laser.dirU.mX3)-atan(fTracks.dirPU.mX3):fTracks.mSector>>hdTheta(12,1,25,100,-.15,0.15)",
	      "fTracks.Flag>1&&abs(fTracks.dU.mX1)<1&&abs(fTracks.dU.mX2)<1","colz");
  TH2D *dTheta = (TH2D *) gDirectory->Get("hdTheta");
  if (! dTheta) return;
  dTheta->FitSlicesY();
  TH1D *dTheta_1 = (TH1D *) gDirectory->Get("hdTheta_1");
  dTheta_1->SetMarkerStyle(20);
  dTheta_1->Draw("same");
  for (Int_t bin = 1; bin <= 12; bin++) {
    cout << "sector: " << 2*bin << " dTheta: " << 1e3*dTheta_1->GetBinContent(bin) << " +/- " 
	 << 1e3*dTheta_1->GetBinError(bin) << "(mrad)" << endl;
  }
}  
//________________________________________________________________________________
void PrintdXY(TH3 *hdXY = 0) {
  if (! hdXY) return;
  TAxis *z = hdXY->GetZaxis();
  Int_t nbins = z->GetNbins();
  for (Int_t bin = 1; bin <= nbins; bin++) {
    z->SetRange(bin,bin);
    Int_t mirror = (bin-1)%7 + 1;
    Int_t bundle = ((bin-1)/7)%6 + 1;
    Int_t sector = ((bin-1)/(7*6)+1)*2;
    TH2 *h2 = (TH2 *)  hdXY->Project3D(Form("yx_%i",bin));
    Double_t e = h2->GetEntries();
    cout << Form("bin: %3i, entries = %10.5g, sector: %2i, bundle: %2i, mirror: %2i",bin,e,sector,bundle,mirror);
    if (e < 100.) {
      cout << endl;
      continue;
    }
    Double_t dX = h2->GetMean(1), ddX = h2->GetRMS(1), ux = dX/ddX;
    Double_t dY = h2->GetMean(2), ddY = h2->GetRMS(2), uy = dY/ddY;
    Double_t cor = h2->GetCorrelationFactor();
    Double_t chi2 = (ux*ux - 2*cor*ux*uy + uy*uy)/(1 - cor*cor);;
    cout << Form(", dX = %7.4f +/- %7.4f, dY = %7.4f +/- %7.4f, corr = %7.4f, chi2 = %10.2f",dX, ddX, dY, ddY, cor, chi2);
    cout << endl;
  }
}
//________________________________________________________________________________
void dXY() {
  TH3D *hdXY = (TH3D *) gDirectory->Get("hdXY");
  if (! hdXY) { 
    if (! laser) return;
    hdXY = new TH3D("hdXY","diff  ; dX;  dY; 7*(3*(fTracks.Laser.Sector/2-1)+fTracks.Laser.Bundle-1)+fTracks.Laser.Mirror-0.5  ",600,-0.6,0.6,600,-0.6,0.6,7*7*6,0.,7*7*6);
    laser->Draw("7*(3*(fTracks.Laser.Sector/2-1)+fTracks.Laser.Bundle-1)+fTracks.Laser.Mirror-0.5:fTracks.dU.mX2:fTracks.dU.mX1>>hdXY","fTracks.Laser.Sector>0","goff");
    hdXY = (TH3D *) gDirectory->Get("hdXY");
    if (! hdXY) return;
    PrintdXY(hdXY);
  }
}  
//________________________________________________________________________________
void dX() {
  if (! laser) return;
  laser->Draw("fTracks.dU.mX1:7*(3*(fTracks.Laser.Sector-2)+fTracks.Laser.Bundle-1)+fTracks.Laser.Mirror-0.5>>hdX(7*7*6,0,7*7*6,100,-0.5,0.5)","fTracks.Flag>1","colz");
  TH2D *dX = (TH2D *) gDirectory->Get("hdX");
  if (! dX) return;
  dX->FitSlicesY();
  TH1D *dX_1 = (TH1D *) gDirectory->Get("hdX_1");
  dX_1->SetMarkerStyle(20);
  dX_1->Draw("same");
  for (Int_t bin = 1; bin <= 7*7*6; bin++) {
    Int_t mirror = (bin-1)%7 + 1;
    Int_t bundle = ((bin-1)/7)%6 + 1;
    Int_t sector = ((bin-1)/(7*6)+1)*2;
    cout << "sector: " << sector << " bundle: " << bundle << " mirror: " << mirror  
	 << " dX: " << dX_1->GetBinContent(bin) << " +/- " 
	 << dX_1->GetBinError(bin) << "(cm)" << endl;
  }
}  
//________________________________________________________________________________
void dY() {
  if (! laser) return;
  laser->Draw("fTracks.dU.mX2:7*(3*(fTracks.Laser.Sector-2)+fTracks.Laser.Bundle-1)+fTracks.Laser.Mirror-0.5>>hdY(7*7*6,0,7*7*6,100,-0.5,0.5)","fTracks.Flag>1","colz");
  TH2D *dY = (TH2D *) gDirectory->Get("hdY");
  if (! dY) return;
  dY->FitSlicesY();
  TH1D *dY_1 = (TH1D *) gDirectory->Get("hdY_1");
  dY_1->SetMarkerStyle(20);
  dY_1->Draw("same");
  for (Int_t bin = 1; bin <= 7*7*6; bin++) {
    Int_t mirror = (bin-1)%7 + 1;
    Int_t bundle = ((bin-1)/7)%6 + 1;
    Int_t sector = ((bin-1)/(7*6)+1)*2;
    cout << "sector: " << 2*sector << " bundle: " << bundle << " mirror: " << mirror  
	 << " dY: " << dY_1->GetBinContent(bin) << " +/- " 
	 << dY_1->GetBinError(bin) << "(cm)" << endl;
  }
}  
//________________________________________________________________________________
void LAnalysis(TChain *tChain = 0){
  if (! tChain) return;
  laser = tChain;
  //  Slopes();
  //  FillHists(n1);
}
