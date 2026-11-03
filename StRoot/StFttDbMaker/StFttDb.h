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

class St_Survey;

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

    // ---- geometry offsets: from the DB (default) or the original hardcoded numbers ----
    // The X_shift_Quad* / Y_shift_Quad* / idealPlaneZLocations_Quad* statics above are
    // the ORIGINAL hardcoded numbers. They stay as the placeholder, and are exactly what
    // setUseDbGeometry(false) restores, so the old behaviour is always one call away.
    //
    // With the DB on (the default) the hardcoded origins above are NOT used at all.
    // The effective offset is built from the AGML nominal instead:
    //     AGML placeholder + stgcOnTpc + stationOnStgc[station] + pentOnStation[4*station+pent]
    // The tables were written as (StFttDb origin - AGML placeholder) + alignment, so this
    // reproduces the true position exactly while being the SAME quantity AGML computes.
    // Geometry and hit positions then come from one source rather than two kept in step
    // by hand, and an alignment iteration only has to touch the table.
    // with pent = (4 - quad) % 4: AGML orders the four pentagons A,D,C,B by rotation
    // while StFttDb numbers its quadrants A,B,C,D. That map was measured from the built
    // geometry, see FwdGeomUtils::fttChamberIndex and script/fttQuadConvention.C.
    //
    // Units: Survey translations are cm. X/Y_shift are mm, so t0/t1 are scaled by 10;
    // t2 adds straight to the z locations, which are already cm.
    //
    // Rows are taken in table order, which is what AGML's <Misalign row="N"/> indexes.
    /// Choose where the per-quadrant offsets come from. Call before InitRun.
    /// \param v true (default) = AGML placeholder plus the Geometry/ftt survey
    ///          tables; false = the original hardcoded numbers.
    void setUseDbGeometry( bool v ) { mUseDbGeometry = v; }

    /// Which source was REQUESTED. \sa geometryFromDb for what actually happened.
    bool useDbGeometry() const      { return mUseDbGeometry; }

    /// True once survey tables have actually been applied. False means the
    /// hardcoded numbers are in use, either because setUseDbGeometry(false) was
    /// called or because the tables were missing.
    bool geometryFromDb() const     { return mGeoFromDb; }

    /// Put the hardcoded offsets back and clear geometryFromDb().
    void resetGeometryToHardcoded();

    /// Apply the three Geometry/ftt survey tables to the offsets returned by
    /// xShift(), yShift() and zLoc(). Called by StFttDbMaker::InitRun; there is no
    /// need to call it directly.
    /// \param stgcOnTpc      whole-detector placement, 1 row
    /// \param stationOnStgc  one row per station
    /// \param pentOnStation  one row per pentagon, indexed 4*station + pent
    /// \return the number of tables applied, 0 if none were usable
    int  loadGeometryFromDb( St_Survey *stgcOnTpc, St_Survey *stationOnStgc, St_Survey *pentOnStation );
    // The values getGloablOffset*() actually uses. Prefer these over the statics, which
    // are only the placeholder once the DB is in play.
    /// Effective x offset of a quadrant, in mm. \param quad 0..3 \param plane 0..3
    double xShift( int quad, int plane ) const { return mXShift[quad][plane]; }
    /// Effective y offset of a quadrant, in mm. \param quad 0..3 \param plane 0..3
    double yShift( int quad, int plane ) const { return mYShift[quad][plane]; }
    /// Effective z position of a quadrant, in cm. \param quad 0..3 \param plane 0..3
    double zLoc  ( int quad, int plane ) const { return mZLoc  [quad][plane]; }

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
    // The inverse of hardwareMap(): which channel reads a given strip. Note that
    // (row,strip) is AMBIGUOUS on its own -- the same pair exists once per
    // orientation in the real map (H and V, or DiagonalH and DiagonalV on rows
    // 3,4) -- so rob is needed to resolve it, and orientation is in/out: pre-set
    // it to pick a specific one, or leave it kFttUnknownOrientation to take
    // whichever comes first. A caller that gets this wrong puts charge on the
    // wrong strip, which is why there is no overload that drops rob.
    bool reverseHardwareMap(int &rob, int &feb, int &vmm, int &ch, int plane, int quad, int row, int strip, UChar_t &orientation) const;

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

    // ---- per-run VMM time anchors (Calibrations/ftt/fttDataWindowsB) ------------
    // VMM dbcid anchors are reset at random at every run start, so an anchor is only
    // meaningful for the run it was measured in. STAR DB entries carry a begin time
    // only, so St_db_Maker hands a run with no entry of its own the PREVIOUS run's
    // entry. Hence the RUN STAMP written by script/fttDataWindow_db.C into the spare
    // slot 384 (uuid -1, min = run/10000, max = run%10000), and anchors are used only
    // when StFttDbMaker has confirmed stamp == run being reconstructed.
    /// Run number the loaded data-window entry was measured for, -1 if the entry
    /// carries no stamp (the legacy global entry).
    int  dataWindowStampRun() const            { return mDwStampRun; }

    /// Declare whether the loaded anchors may be used. Set by StFttDbMaker once it
    /// has compared dataWindowStampRun() with the run being reconstructed; do not
    /// call it from anywhere else.
    void setDataWindowAnchorsValid( bool v )   { mDwAnchorsValid = v; }

    /// True if getAnchor() can return a stored anchor for this run.
    bool dataWindowAnchorsValid() const        { return mDwAnchorsValid; }
    // true, with the anchor, only if anchors are validated for this run AND this VMM
    // has one (anchor -1 in the table = no usable calibration for that VMM)
    /// Stored dbcid anchor for a hit's VMM.
    /// \param hit     the raw hit, used only for its VMM id
    /// \param anchor  set to the stored anchor on success, untouched otherwise
    /// \return true only if the anchors are valid for this run AND this VMM has one;
    ///         false means the caller must derive the anchor itself.
    bool getAnchor( StFttRawHit * hit, Short_t &anchor );
    // Forget any previously loaded windows/anchors/stamp. Called before every load so a
    // run whose fetch fails cannot silently keep the previous run's entry.
    /// Forget the loaded windows, anchors and stamp. Called before every load so a
    /// failed one cannot leave the previous run's values in place.
    void clearDataWindows() { dwMap.clear(); mDwStampRun = -1; mDwAnchorsValid = false; mDwFallbackWarned = false; }

 private:
  bool   mUseDbGeometry = true;          //!< requested source, \sa setUseDbGeometry
  bool   mGeoFromDb     = false;         //!< true once survey tables were applied
  double mXShift[nQuadPerPlane][nPlane]; //!< effective x offset per [quad][plane], mm
  double mYShift[nQuadPerPlane][nPlane]; //!< effective y offset per [quad][plane], mm
  double mZLoc  [nQuadPerPlane][nPlane]; //!< effective z position per [quad][plane], cm

  int   mDbAccess=1;                     //! enable(1) or disabe(0) DB access
  int   mRun=0;                          //! run#
  // int   mDebug=1;                     //! >0 dump tables to text files    
  int   mDebug=0;                        //! >0 dump tables to text files    

  bool mUserDefinedTimeCut = false;
  // Returned by getTimeCut() for a VMM with no data-window entry. These used to have
  // no initializer, so such a VMM got an undefined mode and window -- and since
  // StFttClusterMaker defaults to kTimeCutModeDB, that reaches every chain that does
  // not call SetTimeCut() (BFC production, simulation). A VMM is "missing" when no
  // fttDataWindowsB entry was loaded at all (query time before 2021-10-01, no DB
  // access), when an entry's uuid column skips ids, or when the hit's vmmId is out of
  // range. Default = calibrated time, [-65, 100]: exactly the global DB entry in use
  // since 2021-10-01, so a missing entry behaves like the DB default.
  TimeCutMode mTimeCutMode = CalibratedBunchCrossingMode;
  int mTimeCutLow  = -65;
  int mTimeCutHigh = 100;
  bool mDwFallbackWarned = false;  //!< getTimeCut() has already warned about a missing entry

  std :: map< uint16_t , uint16_t > mMap;
  std :: map< uint16_t , std::vector<uint16_t> > rMap; // reverse map -- a given (row,strip) has one channel per orientation (H and V both exist at the same row/strip in the real hardware map, confirmed by scanning the forward map), so this must hold all of them, not just the last one loaded
  //  data windows map
  std :: map< uint16_t , FttDataWindow > dwMap;
  int  mDwStampRun = -1;          //!< run the loaded entry was measured for, -1 = unstamped
  bool mDwAnchorsValid = false;   //!< anchors may be used, \sa setDataWindowAnchorsValid
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

