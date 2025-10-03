// root.exe 'bfc.C(0)' Epd.C
void Epd() {
  gSystem->Load("StEpdFastSimMaker");
  StMaker *mk = new StEpdFastSimMaker;
  chain->AddAfter("TpcRS",mk);
  mk->Init();
}
