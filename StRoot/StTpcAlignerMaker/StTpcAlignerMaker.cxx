// Author : Yuri V. Fisyak 10/01/2004
//#define __TIME_CORRECTION__
//#define __USE_LOCAL__
#include <assert.h>
#include <vector>
#include <Stiostream.h>		 
#include "StTpcAlignerMaker.h"
#include "StDetectorDbMaker/StiTpcInnerHitErrorCalculator.h"
#include "StDetectorDbMaker/StiTpcOuterHitErrorCalculator.h"
#include "StDetectorDbMaker/St_tpcPadConfigC.h"
#include "StDetectorDbMaker/St_tpcStatusC.h"
	       // StDb
#include "StDbUtilities/StTpcCoordinateTransform.hh"
#include "StDbUtilities/StCoordinates.hh" 
#include "StTpcDb/StTpcDb.h"
	       // StarClassLibrary
#include "SystemOfUnits.h"
#include "StPhysicalHelixD.hh"
	       // StEvent 
#include "StEvent/StBTofCollection.h"
#include "StEvent/StBTofRawHit.h"
#include "StEvent/StBTofHeader.h"
#include "StEvent/StDcaGeometry.h"
	       // StarRoot
#include "THelixTrack.h"
#include "TRVector.h"
#include "TRMatrix.h"
	       // ROOT
