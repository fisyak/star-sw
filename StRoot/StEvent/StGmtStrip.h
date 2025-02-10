#ifndef StGmtStrip_hh
#define StGmtStrip_hh

/**
 * \class StGmtStrip
 * \brief Holds data for the strip in GMT
 * 
 * Data for an individual strip in GMT (based on StFgtStrip).
 *
 * \author K.S. Engle, Jan. 2013
 * \author Richard Witt (witt@usna.edu), Jan. 2013
 * \author Grigory Nigmatkulov (nigmatkulov@gmail.com), Dec. 2020
 */

#include "StObject.h"
#include "StEnumerations.h"
#include "St_base/StMessMgr.h"
#include "TMath.h"
class StGmtStrip : public StObject {    
 public:
  StGmtStrip();
  virtual ~StGmtStrip() {}
    
  // accessors
  Int_t   getGeoId()           const { return mGeoId; }
  Int_t   getModule()          const { return mModule; }
  Int_t   getCoordNum()        const { return mCoordNum; }
  Int_t   isY()                const { return mIsY; }
  Int_t   isC()                const { return mIsC; }
  Float_t getPosition()        const { return mPosition; }
  Short_t getMaxAdc()          const { return mMaxAdc; }
  Short_t getMaxAdcTB()        const { return mMaxAdcTB; }
  Float_t getCharge()          const { return mCharge; }
  Float_t getChargeUncert()    const { return mChargeUncert; }
  Short_t getAdc( Int_t tb )   const { return mAdc[ (tb < 0 || tb >= kGmtNumTimeBins) ? mDefaultTimeBin : tb ];}
  Float_t getAdcSum()          const { return mAdcSum;}
  Float_t getAdcSum()          { 
    mAdcSum = 0;
    mAdcSumRMS = 0;
    Int_t n = 0;
    Float_t ped = getPed();
    Float_t pedRMS = getPedRMS();
    for (Int_t i = kGmtNumTimeBinsForPed; i < kGmtNumTimeBins; i++) {
      if (mAdc[i] < ped || mAdc[i] > kGmtMaxAdc) continue;
      n++;
      mAdcSum    += mAdc[i] - ped;
      mAdcSumRMS += mAdc[i] - ped;
    }
    mAdcSumRMS = TMath::Sqrt(mAdcSumRMS + n*pedRMS*pedRMS);
    return mAdcSum;
  }
  Float_t getAdcSumRMS()        const { return mAdcSumRMS;}
  void    getElecCoords( Int_t& rdo, Int_t& arm,  Int_t& apv,  Int_t& chan ){ rdo = mRdo; arm = mArm; apv = mApv; chan = mChan; }
  Float_t getPedV()          const { return mPed;}
  Float_t getPed()                   {
    Int_t n = 0;
    mPed = 0;
    mPedRMS = 0;
    Float_t ped = 0, ped2 = 0;
    for (Int_t i = 0; i < kGmtNumTimeBinsForPed; i++) {
      if (mAdc[i] < 0 || mAdc[i] > kGmtMaxAdc) continue;
      n++;
      ped  += mAdc[i];
      ped2 += mAdc[i];
    }
    if (n > 0) {
      mPed = ped/n;
      mPedRMS = TMath::Sqrt(ped2/n);
    }
    return mPed;
  }
  Float_t getPedRMS()          const { return mPedRMS;}
  Bool_t  chargeValid()        const { return mCharge != 0 && mCharge != kInvalidChargeValue; }
  Int_t   getRdo()             const { return mRdo; }
  Int_t   getArm()             const { return mArm; }
  Int_t   getApv()             const { return mApv; }
  Int_t   getChannel()         const { return mChan; }
  
  // modifiers
  void setGeoId( Int_t geoId )                 { mGeoId = geoId; }
  void setModule( Int_t module )               { mModule = module; }
  void setCoordNum( Int_t coord )              { mCoordNum = coord; }
  void setIsY( Int_t isy )                     { mIsY = isy; }
  void setIsC( Int_t isy )                     { mIsC = isy; }
  void setPosition( Float_t position )         { mPosition = position; }
  void setAdc    ( Short_t adc, Int_t tb = -1 ){mAdc[ (tb < 0 || tb >= kGmtNumTimeBins) ? mDefaultTimeBin : tb ] = adc;}
  void setCharge ( Float_t charge )            { mCharge = charge; }
  void setChargeUncert ( Float_t chargeUncert ){ mChargeUncert = chargeUncert; }
  void setElecCoords( Int_t rdo, Int_t arm,  Int_t apv,  Int_t chan ){ mRdo = rdo; mArm = arm; mApv = apv; mChan = chan; }
  void invalidateCharge()                      { mCharge = kInvalidChargeValue; }
  void setMaxAdc(Short_t adc);
  
  // query default time bin
  static void setDefaultTimeBin( Int_t tb )    { mDefaultTimeBin = tb; }
  static Int_t getDefaultTimeBin()             { return mDefaultTimeBin; }
  void   Print(Option_t *option="") const;
 protected:
  // data members
  Char_t *mBeg[1];                  //!
  Int_t   mGeoId;                // indexing: 8 modules * 2 APV * 128 channels = 2048
  Int_t   mModule;                // indexing: 8 modules
  Int_t   mCoordNum;                // 0-127 in each dimension (X and Y)
  Int_t   mIsY;                  // is it a pad (as opposed to a strip)?
  Float_t mPosition;                  // coordinate position relative to local origin (in module)
  Short_t mAdc[kGmtNumTimeBins]; // note "StRoot/RTS/src/DAQ_GMT/daq_gmt.h" uses UShort_t
  Short_t mMaxAdc;               // max over the time bins
  Short_t mMaxAdcTB;               // max over the time bins
  Float_t mCharge;               // before GEM, units (C), relation: ADC = ped + charge*gain(r,phi,disc)
  Float_t mChargeUncert;
  Int_t   mRdo, mArm, mApv, mChan; // elec coords, straight out of the DAQ file
  Int_t   mIsC; //is used in a cluster ?
  Int_t   mAdcSum;
  Int_t   mAdcSumRMS;
  Float_t mPed;
  Float_t mPedRMS;
  Char_t *mEnd[1];                  //!
  
  static Int_t mDefaultTimeBin;
  
  // to signify an invalid value of the charge
  enum { kInvalidChargeValue = -10000 };
  ClassDef(StGmtStrip,1)
};
ostream&              operator<<(ostream& os, StGmtStrip const & v);

// Functor for sorting the strips in the strip weight map.
struct gmtStripPtrLessThan {
    Bool_t operator() (const StGmtStrip* strip1, const StGmtStrip* strip2) const;
};
#endif /* StGmtStrip_hh */
