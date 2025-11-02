#define __UseMagScaleFactor__
#include "kfpAnalysis.C"
void kfpAnalysisB(Int_t N = 10000000, 
		 const Char_t *input = "*.picoDst.root", 
		 const Char_t *output = "Ana.root", const Char_t *triggerSet = "y2021", Bool_t idNdx = kFALSE) {
  kfpAnalysis(N,input,output,triggerSet,idNdx);
}
