/***************************************************************************
 *
 * $Id: StFttClusterMaker.cxx,v 1.4 2019/03/08 18:45:40 fseck Exp $
 *
 * Author: Florian Seck, April 2018
 ***************************************************************************
 *
 * Description: StFttClusterMaker - class to fill the StEvent from DAQ reader:
 * unpack raw data & save StETofHeader & StETofDigis in StETofCollection 
 *
 ***************************************************************************/
#include <vector>
#include <map>
#include <array>
#include <algorithm>
#include <climits>

#include "StEvent.h"
#include "StEnumerations.h"

#include "StFttClusterMaker.h"

// Value written to a cluster's x / sigma when no charge was accumulated, so the
// divide-by-zero never happens and downstream consumers have one value to test
// against instead of a bare -999 appearing twice.
static const float kNoChargeSentinel = -999.0f;


#include "StEvent/StFttRawHit.h"
#include "StEvent/StFttCluster.h"
#include "StEvent/StEvent.h"
#include "StEvent/StFttCollection.h"

#include "StFttDbMaker/StFttDb.h"

// Per-file gating of STAR logging macros via mDebug. Bypasses a leak in the
// log4cxx pipeline (~312 B per LOG_INFO call). When mDebug==false the entire
// LOG expression is skipped at the AST level — no allocation, no leak.
// Affects only this translation unit. The `if (!mDebug) {} else` form guards
// against dangling-else attaching to a caller's `if`. LOG_WARN is left
// ungated so warnings are always emitted.
#undef  LOG_INFO
#undef  LOG_DEBUG
#define LOG_INFO  if (!mDebug) {} else LOGGERMESSAGE(Info)
#define LOG_DEBUG if (!mDebug) {} else LOGGERMESSAGE(Debug)


//_____________________________________________________________
StFttClusterMaker::StFttClusterMaker( const char* name )
: StMaker( name ),
  mRunYear( 0 ),        /// year in which the data was taken (switch at 1st Oct)
  mDebug( false ),       /// print out of all full messages for debugging
  mFttDb( nullptr )
{
    LOG_DEBUG << "StFttClusterMaker::ctor"  << endm;
}

//_____________________________________________________________
StFttClusterMaker::~StFttClusterMaker()
{  /* no op */

}

//_____________________________________________________________
Int_t
StFttClusterMaker::Init()
{
    LOG_INFO << "StFttClusterMaker::Init" << endm;

    return kStOk;
}

//_____________________________________________________________
Int_t
StFttClusterMaker::InitRun( Int_t runnumber )
{ 
    mRunYear = ( runnumber + 727000 ) / 1000000 + 1999;

    LOG_INFO << "runnumber: " << runnumber << "  --> year: " << mRunYear << endm;

    return kStOk;
}

//_____________________________________________________________
Int_t
StFttClusterMaker::FinishRun( Int_t runnumber )
{ 
    return kStOk;
}

//_____________________________________________________________
Int_t
StFttClusterMaker::Finish()
{ 
    return kStOk;
}


