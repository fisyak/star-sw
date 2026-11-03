/***************************************************************************
 *
 * $Id: StFttRawHit.h,v 1.0 2021/11/18 18:52:38 jdb Exp $
 *
 * Author: Philipp Weidenkaff, April 2018
 ***************************************************************************
 *
 * Description: Data class for sTGC raw hit in StEvent
 *
 ***************************************************************************/
#ifndef STFTTRAWHIT_H
#define STFTTRAWHIT_H

#include <Stiostream.h>
#include "StObject.h"
#include "StEnumerations.h"


class StFttRawHit : public StObject {
public:
    /**
    ** @brief Default constructor.
    **/
    StFttRawHit();

    StFttRawHit(    UChar_t mSector, UChar_t mRDO, UChar_t mFEB, 
                    UChar_t mVMM, UChar_t mChannel, UShort_t mADC, 
                    UShort_t mBCID, Short_t mTB, Short_t mBCIDDelta );

    ~StFttRawHit() {}

    void setRaw(    UChar_t mSector, UChar_t mRDO, UChar_t mFEB, 
                    UChar_t mVMM, UChar_t mChannel, UShort_t mADC, 
                    UShort_t mBCID, Short_t mTB, Short_t mBCIDDelta );

    void setMapping( UChar_t mPlane, UChar_t mQuadrant, UChar_t mRow, UChar_t mStrip, UChar_t mOrientation );

    void setStripEdges( Float_t mStripCenter, Float_t mStripLeftEdge, Float_t mStripRightEdge );

    void setStripLength( Float_t mStripLength );

    void setTime( Short_t mTime ) { this->mTime = mTime; }
    void setIdTruth( UShort_t id ) { mIdTruth = id; }
    void setQaTruth( UShort_t qa ) { mQaTruth = qa; }

    // constant getters. Ranges, units and sentinels are documented once, on the
    // members these return -- see the protected block below.
    UChar_t sector() const;         // [1-4], one-based: plane = sector-1
    UChar_t rdo() const;            // [1-4], one-based: quadrant = rdo-1
    UChar_t feb() const;            // [0-5]
    UChar_t vmm() const;            // [0-3]
    UChar_t channel() const;        // [0-63]
    UShort_t adc() const;           // [0-1023], 10 bit
    UShort_t bcid() const;          // [0-4095], 12 bit
    Short_t dbcid() const;          // bcid - trigger bcid, in bunch-crossing ticks
    Short_t tb() const;             // from the trigger
    Short_t time() const;           // calibrated dbcid

    UChar_t plane() const;          // [0-3],   255 = unmapped
    UChar_t quadrant() const;       // [0-3],   kFttUnknownQuadrant (4) = unmapped
    UChar_t row() const;            // [0-4],   255 = unmapped
    UChar_t strip() const;          // per-row set from StFttDb, 255 = unmapped
    Float_t stripCenter() const;    // mm, quadrant-local; -1 = unmapped
    Float_t stripLength() const;    // mm; -1 = unmapped
    Float_t stripLeftEdge() const;  // mm, quadrant-local; -1 = unmapped
    Float_t stripRightEdge() const; // mm, quadrant-local; -1 = unmapped
    UChar_t orientation() const;    // [0-3],   kFttUnknownOrientation (4) = unmapped
    UShort_t idTruth() const { return mIdTruth; }
    UShort_t qaTruth() const { return mQaTruth; }

protected:
    // ---- electronics, as read out -------------------------------------------
    UChar_t mSector;      // DAQ sector, ONE-BASED [1-4]: StFttDb takes the plane as
                          // sector-1 (StFttDb.cxx:110, :851), so sector 1-4 <-> plane 0-3
    UChar_t mRDO;         // readout board, ONE-BASED [1-4]: StFttDb takes the quadrant
                          // as rdo-1, so rdo 1-4 <-> quadrant A-D
    UChar_t mFEB;         // front-end board within the RDO [0-5], StFttDb::nFobPerQuad = 6
                          // (StFttDb's lookups take feb+1, i.e. they are 1-based there)
    UChar_t mVMM;         // VMM chip on the FEB [0-3], StFttDb::nVMMPerFob = 4
    UChar_t mChannel;     // channel in the VMM [0-63], StFttDb::nChPerVMM = 64
    UShort_t mADC;        // VMM amplitude, 10 bit [0-1023] (zero-suppressed, so the
                          // low end is the threshold, ~16 in Run 22 data)
    UShort_t mBCID;       // bunch-crossing ID from the VMM, 12 bit [0-4095]
    Short_t mTB;          // from the trigger
    Short_t mBCIDDelta;   // mBCID minus the trigger BCID, in 106 ns ticks; wraps
                          // through the 4096 range, so both signs occur
    Short_t mTime;        // calibrated BCID Delta

