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
  /* wihtout He3 and alpha 
[cvmfswrite06] ~/TFG/TPC23/2025 $ root.exe COLE/electron+/SparseGPAdcSparse8.root COLE/electron-/SparseGPAdcSparse8.root COLE/kaon+/SparseGPAdcSparse8.root COLE/kaon-/SparseGPAdcSparse8.root COLE/pion+/SparseGPAdcSparse8.root COLE/pion-/SparseGPAdcSparse8.root COLE/proton+/SparseGPAdcSparse8.root COLE/proton-/SparseGPAdcSparse8.root COLE/triton/SparseGPAdcSparse8.root FXTE/deuteron/SparseGPAdcSparse8.root FXTE/electron+/SparseGPAdcSparse8.root FXTE/electron-/SparseGPAdcSparse8.root FXTE/kaon+/SparseGPAdcSparse8.root FXTE/kaon-/SparseGPAdcSparse8.root FXTE/pion+/SparseGPAdcSparse8.root FXTE/pion-/SparseGPAdcSparse8.root FXTE/proton+/SparseGPAdcSparse8.root FXTE/proton-/SparseGPAdcSparse8.root FXTE/triton/SparseGPAdcSparse8.root Chain.C
    tChain->Draw("mu:z3>>O(70,3,10,200,0.,1.)","dsigma>0&&dsigma<0.02&&dmu>0&&dmu<0.01&&j==2&&z2>203","colz")
    TF1 *off1 = new TF1("off1","TMath::Log(1.+[0]*TMath::Exp(-x))+pol1(1)",3,10.2)
    O->Fit("pol1")
  */
  row.type     =           10; //
  row.idx      =            1; //
  row.nrows    =        nrows; //
  row.npar     =            2; //
  row.a[0]     =     0.761155;//   +/-   0.00723945  0.722057; //   +/-   0.00919842 
  row.a[1]     =   -0.0595495;//   +/-   0.00136358-0.0532346; //   +/-   0.00164662-
  tableSet->AddAt(&row);     // 
  memset(&row,0,tableSet->GetRowSize());
  /* 
    tChain->Draw("mu:z3>>I(70,3,10,200,0.,1.)","dsigma>0&&dsigma<0.02&&dmu>0&&dmu<0.01&&j==1&&z2>203","colz")
    I->Fit("pol2")
   */
  row.type     =           10; //
  row.idx      =            2; //
  row.nrows    =        nrows; //
  row.npar     =            3; //
  row.a[0]     =    -0.385137; //   +/-   0.175303   0.738988; //   +/-   0.00901403 
  row.a[1]     =     0.485637; //   +/-   0.0847559-0.0556767; //   +/-   0.00166946 
  row.a[2]     =   -0.0635574; //   +/-   0.0101669
  tableSet->AddAt(&row);     // 
// ----------------- end of code ---------------
 return (TDataSet *)tableSet;
}
