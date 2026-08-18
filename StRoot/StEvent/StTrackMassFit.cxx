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
StTrackMassFit::StTrackMassFit(const StTrackMassFit& track) : StTrack(track) {
  mPDG    = track.pdg();
  mpInTpc = track.pInTpc();
  mNDF = track.NDF();
  mChi2 = track.Chi2();
  mKFParticle=0;
  if (track.mKFParticle) mKFParticle = new KFParticle(*(track.mKFParticle));
  mDca = 0;
  if (track.mDca) mDca = new StDcaGeometry(*(track.mDca));
}
//________________________________________________________________________________
StTrackMassFit& StTrackMassFit::operator=(const StTrackMassFit& track) {
  if (this != &track) {
    mPDG    = track.pdg();
    mNDF = track.NDF();
    mChi2 = track.Chi2();
    SafeDelete(mKFParticle);
    static_cast<StTrack&>(*this) = track;
    if (track.mKFParticle) mKFParticle = new KFParticle(*(track.mKFParticle));
    SafeDelete(mDca);
    if (track.mDca) mDca = new StDcaGeometry(*(track.mDca));
  }
  return *this;
}
//________________________________________________________________________________
StDcaGeometry *StTrackMassFit::dca() const {
  if (mDca) return mDca;
  if (! node()) return 0;
  StGlobalTrack *gTrack = (StGlobalTrack *)  node()->track(global);
  if (gTrack) return gTrack->dcaGeometry();  
  return 0;
  
}
//________________________________________________________________________________
KFParticle *StTrackMassFit::Particle() const {
  if (! dca()) return 0;
  return &dca()->Particle(key(),pdg(),mChi2,mNDF);
}
//________________________________________________________________________________
ostream&  operator<<(ostream& os,  const StTrackMassFit& track) {
    os << *((StTrack *) &track);
    if (track.dca()) {
      KFParticle *particle = track.Particle();
      if (particle) 
	os << " " << *particle;
    }
    os << Form("\t p/q in TPC %8.3f",track.pInTpc());
    return os;
}
//________________________________________________________________________________
void StTrackMassFit::Print(Option_t *option) const {cout << option << *this << endl; }
