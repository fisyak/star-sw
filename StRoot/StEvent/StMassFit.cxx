#include "StMassFit.h"
#include "TMath.h"
ClassImp(StMassFit)

//_________________
StMassFit::StMassFit(Int_t key, Int_t pdg, Float_t pInTpc, Float_t chi2, Int_t ndf, const StDcaGeometry *dcaG ) :
mKey(key), mPDG(pdg), mpInTpc(pInTpc),  mChi2(chi2), mNDF(ndf) {
  memset(mBeg,0,mEnd-mBeg+1);
  if (dcaG) {
    // Retrieve pointers to the covariance matrix values and errors
    const Float_t* parDCA = dcaG->params();
    const Float_t* errorMatrix = dcaG->errMatrix();
    
    // Set covariance matrix values
    setImp( parDCA[0] );
    setZ( parDCA[1] );
    setPsi( parDCA[2] );
    setPti( parDCA[3] );
    setTan( parDCA[4] );
    setCurv( parDCA[5] );

    Float_t SigmaArr[5];
    Float_t CorrArr[10];
    Int_t ii = 0;
    for(Int_t iVal=0; iVal<5; iVal++) {
      SigmaArr[iVal] = TMath::Sqrt( errorMatrix[ii] );
      for(Int_t j=0; j<iVal; j++) {
	Int_t ij = (ii - iVal - 1) + (j + 1);
	Int_t ij1 = ij - iVal;
	CorrArr[ij1] = errorMatrix[ij] / ( SigmaArr[iVal] * SigmaArr[j] );
      }
      ii += iVal+2;
    } //for(Int_t iVal = 0; iVal < 5; iVal++)
    // Set sigma and correlation arrays
    setSigmas( SigmaArr );
    setCorrelations( CorrArr );
  }
}
//_________________
Bool_t StMassFit::isBadCovMatrix() {
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

//_________________
StDcaGeometry &StMassFit::dcaGeometry() const {
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
//________________________________________________________________________________
ostream&  operator<<(ostream& os,  const StMassFit& track) {
  os << " " << track.Particle();
  os << Form("\t p/q in TPC %8.3f",track.pInTpc());
  return os;
}
//________________________________________________________________________________
void StMassFit::Print(Option_t *option) const {cout << option << *this << endl; }
