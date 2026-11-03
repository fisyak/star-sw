/**************************************************************************
 *
 * StFttPoint.h
 *
 * Author: jdb 2021
 **************************************************************************
 *
 * Description: Declaration of StFttPoint, the StEvent FTT point structure
 * Represents a "point" (cluster centroid etc) via cluster finding.
 *
 **************************************************************************/
#ifndef StFttPoint_h
#define StFttPoint_h

#include "StThreeVectorD.hh"
#include "StObject.h"
#include "StEnumerations.h"
#include "StContainers.h"

class StFttCluster;

class StFttPoint : public StObject {
public:
    StFttPoint();
    ~StFttPoint();

    // UNITS, because the two frames here are easy to mix up and the result looks
    // like a broken detector: x(), y(), d1(), d2() and the sigmas are
    // QUADRANT-LOCAL MILLIMETRES, while xyz() is GLOBAL STAR CENTIMETRES. There is
    // no z() -- the point's global z is xyz().Z().
    UChar_t plane()   const; // Detector plane (station) [0-3], StFttDb::nPlane = 4
    UChar_t quadrant()   const; // detector quadrant [0-3] = A,B,C,D (kFttQuadrantA..D)
    float x() const;  // local mm, NOT cell/strip units. For a point built from one
                      // 1-D cluster this is the cluster's charge-weighted centre on
                      // the measured axis, or the max-strip centre on the other.
    float y() const;  // local mm, same two cases as x()
    float d1() const; // local mm, diagonal-1 coordinate. NEVER SET: nothing calls
                      // setD1 in StRoot, so this is always its default
    float d2() const; // local mm, diagonal-2 coordinate. NEVER SET, as d1()
    float sigmaX() const; // mm, 1 sigma on x() -- NOT "diagonal1" as this used to say.
                      // On the unmeasured axis StFttClusterPointMaker uses the strip
                      // length / sqrt(12), i.e. the along-strip coordinate is only
                      // known to within one strip.
    float sigmaY() const; // mm, 1 sigma on y(); same remark as sigmaX()
    float sigmaXY() const; // mm^2 off-diagonal covariance (a covariance, no sqrt);
                      // 0 for points built from a single 1-D cluster
    int nClusters() const; // Number of parent clusters [1-4] (one per orientation)
    StFttCluster* cluster( size_t i); //  Parent cluster, i in [0, nClusters-1]
    const StThreeVectorD& xyz() const; // GLOBAL STAR position in CENTIMETRES
    std::vector<std::vector<float>> cov() const; // 2x2 covariance of (x,y), mm^2

    UShort_t idTruth() const { return mIdTruth; }
    UShort_t qaTruth() const { return mQaTruth; }

    void setPlane(UChar_t plane);
    void setQuadrant(UChar_t quad);
    void setX(float x);
    void setY(float y);
    void setD1(float d1);
    void setD2(float d2);
    void setSigmaX(float SigmaX);
    void setSigmaY(float SigmaY);
    void setSigmaXY(float SigmaXY);
    void addCluster(StFttCluster* cluster, UChar_t dir);
    void setXYZ(const StThreeVectorD& p3);
    void setCov(std::vector<std::vector<float>> mat);

    void setIdTruth( UShort_t id ) { mIdTruth = id; }
    void setQaTruth( UShort_t qa ) { mQaTruth = qa; }


    void print(int option=0);

private:
    UChar_t mPlane=0;        // [0-3]
    UChar_t mQuadrant=0;     // [0-3] = A,B,C,D
    Float_t  mX=0.0;         // x-position, quadrant-local MILLIMETRES
    Float_t  mY=0.0;         // y-position, quadrant-local MILLIMETRES
    StFttCluster *mClusters[4];
    StThreeVectorD  mXYZ;    // Point position, GLOBAL STAR frame, CENTIMETRES
                             // (mX/mY above are quadrant-local mm -- different frame
                             // AND different unit; there is no separate z member)

    Float_t mD1=0.0;         // 1st diagnoal cluster position
    Float_t mD2=0.0;         // 2nd diagnoal cluster position
    Float_t mSigmaX = -99.;  // sigma for 1D X cluster along the strip direction, it should be the striplength/sqrt(12)
    Float_t mSigmaY = -99.;  // sigma for 1D Y cluster along the strip direction, it should be the striplength/sqrt(12)
    Float_t mSigmaXY = -99.; // off diagonal covariance matrix elements
    std::vector<std::vector<float>> mCov; // Covariance matrix of the point position

    UShort_t mIdTruth=0; // Truth ID
    UShort_t mQaTruth=0; // Truth Quality

    ClassDef(StFttPoint, 4)
};

inline UChar_t StFttPoint::plane() const { return mPlane; }
inline UChar_t StFttPoint::quadrant() const { return mQuadrant; }
inline float StFttPoint::x() const { return mX; } // x position (mm) in local coords.
inline float StFttPoint::y() const { return mY; } // y position (mm) in local coords.
inline float StFttPoint::d1() const { return mD1; } // 1st diagnoal position (mm) in local coords.(along diagnoal direction)
inline float StFttPoint::d2() const { return mD2; } // 2nd diagnoal position (mm) in local coords.(along diagnoal direction)
inline float StFttPoint::sigmaX() const { return mSigmaX; }
inline float StFttPoint::sigmaY() const { return mSigmaY; }
inline float StFttPoint::sigmaXY() const { return mSigmaXY; }
inline StFttCluster* StFttPoint::cluster( size_t i ) { if ( i < 4 ) return mClusters[i]; return nullptr; } //  Parent cluster of the photon.
inline const StThreeVectorD& StFttPoint::xyz() const { return mXYZ; }
inline std::vector<std::vector<float>> StFttPoint::cov() const { return mCov; }
inline void StFttPoint::setPlane(UChar_t plane) { mPlane = plane; }
inline void StFttPoint::setQuadrant(UChar_t quadrant) { mQuadrant = quadrant; }
inline void StFttPoint::setX(float xpos) { mX = xpos; }
inline void StFttPoint::setY(float ypos) { mY = ypos; }
inline void StFttPoint::setD1(float d1) { mD1 = d1; }
inline void StFttPoint::setD2(float d2) { mD2 = d2; }
inline void StFttPoint::setSigmaX( float SigmaX) { mSigmaX = SigmaX; }
inline void StFttPoint::setSigmaY( float SigmaY) { mSigmaY = SigmaY; }
inline void StFttPoint::setSigmaXY( float SigmaXY) { mSigmaXY = SigmaXY; }
inline void StFttPoint::addCluster(StFttCluster* cluster, UChar_t dir) { mClusters[dir] = (cluster); }
inline void StFttPoint::setXYZ(const StThreeVectorD& p3) { mXYZ = p3; }
inline void StFttPoint::setCov(std::vector<std::vector<float>> mat) { mCov = mat; }

#endif  // StFttPoint_h