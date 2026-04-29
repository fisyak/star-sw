#ifndef __CINT__
#include "tables/St_tpcCorrection_Table.h"
#endif

TDataSet *CreateTable() { 
  if (!gROOT->GetClass("St_tpcCorrection")) return 0;
  tpcCorrection_st row;
  Int_t nrows = 2;
  St_tpcCorrection *tableSet = new St_tpcCorrection("tpcGainCorrection",nrows);
  memset(&row,0,tableSet->GetRowSize()); // 0
    row.idx	 =          1; // ;
    row.nrows	 =      nrows; // ;
    row.npar	 =          2; // ;
    row.min	 =       -100; // ;
    row.max	 =        100; // ;
    row.a[0]	 =   7.178177; // ;
    row.a[1]	 = 0.009470269;
  tableSet->AddAt(&row); // Outer
  memset(&row,0,tableSet->GetRowSize()); // 0
    row.idx	 =          2; // ;
    row.nrows	 =      nrows; // ;
    row.npar	 =          2; // ;
    row.min	 =       -200; // ;
    row.max	 =        100; // ;
    row.a[0]	 =   8.178157 -0.16022460; // ;
    row.a[1]	 = 0.01148008 -0.00289645;
  tableSet->AddAt(&row); // Inner
  // ----------------- end of code ---------------
  return (TDataSet *)tableSet;
}
