void ZTMfl0T() {
  cout << gDirectory->GetName() << endl;
  TNtuple *FitP = (TNtuple *) gDirectory->Get("FitP");
  if (! FitP) return;
  FitP->Draw("mu:sector>>Mu(24,0.5,24.5,100,2,12)","dmu>0&&dmu<0.2");
}
