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
  row.npar =            7;// AuAu_2025
  row.a[0] =     -0.12605;
  row.a[1] =    0.0031257;
  row.a[2] =  -0.00012171;
  row.a[3] =   2.0348e-06;
  row.a[4] =  -1.5599e-08;
  row.a[5] =   5.7938e-11;
  row.a[6] =  -8.5382e-14;
  tableSet->AddAt(&row);
  memset(&row,0,tableSet->GetRowSize());
  row.idx   = 2;
  row.nrows = nrows;
  row.min =  18.0;
  row.max = 202.0;
  row.npar =            5;// AuAu_2025
  row.a[0] =    -0.045082;
  row.a[1] =    0.0020186;
  row.a[2] =  -4.9638e-05;
  row.a[3] =   3.6423e-07;
  row.a[4] =  -8.1854e-10;
  tableSet->AddAt(&row);
  return (TDataSet *)tableSet;
}
