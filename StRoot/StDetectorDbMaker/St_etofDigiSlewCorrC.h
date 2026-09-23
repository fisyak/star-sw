#ifndef St_etofDigiSlewCorrC_h
#define St_etofDigiSlewCorrC_h

#include "TChair.h"
#include "tables/St_etofDigiSlewCorr_Table.h"

class St_etofDigiSlewCorrC : public TChair {
 public:
  static St_etofDigiSlewCorrC* 	instance();
  etofDigiSlewCorr_st 	*Struct(Int_t i = 0) 	const {return ((St_etofDigiSlewCorr*) Table())->GetTable()+i;}
  UInt_t     	getNumRows()                	const {return GetNRows();}
  UShort_t * 	channelId(Int_t i = 0) 	const {return Struct(i)->channelId;}
  UShort_t * 	upperTotEdge(Int_t i = 0) 	const {return Struct(i)->upperTotEdge;}
  Short_t* 	corr(Int_t i = 0) 	const {return Struct(i)->corr;}
 protected:
  St_etofDigiSlewCorrC(St_etofDigiSlewCorr *table=0) : TChair(table) {}
  virtual ~St_etofDigiSlewCorrC() {fgInstance = 0;}
 private:
  static St_etofDigiSlewCorrC* fgInstance;
  ClassDefChair(St_etofDigiSlewCorr, etofDigiSlewCorr_st )
  ClassDef(St_etofDigiSlewCorrC,1) //C++ TChair for etofDigiSlewCorr table class
};
#endif
