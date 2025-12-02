#ifndef __CINT__
#include "tables/St_MDFCorrection4_Table.h"
#endif
//  cat TpcPullMDF4pullYICOL.C TpcPullMDF4pullZICOL.C TpcPullMDF4pullYOCOL.C TpcPullMDF4pullZOCOL.C > TpcPullMDF4COL.y2019.C
TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_MDFCorrection4")) return 0;
  MDFCorrection4_st row;
  St_MDFCorrection4 *tableSet = new St_MDFCorrection4("TpcPullMDF4COL",8);
  memset(&row,0,tableSet->GetRowSize());
  tableSet->AddAt(&row); // idx = 1
  tableSet->AddAt(&row); // idx = 2
  tableSet->AddAt(&row); // idx = 3
  tableSet->AddAt(&row); // idx = 4
  tableSet->AddAt(&row); // idx = 5
  tableSet->AddAt(&row); // idx = 6
  tableSet->AddAt(&row); // idx = 7
  tableSet->AddAt(&row); // idx = 8
  return (TDataSet *)tableSet;
}
