/*
TpcRS_RF>    root.exe  RF.Plots.root FitTpcT.C
      RF>    root.exe ../TpcRS_RF/RF.Plots.root RF.Plots.root FitTpcT.C
TpcRS_RF>    root.exe  ~/macros/TpcRS_y2023.root *.T.root  FitTpcT.C

*/
#include "Riostream.h"
void FitTpcT() {
#if defined(__CINT__) && ! defined(__MAKECINT__)
  gROOT->LoadMacro("lBichsel.C");
  lBichsel();
  gROOT->LoadMacro("TpcT.C+");
  Fits();
#else
  cout << " FitTpcT.C does not work with AClick" << endl;
#endif
}
