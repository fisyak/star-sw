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
  row.npar =            7;// RunXXVI59/9p8GeV_fixedTarget_2026b
  row.a[0] =       0.7797;
  row.a[1] =    -0.012195;
  row.a[2] =  -3.1189e-05;
  row.a[3] =   2.2357e-06;
  row.a[4] =  -2.3356e-08;
  row.a[5] =   1.0393e-10;
  row.a[6] =   -1.726e-13;
  tableSet->AddAt(&row);
  memset(&row,0,tableSet->GetRowSize());
  row.idx   = 2;
  row.nrows = nrows;
  row.min =  13.0;
  row.max = 203.0;
  row.type =          300;// Use correction in the range
  row.npar =            7;// RunXXVI59/9p8GeV_fixedTarget_2026b
  row.a[0] =      0.21691;
  row.a[1] =     0.059932;
  row.a[2] =   -0.0017758;
  row.a[3] =   2.1328e-05;
  row.a[4] =  -1.3202e-07;
  row.a[5] =   4.1637e-10;
  row.a[6] =  -5.3081e-13;
  tableSet->AddAt(&row);
  memset(&row,0,tableSet->GetRowSize());
  row.idx   = 3;
  row.nrows = nrows;
  row.min =  13.0;
  row.max = 208.0;
  row.type =          300;// Use correction in the range
  row.npar =            7;// RunXXVI59/9p8GeV_fixedTarget_2026b
  row.a[0] =     0.075132;
  row.a[1] =    0.0013886;
  row.a[2] =  -7.8222e-05;
  row.a[3] =   1.5262e-06;
  row.a[4] =  -1.4414e-08;
  row.a[5] =   6.4401e-11;
  row.a[6] =  -1.0913e-13;
  tableSet->AddAt(&row);
  memset(&row,0,tableSet->GetRowSize());
  row.idx   = 4;
  row.nrows = nrows;
  row.min =  13.0;
  row.max = 203.0;
  row.type =          300;// Use correction in the range
  row.npar =            7;// RunXXVI59/9p8GeV_fixedTarget_2026b
  row.a[0] =    -0.063971;
  row.a[1] =     0.034327;
  row.a[2] =  -0.00097209;
  row.a[3] =   1.3182e-05;
  row.a[4] =   -9.422e-08;
  row.a[5] =    3.383e-10;
  row.a[6] =  -4.8079e-13;
  tableSet->AddAt(&row);
  return (TDataSet *)tableSet;
}
