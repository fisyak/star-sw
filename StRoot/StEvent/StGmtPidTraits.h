/*!
 * \class StGmtPidTraits 
 * ()\author Yuri Fisyak 01/28/2025
 */
#ifndef StGmtPidTraits_hh
#define StGmtPidTraits_hh
#include "TMath.h"
#include "StTrackPidTraits.h"
#include "StGmtPoint.h"
#include "StThreeVectorF.hh"

class StGmtPidTraits : public StTrackPidTraits {
 public:
 StGmtPidTraits(StGmtPoint *gmtPoint = 0) : StTrackPidTraits(kGmtId),// mGmtPoint(gmtPoint), 
    mId(-1), mModule(255), mYLocal(0), mZLocal(0), mDeltaY(-999), mDeltaZ(-999), mSigmaY(-999), mSigmaZ(-999),  mPosition() { 
    if (gmtPoint) {
      setPointId(gmtPoint->id());
      setModule(gmtPoint->getModule());
      setYLocal(gmtPoint->local().y());
      setZLocal(gmtPoint->local().z());
      setDeltaY(gmtPoint->yD() - mYLocal);
      setDeltaZ(gmtPoint->zD() - mZLocal);
      setSigmaY(gmtPoint->dyD());
      setSigmaZ(gmtPoint->dzD());
      setPosition(gmtPoint->position());
    }
  }
  virtual ~StGmtPidTraits() {}
  
/*   StGmtPoint*       gmtPoint()             { return mGmtPoint;}	     */
/*   const StGmtPoint* gmtPoint()  const      { return mGmtPoint;}	     */
  
  UChar_t          id()         const      { return mId;}	    
  UChar_t          module()     const      { return mModule;}	    
  Float_t          yLocal()     const      { return mYLocal;          }
  Float_t          zLocal()     const      { return mZLocal;          }
  Float_t          deltaY()     const      { return mDeltaY;          }
  Float_t          deltaZ()     const      { return mDeltaZ;          }
  Float_t          sigmaY()     const      { return mSigmaY;          }
  Float_t          sigmaZ()     const      { return mSigmaZ;          }
  Double_t         deviation()  const      { return TMath::Sqrt(deltaY()*deltaY() + deltaZ()*deltaZ());}
  StThreeVectorF&         position()       { return mPosition;}
  const StThreeVectorF&   position() const { return mPosition;}
  //
  void    setPointId(Int_t id)             { mId = id;} 
  void    setModule(Int_t m)               { mModule = m;} 
  //  void    setGmtPoint(StGmtPoint* hit)     { mGmtPoint = hit;}
  void    setYLocal(Float_t val)           { mYLocal = val;}
  void    setZLocal(Float_t val)           { mZLocal = val;}          
  void    setPosition( const StThreeVectorF& pos) { mPosition = pos;}
  void    setDeltaY(Float_t val)           { mDeltaY = val;}
  void    setDeltaZ(Float_t val)           { mDeltaZ = val;}
  void    setSigmaY(Float_t val)           { mSigmaY = val;}
  void    setSigmaZ(Float_t val)           { mSigmaZ = val;}
 private:
#if 0
#if defined(__CINT__) || defined(__CLING__)
  StObjLink        mGmtPoint;
#else
  StLink<StGmtPoint>  mGmtPoint;
#endif //__CINT__
#endif
  Int_t     mId;                  
  UChar_t   mModule;
  Float_t   mYLocal;                // track prediction local position
  Float_t   mZLocal;                //  -"-
  Float_t   mDeltaY;                // DeltaY between matched track-hit pair
  Float_t   mDeltaZ;                // DeltaZ between matched track-hit pair
  Float_t   mSigmaY;                // sigma of DeltaY between matched track-hit pair
  Float_t   mSigmaZ;                // sigma of DeltaZ between matched track-hit pair
  StThreeVectorF  mPosition;        // Track prediction global position at Gmt hit
  
  
  ClassDef(StGmtPidTraits,1)
};

#endif
