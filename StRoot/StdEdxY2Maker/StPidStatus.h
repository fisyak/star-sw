#ifndef __StPidStatus_h__
#define __StPidStatus_h__
#include <vector>
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
#include "StPicoEvent/StPicoBEmcPidTraits.h"
#endif /* __TFG__VERSION__ */
class StGlobalTrack;
//________________________________________________________________________________
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
  Double_t PullC[KPidParticles];        // Pull Corrected
  Char_t                mEnd[1];        //!
};
//________________________________________________________________________________
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
//________________________________________________________________________________
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
//________________________________________________________________________________
class StETofStatus  : public StTrackPiD {
 public:
  StETofStatus(StETofPidTraits *pid = 0) { fPiD = (pid && pid->matchFlag()) ? pid : 0;}
  virtual ~StETofStatus() {}
  StETofPidTraits *PiD() {return fPiD;}
  StETofPidTraits *fPiD; //!
  Float_t beta() {return fPiD ? fPiD->beta() : -999;}
};
//________________________________________________________________________________
class StMtdStatus  : public StTrackPiD {
 public:
  StMtdStatus(StMtdPidTraits *pid = 0) { fPiD = (pid && pid->matchFlag()) ? pid : 0;}
  virtual ~StMtdStatus() {}
  StMtdPidTraits *PiD() {return fPiD;}
  StMtdPidTraits *fPiD; //!
  Float_t beta() {return fPiD ? fPiD->beta() : -999;}
};
//________________________________________________________________________________
class StBEmcStatus  : public StTrackPiD {
 public:
 StBEmcStatus(StPicoBEmcPidTraits *pid = 0) : StTrackPiD(), fPiD(pid) {}
  virtual ~StBEmcStatus() {}
  StPicoBEmcPidTraits *PiD() {return fPiD;}
  StPicoBEmcPidTraits *fPiD; //!
};
//________________________________________________________________________________
struct Particle_t {
  Int_t pdg;
  const Char_t *name;
  Double_t mass;
  Int_t charge;
  Int_t code;
};
//________________________________________________________________________________
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
    kBTof,   kETof,   kMtd, kBEmc, kTotal
  };
  enum {Nparticles = 18, NparticlesA = 10,  Ndecays = 4};
    StPidStatus(StGlobalTrack *gTrack = 0);
  StPidStatus(StMuTrack *muTrack = 0, TVector3 *g3KFP = 0);
#ifdef __TFG__VERSION__
  StPidStatus(StPicoTrack *picoTrack = 0, TVector3 *g3KFP = 0);
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
  StBTofPidTraits SetBTofPidTraits(const StPicoBTofPidTraits &pid, StPicoTrack *gTrack = 0);
  StETofPidTraits SetETofPidTraits(const StPicoETofPidTraits &pid);
  StMtdPidTraits  SetMtdPidTraits(const StPicoMtdPidTraits &pid);
  StPicoBEmcPidTraits  SetBEmcPidTraits(const StPicoBEmcPidTraits &pid);
#endif /* __TFG__VERSION__ */
  void Set();
  const std::vector<Int_t> &GetPDG()        {return *&fPDGList;}
  const std::vector<Int_t> &GetPDGfromTPC() {return *&fTPCPDG;}
  const std::vector<Int_t> &GetPDGfromTof() {return *&fTofPDG;}
  void SetPDG();
  void SetPDGfromTPC();
  void SetPDGfromTof();
  static void SetUsedx2(Bool_t k = kTRUE) {fgUsedx2 = k;}
  static void SetUseTof(Bool_t k = kTRUE) {fgUseTof = k;}
  Int_t       PiDStatus; //!
  void        Print(Option_t *option="") const;
  //  StGlobalTrack *gTrack; //!
  TVector3 g3; //!
  Int_t    fQ; // charge
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
  StBEmcStatus    *fBEmc    () {return (StBEmcStatus     *) fStatus[kBEmc  ];} 
  static Double_t  dEdxCorr(Double_t bgL10, Int_t code);
  static Double_t  dEdxSigma(Double_t bgL10, Int_t code);
  static Double_t  dEdxPullCorrection(Double_t pull, Double_t bgL10, Int_t code);
  static Double_t  M2BTofCorr(Double_t pL10, Int_t code);
  static Double_t  M2BTofSigma(Double_t pL10, Int_t code);
  static Double_t  fgSigmaCut;
  static Int_t     fgl2p[KPidParticles];
  static Particle_t fgParticles[34];
 private:
  std::vector<Int_t> fTPCPDG;
  std::vector<Int_t> fTofPDG;
  std::vector<Int_t> fPDGList;
  static Bool_t fgUsedx2;
  static Bool_t fgUseTof;
};

#endif 
