/***************************************************************************
 *
 * $Id: StTrackMassFit.cxx,v 1.1.1.1 2013/07/23 14:13:30 fisyak Exp $
 *
 * Author: Yuri Fisyak, April 5, 2013
 **************************************************************************/
#include "StTrackMassFit.h"
#include "StTrackNode.h"
#include "StGlobalTrack.h"
ClassImp(StTrackMassFit)

static const char rcsid[] = "$Id: StTrackMassFit.cxx,v 1.1.1.1 2013/07/23 14:13:30 fisyak Exp $";
//________________________________________________________________________________
StTrackMassFit::StTrackMassFit(Int_t key, Int_t pdg, Float_t pInTpc, Float_t chi2, Int_t ndf, const StDcaGeometry *dcaG )  : mKFParticle(0) {
  setKey(key); 
  mMF = 0;
  if (dcaG) mMF = new StMassFit(key, pdg, pInTpc, chi2, ndf, dcaG);
}
//________________________________________________________________________________
StTrackMassFit::StTrackMassFit(const StTrackMassFit& track) : StTrack(track) {
  mKFParticle=0;
  if (track.mKFParticle) mKFParticle = new KFParticle(*(track.mKFParticle));
  mMF = 0;
  if (track.mf()) mMF = new StMassFit(*(track.mf()));
}
//________________________________________________________________________________
StTrackMassFit& StTrackMassFit::operator=(const StTrackMassFit& track) {
  if (this != &track) {
    SafeDelete(mKFParticle);
    static_cast<StTrack&>(*this) = track;
    if (track.mKFParticle) mKFParticle = new KFParticle(*(track.mKFParticle));
    SafeDelete(mMF);
    if (track.mf()) mMF = new StMassFit(*(track.mf()));
  }
  return *this;
}
//________________________________________________________________________________
KFParticle *StTrackMassFit::Particle() const {
  if (! mf()) return 0;
  return &mf()->Particle();
}
//________________________________________________________________________________
ostream&  operator<<(ostream& os,  const StTrackMassFit& track) {
    os << *((StTrack *) &track);
    if (track.mf())  os << " " << *track.mf();
    else {
      if (track.Particle()) os << " " << *track.Particle();
    }
    return os;
}
//________________________________________________________________________________
void StTrackMassFit::Print(Option_t *option) const {cout << option << *this << endl; }