//_____________________________________________________________
Int_t
StFttClusterMaker::Make()
{ 
    StEvent *event = (StEvent*)GetInputDS("StEvent");
    if(!event) {
        LOG_WARN<<"No StEvent!"<<endm;
        return kStWarn;
    }
    mFttCollection=event->fttCollection();
    if(!mFttCollection) {
        LOG_WARN << "No StFttCollection" << endm;
        return kStOk;
    }
    // Clear any clusters from a previous event so the collection doesn't
    // accumulate across events when it survives event boundaries.
    //
    // Points MUST go first. StFttCollection::clusters() is an StSPtrVec, i.e. an
    // owning container whose clear() deletes the elements (StStrArray::clear), while
    // StFttPoint keeps its parents as raw StFttCluster* (StFttPoint::mClusters[4]).
    // Clearing clusters alone therefore leaves every surviving point pointing at freed
    // memory, and point->cluster(i) reads it. That is exactly the case this clear()
    // exists for -- a collection that survived the event boundary, or an StEvent
    // rebuilt from a MuDst that already carries production points -- so the two must
    // be cleared together. Downstream point makers rebuild points from the new
    // clusters in the same event.
    mFttCollection->points().clear();
    mFttCollection->clusters().clear();

    mFttDb = static_cast<StFttDb*>(GetDataSet("fttDb"));
    assert( mFttDb );

    LOG_DEBUG << "Found " << mFttCollection->rawHits().size() << " Ftt Hits" << endm;
    ApplyHardwareMap();

    

    // InjectTestData();

    // next we need to sort the hits into 1D projections
    // process 1 quadrant (ROB) at a time,
    // process horizontal, vertical or diagonal strips one at a time

    // key == ROB
    std::map< UChar_t, std::vector<StFttRawHit *> > hStripsPerRob; // Horizontal
    std::map< UChar_t, std::vector<StFttRawHit *> > vStripsPerRob; // Vertical
    std::map< UChar_t, std::vector<StFttRawHit *> > dhStripsPerRob; // Diagonal on Horizontal
    std::map< UChar_t, std::vector<StFttRawHit *> > dvStripsPerRob; // Diagonal on Vertical

    size_t nStripsHit = 0;
    for ( StFttRawHit* hit : mFttCollection->rawHits() ) {
        UChar_t rob = mFttDb->rob( hit );
        UChar_t so = mFttDb->orientation( hit );

        // Apply the time cut
        if ( !PassTimeCut( hit ) ) continue;

        if ( kFttHorizontal == so ){
            hStripsPerRob[ rob ].push_back(hit);
            nStripsHit++;
        } else if ( kFttVertical   == so ){
            vStripsPerRob[ rob ].push_back(hit);
            nStripsHit++;
        } else if ( kFttDiagonalH  == so ){
            dhStripsPerRob[ rob ].push_back(hit);
            nStripsHit++;
        } else if ( kFttDiagonalV  == so ){
            dvStripsPerRob[ rob ].push_back(hit);
            nStripsHit++;
        }
    } // loop on hit

    size_t nClusters = 0;
    LOG_DEBUG << "StFttClusterMaker::Make{ nStripsHit = " << nStripsHit << " }" << endm;

    // Look up per-ROB hits without mutating the maps. std::map::operator[] would
    // default-construct an empty vector for every missing ROB key, growing the map
    // while merely reading it. The maps are local to Make(), so nothing escapes the
    // call; the benefit is avoiding the needless insertions and allowing the lookup
    // to take the map by const reference.
    static const std::vector<StFttRawHit*> emptyHits;
    auto getHits = []( const std::map<UChar_t, std::vector<StFttRawHit*>>& m, UChar_t key ) -> const std::vector<StFttRawHit*>& {
        auto it = m.find( key );
        return it != m.end() ? it->second : emptyHits;
    };

    if ( nStripsHit > 0 ){ // could make more strict?
        for ( UChar_t iRob = 1; iRob < StFttDb::nRob+1; iRob++ ){

            auto hClusters = FindClusters( getHits( hStripsPerRob, iRob ) );
            // Add them to StEvent
            for ( StFttCluster * clu : hClusters ){
                mFttCollection->addCluster( clu );
                nClusters++;
            }
            auto vClusters = FindClusters( getHits( vStripsPerRob, iRob ) );
            // Add them to StEvent
            for ( StFttCluster * clu : vClusters ){
                mFttCollection->addCluster( clu );
                nClusters++;
            }
            auto hdClusters = FindClusters( getHits( dhStripsPerRob, iRob ) );
            // Add them to StEvent
            for ( StFttCluster * clu : hdClusters ){
                mFttCollection->addCluster( clu );
                nClusters++;
            }
            auto vdClusters = FindClusters( getHits( dvStripsPerRob, iRob ) );
            // Add them to StEvent
            for ( StFttCluster * clu : vdClusters ){
                mFttCollection->addCluster( clu );
                nClusters++;
            }
        } // loop on iRob
    } // nStripsHit
    LOG_DEBUG << "Found " << nClusters << " clusters this event" << endm;

    return kStOk;
} // Make

void StFttClusterMaker::InjectTestData(){
    mFttCollection->rawHits().clear();

    StFttRawHit *hit = new StFttRawHit( 1, 1, 1, 1, 1, 55, 1, 1, 0 );
    hit->setMapping( 1, 1, 1, 23, kFttHorizontal ); // LEFT 2
    mFttCollection->addRawHit( hit );

    hit = new StFttRawHit( 1, 1, 1, 1, 1, 90, 1, 1, 0 );
    hit->setMapping( 1, 1, 1, 24, kFttHorizontal ); // LEFT 1
    mFttCollection->addRawHit( hit );

    hit = new StFttRawHit( 1, 1, 1, 1, 1, 60, 1, 1, 0 );
    hit->setMapping( 1, 1, 1, 27, kFttHorizontal );
    mFttCollection->addRawHit( hit );

    hit = new StFttRawHit( 1, 1, 1, 1, 1, 95, 1, 1, 0 );
    hit->setMapping( 1, 1, 1, 25, kFttHorizontal ); // CENTER
    mFttCollection->addRawHit( hit );

    hit = new StFttRawHit( 1, 1, 1, 1, 1, 93, 1, 1, 0 );
    hit->setMapping( 1, 1, 1, 26, kFttHorizontal );
    mFttCollection->addRawHit( hit );

    hit = new StFttRawHit( 1, 1, 1, 1, 1, 19, 1, 1, 0 );
    hit->setMapping( 1, 1, 1, 28, kFttHorizontal );
    mFttCollection->addRawHit( hit );
} // InjectTestData


