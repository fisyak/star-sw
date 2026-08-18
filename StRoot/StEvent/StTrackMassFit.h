/*!
 * \class StTrackMassFit 
 */
/***************************************************************************
 *
 * $Id: StTrackMassFit.h,v 1.2 2014/01/14 14:48:24 fisyak Exp $
 *
 * Author: Yuri Fisyak, April 5, 2013
 ***************************************************************************
 *
 * Description: Keep results of track mass fit
 *
 ***************************************************************************/
#ifndef StTrackMassFit_hh
#define StTrackMassFit_hh

#include "StTrack.h"
#include "KFParticle/KFParticle.h"
#include "StDcaGeometry.h"
class StTrackMassFit : public StTrack {
public:
 StTrackMassFit(Int_t key = 0, Float_t pInTpc = 0, Int_t pdg = 0, Float_t chi2 = 0, Int_t ndf = 0, StDcaGeometry *dca  = 0)  : 
  mPDG(pdg), mpInTpc(pInTpc),  mChi2(chi2), mNDF(ndf), mKFParticle(0), mDca((dca) ? new StDcaGeometry(*dca) : 0) {setKey(key);}
 StTrackMassFit(Int_t key, StDcaGeometry *dca)  : StTrackMassFit(key, 0.0, 0, 0.0, 0, dca) {}
 StTrackMassFit(Int_t key, KFParticle* particle) : StTrackMassFit()  {mKFParticle = particle; setKey(key);}
  StTrackMassFit(const StTrackMassFit&);
  StTrackMassFit& operator=(const StTrackMassFit&);
  ~StTrackMassFit()  {SafeDelete(mKFParticle);}
  
  virtual StTrackType     type() const {return (!vertex()) ? massFit : massFitAtVx; }
  KFParticle* Particle() const;
  StDcaGeometry *dca() const;
  void SetParticle(KFParticle *particle = 0) {mKFParticle = particle;}
  void SetParentID(Int_t id) {if (mKFParticle) mKFParticle->SetParentID(id);}
  virtual void Print(Option_t *option="") const;
  Int_t pdg() const {return mPDG;}
  Float_t pInTpc() const {return mpInTpc;}
  Int_t   NDF()    const {return mNDF;}
  Float_t Chi2()   const {return mChi2;}
 protected:
  Int_t         mPDG;
  Float_t       mpInTpc; // momentum at the first TPC hit
  Float_t       mChi2;
  Int_t         mNDF;
  KFParticle    *mKFParticle;
  StDcaGeometry *mDca;
  ClassDef(StTrackMassFit,3)
};

ostream&  operator<<(ostream& os,  const StTrackMassFit& t);
#endif
