#ifndef St_etofSignalVelocityC_h
#define St_etofSignalVelocityC_h

#include "TChair.h"
#include "tables/St_etofSignalVelocity_Table.h"

class St_etofSignalVelocityC : public TChair {
 public:
  static St_etofSignalVelocityC* 	instance();
  etofSignalVelocity_st 	*Struct(Int_t i = 0) 	const {return ((St_etofSignalVelocity*) Table())->GetTable()+i;}
  UInt_t     	getNumRows()                	const {return GetNRows();}
  Float_t* 	signalVelocity(Int_t i = 0) 	const {return Struct(i)->signalVelocity;}
 protected:
  St_etofSignalVelocityC(St_etofSignalVelocity *table=0) : TChair(table) {}
  virtual ~St_etofSignalVelocityC() {fgInstance = 0;}
 private:
  static St_etofSignalVelocityC* fgInstance;
  ClassDefChair(St_etofSignalVelocity, etofSignalVelocity_st )
  ClassDef(St_etofSignalVelocityC,1) //C++ TChair for etofSignalVelocity table class
};
#endif
