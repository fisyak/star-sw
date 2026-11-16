#ifndef __CINT__
#include "tables/St_runConfiguration_Table.h"
#endif
TDataSet *CreateTable() { 
  // ------  Test whether this table share library was loaded ------
  if (!gROOT->GetClass("St_runConfiguration")) return 0;
  Int_t nrows = 1;
  St_runConfiguration *tableSet = new St_runConfiguration("runConfiguration",nrows);
  runConfiguration_st row = {0, 0, 0, 0, "", "", ""};
  tableSet->AddAt(&row);
  return (TDataSet *)tableSet;
}
