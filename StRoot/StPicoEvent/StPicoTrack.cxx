//
// StPicoTrack holds information about the reconstructed tracks
//

// C+++ headers
#include <limits>

// ROOT headers
#include "TMath.h"

// PicoDst headers
#include "StPicoMessMgr.h"
#include "StPicoTrack.h"
#if defined(__TFG__VERSION__)
#include "StPicoDst.h"
#include "TMath.h"
#include "TF1.h"
#include "StMuDSTMaker/COMMON/StMuTrack.h"
#include "StBichsel/Bichsel.h"
#include "StBichsel/StdEdxModel.h"
#include "StBichsel/StdEdxPull.h"
#include "StEvent/StMassFit.h"
Int_t StPicoTrack::fgdEdXMode = 1;
Float_t StPicoTrack::fgdEdxErrorScale = 1;
#endif /* __TFG__VERSION__ */

ClassImp(StPicoTrack)

//_________________
StPicoTrack::StPicoTrack() : TObject(),
  mId(0), 
#if defined (__TFG__VERSION__)
  mFlagExtension(0),
#endif
  mChi2(std::numeric_limits<unsigned short>::max()),
  mPMomentumX(0), mPMomentumY(0), mPMomentumZ(0),
  mGMomentumX(0), mGMomentumY(0), mGMomentumZ(0),
  mOriginX(0),mOriginY(0), mOriginZ(0),
  mDedx(0), mDedxError(0),
  mDnDx(0),mDnDxError(0),
  mNHitsFit(0), mNHitsMax(0), mNHitsDedx(0),
  mNSigmaPion( std::numeric_limits<short>::min() ),
  mNSigmaKaon( std::numeric_limits<short>::min() ),
  mNSigmaProton( std::numeric_limits<short>::min() ),
  mNSigmaElectron( std::numeric_limits<short>::min() ),
  mTopologyMap{}, mBEmcPidTraitsIndex(-1), mBTofPidTraitsIndex(-1),
  mMtdPidTraitsIndex(-1), mETofPidTraitsIndex(-1),
  mBEmcMatchedTowerIndex(-1)
#if !defined (__TFG__VERSION__)
  , mTopoMap_iTpc(0)
#else
  , mpIn(0)
#endif
  , mIdTruth(0), mQATruth(0), mVertexIndex(-1) {
  // Default constructor
  /* empty */
}

//_________________
StPicoTrack::StPicoTrack(const StPicoTrack &track) : TObject() {

  mId = track.mId;
  mDedxError = track.mDedxError;
#if defined (__TFG__VERSION__)
  mFlagExtension = track.mFlagExtension;
#endif
  mChi2 = track.mChi2;
  mPMomentumX = track.mPMomentumX;
  mPMomentumY = track.mPMomentumY;
  mPMomentumZ = track.mPMomentumZ;
  mGMomentumX = track.mGMomentumX;
  mGMomentumY = track.mGMomentumY;
  mGMomentumZ = track.mGMomentumZ;
  mOriginX = track.mOriginX;
  mOriginY = track.mOriginY;
  mOriginZ = track.mOriginZ;
  mDedx = track.mDedx;
  mDedxError = track.mDedxError;
#if defined (__TFG__VERSION__)
  mDnDx = track.mDnDx;
  mDnDxError = track.mDnDxError;
#endif
  mNHitsFit = track.mNHitsFit;
  mNHitsMax = track.mNHitsMax;
  mNHitsDedx = track.mNHitsDedx;
  mNSigmaPion = track.mNSigmaPion;
  mNSigmaKaon = track.mNSigmaKaon;
  mNSigmaProton = track.mNSigmaProton;
  mNSigmaElectron = track.mNSigmaElectron;
  for(int iIter=0; iIter<eTopologyMap; iIter++) {
    mTopologyMap[iIter] = track.mTopologyMap[iIter];
  }
  mBEmcPidTraitsIndex = track.mBEmcPidTraitsIndex;
  mBTofPidTraitsIndex = track.mBTofPidTraitsIndex;
  mETofPidTraitsIndex = track.mETofPidTraitsIndex;
  mMtdPidTraitsIndex = track.mMtdPidTraitsIndex;
  mETofPidTraitsIndex = track.mETofPidTraitsIndex;
#if !defined (__TFG__VERSION__)
  mTopoMap_iTpc = track.mTopoMap_iTpc;
#else
  mpIn = track.pIn();
  mIndex2MFbegin = track.index2MFbegin();
  mIndex2MFend   = track.index2MFend();
#endif
  mIdTruth = track.mIdTruth;
  mQATruth = track.mQATruth;
  mVertexIndex = track.mVertexIndex;
}

