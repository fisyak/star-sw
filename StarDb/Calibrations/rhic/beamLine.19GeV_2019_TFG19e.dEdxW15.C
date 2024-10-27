TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_beamLine")) return 0;
  beamLine_st row;
  St_beamLine *tableSet = new St_beamLine("beamLine",1);
  memset(&row,0,tableSet->GetRowSize());
  row.X =      0.093; row.sigma_X =      0.134;
  row.Y =     -0.298; row.sigma_Y =      0.080;
  row.Z =     -8.106; row.sigma_Z =     94.452;
  tableSet->AddAt(&row);// PVxyz19GeV_2019_TFG19e.dEdxW15.root
  return (TDataSet *)tableSet;
}
