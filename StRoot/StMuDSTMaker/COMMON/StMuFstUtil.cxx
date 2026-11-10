#include "StEvent/StFstHitCollection.h"
#include "StEvent/StFstHit.h"
#include "StEvent/StFstEvtCollection.h"
#include "StEvent/StFstRawHit.h"

#include "StMuDSTMaker/COMMON/StMuFstHit.h"
#include "StMuDSTMaker/COMMON/StMuFstRawHit.h"
#include "StMuDSTMaker/COMMON/StMuFstUtil.h"
#include "StMuDSTMaker/COMMON/StMuFstCollection.h"
#include "StMuDSTMaker/COMMON/StMuDst.h"
#include "StMuDSTMaker/COMMON/StMuEvent.h"
#include "StEvent/StEvent.h"
#include "St_base/StMessMgr.h"
#include "StEvent/StEventTypes.h"
#include "StEvent/StTriggerData.h"
#include "StEvent/StContainers.h"

#include <algorithm>  // For std::find
#include <iterator>  // For std::distance

#include "TCollection.h"  // For TIter
#include "TRefArray.h"
#include "TVector3.h"

ClassImp(StMuFstUtil)

StMuFstUtil::StMuFstUtil()
{
}
StMuFstUtil::~StMuFstUtil()
{
}

StMuFstCollection* StMuFstUtil::getMuFst(StFstHitCollection *fstcol, StFstEvtCollection *fstevtcol)
{
    LOG_DEBUG << "StMuFstUtil::getMuFst" << endm;
    if(!fstcol) return NULL;
    StMuFstCollection* muFst=new StMuFstCollection();
    fillMuFst(muFst,fstcol,fstevtcol);
    return muFst;
} // getMuFst

StFstHitCollection* StMuFstUtil::getFst(StMuFstCollection* muFst)
{
    if(!muFst) return NULL;

    StFstHitCollection *fst=new StFstHitCollection();
    fillFst(fst,muFst);
    return fst;
} //getFst

StFstEvtCollection* StMuFstUtil::getFstEvt(StMuFstCollection* muFst)
{
    if(!muFst) return NULL;

    StFstEvtCollection *fstevt=new StFstEvtCollection();
    fillFstEvt(fstevt,muFst);
    return fstevt;
} //getFstEvt

void StMuFstUtil::fillMuFst(StMuFstCollection *muFst,StFstHitCollection *fstcol,StFstEvtCollection *fstevtcol)
{
    LOG_INFO << "fillMuFst" << endm;
    if(!fstcol) return;
    if(!muFst) return;

    fillMuFstHits(muFst, fstcol, fstevtcol);

} // fillMuFst

void StMuFstUtil::fillFst(StFstHitCollection* fstcol,StMuFstCollection* muFst)
{
    if(!muFst) return;
    if(!fstcol) return;
    fillFstHits(fstcol, muFst);
} // fillFst

void StMuFstUtil::fillFstEvt(StFstEvtCollection* fstevtcol,StMuFstCollection* muFst)
{
    if(!muFst) return;
    if(!fstevtcol) return;
    fillFstRawHits(fstevtcol, muFst);
} // fillFstEvt

void StMuFstUtil::fillMuFstHits(StMuFstCollection* muFst,
        StFstHitCollection* fstcol,
        StFstEvtCollection *fstevtcol)
{
    LOG_INFO << "fillMuFstHits" << endm;
    //fill FST Raw Hits
    if(fstevtcol) {
        LOG_DEBUG << "fillMuFstHits (raw hits)" << endm;
        if(fstevtcol->numberOfRawHits() > 0) {
            const StSPtrVecFstRawHit &vecRawHit = fstevtcol->rawHits();
            for(unsigned int i=0; i<fstevtcol->numberOfRawHits(); i++)
            {
                StMuFstRawHit* muFstRawHit = muFst->addRawHit();
                muFstRawHit->set( vecRawHit[i] );
            }  // for i hit
        } // if has FST Raw hit

    } // if has FST Raw hit collection

    //fill FST hits
    for(int wedgeIdx=0; wedgeIdx<kFstNumWedges; wedgeIdx++ )
    {
        StFstWedgeHitCollection* wedgeHitCollection = fstcol->wedge(wedgeIdx);
        for(int sensorIdx=0; sensorIdx<kFstNumSensorsPerWedge; sensorIdx++)
        {
            StFstSensorHitCollection* sensorHitCollection = wedgeHitCollection->sensor(sensorIdx);

            const StSPtrVecFstHit &vecHit = sensorHitCollection->hits();
            for(unsigned int i=0; i<sensorHitCollection->numberOfHits(); i++)
            {
                StMuFstHit* muFstHit = muFst->addHit();
                muFstHit->set( vecHit[i] );
            }  // for i hit
        }  // for sensorIdx
    }  // for wedgeIdx

} // fillMuFstHits

// Rebuild StEvent raw hits from the MuDst. Counterpart of fillMuFstHits()'s raw-hit
// half; mirrors StMuFttUtil::fillFttRawHits, which is what lets the FTT chain re-run
// from a MuDst. Every member StMuFstRawHit::set() copies is restored here, so the
// round trip is lossless.
//
// Uses TIter so a null array is handled without a special case, as on the FTT side.
void StMuFstUtil::fillFstRawHits(StFstEvtCollection* fstevtcol,
        StMuFstCollection* muFst)
{
    LOG_INFO << "fillFstRawHits" << endm;
    TIter next(muFst->getRawHitArray());
    StMuFstRawHit* muHit(NULL);
    int n = 0;
    while ((muHit = static_cast<StMuFstRawHit*>(next()))) {
        StFstRawHit* hit = new StFstRawHit();
        hit->setChannelId( muHit->getChannelId() );
        hit->setGeoId( muHit->getGeoId() );
        hit->setSeedhitflag( muHit->getSeedhitflag() );
        for (int tb = 0; tb < kFstNumTimeBins; tb++) {
            hit->setCharge( muHit->getCharge(tb), tb );
            hit->setChargeErr( muHit->getChargeErr(tb), tb );
        }
        hit->setMaxTimeBin( muHit->getMaxTimeBin() );
        hit->setIdTruth( muHit->getIdTruth() );
        fstevtcol->addRawHit( hit );
        n++;
    }
    LOG_DEBUG << "fillFstRawHits - restored " << n << " FST raw hits from the MuDst" << endm;
} // fillFstRawHits

void StMuFstUtil::fillFstHits(StFstHitCollection* fstcol,
        StMuFstCollection* muFst)
{
    // Using TIter to iterate is safe in the case of hits being NULL
    TIter next(muFst->getHitArray());
    StMuFstHit* muHit(NULL);
    while ((muHit = static_cast<StMuFstHit*>(next())))
    {
        StFstHit *newHit = new StFstHit(muHit->getDisk(), muHit->getWedge(), muHit->getSensor(), muHit->getApv(), muHit->getCharge(), muHit->getChargeErr(), muHit->getMaxTimeBin(), muHit->getMeanRStrip(), muHit->getMeanPhiStrip(), muHit->getNRawHits(), muHit->getNRawHitsR(), muHit->getNRawHitsPhi());
        newHit->setId(muHit->getId());
        newHit->setIdTruth(muHit->getIdTruth());

        newHit->setLocalPosition(muHit->localPosition(0), muHit->localPosition(1), muHit->localPosition(2)); //set local position on sensor

        fstcol->addHit(newHit);
    }  // while
} // fillFstHits
