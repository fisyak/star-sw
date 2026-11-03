/***************************************************************************
 * StFttDb.h
 * jdb Feb, 2022
 ***************************************************************************
 *
 * Description: FTT DB Utility
 ***************************************************************************/

#ifndef STFTTDB_H
#define STFTTDB_H

#ifndef StMaker_H
#include "StMaker.h"
#endif
#include "StEvent/StEnumerations.h"
#include <stdint.h>
#include <map>
#include <vector>


class StFttRawHit;
class StFttCluster;
class StFttPoint;

struct FttDataWindow {
    Short_t uuid;
    UChar_t mode;
    Short_t min;
    Short_t max;
    Short_t anchor;
};


class St_fttHardwareMap;
class St_fttDataWindowsB;

class StFttDb : public TDataSet {

public: 
  StFttDb(const char *name="fttDb");
  virtual       ~StFttDb();
  int  Init();
  int  InitRun(int runNumber);
 
  void SetDebug(int v=1) {mDebug=v;}  //! debug level
  void setDebug(int v=1) {mDebug=v;}  //! debug level
  void setDbAccess(int v=1);  //! enable(1) or disable(0) offline DB access
  void setRun(int run);       //! set run# 

  static size_t uuid( StFttRawHit * h, bool includeStrip = false ) ;
  static size_t uuid( StFttCluster * c ) ;
  static size_t vmmId( StFttRawHit * h ) ;

  // HARDWARE Mapping StFttRawHits
    uint16_t packKey( int feb, int vmm, int ch ) const;
    void unpackKey( int key, int &feb, int &vmm, int &ch ) const;
    uint16_t packVal( int row, int strip ) const;
    void unpackVal( int val, int &row, int &strip ) const;
    void loadHardwareMapFromFile( std::string fn );
    void loadHardwareMapFromDb( St_fttHardwareMap * );
    void loadDataWindowsFromFile( std::string fn );
    void loadDataWindowsFromDb( St_fttDataWindowsB * );

    // FTT was retired with fixed hardware geometry; strip center/edge/length
    // tables below are compiled-in constants populated by initStripGeometry().
    void initStripGeometry();


    UChar_t plane( StFttRawHit * hit );
    UChar_t quadrant( StFttRawHit * hit );
    UChar_t fob( StFttRawHit * hit );
    UChar_t rob( StFttRawHit * hit );
    UChar_t rob( StFttCluster * clu );

    static double stripPitch; // mm
    static double gapPitch; // mm
    static double stripWidth; // mm
    static double rowLength; // mm
    static double HVStripShift; // mm
    static double DiagStripShift; // mm
    static double lowerQuadOffsetX; //mm
    static double idealPlaneZLocations[4];

    static const size_t nPlane        = 4;
    static const size_t nQuadPerPlane = 4;
    static const size_t nFobPerQuad   = 6;
    static const size_t nVMMPerFob    = 4;
    static const size_t nChPerVMM     = 64;
    static const size_t nStripGroupEdge = 8;

    //name for the cluster direction
    static TString Direction_name[nQuadPerPlane+1];
    static double FirstStripEdge[2]; //mm

