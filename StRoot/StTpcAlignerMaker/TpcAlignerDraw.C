/*
  ln -s ~/macros/.sl* .
  root.exe -q -b TpcAlignerDrawB.C+ 'TpcAlignerDraw.C+(2)'>& TpcAlignerDraw.log &
  root.exe -q -b 'TpcAlignerDraw.C+(1)' 'TpcAlignerDraw.C+(3)'> & TpcAlignerDraw1.log &
foreach f (`ls -1d 2014*.root`)
set b = `basename ${f} .root`; root.exe -q -b 'TpcAlignerDraw.C+(0,"'${f}'")' >& ${b}.log &
end
FPE_OFF
foreach f (`ls -1d 2014*.IO*.Errors.root`)
set b = `basename ${f} .root`; root.exe -q -b ${f} 'TpcAlignerDraw.C+(2)' >& ${b}.Fit.log &
end

@ count = 0
foreach r (`ls -1d st_*.root | sed -e 's/st_//' -e 's/adc_//' -e 's/hltcosmic_//' -e 's/gmt_//' | awk -F_ '{print $1}' | sort -u`)
  set file = st${r}Plots.Cut.Errors.root
  if (-r ${file}) continue;
  root.exe -q -b 'TpcAlignerDraw.C+(0,"st*'${r}'*.root")' >& ${r}.log &
    @ count++;  echo "count $count";
    if ($count > 40) break;
end


*/
#if !defined(__CINT__) || defined(__MAKECINT__)
#include "Riostream.h"
#include "Rtypes.h"
#include "TROOT.h"
#include "TSystem.h"
#include "TH2.h"
#include "TH3.h"
#include "TF1.h"
#include "TLegend.h"
#include "TProfile.h"
#include "TTree.h"
#include "TFile.h"
#include "TChain.h"
#include "TCanvas.h"
#include "TClassTable.h"
#include "TVector3.h"
#include "TMinuit.h"
#include "TMinuitMinimizer.h"
#include "TMath.h"
#include "TFileSet.h"
#include "StarRoot/TDirIter.h"
#include "StarRoot/TTreeIter.h"
#include "TArrayD.h"
#include "TRVector.h"
#include "TRMatrix.h"
#include "TGeoMatrix.h"
#endif
/* 
   TpcW2STree->Draw("(abs(HelixU.Rho)-abs(HelixS.Rho))/(abs(HelixU.Rho)+abs(HelixS.Rho))>>dC(100,-2e-1,2e-1)") => sigma = 3.55241e-02
   TpcInOutTree->Draw("(abs(In.Rho)-abs(Out.Rho))/(abs(In.Rho)+abs(Out.Rho))>>dC(100,-2e-1,2e-1)") => 6.24288e-02
 */
static Int_t _debug = 0;
#define PrPP1(B) {cout << (#B) << " = \t" << (B) << endl;}

\

#define PrPP(B) if (_debug) PrPP1(B)

