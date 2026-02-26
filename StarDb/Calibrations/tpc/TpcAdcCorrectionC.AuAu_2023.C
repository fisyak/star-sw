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
    tChain->Draw("mu:z3>>O","chisq>0&&chisq<2.5e2&&dsigma<0.02&&dmu<0.02&&sigma<0.1&&abs(mu-0.5)<0.2&&j==2","colz")
    O->FitSlicesY()
    TF1 *off = new TF1("off","TMath::Log(1.+[0]*TMath::Exp(-x))+pol2(1)",310)
    O_1->Fit(off,"er","",4.2,8.0)
    root.exe [42] O_1->Fit(off,"er","",4,7.5)
   */
  row.type     =           10; //
  row.idx      =            1; //
  row.nrows    =        nrows; //
  row.min      =          4.2;
  row.max      =          8.0;
  row.npar     =            4; //
  row.OffSet   =  2.29187e+01;
  row.a[0]     = -5.12735e-01; //
  row.a[1]     =  3.00282e-01; //
  row.a[2]     = -2.52198e-02; //
  tableSet->AddAt(&row);     // 
  memset(&row,0,tableSet->GetRowSize());
  /* 
    tChain->Draw("mu:z3>>I","chisq>0&&chisq<2.5e2&&dsigma<0.02&&dmu<0.02&&sigma<0.1&&abs(mu-0.5)<0.2&&j==1","colz")
    I->FitSlicesY()
    TF1 *off = new TF1("off","TMath::Log(1.+[0]*TMath::Exp(-x))+pol2(1)",310)
    I_1->Fit(off,"er","",4.2,8.0)
   */
  row.type     =           10; //
  row.idx      =            2; //
  row.nrows    =        nrows; //
  row.min      =          4.2;
  row.max      =          8.0;
  row.npar     =            3; //
  row.OffSet   =  3.63779e+01;
  row.a[0]     = -6.94882e-01; //
  row.a[1]     =  3.35395e-01; //
  row.a[2]     = -2.63062e-02; //
  tableSet->AddAt(&row);     // 
// ----------------- end of code ---------------
 return (TDataSet *)tableSet;
}
