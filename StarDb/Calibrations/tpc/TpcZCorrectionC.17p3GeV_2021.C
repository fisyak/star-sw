TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcCorrection")) return 0;
  Int_t nrows = 4;
  St_tpcCorrection *tableSet = new St_tpcCorrection("TpcZCorrectionC",nrows);
  tpcCorrection_st row;
  memset(&row,0,tableSet->GetRowSize());
  row.idx   = 1;
  row.nrows = nrows;
  row.min =  22.5;
  row.max = 208.0;
  row.npar =            5;// 17p3GeV_2021
  row.a[0] =     0.041647;
  row.a[1] =  -0.00014345;
  row.a[2] =  -4.3543e-06;
  row.a[3] =   3.1716e-08;
  row.a[4] =  -7.1856e-11;
  tableSet->AddAt(&row);
  memset(&row,0,tableSet->GetRowSize());
  row.idx   = 2;
  row.nrows = nrows;
  row.min =  16.5;
  row.max = 208.0;
  row.npar =            5;// 17p3GeV_2021
  row.a[0] =     0.063063;
  row.a[1] =    0.0033255;
  row.a[2] =  -5.4382e-05;
  row.a[3] =   2.2779e-07;
  row.a[4] =  -2.8381e-10;
  tableSet->AddAt(&row);
  memset(&row,0,tableSet->GetRowSize());
  row.idx   = 3;
  row.nrows = nrows;
  row.min =  22.5;
  row.max = 208.0;
  row.npar =            5;// 17p3GeV_2021
  row.a[0] =     0.039281;
  row.a[1] =  -8.6566e-05;
  row.a[2] =  -5.2668e-06;
  row.a[3] =   3.8126e-08;
  row.a[4] =  -8.4814e-11;
  tableSet->AddAt(&row);
  memset(&row,0,tableSet->GetRowSize());
  row.idx   = 4;
  row.nrows = nrows;
  row.min =  16.5;
  row.max = 208.0;
  row.npar =            5;// 17p3GeV_2021
  row.a[0] =     0.036909;
  row.a[1] =    0.0048527;
  row.a[2] =  -7.5165e-05;
  row.a[3] =   3.3031e-07;
  row.a[4] =  -4.5114e-10;
  tableSet->AddAt(&row);
  return (TDataSet *)tableSet;
}
