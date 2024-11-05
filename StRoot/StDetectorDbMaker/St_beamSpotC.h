#ifndef St_beamSpotC_h
#define St_beamSpotC_h

#include "TChair.h"
#include "tables/St_beamSpot_Table.h"

class St_beamSpotC : public TChair {
 public:
  static St_beamSpotC* 	instance();
  beamSpot_st 	*Struct(Int_t i = 0) 	const {return ((St_beamSpot*) Table())->GetTable()+i;}
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
  St_beamSpotC(St_beamSpot *table=0) : TChair(table) {}
  virtual ~St_beamSpotC() {fgInstance = 0;}
 private:
  static St_beamSpotC* fgInstance;
  ClassDefChair(St_beamSpot, beamSpot_st )
  ClassDef(St_beamSpotC,1) //C++ TChair for beamSpot table class
};
#endif
