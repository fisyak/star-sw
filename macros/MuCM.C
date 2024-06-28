/* Check Last Hit points near Central Membrane */
//   root.exe -q -b -x lMuDst.C 'MuCM.C+(9999999,"*/*/*MuDst.root")' >& MuCM2.log &
#include "Rtypes.h"
//#include "Riostream.h"
#include "TROOT.h"
#include "TSystem.h"
#include "TH2.h"
#include "TH3.h"
#include "TF1.h"
#include "TProfile.h"
#include "TProfile3D.h"
#include "TTree.h"
#include "TChain.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TClassTable.h"
#include "TFile.h"
#include "TChain.h"
#include "TString.h"
#include "TMath.h"
#include "StMuDSTMaker/COMMON/StMuDst.h"
#include "StMuDSTMaker/COMMON/StMuEvent.h"
#include "StMuDSTMaker/COMMON/StMuTrack.h"
#include "StMuDSTMaker/COMMON/StMuPrimaryVertex.h"
#include "StMuDSTMaker/COMMON/StMuMcVertex.h"
#include "StMuDSTMaker/COMMON/StMuMcTrack.h"
#include "StMuDSTMaker/COMMON/StMuPrimaryTrackCovariance.h"
#include "StMuDSTMaker/COMMON/StMuDstMaker.h"
StMuDstMaker* maker = 0;
Int_t _debug = 0;
//________________________________________________________________________________
Bool_t Accept(const StMuTrack *gTrack = 0) {
  if (! gTrack)            return kFALSE;
  //  if (! gTrack->idTruth()) return kFALSE;
  if (! gTrack->charge())  return kFALSE;
  if (  gTrack->flag() < 100 ||  gTrack->flag()%100 == 11) return kFALSE; // bad fit or short track pointing to EEMC
  if (  gTrack->flag() > 1000) return kFALSE;  // pile up track in TPC
  if (  gTrack->nHitsFit() < 10) return kFALSE;
  //  if (  gTrack->qaTruth() < 90) return kFALSE;
  return kTRUE;
}
//________________________________________________________________________________
void MuCM(Long64_t nevent = 9999999,
	  //	  const char* file="/star/rcf/test/dev/trs_sl302.ittf/Wed/year_2011/pp500_pileup/rcf10100_90_200evts_Wplus_enu.MuDst.root",
	  //	const char* file="MuDstSel.lis",
	  const char* file="*/*/*.MuDst.root",
	  const char* filter="st:MuDst.root",
	  const  char* outFile="MuCM2.root") {
  TFile *fOut = new TFile(outFile,"recreate");
  TH1F *NoPrimTr = new TH1F("NoPrimTr", "no. of primary tracks",500,0.5,500.5);
  TH1F *NoGlobTr = new TH1F("NoGlobTr", "no. of primary tracks",2000,-0.5,1999.5);
  TH1F *ZLastHitP = new TH1F("ZLastHitP","Z of the last hit on primary track : Z",440,-220,220); 
  TH1F *ZLastHitG = new TH1F("ZLastHitG","Z of the last hit on global track : Z",440,-220,220); 
  TH2F *XYLastHitP   = new TH2F("XYLastHitP","Y versus X for the last hit on primary track with |ZlastHit| < 3 : X : Y", 200, -200., 200., 200, -200., 200.);
  TH2F *XYLastHitG   = new TH2F("XYLastHitG","Y versus X for the last hit on global track with |ZlastHit| < 3 : X : Y",  200, -200., 200., 200, -200., 200.);
  StMuDebug::setLevel(0);  
  maker = new StMuDstMaker(0,0,"",file,filter,1e9);   // set up maker in read mode
  //                       0,0                        this mean read mode
  //                           dir                    read all files in this directory
  //                               file               bla.lis real all file in this list, if (file!="") dir is ignored
  //                                    filter        apply filter to filenames, multiple filters are separated by ':'
  //                                          10      maximum number of file to read
  maker->SetStatus("*",0);
  const Char_t *ActiveBranches[] = {"MuEvent"
				    ,"PrimaryVertices"
				    ,"PrimaryTracks"
				    ,"GlobalTracks"
#if 0
				    ,"CovPrimTrack"
				    ,"CovGlobTrack"
				    ,"StStMuMcVertex"
				    ,"StStMuMcTrack"
#endif
  };
  Int_t Nb = sizeof(ActiveBranches)/sizeof(Char_t *);
  for (Int_t i = 0; i < Nb; i++) maker->SetStatus(ActiveBranches[i],1); // Set Active braches
  StMuDebug::setLevel(0);  
  TChain *tree = maker->chain();
  if (! tree) return;
  Long64_t nentries = tree->GetEntries();
  nevent = TMath::Min(nevent,nentries);
  cout << nentries << " events in chain " << nevent << " will be read." << endl;
  //  if (nentries < 100) return;
  tree->SetCacheSize(-1);        //by setting the read cache to -1 we set it to the AutoFlush value when writing
  tree->SetCacheLearnEntries(1); //one entry is sufficient to learn
  tree->SetCacheEntryRange(0,nevent);

  for (Long64_t ev = 0; ev < nevent; ev++) {
    if (maker->Make()) break;
    StMuDst* mu = maker->muDst();   // get a pointer to the StMuDst class, the class that points to all the data
    if (ev%1000 == 0) cout << "Read event\t" << ev << endl;
    StMuEvent* muEvent = mu->event(); // get a pointer to the class holding event-wise information
    // cout << " #" << ev;
    //    Int_t referenceMultiplicity = muEvent->refMult(); // get the reference multiplicity
    // cout << " refMult= "<< referenceMultiplicity;
    TClonesArray *PrimaryVertices   = mu->primaryVertices(); 
    Int_t NoPrimaryVertices = PrimaryVertices->GetEntriesFast();  // cout << "\tPrimaryVertices " << NoPrimaryVertices;
    TClonesArray *PrimaryTracks    = mu->array(muPrimary);  
    Int_t NoPrimaryTracks = PrimaryTracks->GetEntriesFast();  // cout << "\tPrimaryTracks " << NoPrimaryTracks;
    TClonesArray *GlobalTracks     = mu->array(muGlobal);  
    Int_t NoGlobalTracks = GlobalTracks->GetEntriesFast();        if (_debug) {cout << "\tGlobalTracks " << NoGlobalTracks;}
    TClonesArray *CovPrimTrack     = mu->covPrimTrack();          if (_debug) {cout << "\tCovPrimTrack " << CovPrimTrack->GetEntriesFast();}
#if 0
    TClonesArray *CovGlobTrack     = mu->covGlobTrack();          if (_debug) {cout << "\tCovGlobTrack " << CovGlobTrack->GetEntriesFast();}
#endif
    NoPrimTr->Fill(NoPrimaryTracks);
    NoGlobTr->Fill(NoGlobalTracks);
    for (Int_t k = 0; k < NoGlobalTracks; k++) {
      StMuTrack *gTrack = (StMuTrack *) GlobalTracks->UncheckedAt(k);
      if (! Accept(gTrack)) continue;
      const StThreeVectorF &xyzL = gTrack->lastPoint();
      ZLastHitG->Fill(xyzL.z());
      if (TMath::Abs(xyzL.z()) > 1.0) continue;
      XYLastHitG->Fill(xyzL.x(),xyzL.y());
    }
    for (Int_t k = 0; k < NoPrimaryTracks; k++) {
      StMuTrack *pTrack = (StMuTrack *) PrimaryTracks->UncheckedAt(k);
      if (! Accept(pTrack)) continue;
      if (pTrack->vertexIndex() != 0) continue;
      const StThreeVectorF &xyzL = pTrack->lastPoint();
      ZLastHitP->Fill(xyzL.z());
      if (TMath::Abs(xyzL.z()) > 1.0) continue;
      XYLastHitP->Fill(xyzL.x(),xyzL.y());
    }
  }
#if 1
  if (fOut) fOut->Write();
#endif
}



