
// Make Histogram from Integral of hist
TH1D *ITH1(TH1D *hist) {
  if (! hist) return 0;
  TH1D *ihist = new TH1D(*hist);
  ihist->SetName(Form("I%s",hist->GetName()));
  Int_t nbinsx = ihist->GetNbinsX();
  Double_t *Integral = hist->GetIntegral();
  for (Int_t i = 0; i <= nbinsx+1; i++) {
    ihist->SetBinContent(i,Integral[i]);
  }
  return ihist;
}
