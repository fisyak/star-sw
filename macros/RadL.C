/*
foreach f (`ls -1d Geanttino*.root`)
  set d = RadL/`echo ${f} | sed -e 's/Geanttino//' -e 's/.root//'`
  echo "${d}"
  if (! -d ${d}) mkdir -p ${d}
  cd ${d}
  root.exe ../../${f} RadL.C
  cd -
end
 */
void RadL() {// plot radl and absl from Gianttino run
  gStyle->SetOptStat(0);
  TString Set(gDirectory->GetName());
  Bool_t iFXT = kFALSE;
  if (Set.Contains("FXT")) iFXT = kTRUE;
  Set.ReplaceAll(".root","");
  Set.ReplaceAll("Geanttino","");
  TString Histname[12] = {"RadLetaR","RadLIetaR","AbsLetaR","AbsLIetaR","RadLXY","RadLIXY","AbsLXY","AbsLIXY","RadLRZ","RadLIRZ","AbsLRZ","AbsLIRZ"};
  for (Int_t i = 0; i < 12; i+=2) {
    //    TString Title(Form("%s_%s",Histname[i].Data(),Set.Data()));
    TString Title = Histname[i];
    TCanvas *c = new TCanvas(Title,Title,200,10,800,800);
    c->SetLogz(1);
    TProfile2D *h = (TProfile2D *) gDirectory->Get(Histname[i]);
    if (! h) continue;
    if (Histname[i].Contains("etaR")) {
      h->GetYaxis()->SetRange(1,50);
      if (iFXT) h->GetXaxis()->SetRange(1,100);
    }
    if (Histname[i].Contains("Z") && iFXT) {
      h->GetXaxis()->SetRange(2701,4400);
    }
    if (Histname[i].Contains("RadL")) {
      h->SetMinimum(1e-3);
      h->SetMaximum(2e-1);
    } else {
      h->SetMinimum(1e-4);
      h->SetMaximum(2e-2);
    }
    h->Draw("colz");
    c->Update();
    c->SaveAs(".png");
  }
}
	   
