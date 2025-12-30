#ifndef __CINT__
#include "tables/St_tpcCorrection_Table.h"
#endif

TDataSet *CreateTable() { 
  if (!gROOT->GetClass("St_tpcCorrection")) return 0;
  tpcCorrection_st row;
  Int_t nrows = 2;
  St_tpcCorrection *tableSet = new St_tpcCorrection("tpcGainCorrection",nrows);
  memset(&row,0,tableSet->GetRowSize()); // 0
  row.nrows      =        nrows; // VoltageCGFRunIX29DEV
  row.idx        =            1; // FitP->Draw("mu:y-1390>>O(16,-300,20)","(i&&j&&i>13&&abs(mu)<0.4)/(dmu*dmu)","profg")
  row.npar       =            1; // 
  row.min        =         -500;
  row.max        =          100;
  row.a[0]       = TMath::Log(1310)       +3.94933e-04; // from tsspar gain at nominal 1390 V + corrections
  tableSet->AddAt(&row); // Outer
  memset(&row,0,tableSet->GetRowSize()); // 0
  row.nrows      =        nrows; //  VoltageCGFRunIX29DEV 
  row.idx        =            2; //  FitP->Draw("mu:y-1170>>I(20,-180,20)","(i&&j&&prob>0.01&&i<=13&&abs(mu)<0.4)/(dmu*dmu)","profg")
  row.npar       =            1; // 
  row.min        =         -500;
  row.max        =          100;
  row.a[0]       = TMath::Log(3558)                            +1.20357e-03; // at nominal 1170V
  tableSet->AddAt(&row); // Inner
  // ----------------- end of code ---------------
  return (TDataSet *)tableSet;
}
