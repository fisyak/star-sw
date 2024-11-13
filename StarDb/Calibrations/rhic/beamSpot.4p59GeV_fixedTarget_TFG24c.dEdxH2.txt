TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_beamSpot")) return 0;
  beamSpot_st row;
  St_beamSpot *tableSet = new St_beamSpot("beamSpot",1);
  memset(&row,0,tableSet->GetRowSize());
  row.X =     -0.366; row.sigma_X =      0.123;
  row.Y =     -2.194; row.sigma_Y =      0.073;
  row.Z =    200.152; row.sigma_Z =      0.162;
  tableSet->AddAt(&row);// PVxyz4p59GeV_fixedTarget_TFG24c.dEdxH2.root
  return (TDataSet *)tableSet;
}
