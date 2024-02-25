#include "TString.h"
#include "Riostream.h"
#include "TFile.h"
#include "TH3.h"
#include "TH2.h"
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
/* mX(0), A( 4,0), ds, */ {"dnXdbS",       "-nZS   => bS", 110,-1.100, 1.100,100,-0.005, 0.005}, // 0
/* mX(0), A( 5,0), ds, */ {"dnXdgS",       "nYS    => gS", 110,-1.100, 1.100,100,-0.005, 0.005}, // 1
/* mX(0), A(10,0), dw, */ {"dnXdbW",       "-nZU   => bW", 110,-1.100, 1.100,100,-0.005, 0.005}, // 2
/* mX(0), A(11,0), dw, */ {"dnXdgW",       "nYU    => gW", 110,-1.100, 1.100,100,-0.005, 0.005}, // 3
/* mX(1), A( 3,1), ds, */ {"dnYdaS",       "nZS    => aS", 110,-1.100, 1.100,100,-0.005, 0.005}, // 4
/* mX(1), A( 5,1), ds, */ {"dnYdgS",       "-nXS   => gS", 110,-1.100, 1.100,100,-0.005, 0.005}, // 5
/* mX(1), A( 9,1), dw, */ {"dnYdaW",       "nZU    => aW", 110,-1.100, 1.100,100,-0.005, 0.005}, // 6
/* mX(1), A(11,1), dw, */ {"dnYdgW",       "-nXU   => gW", 110,-1.100, 1.100,100,-0.005, 0.005}, // 7
/* mX(2), A( 3,2), ds, */ {"dnZdaS",       "-nYS   => aS", 110,-1.100, 1.100,100,-0.005, 0.005}, // 8
/* mX(2), A( 4,2), ds, */ {"dnZdbS",       "-nXS   => bS", 110,-1.100, 1.100,100,-0.005, 0.005}, // 9
/* mX(2), A( 9,2), dw, */ {"dnZdaW",       "-nYU   => aW", 110,-1.100, 1.100,100,-0.005, 0.005}, //10
/* mX(2), A(10,2), dw, */ {"dnZdbW",       "-nXU   => bW", 110,-1.100, 1.100,100,-0.005, 0.005}, //11
/* mX(3), A( 4,3), ds, */ {"dXdbS",        "-ZS    => bS", 100,-250.0, 9.999,100,-1.000, 1.000}, //12
/* mX(3), A( 5,3), ds, */ {"dXdgS",        "YS     => gS", 110,-1.100, 1.100,100,-1.000, 1.000}, //13
/* mX(3), A(10,3), dw, */ {"dXdbW",        "-ZU    => bW", 100,-250.0, 9.999,100,-1.000, 1.000}, //14
/* mX(3), A(11,3), dw, */ {"dXdgW",        "YU     => gW", 110,-1.100, 1.100,100,-1.000, 1.000}, //15
/* mX(5), A( 3,5), ds, */ {"dZdaS",        "-YS    => aS", 120,-175.0, -55.0,100,-0.005, 0.005}, //16
/* mX(5), A( 4,5), ds, */ {"dZdbS",        "-XS    => bS", 120, -60.0,  60.0,100,-1.000, 1.000}, //17
/* mX(5), A( 9,5), dw, */ {"dZdaW",        "-YU    => aW", 120,-175.0, -55.0,100,-0.005, 0.005}, //18
/* mX(5), A(10,5), dw  */ {"dZdbW",        "-XU    => bW", 120, -60.0,  60.0,100,-1.000, 1.000}  //19
};
//________________________________________________________________________________
void makeW2SHist() {
  const Char_t *M[6] = {"nX",     "nY",   "nZ",   "X",  "Y",     "Z"};
  const Char_t *P[12] = {"xS","yS","zS","aS","bS","gS","xW","yW","zW","aW","bW","gW"};
  const Char_t *S[2] = {"ds", "dw"};
  TString A[12][6] = { 
    //      0       1        2      3      4      5
    //     nX      nY       nZ      X      Y      Z  
    {     "0",    "0",     "0",  "-1",   "0",   "0"}, // 0 xS",
    {     "0",    "0",     "0",   "0",  "-1",   "0"}, // 1 yS",
    {     "0",    "0",     "0",   "0",   "0",  "-1"}, // 2 zS",
    {     "0",  "nZS",  "-nYS",   "0",  "ZS", "-YS"}, // 3 aS",
    {  "-nZS",    "0",  "-nXS", "-ZS",   "0", "-XS"}, // 4 bS",
    {   "nYS", "-nXS",     "0",  "YS", "-XS",   "0"}, // 5 gS",
    {     "0",    "0",     "0",  "-1",   "0",   "0"}, // 6 xW",
    {     "0",    "0",     "0",   "0",  "-1",   "0"}, // 7 yW",
    {     "0",    "0",     "0",   "0",   "0",  "-1"}, // 8 zW",
    {     "0",  "nZU",  "-nYU",   "0",  "ZU", "-YU"}, // 9 aW",
    {  "-nZU",    "0",  "-nXU", "-ZU",   "0", "-XU"}, //10 bW",
    {   "nYU", "-nXU",     "0",  "YU", "-XU",   "0"}  //11 gW",
  };
  Int_t nh = 0;
  for (Int_t m = 0; m < 6; m++) {
    if (m == 4) continue;
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
      if (Meas.BeginsWith("n")) {Zaxis = "100,-0.005, 0.005";}
      else                      {Zaxis = "100,-1.000, 1.000";}
      if      (AA.BeginsWith("-Z"))   {Yaxis = "100,-250.0, 9.999";}
      else if (AA.BeginsWith("Z"))    {Yaxis = "100, 0.000, 250.0";}
      else if (AA.BeginsWith("-Y"))   {Yaxis = "120,-175.0, -55.0"; Zaxis = "100,-0.005, 0.005"; }
      else if (AA.BeginsWith("-Y"))   {Yaxis = "120,  55.0, 175.0"; Zaxis = "100,-0.005, 0.005"; }
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
void CheckPlots() {
  TCanvas *c1 = new TCanvas("Tb","time buckets",1200,800);
  c1->Divide(5,4);
  for (Int_t i = 0; i < NwsPlots; i++) {
    c1->cd(i+1)->SetLogz(1);
    TH3 *h3 = (TH3 *) gDirectory->Get(plotNameWS[i].Name);
    if (! h3) continue;
    h3->Project3D("zy")->Draw("colz");
  }
  c1->Update();
};
 
