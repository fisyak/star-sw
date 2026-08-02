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
  row.npar =            7;// Z3NCGG9p8GeV_fixedTarget_2026a
  row.a[0] =       1.4275;
  row.a[1] =    -0.069824;
  row.a[2] =    0.0019569;
  row.a[3] =  -2.8227e-05;
  row.a[4] =   2.1001e-07;
  row.a[5] =  -7.7161e-10;
  row.a[6] =     1.11e-12;
  tableSet->AddAt(&row);
  memset(&row,0,tableSet->GetRowSize());
  row.idx   = 2;
  row.nrows = nrows;
  row.min =  18.0;
  row.max = 202.0;
  row.type =          300;// Use correction in the range
  row.npar =            5;// Z3NCGG9p8GeV_fixedTarget_2026a
  row.a[0] =       0.8415;
  row.a[1] =     0.012789;
  row.a[2] =  -0.00032456;
  row.a[3] =   1.9336e-06;
  row.a[4] =  -3.6829e-09;
  tableSet->AddAt(&row);
  memset(&row,0,tableSet->GetRowSize());
  row.idx   = 3;
  row.nrows = nrows;
  row.min =  18.0;
  row.max = 202.0;
  row.type =          300;// Use correction in the range
  row.npar =            4;// Z3NCGG9p8GeV_fixedTarget_2026a
  row.a[0] =      0.22141;
  row.a[1] =   0.00050945;
  row.a[2] =  -1.6253e-05;
  row.a[3] =   5.6084e-08;
  tableSet->AddAt(&row);
  memset(&row,0,tableSet->GetRowSize());
  row.idx   = 4;
  row.nrows = nrows;
  row.min =  18.0;
  row.max = 202.0;
  row.type =          300;// Use correction in the range
  row.npar =            3;// Z3NCGG9p8GeV_fixedTarget_2026a
  row.a[0] =      0.32966;
  row.a[1] =  -0.00048193;
  row.a[2] =  -2.6547e-06;
  tableSet->AddAt(&row);
  return (TDataSet *)tableSet;
}
