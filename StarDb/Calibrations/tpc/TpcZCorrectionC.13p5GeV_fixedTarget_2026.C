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
  row.type =          300;// Use correction in the range
  row.npar =            7;// Z3NCGG13p5GeV_fixedTarget_2026
  row.a[0] =      0.96234;
  row.a[1] =    -0.048288;
  row.a[2] =    0.0011981;
  row.a[3] =  -1.5939e-05;
  row.a[4] =    1.123e-07;
  row.a[5] =  -3.9715e-10;
  row.a[6] =   5.5551e-13;
  tableSet->AddAt(&row);
  memset(&row,0,tableSet->GetRowSize());
  row.idx   = 2;
  row.nrows = nrows;
  row.min =  18.0;
  row.max = 202.0;
  row.type =          300;// Use correction in the range
  row.npar =            4;// Z3NCGG13p5GeV_fixedTarget_2026
  row.a[0] =      0.86696;
  row.a[1] =    -0.017926;
  row.a[2] =   0.00010814;
  row.a[3] =  -2.3509e-07;
  tableSet->AddAt(&row);
  memset(&row,0,tableSet->GetRowSize());
  row.idx   = 3;
  row.nrows = nrows;
  row.min =  18.0;
  row.max = 202.0;
  row.type =          300;// Use correction in the range
  row.npar =            7;// Z3NCGG13p5GeV_fixedTarget_2026
  row.a[0] =    -0.068278;
  row.a[1] =     0.010808;
  row.a[2] =  -0.00033322;
  row.a[3] =   4.6551e-06;
  row.a[4] =  -3.3728e-08;
  row.a[5] =   1.2226e-10;
  row.a[6] =  -1.7485e-13;
  tableSet->AddAt(&row);
  memset(&row,0,tableSet->GetRowSize());
  row.idx   = 4;
  row.nrows = nrows;
  row.min =  18.0;
  row.max = 202.0;
  row.type =          300;// Use correction in the range
  row.npar =            3;// Z3NCGG13p5GeV_fixedTarget_2026
  row.a[0] =      0.12121;
  row.a[1] =    0.0005338;
  row.a[2] =  -6.7246e-06;
  tableSet->AddAt(&row);
  return (TDataSet *)tableSet;
}
