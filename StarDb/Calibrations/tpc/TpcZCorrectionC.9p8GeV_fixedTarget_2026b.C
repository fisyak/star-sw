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
  row.npar =            5;// 9p8GeV_fixedTarget_2026b
  row.a[0] =       0.4198;
  row.a[1] =   0.00019881;
  row.a[2] =  -9.8726e-05;
  row.a[3] =   7.2657e-07;
  row.a[4] =    -1.54e-09;
  tableSet->AddAt(&row);
  memset(&row,0,tableSet->GetRowSize());
  row.idx   = 2;
  row.nrows = nrows;
  row.min =  18.0;
  row.max = 202.0;
  row.npar =            5;// 9p8GeV_fixedTarget_2026b
  row.a[0] =      0.70779;
  row.a[1] =    0.0094882;
  row.a[2] =  -0.00029597;
  row.a[3] =   1.9097e-06;
  row.a[4] =  -3.8796e-09;
  tableSet->AddAt(&row);
  memset(&row,0,tableSet->GetRowSize());
  row.idx   = 3;
  row.nrows = nrows;
  row.min =  18.0;
  row.max = 202.0;
  row.npar =            3;// 9p8GeV_fixedTarget_2026b
  row.a[0] =      0.18632;
  row.a[1] =   -0.0020156;
  row.a[2] =   4.2688e-06;
  tableSet->AddAt(&row);
  memset(&row,0,tableSet->GetRowSize());
  row.idx   = 4;
  row.nrows = nrows;
  row.min =  18.0;
  row.max = 202.0;
  row.npar =            3;// 9p8GeV_fixedTarget_2026b
  row.a[0] =       0.2121;
  row.a[1] =  -7.1646e-05;
  row.a[2] =  -5.5418e-06;
  tableSet->AddAt(&row);
  return (TDataSet *)tableSet;
}
