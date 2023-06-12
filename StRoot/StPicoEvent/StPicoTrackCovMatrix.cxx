// PicoDst headers
#include "StPicoMessMgr.h"
#include "StPicoTrackCovMatrix.h"

ClassImp(StPicoTrackCovMatrix)

//_________________
StPicoTrackCovMatrix::StPicoTrackCovMatrix() : TObject(),
  mImp(0), mZ(0), mPsi(0), mPti(0), mTan(0), mCurv(0),
  mSigma{}, mCorr{} {
  /* empty */
}

//_________________
StPicoTrackCovMatrix::StPicoTrackCovMatrix(const StPicoTrackCovMatrix &mtx) : TObject() {
  mImp = mtx.mImp;
  mZ = mtx.mZ;
  mPsi = mtx.mPsi;
  mPti = mtx.mPti;
  mTan = mtx.mTan;
  mCurv = mtx.mCurv;
  for(Int_t iIter=0; iIter<5; iIter++) {
    mSigma[iIter] = mtx.mSigma[iIter];
  }
  for(Int_t iIter=0; iIter<10; iIter++) {
    mCorr[iIter] = mtx.mCorr[iIter];
  }
}

//_________________
StPicoTrackCovMatrix::~StPicoTrackCovMatrix() {
  /* empty */
}

//_________________
void StPicoTrackCovMatrix::Print(Char_t const* option __attribute__((unused)) ) const {
  const Float_t *lSigma = sigmas();
  const Float_t *lCorr = correlations();
  LOG_INFO << "imp: " << imp()
	   << "\tz: " << z()
	   << "\tpsi: " << psi()
	   << "\tpti: " << pti()
	   << "\ttan: " << tan()
	   << "\tcurv: " << curv()
	   << "\nsigmas: \t"
	   << lSigma[0] << "\t" << lSigma[1] << "\t"
	   << lSigma[2] << "\t" << lSigma[3] << "\t"
	   << lSigma[4] << "\n"
	   << "correlations: \n"
	   << lCorr[0] << "\t" << lCorr[1] << "\t"
	   << lCorr[2] << "\t" << lCorr[3] << "\t"
	   << lCorr[4] << "\t" << lCorr[5] << "\t"
	   << lCorr[6] << "\t" << lCorr[7] << "\t"
	   << lCorr[8] << "\t" << lCorr[9] << endm;
}

//_________________
Bool_t StPicoTrackCovMatrix::isBadCovMatrix() {
  return( mImp == 0 &&
	  mZ == 0 &&
	  mPsi == 0 &&
	  mPti == 0 &&
	  mTan == 0 &&
	  mCurv == 0 &&
	  mSigma[0]==0 && mSigma[1]==0 && mSigma[2]==0 && mSigma[3]==0 && mSigma[4]==0 &&
	  mCorr[0]==0 && mCorr[1]==0 && mCorr[2]==0 && mCorr[3]==0 && mCorr[4]==0 &&
	  mCorr[5]==0 && mCorr[6]==0 && mCorr[7]==0 && mCorr[8]==0 && mCorr[9]==0 );
}

#if defined (__TFG__VERSION__)
//_________________
StDcaGeometry &StPicoTrackCovMatrix::dcaGeometry() const {
  static StDcaGeometry a;
  Float_t errMatrix[15];
  Int_t ii = 0;
  for (int i = 0; i < 5; i++) {
    errMatrix[ii] = mSigma[i]*mSigma[i];
    for (int j = 0; j < i; j++) {
      Int_t ij = ii - i - 1 + j + 1;
      Int_t ij1 = ij - i;
      errMatrix[ij] = mCorr[ij1]*mSigma[i]*mSigma[j];
    }
    ii += i+2;
  }
  a.set(params(), errMatrix);
  return *&a;
}      
#endif /* __TFG__VERSION__ */
