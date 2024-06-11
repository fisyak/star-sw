#ifndef __CINT__
#include "tables/St_Survey_Table.h"
#endif

TDataSet *CreateTable() { 
  if (!TClass::GetClass("St_Survey")) return 0;
  Survey_st row = {
    //            -gamma     beta    gamma            -alpha    -beta    alpha                 x0        y0        z0   
    {0, 1.00000,-0.00000,-0.00056, 0.00000, 1.00000,-0.00013, 0.00056, 0.00013, 1.00000,  -0.1423,  -0.2979,  -0.1618,0.,0.,0.,0.,0.,0.,"2024 TPC 03/04/2024 average of West and East"}
  };
  St_Survey *tableSet = new St_Survey("TpcPosition",1);
  tableSet->AddAt(&row.Id);
  return (TDataSet *) tableSet;
}
