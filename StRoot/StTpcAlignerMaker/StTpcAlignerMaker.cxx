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
//________________________________________________________________________________
ClassImp(SectorSegment);
ClassImp(StTpcW2SMatch);
//ClassImp(HelixPar_t);
//ClassImp(Hit_t);
ClassImp(StTpcInOutMatch);
ClassImp(StTpcAlignerMaker);
//________________________________________________________________________________
static TTree* TpcInOutTree = 0;
static TTree* TpcW2STree = 0;
static Int_t _debug = 0;
//________________________________________________________________________________
void  SectorSegment::Print(Option_t */* option */) const {
  cout << "Segment: " << GetName() << " for sector " << fSector << " rowMin " << fRowMin<< endl;
  if (_debug) {
    TIter next(&fList);
    Int_t i = 0;
    StTpcHit *tpcHit = 0;
    while ((tpcHit = (StTpcHit *) next())) {
      cout << i++ << "\t" << *tpcHit << endl;
    }
    fHelix.Print();
  }
  if (fSector > 0) cout << " HlxPar " << HlxPar << endl;
}
//________________________________________________________________________________
ostream&  operator<<(ostream& os, const HelixPar_t &v) {
  os << Form("sector %2i Rho = %10.3g +/- %10.3g",v.sector, v.Rho, v.dRho);
  os << Form(" n: %8.3f %8.3f %8.3f xyz: %8.3f %8.3f %8.3f ", v.nx, v.ny, v.nz, v.x, v.y, v.z);
  os << Form("<drift> %8.3f step %8.3f", v.DriftZ, v.step);
  os << Form(" ng: %8.3f %8.3f %8.3f", v.nxG, v.nyG, v.nzG);
  os << Form(" xyzG: %8.3f %8.3f %8.3f", v.xG, v.yG, v.zG);
  if (_debug) {
    os << endl;
    TRSymMatrix C(5,v.fCov);
    os << C << endl;
  }
  os << "\tPoints = " << v.Npoints << "\tused = " << v.Nused << "\tchi2/Ndf = " << v.Chi2 << "/" << v.Ndf;
  return os;
}
//_____________________________________________________________________________
HelixPar_t &HelixPar_t::operator=(const THelixFitter &helix) {
  Chi2 = helix.Chi2();
  Ndf  = helix.Ndf();
  Npoints = helix.Size();
  Nused   = helix.Used();
  helix.Get(xyzG(),pxyzG(),Rho);
  return *this;
}
//_____________________________________________________________________________
void HelixPar_t::Print(Option_t *opt) const {
  cout << *this << endl;
}
//________________________________________________________________________________
Double_t StTpcAlignerMaker::Project(const Double_t n[3], const Double_t x[3]) {
  StThreeVectorD G(x);
  StThreeVectorD nG(n);
  return  G.dot(nG);
}
//________________________________________________________________________________
void StTpcAlignerMaker::CheckDirection(HelixPar_t *HlxPar) {
  if (! HlxPar) return;
  Double_t proj = Project(HlxPar->pxyzG(), HlxPar->xyzG());
  if (proj < 0) {HlxPar->nxG *= -1; HlxPar->nyG *= -1; HlxPar->nzG *= -1;}
}
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
  StBTofCollection *btofcol = pEvent->btofCollection();
#if 0
  Double_t tofMin = 1e9; 
  Double_t tofMax =   0;
  if (btofcol) {
    StSPtrVecBTofHit &tofHits = btofcol->tofHits();
    UInt_t nHits = tofHits.size();
    for(UInt_t i=0; i < nHits; i++) {
      StBTofHit *aHit = tofHits[i]; // aHit->tray(); 
      if(!aHit) continue;
      if (!aHit->associatedTrack()) continue;
      if (Debug()%10 > 5) cout << "TofHit : " << i << *aHit << " Tpc sector " << TpcSectorFromBTofTray(aHit->tray()) << endl;
      Double_t time = aHit->leadingEdgeTime();
      if (time > tofMax) {tofMax = time;}
      if (time < tofMin) {tofMin = time;}
    }
  }
