TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_beamLine")) return 0;
  beamLine_st row;
  St_beamLine *tableSet = new St_beamLine("beamLine",1);
  memset(&row,0,tableSet->GetRowSize());
  row.X =     -0.364; row.sigma_X =      0.123;
  row.Y =     -2.194; row.sigma_Y =      0.073;
  row.Z =    200.150; row.sigma_Z =      0.161;
  tableSet->AddAt(&row);// PVxyz4p59GeV_fixedTarget_TFG24d.dEdxD.root
  return (TDataSet *)tableSet;
}
