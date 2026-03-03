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
  //    [l409] /hlt/cephfs/reco/TPC23/2023 $ root.exe SparseGGAdcSparse7.root */SparseGGAdcSparse7.root Chain.C
  /*
    tChain->Draw("mu:z3>>O(72,3,10.2,200,0.2,0.9)","chisq>0&&chisq<2.5e2&&dsigma<0.02&&dmu<0.02&&sigma<0.1&&j==2&&z2<=203","colz")
    TF1 *off3 = new TF1("off3","TMath::Log(1.+[0]*TMath::Exp(-x))+pol3(1)",3,10.2)
    O->Fit(off3)
  */
  row.type     =           10; //
  row.idx      =            1; //
  row.nrows    =        nrows; //
  row.npar     =            4; //
  row.OffSet   =      74.7649;   
  row.a[0]     =     -4.53107; //
  row.a[1]     =      1.83637; //
  row.a[2]     =    -0.228486; //
  row.a[3]     =   0.00927307; //
  tableSet->AddAt(&row);     // 
  memset(&row,0,tableSet->GetRowSize());
  /* 
     tChain->Draw("mu:z3>>I(72,3,10.2,200,0.2,1.2)","chisq>0&&chisq<2.5e2&&dsigma<0.02&&dmu<0.02&&sigma<0.1&&j==1&&z2<=203","colz")
     I->Fit(off3)
  */
  row.type     =           10; //
  row.idx      =            2; //
  row.nrows    =        nrows; //
  row.npar     =            4; //
  row.OffSet   =      88.8702;   
  row.a[0]     =     -3.82625; //
  row.a[1]     =      1.47097; //
  row.a[2]     =    -0.169096; //
  row.a[3]     =   0.00623169; //
  tableSet->AddAt(&row);     // 
// ----------------- end of code ---------------
 return (TDataSet *)tableSet;
}
