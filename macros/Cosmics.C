#if 0
/* to Run: root.exe -q -b lMuDst.C Cosmics.C+
   

   to get momentum Resolution:
   CosmicT->Draw("(K.mPti+L.mPti)*TMath::Sqrt(2.)/TMath::Abs(K.mPti-L.mPti):-TMath::Log10(TMath::Abs(K.mPti-L.mPti)/2.)>>DpT(30,-1,2,100,-0.2,0.2)","noFitpK>30&&noFitpL>30&&chi2<200","colz");
   CosmicT->Draw("(K.mPti+L.mPti)*TMath::Sqrt(2.)/TMath::Abs(K.mPti-L.mPti):-TMath::Log10(TMath::Abs(K.mPti-L.mPti)/2.)>>DpT(60,-1,2,400,-0.2,0.2)","chi2<200","colz");
   TLegend *leg = new TLegend(0.4,0.4,0.7,0.7);
   TF1 *f = new TF1("f","TMath::Sqrt([0]*[0]/TMath::Power(10.,2*x)+[1]*[1]*TMath::Power(10.,2*x))",-1,2);
   Int_t color = 2; 
   CosmicT->Draw("(K.mPti+L.mPti)*TMath::Sqrt(2.)/TMath::Abs(K.mPti-L.mPti):-TMath::Log10(TMath::Abs(K.mPti-L.mPti)/2.)>>DpT(30,-1,2,100,-0.2,0.2)","noFitpK>30&&noFitpL>30&&chi2<200","colz");
   TH2 *DpT = (TH2 *) gDirectory->Get("DpT");
   DpT->FitSlicesY();
   TH1 *DpT_2 = (TH1 *) gDirectory->Get("DpT_2");
   DpT_2->SetTitle("Relative p_{T} resolution from cosmics muons");
   DpT_2->SetXTitle("Log_{10}(p_{TAv})");
   DpT_2->SetYTitle("#sigma (#Delta p_{T}/p_{TAv})/ #sqrt{2}");
   DpT_2->SetMarkerStyle(20);
   DpT_2->SetMarkerColor(color);
   DpT_2->SetLineColor(color);
   DpT_2->SetStats(0);
   f->SetParameters(0,1);
   f->SetLineColor(color);
   DpT_2->Fit(f);
   if (color == 1) leg->AddEntry(DpT_2,"without correction (No. fit points > 30)");
   if (color == 2) leg->AddEntry(DpT_2,"with correction (No. fit points > 30)");
   
   Pulls:
   TLegend *legP = new TLegend(0.4,0.4,0.7,0.7);
   Int_t color = 2; 
    CosmicT->Draw("(K.mPti+L.mPti)/TMath::Sqrt(K.mPtiPti+L.mPtiPti):-TMath::Log10(TMath::Abs(K.mPti-L.mPti)/2.)>>PullDpT(30,-1,2,100,-5,5)","noFitpK>30&&noFitpL>30&&chi2<200","colz");
   TH2 *PullDpT = (TH2 *) gDirectory->Get("PullDpT");
   PullDpT->FitSlicesY();
   TH1 *PullDpT_2 = (TH1 *) gDirectory->Get("PullDpT_2");
   PullDpT_2->SetTitle("#sigma for p_{T} pull from cosmics muons");
   PullDpT_2->SetXTitle("Log_{10}(p_{TAv})");
   PullDpT_2->SetYTitle("#sigma (#Delta p_{T}/#sigma p_{T})");
   PullDpT_2->SetMarkerStyle(20);
   PullDpT_2->SetMarkerColor(color);
   PullDpT_2->SetLineColor(color);
   PullDpT_2->SetStats(0);
   if (color == 1) legP->AddEntry(PullDpT_2,"without correction (No. fit points > 30)");
   if (color == 2) legP->AddEntry(PullDpT_2,"with correction (No. fit points > 30)");
   
   dEdx:
   CosmicT->Draw("zK:-TMath::Log10(TMath::Abs(K.mPti-L.mPti)/2.)>>dEdx(30,-1,2,100,-0.25,0.25)","noFitpK>15&&noFitpL>15&&zK>-1","colz")
   CosmicT->Draw("zK:TMath::Log10(bgK)>>dEdxbg(50,0,5.,100,-.5,0.5)","noFitpK>15&&noFitpL>15&&zK>-1&&chi2<200","colz")
   foreach f (`ls -1d ???/*.root`)
     mv ${f} ${f}.HOLD4
   end
   foreach d (`ls -1d ???`)
     cd ${d}
     if (! -r Cosmics.root) then
        echo "$PWD"
        ln -s ~/macros/.sl* .
        root.exe -q -b lMuDst.C 'Cosmics.C+("*\/*MuDst.root")' > & Cosmics.log &
     endif
     cd -
   end

*/
#endif
//#define __PrimaryVertices__
//#define __PrimaryTracks__
#if !defined(__CINT__) || defined(__MAKECINT__)
#include <assert.h>
#include "Riostream.h"
#include <stdio.h>
#include "TSystem.h"
#include "TMath.h"
#include "TH1.h"
#include "TH2.h"
#include "TH3.h"
#include "TProfile.h"
#include "TStyle.h"
#include "TF1.h"
#include "TTree.h"
#include "TChain.h"
#include "TFile.h"
#include "TNtuple.h"
#include "TCanvas.h"
#include "TMinuit.h"
#include "TSpectrum.h"
#include "TString.h"
#include "TLine.h"
#include "TText.h"
#include "TROOT.h"
#include "TList.h"
#include "TPolyMarker.h"
#include "StBichsel/Bichsel.h"
#include "TDirIter.h"
#include "TTree.h"
#include "TTreeIter.h"
#include "TRandom.h"
#include "TFractionFitter.h"
#include "TLegend.h"
#include "TRVector.h"
#include "TRSymMatrix.h"
#include "StDcaGeometry.h"
#include "TROOT.h"
#include "TSystem.h"
//#include "StDedxPidTraits.h"
#include "StEnumerations.h"
#include "TCernLib.h"
#else
class TSystem;
class TMath;
class TH1;
class TH2;
class TH3;
class TProfile;
class TStyle;
class TF1;
class TTree;
class TChain;
class TFile;
class TNtuple;
class TCanvas;
class TMinuit;
class TSpectrum;
class TString;
class TLine;
class TText;
class TROOT;
class TList;
class TPolyMarker;
class Bichsel;
class TDirIter;
class TTreeIter;
#endif
Bichsel *m_Bichsel = 0;
//#define __DEBUG__
static Int_t _debug = 0;
#ifdef __DEBUG__
#define PrP(A) {cout <<  (#A) << " = \t" << (A) << endl;}
#else
#define PrP(A) 
#endif 
#include "Names.h"
#if 0
#ifndef StTrackPidTraits_hh
#define StTrackPidTraits_hh
//________________________________________________________________________________
class StDedxPidTraits : public TObject {
public:
  StDedxPidTraits(StDetectorId det=kUnknownId, short meth=0,
		  unsigned short n=0, float dedx=0, float sig=0) : 
    mDetectorId(det), mNumberOfPoints(n), mMethod(meth), mDedx(dedx), mSigma(sig) {}
protected:
  Short_t  mDetectorId;
  UShort_t mNumberOfPoints;
  Short_t  mMethod;
  Float_t  mDedx;
  Float_t  mSigma;
  ClassDef(StDedxPidTraits,9)
    };
