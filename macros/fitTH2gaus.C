#include "TMath.h"
#include "TH2D.h"
#include "TF1.h"
#include "TF2.h"
#include "TCanvas.h"
#include "TStyle.h"
#include "TVirtualFitter.h"
#include "TROOT.h"
//________________________________________________________________________________
Double_t gauss2D(double *x, double *par) {
  Double_t normL  = par[0];
  Double_t mu1    = par[1];
  Double_t sigma1 = par[2];
  Double_t mu2    = par[3];
  Double_t sigma2 = par[4];
  Double_t rho12  = par[5];
  Double_t X = x[0];
  Double_t Y = x[1];
  Double_t u1 = (X - mu1)/sigma1;
  Double_t u2 = (Y - mu2)/sigma2;
  Double_t rho = 1 - rho12*rho12;
  Double_t resL = (u1*u1 - 2*rho12*u1*u2 + u2*u2)/(2*rho);
  return TMath::Exp(normL - resL)/(TMath::TwoPi()*sigma1*sigma2*rho);
}
//________________________________________________________________________________
void fitTH2gaus(TH2D *h2) {
  Double_t param1[3], param2[3],param[5];
  if (! h2) return;
  TH1D *proj1 = h2->ProjectionX();
  if (proj1->Fit("gaus")) return;
  TF1 *gaus1 = (TF1 *) proj1->GetListOfFunctions()->FindObject("gaus"); 
  if (! gaus1) return;
  gaus1->GetParameters(param1);
  TH1D *proj2 = h2->ProjectionY();
  if (proj2->Fit("gaus")) return;
  TF1 *gaus2 = (TF1 *) proj2->GetListOfFunctions()->FindObject("gaus");
  if (! gaus2) return;
  gaus2->GetParameters(param2);
  param[0] = TMath::Log(param1[0]);
  param[1] = param1[1];
  param[2] = param1[2];
  param[3] = param2[1];
  param[4] = param2[2];
  param[5] = 0;
  TF2 *gaus12 = (TF2 *) gROOT->GetListOfFunctions()->FindObject("gaus12");
  if (! gaus12) {
    gaus12 = new TF2("gaus12",gauss2D, -1, 1, -1, 1, 6);
// 		     h2->GetXaxis()->GetXmin(),h2->GetXaxis()->GetXmax(),
// 		     h2->GetYaxis()->GetXmin(),h2->GetYaxis()->GetXmax(), 6);
    gaus12->SetParName(0,"log(N)");
    gaus12->SetParName(1,"#mu_{1}");
    gaus12->SetParName(2,"#sigma_{1}");
    gaus12->SetParName(3,"#mu_{2}");
    gaus12->SetParName(4,"#sigma_{2}");
    gaus12->SetParName(5,"#rho_{12}");
  }
  gaus12->SetParameters(param);
  h2->Fit(gaus12,"rli");
}
