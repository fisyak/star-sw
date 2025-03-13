TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcCorrection")) return 0;
  Int_t nrows = 2;
  St_tpcCorrection *tableSet = new St_tpcCorrection("TpcZCorrectionC",nrows);
  tpcCorrection_st row;
  memset(&row,0,tableSet->GetRowSize());
  row.idx   = 1;
  row.nrows = nrows;
  row.min =  10.0;
  row.max = 220.0;
  row.npar =            6;// pp500_2022
  row.a[0] =   -0.0064401;
  row.a[1] =    0.0041693;
  row.a[2] =  -9.0693e-05;
  row.a[3] =   7.9915e-07;
  row.a[4] =  -3.3999e-09;
  row.a[5] =    5.635e-12;
  tableSet->AddAt(&row);
  memset(&row,0,tableSet->GetRowSize());
  row.idx   = 2;
  row.nrows = nrows;
  row.min =  10.0;
  row.max = 220.0;
  row.npar =            6;// pp500_2022
  row.a[0] =   -0.0093259;
  row.a[1] =    0.0037267;
  row.a[2] =  -5.0702e-05;
  row.a[3] =   2.6338e-07;
  row.a[4] =  -8.3108e-10;
  row.a[5] =   1.4389e-12;
  tableSet->AddAt(&row);
  return (TDataSet *)tableSet;
}
