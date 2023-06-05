#ifndef __StPidStatus_h__
#define __StPidStatus_h__
#include "StEnumerations.h"
#include "StProbPidTraits.h"
#include "StBTofPidTraits.h"
#include "StETofPidTraits.h"
#include "StMtdPidTraits.h"
#include "StDedxPidTraits.h"
#include "StMuDSTMaker/COMMON/StMuTrack.h"
#include "StMuDSTMaker/COMMON/StMuBTofPidTraits.h"
#include "StMuDSTMaker/COMMON/StMuETofPidTraits.h"
#include "StMuDSTMaker/COMMON/StMuMtdPidTraits.h"
#ifdef __TFG__VERSION__
#include "StPicoEvent/StPicoTrack.h"
#include "StPicoEvent/StPicoBTofPidTraits.h"
#include "StPicoEvent/StPicoETofPidTraits.h"
#include "StPicoEvent/StPicoMtdPidTraits.h"
#endif /* __TFG__VERSION__ */
class StGlobalTrack;
class StTrackPiD {
 public:
 StTrackPiD() {Clear();}
  virtual ~StTrackPiD() {}
  void Clear() {memset(mBeg,0,mEnd-mBeg+1);}
  void Print(Option_t *option = "") const;
  Double_t Pull(Int_t k = 0)  {return devS[k];}
  Char_t                mBeg[1];                   //!
  Double_t Pred[KPidParticles];
  Double_t dev[KPidParticles];
  Double_t devS[KPidParticles];         // Pull
  Char_t                mEnd[1];        //!
};
class StdEdxStatus : public StTrackPiD {
 public:
 StdEdxStatus(StDedxPidTraits *pid = 0) : fPiD(pid) {Clear();}
  virtual ~StdEdxStatus() {}
  StDedxPidTraits *fPiD; //!
  Double_t I() const {return (fPiD) ? fPiD->mean() : 0;}
  Double_t D() const {return (fPiD) ? fPiD->errorOnMean() : 0;}
  Double_t TrackLength() const {return (fPiD) ? fPiD->length() : 0;}
  Double_t log2dX() const {return (fPiD) ? fPiD->log2dX() : 0;}
  Int_t    N() const {return (fPiD) ? fPiD->numberOfPoints() : 0;}
  void Print(Option_t *option = "") const;
};
class StBTofStatus  : public StTrackPiD {
 public:
  StBTofStatus(StBTofPidTraits *pid ) { fPiD = (TMath::Abs(pid->yLocal()) < 1.8) ? pid : 0;}
  virtual ~StBTofStatus() {}
  StBTofPidTraits *fPiD; //!
  StBTofPidTraits *PiD() {return fPiD;}
  Float_t beta() {return fPiD ? fPiD->beta() : -999;}
  Double_t Sigma(Int_t l) {
    if (fPiD) {
      switch (l) {
      case kPidElectron:
	return fPiD->sigmaElectron();
      case kPidProton:
	return fPiD->sigmaProton();
      case kPidKaon:
	return fPiD->sigmaKaon();
      case kPidPion:
	return fPiD->sigmaPion();
      default:
	return 999.;
      }
    }
    return 999.;
  }
};
class StETofStatus  : public StTrackPiD {
 public:
  StETofStatus(StETofPidTraits *pid = 0) { fPiD = (pid && pid->matchFlag()) ? pid : 0;}
  virtual ~StETofStatus() {}
  StETofPidTraits *PiD() {return fPiD;}
  StETofPidTraits *fPiD; //!
  Float_t beta() {return fPiD ? fPiD->beta() : -999;}
};
class StMtdStatus  : public StTrackPiD {
 public:
  StMtdStatus(StMtdPidTraits *pid = 0) { fPiD = (pid && pid->matchFlag()) ? pid : 0;}
  virtual ~StMtdStatus() {}
  StMtdPidTraits *PiD() {return fPiD;}
  StMtdPidTraits *fPiD; //!
  Float_t beta() {return fPiD ? fPiD->beta() : -999;}
};

