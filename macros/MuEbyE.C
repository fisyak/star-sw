///  root.exe 'lMuDst.C(-1,"","StEvent,Stu,MuDst,picoEvt,mysql,tpcDb,detDb,TFGdbOpt,CorrZ,magF,nodefault")' 'MuEbyE.C+("7p7GeV_EastOff/*/*/*.MuDst.root","7p7GeV_WestOff/*/*/*.MuDst.root","EbyE7p7GeV.root")'
///  root.exe 'lMuDst.C(-1,"","StEvent,Stu,MuDst,picoEvt,mysql,tpcDb,detDb,TFGdbOpt,CorrZ,magF,nodefault")' 'MuEbyE.C+("14p5GeV_2019_EastOff/118/20118006/st_physics_20118006_raw_1500002.MuDst.root","14p5GeV_2019_WestOff/118/20118006/st_physics_20118006_raw_3000001.MuDst.root","EbyE14p5GeV.root")'
//________________________________________________________________________________
// foreach W (`ls -1d */*WestOff/???`) 
//  set E = `echo ${W} | sed -e 's/West/East/'`
//  set B = `echo ${W} | sed -e 's/WestOff//'`
//  set C = `echo ${B} | sed -e 's/\//_/g'`
//  root.exe -q -b 'lMuDst.C(-1,"","StEvent,Stu,MuDst,picoEvt,mysql,tpcDb,detDb,CorrZ,magF,nodefault")' 'MuEbyE.C+("'${W}'/*/*.MuDst.root","'${E}'/*/*.MuDst.root","EbyE'${C}'.root")' >& ${C}.log & 
// end
//________________________________________________________________________________
#if ! defined(__CINT__) && ! defined(__CLING__) || defined(__MAKECINT__)
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
class StMuDst;
#endif
StMuDstMaker *muDstMko = 0;
StMuDstMaker *muDstMkn = 0;
//void *muTbyT(StMuDst *oldMuDst, StMuDst *newMuDst);
StMuDst *oldMuDst = 0;
StMuDst *newMuDst = 0;
StMuEvent *oldEv = 0, *newEv = 0;
Int_t NoGTrkOld = 0, NoGTrkNew = 0;
Int_t NoPvtxOld = 0, NoPvtxNew = 0;
TFile *fOut   = 0;
static Int_t _debug = 0;
struct BPoint_t {
  Float_t dT, freq, DV, run, trigOff, time;//
};
const Char_t *vName = "dT:freq:DV:run:trigOff: time";
BPoint_t BPoint;
//________________________________________________________________________________
void Fill(const Char_t *out = 0) {
  static TNtuple *FitP = 0;
  static TH2F *dX      = 0;
  static TH2F *dY      = 0;
  static TH2F *dZ      = 0;
  static TH2F *dT      = 0;
  static TH2F *dXY2[2];
  static TH1F *dZ2[2];
  static TH2F *XZ[2];
  static TH2F *YZ[2];
  if (out) {
    TString fileO(out);
    fOut   = new TFile(fileO,"recreate");
    FitP = new TNtuple("FitP","dT versus run",vName);
    dX      = new TH2F("dX","dX (West - East) versus Z; Z ; dX ",420,-210,210,400,-2.,2.); 
    dY      = new TH2F("dY","dY (West - East) versus Z; Z ; dY ",420,-210,210,400,-2.,2.); 
    dZ      = new TH2F("dZ","dZ (West - East) versus Z; Z ; dZ ",420,-210,210,400,-5.,5.); 
    dT      = new TH2F("dT","dT(#musec) (West - East) versus Z ; Z ; dT",420,-210,210,1000,-0.5,0.5); 
    XZ[0]   = new TH2F("XZW","X versus Z (West) ; Z ; X",420,-210,210,400,-2,2);
    XZ[1]   = new TH2F("XZE","X versus Z (East) ; Z ; X",420,-210,210,400,-2,2);
    YZ[0]   = new TH2F("YZW","Y versus Z (West) ; Z ; Y",420,-210,210,400,-2,2);
    YZ[1]   = new TH2F("YZE","Y versus Z (East) ; Z ; Y",420,-210,210,400,-2,2);
    dXY2[0] = new TH2F("dXY2W","dY versus dX of the second vertex (West) ; dX2 ; dY2",400,-2,2,400,-2,2);
    dXY2[1] = new TH2F("dXY2E","dY versus dX of the second vertex (East) ; dX2 ; dY2",400,-2,2,400,-2,2);
    dZ2[0]  = new TH1F("dZ2W","dZ of the second vertex (West) ; dZ2",400,-2,2);
    dZ2[1]  = new TH1F("dZ2E","dZ of the second vertex (East) ; dZ2",400,-2,2);
    return;
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
      if (_debug) {cout << k << ":\t"; Vtx->Print();}
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
      if (_debug) {cout << k << ": Extra\t"; Vtx->Print();}
      if (TMath::Abs(Vtx->position().z() - Z_ref) < 5.0) {
	dXY2[k]->Fill(Vtx->position().x() - BestVtx[k]->position().x(), Vtx->position().y() - BestVtx[k]->position().y());
	dZ2[k]->Fill(Vtx->position().z() - BestVtx[k]->position().z());
	okVX = kFALSE;
      }
    }
  }
  if (okVX && BestVtx[0] &&  BestVtx[1]) {
    StThreeVectorF xyzD = (BestVtx[0]->position() - BestVtx[1]->position())/2; 
    if (_debug) {
      cout << "West\t"; BestVtx[0]->Print();
      cout << "East\t"; BestVtx[1]->Print();
      cout << "Diff:\t" << xyzD << endl;
    }
    for (Int_t k = 0; k < 2; k++) {
      XZ[k]->Fill(BestVtx[k]->position().z(), BestVtx[k]->position().x());
      YZ[k]->Fill(BestVtx[k]->position().z(), BestVtx[k]->position().y());
    }
    if (TMath::Abs(xyzD.z()) > 5.0) return;
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
}
//________________________________________________________________________________
void MuEbyE(const Char_t *oldf="/gpfs01/star/subsys-tpc/fisyak/reco/2018/EastOff/st_physics_adc_19116021_raw_1000030.MuDst.root",
	    const Char_t *newf="/gpfs01/star/subsys-tpc/fisyak/reco/2018/WestOff/st_physics_adc_19116021_raw_1000030.MuDst.root",
	    const Char_t *out = "MuTbyT.root") {
  Fill(out);
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
  Int_t nev = 0;
  Long64_t nentries = chainO->GetEntries();
  if (nentries <= 0) return;
#if 0
  Int_t ok = chain->MakeEvent();
#endif
  //  Bool_t FXT = St_beamInfoC::instance()->IsFixedTarget();
  UInt_t NPV[2];
#if 0
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
	Fill();
      }
    } else {
      cout << "event " << nev << "\trun = " << oldEv->runId() << "\tevents Old = " << oldEv->eventId() << "\tnew = " << newEv->eventId() 
	   << " has not matched" << endl;
    }
  NEXT_EVENT:
    ok = chain->MakeEvent();
  }
