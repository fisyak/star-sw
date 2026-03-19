#include "StMDF.h"
StMDF *StMDF::fgMDF = 0;
//____________________________________________________________________
Double_t StMDF::MDFunc(Double_t *x, Double_t *p) {
  // Evaluate parameterization at point x. Optional argument coeff is
  // a vector of coefficients for the parameterisation, NCoefficients
  // elements long.
  assert(x);
  Double_t returnValue = fgMDF->DMean();
  Double_t term        = 0;
  UChar_t    i, j;
  for (i = 0; i < fgMDF->NCoefficients(); i++) {
    // Evaluate the ith term in the expansion
    term = fgMDF->Coefficients()[i];
    for (j = 0; j < fgMDF->NVariables(); j++) {
      // Evaluate the factor (polynomial) in the j-th variable.
      Int_t    p  =  fgMDF->Power()[i * fgMDF->NVariables() + j];
      Double_t y  =  1 + 2. / (fgMDF->XMax()[j] - fgMDF->XMin()[j]) * (x[j] - fgMDF->XMax()[j]);
      term        *= fgMDF->EvalFactor(p,y);
    }
    // Add this term to the final result
    returnValue += term;
  }
  return returnValue;
}
//____________________________________________________________________
Double_t StMDF::Eval(Double_t *x) const {
  // Evaluate parameterization at point x. Optional argument coeff is
  // a vector of coefficients for the parameterisation, NCoefficients
  // elements long.
  assert(x);
  Double_t xx[4] = {0};
  if (NVariablesS() < 0) {// cut on limits
    for (Int_t v = 0; v < NVariables(); v++) {
      if (x[v] < XMin()[v] || x[v] > XMax()[v]) return 0;
    }
  } 
  for (Int_t v = 0; v < NVariables(); v++) {
    xx[v] = TMath::Max(XMin()[v], TMath::Min(XMin()[v]+0.999*(XMax()[v]-XMin()[v]), x[v]));
  }
  Double_t returnValue = 0;
  if (fFunc) {
    returnValue = fFunc->GetSave(xx);
  } else  {
    returnValue = MDFunc(xx);
  }
  return returnValue;
}
//____________________________________________________________________
TF1 *StMDF::GetFunction() const {
  fgMDF = (StMDF *) this;
  if (! fFunc && NVariables() <= 3) { 
    if (NVariables() == 1) {
      fFunc = new TF1(getName(),StMDF::MDFunc,
		      XMin()[0],XMax()[0]);
      fFunc->Save(XMin()[0],XMax()[0],0,0,0,0);
    } else if (NVariables() == 2) {
      fFunc = new TF2(getName(),StMDF::MDFunc,
		      XMin()[0],XMax()[0],XMin()[1],XMax()[1]);
      ((TF2 *) fFunc)->Save(XMin()[0],XMax()[0],XMin()[1],XMax()[1],0,0);
    } else if (NVariables() == 3) {
      fFunc = new TF3(getName(),StMDF::MDFunc,
		      XMin()[0],XMax()[0],XMin()[1],XMax()[1],XMin()[2],XMax()[2]);
      ((TF3 *) fFunc)->Save(XMin()[0],XMax()[0],XMin()[1],XMax()[1],XMin()[2],XMax()[2]);
    }
  }
  return fFunc;
}
//____________________________________________________________________
Double_t StMDF::EvalError( Double_t *x) const {
  // Evaluate parameterization error at point x. Optional argument coeff is
  // a vector of coefficients for the parameterisation, NCoefficients()
  // elements long.
  assert(x);
  Double_t xx[4] = {0};
  if (NVariablesS() < 0) {// cut on limits
    for (Int_t v = 0; v < NVariables(); v++) {
      if (x[v] < XMin()[v] || x[v] > XMax()[v]) return 0;
    }
  } 
  // set in limits
  for (Int_t v = 0; v < NVariables(); v++) {
    xx[v] = TMath::Max(XMin()[v], TMath::Min(XMin()[v]+0.999*(XMax()[v]-XMin()[v]), x[v]));
  }
  Double_t returnValue = 0;
  Double_t term        = 0;
  UChar_t    i, j;
  for (i = 0; i < NCoefficients(); i++) {
    // Evaluate the ith term in the expansion
    term = CoefficientsRMS()[i];
    for (j = 0; j < NVariables(); j++) {
      // Evaluate the factor (polynomial) in the j-th variable.
      Int_t    p  =  Power()[i * NVariables() + j];
      Double_t y  =  1 + 2. / (XMax()[j] - XMin()[j])
	* (xx[j] - XMax()[j]);
      term        *= fgMDF->EvalFactor(p,y);
    }
    // Add this term to the final result
    returnValue += term*term;
  }
  returnValue = TMath::Sqrt(returnValue);
  return returnValue;
}
//____________________________________________________________________
Double_t StMDF::EvalFactor(Int_t p, Double_t x) {
  // Evaluate function with power p at variable value x
  Int_t    i   = 0;
  Double_t p1  = 1;
  Double_t p2  = 0;
  Double_t p3  = 0;
  Double_t r   = 0;

  switch(p) {
  case 1:
    r = 1;
    break;
  case 2:
    r =  x;
    break;
  default:
    p2 = x;
    for (i = 3; i <= p; i++) {
      if (PolyType() == kLegendre)	  p3 = ((2 * i - 3) * p2 * x - (i - 2) * p1) / (i - 1);
      else if (PolyType() == kChebyshev)  p3 = 2 * x * p2 - p1;
      else                                p3 = p2 * x;
      p1 = p2;
      p2 = p3;
    }
    r = p3;
  }
  return r;
}
//________________________________________________________________________________
