void Multiplicity(const Char_t *files = "2*/st*.root", const Char_t *path = "Particles/KFParticlesFinder/Particles/Ks/Parameters/Multiplicity") {
  TDirIter Dir(files);
  Char_t *file = 0;
  Char_t *file1 = 0;
  while ((file = (Char_t *) Dir.NextFile())) {
    TFile *f = new TFile (file);
    TH1 *h1 = (TH1 *) gDirectory->Get(path);
    if (! h1) {cout << file << " histogram " << path << " is missing" << endl;}
    else {
      cout << file << " Mean of " << path << " is " << h1->GetMean() << endl;
    }
    delete f;
  }
}
