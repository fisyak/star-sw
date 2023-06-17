void GoodVx4dEdx() {
  TSeqCollection *files = gROOT->GetListOfFiles();
  if (! files) return;
  TIter next(files);
  TFile *f = 0;
  while ( (f = (TFile *) next()) ) { 
    TString F(f->GetName());
    F.ReplaceAll(".root","");
    TH3F *PVxyz = (TH3F *) f->Get("PVxyz");
    TH3F *PVxyzC = (TH3F *) f->Get("PVxyzC");
    TH2F *aTdEdxF = (TH2F *) f->Get("aTdEdxF");
    Double_t NV = 0; if (PVxyz) NV = PVxyz->GetEntries();
    Double_t NC = 0; if (PVxyz) NC = PVxyz->GetEntries();
    Double_t Npos = 0; 
    Double_t Nneg = 0;
    if (aTdEdxF) {
      TAxis *ax = aTdEdxF->GetXaxis();
      Int_t nb = ax->GetNbins();
      ax->SetRange(1, nb/2);
      Nneg = aTdEdxF->ProjectionX()->GetEntries();
      ax->SetRange(nb/2+1,nb);
      Npos = aTdEdxF->ProjectionX()->GetEntries();
    }
    cout << Form("%-30s:\tNo. of Primary Vertices = %10.5gM,\tGood = %10.5gM,\tNo. positive tracks = %10.5gM,\tnegative tracks = %10.5gM",
		 F.Data(),  NV/1e6, NC/1e6, Npos/1e6, Nneg/1e6) << endl;
  }
}