/**
 * @brief Checks if a hit passes the time cut.
 *
 * This function checks if a given hit passes the time cut based on 
 * the current time cut mode.
 * - mTimeCutMode = kTimeCutModeAcceptAll: accept all hits
 * - mTimeCutMode = kTimeCutModeDB: use the time cut from the database
 * - mTimeCutMode = kTimeCutModeCalibratedTime: use the calibrated time cut 
 *      set by the user
 * - mTimeCutMode = kTimeCutModeTimebin: use the timebin cut set by the user
 * 
 * if unrecognized time cut mode is set, the function will return true accepting all hits
 *
 * @param hit Pointer to the StFttRawHit object to be checked.
 * @return true if the hit passes the time cut, false otherwise.
 */
bool StFttClusterMaker::PassTimeCut( StFttRawHit * hit ){
    if (mTimeCutMode == kTimeCutModeAcceptAll) 
        return true;
    else if (mTimeCutMode == kTimeCutModeDB ) {
        int timeCutMin = INT_MIN;
        int timeCutMax = INT_MAX;
        int hitTimeMode = (int)kHitCalibratedTime;

        mFttDb->getTimeCut(hit, hitTimeMode, timeCutMin, timeCutMax);
        LOG_DEBUG << TString::Format( "StFttClusterMaker::PassTimeCut - DB gave hit time mode: %d, time cut min: %d, time cut max: %d", hitTimeMode, timeCutMin, timeCutMax ) << endm;
        if (hitTimeMode == kHitCalibratedTime) {
            return (hit->time() >= timeCutMin && hit->time() <= timeCutMax);
        } else if ( hitTimeMode == kHitTimebin ) {
            return (hit->tb() >= timeCutMin && hit->tb() <= timeCutMax);
        } else {
            LOG_WARN << "StFttClusterMaker::PassTimeCut - Unknown hit time mode from database: " << hitTimeMode << endm;
            LOG_WARN << "Accepting all hits" << endm;
            return true;
        }
    } else if (mTimeCutMode == kTimeCutModeCalibratedTime) {
        return (hit->time() >= mTimeCutMin && hit->time() <= mTimeCutMax);
    } else if (mTimeCutMode == kTimeCutModeTimebin) {
        return (hit->tb() >= mTimeCutMin && hit->tb() <= mTimeCutMax);
    } else {
        LOG_WARN << "StFttClusterMaker::PassTimeCut - Unknown time cut mode: " << mTimeCutMode << endm;
        LOG_WARN << "Accepting all hits" << endm;
        return true; // Default return value if no conditions are met
    }
    return true;
} // PassTimeCut


StFttRawHit * StFttClusterMaker::FindMaxAdc( const std::vector<StFttRawHit *>& hits, size_t &pos ){
    auto itMax = std::max_element(hits.begin(),
                             hits.end(),
                             [](const StFttRawHit* a,const StFttRawHit* b) { return a->adc() < b->adc(); });

    pos = (itMax - hits.begin());
    if ( itMax == hits.end() ) return nullptr;
    return *itMax;
}

void StFttClusterMaker::SearchClusterEdges( const std::vector< StFttRawHit * >& hits,
                                            size_t start, // start index at MaxADC
                                            size_t &left, size_t &right ){
    // set initial values
    left     = start;
    right    = start;

    auto lastHitLeft  = hits[start];
    auto lastHitRight = hits[start];

    bool searchRight = true;
    bool searchLeft = true;

    StFttRawHit *hitLeft = nullptr, *hitRight = nullptr;

    while ( searchRight || searchLeft ){
            LOG_DEBUG << "LEFT: " << left << ", RIGHT: " << right <<  ", start = " << start << ", size=" << hits.size() << endm;
        if ( searchRight ){
            if ( right == hits.size() || right == hits.size() - 1 ){ 
                searchRight = false;
            }
            else {
                
                hitRight = hits[right+1];
                if ( hitRight->adc() > lastHitRight->adc() || hitRight->adc() < GetThresholdFor( hitRight ) ){
                    searchRight = false;
                }
                if ( hitRight->row() != lastHitRight->row() || abs( hitRight->strip() - lastHitRight->strip() ) > 1 ){
                    searchRight = false;
                }

                if ( searchRight ){
                    right ++;
                    lastHitRight = hitRight;
                }
            } // right < size - 1
        } // searchRight

        if ( searchLeft ){
            if ( left == 0 ){
                searchLeft = false;
            } else {
                hitLeft = hits[left-1];
                if ( hitLeft->adc() > lastHitLeft->adc() || hitLeft->adc() < GetThresholdFor( hitLeft ) ){
                    searchLeft = false;
                }
                if ( hitLeft->row() != lastHitLeft->row() || abs( hitLeft->strip() - lastHitLeft->strip() ) > 1 ){
                    searchLeft = false;
                }

                if (searchLeft){
                    left--;
                    lastHitLeft = hitLeft;
                }
            } // left != 0
        } // searchLeft
    } // while searching
} // SearchClusterEdges


