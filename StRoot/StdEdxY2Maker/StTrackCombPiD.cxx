#include "Riostream.h"
#ifdef __TFG__VERSION__
#include "StPicoEvent/StPicoDst.h"
#include "StPicoEvent/StPicoEvent.h"
#endif /*  __TFG__VERSION__ */
#include "StTrackCombPiD.h"
#include "StBichsel/Bichsel.h"
#include "StBichsel/StdEdxModel.h"
#include "StBichsel/StdEdxPull.h"
#include "StVertex.h"
#include "StGlobalTrack.h"
#include "StTrackGeometry.h"
#include "StThreeVector.hh"
#include "TMath.h"
#include "TVector3.h"
#include "TCallf77.h"
#include "StarRoot/TRMatrix.h"
#include "StarRoot/TRSymMatrix.h"
#include "StDetectorDbMaker/St_tofSimResParamsC.h"
#include "StDetectorDbMaker/St_pidCorrectionC.h"
#ifndef WIN32
#define btofDeriv btofderiv_
#else
#define btofDeriv BTOFDERIV
#endif
extern "C" {
  void type_of_call btofDeriv(const Float_t *dcaPars, Double_t &tof, Float_t *xyzV, Float_t *xyzH, Double_t &betaV, Double_t &M2q2, Double_t *Deriv);
};
KFVertex StTrackCombPiD::fgBestVx;
Double_t StTrackCombPiD::fgSigmaCut = 3.0;
Particle_t StTrackCombPiD::fgParticles[34] = {
  {         11,  "e-",   0.51099907e-3, -1,  kPidElectron},  
  {        -11,  "e+",   0.51099907e-3,  1,  kPidElectron},  
  {         13,  "mu-",  0.1056584,     -1,  kPidMuon},        
  { 	   -13,  "mu+",  0.1056584,      1,  kPidMuon},        
  {        211,  "pi+",  0.13956995,     1,  kPidPion},        
  {       -211,  "pi-",  0.13956995,    -1,  kPidPion},        
  { 	   321,  "K+",   0.493677,       1,  kPidKaon},        
  { 	  -321,  "K-",   0.493677,       1,  kPidKaon},        
  {       2212,  "p",    0.93827231,     1,  kPidProton},      
  {      -2212,  "p-",   0.93827231,    -1,  kPidProton},      
  { 1000010020,  "d",    1.8756,         1,  kPidDeuteron},       
  {-1000010020,  "d-",   1.8756,        -1,  kPidDeuteron},       
  { 1000010030,  "t",    2.8089,         1,  kPidTriton},      
  {-1000010030,  "t-",   2.8089,        -1,  kPidTriton},      
  { 1000020030,  "He3",  2.8084,         2,  kPidHe3},      
  {-1000020030,  "He3-", 2.8084,        -2,  kPidHe3},      
  { 1000020040,  "He4",  3.7274,         2,  kPidAlpha},	 
  {-1000020040,  "He4-", 3.7274,        -2,  kPidAlpha},	 
  { 1000020060,  "He6",  5.6055,         2,  kPidHe6},	 
  {-1000020060,  "He6-", 5.6055,        -2,  kPidHe6},	 
  { 1000030050,  "Li5",  4.6676,         3,  kPidLi5},	 
  {-1000030050,  "Li5-", 4.6676,        -3,  kPidLi5},	 
  { 1000030060,  "Li6",  5.6015,         3,  kPidLi6},	 
  {-1000030060,  "Li6-", 5.6015,         3,  kPidLi6},	 
  { 1000030070,  "Li7",  6.5338,         3,  kPidLi7},	 
  {-1000030070,  "Li7-", 6.5338,        -3,  kPidLi7},	 
  { 1000040070,  "Be7",  6.5342,         4,  kPidBe7},	 
  {-1000040070,  "Be7-", 6.5342,        -4,  kPidBe7},	 
  { 1000040090,  "Be9",  8.3948,         4,  kPidBe9},	 
  {-1000040090,  "Be9-", 8.3948,        -4,  kPidBe9},	 
  { 1000040100,  "Be10", 9.3275,         4,  kPidBe10},	 
  {-1000040100,  "Be10-",9.3275,        -4,  kPidBe10},	 
  { 1000050110,  "B11", 10.2666,         5,  kPidB11},	 
  {-1000050110,  "B11-",10.2666,        -5,  kPidB11}
};
const Char_t *StTrackCombPiD::fgPiDStatusNames[kTotal+1] = {
  "Undef",     "I70",     "I70U",     "Fit",     "FitU",     "dNdx",     "dNdxU", 
  "BTof",      "ETof",    "Mtd",      "BEmc",    "dEdx & BTof"
};

Int_t  StTrackCombPiD::fgl2p[KPidAllParticles] = {0};
Bool_t StTrackCombPiD::fgUsedx2 = kFALSE;
Bool_t StTrackCombPiD::fgUseTof = kFALSE;
Int_t  StTrackCombPiD::fgDebug = 0;
Int_t  StTrackCombPiD::fgNparticles = KPidParticles;
Int_t  StTrackCombPiD::fgUsePiDCorrection = 1;
StThreeVectorF StTofStatus::zeroP;
#define PrPP(A,B) if (StTrackCombPiD::Debug()) {std::cout << "StTrackCombPiD::" << (#A) << "\t" << (#B) << " = \t" << (B) << std::endl;}
#define PrPT(A,B) if (StTrackCombPiD::Debug()) {std::cout << "StTrackCombPiD::" << (#A) << "\t" << (#B) << " = \t" << (B);}

