#ifndef __CINT__
#include "tables/St_MDFCorrection4_Table.h"
#endif
TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_MDFCorrection4")) return 0;
  MDFCorrection4_st row;
  St_MDFCorrection4 *tableSet = new St_MDFCorrection4("TpcInnerPullMDF4",4);
  memset(&row,0,tableSet->GetRowSize());
  tableSet->AddAt(&row); // idx = 1
  tableSet->AddAt(&row); // idx = 2
  tableSet->AddAt(&row); // idx = 3
  tableSet->AddAt(&row); // idx = 4
  return (TDataSet *)tableSet;	  
}
