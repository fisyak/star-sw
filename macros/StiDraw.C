/* Draw Sti pull and errors 
    root.exe 'bfc.C(-1,"Sti")'  *2026/*.root 'StiDraw.C("pullYP")'
*/
void StiDraw(const Char_t *opt="pullYP") {
  gROOT->LoadMacro("StiPulls.C+");
  LoopOverHistogr(opt);
}
