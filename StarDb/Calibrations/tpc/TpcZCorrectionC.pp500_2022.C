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
  row.a[0] =     0.012708;
  row.a[1] =    0.0037244;
  row.a[2] =   -8.101e-05;
  row.a[3] =   6.8499e-07;
  row.a[4] =  -2.8422e-09;
  row.a[5] =   4.6701e-12;
  tableSet->AddAt(&row);
  memset(&row,0,tableSet->GetRowSize());
  row.idx   = 2;
  row.nrows = nrows;
  row.min =  10.0;
  row.max = 220.0;
  row.npar =            6;// pp500_2022
  row.a[0] =   -0.0009878;
  row.a[1] =    0.0034222;
  row.a[2] =  -4.3152e-05;
  row.a[3] =   2.0117e-07;
  row.a[4] =  -6.6083e-10;
  row.a[5] =   1.3387e-12;
  tableSet->AddAt(&row);
  return (TDataSet *)tableSet;
}
