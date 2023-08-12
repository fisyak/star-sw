#include "TMath.h"
#include "TF1.h"
TF1 *gg = 0;
Double_t gaus2(Double_t *x, Double_t *p) {
  Double_t NormL = p[0];
  Double_t mu    = p[1];
  Double_t muP   = mu + p[4];
  Double_t sigma = p[2];
  Double_t sigmaP = sigma*p[5];
  Double_t phi   = p[3];
  Double_t frac = TMath::Sin(phi);
  frac *= frac;
  return TMath::Exp(NormL)*((1 - frac)*TMath::Gaus(x[0],mu ,sigma ,kTRUE) + 
			    frac      *TMath::Gaus(x[0],muP,sigmaP,kTRUE)); 
}
//________________________________________________________________________________
TF1 *FXTGausZ() {
  if (gg) return gg;
  TF1 *f = new TF1("Gaus2",gaus2,190,210,6);
  f->SetParName(0,"NormL"); f->SetParLimits(0,-10.,10.);
  f->SetParName(1,"mu");    f->SetParLimits(1,190,210);
  f->SetParName(2,"sigma"); f->SetParLimits(2, 0.01,0.5);
  f->SetParName(3,"phiP");  f->SetParLimits(3, 0.0,TMath::Pi()/2);
  f->SetParName(4,"muP");
  f->SetParName(5,"sigmaP");
  f->SetParameters( 10, 200.0, 0.2, 0., 1.);
  f->FixParameter(3,0);
  f->FixParameter(4,0);
  f->FixParameter(5,5);
  gg = f;
  return f;
}
//________________________________________________________________________________
