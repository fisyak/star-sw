///  root.exe 'lMuDst.C(-1,"","StEvent,Stu,MuDst,mysql,tpcDb,detDb,TFGdbOpt,CorrZ,magF,nodefault")' 'MuEbyE.C+("7p7GeV_EastOff/*/*/*.MuDst.root","7p7GeV_WestOff/*/*/*.MuDst.root","EbyE7p7GeV.root")'

#if ! defined(__CINT__) && ! defined(__CLING__)
#include "StBFChain/StBFChain.h"
#include "StMuDSTMaker/COMMON/StMuDst.h"
#include "StMuDSTMaker/COMMON/StMuEvent.h"
#include "StMuDSTMaker/COMMON/StMuDstMaker.h"
#include "StTpcDb/StTpcDb.h"
#include "TNtuple.h"
#include "TTree.h"
#include "TChain.h"
#include "StDetectorDbMaker/St_beamInfoC.h"
#include "StDetectorDbMaker/St_starTriggerDelayC.h"
#else
class StMuDstMaker;
#endif
StMuDstMaker *muDstMko = 0;
StMuDstMaker *muDstMkn = 0;
//void *muTbyT(StMuDst *oldMuDst, StMuDst *newMuDst);
struct BPoint_t {
  Float_t dT, freq, DV, run, trigOff, time;//
};
const Char_t *vName = "dT:freq:DV:run:trigOff: time";
BPoint_t BPoint;
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
  TNtuple *FitP = new TNtuple("FitP","dT versus run",vName);
  TH2D *dX = new TH2D("dX","dX (West - East) versus Z; Z ; dX ",420,-210,210,400,-2.,2.); 
  TH2D *dY = new TH2D("dY","dY (West - East) versus Z; Z ; dY ",420,-210,210,400,-2.,2.); 
  TH2D *dZ = new TH2D("dZ","dZ (West - East) versus Z; Z ; dZ ",420,-210,210,400,-2.,2.); 
  TH2D *dT = new TH2D("dT","dT(#musec) (West - East) versus Z ; Z ; dT",420,-210,210,1000,-0.5,0.5); 
  TH2D *dXY2[2] = {new TH2D("dXY2W","dY versus dX of the second vertex (West) ; dX2 ; dY2",400,-2,2,400,-2,2),
		   new TH2D("dXY2E","dY versus dX of the second vertex (East) ; dX2 ; dY2",400,-2,2,400,-2,2)};
  TH1D *dZ2[2] = {new TH1D("dZ2W","dZ of the second vertex (West) ; dZ2",400,-2,2),
		  new TH1D("dZ2E","dZ of the second vertex (East) ; dZ2",400,-2,2)};
  muDstMko = new StMuDstMaker(0,0,oldf,"","",99999,"MuDstOld"); // no East
  muDstMkn = new StMuDstMaker(0,0,newf,"","",99999,"MuDstNew"); // no West
  StMuDstMaker *muDstMk[2] = {muDstMko, muDstMkn};
  StBFChain *chain = (StBFChain *) StMaker::GetTopChain();
  chain->AddBefore("db",muDstMko);
  chain->AddBefore("db",muDstMkn);
  chain->SetDEBUG(1);
  StMaker::lsMakers();
  chain->Init();
  TChain *chainO = muDstMko->chain();
  TChain *chainN = muDstMkn->chain();
  //  chainO->AddFriend(chainN );
  chainN->BuildIndex("MuEvent.mRunInfo.mRunId","MuEvent.mEventInfo.mId");
  StMuDst *oldMuDst = 0;
  StMuDst *newMuDst = 0;
  StMuEvent *oldEv = 0, *newEv = 0;
  Int_t NoGTrkOld = 0, NoGTrkNew = 0;
  Int_t NoPvtxOld = 0, NoPvtxNew = 0;
  static Int_t _debug = 0;
  Int_t nev = 0;
  Long64_t nentries = chainO->GetEntries();
  if (nentries <= 0) return;
  Int_t ok = chain->MakeEvent();
  Bool_t FXT = St_beamInfoC::instance()->IsFixedTarget();
  UInt_t NPV[2];
  while (! ok) {
    if (_debug) cout << "================================================================================" << endl;
    oldMuDst = muDstMko->muDst(); oldMuDst->SetInstance(); oldEv = oldMuDst->event(); if (_debug) {cout << "Old:"; oldMuDst->Print();}
    if (! oldEv) goto NEXT_EVENT;
    
    newMuDst = muDstMkn->muDst(); newMuDst->SetInstance(); newEv = newMuDst->event(); if (_debug) {cout << "New:"; newMuDst->Print();}
    if (! newEv || oldEv->runId() != newEv->runId() || oldEv->eventId() != newEv->eventId()) {
      muDstMkn->Clear(); ok = muDstMkn->Make(oldEv->runId(), oldEv->eventId()); 
      if (ok) continue;
      newMuDst = muDstMkn->muDst(); newMuDst->SetInstance(); newEv = newMuDst->event(); if (_debug) {cout << "New:"; newMuDst->Print();}
      if (! newEv) goto NEXT_EVENT;
    }
    if (oldEv->runId() == newEv->runId() && oldEv->eventId() == newEv->eventId()) {
      nev++;
      if (nev%1000 == 1) {
	cout << "event " << nev << "\trun = " << oldEv->runId() << "\tevents Old = " << oldEv->eventId() << "\tnew = " << newEv->eventId() 
	     << " has matched" << endl;
      }
      // Require only one primary vertex in Z range [195,205];
      StMuDst *MuDst[2] = {oldMuDst, newMuDst};
      Bool_t okVX = kTRUE;
      StMuPrimaryVertex *BestVtx[2] = {0,0};
      for (Int_t k = 0; k < 2; k++) {// old new == West (EastOff)  East (WestOff)
	MuDst[k]->SetInstance();
	UInt_t NPV = MuDst[k]->numberOfPrimaryVertices();
	if (! NPV) continue;
	if (! MuDst[k]->primaryVertex(0)) continue;
	// Find vertex with highest multiplicity (ignore rank)
	Int_t MaxnoTracks = 0;
	for(UInt_t  iPV=0; iPV < NPV; iPV++) {
	  StMuPrimaryVertex *Vtx = MuDst[k]->primaryVertex(iPV);
	  if (! Vtx) continue;
	  Int_t noTracks = Vtx->noTracks();
	  if (noTracks > MaxnoTracks) {
	    BestVtx[k] = Vtx;
	    MaxnoTracks = noTracks;
	  }
	}
	if (! BestVtx[k]) continue;
	Double_t Z_ref = BestVtx[k]->position().z();
	for(UInt_t  iPV=0; iPV < NPV; iPV++) {
	  StMuPrimaryVertex *Vtx = MuDst[k]->primaryVertex(iPV);
	  if (! Vtx) continue;
	  if (Vtx == BestVtx[k]) continue;
	  if (_debug) Vtx->Print();
	  if (TMath::Abs(Vtx->position().z() - Z_ref) < 5.0) {
	    dXY2[k]->Fill(Vtx->position().x() - BestVtx[k]->position().x(), Vtx->position().y() - BestVtx[k]->position().y());
	    dZ2[k]->Fill(Vtx->position().z() - BestVtx[k]->position().z());
	    okVX = kFALSE;
	  }
	}
      }
      if (okVX && BestVtx[0] &&  BestVtx[1]) {
	StThreeVectorF xyzD = (BestVtx[0]->position() - BestVtx[1]->position())/2; 
	StThreeVectorF xyzA = (BestVtx[0]->position() + BestVtx[1]->position())/2;
	Double_t driftVel = StTpcDb::instance()->DriftVelocity()*1e-6;
	dX->Fill(xyzA.z(),xyzD.x());
	dY->Fill(xyzA.z(),xyzD.y());
	dZ->Fill(xyzA.z(),xyzD.z());
	BPoint.dT = xyzD.z()/driftVel;
	BPoint.freq = StTpcDb::instance()->Electronics()->samplingFrequency();
	BPoint.DV = driftVel;
	BPoint.trigOff = St_starTriggerDelayC::instance()->TrigT0();
	BPoint.run = muDstMko->GetRunNumber();
	BPoint.time = muDstMko->GetDateTime().Convert();
	dT->Fill(xyzA.z(),BPoint.dT);
	FitP->Fill(&BPoint.dT);
      }
    } else {
      cout << "event " << nev << "\trun = " << oldEv->runId() << "\tevents Old = " << oldEv->eventId() << "\tnew = " << newEv->eventId() 
	   << " has not matched" << endl;
    }
  NEXT_EVENT:
    ok = chain->MakeEvent();
  }
  fOut->Write();
}
