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
#include "StMassFit.h"
#include "StDcaGeometry.h"
class StTrackMassFit : public StTrack {
public:
 StTrackMassFit(Int_t key = 0, Int_t pdg = 0, Float_t pInTpc = 0, Float_t chi2 = 0, Int_t ndf = 0, const StDcaGeometry *dcaG  = 0);
 StTrackMassFit(Int_t key, const StDcaGeometry *dcaG)  : StTrackMassFit(key, 0, 0.0, 0.0, 0, dcaG) {}
 StTrackMassFit(Int_t key, KFParticle* particle) : StTrackMassFit()  {mKFParticle = particle; setKey(key);}
  StTrackMassFit(const StTrackMassFit&);
  StTrackMassFit& operator=(const StTrackMassFit&);
  ~StTrackMassFit()  {SafeDelete(mKFParticle); SafeDelete(mMF);}
  
  virtual StTrackType     type() const {return (!vertex()) ? massFit : massFitAtVx; }
  KFParticle*         Particle() const;
  StMassFit               *mf()  const {return mMF;}
  void SetParticle(KFParticle *particle = 0) {mKFParticle = particle;}
  void SetParentID(Int_t id) {if (mKFParticle) mKFParticle->SetParentID(id);}
  virtual void Print(Option_t *option="") const;
  Int_t   pdg()    const {return (mMF) ? mMF->pdg() : 0;}
  Float_t pInTpc() const {return (mMF) ? mMF->pInTpc() : 0;}
  Int_t   ndf()    const {return (mMF) ? mMF->ndf() : 0;}
  Float_t chi2()   const {return (mMF) ? mMF->chi2() : 0;}
 protected:
  KFParticle    *mKFParticle;
  StMassFit     *mMF;
  ClassDef(StTrackMassFit,4)
};

ostream&  operator<<(ostream& os,  const StTrackMassFit& t);
#endif
