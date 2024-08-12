///  root.exe 'lMuDst.C(-1,"","StEvent,Stu,MuDst,mysql,tpcDb,detDb,TFGdbOpt,CorrZ,magF,nodefault")' 'MuEbyE.C+("7p7GeV_EastOff/*/*/*.MuDst.root","7p7GeV_WestOff/*/*/*.MuDst.root","EbyE7p7GeV.root")'

#if ! defined(__CINT__) && ! defined(__CLING__)
#include "StBFChain/StBFChain.h"
#include "StMuDSTMaker/COMMON/StMuDst.h"
#include "StMuDSTMaker/COMMON/StMuEvent.h"
#include "StMuDSTMaker/COMMON/StMuDstMaker.h"
#include "StTpcDb/StTpcDb.h"
#include "TTree.h"
#include "TChain.h"
#else
class StMuDstMaker;
#endif
StMuDstMaker *muDstMko = 0;
StMuDstMaker *muDstMkn = 0;
//void *muTbyT(StMuDst *oldMuDst, StMuDst *newMuDst);
void MuEbyE(
#if 0
	       const Char_t *oldf="/gpfs02/eic/ayk/STAR/reco/MuDst/AuAu_200_production_2016/ReversedFullField/P16ij/2016/125/17125034/st_physics_adc_17125034_raw_1000007.MuDst.root", 
	       const Char_t *newf="/gpfs01/star/pwg/fisyak/Embedding/2016/piNmTsq5PerCentZ6cm/st_physics_adc_17125034_raw_1000007.MuDst.root",
#else
	       const Char_t *oldf="/gpfs01/star/subsys-tpc/fisyak/reco/2018/EastOff/st_physics_adc_19116021_raw_1000030.MuDst.root",
	       const Char_t *newf="/gpfs01/star/subsys-tpc/fisyak/reco/2018/WestOff/st_physics_adc_19116021_raw_1000030.MuDst.root",
#endif
	       const Char_t *out = "MuTbyT.root") {
  TString fileO(out);
  if (fileO == "") {
    fileO = gSystem->BaseName(oldf);
    fileO.ReplaceAll("MuDst.","");
  }
  TFile *fOut = new TFile(fileO,"recreate");
  TH2D *dX = new TH2D("dX","dX (West - East) versus Z",420,-210,210,400,-2.,2.); 
  TH2D *dY = new TH2D("dY","dY (West - East) versus Z",420,-210,210,400,-2.,2.); 
  TH2D *dZ = new TH2D("dZ","dZ (West - East) versus Z",420,-210,210,400,-2.,2.); 
  TH2D *dT = new TH2D("dT","dT(#musec) (West - East) versus Z",420,-210,210,500,-0.25,025); 
#if 0
  new St_db_Maker;
  new StMagFMaker;
  new StTpcDbMaker;
#endif
  muDstMko = new StMuDstMaker(0,0,oldf,"","",99999,"MuDstOld"); // no East
  muDstMkn = new StMuDstMaker(0,0,newf,"","",99999,"MuDstNew"); // no West
  StBFChain *chain = (StBFChain *) StMaker::GetTopChain();
  chain->AddBefore("db",muDstMko);
  chain->AddBefore("db",muDstMkn);
  chain->SetDEBUG(1);
  StMaker::lsMakers();
  chain->Init();
  TChain *chainO = muDstMko->chain();
  TChain *chainN = muDstMkn->chain();
  //  chainO->AddFriend(chainN );
  //  chainN->BuildIndex("MuEvent.mRunInfo.mRunId","MuEvent.mEventInfo.mId");
  StMuDst *oldMuDst = 0;
  StMuDst *newMuDst = 0;
  StMuEvent *oldEv = 0, *newEv = 0;
  Int_t NoGTrkOld = 0, NoGTrkNew = 0;
  Int_t NoPvtxOld = 0, NoPvtxNew = 0;
  Int_t nev = 0;
  Long64_t nentries = chainO->GetEntries();
  if (nentries <= 0) return;
  Int_t ok = 0;
  while (1) {
    Int_t ok = chain->MakeEvent();
    if (ok) break;
    oldMuDst = muDstMko->muDst(); oldMuDst->SetInstance(); oldEv = oldMuDst->event(); NoGTrkOld = oldMuDst->numberOfGlobalTracks(); NoPvtxOld = oldMuDst->numberOfPrimaryVertices();
    if (! oldEv) continue;
    StThreeVectorF xyzW = oldEv->primaryVertexPosition(); //cout << "old(West) Vx " << xyzW << endl;
    newMuDst = muDstMkn->muDst(); newMuDst->SetInstance();
    newEv = newMuDst->event(); 
    if (! newEv || oldEv->runId() != newEv->runId() || oldEv->eventId() != newEv->eventId()) {
      muDstMkn->Clear(); Int_t okN = muDstMkn->Make(oldEv->runId(), oldEv->eventId()); if (okN) continue;
      newMuDst->event();
      if (! newEv) continue;
    }
    NoGTrkNew = newMuDst->numberOfGlobalTracks(); NoPvtxNew = newMuDst->numberOfPrimaryVertices(); //cout << "new(East) N global " << NoGTrkNew << endl;
    if (oldEv->runId() == newEv->runId() && oldEv->eventId() == newEv->eventId()) {
      nev++;
      if (nev%100 == 1) {
	cout << "event " << nev << "\trun = " << oldEv->runId() << "\tevents Old = " << oldEv->eventId() << "\tnew = " << newEv->eventId() 
	     << " has matched" << endl;
      }
      if (NoPvtxOld && NoPvtxNew) {
	StThreeVectorF xyzE = newEv->primaryVertexPosition(); //cout << "new(East) Vx " << xyzE << endl;
	StThreeVectorF xyzD = (xyzW - xyzE)/2;
	StThreeVectorF xyzA = (xyzW + xyzE)/2;
	Double_t driftVel = StTpcDb::instance()->DriftVelocity()*1e-6;
	dX->Fill(xyzA.z(),xyzD.x());
	dY->Fill(xyzA.z(),xyzD.y());
	dZ->Fill(xyzA.z(),xyzD.z());
	dT->Fill(xyzA.z(),xyzD.z()/driftVel);
      }
    } else {
      cout << "event " << nev << "\trun = " << oldEv->runId() << "\tevents Old = " << oldEv->eventId() << "\tnew = " << newEv->eventId() 
	   << " has not matched" << endl;
    }
  }
  fOut->Write();
}
