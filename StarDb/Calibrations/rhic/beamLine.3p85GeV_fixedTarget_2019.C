TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_beamLine")) return 0;
  beamLine_st row;
  St_beamLine *tableSet = new St_beamLine("beamLine",1);
  memset(&row,0,tableSet->GetRowSize());
  row.X =     -0.547; row.sigma_X =      0.117;
  row.Y =     -2.186; row.sigma_Y =      0.077;
  row.Z =    200.085; row.sigma_Z =      0.142;
  tableSet->AddAt(&row);// PVxyz3p85GeV_fixedTarget_TFG24c.dEdxH.root
  return (TDataSet *)tableSet;
}
