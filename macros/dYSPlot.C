#if 0
  root.exe MuTpcG.root dYSPlot.C
foreach f (`ls -1d  */*/*/picoTpcG.root`)
  set d = `dirname ${f}`;
  cd ${d}
  root.exe picoTpcG.root dYS.C
  cd -
end
#endif
void dYSPlot() {
  TH3F *h3 = (TH3F*) gDirectory->Get("dYS");
  if (! h3) return;
  TCanvas *c1 = (TCanvas *) gROOT->GetListOfCanvases()->FindObject("c1");
  if (! c1 ) c1 = new TCanvas("c1","c1");
  c1->SetLogz(1);
  TH2  *h2 = (TH2 *) h3->Project3D("zx");
  h2->SetStats(0);
  h2->Draw("colz");
  TString PWD(gSystem->WorkingDirectory());
  Int_t index = PWD.Index("reco/");
  TString Prod = PWD.Data()+index+5;
  TLegend *l0 = new TLegend(0.10,0.8,0.60,0.90);
  l0->AddEntry(h2,Prod.Data());
  l0->Draw();
  h2->FitSlicesY();
  TH1 *h1 = (TH1 *) gDirectory->Get(Form("%s_1",h2->GetName()));
  if (! h1) return;
  cout << "Found " << h1->GetName() << endl;
  h1->Draw("sames");
  TF1 *FW = new TF1("FW","[0]+[1]*TMath::Cos(TMath::Pi()/6*x)",0.5,24.5);
  TF1 *FE = new TF1("FE","[0]+[1]*TMath::Cos(TMath::Pi()/6*x)",0.5,24.5);
  FE->SetLineColor(4);
  TLegend *l = new TLegend(0.1,0.2,0.9,0.4);
  h1->Fit(FW,"er" ,"", 0.5,12.5);
  TLegend *l = new TLegend(0.15,0.15,0.85,0.35);
  l->AddEntry(FW,Form("West %5.2f + %5.2f*cos(30*sector)",FW->GetParameter(0), FW->GetParameter(1)));
  
  h1->Fit(FE,"er+","",12.5,24.5);
  l->AddEntry(FE,Form("East: %5.2f + %5.2f*cos(30*sector)",FE->GetParameter(0), FE->GetParameter(1)));
  l->Draw();
  c1->SaveAs("dYS.png");

  std::ofstream file_("dYS.txt");
  file_ << FW->GetParameter(0) << "," << FW->GetParameter(1) << "," << FE->GetParameter(0) << "," << FE->GetParameter(1) << std::endl;
  file_.close();
}
