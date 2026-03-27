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
  St_tpcCorrection *tableSet = new St_tpcCorrection("TpcAdcCorrectionC",nrows);
  memset(&row,0,tableSet->GetRowSize());
  /* wihtout He3 and alpha 
[cvmfswrite06] ~/TFG/TPC23/2025 $ root.exe COLE/electron+/SparseGPAdcSparse8.root COLE/electron-/SparseGPAdcSparse8.root COLE/kaon+/SparseGPAdcSparse8.root COLE/kaon-/SparseGPAdcSparse8.root COLE/pion+/SparseGPAdcSparse8.root COLE/pion-/SparseGPAdcSparse8.root COLE/proton+/SparseGPAdcSparse8.root COLE/proton-/SparseGPAdcSparse8.root COLE/triton/SparseGPAdcSparse8.root FXTE/deuteron/SparseGPAdcSparse8.root FXTE/electron+/SparseGPAdcSparse8.root FXTE/electron-/SparseGPAdcSparse8.root FXTE/kaon+/SparseGPAdcSparse8.root FXTE/kaon-/SparseGPAdcSparse8.root FXTE/pion+/SparseGPAdcSparse8.root FXTE/pion-/SparseGPAdcSparse8.root FXTE/proton+/SparseGPAdcSparse8.root FXTE/proton-/SparseGPAdcSparse8.root FXTE/triton/SparseGPAdcSparse8.root Chain.C
    tChain->Draw("mu:z3>>O(70,3,10,200,0.,1.)","dsigma>0&&dsigma<0.02&&dmu>0&&dmu<0.01&&j==2&&z2<203","colz")
    TF1 *off1 = new TF1("off1","TMath::Log(1.+[0]*TMath::Exp(-x))+pol1(1)",3,10.2)
    O->Fit(off1)
  */
  row.type     =           10; //
  row.idx      =            1; //
  row.nrows    =        nrows; //
  row.npar     =            2; //
  row.OffSet   =      5.28057;//   +/-   0.5106         7.3107; //   +/-   1.2361    
  row.a[0]     =     0.673227;//   +/-   0.0107744    0.595928; //   +/-   0.0149052 
  row.a[1]     =   -0.0437482;//   +/-   0.00155876 -0.0333872; //   +/-   0.00198954
  tableSet->AddAt(&row);      // 
  memset(&row,0,tableSet->GetRowSize());
  /* 
    tChain->Draw("mu:z3>>I(70,3,10,200,0.,1.)","dsigma>0&&dsigma<0.02&&dmu>0&&dmu<0.01&&j==1&&z2<203","colz")
     I->Fit(off1)
  */
  row.type     =           10; //
  row.idx      =            2; //
  row.nrows    =        nrows; //
  row.npar     =            2; //
  row.OffSet   =      10.8046;//   +/-   0.625754    7.87712; //   +/-   1.15075    
  row.a[0]     =     0.736502;//   +/-   0.0162701  0.608362; //   +/-   0.0156548  
  row.a[1]     =   -0.0510437;//   +/-   0.002447 -0.0321323; //   +/-   0.00210247 
  tableSet->AddAt(&row);     // 
// ----------------- end of code ---------------
 return (TDataSet *)tableSet;
}
