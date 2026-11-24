#ifndef St_runConfigurationC_h
#define St_runConfigurationC_h

#include "TChair.h"
#include "tables/St_runConfiguration_Table.h"
#include "TString.h"
class St_runConfigurationC : public TChair {
 public:
  static St_runConfigurationC* 	instance();
  runConfiguration_st 	*Struct(Int_t i = 0) 	const {return ((St_runConfiguration*) Table())->GetTable()+i;}
  UInt_t     	getNumRows()                	const {return GetNRows();}
  Short_t 	idx(Int_t i = 0) 	const {return Struct(i)->idx;}
  Short_t 	nrows(Int_t i = 0) 	const {return Struct(i)->nrows;}
  Int_t 	runMin(Int_t i = 0) 	const {return Struct(i)->runMin;}
  Int_t 	runMax(Int_t i = 0) 	const {return Struct(i)->runMax;}
  Char_t* 	trigger(Int_t i = 0) 	const {return Struct(i)->trigger;}
  Char_t* 	field(Int_t i = 0) 	const {return Struct(i)->field;}
  Char_t* 	beginTime(Int_t i = 0) 	const {return Struct(i)->beginTime;}
  static TString Trigger()   {return (currentIndex >= 0) ? TString(instance()->trigger(currentIndex))   : TString("Unknown");}
  static TString Field()     {return (currentIndex >= 0) ? TString(instance()->field(currentIndex))     : TString("Unknown");}
  static TString BeginTime() {return (currentIndex >= 0) ? TString(instance()->beginTime(currentIndex)) : TString("Unknown");}
 protected:
  St_runConfigurationC(St_runConfiguration *table=0) : TChair(table) {}
  virtual ~St_runConfigurationC() {fgInstance = 0;}
 private:
  static St_runConfigurationC* fgInstance;
  static Int_t   currentRun;
  static Int_t   currentIndex;
  ClassDefChair(St_runConfiguration, runConfiguration_st )
  ClassDef(St_runConfigurationC,1) //C++ TChair for runConfiguration table class
};
#endif