#include "TChain.h"
#include "TFile.h"
#include "TVector3.h"
#if ROOT_VERSION_CODE < 331013
#include "TCL.h"
#else
#include "TCernLib.h"
#endif
#include "TIterator.h"
#include "TArrayI.h"
#include "TArrayD.h"
#include "TH3.h"
#include "StBFChain.h"
#include "StMessMgr.h" 
#include "StEventTypes.h"
#define __DEBUG__
#ifdef __DEBUG__
#define DEBUG_LEVEL if (Debug()%10 > 1 || _debug)
#define PrPP(A,B)  DEBUG_LEVEL {LOG_INFO << "StTpcAlignerMaker::" << (#A) << "\t" << (#B) << " = \t" << (B) << endm;}
#define PrP2(A,B)  DEBUG_LEVEL {cout << (#A) << "\t"; (B).Print();}
#else
#define PrPP(A,B)
#define PrP2(A,B)
#endif
#define __IN2OUT__
#define __Sup12S__ /* use Sup12S for W2S */
//________________________________________________________________________________
ClassImp(StTpcW2SMatch);
//ClassImp(HelixPar_t);
//ClassImp(Hit_t);
ClassImp(StTpcInOutMatch);
ClassImp(StTpcAlignerMaker);
//________________________________________________________________________________
static TTree* TpcInOutTree = 0;
static TTree* TpcW2STree = 0;
static Int_t _debug = 0;
//_____________________________________________________________________________
Int_t StTpcAlignerMaker::Init(){
  StBFChain *chain = dynamic_cast<StBFChain*>(GetChain());
  TFile *f = 0;
  if (chain) f = chain->GetTFile();
  if (! f) {
    gMessMgr->Warning() << "StTpcAlignerMaker::Init root file has not been found" << endm;
    assert(f);
  }
  gMessMgr->Warning() << "StTpcAlignerMaker::Init found " << f->GetName() << " Create TpcInOutTree" << endm;
  f->cd();
  Int_t comp   = 1;       // by default file is compressed
  f->SetCompressionLevel(comp);
  Int_t split  = 9;       // by default, split Event in sub branches
  //   Int_t split  = -2;       // by default, split Event in sub branches << old style
  Int_t bufsize = 64000;
  if (split)  bufsize /= 4;
   Int_t branchStyle = 1; //new style by default
   if (split < 0) {branchStyle = 0; split = -1-split;}
   TTree::SetBranchStyle(branchStyle);
  TpcInOutTree = new TTree("TpcInOutTree","the TPC residuals between Inner and Outer sub sectors");
  TpcInOutTree->SetAutoSave(1000000000); // autosave when 1 Gbyte written
  TpcInOutTree->SetCacheSize(10000000);  // set a 10 MBytes cache (useless when writing local files)
  StTpcInOutMatch::Class()->IgnoreTObjectStreamer();
  HelixPar_t::Class()->IgnoreTObjectStreamer();
  StTpcW2SMatch::Class()->IgnoreTObjectStreamer();
  fTpcInOutMatch = new StTpcInOutMatch();
  TBranch *branch = TpcInOutTree->Branch("StTpcInOutMatch","StTpcInOutMatch",&fTpcInOutMatch, bufsize,split);
  branch->SetAutoDelete(kFALSE);
  if(split >= 0 && branchStyle) TpcInOutTree->BranchRef();
  fTpcW2SMatch = new StTpcW2SMatch();
  TpcW2STree = new TTree("TpcW2STree","the TPC residuals for prediction from sector W in sector S");
  TpcW2STree->SetAutoSave(1000000000); // autosave when 1 Gbyte written
  TpcW2STree->SetCacheSize(10000000);  // set a 10 MBytes cache (useless when writing local files)
  branch = TpcW2STree->Branch("StTpcW2SMatch","StTpcW2SMatch",&fTpcW2SMatch, bufsize,split);
  branch->SetAutoDelete(kFALSE);
  if(split >= 0 && branchStyle) TpcW2STree->BranchRef();
  return StMaker::Init();
}
//_____________________________________________________________________________
Double_t StTpcAlignerMaker::PhiFromBTofTray(Int_t tray) {
  Double_t Phi = 0;
  if (tray > 60) { // east
    Phi = 6*(tray + 0.5 - 61) - 255;
  } else {
    Phi = 435 - 6*(tray + 0.5 -  1);
  }
  if (Phi > 180) Phi -= 360;
  if (Phi <-180) Phi += 360;
  return TMath::DegToRad()*Phi;
}
//_____________________________________________________________________________
Int_t StTpcAlignerMaker::TpcSectorFromBTofTray(Int_t tray) {
  Double_t angle = TMath::RadToDeg()*PhiFromBTofTray(tray);
  if (angle < 0) angle += 360;
  Int_t sec = (Int_t) ((angle + 15.)/30.);
  if (tray <= 60) {sec = 15 - sec; if (sec > 12) sec -= 12;}
  else            {sec +=       9; if (sec <=12) sec += 12;}
  return sec;
}
//_____________________________________________________________________________
Int_t StTpcAlignerMaker::Make(){
  assert(gStTpcDb);
  bField = 0;
  pEvent = dynamic_cast<StEvent*> (GetInputDS("StEvent"));
  if (!pEvent) {
    gMessMgr->Info() << "StdEdxY2Maker: no StEvent " << endm;
    return kStOK;        // if no event, we're done
  }
  if (pEvent->runInfo()) bField = pEvent->runInfo()->magneticField();//*kilogauss;
  driftVel = 1e-6*gStTpcDb->DriftVelocity(24,0); // cm/mkmsec
  freq     = gStTpcDb->Electronics()->samplingFrequency(); // MHz
  TriggerId = 0;
  static Int_t goodIds[8] = {9200,9201,               // laser
			     310811, 310812, 310813,  // cosmic
			     420811, 420812, 420813}; // cosmic 2014
  const StTriggerIdCollection* trig = pEvent->triggerIdCollection();
  if (trig) {
    const StTriggerId *nominal = trig->nominal();
    if (nominal) {
      for (Int_t i = 0; i < 8; i++) {
	if (nominal->isTrigger(goodIds[i])) {TriggerId = goodIds[i]; break;}
      } 
    } else {TriggerId = goodIds[0];}
  }
  //  Bool_t LaserT  = TriggerId == goodIds[0] || TriggerId == goodIds[1];
  //  Bool_t CosmicT = TriggerId != 0 && ! LaserT;
  //  Bool_t EventT  = ! LaserT && ! CosmicT;
  StSPtrVecTrackNode& trackNode = pEvent->trackNodes();
  UInt_t nTracks = trackNode.size();
  if (! nTracks) return kStOK;
  //  if (TriggerId > 310810 && nTracks > 5) return kStOK;
  // Check ToF to understand direction where muons a comint from
  //  StBTofCollection *btofcol = pEvent->btofCollection();
#ifdef __IN2OUT__
  MakeIO();
#endif /* __IN2OUT__ */
  MakeW2S();
#if 0
  if (TpcInOutTree) TpcInOutTree->AutoSave("SaveSelf");
  if (TpcW2STree)   TpcW2STree->AutoSave("SaveSelf");
#endif
  return kStOK;
}
// ______________________________________________________________________________
Int_t StTpcAlignerMaker::MakeIO() {
  // Outer to Inner sector alignment
  enum {kMaxHits = 255};
  static StThreeVectorD XyzI, XyzO;
  static StThreeVectorD DirI, DirO;
  static StGlobalCoordinate              globalCoo;
  static StTpcLocalSectorCoordinate      local;
  static StGlobalDirection               globalDir;
  static StTpcLocalSectorDirection       localDir;
  static StTpcCoordinateTransform transform(StTpcDb::instance());
  StSPtrVecTrackNode& trackNode = pEvent->trackNodes();
  UInt_t nTracks = trackNode.size();
  for (UInt_t t=0; t < nTracks; t++) {
    StTrackNode *node = trackNode[t]; 
    if (!node) continue;
    StGlobalTrack  *gTrack = static_cast<StGlobalTrack *>(node->track(global));
    if (! gTrack ) continue;
    if (gTrack->flag() < 0) continue;
    if (! gTrack->detectorInfo()) continue;
    const StDcaGeometry* dca = gTrack->dcaGeometry();
    if (! dca) continue;
    if (Debug()%10 > 5) {
      cout << "Track: " << t << " " << *dca << endl;
    }
    const StThreeVectorF &pxyz = gTrack->geometry()->momentum();
    fTpcInOutMatch->Clear();
    fTpcInOutMatch->TriggerId = TriggerId;
    fTpcInOutMatch->field  = bField;
    fTpcInOutMatch->driftVel = driftVel;
    fTpcInOutMatch->freq      = freq;
    fTpcInOutMatch->charge = gTrack->geometry()->charge();
    fTpcInOutMatch->pX     = pxyz.x();
    fTpcInOutMatch->pY     = pxyz.y();
    fTpcInOutMatch->pZ     = pxyz.z();
    StPtrVecHit hvec   = gTrack->detectorInfo()->hits();
    Int_t count = 0;
    if ( hvec.size() < 10) continue;
    //      Int_t Id = gTrack->key();
    fTpcInOutMatch->NoFitPoints = gTrack->fitTraits().numberOfFitPoints(kTpcId);
    if (fTpcInOutMatch->NoFitPoints < 10) continue;
    Int_t NhitInSector[24]; memset(NhitInSector,0,sizeof(NhitInSector));
    // Find sector with maximum no. of hits
    //      UInt_t sectorWithMaxRowNo = 0;
    UInt_t Nhits = hvec.size();
    for (UInt_t j=0; j < Nhits; j++) {// hit loop
      if (! hvec[j]) continue;
      if (hvec[j]->detector() != kTpcId) continue;
      StTpcHit *tpcHit = (StTpcHit *) hvec[j];
      //      if (_debug) tpcHit->Print("");
      if (! tpcHit->usedInFit() || tpcHit->flag()) continue;
      Int_t sector = tpcHit->sector();
      NhitInSector[sector-1]++;
    }	
    UInt_t sectorWithMaxNoHits = 0;
    Int_t N = 0;
    for (Int_t j = 0; j < 24; j++) {
      if (NhitInSector[j] < 10) continue;
      if (NhitInSector[j] > N) {
	sectorWithMaxNoHits = j+1;
	N = NhitInSector[j];
      }
    }
    if (sectorWithMaxNoHits == 0) continue;
    Int_t sector = sectorWithMaxNoHits;
    N = 0;
    SectorTrack ssegm[2]; // 0 => Inner, 1 => Outer
    for (UInt_t j=0; j < Nhits; j++) {// hit loop
      if (! hvec[j]) continue;
      if (hvec[j]->detector() != kTpcId) continue;
      StTpcHit *tpcHit = (StTpcHit *) hvec[j];
      if (tpcHit->sector() != sectorWithMaxNoHits) continue;
      if (! tpcHit->usedInFit() || tpcHit->flag()) continue;
      if (_debug) tpcHit->Print("");
      Int_t row = tpcHit->padrow();
      if (row <= St_tpcPadConfigC::instance()->innerPadRows(sector)) ssegm[0].AddHit(tpcHit);
      else                                                           ssegm[1].AddHit(tpcHit);
    }
    if (ssegm[0].List()->GetSize() < 5 || ssegm[1].List()->GetSize() < 5) continue;
    
    static Double_t yRef = 123;
    static Double_t RefSurfice[5] = {-yRef, 0, 1, 0, yRef};
    Double_t xyz123L[3] = {0, - RefSurfice[0], 0};
    Double_t RefSurficeG[5] = {0};
#ifdef __Sup12S__
    Double_t xyz123G[3];
    StTpcDb::instance()->Sup12S2Glob(sector).LocalToMaster(xyz123L, xyz123G);
    StTpcDb::instance()->Sup12S2Glob(sector).LocalToMasterVect(&RefSurfice[1], &RefSurficeG[1]);
#else
    local = StTpcLocalSectorCoordinate(xyz123L, sector);
    transform(local,globalCoo);
    Double_t *xyz123G = globalCoo.position().xyz();
#endif
    RefSurficeG[0] = - (xyz123G[0]*RefSurficeG[1] + xyz123G[1]*RefSurficeG[2] + xyz123G[2]*RefSurficeG[3]);
    RefSurficeG[4] = RefSurfice[4];
    if (ssegm[0].MakeTHelix(RefSurficeG)) continue;
    if (ssegm[1].MakeTHelix(RefSurficeG)) continue;
    HelixPar_t *HlxPars[2] = {&fTpcInOutMatch->In, &fTpcInOutMatch->Out};
    *HlxPars[0] = ssegm[0];
    *HlxPars[1] = ssegm[1];
    if (HlxPars[0]->sector <= 0 || HlxPars[1]->sector <= 0) continue;
    if (Debug()) {
      for (Int_t io = 0; io < 2; io++) {
	if (! io) cout << "In:\t";
	else      cout << "Out:\t"; 
	cout << *HlxPars[io] << endl;
      }
      HelixPar_t diff = *HlxPars[1];
      diff -= *HlxPars[0];
      cout << "Diff:" << diff << endl;
    } // end loop over helices
    if (TpcInOutTree) {
      TpcInOutTree->Fill();
    }
    count++;
  } // loop over tracks
  return kStOK;
}
//________________________________________________________________________________
Int_t StTpcAlignerMaker::MakeW2S() {
  // Sector to Sector Alignment
  static StTpcCoordinateTransform transform(StTpcDb::instance());
  StSPtrVecTrackNode& trackNode = pEvent->trackNodes();
  fTpcW2SMatch->TriggerId = TriggerId;
  fTpcW2SMatch->field  = bField;
  fTpcW2SMatch->driftVel = driftVel;
  fTpcW2SMatch->freq      = freq;
  UInt_t nTracks = trackNode.size();
  TList SegmentList; SegmentList.SetOwner(kTRUE);
  for (UInt_t i=0; i < nTracks; i++) {
    StTrackNode *node = trackNode[i]; 
    if (!node) continue;
    StGlobalTrack  *gTrack = static_cast<StGlobalTrack *>(node->track(global));
    if (! gTrack ) continue;
    if (gTrack->flag() < 0) continue;
    if (! gTrack->detectorInfo()) continue;
    if (gTrack->fitTraits().numberOfFitPoints(kTpcId) < 10) continue;
    StPtrVecHit hvec   = gTrack->detectorInfo()->hits();
    if (hvec.size() < 10) continue;
    const StThreeVectorF &pxyz = gTrack->geometry()->momentum();
    Double_t pMomentum = pxyz.mag();
    if (TMath::Abs(bField) < 0.10) pMomentum = 1000;
    if (pMomentum < 1.0) continue;
    StTpcHit *tpcHit = 0;
    //      Int_t Id = gTrack->key();
    PrPP(track,i);
    Int_t oldSect = -1;
    SectorTrack *ssegm = 0;
    for (UInt_t j=0; j<hvec.size(); j++) {// hit loop
      if (! hvec[j]) continue;
      if (hvec[j]->detector() != kTpcId) continue;
      tpcHit = (StTpcHit *) hvec[j];
      if (! tpcHit->usedInFit() || tpcHit->flag()) continue;
      Int_t sector = tpcHit->sector();
      if (!ssegm || sector != oldSect) {
	ssegm = new SectorTrack(sector);
	SegmentList.Add(ssegm);
	oldSect = sector;
      }
      ssegm->AddHit(tpcHit); 
    }
  }
  if (SegmentList.GetSize() < 2) return kStOK;
  // Fit Segments
  SegmentList.Sort();
  TIter nextSegment(&SegmentList);
  SectorTrack *segm = 0;
  while ((segm = (SectorTrack *) nextSegment())) {
    if (segm->MakeTHelix()) continue;
#if 0
    StTpcHit *tpcHit = (StTpcHit *) segm->List()->First();
    Int_t sector = tpcHit->sector();
    assert(sector == segm->Sector());
    Int_t row    = tpcHit->padrow();
    Double_t Y = transform.yFromRow(sector, row);
    Double_t RefSurfice[5] = {- Y, 0, 1, 0, Y};
    Double_t xyz123L[3] = {0, - RefSurfice[0], 0};
    Double_t RefSurficeG[5] = {0};
    Double_t xyz123G[3];
    StTpcDb::instance()->Sup12S2Glob(sector).LocalToMaster(xyz123L, xyz123G);
    StTpcDb::instance()->Sup12S2Glob(sector).LocalToMasterVect(&RefSurfice[1], &RefSurficeG[1]);
    RefSurficeG[0] = - (xyz123G[0]*RefSurficeG[1] + xyz123G[1]*RefSurficeG[2] + xyz123G[2]*RefSurficeG[3]);
    RefSurficeG[4] = RefSurfice[4];
    if (Debug() > 2) {
      for (Int_t j = 0; j < 4; j++) {
	cout << "\tRefSurficeG[" << j << "] = " << RefSurficeG[j];
      }
      cout << endl;
    }
    if (segm->Move(RefSurficeG)) continue;
    if (Debug()%10 > 0) segm->Print();
#endif
  }
  Int_t NoSegm = SegmentList.GetSize();
  fTpcW2SMatch->TriggerId = TriggerId;
  if (NoSegm <= 1) return kStOK;
  HelixPar_t    &HlxParW   = *&fTpcW2SMatch->HlxParW;
  HelixPar_t    &HlxParS   = *&fTpcW2SMatch->HlxParS;
  HelixPar_t    &HlxParW2S = *&fTpcW2SMatch->HlxParW2S;
  TGeoHMatrix   &RW2S      = *&fTpcW2SMatch->RW2S;
  for (Int_t k = 0; k < NoSegm; k++) { // W
    if (! SegmentList.At(k)) continue;
    SectorTrack *segW = (SectorTrack *)  SegmentList.At(k);
    if (segW->Status()) continue;
    Int_t sectorW = segW->Sector();
    if (! sectorW) continue;
    for (Int_t l = 0; l < NoSegm; l++) { // S
      fTpcW2SMatch->Clear();
      if (l == k) continue;
      if (! SegmentList.At(l)) continue;
      SectorTrack *segS = (SectorTrack *)  SegmentList.At(l);
      if (segS->Status()) continue;
      Int_t sectorS = segS->Sector();
      if (sectorW == sectorS) continue;
      // Find closest rows
      TVector3 dXYZ[4] = {segS->fXYZmin - segW->fXYZmin, segS->fXYZmin - segW->fXYZmax, segS->fXYZmax - segW->fXYZmin, segS->fXYZmax - segW->fXYZmax};
      Double_t distOld = 99999;
      Int_t mOld = -1;
      for (Int_t m = 0; m < 4; m++) {
	Double_t dist = dXYZ[m].Mag();
	if (dist < distOld) {
	  mOld = m;
	  distOld = dist;
	}
      } 
      if (mOld < 0) continue;
      Int_t rowS = segS->RowMin();
      if (mOld > 1) rowS = segS->RowMax();
      Double_t Y = transform.yFromRow(sectorS, rowS);
      Double_t RefSurfice[5] = {- Y, 0, 1, 0, Y};
      Double_t xyz123L[3] = {0, - RefSurfice[0], 0};
      Double_t RefSurficeG[5] = {0};
      Double_t xyz123G[3];
      StTpcDb::instance()->Sup12S2Glob(sectorS).LocalToMaster(xyz123L, xyz123G);
      StTpcDb::instance()->Sup12S2Glob(sectorS).LocalToMasterVect(&RefSurfice[1], &RefSurficeG[1]);
      RefSurficeG[0] = - (xyz123G[0]*RefSurficeG[1] + xyz123G[1]*RefSurficeG[2] + xyz123G[2]*RefSurficeG[3]);
      RefSurficeG[4] = RefSurfice[4];
      RW2S = StTpcDb::instance()->Sup12S2Tpc(sectorS).Inverse() * StTpcDb::instance()->Sup12S2Tpc(sectorW); 
      SectorTrack segSS = *segS;
      if (segSS.Move(RefSurficeG)) continue;
      SectorTrack segWW = *segW;
      if (segWW.Move(RefSurficeG)) continue;
      SectorTrack segW2S = segWW;
      segW2S.SetSector(100*sectorW + sectorS);
      segW2S.SetRow(rowS);
      if (segW2S.Move(RefSurficeG)) continue;
      HlxParS   = segSS;
      HlxParW   = segWW;
      HlxParW2S = segW2S;
      PrPP(Make,HlxParW2S);
      const Char_t * names[6] = {"x","y","z","nx","ny","nz"};
      Double_t *s = HlxParS.xyzG();
      Double_t *w = HlxParW2S.xyzG();
      DEBUG_LEVEL {
	cout << "Matching segment  from sectorW " << sectorW << " to sectorS " << sectorS
	     << " at step = " << segW2S.Step() << endl;
	cout << "HlxParW\t"   << HlxParW << endl;
	cout << "HlxPaxS\t"   << HlxParS << endl;
	cout << "HlxParW2S\t" << HlxParW2S << endl;
      }
      Int_t reject = 0;
      for (Int_t i = 0; i < 6; i++) {
	DEBUG_LEVEL {
	  cout << names[i] << "\t" << s[i] << "\t" << w[i] << "\tDelta " << s[i] - w[i] << endl;
	}
	if (i < 3 && TMath::Abs(s[i] - w[i]) > 10) reject++;
      }
      DEBUG_LEVEL {
	if (reject) cout << "rejected" << endl;
      }
      if (reject) continue;
      TpcW2STree->Fill();
    }
  }
  return kStOK;
}
