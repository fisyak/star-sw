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
  const Char_t *M[6] = { "X",  "Y",  "Z", "nX", "nY", "nZ"};
  const Char_t *P[12] = {"xS","yS","zS","aS","bS","gS","xW","yW","zW","aW","bW","gW"};
  const Char_t *S[2] = {"ds", "dw"};
  TString A[12][6] = { 
    //     0      1      2      3       4        5
#if 0
    //     X      Y      Z     nX      nY       nZ   
    {   "-1",   "0",   "0"    "0",    "0",     "0",}, // 0 xS",
    {    "0",  "-1",   "0"    "0",    "0",     "0",}, // 1 yS",
    {    "0",   "0",  "-1"    "0",    "0",     "0",}, // 2 zS",
    {    "0",  "ZS", "-YS"    "0",  "nZS",  "-nYS",}, // 3 aS",
    {  "-ZS",   "0", "-XS" "-nZS",    "0",  "-nXS",}, // 4 bS",
    {   "YS", "-XS",   "0"  "nYS", "-nXS",     "0",}, // 5 gS",
    {   "-1",   "0",   "0"    "0",    "0",     "0",}, // 6 xW",
    {    "0",  "-1",   "0"    "0",    "0",     "0",}, // 7 yW",
    {    "0",   "0",  "-1"    "0",    "0",     "0",}, // 8 zW",
    {    "0",  "ZU", "-YU"    "0",  "nZU",  "-nYU",}, // 9 aW",
    {  "-ZU",   "0", "-XU" "-nZU",    "0",  "-nXU",}, //10 bW",
    {   "YU", "-XU",   "0"  "nYU", "-nXU",     "0",}  //11 gW",
#else
    //     X        Y        Z        nX        nY             nZ	  
    {    "-1",     "0",     "0",      "0",      "0",	    "0"},  // xS,
    {     "0",    "-1",     "0",      "0",      "0",	    "0"},  // yS,
    {     "0",     "0",    "-1",      "0",      "0",	    "0"},  // zS,
    {     "0",    "ZS",   "-YS",      "0",    "nZS",	 "-nYS"},  // aS,
    {   "-ZS",     "0",   "-XS",   "-nZS",      "0",	 "-nXS"},  // bS,
    {    "YS",   "-XS",     "0",    "nYS",   "-nXS",	    "0"},  // gS,
    {    "-1",     "0",     "0",      "0",      "0",	    "0"},  // xW,
    {     "0",    "-1",     "0",      "0",      "0",	    "0"},  // yW,
    {     "0",     "0",    "-1",      "0",      "0",	    "0"},  // zW,
    {     "0",    "ZU",   "-YU",      "0",    "nZU",	 "-nYU"},  // aW,
    {   "-ZU",     "0",   "-XU",   "-nZU",      "0",	 "-nXU"},  // bW,
    {    "YU",   "-XU",     "0",    "nYU",   "-nXU",	    "0"},  // gW,
#endif
  };
  Int_t nh = 0;
  for (Int_t m = 0; m < 6; m++) {
    if (m == 1) continue;
    for (Int_t p = 0; p < 12; p++) {
    Int_t s = 0;
    if (p > 6) s = 1;
      TString Der(A[p][m]);
      if (Der == "0") continue;
      if (Der == "-1") continue;
      TString Yaxis("110,-1.100, 1.100");
      TString Zaxis("100,-250.0, 250.0");
      TString Meas(M[m]);
      TString AA(A[p][m]);
      if      (Meas.BeginsWith("nX")) {Zaxis = "500,-0.050, 0.050";}
      else if (Meas.BeginsWith("nY")) {Zaxis = "500,-0.020, 0.020";}
      else if (Meas.BeginsWith("nZ")) {Zaxis = "500,-0.010, 0.010";}
      else                            {Zaxis = "500,-1.000, 1.000";}
      if      (AA.BeginsWith("-Z"))   {Yaxis = "100,-250.0, 10.00";}
      else if (AA.BeginsWith("Z"))    {Yaxis = "100,-10.00, 250.0";}
      else if (AA.BeginsWith("-Y"))   {Yaxis = " 65,-180.0, -50.0";}
      else if (AA.BeginsWith("Y"))    {Yaxis = " 65,  50.0, 180.0";}
      else if (AA.BeginsWith("-X") ||
	       AA.BeginsWith("X"))    {Yaxis = "120, -60.0,  60.0";}
      cout << "mX(" << m << "), A(" << Form("%2i",p) << "," << m << "), " << S[s] << ", // {\"d" << M[m] << "d" << P[p] << "\", \t\"" << A[p][m] << " \t=> " << P[p] << "\","  
	   << "\t" << Yaxis.Data() << "," << Zaxis.Data()  << "}, //" << Form("%2i",nh) << endl;
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
  const Char_t *M[5] = { "X",  "Z", "nX", "nY", "nZ"};
  const Char_t *P[6] = {"alpha","beta","gamma","x","y","z"};
  TString Yaxis("110,-1.100, 1.100");
  TString Zaxis("500,  -1.0,   1.0");
  Int_t nh = 0;
  for (Int_t m = 0; m < 5; m++) {
    Int_t m1 = m + 1;
    for (Int_t p = 0; p < 6; p++) {
      Int_t p1 = p + 1;
      /*
      dRdpIOs(4,4) = 0
      dRdpIOs(4,5) = 0
      dRdpIOs(4,6) = 0
      */
      if (m1 == 4 && p1 >=4) continue;
      cout << "mX(" << m << "), A(" << m << "," << p << "), , // {\"d" << M[m] << "d" << P[p] << "\", \t\"" << "d" << M[m] << "d" << P[p]  << " \t=> d" << P[p] << "\","  
	   << "\t" << Yaxis.Data() << "," << Zaxis.Data()  << "}, //" << Form("%2i",nh) << endl;
      nh++;
    }
  }
}
