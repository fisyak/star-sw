TH2F *TH2NormX(TH2F *h2) {
  if (!h2) return 0;
  TH2F *h2new = new TH2F(*h2);
  h2new->SetName(Form("%sNorm",h2->GetName()));
  Int_t nx = h2->GetXaxis()->GetNbins();
  Int_t ny = h2->GetYaxis()->GetNbins();
  for (Int_t i = 1; i <= nx; i++) {
    Double_t sum = 0;
    for (Int_t j = 1; j <= ny; j++) {
      sum += h2->GetBinContent(i,j);
    }
    if (sum > 0.0) {
      for (Int_t j = 1; j <= ny; j++) {
	h2new->SetBinContent(i,j,h2->GetBinContent(i,j)/sum);
      }
    }
  }
  return h2new;
}
