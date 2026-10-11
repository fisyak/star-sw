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
  row.npar =            7;// RunXXVI59/9p8GeV_fixedTarget_2026
  row.a[0] =      0.59441;
  row.a[1] =    -0.017762;
  row.a[2] =   0.00029104;
  row.a[3] =  -3.1981e-06;
  row.a[4] =     1.91e-08;
  row.a[5] =  -5.4711e-11;
  row.a[6] =    5.662e-14;
  tableSet->AddAt(&row);
  memset(&row,0,tableSet->GetRowSize());
  row.idx   = 2;
  row.nrows = nrows;
  row.min =  13.0;
  row.max = 203.0;
  row.type =          300;// Use correction in the range
  row.npar =            7;// RunXXVI59/9p8GeV_fixedTarget_2026
  row.a[0] =      0.81259;
  row.a[1] =      0.03272;
  row.a[2] =   -0.0010905;
  row.a[3] =   1.2572e-05;
  row.a[4] =   -7.504e-08;
  row.a[5] =    2.311e-10;
  row.a[6] =  -2.9047e-13;
  tableSet->AddAt(&row);
  memset(&row,0,tableSet->GetRowSize());
  row.idx   = 3;
  row.nrows = nrows;
  row.min =  13.0;
  row.max = 208.0;
  row.type =          300;// Use correction in the range
  row.npar =            7;// RunXXVI59/9p8GeV_fixedTarget_2026
  row.a[0] =     -0.05584;
  row.a[1] =    0.0035496;
  row.a[2] =   -0.0001385;
  row.a[3] =   2.3509e-06;
  row.a[4] =  -2.0248e-08;
  row.a[5] =   8.4889e-11;
  row.a[6] =  -1.3741e-13;
  tableSet->AddAt(&row);
  memset(&row,0,tableSet->GetRowSize());
  row.idx   = 4;
  row.nrows = nrows;
  row.min =  13.0;
  row.max = 203.0;
  row.type =          300;// Use correction in the range
  row.npar =            7;// RunXXVI59/9p8GeV_fixedTarget_2026
  row.a[0] =     -0.21179;
  row.a[1] =     0.040119;
  row.a[2] =   -0.0011964;
  row.a[3] =   1.6493e-05;
  row.a[4] =   -1.193e-07;
  row.a[5] =   4.3402e-10;
  row.a[6] =  -6.2396e-13;
  tableSet->AddAt(&row);
  return (TDataSet *)tableSet;
}
