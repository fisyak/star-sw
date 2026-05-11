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
  row.npar =            5;// 13p5GeV_fixedTarget_2026
  row.a[0] =      0.66667;
  row.a[1] =    -0.013445;
  row.a[2] =   9.4966e-05;
  row.a[3] =  -3.3042e-07;
  row.a[4] =   4.5584e-10;
  tableSet->AddAt(&row);
  memset(&row,0,tableSet->GetRowSize());
  row.idx   = 2;
  row.nrows = nrows;
  row.min =  18.0;
  row.max = 202.0;
  row.npar =            4;// 13p5GeV_fixedTarget_2026
  row.a[0] =      0.89551;
  row.a[1] =    -0.017746;
  row.a[2] =   0.00010188;
  row.a[3] =  -2.0578e-07;
  tableSet->AddAt(&row);
  memset(&row,0,tableSet->GetRowSize());
  row.idx   = 3;
  row.nrows = nrows;
  row.min =  18.0;
  row.max = 202.0;
  row.npar =            4;// 13p5GeV_fixedTarget_2026
  row.a[0] =      0.13429;
  row.a[1] =   -0.0020495;
  row.a[2] =   9.6366e-06;
  row.a[3] =  -1.8522e-08;
  tableSet->AddAt(&row);
  memset(&row,0,tableSet->GetRowSize());
  row.idx   = 4;
  row.nrows = nrows;
  row.min =  18.0;
  row.max = 202.0;
  row.npar =            3;// 13p5GeV_fixedTarget_2026
  row.a[0] =      0.11629;
  row.a[1] =   0.00056144;
  row.a[2] =  -7.4736e-06;
  tableSet->AddAt(&row);
  return (TDataSet *)tableSet;
}
