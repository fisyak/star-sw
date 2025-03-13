#ifndef __CINT__
#include "tables/St_tpcCorrection_Table.h"
#endif
TDataSet *CreateTable() { 
  if (!gROOT->GetClass("St_tpcCorrection")) return 0;
  Int_t nrows = 2;
  tpcCorrection_st row;
  St_tpcCorrection *tableSet = new St_tpcCorrection("TpcAccumulatedQ",nrows);
  memset(&row,0,tableSet->GetRowSize()); // ~/work/Histograms/RunXXII10 $ root.exe QcmCGPpp500_2022_2022.root
  row.nrows      =        nrows; // Outer sector correction 
  row.idx        =            1; // FitP->Draw("mu:y>>OP","i&&j&&(i-1)%8+1>4","prof");   OP->Fit("pol2","e")
  row.npar       =            3; // 
  row.a[0]       = -9.89021e-03;// 
  row.a[1]       = -2.43989e-05;//
  row.a[2]       =  3.05036e-07;//
  tableSet->AddAt(&row);
  memset(&row,0,tableSet->GetRowSize()); // 0
  row.nrows      =        nrows; // Inner sector correction 
  row.idx        =            2; //  FitP->Draw("mu:y>>IP","i&&j&&(i-1)%8+1<=4","prof"); IP->Fit("pol3","er","",0.,0.41)
  row.npar       =            6; // 
  row.min        =           0.;
  row.max        =         600.;
  row.type       =          300; // don't correct out of range [min,max]
  row.a[0]       =  3.08963e-02;
  row.a[1]       = -1.70712e-03;
  row.a[2]       =  1.43659e-05;
  row.a[3]       = -4.69044e-08;
  row.a[4]       =  7.02425e-11;
  row.a[5]       = -3.95085e-14;
  tableSet->AddAt(&row);
  // ----------------- end of code ---------------
  return (TDataSet *)tableSet;
}
