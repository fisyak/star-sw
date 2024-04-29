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
#include "StTpcUtil/StTpcUtil.h"
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
enum {NPlots = 15, NFPlots=NPlots+7, NwsPlots=20, NwsFPlots=20, NwsPlotsTpc=14};
const  PlotName_t plotNameD[NFPlots] = {// plots for drift
  {"dXdalpha",       "dX versus dX/dalpha[1,4]       => dalpha",     110,  -0.15,   0.15,500,-0.60, 0.60}, // 0
  {"dXdbeta",        "dX versus dX/dbeta[1,5]        => dbeta",      110,  20.00, 210.00,500,-0.60, 0.60}, // 1
  {"dXdgamma",       "dX versus dX/dgamma[1,6]       => dgamma",     110,-123.10,-122.80,500,-0.60, 0.60}, // 2
  {"dZdalpha",       "dZ versus dZ/dalpha[2,4]       => dalpha",     110, 122.80, 123.10,500,-0.20, 0.20}, // 3
  {"dZdbeta",        "dZ versus dZ/dbeta[2,5]        => dbeta",      110, -30.00,  30.00,500,-0.20, 0.20}, // 4
  {"dZdgamma",       "dZ versus dZ/dgamma[2,6]       => dgamma",     110,  -0.01,   0.01,500,-0.20, 0.20}, // 5
  {"dnXdalpha",      "dnX versus dnX/dalpha[3,4]     => dalpha",     110,  -0.60,   0.60,500,-0.02, 0.02}, // 6
  {"dnXdbeta",       "dnX versus dnX/dbeta[3,5]      => dbeta",      110,  -0.80,   0.80,500,-0.02, 0.02}, // 7
  {"dnXdgamma",      "dnX versus dnX/dgamma[3,6]     => dgamma",     110,  -1.00,  -0.50,500,-0.02, 0.02}, // 8
  {"dnYdalpha",      "dnY versus dnY/dalpha[4,4]     => dalpha",     110,  -0.80,   0.80,500,-0.01, 0.01}, // 9
  {"dnYdbeta",       "dnY versus dnY/dbeta[4,5]      => dbeta",      110,  -0.60,   0.60,500,-0.01, 0.01}, //10
  {"dnYdgamma",      "dnY versus dnY/dgamma[4,6]     => dgamma",     110,  -0.70,   0.70,500,-0.01, 0.01}, //11
  {"dnZdalpha",      "dnZ versus dnZ/dalpha[5,4]     => dalpha",     110,   0.40,   1.00,500,-0.01, 0.01}, //12
  {"dnZdbeta",       "dnZ versus dnZ/dbeta[5,5]      => dbeta",      110,  -0.70,   0.70,500,-0.01, 0.01}, //13
  {"dnZdgamma",      "dnZ versus dnZ/dgamma[5,6]     => dgamma",     110,  -0.20,   0.20,500,-0.01, 0.01}, //14
  {"dX"       ,"dX  versus Z"                    , 200,    10,    210, 500, -0.500, 0.500}, //14
  {"dY"       ,"dY  versus Z"                    , 200,    10,    210, 500,  -3e-2,  3e-2}, //15
  {"dZ"       ,"dZ  versus Z"                    , 200,    10,    210, 500, -0.500, 0.500}, //16
  {"dnX"      ,"dnX versus Z"                    , 200,    10,    210, 500, -0.020, 0.020}, //17
  {"dnY"      ,"dnY versus Z"                    , 200,    10,    210, 500,  -2e-2,  2e-2}, //18
  {"dnZ"      ,"dnZ versus Z"                    , 200,    10,    210, 500,  -1e-2,  1e-2}, //19
  {"dT"       ,"dT (time buckets)  versus Z"     , 200,    10,    210, 500, -0.500, 0.500}  //20
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

