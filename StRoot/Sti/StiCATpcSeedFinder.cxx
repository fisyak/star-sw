#include <assert.h>
#include <string.h>
#include "TVector3.h"
#include "Sti/StiToolkit.h"
#include "Sti/StiHit.h"
#include "StiUtilities/StiDebug.h"
#include "StMessMgr.h"
#include "StEvent/StTpcHit.h"
#include "Sti/StiKalmanTrack.h"

#include "StiCATpcTrackerInterface.h"
//#define PRINT_SEED_STATISTIC
//#define PRINT_FIT_ERR_STATISTIC
#ifdef PRINT_FIT_ERR_STATISTIC
#include <map>
#endif // PRINT_FIT_ERR_STATISTIC
//#define EXTRAPOLATION_CUT
//#define KINK_REJECTION  
#define OVERLAP_REJECTION
//#define StiCATpcSeedFinderBLOG
Int_t StiCATpcSeedFinder::_debug = 0;
//________________________________________________________________________________
Bool_t StiCATpcSeedFinder::SeedsCompareStatus(const Seed_t a, const Seed_t b)
{
  return (a.total_hits < b.total_hits);
}
//________________________________________________________________________________
StiTrack *StiCATpcSeedFinder::findTrack(double rMin)
{ 
  if (_debug) {
    cout << "StiCATpcSeedFinder::findTrack(" << rMin << ");" << endl;
  }
  static StiCATpcTrackerInterface& caTrackerInt = StiCATpcTrackerInterface::Instance();
  if (!mSeeds || mSeeds->size()==0) {
    if (mEnded) return 0;
    caTrackerInt.SetNewEvent();
    // zero all banks before filling !!! 
    auto *map =  &StiToolkit::instance()->getHitContainer()->hits();


    // Run reconstruction by the CA Tracker
    caTrackerInt.SetHits(*map);
    caTrackerInt.Run();
    mSeeds = &caTrackerInt.GetSeeds();
    if (!mSeeds->size()) { mEnded = 2; return 0;}
    sort(mSeeds->begin(), mSeeds->end(),SeedsCompareStatus );
  }
  while (mSeeds->size()) {
  
    Seed_t aSeed = mSeeds->back();
    mSeeds->pop_back();
    
    vector<StiHit*>        _seedHits;
    int nHits = aSeed.vhit.size();
    Int_t nHitsUsed = 0;
    for (int iHit=0;iHit<nHits;iHit++)     {
      StiHit *hit = aSeed.vhit[iHit]->hit;if (!hit) continue;
      if (hit->timesUsed()) nHitsUsed++;
      _seedHits.push_back(hit);
#if 0 /* move to initialize0 */
      if ( hit->detector()->getGroupId() == kTpcId) {
	vector<StiHit*> & hits = StiToolkit::instance()->getHitContainer()->getTpc2Hits(*hit, 
											StiLocalTrackSeedFinderParameters::instance()->deltaY(), 
											StiLocalTrackSeedFinderParameters::instance()->deltaZ());
	if (hits.size() < 2) continue;
	for (auto l : hits) {
	  if (! l) continue;
	  if (hit == l) continue;
	  _seedHits.push_back(l);
	}
      }
#endif
    }
    if (_seedHits.size() >=4 && nHitsUsed < 0.1*nHits)  {
      StiKalmanTrack* track = static_cast<StiKalmanTrack*>(StiToolkit::instance()->getTrackFactory()->getInstance());
      // use CATracker parameters. P.S errors should not be copied, they'd be initialized.
      track->initialize0(_seedHits, &aSeed.firstNodePars, &aSeed.lastNodePars/*, &aSeed.firstNodeErrs, &aSeed.lastNodeErrs*/ ); 
      mEnded = !mSeeds->size();
      return track;
    }
  }
  mEnded = 3; return 0;
}
//________________________________________________________________________________
