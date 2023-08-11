TDataSet *CreateTable() { 
  // -----------------------------------------------------------------
  // bfc/.make/db/.const/StarDb/RunLog/onl/.starTriggerDelay/starTriggerDelay Allocated rows: 1  Used rows: 1  Row size: 16 bytes
  //  Table: starTriggerDelay_st[0]--> starTriggerDelay_st[0]
  // ====================================================================
  // ------  Test whether this table share library was loaded ------
  if (!TClass::GetClass("St_starTriggerDelay")) return 0;
  starTriggerDelay_st row;
  St_starTriggerDelay *tableSet = new St_starTriggerDelay("starTriggerDelay",1);
  //
  memset(&row,0,tableSet->GetRowSize());
  row.clocks     = 17; // from Run XIX + XX + XXI scan` 
  //  row.tZero	 = 0.435 - 0.029 -0.072 ; // from West East analysys 08/08/2023 wrong sign
  //  row.tZero	 = 0.435 - 0.029 +0.072 ; // from West East analysys 08/09/2023 should be: -(zW - zE)/2/DV
  //  row.tZero	 = 0.435 - 0.029 +0.072 + 0.004 ; // from West East analysys 08/09/2023 should be: -(zW - zE)/2/DV
  //  row.tZero	 = 0.435 - 0.029 +0.072 + 0.004 + 7.8e-3  ; // 4 from West East analysys 08/09/2023 should be: -(zW - zE)/2/DV
  row.tZero	 = 0.435 - 0.029 +0.072 + 0.004 - 7.8e-3  ; // 5 swap sign => 6
  tableSet->AddAt(&row);
  // ----------------- end of code ---------------
  return (TDataSet *)tableSet;
}
