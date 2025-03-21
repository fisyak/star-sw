#ifndef __CINT__
#include "tables/St_tpcCorrection_Table.h"
#endif
TDataSet *CreateTable() { 
// -----------------------------------------------------------------
// bfc/.make/db/.const/StarDb/Calibrations/tpc/.tpcPressureB/tpcPressureB Allocated rows: 50  Used rows: 50  Row size: 120 bytes
//  Table: tpcCorrection_st[0]--> tpcCorrection_st[49]
// ====================================================================
// ------  Test whether this table share library was loaded ------
  if (!TClass::GetClass("St_tpcCorrection")) return 0;
  tpcCorrection_st row;
  Int_t nrows = 2;
  St_tpcCorrection *tableSet = new St_tpcCorrection("tpcPressureB",2);
  //
  memset(&row,0,tableSet->GetRowSize()); // ~/work/Histograms/RunXXII15 $ root.exe  PressureG4EYpp500_2022.root PressurePG4EYpp500_2022.root Chain.C
  row.type	 =           0; //        tChain->Draw("mu-muJ:y>>o","i&&j&&dmu>0&&dmu<0.02&&&abs(x)>40","prof")
  row.idx	 =           1; //         o->Fit("pol1")
  row.nrows	 =       nrows; //
  row.npar	 =           2; //
  row.a[0]	 =  1.94849e+01; //
  row.a[1]	 = -2.81515e+00;
  tableSet->AddAt(&row);
  memset(&row,0,tableSet->GetRowSize()); // ~/work/Histograms/RunXXII15 $ root.exe  PressureG4EYpp500_2022.root PressurePG4EYpp500_2022.root Chain.C
  row.type	 =            0; //        tChain->Draw("mu-muJ:y>>o","i&&j&&dmu>0&&dmu<0.02&&&abs(x)>40","prof")
  row.idx	 =            1; //         i->Fit("pol2")
  row.nrows	 =        nrows; //
  row.npar	 =            3; //
  row.a[0]	 =  1.12513e+03; //
  row.a[1]	 = -3.23066e+02;
  row.a[2]	 =  2.31901e+01;
 tableSet->AddAt(&row);
  // ----------------- end of code ---------------
  return (TDataSet *)tableSet;
}
