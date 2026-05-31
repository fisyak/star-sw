#ifndef __CINT__
#include "tables/St_tpcCorrection_Table.h"
#endif
TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcCorrection")) return 0;
  Int_t nrows = 2;
  St_tpcCorrection *tableSet = new St_tpcCorrection("TpcZCorrectionC",nrows);
  tpcCorrection_st row;
  memset(&row,0,tableSet->GetRowSize());
  row.idx   = 1;
  row.nrows = nrows;
  row.min =  18.0;
  row.max = 202.0;
  row.npar =            5;// AuAu_2023_1
  row.a[0] =      0.16845;
  row.a[1] =   0.00082959;
  row.a[2] =  -2.7477e-05;
  row.a[3] =   7.3102e-08;
  row.a[4] =   1.7515e-11;
  tableSet->AddAt(&row);
  memset(&row,0,tableSet->GetRowSize());
  row.idx   = 2;
  row.nrows = nrows;
  row.min =  18.0;
  row.max = 202.0;
  row.npar =            5;// AuAu_2023_1
  row.a[0] =      0.14522;
  row.a[1] =  -0.00094477;
  row.a[2] =   2.9219e-05;
  row.a[3] =  -3.4596e-07;
  row.a[4] =   9.5814e-10;
  tableSet->AddAt(&row);
  return (TDataSet *)tableSet;
}
