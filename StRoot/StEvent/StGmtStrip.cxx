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

#include "StGmtStrip.h"
#include <string>

bool gmtStripPtrLessThan::operator() (const StGmtStrip* strip1, const StGmtStrip* strip2) const
{
    return ((strip1 && strip2) ? strip1->getGeoId() < strip2->getGeoId() : 0 );
}


StGmtStrip::StGmtStrip() : StObject() {
  memset(mBeg, 0, mEnd-mBeg+1);
}
int StGmtStrip::mDefaultTimeBin = kGmtNumTimeBins;  // was 2 for the FGT, RW 03/15/13
ostream&  operator<<(ostream& os, const StGmtStrip& v)
{
  os << Form("GmtStrip gId %3i m %3i C %3i Y %1i C %1i p %8.3f",v.getGeoId(), v.getModule(), v.getCoordNum(), v.isY(), v.isC(), v.getPosition());
  os << Form(" Rdo: %2i,Arm: %2i, Apv: %2i, cha: %3i, : ADcs : ",v.getRdo(), v.getArm(), v.getApv(), v.getChannel()); 
  for (Int_t i = 0; i < kGmtNumTimeBins; i++) {if (v.getAdc(i) > 0) {os << Form("%2i:%4i,", i,v.getAdc(i));}}
  os << Form("Sum : %5.2f +/-  %5.2f",v.getAdcSum(), v.getAdcSumRMS());
  return os;
}
void   StGmtStrip::Print(Option_t *option) const {cout << *this << endl;}