void StFttClusterMaker::CalculateClusterInfo( StFttCluster * clu ){

    clu->setNStrips( clu->rawHits().size() );

    // Compute the sumAdc, strip gravity center, and variance.
    //
    // Accumulated in DOUBLE, and the variance taken in TWO passes rather than
    // one. x is an ABSOLUTE strip position, up to ~530 mm from the quadrant
    // origin, so SUM q*x*x and (SUM q*x)^2 / SUM q are two large and nearly
    // equal numbers and the one-pass variance ( m2 - m1*m1/m0 ) / m0 is their
    // difference. In float that difference loses most of its significance:
    // measured on 334k clusters from a Run 22 production MuDst
    // (script/fttClusterSigma.C, fcstrk11), a SINGLE-strip cluster, whose
    // variance is exactly zero, came out NEGATIVE 46% of the time and wrong by
    // up to 0.042 mm^2. Subtracting the centroid strip by strip keeps every
    // term small and non-negative, so no cancellation happens and the clamp
    // below becomes belt and braces instead of load-bearing.
    double m0Sum = 0;
    double m1Sum = 0;

    std::for_each (clu->rawHits().begin(), clu->rawHits().end(), [&](const StFttRawHit *h) {
        double x = ( h->strip() * 3.2 - 1.6 ); // replace with CONST

        m0Sum += h->adc();
        m1Sum += (h->adc() * x);
    });

    if ( mDebug ) {
        LOG_DEBUG << "m0Sum = " << m0Sum << endm;
        LOG_DEBUG << "m1Sum = " << m1Sum << endm;
    }

    // m0Sum = sumAdc
    // m1Sum / m0Sum = gravity center (1st moment)

    clu->setSumAdc( m0Sum );
    if ( m0Sum > 0 ){
        const double xBar = m1Sum / m0Sum;
        clu->setX( xBar );

        // Second pass for the 2nd moment: SUM q*(x-xBar)^2, so every term is
        // small and non-negative. The clamp at zero below is kept because a
        // variance that is zero to the last bit is still possible, but it no
        // longer has rounding to catch.
        double s2Sum = 0;
        std::for_each (clu->rawHits().begin(), clu->rawHits().end(), [&](const StFttRawHit *h) {
            double dx = ( h->strip() * 3.2 - 1.6 ) - xBar;
            s2Sum += h->adc() * dx * dx;
        });
        double var = s2Sum / m0Sum;
        // The variance is still zero EXACTLY for every SINGLE-STRIP cluster --
        // all the charge sits in one strip, so there is nothing for a 2nd moment
        // to measure, and that is 18% of the clusters in Run 22 data, not an edge
        // case. A zero sigma gives GenFit an infinite weight in the precise
        // direction, forcing the track through the strip centre exactly and
        // making the fit unstable.
        // Floor it at the resolution one strip actually carries, pitch/sqrt(12).
        // StFttDb::stripPitch is mm, which is the unit setX()/setSigma() use here.
        //
        // NOTE this sigma is the cluster's CHARGE WIDTH, not the uncertainty on
        // its centroid, and StFttClusterPointMaker uses it as the latter. The
        // two differ by an order of magnitude; which number belongs in the
        // covariance is a separate, open question (script/fttClusterSigma.C).
        const double kSigmaMin = StFttDb::stripPitch / sqrt( 12.0 ); // 0.924 mm
        const double sig = sqrt( var < 0 ? 0 : var );
        clu->setSigma( sig < kSigmaMin ? kSigmaMin : sig );
    } else {
        // No charge accumulated; assign a sentinel rather than NaN from divide-by-zero.
        clu->setX( kNoChargeSentinel );
        clu->setSigma( kNoChargeSentinel );
    }
}



