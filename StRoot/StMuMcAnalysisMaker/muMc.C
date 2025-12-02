/*
  FPE_OFF
  root.exe -q -b -x 'muMc.C(1e6,"../*MuDst.root")'
*/
void muMc(Int_t N = 1000000, Bool_t rePlot = kTRUE,
	  const Char_t *input = "../*.MuDst.root", 
	  const Char_t *output = "muMc.root", 
	  const Char_t *ChainOpt = "RMuDst,KFPInter,MuMc,quiet,mysql,nodefault,y2023,corrZ") {
#if !defined(__CINT__)
  std::cout << "This code cannot be compiled" << std::endl;
#else
  //  gSystem->SetFPEMask(kInvalid | kDivByZero | kOverflow );
  gROOT->LoadMacro("lMuDst.C");
  Char_t *file = 0;
  if (rePlot) {
    file = gSystem->Which("./",output,kReadPermission);
  }
  if (! file) {
    //    lMuDst(-1,input,"RMuDst,KFPInter,MuMc,quiet,mysql,nodefault",output);
    lMuDst(-1,input,ChainOpt,output);
    StMuMcAnalysisMaker *muMc = StMuMcAnalysisMaker::instance();
    if (muMc) {cout << "MuMcAnalysis has been found" << endl;}
    muMc->SetAttr("TrackPlots",1);
    muMc->SetAttr("PiDPlots",1);
    muMc->SetAttr("VertexPlots",1);
#if 0
    muMc->SetNeta(50);
    muMc->SetEtaMin(-1.5);
    muMc->SetEtaMax(-0.5);
#endif
    //    muMc->SetAttr("StoreCutNTuples",1);
    chain->Init();
    if (N <= 0) return;
    chain->EventLoop(N);
    TFile *f = chain->GetTFile();
    if (f) f->Write();
    StMuMcAnalysisMaker::instance()->Draw();
  } else {
    lMuDst(-1,"","RMuDst,MuMc,mysql,nodefault");
    TFile *f = new TFile(output);
    if (! f) return;
    //    StBFChain *chain = StMaker::GetTopChain();
    chain->SetTFile(f);
    StMuMcAnalysisMaker *muMc = StMuMcAnalysisMaker::instance();
    muMc->SetAttr("TrackPlots",1);
    muMc->SetAttr("VertexPlots",1);
    chain->Init();
#if 1
    StMuMcAnalysisMaker::instance()->Draw();
#else 
    //                                      gp,pp,xx,ii,xy 
    StMuMcAnalysisMaker::instance()->DrawQA( 0, 0, 1, 6, 0); // Tracks_Global_Rec_All_EtapT_dPtiR_zx_1.png;
    StMuMcAnalysisMaker::instance()->DrawQA( 0, 0, 1, 9, 0); // Tracks_Global_Rec_All_EtapT_pDcaXY_zx_1
#endif
  }
  delete [] file;
#endif
  
}
