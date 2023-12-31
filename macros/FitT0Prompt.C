//   root.exe -q -b ZTMfl0.root  FitT0Prompt.C > & FitT0Prompt.log &
void FitT0Prompt() {
  TH3F *T = gDirectory->Get("T"); 
  if (! T) return;
  gROOT->LoadMacro("lDb.C");
  lDb();
  gROOT->LoadMacro("TpcPrompt.C+");
  T0Fit(T);
} 
