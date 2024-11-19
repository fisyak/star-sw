TH2D *GetEntriesTP(TProfile2D *hist) {// entries in TProfile2D
  if (! hist) return 0;
  Int_t nx = hist->GetNbinsX(); 
  Int_t ny = hist->GetNbinsY();
  TAxis *ar = hist->GetXaxis();
  TAxis *az = hist->GetYaxis();
  TString name(hist->GetName());
  name += "_Cont";
  TH2D *newhist = new TH2D(name.Data(),hist->GetTitle(),
			   nx,hist->GetXaxis()->GetXmin(),hist->GetXaxis()->GetXmax(),
			   ny,hist->GetYaxis()->GetXmin(),hist->GetYaxis()->GetXmax());
  for (int i = 1; i <= nx; i++) {
    for (int j = 1; j <= ny; j++) {
      Int_t bin = newhist->GetBin(i,j);
      Double_t v = hist->GetBinEntries(bin);
      newhist->SetBinContent(i,j,v);
    }
  }
  return newhist;
}
//`________________________________________________________________________________
void GetEntries(const Char_t *histName = "PVxyzC") {
  TSeqCollection *files = gROOT->GetListOfFiles();
  if (! files) return;
  TIter next(files);
  TFile *f = 0;
  while ( (f = (TFile *) next()) ) { 
    TString F(f->GetName());
    TH1 *h = (TH1 *) f->Get(histName);
    if (! h) continue;
    cout << F.Data() << " histogram " << histName << "\t has " << h->GetEntries() << " entries" << endl;
  }
}
