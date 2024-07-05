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
  TH2D *dT = new TH2D("dT","dT(#musec) (West - East) versus Z",420,-210,210,200,-0.1,0.1); 
#if 0
  new St_db_Maker;
  new StMagFMaker;
  new StTpcDbMaker;
#endif
  muDstMko = new StMuDstMaker(0,0,oldf,"","",99999,"MuDstOld"); // no East
  muDstMkn = new StMuDstMaker(0,0,newf,"","",99999,"MuDstNew"); // no West
  chain->AddBefore("db",muDstMko);
  chain->AddBefore("db",muDstMkn);
  StMaker::lsMakers(chain);
  chain->Init();
  StMuDst *oldMuDst = 0;
  StMuDst *newMuDst = 0;
  StMuEvent *oldEv = 0, *newEv = 0;
  Int_t NoGTrkOld = 0, NoGTrkNew = 0;
  Int_t NoPvtxOld = 0, NoPvtxNew = 0;
  Int_t nev = 0;
  Bool_t bothRead = kTRUE;
  Int_t iok = chain->MakeEvent();
  while (! iok) {
    oldMuDst = muDstMko->muDst(); oldMuDst->SetInstance(); oldEv = oldMuDst->event(); NoGTrkOld = oldMuDst->numberOfGlobalTracks(); NoPvtxOld = oldMuDst->numberOfPrimaryVertices(); //cout << "old(West) N global " << NoGTrkOld << endl;
    newMuDst = muDstMkn->muDst(); newMuDst->SetInstance(); newEv = newMuDst->event(); NoGTrkNew = newMuDst->numberOfGlobalTracks(); NoPvtxNew = newMuDst->numberOfPrimaryVertices(); //cout << "new(East) N global " << NoGTrkNew << endl;
    if (oldEv->runId() != newEv->runId()) break;
    if (oldEv->eventId() == newEv->eventId()) {
      nev++;
      if (NoPvtxOld && NoPvtxNew) {
	//      muTbyT(oldMuDst, newMuDst);
	oldMuDst->SetInstance();
	StThreeVectorF xyzW = oldEv->primaryVertexPosition(); //cout << "old(West) Vx " << xyzW << endl;
	newMuDst->SetInstance();
	StThreeVectorF xyzE = newEv->primaryVertexPosition(); //cout << "new(East) Vx " << xyzE << endl;
	StThreeVectorF xyzD = (xyzW - xyzE)/2;
	StThreeVectorF xyzA = (xyzW + xyzE)/2;
	Double_t driftVel = StTpcDb::instance()->DriftVelocity()*1e-6;
	dX->Fill(xyzA.z(),xyzD.x());
	dY->Fill(xyzA.z(),xyzD.y());
	dZ->Fill(xyzA.z(),xyzD.z());
	dT->Fill(xyzA.z(),xyzD.z()/driftVel);
      }
      iok = chain->MakeEvent();
    } else {
      cout << "event " << nev << "\trun = " << oldEv->runId() << "\tevents Old = " << oldEv->eventId() << "\tnew = " << newEv->eventId() 
	   << " has not matched" << endl;
      if (oldEv->eventId() < newEv->eventId()) {
        muDstMko->Clear(); iok = muDstMko->Make();
	if (iok) break;
      } else {
	muDstMkn->Clear(); iok = muDstMkn->Make();
	if (iok) break;
      }
    }
  }
  fOut->Write();
}
