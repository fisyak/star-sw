#if !defined(__CINT__) || defined(__MAKECINT__)
#include "Riostream.h"
#include "Rtypes.h"
#include "TROOT.h"
#include "TSystem.h"
#include "TH2.h"
#include "TH3.h"
#include "TFile.h"
#include "TMath.h"
#include "TArrayD.h"
#include "TRVector.h"
#include "TRMatrix.h"
#include "TVectorD.h"
#include "TMatrixD.h"
#include "TMatrixDSymEigen.h"
#endif
#define PrPP(B) {cout << (#B) << " = \t" << (B) << endl;}
//________________________________________________________________________________
void CheckW2S() {
  TH1D *LSF = (TH1D *) gDirectory->Get("LSF");
  Double_t *array = LSF->GetArray() + 1;
  Int_t NEntries = array[0];
  if (NEntries  < 1000) return;
  enum {kM = 6, kP = 6};
  Int_t NP  = kP*24; // Total no. of parameters per sector
  Int_t fNumberOfVariables = NP;
  Int_t NPP = NP*(NP+1)/2; // size of matrix
  Int_t NT  = NP + NPP; // bin0 -> no. of entries; bin_NT+2 = chi2
  Double_t yTy = array[NT+2];
  Int_t im = 1;
  Int_t is = im + NP;
  TRVector AmX(NP,array+im);  PrPP(AmX);
  TRSymMatrix S(NP,array+is); PrPP(S);
  TMatrixD fCovarianceMatrix(NP,NP);
  TVectorD fSigmas(NP);
  Double_t    fTrace = 0;
  Int_t i,j;
  for (i = 0; i < NP; i++) 
    for (j = 0; j <= i; j++) fCovarianceMatrix(i,j) = S(i,j);
  for (i = 0; i < fNumberOfVariables; i++) {
    fSigmas(i) = TMath::Sqrt(fCovarianceMatrix(i,i));
    for (j = 0; j <= i; j++) {
      if (fSigmas(i) > 0 && fSigmas(j) > 0) {
	fCovarianceMatrix(i,j) /= (fSigmas(i) * fSigmas(j));
      } else  fCovarianceMatrix(i,j) = 0;
    }
    fTrace += fCovarianceMatrix(i,i);
  }
  // Fill remaining parts of matrix, and scale.
  for (i = 0; i < fNumberOfVariables; i++)
    for (j = 0; j <= i; j++) {
      fCovarianceMatrix(i,j) /= fTrace;
      fCovarianceMatrix(j,i) = fCovarianceMatrix(i,j);
    }
  
  TMatrixDSym sym; sym.Use(fCovarianceMatrix.GetNrows(),fCovarianceMatrix.GetMatrixArray());
  TMatrixDSymEigen eigen(sym);
  TMatrixD fEigenVectors = eigen.GetEigenVectors();
  TVectorD fEigenValues  = eigen.GetEigenValues();
  //make sure that eigenvalues are positive
  for (Int_t i = 0; i < fNumberOfVariables; i++) {
    if (fEigenValues[i] < 0) fEigenValues[i] = -fEigenValues[i];
  }
}
//________________________________________________________________________________
void CheckIO(Int_t sector = 1) {
  TH1D *LSF = (TH1D *) gDirectory->Get(Form("LSF_%02i",sector));
  if (! LSF) return;
  Double_t *array = LSF->GetArray() + 1;
  Int_t NEntries = array[0];
  if (NEntries  < 1000) return;
  enum {kM = 5, kP = 6, kPP = kP*(kP+1)/2};
  Int_t fNumberOfVariables = kP;
  Int_t NPP = kPP; // size of matrix
  Int_t NT  = kP + kPP; // bin0 -> no. of entries; bin_NT+2 = chi2
  Double_t yTy = array[NT+1];
  Int_t im = 1;
  Int_t is = im + kP;
  TRVector AmX(kP,array+im);  PrPP(AmX);
  TRSymMatrix S(kP,array+is); PrPP(S);
  TRSymMatrix Cor(S, TRArray::kSCor);  PrPP(Cor);
  TRSymMatrix SInv(S,TRArray::kInverted);  PrPP(SInv);
  TRVector  X(SInv,TRArray::kSxA,AmX);     PrPP(X);
  Double_t chi2 = yTy;
  chi2 -= AmX*X;
  cout << "chi2 = " << chi2 << endl;
  TMatrixD fCovarianceMatrix(kP,kP);
  TVectorD fSigmas(kP);
  Double_t    fTrace = 0;
  Int_t i,j;
  for (i = 0; i < kP; i++) 
    for (j = 0; j <= i; j++) fCovarianceMatrix(i,j) = S(i,j);
  for (i = 0; i < fNumberOfVariables; i++) {
    fSigmas(i) = TMath::Sqrt(fCovarianceMatrix(i,i));
    for (j = 0; j <= i; j++) {
      if (fSigmas(i) > 0 && fSigmas(j) > 0) {
	fCovarianceMatrix(i,j) /= (fSigmas(i) * fSigmas(j));
      } else  fCovarianceMatrix(i,j) = 0;
    }
    fTrace += fCovarianceMatrix(i,i);
  }
  // Fill remaining parts of matrix, and scale.
  for (i = 0; i < fNumberOfVariables; i++)
    for (j = 0; j <= i; j++) {
      fCovarianceMatrix(i,j) /= fTrace;
      fCovarianceMatrix(j,i) = fCovarianceMatrix(i,j);
    }
  
  TMatrixDSym sym; sym.Use(fCovarianceMatrix.GetNrows(),fCovarianceMatrix.GetMatrixArray());
  TMatrixDSymEigen eigen(sym);
  TMatrixD fEigenVectors = eigen.GetEigenVectors();
  TVectorD fEigenValues  = eigen.GetEigenValues();
  //make sure that eigenvalues are positive
  for (Int_t i = 0; i < fNumberOfVariables; i++) {
    if (fEigenValues[i] < 0) fEigenValues[i] = -fEigenValues[i];
  }
  fCovarianceMatrix.Print();
  fEigenVectors.Print();
  fEigenValues.Print();
}
//________________________________________________________________________________
void CheckIO2(Int_t sector = 1) {
  TH1D *LSF = (TH1D *) gDirectory->Get(Form("LSF_%02i",sector));
  if (! LSF) return;
  Double_t *array = LSF->GetArray() + 1;
  Int_t NEntries = array[0];
  if (NEntries  < 1000) return;
  enum {kM = 5, kP = 6, kPP = kP*(kP+1)/2};
  Int_t fNumberOfVariables = kP;
  Int_t NPP = kPP; // size of matrix
  Int_t NT  = kP + kPP; // bin0 -> no. of entries; bin_NT+2 = chi2
  Double_t yTy = array[NT+1];
  Int_t im = 1;
  Int_t is = im + kP;
  TRVector AmX(kP,array+im);  PrPP(AmX);
  TRSymMatrix S(kP,array+is); PrPP(S);
  Double_t b4x6[24] = {
    1, 0, 0, 0, 0, 0,
    0, 1, 0, 0, 0, 0,
    0, 0, 1, 0, 0, 0,
    0, 0, 0, 0, 0, 1};
  TRMatrix B4x6(4, 6, b4x6); PrPP(B4x6);
  TRSymMatrix S4x4(B4x6, TRArray::kAxSxAT, S); PrPP(S4x4);
  TRVector AmX4( B4x6,TRArray::kAxB, AmX); PrPP(AmX4);
  TRSymMatrix S4x4Inv(S4x4, TRArray::kInverted); PrPP(S4x4Inv);
  TRVector  X4(S4x4Inv,TRArray::kSxA,AmX4); PrPP(X4);
#if 0
  TRSymMatrix D(kP);
  TRSymMatrix DI(kP);
  for (Int_t i = 0; i < kP; i++){ D(i,i) = TMath::Sqrt(S(i,i)); DI(i,i) = 1./D(i,i);}
  TRSymMatrix SDI(DI,TRArray::kRxSxR, S); PrPP(SDI);
  TRVector AmXDI(D,TRArray::kSxA,AmX);  PrPP(AmXDI);
  TRSymMatrix SDIInv(SDI,TRArray::kInverted);  PrPP(SDIInv);
  TRVector  XDI(SDIInv,TRArray::kSxA,AmXDI); PrPP(XDI);
  TRVector  XD(DI,TRArray::kSxA,XDI); PrPP(XD);
#endif
  //  Int_t N = kP;
  Int_t N = 4;
  TMatrixD fCovarianceMatrix(N,N);
  for (Int_t i = 0; i < N; i++) 
    for (Int_t j = 0; j < N; j++)
      //      fCovarianceMatrix(i,j) = SDI(i,j);
      fCovarianceMatrix(i,j) = S4x4(i,j);
  TMatrixDSym sym; sym.Use(fCovarianceMatrix.GetNrows(),fCovarianceMatrix.GetMatrixArray());
  TMatrixDSymEigen eigen(sym);
  TMatrixD fEigenVectors = eigen.GetEigenVectors();
  TVectorD fEigenValues  = eigen.GetEigenValues();
  fCovarianceMatrix.Print();
  fEigenVectors.Print();
  fEigenValues.Print();
}
