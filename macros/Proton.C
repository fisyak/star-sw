/*
  root.exe 4p59GeV_fixedTarget_TFG24e.dEdx.D.root lBichsel.C DrawdEdx.C+ Proton.C=
*/
#include "TROOT.h"
#include "TMath.h"
#include "TF1.h"
void Proton(Double_t p = 0.5, Double_t M = 0.93827231) {
  struct  MyMat_t {
  public: 
    const Char_t* Material; 
    const Char_t *type;
    Int_t No; 
    Float_t Rmin,Rmax, A, Z, Density, RadLen, Zmin, Zmax;
    //    TGeoMaterial *mat;
    Int_t mat;
  }; 
  MyMat_t myMat[10] = { 
    //         Media name, type, No,   R_min,   R_max,       A,       Z,   density.       X_0,   Z_min,   Z_max, *Media
    //{"Vacuum"            ,"gas",  0,   3.900,   4.000,   1.000,   0.000, 0.000e+00, 1.000e+11, -76.200,  76.200, 0},//PIPE_1/PIPC_1
    //{"Vacuum"            ,"gas",  2,   3.875,   4.000,   1.000,   0.000, 0.000e+00, 1.000e+11,  76.200, 383.000, 0},//PIPE_1/PIPO_1/PVAO_1
    //{"Vacuum"            ,"gas",  4,   3.875,   4.000,   1.000,   0.000, 0.000e+00, 1.000e+11,-383.000, -76.200, 0},//PIPE_2/PIPO_1/PVAO_1
    {"Vacuum"            ,"mat",  2,   0.000,   3.875,   1.000,   0.000, 0.000e+00, 1.000e+11,  76.200, 383.000, 0},
    {"Vacuum"            ,"mat",  4,   0.000,   3.875,   1.000,   0.000, 0.000e+00, 1.000e+11,-383.000, -76.200, 0},
    {"Vacuum"            ,"mat",  0,   0.000,   3.900,   1.000,   0.000, 0.000e+00, 1.000e+11, -76.200,  76.200, 0},//PIPE_1/PIPC_1
    {"BERILLIUM"         ,"mat",  1,   3.900,   4.000,   9.010,   4.000,     1.848, 3.446e+01, -76.200,  76.200, 0},//PIPE_1/PIPC_1
    {"PIPE"              ,"mat",  3,   3.875,   4.000,  26.980,  13.000,     2.700, 8.875e+00,  76.200, 383.000, 0},//PIPE_1/PIPO_1/PVAO_1
    {"PIPE"              ,"mat",  5,   3.875,   4.000,  26.980,  13.000,     2.700, 8.875e+00,-383.000, -76.200, 0},//PIPE_2/PIPO_1/PVAO_1
    {"AIR"               ,"mat", -1,   4.000,   46.60,   14.61,     7.3,0.1205E-02,   30412.6,-383.000, 383.000, 0},
    {"ALUMINIUM_TIFC"    ,"mat",  7,  46.600,  51.700,  21.181,  10.311,     0.089, 3.220e+02,-230.876, 230.484, 0},///TIFC_1
    {"TPCE_SENSITIVE_GAS","gas",  8,  51.700, 200.000,  38.691,  17.436, 1.541e-03, 1.302e+04,-224.186, 223.794, 0},///TOFC_1
    {"ALUMINIUM_TOFC"    ,"mat",  9, 200.000, 207.731,  26.827,  12.886,     0.324, 7.480e+01,-224.186, 223.794, 0} ///TOFC_1
  };
  for (Int_t i = 3; i < 9; i++) {
    cout << myMat[i].Material  << "\tdR = " << myMat[i].Rmax - myMat[i].Rmin << " [cm],  \tX0 = " << (myMat[i].Rmax - myMat[i].Rmin)/myMat[i].RadLen*100 <<  "%" << endl;

  }
  Double_t eta[4] = {0.0, -0.68, -0.87, -1.06};
  Double_t R = 180; // cm
  Double_t bgL10 = TMath::Log10(p/M);
  TF1 *zNp1 = (TF1*) gROOT->GetListOfFunctions()->FindObject("zNp1");
  if (! zNp1) return;
  Double_t dEdx = TMath::Power(10., zNp1->Eval(bgL10));
  Double_t x0TPC = 1.13902; // %
  //                  PIPE        Air       IFC
  Double_t x0All = 1.40845 + 0.140074 + 1.58385 + x0TPC; // %
  Double_t dEdx0 = dEdx*148.3/x0TPC;
  Double_t dEdxT = 1e-6*dEdx0*x0All;
  Double_t E = TMath::Sqrt(p*p + M*M);
  cout << "p = " << p << " [GeV/c] => E = " << E << " [GeV] => " << dEdx << " [keV/cm]" << endl;
  for (Int_t i = 0; i < 4; i++) {
    Double_t e = E - dEdxT*TMath::CosH(eta[i]);
    Double_t pp = TMath::Sqrt(e*e - M*M);
    Double_t bgL10p = TMath::Log10(pp/M);
    Double_t dEdxp = TMath::Power(10., zNp1->Eval(bgL10p));
    cout << "eta = " << eta[i] << "\tpp = " << pp << " [GeV/c] => e = " << e << " [GeV] => " << dEdxp << " [keV/cm] shift = " << (dEdxp/dEdx - 1)*100 << " %" <<  endl;
  }
}
void Deuteron(Double_t p = 0.5, Double_t M = 1.875613) {
  Proton(p,M);
}
/*
root.exe [13] .x Proton.C+
BERILLIUM               dR = 0.0999999 [cm],    X0 = 0.290191%
PIPE            	dR = 0.125 [cm],        X0 = 1.40845% 
PIPE            	dR = 0.125 [cm],        X0 = 1.40845% 
AIR             	dR = 42.6 [cm],         X0 = 0.140074%
ALUMINIUM_TIFC  	dR = 5.1 [cm],          X0 = 1.58385% 
TPCE_SENSITIVE_GAS      dR = 148.3 [cm],        X0 = 1.13902%

p = 0.5 [GeV/c] => E = 1.06318 [GeV] => 8.84264 [keV/cm]
eta = -0.68 pp = 0.495789 [GeV/c] => e = 1.06121 [GeV] => 8.95427 [keV/cm] shift = 1.26234 %
eta = -0.87 pp = 0.495234 [GeV/c] => e = 1.06095 [GeV] => 8.96917 [keV/cm] shift = 1.43085 %
eta = -1.06 pp = 0.494506 [GeV/c] => e = 1.06061 [GeV] => 8.98881 [keV/cm] shift = 1.65303 %
root.exe [14] Deuteron()
p = 0.5 [GeV/c] => E = 1.94111 [GeV] => 26.6898 [keV/cm]
eta = -0.68 pp = 0.476344 [GeV/c] => e = 1.93516 [GeV] => 28.8632 [keV/cm] shift = 8.14325 %
eta = -0.87 pp = 0.473159 [GeV/c] => e = 1.93437 [GeV] => 29.1767 [keV/cm] shift = 9.31784 %
eta = -1.06 pp = 0.468949 [GeV/c] => e = 1.93335 [GeV] => 29.5992 [keV/cm] shift = 10.9011 %

.x Proton.C+
                 p = 0.5      [GeV/c] => E = 1.06318 [GeV] => 8.84264 [keV/cm]
eta = 0         pp = 0.489456 [GeV/c] => e = 1.05826 [GeV] => 9.12733 [keV/cm] shift = 3.21951 %
eta = -0.68     pp = 0.486896 [GeV/c] => e = 1.05708 [GeV] => 9.19913 [keV/cm] shift = 4.03149 %
eta = -0.87     pp = 0.485157 [GeV/c] => e = 1.05628 [GeV] => 9.24854 [keV/cm] shift = 4.59026 %
eta = -1.06     pp = 0.482867 [GeV/c] => e = 1.05523 [GeV] => 9.31438 [keV/cm] shift = 5.33475 %

BERILLIUM       dR = 0.0999999 [cm],    X0 = 0.290191%
PIPE    dR = 0.125 [cm],        X0 = 1.40845%
PIPE    dR = 0.125 [cm],        X0 = 1.40845%
AIR     dR = 42.6 [cm],         X0 = 0.140074%
ALUMINIUM_TIFC  dR = 5.1 [cm],          X0 = 1.58385%
TPCE_SENSITIVE_GAS      dR = 148.3 [cm],        X0 = 1.13902%
                p  = 0.5      [GeV/c] => E = 1.94111 [GeV] => 26.6898 [keV/cm]
eta = 0         pp = 0.438858 [GeV/c] => e = 1.92627 [GeV] => 32.9136 [keV/cm] shift = 23.3192 %
eta = -0.68     pp = 0.422931 [GeV/c] => e = 1.92271 [GeV] => 34.9013 [keV/cm] shift = 30.xs7667 %
eta = -0.87     pp = 0.411814 [GeV/c] => e = 1.92029 [GeV] => 36.3982 [keV/cm] shift = 36.3751 %
eta = -1.06     pp = 0.396776 [GeV/c] => e = 1.91712 [GeV] => 38.5862 [keV/cm] shift = 44.573 %
*/
