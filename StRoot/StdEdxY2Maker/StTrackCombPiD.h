#ifndef __StTrackCombPiD_h__
#define __StTrackCombPiD_h__
#include <vector>
#include "StEnumerations.h"
#include "StProbPidTraits.h"
#include "StBTofPidTraits.h"
#include "StETofPidTraits.h"
#include "StMtdPidTraits.h"
#include "StDedxPidTraits.h"
#include "StPidParticleDefinition.h"
#include "StMuDSTMaker/COMMON/StMuDst.h"
#include "StMuDSTMaker/COMMON/StMuTrack.h"
#include "StMuDSTMaker/COMMON/StMuBTofPidTraits.h"
#include "StMuDSTMaker/COMMON/StMuETofPidTraits.h"
#include "StMuDSTMaker/COMMON/StMuMtdPidTraits.h"
#ifdef __TFG__VERSION__
#include "StPicoEvent/StPicoDst.h"
#include "StPicoEvent/StPicoTrack.h"
#include "StPicoEvent/StPicoBTofPidTraits.h"
#include "StPicoEvent/StPicoETofPidTraits.h"
#include "StPicoEvent/StPicoMtdPidTraits.h"
#include "StPicoEvent/StPicoBEmcPidTraits.h"
#include "KFParticle/KFVertex.h"
#endif /* __TFG__VERSION__ */
class StGlobalTrack;
//________________________________________________________________________________
class StTrackPiD {
 public:
 StTrackPiD() {Clear();}
  virtual ~StTrackPiD() {}
  void Clear() {memset(mBeg,0,mEnd-mBeg+1); for (Int_t l = 0; l < KPidAllParticles; l++) fPred[l] = fPredC[l] = fdev[l] = fPull[l] = fPullC[l] = -999;}
  void Print(Option_t *option = "") const;
  Double_t pred(Int_t  k = 0)       const {return fPred[k];}
  double_t residual(Int_t   k = 0)  const {return fdev[k];}
  double_t pull(Int_t  k = 0)       const {return fPull[k];}
  double_t predC(Int_t k = 0)       const {return fPredC[k];}
  double_t residualC(Int_t  k = 0)  const {return fdevC[k];}
  double_t pullC(Int_t k = 0)       const {return fPullC[k];}
  Double_t &Pred(Int_t  k = 0)       {return fPred[k];}
  Double_t &Residual(Int_t   k = 0)  {return fdev[k];}
  Double_t &Pull(Int_t  k = 0)       {return fPull[k];}
  Double_t &PredC(Int_t k = 0)       {return fPredC[k];}
  Double_t &ResidualC(Int_t  k = 0)  {return fdevC[k];}
  Double_t &PullC(Int_t k = 0)       {return fPullC[k];}
 private:
  Char_t                  mBeg[1];                   //!
  Double_t fPred[KPidAllParticles];
  Double_t fPredC[KPidAllParticles];
  Double_t fdev[KPidAllParticles];          // residual
  Double_t fdevC[KPidAllParticles];         // residual wrt PredC
  Double_t fPull[KPidAllParticles];         // Pull
  Double_t fPullC[KPidAllParticles];        // Pull Corrected
  Char_t                   mEnd[1];        //!
};
//________________________________________________________________________________
class StdEdxStatus : public StTrackPiD {
 public:
  StdEdxStatus(StDedxPidTraits *pid = 0) : fPiD(pid) {}
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
  StBTofStatus(StBTofPidTraits *pid = 0);
  virtual ~StBTofStatus() {}
  StBTofPidTraits *fPiD; //
  StBTofPidTraits *PiD() const  {return fPiD;}
  Float_t beta() const {return fPiD ? fPiD->beta() : -999;}
  Double_t fBetaV; // Inverse beta measured
  Double_t fSigmaBetaV; // Estimated errors in BetaV
  Double_t Sigma(Int_t l) const {
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
  StETofPidTraits *PiD() const  {return fPiD;}
  StETofPidTraits *fPiD; //!
  Float_t beta() const {return fPiD ? fPiD->beta() : -999;}
};
//________________________________________________________________________________
class StMtdStatus  : public StTrackPiD {
 public:
  StMtdStatus(StMtdPidTraits *pid = 0) { fPiD = (pid && pid->matchFlag()) ? pid : 0;}
  virtual ~StMtdStatus() {}
  StMtdPidTraits *PiD() const  {return fPiD;}
  StMtdPidTraits *fPiD; //!
  Float_t beta()              const {return fPiD ? fPiD->beta() : -999;}
  Float_t deltaTimeOfFlight() const {return fPiD->timeOfFlight() - fPiD->expTimeOfFlight();}
};
//________________________________________________________________________________
class StBEmcStatus  : public StTrackPiD {
 public:
 StBEmcStatus(StPicoBEmcPidTraits *pid = 0) : StTrackPiD(), fPiD(pid) {}
  virtual ~StBEmcStatus() {}
  StPicoBEmcPidTraits *PiD() const  {return fPiD;}
  StPicoBEmcPidTraits *fPiD; //!
  Double_t bemcE() {return fPiD->bemcE();}
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
class StTrackCombPiD {
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
  StTrackCombPiD();
  StTrackCombPiD(StGlobalTrack *gTrack, StVertex *bestVx = 0);
  StTrackCombPiD(StMuTrack *muTrack, TVector3 *g3KFP = 0, StMuPrimaryVertex *bestVx = 0);
  StTrackCombPiD(StMuDst *muDst, Int_t iTrack);
#ifdef __TFG__VERSION__
  StTrackCombPiD(StPicoTrack *picoTrack, TVector3 *g3KFP = 0, TVector3 *bestVx = 0);
  StTrackCombPiD(StPicoDst *picoDst, Int_t iTrack);
#endif /* __TFG__VERSION__ */
  virtual ~StTrackCombPiD() {
    for (Int_t k = kI70; k < kTotal; k++) {SafeDelete(fStatus[k]);}
    fProb = 0;
  }
  void Clear() {memset(mBeg,0,mEnd-mBeg+1);}
  Int_t Status() {return fPiDStatus;}
  StTrackPiD     *Status(Int_t k) {return fStatus[k];}
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
  static void SetNparticles(Int_t k = KPidAllParticles) {fgNparticles = k;}
  static Int_t Nparticles() {return fgNparticles;}
  Double_t bghyp(Int_t l) {return fbghyp[l];}
  Double_t pMomentum() {return fg3.Mag();}
  // ________________________________________________________________________________
  void        Print(Option_t *option="") const;
  const StdEdxStatus    *fI70	 () const  {return (const StdEdxStatus    *) fStatus[kI70  ];} 
  const StdEdxStatus 	*fFit    () const  {return (const StdEdxStatus    *) fStatus[kFit  ];} 
  const StdEdxStatus 	*fI70U   () const  {return (const StdEdxStatus    *) fStatus[kI70U ];}  
  const StdEdxStatus 	*fFitU   () const  {return (const StdEdxStatus    *) fStatus[kFitU ];}  
  const StdEdxStatus 	*fdNdx   () const  {return (const StdEdxStatus    *) fStatus[kdNdx ];}  
  const StdEdxStatus 	*fdNdxU  () const  {return (const StdEdxStatus    *) fStatus[kdNdxU];}  
  const StBTofStatus 	*fBTof   () const  {return (const StBTofStatus    *) fStatus[kBTof ];}  
  const StETofStatus 	*fETof   () const  {return (const StETofStatus    *) fStatus[kETof ];}  
  const StMtdStatus  	*fMtd    () const  {return (const StMtdStatus     *) fStatus[kMtd  ];} 
  const StBEmcStatus    *fBEmc   () const  {return (const StBEmcStatus     *) fStatus[kBEmc  ];} 
  static Double_t  dEdxCorr(Double_t bgL10, Int_t code);
  static Double_t  dEdxPullCorrection(Double_t pull, Double_t bgL10, Int_t code);
  static Double_t  M2BTofCorr(Double_t pL10, Int_t code);
  static Double_t  M2BTofSigma(Double_t pL10, Int_t code);
  static Double_t  fgSigmaCut;
  static Int_t     fgl2p[KPidAllParticles];
  static Particle_t fgParticles[34];
  static const Char_t *fgPiDStatusNames[kTotal+1];
  static Particle_t &l2par(Int_t l) {return *&fgParticles[fgl2p[l]];}
  static const KFVertex &BestVX() {return fgBestVx;}
  static void SetBestVx(const Float_t xyz[3], const Float_t xyzErrors[3]);
  static void SetBestVx(const Double_t xyz[3], const Double_t xyzErrors[3]);
  static void SetBestVxCov(const Float_t xyz[3], const Float_t covVx[6]);
  static void SetBestVx(const StVertex *bestVx);
  static void SetBestVx(const StMuPrimaryVertex *bestVx);
  static void SetBestVx(const StPicoEvent *event);
  static void ResetSetBestVx() {fgBestVx.SetId(0);}
 private:
  std::vector<Int_t> fTPCPDG;
  std::vector<Int_t> fTofPDG;
  std::vector<Int_t> fPDGList;
  static Bool_t fgUsedx2;
  static Bool_t fgUseTof;
  static Int_t  fgDebug;
  static Int_t  fgNparticles;
  static KFVertex fgBestVx;
  Char_t           mBeg[1];                   //!
  Int_t            fPiDStatus; //
  Int_t            fQ; // charge
  StTrackPiD      *fStatus[kTotal];
  Double_t         fbghyp[kTotal]; //! log10(bg)
  Double_t         fbgs[kTotal]; //! bg
  StProbPidTraits *fProb;
  Char_t            mEnd[1];        //!
  TVector3 fg3; //!
};

#endif 