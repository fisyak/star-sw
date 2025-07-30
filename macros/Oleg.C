void Oleg(Double_t Z = 635, const Char_t *histName = "flux100keVn") {
  TFile *_file0 = TFile::Open("2013/pp510/flux_2013xPythiaPP510.root"); //  Nov 16  2014
  TFile *_file1 = TFile::Open("r2013VMC/r2013VMC.root");
  TFile *_file2 = TFile::Open("r2013VMCTFG25c/r2013VMCTFG25c.root");
  TFile *_file3 = TFile::Open("r2013G3/r2013G3.root");
  TFile *_file4 = TFile::Open("r2022VMC/r2022VMC.root");
  TFile *_file5 = TFile::Open("r2022G3/r2022G3.root");
  TFile *files[6] = {_file0, _file1,  _file2, _file3, _file4, _file5};
  const Char_t *tags[6] = {"2013G3old", "2013VMC",  "2013VMCTFG25c", "2013G3", "2022VMC", "2022G3"};
  Int_t binX = -1;
  TLegend *l = new TLegend(0.5,0.6,0.8,0.9);
  TString same("");
  THStack *hstack = 0; // new THStack("hs",histName);
  for (Int_t i = 1; i < 3; i++) {
    TH2 *flux = (TH2*) files[i]->Get(histName);
    if (binX < 0) {
      binX = flux->GetXaxis()->FindBin(Z);
      hstack = new THStack(Form("S%s",flux->GetName()),Form("%s at Z = %6.1f",flux->GetTitle(),Z));
    }
    TString Title = gSystem->DirName(flux->GetDirectory()->GetName());
    TH1D *proj = flux->ProjectionY(tags[i], binX, binX);
    proj->SetLineColor(i+1);
    proj->SetMarkerColor(i+1);
    proj->SetXTitle("R (cm)");
    //    proj->Draw(same); same = "sames";
    hstack->Add(proj);
    l->AddEntry(proj,tags[i]);
  }
  hstack->Draw("nostack");
  l->Draw();
}
