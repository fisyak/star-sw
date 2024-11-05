/*
  root.exe -q -b -x 'muMc.C(1e6,"../*MuDst.root")'
*/
void femtoAnalysis(Int_t N = 1000, 
                   const Char_t *input = "~/testData/*",
                   const Char_t *output = "femto.root",
                   const TString beamSpotMode = "2020_5AGeV",
                   int year = 2016,
                   TString flowFileList = "",
                   bool isPico = true) // list of files with centrality and reaction plane, files should be separated with ";"
{
// #if !defined(__CINT__)
//   std::cout << "This code cannot be compiled" << std::endl;
// #else
  //  gSystem->SetFPEMask(kInvalid | kDivByZero | kOverflow );

  gROOT->LoadMacro("lMuDst.C");
  lMuDst(-1,input,"ry2016,RpicoDst,mysql,kfpAna,quiet,nodefault",output);
  

  std::cout << "KFParticleAnalysis: running analysis for the year " << year << "." << std::endl; 
  StKFParticleAnalysisMaker* kfpAnalysis = (StKFParticleAnalysisMaker*) StMaker::GetTopChain()->Maker("KFParticleAnalysis");
  // kfpAnalysis->AnalyseDsPhiPi();
  kfpAnalysis->CollectPIDHistograms();
  kfpAnalysis->CollectTrackHistograms();
  kfpAnalysis->CollectPVHistograms();

#if 1
  kfpAnalysis->AddDecayToReconstructionList( 310);
  kfpAnalysis->AddDecayToReconstructionList( 3122);
  kfpAnalysis->AddDecayToReconstructionList(-3122);
  kfpAnalysis->AddDecayToReconstructionList( 3312);
  kfpAnalysis->AddDecayToReconstructionList(-3312);
  kfpAnalysis->AddDecayToReconstructionList( 3334);
  kfpAnalysis->AddDecayToReconstructionList(-3334);
  kfpAnalysis->AddDecayToReconstructionList(   22);
  kfpAnalysis->AddDecayToReconstructionList(  111);
  kfpAnalysis->AddDecayToReconstructionList(  333);
  kfpAnalysis->AddDecayToReconstructionList(  313);
  kfpAnalysis->AddDecayToReconstructionList( -313);
  kfpAnalysis->AddDecayToReconstructionList(  323);
  kfpAnalysis->AddDecayToReconstructionList( -323);

  kfpAnalysis->AddCandidateToStore(310);
#endif

#if 0
  kfpAnalysis->AddDecayToReconstructionList( 3004); // H3L
  kfpAnalysis->AddDecayToReconstructionList( 3006); // He4L
  kfpAnalysis->AddDecayToReconstructionList( 3008); // H4LL

  kfpAnalysis->AddCandidateToStore(3008);
#endif

#if 0
  kfpAnalysis->AddDecayToReconstructionList( 310);
  kfpAnalysis->AddDecayToReconstructionList( 100321);
  kfpAnalysis->AddDecayToReconstructionList(-100321);
  kfpAnalysis->AddDecayToReconstructionList( 3122);
  kfpAnalysis->AddDecayToReconstructionList(-3122);
  kfpAnalysis->AddDecayToReconstructionList( 3312);
  kfpAnalysis->AddDecayToReconstructionList(-3312);
  kfpAnalysis->AddDecayToReconstructionList( 3334);
  kfpAnalysis->AddDecayToReconstructionList(-3334);
  
  kfpAnalysis->AddDecayToReconstructionList(   22);
  kfpAnalysis->AddDecayToReconstructionList(  111);
  kfpAnalysis->AddDecayToReconstructionList(  333);
  kfpAnalysis->AddDecayToReconstructionList(  313);
  kfpAnalysis->AddDecayToReconstructionList( -313);
  kfpAnalysis->AddDecayToReconstructionList(  323);
  kfpAnalysis->AddDecayToReconstructionList( -323);
  kfpAnalysis->AddDecayToReconstructionList( 3324);
  kfpAnalysis->AddDecayToReconstructionList(-3324);
  
  kfpAnalysis->AddDecayToReconstructionList( 3000);
  kfpAnalysis->AddDecayToReconstructionList( 3001);
#endif

#if 0
  kfpAnalysis->AddDecayToReconstructionList( 3003); // LN
  kfpAnalysis->AddDecayToReconstructionList( 3103); // LNN
  kfpAnalysis->AddDecayToReconstructionList( 3004); // H3L
  kfpAnalysis->AddDecayToReconstructionList( 3005); // H4L
  kfpAnalysis->AddDecayToReconstructionList( 3006); // He4L
  kfpAnalysis->AddDecayToReconstructionList( 3007); // He5L
  kfpAnalysis->AddDecayToReconstructionList( 3012); // H3L->dppi
  kfpAnalysis->AddDecayToReconstructionList( 3013); // H4L->tppi
  
  kfpAnalysis->AddDecayToReconstructionList( 3008); // H4LL
  kfpAnalysis->AddDecayToReconstructionList( 3009); // H4LL
  kfpAnalysis->AddDecayToReconstructionList( 3010); // H5LL
  kfpAnalysis->AddDecayToReconstructionList( 3011); // He6LL
  kfpAnalysis->AddDecayToReconstructionList( 3203); // LLN
  kfpAnalysis->AddDecayToReconstructionList( 3040); // LLNN
  
  kfpAnalysis->AddDecayToReconstructionList( 3016); // H6L->He6pi
  kfpAnalysis->AddDecayToReconstructionList( 3019); // He6L->Li6pi
  kfpAnalysis->AddDecayToReconstructionList( 3022); // He7L->Li7pi
  kfpAnalysis->AddDecayToReconstructionList( 3025); // Li7L->Be7pi

  kfpAnalysis->AddDecayToReconstructionList( 3038); // Li5L->He3 p p pi
  kfpAnalysis->AddDecayToReconstructionList( 3039); // Li6L->He4 p p pi

  kfpAnalysis->AddCandidateToStore(3003);
  kfpAnalysis->AddCandidateToStore(3103);

  kfpAnalysis->AddCandidateToStore(3004);
  kfpAnalysis->AddCandidateToStore(3005);
  kfpAnalysis->AddCandidateToStore(3006);
  kfpAnalysis->AddCandidateToStore(3007);
  kfpAnalysis->AddCandidateToStore(3012);
  kfpAnalysis->AddCandidateToStore(3013);
  
  kfpAnalysis->AddCandidateToStore(3008);
  kfpAnalysis->AddCandidateToStore(3009);
  kfpAnalysis->AddCandidateToStore(3010);
  kfpAnalysis->AddCandidateToStore(3011);
  kfpAnalysis->AddCandidateToStore(3203);
  kfpAnalysis->AddCandidateToStore(3040);
  
  kfpAnalysis->AddCandidateToStore(3016);
  kfpAnalysis->AddCandidateToStore(3019);
  kfpAnalysis->AddCandidateToStore(3022);
  kfpAnalysis->AddCandidateToStore(3025);
  
  kfpAnalysis->AddCandidateToStore(3038);
  kfpAnalysis->AddCandidateToStore(3039);
#endif

#if 0
  kfpAnalysis->AddDecayToReconstructionList( 3014); // H4L->ddpi
  kfpAnalysis->AddDecayToReconstructionList( 3015); // H5L->tdpi
  kfpAnalysis->AddDecayToReconstructionList( 3017); // H6L->ttpi
  kfpAnalysis->AddDecayToReconstructionList( 3018); // He5L->He3dpi
  kfpAnalysis->AddDecayToReconstructionList( 3020); // He6L->He3tpi
  kfpAnalysis->AddDecayToReconstructionList( 3021); // He6L->He4dpi
  kfpAnalysis->AddDecayToReconstructionList( 3023); // He7L->He4tpi
  kfpAnalysis->AddDecayToReconstructionList( 3024); // Li6L->2He3pi
  kfpAnalysis->AddDecayToReconstructionList( 3026); // Li7L->He4He3pi
  kfpAnalysis->AddDecayToReconstructionList( 3027); // Li8L->2He4pi
#endif

#if 0
  kfpAnalysis->AddDecayToReconstructionList(3030); //H2Sp  -> d+   pi+
  kfpAnalysis->AddDecayToReconstructionList(3031); //H3Sp  -> t+   pi+
  kfpAnalysis->AddDecayToReconstructionList(3032); //He3Sp -> He3+ pi+
  kfpAnalysis->AddDecayToReconstructionList(3033); //He4Sp -> He4+ pi+
  kfpAnalysis->AddDecayToReconstructionList(3034); //He6Sp -> He6+ pi+
  kfpAnalysis->AddDecayToReconstructionList(3035); //Li6Sp -> Li6+ pi+
  kfpAnalysis->AddDecayToReconstructionList(3036); //Li7Sp -> Li7+ pi+
  kfpAnalysis->AddDecayToReconstructionList(3037); //Be7Sp -> Be7+ pi+
#endif

#if 0
  kfpAnalysis->AddDecayToReconstructionList( 3122);
  kfpAnalysis->AddDecayToReconstructionList( 1003004);
  kfpAnalysis->AddDecayToReconstructionList( 1003005);
  kfpAnalysis->AddDecayToReconstructionList( 1003006);
  kfpAnalysis->AddDecayToReconstructionList( 1003007);

  kfpAnalysis->AddCandidateToStore( 1003004);
  kfpAnalysis->AddCandidateToStore( 1003005);
  kfpAnalysis->AddCandidateToStore( 1003006);
  kfpAnalysis->AddCandidateToStore( 1003007);
#endif

#if 0
  kfpAnalysis->AddDecayToReconstructionList(113);
  kfpAnalysis->AddDecayToReconstructionList(313);
  kfpAnalysis->AddDecayToReconstructionList(-313);
  kfpAnalysis->AddDecayToReconstructionList(333);

  kfpAnalysis->AddDecayToReconstructionList(2114);
  kfpAnalysis->AddDecayToReconstructionList(2224);

  kfpAnalysis->AddDecayToReconstructionList(100001); //dpi-
  kfpAnalysis->AddDecayToReconstructionList(100002); //dpi+
  kfpAnalysis->AddDecayToReconstructionList(100003); //tpi-
  kfpAnalysis->AddDecayToReconstructionList(100004); //tpi+
  kfpAnalysis->AddDecayToReconstructionList(100005); //He3pi-
  kfpAnalysis->AddDecayToReconstructionList(100006); //He3pi+
  kfpAnalysis->AddDecayToReconstructionList(100007); //He4pi-
  kfpAnalysis->AddDecayToReconstructionList(100008); //He4pi+
  // kfpAnalysis->AddDecayToReconstructionList(100009); //He6pi-
  // kfpAnalysis->AddDecayToReconstructionList(100010); //He6pi+
  // kfpAnalysis->AddDecayToReconstructionList(100011); //Li6pi-
  // kfpAnalysis->AddDecayToReconstructionList(100012); //Li6pi+
  // kfpAnalysis->AddDecayToReconstructionList(100013); //Li7pi-
  // kfpAnalysis->AddDecayToReconstructionList(100014); //Li7pi+
  // kfpAnalysis->AddDecayToReconstructionList(100015); //Be7pi-
  // kfpAnalysis->AddDecayToReconstructionList(100016); //Be7pi+
  kfpAnalysis->AddDecayToReconstructionList(110001); //dK- 
  kfpAnalysis->AddDecayToReconstructionList(110002); //dK+ 
  kfpAnalysis->AddDecayToReconstructionList(110003); //tK- 
  kfpAnalysis->AddDecayToReconstructionList(110004); //tK+ 
  kfpAnalysis->AddDecayToReconstructionList(110005); //He3K-
  kfpAnalysis->AddDecayToReconstructionList(110006); //He3K+
  kfpAnalysis->AddDecayToReconstructionList(110007); //He4K-
  kfpAnalysis->AddDecayToReconstructionList(110008); //He4K+
  // kfpAnalysis->AddDecayToReconstructionList(110009); //He6K-
  // kfpAnalysis->AddDecayToReconstructionList(110010); //He6K+
  // kfpAnalysis->AddDecayToReconstructionList(110011); //Li6K-
  // kfpAnalysis->AddDecayToReconstructionList(110012); //Li6K+
  // kfpAnalysis->AddDecayToReconstructionList(110013); //Li7K-
  // kfpAnalysis->AddDecayToReconstructionList(110014); //Li7K+
  // kfpAnalysis->AddDecayToReconstructionList(110015); //Be7K-
  // kfpAnalysis->AddDecayToReconstructionList(110016); //Be7K+
  // kfpAnalysis->AddDecayToReconstructionList(200001); //pp  
  kfpAnalysis->AddDecayToReconstructionList(200002); //dp  
  kfpAnalysis->AddDecayToReconstructionList(200003); //tp  
  kfpAnalysis->AddDecayToReconstructionList(200004); //He3p
  kfpAnalysis->AddDecayToReconstructionList(200005); //He4p
  // kfpAnalysis->AddDecayToReconstructionList(200006); //He6p
  // kfpAnalysis->AddDecayToReconstructionList(200007); //Li6p
  // kfpAnalysis->AddDecayToReconstructionList(200008); //Li7p
  // kfpAnalysis->AddDecayToReconstructionList(200009); //Be7p

  // kfpAnalysis->AddDecayToReconstructionList( 3122);
  // kfpAnalysis->AddDecayToReconstructionList(1003003);
  // kfpAnalysis->AddCandidateToStore( 1003003);
#endif

  chain->Init();

  if(isPico)
  {
    StKFParticleInterface::instance()->CleanLowPVTrackEvents();
//     StKFParticleInterface::instance()->UseHFTTracksOnly();
  }
  
  StKFParticleInterface::instance()->SetSoftKaonPIDMode();
  StKFParticleInterface::instance()->SetSoftTofPidMode();


//   StKFParticleInterface::instance()->SetChiPrimaryMaxCut(5.e3);
  StKFParticleInterface::instance()->SetChiPrimaryCut(18.f);
  // StKFParticleInterface::instance()->SetChiPrimaryCutFragments(0.f); // TODO
  StKFParticleInterface::instance()->SetChiPrimaryCutFragments(18.f);   // TODO
  // StKFParticleInterface::instance()->SetSecondaryCuts(3.f, 5.f, 0.f);   // TODO

  StKFParticleInterface::instance()->SetMaxDistanceBetweenParticlesCut(1);
  StKFParticleInterface::instance()->SetLCut(0.f);
  
  StKFParticleInterface::instance()->SetChiPrimaryCut2D(0);
  StKFParticleInterface::instance()->SetChi2Cut2D(3);
  StKFParticleInterface::instance()->SetLdLCut2D(5.f); // TODO
  // StKFParticleInterface::instance()->SetLdLCut2D(0); // TODO
  
  StKFParticleInterface::instance()->SetChi2CutXiOmega(3);
  StKFParticleInterface::instance()->SetChi2TopoCutXiOmega(3);
  StKFParticleInterface::instance()->SetLdLCutXiOmega(5);  
  
  StKFParticleInterface::instance()->SetChi2CutCharmManybodyDecays(3);
  StKFParticleInterface::instance()->SetChi2TopoCutCharmManybodyDecays(3);
  StKFParticleInterface::instance()->SetLdLCutCharmManybodyDecays(5);

  StKFParticleInterface::instance()->SetBeamSpot(beamSpotMode);

  StPicoDstMaker* maker = (StPicoDstMaker *) StMaker::GetTopChain()->Maker("PicoDst");
  if (! maker) return;
  maker->SetStatus("*",1);
  TChain *tree = maker->chain();
  Long64_t nentries = tree->GetEntries();
  if (nentries <= 0) return;
  Long64_t nevent = N;
  nevent = TMath::Min(nevent,nentries);
  cout << nentries << " events in chain " << nevent << " will be read." << endl;
//   new StGoodTrigger("y2014");
//   chain->SetAttr(".Privilege",1,"StPicoDstMaker::*")
  chain->EventLoop(nevent);

// #endif
  
}
