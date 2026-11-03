#ifndef STFTTCLUSTER_H
#define STFTTCLUSTER_H

#include "StObject.h"
#include <Stiostream.h>
#include "StContainers.h"  // For StPtrVecFttRawHit
#include "StEnumerations.h"

class StFttRawHit;
class StFttPoint;
class StFttDb;

class StFttCluster : public StObject {
public:
    StFttCluster();
    ~StFttCluster();
    
    int id() const; // Cluster ID
    UChar_t plane()   const; // Detector plane (station) [0-3]
    UChar_t quadrant()   const; // detector quadrant [0-3] = A,B,C,D
    UChar_t row()   const; // detector row [0-4]: 0-2 X/Y strips, 3-4 diagonals
    UChar_t orientation() const;
    int nStrips() const;
    int nPoints() const;
    int nRawHits() const; // == nStrips?? need both?
    int nNeighbors() const;
    float sumAdc() const;
    float x() const;  // Charge-weighted mean strip centre (1st moment) along the
                      // measured coordinate, quadrant-local mm; -999 if sumAdc was 0.
    float sigma() const; // sqrt( sum(w*x^2)/sum(w) - (sum(w*x)/sum(w))^2 ) over the
                      // member strips, w = ADC, x = strip centre: a 1-D spread in mm,
                      // floored at pitch/sqrt(12) = 0.924 mm. NOT a major-axis 2nd
                      // moment -- the clusters are one-dimensional.
                      // https://www.google.com/search?q=formula+1st+2nd+moments+calorimeter+clusters

    float maxADC() const;
    int   indexMaxStrip() const;
    float maxStripLength() const;
    float maxStripCenter() const;
    float maxStripLeftEdge() const;
    float maxStripRightEdge() const;

    UShort_t idTruth() const { return mIdTruth; }
    UShort_t qaTruth() const { return mQaTruth; }


    void setId(int cluid);
    void setPlane(UChar_t plane);
    void setQuadrant(UChar_t quad);
    void setRow(UChar_t row);
    void setOrientation( UChar_t );
    void setNStrips(int numStrips);
    void setSumAdc(int theSumAdc);
    void setX(float x0);
    void setSigma(float sigma);

    void setMaxADC(int theMaxADC);
    void setIndexMaxStrip(int index);
    void setMaxStripLength( float sl );
    void setMaxStripCenter(float sc);
    void setMaxStripLeftEdge(float LEdge);
    void setMaxStripRightEdge(float REdge);

    void setIdTruth( UShort_t id ) { mIdTruth = id; }
    void setQaTruth( UShort_t qa ) { mQaTruth = qa; }

    StPtrVecFttRawHit& rawHits();
    const StPtrVecFttRawHit& rawHits() const;
    void addRawHit(StFttRawHit* p);
    void addNeighbor(StFttCluster* neighbor);
    StPtrVecFttCluster& neighbor();
    const StPtrVecFttCluster& neighbor() const;    
    StPtrVecFttPoint& points();
    const StPtrVecFttPoint& points() const;
    void addPoint(StFttPoint* p);
    // void print(Option_t *option="") const;
    void print();

private:
    Int_t   mId          = -1;             // Eventwise cluster ID, [0, nClusters-1]; -1 = unset
    UChar_t mPlane       = 0; // Detector plane (station) [0~3], StFttDb::nPlane = 4
    UChar_t mQuadrant    = 0; // Detector quadrant [0~3] = A,B,C,D (kFttQuadrantA..D)
    UChar_t mRow         = 0; // Detector row [0~4], StFttDb::nRowsPerQuad = 5: rows 0-2
                              // carry the X/Y strips, rows 3-4 the diagonals, which is
                              // what StFttDb::stripCenter()/stripEdges() enforce
    UChar_t mOrientation = kFttUnknownOrientation;        // [0~3] = kFttHorizontal,
                              // kFttVertical, kFttDiagonalH, kFttDiagonalV;
                              // kFttUnknownOrientation (4) = not set
    Int_t   mNStrips     = 0;         // Number of strips in the cluster, >= 1
                                      // (1-26 observed over 620k clusters, Run 22 data)
    Float_t mSumAdc      = 0.0;      // Total ADC (0th moment): sum over the member
                                      // strips, each [0-1023], so >= 0
    Float_t mX           = -999;             // Charge-weighted mean strip centre along the
                              // MEASURED coordinate -- quadrant-local MILLIMETRES, not
                              // strip units (StFttClusterMaker: "x is a strip centre in
                              // quadrant-local mm"). -999 when the charge sum was 0.
    Float_t mSigma       = -999;        // sqrt of the charge-weighted variance of those
                              // strip centres, mm. Floored at one pitch/sqrt(12) =
                              // 3.2/sqrt(12) = 0.924 mm, because a zero sigma gives
                              // GenFit infinite weight. -999 when the charge sum was 0.
    
    StPtrVecFttRawHit mRawHits;       // Tower hits of the current cluster
    StPtrVecFttCluster mNeighbors;    // Neighbor clusters
    StPtrVecFttPoint mPoints;         // Fitted points using this cluster
    
