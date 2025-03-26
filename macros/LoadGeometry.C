void LoadGeometry(const Char_t *year="y2019") {
  TString geometry = Form("$STAR/StarDb/AgiGeometry/Geometry.%s.C",year);
  gROOT->LoadMacro(geometry);
  CreateTable();
}
