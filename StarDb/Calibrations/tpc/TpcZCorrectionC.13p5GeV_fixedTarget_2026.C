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
  row.npar =            7;// 13p5GeV_fixedTarget_2026
  row.a[0] =     -0.13067;
  row.a[1] =      0.01999;
  row.a[2] =  -0.00043744;
  row.a[3] =   3.6273e-06;
  row.a[4] =   -1.237e-08;
  row.a[5] =   7.3747e-12;
  row.a[6] =   2.9846e-14;
  tableSet->AddAt(&row);
  memset(&row,0,tableSet->GetRowSize());
  row.idx   = 2;
  row.nrows = nrows;
  row.min =  18.0;
  row.max = 202.0;
  row.npar =            6;// 13p5GeV_fixedTarget_2026
  row.a[0] =     0.019077;
  row.a[1] =     0.025089;
  row.a[2] =  -0.00069779;
  row.a[3] =    6.985e-06;
  row.a[4] =  -3.1053e-08;
  row.a[5] =   5.1443e-11;
  tableSet->AddAt(&row);
  memset(&row,0,tableSet->GetRowSize());
  row.idx   = 3;
  row.nrows = nrows;
  row.min =  18.0;
  row.max = 202.0;
  row.npar =            3;// 13p5GeV_fixedTarget_2026
  row.a[0] =     0.080328;
  row.a[1] =  -0.00099929;
  row.a[2] =   1.8098e-06;
  tableSet->AddAt(&row);
  memset(&row,0,tableSet->GetRowSize());
  row.idx   = 4;
  row.nrows = nrows;
  row.min =  18.0;
  row.max = 202.0;
  row.npar =            3;// 13p5GeV_fixedTarget_2026
  row.a[0] =     0.038464;
  row.a[1] =   0.00061467;
  row.a[2] =  -6.8899e-06;
  tableSet->AddAt(&row);
  return (TDataSet *)tableSet;
}