    //for idealPlaneZLocations_QuadX, now using the cm as unit because that in the old version this using the cm as unit
    static double LocalStripZLocations[nPlane];
    static double idealPlaneZLocations_QuadA[nPlane];//cm
    static double idealPlaneZLocations_QuadB[nPlane];
    static double idealPlaneZLocations_QuadC[nPlane];
    static double idealPlaneZLocations_QuadD[nPlane];
    static double X_shift_QuadA[nQuadPerPlane];//mm , x shift from pin hole to (0,0)
    static double X_shift_QuadB[nQuadPerPlane];//mm , x shift from pin hole to (0,0)
    static double X_shift_QuadC[nQuadPerPlane];//mm , x shift from pin hole to (0,0)
    static double X_shift_QuadD[nQuadPerPlane];//mm , x shift from pin hole to (0,0)
    static double Y_shift_QuadA[nQuadPerPlane];//mm , y shift from pin hole to (0,0)
    static double Y_shift_QuadB[nQuadPerPlane];//mm , y shift from pin hole to (0,0)
    static double Y_shift_QuadC[nQuadPerPlane];//mm , y shift from pin hole to (0,0)
    static double Y_shift_QuadD[nQuadPerPlane];//mm , y shift from pin hole to (0,0)
    static double YX_StripGroupEdge[nStripGroupEdge]; // mm , from left to right, reference : https://drupal.star.bnl.gov/STAR/system/files/StFttPointMaker_ZhenWang_20221013_fwdsoftmeeting.pdf Slide 14
    static double D_StripGroupEdge[nStripGroupEdge]; // mm , from left to right, reference : https://drupal.star.bnl.gov/STAR/system/files/StFttPointMaker_ZhenWang_20221013_fwdsoftmeeting.pdf Slide 14
    static double X_StripGroupEdge[nStripGroupEdge]; // mm , from left to right, reference : https://drupal.star.bnl.gov/STAR/system/files/
    static double Y_StripGroupEdge[nStripGroupEdge]; // mm , from left to right, reference : https://drupal.star.bnl.gov/STAR/system/files/StFttPointMaker_ZhenWang_20221013_fwdsoftmeeting.pdf Slide 14

    static const size_t nQuad = nQuadPerPlane * nPlane; // 4 * 4 = 16 Total number of Quadrants
    static const size_t nRob = nQuad;

    static const size_t nFobPerPlane = nFobPerQuad * nQuadPerPlane; // 4 * 6 = 24 Total number of FOB
    static const size_t nFob         = nFobPerPlane * nPlane; // 24 * 4 = 96 total FOB;

    static const size_t nVMMPerQuad  = nFobPerQuad * nVMMPerFob; // 6 * 4 = 24 VMM per Quad
    static const size_t nVMMPerPlane = nVMMPerQuad * nQuadPerPlane; // 24 * 4 = 96 VMM per Plane
    static const size_t nVMM         = nVMMPerPlane * nPlane; // 96 * 4 = 384 VMM total

    static const size_t nChPerFob    = nVMMPerFob * nChPerVMM; // 4 * 64 = 256 VMM per Plane
    static const size_t nChPerQuad   = nChPerFob * nFobPerQuad; // 256 * 6 = 1536 VMM per Plane
    static const size_t nChPerPlane  = nChPerQuad * nQuadPerPlane; // 1536 * 4 = 6144 Ch per Plane
    static const size_t nCh          = nChPerPlane * nPlane; // 6144 * 4 = 24576 Ch per Plane

    static const size_t maxADC       = 1024 + 1; // 10 bits;
    static const size_t maxBCID      = 4096 + 1; // 12 bits;
    static const int minTb           = -32768 - 1000; // get the under and overflow
    static const int maxTb           = 32768 + 1000;
    
    static const size_t nRowsPerQuad       = 5; // 0 - 2 (Horizontal or Vertical) + 3, 4 for Diagonal
    static const size_t nStripOrientations = 5; // real orientations (4) + 1 for unkown                       = 5 total
    static const size_t maxStripPerRow     = 166; // max number of strips in a row (only row 0 has this many)
    
    static vector<string> orientationLabels;



    UChar_t orientation( StFttRawHit * hit );
    UChar_t getOrientation( int rob, int feb, int vmm, int row ) const;
    bool hardwareMap( int rob, int feb, int vmm, int ch, int &row, int &strip, UChar_t &orientation ) const;
    // Fills the raw hit's mapping and, from the strip tables, its centre, edges
    // and length -- all in mm. NOTE the edge convention: only the DIAGONAL rows
    // (3,4) have measured left/right edges, because only there do the strips
    // need individual pad bounds. Horizontal and vertical strips keep the
    // initial -1, i.e. "not set", and must be bounded from the centre and the
    // pitch instead. -1 is outside the quadrant, so it cannot be mistaken for a
    // position; nothing in the chain reads the edges today.
    bool hardwareMap( StFttRawHit * rawHit ) const;

