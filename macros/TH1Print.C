void TH1Print(TH1 *hist) {
  if (! hist) return;
  Int_t nx = hist->GetNbinsX();
  const Char_t *vars[6] = {"u","v","w","alpha","beta","gamma"};
  cout << "===================================================" << endl;
  for (int i  = 1; i <= nx; i++) {
    Double_t cor = hist->GetBinContent(i); 
    cout << i << "\t" << cor << endl;
  }
}
