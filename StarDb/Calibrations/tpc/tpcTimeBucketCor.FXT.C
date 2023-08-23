TDataSet *CreateTable() { 
// ------  Test whether this table share library was loaded ------
  if (!gROOT->GetClass("St_tpcCorrection")) return 0;
  tpcCorrection_st row;
  Int_t nrows = 4; // /net/l404/data/fisyak/Tpc/TpcRS/2019/3p85_GeV_fixedTarget_2019_PHQMD6
  St_tpcCorrection *tableSet = new St_tpcCorrection("tpcTimeBucketCor",nrows);
  memset(&row,0,tableSet->GetRowSize()); 
  row.nrows      =        nrows; // BOWGPT0 : f1_50->Fit("gaus","re","",-0.11,0.12) => Mean         3.87095e-03 +/- 6.48198e-05
  row.idx        =            1; // FitP->Draw("mu-3.87095e-03:x>>OW","(i&&j)/dmu**2","profg")
  row.npar       =            3; // 
  row.a[0]       =  3.25111e-02; 
  row.a[1]       =  5.59836e-03;
  row.a[2]       = -1.42976e-03;
  tableSet->AddAt(&row);
  memset(&row,0,tableSet->GetRowSize());
  row.idx        =            2; // BIWGPT0 : f1_50->Fit("gaus","er","",-0.13,0.04) => Mean        -4.57129e-02 +/- 5.10775e-05
  row.npar       =            3; // FitP->Draw("mu+4.57129e-02:x>>IW","(i&&j)/dmu**2","profg")
  row.a[0]       =  3.20728e-02; 
  row.a[1]       =  3.59554e-03;
  row.a[2]       = -1.63944e-03;
  tableSet->AddAt(&row);
  memset(&row,0,tableSet->GetRowSize()); 
  row.nrows      =        nrows; // BOEGPT0 BOWGPT0 : f1_50->Fit("gaus","re","",-0.5,0.4) => Mean        -4.68791e-02 +/- 2.01232e-04
  row.idx        =            3; // FitP->Draw("mu+4.68791e-02:x>>OE","(i&&j)/dmu**2","profg")
  row.npar       =            4; // OE->Fit("pol3","er","",4,24)
  row.min        =            4;
  row.max        =           24;
  row.a[0]       =  1.20316e+00; 
  row.a[1]       = -2.78332e-01;
  row.a[2]       =  2.17043e-02;
  row.a[3]       = -5.71913e-04;
  tableSet->AddAt(&row);
  memset(&row,0,tableSet->GetRowSize());
  row.idx        =            4; //  => Mean        -0.1154 +/- 0.00045
  row.npar       =            4; // FitP->Draw("mu+0.1154:x>>IE","(i&&j)/dmu**2","profg")
  row.min        =            2; // IE->Fit("pol3","er","",2,28)
  row.max        =           28;
  row.a[0]       =  1.03837e+00; 
  row.a[1]       = -2.02657e-01;
  row.a[2]       =  1.37715e-02;
  row.a[3]       = -3.34972e-04;
  tableSet->AddAt(&row);
  // ----------------- end of code ---------------
  return (TDataSet *)tableSet;
}
