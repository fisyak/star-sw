#ifdef __TFG__VERSION__
#include "StPicoEvent/StPicoDst.h"
#endif /*  __TFG__VERSION__ */
#include "StPidStatus.h"
#include "StBichsel/Bichsel.h"
#include "StBichsel/StdEdxModel.h"
#include "StBichsel/StdEdxPull.h"
#include "StGlobalTrack.h"
#include "StTrackGeometry.h"

#include "TMath.h"
#include "TVector3.h"
//________________________________________________________________________________
StBTofPidTraits StPidStatus::SetBTofPidTraits(const StMuBTofPidTraits &pid) {
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
  btofPidTraits.setProbElectron (pid.probElectron()); 
  btofPidTraits.setProbPion     (pid.probPion()); 
  btofPidTraits.setProbKaon     (pid.probKaon()); 
  btofPidTraits.setProbProton   (pid.probProton());  
  return btofPidTraits;
}
#ifdef __TFG__VERSION__
//________________________________________________________________________________
StBTofPidTraits StPidStatus::SetBTofPidTraits(const StPicoBTofPidTraits &pid) {
  StBTofPidTraits btofPidTraits;
  btofPidTraits.setMatchFlag    (pid.btofMatchFlag());
  btofPidTraits.setYLocal       (pid.btofYLocal());
  btofPidTraits.setZLocal       (pid.btofZLocal());
  //  btofPidTraits.setThetaLocal   (pid.btofThetaLocal());
  btofPidTraits.setTimeOfFlight (pid.btof());
  //  btofPidTraits.setPathLength   (pid.btofPathLength());
  btofPidTraits.setBeta         (pid.btofBeta());
  btofPidTraits.setPosition     (StThreeVectorF(pid.btofHitPosX(),pid.btofHitPosY(),pid.btofHitPosZ()));
				      
  btofPidTraits.setSigmaElectron(pid.nSigmaElectron()); 
  btofPidTraits.setSigmaPion    (pid.nSigmaPion()); 
  btofPidTraits.setSigmaKaon    (pid.nSigmaKaon()); 
  btofPidTraits.setSigmaProton  (pid.nSigmaProton());  
  //  btofPidTraits.setProbElectron (pid.btofProbElectron()); 
  //  btofPidTraits.setProbPion     (pid.btofProbPion()); 
  //  btofPidTraits.setProbKaon     (pid.btofProbKaon()); 
  //  btofPidTraits.setProbProton   (pid.btofProbProton());  
  return btofPidTraits;
}
#endif /*  __TFG__VERSION__ */				      
//________________________________________________________________________________
StETofPidTraits StPidStatus::SetETofPidTraits(const StMuETofPidTraits &pid) {
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
StETofPidTraits StPidStatus::SetETofPidTraits(const StPicoETofPidTraits &pid) {
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
StMtdPidTraits StPidStatus::SetMtdPidTraits(const StPicoMtdPidTraits &pid) {
  StMtdPidTraits mtdPidTraits;
  mtdPidTraits.setMatchFlag      (pid.matchFlag());
//   mtdPidTraits.setYLocal         (pid.yLocal());
//   mtdPidTraits.setZLocal         (pid.zLocal());
  mtdPidTraits.setDeltaY         (pid.deltaY());
  mtdPidTraits.setDeltaZ         (pid.deltaZ());
  //  mtdPidTraits.setThetaLocal     (pid.thetaLocal());
  //  mtdPidTraits.setTimeOfFlight   (pid.timeOfFlight());
  //  mtdPidTraits.setExpTimeOfFlight(pid.expTimeOfFlight());
  //  mtdPidTraits.setPathLength     (pid.pathLength());
  mtdPidTraits.setBeta           (pid.beta());
  //  mtdPidTraits.setPosition       (pid.position());

  //  mtdPidTraits.setSigmaMuon      (pid.sigmaMuon()); 
  //  mtdPidTraits.setProbMuon       (pid.probMuon()); 
  return mtdPidTraits;
}
#endif /*  __TFG__VERSION__ */
//________________________________________________________________________________
StMtdPidTraits StPidStatus::SetMtdPidTraits(const StMuMtdPidTraits &pid) {
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
//________________________________________________________________________________
StPidStatus::StPidStatus(StGlobalTrack *gTrack, Bool_t Usedx2) : PiDStatus(-1), fUsedx2(Usedx2) {// , gTrack(Track) {
  Clear();
  if (! gTrack) return;
  g3 = TVector3(gTrack->geometry()->momentum().xyz()); // p of global track
  StSPtrVecTrackPidTraits &traits = gTrack->pidTraits();
  if (! traits.size()) return;
  for (UInt_t i = 0; i < traits.size(); i++) {
    StTrackPidTraits *trait = traits[i];
    if (! trait) continue;
    if ( trait->IsZombie()) continue;
    Short_t id = trait->detector()%100;
    if (id == kBTofId) {
      StBTofPidTraits* pid = dynamic_cast<StBTofPidTraits*>(trait);
      if (! pid) continue;
      if (TMath::Abs(pid->yLocal()) < 1.8) fStatus[kBTof] = new StBTofStatus(pid);
    } else if (id == kETofId) {
      StETofPidTraits* pid = dynamic_cast<StETofPidTraits*>(trait);
      if (! pid) continue;
      fStatus[kETof] = new StETofStatus(pid);
    } else if (id == kMtdId) {
      StMtdPidTraits* pid = dynamic_cast<StMtdPidTraits*>(trait);
      if (! pid) continue;
      fStatus[kMtd] = new StMtdStatus(pid);
    } else if (id == kTpcId) {
      StDedxPidTraits* pid = dynamic_cast<StDedxPidTraits*>(trait);
      if (pid) {
	switch (pid->method()) {
	case kTruncatedMeanId: fStatus[kI70] = new StdEdxStatus(pid); break;
	case kLikelihoodFitId: fStatus[kFit] = new StdEdxStatus(pid); break;
	case kEnsembleTruncatedMeanId: fStatus[kI70U] = new StdEdxStatus(pid); break;// == kTruncatedMeanId+1 uncorrected
	case kWeightedTruncatedMeanId: fStatus[kFitU] = new StdEdxStatus(pid); break;  // == kLikelihoodFitId+1; uncorrected
	case kOtherMethodId:           fStatus[kdNdx] = new StdEdxStatus(pid); break;
	case kOtherMethodId2:          fStatus[kdNdxU] = new StdEdxStatus(pid); break;
	default: break;
	}
      } else {
	StProbPidTraits *pidprob = dynamic_cast<StProbPidTraits*>(trait);
	if (pidprob) fProb = pidprob;
      }
    }
  }
  Set();
}
//________________________________________________________________________________
StPidStatus::StPidStatus(StMuTrack *muTrack, Bool_t Usedx2, TVector3 *g3KFP) : PiDStatus(-1), fUsedx2(Usedx2) {
  Clear();
  if (! muTrack) return;
  const StMuProbPidTraits &probPidTraits = muTrack->probPidTraits();
  const StMuBTofPidTraits &btofPidTraits = muTrack->btofPidTraits();
  const StMuETofPidTraits &etofPidTraits = muTrack->etofPidTraits();
  const StMuMtdPidTraits  &mtdPidTraits = muTrack->mtdPidTraits();
  if (! g3KFP) 
    g3 = TVector3(muTrack->p().xyz()); // p of global track
  else 
    g3 = *g3KFP;
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
    pidI70 = StDedxPidTraits(kTpcId, kTruncatedMeanId, 100*((UShort_t)probPidTraits.dEdxTrackLength()) + muTrack->nHitsDedx(), 
			     probPidTraits.dEdxTruncated(), probPidTraits.dEdxErrorTruncated(),probPidTraits.log2dX());
    fStatus[kI70] = new StdEdxStatus(&pidI70);
  } 
  if (probPidTraits.dEdxFit() > 0) {
    pidFit = StDedxPidTraits(kTpcId, kLikelihoodFitId, 100*((UShort_t)probPidTraits.dEdxTrackLength()) + muTrack->nHitsDedx(), 
			     probPidTraits.dEdxFit(), probPidTraits.dEdxErrorFit(),probPidTraits.log2dX());
    fStatus[kFit] = new StdEdxStatus(&pidFit);
  }
  if (probPidTraits.dNdxFit() > 0) {
    pidNdx = StDedxPidTraits(kTpcId, kOtherMethodId, 100*((UShort_t)probPidTraits.dEdxTrackLength()) + muTrack->nHitsDedx(), 
			     probPidTraits.dNdxFit(), probPidTraits.dNdxErrorFit(),probPidTraits.log2dX());
    fStatus[kdNdx] = new StdEdxStatus(&pidNdx);
  }
  if (btofPidTraits.matchFlag()) {
    static StBTofPidTraits btof;
    btof= SetBTofPidTraits(muTrack->btofPidTraits());
    fStatus[kBTof] = new StBTofStatus(&btof);
  }
  if (etofPidTraits.matchFlag()) {
    static StETofPidTraits etof;
    etof = SetETofPidTraits(muTrack->etofPidTraits());
    fStatus[kETof] = new StETofStatus(&etof);
  }
  if (mtdPidTraits.matchFlag()) {
    StMtdPidTraits mtd;
    mtd = SetMtdPidTraits(muTrack->mtdPidTraits());
    fStatus[kMtd] = new StMtdStatus(&mtd);
  }

  Set();
}
#ifdef __TFG__VERSION__
//________________________________________________________________________________
StPidStatus::StPidStatus(StPicoTrack *picoTrack, Bool_t Usedx2, TVector3 *g3KFP) : PiDStatus(-1), fUsedx2(Usedx2) {
  Clear();
  if (! picoTrack) return;
  if (! g3KFP) {
    g3 = picoTrack->gMom();
  } else {
    g3 = *g3KFP;
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
  if (picoTrack->dEdx() > 0) {
#if 0 /* no I70 on picoDst */
    pidI70 = StDedxPidTraits(kTpcId, kTruncatedMeanId, picoTrack->nHitsDedx(), 
			     1e-6*picoTrack->dEdx(), picoTrack->dEdxError());
    fStatus[kI70] = new StdEdxStatus(&pidI70);
#endif
    pidFit = StDedxPidTraits(kTpcId, kLikelihoodFitId, picoTrack->nHitsDedx(), 
			     1e-6*picoTrack->dEdx(), picoTrack->dEdxError());
    fStatus[kFit] = new StdEdxStatus(&pidFit);
  }
  if (picoTrack->dNdx() > 0) {
    pidNdx = StDedxPidTraits(kTpcId, kOtherMethodId, picoTrack->nHitsDedx(),
			     picoTrack->dNdx(), picoTrack->dNdxError());
    fStatus[kdNdx] = new StdEdxStatus(&pidNdx);
  }
  Int_t ibtof = picoTrack->bTofPidTraitsIndex();
  if (ibtof >= 0) {
    static StBTofPidTraits pidBTof;
    pidBTof = SetBTofPidTraits(*StPicoDst::instance()->btofPidTraits(ibtof));
    fStatus[kBTof] = new StBTofStatus(&pidBTof);
  }
  Int_t ietof = picoTrack->eTofPidTraitsIndex();
  if (ietof >= 0) {
    static StETofPidTraits pidETof;
    pidETof = SetETofPidTraits(*StPicoDst::instance()->etofPidTraits(ietof));
    fStatus[kETof] = new StETofStatus(&pidETof);
  }
  Int_t imtd = picoTrack->mtdPidTraitsIndex();
  if (imtd >= 0) {
    static StMtdPidTraits pidMtd;
    pidMtd = SetMtdPidTraits(*StPicoDst::instance()->mtdPidTraits(imtd));
    fStatus[kMtd] = new StMtdStatus(&pidMtd);
  }

  Set();
}
#endif /* __TFG__VERSION__ */
//________________________________________________________________________________
void StPidStatus::Set() {
  struct Particle_t {
    Int_t pdg;
    const Char_t *name;
    Double_t mass;
    Int_t charge;
    Int_t code;
  };
  enum {Nparticles = 18, NparticlesA = 10,  Ndecays = 4};
  static Particle_t particles[34] = {
    {         11,  "e-",   0.51099907e-3, -1,  kPidElectron},  
    { 	     -11,  "e+",   0.51099907e-3,  1,  kPidElectron},  
    { 	      13,  "mu-",  0.1056584,     -1,  kPidMuon},        
    { 	     -13,  "mu+",  0.1056584,      1,  kPidMuon},        
    {        211,  "pi+",  0.13956995,     1,  kPidPion},        
    { 	    -211,  "pi-",  0.13956995,    -1,  kPidPion},        
    { 	     321,  "K+",   0.493677,       1,  kPidKaon},        
    { 	    -321,  "K-",   0.493677,       1,  kPidKaon},        
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
    {-1000040100,  "Be10-",9.3275,         4,  kPidBe10},	 
    { 1000050110,  "B11", 10.2666,         5,  kPidB11},	 
    {-1000050110,  "B11-",10.2666,         5,  kPidB11}
  };
  static Int_t l2p[KPidParticles] = {0};
  if (! l2p[3]) {
    for (Int_t l = kPidElectron; l < KPidParticles; l++) {
      for (Int_t p = 0; p < 34; p++) {
	if (particles[p].code == l) {
	  l2p[l] = p;
	  break;
	}
      }
    }
  }
  if (! fStatus[kI70] && ! fStatus[kFit] && ! fStatus[kdNdx]) return;
  PiDStatus = 0;
  Double_t pMomentum = g3.Mag();
  Double_t pL10 = TMath::Log10(pMomentum);
  Double_t p2 = pMomentum*pMomentum;
  //  Double_t bg = TMath::Log10(pMomentum/StProbPidTraits::mPidParticleDefinitions[kPidPion]->mass());
  PredBMN[0] = Pred70BMN[0] =  1;
  PredBMN[1] = Pred70BMN[1] = -1;
  // Set up Tof
  Double_t sigmaCor = 1;
  Float_t betaTof = -999;
  Double_t sigmaInvBeta = -999;
  Double_t sigmaTof = -999;
  if (fBTof() || fETof()) {
    Int_t l = kPidProton;
    Int_t p = l2p[l];
    Double_t mass = particles[p].mass;
    Double_t bg = pMomentum/mass; 
    Double_t b_P = bg/TMath::Sqrt(1. + bg*bg);
    // sigmaTof = dBeta/sigmaInvBeta
    
    if (fBTof()) {
      betaTof = fBTof()->beta();
      sigmaTof = fBTof()->Sigma(l);
    } else if (fETof()) {
      betaTof = fETof()->beta();
      //      sigmaTof = fETof()->Sigma(l);
    }
    if (betaTof > 0 && betaTof < 2) {
      sigmaInvBeta = 1e-7;
      Double_t dBeta = (1./betaTof - 1/b_P);
      if (TMath::Abs(dBeta) < 5e-5) dBeta = 5e-5;
      if (TMath::Abs(sigmaTof) > 1e-7)    sigmaInvBeta = dBeta / sigmaTof;
    }
  }
  for (Int_t l = kPidElectron; l < KPidParticles; l++) {
    Int_t p = l2p[l];
#if 0    
    Int_t charge = StProbPidTraits::mPidParticleDefinitions[l]->charge();
    Double_t mass   = StProbPidTraits::mPidParticleDefinitions[l]->mass();
#else
    Int_t charge  = particles[p].charge;
    Double_t mass = particles[p].mass;
#endif
    Double_t M2 = mass*mass;
    Double_t betagamma = pMomentum*TMath::Abs(charge)/mass;
    Double_t beta = betagamma/TMath::Sqrt(1. + betagamma*betagamma);
    bgs[l] = betagamma;
    bghyp[l] = TMath::Log10(bgs[l]);
    for (Int_t k = kI70; k <= kOtherMethodId2; k++) {
      if (! fStatus[k]) continue;
      UChar_t fit = 0;
      if (k == kLikelihoodFitId || k == kWeightedTruncatedMeanId) fit = 1;
      else if (k == kOtherMethodId || k == kOtherMethodId2) fit = 2;
      if (fUsedx2) 
	fStatus[k]->Pred[l] = StdEdxPull::EvalPred2(betagamma, dEdxStatus(k)->log2dX(), fit, charge);
      else {
	fStatus[k]->Pred[l] = StdEdxPull::EvalPred(betagamma, fit, charge, mass, &sigmaCor) * dEdxCorr(bghyp[l], l);
      }
      if (dEdxStatus(k)->I() > 0) {
	fStatus[k]->dev[l] = TMath::Log(dEdxStatus(k)->I()/fStatus[k]->Pred[l]);
	fStatus[k]->devS[l] = -999;
	if (dEdxStatus(k)->D() > 0) {
	  fStatus[k]->devS[l] = fStatus[k]->dev[l]/(dEdxStatus(k)->D()*sigmaCor);
	}
      }
      if (fStatus[k]->Pred[l] < PredBMN[0]) PredBMN[0] = fStatus[k]->Pred[l];
      if (fStatus[k]->Pred[l] > PredBMN[1]) PredBMN[1] = fStatus[k]->Pred[l];
    }
    // ToF
     for (Int_t k = kBTof; k <= kETof; k++) {
      if (! fStatus[k]) continue;
      if (betaTof > 0 && betaTof < 2) {
	Double_t sigmadM2 = -999;
	Double_t dM2 = p2*(1./(betaTof*betaTof) - 1.) - M2;
	dM2 -= M2BTofCorr(pL10, l);
	fStatus[k]->dev[l] = dM2;
	if (l == kPidElectron || l == kPidPion || l == kPidProton) {
	  sigmadM2 = M2BTofSigma(pL10, l);
	} else {
	  sigmadM2 = 2*p2/beta*sigmaInvBeta;
	}
	if (sigmadM2 > 0) fStatus[k]->devS[l] = fStatus[k]->dev[l]/sigmadM2;
      }
    }
  }
}
//________________________________________________________________________________
void StPidStatus::Print(Option_t *opt) const {
  for (Int_t k = 1; k <= kOtherMethodId2; k++) {
    if (! fStatus[k]) continue;
    if      (k == kUndefinedMethodId)         cout << "UndefinedMethod       ";
    else if (k == kTruncatedMeanId)           cout << "TruncatedMean         ";
    else if (k == kEnsembleTruncatedMeanId)   cout << "EnsembleTruncatedMean ";
    else if (k == kLikelihoodFitId)           cout << "LikelihoodFit         ";
    else if (k == kWeightedTruncatedMeanId)   cout << "WeightedTruncatedMean ";
    else if (k == kOtherMethodId)             cout << "OtherMethod           "; 
    else if (k == kOtherMethodId2)            cout << "OtherMethodIdentifier2";
    fStatus[k]->Print();
  }
}
//________________________________________________________________________________
void StdEdxStatus::Print(Option_t *option) const {
  if (! fPiD) {cout << "\tEmpty" << endl;}
  else {
    static Double_t scale = 1;
    if (I() < 10) cout << "\tI = " << scale*I() << "keV";
    else          cout << "\tI = " << I();
    cout << " +/- " << 100*D() << "%";
    StTrackPiD::Print(option);
  }
}
//________________________________________________________________________________
void StTrackPiD::Print(Option_t *option) const {
  static Double_t scale = 1;
  cout << "\tPred: ";
  for (Int_t l = kPidElectron; l <= kPidPion; l++) {cout << "\t" << scale*Pred[l];}
  cout << "\tdev:";
  for (Int_t l = kPidElectron; l <= kPidPion; l++) {cout << "\t" << dev[l];}
  cout << "\tdevS:";
  for (Int_t l = kPidElectron; l <= kPidPion; l++) {cout << "\t" << devS[l];}
  cout << endl;
}
//________________________________________________________________________________
Double_t StPidStatus::dEdxCorr(Double_t bgL10, Int_t code)  {
  Double_t CorrL = 0;
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
      CorrL = E1->Eval(bg10);
    } else {
      static TF1 *E2 = 0;
      if (! E2) {
	Double_t pars[7] = {-0.3267676,   0.476879, -0.3152098, 0.01623315, 0.06886368, -0.02498914, 0.002566173}; //electrons [2,5,3.8]
	E2 = new TF1("dEdxE2","pol6",2.50,3.80);
	E2->SetParameters(pars);
      }
      CorrL = E2->Eval(bg10);
    }
  } else if (code == kPidPion) {
    if (bgL10 < -0.25) bg10 = 0.25;
    if (bgL10 < 0.05) {
      static TF1 *Pi1 = 0;
      if (! Pi1) {
	Double_t pars[5] = {-0.0116273, 0.05124145, -0.9784855,  -10.31482,    -2.1687}; //pi [-0.25,0.05]
	Pi1 = new TF1("dEdxPi1","pol4",-0.25,0.05);
	Pi1->SetParameters(pars);
      }
      CorrL = Pi1->Eval(bg10);
    } else if (bgL10 < 0.55) {
      static TF1 *Pi2 = 0;
      if (! Pi2) {
	Double_t pars[5] = {-0.0007022319, -0.3074184,   1.313129,  -1.709188,  0.6149398}; //pi [0.02,0.55]
	Pi2 = new TF1("dEdxPi2","pol4",0.02,0.55);
	Pi2->SetParameters(pars);
      }
      CorrL = Pi2->Eval(bg10);
    } else {
      static TF1 *Pi3 = 0;
      if (! Pi3) {
	Double_t pars[7] = {-0.8277655,   5.488526,  -14.61932,   19.99763,  -14.81849,   5.647092,  -0.866685}; //pi [0.50,1.80]
	Pi3 = new TF1("dEdxPi3","pol6",0.50,1.80);
	Pi3->SetParameters(pars);
      }
      if (bgL10 > 1.7) bg10 = 1.7;
      CorrL = Pi3->Eval(bg10);
    }
  } else if (code == kPidProton) {
    if (bgL10 < -0.8) bg10 = -0.8;
    if (bgL10 >  0.8) bg10 =  0.8;
    static TF1 *Proton1 = 0;
    if (! Proton1) {
      Double_t pars[10] = {0.0007210231, -0.01249025,   0.208259, -0.2458525, -0.5773149,  0.5679841,   1.433286,  -1.169037,  -1.628503,   1.460514}; //P [-0.80,0.80]
      Proton1 = new TF1("dEdxProton1","pol9",-0.80,0.80);
      Proton1->SetParameters(pars);
    }
    CorrL = Proton1->Eval(bg10);
  }
  return TMath::Exp(CorrL);
}
//________________________________________________________________________________
Double_t StPidStatus::M2BTofCorr(Double_t pL10, Int_t code)  {
  Double_t Corr = 0;
  Double_t p10 = pL10;
  if (code == kPidElectron) {
    static TF1 *E1 = 0;
    if (! E1) {
    //Double_t pars[5] = { 0.01265596, -0.02078762, -0.04596959, -0.04943213, -0.02199248}; //e
      Double_t pars[5] = {-0.00352904, -0.02078762, -0.04596959, -0.04943213, -0.02199248}; //e
      E1 = new TF1("M2BTofE1","pol4",-0.85,0.28);
      E1->SetParameters(pars);
    }
    Corr = E1->Eval(p10);
  } else if (code == kPidPion) {
    static TF1 *Pion1 = 0;
    if (! Pion1) {
      Double_t pars[8] = {0.005495614, 0.00672486, -0.001912834, -0.01906281, -0.07363129,   -0.20461, -0.2838375,  -0.144034}; //pion
      Pion1 = new TF1("M2BTofPion1","pol7",-0.90,0.60);
      Pion1->SetParameters(pars);
    }
    Corr = Pion1->Eval(p10);
  } else if (code == kPidProton) {
    static TF1 *Proton1 = 0;
    if (! Proton1) {
      //      Double_t pars[2] = {0.01191059, 0.02612714}; //proton
      Double_t pars[2] = {-0.004274406, 0.02612714}; //proton
      Proton1 = new TF1("M2BTofProton1","pol1",-0.50,0.50);
      Proton1->SetParameters(pars);
    }
    Corr = Proton1->Eval(p10);
  }
  return Corr;
}
//________________________________________________________________________________
Double_t StPidStatus::dEdxSigma(Double_t bgL10, Int_t code)  {
  return 1;
}
//________________________________________________________________________________
Double_t StPidStatus::M2BTofSigma(Double_t pL10, Int_t code)  {
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
  } else if (code == kPidPion) {
    static TF1 *Pion1 = 0;
    if (! Pion1) {
      Double_t pars[2] = { -4.011896,   3.862085}; //pion
      Pion1 = new TF1("M2BTofSigmaPion1","expo",-0.90,0.60);
      Pion1->SetParameters(pars);
    }
    sigma = Pion1->Eval(p10);
  } else if (code == kPidProton) {
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
