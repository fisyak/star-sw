TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcCorrection")) return 0;
  Int_t nrows = 4;
  St_tpcCorrection *tableSet = new St_tpcCorrection("TpcZCorrectionC",nrows);
  tpcCorrection_st row;
  memset(&row,0,tableSet->GetRowSize());
  row.idx   = 1;
  row.nrows = nrows;
  row.min =  22.5;
  row.max = 208.0;
  row.npar =            6;// 9p8GeV_fixedTarget_2020
  row.a[0] =     0.025914;
  row.a[1] =   -0.0012192;
  row.a[2] =   1.8629e-05;
  row.a[3] =  -1.3497e-07;
  row.a[4] =   4.9118e-10;
  row.a[5] =  -7.0365e-13;
  tableSet->AddAt(&row);
  memset(&row,0,tableSet->GetRowSize());
  row.idx   = 2;
  row.nrows = nrows;
  row.min =  20.5;
  row.max = 208.0;
  row.npar =            6;// 9p8GeV_fixedTarget_2020
  row.a[0] =      0.12662;
  row.a[1] =   -0.0078066;
  row.a[2] =   0.00018198;
  row.a[3] =  -1.8063e-06;
  row.a[4] =   7.9117e-09;
  row.a[5] =  -1.2659e-11;
  tableSet->AddAt(&row);
  memset(&row,0,tableSet->GetRowSize());
  row.idx   = 3;
  row.nrows = nrows;
  row.min =  22.5;
  row.max = 208.0;
  row.npar =            6;// 9p8GeV_fixedTarget_2020
  row.a[0] =   -0.0015172;
  row.a[1] =   0.00064992;
  row.a[2] =  -1.7482e-05;
  row.a[3] =   1.5393e-07;
  row.a[4] =  -6.0603e-10;
  row.a[5] =   9.9364e-13;
  tableSet->AddAt(&row);
  memset(&row,0,tableSet->GetRowSize());
  row.idx   = 4;
  row.nrows = nrows;
  row.min =  20.5;
  row.max = 208.0;
  row.npar =            6;// 9p8GeV_fixedTarget_2020
  row.a[0] =     -0.10176;
  row.a[1] =    0.0036685;
  row.a[2] =  -1.6949e-05;
  row.a[3] =  -2.7039e-07;
  row.a[4] =   2.4059e-09;
  row.a[5] =  -5.0498e-12;
  tableSet->AddAt(&row);
  return (TDataSet *)tableSet;
}
