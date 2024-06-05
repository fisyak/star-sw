TDataSet *CreateTable() { 
// -----------------------------------------------------------------
// bfc/.make/db/.const/StarDb/Geometry/tpc/.tpcFieldCageShort/tpcFieldCageShort Allocated rows: 10  Used rows: 10  Row size: 20 bytes
//  Table: tpcFieldCageShort_st[0]--> tpcFieldCageShort_st[9]
// ====================================================================
// ------  Test whether this table share library was loaded ------
  if (!TClass::GetClass("St_tpcFieldCageShort")) return 0;
tpcFieldCageShort_st row;
St_tpcFieldCageShort *tableSet = new St_tpcFieldCageShort("tpcFieldCageShort",10);
//
memset(&row,0,tableSet->GetRowSize());
    row.side	 =          0; // 0 = east, 1 = west ;
    row.cage	 =          0; // 0 = inner, 1 = outer ;
    row.ring	 =          0; // ring location of the short (e.g. 169.5) ;
    row.resistor	 =          0; // MOhm value of added external resistor to resistor chain ;
    row.MissingResistance	 =          0; // missing resistance ;
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.side	 =          0; // 0 = east, 1 = west ;
    row.cage	 =          0; // 0 = inner, 1 = outer ;
    row.ring	 =          0; // ring location of the short (e.g. 169.5) ;
    row.resistor	 =          0; // MOhm value of added external resistor to resistor chain ;
    row.MissingResistance	 =          0; // missing resistance ;
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.side	 =          0; // 0 = east, 1 = west ;
    row.cage	 =          0; // 0 = inner, 1 = outer ;
    row.ring	 =          0; // ring location of the short (e.g. 169.5) ;
    row.resistor	 =          0; // MOhm value of added external resistor to resistor chain ;
    row.MissingResistance	 =          0; // missing resistance ;
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.side	 =          1; // 0 = east, 1 = west ;
    row.cage	 =          0; // 0 = inner, 1 = outer ;
    row.ring	 =      160.5; // ring location of the short (e.g. 169.5) ;
    row.resistor	 =       1.25; // MOhm value of added external resistor to resistor chain ;
    row.MissingResistance	 =          2; // missing resistance ;
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.side	 =          1; // 0 = east, 1 = west ;
    row.cage	 =          1; // 0 = inner, 1 = outer ;
    row.ring	 =       80.5; // ring location of the short (e.g. 169.5) ;
    row.resistor	 =          0; // MOhm value of added external resistor to resistor chain ;
    row.MissingResistance	 =          0; // missing resistance ;
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.side	 =          0; // 0 = east, 1 = west ;
    row.cage	 =          0; // 0 = inner, 1 = outer ;
    row.ring	 =          0; // ring location of the short (e.g. 169.5) ;
    row.resistor	 =          0; // MOhm value of added external resistor to resistor chain ;
    row.MissingResistance	 =          0; // missing resistance ;
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.side	 =          0; // 0 = east, 1 = west ;
    row.cage	 =          0; // 0 = inner, 1 = outer ;
    row.ring	 =          0; // ring location of the short (e.g. 169.5) ;
    row.resistor	 =          0; // MOhm value of added external resistor to resistor chain ;
    row.MissingResistance	 =          0; // missing resistance ;
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.side	 =          0; // 0 = east, 1 = west ;
    row.cage	 =          0; // 0 = inner, 1 = outer ;
    row.ring	 =          0; // ring location of the short (e.g. 169.5) ;
    row.resistor	 =          0; // MOhm value of added external resistor to resistor chain ;
    row.MissingResistance	 =          0; // missing resistance ;
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.side	 =          0; // 0 = east, 1 = west ;
    row.cage	 =          0; // 0 = inner, 1 = outer ;
    row.ring	 =          0; // ring location of the short (e.g. 169.5) ;
    row.resistor	 =          0; // MOhm value of added external resistor to resistor chain ;
    row.MissingResistance	 =          0; // missing resistance ;
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.side	 =          0; // 0 = east, 1 = west ;
    row.cage	 =          0; // 0 = inner, 1 = outer ;
    row.ring	 =          0; // ring location of the short (e.g. 169.5) ;
    row.resistor	 =          0; // MOhm value of added external resistor to resistor chain ;
    row.MissingResistance	 =          0; // missing resistance ;
tableSet->AddAt(&row);
// ----------------- end of code ---------------
 return (TDataSet *)tableSet;
}
