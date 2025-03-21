#ifndef __CINT__
#include "tables/St_tpcCorrection_Table.h"
#endif

TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcCorrection")) return 0;
  Int_t nrows = 2;
  St_tpcCorrection *tableSet = new St_tpcCorrection("TpcEtaCorrection",nrows);
  tpcCorrection_st row;
  memset(&row,0,tableSet->GetRowSize()); // ~/work/Histograms/RunXXII16 $ root.exe Eta3GPpp500_2022.root Eta3PGPpp500_2022.root Chain.C
  row.idx   = 1;                         //   tChain->Draw("mu-muJ:y*y>>o","(i&&j&&mu>-0.4&&abs(x)>40.5)/dmu**2","profg")
  row.nrows = nrows;
  row.npar =            8;//  o->Fit("pol7","e")
  row.a[0] =  9.39789e-02;
  row.a[1] = -3.13606e-01;
  row.a[2] =  1.66940e-01;
  row.a[3] = -2.40561e-01;
  row.a[4] =  4.62371e-01;
  row.a[5] = -3.89208e-01;
  row.a[6] =  1.48440e-01;
  row.a[7] = -2.13348e-02;
  tableSet->AddAt(&row);
  memset(&row,0,tableSet->GetRowSize());
  row.idx   = 2;                         //  tChain->Draw("mu-muJ:y*y>>i","(i&&j&&mu>-0.4&&abs(x)<40.5)/dmu**2","profg")
  row.nrows = nrows;
  row.npar =            6;// i->Fit("pol5","e")
  row.a[0] =  1.23525e-01; 
  row.a[1] = -3.06953e-01;
  row.a[2] =  2.16029e-01;
  row.a[3] = -1.31120e-01;
  row.a[4] =  4.96652e-02;
  row.a[5] = -6.91850e-03;
  tableSet->AddAt(&row);
  return (TDataSet *)tableSet;
}
