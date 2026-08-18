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
  row.npar =            7;// RunXXVI53/13p5GeV_fixedTarget_2026
  row.a[0] =      0.74835;
  row.a[1] =     -0.03464;
  row.a[2] =   0.00081784;
  row.a[3] =  -1.0488e-05;
  row.a[4] =   7.0444e-08;
  row.a[5] =  -2.3444e-10;
  row.a[6] =   3.0482e-13;
  tableSet->AddAt(&row);
  memset(&row,0,tableSet->GetRowSize());
  row.idx   = 2;
  row.nrows = nrows;
  row.min =  13.0;
  row.max = 203.0;
  row.type =          300;// Use correction in the range
  row.npar =            4;// RunXXVI53/13p5GeV_fixedTarget_2026
  row.a[0] =      0.84291;
  row.a[1] =    -0.018074;
  row.a[2] =   0.00010979;
  row.a[3] =  -2.4143e-07;
  tableSet->AddAt(&row);
  memset(&row,0,tableSet->GetRowSize());
  row.idx   = 3;
  row.nrows = nrows;
  row.min =  13.0;
  row.max = 208.0;
  row.type =          300;// Use correction in the range
  row.npar =            7;// RunXXVI53/13p5GeV_fixedTarget_2026
  row.a[0] =    -0.023007;
  row.a[1] =    0.0081642;
  row.a[2] =  -0.00028644;
  row.a[3] =   4.3733e-06;
  row.a[4] =  -3.4193e-08;
  row.a[5] =   1.3257e-10;
  row.a[6] =  -2.0141e-13;
  tableSet->AddAt(&row);
  memset(&row,0,tableSet->GetRowSize());
  row.idx   = 4;
  row.nrows = nrows;
  row.min =  13.0;
  row.max = 203.0;
  row.type =          300;// Use correction in the range
  row.npar =            7;// RunXXVI53/13p5GeV_fixedTarget_2026
  row.a[0] =     -0.44636;
  row.a[1] =     0.046634;
  row.a[2] =   -0.0013651;
  row.a[3] =   1.9227e-05;
  row.a[4] =  -1.4047e-07;
  row.a[5] =   5.1026e-10;
  row.a[6] =  -7.2895e-13;
  tableSet->AddAt(&row);
  return (TDataSet *)tableSet;
}
