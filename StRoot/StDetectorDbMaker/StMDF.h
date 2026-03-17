#ifndef StMDF_h
#define StMDF_h
#include <string.h>
#include "TChair.h"
#include "tables/St_MDFCorrection_Table.h"
#include "TF3.h"
#include "TF2.h"
#include "TF1.h"
#include "TMath.h"
class StMDF {
 public:
  enum EMDFPolyType {
    kMonomials,
    kChebyshev,
    kLegendre
  };
 StMDF(Int_t N = 0);
 virtual UInt_t     	getNumRows()            const {return 0;}
 virtual const Char_t  *getName()               const {return 0;}
  virtual UChar_t 	idx(Int_t k)        	const {return 0;}
  virtual UChar_t 	nrows(Int_t k) 	        const {return 0;}
  virtual UChar_t 	PolyType(Int_t k) 	const {return 0;}
  virtual Char_t 	NVariablesS(Int_t k) 	const {return 0;}
  virtual Char_t  	NVariables(Int_t k) 	const {return 0;}
  virtual UChar_t 	NCoefficients(Int_t k) 	const {return 0;}
  virtual UChar_t* 	Powers(Int_t k) 	const {return 0;}
  virtual Double_t 	DMean(Int_t k)          const {return 0;}
  virtual Double_t* 	XMin(Int_t k)         	const {return 0;}
  virtual Double_t* 	XMax(Int_t k)       	const {return 0;}
  virtual Double_t* 	Coefficients(Int_t k) 	const {return 0;}
  virtual Double_t* 	CoefficientsRMS(Int_t k)const {return 0;}
  Double_t              Eval(Int_t k, Double_t *x = 0) const;
  Double_t              Eval(Int_t k, Double_t x0, Double_t x1, Double_t x2 = 0, Double_t x3 = 0) {Double_t xx[4] = {x0, x1, x2, x3}; return Eval(k,xx);}
  Double_t      	EvalError(Int_t k, Double_t *x = 0) const;;			     
  Int_t         	IsActiveChair() const;						     
  TF1*          	GetFunction(Int_t k = 0)        const { return fFunc ? fFunc[k] : 0;}
  static Double_t       MDFunc(Double_t *x = 0, Double_t *p = 0);
  virtual ~StMDF();
 private:
  Double_t EvalFactor(Int_t k = 0, Int_t p = 0, Double_t x = 0);
  static void      SetInstance(const StMDF *p) {fgMDF = (StMDF *) p;}
  TF1    **fFunc;
  static StMDF *fgMDF;
};
#endif
