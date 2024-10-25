TDataSet *CreateTable() { // Simulation !
  // -----------------------------------------------------------------
  // db/.const/StarDb/Calibrations/rhic/.beamLine/beamLine Allocated rows: 1  Used rows: 1  Row size: 44 bytes
  //  Table: beamLine_st[0]--> beamLine_st[0]
  // ====================================================================
  // ------  Test whether this table share library was loaded ------
  if (!TClass::GetClass("St_beamLine")) return 0;
  beamLine_st row;
  St_beamLine *tableSet = new St_beamLine("beamLine",1);
  //
  memset(&row,0,tableSet->GetRowSize());
  row.X =     0;
  row.Y =  -2.0;
  row.Z = 200.0;
  tableSet->AddAt(&row);
  // ----------------- end of code ---------------
  return (TDataSet *)tableSet;
}
