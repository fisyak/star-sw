/***************************************************************************
 *
 * $Id: StTpcRawData.h,v 2.14 2018/09/27 22:01:24 ullrich Exp $
 *
 * Author: Yuri Fisyak, Mar 2008
 ***************************************************************************/
#ifndef StTpcRawData_h
#define StTpcRawData_h

#include "StObject.h"
#include <vector>
#include <map>
#include <utility>
#include "StSequence.hh"
#include "StTpcPixel.h"
#include "StDetectorDbMaker/St_tpcPadConfigC.h"
#include "StMemoryPool.hh"
#define __MaxNumberOfTimeBins__ 512
class StDigitalPixel {
 public:
  StDigitalPixel(Short_t adc=0, Int_t Idt=0): mAdc(adc), mIdt(Idt) {}
  virtual ~StDigitalPixel() {}
  Short_t  adc()   const {return mAdc;}
  Int_t    idt()   const {return mIdt;}
#if 1
  void* operator new(size_t) { return mPool.alloc(); }
  void  operator delete(void* p)  { mPool.free(p); }
#endif
 private:
  Short_t  mAdc;
  Int_t    mIdt; 
  static StMemoryPool mPool;
};
typedef std::map<UShort_t,StDigitalPixel>    StDigitalTimeBins;
typedef std::vector<StDigitalTimeBins>       StDigitalPadRow;
typedef std::vector<StDigitalPadRow>         StDigitalSector;
typedef std::vector<StTpcPixel>              StVectPixel;
typedef std::vector<StSequence>              StVecSequence;
typedef std::vector<Int_t*>                  StVecIds;
typedef std::vector<UChar_t>                 StVecPads;
typedef std::vector<UChar_t> 	             StVecUChar;
typedef std::vector<Int_t> 	             StVecInt;

class StTpcDigitalSector : public StObject {
public:
  StTpcDigitalSector(Int_t sector);
    virtual ~StTpcDigitalSector() {}
    // access functions
    const StDigitalTimeBins* timeBinsOfRowAndPad(Int_t rowN, Int_t padN) const { return (&mData[(rowN-1)][(padN-1)]);}
    StDigitalTimeBins*       timeBinsOfRowAndPad(Int_t rowN, Int_t padN)       { return (&mData[(rowN-1)][(padN-1)]);}
    StDigitalPadRow*         padsOfRow(Int_t rowN)                             { return (&mData[(rowN-1)]);}
    StDigitalSector*         rows()                                            { return (&mData);}
    
    Int_t  numberOfRows()             		        const    { return mData.size();}
    Int_t  numberOfPadsInRow(Int_t rowN)		const    { return mData[(rowN-1)].size();}
    Int_t  numberOfTimeBins(Int_t rowN, Int_t padN) 	const    { return mData[(rowN-1)][(padN-1)].size();}
    
    // Adding
    void   assignTimeBins(Int_t row , Int_t pad, StDigitalTimeBins*);
    Int_t  getTimeAdc(Int_t row, Int_t pad, Short_t ADCs[__MaxNumberOfTimeBins__], 
		      Int_t IDTs[__MaxNumberOfTimeBins__]); // with  8 => 10 conversion
    Int_t  getTimeAdc(Int_t row, Int_t pad, UChar_t  ADCs[__MaxNumberOfTimeBins__], 
		      Int_t IDTs[__MaxNumberOfTimeBins__]);
    Int_t  putTimeAdc(Int_t row, Int_t pad, Short_t *ADCs, UShort_t *IDTs);     // with 10 =>  8 conversion
    Int_t  putTimeAdc(Int_t row, Int_t pad, UChar_t  *ADCs, UShort_t *IDTs);
    Int_t  putTimeAdc(Int_t row, Int_t pad, Short_t *ADCs, Int_t *IDTs = 0);     // with 10 =>  8 conversion
    Int_t  putTimeAdc(Int_t row, Int_t pad, UChar_t  *ADCs, Int_t *IDTs = 0);
    void   setSector(Int_t sector) {mSector = sector;} 
    void   clear();
    Int_t  cleanup();
    virtual void   Print(const Option_t *opt="") const;
    virtual Int_t  PrintTimeAdc(Int_t row, Int_t pad) const;
    StTpcDigitalSector &operator+= (StTpcDigitalSector& v);
    Int_t numberOfPadsAtRow(Int_t row) const {return (row > 0 && row <= mNoRows) ? St_tpcPadConfigC::instance()->padsPerRow(mSector, row) : 0;}
    StTpcDigitalSector& operator=(const StTpcDigitalSector&);
    Int_t sector() {return mSector;}
    Int_t NoRows() {return mNoRows;}
 private:
    StTpcDigitalSector(const StTpcDigitalSector&);
    StDigitalSector       mData;
    Int_t                 mSector;
    StVecPads             mPadList;
    StVecSequence         mSequence;
    StVecIds              mIds;
    Int_t                 mNoRows;
    ClassDef(StTpcDigitalSector,2)
};
class StTpcRawData : public StObject {
 public:
    StTpcRawData(Int_t noSectors = 24) {setNoSectors(noSectors);}
    virtual ~StTpcRawData() {clear();}
    UInt_t size() {return mSectors.size();}
    UInt_t getNoSectors() {return size();}
    StTpcDigitalSector *GetSector(UInt_t sector) {return sector > 0 && sector <= size() ? mSectors[sector-1] : 0;}
    StTpcDigitalSector *getSector(UInt_t sector) {return GetSector(sector);}
    Int_t  getVecOfPixels(StVectPixel &pixels, Int_t sector, Int_t row, Int_t padMin = 1, Int_t padMax = -1, 
			  Int_t tMin = 0, Int_t tMax = -1);
    void   setNoSectors(UInt_t noSectors = 0) {mSectors.resize(noSectors); for (UInt_t i = 0; i < noSectors; i++) mSectors[i] = 0;} 
    void   setSector(UInt_t sector, StTpcDigitalSector* digitSector);
    void   clear() {Clear();}
    void   Clear(const Option_t *opt = ""); 
    StTpcRawData &operator+= (StTpcRawData& v);
    virtual void Print(const Option_t *opt="") const; 
    const std::vector<StTpcDigitalSector*> &Sectors() {return *&mSectors;}
 private:
    std::vector<StTpcDigitalSector*> mSectors;
    ClassDef(StTpcRawData,1)
 };
#endif
