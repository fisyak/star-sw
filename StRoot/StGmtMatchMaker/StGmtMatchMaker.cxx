#include "StGmtMatchMaker.h"
#include <stdlib.h>
#include "Riostream.h"
#include "TROOT.h"
#include "TSystem.h"
#include "TMath.h"
#include "TVector3.h"
#include "StThreeVectorD.hh"
#include "StThreeVectorF.hh"
#include "StEvent.h"
#include "TGeoMatrix.h"
#include "StMessMgr.h" 
#include "StTpcDb/StTpcDb.h"
#include "StDetectorDbMaker/StGmtSurveyC.h"
#include "StGmtCollection.h"
#include "StGmtHit.h"
#include "StGmtPoint.h"
#include "StGmtPidTraits.h"
#include "StTrackNode.h"
#include "StTrack.h"
#include "StTrackGeometry.h"
#include "StTrackDetectorInfo.h"
#include "StPrimaryTrack.h"
#include "StGlobalTrack.h"
#include "StDcaGeometry.h"
#include "TRVector.h"
#include "StGmtRawMaker/StGmtConsts.h"
Int_t    StGmtMatchMaker::fMinNoHits = 15;
Double_t StGmtMatchMaker::fpCut = 0.2;;
static   Int_t _debug = 0;
//________________________________________________________________________________
Int_t StGmtMatchMaker::Make() {
  pEvent = (StEvent*) GetInputDS("StEvent");
  if (! pEvent) return kStOK;
  StGmtCollection* GmtCollection = pEvent->gmtCollection();
  if (! GmtCollection) {
    if (Debug()) { LOG_WARN << "No GMT Collections" << endm; }
    return kStOK;
  }
  if (GmtCollection->getNumHits() == 0) return kStOK;
  StSPtrVecTrackNode& theNodes = pEvent->trackNodes();
  UInt_t nnodes = theNodes.size();
  if (! nnodes) { cout << "No tracks" << endl; return kStOK;}
  if (! fRotMHash) MakeListOfRotations();
  Match();
  return kStOK;
}
//________________________________________________________________________________
void StGmtMatchMaker::MakeListOfRotations() {
  if (fRotMHash) return;
  fRotMHash = new THashList(100,0);
  //  THashList *hash = 0;
  const TGeoHMatrix& tpc2Glob = gStTpcDb->Tpc2GlobalMatrix();
  for(int module=0;module<  kGmtNumModules;module++)    {
    TGeoHMatrix *L            = new TGeoHMatrix(StGmtOnModule::instance()->GetMatrix(module));
    L->SetName(Form("L%i",module));
    fRotMHash->Add(L);
    TGeoHMatrix GmtOnGlob      = tpc2Glob * StGmtOnTpc::instance()->GetMatrix(module) * (*L);
    TGeoHMatrix *R             = new TGeoHMatrix(GmtOnGlob);
    R->SetName(Form("R%i",module));
    fRotMHash->Add(R);
  }
}
//______________________________________________________________________________
Int_t  StGmtMatchMaker::Match() {
  Int_t iok = 1;
  StGmtCollection* GmtCollection = pEvent->gmtCollection();
  StSPtrVecTrackNode& theNodes = pEvent->trackNodes();
  UInt_t nnodes = theNodes.size();
  if (! nnodes) { cout << "No tracks" << endl; return iok;}
  Int_t nTotMatch = 0;
  //  Create and Fill the GmtTrack objects
  StGmtPointCollection* gmtPointCol = GmtCollection->getPointCollection();  
  assert(fRotMHash);
  for (UInt_t module = 0; module < GmtCollection->getNumModules(); module++) {
    StGmtHitCollection* GmtHitCollection = GmtCollection->getHitCollection(module);
    StSPtrVecGmtHit& gmtHitVec = GmtHitCollection->getHitVec();
    UInt_t NoGMThits = gmtHitVec.size();
    if (! NoGMThits) continue;
    // Check Y and Z
    Int_t nY = 0, nZ = 0;
    for (UInt_t l = 0; l < NoGMThits; l++) {
      StGmtHit *hitY = gmtHitVec[l];
      if (! hitY) continue; 
      if (hitY->getXorY() == 0) nY++;
      else                      nZ++;
    }
    if (! nY || ! nZ) continue;
    TGeoHMatrix *comb = (TGeoHMatrix *) fRotMHash->FindObject(Form("R%i",module));
    if (! comb) continue;
    if (_debug) {
      cout << comb->GetName() << "\tmodule = " << module << endl;
      comb->Print();
    }
    static Double_t dz[2] = {50.00, kGmtSlast/2.};
    static Double_t dx[2] = {50.00, kGmtSlast/2.};
    Double_t *rot = comb->GetRotationMatrix();
    Double_t *tra = comb->GetTranslation();
    const StThreeVectorD unit(1.,0.,0.);
    const StThreeVectorD zero(0.,0.,0.);
    StThreeVectorD normal(rot[2],      rot[5],      rot[8]);
    StThreeVectorD middle(tra);
    if (_debug) cout << "Global middle:" << middle << "\tnormal:" << normal << endl;
    comb->LocalToMaster(zero.xyz(),middle.xyz());
    comb->LocalToMasterVect(unit.xyz(), normal.xyz());
    if (_debug) cout << "Local middle:" << middle << "\tnormal:" << normal << endl;
    Double_t zM = middle.z();
    Double_t phiM = TMath::RadToDeg()*middle.phi();
    for (UInt_t i=0; i<nnodes; i++) {
      StTrackNode *node = theNodes[i];
      if (! node) continue;
      StTrack *Track = node->track(global);
      if (! Track) continue;
      StGlobalTrack *gTrack = (StGlobalTrack *) Track;
      if (gTrack->fitTraits().numberOfFitPoints() < fMinNoHits) continue;
      StDcaGeometry *dca = gTrack->dcaGeometry();
      if (! dca) continue;
      StPrimaryTrack *pTrack = (StPrimaryTrack *) node->track(primary);
      StTrack *tracks[2] = {gTrack, pTrack};
      for (Int_t t = 0; t <2 ; t++) {
	Track = tracks[t];
	if (! Track) continue;
	StThreeVectorD g3 = Track->geometry()->momentum();
	Double_t pMom = g3.mag();
	if (pMom < fpCut) continue;
	StPhysicalHelixD helixO = Track->outerGeometry()->helix();
	Double_t R_tof[2]= {210., 216.};  // inner and outer surfaces
	pair<Double_t,Double_t> shR = helixO.pathLength(0.5*(R_tof[0]+R_tof[1]));
	if (TMath::Abs(shR.first) > 200 && TMath::Abs(shR.second) > 200) continue; 
	Double_t stepR = (shR.first > 0) ? shR.first : shR.second;
	StThreeVectorD xyzR = helixO.at(stepR);
	Double_t phiR = TMath::RadToDeg()*xyzR.phi();
	if (_debug) 
	  cout << "\t shR " << shR.first << "\t" << shR.second << "\tstepR " << stepR 
	       << "\txyzR\t" << xyzR << "\tphiR\t" << phiR << endl;
	if (_debug) cout << "phiR = " << phiR << "\tphiM = " << phiM << "\tzM = " << zM << endl;
	Double_t dPhi = phiR - phiM; 
	if (dPhi >  360) dPhi -= 360;
	if (dPhi < -360) dPhi += 360;
	if (TMath::Abs(dPhi) > 15) continue;
	if (_debug) cout << "zR = " << xyzR.z() << "\tzM = " << tra[2] << endl;
	if (TMath::Abs(xyzR.z() -  tra[2]) > 20) continue;
	Double_t sh = helixO.pathLength(middle, normal); 
	if (_debug) {
	  cout << "StHelix sh " << sh 
	       << "\t shR " << shR.first << "\t" << shR.second
	       << endl;
	}
	StThreeVectorD xyzG = helixO.at(sh); if (_debug) cout << "StHelix xyzG\t" << xyzG << endl;
	StThreeVectorD dR = xyzR - xyzG; if (_debug) cout << "dR\t" << dR << " dist = " << dR.magnitude() << endl;
	if (dR.magnitude() > 50) continue;
	if (sh < -5e2 || sh > 5e2) continue;
	if (_debug) { 
	  StThreeVectorD dX = xyzG - helixO.at(0); 
	  cout << "Qi: " << Track->geometry()->charge() 
	       << "\tQo: " << Track->outerGeometry()->charge()
	       << "\tdX " << dX << endl;
	  cout << *dca << endl;
	}
	Double_t uvPred[3];
	comb->MasterToLocal(xyzG.xyz(),uvPred);
	TRVector xyzL(3,uvPred); if (_debug) cout << "StHelix xyzL\t" << xyzL << endl;
	Double_t dirGPred[3] = {helixO.cx(sh),helixO.cy(sh),helixO.cz(sh)};
	Double_t dxyzL[3];
	comb->MasterToLocalVect(dirGPred,dxyzL);
	Double_t tuvPred[2] = {dxyzL[1]/dxyzL[0], dxyzL[2]/dxyzL[0]};
	if (_debug) cout << "StHelix tU/tV =  " << tuvPred[0] << "\t" << tuvPred[1] << endl; 
	Int_t k = 0; // gmt
	if (TMath::Abs(uvPred[1]) > dx[k] + 1.0) continue;
	if (TMath::Abs(uvPred[2]) > dz[k] + 1.0) continue;
	Int_t TrackId = Track->key();
	StGmtPoint *point = 0, *pointBest = 0;
	StGmtPidTraits *pid = 0, *pidBest = 0;
	for (UInt_t l = 0; l < NoGMThits; l++) {
	  StGmtHit *hitY = gmtHitVec[l];
	  if (! hitY) continue;
	  if (hitY->getXorY() != 0) continue; // x => Z
	  Float_t u = hitY->getLocal();
	  if (TMath::Abs(u - uvPred[1]) > kGmtSlast) continue;
	  for (UInt_t k = 0; k < NoGMThits; k++) {
	    if (l == k) continue;
	    StGmtHit *hitZ = gmtHitVec[k];
	    if (! hitZ) continue;
	    if (hitZ->getXorY() != 1) continue; // y => Y
	    Float_t v = hitZ->getLocal();
	    if (TMath::Abs(v - uvPred[2]) > kGmtSlast) continue;
	    assert(! point || ! pid);
	    StThreeVectorF xyzGF(xyzG);
	    StThreeVectorF uvPredF(uvPred);
	    point = new StGmtPoint(*hitY, *hitZ, TrackId, xyzGF, uvPredF);
	    point->setAssociatedTrack(Track);
	    pid = new StGmtPidTraits(point);
	    // Check for the best match
	    if (pidBest) {
	      if (pid->deviation() < pidBest->deviation()) {
		delete pointBest; 
		delete pidBest;
		pointBest = point;
                pidBest  = pid;
		point = 0;
		pid = 0;
	      } else {
		SafeDelete(point);
		SafeDelete(pid);
	      }
	    } else {
	      pointBest = point;
	      pidBest  = pid;
	      point = 0;
	      pid = 0;
	    }
	  } // hit Z
	} // hit Y
	if (! pointBest) continue;
	StTrackDetectorInfo* detInfo = Track->detectorInfo();
	if (detInfo) detInfo->addHit(pointBest);
	gmtPointCol->getPointVec().push_back(pointBest);
	// detectorInfo
	Track->addPidTraits(pidBest);;
      } // global primary
    } // nodes
  } // loop over modules
  if (nTotMatch) iok = 0;
  return iok;
}  
