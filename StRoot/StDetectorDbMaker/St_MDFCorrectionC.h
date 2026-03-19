#ifndef St_MDFCorrectionC_h
#define St_MDFCorrectionC_h
#include "StMDF.h"
#if 1
__MDFCorrectionC__();
#else
class St_MDFCorrectionC : public TChair {	
 public:								
 St_MDFCorrectionC(St_MDFCorrection *table=0 ): TChair(table), mdf(0) {	
    Int_t N = (table ? table->GetNRows() : 0);			
    if (N > 0) {mdf = new StMDF*[N]; memset(mdf, 0, N*sizeof(StMDF*));} 
  }									
  virtual ~St_MDFCorrectionC() {for (size_t i; i < sizeof(mdf)/sizeof(StMDF*); i++) SafeDelete(mdf[i]); delete [] mdf;} 
  MDFCorrection_st 	*Struct(Int_t k = 0) 	const {return ((St_MDFCorrection*) Table())->GetTable()+k;} 
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
  ClassDefChair(St_MDFCorrection, MDFCorrection_st ) 
  ClassDef(St_MDFCorrectionC,1)			
};
#endif
#endif