//_________________
StPicoTrack::~StPicoTrack() {
  /* emtpy */
}

//_________________
void StPicoTrack::Print(const Char_t* option __attribute__((unused)) ) const {
#if ! defined(__TFG__VERSION__)
  LOG_INFO << "id: " << id() << " chi2: " << chi2() << "\n"
           << "pMom: " << pMom().X() << " " << pMom().Y() << " " << pMom().Z() << "\n"
           << "gMom: " << gMom().X() << " " << gMom().Y() << " " << gMom().Z() << "\n"
           << "origin: " << origin().X() << " " << origin().Y() << " " << origin().Z() << "\n"
	   << "q: " << charge()
           << " nHitsFit: " << nHitsFit()
           << " nHitsdEdx: " << nHitsDedx() 
           << "\n\tnSigma pi/K/p/e: " << nSigmaPion()   << "/" << nSigmaKaon() << "/"
           << nSigmaProton() << "/" << nSigmaElectron() << "\n"
           << "Hit index in BEMC/BTof/MTD/ETof: " << mBEmcPidTraitsIndex << "/"
           << mBTofPidTraitsIndex << "/" << mMtdPidTraitsIndex << "/" << mETofPidTraitsIndex << "\n"
           << "idTruth: " << idTruth() << " qaTruth: " << qaTruth() << "\n"
           << endm;
#else /* __TFG__VERSION__ */
  LOG_INFO << "id: " << id() << " chi2: " << chi2() << "\t"
           << "pMom: " << pMom().X() << " " << pMom().Y() << " " << pMom().Z() << "\t"
	   << "gMom: " << gMom().X() << " " << gMom().Y() << " " << gMom().Z() << "\t"
	   << "origin: " << origin().X() << " " << origin().Y() << " " << origin().Z() << "\t"
	   << "q: " << charge()
           << " nHitsFit: " << nHitsFit()
           << " nHitsdEdx: " << nHitsDedx() 
           << "\n\tnSigma pi/K/p/e: " << nSigmaPion()   << "/" << nSigmaKaon() << "/"
           << nSigmaProton() << "/" << nSigmaElectron() << "\t"
	   << "Hit index in BEMC/BTof/MTD/ETof: " << mBEmcPidTraitsIndex << "/"
	   << mBTofPidTraitsIndex << "/" << mMtdPidTraitsIndex << "/" << mETofPidTraitsIndex 
	   << endm;
  Int_t index = StPicoDst::instance()->picoArray(StPicoArrays::Track)->IndexOf(this);
  StPicoTrackCovMatrix* CovMatrix = StPicoDst::instance()->trackCovMatrix(index);
  if (CovMatrix) {
    StDcaGeometry &dca = CovMatrix->dcaGeometry();
    LOG_INFO << dca << endm;
  }
  if (index2MFbegin() <= index2MFend()) {
    for (Int_t i = index2MFbegin(); i <= index2MFend(); i++) {
      StMassFit *mf = StPicoDst::instance()->massFit(i);
      if (mf)  LOG_INFO << *mf << endm;
    }
  }
#endif /* __TFG__VERSION__ */
}

//_________________
Float_t StPicoTrack::gDCAxy(Float_t x, Float_t y) const {
  return TMath::Sqrt( (mOriginX-x)*(mOriginX-x) + (mOriginY-y)*(mOriginY-y) );
}

//_________________
Float_t StPicoTrack::gDCA(Float_t x, Float_t y, Float_t z) const {
  return TMath::Sqrt( (mOriginX-x)*(mOriginX-x) +
		      (mOriginY-y)*(mOriginY-y) +
		      (mOriginZ-z)*(mOriginZ-z) );
}

//_________________
TVector3 StPicoTrack::gDCA(TVector3 pVtx) const {
  return (origin() - pVtx);
}

//_________________
void StPicoTrack::setChi2(Float_t chi2) {
  mChi2 = ( (chi2 * 1000.) > std::numeric_limits<unsigned short>::max() ?
	    std::numeric_limits<unsigned short>::max() :
	    (UShort_t)( TMath::Nint( chi2 * 1000. ) ) );
}

//_________________
void StPicoTrack::setDedx(Float_t dEdx) {
  // In keV/cm
  mDedx = dEdx * 1.e6;
}

//_________________
void StPicoTrack::setNHitsMax(Int_t nhits) {
  mNHitsMax = (UChar_t)nhits;
}

