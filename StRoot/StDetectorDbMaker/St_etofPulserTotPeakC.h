#ifndef St_etofPulserTotPeakC_h
#define St_etofPulserTotPeakC_h

#include "TChair.h"
#include "tables/St_etofPulserTotPeak_Table.h"

class St_etofPulserTotPeakC : public TChair {
 public:
  static St_etofPulserTotPeakC* 	instance();
  etofPulserTotPeak_st 	*Struct(Int_t i = 0) 	const {return ((St_etofPulserTotPeak*) Table())->GetTable()+i;}
  UInt_t     	getNumRows()                	const {return GetNRows();}
  UChar_t* 	pulserTot(Int_t i = 0) 	const {return Struct(i)->pulserTot;}
 protected:
  St_etofPulserTotPeakC(St_etofPulserTotPeak *table=0) : TChair(table) {}
  virtual ~St_etofPulserTotPeakC() {fgInstance = 0;}
 private:
  static St_etofPulserTotPeakC* fgInstance;
  ClassDefChair(St_etofPulserTotPeak, etofPulserTotPeak_st )
  ClassDef(St_etofPulserTotPeakC,1) //C++ TChair for etofPulserTotPeak table class
};
#endif
