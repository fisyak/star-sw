#include "StMDF.h"
StMDF *StMDF::fgMDF = 0;
//____________________________________________________________________
StMDF::StMDF() : fFunc(0) {
  UInt_t N = getNumRows();
  fFunc = new TF1*[N];
  memset(fFunc, 0, N*sizeof(TF1*));
}
//____________________________________________________________________
StMDF::~StMDF() {
  UInt_t N = getNumRows();
  for (UInt_t i = 0; i < N; i++) {SafeDelete(fFunc[i]);}
  delete [] fFunc;
}
//____________________________________________________________________
Double_t StMDF::MDFunc(Double_t *x, Double_t *p) {
  // Evaluate parameterization at point x. Optional argument coeff is
  // a vector of coefficients for the parameterisation, NCoefficients
  // elements long.
  assert(x);
  UInt_t k = p[0];
  assert(k >= 0 && k < fgMDF->getNumRows());
  Double_t returnValue = fgMDF->DMean(k);
  Double_t term        = 0;
  UChar_t    i, j;
  for (i = 0; i < fgMDF->NCoefficients(k); i++) {
    // Evaluate the ith term in the expansion
    term = fgMDF->Coefficients(k)[i];
    for (j = 0; j < fgMDF->NVariables(k); j++) {
      // Evaluate the factor (polynomial) in the j-th variable.
      Int_t    p  =  fgMDF->Powers(k)[i * fgMDF->NVariables(k) + j];
      Double_t y  =  1 + 2. / (fgMDF->XMax(k)[j] - fgMDF->XMin(k)[j]) * (x[j] - fgMDF->XMax(k)[j]);
      term        *= fgMDF->EvalFactor(k,p,y);
    }
    // Add this term to the final result
    returnValue += term;
  }
  return returnValue;
}
//____________________________________________________________________
Double_t StMDF::Eval(Int_t k, Double_t *x) const {
  // Evaluate parameterization at point x. Optional argument coeff is
  // a vector of coefficients for the parameterisation, NCoefficients
  // elements long.
  assert(x);
  Double_t xx[4] = {0};
  if (NVariablesS(k) < 0) {// cut on limits
    for (Int_t v = 0; v < NVariables(k); v++) {
      if (x[v] < XMin(k)[v] || x[v] > XMax(k)[v]) return 0;
    }
  } 
  for (Int_t v = 0; v < NVariables(k); v++) {
    xx[v] = TMath::Max(XMin(k)[v], TMath::Min(XMin(k)[v]+0.999*(XMax(k)[v]-XMin(k)[v]), x[v]));
  }
  SetInstance(this);
  Double_t returnValue = 0;
  if (NVariables(k) <= 3) { 
    if (! fFunc[k]) {
      if (NVariables(k) <= 0) {
	return returnValue;
      } else if (NVariables(k) == 1) {
	fFunc[k] = new TF1(Form("%s_%i",getName(),k),StMDF::MDFunc,
			   XMin(k)[0],XMax(k)[0],1);
	fFunc[k]->SetParameter(0,k);
	fFunc[k]->Save(XMin(k)[0],XMax(k)[0],0,0,0,0);
      } else if (NVariables(k) == 2) {
	fFunc[k] = new TF2(Form("%s_%i",getName(),k),StMDF::MDFunc,
			   XMin(k)[0],XMax(k)[0],XMin(k)[1],XMax(k)[1],1);
	fFunc[k]->SetParameter(0,k);
	((TF2 *) fFunc[k])->Save(XMin(k)[0],XMax(k)[0],XMin(k)[1],XMax(k)[1],0,0);
      } else if (NVariables(k) == 3) {
	fFunc[k] = new TF3(Form("%s_%i",getName(),k),StMDF::MDFunc,
			   XMin(k)[0],XMax(k)[0],XMin(k)[1],XMax(k)[1],XMin(k)[2],XMax(k)[2],1);
	fFunc[k]->SetParameter(0,k);
	((TF3 *) fFunc[k])->Save(XMin(k)[0],XMax(k)[0],XMin(k)[1],XMax(k)[1],XMin(k)[2],XMax(k)[2]);
      }
    }
    returnValue = fFunc[k]->GetSave(xx);
  } else  {
    Double_t par[1] = {(Double_t) k};
    returnValue = MDFunc(xx,par);
  }
  return returnValue;
}
//____________________________________________________________________
Double_t StMDF::EvalError(Int_t k, Double_t *x) const {
  // Evaluate parameterization error at point x. Optional argument coeff is
  // a vector of coefficients for the parameterisation, NCoefficients(k)
  // elements long.
  assert(x);
  Double_t xx[4] = {0};
  if (NVariablesS(k) < 0) {// cut on limits
    for (Int_t v = 0; v < NVariables(k); v++) {
      if (x[v] < XMin(k)[v] || x[v] > XMax(k)[v]) return 0;
    }
  } 
  // set in limits
  for (Int_t v = 0; v < NVariables(k); v++) {
    xx[v] = TMath::Max(XMin(k)[v], TMath::Min(XMin(k)[v]+0.999*(XMax(k)[v]-XMin(k)[v]), x[v]));
  }
  Double_t returnValue = 0;
  Double_t term        = 0;
  UChar_t    i, j;
  for (i = 0; i < NCoefficients(k); i++) {
    // Evaluate the ith term in the expansion
    term = CoefficientsRMS(k)[i];
    for (j = 0; j < NVariables(k); j++) {
      // Evaluate the factor (polynomial) in the j-th variable.
      Int_t    p  =  Powers(k)[i * NVariables(k) + j];
      Double_t y  =  1 + 2. / (XMax(k)[j] - XMin(k)[j])
	* (xx[j] - XMax(k)[j]);
      term        *= fgMDF->EvalFactor(p,y);
    }
    // Add this term to the final result
    returnValue += term*term;
  }
  returnValue = TMath::Sqrt(returnValue);
  return returnValue;
}
//____________________________________________________________________
Double_t StMDF::EvalFactor(Int_t k, Int_t p, Double_t x) {
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
      p3 = p2 * x;
      if (PolyType(k) == kLegendre)
	p3 = ((2 * i - 3) * p2 * x - (i - 2) * p1) / (i - 1);
      else if (PolyType(k) == kChebyshev)
	p3 = 2 * x * p2 - p1;
      p1 = p2;
      p2 = p3;
    }
    r = p3;
  }
  return r;
}
//________________________________________________________________________________
Int_t StMDF::IsActiveChair() const {
  Int_t npar = 0;
  Int_t N = getNumRows();
  if (! N)     return npar;
  for (Int_t i = 0; i < N; i++) {
    if (nrows(i) == 0 && idx(i) == 0) continue;
    npar++;
  }
  return npar;
}
//________________________________________________________________________________
