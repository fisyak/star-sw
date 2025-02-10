/***************************************************************************
 *
 * Authors: K.S. Engle and Richard Witt (witt@usna.edu), Jan 2013
 * based on StFgtHit
 *
 ***************************************************************************
 *
 * Description: data for individual ``point'' on the GMT, i.e. a pair
 * of 1D clusters.  Note, if errors during construction, the key will
 * be set to -999.  Need to check this after constructing.
 *
 ***************************************************************************/

#ifndef _ST_GMT_POINT_H_
#define _ST_GMT_POINT_H_

#include "StGmtHit.h"
#include "StTrack.h"

class StGmtPoint : public StHit {
public:
 StGmtPoint(Int_t id  = -1, Int_t module = -1, Int_t trackId = 0, 
	    Double32_t XG = 0, Double32_t YG = 0, Double32_t ZG = 0,
	    Double32_t XL = 0, Double32_t YL = 0, Double32_t ZL = 0, 
	    Float_t yD = 0, Float_t sigmaY = 0, Float_t AdcLy = 0,
	    Float_t dyD = 0, Float_t dsigmaY = 0, Float_t dAdcLy = 0,
	    Float_t zD = 0, Float_t sigmaZ = 0, Float_t AdcLz = 0,
	    Float_t dzD = 0, Float_t dsigmaZ = 0, Float_t dAdcLz = 0);
#if 1
 StGmtPoint(StGmtHit &hitY, StGmtHit &hitZ, Int_t trackId, StThreeVectorF &global, StThreeVectorF &local);
#endif
  ~StGmtPoint() {}
  StDetectorId detector()      const  {return kGmtId;}    
  Int_t        getTrackId()    const  {return mTrackId;}
  Int_t        getModule()     const  {return hardwarePosition()/2 - 1;}
  Int_t        volumeID()      const  {return 0;}
  StThreeVectorF local()       const  {return positionError();}  // prediction in local coorditane system
  Float_t      yD()            const  {return myD;}
  Float_t      sigmaY()        const  {return msigmaY;}
  Float_t      AdcLy()         const  {return mAdcLy;}
  Float_t      dyD()           const  {return mdyD;}
  Float_t      dsigmaY()       const  {return mdsigmaY;}
  Float_t      dAdcLy()        const  {return mdAdcLy;}
  Float_t      zD()            const  {return mzD;}
  Float_t      sigmaZ()        const  {return msigmaZ;}
  Float_t      AdcLz()         const  {return mAdcLz;}
  Float_t      dzD()           const  {return mdzD;}
  Float_t      dsigmaZ()       const  {return mdsigmaZ;}
  Float_t      dAdcLz()        const  {return mdAdcLz;}
  void setAssociatedTrack(StTrack* val);
  StTrack*        associatedTrack();
  const StTrack*  associatedTrack() const;
  virtual void Print(Option_t *opt="") const;
 private:   
  // data members
  Int_t   mTrackId;              
  Float_t myD, msigmaY, mAdcLy;
  Float_t mdyD, mdsigmaY, mdAdcLy;
  Float_t mzD, msigmaZ, mAdcLz;
  Float_t mdzD, mdsigmaZ, mdAdcLz;
#if defined(__CINT__) || defined(__CLING__)
  StObjLink        mAssociatedTrack;		
#else
  StLink<StTrack>  mAssociatedTrack;		
#endif //__CINT__
  ClassDef(StGmtPoint,2)
}; 
#endif
