#ifndef __CINT__
#include "tables/St_starTriggerDelay_Table.h"
#endif

TDataSet *CreateTable() { 
  // -----------------------------------------------------------------
  // bfc/.make/db/.const/StarDb/RunLog/onl/.CosmicsDelay/CosmicsDelay Allocated rows: 1  Used rows: 1  Row size: 16 bytes
  //  Table: starTriggerDelay_st[0]--> starTriggerDelay_st[0]
  // ====================================================================
  // ------  Test whether this table share library was loaded ------
  if (!TClass::GetClass("St_starTriggerDelay")) return 0;
  starTriggerDelay_st row;
  St_starTriggerDelay *tableSet = new St_starTriggerDelay("CosmicsDelay",1);
  //
  memset(&row,0,tableSet->GetRowSize());
  row.clocks     = (2*0.372-0.55711)/2;  // Run XIX RF and FF +(West - East)/2
  row.tZero	 = 0; // -"-
  tableSet->AddAt(&row);
  // ----------------- end of code ---------------
  return (TDataSet *)tableSet;
}
