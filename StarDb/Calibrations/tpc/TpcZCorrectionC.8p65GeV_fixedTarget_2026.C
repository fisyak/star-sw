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
  row.npar =            7;// Z3NCGG8p65GeV_fixedTarget_2026
  row.a[0] =      0.94848;
  row.a[1] =    -0.047522;
  row.a[2] =    0.0011878;
  row.a[3] =  -1.5959e-05;
  row.a[4] =   1.1352e-07;
  row.a[5] =  -4.0481e-10;
  row.a[6] =   5.7015e-13;
  tableSet->AddAt(&row);
  memset(&row,0,tableSet->GetRowSize());
  row.idx   = 2;
  row.nrows = nrows;
  row.min =  18.0;
  row.max = 202.0;
  row.type =          300;// Use correction in the range
  row.npar =            4;// Z3NCGG8p65GeV_fixedTarget_2026
  row.a[0] =      0.86787;
  row.a[1] =    -0.017883;
  row.a[2] =    0.0001079;
  row.a[3] =  -2.3465e-07;
  tableSet->AddAt(&row);
  memset(&row,0,tableSet->GetRowSize());
  row.idx   = 3;
  row.nrows = nrows;
  row.min =  18.0;
  row.max = 202.0;
  row.type =          300;// Use correction in the range
  row.npar =            7;// Z3NCGG8p65GeV_fixedTarget_2026
  row.a[0] =    -0.061276;
  row.a[1] =     0.010208;
  row.a[2] =   -0.0003181;
  row.a[3] =   4.5001e-06;
  row.a[4] =  -3.2916e-08;
  row.a[5] =    1.201e-10;
  row.a[6] =  -1.7261e-13;
  tableSet->AddAt(&row);
  memset(&row,0,tableSet->GetRowSize());
  row.idx   = 4;
  row.nrows = nrows;
  row.min =  18.0;
  row.max = 202.0;
  row.type =          300;// Use correction in the range
  row.npar =            3;// Z3NCGG8p65GeV_fixedTarget_2026
  row.a[0] =      0.12732;
  row.a[1] =   0.00060388;
  row.a[2] =  -6.6819e-06;
  tableSet->AddAt(&row);
  return (TDataSet *)tableSet;
}
