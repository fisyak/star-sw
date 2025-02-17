#include "TMath.h"
#include "TString.h"
#include "TH2.h"
#include "TH3.h"
#include "TAxis.h"
#include "TF1.h"
#include "TF2.h"
#include "TCanvas.h"
#include "TStyle.h"
#include "TVirtualFitter.h"
#include "TROOT.h"
TF1 *gaus1 = 0, *gaus2 = 0;
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
TF2 *fit2D(TH2 *h2) {
  Double_t param1[3], param2[3],param[5];
  if (! h2) return 0;
  TH1D *proj1 = h2->ProjectionX();
  if (proj1->Fit("gaus","er","",-1.0,1.0)) return 0;
  gaus1 = (TF1 *) proj1->GetListOfFunctions()->FindObject("gaus"); 
  if (! gaus1) return 0;
  gaus1->GetParameters(param1);
  TH1D *proj2 = h2->ProjectionY();
  if (proj2->Fit("gaus","er","",-1.0,1.0)) return 0;
  gaus2 = (TF1 *) proj2->GetListOfFunctions()->FindObject("gaus");
  if (! gaus2) return 0;
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
  h2->Fit(gaus12,"rl");
  return gaus12;
}
//________________________________________________________________________________
void fit2D(TH3 *h3=0) {
  if (! h3) {
    h3 = (TH3 *) gDirectory->Get("MdYZ");
  }
  if (! h3) return;
  TAxis *xa = h3->GetXaxis();
  Int_t nx = xa->GetNbins();
  for (Int_t ix = 1; ix <= nx; ix++) {
    xa->SetRange(ix,ix);
    TH2D *h2 = (TH2D *) h3->Project3D(Form("yz_%i",ix-1)); 
    TF2 *gaus12 = fit2D(h2);
    if (! gaus12) continue;
    cout << Form("%10s",h2->GetName()); 
    if (gaus1) cout << Form(" Y %7.3f +/- %7.3f sY %7.3f +/- %7.3f",gaus1->GetParameter(1), gaus1->GetParError(1),gaus1->GetParameter(2), gaus2->GetParError(2));  
    else       cout << "                                            ";
    if (gaus2) cout << Form(" Z %7.3f +/- %7.3f sZ %7.3f +/- %7.3f",gaus1->GetParameter(1), gaus1->GetParError(1),gaus1->GetParameter(2), gaus2->GetParError(2));  
    cout << endl;
    cout << "          ";
    cout << Form(" Y %7.3f +/- %7.3f sY %7.3f +/- %7.3f",gaus12->GetParameter(1), gaus12->GetParError(1), gaus12->GetParameter(2), gaus2->GetParError(2));  
    cout << Form(" Z %7.3f +/- %7.3f sZ %7.3f +/- %7.3f",gaus12->GetParameter(3), gaus12->GetParError(3), gaus12->GetParameter(4), gaus2->GetParError(4));  
    cout << Form(" rho %7.3f +/- %7.3f", gaus12->GetParameter(5), gaus2->GetParError(5)) << endl;  
#if 0
    std::cout << h2->GetName(); 
    std::cout << std::fixed << std::showpoint;
    //    std::cout << std::setprecision(5);
    std::cout 
	 << "\tmuY =    " << gaus12->GetParameter(1) << " +/- " << gaus12->GetParError(1)
	 << "\tsigmaY = " << gaus12->GetParameter(2) << " +/- " << gaus12->GetParError(2)
	 << "\tmuZ =    " << gaus12->GetParameter(3) << " +/- " << gaus12->GetParError(3)
	 << "\tsigmaZ = " << gaus12->GetParameter(4) << " +/- " << gaus12->GetParError(4)
	 << "\trhoYZ  = " << gaus12->GetParameter(5) << " +/- " << gaus12->GetParError(5) << std::endl;
#endif
  }
}
