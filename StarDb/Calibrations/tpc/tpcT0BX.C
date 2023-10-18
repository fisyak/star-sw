#ifndef __CINT__
#include "tables/St_tpcT0BX_Table.h"
#endif

TDataSet *CreateTable() { 
// ------  Test whether this table share library was loaded ------
  if (!TClass::GetClass("St_tpcT0BX")) return 0;
  Int_t nrows = 7;  
  tpcT0BX_st row[7] = {
    // Id,    name, xmin, xmax, tMean, vMean, toff, dtoff, slope, dsplote, CPts, CdPts  
    {  -1,   "vpd",    0,    0,     0,      0,   0,     0,      0,      0,    0,     0}, 
    {  -2,   "bbc",    0,    0,     0,	    0, 	 0, 	0,      0, 	0,    0,     0},
    {  -3,   "epd",    0,    0,     0,	    0, 	 0, 	0,      0, 	0,    0,     0},
    {  -4,   "zdc",    0,    0,     0,	    0, 	 0, 	0,      0, 	0,    0,     0},
    {  -5,   "TAC",    0,    0,     0,	    0, 	 0, 	0,      0, 	0,    0,     0},
    {  -6,   "CAV",    0,    0,     0,      0, 	 0, 	0,      0, 	0,    0,     0},
    {  -7, "zKFXT",    0,    0,     0,	    0, 	 0, 	0,      0, 	0,    0,     0} 
  };
  St_tpcT0BX *tableSet = new St_tpcT0BX("tpcT0BX",nrows);
  for (Int_t i = 0; i < nrows; i++) tableSet->AddAt(&row[i].detId);
  return (TDataSet *)tableSet;
}

