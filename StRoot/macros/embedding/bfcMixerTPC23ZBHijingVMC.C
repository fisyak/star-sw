//////////////////////////////////////////////////////////////////////////
// Owner:  Yuri Fisyak
//
// $Id:$
//////////////////////////////////////////////////////////////////////////
// root.exe -q -b -x 'bfcMixerVMC.C(10)'
//#define __NO_DAQ_CLUSTERS__
//#define __TrackingOnly__
//#define __PXL_SLOW_SIM__ 
//#define __IST_SLOW_SIM__ 
//#define __SST_SLOW_SIM__ 
class StBFChain;
StBFChain *Chain = 0, *chain1, *chain2, *chain3, *chain4;
//_____________________________________________________________________
void bfcMixerTPC23ZBHijingVMC(Int_t First, Int_t Last, const Char_t *opt,
			      const Char_t *daqfile,
			      const Char_t *genfile,
			      const Char_t *output="",
			      Int_t RunG=0, const Char_t *triggersC="") {
  if (gClassTable->GetID("TGiant3") >= 0) {
    cout << "bfcMixerTPC23ZBHijingVMC does not intent to run with root4star. Please use root.exe" << endl;
    return;
  }
  //________________________________________________________________________________
  //  gSystem->Load("StFtpcMixerMaker");
  //  StFtpcMixerMaker  *ftpcmixer = new StFtpcMixerMaker("FtpcMixer","daq","trs");
  //________________________________________________________________________________
  // Dynamically link some shared libs1
  gROOT->LoadMacro("bfc.C");
  if (gClassTable->GetID("StBFChain") < 0) Load();
  //______________Create the main chain object______________________________________
  Chain = (StBFChain *) StMaker::New("StBFChain","Embedding");
#if 0
  Chain->SetFlags("TObjTable,nodefault");
#else
  Chain->SetFlags("nodefault");
#endif
  //  StMaker::lsMakers(Chain);
  //________________________________________________________________________________
  TString Opt(opt);
  TString chain1Opt("in,daq,magF,tpcDb,MakeEvent,trgd,TpxRaw,NoAnnotateCL,NoDefault,nooutput");
  chain1 = bfc(-1,chain1Opt,daqfile,0,0,"DAQ");
  //  StMaker::lsMakers(chain1);
  Chain->cd();
  //________________________________________________________________________________
  TString chain2Opt(Form("Vmc,%s,gen_T,geomT,sim_T,CorrZ,nodefault,TpcRS,nooutput",Opt.Data()));
  chain2 = bfc(-1,chain2Opt,genfile,0,0,"MC");
  //  StMaker::lsMakers(chain2);
  StMaker *geant = chain2->Maker("geant");
  Chain->cd();
  TString chain3Opt("noInput,-in,NoInput");
  chain3Opt += ",TpcMixer";
  chain3 = bfc(-1,chain3Opt,0,0,0,"Mixer");
  //  StMaker::lsMakers(chain3);
  Chain->cd();
  //________________________________________________________________________________  
  TString OutputFileName(output);
  if (OutputFileName == "") {
    OutputFileName = gSystem->BaseName(daqfile);;
    OutputFileName.ReplaceAll("*","");
    OutputFileName.ReplaceAll(".daq","");
    //  OutputFileName.Append("_emb.root");
    OutputFileName.Append(".root");
  }
  TString chain4Opt("P2023a,TPC23,McTpcAna,BEmcChkStat,CorrZ,evout");
  chain4Opt += ",noInput,-in,StiCA"; // ,MiniMcMk,McAna,GeantOut
  //  chain4Opt += ",TPC23,TpcHitMover"; // ,evout
  chain4Opt += ",noHistos,noRunco";
  //  chain4Opt += ",picoWrite";
  //  chain4Opt += ",KFVertex";
  chain4 = bfc(-1,chain4Opt,0,OutputFileName,0,"RC");
  //  StMaker::lsMakers(chain4);
  Chain->cd();
  //________________________________________________________________________________
  {
    TDatime t;
    gMessMgr->QAInfo() << Form("Run is started at Date/Time %i/%i",t.GetDate(),t.GetTime()) << endm;
  }
  gMessMgr->QAInfo() << Form("Run on %s in %s",gSystem->HostName(),gSystem->WorkingDirectory()) << endm;
  gMessMgr->QAInfo() << Form("with %s", Chain->GetCVS()) << endm;
  //  TAttr::SetDebug(0);
  Chain->SetAttr(".Privilege",0,"*"                ); 	//All  makers are NOT priviliged
  Chain->SetAttr(".Privilege",1,"StBFChain::*" ); 	//StBFChain is priviliged
  Chain->SetAttr(".Privilege",1,"StIOInterFace::*" ); 	//All IO makers are priviliged
  Chain->SetAttr(".Privilege",1,"StVMCMaker::*"); 	//It is also IO maker
  StMaker::lsMakers(Chain);
  if (StVMCMaker::instance()) {
    StVMCMaker::instance()->SetVxSigma(-1);
    StVMCMaker::instance()->SetAttr("SmearVertex",1); // To smear production vertex accoudingly vertex errors
  }
  Int_t iInit = Chain->Init();
  if (iInit >=  kStEOF) {Chain->FatalErr(iInit,"on init"); return;}
#if defined(__CINT__) && !defined(__MAKECINT__)
  if (TClass::GetClass("StarMCPrimaryGenerator")) { // Print list of input  particles
    if (StarMCPrimaryGenerator::Instance()) {
      StarMCPrimaryGenerator::Instance()->SetDebug(1);
    }
  }
#endif
  if (First <= Last) {
    Chain->EventLoop(First,Last);
    gMessMgr->QAInfo() << "Run completed " << endm;
    gSystem->Exec("date");
  }
}
//________________________________________________________________________________
void bfcMixerTPC23ZBHijingVMC(Int_t Last=1, const Char_t *opt = "HijingAuAu200",
			      const Char_t *daqfile="/hlt/cephfs/daq/2023/211/24211048/st_zerobias_adc_24211048_raw_0000007.daq",
			      const Char_t *genfile="/net/l401/data/scratch2/fisyak/simu/Hijing/AuAu200/hijingAuAu200_1_1000.gener.root",
			      const Char_t *output = "",
			      Int_t RunG=0, const Char_t *triggersC = "") {
  bfcMixerTPC23ZBHijingVMC(1,Last,opt,daqfile,genfile,output,RunG,triggersC);
}
