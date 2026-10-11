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
  row.npar =            7;// RunXXVI59/8p65GeV_fixedTarget_2026
  row.a[0] =      0.76724;
  row.a[1] =    -0.021575;
  row.a[2] =   0.00027998;
  row.a[3] =  -2.0906e-06;
  row.a[4] =    6.983e-09;
  row.a[5] =  -1.4603e-12;
  row.a[6] =  -2.8438e-14;
  tableSet->AddAt(&row);
  memset(&row,0,tableSet->GetRowSize());
  row.idx   = 2;
  row.nrows = nrows;
  row.min =  13.0;
  row.max = 203.0;
  row.type =          300;// Use correction in the range
  row.npar =            6;// RunXXVI59/8p65GeV_fixedTarget_2026
  row.a[0] =      0.55296;
  row.a[1] =    -0.001939;
  row.a[2] =  -0.00023079;
  row.a[3] =   3.0916e-06;
  row.a[4] =  -1.5303e-08;
  row.a[5] =   2.6615e-11;
  tableSet->AddAt(&row);
  memset(&row,0,tableSet->GetRowSize());
  row.idx   = 3;
  row.nrows = nrows;
  row.min =  13.0;
  row.max = 208.0;
  row.type =          300;// Use correction in the range
  row.npar =            7;// RunXXVI59/8p65GeV_fixedTarget_2026
  row.a[0] =    -0.004956;
  row.a[1] =    0.0042429;
  row.a[2] =  -0.00016392;
  row.a[3] =   2.8415e-06;
  row.a[4] =  -2.4792e-08;
  row.a[5] =    1.047e-10;
  row.a[6] =  -1.7016e-13;
  tableSet->AddAt(&row);
  memset(&row,0,tableSet->GetRowSize());
  row.idx   = 4;
  row.nrows = nrows;
  row.min =  13.0;
  row.max = 203.0;
  row.type =          300;// Use correction in the range
  row.npar =            7;// RunXXVI59/8p65GeV_fixedTarget_2026
  row.a[0] =     -0.52893;
  row.a[1] =     0.055181;
  row.a[2] =   -0.0015726;
  row.a[3] =   2.1651e-05;
  row.a[4] =   -1.552e-07;
  row.a[5] =   5.5537e-10;
  row.a[6] =  -7.8426e-13;
  tableSet->AddAt(&row);
  return (TDataSet *)tableSet;
}
