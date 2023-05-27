TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_spline3")) return 0;
  Int_t nrows = 1;
  St_spline3 *tableSet = new St_spline3("PionDEV_dEdx",nrows);
  spline3_st row;
  memset(&row,0,tableSet->GetRowSize());
  row.nknots = 17;
  Double_t X[17] = {-0.2625,-0.2425,-0.2,-0.15,-0.1,0.05,0.15,0.3,0.4,0.5,0.6,0.7,0.8,1,1.2,1.4,1.5225};
  Double_t Y[17] = {0.0246311,0.0643732,0.0539716,0.0138,-0.00204332,-0.00874623,-0.0121278,-0.00118923,0.00782006,0.014064,0.0177632,0.0198492,0.0217606,0.0252433,0.0322451,0.0341294,0.0372835};
  for (Int_t i = 0; i < 17; i++) {row.Xknots[i] = X[i]; row.Yknots[i] = Y[i];}
  tableSet->AddAt(&row);
  return (TDataSet *)tableSet;
}
