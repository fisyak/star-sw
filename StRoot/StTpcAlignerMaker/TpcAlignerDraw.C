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

    root.exe -q -b 'lDb.C(1,"Cosmic_2024/RF,FGdbOpt,CorrZ")' TpcAlignerDraw.C+ 'TpcAlignerDraw.C+(2)'>& TpcAlignerDraw.log &
    root.exe -q -b 'lDb.C(1,"Cosmic_2024/RF,FGdbOpt,CorrZ")' T'pcAlignerDraw.C+(1)' 'TpcAlignerDraw.C+(3)'>& TpcAlignerDraw1.log &
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
#include "StTpcDb/StTpcDb.h"
#include "StBichsel/StTpcUtil.h"
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
enum {NPlots = 6, NFPlots=NPlots+7, NwsPlots=32, NwsFPlots=20, NwsPlotsTpc=14};
const  PlotName_t plotNameD[NFPlots] = {// plots for drift
  {"dXdy",   "dX versus dX/dy[1,2]   => dy",                         110,-0.95,  0.95,500,-0.30, 0.30}, // 0
  {"dXdgamma",       "dX versus dX/dgamma[1,4]       => dgamma",     110,117.0, 137.0,500,-0.30, 0.30}, // 1
  {"dZdy",   "dZ versus dZ/dy[2,2]   => dy", 110, -1.2,              1.0,500,-0.30, 0.30}, // 2
  {"dZdgamma",       "dZ versus dZ/dgamma[2,4]       => dgamma",     110,-25.0, 25.0,500,-0.30, 0.30}, // 3
  {"dnXdgamma",      "dnX versus dnX/dgamma[3,4]     => dgamma",     110,  0.4,  1.0,500,-0.02, 0.02}, // 4
  {"dnYdgamma",      "dnY versus dnY/dgamma[4,4]     => dgamma",     110, -0.8,  0.8,500,-0.02, 0.02}, // 5
  {"dX"       ,"dX  versus Z"                    , 200,    10,    210, 500, -0.300, 0.300}, //14
  {"dY"       ,"dY  versus Z"                    , 200,    10,    210, 500,  -3e-2,  3e-2}, //15
  {"dZ"       ,"dZ  versus Z"                    , 200,    10,    210, 500, -0.300, 0.300}, //16
  {"dnX"      ,"dnX versus Z"                    , 200,    10,    210, 500, -0.020, 0.020}, //17
  {"dnY"      ,"dnY versus Z"                    , 200,    10,    210, 500,  -2e-2,  2e-2}, //18
  {"dnZ"      ,"dnZ versus Z"                    , 200,    10,    210, 500,  -1e-2,  1e-2}, //19
  {"dT"       ,"dT (time buckets)  versus Z"     , 200,    10,    210, 500, -0.500, 0.500}  //20
};
const  PlotName_t plotNameWS[NwsPlots] = {// plots for drift
  {"dXdyS",       "dX     versus dX/dyS   [1, 2]  => dyS",        110,-1.500, 1.500,500,   -0.8,  0.8}, // 0
  {"dXdaS",       "dX     versus dX/daS   [1, 4]  => daS",        110,-300.0, 300.0,500,   -0.8,  0.8}, // 1
  {"dXdbS",       "dX     versus dX/dbS   [1, 5]  => dbS",        110,  10.0, 220.0,500,   -0.8,  0.8}, // 2
  {"dXdgS",       "dX     versus dX/dgS   [1, 6]  => dgS",        110,-200.0, -50.0,500,   -0.8,  0.8}, // 3
  {"dXdxW",       "dX     versus dX/dxW   [1, 7]  => dxW",        110,-1.400, 1.400,500,   -0.8,  0.8}, // 4
  {"dXdyW",       "dX     versus dX/dyW   [1, 8]  => dyW",        110,-1.800, 1.800,500,   -0.8,  0.8}, // 5
  {"dXdaW",       "dX     versus dX/daW   [1,10]  => daW",        110,-340.0, 340.0,500,   -0.8,  0.8}, // 6
  {"dXdbW",       "dX     versus dX/dbW   [1,11]  => dbW",        110,-240.0, 240.0,500,   -0.8,  0.8}, // 7
  {"dXdgW",       "dX     versus dX/dgW   [1,12]  => dgW",        110,-200.0, 200.0,500,   -0.8,  0.8}, // 8
  {"dZdyS",       "dZ     versus dZ/dyS   [2, 2]  => dyS",        110,-1.500, 1.500,500,   -1.0,  1.0}, // 9
  {"dZdaS",       "dZ     versus dZ/daS   [2, 4]  => daS",        110,-200.0, 410.0,500,   -1.0,  1.0}, //10
  {"dZdbS",       "dZ     versus dZ/dbS   [2, 5]  => dbS",        110, -45.0,  45.0,500,   -1.0,  1.0}, //11
  {"dZdgS",       "dZ     versus dZ/dgS   [2, 6]  => dgS",        110, -50.0,  50.0,500,   -1.0,  1.0}, //12
  {"dZdxW",       "dZ     versus dZ/dxW   [2, 7]  => dxW",        110,-0.800, 0.800,500,   -1.0,  1.0}, //13
  {"dZdyW",       "dZ     versus dZ/dyW   [2, 8]  => dyW",        110,-1.500, 1.500,500,   -1.0,  1.0}, //14
  {"dZdaW",       "dZ     versus dZ/daW   [2,10]  => daW",        110,-360.0, 420.0,500,   -1.0,  1.0}, //15
  {"dZdbW",       "dZ     versus dZ/dbW   [2,11]  => dbW",        110,-175.0, 175.0,500,   -1.0,  1.0}, //16
  {"dZdgW",       "dZ     versus dZ/dgW   [2,12]  => dgW",        110, -50.0,  50.0,500,   -1.0,  1.0}, //17
  {"dnXdbS",      "dnX    versus dnX/dbS  [3, 5]  => dbS",        110,-0.800, 0.800,500,  -0.03, 0.03}, //18
  {"dnXdgS",      "dnX    versus dnX/dgS  [3, 6]  => dgS",        110,   -1.,  -0.4,500,  -0.03, 0.03}, //19
  {"dnXdaW",      "dnX    versus dnX/daW  [3,10]  => daW",        110,-0.400, 0.400,500,  -0.03, 0.03}, //20
  {"dnXdbW",      "dnX    versus dnX/dbW  [3,11]  => dbW",        110,-0.700, 0.700,500,  -0.03, 0.03}, //21
  {"dnXdgW",      "dnX    versus dnX/dgW  [3,12]  => dgW",        110,   -1.,    1.,500,  -0.03, 0.03}, //22
  {"dnYdaS",      "dnY    versus dnY/daS  [4, 4]  => daS",        110,-0.800, 0.800,500,  -0.03, 0.03}, //23
  {"dnYdgS",      "dnY    versus dnY/dgS  [4, 6]  => dgS",        110,-0.800, 0.800,500,  -0.03, 0.03}, //24
  {"dnYdaW",      "dnY    versus dnY/daW  [4,10]  => daW",        110,-0.700, 0.700,500,  -0.03, 0.03}, //25
  {"dnYdbW",      "dnY    versus dnY/dbW  [4,11]  => dbW",        110,-0.400, 0.400,500,  -0.03, 0.03}, //26
  {"dnYdgW",      "dnY    versus dnY/dgW  [4,12]  => dgW",        110,-0.800, 0.800,500,  -0.03, 0.03}, //27
  {"dnZdaS",      "dnZ    versus dnZ/daS  [5, 4]  => daS",        110, 0.450, 1.000,500,  -0.01, 0.01}, //28
  {"dnZdbS",      "dnZ    versus dnZ/dbS  [5, 5]  => dbS",        110,-0.800, 0.800,500,  -0.01, 0.01}, //29
  {"dnZdaW",      "dnZ    versus dnZ/daW  [5,10]  => daW",        110,-1.000, 1.000,500,  -0.01, 0.01}, //30
  {"dnZdbW",      "dnZ    versus dnZ/dbW  [5,11]  => dbW",        110,-1.000, 1.000,500,  -0.01, 0.01}, //31
};
const  PlotName_t plotNameTpc[NwsPlotsTpc] = {
  {"dXTpc"       ,"dX  versus Z"                    , 210,  -210,    210, 500, -1.000, 1.000}, // 0
  {"dYTpc"       ,"dY  versus Z"                    , 210,  -210,    210, 500, -1.000, 1.000}, // 1
  {"dZTpc"       ,"dZ  versus Z"                    , 210,  -210,    210, 500, -5.000, 5.000}, // 2
  {"dnXTpc"      ,"dnX versus Z"                    , 210,  -210,    210, 500, -0.010, 0.010}, // 3
  {"dnYTpc"      ,"dnY versus Z"                    , 210,  -210,    210, 500, -0.025, 0.025}, // 4
  {"dnZTpc"      ,"dnZ versus Z"                    , 210,  -210,    210, 500, -0.010, 0.010}, // 5
  {"dTTpc"       ,"dT (time buckets)  versus Z"     , 210,  -210,    210, 500, -5.000, 5.000}, // 6

  {"dXG"         ,"dX  versus Z"                    , 210,  -210,    210, 500, -1.000, 1.000}, // 7
  {"dYG"         ,"dY  versus Z"                    , 210,  -210,    210, 500, -1.000, 1.000}, // 8
  {"dZG"         ,"dZ  versus Z"                    , 210,  -210,    210, 500, -5.000, 5.000}, // 9
  {"dnXG"        ,"dnX versus Z"                    , 210,  -210,    210, 500, -0.010, 0.010}, //10
  {"dnYG"        ,"dnY versus Z"                    , 210,  -210,    210, 500, -0.025, 0.025}, //11
  {"dnZG"        ,"dnZ versus Z"                    , 210,  -210,    210, 500, -0.010, 0.010}, //12
  {"dTG"         ,"dT (time buckets)  versus Z"     , 210,  -210,    210, 500, -5.000, 5.000}  //13
};
//________________________________________________________________________________
#include "StTpcAlignerMaker/IO.C"
#include "StTpcAlignerMaker/W2S.C"
//________________________________________________________________________________
void TpcAlignerDraw(Int_t jcase = 0, const Char_t *files = "../*Aligner.root", const Char_t *Out = "") {
  switch (jcase) {
  case 0: TpcAlignerDrawIO(files, Out);  break;
  case 1: TpcAlignerDrawW2S(files, Out); break;
  case 2: TDrawIO();                break;
  case 3: TDrawW2S();               break;
  default:
    break;
  };
}

