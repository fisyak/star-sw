#ifndef St_starMagRotationC_h
#define St_starMagRotationC_h

#include "TChair.h"
#include "tables/St_starMagRotation_Table.h"

class St_starMagRotationC : public TChair {
 public:
  static St_starMagRotationC* 	instance();
  starMagRotation_st 	*Struct(Int_t i = 0) 	const {return ((St_starMagRotation*) Table())->GetTable()+i;}
  UInt_t     	getNumRows()                	const {return GetNRows();}
  Int_t 	Id(Int_t i = 0) 	const {return Struct(i)->Id;}
  Float_t 	alpha(Int_t i = 0) 	const {return Struct(i)->alpha;}
  Float_t 	beta(Int_t i = 0) 	const {return Struct(i)->beta;}
  Float_t 	gamma(Int_t i = 0) 	const {return Struct(i)->gamma;}
 protected:
  St_starMagRotationC(St_starMagRotation *table=0) : TChair(table) {}
  virtual ~St_starMagRotationC() {fgInstance = 0;}
 private:
  static St_starMagRotationC* fgInstance;
  ClassDefChair(St_starMagRotation, starMagRotation_st )
  ClassDef(St_starMagRotationC,1) //C++ TChair for starMagRotation table class
};
#endif
