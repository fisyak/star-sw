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
  row.npar =            5;// AuAu_2023_2
  row.a[0] =      0.14396;
  row.a[1] =    0.0012006;
  row.a[2] =  -3.0213e-05;
  row.a[3] =   8.4378e-08;
  row.a[4] =  -4.5346e-12;
  tableSet->AddAt(&row);
  memset(&row,0,tableSet->GetRowSize());
  row.idx   = 2;
  row.nrows = nrows;
  row.min =  18.0;
  row.max = 202.0;
  row.npar =            5;// AuAu_2023_2
  row.a[0] =     0.055374;
  row.a[1] =     -0.00297;
  row.a[2] =   9.1542e-05;
  row.a[3] =   -7.318e-07;
  row.a[4] =   1.6359e-09;
  tableSet->AddAt(&row);
  return (TDataSet *)tableSet;
}
