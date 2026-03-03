#ifndef __CINT__
#include "tables/St_tpcCorrection_Table.h"
#endif
TDataSet *CreateTable() { 
// -----------------------------------------------------------------
// bfc/.make/db/.const/StarDb/Calibrations/tpc/.TpcAdcCorrectionC/TpcAdcCorrectionC Allocated rows: 50  Used rows: 50  Row size: 120 bytes
//  Table: tpcCorrection_st[0]--> tpcCorrection_st[49]
// ====================================================================
// ------  Test whether this table share library was loaded ------
  if (!gROOT->GetClass("St_tpcCorrection")) return 0;
  tpcCorrection_st row;
  Int_t nrows = 2;
  St_tpcCorrection *tableSet = new St_tpcCorrection("TpcAdcCorrectPrompt",nrows);
  memset(&row,0,tableSet->GetRowSize());
  //    [l409] /hlt/cephfs/reco/TPC23/2023 $ root.exe SparseGGAdcSparse7.root */SparseGGAdcSparse7.root Chain.C
  /*
    tChain->Draw("mu:z3>>OPrompt(72,3,10.2,200,0.2,0.6)","chisq>0&&chisq<2.5e2&&dsigma<0.02&&dmu<0.02&&sigma<0.1&&j==2&&z2>203","colz")
    TF1 *off = new TF1("off4","TMath::Log(1.+[0]*TMath::Exp(-x))+pol2(1)",3,10.2)
    OPrompt->Fit(off)
   */
  row.type     =           10; //
  row.idx      =            1; //
  row.nrows    =        nrows; //
  row.npar     =            3; //
  row.OffSet   =     -5.83714;   
  row.a[0]     =      1.07389; //
  row.a[1]     =    -0.137633; //
  row.a[2]     =    0.0048064; //
  tableSet->AddAt(&row);     // 
  memset(&row,0,tableSet->GetRowSize());
  /* 
    tChain->Draw("mu:z3>>IPrompt(72,3,10.2,200,0.2,0.6)","chisq>0&&chisq<2.5e2&&dsigma<0.02&&dmu<0.02&&sigma<0.1&&j==1&&z2>203","colz")
    IPrompt->Fit(off)
   */
  row.type     =           10; //
  row.idx      =            2; //
  row.nrows    =        nrows; //
  row.npar     =            3; //
  row.OffSet   =     -5.33798;   
  row.a[0]     =      1.10012; //
  row.a[1]     =    -0.153088; //
  row.a[2]     =   0.00673854; //
  tableSet->AddAt(&row);     // 
// ----------------- end of code ---------------
 return (TDataSet *)tableSet;
}
