TDataSet *CreateTable() { 
// -----------------------------------------------------------------
// bfc/.make/db/.const/StarDb/Calibrations/tracker/.PrimaryVertexCuts/PrimaryVertexCuts Allocated rows: 1  Used rows: 1  Row size: 40 bytes
//  Table: VertexCuts_st[0]--> VertexCuts_st[0]
// ====================================================================
// ------  Test whether this table share library was loaded ------
  if (!TClass::GetClass("St_VertexCuts")) return 0;
VertexCuts_st row;
St_VertexCuts *tableSet = new St_VertexCuts("PrimaryVertexCuts",1);
//
memset(&row,0,tableSet->GetRowSize());
    row.MinNumberOfFitPointsOnTrack	 =         20; // ;
    row.MinTrack	 =          2; // ;
    row.DcaZMax	 =          6; // ;
    row.RImpactMax	 =          6; // ;
    row.MinFracOfPossFitPointsOnTrack	 =        0.0; // ;
    row.MinTrackPt	 =        0.0; // ;
    row.ZMin	 =       -200; // ;
    row.ZMax	 =        225; // ;
tableSet->AddAt(&row);
// ----------------- end of code ---------------
 return (TDataSet *)tableSet;
}
