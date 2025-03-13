#ifndef __CINT__
#include "tables/St_tpcCorrection_Table.h"
#endif

TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcCorrection")) return 0;
  Int_t nrows = 2;
  St_tpcCorrection *tableSet = new St_tpcCorrection("TpcEtaCorrection",nrows);
  tpcCorrection_st row;
  memset(&row,0,tableSet->GetRowSize()); // //net/l404/data/fisyak/Histograms/RunXXII12/Eta" 
  row.idx   = 1;                         //  root.exe *.root Chain.C ,  tChaain->Draw("mu-muJ:y*y>>o","i&&j&&mu>-0.4&&abs(x)>40.5","prof")
  row.nrows = nrows;
  row.npar =            6;//  o->Fit("pol5","e")
  row.a[0] =  7.68487e-02;
  row.a[1] = -1.46571e-01;
  row.a[2] = -2.08002e-01;
  row.a[3] =  3.15222e-01;
  row.a[4] = -1.29356e-01;
  row.a[5] =  1.71639e-02;
  tableSet->AddAt(&row);
  memset(&row,0,tableSet->GetRowSize());
  row.idx   = 2;                         //  tChain->Draw("mu-muJ:y*y>>i","i&&j&&mu>-0.4&&abs(x)<40.5","prof")
  row.nrows = nrows;
  row.npar =            7;// i->Fit("pol6","e")
  row.a[0] =  1.17781e-01; 
  row.a[1] = -3.23740e-01;
  row.a[2] =  5.37433e-01;
  row.a[3] = -6.35513e-01;
  row.a[4] =  3.60018e-01;
  row.a[5] = -9.18971e-02;
  row.a[6] =  8.64982e-03;
  tableSet->AddAt(&row);
  return (TDataSet *)tableSet;
}