//________________________________________________________________________________
struct PlotName_t {
  const Char_t *Name;
  const Char_t *Title;
  Int_t nx;
  Double_t xmin, xmax;
  Int_t nz;
  Double_t zmin, zmax;
};
enum {NPlots = 21, NFPlots=14, NwsPlots=20, NwsFPlots=20};
const  PlotName_t plotNameD[NPlots] = {// plots for drift
  {"dXdy"     ,"dX  versus  tX         =>  dy",    100,  -0.5,  0.5, 500, -1.000, 1.000}, // 0 -> <dx>, dy   
  {"dXdalpha" ,"dX  versus -tX*zO      =>  alpha", 100,  -60.,  40., 500, -1.000, 1.000}, // 1 -> <dx>, alpha
  {"dXdbeta"  ,"dX  versus -zO         =>  beta",  100, -210., -10., 500, -1.000, 1.000}, // 2 -> <dx>, beta 
  {"dXdgamma" ,"dX  versus  yO + tX*xO =>  gamma", 100,  118., 130., 500, -1.000, 1.000}, // 3 -> <dx>, gamma
  {"dZdy"     ,"dZ  versus  tZ         =>  dy",    100, -0.8 ,  0.6, 500, -1.000, 1.000}, // 4 -> <dz>, dy   
  {"dZdalpha" ,"dZ  versus -(yO+tZ*zO) =>  alpha", 100, -200., -50., 500, -1.000, 1.000}, // 5 -> <dz>, alpha
  {"dZdbeta"  ,"dZ  versus  xO         =>  beta",  100,  -30.,  30., 500, -1.000, 1.000}, // 6 -> <dz>, beta 
  {"dZdgamma" ,"dZ  versus  tZ*xO      =>  gamma", 100,  -10.,  10., 500, -1.000, 1.000}, // 7 -> <dz>, gamma
  {"dnXdbeta" ,"dnX versus -nzO        =>  beta",  100,  -0.8,  0.8, 500, -0.025, 0.025}, // 8 ->       beta 
  {"dnXdgamma","dnX versus  nyO        =>  gamma", 100,   0.7,  1.0, 500, -0.025, 0.025}, // 9 ->       gamma
  {"dnYdalpha","dnY versus  nzO        =>  alpha", 100,  -0.8,  0.8, 500, -0.025, 0.025}, //10 ->       alpha 
  {"dnYdgamma","dnY versus -nxO        =>  gamma", 100,   -.6,   .6, 500, -0.025, 0.025}, //11 ->       gamma
  {"dnZdalpha","dnZ versus -nyO        =>  alpha", 100,  -1.0,  -.7, 500, -0.025, 0.025}, //12 ->       alpha
  {"dnZdbeta" ,"dnZ versus  nxO        =>  beta" , 100,   -.6,   .6, 500, -0.025, 0.025}, //13 ->       beta
  {"dX"       ,"dX  versus Z"                    , 200,    10,  210, 500, -1.000, 1.000}, //14
  {"dY"       ,"dY  versus Z"                    , 200,    10,  210, 500, -0.001, 0.001}, //15
  {"dZ"       ,"dZ  versus Z"                    , 200,    10,  210, 500, -1.000, 1.000}, //16
  {"dnX"      ,"dnX versus Z"                    , 200,    10,  210, 500, -0.025, 0.025}, //17
  {"dnY"      ,"dnY versus Z"                    , 200,    10,  210, 500, -0.025, 0.025}, //18
  {"dnZ"      ,"dnZ versus Z"                    , 200,    10,  210, 500, -0.025, 0.025}, //19
  {"dT"       ,"dT (time buckets)  versus Z"     , 200,    10,  210, 500, -2.000, 2.000}  //20
};
const  PlotName_t plotNameWS[NwsPlots] = {// plots for drift
#if 0
/* mX(0), A( 4,0), ds, */ {"dnXdbS",       "-nZS   => bS", 110,-1.100, 1.100,500,-0.050, 0.050}, // 0
/* mX(0), A( 5,0), ds, */ {"dnXdgS",       "nYS    => gS", 110,-1.100, 1.100,500,-0.050, 0.050}, // 1
/* mX(0), A(10,0), dw, */ {"dnXdbW",       "-nZU   => bW", 110,-1.100, 1.100,500,-0.050, 0.050}, // 2
/* mX(0), A(11,0), dw, */ {"dnXdgW",       "nYU    => gW", 110,-1.100, 1.100,500,-0.050, 0.050}, // 3
/* mX(1), A( 3,1), ds, */ {"dnYdaS",       "nZS    => aS", 110,-1.100, 1.100,500,-0.020, 0.020}, // 4 0.050 => 0.020
/* mX(1), A( 5,1), ds, */ {"dnYdgS",       "-nXS   => gS", 110,-1.100, 1.100,500,-0.020, 0.020}, // 5 
/* mX(1), A( 9,1), dw, */ {"dnYdaW",       "nZU    => aW", 110,-1.100, 1.100,500,-0.020, 0.020}, // 6
/* mX(1), A(11,1), dw, */ {"dnYdgW",       "-nXU   => gW", 110,-1.100, 1.100,500,-0.020, 0.020}, // 7
/* mX(2), A( 3,2), ds, */ {"dnZdaS",       "-nYS   => aS", 110,-1.100, 1.100,500,-0.010, 0.010}, // 8 0.020 => 0.010
/* mX(2), A( 4,2), ds, */ {"dnZdbS",       "-nXS   => bS", 110,-1.100, 1.100,500,-0.010, 0.010}, // 9
/* mX(2), A( 9,2), dw, */ {"dnZdaW",       "-nYU   => aW", 110,-1.100, 1.100,500,-0.010, 0.010}, //10
/* mX(2), A(10,2), dw, */ {"dnZdbW",       "-nXU   => bW", 110,-1.100, 1.100,500,-0.010, 0.010}, //11

/* mX(3), A( 4,3), ds, */ {"dXdbS",        "-ZS    => bS", 100,-250.0, 10.00,500,-1.000, 1.000}, //12 2.000 => 1.000
/* mX(3), A( 5,3), ds, */ {"dXdgS",        "YS     => gS",  65, 50.00,180.00,500,-1.000, 1.000}, //13
/* mX(3), A(10,3), dw, */ {"dXdbW",        "-ZU    => bW", 100,-250.0, 10.00,500,-1.000, 1.000}, //14
/* mX(3), A(11,3), dw, */ {"dXdgW",        "YU     => gW",  65, 50.00,180.00,500,-1.000, 1.000}, //15
/* mX(5), A( 3,5), ds, */ {"dZdaS",        "-YS    => aS",  65,-185.0, -50.0,500,-0.500, 0.500}, //16 1.000 => 0.500
/* mX(5), A( 4,5), ds, */ {"dZdbS",        "-XS    => bS", 120, -60.0,  60.0,500,-0.500, 0.500}, //17
/* mX(5), A( 9,5), dw, */ {"dZdaW",        "-YU    => aW",  65,-185.0, -50.0,500,-0.500, 0.500}, //18
/* mX(5), A(10,5), dw  */ {"dZdbW",        "-XU    => bW", 120, -60.0,  60.0,500,-0.500, 0.500}  //19
#else
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
#endif
};
//________________________________________________________________________________
#include "StTpcAlignerMaker/IO.C"
#include "StTpcAlignerMaker/W2S.C"
//________________________________________________________________________________
void TpcAlignerDraw(Int_t jcase = 0, const Char_t *files = "../*Aligner.root") {
  switch (jcase) {
  case 0: TpcAlignerDrawIO(files);  break;
  case 1: TpcAlignerDrawW2S(files); break;
  case 2: TDrawIO();                break;
  case 3: TDrawW2S();               break;
  default:
    break;
  };
}