//_________________
void StPicoTrack::setNHitsPossible(Int_t nhits) {
  // For those who wants to have standard terminology
  setNHitsMax(nhits);
}

//_________________
void StPicoTrack::setNHitsDedx(Int_t nhits) {
  mNHitsDedx = (UChar_t)nhits;
}

//_________________
void StPicoTrack::setTopologyMap(Int_t id, UInt_t word) {
  if(id==0 || id==1 || id==2) {
    mTopologyMap[id] = word;
  }
  else {
    // Shouldn't here be a protection?
  }
}

//_________________
void StPicoTrack::setNSigmaPion(Float_t ns) {
  mNSigmaPion = ( fabs(ns * 1000.) > std::numeric_limits<short>::max() ?
		  ( (ns > 0) ? std::numeric_limits<short>::max() :
		    std::numeric_limits<short>::min() ) :
		  (Short_t)( TMath::Nint( ns * 1000. ) ) );
}

//_________________
void StPicoTrack::setNSigmaKaon(Float_t ns) {
  mNSigmaKaon = ( fabs(ns * 1000.) > std::numeric_limits<short>::max() ?
		  ( (ns > 0) ? std::numeric_limits<short>::max() :
		    std::numeric_limits<short>::min() ) :
		  (Short_t)( TMath::Nint( ns * 1000. ) ) );
}

//_________________
void StPicoTrack::setNSigmaProton(Float_t ns) {
  mNSigmaProton = ( fabs(ns * 1000.) > std::numeric_limits<short>::max() ?
		    ( (ns > 0) ? std::numeric_limits<short>::max() :
		      std::numeric_limits<short>::min() ) :
		    (Short_t)( TMath::Nint( ns * 1000. ) ) );
}

//_________________
void StPicoTrack::setNSigmaElectron(Float_t ns) {
  mNSigmaElectron = ( fabs(ns * 1000.) > std::numeric_limits<short>::max() ?
		      ( (ns > 0) ? std::numeric_limits<short>::max() :
			std::numeric_limits<short>::min() ) :
		      (Short_t)( TMath::Nint( ns * 1000. ) ) );
}

//_________________
TVector3 StPicoTrack::gMom(TVector3 pVtx, Float_t const B) const {
  StPicoPhysicalHelix gHelix = helix(B);
  return gHelix.momentumAt( gHelix.pathLength( pVtx ), B * kilogauss );
}

//_________________
StPicoPhysicalHelix StPicoTrack::helix(Float_t const B) const {
  return StPicoPhysicalHelix( gMom(), origin(), B * kilogauss,
			      static_cast<float>( charge() ) );
}

//_________________
Float_t StPicoTrack::dEdxPull(Float_t mass, UChar_t fit, Int_t charge) const {
  Float_t z = -999.;
#if defined(__TFG__VERSION__)
  Float_t momentum  = pIn();
  if (momentum <= 0.0) momentum  = gMom().Mag();
#else
  Float_t momentum  = gMom().Mag();
#endif
  Float_t betagamma = momentum * TMath::Abs(charge) / mass;
  Float_t dedx_measured, dedx_resolution = -1;
  if (! fit) { // I70
    dedx_measured = 1e-6*dEdx();
    dedx_resolution = dEdxError();
  }
  else if ( fit == 1) {     // Ifit
    dedx_measured = 1e-6*dEdx();
    dedx_resolution = dEdxError();
  }
  else {     // dNdx
    dedx_measured = dNdx();
    dedx_resolution = dNdxError();
  }
  if (dedx_resolution <= 0) return z;
  z = StdEdxPull::Eval(dedx_measured,dedx_resolution,betagamma,fit,charge, mass);
  return z;
}

//_________________
Float_t StPicoTrack::gDCAs(TVector3 point) const {
  // Signed DCA is defined for tracks with primary partners
  // and with non-zero global track momentum
  if ( (gMom().Mag() == 0 ) || ( !isPrimary() ) ) {
    return -999;
  }
  // Momentum of the global track
  TVector3 dir = gMom();
  // Unit vector
  dir = dir.Unit();
  Float_t cosl = dir.Perp();
  // Return DCA vector to the point (origin - point)
  TVector3 dca = gDCA( point );
  return -dir.Y()/cosl * dca.X() + dir.X()/cosl * dca.Y();
}

//_________________
void StPicoTrack::setVertexIndex(Int_t index) {
  if ( index<=-2 || index>std::numeric_limits<char>::max() ) {
    mVertexIndex = -2;
  }
  else {
    mVertexIndex = (Char_t)index;
  }
}
