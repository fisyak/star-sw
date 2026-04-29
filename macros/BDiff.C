// root.exe lBichsel.C BDiff.C+
#include "Names.h"
#include "StRoot/StBichsel/Bichsel.h"
#include "StRoot/StBichsel/StdEdxModel.h"
#include "TMath.h"
#include "TF1.h"
#include "TH1.h"
#include "TRandom.h"
static Bichsel *m_Bichsel = 0;
//________________________________________________________________________________
Double_t gFunc(Double_t *x, Double_t *p = 0) {
  return TMath::Gaus(x[0], 1.75843e-01,2.21705e-01);
}
//________________________________________________________________________________
void BDiff() {
#ifdef __Bichsel__1   
  m_Bichsel = Bichsel::Instance();
#endif
#if 1
  // MIP from Heed bg = 3.77 => p_pion = 0.526
  Double_t pMIP = 0.526;
  Double_t pmin = pMIP - 0.05; // 0.45;
  Double_t pmax = pMIP + 0.05; // 0.55;
#else
  Double_t pmin = 0.35;
  Double_t pmax = 0.75;
#endif
  //                 pi p  k  e  d mu t He3 alpha 
  enum {nh = 9};
  Int_t idx[nh] = {2, 8, 6, 5,10, 0,11,12, 13};
  Int_t kpi = idx[0];
  TH1D *hyps[nh] = {0};
  TH2F *hypsp[nh] = {0};
  for (Int_t h = 1; h < nh; h++) {
    Int_t i = idx[h];
    hyps[h] = new TH1D(TpcRSPart[i].name,TpcRSPart[i].name,1440,-0.2,14.2);
    hypsp[h] = new TH2F(Form("%sP",TpcRSPart[i].name),TpcRSPart[i].name,40,pmin,pmax,1440,-0.2,14.2);
  }
  TH2F *zpiP = new TH2F("zpiP","zP vs zpi",100,7.8,8.0,100,8,10);
  //  TF1::InitStandardFunctions();
  TF1 *f = new TF1("pMom",gFunc,pmin,pmax); 
  f->SetNpx(500);
  //  TF1 *f = new TF1("pMom","gaus",pmin,pmax,3); 
  // TF1 *f = new TF1("gaus","gaus",pmin,pmax); 
  //  TF1 *f = (TF1 *) gROOT->GetListOfFunctions()->FindObject("gaus");
  //  f->SetRange(pmin,pmax);
  // f->SetParameters(1., 1.75843e-01,2.21705e-01);
  for (Int_t iev = 0; iev < 10000; iev++) {
    //    Double_t p = pmin + (pmax - pmin)*gRandom->Rndm();
    Double_t p = f->GetRandom();
    Double_t bgpi = p/TpcRSPart[kpi].mass;
    Double_t dX = 4.0; // 2.0;
    Double_t dXLog2 = TMath::Log2(dX);
    StdEdxModel::instance()->ZMP()->SetParameter(0,dXLog2);
    StdEdxModel::instance()->ZMP()->SetParameter(1,TpcRSPart[kpi].charge);
    StdEdxModel::instance()->ZMP()->SetParameter(2,TpcRSPart[kpi].mass);
    Double_t zpi =  StdEdxModel::instance()->ZMP()->Eval(TMath::Log10(bgpi));
    for (Int_t h = 1; h < nh; h++) {
     Int_t i = idx[h];
     Double_t bg = p/TpcRSPart[i].mass;
     StdEdxModel::instance()->ZMP()->SetParameter(1,TpcRSPart[i].charge);
     StdEdxModel::instance()->ZMP()->SetParameter(2,TpcRSPart[i].mass);
     Double_t z =  StdEdxModel::instance()->ZMP()->Eval(TMath::Log10(bg));
      if (h == 1) {
	zpiP->Fill(zpi, z);
#if 0
	cout << "p = " << p << "\tbgpi = " << bgpi << "\tn_Ppi = " << n_Ppi << "\tlogdEMPVpi = " << logdEMPVpi << "\tzpi = " << zpi << endl;
	cout                <<  "\t\tbg = " << bg << "\tn_P = " << n_P << "\tlogdEMPV = " << logdEMPV << "\tz = " << z << "\tdz = " << z - zpi <<  endl;
#endif
      }
      hyps[h]->Fill(z-zpi);
      hypsp[h]->Fill(p,z-zpi);
    }
  }
  for (Int_t h = 1; h < nh; h++) {
    Int_t i = idx[h];
    cout << "\t{\t" << hyps[h]->GetMean() << ",\t" <<  hyps[h]->GetRMS() << ",\t" << TpcRSPart[i].mass << ",\t\"" << hyps[h]->GetName() << "\"}," << endl;
  }
}
/* dX = 2cm
        {       1.25585,        0.0819109,      0.938272,       "proton+"},
        {       0.458602,       0.0504055,      0.493677,       "kaon+"},
        {       0.351404,       0.000874124,    0.000510999,    "electron+"},
        {       2.36284,        0.088633,       1.87561,        "deuteron"},
        {       0.0129274,      0.00328871,     0.105658,       "muon+"},
        {       2.9919, 0.0814963,      2.80892,        "triton"},
        {       4.39986,        0.079048,       2.80839,        "He3"},
        {       4.78636,        0.0707888,      3.72738,        "alpha"},

 */
