#ifndef St_etofElectronicsMapC_h
#define St_etofElectronicsMapC_h

#include "TChair.h"
#include "tables/St_etofElectronicsMap_Table.h"

class St_etofElectronicsMapC : public TChair {
 public:
  static St_etofElectronicsMapC* 	instance();
  etofElectronicsMap_st 	*Struct(Int_t i = 0) 	const {return ((St_etofElectronicsMap*) Table())->GetTable()+i;}
  UInt_t     	getNumRows()                	const {return GetNRows();}
  UChar_t 	nAfcks(Int_t i = 0) 	const {return Struct(i)->nAfcks;}
  UShort_t  	nChannels(Int_t i = 0) 	const {return Struct(i)->nChannels;}
  UShort_t * 	afckAddress(Int_t i = 0) 	const {return Struct(i)->afckAddress;}
  UChar_t* 	sector(Int_t i = 0) 	const {return Struct(i)->sector;}
  UShort_t * 	channelNumber(Int_t i = 0) 	const {return Struct(i)->channelNumber;}
  UShort_t * 	geometryId(Int_t i = 0) 	const {return Struct(i)->geometryId;}
 protected:
  St_etofElectronicsMapC(St_etofElectronicsMap *table=0) : TChair(table) {}
  virtual ~St_etofElectronicsMapC() {fgInstance = 0;}
 private:
  static St_etofElectronicsMapC* fgInstance;
  ClassDefChair(St_etofElectronicsMap, etofElectronicsMap_st )
  ClassDef(St_etofElectronicsMapC,1) //C++ TChair for etofElectronicsMap table class
};
#endif