#endif
  // Best PV
  pVbest  = pEvent->primaryVertex();
  if (btofcol) {
    Double_t VpdZ = -300;
    if (btofcol->tofHeader()) VpdZ = btofcol->tofHeader()->vpdVz();
    if (TMath::Abs(VpdZ) < 200) {
      Double_t dZbest = 999;
      StPrimaryVertex *pVertex = 0;
      for (Int_t ipr=0;(pVertex=pEvent->primaryVertex(ipr));ipr++) {
	Double_t dZ = TMath::Abs(pVertex->position().z()-VpdZ);
	if (dZ < dZbest) {
	  dZbest = dZ;
	  pVbest = pVertex;
	}
      }
      if (dZbest > 3.0) pVbest = 0;
    }
  }
#define __IN2OUT__
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
//________________________________________________________________________________
TRMatrix StTpcAlignerMaker::GetSti2R(Double_t nx, Double_t ny, Double_t nz) {
  Double_t dxy  = TMath::Sqrt(nx*nx + ny*ny);
  Double_t tanL = nz/dxy;
  Double_t l2   = TMath::Sqrt(1+tanL*tanL);
  Double_t l1l = tanL*l2;
  Double_t Sti2R[30] = {
    /*          y, z      nx,     ny,  nz,*/
    /* x    */  0, 0,      0,      0,   0,  
    /* y    */  1, 0,      0,      0,   0,  
    /* z    */  0, 1,      0,      0,   0,  
    /* eta  */  0, 0,    -ny,     nx,   0,
    /* curv */  0, 0,      0,      0,   0,  
    /* tanL */  0, 0, nx*l1l, ny*l1l, -l2};
  return TRMatrix(6,5,Sti2R); 
}
// ______________________________________________________________________________
Int_t StTpcAlignerMaker::MakeIO() {
  // Outer to Inner sector alignment
  enum {kMaxHits = 255};
  static Hit_t tpcHits[kMaxHits+1];
  static Double_t RIO[kMaxHits+1];
  static Int_t idx[kMaxHits+1];
  static StThreeVectorD XyzI, XyzO;
  static StThreeVectorD DirI, DirO;
  static Double_t stepMX = 1.e3;
  Double_t StiErr[21];
  Double_t step;
  static StTpcLocalSectorCoordinate              local;
  static Double_t err2xy[3] = {0,0,0}, err2z = 0;
  StSPtrVecTrackNode& trackNode = pEvent->trackNodes();
  UInt_t nTracks = trackNode.size();
  StBTofCollection *btofcol = pEvent->btofCollection();
  for (UInt_t t=0; t < nTracks; t++) {
    StTrackNode *node = trackNode[t]; 
    if (!node) continue;
    StGlobalTrack  *gTrack = static_cast<StGlobalTrack *>(node->track(global));
    if (! gTrack ) continue;
    if (gTrack->flag() < 0) continue;
    if (! gTrack->detectorInfo()) continue;
    if (gTrack->TestBit(kRejected)) continue;
    if (TriggerId && btofcol &&
	! gTrack->TestBit(kComingFromOutSide) &&
	! gTrack->TestBit(kComingFromInSideTofMatched) &&
	! gTrack->TestBit(kNoToFDependece)) continue;
    const StDcaGeometry* dca = gTrack->dcaGeometry();
    if (! dca) continue;
    if (Debug()%10 > 5) {
      cout << "Track:" << t << *dca << endl;
    }
    const StThreeVectorF &pxyz = gTrack->geometry()->momentum();
#ifdef __TIME_CORRECTION__
    Double_t pMomentum = pxyz.mag();
    if (TMath::Abs(bField) < 0.01) pMomentum = 1000;
    StThreeVectorD origin    = dca->origin();
    StThreeVectorD dir       = dca->momentum().unit();
    //    Double_t       curvature = dca->curvature();
    Double_t tanl  = dir.z()/dir.perp();
    Double_t coslI = sqrt(1.+tanl*tanl);
    static const Double_t M2muon = 0.1056584*0.1056584;
    Double_t e = TMath::Sqrt(M2muon + pMomentum*pMomentum);
    Double_t beta = pMomentum/e;
#endif
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
    for (UInt_t j=0; j<hvec.size(); j++) {// hit loop
      if (! hvec[j]) continue;
      if (hvec[j]->detector() != kTpcId) continue;
      StTpcHit *tpcHit = (StTpcHit *) hvec[j];
      if (_debug) tpcHit->Print("");
      Int_t sector = tpcHit->sector();
      NhitInSector[sector-1]++;
    }	
    Int_t sectorWithMaxNoHits = -1;
    Int_t N = 0;
    for (Int_t j = 0; j < 24; j++) {
      if (NhitInSector[j] > N) {
	sectorWithMaxNoHits = j+1;
	N = NhitInSector[j];
      }
    }
    if (sectorWithMaxNoHits < 0 || N < 10) continue;
    static StThreeVectorD xyzLPV; // Primary vertex position in Tpc Sector Coordinate System
    Int_t sector = sectorWithMaxNoHits;
#if 0
    static Int_t sectorOld = -1;
    if (pVbest && sector != sectorOld) {
      sectorOld = sector;
      StThreeVectorD xyzG(pVbest->position());
      StThreeVectorD xyzL;
      StTpcDb::instance()->Sup12S2Glob(sector).MasterToLocal(xyzG.xyz(), xyzL.xyz());
      fTpcInOutMatch->iPV = 1;
      fTpcInOutMatch->xPV =  xyzLPV.x();
      fTpcInOutMatch->yPV =  xyzLPV.y();
      fTpcInOutMatch->zPV =  xyzLPV.z();
    }
#endif
    N = 0;
    UInt_t Nhits = hvec.size();
    Double_t driftZ = 0;
    for (UInt_t j = 0; j < Nhits; j++) {// hit loop
      if (hvec[j]->detector() != kTpcId) continue;
      StTpcHit *tpcHit = static_cast<StTpcHit *> (hvec[j]);
      if (! tpcHit) continue;
      Int_t sector = tpcHit->sector();
      Int_t row    = tpcHit->padrow();
      if (St_tpcStatusC::instance()->status(sector,row)) continue;
      if (! tpcHit->usedInFit() || tpcHit->flag()) continue;
      if (sector != sectorWithMaxNoHits) continue;
      StGlobalCoordinate global(tpcHit->position());
#ifdef __TIME_CORRECTION__
      // Distance from Dca to the hit 
      StThreeVectorD dist = StThreeVectorD(tpcHit->position()) - origin;
      Double_t d = dist.perp();
      Double_t sn = 0;
      if (d > 0) sn = TMath::Abs(dir.x()*dist.y() - dir.y()*dist.x())/d;
      if (sn> 0.99) sn =  0.99;
      if (sn<0.2) {
	d *= (1.+sn*sn/6);
      } else {
	d *= TMath::ASin(sn)/sn;
      }
      d *= coslI;
      Double_t time = d/(TMath::Ccgs()*beta*1e-6); // mksec  
      if (gTrack->TestBit(kComingFromOutSide)) time = - time;
      //	transform(global,local,sector,row);
#endif
      StThreeVectorD xyzL;
      StThreeVectorD xyz;
      StTpcDb::instance()->Sup12S2Glob(sector).MasterToLocal(global.position().xyz(), xyzL.xyz());
      local = StTpcLocalSectorCoordinate(xyzL,sector,row);
#ifdef __USE_LOCAL__
      tpcHits[N].x = local.position().x();
      tpcHits[N].y = local.position().y();
#ifdef __TIME_CORRECTION__
      tpcHits[N].z = local.position().z() - driftVel*time;
#else
      tpcHits[N].z = local.position().z();
#endif
      RIO[N]      = tpcHits[N].y;
#else /* ! __USE_LOCAL__ */
      tpcHits[N].x = global.position().x();
      tpcHits[N].y = global.position().y();
      tpcHits[N].z = global.position().z();
      RIO[N]      = local.position().y();
#endif /*  __USE_LOCAL__ */
      tpcHits[N].err2xy[0] = tpcHit->positionError().perp2();
      tpcHits[N].err2z  = tpcHit->positionError().z()*tpcHit->positionError().z();
      if (tpcHits[N].err2xy > 0) {
	tpcHits[N].err2xy[0] = tpcHit->positionError().x()*tpcHit->positionError().x();
	tpcHits[N].err2xy[1] = 0;
	tpcHits[N].err2xy[2] = tpcHit->positionError().y()*tpcHit->positionError().y();
	tpcHits[N].err2z = tpcHit->positionError().z()*tpcHit->positionError().z();
      }
      tpcHits[N].row    = row;
      tpcHits[N].driftZ = local.position().z();
      if (_debug) {
	if (Debug()%10 > 5)    
	  cout << Form("sector = %2i row = %2i N =%2i x = %8.3f +/- %8.3f y = %8.3f +/- %8.3f z = %8.3f +/- %8.3f, R = %8.3f",sector,row,N,
		       tpcHits[N].x,TMath::Sqrt(tpcHits[N].err2xy[0]),
		       tpcHits[N].y,TMath::Sqrt(tpcHits[N].err2xy[2]),
		       tpcHits[N].z,TMath::Sqrt(tpcHits[N].err2z), RIO[N])<< endl;
      }
      if (N < kMaxHits) N++;
    }
    if (N == 0) continue;
    //      TArrayI idxT(N); Int_t *idx = idxT.GetArray();
    TMath::Sort(N,RIO,idx,0);
    Int_t I123 = 0;
    Int_t i,k;
    for (i = 0; i < N; i++) {
      if (RIO[idx[i]] <= 123.0) {
	I123++;
      } else {
	break;
      }
    }
    Int_t NoIOHits[2] = {I123, N - I123};
    if (NoIOHits[0] < 5 || NoIOHits[1] < 5) continue;
    THelixFitter vHelices[2];
    HelixPar_t *HlxPars[2] = {&fTpcInOutMatch->In, &fTpcInOutMatch->Out};
    for (Int_t io = 0; io < 2; io++) {// Inner / Outer Loop
      if (NoIOHits[io] < 5) continue;
      HlxPars[io]->sector = sectorWithMaxNoHits;
      Int_t i2 = N;
      Int_t ii = 1;
      Int_t i1 = 0;
      i2 = NoIOHits[0];
      if (io) {i1 = NoIOHits[0]; ii = 1; i2 = N;}
      Int_t nn = 0;
      driftZ = 0;
      for (i = i1, k = 0; i >= 0 && i < i2; i += ii, k++) {
	Double_t *xyz = &tpcHits[idx[i]].x;
	vHelices[io].Add(xyz);
	if (tpcHits[idx[i]].err2xy[0] == 0 || tpcHits[idx[i]].err2z == 0) {
	  if (! io) StiTpcInnerHitErrorCalculator::instance()->calculateError(200-xyz[2], 0., 0., err2xy[0], err2z);
	  else      StiTpcOuterHitErrorCalculator::instance()->calculateError(200-xyz[2], 0., 0., err2xy[0], err2z);
	  vHelices[io].AddErr(err2xy,err2z);
	} else {
	  vHelices[io].AddErr(tpcHits[idx[i]].err2xy, tpcHits[idx[i]].err2z);
	}
	if (TMath::IsNaN(err2xy[0]) || TMath::IsNaN(err2z)) {
	  static Int_t iBreak = 0;
	  iBreak++;
	}
	driftZ += tpcHits[idx[i]].driftZ;
	nn++;
      }
      HlxPars[io]->DriftZ = driftZ/nn;
      vHelices[io].Fit();
      vHelices[io].MakeErrs();
      vHelices[io].Backward();
      *HlxPars[io] = vHelices[io]; 
      static Double_t RefSurfice[4] = {-123, 0, 1, 0};
      Double_t xyz123L[3] = {0, - RefSurfice[0], 0};
      Double_t xyz123G[3];
      Double_t *RefSurficeG = HlxPars[io]->RefSurficeG;
      StTpcDb::instance()->Sup12S2Glob(sector).LocalToMaster(xyz123L, xyz123G);
      StTpcDb::instance()->Sup12S2Glob(sector).LocalToMasterVect(&RefSurfice[1], &RefSurficeG[1]);
      RefSurficeG[0] = - (xyz123G[0]*RefSurficeG[1] + xyz123G[1]*RefSurficeG[2] + xyz123G[2]*RefSurficeG[3]);
      step = vHelices[io].Step(stepMX, RefSurficeG, 4, HlxPars[io]->xyzG(), HlxPars[io]->pxyzG(), 1); 
      if (TMath::Abs(step) >= stepMX) goto FAILED;;
      HlxPars[io]->step = step; //{PrPP(Step,*HlxPars[io]);}
      CheckDirection(HlxPars[io]);
      StTpcDb::instance()->Sup12S2Glob(sector).MasterToLocalVect(HlxPars[io]->pxyzG(),HlxPars[io]->pxyz());
      StTpcDb::instance()->Sup12S2Glob(sector).MasterToLocal(HlxPars[io]->xyzG(),HlxPars[io]->xyz());
      HlxPars[io]->Rho = vHelices[io].GetRho();
      HlxPars[io]->dRho = vHelices[io].GetDRho();
      vHelices[io].StiEmx(StiErr);
      TRSymMatrix StiMtx(6,StiErr); //PrPP(Make,StiMtx);
      TRMatrix S2R = GetSti2R(HlxPars[io]->nx, HlxPars[io]->ny, HlxPars[io]->nz);
      TRSymMatrix Cov2(S2R,TRArray::kATxSxA,StiMtx);  if (_debug) {PrPP(Make,Cov2);}
      memcpy(HlxPars[io]->fCov, Cov2.GetArray(), 15*sizeof(Double_t));
      if (Debug()%10 > 5) {
	if (! io) cout << "In:\t";
	else      cout << "Out:\t"; 
	cout << *HlxPars[io] << endl;
	//	  const THelixFitter &p = *&vHelices[io];
	//	  p.Print("");
      }
#if 0
      // To Primary Vertex
      if (fTpcInOutMatch->iPV) {
	//	  step = vHelices[io].Step(stepMX, xyzLPV.xyz());
	step = vHelices[io].Path(fTpcInOutMatch->xPV, fTpcInOutMatch->yPV);
	if (TMath::Abs(step) >= stepMX) goto FAILED;;
	vHelices[io].Move(step);
	if (step < 0) {HlxPars[io+2]->nx *= -1; HlxPars[io+2]->ny *= -1; HlxPars[io+2]->nz *= -1;}
	*HlxPars[io+2] = vHelices[io];
	HlxPars[io+2]->sector = sector;
	HlxPars[io+2]->Rho = vHelices[io].GetRho();
	HlxPars[io+2]->dRho = vHelices[io].GetDRho();
	vHelices[io].StiEmx(StiErr);
	TRSymMatrix StiMtx(6,StiErr);// PrPP(Make,StiMtx);
	TRMatrix S2R = GetSti2R(HlxPars[io]->nx, HlxPars[io+2]->ny, HlxPars[io+2]->nz);
	TRSymMatrix Cov2(S2R,TRArray::kATxSxA,StiMtx);//  PrPP(Make,Cov2);
	memcpy(HlxPars[io+2]->fCov, Cov2.GetArray(), 15*sizeof(Double_t));
	if (Debug()%10 > 5) {
	  if (! io) cout << "InAtVx:\t";
	  else      cout << "OutAtVx:\t";
	  //	    const THelixFitter &p2 = *&vHelices[io];
	  //	    p2.Print("");
	  cout << *HlxPars[io+2] << endl;
	}
      }
#endif
    } // end loop over helices
    if (TpcInOutTree && HlxPars[0]->sector > 0 && HlxPars[0]->sector > 0 ) {
      if (Debug()) {
	cout << "In:\t"  << *HlxPars[0] << endl;
	cout << "Out:\t" << *HlxPars[1] << endl;
      }
      TpcInOutTree->Fill();
    }
  FAILED:
    count++;
  } // loop over tracks
  return kStOK;
}
//________________________________________________________________________________
Int_t StTpcAlignerMaker::MakeW2S() {
  // Sector to Sector Alignment
  static StThreeVectorD XyzI, XyzO;
  static StThreeVectorD DirI, DirO;
  static Double_t stepMX = 1.e3;
  Double_t StiErr[21];
  Double_t step;
  static StTpcLocalSectorCoordinate              local;
  static Double_t err2xy[3] = {0,0,0}, err2z = 0;
  static StTpcCoordinateTransform transform(gStTpcDb);
  TList SegmentList; SegmentList.SetOwner(kTRUE);
  StSPtrVecTrackNode& trackNode = pEvent->trackNodes();
  UInt_t nTracks = trackNode.size();
  StBTofCollection *btofcol = pEvent->btofCollection();
  for (UInt_t i=0; i < nTracks; i++) {
    StTrackNode *node = trackNode[i]; 
    if (!node) continue;
    StGlobalTrack  *gTrack = static_cast<StGlobalTrack *>(node->track(global));
    if (! gTrack ) continue;
    if (gTrack->flag() < 0) continue;
    if (! gTrack->detectorInfo()) continue;
    if (gTrack->TestBit(kRejected)) continue;
    if (TriggerId && btofcol &&
	! gTrack->TestBit(kComingFromOutSide) &&
	! gTrack->TestBit(kComingFromInSideTofMatched) &&
	! gTrack->TestBit(kNoToFDependece)) continue;
    const StThreeVectorF &pxyz = gTrack->geometry()->momentum();
    Double_t pMomentum = pxyz.mag();
    if (TMath::Abs(bField) < 0.01) pMomentum = 1000;
    if (pMomentum < 1.0) continue;
    StPtrVecHit hvec   = gTrack->detectorInfo()->hits();
    StTpcHit *tpcHit = 0;
    if (hvec.size()){
      //      Int_t Id = gTrack->key();
      if (gTrack->fitTraits().numberOfFitPoints(kTpcId) < 10) continue;
      TList HitList;
      PrPP(track,i);
      for (UInt_t j=0; j<hvec.size(); j++) {// hit loop
	if (! hvec[j]) continue;
	if (hvec[j]->detector() != kTpcId) continue;
	tpcHit = (StTpcHit *) hvec[j];
	if (_debug) {
	  PrPP(hit,*tpcHit);
	}
	HitList.Add(tpcHit);
      }	
      HitList.Sort();
      TIter next(&HitList);
      Int_t oldSect = -1;
      SectorSegment *ssegm = 0;
      while ((tpcHit = (StTpcHit *) next())) {
	Int_t sector = tpcHit->sector();
	if (!ssegm || sector != oldSect) {
	  ssegm = new SectorSegment(sector);
	  SegmentList.Add(ssegm);
	  oldSect = sector;
	}
	ssegm->List()->Add(tpcHit); 
      }
    }
  }
  if (SegmentList.GetSize() < 2) return kStOK;
  // Fit Segments
  SegmentList.Sort();
  TIter nextSegment(&SegmentList);
  SectorSegment *ssegm = 0;
  while ((ssegm = (SectorSegment *) nextSegment())) {
    TIter nextHit(ssegm->List());
    StTpcHit *tpcHit = 0;
    Int_t nh = 0;
    //    ssegm->Helix() = THelixFitter();
    Double_t driftZ = 0;
    while ((tpcHit = (StTpcHit *) nextHit())) {
      Int_t sector = tpcHit->sector();
      Int_t row    = tpcHit->padrow();
      StThreeVectorD global(tpcHit->position());
      StThreeVectorD xyz;
      StTpcDb::instance()->Sup12S2Glob(sector).MasterToLocal(global.xyz(), xyz.xyz());
      ssegm->Helix().Add(global.xyz());
      if (tpcHit->positionError().perp2() == 0 || tpcHit->positionError().z() == 0) {
	if (row <= St_tpcPadConfigC::instance()->innerPadRows(sector)) StiTpcInnerHitErrorCalculator::instance()->calculateError(200-xyz[2], 0., 0., err2xy[0], err2z);
	else                                                           StiTpcOuterHitErrorCalculator::instance()->calculateError(200-xyz[2], 0., 0., err2xy[0], err2z);
      } else {
	err2xy[0] = tpcHit->positionError().x()*tpcHit->positionError().x();
	err2xy[0] = 0;
	err2xy[2] = tpcHit->positionError().y()*tpcHit->positionError().y();
	err2z     = tpcHit->positionError().z()*tpcHit->positionError().z();
      }
      ssegm->Helix().AddErr(err2xy,err2z);
      if (Debug()%10 > 5) {
	cout << nh << "\t" << *tpcHit 
	     << " loc " << xyz 
	     << " err xy/z " << TMath::Sqrt(err2xy[0]) << " " << TMath::Sqrt(err2z) << endl;
      }
      if (row < ssegm->fRowMin) {ssegm->fRowMin = row;}
      driftZ += xyz.z();
      nh++;
    }
    if (nh < 5) continue;
    HelixPar_t *HlxPars = &ssegm->HlxPar;
    HlxPars->DriftZ = driftZ/nh;
    ssegm->Helix().Fit();
    ssegm->Helix().MakeErrs();
    ssegm->SetStatus(0);
    //    ssegm->Helix().Backward();
    THelixFitter helix =  ssegm->Helix();
    //      if (io) helix.Backward();
    Int_t sector = ssegm->Sector();
    Int_t row    = ssegm->fRowMin;
    Double_t Y = transform.yFromRow(sector, row);
    Double_t RefSurfice[4] = {- Y, 0, 1, 0};
    Double_t xyz123L[3] = {0, - RefSurfice[0], 0};
    Double_t xyz123G[3];
    Double_t *RefSurficeG = HlxPars->RefSurficeG;
    StTpcDb::instance()->Sup12S2Glob(sector).LocalToMaster(xyz123L, xyz123G);
    StTpcDb::instance()->Sup12S2Glob(sector).LocalToMasterVect(&RefSurfice[1], &RefSurficeG[1]);
    RefSurficeG[0] = - (xyz123G[0]*RefSurficeG[1] + xyz123G[1]*RefSurficeG[2] + xyz123G[2]*RefSurficeG[3]);
    if (Debug() > 2) {
      for (Int_t j = 0; j < 4; j++) {
	cout << "\tHlxPars->RefSurficeG[" << j << "] = " << HlxPars->RefSurficeG[j];
      }
      cout << endl;
    }
    *HlxPars = helix;
    step = helix.Step(stepMX, RefSurficeG, 4, HlxPars->xyzG(), HlxPars->pxyzG(),1);
    if (TMath::Abs(step) >= stepMX) continue;
    HlxPars->step = step;
    HlxPars->Rho = helix.GetRho();
    HlxPars->dRho = helix.GetDRho();
    helix.StiEmx(StiErr);
    StTpcDb::instance()->Sup12S2Glob(ssegm->Sector()).MasterToLocal(HlxPars->xyzG(), HlxPars->xyz());
    StTpcDb::instance()->Sup12S2Glob(ssegm->Sector()).MasterToLocalVect(HlxPars->pxyzG(), HlxPars->pxyz());
    TRSymMatrix StiMtx(6,StiErr); // PrPP(Make,StiMtx);
    TRMatrix S2R = GetSti2R(HlxPars->nx, HlxPars->ny, HlxPars->nz);
    TRSymMatrix Cov2(S2R,TRArray::kATxSxA,StiMtx);// PrPP(Make,Cov2);
    memcpy(HlxPars->fCov, Cov2.GetArray(), 15*sizeof(Double_t));
    HlxPars->sector = ssegm->Sector();
    PrPP(Make,*HlxPars);
    if (Debug()%10 > 0) ssegm->Print();
  }
  Int_t NoSegm = SegmentList.GetSize();
  if (NoSegm > 1) {
    HelixPar_t    &HlxParW   = *&fTpcW2SMatch->HlxParW;
    HelixPar_t    &HlxParS   = *&fTpcW2SMatch->HlxParS;
    HelixPar_t    &HlxParW2S = *&fTpcW2SMatch->HlxParW2S;
    TGeoHMatrix   &RW2S      = *&fTpcW2SMatch->RW2S;
    for (Int_t k = 0; k < NoSegm; k++) { // W
      if (! SegmentList.At(k)) continue;
      SectorSegment *ssegW = (SectorSegment *)  SegmentList.At(k);
      if (ssegW->Status()) continue;
      Int_t sectorW = ssegW->Sector();
      if (! sectorW) continue;
      Int_t RowsW = ssegW->fRowMin;
      for (Int_t l = 0; l < NoSegm; l++) { // S
	fTpcW2SMatch->Clear();
	if (l == k) continue;
	if (! SegmentList.At(l)) continue;
	SectorSegment *ssegS = (SectorSegment *)  SegmentList.At(l);
	if (ssegS->Status()) continue;
	Int_t sectorS = ssegS->Sector();
	if (sectorW == sectorS) continue;
	Int_t RowsS = ssegS->fRowMin;
	//	HlxParS =  ssegS->Helix();
	HlxParW =  ssegW->HlxPar;                PrP2(MakeW,HlxParW);
	HlxParS =  ssegS->HlxPar;                PrP2(MakeS,HlxParS);
	DEBUG_LEVEL {
	  cout << "ssegW\t"; ssegW->Print();
	  cout << "ssegS\t"; ssegS->Print();
	}
	DEBUG_LEVEL {
	  cout <<   "sectorW " << sectorW << "\tRowsW [" << RowsW << "]" 
	       << "\tsectorS " << sectorS << "\tRowsS [" << RowsS << "]" << endl;
	  if (_debug) {
	    cout << "W: " << sectorW; StTpcDb::instance()->Sup12S2Tpc(sectorW).Print();
	    cout << "S: " << sectorS; StTpcDb::instance()->Sup12S2Tpc(sectorS).Print();
	    cout << "SI: " << sectorS; StTpcDb::instance()->Sup12S2Tpc(sectorS).Inverse().Print();
	  }
	}
	RW2S = StTpcDb::instance()->Sup12S2Tpc(sectorS).Inverse() * StTpcDb::instance()->Sup12S2Tpc(sectorW); 
	DEBUG_LEVEL {
	  cout << "RW2S\t"; RW2S.Print();
	}
	HlxParW2S = HlxParW;
	HlxParW2S.sector = ssegS->Sector() + 100*ssegW->Sector();
	PrPP(Before,HlxParW2S);
	PrPP(After,HlxParW2S);
	THelixTrack helixW2S(HlxParW2S.xyzG(),HlxParW2S.pxyzG(),HlxParW2S.Rho,HlxParW2S.dRho);  //=  ssegW->Helix(); 
	if (Debug() > 2) {
	  for (Int_t j = 0; j < 4; j++) {
	    cout << "HlxParW.RefSurficeG[" << j << "] = " << HlxParW.RefSurficeG[j] 
		 << "\tHlxParS.RefSurficeG[" << j << "] = " << HlxParS.RefSurficeG[j] << endl;
	  }
	}
	step = helixW2S.Step(stepMX, HlxParS.RefSurficeG, 4, HlxParW2S.xyzG(), HlxParW2S.pxyzG(),1); 
	if (TMath::Abs(step) >= stepMX) continue;
	CheckDirection(&HlxParW2S);
	HlxParW2S.step = step;
	HlxParW2S.Rho = helixW2S.GetRho();
	HlxParW2S.dRho = helixW2S.GetDRho();
	StTpcDb::instance()->Sup12S2Glob(sectorS).MasterToLocal(HlxParW2S.xyzG(), HlxParW2S.xyz());
	StTpcDb::instance()->Sup12S2Glob(sectorS).MasterToLocalVect(HlxParW2S.pxyzG(), HlxParW2S.pxyz());
	PrPP(Make,HlxParW2S);
	const Char_t * names[6] = {"x","y","z","nx","ny","nz"};
	Double_t *s = HlxParS.xyz();
	Double_t *w = HlxParW2S.xyz();
	DEBUG_LEVEL {
	  cout << "Matching segment  from sectorW " << sectorW << " to sectorS " << sectorS
	       << " at step = " << step << endl;
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
      }
      fTpcW2SMatch->TriggerId = TriggerId;
      TpcW2STree->Fill();
    }
  }
  return kStOK;
}
