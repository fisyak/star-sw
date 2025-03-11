#define __ASK__
#ifdef __ASK__
#include "Ask.h"
#endif
class StIOMaker;
class StEvent;
class StUKey;
StIOMaker *makers[2] = {0};
StEvent   *events[2] = {0};
//________________________________________________________________________________
void RunTbyT(Int_t nevents=999,
	     const char *eventFile1="/star/data98/reco/AuAu200_production/FullField/eval_Sti/2010/030/11030018/st_physics_11030018_raw_1020001.event.root",
	     //"./old/st_physics_11035026_raw_2010001.event.root",
	     const char *eventFile2="/star/data99/reco/AuAu200_production/FullField/eval_Stv/2010/030/11030018/st_physics_11030018_raw_1020001.event.root",
	     //"./new/st_physics_11035026_raw_2010001_1_200.event.root",
	     const char* tFile="TbyT.root") {
  gROOT->LoadMacro("bfc.C");
  TString Chain("StEvent,StiLib,detDb,StarMagField,magF,tpcDb,mysql,nodefault");
  bfc(-1,Chain.Data(),0,0,tFile);
  gSystem->Load("StTbyTMaker");
  //  StTbyTMaker::SetHitMatch(kTRUE);
  cout << "Job will run on    File: " << eventFile1 << endl;
  cout << "Corresponding new  File: " << eventFile2 << endl;
  gSystem->Load("StIOMaker");
  // 1st IOMaker, for tpt file
  makers[0] = new StIOMaker("IO1","r",eventFile1);//,"bfcTree");
  chain->AddBefore("db",makers[0]);
  // 2nd IOMaker, for ittf file
  makers[1] = new StIOMaker("IO2","r",eventFile2);//,"bfcTree");
  chain->AddBefore("db",makers[1]);
  StTbyTMaker*  goodStuff      = new StTbyTMaker;
  
  goodStuff->SetActive(kFALSE);
  //  chain->SetDEBUG(2);
  // now execute the chain member functions
  StMaker::lsMakers(chain);
  chain->PrintInfo();
  Int_t initStat = chain->Init(); // This should call the Init() method in ALL makers
  if (initStat) chain->Fatal(initStat, "during Init()");
  StUKey    ukey[2];
  //  if (nevents > 0) chain->EventLoop(1,nevents);
  Int_t iMake = chain->MakeEvent();
  if (iMake) return 1;;
  for (Int_t ev = 0; ev < nevents; ev++) {
    if ( StTbyTMaker::EventMatch()) return;
    if (goodStuff->Make()) return;
#ifdef __ASK__
    if (! gROOT->IsBatch()) {
      if (Ask()) return;
    } else {_debugAsk = 0;}
#endif
  }
}
