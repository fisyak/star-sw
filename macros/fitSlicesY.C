void fitSlicesY(const Char_t *W = "XZW", const Char_t *E = "XZE") {
  Int_t NF = 0;
  TSeqCollection *files = gROOT->GetListOfFiles();
  if (! files) return;
  Int_t nn = files->GetSize();
  if (! nn) return;
  TIter next(files);
  TFile *f = 0;
  const Char_t *WE[2] = {W, E};
  Double_t xWE[2] = {0,0};
  Double_t dxWE[2] = {0,0};
  TObjArray *arr = new TObjArray(4);
  while ( (f = (TFile *) next()) ) { 
    TString F(f->GetName());
    cout << Form("%-36s",F.Data());
    for (Int_t i = 0; i < 2; i++) {
      TH2 *h2 = (TH2*) f->Get(WE[i]);
      if (! h2) continue;
      h2->FitSlicesY(0, 0, -1, 0, "QNRg3s", arr);
      TH1 *mu = (TH1 *) (*arr)[1];
      if (! mu) continue;
      mu->Fit("pol1","q");
      TF1 *pol1 = (TF1 *) mu->GetListOfFunctions()->FindObject("pol1");
      xWE[i] = pol1->GetParameter(0);
      dxWE[i] = pol1->GetParError(0);
      cout << Form(" : %s : x0 = %9.4f +- %6.4f\t", mu->GetName(), xWE[i], dxWE[i]);
    }
    Double_t dX = (xWE[0] - xWE[1])/2;
    Double_t ddX = TMath::Sqrt(dxWE[0]*dxWE[0] + dxWE[1]*dxWE[1])/2.;
    cout << Form("dWE = %9.4f +/- %6.4f", dX, ddX) << endl;
  }
}
