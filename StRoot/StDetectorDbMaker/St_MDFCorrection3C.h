#ifndef St_MDFCorrection3C_h
#define St_MDFCorrection3C_h
#include "StMDF.h"
#if 1
__MDFCorrectionC__(3);
#else
class St_MDFCorrection3C : public TChair {	
 public:								
 St_MDFCorrection3C(St_MDFCorrection3 *table=0 ): TChair(table), mdf(0) {	
    Int_t N = (table ? table->GetNRows() : 0);			
    if (N > 0) {mdf = new StMDF*[N]; memset(mdf, 0, N*sizeof(StMDF*));} 
  }									
  virtual ~St_MDFCorrection3C() {for (size_t i; i < sizeof(mdf)/sizeof(StMDF*); i++) SafeDelete(mdf[i]); delete [] mdf;} 
  MDFCorrection3_st 	*Struct(Int_t k = 0) 	const {return ((St_MDFCorrection3*) Table())->GetTable()+k;} 
  UInt_t     	getNumRows()                	const {return GetNRows();} 
  const Char_t  *getName()                      const {return Table()->GetName();} 
  UChar_t 	idx(Int_t k = 0)        	const {return Struct(k)->idx;} 
  UChar_t 	nrows(Int_t k = 0) 	        const {return Struct(k)->nrows;} 
  StMDF*        MDF(Int_t k = 0)                const {		
    if (! mdf[k])    mdf[k] = new StMDF(Struct(k), Form("%s_%i",Table()->GetName(),k)); 
    return mdf[k];							
  }									
  Double_t      Eval(Int_t k = 0, Double_t *x = 0) const  {return MDF(k)->Eval(x);} 
  Double_t      Eval(Int_t k, Double_t x0, Double_t x1, Double_t x2 = 0, Double_t x3 = 0) const  {return MDF(k)->Eval(x0,x1,x2,x3);} 
  Double_t      EvalError(Int_t k = 0, Double_t *x = 0) const  {return MDF(k)->EvalError(x);}	
 protected:								
  StMDF **mdf;							
 private:								
  ClassDefChair(St_MDFCorrection3, MDFCorrection3_st ) 
  ClassDef(St_MDFCorrection3C,1)			
};
#endif
#endif
