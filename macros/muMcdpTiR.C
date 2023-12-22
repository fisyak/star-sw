void muMcdpTiR() {
  TH3F *h3[2] = {0};
  h3[0] = (TH3F *) gDirectory->Get("/Tracks/Global/Rec/All/(-)/EtapT/dPtiR");
  h3[1] = (TH3F *) gDirectory->Get("/Tracks/Primary/Rec/All/(-)/EtapT/dPtiR");
  if (! h3[0] || ! h3[1]) return;
  TObjArray *arr = new TObjArray(4);
  TString same;
  for (Int_t k = 0; k < 2; k++) {
    h3[k]->GetDirectory()->cd();
    TH2D *h2 = h3[k]->Project3D("zy");
    h2->FitSlicesY(0, 0, -1, 0, "QNR", arr);
    TH1D *sigma = (TH1D *) (*arr)[2];
    sigma->SetMarkerColor(k+1);
    sigma->Draw(same);
    same = "same";
  }
}
