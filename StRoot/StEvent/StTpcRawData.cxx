/***************************************************************************
 *
 * $Id: StTpcRawData.cxx,v 2.18 2018/04/10 11:32:08 smirnovd Exp $
 *
 * Author: Yuri Fisyak, Mar 2008
  **************************************************************************/
#include "StTpcRawData.h"
#include "Riostream.h"
#include "TError.h"
#include <assert.h>
#include "TMath.h"
#include "StDaqLib/TPC/trans_table.hh"
#include "StDetectorDbMaker/St_tpcPadConfigC.h"
StMemoryPool StDigitalPixel::mPool(sizeof(StDigitalPixel));

//________________________________________________________________________________
StTpcDigitalSector::StTpcDigitalSector(Int_t sector) : mSector(sector) {
  mNoRows = St_tpcPadConfigC::instance()->padRows(sector);
  for(Int_t row=1; row <= mNoRows; row++) {
    StDigitalPadRow    padRow;
    Int_t NoPads = St_tpcPadConfigC::instance()->numberOfPadsAtRow(sector,row);
    padRow.resize(NoPads);
    mData.push_back(padRow);
  }
}
//________________________________________________________________________________
void StTpcDigitalSector::clear() {// clears only the time bins
  for(UInt_t row=0; row<mData.size(); row++) {
    for(UInt_t ipad=0; ipad<mData[row].size(); ipad++) {
      mData[row][ipad].clear();
    }
  }
}
//________________________________________________________________________________
void StTpcDigitalSector::assignTimeBins(Int_t rowN, Int_t padN, StDigitalTimeBins* tbins) {
  assert( (rowN >= 1 && rowN <= mNoRows ) ||
	  (padN >= 1 && padN <= numberOfPadsAtRow(rowN)));
  StDigitalPadRow    &Row = mData[(rowN-1)];
  StDigitalTimeBins  &Pad = Row[(padN-1)];
  if (Pad.size() > 0)  Pad.clear();
  Pad.swap(*tbins);
}
//________________________________________________________________________________
Int_t StTpcDigitalSector::cleanup() {
  UInt_t numberOfEmptyRows=0;
  for (UInt_t iRow=0; iRow<mData.size(); iRow++) {
    UInt_t numberOfEmptyPads=0;
    for (UInt_t iPad=0; iPad<mData[iRow].size(); iPad++) {
      if (mData[iRow][iPad].size()<7) {
	mData[iRow][iPad].clear();
	numberOfEmptyPads++;
      }
    } // Pads are now clean
    if (numberOfEmptyPads == mData[iRow].size()) {
      mData[iRow].clear();
      numberOfEmptyRows++;
    }
  } // Rows are now clean
    //cout << "This sector had " << numberOfEmptyRows << " empty rows." << endl;
  if (numberOfEmptyRows==mData.size()) return 1;
  else return 0;
}
//________________________________________________________________________________
Int_t StTpcDigitalSector::putTimeAdc(Int_t row, Int_t pad, Short_t *ADCs, UShort_t *IDTs) {// 10 -> 8 conversion
  Int_t ntimebins = 0;
  static StDigitalTimeBins  digPadData;
  digPadData.clear();
  for (Int_t tb = 0; tb < __MaxNumberOfTimeBins__; tb++) {
    if (! ADCs[tb]) continue;
    Int_t Idt = 0;
    if (IDTs) Idt = IDTs[tb]; 
    digPadData[tb] = StDigitalPixel(ADCs[tb], Idt);
    ntimebins++;
  }
  if (ntimebins) assignTimeBins(row,pad,&digPadData);
  return ntimebins;
}
//________________________________________________________________________________
Int_t StTpcDigitalSector::putTimeAdc(Int_t row, Int_t pad, UChar_t *ADCs, UShort_t *IDTs) {// no conversion
  Int_t ntimebins = 0;
  static StDigitalTimeBins  digPadData;
  digPadData.clear();
  for (UShort_t tb = 0; tb < __MaxNumberOfTimeBins__; tb++) {
    if (! ADCs[tb]) continue;
    Int_t Idt = 0;
    if (IDTs) Idt = IDTs[tb]; 
    UShort_t adc = log8to10_table[ADCs[tb]];
    digPadData[tb] = StDigitalPixel(adc, Idt);
    ntimebins++;
  }
  assignTimeBins(row,pad,&digPadData);
  return ntimebins;
}
//________________________________________________________________________________
Int_t StTpcDigitalSector::putTimeAdc(Int_t row, Int_t pad, Short_t *ADCs, Int_t *IDTs) {// 10 -> 8 conversion
  Int_t ntimebins = 0;
  static StDigitalTimeBins  digPadData;
  digPadData.clear();
  for (UShort_t tb = 0; tb < __MaxNumberOfTimeBins__; tb++) {
    if (! ADCs[tb]) continue;
    Int_t Idt = 0;
    if (IDTs) Idt = IDTs[tb]; 
    digPadData[tb] = StDigitalPixel(ADCs[tb], Idt);
    ntimebins++;
  }
  if (ntimebins) assignTimeBins(row,pad,&digPadData);
  return ntimebins;
}
//________________________________________________________________________________
Int_t StTpcDigitalSector::putTimeAdc(Int_t row, Int_t pad, UChar_t *ADCs, Int_t *IDTs) {// no conversion
  Int_t ntimebins = 0;
  static StDigitalTimeBins  digPadData;
  digPadData.clear();
  for (UShort_t tb = 0; tb < __MaxNumberOfTimeBins__; tb++) {
    if (! ADCs[tb]) continue;
    Int_t Idt = 0;
    if (IDTs) Idt = IDTs[tb]; 
    digPadData[tb] = StDigitalPixel(ADCs[tb], Idt);
    ntimebins++;
  }
  assignTimeBins(row,pad,&digPadData);
  return ntimebins;
}
//________________________________________________________________________________
Int_t StTpcDigitalSector::getTimeAdc(Int_t row, Int_t pad, 
				     Short_t  ADCs[__MaxNumberOfTimeBins__],
				     Int_t IDTs[__MaxNumberOfTimeBins__]) { 
  // no conversion
  UInt_t nTimeSeqs = 0;
  memset (ADCs, 0, __MaxNumberOfTimeBins__*sizeof(Short_t));
  memset (IDTs, 0, __MaxNumberOfTimeBins__*sizeof(Int_t));
  if ( ! ((row >= 1 && row <= mNoRows ) ||
	  (pad >= 1 && pad <= numberOfPadsAtRow(row)))) return nTimeSeqs;
  StDigitalTimeBins* TrsPadData = timeBinsOfRowAndPad(row,pad);
  if (! TrsPadData) return nTimeSeqs;
  StDigitalTimeBins &trsPadData = *TrsPadData;
  nTimeSeqs = trsPadData.size();
  if (! nTimeSeqs) return nTimeSeqs;
  if (nTimeSeqs > 511) {
    Error("StTpcDigitalSector::getTimeAdc","row = %i, pad = %i has corrupted nTimeSeqs = %i", row, pad, nTimeSeqs);
    return 0;
  }
  for (auto it =  trsPadData.cbegin(); it != trsPadData.cend(); ++it) {
    ADCs[(*it).first] = (*it).second.adc();
    IDTs[(*it).first] = (*it).second.idt();
  }
  return nTimeSeqs;
}
//________________________________________________________________________________
Int_t StTpcDigitalSector::getTimeAdc(Int_t row, Int_t pad, 
				     UChar_t ADCs[__MaxNumberOfTimeBins__], 
				     Int_t IDTs[__MaxNumberOfTimeBins__]) {
  // 10-> 8 conversion
  // no conversion
  UInt_t nTimeSeqs = 0;
  memset (ADCs, 0, __MaxNumberOfTimeBins__*sizeof(UChar_t));
  memset (IDTs, 0, __MaxNumberOfTimeBins__*sizeof(Int_t));
  if ( ! ((row >= 1 && row <= mNoRows ) ||
	  (pad >= 1 && pad <= numberOfPadsAtRow(row)))) return nTimeSeqs;
  StDigitalTimeBins* TrsPadData = timeBinsOfRowAndPad(row,pad);
  if (! TrsPadData) return nTimeSeqs;
  StDigitalTimeBins &trsPadData = *TrsPadData;
  nTimeSeqs = trsPadData.size();
  if (! nTimeSeqs) return nTimeSeqs;
  if (nTimeSeqs > 511) {
    Error("StTpcDigitalSector::getTimeAdc","row = %i, pad = %i has corrupted nTimeSeqs = %i", row, pad, nTimeSeqs);
    return 0;
  }
  for (auto it =  trsPadData.cbegin(); it != trsPadData.cend(); ++it) {
    ADCs[(*it).first] = (*it).second.adc();
    IDTs[(*it).first] = (*it).second.idt();
  }
  return nTimeSeqs;
 }
