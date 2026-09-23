#ifndef St_etofGet4StateC_h
#define St_etofGet4StateC_h

#include "TChair.h"
#include "tables/St_etofGet4State_Table.h"

class St_etofGet4StateC : public TChair {
 public:
  static St_etofGet4StateC* 	instance();
  etofGet4State_st 	*Struct(Int_t i = 0) 	const {return ((St_etofGet4State*) Table())->GetTable()+i;}
  UInt_t     	getNumRows()                	const {return GetNRows();}
  UInt_t* 	etofGet4State(Int_t i = 0) 	const {return Struct(i)->etofGet4State;}
 protected:
  St_etofGet4StateC(St_etofGet4State *table=0) : TChair(table) {}
  virtual ~St_etofGet4StateC() {fgInstance = 0;}
 private:
  static St_etofGet4StateC* fgInstance;
  ClassDefChair(St_etofGet4State, etofGet4State_st )
  ClassDef(St_etofGet4StateC,1) //C++ TChair for etofGet4State table class
};
#endif
