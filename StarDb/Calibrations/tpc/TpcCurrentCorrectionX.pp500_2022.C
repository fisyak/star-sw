#ifndef __CINT__
#include "tables/St_tpcCorrection_Table.h"
#endif
TDataSet *CreateTable() { 
  if (!gROOT->GetClass("St_tpcCorrection")) return 0;
  Int_t nrows = 2;
  tpcCorrection_st row;
  St_tpcCorrection *tableSet = new St_tpcCorrection("TpcCurrentCorrection",nrows);
  memset(&row,0,tableSet->GetRowSize()); // ~/work/Histograms/RunXXII09 $ root.exe AvCurrentGPpp500_2022.root
  row.nrows      =        nrows; // Outer sector correction 
  row.idx        =            1; // FitP->Draw("mu:y>>OP","i&&j&&(i-1)%8+1>4","prof");  OP->Fit("pol2","er","",0.02,0.3)
  row.npar       =            3; // 
  row.min        =         0.02;
  row.max        =          0.3;
  row.type       =          300; // don't correct out of range [min,max]
  row.a[0]       =  1.04511e-01;// 
  row.a[1]       = -6.58607e-01;//
  row.a[2]       =  6.54223e-01;//
   tableSet->AddAt(&row);
  memset(&row,0,tableSet->GetRowSize()); // 0
  row.nrows      =        nrows; // Inner sector correction 
  row.idx        =            2; //  FitP->Draw("mu:y>>IP","i&&j&&(i-1)%8+1<=4","prof"); IP->Fit("pol3","er","",0.,0.41)
  row.npar       =            4; // 
  row.min        =           0.;
  row.max        =         0.41;
  row.type       =          300; // don't correct out of range [min,max]
  row.a[0]       =  1.24728e-01;
  row.a[1]       = -6.28860e-01;
  row.a[2]       = -1.75935e+00;
  row.a[3]       =  7.74635e+00;
  tableSet->AddAt(&row);
  // ----------------- end of code ---------------
  return (TDataSet *)tableSet;
}
