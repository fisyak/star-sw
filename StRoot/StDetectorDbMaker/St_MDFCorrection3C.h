#ifndef St_MDFCorrection3C_h
#define St_MDFCorrection3C_h
#include "tables/St_MDFCorrection3_Table.h"
#include "StMDF.h"
class St_MDFCorrection3C : public TChair , public StMDF {
 public:
  St_MDFCorrection3C(St_MDFCorrection3 *table=0) : TChair(table), StMDF(table ? table->GetNRows() : 0) {}
  MDFCorrection3_st 	*Struct(Int_t k = 0) 	const {return ((St_MDFCorrection3*) Table())->GetTable()+k;}
  UInt_t     	getNumRows()                	const {return GetNRows();}
  const Char_t  *getName()                      const {return Table()->GetName();}
  UChar_t 	idx(Int_t k = 0)        	const {return Struct(k)->idx;}
  UChar_t 	nrows(Int_t k = 0) 	        const {return Struct(k)->nrows;}
  UChar_t 	PolyType(Int_t k = 0) 	        const {return Struct(k)->PolyType;}
  Char_t 	NVariablesS(Int_t k = 0) 	const {return (Char_t) (Struct(k)->NVariables);}
  UChar_t 	NCoefficients(Int_t k = 0) 	const {return Struct(k)->NCoefficients;}
  UChar_t* 	Powers(Int_t k = 0) 	        const {return Struct(k)->Power;}
  Double_t 	DMean(Int_t k = 0)           	const {return Struct(k)->DMean;}
  Double_t* 	XMin(Int_t k = 0)         	const {return Struct(k)->XMin;}
  Double_t* 	XMax(Int_t k = 0)       	const {return Struct(k)->XMax;}
  Double_t* 	Coefficients(Int_t k = 0) 	const {return Struct(k)->Coefficients;}
  Double_t* 	CoefficientsRMS(Int_t k = 0) 	const {return Struct(k)->CoefficientsRMS;}
 protected:
  virtual ~St_MDFCorrection3C() {}
 private:
  ClassDefChair(St_MDFCorrection3, MDFCorrection3_st )
  ClassDef(St_MDFCorrection3C,1) //C++ TChair for MDFCorrection3 table class
};
#endif
