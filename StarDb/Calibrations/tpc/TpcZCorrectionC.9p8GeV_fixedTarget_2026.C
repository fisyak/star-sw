TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcCorrection")) return 0;
  Int_t nrows = 4;
  St_tpcCorrection *tableSet = new St_tpcCorrection("TpcZCorrectionC",nrows);
  tpcCorrection_st row;
  memset(&row,0,tableSet->GetRowSize());
  row.idx   = 1;
  row.nrows = nrows;
  row.min =  13.0;
  row.max = 208.0;
  row.type =          300;// Use correction in the range
  row.npar =            7;// RunXXVI53/9p8GeV_fixedTarget_2026
  row.a[0] =      0.79315;
  row.a[1] =     -0.03577;
  row.a[2] =   0.00079959;
  row.a[3] =   -9.882e-06;
  row.a[4] =   6.4846e-08;
  row.a[5] =  -2.1239e-10;
  row.a[6] =   2.7272e-13;
  tableSet->AddAt(&row);
  memset(&row,0,tableSet->GetRowSize());
  row.idx   = 2;
  row.nrows = nrows;
  row.min =  13.0;
  row.max = 203.0;
  row.type =          300;// Use correction in the range
  row.npar =            7;// RunXXVI53/9p8GeV_fixedTarget_2026
  row.a[0] =      0.73243;
  row.a[1] =     0.040412;
  row.a[2] =   -0.0013028;
  row.a[3] =   1.5321e-05;
  row.a[4] =  -9.3822e-08;
  row.a[5] =   2.9743e-10;
  row.a[6] =   -3.862e-13;
  tableSet->AddAt(&row);
  memset(&row,0,tableSet->GetRowSize());
  row.idx   = 3;
  row.nrows = nrows;
  row.min =  13.0;
  row.max = 208.0;
  row.type =          300;// Use correction in the range
  row.npar =            7;// RunXXVI53/9p8GeV_fixedTarget_2026
  row.a[0] =    -0.089975;
  row.a[1] =    0.0094246;
  row.a[2] =  -0.00031515;
  row.a[3] =   4.6334e-06;
  row.a[4] =  -3.5154e-08;
  row.a[5] =   1.3319e-10;
  row.a[6] =  -1.9888e-13;
  tableSet->AddAt(&row);
  memset(&row,0,tableSet->GetRowSize());
  row.idx   = 4;
  row.nrows = nrows;
  row.min =  13.0;
  row.max = 203.0;
  row.type =          300;// Use correction in the range
  row.npar =            7;// RunXXVI53/9p8GeV_fixedTarget_2026
  row.a[0] =     -0.24521;
  row.a[1] =     0.042259;
  row.a[2] =   -0.0012749;
  row.a[3] =   1.7837e-05;
  row.a[4] =  -1.3059e-07;
  row.a[5] =   4.7959e-10;
  row.a[6] =  -6.9475e-13;
  tableSet->AddAt(&row);
  return (TDataSet *)tableSet;
}
