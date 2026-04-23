#ifndef __CINT__
#include "tables/St_MDFCorrection4_Table.h"
#endif
TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_MDFCorrection4")) return 0;
  MDFCorrection4_st row;
  St_MDFCorrection4 *tableSet = new St_MDFCorrection4("TpcInnerPullMDF4",4);
  memset(&row,0,tableSet->GetRowSize());
  row.nrows =  4; //pullYI	13p5GeV_fixedTarget_2026/pullYIGP2025_RF_13p5GeV_fixedTarget_2026GP.PullsH.root
  row.idx   =  1;//	Sigma
  row.DMean = 	1.924;
  tableSet->AddAt(&row); // idx = 1
  memset(&row,0,tableSet->GetRowSize());
  row.nrows =  4; //pullYI	13p5GeV_fixedTarget_2026/pullYIGP2025_RF_13p5GeV_fixedTarget_2026GP.PullsH.root
  row.idx   =  2;//	Mu
  tableSet->AddAt(&row); // idx = 2
  memset(&row,0,tableSet->GetRowSize());
  row.nrows =  4; //pullZI	13p5GeV_fixedTarget_2026/pullZIGP2025_RF_13p5GeV_fixedTarget_2026GP.PullsH.root
  row.idx   =  3;//	Sigma
  row.DMean = 	1.600;;
  tableSet->AddAt(&row); // idx = 3
  memset(&row,0,tableSet->GetRowSize());
  row.nrows =  4; //pullZI	13p5GeV_fixedTarget_2026/pullZIGP2025_RF_13p5GeV_fixedTarget_2026GP.PullsH.root
  row.idx   =  4;//	Mu
  tableSet->AddAt(&row); // idx = 4
  return (TDataSet *)tableSet;
}
