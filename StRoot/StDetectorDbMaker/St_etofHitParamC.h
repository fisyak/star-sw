#ifndef St_etofHitParamC_h
#define St_etofHitParamC_h

#include "TChair.h"
#include "tables/St_etofHitParam_Table.h"

class St_etofHitParamC : public TChair {
 public:
  static St_etofHitParamC* 	instance();
  etofHitParam_st 	*Struct(Int_t i = 0) 	const {return ((St_etofHitParam*) Table())->GetTable()+i;}
  UInt_t     	getNumRows()                	const {return GetNRows();}
  Float_t 	maxLocalY(Int_t i = 0) 	const {return Struct(i)->maxLocalY;}
  Float_t 	clusterMergeRadius(Int_t i = 0) 	const {return Struct(i)->clusterMergeRadius;}
 protected:
  St_etofHitParamC(St_etofHitParam *table=0) : TChair(table) {}
  virtual ~St_etofHitParamC() {fgInstance = 0;}
 private:
  static St_etofHitParamC* fgInstance;
  ClassDefChair(St_etofHitParam, etofHitParam_st )
  ClassDef(St_etofHitParamC,1) //C++ TChair for etofHitParam table class
};
#endif
