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
  row.npar =            5;// 9p8GeV_fixedTarget_2026
  row.a[0] =      0.61465;
  row.a[1] =     -0.01265;
  row.a[2] =   9.1944e-05;
  row.a[3] =  -3.3903e-07;
  row.a[4] =   5.0017e-10;
  tableSet->AddAt(&row);
  memset(&row,0,tableSet->GetRowSize());
  row.idx   = 2;
  row.nrows = nrows;
  row.min =  18.0;
  row.max = 202.0;
  row.npar =            5;// 9p8GeV_fixedTarget_2026
  row.a[0] =       1.0633;
  row.a[1] =    0.0063969;
  row.a[2] =  -0.00029066;
  row.a[3] =   1.8567e-06;
  row.a[4] =  -3.7163e-09;
  tableSet->AddAt(&row);
  memset(&row,0,tableSet->GetRowSize());
  row.idx   = 3;
  row.nrows = nrows;
  row.min =  18.0;
  row.max = 202.0;
  row.npar =            3;// 9p8GeV_fixedTarget_2026
  row.a[0] =     0.059668;
  row.a[1] =   -0.0012654;
  row.a[2] =   2.7567e-06;
  tableSet->AddAt(&row);
  memset(&row,0,tableSet->GetRowSize());
  row.idx   = 4;
  row.nrows = nrows;
  row.min =  18.0;
  row.max = 202.0;
  row.npar =            4;// 9p8GeV_fixedTarget_2026
  row.a[0] =      0.23305;
  row.a[1] =   -4.984e-05;
  row.a[2] =  -2.4791e-05;
  row.a[3] =   8.8474e-08;
  tableSet->AddAt(&row);
  return (TDataSet *)tableSet;
}
