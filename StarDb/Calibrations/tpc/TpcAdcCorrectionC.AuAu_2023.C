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
  //    [l409]  /hlt/cephfs/reco/TPC23/2025 $ root.exe 'lDb.C(0,"AuAu_2025,Corrz")' */*/SparseGPAdcSparse8.root Chain.C
  /*
    tChain->Draw("mu:z3>>O(70,3,10,200,0.,1.)","dsigma>0&&dsigma<0.04&&dmu<0.02&&sigma<0.02&&j==2&&z2<203","colz")
    TF1 *off1 = new TF1("off1","TMath::Log(1.+[0]*TMath::Exp(-x))+pol1(1)",3,10.2)
    O->Fit(off1)
  */
  row.type     =           10; //
  row.idx      =            1; //
  row.nrows    =        nrows; //
  row.npar     =            2; //
  row.OffSet   =       7.3107; //   +/-   1.2361    
  row.a[0]     =     0.595928; //   +/-   0.0149052 
  row.a[1]     =   -0.0333872; //   +/-   0.00198954
  tableSet->AddAt(&row);      // 
  memset(&row,0,tableSet->GetRowSize());
  /* 
    tChain->Draw("mu:z3>>I(70,3,10,200,0.,1.)","dsigma>0&&dsigma<0.04&&dmu<0.02&&sigma<0.02&&j==1&&z2<203","colz")
     I->Fit(off1)
  */
  row.type     =           10; //
  row.idx      =            2; //
  row.nrows    =        nrows; //
  row.npar     =            2; //
  row.OffSet   =      7.87712; //   +/-   1.15075    
  row.a[0]     =     0.608362; //   +/-   0.0156548  
  row.a[1]     =   -0.0321323; //   +/-   0.00210247 
  tableSet->AddAt(&row);     // 
// ----------------- end of code ---------------
 return (TDataSet *)tableSet;
}