//________________________________________________________________________________
StBTofStatus::StBTofStatus(StBTofPidTraits *pid) : StTofStatus() {
  if (pid && TMath::Abs(pid->yLocal()) < 1.8 && pid->timeOfFlight() > 0 && pid->timeOfFlight() < 100) {
    fPiD = pid;
  } else {
    if (StTrackCombPiD::Debug() > 0) {
      cout << "StBTofStatus::StBTofStatus reject yLocal = " << pid->yLocal() << "\tzLocal = " << pid->zLocal() << "\ttimeOfFlight = " << pid->timeOfFlight() <<endl;
    }
    fPiD = 0;
  }
}
//________________________________________________________________________________
StETofStatus::StETofStatus(StETofPidTraits *pid) : StTofStatus() {
  if (pid && // TMath::Abs(pid->localX()) < 1.8 && 
      pid->timeOfFlight() > 0 && pid->timeOfFlight() < 100) {
    fPiD = pid;
  } else {
    if (StTrackCombPiD::Debug() > 0) {
      cout << "StETofStatus::StETofStatus reject localX = " << pid->localX() << "\tlocalY = " << pid->localY() 
	   << "\tdX = " << pid->deltaX() << "\tdY = " << pid->deltaY() 
	   << "\ttimeOfFlight = " << pid->timeOfFlight() <<endl;
    }
    fPiD = 0;
  }
}
//________________________________________________________________________________
void StTofStatus::Set(const KFParticle &particle, const KFVertex &bestVx) {
  static Double_t kClight = 1e-9*TMath::Ccgs(); // cm/nsec
  Double_t timeTof  = timeOfFlight(); PrPP(StBTofStatus::Set, timeTof);
  Double_t lengthTof = pathLength(); PrPP(StBTofStatus::Set, lengthTof);
  Double_t sigmaTime = St_tofSimResParamsC::instance()->average_timeres_tof()*1e-3; // in nses
  if (StTrackCombPiD::Debug()) {
    cout << "StTofStatus::Set particle\t"; particle.Print();
    cout << "StTofStatus::Set bestVx  \t"; bestVx.Print();
  }
  KFParticle atVx(particle);
  //  atVx.Covariance(35) = -1.; // non decay Vertex
  atVx.SetProductionVertex(bestVx);
  if (StTrackCombPiD::Debug()) {
    cout << "StTofStatus::Set atVx    \t"; atVx.Print();
  }
  Float_t dsdr[6] = {0};
  Float_t ds = atVx.GetDStoPoint(position().xyz(), dsdr);
  TRMatrix F(1,6, dsdr);                         PrPT(StBTofStatus::Set,F);
  TRSymMatrix Cov(6, &atVx.Covariance(0));       PrPT(StBTofStatus::Set,Cov);
  TRSymMatrix Bcov(F, TRArray::kAxSxAT, Cov);    PrPT(StBTofStatus::Set,Bcov);
  Double_t dds = TMath::Sqrt(Bcov[0]);
  Float_t pq, dpq;
  atVx.GetMomentum(pq, dpq);
  Double_t p2p2 = pq*pq;
  Double_t dp2q2 = 2*pq*dpq;
  Double_t length = ds*pq;
  fBetaV = timeTof*kClight/length;
  Double_t dds2 = TMath::Power(dds/ds, 2);
  Double_t dTime2 = TMath::Power(sigmaTime/timeTof, 2);
  fSigmaBetaV = fBetaV*TMath::Sqrt(dds2 + dTime2);
  fM2q2 =  p2p2*(fBetaV*fBetaV - 1);
  fSigmaM2q2 = fM2q2*TMath::Sqrt(TMath::Power(dp2q2/p2p2,2) + TMath::Power((2*fSigmaBetaV*fBetaV)/(fBetaV*fBetaV - 1), 2));
  if (StTrackCombPiD::Debug()) {
    cout << "StTofStatus::Set\t1/beta = " << fBetaV << " +/- " << fSigmaBetaV
	 << "\tM2/q2 = " << fM2q2 << " +/- " <<  fSigmaM2q2 << endl;
  }
  return;
}
//________________________________________________________________________________
StBTofPidTraits StTrackCombPiD::SetBTofPidTraits(const StMuBTofPidTraits &pid) {
  StBTofPidTraits btofPidTraits;
  btofPidTraits.setMatchFlag    (pid.matchFlag());
  btofPidTraits.setYLocal       (pid.yLocal());
  btofPidTraits.setZLocal       (pid.zLocal());
  btofPidTraits.setThetaLocal   (pid.thetaLocal());
  btofPidTraits.setTimeOfFlight (pid.timeOfFlight());
  btofPidTraits.setPathLength   (pid.pathLength());
  btofPidTraits.setBeta         (pid.beta());
  btofPidTraits.setPosition     (pid.position());
  btofPidTraits.setSigmaElectron(pid.sigmaElectron()); 
  btofPidTraits.setSigmaPion    (pid.sigmaPion()); 
  btofPidTraits.setSigmaKaon    (pid.sigmaKaon()); 
  btofPidTraits.setSigmaProton  (pid.sigmaProton());  
  return btofPidTraits;
}
#ifdef __TFG__VERSION__
//________________________________________________________________________________
StBTofPidTraits StTrackCombPiD::SetBTofPidTraits(const StPicoBTofPidTraits &pid, StPicoTrack *gTrack) {
  StBTofPidTraits btofPidTraits;
  btofPidTraits.setMatchFlag    (pid.btofMatchFlag());
  btofPidTraits.setYLocal       (pid.btofYLocal());
  btofPidTraits.setZLocal       (pid.btofZLocal());
  btofPidTraits.setPosition     (StThreeVectorF(pid.btofHitPosX(),pid.btofHitPosY(),pid.btofHitPosZ()));
  //  btofPidTraits.setThetaLocal   (pid.btofThetaLocal());
  btofPidTraits.setTimeOfFlight (pid.btof());
  //  btofPidTraits.setPathLength   (pid.btofPathLength());
  btofPidTraits.setBeta         (pid.btofBeta());
  btofPidTraits.setSigmaElectron(pid.nSigmaElectron()); 
  btofPidTraits.setSigmaPion    (pid.nSigmaPion()); 
  btofPidTraits.setSigmaKaon    (pid.nSigmaKaon()); 
  btofPidTraits.setSigmaProton  (pid.nSigmaProton());  
  return btofPidTraits;
}
#endif /*  __TFG__VERSION__ */				      
//________________________________________________________________________________
StETofPidTraits StTrackCombPiD::SetETofPidTraits(const StMuETofPidTraits &pid) {
  StETofPidTraits etofPidTraits;
  etofPidTraits.setMatchFlag(   pid.matchFlag   ());
  etofPidTraits.setLocalX(      pid.localX      ());
  etofPidTraits.setLocalY(      pid.localY      ());
  etofPidTraits.setThetaLocal(  pid.thetaLocal  ());
  etofPidTraits.setPosition(    pid.position    ());
  etofPidTraits.setDeltaX(      pid.deltaX      ());
  etofPidTraits.setDeltaY(      pid.deltaY      ());
  etofPidTraits.setTimeOfFlight(pid.timeOfFlight());
  etofPidTraits.setPathLength(  pid.pathLength  ());
  etofPidTraits.setBeta(        pid.beta        ());
  return etofPidTraits;
}
#ifdef __TFG__VERSION__
//________________________________________________________________________________
StETofPidTraits StTrackCombPiD::SetETofPidTraits(const StPicoETofPidTraits &pid) {
  StETofPidTraits etofPidTraits;
  etofPidTraits.setMatchFlag(   pid.matchFlag   ());
  //  etofPidTraits.setLocalX(      pid.localX      ());
  //  etofPidTraits.setLocalY(      pid.localY      ());
  //  etofPidTraits.setThetaLocal(  pid.thetaLocal  ());
  etofPidTraits.setPosition     (StThreeVectorF(pid.crossingX(),pid.crossingY(),pid.crossingZ()));
  etofPidTraits.setDeltaX(      pid.deltaX      ());
  etofPidTraits.setDeltaY(      pid.deltaY      ());
  etofPidTraits.setTimeOfFlight(pid.tof         ());
  //  etofPidTraits.setPathLength(  pid.pathLength  ());
  etofPidTraits.setBeta(        pid.beta        ());
  return etofPidTraits;
}
//________________________________________________________________________________
StMtdPidTraits StTrackCombPiD::SetMtdPidTraits(const StPicoMtdPidTraits &pid) {
  StMtdPidTraits mtdPidTraits;
  mtdPidTraits.setMatchFlag      (pid.matchFlag());
//   mtdPidTraits.setYLocal         (pid.yLocal());
//   mtdPidTraits.setZLocal         (pid.zLocal());
  mtdPidTraits.setDeltaY         (pid.deltaY());
  mtdPidTraits.setDeltaZ         (pid.deltaZ());
  //  mtdPidTraits.setThetaLocal     (pid.thetaLocal());
  mtdPidTraits.setTimeOfFlight   (pid.deltaTimeOfFlight());
  mtdPidTraits.setExpTimeOfFlight(0);
  //  mtdPidTraits.setPathLength     (pid.pathLength());
  mtdPidTraits.setBeta           (pid.beta());
  //  mtdPidTraits.setPosition       (pid.position());

  //  mtdPidTraits.setSigmaMuon      (pid.sigmaMuon()); 
  //  mtdPidTraits.setProbMuon       (pid.probMuon()); 
  return mtdPidTraits;
}
#endif /*  __TFG__VERSION__ */
//________________________________________________________________________________
StMtdPidTraits StTrackCombPiD::SetMtdPidTraits(const StMuMtdPidTraits &pid) {
  StMtdPidTraits mtdPidTraits;
  mtdPidTraits.setMatchFlag      (pid.matchFlag());
  mtdPidTraits.setYLocal         (pid.yLocal());
  mtdPidTraits.setZLocal         (pid.zLocal());
  mtdPidTraits.setDeltaY         (pid.deltaY());
  mtdPidTraits.setDeltaZ         (pid.deltaZ());
  mtdPidTraits.setThetaLocal     (pid.thetaLocal());
  mtdPidTraits.setTimeOfFlight   (pid.timeOfFlight());
  mtdPidTraits.setExpTimeOfFlight(pid.expTimeOfFlight());
  mtdPidTraits.setPathLength     (pid.pathLength());
  mtdPidTraits.setBeta           (pid.beta());
  mtdPidTraits.setPosition       (pid.position());

  mtdPidTraits.setSigmaMuon      (pid.sigmaMuon()); 
  mtdPidTraits.setProbMuon       (pid.probMuon()); 
  return mtdPidTraits;
}
//__________________________________________________________x[______________________
StTrackCombPiD::StTrackCombPiD() : fg3(), fPiDStatus(-1) {
  Clear();
}
//________________________________________________________________________________
StTrackCombPiD::StTrackCombPiD(StGlobalTrack *gTrack) : StTrackCombPiD() {
  if (! gTrack) return;
  StDcaGeometry *dca = gTrack->dcaGeometry();
  if (! dca) return;
  if (fgDebug) gTrack->Print();
  fId = gTrack->key();
  fDca = *dca;
  StSPtrVecTrackPidTraits &traits = gTrack->pidTraits();
  if (! traits.size()) return;
  for (UInt_t i = 0; i < traits.size(); i++) {
    StTrackPidTraits *trait = traits[i];
    if (! trait) continue;
    if ( trait->IsZombie()) continue;
    Short_t id = trait->detector()%100;
    if (id == kBTofId) {
      StBTofPidTraits* btof = dynamic_cast<StBTofPidTraits*>(trait);
      if (! btof) continue;
      StBTofStatus * btofSt =  new StBTofStatus(btof);
      if (btofSt->IsFailed()) {
	delete btofSt;
      } else {
	fStatus[kBTof] = btofSt;
      }
    } else if (id == kETofId) {
      StETofPidTraits* etof = dynamic_cast<StETofPidTraits*>(trait);
      if (! etof) continue;
      StETofStatus * etofSt =  new StETofStatus(etof);
      if (etofSt->IsFailed()) {
	delete etofSt;
      } else {
	fStatus[kETof] = etofSt;
      }
    } else if (id == kMtdId) {
      StMtdPidTraits* pid = dynamic_cast<StMtdPidTraits*>(trait);
      if (! pid) continue;
      fStatus[kMtd] = new StMtdStatus(pid);
    } else if (id == kTpcId) {
      StDedxPidTraits* pid = dynamic_cast<StDedxPidTraits*>(trait);
      if (pid) {
	switch (pid->method()) {
	case kTruncatedMeanId:         fStatus[kI70]   = new StdEdxStatus(pid); break;
	case kLikelihoodFitId:         fStatus[kFit]   = new StdEdxStatus(pid); break;
	case kEnsembleTruncatedMeanId: fStatus[kI70U]  = new StdEdxStatus(pid); break;// == kTruncatedMeanId+1 uncorrected
	case kWeightedTruncatedMeanId: fStatus[kFitU]  = new StdEdxStatus(pid); break;  // == kLikelihoodFitId+1; uncorrected
	case kOtherMethodId:           fStatus[kdNdx]  = new StdEdxStatus(pid); break;
	case kOtherMethodId2:          fStatus[kdNdxU] = new StdEdxStatus(pid); break;
	default: break;
	}
      } else {
	StProbPidTraits *pidprob = dynamic_cast<StProbPidTraits*>(trait);
	if (pidprob) fProb = pidprob;
      }
    }
  }
  SetCombPiD();
}
//________________________________________________________________________________
StTrackCombPiD::StTrackCombPiD(StMuTrack *gTrack) : StTrackCombPiD() {
  Clear();
  if (! gTrack) return;
  if (fgDebug) gTrack->Print();
  Int_t dcaGeometryIndex = gTrack->index2Cov();
  if (dcaGeometryIndex < 0) return;
  fId = gTrack->id();
  fDca = *StMuDst::instance()->covGlobTracks(dcaGeometryIndex);
  const StMuProbPidTraits &probPidTraits = gTrack->probPidTraits();
  const StMuBTofPidTraits &btofPidTraits = gTrack->btofPidTraits();
  const StMuETofPidTraits &etofPidTraits = gTrack->etofPidTraits();
  const StMuMtdPidTraits  &mtdPidTraits = gTrack->mtdPidTraits();
  fg3 = TVector3(gTrack->p().xyz()); // p of global track
  static StDedxPidTraits pidI70; //!
  static StDedxPidTraits pidFit; //!
  static StDedxPidTraits pidI70U; //!
  static StDedxPidTraits pidFitU; //!
  static StDedxPidTraits pidNdx; //!
  static StDedxPidTraits pidNdxU;//!
  static StBTofPidTraits pidBTof; //!
  static StETofPidTraits pidETof; //!
  static StMtdPidTraits  pidMtd; //!
  if (probPidTraits.dEdxTruncated() > 0) {
    pidI70 = StDedxPidTraits(kTpcId, kTruncatedMeanId, 100*((UShort_t)probPidTraits.dEdxTrackLength()) + gTrack->nHitsDedx(), 
			     probPidTraits.dEdxTruncated(), probPidTraits.dEdxErrorTruncated(),probPidTraits.log2dX());
    fStatus[kI70] = new StdEdxStatus(&pidI70);
  } 
  if (probPidTraits.dEdxFit() > 0) {
    pidFit = StDedxPidTraits(kTpcId, kLikelihoodFitId, 100*((UShort_t)probPidTraits.dEdxTrackLength()) + gTrack->nHitsDedx(), 
			     probPidTraits.dEdxFit(), probPidTraits.dEdxErrorFit(),probPidTraits.log2dX());
    fStatus[kFit] = new StdEdxStatus(&pidFit);
  }
  if (probPidTraits.dNdxFit() > 0) {
    pidNdx = StDedxPidTraits(kTpcId, kOtherMethodId, 100*((UShort_t)probPidTraits.dEdxTrackLength()) + gTrack->nHitsDedx(), 
			     probPidTraits.dNdxFit(), probPidTraits.dNdxErrorFit(),probPidTraits.log2dX());
    fStatus[kdNdx] = new StdEdxStatus(&pidNdx);
  }
  if (btofPidTraits.matchFlag()) {
    static StBTofPidTraits btof;
    btof= SetBTofPidTraits(gTrack->btofPidTraits());
    StBTofStatus * btofSt =  new StBTofStatus(&btof);
    if (btofSt->IsFailed()) {
      delete btofSt;
    } else {
      fStatus[kBTof] = btofSt;
    }
  }
  if (etofPidTraits.matchFlag()) {
    static StETofPidTraits etof;
    etof = SetETofPidTraits(gTrack->etofPidTraits());
    StETofStatus *etofSt = new StETofStatus(&etof);
    if (etofSt->IsFailed()) {
      delete etofSt;
    } else {
      fStatus[kETof] = etofSt;
    }
  }
  if (mtdPidTraits.matchFlag()) {
    StMtdPidTraits mtd;
    mtd = SetMtdPidTraits(gTrack->mtdPidTraits());
    fStatus[kMtd] = new StMtdStatus(&mtd);
  }
  if (mtdPidTraits.matchFlag()) {
    StMtdPidTraits mtd;
    mtd = SetMtdPidTraits(gTrack->mtdPidTraits());
    fStatus[kMtd] = new StMtdStatus(&mtd);
  }

  SetCombPiD();
  if (fgDebug > 1) Print();
}
//________________________________________________________________________________
StTrackCombPiD::StTrackCombPiD(StMuDst *muDst, Int_t iTrack) : StTrackCombPiD(muDst->globalTracks(iTrack)) {}
//________________________________________________________________________________
#ifdef __TFG__VERSION__
//________________________________________________________________________________
StTrackCombPiD::StTrackCombPiD(StPicoTrack *gTrack, StPicoTrackCovMatrix *cov ) : StTrackCombPiD() {
  if (! gTrack) return;
  if (fgDebug) gTrack->Print();
  if (! gTrack->charge())  return;
  if (  gTrack->nHitsFit() < 15) return;
  if (  gTrack->dEdxError() < 0.01 || gTrack->dEdxError() > 0.15 ) return;
  if (cov) {
    fId = gTrack->id();
    fDca = cov->dcaGeometry();
  } else {
    cout << "StTrackCombPiD::StTrackCombPiD(StPicoTrack " << gTrack << ", StPicoTrackCovMatrix *" << cov << ")   Not valid DCA" << endl; 
    return;
  }
  static StDedxPidTraits pidI70; //!
  static StDedxPidTraits pidFit; //!
  static StDedxPidTraits pidI70U; //!
  static StDedxPidTraits pidFitU; //!
  static StDedxPidTraits pidNdx; //!
  static StDedxPidTraits pidNdxU;//!
  static StBTofPidTraits pidBTof; //!
  static StETofPidTraits pidETof; //!
  static StMtdPidTraits  pidMtd; //!
  static StPicoBEmcPidTraits pidBEmc; //!
  if (gTrack->dEdx() > 0) {
#if 0 /* no I70 on picoDst */
    pidI70 = StDedxPidTraits(kTpcId, kTruncatedMeanId, gTrack->nHitsDedx(), 
			     1e-6*gTrack->dEdx(), gTrack->dEdxError());
    fStatus[kI70] = new StdEdxStatus(&pidI70);
#endif
    pidFit = StDedxPidTraits(kTpcId, kLikelihoodFitId, gTrack->nHitsDedx(), 
			     1e-6*gTrack->dEdx(), gTrack->dEdxError());
    fStatus[kFit] = new StdEdxStatus(&pidFit);
  }
  if (gTrack->dNdx() > 0) {
    pidNdx = StDedxPidTraits(kTpcId, kOtherMethodId, gTrack->nHitsDedx(),
			     gTrack->dNdx(), gTrack->dNdxError());
    fStatus[kdNdx] = new StdEdxStatus(&pidNdx);
  }
  Int_t ibtof = gTrack->bTofPidTraitsIndex();
  if (ibtof >= 0) {
    static StBTofPidTraits btof;
    btof = SetBTofPidTraits(*StPicoDst::instance()->btofPidTraits(ibtof), gTrack);
    StBTofStatus * btofSt =  new StBTofStatus(&btof);
    if (btofSt->IsFailed()) {
      delete btofSt;
    } else {
      fStatus[kBTof] = btofSt;
    }
  }
  Int_t ietof = gTrack->eTofPidTraitsIndex();
  if (ietof >= 0) {
    static StETofPidTraits etof;
    etof = SetETofPidTraits(*StPicoDst::instance()->etofPidTraits(ietof));
    StETofStatus *etofSt = new StETofStatus(&etof);
    if (etofSt->IsFailed()) {
      delete etofSt;
    } else {
      fStatus[kETof] = etofSt;
    }
  }
  Int_t imtd = gTrack->mtdPidTraitsIndex();
  if (imtd >= 0) {
    static StMtdPidTraits pidMtd;
    pidMtd = SetMtdPidTraits(*StPicoDst::instance()->mtdPidTraits(imtd));
    fStatus[kMtd] = new StMtdStatus(&pidMtd);
  }
  Int_t ibemc = gTrack->bemcPidTraitsIndex();
  if (ibemc >= 0) {
    fStatus[kBEmc] = new StBEmcStatus(StPicoDst::instance()->bemcPidTraits(ibemc));
  }
  SetCombPiD();
}
#endif /* __TFG__VERSION__ */
//________________________________________________________________________________
StTrackCombPiD::StTrackCombPiD(StPicoDst *pico, Int_t iTrack) : StTrackCombPiD(pico->track(iTrack), pico->trackCovMatrix(iTrack)) {}
//________________________________________________________________________________
void StTrackCombPiD::SetCombPiD() {
  if (! fgl2p[3]) {
    for (Int_t l = kPidElectron; l < fgNparticles; l++) {
      for (Int_t p = 0; p < 34; p++) {
	if (fgParticles[p].code == l) {
	  fgl2p[l] = p;
	  break;
	}
      }
    }
  }
  if (! (fStatus[kI70] || fStatus[kFit])) return;
  if (fId <= 0) return;
  fParticle = fDca.Particle(fId);
  fg3 = TVector3(fParticle.GetPx(),fParticle.GetPy(),fParticle.GetPz());
  fPiDStatus = 0;
  Double_t pMomentum = fg3.Mag();
  fpL10 = TMath::Log10(pMomentum);
  // Set up Tof
  Float_t betaTof = -999;
  if (fBTof() && fBTof()->PiD()) {
    StBTofStatus    *BTofSt = (StBTofStatus    *) fStatus[kBTof ]; 
    betaTof = BTofSt->beta();
    BTofSt->Set(fParticle, fgBestVx); //     BTofSt->Set(fDca, fgBestVx);
    if (BTofSt->BetaV() < 0.5) {
      SafeDelete(fStatus[kBTof ]); 
    }
  } else if (fETof() && fETof()->PiD()) {
    StETofStatus    *ETofSt = (StETofStatus    *) fStatus[kETof ]; 
    betaTof = ETofSt->beta();
    ETofSt->Set(fParticle, fgBestVx); //     ETofSt->Set(fDca, fgBestVx);
    if (ETofSt->BetaV() < 0.5) {
      SafeDelete(fStatus[kETof ]); 
    }
  }
  for (Int_t l = kPidElectron; l < fgNparticles; l++) {
    Int_t p = fgl2p[l];
    Int_t charge  = fgParticles[p].charge;
    Double_t mass = fgParticles[p].mass;
    Double_t pOverQ = pMomentum/charge;
    Double_t p2OverQ2 = pOverQ*pOverQ;
    Double_t M2overQ2 = mass*mass/(charge*charge);
    Double_t betagamma = pMomentum*TMath::Abs(charge)/mass;
    //    Double_t beta = betagamma/TMath::Sqrt(1. + betagamma*betagamma);
    fbgs[l] = betagamma;
    fbghyp[l] = TMath::Log10(fbgs[l]);
    for (Int_t k = kI70; k <= kOtherMethodId2; k++) {
      if (! fStatus[k]) continue;
      if (dEdxStatus(k)->I() > 0 && dEdxStatus(k)->D() > 0.01 && dEdxStatus(k)->D() < 0.15) {
	UChar_t fit = 0;
	if (k == kLikelihoodFitId || k == kWeightedTruncatedMeanId) fit = 1;
	else if (k == kOtherMethodId || k == kOtherMethodId2) fit = 2;
	if (fgUsedx2) {
	  fStatus[k]->Pred(l)  = StdEdxPull::EvalPred2(betagamma, dEdxStatus(k)->log2dX(), fit, charge);
	  fStatus[k]->PredC(l) = fStatus[k]->Pred(l);
	}
	else {
	  fStatus[k]->Pred(l)  = StdEdxPull::EvalPred(betagamma, fit, charge, mass);
	  if (PiDCorrection()) {
	    //	    fStatus[k]->PredC(l) = fStatus[k]->Pred(l)  * dEdxCorr(fbghyp[l], l);
	    fStatus[k]->PredC(l) = fStatus[k]->Pred(l)  * St_pidCorrectionC::instance()->Correction(fpL10, l, k);
	  } else {
	    fStatus[k]->PredC(l) = fStatus[k]->Pred(l);
	  }
	}
	fStatus[k]->Residual(l)  = TMath::Log(dEdxStatus(k)->I()/fStatus[k]->Pred(l));
	fStatus[k]->Pull(l) = fStatus[k]->Residual(l)/(dEdxStatus(k)->D());
	fStatus[k]->ResidualC(l) = TMath::Log(dEdxStatus(k)->I()/fStatus[k]->PredC(l));
        if (fgUsedx2) {
	  fStatus[k]->PullC(l) = fStatus[k]->Pull(l);
	} else {
	  Double_t pullC = fStatus[k]->ResidualC(l)/dEdxStatus(k)->D();
	  if (PiDCorrection()) {
	    //	    fStatus[k]->PullC(l) = dEdxPullCorrection(pullC, fbghyp[l], l);
	    fStatus[k]->PullC(l) = pullC*St_pidCorrectionC::instance()->Correction(fpL10, l, k, 0, 1, 0);
	  } else {
	    fStatus[k]->PullC(l) = pullC;
	  }
	}
      } else {
	SafeDelete(fStatus[k]);
      }
    }
    // ToF
    for (Int_t k = kBTof; k <= kETof; k++) {
      if (! fStatus[k]) continue;
      if (fStatus[k]->IsFailed()) {
	SafeDelete(fStatus[k]);
	continue;
      }
      StTofStatus *tofSt = (StTofStatus *) Status(k);
      tofSt->Pred(l)  = M2overQ2;
      tofSt->PredC(l) = tofSt->Pred(l) ;
      Double_t M2q2   = tofSt->M2q2();
      Double_t SigmaM2q2 = tofSt->SigmaM2q2();
      Double_t dM2q = M2q2 - M2overQ2;
      tofSt->ResidualC(l) = dM2q;
      tofSt->PullC(l) = tofSt->ResidualC(l)/SigmaM2q2;
      Double_t sigma = tofSt->Sigma(l);
      if (TMath::Abs(sigma) < 100 && betaTof > 0 && betaTof < 2) {
	Double_t dM2 = p2OverQ2*(1./(betaTof*betaTof) - 1.) - tofSt->Pred(l);
	tofSt->Residual(l) = dM2;
	tofSt->Pull(l) = sigma;
      }
    }
  }
  SetPDG();
  if (fgDebug) {
    Print();
  }
}
//________________________________________________________________________________
void StTrackCombPiD::Print(Option_t *opt) const {
  for (Int_t k = 1; k < kTotal; k++) {
    if (! fStatus[k]) continue;
    cout << fgPiDStatusNames[k];
    if        (k == kUndefinedMethodId) {cout << "UndefinedMethod       " << endl; continue;
    } else if (k <= kdNdxU) {((StdEdxStatus *) fStatus[k])->Print(); continue;
    } else if (k == kBTof)  {cout << " beta = " << fBTof()->beta() << "\t1/beta = " 
				  << fBTof()->BetaV() << " +/- " << fBTof()->SigmaBetaV() << "\tM2/q2 = " << fBTof()->M2q2() << " +/- " <<  fBTof()->SigmaM2q2();
    } else if (k == kETof)  {cout << " beta = " << fETof()->beta() << "\t1/beta = " 
				  << fETof()->BetaV() << " +/- " << fETof()->SigmaBetaV() << "\tM2/q2 = " << fETof()->M2q2() << " +/- " <<  fETof()->SigmaM2q2();
    } else if (k == kMtd)   {cout << " beta = " << fMtd()->beta() << "\tdetaY = " << fMtd()->PiD()->deltaY() << "\tdetaZ = " << fMtd()->PiD()->deltaZ() 
				  << "\tdT = " << fMtd()->PiD()->timeOfFlight() - fMtd()->PiD()->expTimeOfFlight();
    } else if (k == kBEmc)  {cout << " bemcR = " << fBEmc()->PiD()->bemcE();
    }
    cout << endl;
    fStatus[k]->Print();
  }
  if (fTPCPDG.size())  {cout << "TPC: "; for (auto pdg :  fTPCPDG) cout << "\t" << pdg; cout << endl;}
  if (fTofPDG.size())  {cout << "Tof: "; for (auto pdg :  fTofPDG) cout << "\t" << pdg; cout << endl;}
  if (fPDGList.size()) {cout << "All: "; for (auto pdg : fPDGList) cout << "\t" << pdg; cout << endl;}
  if (fStatus[kBTof] || fStatus[kETof]) {
    cout << "have ToF" << endl;
  }
}
//________________________________________________________________________________
void StdEdxStatus::Print(Option_t *option) const {
  if (! fPiD) {cout << "\tEmpty" << endl;}
  else {
    cout << Form("\tI = %8.3f keV +/- %8.3f %% ",1e6*I(), 100*D()) << endl;
    cout << "Part: "; for (Int_t l = kPidElectron; l < StTrackCombPiD::Nparticles(); l++) {cout << Form("%10s", StTrackCombPiD::l2par(l).name);} cout << endl;
    cout << "Pred: "; for (Int_t l = kPidElectron; l < StTrackCombPiD::Nparticles(); l++) {cout << Form("%10.4g",1e6*pred(l));} cout << endl;
    cout << "PredC:"; for (Int_t l = kPidElectron; l < StTrackCombPiD::Nparticles(); l++) {cout << Form("%10.4g",1e6*predC(l));} cout << endl;
    cout << "Res.: "; for (Int_t l = kPidElectron; l < StTrackCombPiD::Nparticles(); l++) {cout << Form("%10.4g",residual(l));} cout << endl;
    cout << "Res.C:"; for (Int_t l = kPidElectron; l < StTrackCombPiD::Nparticles(); l++) {cout << Form("%10.4g",residualC(l));} cout << endl;
    cout << "Pull: "; for (Int_t l = kPidElectron; l < StTrackCombPiD::Nparticles(); l++) {cout << Form("%10.4g",pull(l));} cout << endl;
    cout << "PullC:"; for (Int_t l = kPidElectron; l < StTrackCombPiD::Nparticles(); l++) {cout << Form("%10.4g",pullC(l));} cout << endl;
  }
}
//________________________________________________________________________________
void StTrackPiD::Print(Option_t *option) const {
  cout << "Part: "; for (Int_t l = kPidElectron; l < StTrackCombPiD::Nparticles(); l++) {cout << Form("%10s", StTrackCombPiD::l2par(l).name);} cout << endl;
  cout << "Pred: "; for (Int_t l = kPidElectron; l < StTrackCombPiD::Nparticles(); l++) {cout << Form("%10.4g",pred(l));} cout << endl;
  cout << "PredC:"; for (Int_t l = kPidElectron; l < StTrackCombPiD::Nparticles(); l++) {cout << Form("%10.4g",predC(l));} cout << endl;
  cout << "Res.: "; for (Int_t l = kPidElectron; l < StTrackCombPiD::Nparticles(); l++) {cout << Form("%10.4g",residual(l));} cout << endl;
  cout << "ResC: "; for (Int_t l = kPidElectron; l < StTrackCombPiD::Nparticles(); l++) {cout << Form("%10.4g",residualC(l));} cout << endl;
  cout << "Pull: "; for (Int_t l = kPidElectron; l < StTrackCombPiD::Nparticles(); l++) {cout << Form("%10.4g",pull(l));} cout << endl;
  cout << "PullC:"; for (Int_t l = kPidElectron; l < StTrackCombPiD::Nparticles(); l++) {cout << Form("%10.4g",pullC(l));} cout << endl;
}
#if 0
//________________________________________________________________________________
Double_t StTrackCombPiD::dEdxCorr(Double_t bgL10, Int_t code)  {
  Double_t CorrL = 4.87e-03;
  Double_t bg10 = bgL10;
  if (code == kPidElectron) {
    if (bgL10 < 2.15) bg10 = 2.15;
    if (bgL10 < 2.50) {
      static TF1 *E1 = 0;
      if (! E1) {
	Double_t pars[7] = {  12.52016,  -7.676868,  -1.707558,  0.5937531,  0.4350409, 0.02464118, -0.04630323}; //electrons [2,1,2.5]
	E1 = new TF1("dEdxE1","pol6",2.15,2.50);
	E1->SetParameters(pars);
      }
      CorrL += E1->Eval(bg10);
    } else {
      static TF1 *E2 = 0;
      if (! E2) {
	Double_t pars[7] = {-0.3267676,   0.476879, -0.3152098, 0.01623315, 0.06886368, -0.02498914, 0.002566173}; //electrons [2,5,3.8]
	E2 = new TF1("dEdxE2","pol6",2.50,3.80);
	E2->SetParameters(pars);
      }
      CorrL += E2->Eval(bg10);
    }
    static TF1 *E3 = 0;
    if (! E3) {
      Double_t pars[2] = {-0.03429437, 0.02038976}; //e
      Double_t parb[2] = {-0.03751737, 0.01611591}; //E4 ???
      for (Int_t i = 0; i < 2; i++) pars[i] += parb[i];
      E3 = new TF1("dEdxE3","pol1",2.1,3.8);
      E3->SetParameters(pars);
    }
    CorrL += E3->Eval(bgL10);
  } else if (code == kPidPion || code == kPidMuon || code == kPidKaon) {
    if (bgL10 < -0.25) bg10 = 0.25;
    if (bgL10 < 0.05) {
      static TF1 *Pi1 = 0;
      if (! Pi1) {
	Double_t pars[5] = {-0.0116273, 0.05124145, -0.9784855,  -10.31482,    -2.1687}; //pi [-0.25,0.05]
	Pi1 = new TF1("dEdxPi1","pol4",-0.25,0.05);
	Pi1->SetParameters(pars);
      }
      CorrL += Pi1->Eval(bg10);
    } else if (bgL10 < 0.55) {
      static TF1 *Pi2 = 0;
      if (! Pi2) {
	Double_t pars[5] = {-0.0007022319, -0.3074184,   1.313129,  -1.709188,  0.6149398}; //pi [0.02,0.55]
	Pi2 = new TF1("dEdxPi2","pol4",0.02,0.55);
	Pi2->SetParameters(pars);
      }
      CorrL += Pi2->Eval(bg10);
    } else {
      static TF1 *Pi3 = 0;
      if (! Pi3) {
	Double_t pars[7] = {-0.8277655,   5.488526,  -14.61932,   19.99763,  -14.81849,   5.647092,  -0.866685}; //pi [0.50,1.80]
	Pi3 = new TF1("dEdxPi3","pol6",0.50,1.80);
	Pi3->SetParameters(pars);
      }
      if (bgL10 > 1.7) bg10 = 1.7;
      CorrL += Pi3->Eval(bg10);
    }
    static TF1 *Pi4 = 0;
    if (! Pi4) {
      Double_t pars[8] = {0.005057659, -0.05614078,  0.4202523, -0.9288579,  0.9325692, -0.3811554, 0.008754178, 0.02183855}; //pi
      Double_t parb[5] = {-0.003534838,  0.0238152, -0.04105992, 0.03616169, -0.01032226}; //pion b
      for (Int_t i = 0; i < 5; i++) pars[i] += parb[i];
      Pi4 = new TF1("dEdxPi4","pol7",-0.25,1.70);
      Pi4->SetParameters(pars);
    }
    CorrL += Pi4->Eval(bgL10);
  } else if (code == kPidProton || code >= kPidDeuteron) {
    if (bgL10 < -0.8) bg10 = -0.8;
    if (bgL10 >  0.8) bg10 =  0.8;
    static TF1 *Proton1 = 0;
    if (! Proton1) {
      Double_t pars[10] = {0.0007210231, -0.01249025,   0.208259, -0.2458525, -0.5773149,  0.5679841,   1.433286,  -1.169037,  -1.628503,   1.460514}; //P [-0.80,0.80]
      Proton1 = new TF1("dEdxProton1","pol9",-0.80,0.80);
      Proton1->SetParameters(pars);
    }
    CorrL += Proton1->Eval(bg10);
    static TF1 *Proton2 = 0;
    if (! Proton2) {
      Double_t pars[4] = {0.01299427, 0.01952912, 0.03317554, -0.02754662}; //p
      Double_t parb[2] = {0.002984208, 0.007781605}; //proton b
      for (Int_t i = 0; i < 2; i++) pars[i] += parb[i];
      Proton2 = new TF1("dEdxProton2","pol3",-0.80,0.80);
      Proton2->SetParameters(pars);
    }
    CorrL += Proton2->Eval(bgL10);
  }
  return TMath::Exp(CorrL);
}
//________________________________________________________________________________
Double_t StTrackCombPiD::dEdxPullCorrection(Double_t pull, Double_t bgL10, Int_t code)  {
  Double_t Pull = pull;
#if 0
  Double_t bg10 = bgL10;
  if (code == kPidElectron) {
    Pull += -0.0761419;
    if (bgL10 < 2.2) bg10 = 2.2;
    if (bgL10 > 3.6) bg10 = 3.6;
    if (bg10 > 2.3) {
      static TF1 *E1S = 0;
      if (! E1S) {
	Double_t pars[4] = {  9.759174,  -7.884564,   2.321952, -0.2280004}; //e [2.3,3.6]
	E1S = new TF1("dEdxSigmaE1","pol3",2.3,3.6);
	E1S->SetParameters(pars);
      }
      Pull /= E1S->Eval(bg10);
    } else {
      static TF1 *E2S = 0;
      if (! E2S) {
	Double_t pars[3] = {  20.30106,  -18.17585,   4.273127}; //e [2.00,2.32]
	E2S = new TF1("dEdxSigmaE2","pol2",2.00,2.32);
	E2S->SetParameters(pars);
      }
      Pull /= E2S->Eval(bg10);
    }
  } else if (code == kPidPion || code == kPidMuon || code == kPidKaon) {
    if (bgL10 < -0.2) bg10 = -0.2;
    if (bgL10 <  0.4) {
      static TF1 *Pi1S = 0;
      if (! Pi1S) {
	Double_t pars[3] = {  1.096374, -0.8221205,   1.539101}; //pi [-0.2,0.5]
	Pi1S = new TF1("dEdxSigmaPi1","pol2",-0.2,0.5);
	Pi1S->SetParameters(pars);
      }
      Pull /= Pi1S->Eval(bg10);
    } else {
      Pull /= 1.05911e+00;
    }
  } else if (code == kPidProton || code >= kPidDeuteron) {
    if (bgL10 < -0.6) bg10 = -0.6;
    if (bgL10 <  0.8) bg10 =  0.8;
    if (bg10 < -0.05) {
       Double_t pars[2] = {  1.137791,  0.3378384}; //proton [-0.6,0.0]
       Pull /= (pars[0] + pars[1]*bg10);
    } else {
       Double_t pars[2] = {  1.120294, -0.1218736}; //proton [-0.05,0.80]
       Pull /= (pars[0] + pars[1]*bg10);
    }
  }
#endif
  return Pull;
}
//________________________________________________________________________________
Double_t StTrackCombPiD::M2BTofCorr(Double_t pL10, Int_t code)  {
  Double_t Corr = 0;
  Double_t p10 = pL10;
  if (code == kPidElectron) {
    static TF1 *E1 = 0;
    if (! E1) {
    //Double_t pars[5] = { 0.01265596, -0.02078762, -0.04596959, -0.04943213, -0.02199248}; //e
      Double_t pars[5] = {-0.00352904, -0.02078762, -0.04596959, -0.04943213, -0.02199248}; //e
      Double_t parb[5] = {-0.003455332, -0.02078977, -0.04685939, -0.05109632, -0.02288036}; //e dEdxP
      for (Int_t i = 0; i < 5; i++) pars[i] += parb[i];
      E1 = new TF1("M2BTofE1","pol4",-0.85,0.28);
      E1->SetParameters(pars);
    }
    Corr = E1->Eval(p10);
  } else if (code == kPidPion || code == kPidMuon || code == kPidKaon) {
    static TF1 *Pion1 = 0;
    if (! Pion1) {
      Double_t pars[8] = {0.005495614, 0.00672486, -0.001912834, -0.01906281, -0.07363129,   -0.20461, -0.2838375,  -0.144034}; //pion
      Double_t parb[7] = {0.005508667, 0.006677259, -0.008315284, -0.05185988, -0.1001799, -0.08455071, -0.02629651}; //pion dEdxP
      for (Int_t i = 0; i < 7; i++) pars[i] += parb[i];
      Pion1 = new TF1("M2BTofPion1","pol7",-0.90,0.60);
      Pion1->SetParameters(pars);
    }
    Corr = Pion1->Eval(p10);
  } else if (code == kPidProton || code >= kPidDeuteron) {
    static TF1 *Proton1 = 0;
    if (! Proton1) {
      //      Double_t pars[2] = {0.01191059, 0.02612714}; //proton
      Double_t pars[2] = {-0.004274406, 0.02612714}; //proton
      Double_t parb[2] = {-0.004009571, 0.01519456}; //proton dEdxP
      for (Int_t i = 0; i < 2; i++) pars[i] += parb[i];
      Proton1 = new TF1("M2BTofProton1","pol1",-0.50,0.60);
      Proton1->SetParameters(pars);
    }
    Corr = Proton1->Eval(p10);
  }
  return Corr;
}
//________________________________________________________________________________
Double_t StTrackCombPiD::M2BTofSigma(Double_t pL10, Int_t code)  {
  Double_t sigma = 0;
  Double_t p10 = pL10;
  if (code == kPidElectron) {
    static TF1 *E1 = 0;
    if (! E1) {
      Double_t pars[2] = { -4.087059,   4.408073}; //e
      E1 = new TF1("M2BTofSigmaE1","expo",-0.85,0.28);
      E1->SetParameters(pars);
    }
    sigma = E1->Eval(p10);
  } else if (code == kPidPion || code == kPidMuon || code == kPidKaon) {
    static TF1 *Pion1 = 0;
    if (! Pion1) {
      Double_t pars[2] = { -4.011896,   3.862085}; //pion
      Pion1 = new TF1("M2BTofSigmaPion1","expo",-0.90,0.60);
      Pion1->SetParameters(pars);
    }
    sigma = Pion1->Eval(p10);
  } else if (code == kPidProton || code >= kPidDeuteron) {
    if (pL10 < -0.4) {
      static TF1 *Proton1 = 0;
      if (! Proton1) {
	Double_t pars[3] = {  12.91172,   81.80843,   103.4481}; //proton [-0.6,-0.38]
	Proton1 = new TF1("M2BTofSigmaProton1","TMath::Exp([0]+x*([1]+x*[2]))",-0.60,-0.38);
	Proton1->SetParameters(pars);
      }
      sigma = Proton1->Eval(p10);
    } else {
      static TF1 *Proton2 = 0;
      if (! Proton2) {
	Double_t pars[3] = { -3.144486,   1.730876,   3.622293}; //proton [-0.4,0.6]
	Proton2 = new TF1("M2BTofSigmaProton2","TMath::Exp([0]+x*([1]+x*[2]))",-0.60,-0.38);
	Proton2->SetParameters(pars);
      }
      sigma = Proton2->Eval(p10);
    }
  }
  return sigma;
}
#endif
//________________________________________________________________________________
void StTrackCombPiD::SetPDGfromTPC() {
  for (Int_t k = kI70; k <= kOtherMethodId2; k++) {
    if (! fStatus[k]) continue;
    for (Int_t l = kPidElectron; l < fgNparticles; l++) {
      if (TMath::Abs(fStatus[k]->PullC(l)) < fgSigmaCut) {
	Int_t p = fgl2p[l];
	fTPCPDG.push_back(GetQ()*fgParticles[p].pdg);
      }
    }
  }
}
//________________________________________________________________________________
void StTrackCombPiD::SetPDGfromTof() {
  for (Int_t k = kBTof; k <= kETof; k++) {
    if (! fStatus[k]) continue;
    for (Int_t l = kPidElectron; l < fgNparticles; l++) {
      if (TMath::Abs(fStatus[k]->PullC(l)) < fgSigmaCut) {
	Int_t p = fgl2p[l];
	fTofPDG.push_back(GetQ()*fgParticles[p].pdg);
      }
    }
  }
}
//________________________________________________________________________________
void StTrackCombPiD::SetPDG() {
  SetPDGfromTPC();
  if (fgUseTof) {
    SetPDGfromTof();
  }
  if (fTofPDG.size()) {
    for (auto tpcPDG : fTPCPDG) {
      for (auto tofPDG : fTofPDG) {
	if (tpcPDG == tofPDG) {
	  fPDGList.push_back(tpcPDG);
	}
      }
    }
  } else {
    fPDGList = fTPCPDG;
  }
  if (! fPDGList.size()) {fPDGList.push_back(-1);}
}
//________________________________________________________________________________
void StTrackCombPiD::ResetBestVx() {
  Float_t param[6] = {0};
  Float_t Cov[21] = {0};
  ((KFParticleBase *) &fgBestVx)->Initialize(param,Cov, 0, 1.f);
  ((KFParticleBase *) &fgBestVx)->SetId(0);
}
//________________________________________________________________________________
void StTrackCombPiD::SetBestVx(const Float_t xyz[3], const Float_t xyzErrors[3]) {
  if (! xyz) {ResetBestVx(); return;}
  Float_t param[6] = {0};
  Float_t Cov[21] = {0};
  for (Int_t i = 0; i < 3; i++) {
    param[i] = xyz[i];
    if (! xyzErrors) {
      Cov[KFParticleBase::IJ(i,i)] = xyzErrors[i]*xyzErrors[i];
    }
  }
  ((KFParticleBase *) &fgBestVx)->Initialize(param,Cov, 0, 1.f);
  ((KFParticleBase *) &fgBestVx)->SetId(1);
}
//________________________________________________________________________________
void StTrackCombPiD::SetBestVx(const Double_t xyz[3], const Double_t xyzErrors[3]) {
  Float_t param[6] = {0};
  Float_t Cov[21] = {0};
  if (! xyz) {ResetBestVx(); return;}
  
  for (Int_t i = 0; i < 3; i++) {
    param[i] = xyz[i];
    Cov[KFParticleBase::IJ(i,i)] = xyzErrors[i]*xyzErrors[i];
  }
  ((KFParticleBase *) &fgBestVx)->Initialize(param,Cov, 0, 1.f);
  ((KFParticleBase *) &fgBestVx)->SetId(1);
}
//________________________________________________________________________________
void StTrackCombPiD::SetBestVxCov(const Float_t xyz[3], const Float_t covVx[6]) {
  Float_t param[6] = {0};
  Float_t Cov[21] = {0};
  std::copy(xyz, xyz+3, param);
  std::copy(covVx, covVx+6, Cov);
  ((KFParticleBase *) &fgBestVx)->Initialize(param,Cov, 0, 1.f);
  ((KFParticleBase *) &fgBestVx)->SetId(1);
}
//________________________________________________________________________________
void StTrackCombPiD::SetBestVx(const StVertex *bestVx) {
  if (bestVx) {
    SetBestVxCov(bestVx->position().xyz(), bestVx->covariance());
    ((KFParticleBase *) &fgBestVx)->SetId(bestVx->key());
  } else {
    ResetBestVx();
  }
}
//________________________________________________________________________________
void StTrackCombPiD::SetBestVx(const StMuPrimaryVertex *bestVx) {
  if (bestVx) {
    SetBestVx(bestVx->position().xyz(), bestVx->posError().xyz());
  } else {
    ResetBestVx();
  }
}
//________________________________________________________________________________
void StTrackCombPiD::SetBestVx(const StPicoEvent *event) {
  if (event) {
    Double_t xyz[3], xyzError[3];
    event->primaryVertex().GetXYZ(xyz);
    event->primaryVertexError().GetXYZ(xyzError);
    SetBestVx(xyz, xyzError);
  }
}
//_________________________________________________________________________________
#undef PrPP
#undef PrPT
