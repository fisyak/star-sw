#ifndef __CINT__
#include "tables/St_Survey_Table.h"
#endif

TDataSet *CreateTable() { 
  if (!TClass::GetClass("St_Survey")) return 0;
  Survey_st row = {
    //           -gamma     beta    gamma            -alpha    -beta    alpha                 x0        y0        z0
//  0,       1,-0.00036,-0.00048, 0.00036,       1, -0.0001, 0.00048,  0.0001,       1,  -0.2383,  -0.1732,  -0.1957,0,0,0,0,0,0,"2013 Tpc"
//  0, 1.00000, 0.00000,-0.00037, 0.00000, 1.00000, 0.00000, 0.00037, 0.00000, 1.00000,   0.0000,   0.0000,  -0.3062,0,0,0,0,0,0,"2024 Tpc"
    0, 1.00000,-0.00037,-0.00037, 0.00037, 1.00000, 0.00014, 0.00037,-0.00014, 1.00000,  -0.1100,  -0.2881,  -0.3062,0,0,0,0,0,0,"2024 Tpc"
  };
  St_Survey *tableSet = new St_Survey("TpcPosition",1);
  tableSet->AddAt(&row.Id);
  return (TDataSet *) tableSet;
}