//________________________________________________________________________________
Int_t StTpcDigitalSector::PrintTimeAdc(Int_t row, Int_t pad) const {
  UInt_t nTimeSeqs = 0;
  if ( ! ((row >= 1 && row <= mNoRows ) ||
	  (pad >= 1 && pad <= numberOfPadsAtRow(row)))) return nTimeSeqs;
  const StDigitalTimeBins* TrsPadData = timeBinsOfRowAndPad(row,pad);
  if (! TrsPadData) return nTimeSeqs;
  const StDigitalTimeBins &trsPadData = *TrsPadData;
  nTimeSeqs = trsPadData.size();
  if (! nTimeSeqs) return nTimeSeqs;
  cout << "Time/Adc/IdTruth for row " << row << "\tpad " << pad << endl;
  for (auto it =  trsPadData.cbegin(); it != trsPadData.cend(); ++it) {
    cout << "\t" << (*it).first << "\t" << (*it).second.adc() << "\t" << (*it).second.idt() << endl;
  }
  return nTimeSeqs;
 }
//________________________________________________________________________________
StTpcDigitalSector &StTpcDigitalSector::operator+= (StTpcDigitalSector& v) {
  static Short_t ADCs1[__MaxNumberOfTimeBins__], ADCs2[__MaxNumberOfTimeBins__];
  static Int_t IDTs1[__MaxNumberOfTimeBins__], IDTs2[__MaxNumberOfTimeBins__];
  for (Int_t row = 1; row <= mNoRows; row++) {
    Int_t npad2 = v.numberOfPadsInRow(row);
    if (! npad2) continue;
    for (Int_t pad = 1; pad <= numberOfPadsAtRow(row); pad++) {
      Int_t ntb2 =  v.numberOfTimeBins(row,pad);
      if (! ntb2) continue;
      Int_t ntb1 =    numberOfTimeBins(row,pad);
      if (! ntb1) {
	StDigitalTimeBins tbins2 = *v.timeBinsOfRowAndPad(row,pad);
	assignTimeBins(row,pad,&tbins2);
	continue;
      }
      getTimeAdc(row,pad,ADCs1,IDTs1);
      v.getTimeAdc(row,pad,ADCs2,IDTs2);
      for (Int_t i = 0; i < __MaxNumberOfTimeBins__; i++) {
	if ((IDTs1[i] || IDTs2[i]) && ADCs1[i] < ADCs2[i]) IDTs1[i] = IDTs2[i];
	ADCs1[i] += ADCs2[i];
      }
      putTimeAdc(row, pad, ADCs1, IDTs1);
    }
  }
  return *this;
}
//________________________________________________________________________________
StTpcDigitalSector &StTpcDigitalSector::operator= (const StTpcDigitalSector& v) {
  for (Int_t row = 1; row <= mNoRows; row++) {
    Int_t npad2 = v.numberOfPadsInRow(row);
    if (! npad2) continue;
    for (Int_t pad = 1; pad <= numberOfPadsAtRow(row); pad++) {
      Int_t ntb2 =  v.numberOfTimeBins(row,pad);
      if (! ntb2) continue;
      StDigitalTimeBins tbins2 = *v.timeBinsOfRowAndPad(row,pad);
      assignTimeBins(row,pad,&tbins2);
      continue;
    }
  }
  return *this;
}
//________________________________________________________________________________
void StTpcDigitalSector::Print(const Option_t *opt) const {
  TString Opt(opt);
  for (Int_t row = 1; row <= mNoRows; row++) {
    //    cout << "sector/row " << mSector << "/" << row << endl;
    Int_t npads = numberOfPadsInRow(row);
    for (Int_t pad = 1; pad <= npads; pad++) {
      //      cout << "sector/row/pad = " << mSector << "/" << row << "/" << pad << endl;
      Int_t ntb = numberOfTimeBins(row,pad);
      if (! ntb) continue;
      cout << "sector/row/pad = " << mSector << "/" << row << "/" << pad << " = " << ntb << " time sequences" << endl;
      if (Opt.Contains("all",TString::kIgnoreCase)) PrintTimeAdc(row,pad);
    }
  }
}
//________________________________________________________________________________
void StTpcRawData::setSector(UInt_t  sector, StTpcDigitalSector* digitSector) {    
  if (sector > 0 && sector <= mSectors.size()) {
    if (mSectors[sector-1]) delete mSectors[sector-1];
    digitSector->setSector(sector);
    mSectors[sector-1] = digitSector;
  }
}
//________________________________________________________________________________
void StTpcRawData::Clear(const Option_t*) {
  for (UInt_t ii=0; ii<mSectors.size(); ii++) {SafeDelete(mSectors[ii]);}
}
//________________________________________________________________________________
Int_t StTpcRawData::getVecOfPixels(StVectPixel &pixels, Int_t sector, Int_t row, Int_t padMin, Int_t padMax, Int_t tMin, Int_t tMax) {
  pixels.clear();
  StTpcDigitalSector *s =   GetSector(sector);
  if (s) {
    static Short_t  ADCs[__MaxNumberOfTimeBins__];
    static Int_t IDTs[__MaxNumberOfTimeBins__];
    Int_t npads = s->numberOfPadsInRow(row);
    if (npads) {
      if (padMin <      1) padMin = 1;
      if (padMax < padMin) padMax = s->numberOfPadsAtRow(row);
      if (tMin   <      0) tMin   = 0;
      if (tMax   <   tMin) tMax =  __MaxNumberOfTimeBins__ - 1;
      tMax   = TMath::Min(tMax,  __MaxNumberOfTimeBins__ - 1);
      for (Int_t pad = padMin; pad <= padMax; pad++) {
	Int_t ntbs =    s->numberOfTimeBins(row,pad);
	if (ntbs) {
	  s->getTimeAdc(row,pad,ADCs,IDTs);
	  for (Int_t tb = tMin; tb <= tMax; tb++) {
	    if (ADCs[tb])	pixels.push_back(StTpcPixel(kTpcId,sector,row,pad,tb,ADCs[tb],IDTs[tb],0));
	  }
	}
      }
    }
  }
  return pixels.size();
}
//________________________________________________________________________________
void StTpcRawData::Print(const Option_t *opt) const {
  Int_t N = ((StTpcRawData *) this)->size();
  for (Int_t i = 0; i < N; i++) {
    StTpcDigitalSector *sector =  ((StTpcDigitalSector* )mSectors[i]);
    if (sector) sector->Print(opt);
  }
}
//________________________________________________________________________________
StTpcRawData &StTpcRawData::operator+= (StTpcRawData& v) {
  for (Int_t sec = 1; sec <= 24; sec++) {
    StTpcDigitalSector *a = getSector(sec);
    StTpcDigitalSector *b = v.getSector(sec);
    if (!b ) continue;
    if (!a) {
      a = new StTpcDigitalSector(sec);
      *a = *b;
      setSector(sec, a);
      continue;
    }
    *a += *b;
  }
  return *this;
}
