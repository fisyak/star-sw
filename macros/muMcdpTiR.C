/*
  root.exe muMc.root  muMcdpTiR.C
 */
void muMcdpTiR(const Char_t *charge = "-") {
  TH3F *h3[2] = {0};
  h3[0] = (TH3F *) gDirectory->Get(Form("/Tracks/Global/Rec/All/(%s)/EtapT/dPtiR",charge));
  h3[1] = (TH3F *) gDirectory->Get(Form("/Tracks/Primary/Rec/All/(%s)/EtapT/dPtiR",charge));
  if (! h3[0] || ! h3[1]) return;
  TObjArray *arr = new TObjArray(4);
  TString same;
  TF1 *dpTOverpT = new TF1("dpTOverpT","TMath::Sqrt([0]*[0]+[1]*[1]*x*x+[2]*[2]/(x*x))",0.1,5.0);
  dpTOverpT->SetParameters(1e-2,1e-2,1e-2);
  dpTOverpT->SetLineColor(3);
  TLegend *l = new TLegend(0.15,0.7,0.90xs,0.85);
  for (Int_t k = 0; k < 2; k++) {
    h3[k]->GetDirectory()->cd();
    TH2D *h2 = h3[k]->Project3D("zy");
    h2->FitSlicesY(0, 0, -1, 0, "QNR", arr);
    TH1D *sigma = (TH1D *) (*arr)[2];
    sigma->SetTitle("#sigma(#DeltapT)/pT(%) versus pT for global and primary tracks");
    sigma->SetStats(0);
    sigma->SetMarkerColor(k+1);
    sigma->Draw(same);
    dpTOverpT->SetLineColor(k+1);
    sigma->Fit(dpTOverpT);
    same = "same";
    l->AddEntry(sigma,Form("#sigma(#DeltapT)/pT = %5.2f%% #oplus %5.2f%% #times pT #oplus %5.2f%% / pT => %5.2f%%(@1GeV/c)",
			   100*dpTOverpT->GetParameter(0),100*dpTOverpT->GetParameter(1), 100*dpTOverpT->GetParameter(2), 100*dpTOverpT->Eval(1.0)));
  }
  l->Draw();
}