#else
  while (1) {
    Int_t ok = chain->MakeEvent();
    if (ok) break;
    oldMuDst = muDstMko->muDst(); if (_debug) {cout << "Old:"; oldMuDst->Print("B");}
    oldEv = oldMuDst->event();
    newMuDst = muDstMkn->muDst(); if (_debug) {cout << "New:"; newMuDst->Print("B");}
    newEv = newMuDst->event(); 
    if (oldEv->runId() != newEv->runId() || oldEv->eventId() != newEv->eventId()) {
      muDstMkn->Clear(); 
      Int_t okN = muDstMkn->Make(oldEv->runId(), oldEv->eventId()); 
      if (okN) continue;
      if (oldEv->runId() != newEv->runId() || oldEv->eventId() != newEv->eventId()) {
	cout << "event " << nev << "\trun = " << oldEv->runId() << "\tevents Old = " << oldEv->eventId() << "\tnew = " << newEv->eventId() 
	     << " has not matched" << endl;
	continue;
      }
      newMuDst = muDstMkn->muDst(); if (_debug) {cout << "New:"; newMuDst->Print("B");}
      newEv = newMuDst->event();
    }
    nev++;
    if (nev%1000 == 1) {
      cout << "event " << nev << "\trun = " << oldEv->runId() << "\tevents Old = " << oldEv->eventId() << "\tnew = " << newEv->eventId() 
	   << " has matched" << endl;
    }
    Fill();
  }
#endif
  fOut->Write();
}
