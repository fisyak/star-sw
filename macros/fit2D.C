// Instruction at the bottom 
#include "Riostream.h"
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
#include "TSystem.h"
TF1 *gaus1 = 0, *gaus2 = 0;
TCanvas *c1 = 0;
Int_t module = -1;
//________________________________________________________________________________
Double_t gauss2D(double *x, double *par) {
  Double_t normL  = par[0];
  Double_t mu1    = par[1];
  Double_t sigma1 = par[2];
  Double_t mu2    = par[3];
  Double_t sigma2 = par[4];
  Double_t rho12  = par[5];
  Double_t back   = par[6];
  Double_t X = x[0];
  Double_t Y = x[1];
  Double_t u1 = (X - mu1)/sigma1;
  Double_t u2 = (Y - mu2)/sigma2;
  Double_t rho = 1 - rho12*rho12;
  Double_t resL = (u1*u1 - 2*rho12*u1*u2 + u2*u2)/(2*rho);
  return TMath::Exp(normL - resL)/(TMath::TwoPi()*sigma1*sigma2*rho);
}
//________________________________________________________________________________
Double_t gauss1D(double *x, double *par) {
  Double_t normL  = par[0];
  Double_t mu1    = par[1];
  Double_t sigma1 = par[2];
  Double_t back   = par[3];
  Double_t val = back;
  if (normL < -9) return val;
  Double_t X = x[0];
  Double_t u1 = (X - mu1)/sigma1;
  Double_t resL = u1*u1;
  val +=  TMath::Exp(normL - resL)/(TMath::Sqrt(TMath::TwoPi())*sigma1);
  return val;
}
//________________________________________________________________________________
TF2 *fit2D(TH2 *h2) {
  Double_t param1[4], param2[4],param[6];
  if (! h2) return 0;
  TF1 *gaus1D = (TF1 *) gROOT->GetListOfFunctions()->FindObject("gaus1D");
  if (! gaus1D) {
    gaus1D = new TF1("gaus1D",gauss1D, -2.5, 2.5, 4);
    gaus1D->SetParName(0,"log(N)");
    gaus1D->SetParName(1,"#mu");
    gaus1D->SetParName(2,"#sigma"); gaus1D->SetParLimits(2,0.01,0.5);
    gaus1D->SetParName(3,"back");
  }
  TH1D *proj1 = h2->ProjectionX();
  Double_t T = proj1->GetEntries();
  Double_t mu = proj1->GetMean();
  Double_t sigma = proj1->GetRMS();
  if (sigma > 0.5) sigma = 0.5;
  c1->cd(3*module+1);
  gaus1D->FixParameter(0,-99.);
  gaus1D->FixParameter(1, mu); 
  gaus1D->FixParameter(2, sigma); 
  proj1->Fit(gaus1D,"rl");
  gaus1D->ReleaseParameter(0); gaus1D->SetParameter(0, TMath::Log(T) - 1.0); gaus1D->SetParLimits(0, 0.0, TMath::Log(T));
  gaus1D->ReleaseParameter(1); gaus1D->FixParameter(1, mu); gaus1D->SetParLimits(1, mu - 1.0, mu + 1.0); 
  gaus1D->ReleaseParameter(2); gaus1D->FixParameter(2, sigma); gaus1D->SetParLimits(2,0.05, sigma);
  if (proj1->Fit(gaus1D,"erl","",-2.5,2.5)) {proj1->Draw(); return 0;}
  c1->Update();
  gaus1 = (TF1 *) proj1->GetListOfFunctions()->FindObject("gaus1D"); 
  if (! gaus1) return 0;
  gaus1->GetParameters(param1);
  TH1D *proj2 = h2->ProjectionY();
  c1->cd(3*module+2); 
  gaus1D->FixParameter(0,-99.);
  gaus1D->FixParameter(1, proj2->GetMean());
  gaus1D->FixParameter(2, proj2->GetRMS());
  proj2->Fit(gaus1D,"rl");
  T = proj2->GetEntries();
  mu = proj2->GetMean();
  sigma = proj2->GetRMS();
  if (sigma > 0.5) sigma = 0.5;
  gaus1D->ReleaseParameter(0); gaus1D->SetParameter(0, TMath::Log(T) - 1.0); gaus1D->SetParLimits(0, 0.0, TMath::Log(T));
  gaus1D->ReleaseParameter(1); gaus1D->FixParameter(1, mu); gaus1D->SetParLimits(1, mu - 1.0, mu + 1.0); 
  gaus1D->ReleaseParameter(2); gaus1D->FixParameter(2, sigma); gaus1D->SetParLimits(2,0.05, sigma);
  if (proj2->Fit(gaus1D,"erl","",-2.5,2.5)) {proj2->Draw(); return 0;}
  c1->Update();
  gaus2 = (TF1 *) proj2->GetListOfFunctions()->FindObject("gaus1D");
  if (! gaus2) return 0;
  gaus2->GetParameters(param2);
  param[0] = TMath::Log(param1[0]);
  param[1] = param1[1];
  param[2] = param1[2];
  param[3] = param2[1];
  param[4] = param2[2];
  param[5] = 0;
  param[6] = 0.5*(param1[3] + param2[3]);
  TF2 *gaus12 = (TF2 *) gROOT->GetListOfFunctions()->FindObject("gausD2");
  if (! gaus12) {
    gaus12 = new TF2("gaus2D",gauss2D, -2.5, 2.5, -2.5, 2.5, 7);
// 		     h2->GetXaxis()->GetXmin(),h2->GetXaxis()->GetXmax(),
// 		     h2->GetYaxis()->GetXmin(),h2->GetYaxis()->GetXmax(), 6);
    gaus12->SetParName(0,"log(N)");
    gaus12->SetParName(1,"#mu_{1}");
    gaus12->SetParName(2,"#sigma_{1}");
    gaus12->SetParName(3,"#mu_{2}");
    gaus12->SetParName(4,"#sigma_{2}");
    gaus12->SetParName(5,"#rho_{12}");
    gaus12->SetParName(6,"back");
  }
  gaus12->SetParameters(param);
  c1->cd(3*module+3);
  h2->Fit(gaus12,"rl");
  c1->Update();
  return gaus12;
}
//________________________________________________________________________________
void fit2D(TH3 *h3=0) {
  if (! h3) {
    h3 = (TH3 *) gDirectory->Get("MdYZ");
  }
  TString Out("GMT.");
  Out += gDirectory->GetName();
  Out.ReplaceAll("/","_");
  Out.ReplaceAll(".root",".data");
  ofstream out;
  if (gSystem->AccessPathName(Out)) out.open(Out, ios::out); //"Results.list",ios::out | ios::app);
  else                              out.open(Out, ios::app);
  cout << Out.Data() << endl;
  out << Out.Data() << endl;
  if (! h3) return;
  TAxis *xa = h3->GetXaxis();
  Int_t nx = xa->GetNbins();
  c1 = (TCanvas *) gROOT->GetListOfCanvases()->FindObject("c1");
  if (! c1) c1 = new TCanvas("c1","c1",600,1600);
  c1->Clear();
  c1->Divide(3,nx);
  for (module = 0; module < nx; module++) {
    Int_t ix = module + 1;
    xa->SetRange(ix,ix);
    TH2D *h2 = (TH2D *) h3->Project3D(Form("yz_%i",ix-1)); 
    TF2 *gaus12 = fit2D(h2);
    if (! gaus12) continue;
    cout << Form("%10s",h2->GetName()); 
    if (gaus1) cout << Form(" Y %7.3f +/- %7.3f sY %7.3f +/- %7.3f",gaus1->GetParameter(1), gaus1->GetParError(1),gaus1->GetParameter(2), gaus2->GetParError(2));  
    else       cout << "                                            ";
    if (gaus2) cout << Form(" Z %7.3f +/- %7.3f sZ %7.3f +/- %7.3f",gaus2->GetParameter(1), gaus2->GetParError(1),gaus2->GetParameter(2), gaus2->GetParError(2));  
    cout << endl;
    cout << "          ";
    cout << Form(" Y %7.3f +/- %7.3f sY %7.3f +/- %7.3f",gaus12->GetParameter(1), gaus12->GetParError(1), gaus12->GetParameter(2), gaus12->GetParError(2));  
    cout << Form(" Z %7.3f +/- %7.3f sZ %7.3f +/- %7.3f",gaus12->GetParameter(3), gaus12->GetParError(3), gaus12->GetParameter(4), gaus12->GetParError(4));  
    cout << Form(" rho %7.3f +/- %7.3f", gaus12->GetParameter(5), gaus12->GetParError(5));
    if (gaus12->GetParameter(2) > 0.45 || gaus12->GetParameter(4) > 0.45) cout << " ==========  Unreliable";
    cout<< endl;  
    //
    out << Form("%10s",h2->GetName()); 
    if (gaus1) out << Form(" Y %7.3f +/- %7.3f sY %7.3f +/- %7.3f",gaus1->GetParameter(1), gaus1->GetParError(1),gaus1->GetParameter(2), gaus2->GetParError(2));  
    else       out << "                                            ";
    if (gaus2) out << Form(" Z %7.3f +/- %7.3f sZ %7.3f +/- %7.3f",gaus2->GetParameter(1), gaus2->GetParError(1),gaus2->GetParameter(2), gaus2->GetParError(2));  
    out << endl;
    out << "          ";
    out << Form(" Y %7.3f +/- %7.3f sY %7.3f +/- %7.3f",gaus12->GetParameter(1), gaus12->GetParError(1), gaus12->GetParameter(2), gaus12->GetParError(2));  
    out << Form(" Z %7.3f +/- %7.3f sZ %7.3f +/- %7.3f",gaus12->GetParameter(3), gaus12->GetParError(3), gaus12->GetParameter(4), gaus12->GetParError(4));  
    out << Form(" rho %7.3f +/- %7.3f", gaus12->GetParameter(5), gaus12->GetParError(5));
    if (gaus12->GetParameter(2) > 0.45 || gaus12->GetParameter(4) > 0.45) out << " ==========  Unreliable";
    out<< endl;  
  }
  out.close();
}
#if 0
//foreach f (`ls -1d */*/MdYZB.root`)
   root.exe -q ${f} fit2D.C+
end
#endif
