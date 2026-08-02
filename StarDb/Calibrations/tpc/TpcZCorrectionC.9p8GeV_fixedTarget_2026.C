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
  row.type =          300;// Use correction in the range
  row.npar =            7;// Z3NCGG9p8GeV_fixedTarget_2026
  row.a[0] =      0.61111;
  row.a[1] =    -0.028218;
  row.a[2] =    0.0007299;
  row.a[3] =  -1.0399e-05;
  row.a[4] =   7.7068e-08;
  row.a[5] =  -2.8247e-10;
  row.a[6] =   4.0555e-13;
  tableSet->AddAt(&row);
  memset(&row,0,tableSet->GetRowSize());
  row.idx   = 2;
  row.nrows = nrows;
  row.min =  18.0;
  row.max = 202.0;
  row.type =          300;// Use correction in the range
  row.npar =            5;// Z3NCGG9p8GeV_fixedTarget_2026
  row.a[0] =       1.4732;
  row.a[1] =   -0.0092141;
  row.a[2] =   -8.931e-05;
  row.a[3] =   7.8937e-07;
  row.a[4] =  -1.7209e-09;
  tableSet->AddAt(&row);
  memset(&row,0,tableSet->GetRowSize());
  row.idx   = 3;
  row.nrows = nrows;
  row.min =  18.0;
  row.max = 202.0;
  row.type =          300;// Use correction in the range
  row.npar =            7;// Z3NCGG9p8GeV_fixedTarget_2026
  row.a[0] =     -0.13023;
  row.a[1] =     0.011845;
  row.a[2] =  -0.00035277;
  row.a[3] =   4.7654e-06;
  row.a[4] =  -3.3571e-08;
  row.a[5] =   1.1897e-10;
  row.a[6] =  -1.6708e-13;
  tableSet->AddAt(&row);
  memset(&row,0,tableSet->GetRowSize());
  row.idx   = 4;
  row.nrows = nrows;
  row.min =  18.0;
  row.max = 202.0;
  row.type =          300;// Use correction in the range
  row.npar =            3;// Z3NCGG9p8GeV_fixedTarget_2026
  row.a[0] =      0.34522;
  row.a[1] =   -0.0031712;
  row.a[2] =    5.608e-06;
  tableSet->AddAt(&row);
  return (TDataSet *)tableSet;
}
