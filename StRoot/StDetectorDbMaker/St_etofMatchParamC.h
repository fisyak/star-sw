#ifndef St_etofMatchParamC_h
#define St_etofMatchParamC_h

#include "TChair.h"
#include "tables/St_etofMatchParam_Table.h"

class St_etofMatchParamC : public TChair {
 public:
  static St_etofMatchParamC* 	instance();
  etofMatchParam_st 	*Struct(Int_t i = 0) 	const {return ((St_etofMatchParam*) Table())->GetTable()+i;}
  UInt_t     	getNumRows()                	const {return GetNRows();}
  Float_t 	matchRadius(Int_t i = 0) 	const {return Struct(i)->matchRadius;}
  UChar_t 	trackCutNHitsFit(Int_t i = 0) 	const {return Struct(i)->trackCutNHitsFit;}
  Float_t 	trackCutNHitsRatio(Int_t i = 0) 	const {return Struct(i)->trackCutNHitsRatio;}
  Float_t 	trackCutLowPt(Int_t i = 0) 	const {return Struct(i)->trackCutLowPt;}
 protected:
  St_etofMatchParamC(St_etofMatchParam *table=0) : TChair(table) {}
  virtual ~St_etofMatchParamC() {fgInstance = 0;}
 private:
  static St_etofMatchParamC* fgInstance;
  ClassDefChair(St_etofMatchParam, etofMatchParam_st )
  ClassDef(St_etofMatchParamC,1) //C++ TChair for etofMatchParam table class
};
#endif
