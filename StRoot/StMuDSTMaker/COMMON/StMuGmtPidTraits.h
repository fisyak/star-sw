/*!
 * \class StMuGmtPidTraits 
 * ()\author Yuri Fisyak 01/28/2025
 */
#ifndef StMuGmtPidTraits_hh
#define StMuGmtPidTraits_hh
#include "TObject.h"
#include "StThreeVectorF.hh"
#include "TMath.h"
class StGmtPidTraits;
class StMuGmtPidTraits : public TObject {
 public:
  StMuGmtPidTraits(const StGmtPidTraits *gmtPidTrait = 0); 
  virtual ~StMuGmtPidTraits() {}
  void             set(const StGmtPidTraits *gmtPidTrait);
  Int_t            id()         const      { return mId;}
  UChar_t          module()     const      { return mModule;}	    
  Float_t          yLocal()     const      { return mYLocal;          }
  Float_t          zLocal()     const      { return mZLocal;          }
  Float_t          deltaY()     const      { return mDeltaY;          }
  Float_t          deltaZ()     const      { return mDeltaZ;          }
  Float_t          sigmaY()     const      { return mSigmaY;          }
  Float_t          sigmaZ()     const      { return mSigmaZ;          }
  Double_t         deviation()  const      { return TMath::Sqrt(deltaY()*deltaY() + deltaZ()*deltaZ());}
  StThreeVectorF   position()   const      { return StThreeVectorF(mxG, myG, mzG);}
  //
  void    setId(Int_t id)                  { mId = id;} 
  void    setModule(Int_t m)               { mModule = m;} 
  void    setYLocal(Float_t val)           { mYLocal = val;}
  void    setZLocal(Float_t val)           { mZLocal = val;}          
  void    setDeltaY(Float_t val)           { mDeltaY = val;}
  void    setDeltaZ(Float_t val)           { mDeltaZ = val;}
  void    setSigmaY(Float_t val)           { mSigmaY = val;}
  void    setSigmaZ(Float_t val)           { mSigmaZ = val;}
  void    setxG(Float_t val)               { mxG = val;}
  void    setyG(Float_t val)               { myG = val;}
  void    setzG(Float_t val)               { mzG = val;}
 private:
  Char_t      mBeg[1];                //!
  UShort_t        mId;                  
  UChar_t     mModule;
  Float16_t   mYLocal;                // track prediction local position
  Float16_t   mZLocal;                //  -"-
  Float16_t   mDeltaY;                // DeltaY between matched track-hit pair
  Float16_t   mDeltaZ;                // DeltaZ between matched track-hit pair
  Float16_t   mSigmaY;                // sigma of DeltaY between matched track-hit pair
  Float16_t   mSigmaZ;                // sigma of DeltaZ between matched track-hit pair
  Float16_t   mxG, myG, mzG;          // Track prediction global position at Gmt hit
  Char_t      mEnd[1];                //!
  
  
  ClassDef(StMuGmtPidTraits,1)
};

#endif /* StMuGmtPidTraits_hh */
