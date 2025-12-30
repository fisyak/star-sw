//  root.exe 'Chain.C+("st*26080003*.laser.root","laser")' 'lana.C+(tChain)'
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
#include "TCahin.h"
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
  //  laser->Draw("fTracks.dPhi:fTracks.mSector>>dPhi(12,1,25,100,-.15,0.15)","fTracks.Flag>1","colz");
  //  laser->Draw("TMath::ATan2(fTracks.Laser.dirU.mX2, fTracks.Laser.dirU.mX2)-TMath::ATan2(fTracks.dirPU.mX2,fTracks.dirPU.mX1):fTracks.mSector>>dPhi(12,1,25,100,-.15,0.15)","fTracks.Flag>1","colz");
  laser->Draw(
	      "atan(fTracks.Laser.dirU.mX2/fTracks.Laser.dirU.mX1)-atan(fTracks.dirPU.mX2/fTracks.dirPU.mX1):fTracks.mSector>>dPhi(12,1,25,100,-.15,0.15)",
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
  laser->Draw("atan(fTracks.Laser.dirU.mX3)-atan(fTracks.dirPU.mX3):fTracks.mSector>>dTheta(12,1,25,100,-.15,0.15)",
	      "fTracks.Flag>1&&abs(fTracks.dU.mX1)<1&&abs(fTracks.dU.mX2)<1","colz");
  TH2D *dTheta = (TH2D *) gDirectory->Get("dTheta");
  if (! dTheta) return;
  dTheta->FitSlicesY();
  TH1D *dTheta_1 = (TH1D *) gDirectory->Get("dTheta_1");
  dTheta_1->SetMarkerStyle(20);
  dTheta_1->Draw("same");
  for (Int_t bin = 1; bin <= 12; bin++) {
    cout << "sector: " << 2*bin << " dTheta: " << 1e3*dTheta_1->GetBinContent(bin) << " +/- " 
	 << 1e3*dTheta_1->GetBinError(bin) << "(mrad)" << endl;
  }
}  
//________________________________________________________________________________
void dX() {
  if (! laser) return;
  laser->Draw("fTracks.XyzPU.mX1-fTracks.Laser.XyzU.mX1:7*(3*(fTracks.Laser.Sector-2)+fTracks.Laser.Bundle-1)+fTracks.Laser.Mirror-0.5>>dX(504,0,504,100,-.2,0.2)","fTracks.Flag>1","colz");
  TH2D *dX = (TH2D *) gDirectory->Get("dX");
  if (! dX) return;
  dX->FitSlicesY();
  TH1D *dX_1 = (TH1D *) gDirectory->Get("dX_1");
  dX_1->SetMarkerStyle(20);
  dX_1->Draw("same");
  for (Int_t bin = 1; bin <= 504; bin++) {
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
  laser->Draw("fTracks.XyzPU.mX2-fTracks.Laser.XyzU.mX2:7*(3*(fTracks.Laser.Sector-2)+fTracks.Laser.Bundle-1)+fTracks.Laser.Mirror-0.5>>dY(504,0,504,100,-.2,0.2)","fTracks.Flag>1","colz");
  TH2D *dY = (TH2D *) gDirectory->Get("dY");
  if (! dY) return;
  dY->FitSlicesY();
  TH1D *dY_1 = (TH1D *) gDirectory->Get("dY_1");
  dY_1->SetMarkerStyle(20);
  dY_1->Draw("same");
  for (Int_t bin = 1; bin <= 504; bin++) {
    Int_t mirror = (bin-1)%7 + 1;
    Int_t bundle = ((bin-1)/7)%6 + 1;
    Int_t sector = ((bin-1)/(7*6)+1)*2;
    cout << "sector: " << sector << " bundle: " << bundle << " mirror: " << mirror  
	 << " dY: " << dY_1->GetBinContent(bin) << " +/- " 
	 << dY_1->GetBinError(bin) << "(cm)" << endl;
  }
}  
//________________________________________________________________________________
void Laser(TChain *tChain = 0){
  if (! tchain) return;
  laser = tChain;
  //  Slopes();
  //  FillHists(n1);
}