    // The six below describe the strip carrying the largest ADC in this cluster.
    // Only TWO of them are ever filled: StFttClusterMaker sets mMaxStripCenter and
    // mMaxStripLength. The other four have no setter call anywhere in StRoot, so
    // they keep -999 for every cluster ever written -- do not read them until
    // something fills them.
    Float_t mMaxADC            = -999;// ADC [0-1023] of the strip with maximum ADC.
                                      // NEVER SET: always -999
    Int_t   mIndexMaxStrip     = -999;// index of the strip with maximum ADC.
                                      // NEVER SET: always -999
    Float_t mMaxStripCenter    = -999;// mm, quadrant-local: centre of the strip with
                                      // maximum ADC; -1 if its mapping failed
    Float_t mMaxStripLength    = -999;// mm: LENGTH of the strip with maximum ADC
                                      // (the comment here used to say "Strip center",
                                      // copied from the line above); -1 if unmapped
    Float_t mMaxStripLeftEdge  = -999;// mm, quadrant-local: left edge of that strip.
                                      // NEVER SET: always -999
    Float_t mMaxStripRightEdge = -999;// mm, quadrant-local: right edge of that strip.
                                      // NEVER SET: always -999

    UShort_t mIdTruth=0; // Truth ID
    UShort_t mQaTruth=0; // Truth Quality

    ClassDef(StFttCluster, 5)
};

std::ostream& operator << ( std::ostream&, const StFttCluster& clu ); // Printing operator


inline int StFttCluster::id() const { return mId; } // Cluster ID
inline UChar_t StFttCluster::plane() const { return mPlane; }
inline UChar_t StFttCluster::quadrant() const { return mQuadrant; }
inline UChar_t StFttCluster::row() const { return mRow; }
inline UChar_t StFttCluster::orientation() const { return mOrientation; }
inline int StFttCluster::nStrips() const { return mNStrips; }
inline int StFttCluster::nRawHits() const { return mRawHits.size(); }
inline int StFttCluster::nNeighbors() const { return mNeighbors.size(); }
inline int StFttCluster::nPoints() const { return mPoints.size(); }
inline float StFttCluster::sumAdc() const { return mSumAdc; }
inline float StFttCluster::x() const { return mX; } // Mean x ("center of gravity") in local grid coordinate (1st moment).
inline float StFttCluster::sigma() const { return mSigma; } // 2nd moment

inline float StFttCluster::maxADC() const{ return mMaxADC; }
inline int StFttCluster::indexMaxStrip() const { return mIndexMaxStrip; } 
inline float StFttCluster::maxStripCenter() const { return mMaxStripCenter; } 
inline float StFttCluster::maxStripLength() const { return mMaxStripLength; } 
inline float StFttCluster::maxStripLeftEdge() const { return mMaxStripLeftEdge; } 
inline float StFttCluster::maxStripRightEdge() const { return mMaxStripRightEdge; } 



inline void StFttCluster::setPlane(UChar_t plane) { mPlane = plane; }
inline void StFttCluster::setQuadrant(UChar_t quadrant) { mQuadrant = quadrant; }
inline void StFttCluster::setRow(UChar_t row) { mRow = row; }
inline void StFttCluster::setOrientation( UChar_t so ) { mOrientation = so; }
inline void StFttCluster::setNStrips(int numStrips) { mNStrips = numStrips; }
inline void StFttCluster::setSumAdc(int theSumAdc) { mSumAdc = theSumAdc; }
inline void StFttCluster::setX(float x0) { mX = x0; }
inline void StFttCluster::setSigma(float sigma) { mSigma = sigma; }

inline void StFttCluster::setMaxADC(int theMaxADC) {mMaxADC = theMaxADC;}
inline void StFttCluster::setIndexMaxStrip( int index ) { mIndexMaxStrip = index; }
inline void StFttCluster::setMaxStripLength( float sl ) { mMaxStripLength = sl; }
inline void StFttCluster::setMaxStripCenter( float sc ) { mMaxStripCenter = sc; }
inline void StFttCluster::setMaxStripLeftEdge( float LEdge ) { mMaxStripLeftEdge = LEdge; }
inline void StFttCluster::setMaxStripRightEdge( float REdge ) { mMaxStripRightEdge = REdge; }

inline void StFttCluster::setId(int cluid) { mId = cluid; }

inline StPtrVecFttRawHit& StFttCluster::rawHits() { return mRawHits; }
inline const StPtrVecFttRawHit& StFttCluster::rawHits() const { return mRawHits; }
inline StPtrVecFttCluster& StFttCluster::neighbor() { return mNeighbors; }
inline const StPtrVecFttCluster& StFttCluster::neighbor() const { return mNeighbors; }
inline StPtrVecFttPoint& StFttCluster::points() { return mPoints; }
inline const StPtrVecFttPoint& StFttCluster::points() const { return mPoints; }

#endif  // STFTTCLUSTER_H
