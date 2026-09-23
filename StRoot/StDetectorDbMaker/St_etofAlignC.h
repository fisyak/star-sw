#ifndef St_etofAlignC_h
#define St_etofAlignC_h

#include "TChair.h"
#include "tables/St_etofAlign_Table.h"

class St_etofAlignC : public TChair {
 public:
  static St_etofAlignC* 	instance();
  etofAlign_st 	*Struct(Int_t i = 0) 	const {return ((St_etofAlign*) Table())->GetTable()+i;}
  UInt_t     	getNumRows()                	const {return GetNRows();}
  Float_t* 	detectorAlignX(Int_t i = 0) 	const {return Struct(i)->detectorAlignX;}
  Float_t* 	detectorAlignY(Int_t i = 0) 	const {return Struct(i)->detectorAlignY;}
  Float_t* 	detectorAlignZ(Int_t i = 0) 	const {return Struct(i)->detectorAlignZ;}
 protected:
  St_etofAlignC(St_etofAlign *table=0) : TChair(table) {}
  virtual ~St_etofAlignC() {fgInstance = 0;}
 private:
  static St_etofAlignC* fgInstance;
  ClassDefChair(St_etofAlign, etofAlign_st )
  ClassDef(St_etofAlignC,1) //C++ TChair for etofAlign table class
};
#endif
