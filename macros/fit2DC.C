#include "TF2.h"
#include "TMath.h"
#include "TROOT.h"
#include "TH2.h"
#include "TH3.h"
#include "Ask.h"
#include "TCanvas.h"
//________________________________________________________________________________
Double_t gauss2DC(double *x, double *par) {
  Double_t normL  = par[0];
  Double_t muX    = par[1];
  Double_t muY    = par[2];
  Double_t sigmaX2 = 2*par[3]*par[3];
  Double_t sigmaY2 = 2*par[4]*par[4];
  Double_t phi    = TMath::DegToRad()*par[5];
  Double_t X = x[0] - muX;
  Double_t Y = x[1] - muY;
  Double_t C = TMath::Cos(phi);
  Double_t S = TMath::Sin(phi);
  Double_t a =  C*C/sigmaX2 + S*S/sigmaY2;
  Double_t b = -S*C/sigmaX2 + S*C/sigmaY2;
  Double_t c =  S*S/sigmaX2 + C*C/sigmaY2;
  Double_t val = a*X*X + 2*b*X*Y + c*Y*Y;
  return TMath::Exp(normL - val);
}
//________________________________________________________________________________
TF2 *Fit2DC() {
 TF2 *gaus12 = (TF2 *) gROOT->GetListOfFunctions()->FindObject("gausD2");
  if (! gaus12) {
    gaus12 = new TF2("gaus2D",gauss2DC, -0.5, 0.5, -0.5, 0.5, 6);
    gaus12->SetParName(0,"log(N)");
    gaus12->SetParName(1,"#mu_{X}");  gaus12->SetParLimits(1,-.5,0.5);
    gaus12->SetParName(2,"#mu_{Y}");  gaus12->SetParLimits(2,-.5,0.5);
    gaus12->SetParName(3,"#sigma_{X}"); gaus12->SetParLimits(3,1e-3,0.5);
    gaus12->SetParName(4,"#sigma_{Y}"); gaus12->SetParLimits(4,1e-3,0.5);
    gaus12->SetParName(5,"#phi");  gaus12->SetParLimits(5,-90.0, 90.0);
    Double_t param[6] = {0., 0., 0., 1e-2, 1e-2, 0.};
    gaus12->SetParameters(param);
  }
  return gaus12;
}
//________________________________________________________________________________
void fit2DC(TH2 *h = 0) {
  if (! h) return;
  TF2 *F = Fit2DC();
  F->SetParameter(0, 2./TMath::Pi()*TMath::Log(h->GetEntries()));
  F->SetParameter(1, h->GetMean(1));
  F->SetParameter(2, h->GetMean(2));
  F->SetParameter(3, h->GetRMS(1));
  F->SetParameter(4, h->GetRMS(2));
  F->SetParameter(5, 2*TMath::RadToDeg()*TMath::ATan(h->GetCorrelationFactor(1,2)));
  F->Print();
  F->FixParameter(1,0);
  F->FixParameter(2,0);
  h->Fit(F);
}
//________________________________________________________________________________
void fitdXY(TH3 * dXY = 0) {
  if (! dXY) return;
  TAxis *z = dXY->GetZaxis();
  Int_t nz = z->GetNbins();
  for (Int_t i = 1; i <= nz; i++) {
    z->SetRange(i,i);
    TH2 *h2 = (TH2 *) dXY->Project3D(Form("yx_%i",i));
    if (! h2) continue;
    if (h2->GetEntries() < 100) continue;
    fit2DC(h2);
    if (Ask()) break;
  }
}
