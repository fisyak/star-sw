#ifndef __CINT__
#include "tables/St_starMagRotation_Table.h"
#endif

TDataSet *CreateTable() { 
  if (!gROOT->GetClass("St_starMagRotation")) return 0;
  starMagRotation_st rows[2] = {
    //Id  alpha,  beta, gamma 
    { 0,  0.000, 0.000, 0.000}, // RF
    { 1,  0.000, 0.000, 0.000}  // FF
  };
  Int_t n = 2;// RF = 0, FF = 1 
  St_starMagRotation *tableSet = new St_starMagRotation("starMagRotation",n);
  for (Int_t i = 0; i < n; i++) {
    tableSet->AddAt(&rows[i].Id);
  }
  return (TDataSet *)tableSet;
}
