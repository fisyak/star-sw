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
  row.npar =            7;// RunXXVI53/9p8GeV_fixedTarget_2026b
  row.a[0] =      0.54728;
  row.a[1] =   -0.0021384;
  row.a[2] =  -0.00017202;
  row.a[3] =   2.6663e-06;
  row.a[4] =  -1.7748e-08;
  row.a[5] =   5.8407e-11;
  row.a[6] =  -7.8198e-14;
  tableSet->AddAt(&row);
  memset(&row,0,tableSet->GetRowSize());
  row.idx   = 2;
  row.nrows = nrows;
  row.min =  13.0;
  row.max = 203.0;
  row.type =          300;// Use correction in the range
  row.npar =            6;// RunXXVI53/9p8GeV_fixedTarget_2026b
  row.a[0] =      0.67836;
  row.a[1] =     0.022067;
  row.a[2] =  -0.00067664;
  row.a[3] =   6.2387e-06;
  row.a[4] =  -2.5075e-08;
  row.a[5] =   3.7642e-11;
  tableSet->AddAt(&row);
  memset(&row,0,tableSet->GetRowSize());
  row.idx   = 3;
  row.nrows = nrows;
  row.min =  13.0;
  row.max = 208.0;
  row.type =          300;// Use correction in the range
  row.npar =            7;// RunXXVI53/9p8GeV_fixedTarget_2026b
  row.a[0] =    -0.074023;
  row.a[1] =     0.020494;
  row.a[2] =  -0.00064888;
  row.a[3] =   8.9593e-06;
  row.a[4] =  -6.3492e-08;
  row.a[5] =   2.2538e-10;
  row.a[6] =  -3.1689e-13;
  tableSet->AddAt(&row);
  memset(&row,0,tableSet->GetRowSize());
  row.idx   = 4;
  row.nrows = nrows;
  row.min =  13.0;
  row.max = 203.0;
  row.type =          300;// Use correction in the range
  row.npar =            7;// RunXXVI53/9p8GeV_fixedTarget_2026b
  row.a[0] =    -0.071308;
  row.a[1] =     0.028461;
  row.a[2] =  -0.00074486;
  row.a[3] =   9.4344e-06;
  row.a[4] =  -6.3386e-08;
  row.a[5] =   2.1474e-10;
  row.a[6] =  -2.8948e-13;
  tableSet->AddAt(&row);
  return (TDataSet *)tableSet;
}