    // ---- quadrant-local -> global: UNITS ARE MIXED, and deliberately so ------
    // Both functions return a translation (dx,dy,dz) and a reflection (sx,sy,sz),
    // with sx,sy,sz in {+1,-1}. The translation is NOT in one unit:
    //
    //     dx, dy : MILLIMETRES, from X_shift_Quad* / Y_shift_Quad*
    //     dz     : CENTIMETRES, from idealPlaneZLocations_Quad*
    //
    // That is not a choice we made here: every quadrant-local x/y in the FTT
    // chain is in mm (StFttDb's strip map, StFttCluster::x(), StFttPoint::x()/y())
    // while every z in STAR is in cm, so dx,dy match what they are added to and
    // dz matches what it is added to. The mix only becomes a trap at the point
    // where the three are packed into one global vector, because
    // StFttPoint::xyz() is documented as cm.
    //
    // A CALLER MUST THEREFORE SCALE x AND y, NOT z:
    //
    //     global.set( ((x*sx)+dx)/10.0, ((y*sy)+dy)/10.0, z+dz );   // cm
    //
    // and must scale any covariance built from mm lengths by 1/100, since
    // variance goes as length squared.
    void getGloablOffset( UChar_t plane, UChar_t quad, float &dx, float &sx, float &dy, float &sy, float &dz, float &sz );
    void getGloablOffset_ClusterPoint( UChar_t plane, UChar_t quad, float &dx, float &sx, float &dy, float &sy, float &dz, float &sz );
    bool reverseHardwareMap(int &rob, int &feb, int &vmm, int &ch, int plane, int quad, int row, int strip, UChar_t &orientation) const;
    // (row,strip) is AMBIGUOUS: the same pair exists once per orientation in the
    // real map (H and V, or DiagonalH and DiagonalV on rows 3,4). This 5-argument
    // form has no rob and so cannot resolve it -- it returns the first channel on
    // record, which is the pre-existing behaviour. Simulation and embedding, where
    // the wrong orientation means charge on the wrong strip, must use the
    // 9-argument form above and pre-set orientation.
    bool reverseHardwareMap( int &feb, int &vmm, int &ch, int row, int strip ) const;

    enum TimeCutMode {
      CalibratedBunchCrossingMode = 0,
      TimebinMode = 1
    };

    void setTimeCut(TimeCutMode mode, int low=-70, int high=30)
    {
        mUserDefinedTimeCut = true;
        mTimeCutMode=mode; 
        mTimeCutLow=low; 
        mTimeCutHigh=high;
    }

    void getTimeCut( StFttRawHit * hit, int &mode, int &l, int &h );

 private:
  int   mDbAccess=1;                     //! enable(1) or disabe(0) DB access
  int   mRun=0;                          //! run#
  // int   mDebug=1;                     //! >0 dump tables to text files    
  int   mDebug=0;                        //! >0 dump tables to text files    

  bool mUserDefinedTimeCut = false;
  TimeCutMode mTimeCutMode;
  int mTimeCutLow, mTimeCutHigh;

  std :: map< uint16_t , uint16_t > mMap;
  std :: map< uint16_t , std::vector<uint16_t> > rMap; // reverse map -- a given (row,strip) has one channel per orientation (H and V both exist at the same row/strip in the real hardware map, confirmed by scanning the forward map), so this must hold all of them, not just the last one loaded
  //  data windows map
  std :: map< uint16_t , FttDataWindow > dwMap;
  std :: map< int , Float_t > scMapXY; // strip center map 
  std :: map< int , Float_t > scMapDiag; // strip center map 
  std :: map< int , Float_t > slMapRow1; // strip length map Row1
  std :: map< int , Float_t > slMapRow2; // strip length map Row2
  std :: map< int , Float_t > slMapRow3; // strip length map Row3
  std :: map< int , Float_t > slMapRow4; // strip length map Row4
  std :: map< int , Float_t > slMapRow5; // strip length map Row5
  std :: map< int , Float_t > seMapDiagLeft; // strip left edge map, just for the diagonal strips 
  std :: map< int , Float_t > seMapDiagRight; // strip right edge map, just for the diagonal strips

  ClassDef(StFttDb,1)   //StAF chain virtual base class for Makers        
};

#endif

