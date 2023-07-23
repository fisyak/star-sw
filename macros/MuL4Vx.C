/* 
   root.exe lMuDst.C MuL4Vx.C+
*/
#if !defined(__CINT__) || defined(__MAKECINT__)
#include <assert.h>
#include <map>
#include <utility>
#include "Riostream.h"
#include "Rtypes.h"
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
#include "SystemOfUnits.h"
#include "StMuDSTMaker/COMMON/StMuTimer.h"
#include "StMuDSTMaker/COMMON/StMuDebug.h"
#include "StMuDSTMaker/COMMON/StMuDst.h"
#include "StMuDSTMaker/COMMON/StMuEvent.h"
#include "StMuDSTMaker/COMMON/StMuTrack.h"
#include "StMuDSTMaker/COMMON/StMuPrimaryVertex.h"
#include "StMuDSTMaker/COMMON/StMuMcVertex.h"
#include "StMuDSTMaker/COMMON/StMuMcTrack.h"
#include "StMuDSTMaker/COMMON/StMuPrimaryTrackCovariance.h"
#include "StarRoot/TPolynomial.h"
#include "StDcaGeometry.h"
#include "TRSymMatrix.h"
#include "THelixTrack.h"
#include "Names.h"
#include "StBichsel/Bichsel.h"
#define ClassStMessMgr
#define StMessMgr Int_t
#include "StMuDSTMaker/COMMON/StMuDstMaker.h"
#undef  StMessMgr
#undef ClassStMessMgr
#else
#ifndef __MAKECINT__
#define BIT(n)       (1 << (n))
#define SETBIT(n,i)  ((n) |= (1 << i))
#define CLRBIT(n,i)  ((n) &= ~(1 << i))
#define TESTBIT(n,i) ((Bool_t)(((n) & (1 << i)) != 0))
class StMuDstMaker;
#endif
#endif
StMuDstMaker* maker = 0;
enum TrackMatchType {kPositive, kNegative, kTotalSigns};                                     // switch between charges
struct PlotName_t {
  TrackMatchType    k;
  const Char_t *Name;
  const Char_t *Title;
};
struct VarName_t {
  const Char_t *Name;
  const Char_t *Title;
  Int_t nx;
  Double_t xmin, xmax;
  Int_t ny;
  Double_t ymin, ymax;
  Int_t nz;
  Double_t zmin, zmax;
  Double_t  min,  max; // min and max for plots
};
//________________________________________________________________________________
static Int_t _debug = 0;
void SetDebug(Int_t k) {_debug = k;}
Int_t Debug() {return _debug;}
//________________________________________________________________________________
void MuL4Vx(Long64_t nevent = 9999999,
	  //	  const char* file="/star/rcf/test/dev/trs_sl302.ittf/Wed/year_2011/pp500_pileup/rcf10100_90_200evts_Wplus_enu.MuDst.root",
	//	const char* file="MuDstSel.lis",
	const char* file="*.MuDst.root",
	const char* filter="st:MuDst.root",
	const  char* outFile="MuL4Vx.root") {
#if 1
  TFile *fOut = new TFile(outFile,"recreate");
  TH1F  *zVxAll = new TH1F("zVXAll","Z of all reconstructed vertices",210,-210,210);
  TH1F  *zVxAll1 = new TH1F("zVXAll1","Z of the highest rank vertex",210,-210,210);
  TH1F  *zVxAllF = new TH1F("zVXAllF","Z of the highest rank vertex",100,198,202);
  TH1F  *noTracks = new TH1F("noTracks", "no. of tracks in a vertex",100,0,250); 
  TH1F  *noTracks1 = new TH1F("noTracks1", "no. of tracks in the highest rang vertrex",100,0,250); 
  TH1F  *noTracksF = new TH1F("noTracksF", "no. of tracks in the highest rang vertrex with |Z-200| < 5 cm",100,0,250); 
  TH2F  *ZnoTracksF = new TH2F("ZnoTracksF", "(Z-200) versus no. of tracks in the highest rang vertrex with |Z-200| < 2 cm",100,0,250,100,-2,2); 
  TH2F  *CAnWestEast = new TH2F("CAnWestEast","no. of tracks West versus East",150,0,150,150,0,150);
  TH2   *CAZvxZ  = new TH2F("CAZvsZ","Z All from CA vesrsus Z > 10 tracks", 100, 199,201, 100, 197, 202);
  TH2   *CAZWestVsEast  = new TH2F("CAZWestVsEast","ZWest -ZAll vs ZEast - ZAll", 100, -2, 2, 100, -5, 5);
#endif
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
#if 0
				    ,"PrimaryTracks"
				    ,"GlobalTracks"
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
    StEventSummary &summary = muEvent->eventSummary();
    L4CAVertex &L4Vx      = summary.L4Vx ;
    L4CAVertex &L4VxWest  = summary.L4VxWest ;
    L4CAVertex &L4VxEast  = summary.L4VxEast ;
    // cout << " #" << ev;
    //    Int_t referenceMultiplicity = muEvent->refMult(); // get the reference multiplicity
    // cout << " refMult= "<< referenceMultiplicity;
    TClonesArray *PrimaryVertices   = mu->primaryVertices(); 
    Int_t NoPrimaryVertices = PrimaryVertices->GetEntriesFast();  // cout << "\tPrimaryVertices " << NoPrimaryVertices;
#if 0
    TClonesArray *PrimaryTracks    = mu->array(muPrimary);  
    Int_t NoPrimaryTracks = PrimaryTracks->GetEntriesFast();  // cout << "\tPrimaryTracks " << NoPrimaryTracks;
    TClonesArray *GlobalTracks     = mu->array(muGlobal);  
    Int_t NoGlobalTracks = GlobalTracks->GetEntriesFast();        if (Debug()) {cout << "\tGlobalTracks " << NoGlobalTracks;}
    TClonesArray *CovPrimTrack     = mu->covPrimTrack();          if (Debug()) {cout << "\tCovPrimTrack " << CovPrimTrack->GetEntriesFast();}
    TClonesArray *CovGlobTrack     = mu->covGlobTrack();          if (Debug()) {cout << "\tCovGlobTrack " << CovGlobTrack->GetEntriesFast();}
#endif
    for (Int_t l = 0; l < NoPrimaryVertices; l++) {
      StMuPrimaryVertex *Vtx = (StMuPrimaryVertex *) PrimaryVertices->UncheckedAt(l);
      if (! Vtx) continue;
      Int_t NTracks = Vtx->noTracks();
      Double_t Z = Vtx->position().z();
      zVxAll->Fill(Z);
      noTracks->Fill(NTracks);
      if (l) continue;
      zVxAll1->Fill(Z);
      noTracks1->Fill(NTracks);
      if (TMath::Abs(Vtx->position().z() - 200) > 2) continue;
      zVxAllF->Fill(Z);
      noTracksF->Fill(NTracks);
      ZnoTracksF->Fill(NTracks, Z - 200);
      CAnWestEast->Fill(L4VxEast.Const,L4VxWest.Const);
      if (L4Vx.Const < 10) continue;
      CAZvxZ->Fill(Z, L4Vx.Mu);
      CAZWestVsEast->Fill(L4VxEast.Mu -  L4Vx.Mu, L4VxWest.Mu -  L4Vx.Mu);
    }
  }
#if 1
  if (fOut) fOut->Write();
#endif
}



