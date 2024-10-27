TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_beamLine")) return 0;
  beamLine_st row;
  St_beamLine *tableSet = new St_beamLine("beamLine",1);
  memset(&row,0,tableSet->GetRowSize());
  row.X =     -0.320; row.sigma_X =      0.112;
  row.Y =     -2.236; row.sigma_Y =      0.072;
  row.Z =    200.209; row.sigma_Z =      0.147;
  tableSet->AddAt(&row);// PVxyz5p75GeV_fixedTarget_TFG24c.dEdxH2.root
  return (TDataSet *)tableSet;
}
