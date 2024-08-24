/*
  root.exe lMuDst.C MuTbyT.C+ MuDstTbyT.C
  root.exe lMuDst.C MuTbyT.C+ 'MuDstTbyT.C("14p5GeV_EastOff/094/20094101/hlt_20094101_10_01_000.MuDst.root","14p5GeV_WestOff/094/20094101/hlt_20094101_10_01_000.MuDst.root","14p5GeV_20094101.root")'
  root.exe 'MuDstTbyT.C("14p5GeV_EastOff/094/20094101/hlt_20094101_10_01_000.MuDst.root","14p5GeV_WestOff/094/20094101/hlt_20094101_10_01_000.MuDst.root","14p5GeV_20094101.root")'
*/
// /hlt/cephfs/reco/DEV2WE2/2019/RF root.exe lMuDst.C MuTbyT.C+ 'MuDstTbyT.C("14p5GeV_EastOff/*/*/*MuDst.root","14p5GeV_WestOff/*/*/*MuDst.root","14p5GeV.root")' 

#if ! defined(__CINT__) && ! defined(__CLING__)
#include "StMuDSTMaker/COMMON/StMuDst.h"
#include "StMuDSTMaker/COMMON/StMuEvent.h"
#include "StMuDSTMaker/COMMON/StMuDstMaker.h"
#include "StTpcDb/StTpcDb.h"
#else
class StMuDstMaker;
#endif
StMuDstMaker *muDstMko = 0;
StMuDstMaker *muDstMkn = 0;
//void *muTbyT(StMuDst *oldMuDst, StMuDst *newMuDst);
void MuDstTbyT(
#if 0
	       const Char_t *oldf="/gpfs02/eic/ayk/STAR/reco/MuDst/AuAu_200_production_2016/ReversedFullField/P16ij/2016/125/17125034/st_physics_adc_17125034_raw_1000007.MuDst.root", 
	       const Char_t *newf="/gpfs01/star/pwg/fisyak/Embedding/2016/piNmTsq5PerCentZ6cm/st_physics_adc_17125034_raw_1000007.MuDst.root",
#else
	       const Char_t *oldf="/gpfs01/star/subsys-tpc/fisyak/reco/2018/EastOff/st_physics_adc_19116021_raw_1000030.MuDst.root",
	       const Char_t *newf="/gpfs01/star/subsys-tpc/fisyak/reco/2018/WestOff/st_physics_adc_19116021_raw_1000030.MuDst.root",
#endif
	       const Char_t *out = "MuTbyT.root") {
  const Char_t *copt = "StEvent,Stu,MuDst,mysql,tpcDb,detDb,TFGdbOpt,CorrZ,magF,nodefault";
  gROOT->LoadMacro("bfc.C");
  TString Chain(copt);
  TString STAR_VERSION(gSystem->Getenv("STAR_VERSION"));
  if (STAR_VERSION == ".DEV2" || STAR_VERSION.Contains("TFG")) {
    Chain += ",quiet,TMVARank";
    //    gSystem->AddIncludePath(" -D__TFG__VERSION__");
  }
  bfc(-1,Chain,"",0,0);
  
  TString fileO(out);
  if (fileO == "") {
    fileO = gSystem->BaseName(oldf);
    fileO.ReplaceAll("MuDst.","");
  }
  TFile *fOut = new TFile(fileO,"recreate");
  TH2D *dX = new TH2D("dX","dX (West - East) versus Z",420,-210,210,200,-1.,1.); 
  TH2D *dY = new TH2D("dY","dY (West - East) versus Z",420,-210,210,200,-1.,1.); 
  TH2D *dZ = new TH2D("dZ","dZ (West - East) versus Z",420,-210,210,200,-1.,1.); 
  TH2D *dT = new TH2D("dT","dT(#musec) (West - East) versus Z",420,-210,210,1000,-0.5,0.5); 
#if 0
  new St_db_Maker;
  new StMagFMaker;
  new StTpcDbMaker;
#endif
  muDstMko = new StMuDstMaker(0,0,oldf,"","",99999,"MuDstOld"); // no East
  muDstMkn = new StMuDstMaker(0,0,newf,"","",99999,"MuDstNew"); // no West
  StMaker::lsMakers();
  chain->AddBefore("db",muDstMko);
  chain->AddBefore("db",muDstMkn);
  chain->SetDEBUG(1);
  StMaker::lsMakers();
  chain->Init();
  StMuDst *oldMuDst = 0;
  StMuDst *newMuDst = 0;
  StMuEvent *oldEv = 0, *newEv = 0;
  Int_t NoGTrkOld = 0, NoGTrkNew = 0;
  Int_t NoPvtxOld = 0, NoPvtxNew = 0;
  Int_t nev = 0;
  Int_t ok = chain->MakeEvent();
  //  cout << "Start Loop" << endl;
  Bool_t FXT = St_beamInfoC::instance()->IsFixedTarget();
  while (! ok) {
    //    cout << "Checks events " << endl;
    oldMuDst = muDstMko->muDst(); oldMuDst->SetInstance(); oldEv = oldMuDst->event(); NoGTrkOld = oldMuDst->numberOfGlobalTracks(); NoPvtxOld = oldMuDst->numberOfPrimaryVertices(); //cout << "old(West) N global " << NoGTrkOld << endl;
    newMuDst = muDstMkn->muDst(); newMuDst->SetInstance(); newEv = newMuDst->event(); NoGTrkNew = newMuDst->numberOfGlobalTracks(); NoPvtxNew = newMuDst->numberOfPrimaryVertices(); //cout << "new(East) N global " << NoGTrkNew << endl;
    if (! oldEv && ! newEv) {
      ok = chain->MakeEvent();
    } else if ( ! oldEv) {
      muDstMko->Clear(); ok = muDstMko->Make();
      //      cout << "old event are 0 => ok " << ok << endl;
    } else if ( ! newEv) {
      muDstMkn->Clear(); ok = muDstMkn->Make();
      //      cout << "new event are 0 => ok " << ok << endl;
    } else {
      //    cout << "Old run = " << oldEv->runId() << "\tNew run " << newEv->runId() << endl;
      if (oldEv->runId() == newEv->runId() && oldEv->eventId() == newEv->eventId()) {
	nev++;
	if (nev%1000 == 1) {
	  cout << "event " << nev << "\trun = " << oldEv->runId() << "\tevents Old = " << oldEv->eventId() << "\tnew = " << newEv->eventId() 
	       << " has matched" << endl;
	}
	// Require only one primary vertex in Z range [195,205];
	StMuDstMaker *muDstMk[2] = {muDstMko, muDstMkn};
	StMuDst *MuDst[2] = {oldMuDst, newMuDst};
	Int_t NoPvtx[2] = {NoPvtxOld, NoPvtxNew};
	if (NoPvtxOld && NoPvtxNew) {
	  Bool_t okVX = kTRUE;
	  StMuPrimaryVertex *BestVtx[2] = {0,0};
	  for (Int_t k = 0; k < 2; k++) {// old new 
	    MuDst[k]->SetInstance();
	    Int_t NPV = MuDst[k]->numberOfPrimaryVertices(); // cout << "k = " << k << " NPV = " << NPV << endl;
	    if (! FXT) {
	      StMuPrimaryVertex *Vtx = MuDst[k]->primaryVertex(0);
	      BestVtx[k] = Vtx;
	      continue;
	    } else {
	      for(UInt_t  iPV=0; iPV < NPV; iPV++) {
		StMuPrimaryVertex *Vtx = MuDst[k]->primaryVertex(iPV);
		if (TMath::Abs(Vtx->position().z() - 200) < 5.0) {
		  if (BestVtx[k]) {
		    okVX = kFALSE;
		    break;
		  }
		  // cout << k << "\t"; Vtx->Print();
		  BestVtx[k] = Vtx;
		  // cout << "xyz[" << k << "] = " << BestVtx[k]->position() << endl;
		}
	      }
	      if (! okVX) break;
	    }
	  }
	  if (BestVtx[0] &&  BestVtx[1]) {
	    // cout << "0\t" << BestVtx[0]->position() << endl;
	    // cout << "1\t" << BestVtx[1]->position() << endl;
	    StThreeVectorF xyzD = (BestVtx[0]->position() - BestVtx[1]->position())/2; 
	    StThreeVectorF xyzA = (BestVtx[0]->position() + BestVtx[1]->position())/2;
	    Double_t driftVel = StTpcDb::instance()->DriftVelocity()*1e-6;
	    dX->Fill(xyzA.z(),xyzD.x());
	    dY->Fill(xyzA.z(),xyzD.y());
	    dZ->Fill(xyzA.z(),xyzD.z());
	    dT->Fill(xyzA.z(),xyzD.z()/driftVel);
	  }
	}
	ok = chain->MakeEvent();
      } else {
	cout << "event " << nev << "\trun = " << oldEv->runId() << "\tevents Old = " << oldEv->eventId() << "\tnew = " << newEv->eventId() 
	     << " has not matched" << endl;
	if (oldEv->runId() < newEv->runId() || (oldEv->runId() == newEv->runId() & oldEv->eventId() < newEv->eventId())) {
	  muDstMko->Clear(); ok = muDstMko->Make();
	  continue;
	} else {
	  muDstMkn->Clear(); ok = muDstMkn->Make();
	  continue;
	}
      }
    }
  }
  fOut->Write();
}
