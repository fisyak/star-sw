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
  row.npar =            7;// 8p65GeV_fixedTarget_2026
  row.a[0] =     -0.54004;
  row.a[1] =     0.043191;
  row.a[2] =  -0.00098893;
  row.a[3] =   1.0505e-05;
  row.a[4] =   -5.923e-08;
  row.a[5] =    1.724e-10;
  row.a[6] =  -2.0491e-13;
  tableSet->AddAt(&row);
  memset(&row,0,tableSet->GetRowSize());
  row.idx   = 2;
  row.nrows = nrows;
  row.min =  18.0;
  row.max = 202.0;
  row.npar =            5;// 8p65GeV_fixedTarget_2026
  row.a[0] =       0.3744;
  row.a[1] =  -0.00061599;
  row.a[2] =  -0.00010176;
  row.a[3] =   8.7123e-07;
  row.a[4] =  -2.1265e-09;
  tableSet->AddAt(&row);
  memset(&row,0,tableSet->GetRowSize());
  row.idx   = 3;
  row.nrows = nrows;
  row.min =  18.0;
  row.max = 202.0;
  row.npar =            3;// 8p65GeV_fixedTarget_2026
  row.a[0] =      0.07107;
  row.a[1] =   -0.0008317;
  row.a[2] =   1.4374e-06;
  tableSet->AddAt(&row);
  memset(&row,0,tableSet->GetRowSize());
  row.idx   = 4;
  row.nrows = nrows;
  row.min =  18.0;
  row.max = 202.0;
  row.npar =            3;// 8p65GeV_fixedTarget_2026
  row.a[0] =     0.020926;
  row.a[1] =   0.00083296;
  row.a[2] =  -7.1723e-06;
  tableSet->AddAt(&row);
  return (TDataSet *)tableSet;
}
