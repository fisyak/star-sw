#ifndef St_etofDigiTimeCorrC_h
#define St_etofDigiTimeCorrC_h

#include "TChair.h"
#include "tables/St_etofDigiTimeCorr_Table.h"

class St_etofDigiTimeCorrC : public TChair {
 public:
  static St_etofDigiTimeCorrC* 	instance();
  etofDigiTimeCorr_st 	*Struct(Int_t i = 0) 	const {return ((St_etofDigiTimeCorr*) Table())->GetTable()+i;}
  UInt_t     	getNumRows()                	const {return GetNRows();}
  Float_t* 	timeCorr(Int_t i = 0) 	const {return Struct(i)->timeCorr;}
 protected:
  St_etofDigiTimeCorrC(St_etofDigiTimeCorr *table=0) : TChair(table) {}
  virtual ~St_etofDigiTimeCorrC() {fgInstance = 0;}
 private:
  static St_etofDigiTimeCorrC* fgInstance;
  ClassDefChair(St_etofDigiTimeCorr, etofDigiTimeCorr_st )
  ClassDef(St_etofDigiTimeCorrC,1) //C++ TChair for etofDigiTimeCorr table class
};
#endif
