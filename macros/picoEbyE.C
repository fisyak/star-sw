//  root.exe 'lMuDst.C(-1,"","StEvent,Stu,MuDst,PicoDeps,mysql,tpcDb,detDb,TFGdbOpt,CorrZ,magF,nodefault")' picoEbyE.C+

#if ! defined(__CINT__) && ! defined(__CLING__)
#include "StBFChain/StBFChain.h"
#include "StPicoEvent/StPicoDst.h"
#include "StPicoEvent/StPicoEvent.h"
#include "StPicoEvent/StPicoTrack.h"
#include "StPicoDstMaker/StPicoDstMaker.h"
#include "StTpcDb/StTpcDb.h"
#include "TMath.h"
#include "TTree.h"
#include "TChain.h"
#include "TSystem.h"
#include "TVector3.h"
#include "TLorentzVector.h"
#include "StDetectorDbMaker/St_beamInfoC.h"
#else
class StPicoDstMaker;
#endif
StPicoDstMaker *picoDstMko = 0;
StPicoDstMaker *picoDstMkn = 0;
//________________________________________________________________________________
void picoEbyE(const Char_t *oldF = "old.root", const Char_t *newF = "new.root",
	      const Char_t *TreeName = "PicoDst", const Char_t *outHist = "picoEbyE.root") {
  Int_t _debug = 0;
  TString fileO(outHist);
  if (fileO == "") {
    fileO = gSystem->BaseName(oldF);
    fileO.ReplaceAll("picoDst.","");
  }
  TFile *fOut = new TFile(fileO,"recreate");
  TH1F *dX = new TH1F("dX","dX (New - Old)", 400,-2.,2.); 
  TH1F *dY = new TH1F("dY","dY (New - Old)", 400,-2.,2.); 
  TH1F *dZ = new TH1F("dZ","dZ (New - Old)", 400,-2.,2.); 
  TH2F *XON = new TH2F("XON","X (New vs Old)", 400,  -1.5,   0.5, 400,  -1.5,   0.5); 
  TH2F *YON = new TH2F("YON","Y (New vs Old)", 400,  -3.0,   1.0, 400,  -3.0,  -1.0); 
  TH2F *ZON = new TH2F("ZON","Z (New vs Old)", 400, 199.0, 201.0, 400, 199.0, 201.0); 
  TH2F *noPTrkON = new TH2F("noPTrkON","No. primary tracks Old vs. New",500,0.5,500.5, 500, 0.5, 500.5);
  TH2F *noPRTrkON = new TH2F("noPRTrkON","No. primary tracks recorded Old vs. New",500,0.5,500.5, 500, 0.5, 500.5);
  TH2F *noPROld = new TH2F("noPROld","No. primary tracks recorded versus No. primary tracks Old",500,0.5,500.5, 500, 0.5, 500.5);
  TH2F *noPRNew = new TH2F("noPRNew","No. primary tracks recorded versus No. primary tracks New",500,0.5,500.5, 500, 0.5, 500.5);
  picoDstMko = new StPicoDstMaker(2,oldF); picoDstMko->SetName("rPicoOld"); 
  picoDstMkn = new StPicoDstMaker(2,newF); picoDstMkn->SetName("rPicoNew"); 
  TH2F *ypT[2];
  ypT[0] = new TH2F("ypTO","pTL10 versus Ycms for negative particles (Old)", 40, -2.0, 2.0, 100, -2.0, 2.0); 
  ypT[1] = new TH2F("ypTN","pTL10 versus Ycms for negative particles (New)", 40, -2.0, 2.0, 100, -2.0, 2.0); 
  StBFChain *chain = (StBFChain *) StMaker::GetTopChain();
  chain->AddBefore("db",picoDstMko);
  chain->AddBefore("db",picoDstMkn);
  chain->SetDEBUG(1);
  StMaker::lsMakers();
  chain->Init();
  TChain *chainO = picoDstMko->chain();
  TChain *chainN = picoDstMkn->chain();
  //  chainO->AddFriend(chainN );
  chainN->BuildIndex("Event.mRunId","Event.mEventId");
  StPicoDst *oldPicoDst = 0;
  StPicoDst *newPicoDst = 0;
  StPicoEvent *oldEv = 0, *newEv = 0;
  Int_t NoGTrkOld = 0, NoGTrkNew = 0;
  Int_t NoPvtxOld = 0, NoPvtxNew = 0;
  Int_t nev = 0;
  Long64_t nentries = chainO->GetEntries();
  if (nentries <= 0) return;
  Int_t ok = 0;
  while (1) {
    Int_t ok = chain->MakeEvent();
    if (ok) break;
    oldPicoDst = picoDstMko->picoDst(); if (_debug) {cout << "Old:"; oldPicoDst->print();}
    oldEv = oldPicoDst->event();
    newPicoDst = picoDstMkn->picoDst(); if (_debug) {cout << "New:"; newPicoDst->print();}
    newEv = newPicoDst->event(); 
    if (oldEv->runId() != newEv->runId() || oldEv->eventId() != newEv->eventId()) {
      picoDstMkn->Clear(); 
      Int_t okN = picoDstMkn->Make(oldEv->runId(), oldEv->eventId()); 
      if (okN) continue;
      if (oldEv->runId() != newEv->runId() || oldEv->eventId() != newEv->eventId()) {
	cout << "event " << nev << "\trun = " << oldEv->runId() << "\tevents Old = " << oldEv->eventId() << "\tnew = " << newEv->eventId() 
	     << " has not matched" << endl;
	continue;
      }
      if (_debug) { cout << "New:"; newPicoDst->print();}
      newEv = newPicoDst->event();
    }
    nev++;
    if (nev%1000 == 1) {
      cout << "event " << nev << "\trun = " << oldEv->runId() << "\tevents Old = " << oldEv->eventId() << "\tnew = " << newEv->eventId() 
	   << " has matched" << endl;
    }
    TVector3 xyzOld = oldEv->primaryVertex(); 
    TVector3 xyzNew = newEv->primaryVertex(); 
    TVector3 xyzD = 0.5*(xyzNew - xyzOld);
    TVector3 xyzA = 0.5*(xyzNew + xyzOld);
    Double_t driftVel = StTpcDb::instance()->DriftVelocity()*1e-6;
    dX->Fill(xyzD.x());
    dY->Fill(xyzD.y());
    dZ->Fill(xyzD.z());
    XON->Fill(xyzOld.x(), xyzNew.x());
    YON->Fill(xyzOld.y(), xyzNew.y());
    ZON->Fill(xyzOld.z(), xyzNew.z());
    noPTrkON->Fill(oldEv->numberOfPrimaryTracks(), newEv->numberOfPrimaryTracks());
    noPRTrkON->Fill(oldPicoDst->numberOfPrimaryTracksRecorded(), newPicoDst->numberOfPrimaryTracksRecorded());
    noPROld->Fill(oldEv->numberOfPrimaryTracks(), oldPicoDst->numberOfPrimaryTracksRecorded());
    noPRNew->Fill(newEv->numberOfPrimaryTracks(), newPicoDst->numberOfPrimaryTracksRecorded());
    StPicoDst *PicoDsts[2] = {oldPicoDst, newPicoDst};
    Float_t Ycms = St_beamInfoC::instance()->Ycms();
    static Double_t piMass = 0.13956995;
    for (Int_t dst = 0; dst < 2; dst++) {
      UInt_t NoTracks = PicoDsts[dst]->numberOfTracks();
      for (UInt_t i = 0; i < NoTracks; i++) {
	StPicoTrack* track =  PicoDsts[dst]->track(i);
	if (! track->isPrimary()) continue;
	if (track->charge() > 0) continue;
	if (track->nHits() < 15) continue;
	TVector3 pMom = track->pMom();
	TLorentzVector p4;
	p4.SetXYZM(pMom.x(),pMom.y(),pMom.z(), piMass);
	Double_t pTL10 = TMath::Log10(p4.Perp());
	Double_t rapidity = p4.Rapidity() - Ycms;
	ypT[dst]->Fill(rapidity, pTL10);
      }
    }
  }
  fOut->Write();
}
