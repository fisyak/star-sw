#ifndef St_etofTimingWindowC_h
#define St_etofTimingWindowC_h

#include "TChair.h"
#include "tables/St_etofTimingWindow_Table.h"

class St_etofTimingWindowC : public TChair {
 public:
  static St_etofTimingWindowC* 	instance();
  etofTimingWindow_st 	*Struct(Int_t i = 0) 	const {return ((St_etofTimingWindow*) Table())->GetTable()+i;}
  UInt_t     	getNumRows()                	const {return GetNRows();}
  UShort_t * 	afckAddress(Int_t i = 0) 	const {return Struct(i)->afckAddress;}
  Float_t* 	timingMin(Int_t i = 0) 	const {return Struct(i)->timingMin;}
  Float_t* 	timingMax(Int_t i = 0) 	const {return Struct(i)->timingMax;}
  Float_t* 	timingPeak(Int_t i = 0) 	const {return Struct(i)->timingPeak;}
  Float_t* 	pulserMin(Int_t i = 0) 	const {return Struct(i)->pulserMin;}
  Float_t* 	pulserMax(Int_t i = 0) 	const {return Struct(i)->pulserMax;}
  Float_t* 	pulserPeak(Int_t i = 0) 	const {return Struct(i)->pulserPeak;}
 protected:
  St_etofTimingWindowC(St_etofTimingWindow *table=0) : TChair(table) {}
  virtual ~St_etofTimingWindowC() {fgInstance = 0;}
 private:
  static St_etofTimingWindowC* fgInstance;
  ClassDefChair(St_etofTimingWindow, etofTimingWindow_st )
  ClassDef(St_etofTimingWindowC,1) //C++ TChair for etofTimingWindow table class
};
#endif
