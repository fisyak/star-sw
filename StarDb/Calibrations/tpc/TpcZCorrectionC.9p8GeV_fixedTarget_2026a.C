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
  row.npar =            7;// RunXXVI59/9p8GeV_fixedTarget_2026a
  row.a[0] =      0.69995;
  row.a[1] =      0.01036;
  row.a[2] =  -0.00041403;
  row.a[3] =   5.1315e-06;
  row.a[4] =  -3.3782e-08;
  row.a[5] =   1.2025e-10;
  row.a[6] =  -1.7989e-13;
  tableSet->AddAt(&row);
  memset(&row,0,tableSet->GetRowSize());
  row.idx   = 2;
  row.nrows = nrows;
  row.min =  13.0;
  row.max = 203.0;
  row.type =          300;// Use correction in the range
  row.npar =            5;// RunXXVI59/9p8GeV_fixedTarget_2026a
  row.a[0] =       1.4132;
  row.a[1] =    0.0030078;
  row.a[2] =  -0.00023003;
  row.a[3] =   1.5798e-06;
  row.a[4] =  -3.2745e-09;
  tableSet->AddAt(&row);
  memset(&row,0,tableSet->GetRowSize());
  row.idx   = 3;
  row.nrows = nrows;
  row.min =  13.0;
  row.max = 208.0;
  row.type =          300;// Use correction in the range
  row.npar =            7;// RunXXVI59/9p8GeV_fixedTarget_2026a
  row.a[0] =      0.20176;
  row.a[1] =     0.013661;
  row.a[2] =  -0.00044554;
  row.a[3] =   6.8838e-06;
  row.a[4] =  -5.4747e-08;
  row.a[5] =   2.1451e-10;
  row.a[6] =  -3.2734e-13;
  tableSet->AddAt(&row);
  memset(&row,0,tableSet->GetRowSize());
  row.idx   = 4;
  row.nrows = nrows;
  row.min =  13.0;
  row.max = 203.0;
  row.type =          300;// Use correction in the range
  row.npar =            7;// RunXXVI59/9p8GeV_fixedTarget_2026a
  row.a[0] =       -0.524;
  row.a[1] =     0.081797;
  row.a[2] =   -0.0023614;
  row.a[3] =   3.2996e-05;
  row.a[4] =  -2.4165e-07;
  row.a[5] =   8.8956e-10;
  row.a[6] =  -1.2978e-12;
  tableSet->AddAt(&row);
  return (TDataSet *)tableSet;
}
