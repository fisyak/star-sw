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
  row.npar =            7;// 9p8GeV_fixedTarget_2026
  row.a[0] =     -0.22489;
  row.a[1] =     0.031053;
  row.a[2] =  -0.00082229;
  row.a[3] =   9.7196e-06;
  row.a[4] =  -6.0916e-08;
  row.a[5] =   1.9683e-10;
  row.a[6] =  -2.5807e-13;
  tableSet->AddAt(&row);
  memset(&row,0,tableSet->GetRowSize());
  row.idx   = 2;
  row.nrows = nrows;
  row.min =  18.0;
  row.max = 202.0;
  row.npar =            6;// 9p8GeV_fixedTarget_2026
  row.a[0] =    -0.046404;
  row.a[1] =     0.048288;
  row.a[2] =   -0.0010557;
  row.a[3] =   9.0297e-06;
  row.a[4] =  -3.6048e-08;
  row.a[5] =   5.5372e-11;
  tableSet->AddAt(&row);
  memset(&row,0,tableSet->GetRowSize());
  row.idx   = 3;
  row.nrows = nrows;
  row.min =  18.0;
  row.max = 202.0;
  row.npar =            3;// 9p8GeV_fixedTarget_2026
  row.a[0] =     0.074173;
  row.a[1] =   -0.0011673;
  row.a[2] =   2.2955e-06;
  tableSet->AddAt(&row);
  memset(&row,0,tableSet->GetRowSize());
  row.idx   = 4;
  row.nrows = nrows;
  row.min =  18.0;
  row.max = 202.0;
  row.npar =            4;// 9p8GeV_fixedTarget_2026
  row.a[0] =      0.20237;
  row.a[1] =  -0.00078579;
  row.a[2] =  -1.3286e-05;
  row.a[3] =   4.6032e-08;
  tableSet->AddAt(&row);
  return (TDataSet *)tableSet;
}
