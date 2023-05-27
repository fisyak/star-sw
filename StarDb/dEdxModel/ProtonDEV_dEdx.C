TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_spline3")) return 0;
  Int_t nrows = 1;
  St_spline3 *tableSet = new St_spline3("ProtonDEV_dEdx",nrows);
  spline3_st row;
  memset(&row,0,tableSet->GetRowSize());
  row.nknots = 16;
  Double_t X[16] = {-0.3825,-0.3105,-0.2385,-0.1665,-0.0945,-0.0225,0.0495,0.1215,0.1935,0.2655,0.3375,0.4095,0.4815,0.5535,0.6255,0.6975};
  Double_t Y[16] = {0.0395151,0.0327945,0.0263327,0.0207465,0.0167052,0.0145071,0.0144848,0.019449,0.0263189,0.0286956,0.0329375,0.0349713,0.037862,0.0402041,0.0427758,0.0446672};
  for (Int_t i = 0; i < 16; i++) {row.Xknots[i] = X[i]; row.Yknots[i] = Y[i];}
  tableSet->AddAt(&row);
  return (TDataSet *)tableSet;
}
