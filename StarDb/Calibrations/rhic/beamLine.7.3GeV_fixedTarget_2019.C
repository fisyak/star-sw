TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_beamLine")) return 0;
  beamLine_st row;
  St_beamLine *tableSet = new St_beamLine("beamLine",1);
  memset(&row,0,tableSet->GetRowSize());
  row.X =     -0.392; row.sigma_X =      0.140;
  row.Y =     -2.190; row.sigma_Y =      0.076;
  row.Z =    200.136; row.sigma_Z =      0.175;
  tableSet->AddAt(&row);// PVxyz7.3GeV_fixedTarget_TFG24c.dEdxH2.root
  return (TDataSet *)tableSet;
}
