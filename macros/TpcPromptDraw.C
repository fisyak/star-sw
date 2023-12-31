//   root.exe 'Chain.C+("*/*/*.root","TpcHit")' 'TpcPromptDraw.C(tChain)'
//   root.exe -q -b ZTMfl0.root 'Chain.C+("*/*/*.root","TpcHit")' 'TpcPromptDraw.C(tChain)' > & TpcPromptDraw.log &
void TpcPromptDraw(TChain *tChain) {
  gROOT->LoadMacro("TpcPrompt.C+");
  Draw(tChain);
} 
