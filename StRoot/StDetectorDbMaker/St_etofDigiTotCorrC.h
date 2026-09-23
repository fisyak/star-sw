#ifndef St_etofDigiTotCorrC_h
#define St_etofDigiTotCorrC_h

#include "TChair.h"
#include "tables/St_etofDigiTotCorr_Table.h"

class St_etofDigiTotCorrC : public TChair {
 public:
  static St_etofDigiTotCorrC* 	instance();
  etofDigiTotCorr_st 	*Struct(Int_t i = 0) 	const {return ((St_etofDigiTotCorr*) Table())->GetTable()+i;}
  UInt_t     	getNumRows()                	const {return GetNRows();}
  Float_t* 	totCorr(Int_t i = 0) 	const {return Struct(i)->totCorr;}
 protected:
  St_etofDigiTotCorrC(St_etofDigiTotCorr *table=0) : TChair(table) {}
  virtual ~St_etofDigiTotCorrC() {fgInstance = 0;}
 private:
  static St_etofDigiTotCorrC* fgInstance;
  ClassDefChair(St_etofDigiTotCorr, etofDigiTotCorr_st )
  ClassDef(St_etofDigiTotCorrC,1) //C++ TChair for etofDigiTotCorr table class
};
#endif
