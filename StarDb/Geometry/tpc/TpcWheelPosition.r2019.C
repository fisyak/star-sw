#ifndef __CINT__
#include "tables/St_Survey_Table.h"
#endif
TDataSet *CreateTable() { 
  if (!gROOT->GetClass("St_Survey")) return 0;
  Double_t alpha_E = -0.28e-3;
  Double_t alpha_W =  0.08e-3;
  Double_t beta_E  =  0.19e-3;
  Double_t beta_W  =  0.16e-3;
  Survey_st row[2] = {
    //            -gamma     beta    gamma            -alpha    -beta    alpha          x0 y0 z0
    {0, 1.00000, 0.00000,  beta_E, 0.00000, 1.00000,-alpha_E, -beta_E, alpha_E, 1.00000, 0, 0, 0, 0,0,0,0,0,0,"2024 Wheel east 03/05/2024"},
    {1, 1.00000, 0.00000,  beta_W, 0.00000, 1.00000,-alpha_W, -beta_W, alpha_W, 1.00000, 0, 0, 0, 0,0,0,0,0,0,"2024 Wheel west 03/05/2024"},
    
  };
  Int_t n = 2;// east = 0, west = 1
  St_Survey *tableSet = new St_Survey("TpcWheelPosition",n);
  for (Int_t half = 0; half < 2; half++) {
    tableSet->AddAt(&row[half].Id);
  }
  return (TDataSet *)tableSet;
}
