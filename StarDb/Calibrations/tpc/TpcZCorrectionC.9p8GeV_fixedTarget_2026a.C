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
  row.npar =            7;// RunXXVI53/9p8GeV_fixedTarget_2026a
  row.a[0] =      -1.0078;
  row.a[1] =     0.097301;
  row.a[2] =   -0.0023866;
  row.a[3] =   2.8562e-05;
  row.a[4] =  -1.8393e-07;
  row.a[5] =   6.1113e-10;
  row.a[6] =  -8.2214e-13;
  tableSet->AddAt(&row);
  memset(&row,0,tableSet->GetRowSize());
  row.idx   = 2;
  row.nrows = nrows;
  row.min =  13.0;
  row.max = 203.0;
  row.type =          300;// Use correction in the range
  row.npar =            7;// RunXXVI53/9p8GeV_fixedTarget_2026a
  row.a[0] =     -0.66666;
  row.a[1] =      0.10077;
  row.a[2] =   -0.0024272;
  row.a[3] =   2.8429e-05;
  row.a[4] =   -1.831e-07;
  row.a[5] =    6.173e-10;
  row.a[6] =  -8.4768e-13;
  tableSet->AddAt(&row);
  memset(&row,0,tableSet->GetRowSize());
  row.idx   = 3;
  row.nrows = nrows;
  row.min =  13.0;
  row.max = 208.0;
  row.type =          300;// Use correction in the range
  row.npar =            7;// RunXXVI53/9p8GeV_fixedTarget_2026a
  row.a[0] =       0.2837;
  row.a[1] =    0.0027996;
  row.a[2] =  -0.00011017;
  row.a[3] =   1.6062e-06;
  row.a[4] =  -1.1885e-08;
  row.a[5] =   4.4167e-11;
  row.a[6] =  -6.5276e-14;
  tableSet->AddAt(&row);
  memset(&row,0,tableSet->GetRowSize());
  row.idx   = 4;
  row.nrows = nrows;
  row.min =  13.0;
  row.max = 203.0;
  row.type =          300;// Use correction in the range
  row.npar =            7;// RunXXVI53/9p8GeV_fixedTarget_2026a
  row.a[0] =     -0.22161;
  row.a[1] =     0.045499;
  row.a[2] =   -0.0012463;
  row.a[3] =   1.6691e-05;
  row.a[4] =  -1.1849e-07;
  row.a[5] =   4.2548e-10;
  row.a[6] =   -6.075e-13;
  tableSet->AddAt(&row);
  return (TDataSet *)tableSet;
}
