#ifndef St_etofPulserTimeDiffGbtxC_h
#define St_etofPulserTimeDiffGbtxC_h

#include "TChair.h"
#include "tables/St_etofPulserTimeDiffGbtx_Table.h"

class St_etofPulserTimeDiffGbtxC : public TChair {
 public:
  static St_etofPulserTimeDiffGbtxC* 	instance();
  etofPulserTimeDiffGbtx_st 	*Struct(Int_t i = 0) 	const {return ((St_etofPulserTimeDiffGbtx*) Table())->GetTable()+i;}
  UInt_t     	getNumRows()                	const {return GetNRows();}
  Float_t* 	pulserTimeDiffGbtx(Int_t i = 0) 	const {return Struct(i)->pulserTimeDiffGbtx;}
 protected:
  St_etofPulserTimeDiffGbtxC(St_etofPulserTimeDiffGbtx *table=0) : TChair(table) {}
  virtual ~St_etofPulserTimeDiffGbtxC() {fgInstance = 0;}
 private:
  static St_etofPulserTimeDiffGbtxC* fgInstance;
  ClassDefChair(St_etofPulserTimeDiffGbtx, etofPulserTimeDiffGbtx_st )
  ClassDef(St_etofPulserTimeDiffGbtxC,1) //C++ TChair for etofPulserTimeDiffGbtx table class
};
#endif