#endif
#else
#include "StTrackPidTraits.h"
#include "StDedxPidTraits.h"
#endif
//________________________________________________________________________________
class CosmicTracks : public TNamed {
public:
  CosmicTracks() : TNamed("","") {}
  Int_t kg;
  Int_t lg;
  Int_t noFitpK;
  Int_t noFitpL;
  Double_t chi2;
  Int_t   sectorK;
  Int_t   sectorL;
  Float_t xyzK[2][3]; // first[0], last[1] potin of K track
  Float_t xyzL[2][3]; // -"-                        L track
  StDcaGeometry K;
  StDcaGeometry L;
  StDcaGeometry T;
  StDedxPidTraits K70;
  StDedxPidTraits L70;
  StDedxPidTraits Kfit;
  StDedxPidTraits Lfit;
  Double_t pK, pL, bgK, bgL;
  Double_t bichK, bichL;
  Double_t zK, zL;
  Double_t zFitK, zFitL;
  virtual void        Print(Option_t *option="") const {
    cout << "K\t" << kg << " NF=" << noFitpK << "\t" << K; 
    cout << Form("\tF: %7.2f  %7.2f  %7.2f\t", xyzK[0][0], xyzK[0][1], xyzK[0][2]);
    cout << Form(  "L: %7.2f  %7.2f  %7.2f\t", xyzK[1][0], xyzK[1][1], xyzK[1][2]);
    cout << Form("S: %3i", sectorK) << endl;
    cout << "L\t" << lg << " NF=" << noFitpL << "\t" << L; 
    cout << Form("\tF: %7.2f  %7.2f  %7.2f\t", xyzL[0][0], xyzL[0][1], xyzL[0][2]);
    cout << Form(  "L: %7.2f  %7.2f  %7.2f\t", xyzL[1][0], xyzL[1][1], xyzL[1][2]);
    cout << Form("S: %3i", sectorL) << endl;
  }
  ClassDef(CosmicTracks,3)
};
ClassImp(StDedxPidTraits);
ClassImp(CosmicTracks);
//______________________________________________________________________
Int_t IndexH(const Char_t *name) {
  Int_t index = -1;
  TString Name(name);
  for (Int_t l = 0; l < KPidParticles; l++) {
    if (Name.BeginsWith(PidNames[l])) {index = l; break;}
  }
  return index;
}
//________________________________________________________________________________
Double_t difPsi(Double_t psi1, Double_t psi2) {
  Double_t psi = psi1 - psi2;
  if (psi >  TMath::PiOver2()) psi -= TMath::Pi();
  if (psi < -TMath::PiOver2()) psi += TMath::Pi(); 
  return psi;
}
//________________________________________________________________________________
Int_t sector(Float_t x, Float_t y, Float_t z) {
  Double_t phi = TMath::RadToDeg()*TMath::ATan2(y, x);
  if (phi <   0) phi += 360;
  if (phi > 360) phi -= 360;
  Int_t sec = ( ( 30 - TMath::Nint(phi/15.) )%24 ) / 2 ;
  if ( z < 0 ) sec = 24 - sec   ;  // Note that order of these two if statements is important
  else if ( sec == 0 ) sec = 12   ;
  return sec;
}
//________________________________________________________________________________
void PrintDCA(TRVector Par, TRSymMatrix Cov) {
  const Double_t *par = Par.GetArray();
  const Double_t *errMx = Cov.GetArray();
  Double_t pt = -1./par[3];
  cout << Form("Dca: imp %7.2f +/-%7.2f, Z:%7.2f +/-%7.2f, psi:%7.2f +/-%7.2f, pT/q:%7.2f +/-%6.1f%%, TanL:%8.3f +/-%8.3f",
	       par[0],    (errMx[0] >= 0)  ? TMath::Sqrt(errMx[0]) : -13,
	       par[1],         (errMx[2] >= 0)  ? TMath::Sqrt(errMx[2]) : -13,
	       par[2],       (errMx[5] >= 0)  ? TMath::Sqrt(errMx[5]) : -13,
	       pt,    100*TMath::Sqrt(errMx[9])*TMath::Abs(pt),
	       par[4],    (errMx[14] >= 0) ? TMath::Sqrt(errMx[14]): -13) << endl;
}
//________________________________________________________________________________
void Cosmics(TString files = "",
	     const Char_t *Out = "Cosmics.root"
	    ){
  //  static const Double_t sigmaB[2] = {6.26273e-01, -5.80915e-01}; // Global Tracks, wrt Bichsel
  if (files == "") return;
  files.ReplaceAll("\\","");
  if (!m_Bichsel) {
    gSystem->Load("StBichsel"); 
    gSystem->Load("StarClassLibrary");  
    m_Bichsel = Bichsel::Instance();
  }
  TDirIter Dir(files.Data());
  Char_t *file = 0;
  Int_t NFiles = 0;
  TTreeIter iter;
  while ((file = (Char_t *) Dir.NextFile())) {iter.AddFile(file); NFiles++;}
  cout << files << "\twith " << NFiles << " files" << endl; 
  if (! NFiles) return;
  // init of user variables
#define __GlobalTracks__
#define __FirstLastPoint__
#define __CovGlobTrack__
#define __FirstLastPoint__
#define __dEdx__
#define __RunInfo__
#define __EventInfo__
  //#include "MuDstIter.h"
#include "MuDstIterMerged.h"
  // Book TTree
  TFile *fOut = new TFile(Out,"recreate");
  TTree *ftree = new TTree("CosmicT","Cosmic tree");
  ftree->SetAutoSave(1000000000);  // autosave when 1 Gbyte written
  Int_t bufsize = 64000;
  Int_t split = 99;
  if (split)  bufsize /= 4;
  CosmicTracks tracks;
  CosmicTracks *ftrack = &tracks;
  TTree::SetBranchStyle(1); //new style by default
  ftree->Branch("CosmicTracksB", "CosmicTracks", &ftrack, bufsize, split);
   //         Now iterations
  StDcaGeometry TK, TL, T, tk, tl, t;
  Int_t netries = 0;
  while (iter.Next()) {
    /*
        Dca: imp   16.44 +/-   0.11,Z   45.00 +/-   0.09,psi    0.76 +/-   0.00, q/pT   -1.63 +/-   1.7%,TanL    0.373 +/-   0.001 L  139.912   0.000 NF   43 chi2    0.939 NP   45
        Dca: imp  -16.55 +/-   0.11,Z   45.07 +/-   0.09,psi   -2.38 +/-   0.00, q/pT    1.61 +/-   1.5%,TanL   -0.369 +/-   0.001 L  138.818   0.000 NF   45 chi2    0.986 NP   45
    */
    if (NoGlobalTracks < 2) continue;
    Int_t Npairs = 0;
    Int_t k = -1; 
    Int_t l = -1;
    for (Int_t kg = 0; kg < NoGlobalTracks; kg++) {
      Double_t Chi2Old = 1.e4;
      TRVector ParK(5);
      TRSymMatrix CovK(5);
      TRVector ParL(5);
      TRSymMatrix CovL(5);
      k = -1; 
      l = -1;
      for (Int_t lg = 0; lg < NoGlobalTracks; lg++) {
	if (kg == lg) continue;
	if (GlobalTracks_mNHitsFitTpc[kg] < 15) continue;
	if (GlobalTracks_mNHitsFitTpc[lg] < 15) continue;
	if (GlobalTracks_mLastPoint_mX2[kg] < GlobalTracks_mLastPoint_mX2[lg]) continue; // kg Up track, lg Low track 
	Int_t kgc = GlobalTracks_mIndex2Cov[kg];
	if (kgc < 0 || kgc > NoCovGlobTrack) continue;
	Double_t parK[6] = {CovGlobTrack_mImp[kgc], CovGlobTrack_mZ[kgc], CovGlobTrack_mPsi[kgc], CovGlobTrack_mPti[kgc], CovGlobTrack_mTan[kgc], 0};
	Double_t covK[15] = {
	CovGlobTrack_mImpImp[kgc], 
	CovGlobTrack_mZImp[kgc]  , CovGlobTrack_mZZ[kgc]    ,
	CovGlobTrack_mPsiImp[kgc], CovGlobTrack_mPsiZ[kgc]  , CovGlobTrack_mPsiPsi[kgc], 
	CovGlobTrack_mPtiImp[kgc], CovGlobTrack_mPtiZ[kgc]  , CovGlobTrack_mPtiPsi[kgc], CovGlobTrack_mPtiPti[kgc], 
	CovGlobTrack_mTanImp[kgc], CovGlobTrack_mTanZ[kgc]  , CovGlobTrack_mTanPsi[kgc], CovGlobTrack_mTanPti[kgc], CovGlobTrack_mTanTan[kgc]};
	ParK = TRVector(5,parK);
	CovK = TRSymMatrix(5,covK);
	tk.set(parK,covK); PrP(tk);
	Int_t lgc = GlobalTracks_mIndex2Cov[lg];
	if (lgc < 0 || lgc > NoCovGlobTrack) continue;
	Double_t parL[6] = {CovGlobTrack_mImp[lgc], -CovGlobTrack_mZ[lgc], TMath::Pi()-CovGlobTrack_mPsi[lgc], CovGlobTrack_mPti[lgc], CovGlobTrack_mTan[lgc], 0};
	if (parL[2] >  TMath::PiOver2()) parL[2] -= TMath::Pi();
	if (parL[2] < -TMath::PiOver2()) parL[2] += TMath::Pi(); 
	Double_t covL[15] = {
	  CovGlobTrack_mImpImp[lgc], 
	  CovGlobTrack_mZImp[lgc]  , CovGlobTrack_mZZ[lgc]    ,
	  CovGlobTrack_mPsiImp[lgc], CovGlobTrack_mPsiZ[lgc]  , CovGlobTrack_mPsiPsi[lgc], 
	  CovGlobTrack_mPtiImp[lgc], CovGlobTrack_mPtiZ[lgc]  , CovGlobTrack_mPtiPsi[lgc], CovGlobTrack_mPtiPti[lgc], 
	  CovGlobTrack_mTanImp[lgc], CovGlobTrack_mTanZ[lgc]  , CovGlobTrack_mTanPsi[lgc], CovGlobTrack_mTanPti[lgc], CovGlobTrack_mTanTan[lgc]};
	tl.set(parL,covL); PrP(tl);
	ParL = TRVector(5,parL);
	CovL = TRSymMatrix(5,covL);
	TRVector Par(ParK);
	Par += ParL;
	if (Par[2] >  TMath::PiOver2()) Par[2] -= TMath::Pi();
	if (Par[2] < -TMath::PiOver2()) Par[2] += TMath::Pi(); 
	TRVector ParS(Par);
	ParS[3] = 0; // ignore difference in q/pT
	TRSymMatrix Cov(CovL);
	Cov += CovK;
	t.set(Par.GetArray(), Cov.GetArray()); PrP(t);
	TRSymMatrix G(Cov,TRArray::kInverted);
        Double_t chi2 = G.Product(ParS,TRArray::kATxSxA);	PrP(chi2);
	if (chi2 < Chi2Old) {
	  Chi2Old = chi2;
	  k = kg;
	  l = lg;
	  TK = tk;
	  TL = tl;
	  T  = t;
	}
      }
      if (k < 0 || l < 0  ||  Chi2Old >= 1e4) continue;
      PrP(TK);
      PrP(TL);
      PrP(T);
      Int_t lg = l;
      tracks.noFitpK = GlobalTracks_mNHits[kg];
      tracks.noFitpL = GlobalTracks_mNHits[lg];
      tracks.chi2 = Chi2Old;
      tracks.kg = kg;
      tracks.lg = lg;
      tracks.K = TK;
      tracks.L = TL;
      tracks.T = T;
      // Add sector
      tracks.sectorK = sector(GlobalTracks_mLastPoint_mX1[kg], GlobalTracks_mLastPoint_mX2[kg], GlobalTracks_mLastPoint_mX3[kg]);
      tracks.sectorL = sector(GlobalTracks_mLastPoint_mX1[lg], GlobalTracks_mLastPoint_mX2[lg], GlobalTracks_mLastPoint_mX3[lg]);
      if (tracks.sectorK != sector(GlobalTracks_mFirstPoint_mX1[kg], GlobalTracks_mFirstPoint_mX2[kg], GlobalTracks_mFirstPoint_mX3[kg])) tracks.sectorK = - tracks.sectorK;
      if (tracks.sectorL != sector(GlobalTracks_mFirstPoint_mX1[lg], GlobalTracks_mFirstPoint_mX2[lg], GlobalTracks_mFirstPoint_mX3[lg])) tracks.sectorL = - tracks.sectorL;
      tracks.xyzK[0][0] = GlobalTracks_mFirstPoint_mX1[kg];
      tracks.xyzK[0][1] = GlobalTracks_mFirstPoint_mX2[kg];
      tracks.xyzK[0][2] = GlobalTracks_mFirstPoint_mX3[kg];
      tracks.xyzK[1][0] = GlobalTracks_mLastPoint_mX1[kg];
      tracks.xyzK[1][1] = GlobalTracks_mLastPoint_mX2[kg];
      tracks.xyzK[1][2] = GlobalTracks_mLastPoint_mX3[kg];
      //
      tracks.xyzL[0][0] = GlobalTracks_mFirstPoint_mX1[lg];
      tracks.xyzL[0][1] = GlobalTracks_mFirstPoint_mX2[lg];
      tracks.xyzL[0][2] = GlobalTracks_mFirstPoint_mX3[lg];
      tracks.xyzL[1][0] = GlobalTracks_mLastPoint_mX1[lg];
      tracks.xyzL[1][1] = GlobalTracks_mLastPoint_mX2[lg];
      tracks.xyzL[1][2] = GlobalTracks_mLastPoint_mX3[lg];
      Npairs++;
      if (_debug || Npairs%100000 == 1 || tracks.sectorK == tracks.sectorL) {
	cout << "Run " << MuEvent_mRunInfo_mRunId[0] << " Event " << MuEvent_mEventInfo_mId[0] << "====================" << endl;
	tracks.Print();
	cout << "T\t" << Npairs/100000 << "0k\t" << T << "\tchi2 = " << tracks.chi2 << endl;
      }
      tracks.K70 = StDedxPidTraits(kTpcId, kTruncatedMeanId, 
				   100*((Int_t) GlobalTracks_mProbPidTraits_mdEdxTrackLength[kg])+GlobalTracks_mNHitsDedx[kg],
				   GlobalTracks_mProbPidTraits_mdEdxTruncated[kg],GlobalTracks_mProbPidTraits_mdEdxErrorTruncated[kg]);
      tracks.L70 = StDedxPidTraits(kTpcId, kTruncatedMeanId, 
				   100*((Int_t) GlobalTracks_mProbPidTraits_mdEdxTrackLength[lg])+GlobalTracks_mNHitsDedx[lg],
				   GlobalTracks_mProbPidTraits_mdEdxTruncated[lg],GlobalTracks_mProbPidTraits_mdEdxErrorTruncated[lg]);
      tracks.Kfit = StDedxPidTraits(kTpcId, kLikelihoodFitIdentifier, 
				    100*((Int_t) GlobalTracks_mProbPidTraits_mdEdxTrackLength[kg])+GlobalTracks_mNHitsDedx[kg],
				    GlobalTracks_mProbPidTraits_mdEdxFit[kg],GlobalTracks_mProbPidTraits_mdEdxErrorFit[kg]);
      tracks.Lfit = StDedxPidTraits(kTpcId, kLikelihoodFitIdentifier, 
				    100*((Int_t) GlobalTracks_mProbPidTraits_mdEdxTrackLength[lg])+GlobalTracks_mNHitsDedx[lg],
				    GlobalTracks_mProbPidTraits_mdEdxFit[lg],GlobalTracks_mProbPidTraits_mdEdxErrorFit[lg]);
      Double_t pT = tracks.K.pt();
      tracks.pK  = pT*TMath::Sqrt(1. + tracks.K.tanDip()*tracks.K.tanDip());
      tracks.bgK = tracks.pK/0.1056584; // for muon
      tracks.bichK = 1e-6*m_Bichsel->GetI70M(TMath::Log10(tracks.bgK),1.);
      tracks.zK = -999;
      if (tracks.K70.mean() > 0) tracks.zK = TMath::Log(tracks.K70.mean()/tracks.bichK);
      pT = tracks.L.pt();
      tracks.pL  = pT*TMath::Sqrt(1. + tracks.L.tanDip()*tracks.L.tanDip());
      tracks.bgL = tracks.pL/0.1056584; // for muon
      tracks.bichL = 1e-6*m_Bichsel->GetI70M(TMath::Log10(tracks.bgL),1.);
      tracks.zL = -999;
      if (tracks.L70.mean() > 0) tracks.zL = TMath::Log(tracks.L70.mean()/tracks.bichL);
      tracks.zFitK = -999;
      if (tracks.Kfit.mean() > 0) tracks.zFitK = TMath::Log(tracks.Kfit.mean()/tracks.bichK);
      tracks.zFitL = -999;
      if (tracks.Lfit.mean() > 0) tracks.zFitL = TMath::Log(tracks.Lfit.mean()/tracks.bichL);
      ftree->Fill();
      netries++;
    }
  }
  if (fOut) fOut->Write();
}
//________________________________________________________________________________
void Plot(Int_t nevents = 1e9, const Char_t *Out = "CosmicPlots.root") {
  TSeqCollection *files = gROOT->GetListOfFiles();
  struct Plot_t {
    const Char_t *Name;
    const Char_t *Title;
    Int_t nx;
    Double_t xmin, xmax;
    Int_t ny;
    Double_t ymin, ymax;
  };
  struct VarPr_t {
    Double_t DeltapTI;
    Double_t pullDeltapTI;
    Double_t DeltapTR;
    Double_t pullDeltapTR;
    Double_t DeltaDCAxy;
    Double_t pullDeltaDCAxy;
    Double_t DeltaDCAz;
    Double_t pullDeltaDCAz;
    Double_t DeltaTan;
    Double_t pullDeltaTan;
    Double_t DeltaPsi;
    Double_t pullDeltaPsi;
  };
  VarPr_t V;
  enum {kTotal=12, kAll=14, NC = 4, NDCA = 3, kCharge = NC*NDCA};
  Double_t pL10min = -1.5;
  Double_t pL10max =  2.0;
  Int_t Np = 70;
  const Plot_t plot[kAll] = {// Name, Title,                                                                        nx,     xmin,    xmax,  ny, ymin, ymax         
    {"DelpTI"  ,   "#Delta 1/p_{T} from cosmics muons             ; Log_{10}(p_{TAv}) ; #Delta 1/p_{T}",            Np,  pL10min, pL10max, 500, -0.5, 0.5},
    {"PullpTI" ,   "pull of #Delta 1/p_{T} from cosmics muons     ; Log_{10}(p_{TAv}) ; pull (#Delta 1/p_{T})",     Np,  pL10min, pL10max, 500, -5.0, 5.0},
    {"DelpTR"  ,   "#Delta p_{T}/p_{T} from cosmics muons         ; Log_{10}(p_{TAv}) ; #Delta p_{T}/p_{T}",        Np,  pL10min, pL10max, 500, -0.5, 0.5},
    {"PullpTR" ,   "pull of #Delta p_{T}/p_{T} from cosmics muons ; Log_{10}(p_{TAv}) ; pull (#Delta p_{T}/p_{T})", Np,  pL10min, pL10max, 500, -5.0, 5.0},
    {"DelImp"  ,   "#Delta DCA_{xy} from cosmics muons            ; Log_{10}(p_{TAv}) ; DCA_{xy}",                  Np,  pL10min, pL10max, 500, -1.0, 1.0},	   
    {"PullImp" ,   "pull of #Delta DCA_{xy} from cosmics muons    ; Log_{10}(p_{TAv}) ; pull DCA_{xy} ",            Np,  pL10min, pL10max, 500, -5.0, 5.0},	   
    {"DelZ"    ,   "#Delta DCA_{z} from cosmics muons             ; Log_{10}(p_{TAv}) ; DCA_{z}",                   Np,  pL10min, pL10max, 500, -2.5, 2.5},   
    {"PullZ"   ,   "pull of #Delta DCA_{z} from cosmics muons     ; Log_{10}(p_{TAv}) ; pull DCA_{z} ",             Np,  pL10min, pL10max, 500, -5.0, 5.0},	   
    {"DelTan"  ,   "#Delta #lambda from cosmics muons             ; Log_{10}(p_{TAv}) ; #lambda",                   Np,  pL10min, pL10max, 500,-0.02, 0.02},   
    {"PullTan" ,   "pull of #Delta Tan(#lambda) from cosmics muons; Log_{10}(p_{TAv}) ; pull Tan(#lambda)",	    Np,  pL10min, pL10max, 500, -5.0, 5.0}, 
    {"DelPsi"  ,   "#Delta #psi from cosmics muons                ; Log_{10}(p_{TAv}) ; #psi",                      Np,  pL10min, pL10max, 500, -0.1, 0.1},	   
    {"PullPsi" ,   "pull of #Delta #psi from cosmics muons        ; Log_{10}(p_{TAv}) ; pull #psi ",                Np,  pL10min, pL10max, 500, -5.0, 5.0},	   
    {"sKsL"    ,   "sector L versus sector K                      ; secotr K ; Sector L",                           49,    -24.5,    24.5,  49,-24.5,24.5},      
    {"fKfL"    ,   "no. fit points L versus no. fit point K       ; no.fit point K ; no. fit points  L",           100,     -0.5,    99.5, 100, -0.5,99.5}  
  };
  const Char_t *nCharge[NC] = {"All","Pos","Neg","Loop"};
  const Char_t *tCharge[NC] = {"","Positive","Negative","Looppers"};
  const Char_t *NameDCA[NDCA] = {"","C","P"};
  const Char_t *tDCA[NDCA] = {"","DCA_{xy}  <= 50 cm", "DCA_{xy}  >  50 cm"};
  //                d   c
  TH2D *H2[kAll][NDCA][NC] = {0};
  //  Char_t *file = gSystem->Which(".",Out,kReadPermission);
  Char_t *file = 0;
  TFile *fOut = 0;
  Bool_t RePlotOnly = kTRUE;
  if (file) {
    fOut = new TFile(file);
    delete [] file;
    for (Int_t k = 0; k < kAll; k++) {
      for (Int_t d = 0; d < NDCA; d++) { 
	for (Int_t c = 0; c < NC; c++) {
	  TString Name(Form("%s%s%s",plot[k].Name,nCharge[c],NameDCA[d]));
	  H2[k][d][c] = (TH2D *) fOut->Get(Name);
	}
      }
    }
  } else { 
    RePlotOnly = kFALSE;
    fOut = new TFile(Out,"recreate");
    for (Int_t k = 0; k < kAll; k++) {
      for (Int_t d = 0; d < NDCA; d++) { 
	for (Int_t c = 0; c < NC; c++) {
	  TString Name(Form("%s%s%s",plot[k].Name,nCharge[c],NameDCA[d]));
	  TString Title(Form("%s %s %s",tCharge[c],plot[k].Title,tDCA[d]));
	  H2[k][d][c] = new TH2D(Name,Title,plot[k].nx,plot[k].xmin,plot[k].xmax,plot[k].ny,plot[k].ymin,plot[k].ymax);
	}
      }
    }
  }
  TF1 *dpTOverpT = new TF1("dpTOverpT","TMath::Sqrt(2*([0]*[0]+[1]*[1]*TMath::Power(10.,2*x)))",pL10min,pL10max);
  dpTOverpT->SetParameters(1e-2,1e-2);
  dpTOverpT->SetLineColor(3);
  TF1 *dpTI = new TF1("dpTI","TMath::Sqrt(2*([0]*[0]+[1]*[1]*TMath::Power(10.,2*x)))*TMath::Power(10.,-x)",pL10min,pL10max);
  dpTI->SetParameters(1e-2,1e-2);
  dpTI->SetLineColor(3);
  CosmicTracks tracks;
  CosmicTracks *ftrack = &tracks;
  TFile *f = 0;
  TH1F *frame = 0;
  if (! RePlotOnly) {
    Int_t nn = files->GetSize();
    if (!nn) return;
    TIter next(files);
    Int_t NF = -1;
    while ( (f = (TFile *) next()) ) {
      f->cd();
      cout << "File: " << f->GetName() << endl;
      NF++;
      TTree *tree = (TTree *) f->Get("CosmicT");
      if (! tree) continue;
      TBranch *branch = tree->GetBranch("CosmicTracksB");
      enum kIntex {kImp = 0, kZ, kPsi, kPti, kTan,
		   kImpImp = 0, 
		   kZImp, kZZ,
		   kPsiImp, kPsiZ, kPsiPsi,
		   kPtiImp, kPtiZ, kPtiPsi, kPtiPti,
		   kTanImp, kTanZ, kTanPsi, kTanPti, kTanTan};
      if (! branch) continue;
      branch->SetAddress(&ftrack);
      Int_t nentries = (Int_t)tree->GetEntries();
      if (nentries < nevents) nevents = nentries;
      for (Int_t ev = 0; ev < nevents; ev++) {
	tree->LoadTree(ev);  //this call is required when using the cache
	tree->GetEntry(ev);   
	if (ev > 0 && ! (ev%100000)) cout << "Read event " << ev << endl;
	H2[kTotal+1][0][0]->Fill(tracks.noFitpK, tracks.noFitpL);
	if (tracks.noFitpK < 30 || tracks.noFitpL < 30) continue;
	StDcaGeometry &K = *&tracks.K;
	StDcaGeometry &L = *&tracks.L;
	StDcaGeometry &T = *&tracks.T;
	Double_t pTIAV    = TMath::Abs(K.params()[kPti] - L.params()[kPti])/2;
	Double_t pTAV     = 1./pTIAV;
	Double_t pTAVL10 = 1.95;
	Double_t sigmapTI = TMath::Sqrt(T.errMatrix()[kPtiPti]); 
	if (sigmapTI < 1e-7) continue;
	if (pTAV < 1e-7) continue;
	Int_t sectorK = tracks.sectorK;
	Int_t sectorL = tracks.sectorL;
	// track K is coming from top 
	Int_t c = (-K.charge() + 3)/2; // K is comint from Top (charge => - charge); charge "+" = 1, "-" => 2, 0 for All
	if (TMath::Abs(sectorK) == TMath::Abs(sectorL)) c = 3; // Loopers are separated
	Int_t d = 1;
	if (TMath::Abs(K.params()[kImp] - L.params()[kImp])/2 > 50.0) d = 2;
	pTAVL10 = TMath::Log10(pTAV);
	V.DeltapTI = T.params()[kPti];  // delta (1/pT) / (1/pT);
	V.pullDeltapTI = V.DeltapTI/sigmapTI;
	V.DeltapTR = V.DeltapTI*pTAV;
	Double_t sigmapTR = pTAV*sigmapTI;
	V.pullDeltapTR = V.DeltapTR/sigmapTR;
	V.DeltaDCAxy = T.params()[kImp];
	Double_t sigmaDCAxy = TMath::Sqrt(T.errMatrix()[kImpImp]);
	V.pullDeltaDCAxy = V.DeltaDCAxy/sigmaDCAxy;
	
	V.DeltaDCAz = T.params()[kZ];
	Double_t sigmaDCAz = TMath::Sqrt(T.errMatrix()[kZZ]);
	V.pullDeltaDCAz = V.DeltaDCAz/sigmaDCAz;
	
	
	V.DeltaTan = T.params()[kTan];
	Double_t sigmaTan = TMath::Sqrt(T.errMatrix()[kTanTan]);
	V.pullDeltaTan = V.DeltaTan/sigmaTan;
	V.DeltaPsi = T.params()[kPsi];
	Double_t sigmaPsi = TMath::Sqrt(T.errMatrix()[kPsiPsi]);
	V.pullDeltaPsi = V.DeltaPsi/sigmaPsi;
	
	Double_t *Y = &V.DeltapTI;
	for (Int_t k = 0; k < kTotal; k++) {
	  H2[k][0][0]->Fill(pTAVL10, Y[k]);
	  H2[k][0][c]->Fill(pTAVL10, Y[k]);
	  H2[k][d][0]->Fill(pTAVL10, Y[k]);
	  H2[k][d][c]->Fill(pTAVL10, Y[k]);
	}
	H2[kTotal][0][0]->Fill(sectorK, sectorL);
	H2[kTotal][0][c]->Fill(sectorK, sectorL);
	H2[kTotal][d][0]->Fill(sectorK, sectorL);
	H2[kTotal][d][c]->Fill(sectorK, sectorL);

	H2[kTotal+1][0][c]->Fill(tracks.noFitpK, tracks.noFitpL);
	H2[kTotal+1][d][0]->Fill(tracks.noFitpK, tracks.noFitpL);
	H2[kTotal+1][d][c]->Fill(tracks.noFitpK, tracks.noFitpL);
      }
    }
  }
  
  TString Field;
  TString pwd(gSystem->WorkingDirectory());
  if (pwd.Contains("FF")) Field = "FF";
  if (pwd.Contains("RF")) Field = "RF";
  Int_t nC = 3; // NC;
  Int_t nDCA = 1; // NDCA;
  Int_t Npads = nC*nDCA*kAll;
  TLegend **leg = new TLegend*[Npads];  memset(leg,  0, Npads*sizeof(TLegend *)); 
  TLegend **leg2 = new TLegend*[Npads]; memset(leg2, 0, Npads*sizeof(TLegend *)); 
  Int_t color = 0;
  TCanvas *c1 = new TCanvas("c1","c1",10,10,200*nC*nDCA,100*kAll);
  c1->Divide(nC*nDCA,kAll);
  color++;
  if (color == 2) color = 4;
  for (Int_t k = 0; k < kAll; k++) {
    for (Int_t d = 0; d < nDCA; d++) {
      for (Int_t c = 0; c < nC; c++) {
	Int_t pad = nC*(nDCA*k + d) + c + 1;
	c1->cd(pad)->SetLogz(1);
	TH2D *h2 = H2[k][d][c];
	if (! h2) continue;
	h2->Draw("colz");
	if (k >= kTotal) continue;
	h2->FitSlicesY();
	TH1D *h_1 = (TH1D *) gDirectory->Get(Form("%s_1",H2[k][d][c]->GetName()));
	TH1D *h_2 = (TH1D *) gDirectory->Get(Form("%s_2",H2[k][d][c]->GetName()));
	Double_t mu = 0, sigma = 0;
	if (h_1 && h_2) {
	  h_1->SetMarkerStyle(20); h_1->SetMarkerColor(color);
	  h_1->Fit("pol0","er","same",pL10min, pL10max);
	  TF1 *pol0 = (TF1 *) h_1->GetListOfFunctions()->FindObject("pol0");
	  if (pol0) {
	    mu = pol0->GetParameter(0);
	    h_1->Draw("same");
	  }
	  h_2->SetMarkerStyle(21); h_2->SetMarkerColor(color);
	  h_2->Fit("pol0","er","same",pL10min, pL10max);
	  pol0 = (TF1 *) h_2->GetListOfFunctions()->FindObject("pol0");
	  if (pol0) {
	    sigma = pol0->GetParameter(0);
	  }
	  if (TMath::Abs(mu) > 1e-7 && TMath::Abs(sigma) > 1e-7) {
	    if (! leg[pad-1]) {
	      leg[pad-1] = new TLegend(0.3,0.8,0.7,0.9);
	      leg[pad-1]->SetFillColor(gStyle->GetLegendFillColor());
	      leg[pad-1]->AddEntry(h_1,Form("%s #mu = %6.3f, #sigma =  %6.3f",Field.Data(),mu,sigma));
	      leg[pad-1]->Draw();
	    }
	  }
	  if (k == 0 || k == 2) {
	    leg2[pad-1] = new TLegend(0.12,0.12,0.88,0.22);
	    leg2[pad-1]->SetFillColor(gStyle->GetLegendFillColor());
	    if (k == 2) { // DelpTR
	      dpTOverpT->SetParameters(1e-2,1e-2);
	      h_2->Fit(dpTOverpT,"e+");
	      leg2[pad-1]->AddEntry(dpTOverpT,Form("#sigma(#DeltapT)) = %5.2f%% #oplus %5.2f%% #times pT => #sigma(#DeltapT/pT) = %5.2f%%(@1GeV/c)",
						   Field.Data(),100*dpTOverpT->GetParameter(0),100*dpTOverpT->GetParameter(1), 100*dpTOverpT->Eval(0.)/TMath::Sqrt(2.)));
	    } else if (k == 0) { // DelpTI
	      dpTI->SetParameters(1e-2,1e-2);
	      h_2->Fit(dpTI,"e+");
	      leg2[pad-1]->AddEntry(dpTI,Form("#sigma(#Delta(1/pT)) = (%5.2f%% #oplus %5.2f%% #times pT)/pT => #sigma(#DeltapT/pT) = %5.2f%%(@1GeV/c)",
					      Field.Data(),100*dpTI->GetParameter(0),100*dpTI->GetParameter(1),100*dpTI->Eval(0.)/TMath::Sqrt(2.)));
	    }
	    leg2[pad-1]->Draw();
	  }
	}
	c1->Update();
      }
    }
  }
}
//________________________________________________________________________________
/*
  Int_t NF = 0;
  TSeqCollection *files = gROOT->GetListOfFiles();
  TIter next(files);
  TFile *f = 0;
  
*/
  