    // ---- mapped information -------------------------------------------------
    // Filled by StFttHitCalibMaker/StFttDb from the electronics address. All five
    // carry a sentinel when the mapping did not cover the channel, so test for it
    // before using them: 255 for plane/row/strip, kFttUnknownQuadrant (4) and
    // kFttUnknownOrientation (4) for the other two. The ctor sets those sentinels.
    UChar_t mPlane;       // sTGC plane (station) [0-3], StFttDb::nPlane = 4; 255 = unmapped
    UChar_t mQuadrant;    // quadrant [0-3] = A,B,C,D (kFttQuadrantA..D);
                          // kFttUnknownQuadrant (4) = unmapped
    UChar_t mRow;         // strip row in the quadrant [0-4], StFttDb::nRowsPerQuad = 5:
                          // rows 0-2 carry the X/Y strips, rows 3-4 the diagonals
                          // (StFttDb::stripCenter enforces exactly that); 255 = unmapped
    UChar_t mStrip;       // strip index within the row. The valid set per row is
                          // data-driven, held by StFttDb's strip-centre maps; at most
                          // StFttDb::maxStripPerRow = 166 strips, which only row 0
                          // reaches; 255 = unmapped
    UChar_t mOrientation; // [0-3] = kFttHorizontal, kFttVertical, kFttDiagonalH,
                          // kFttDiagonalV; kFttUnknownOrientation (4) = unmapped

    UShort_t mIdTruth;    // simulation track id; 0 = no MC association. Set by
                          // StFttSlowSimMaker (and the fast sim / cluster-point
                          // maker set it on points); always 0 on real data.
    UShort_t mQaTruth;    // truth quality. NOT filled by any FTT maker today --
                          // nothing calls setQaTruth in the FTT chain, so this is
                          // always 0. Kept for schema symmetry with the other
                          // detectors; give it a meaning before relying on it.

    // ---- strip geometry: MILLIMETRES, in the QUADRANT-LOCAL frame -----------
    // mm, not cm. StFttDb holds the strip maps in mm (stripPitch 3.2, rowLength
    // 180, FirstStripEdge) and converts to cm only when it builds the global
    // transform (mXShift/10.0). StFttDb::stripEdges() fills these four straight
    // out of those maps, so they inherit mm. All four are -1 when the mapping did
    // not resolve the channel -- that is the value stripEdges() leaves on failure,
    // not a position.
    Float_t mStripCenter;     // centre of the strip along its MEASURED coordinate
    Float_t mStripLeftEdge;   // low-coordinate end of the strip
    Float_t mStripRightEdge;  // high-coordinate end of the strip
    Float_t mStripLength;     // strip length; the UNmeasured coordinate along the
                              // strip is only known to within this (see StFttPoint)

    ClassDef( StFttRawHit, 5 );
};

ostream& operator << ( ostream&, const StFttRawHit& digi ); // Printing operator

inline UChar_t  StFttRawHit::sector()      const { return mSector;      };
inline UChar_t  StFttRawHit::rdo()         const { return mRDO;         };
inline UChar_t  StFttRawHit::feb()         const { return mFEB;         };
inline UChar_t  StFttRawHit::vmm()         const { return mVMM;         };
inline UChar_t  StFttRawHit::channel()     const { return mChannel;     };
inline UShort_t StFttRawHit::adc()         const { return mADC;         };
inline UShort_t StFttRawHit::bcid()        const { return mBCID;        };
inline Short_t  StFttRawHit::dbcid()       const { return mBCIDDelta;   };
inline Short_t  StFttRawHit::tb()          const { return mTB;          };
inline Short_t  StFttRawHit::time()        const { return mTime;        };

inline UChar_t  StFttRawHit::plane()       const { return mPlane;       };
inline UChar_t  StFttRawHit::quadrant()    const { return mQuadrant;    };
inline UChar_t  StFttRawHit::row()         const { return mRow;         };
inline UChar_t  StFttRawHit::strip()       const { return mStrip;       };
inline UChar_t  StFttRawHit::orientation() const { return mOrientation; };
inline Float_t  StFttRawHit::stripCenter() const { return mStripCenter;};
inline Float_t  StFttRawHit::stripLength() const { return mStripLength;};
inline Float_t  StFttRawHit::stripLeftEdge() const { return mStripLeftEdge; };
inline Float_t  StFttRawHit::stripRightEdge() const { return mStripRightEdge; };


#endif // STETOFDIGI_H
