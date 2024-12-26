/*
  root.exe -q -b 'bfc.C(0)' Run1Ev.C 'TpcHit.C(10)'
  root.exe -q -b 'bfc.C(0,"MC,r2023a,P2023a,StiCA,-in,TpcRS,corrY,TpxClu,TPC23,bbcSim,btofsim,ETofSim,Muons20,vmc,Rung.1,dEdxCalib,UseCAVxFinder,evout,geantout")' Run1Ev.C 'TpcHit.C(10)'
  root.exe -q -b 'bfc.C(0,"MC,r2023a,P2023a,StiCA,-in,TpcRS,corrZ,-TpcMDF4Error,TpxClu,TPC23,bbcSim,btofsim,ETofSim,Muons20,vmc,Rung.1,dEdxCalib,UseCAVxFinder,evout,geantout")' Run1Ev.C 'TpcHit.C(10)'
 */
void TpcHit(Int_t nev = 10) {
  StAnalysisMaker::instance()->PrintTpcHits(0,0,1);
  for (Int_t i = 0; i < nev; i++) {
    chain->MakeEvent();
    StAnalysisMaker::instance()->PrintTpcHits(0,0,1);
  }
}
