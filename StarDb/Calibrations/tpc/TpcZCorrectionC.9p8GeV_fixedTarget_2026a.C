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
  row.npar =            5;// 9p8GeV_fixedTarget_2026a
  row.a[0] =      0.27319;
  row.a[1] =    0.0051373;
  row.a[2] =  -0.00013078;
  row.a[3] =   8.2407e-07;
  row.a[4] =  -1.6897e-09;
  tableSet->AddAt(&row);
  memset(&row,0,tableSet->GetRowSize());
  row.idx   = 2;
  row.nrows = nrows;
  row.min =  18.0;
  row.max = 202.0;
  row.npar =            3;// 9p8GeV_fixedTarget_2026a
  row.a[0] =       1.1146;
  row.a[1] =   -0.0097198;
  row.a[2] =   1.9432e-05;
  tableSet->AddAt(&row);
  memset(&row,0,tableSet->GetRowSize());
  row.idx   = 3;
  row.nrows = nrows;
  row.min =  18.0;
  row.max = 202.0;
  row.npar =            2;// 9p8GeV_fixedTarget_2026a
  row.a[0] =      0.13081;
  row.a[1] =   -0.0004321;
  tableSet->AddAt(&row);
  memset(&row,0,tableSet->GetRowSize());
  row.idx   = 4;
  row.nrows = nrows;
  row.min =  18.0;
  row.max = 202.0;
  row.npar =            5;// 9p8GeV_fixedTarget_2026a
  row.a[0] =      0.14796;
  row.a[1] =    0.0015904;
  row.a[2] =  -2.1823e-05;
  row.a[3] =   5.5426e-08;
  row.a[4] =   4.8141e-14;
  tableSet->AddAt(&row);
  return (TDataSet *)tableSet;
}
