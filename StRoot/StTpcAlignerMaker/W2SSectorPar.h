#ifndef __W2SSectorPar23Pass0__
#define __W2SSectorPar23Pass0__
#include "Riostream.h"
#include "Rtypes.h"
#include "TString.h"
#include "TMath.h"
#include "SurveyPass.h"
const Int_t N = 24;
// /net/l404/data/fisyak/Tpc/Alignment/Pass20/

SurveyPass_t Passes[] = {
  //#include "W2S_Pass21.h"
#include "W2S_Pass22.h"
};
const  Int_t NP = sizeof(Passes)/sizeof(SurveyPass_t);
#endif
