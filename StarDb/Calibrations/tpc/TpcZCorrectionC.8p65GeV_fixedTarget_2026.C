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
  row.npar =            7;// RunXXVI53/8p65GeV_fixedTarget_2026
  row.a[0] =      0.85337;
  row.a[1] =    -0.034724;
  row.a[2] =    0.0007136;
  row.a[3] =  -8.2696e-06;
  row.a[4] =    5.135e-08;
  row.a[5] =  -1.5893e-10;
  row.a[6] =   1.9123e-13;
  tableSet->AddAt(&row);
  memset(&row,0,tableSet->GetRowSize());
  row.idx   = 2;
  row.nrows = nrows;
  row.min =  13.0;
  row.max = 203.0;
  row.type =          300;// Use correction in the range
  row.npar =            4;// RunXXVI53/8p65GeV_fixedTarget_2026
  row.a[0] =      0.83823;
  row.a[1] =    -0.017568;
  row.a[2] =   0.00010504;
  row.a[3] =  -2.2665e-07;
  tableSet->AddAt(&row);
  memset(&row,0,tableSet->GetRowSize());
  row.idx   = 3;
  row.nrows = nrows;
  row.min =  13.0;
  row.max = 208.0;
  row.type =          300;// Use correction in the range
  row.npar =            7;// RunXXVI53/8p65GeV_fixedTarget_2026
  row.a[0] =    -0.030402;
  row.a[1] =    0.0096242;
  row.a[2] =  -0.00033902;
  row.a[3] =    5.209e-06;
  row.a[4] =  -4.0637e-08;
  row.a[5] =   1.5646e-10;
  row.a[6] =  -2.3572e-13;
  tableSet->AddAt(&row);
  memset(&row,0,tableSet->GetRowSize());
  row.idx   = 4;
  row.nrows = nrows;
  row.min =  13.0;
  row.max = 203.0;
  row.type =          300;// Use correction in the range
  row.npar =            7;// RunXXVI53/8p65GeV_fixedTarget_2026
  row.a[0] =     -0.66933;
  row.a[1] =     0.065554;
  row.a[2] =   -0.0018922;
  row.a[3] =   2.6333e-05;
  row.a[4] =  -1.9047e-07;
  row.a[5] =   6.8717e-10;
  row.a[6] =   -9.775e-13;
  tableSet->AddAt(&row);
  return (TDataSet *)tableSet;
}
