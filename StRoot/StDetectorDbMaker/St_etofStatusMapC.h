#ifndef St_etofStatusMapC_h
#define St_etofStatusMapC_h

#include "TChair.h"
#include "tables/St_etofStatusMap_Table.h"

class St_etofStatusMapC : public TChair {
 public:
  static St_etofStatusMapC* 	instance();
  etofStatusMap_st 	*Struct(Int_t i = 0) 	const {return ((St_etofStatusMap*) Table())->GetTable()+i;}
  UInt_t     	getNumRows()                	const {return GetNRows();}
  UChar_t* 	status(Int_t i = 0) 	const {return Struct(i)->status;}
 protected:
  St_etofStatusMapC(St_etofStatusMap *table=0) : TChair(table) {}
  virtual ~St_etofStatusMapC() {fgInstance = 0;}
 private:
  static St_etofStatusMapC* fgInstance;
  ClassDefChair(St_etofStatusMap, etofStatusMap_st )
  ClassDef(St_etofStatusMapC,1) //C++ TChair for etofStatusMap table class
};
#endif
