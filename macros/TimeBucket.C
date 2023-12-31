/*
  root.exe 'Chain.C+("st_*Aligner.root","TpcInOutTree")' 'TimeBucket.C(tChain)'
 */
void TimeBucket(TChain *tChain=0) {
  if (! tChain) return;
  tChain->Draw("driftVel/freq >> htemp");
  TH1 *htemp = (TH1 *) gDirectory->Get("htemp");
  cout << gSystem->WorkingDirectory() << "\t" << htemp->GetMean() << endl; 
} 
