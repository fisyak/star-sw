#ifndef __CINT__
#include "tables/St_beamSpot_Table.h"
#endif
TDataSet *CreateTable() { // Simulation !
  // -----------------------------------------------------------------
  // db/.const/StarDb/Calibrations/rhic/.beamSpot/beamSpot Allocated rows: 1  Used rows: 1  Row size: 44 bytes
  //  Table: beamSpot_st[0]--> beamSpot_st[0]
  // ====================================================================
  // ------  Test whether this table share library was loaded ------
  if (!TClass::GetClass("St_beamSpot")) return 0;
  beamSpot_st row;
  St_beamSpot *tableSet = new St_beamSpot("beamSpot",1);
  //
  memset(&row,0,tableSet->GetRowSize());
  tableSet->AddAt(&row);
  // ----------------- end of code ---------------
  return (TDataSet *)tableSet;
}
