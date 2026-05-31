#ifndef __CINT__
#include "tables/St_tpcCorrection_Table.h"
#endif
TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcCorrection")) return 0;
  Int_t nrows = 4;
  St_tpcCorrection *tableSet = new St_tpcCorrection("TpcZCorrectionC",nrows);
  tpcCorrection_st row;
  memset(&row,0,tableSet->GetRowSize());
  row.idx   = 1;
  row.nrows = nrows;
  row.min =  18.0;
  row.max = 202.0;
  row.npar =            5;// 8p65GeV_fixedTarget_2026
  row.a[0] =      0.63384;
  row.a[1] =    -0.012792;
  row.a[2] =   8.7955e-05;
  row.a[3] =  -2.8318e-07;
  row.a[4] =     3.35e-10;
  tableSet->AddAt(&row);
  memset(&row,0,tableSet->GetRowSize());
  row.idx   = 2;
  row.nrows = nrows;
  row.min =  18.0;
  row.max = 202.0;
  row.npar =            4;// 8p65GeV_fixedTarget_2026
  row.a[0] =       0.8692;
  row.a[1] =    -0.017724;
  row.a[2] =   0.00010606;
  row.a[3] =  -2.2254e-07;
  tableSet->AddAt(&row);
  memset(&row,0,tableSet->GetRowSize());
  row.idx   = 3;
  row.nrows = nrows;
  row.min =  18.0;
  row.max = 202.0;
  row.npar =            3;// 8p65GeV_fixedTarget_2026
  row.a[0] =      0.12899;
  row.a[1] =   -0.0016305;
  row.a[2] =   4.4449e-06;
  tableSet->AddAt(&row);
  memset(&row,0,tableSet->GetRowSize());
  row.idx   = 4;
  row.nrows = nrows;
  row.min =  18.0;
  row.max = 202.0;
  row.npar =            3;// 8p65GeV_fixedTarget_2026
  row.a[0] =       0.1034;
  row.a[1] =   0.00083933;
  row.a[2] =    -7.79e-06;
  tableSet->AddAt(&row);
  return (TDataSet *)tableSet;
}
