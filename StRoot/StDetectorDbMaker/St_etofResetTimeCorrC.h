#ifndef St_etofResetTimeCorrC_h
#define St_etofResetTimeCorrC_h

#include "TChair.h"
#include "tables/St_etofResetTimeCorr_Table.h"

class St_etofResetTimeCorrC : public TChair {
 public:
  static St_etofResetTimeCorrC* 	instance();
  etofResetTimeCorr_st 	*Struct(Int_t i = 0) 	const {return ((St_etofResetTimeCorr*) Table())->GetTable()+i;}
  UInt_t     	getNumRows()                	const {return GetNRows();}
  Float_t 	resetTimeOffset(Int_t i = 0) 	const {return Struct(i)->resetTimeOffset;}
 protected:
  St_etofResetTimeCorrC(St_etofResetTimeCorr *table=0) : TChair(table) {}
  virtual ~St_etofResetTimeCorrC() {fgInstance = 0;}
 private:
  static St_etofResetTimeCorrC* fgInstance;
  ClassDefChair(St_etofResetTimeCorr, etofResetTimeCorr_st )
  ClassDef(St_etofResetTimeCorrC,1) //C++ TChair for etofResetTimeCorr table class
};
#endif
