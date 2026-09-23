#ifndef St_etofModCounterC_h
#define St_etofModCounterC_h

#include "TChair.h"
#include "tables/St_etofModCounter_Table.h"

class St_etofModCounterC : public TChair {
 public:
  static St_etofModCounterC* 	instance();
  etofModCounter_st 	*Struct(Int_t i = 0) 	const {return ((St_etofModCounter*) Table())->GetTable()+i;}
  UInt_t     	getNumRows()                	const {return GetNRows();}
  UChar_t* 	detectorModFlag(Int_t i = 0) 	const {return Struct(i)->detectorModFlag;}
 protected:
  St_etofModCounterC(St_etofModCounter *table=0) : TChair(table) {}
  virtual ~St_etofModCounterC() {fgInstance = 0;}
 private:
  static St_etofModCounterC* fgInstance;
  ClassDefChair(St_etofModCounter, etofModCounter_st )
  ClassDef(St_etofModCounterC,1) //C++ TChair for etofModCounter table class
};
#endif
