#ifndef __CINT__
#include "tables/St_etofPulserTotPeak_Table.h"
#endif
TDataSet *CreateTable() { 
// -----------------------------------------------------------------
// bfc/.make/db/.const/StarDb/Calibrations/etof/.etofPulserTotPeak/etofPulserTotPeak Allocated rows: 1  Used rows: 1  Row size: 216 bytes
//  Table: etofPulserTotPeak_st[0]--> etofPulserTotPeak_st[0]
// ====================================================================
// ------  Test whether this table share library was loaded ------
  if (!TClass::GetClass("St_etofPulserTotPeak")) return 0;
  etofPulserTotPeak_st row;
  St_etofPulserTotPeak *tableSet = new St_etofPulserTotPeak("etofPulserTotPeak",1);
  //
  memset(&row,0,tableSet->GetRowSize());
  for (Int_t i = 0; i < 216; i++) {
    row.pulserTot[i]	 =         0x62; // ToT peak position (bin: 0-255) of pulsers per side;
  }
  tableSet->AddAt(&row);
  // ----------------- end of code ---------------
  return (TDataSet *)tableSet;
}
