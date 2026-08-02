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
  row.npar =            7;// Z3NCGG9p8GeV_fixedTarget_2026b
  row.a[0] =      0.74284;
  row.a[1] =    -0.016964;
  row.a[2] =   0.00022432;
  row.a[3] =   -2.518e-06;
  row.a[4] =   1.8457e-08;
  row.a[5] =  -7.1076e-11;
  row.a[6] =   1.0798e-13;
  tableSet->AddAt(&row);
  memset(&row,0,tableSet->GetRowSize());
  row.idx   = 2;
  row.nrows = nrows;
  row.min =  18.0;
  row.max = 202.0;
  row.type =          300;// Use correction in the range
  row.npar =            5;// Z3NCGG9p8GeV_fixedTarget_2026b
  row.a[0] =       1.0536;
  row.a[1] =   -0.0014663;
  row.a[2] =  -0.00017682;
  row.a[3] =   1.3879e-06;
  row.a[4] =   -3.097e-09;
  tableSet->AddAt(&row);
  memset(&row,0,tableSet->GetRowSize());
  row.idx   = 3;
  row.nrows = nrows;
  row.min =  18.0;
  row.max = 202.0;
  row.type =          300;// Use correction in the range
  row.npar =            3;// Z3NCGG9p8GeV_fixedTarget_2026b
  row.a[0] =      0.17357;
  row.a[1] =   -0.0020246;
  row.a[2] =    5.621e-06;
  tableSet->AddAt(&row);
  memset(&row,0,tableSet->GetRowSize());
  row.idx   = 4;
  row.nrows = nrows;
  row.min =  18.0;
  row.max = 202.0;
  row.type =          300;// Use correction in the range
  row.npar =            3;// Z3NCGG9p8GeV_fixedTarget_2026b
  row.a[0] =       0.2764;
  row.a[1] =   0.00020827;
  row.a[2] =  -7.8266e-06;
  tableSet->AddAt(&row);
  return (TDataSet *)tableSet;
}
