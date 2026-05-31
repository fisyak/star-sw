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
  row.npar =            5;// AuAu_2025
  row.a[0] =    -0.089635;
  row.a[1] =  -0.00078796;
  row.a[2] =   9.0264e-06;
  row.a[3] =   1.7041e-08;
  row.a[4] =  -1.3548e-10;
  tableSet->AddAt(&row);
  memset(&row,0,tableSet->GetRowSize());
  row.idx   = 2;
  row.nrows = nrows;
  row.min =  18.0;
  row.max = 202.0;
  row.npar =            5;// AuAu_2025
  row.a[0] =    -0.027516;
  row.a[1] =    0.0005154;
  row.a[2] =  -2.6815e-05;
  row.a[3] =   2.3059e-07;
  row.a[4] =  -5.5249e-10;
  tableSet->AddAt(&row);
  return (TDataSet *)tableSet;
}
