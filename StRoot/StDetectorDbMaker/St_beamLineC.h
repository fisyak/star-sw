#ifndef St_beamLineC_h
#define St_beamLineC_h

#include "TChair.h"
#include "tables/St_beamLine_Table.h"

class St_beamLineC : public TChair {
 public:
  static St_beamLineC* 	instance();
  beamLine_st 	*Struct(Int_t i = 0) 	const {return ((St_beamLine*) Table())->GetTable()+i;}
  UInt_t     	getNumRows()                	const {return GetNRows();}
  Float_t 	X(Int_t i = 0) 	const {return Struct(i)->X;}
  Float_t 	sigma_X(Int_t i = 0) 	const {return Struct(i)->sigma_X;}
  Float_t 	Y(Int_t i = 0) 	const {return Struct(i)->Y;}
  Float_t 	sigma_Y(Int_t i = 0) 	const {return Struct(i)->sigma_Y;}
  Float_t 	Z(Int_t i = 0) 	const {return Struct(i)->Z;}
  Float_t 	sigma_Z(Int_t i = 0) 	const {return Struct(i)->sigma_Z;}
  Float_t 	dXdZ(Int_t i = 0) 	const {return Struct(i)->dXdZ;}
  Float_t 	sigma_dXdZ(Int_t i = 0) 	const {return Struct(i)->sigma_dXdZ;}
  Float_t 	dYdZ(Int_t i = 0) 	const {return Struct(i)->dYdZ;}
  Float_t 	sigma_dYdZ(Int_t i = 0) 	const {return Struct(i)->sigma_dYdZ;}
 protected:
  St_beamLineC(St_beamLine *table=0) : TChair(table) {}
  virtual ~St_beamLineC() {fgInstance = 0;}
 private:
  static St_beamLineC* fgInstance;
  ClassDefChair(St_beamLine, beamLine_st )
  ClassDef(St_beamLineC,1) //C++ TChair for beamLine table class
};
#endif
