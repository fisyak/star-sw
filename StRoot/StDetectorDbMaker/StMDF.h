#ifndef StMDF_h
#define StMDF_h
#include <string>
#include <cstddef>
#include "TChair.h"
#include "tables/St_MDFCorrection_Table.h"
#include "tables/St_MDFCorrection3_Table.h"
#include "tables/St_MDFCorrection4_Table.h"
#include "TF3.h"
#include "TF2.h"
#include "TF1.h"
#include "TMath.h"
#include "TString.h"
class StMDF {
 public:
  enum EMDFPolyType {
    kMonomials,
    kChebyshev,
    kLegendre
  };
  StMDF() {}
 StMDF(MDFCorrection_st 	*Struc, const Char_t *name = "") : fName(name), fFunc(0),
    fPolyType(&Struc->PolyType),
    fNVariables(&Struc->NVariables),
    fNCoefficients(&Struc->NCoefficients),
    fPower(Struc->Power),        
    fDMean(&Struc->DMean),         
    fXMin(Struc->XMin),        	
    fXMax(Struc->XMax),        	
    fCoefficients(Struc->Coefficients), 	
    fCoefficientsRMS(Struc->CoefficientsRMS)
      {  } 
 StMDF(MDFCorrection3_st 	*Struc, const Char_t *name = "") : fName(name), fFunc(0),
    fPolyType(&Struc->PolyType),
    fNVariables(&Struc->NVariables),
    fNCoefficients(&Struc->NCoefficients),
    fPower(Struc->Power),        
    fDMean(&Struc->DMean),         
    fXMin(Struc->XMin),        	
    fXMax(Struc->XMax),        	
    fCoefficients(Struc->Coefficients), 	
    fCoefficientsRMS(Struc->CoefficientsRMS)
      {  } 
 StMDF(MDFCorrection4_st 	*Struc, const Char_t *name = "") : fName(name), fFunc(0),
    fPolyType(&Struc->PolyType),
    fNVariables(&Struc->NVariables),
    fNCoefficients(&Struc->NCoefficients),
    fPower(Struc->Power),        
    fDMean(&Struc->DMean),         
    fXMin(Struc->XMin),        	
    fXMax(Struc->XMax),        	
    fCoefficients(Struc->Coefficients), 	
    fCoefficientsRMS(Struc->CoefficientsRMS)
      {  } 
  const Char_t *getName()                const {return  fName.Data();}
  TF1*          GetFunction()            const;
  Int_t 	PolyType() 	         const {return ((Char_t )*fPolyType)%10;     }
  Int_t 	ConvType() 	         const {return ((Char_t )*fPolyType)/10;     }
  Char_t 	NVariablesS() 		 const {return (Char_t) *fNVariables;   }
  Char_t  	NVariables() 		 const {return TMath::Abs(NVariablesS());}	       
  UChar_t 	NCoefficients() 	 const {return *fNCoefficients;}
  UChar_t* 	Power() 		 const {return  fPower;        }
  Double_t 	DMean()         	 const {return *fDMean;        }
  Double_t* 	XMin()         		 const {return  fXMin;         }
  Double_t* 	XMax()       		 const {return  fXMax;         }
  Double_t* 	Coefficients()           const {return  fCoefficients;  }
  Double_t* 	CoefficientsRMS()        const {return  fCoefficientsRMS;  }
  Double_t      Eval(Double_t *x = 0) const;
  Double_t      Eval(Double_t x0, Double_t x1, Double_t x2 = 0, Double_t x3 = 0) {Double_t xx[4] = {x0, x1, x2, x3}; return Eval(xx);}
  Double_t      EvalError(Double_t *x = 0) const;;			     
  virtual ~StMDF(){SafeDelete(fFunc);}
 private:
  static Double_t       MDFunc(Double_t *x = 0, Double_t *p = 0);
  Double_t EvalFactor(Int_t p = 0, Double_t x = 0);
  TString       fName;
  mutable TF1  *fFunc;
  UChar_t      *fPolyType;
  UChar_t      *fNVariables;
  UChar_t      *fNCoefficients;
  UChar_t      *fPower;        
  Double_t     *fDMean;          //[fgNVariables]		      
  Double_t     *fXMin;           //[fgNVariables]		      
  Double_t     *fXMax;        	 //[fgNCoeffficents]	      
  Double_t     *fCoefficients; 	 //[fgNCoeffficents*fgNVariables]
  Double_t     *fCoefficientsRMS;//[fgNCoeffficents*fgNVariables]
  static StMDF *fgMDF;
  ClassDef(StMDF,1)
};
#define __MDFCorrectionC__(__VARS__)				\
  class St_MDFCorrection ## __VARS__ ## C : public TChair {		\
  public:								\
    St_MDFCorrection ## __VARS__ ## C(St_MDFCorrection ## __VARS__  *table=0 ): TChair(table), mdf(0) {	\
      Int_t N = (table ? table->GetNRows() : 0);			\
      if (N > 0) {mdf = new StMDF*[N]; memset(mdf, 0, N*sizeof(StMDF*));} \
    }									\
    virtual ~St_MDFCorrection ## __VARS__ ## C() {if (mdf) {for (UInt_t i = 0; i < getNumRows(); i++) SafeDelete(mdf[i]); delete [] mdf;}} \
    MDFCorrection ## __VARS__ ## _st 	*Struct(Int_t k = 0) 	const {return ((St_MDFCorrection ## __VARS__ *) Table())->GetTable()+k;} \
    UInt_t     	getNumRows()                	const {return GetNRows();} \
    const Char_t  *getName()                    const {return Table()->GetName();} \
    UChar_t 	idx(Int_t k = 0)        	const {return Struct(k)->idx;} \
    UChar_t 	nrows(Int_t k = 0) 	        const {return Struct(k)->nrows;} \
    StMDF*        MDF(Int_t k = 0)              const {		\
      if (! mdf[k]  && idx(k)) mdf[k] = new StMDF(Struct(k), Form("%s_%i",Table()->GetName(),k)); \
      return mdf[k];							\
    }									\
    Double_t      Eval(Int_t k = 0, Double_t *x = 0) const  {return MDF(k) ? MDF(k)->Eval(x) : 0;} \
    Double_t      Eval(Int_t k, Double_t x0, Double_t x1, Double_t x2 = 0, Double_t x3 = 0) const  {return MDF(k) ? MDF(k)->Eval(x0,x1,x2,x3) : 0;} \
    Double_t      EvalError(Int_t k = 0, Double_t *x = 0) const  {return MDF(k) ? MDF(k)->EvalError(x) : 0;} \
    Int_t IsActiveChair() const {					\
      Int_t npar = 0;							\
      const St_MDFCorrection ## __VARS__  *tableMDF = (const St_MDFCorrection ## __VARS__  *) Table(); \
      if (! tableMDF) return npar;					\
      MDFCorrection ## __VARS__ ## _st *corMDF = tableMDF->GetTable();	\
      Int_t N = tableMDF->GetNRows();					\
      if (! corMDF || ! N) {						\
	return npar;							\
      }									\
      for (Int_t i = 0; i < N; i++, corMDF++) {				\
	if (corMDF->nrows == 0 && corMDF->idx == 0) continue;		\
	npar++;								\
      }									\
      return npar;							\
    }									\
  protected:								\
    StMDF **mdf;							\
  private:								\
      };
#endif
