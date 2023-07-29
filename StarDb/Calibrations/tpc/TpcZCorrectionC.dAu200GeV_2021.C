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
  row.npar =            5;// dAu200_2021
  row.a[0] =     0.094421;
  row.a[1] =   -0.0022779;
  row.a[2] =   1.8994e-05;
  row.a[3] =  -6.4118e-08;
  row.a[4] =    6.521e-11;
  tableSet->AddAt(&row);
  memset(&row,0,tableSet->GetRowSize());
  row.idx   = 2;
  row.nrows = nrows;
  row.min =  16.5;
  row.max = 208.0;
  row.npar =            5;// dAu200_2021
  row.a[0] =    -0.056595;
  row.a[1] =    0.0064668;
  row.a[2] =  -0.00010184;
  row.a[3] =    5.582e-07;
  row.a[4] =  -1.0425e-09;
  tableSet->AddAt(&row);
  memset(&row,0,tableSet->GetRowSize());
  row.idx   = 3;
  row.nrows = nrows;
  row.min =  22.5;
  row.max = 208.0;
  row.npar =            5;// dAu200_2021
  row.a[0] =      0.11578;
  row.a[1] =   -0.0025521;
  row.a[2] =   1.8408e-05;
  row.a[3] =  -5.0755e-08;
  row.a[4] =   3.4243e-11;
  tableSet->AddAt(&row);
  memset(&row,0,tableSet->GetRowSize());
  row.idx   = 4;
  row.nrows = nrows;
  row.min =  16.5;
  row.max = 208.0;
  row.npar =            5;// dAu200_2021
  row.a[0] =    -0.072213;
  row.a[1] =    0.0073237;
  row.a[2] =  -0.00011309;
  row.a[3] =   5.9967e-07;
  row.a[4] =  -1.0605e-09;
  tableSet->AddAt(&row);
  return (TDataSet *)tableSet;
}