class StPidStatus {
 public:
  enum PiDStatusIDs {
    kUndef = kUndefinedMethodId,
    kI70   = kTruncatedMeanId,        
    kI70U  = kEnsembleTruncatedMeanId,
    kFit   = kLikelihoodFitId,        
    kFitU  = kWeightedTruncatedMeanId,
    kdNdx  = kOtherMethodId,          
    kdNdxU = kOtherMethodId2,         
    kBTof,   kETof,   kMtd, kTotal
  };
  StPidStatus(StGlobalTrack *gTrack = 0, Bool_t Usedx2 = kTRUE);
  StPidStatus(StMuTrack *muTrack = 0, Bool_t Usedx2 = kTRUE, TVector3 *g3KFP = 0);
#ifdef __TFG__VERSION__
  StPidStatus(StPicoTrack *picoTrack = 0, Bool_t Usedx2 = kFALSE, TVector3 *g3KFP = 0);
#endif /* __TFG__VERSION__ */
  virtual ~StPidStatus() {
    for (Int_t k = kI70; k < kTotal; k++) {SafeDelete(fStatus[k]);}
    fProb = 0;
  }
  void Clear() {memset(mBeg,0,mEnd-mBeg+1);}
  Int_t Status() {return PiDStatus;}
  StdEdxStatus   *dEdxStatus(Int_t k) {return ( StdEdxStatus   *)  fStatus[k];}
  StBTofPidTraits SetBTofPidTraits(const StMuBTofPidTraits &pid);
  StETofPidTraits SetETofPidTraits(const StMuETofPidTraits &pid);
  StMtdPidTraits  SetMtdPidTraits(const StMuMtdPidTraits &pid);
#ifdef __TFG__VERSION__
  StBTofPidTraits SetBTofPidTraits(const StPicoBTofPidTraits &pid);
  StETofPidTraits SetETofPidTraits(const StPicoETofPidTraits &pid);
  StMtdPidTraits  SetMtdPidTraits(const StPicoMtdPidTraits &pid);
#endif /* __TFG__VERSION__ */
  void Set();
  
  Int_t        PiDStatus; //!
  void        Print(Option_t *option="") const;
  //  StGlobalTrack *gTrack; //!
  TVector3 g3; //!
  Bool_t fUsedx2;
  Char_t                mBeg[1];                   //!
  StTrackPiD *fStatus[kTotal];
  Double_t PredBMN[2], Pred70BMN[2]; //!
  Double_t bghyp[KPidParticles]; //! log10(bg)
  Double_t bgs[KPidParticles]; //! bg
  StProbPidTraits       *fProb;
  Char_t                mEnd[1];        //!
  StdEdxStatus    *fI70	   () {return (StdEdxStatus    *) fStatus[kI70  ];} 
  StdEdxStatus 	  *fFit    () {return (StdEdxStatus    *) fStatus[kFit  ];} 
  StdEdxStatus 	  *fI70U   () {return (StdEdxStatus    *) fStatus[kI70U ];}  
  StdEdxStatus 	  *fFitU   () {return (StdEdxStatus    *) fStatus[kFitU ];}  
  StdEdxStatus 	  *fdNdx   () {return (StdEdxStatus    *) fStatus[kdNdx ];}  
  StdEdxStatus 	  *fdNdxU  () {return (StdEdxStatus    *) fStatus[kdNdxU];}  
  StBTofStatus 	  *fBTof   () {return (StBTofStatus    *) fStatus[kBTof ];}  
  StETofStatus 	  *fETof   () {return (StETofStatus    *) fStatus[kETof ];}  
  StMtdStatus  	  *fMtd    () {return (StMtdStatus     *) fStatus[kMtd  ];} 
  static Double_t dEdxCorr(Double_t bgL10, Int_t code);
  static Double_t M2BTofCorr(Double_t pL10, Int_t code);
  static Double_t dEdxSigma(Double_t bgL10, Int_t code);
  static Double_t M2BTofSigma(Double_t pL10, Int_t code);
};

#endif 
