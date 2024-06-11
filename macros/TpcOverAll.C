/*  Tpc Super Sector Position based on MuTpcG.C.check TFGflag in lDb.C
    root.exe 'lDb.C(1)' TpcOverAll.C+
*/
#if !defined(__CINT__)
// code that should be seen ONLY by the compiler
#else
#if !defined(__CINT__) || defined(__MAKECINT__)
// code that should be seen by the compiler AND rootcint
#else
// code that should always be seen
#endif
#endif
//________________________________________________________________________________
#if !defined(__CINT__) || defined(__MAKECINT__)
#include <stdio.h>
#include <string.h>
#include "Riostream.h"
#include "TString.h"
#include "TMath.h"
#include "TROOT.h"
#include "TSystem.h"
#include "TH1.h"
#include "TStyle.h"
#include "TGraph.h"
#include "TNtuple.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TFile.h"
#include "TNamed.h"
#include "THStack.h"
#include "StChain.h"
#include "tables/St_Survey_Table.h"
#include "TGeoMatrix.h"
#include "StTpcDb/StTpcDb.h"
#include "StEvent/StEnumerations.h"
#include "StDetectorDbMaker/StTpcSurveyC.h"
#include "TGraphErrors.h"
#include "TMultiGraph.h"
#include "TGeoMatrix.h"
#include "StThreeVectorD.hh"
#endif
//________________________________________________________________________________
void TpcOverAll() {
  for (Int_t k = 0; k <= 6; k++) {
    Double_t alpha = 0, beta = 0, gamma = 0, x = 0, y = 0, z = 0;
    if (k == 0) {
    } else if (k == 1) {alpha = 0.010;
    } else if (k == 2) {beta  = 0.010;
    } else if (k == 3) {gamma = 0.010;
    } else if (k == 4) {x     = 0.100;
    } else if (k == 5) {y     = 0.100;
    } else if (k == 6) {z     = 0.100;
    }
    TGeoHMatrix dR;
    Double_t Rotations[9] = {   1., -gamma,  beta, 
				gamma,     1., -alpha,
				-beta, alpha,    1};
    Double_t translation[3] = { x, y, z};
    dR.SetRotation(Rotations);
    dR.SetTranslation(translation);
    dR.Print();
    StThreeVectorD TPCAll;
    StThreeVectorD TPCWest;
    StThreeVectorD TPCEast;
    for (Int_t sector = 1; sector <= 24; sector++) {
      Double_t xyzS[3] = {0, 120, 100};
      StThreeVectorD TPC0;
      StTpcDb::instance()->Sup12S2Tpc(sector).LocalToMaster(xyzS,TPC0.xyz());
      Double_t xyzL[3];
      dR.LocalToMaster(xyzS, xyzL);
      StThreeVectorD TPC;
      //    StTpcDb::instance()->Sup12S2Tpc(sector).Print();
      StTpcDb::instance()->Sup12S2Tpc(sector).LocalToMaster(xyzL,TPC.xyz());
      StThreeVectorD dTPC = TPC - TPC0;
      //      cout << "sector: " << sector << "\txyz \t" << TPC << "\tdTPC\t" << dTPC << endl;
      TPCAll += dTPC;
      if (sector <= 12) TPCWest += dTPC;
      else              TPCEast += dTPC;
    }
    TPCAll /= 24;
    TPCWest /= 12;
    TPCEast /= 12;
    cout << "alpha = " << alpha << " beta = " << beta << " gamma = " << gamma << " x = " << x << " y = " << y << " z = " << z << endl;
    cout << "dTPCAll\t" << TPCAll << "\tdTPCWest\t" << TPCWest <<  "\tdTPCEast\t" << TPCEast << endl;
  }
}
/*
matrix  - tr=1  rot=1  refl=0  scl=0
  1.000000   -0.000000    0.000000    Tx =   0.000000
  0.000000    1.000000   -0.000000    Ty =   0.000000
 -0.000000    0.000000    1.000000    Tz =   0.000000
alpha = 0.00 beta = 0.00 gamma = 0.00 x = 0.00 y = 0.00 z = 0.00
dTPCAll 0.00    0.00    0.00    dTPCWest        0.00    0.00    0.00    dTPCEast        0.00    0.00    0.00
matrix  - tr=1  rot=1  refl=0  scl=0
  1.000000   -0.000000    0.000000    Tx =   0.000000
  0.000000    1.000000   -0.010000    Ty =   0.000000
 -0.000000    0.010000    1.000000    Tz =   0.000000
alpha = 0.01 beta = 0.00 gamma = 0.00 x = 0.00 y = 0.00 z = 0.00
dTPCAll 0.00    0.00    0.00    dTPCWest        -0.00   0.00    -1.20   dTPCEast        0.00    0.00    1.20   << alpha
matrix  - tr=1  rot=1  refl=0  scl=0
  1.000000   -0.000000    0.010000    Tx =   0.000000
  0.000000    1.000000   -0.000000    Ty =   0.000000
 -0.010000    0.000000    1.000000    Tz =   0.000000
alpha = 0.00 beta = 0.01 gamma = 0.00 x = 0.00 y = 0.00 z = 0.00
dTPCAll -0.00   -0.00   0.00    dTPCWest        -0.00   -0.00   0.00    dTPCEast        -0.00   -0.00   0.00
matrix  - tr=1  rot=1  refl=0  scl=0
  1.000000   -0.010000    0.000000    Tx =   0.000000
  0.010000    1.000000   -0.000000    Ty =   0.000000
 -0.000000    0.000000    1.000000    Tz =   0.000000
alpha = 0.00 beta = 0.00 gamma = 0.01 x = 0.00 y = 0.00 z = 0.00
dTPCAll 0.00    -0.00   0.00    dTPCWest        0.00    -0.00   0.00    dTPCEast        0.00    -0.00   0.00
matrix  - tr=1  rot=1  refl=0  scl=0
  1.000000   -0.000000    0.000000    Tx =   0.100000
  0.000000    1.000000   -0.000000    Ty =   0.000000
 -0.000000    0.000000    1.000000    Tz =   0.000000
alpha = 0.00 beta = 0.00 gamma = 0.00 x = 0.10 y = 0.00 z = 0.00
dTPCAll 0.00    0.00    0.00    dTPCWest        -0.00   -0.00   0.00    dTPCEast        0.00    0.00    0.00
matrix  - tr=1  rot=1  refl=0  scl=0
  1.000000   -0.000000    0.000000    Tx =   0.000000
  0.000000    1.000000   -0.000000    Ty =   0.100000
 -0.000000    0.000000    1.000000    Tz =   0.000000
alpha = 0.00 beta = 0.00 gamma = 0.00 x = 0.00 y = 0.10 z = 0.00
dTPCAll -0.00   0.00    0.00    dTPCWest        -0.00   0.00    0.00    dTPCEast        0.00    0.00    0.00
matrix  - tr=1  rot=1  refl=0  scl=0
  1.000000   -0.000000    0.000000    Tx =   0.000000
  0.000000    1.000000   -0.000000    Ty =   0.000000
 -0.000000    0.000000    1.000000    Tz =   0.100000
alpha = 0.00 beta = 0.00 gamma = 0.00 x = 0.00 y = 0.00 z = 0.10
dTPCAll 0.00    0.00    0.00    dTPCWest        0.00    0.00    -0.10   dTPCEast        0.00    0.00    0.10  << z
 */
