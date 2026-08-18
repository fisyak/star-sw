#ifndef St_MDFCorrectionC_h
#define St_MDFCorrectionC_h
#include "StMDF.h"
//__MDFCorrectionC__();
  class St_MDFCorrectionC : public TChair {		
  public:								
    St_MDFCorrectionC(St_MDFCorrection *table=0 ): TChair(table), mdf(0) {	
      Int_t N = (table ? table->GetNRows() : 0);			
      if (N > 0) {mdf = new StMDF*[N]; memset(mdf, 0, N*sizeof(StMDF*));} 
    }									
    virtual ~St_MDFCorrectionC() {if (mdf) {for (UInt_t i = 0; i < getNumRows(); i++) SafeDelete(mdf[i]); delete [] mdf;}} 
    MDFCorrection_st 	*Struct(Int_t k = 0) 	const {return ((St_MDFCorrection*) Table())->GetTable()+k;} 
    UInt_t     	getNumRows()                	const {return GetNRows();} 
    const Char_t  *getName()                    const {return Table()->GetName();} 
    UChar_t 	idx(Int_t k = 0)        	const {return Struct(k)->idx;} 
    UChar_t 	nrows(Int_t k = 0) 	        const {return Struct(k)->nrows;} 
    StMDF*        MDF(Int_t k = 0)              const {		
      if (! mdf[k]  && idx(k)) mdf[k] = new StMDF(Struct(k), Form("%s_%i",Table()->GetName(),k)); 
      return mdf[k];							
    }									
    Double_t      Eval(Int_t k = 0, Double_t *x = 0) const  {return MDF(k) ? MDF(k)->Eval(x) : 0;} 
    Double_t      Eval(Int_t k, Double_t x0, Double_t x1, Double_t x2 = 0, Double_t x3 = 0) const  {return MDF(k) ? MDF(k)->Eval(x0,x1,x2,x3) : 0;} 
    Double_t      EvalError(Int_t k = 0, Double_t *x = 0) const  {return MDF(k) ? MDF(k)->EvalError(x) : 0;} 
    Int_t IsActiveChair() const {					
      Int_t npar = 0;							
      const St_MDFCorrection *tableMDF = (const St_MDFCorrection *) Table(); 
      if (! tableMDF) return npar;					
      MDFCorrection_st *corMDF = tableMDF->GetTable();	
      Int_t N = tableMDF->GetNRows();					
      if (! corMDF || ! N) {						
	return npar;							
      }									
      for (Int_t i = 0; i < N; i++, corMDF++) {				
	if (corMDF->nrows == 0 && corMDF->idx == 0) continue;		
	npar++;								
      }									
      return npar;							
    }									
  protected:								
    StMDF **mdf;							
  private:								
  ClassDef(St_MDFCorrectionC,1)				
      };
#endif
