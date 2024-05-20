#include "TString.h"
#include "Riostream.h"
#include "TFile.h"
#include "TH3.h"
#include "TH2.h"
#include "TH1.h"
#include "TObjArray.h"
#include "TCanvas.h"
struct PlotName_t {
  const Char_t *Name;
  const Char_t *Title;
  Int_t nx;
  Double_t xmin, xmax;
  Int_t nz;
  Double_t zmin, zmax;
};
enum {NPlots = 21, NFPlots=14, NwsPlots=20, NwsFPlots=20};
const  PlotName_t plotNameWS[NwsPlots] = {// plots for drift
/* mX(0), A( 4,0), ds, */ {"dXdbS",        "-ZS    => bS", 100,-250.0, 10.00,500,-1.000, 1.000}, // 0
/* mX(0), A( 5,0), ds, */ {"dXdgS",        "YS     => gS",  65,  50.0, 180.0,500,-1.000, 1.000}, // 1
/* mX(0), A(10,0), dw, */ {"dXdbW",        "-ZU    => bW", 100,-250.0, 10.00,500,-1.000, 1.000}, // 2
/* mX(0), A(11,0), dw, */ {"dXdgW",        "YU     => gW",  65,  50.0, 180.0,500,-1.000, 1.000}, // 3
/* mX(2), A( 3,2), ds, */ {"dZdaS",        "-YS    => aS",  65,-180.0, -50.0,500,-1.000, 1.000}, // 4
/* mX(2), A( 4,2), ds, */ {"dZdbS",        "-XS    => bS", 120, -60.0,  60.0,500,-1.000, 1.000}, // 5
/* mX(2), A( 9,2), dw, */ {"dZdaW",        "-YU    => aW",  65,-180.0, -50.0,500,-1.000, 1.000}, // 6
/* mX(2), A(10,2), dw, */ {"dZdbW",        "-XU    => bW", 120, -60.0,  60.0,500,-1.000, 1.000}, // 7
/* mX(3), A( 4,3), ds, */ {"dnXdbS",       "-nZS   => bS", 110,-1.100, 1.100,500,-0.050, 0.050}, // 8
/* mX(3), A( 5,3), ds, */ {"dnXdgS",       "nYS    => gS", 110,-1.100, 1.100,500,-0.050, 0.050}, // 9
/* mX(3), A(10,3), dw, */ {"dnXdbW",       "-nZU   => bW", 110,-1.100, 1.100,500,-0.050, 0.050}, //10
/* mX(3), A(11,3), dw, */ {"dnXdgW",       "nYU    => gW", 110,-1.100, 1.100,500,-0.050, 0.050}, //11
/* mX(4), A( 3,4), ds, */ {"dnYdaS",       "nZS    => aS", 110,-1.100, 1.100,500,-0.020, 0.020}, //12
/* mX(4), A( 5,4), ds, */ {"dnYdgS",       "-nXS   => gS", 110,-1.100, 1.100,500,-0.020, 0.020}, //13
/* mX(4), A( 9,4), dw, */ {"dnYdaW",       "nZU    => aW", 110,-1.100, 1.100,500,-0.020, 0.020}, //14
/* mX(4), A(11,4), dw, */ {"dnYdgW",       "-nXU   => gW", 110,-1.100, 1.100,500,-0.020, 0.020}, //15
/* mX(5), A( 3,5), ds, */ {"dnZdaS",       "-nYS   => aS", 110,-1.100, 1.100,500,-0.010, 0.010}, //16
/* mX(5), A( 4,5), ds, */ {"dnZdbS",       "-nXS   => bS", 110,-1.100, 1.100,500,-0.010, 0.010}, //17
/* mX(5), A( 9,5), dw, */ {"dnZdaW",       "-nYU   => aW", 110,-1.100, 1.100,500,-0.010, 0.010}, //18
/* mX(5), A(10,5), dw  */ {"dnZdbW",       "-nXU   => bW", 110,-1.100, 1.100,500,-0.010, 0.010}, //19
};
//________________________________________________________________________________
void makeW2SHist() {
  enum {kM = 5, kP = 12};
  const Char_t *M[kM] = { "X",  "Z", "nX", "nY", "nZ"};
  const Char_t *P[kP] = {"xS","yS","zS","aS","bS","gS","xW","yW","zW","aW","bW","gW"};
  const Char_t *S[2] = {"ds", "dw"};
  // AT[kP][kM] Fortran
  Int_t nh = 0;
  for (Int_t m = 0; m < kM; m++) {
    Int_t m1 = m + 1; // Fortran
    for (Int_t p = 0; p < kP; p++) {
      Int_t p1 = p + 1; // Fortran AT[p1][m1]
      Int_t s = 0;
      if (p > 6) s = 1;
      if (p1 == 1 ||
	  p1 == 2 && m1 > 2 ||
	  p1 == 3 ||
	  p1 == 4 && m1 == 3 ||
	  p1 == 5 && m1 == 4 ||
	  p1 == 6 && m1 == 5 ||
          p1 == 7 && m1 >  2 ||
	  p1 == 8 && m1 >  2 ||
	  p1 == 9 && m1 >  2) continue;
      if (p1 == 9 && m1 == 1) continue;
      if (p1 == 9 && m1 == 2) continue;
      if (p1 ==12 && m1 == 5) continue;

      TString         Zaxis("500,-250.0, 250.0");
      if (m1 == 1 ) Zaxis = "500,   -1.5,  1.5";
      if (m1 == 2 ) Zaxis = "500,   -1.0,  1.0";
      if (m1 == 3 ) Zaxis = "500,  -0.03, 0.03";
      if (m1 == 4 ) Zaxis = "500,  -0.03, 0.03";
      if (m1 == 5 ) Zaxis = "500,  -0.01, 0.01";
      TString        Yaxis("110,-1.100, 1.100");
      if (m1 == 1) {
      if (p1 == 2 ) Yaxis ="110,-1.500, 1.500";
      if (p1 == 4 ) Yaxis ="110,-300.0, 300.0";
      if (p1 == 5 ) Yaxis ="110,-100.0, 500.0";
      if (p1 == 6 ) Yaxis ="110,-200.0, 280.0";
      if (p1 == 7 ) Yaxis ="110,-1.400, 1.400";
      if (p1 == 8 ) Yaxis ="110,-1.600, 1.600";
      if (p1 ==10 ) Yaxis ="110,-340.0, 340.0";
      if (p1 ==11 ) Yaxis ="110,-300.0, 240.0";
      if (p1 ==12 ) Yaxis ="110,-280.0, 280.0";
      } else if (m1 == 2) {
      if (p1 == 2 ) Yaxis ="110,-1.500, 1.500";
      if (p1 == 4 ) Yaxis ="110,-320.0, 4100.0";
      if (p1 == 5 ) Yaxis ="110,-160.0, 160.0";
      if (p1 == 6 ) Yaxis ="110, -40.0,  40.0";
      if (p1 == 7 ) Yaxis ="110,-1.200, 0.800";
      if (p1 == 8 ) Yaxis ="110,-1.200, 1.200";
      if (p1 ==10 ) Yaxis ="110,-420.0, 560.0";
      if (p1 ==11 ) Yaxis ="110,-300.0, 200.0";
      if (p1 ==12 ) Yaxis ="110, -40.0,  40.0";
      } else if (m1 == 3) {
      if (p1 == 5 ) Yaxis ="110,-0.800, 0.800";
      if (p1 == 6 ) Yaxis ="110,   -1.,    1.";
      if (p1 == 7 ) Yaxis ="110,-0.500, 0.600";
      if (p1 == 8 ) Yaxis ="110,-0.700, 0.700";
      if (p1 ==12 ) Yaxis ="110,   -1.,    1.";
      } else if (m1 == 4) {
      if (p1 == 4 ) Yaxis ="110,-0.800, 0.800";
      if (p1 == 6 ) Yaxis ="110,-0.800, 0.800";
      if (p1 ==10 ) Yaxis ="110,-0.700, 0.800";
      if (p1 ==11 ) Yaxis ="110,-0.600, 0.500";
      if (p1 ==12 ) Yaxis ="110,-0.800, 0.800";
      } else if (m1 == 5) {
      if (p1 == 4 ) Yaxis ="110,-1.000, 1.000";
      if (p1 == 5 ) Yaxis ="110,-0.800, 0.800";
      if (p1 ==10 ) Yaxis ="110,-1.000, 1.000";
      if (p1 ==11 ) Yaxis ="110,-1.000, 1.000";
      }

      TString Meas(M[m]);
#if 0
      cout << "mX(" << m << "), A(" << m << "," << Form("%2i",p) << "), " << S[s] << ", //  {\"d" << M[m] << "d" << P[p] << "\", \t\"" 
	//	   << A[p][m] 
	 << "d" << M[m] 
	   << " \t=> " << P[p] << "\","  
	   << "\t" << Yaxis.Data() << "," << Zaxis.Data()  << "}, //" << Form("%2i",nh) << endl;
#else
      cout << "mX(" << m << "), A(" << m << "," <<  Form("%2i",p)  << "), " << S[s] << ", //  {\"d" 
	   << M[m] << "d" << P[p] << "\", \t\"" << "d" << M[m] 
	   << "\tversus d" << M[m]  << "/d" << P[p]  << "\t[" << m1 << "," <<  Form("%2i",p1) << "] \t=> d" << P[p] << "\","  
	   << "\t" << Yaxis.Data() << "," << Zaxis.Data()  << "}, //" << Form("%2i",nh) << endl;
#endif
      nh++;
    }
  }
  cout << nh << " histograms" << endl;
}
//________________________________________________________________________________
void CheckPlots(const Char_t *opt = "zy") {
  TCanvas *c1 = new TCanvas("Tb","time buckets",1200,800);
  c1->Divide(4,5);
  TObjArray *arr = new TObjArray(4);
  for (Int_t i = 0; i < NwsPlots; i++) {
    c1->cd(i+1)->SetLogz(1);
    TH3 *h3 = (TH3 *) gDirectory->Get(plotNameWS[i].Name);
    if (! h3) continue;
    TH2D *h2zx = (TH2D *) h3->Project3D(opt);
    h2zx->Draw("colz");
    h2zx->FitSlicesY(0, 0, -1, 0, "QNR", arr);
    TH1D *mu = (TH1D *) (*arr)[1];
    TH1D *sigma = (TH1D *) (*arr)[2];
    mu->Draw("sames");
    sigma->Draw("sames");
  }
  c1->Update();
};
//__________________________________________________________________________________________
void makeIOHist() {
  enum {kM = 5, kP = 4};
  const Char_t *M[kM] = { "X",  "Z", "nX", "nY", "nZ"};
  const Char_t *P[kP] = {"x","y","z","gamma"};
  Int_t nh = 0;
  // AT(kP,kM) fortran
  for (Int_t m = 0; m < kM; m++) {
    Int_t m1 = m + 1;
    for (Int_t p = 0; p < kP; p++) {
      Int_t p1 = p + 1;
      if (p1 == 1 ||
	  p1 == 2 && m1 > 2 ||
	  p1 == 3 ||
	  p1 == 4 && m1 == 5) continue;
      TString       Zaxis("500,-0.30, 0.30");
      if (m1 == 2) Zaxis= "500,-0.30, 0.30";
      if (m1 == 3 || 
	  m1 == 4) Zaxis= "500,-0.02, 0.02";
      if (m1 == 5) Zaxis= "500,-0.01, 0.01";
      TString      Yaxis  ("110,-0.95,  0.95");
      if (p1 == 2 && m1 == 2) Yaxis = "110, -1.2,   1.0";
      if (p1 == 4 && m1 == 1) Yaxis = "110,117.0, 137.0";
      if (p1 == 4 && m1 == 2) Yaxis = "110,-25.0, 25.0";
      if (p1 == 4 && m1 == 3) Yaxis = "110,  0.4,  1.0";
      if (p1 == 4 && m1 == 4) Yaxis = "110, -0.8,  0.8";
      cout << "mX(" << m << "), A(" << m << "," << p << "),   //  {\"d" << M[m] << "d" << P[p] << "\", \t\"" << "d" << M[m] 
	   << " versus d" << M[m]  << "/d" << P[p]  << "[" << m1 << "," << p1 << "] \t=> d" << P[p] << "\","  
	   << "\t" << Yaxis.Data() << "," << Zaxis.Data()  << "}, //" << Form("%2i",nh) << endl;
      nh++;
    }
  }
}
/*
dXdy            nx = 24 min = 0.00      max = 26.00     ny = 110        min = -0.95     max = 0.95      nz = 500        min = -0.40     max = 0.40
dXdz            nx = 24 min = 0.00      max = 26.00     ny = 110        min = -0.25     max = 0.25      nz = 500        min = -0.40     max = 0.40
dXdalpha        nx = 24 min = 0.00      max = 26.00     ny = 110        min = -300.00   max = 300.00    nz = 500        min = -0.40     max = 0.40 
dXdbeta         nx = 24 min = 0.00      max = 26.00     ny = 110        min = -450.00   max = -30.00    nz = 500        min = -0.40     max = 0.40
dXdgamma        nx = 24 min = 0.00      max = 26.00     ny = 110        min = 110.0     max = 130       nz = 500        min = -0.40     max = 0.40
dZdz            nx = 24 min = 0.00      max = 26.00     ny =  12        min = -0.60     max = 0.60      nz = 500        min = -0.40     max = 0.40
dZdalpha        nx = 24 min = 0.00      max = 26.00     ny = 110        min = 50.00     max = 850.00    nz = 500        min = -0.40     max = 0.40
dZdbeta         nx = 24 min = 0.00      max = 26.00     ny = 110        min = -0.65     max = 0.60      nz = 500        min = -0.40     max = 0.40
dZdgamma        nx = 24 min = 0.00      max = 26.00     ny = 110        min = -60.00    max = 60.00     nz = 500        min = -0.40     max = 0.40
dnXdalpha       nx = 24 min = 0.00      max = 26.00     ny = 110        min = -0.60     max = 0.600     nz = 500        min = -0.03     max = 0.03
dnXdbeta        nx = 24 min = 0.00      max = 26.00     ny = 110        min = -0.85     max = 0.85      nz = 500        min = -0.03     max = 0.03
dnXdgamma       nx = 24 min = 0.00      max = 26.00     ny = 110        min =  0.40     max = 1.00      nz = 500        min = -0.03     max = 0.03
nYdgamma        nx = 24 min = 0.00      max = 26.00     ny =  12        min = -0.65     max = 0.55      nz = 500        min = -0.02     max = 0.02
dnZdx           nx = 24 min = 0.00      max = 26.00     ny = 110        min = -0.80     max = 0.80      nz = 500        min = -0.01     max = 0.01
dnZdy           nx = 24 min = 0.00      max = 26.00     ny = 110        min = -1.50     max = 1.50      nz = 500        min = -0.01     max = 0.01
dnZdalpha       nx = 24 min = 0.00      max = 26.00     ny = 110        min = -500.00   max = 300.00    nz = 500        min = -0.01     max = 0.01
dnZdbeta        nx = 24 min = 0.00      max = 26.00     ny = 110        min = -30.00    max = 30.00     nz = 500        min = -0.01     max = 0.01
dnZdgamma       nx = 24 min = 0.00      max = 26.00     ny = 110        min = -30.00    max = 30.00     nz = 500        min = -0.01     max = 0.01
 */
