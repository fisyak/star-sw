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
#include "KFParticle/KFVertex.h"
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
//static Double_t fgzFXT = 199.63;
static Double_t fgzFXT = 199.934;

static Double_t fgyFXT =   -2.0;
//________________________________________________________________________________
void MuL4Vx(Long64_t nevent = 9999999,
	  //	  const char* file="/star/rcf/test/dev/trs_sl302.ittf/Wed/year_2011/pp500_pileup/rcf10100_90_200evts_Wplus_enu.MuDst.root",
	//	const char* file="MuDstSel.lis",
	const char* file="*.MuDst.root",
	const char* filter="st:MuDst.root",
	const  char* outFile="MuL4Vx.root") {
  TFile *fOut = new TFile(outFile,"recreate");
  TH1F  *zVxAll = new TH1F("zVXAll","Z of all reconstructed vertices",210,-210,210);
  TH1F  *zVxAll1 = new TH1F("zVXAll1","Z of the highest rank vertex",210,-210,210);
  TH1F  *zVxMc = new TH1F("zVxMc","Z of the 1st simulated vertex",400,198,202);
  TH1F  *zVxAllF = new TH1F("zVXAllF","Z of the highest rank vertex",400,198,202);
  TH1F  *zVxAllE = new TH1F("zVXAllE","Z of the highest rank vertex with KF East fit",400,198,202);
  TH1F  *zVxAllW = new TH1F("zVXAllW","Z of the highest rank vertex with KF West fit",400,198,202);
  TH2F  *xyVxAllF = new TH2F("xyVXAllF","Y vs X  of the highest rank vertex",100,-2 - fgyFXT, 2 -fgyFXT, 100, -2, 2);
  TH1F  *noTracks = new TH1F("noTracks", "no. of tracks in a vertex",100,0,250); 
  TH1F  *noTracks1 = new TH1F("noTracks1", "no. of tracks in the highest rang vertrex",100,0,250); 
  TH1F  *noTracksF = new TH1F("noTracksF", "no. of tracks in the highest rang vertrex with |Z-200| < 5 cm",100,0,250); 
  TH2F  *ZnoTracksF = new TH2F("ZnoTracksF", "(Z-200) versus no. of tracks in the highest rang vertrex with |Z-200| < 2 cm",100,0,250,100,-2,2); 
  TH2F  *CAnEastWest = new TH2F("CAnEastWest","no. of tracks East versus West",300,0,300,150,0,150);
  TH2F  *CAZvxZ  = new TH2F("CAZvsZ","Z All from CA vesrsus Z > 10 tracks", 100, 197,202, 100, 197, 202);
  TH2F  *CAZEastVsWest  = new TH2F("CAZEastVsWest","ZEast - ZAll   vs ZWest - ZAll", 100, -5, 5, 100, -5, 5);
  TH2F  *KFZEastVsWest  = new TH2F("KFZEastVsWest","ZEast vs ZWest for NDF > 10", 200, fgzFXT - 5, fgzFXT + 5, 200, fgzFXT - 5, fgzFXT + 5);
  TH2F  *noHitsVsEta = new TH2F("noHitsVsEta","no. of hits versus eta for the best primary vertex",100,-3.0, 3.0, 100, 0.5, 100.5);
  TH2F  *noHitsRVsEta = new TH2F("noHitsRVsEta","no. of hits . no. of possible hits ratio versus eta for the best primary vertex",100,-3.0, 3.0, 120, -0.1, 1.1);
  const Char_t *kName[6]  = {"W"   ,"E"   ,"WvsE"             ,"WvsEw"                     ,"WsE"        ,"WsEw"                 };
  const Char_t *kTitle[6] = {"West","East","West and East sum","West and East sum weighted","West - East", "West - East weighted"};
  TString Name, Title;
  Int_t nx = 100, ny = 100, nz = 500;
  Double_t xmin = -2, xmax = 2;
  Double_t ymin = -2, ymax = 2;
  Double_t zmin = -5, zmax = 5;
  const Char_t *vName[1] = {"xyz"};
  const Char_t *vTitle[1] = {"xyz of Vertex"};
  TH3F *kfHist[1][5] = {0};
  TH2F *ZdZ[2] = {0};
  TH2F *dZ[2] = {0};
  TH2F *deltaZ[2] = {0};
  for (Int_t v = 0; v < 1; v++) {
    Int_t k = 0;
    for (; k < 6; k++) {
      Name = vName[v]; Title = vTitle[v]; 
      Name += kName[k]; Title += " "; Title += kTitle[k];
      if (k < 4) 
	kfHist[v][k] = new TH3F(Name,Title, nx, xmin, xmax, ny, ymin + fgyFXT , ymax + fgyFXT, nz, zmin + fgzFXT, zmax + fgzFXT);
      else
	kfHist[v][k] = new TH3F(Name,Title, nx, xmin, xmax, ny, ymin          , ymax         , nz, zmin         , zmax         );
      if (v == 0 && k < 2) {
	Name = "ZOverdZ"; Name += kName[k];
	Title = Form("(Z_{%s} - %8.3f)/dZ versus (NDF()+3)/2", kTitle[k],fgzFXT);  
	ZdZ[k] = new TH2F(Name,Title,150,0.,300.,200,-5,5);
	Name = "dZ"; Name += kName[k];
	Title = Form("dZ_{%s} versus (NDF()+3)/2", kTitle[k]);  
	dZ[k] = new TH2F(Name,Title,150,0.,300.,200,0,1);
	Name = "DeltaZ"; Name += kName[k];
	Title = Form("(Z_{%s} - %8.3f) versus (NDF()+3)/2", kTitle[k],fgzFXT);  
	deltaZ[k] = new TH2F(Name,Title,150,0.,300.,200,-1,1);

	
      }
    }
  }
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
#endif
				    ,"StStMuMcVertex"
#if 0
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
    KFVertex   &KFVxWest  = summary.KFVxWest;
    KFVertex   &KFVxEast  = summary.KFVxEast;
    KFVertex   *KFVx[2]   = {&KFVxWest, &KFVxEast};  
    // cout << " #" << ev;
    //    Int_t referenceMultiplicity = muEvent->refMult(); // get the reference multiplicity
    // cout << " refMult= "<< referenceMultiplicity;
    TClonesArray *PrimaryVertices   = mu->primaryVertices(); 
    Int_t NoPrimaryVertices = PrimaryVertices->GetEntriesFast();  // cout << "\tPrimaryVertices " << NoPrimaryVertices;
    TClonesArray *PrimaryTracks    = mu->array(muPrimary);  
    Int_t NoPrimaryTracks = PrimaryTracks->GetEntriesFast();  // cout << "\tPrimaryTracks " << NoPrimaryTracks;
    TClonesArray *GlobalTracks     = mu->array(muGlobal);  
    Int_t NoGlobalTracks = GlobalTracks->GetEntriesFast();        if (Debug()) {cout << "\tGlobalTracks " << NoGlobalTracks;}
#if 0
    TClonesArray *CovPrimTrack     = mu->covPrimTrack();          if (Debug()) {cout << "\tCovPrimTrack " << CovPrimTrack->GetEntriesFast();}
    TClonesArray *CovGlobTrack     = mu->covGlobTrack();          if (Debug()) {cout << "\tCovGlobTrack " << CovGlobTrack->GetEntriesFast();}
#endif
    StMuMcVertex *muMcVx = mu->MCvertex(0);
    if (muMcVx) {
      zVxMc->Fill(muMcVx->XyzV().z());
    }
    for (Int_t l = 0; l < NoPrimaryVertices; l++) {
      StMuPrimaryVertex *Vtx = (StMuPrimaryVertex *) PrimaryVertices->UncheckedAt(l);
      if (! Vtx) continue;
      Int_t NTracks = Vtx->noTracks();
      Double_t Z = Vtx->position().z();
      zVxAll->Fill(Z);
      noTracks->Fill(NTracks);
      if (l) continue;
      mu->setVertexIndex(l);
      zVxAll1->Fill(Z);
      noTracks1->Fill(NTracks);
      if (TMath::Abs(Vtx->position().z() - fgzFXT) > 10) continue;
      zVxAllF->Fill(Z);
      xyVxAllF->Fill(Vtx->position().y(),Vtx->position().x());
      noTracksF->Fill(NTracks);
      Int_t nprimTracks = StMuDst::primaryTracks()->GetSize();
      for (Int_t k = 0; k < nprimTracks; k++) {
	StMuTrack *pTrack = mu->primaryTracks(k);
	if (! pTrack) continue;
	if (pTrack->vertexIndex() != l) continue;
	noHitsVsEta->Fill(pTrack->eta(), pTrack->nHits());
	Double_t rat = pTrack->nHits();
	rat /= pTrack->nHitsPoss();
	noHitsRVsEta->Fill(pTrack->eta(), rat);
      }
      ZnoTracksF->Fill(NTracks, Z - 200);
      CAnEastWest->Fill(L4VxWest.Const,L4VxEast.Const);
      if (L4Vx.Const < 10) {
	CAZvxZ->Fill(Z, L4Vx.Mu);
	CAZEastVsWest->Fill(L4VxWest.Mu -  L4Vx.Mu, L4VxEast.Mu -  L4Vx.Mu);
      }
      for (Int_t s = 0; s < 2; s++) {
	Double_t ndf = KFVx[s]->GetNDF();
	if (ndf <= 10) continue;
	Int_t p = 2;
	Double_t z = KFVx[s]->GetParameter(p);
	Double_t dz = TMath::Sqrt(KFVx[s]->GetCovariance(p,p));
	dZ[s]->Fill(ndf, dz);
	ZdZ[s]->Fill(ndf, (z - fgzFXT)/dz);
	deltaZ[s]->Fill(ndf, (z - fgzFXT));
      }
      if (KFVxEast.GetNDF() > 10) {zVxAllE->Fill(Z);kfHist[0][0]->Fill(KFVxEast.GetX(), KFVxEast.GetY(), KFVxEast.GetZ());}
      if (KFVxWest.GetNDF() > 10) {zVxAllW->Fill(Z);kfHist[0][1]->Fill(KFVxWest.GetX(), KFVxWest.GetY(), KFVxWest.GetZ());}
      if (! (KFVxWest.GetNDF() > 10 && KFVxEast.GetNDF() > 10 && KFVxEast.GetNDF() > 10 && KFVxEast.GetNDF() > 10)) continue;
      KFZEastVsWest->Fill(KFVxWest.GetZ(),KFVxEast.GetZ());
      kfHist[0][2]->Fill(0.5*(KFVxWest.GetX()+KFVxEast.GetX()), 0.5*(KFVxWest.GetY()+KFVxEast.GetY()), 0.5*(KFVxWest.GetZ()+KFVxEast.GetZ()));
      kfHist[0][4]->Fill(0.5*(KFVxWest.GetX()-KFVxEast.GetX()), 0.5*(KFVxWest.GetY()-KFVxEast.GetY()), 0.5*(KFVxWest.GetZ()-KFVxEast.GetZ()));
      Double_t xyz[2][3] = {0};
      Int_t p = 0;
      for (; p < 3; p++) {
	Double_t w[2] = {0};
	Double_t var[2] = {0};
 	for (Int_t s = 0; s < 2; s++) {
	  var[s] = KFVx[s]->GetParameter(p);
	  w[s] = 1./KFVx[s]->GetCovariance(p,p);
	}
	xyz[0][p] = (var[0]*w[0] + var[1]*w[1])/(w[0]+w[1]);
	xyz[1][p] = (var[0]*w[0] - var[1]*w[1])/(w[0]+w[1]);
      }
      kfHist[0][3]->Fill(xyz[0][0], xyz[0][1], xyz[0][2]);
      kfHist[0][5]->Fill(xyz[1][0], xyz[1][1], xyz[1][2]);
    }
  }
#if 0
  if (fOut) fOut->Write();
#endif
}



