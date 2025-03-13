TDataSet *CreateTable() { 
// -----------------------------------------------------------------
// bfc/.make/db/.const/StarDb/Calibrations/tpc/.tpcPressureB/tpcPressureB Allocated rows: 50  Used rows: 50  Row size: 120 bytes
//  Table: tpcCorrection_st[0]--> tpcCorrection_st[49]
// ====================================================================
// ------  Test whether this table share library was loaded ------
  if (!TClass::GetClass("St_tpcCorrection")) return 0;
  tpcCorrection_st row;
  Int_t nrows = 1;
  St_tpcCorrection *tableSet = new St_tpcCorrection("tpcPressureB",2);
  //
  memset(&row,0,tableSet->GetRowSize()); // ~/work/Histograms/RunXXII13 $ root.exe Pressure+PressurePG4EYpp500_2022.root
  row.type	 =         0; //         FitP->Draw("mu-muJ:y>>oi","i&&j&&dmu>0&&dmu<0.02","prof")
  row.idx	 =         1; //         oi->Fit("pol2")
  row.nrows	 =     nrows; //
  row.npar	 =         3; //
  row.a[0]	 =   867.142; //
  row.a[1]	 =  -248.083;
  row.a[2]	 =   17.7419;
  tableSet->AddAt(&row);
  // ----------------- end of code ---------------
  return (TDataSet *)tableSet;
}