std::vector<StFttCluster*> StFttClusterMaker::FindClusters( std::vector< StFttRawHit * > hits ){
    std::vector<StFttCluster*> clusters;

    // No de-duplication here: early cosmic data (pre 2021-12-10) had hits that were
    // identical except for the timebin, but Tonko fixed that in the DAQ reader.

    // Sort the hits by row and strip
    sort(hits.begin(), hits.end(), [](const StFttRawHit * a, const StFttRawHit * b) -> bool { 
            size_t indexA = a->orientation() + StFttDb::nStripOrientations * ( a->strip() + a->row() * StFttDb::maxStripPerRow);
            size_t indexB = b->orientation() + StFttDb::nStripOrientations * ( b->strip() + b->row() * StFttDb::maxStripPerRow);
            return indexA < indexB; 
        });

    if ( mDebug ) {
        LOG_DEBUG << "We have " << hits.size() << " hits after removing duplicates" << endm;
    }


    // Get the max ADC hit in this projection
    size_t anchor  = hits.size()+1;
    auto maxAdcHit = FindMaxAdc( hits, anchor );

    // Loop as long as there is at least 1 hit left
    while ( maxAdcHit ){
        StFttCluster * clu = new StFttCluster();

        if ( Debug() ){
            LOG_DEBUG << "CLUSTER FIND START WITH HITS:" << endm;
            size_t i = 0;
            for ( auto *h : hits ){
                LOG_DEBUG << "[" << i << "]" << *h;
                i++;
            }
        }

        // Set cluster "location" from max ADC hit
        clu->setPlane       ( maxAdcHit->plane       ( ) );
        clu->setQuadrant    ( maxAdcHit->quadrant    ( ) );
        clu->setRow         ( maxAdcHit->row         ( ) );
        clu->setOrientation ( maxAdcHit->orientation ( ) );

        // These two were the only max-ADC-hit fields never copied onto the cluster,
        // so StFttCluster::maxStripLength() and maxStripCenter() kept their -999
        // defaults for every cluster ever written. Both are documented in
        // StEvent/StFttCluster.h as filled by THIS maker; until now they were not.
        //
        // maxStripLength is the LENGTH of the max-ADC strip, i.e. the extent of the
        // row band along the coordinate the strip does NOT measure. A point maker
        // places the off-axis coordinate at the band centre,
        // StFttDb::YX_StripGroupEdge[row] + maxStripLength()/2 (and the diagonal
        // equivalent in the rotated frame), with an uncertainty of
        // maxStripLength()/sqrt(12). With -999 that formula produced a large
        // negative local value, which combined with the per-quadrant sign flips to
        // swap which end of each row lands near versus far from y=0 -- the
        // top/bottom plus north/south swap and the bowtie shape in the FTT hit maps
        // both come from this one missing line. This is the fix the July 2026 FTT
        // reprocessing was run with.
        clu->setMaxStripLength( maxAdcHit->stripLength( ) );

        // maxStripCenter is the centre of the max-ADC strip along the coordinate the
        // strip DOES measure -- the same axis as cluster x(), from the same scMapXY
        // table (see StFttRawHit::mStripCenter). It is a single-strip, unweighted
        // version of x(), useful for diagnostics and alignment; it is NOT a position
        // along the strip, so it must not be used for the off-axis coordinate.
        clu->setMaxStripCenter( maxAdcHit->stripCenter( ) );

        // Now find the cluster edges
        size_t left = anchor, right = anchor;
        SearchClusterEdges( hits, anchor, left, right);
        
        LOG_DEBUG << "Cluster points ( " << left << ", " << anchor << ", " << right << " )" << endm;
        
        
        // OK now add these hits to the cluster
        for ( size_t i = left; i < right + 1; i++ ){
            clu->addRawHit( hits[i] );
        }

        // Take ownership before CalculateClusterInfo so the cluster is not leaked
        // if anything inside the calculation throws.
        clusters.push_back( clu );

        // Compute cluster information from the added hits
        CalculateClusterInfo( clu );

        if (mDebug){
            LOG_DEBUG << *clu << endm;;
        }

        // Now erase all hits from this cluster so that we can move on to find the next one
        hits.erase( hits.begin() + left, hits.begin() + right + 1 );
        maxAdcHit = FindMaxAdc( hits, anchor );
    } // while maxAdcHit
    return clusters;
}



void StFttClusterMaker::ApplyHardwareMap(){
    for ( StFttRawHit* rawHit : mFttCollection->rawHits() ) {
        mFttDb->hardwareMap( rawHit );
    }

}

