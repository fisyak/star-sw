TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_spline3")) return 0;
  Int_t nrows = 1;
  St_spline3 *tableSet = new St_spline3("ElectonsDEV_dEdx",nrows);
  spline3_st row;
  memset(&row,0,tableSet->GetRowSize());
  row.nknots = 20;
  Double_t X[20] = {2.0975,2.12,2.15,2.2,2.25,2.3,2.35,2.4,2.45,2.5,2.55,2.6,2.7,2.8,2.9,3,3.2,3.3,3.4,3.4625};
  Double_t Y[20] = {-0.102073,-0.102612,-0.0926368,-0.0725882,-0.0459238,-0.0204059,0.00579816,0.0257995,0.0389493,0.0392476,0.039698,0.0453549,0.0590225,0.0735965,0.0811198,0.0852763,0.0983159,0.102621,0.105468,0.108089};
  for (Int_t i = 0; i < 20; i++) {row.Xknots[i] = X[i]; row.Yknots[i] = Y[i];}
  tableSet->AddAt(&row);
  return (TDataSet *)tableSet;
}
