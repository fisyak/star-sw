#ifndef St_etofCalibParamC_h
#define St_etofCalibParamC_h

#include "TChair.h"
#include "tables/St_etofCalibParam_Table.h"

class St_etofCalibParamC : public TChair {
 public:
  static St_etofCalibParamC* 	instance();
  etofCalibParam_st 	*Struct(Int_t i = 0) 	const {return ((St_etofCalibParam*) Table())->GetTable()+i;}
  UInt_t     	getNumRows()                	const {return GetNRows();}
  Float_t 	get4TotBinWidthNs(Int_t i = 0) 	const {return Struct(i)->get4TotBinWidthNs;}
  UChar_t 	minDigisInSlewBin(Int_t i = 0) 	const {return Struct(i)->minDigisInSlewBin;}
  UShort_t  	referencePulserIndex(Int_t i = 0) 	const {return Struct(i)->referencePulserIndex;}
 protected:
  St_etofCalibParamC(St_etofCalibParam *table=0) : TChair(table) {}
  virtual ~St_etofCalibParamC() {fgInstance = 0;}
 private:
  static St_etofCalibParamC* fgInstance;
  ClassDefChair(St_etofCalibParam, etofCalibParam_st )
  ClassDef(St_etofCalibParamC,1) //C++ TChair for etofCalibParam table class
};
#endif
