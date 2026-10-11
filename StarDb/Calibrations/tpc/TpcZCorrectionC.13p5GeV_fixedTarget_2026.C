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
  row.npar =            7;// RunXXVI59/13p5GeV_fixedTarget_2026
  row.a[0] =      0.76183;
  row.a[1] =    -0.025491;
  row.a[2] =   0.00044537;
  row.a[3] =  -4.7732e-06;
  row.a[4] =   2.7859e-08;
  row.a[5] =  -8.0048e-11;
  row.a[6] =   8.6687e-14;
  tableSet->AddAt(&row);
  memset(&row,0,tableSet->GetRowSize());
  row.idx   = 2;
  row.nrows = nrows;
  row.min =  13.0;
  row.max = 203.0;
  row.type =          300;// Use correction in the range
  row.npar =            4;// RunXXVI59/13p5GeV_fixedTarget_2026
  row.a[0] =      0.79237;
  row.a[1] =    -0.017396;
  row.a[2] =    0.0001034;
  row.a[3] =  -2.2299e-07;
  tableSet->AddAt(&row);
  memset(&row,0,tableSet->GetRowSize());
  row.idx   = 3;
  row.nrows = nrows;
  row.min =  13.0;
  row.max = 208.0;
  row.type =          300;// Use correction in the range
  row.npar =            7;// RunXXVI59/13p5GeV_fixedTarget_2026
  row.a[0] =     -0.01431;
  row.a[1] =     0.004103;
  row.a[2] =    -0.000145;
  row.a[3] =   2.3687e-06;
  row.a[4] =  -2.0039e-08;
  row.a[5] =   8.3295e-11;
  row.a[6] =  -1.3422e-13;
  tableSet->AddAt(&row);
  memset(&row,0,tableSet->GetRowSize());
  row.idx   = 4;
  row.nrows = nrows;
  row.min =  13.0;
  row.max = 203.0;
  row.type =          300;// Use correction in the range
  row.npar =            7;// RunXXVI59/13p5GeV_fixedTarget_2026
  row.a[0] =     -0.27864;
  row.a[1] =     0.034041;
  row.a[2] =  -0.00097468;
  row.a[3] =   1.3459e-05;
  row.a[4] =  -9.6687e-08;
  row.a[5] =   3.4554e-10;
  row.a[6] =  -4.8594e-13;
  tableSet->AddAt(&row);
  return (TDataSet *)tableSet;
}
