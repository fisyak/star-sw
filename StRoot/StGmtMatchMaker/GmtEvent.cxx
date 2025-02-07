#include <assert.h>
#include <string.h>
#include "GmtTrack.h"
#include "TRefArray.h"
#include "TRef.h"
#include "TH1.h"
#include "TH2.h"
#include "TStyle.h"
#include "TCanvas.h"
#include "TF1.h"
#include "StEvent.h"
#include "StPrimaryVertex.h"
#include "StEventInfo.h"
#include "StEventSummary.h"
#include "StTrack.h"
#include "StTrackNode.h"
#include "StPrimaryTrack.h"
#include "StGlobalTrack.h"
#include "StTrackDetectorInfo.h"
#include "StTrackGeometry.h"
#include "StDcaGeometry.h"
#include "TGeoMatrix.h"
#include "StarRoot/THelixTrack.h"
#include "GmtEvent.h"
#include "StGmtPoint.h"
#include "StGmtPidTraits.h"
#include "TKey.h"
#include "TDirectory.h"
#include "TClass.h"
#include "TRVector.h"
#include "TRSymMatrix.h"
#include "StGmtHit.h"
#include "StGmtHitCollection.h"
#include "StGmtCollection.h"
#include "TVector2.h"
//#define __OnlyPrimary__

TClonesArray *GmtEvent::fgTracks = 0;
TClonesArray *GmtEvent::fgPoints = 0;
THashList *GmtEvent::fRotList = 0;


static Int_t _debug = 0;
//______________________________________________________________________________
GmtEvent::GmtEvent() : fIsValid(kFALSE)
{
  // Create an GmtEvent object.
  // When the constructor is invoked for the first time, the class static
  // variable fgTracks is 0 and the TClonesArray fgTracks is created.
  
  if (!fgTracks) fgTracks = new TClonesArray("GmtTrack", 1000);
  fTracks = fgTracks;
  fNtrack = 0;
  if (!fgPoints) fgPoints = new TClonesArray("StGmtPoint", 1000);
  fPoints = fgPoints;
  fNpoint = 0;
}

//______________________________________________________________________________
GmtEvent::~GmtEvent()
{
  Clear();
  SafeDelete(fRotList);
}

//______________________________________________________________________________
Int_t  GmtEvent::Build(StEvent *pEvent, Double_t pCut, Int_t NoMinHit) {
  Clear();
  Int_t iok = 1;
  fIsValid = kFALSE;
  StGmtCollection* GmtCollection = pEvent->gmtCollection();
  StSPtrVecTrackNode& theNodes = pEvent->trackNodes();
  UInt_t nnodes = theNodes.size();
  if (! nnodes) { cout << "No tracks" << endl; return iok;}
#if 0
  StEventInfo*      info = pEvent->info();
  Int_t ev = 0, run = 0, time = 0;
  if (info) {
    ev   = info->id();
    run  = info->runId();
    time = info->time();
  }
  StEventSummary* summary = pEvent->summary();
  Double32_t field = 0;
  if (summary) field = summary->magneticField();
  SetHeader(ev,run,time,field);
  SetFlag(1);
#endif
  Int_t nTotMatch = 0;
  //  Create and Fill the GmtTrack objects
  StGmtPointCollection* gmtPointCol = GmtCollection->getPointCollection();  
  THashList *fRotList = RotMatrices();
  assert(fRotList);
  for (UInt_t module = 0; module < GmtCollection->getNumModules(); module++) {
    StGmtHitCollection* GmtHitCollection = GmtCollection->getHitCollection(module);
    StSPtrVecGmtHit& gmtHitVec = GmtHitCollection->getHitVec();
    UInt_t NoGMThits = gmtHitVec.size();
    if (! NoGMThits) continue;
    TGeoHMatrix *comb = (TGeoHMatrix *) fRotList->FindObject(Form("R%i",module));
    if (! comb) continue;
    if (_debug) {
      cout << comb->GetName() << "\tmodule = " << module << endl;
      comb->Print();
    }
    static Double_t dXYModule = 0.0080*kGmtNumPstripsPerModule;
    static Double_t dz[2] = {50.00, dXYModule/2.};
    static Double_t dx[2] = {50.00, dXYModule/2.};
    Double_t *rot = comb->GetRotationMatrix();
    Double_t *tra = comb->GetTranslation();
    const StThreeVectorD unit(1.,0.,0.);
    const StThreeVectorD zero(0.,0.,0.);
    StThreeVectorD normal(rot[2],      rot[5],      rot[8]);
    StThreeVectorD middle(tra);
    if (_debug) cout << "middle:" << middle << "\tnormal:" << normal << endl;
    comb->LocalToMaster(zero.xyz(),middle.xyz());
    comb->LocalToMasterVect(unit.xyz(), normal.xyz());
    if (_debug) cout << "middle:" << middle << "\tnormal:" << normal << endl;
    Double_t zM = middle.z();
    Double_t phiM = TMath::RadToDeg()*middle.phi();
    for (UInt_t i=0; i<nnodes; i++) {
      StTrackNode *node = theNodes[i];
      if (! node) continue;
      StTrack *Track = node->track(global);
      if (! Track) continue;
      StGlobalTrack *gTrack = (StGlobalTrack *) Track;
      if (gTrack->fitTraits().numberOfFitPoints() < NoMinHit) continue;
      StDcaGeometry *dca = gTrack->dcaGeometry();
      if (! dca) continue;
      StPrimaryTrack *pTrack = (StPrimaryTrack *) node->track(primary);
#ifdef __OnlyPrimary__
      if (! pTrack) continue;
      Track = (StTrack *) pTrack;
#else
      if (pTrack) Track = (StTrack *) pTrack;
#endif
      StThreeVectorD g3 = Track->geometry()->momentum();
      Double_t pMom = g3.mag();
      if (pMom < pCut) continue;
#if 0
      Double_t pT = g3.perp();
      GmtTrack *track = AddGmtTrack();
      Double_t InvpT = 0;
      Double_t TanL = 999999;
      if (TMath::Abs(pT) > 1.e-7) {
	InvpT = Track->geometry()->charge()/pT;
	TanL = g3.z()/pT;
      }
      track->SetInvpT(InvpT);
      track->SetPhi(TMath::ATan2(g3.y(),g3.x()));
      track->SetTanL(TanL);
      static const Double_t EC = 2.9979251E-4;
      Double_t Rho = - EC*InvpT*field;
      track->SetRho(Rho);
      track->SetLength(Track->length());
      StTrackDetectorInfo* dinfo=Track->detectorInfo();
      track->SetNpoint(dinfo->numberOfPoints());
#endif
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
#if 0
      Bool_t mIsCrossingMembrain = kTRUE;
      Bool_t mIsPrimary = kFALSE;
      if(pTrack!=0) {
	mIsPrimary = kTRUE;
      }
      StThreeVectorF firstPoint = Track->detectorInfo()->firstPoint();
      StThreeVectorF lastPoint = Track->detectorInfo()->lastPoint();
      if( (firstPoint.z()>0 && lastPoint.z()>0 && xyzG.z()>0) ||
	  (firstPoint.z()<0 && lastPoint.z()<0 && xyzG.z()<0) ) {
	mIsCrossingMembrain = kFALSE;
      }
#endif
      Int_t TrackId = Track->key();
      for (UInt_t l = 0; l < NoGMThits; l++) {
	StGmtHit *hitY = gmtHitVec[l];
	if (! hitY) continue;
	if (hitY->getXorY() != 0) continue; // x => Y
	Float_t u = hitY->getLocal();
	if (TMath::Abs(u - uvPred[1]) > dXYModule) continue;
	for (UInt_t k = 0; k < NoGMThits; k++) {
	  if (l == k) continue;
	  StGmtHit *hitZ = gmtHitVec[k];
	  if (! hitZ) continue;
	  if (hitZ->getXorY() != 1) continue; // y => Z
	  Float_t v = hitZ->getLocal();
	  if (TMath::Abs(v - uvPred[2]) > dXYModule) continue;
	  TClonesArray &points = *fPoints;
	  fNpoint = points.GetEntries();
#if 1
	  new(points[fNpoint]) 
	    StGmtPoint(hitY->id()+100*hitZ->id(), module, TrackId, 
		       xyzG[0], xyzG[1], xyzG[2], //  Global coordinate prediction
		       uvPred[0], uvPred[1], uvPred[2], //  Local coordinate prediction
		       hitY->getLocal(), hitY->getSigma(), hitY->getAdc(),
		       hitY->getErrorLocal(), hitY->getErrorSigma(), hitY->getErrorAdc(),
		       hitZ->getLocal(), hitZ->getSigma(), hitZ->getAdc(),
		       hitZ->getErrorLocal(), hitZ->getErrorSigma(), hitZ->getErrorAdc());
#else
	  new(points[fNpoint]) StGmtPoint(*hitY, *hitZ, TrackId, StThreeVectorF(xyzG), StThreeVectorF(uvPred));
#endif
	  nTotMatch++;
	}
      }
    }
  }
  // Check for the best match
  TClonesArray &points = *fPoints;
  fNpoint = points.GetEntries();
  for (Int_t i = 0; i < fNpoint - 1; i++) {
    StGmtPoint *pointI = (StGmtPoint *) points[i];
    if (! pointI) continue;
    if (pointI->IsZombie()) continue;
    Int_t idI = pointI->id();
    if (idI <= 0) continue;
    TVector2 dI(pointI->local().y() - pointI->yD(), pointI->local().z() - pointI->zD()); 
    for (Int_t j = i+1; j < fNpoint; j++) {
      StGmtPoint *pointJ = (StGmtPoint *) points[j];
      if (! pointJ) continue;
      if (pointJ->IsZombie()) continue;
      Int_t idJ = pointJ->id();
      if (idJ <= 0) continue;
      if (idI != idJ) continue;
      TVector2 dJ(pointJ->local().y() - pointJ->yD(), pointJ->local().z() - pointJ->zD()); 
      if (dI.Mod() > dJ.Mod()) {
	pointI->makeZombie();
      } else {
	pointI->makeZombie();
      }
    }
  }
  fNpoint = points.GetEntries();
  for (Int_t i = 0; i < fNpoint; i++) {
    StGmtPoint *point = (StGmtPoint *) points[i];
    if (point->id() <= 0) continue;
    if (point->IsZombie()) continue;
    gmtPointCol->getPointVec().push_back(new StGmtPoint(*point));
    Int_t TrackId = point->getTrackId();
    for (UInt_t i=0; i<nnodes; i++) {
      StTrackNode *node = theNodes[i];
      if (! node) continue;
      StTrack *Track = node->track(global);
      if (! Track) continue;
      if (TrackId != Track->key()) continue;
      StGlobalTrack *gTrack = (StGlobalTrack *) Track;
      StPrimaryTrack *pTrack = (StPrimaryTrack *) node->track(primary);      
      StTrack *tracks[2] = {gTrack, pTrack};
      for (Int_t k = 0; k < 2; k++) {
	StTrack *Track = tracks[k];
	if (! Track) continue;
	StGmtPidTraits *pidGmt = new StGmtPidTraits(point);
	Track->addPidTraits(pidGmt);;
      }
    }
  }
  fIsValid = kTRUE;
  if (nTotMatch) iok = 0;
  return iok;
}  
#if 0
//______________________________________________________________________________
GmtTrack *GmtEvent::AddGmtTrack()
{
  // Add a new track to the list of tracks for this event.
  // To avoid calling the very time consuming operator new for each track,
  // the standard but not well know C++ operator "new with placement"
  // is called. If tracks[i] is 0, a new GmtTrack object will be created
  // otherwise the previous GmtTrack[i] will be overwritten.
  
  TClonesArray &tracks = *fTracks;
  GmtTrack *track = new(tracks[fNtrack++]) GmtTrack();
  //Save reference to last GmtTrack in the collection of Tracks
  return track;
}
#endif
//______________________________________________________________________________
void GmtEvent::Clear(Option_t * /*option*/)
{
  fTracks->Clear("C"); //will also call GmtTrack::Clear
  //  fPoints->Clear("C"); //will also call Point::Clear
}

//______________________________________________________________________________
void GmtEvent::Reset(Option_t * /*option*/)
{
  // Static function to reset all static objects for this event
  //   fgTracks->Delete(option);
  
  delete fgTracks; fgTracks = 0;
  delete fgPoints; fgPoints = 0;
}
#if 0
//______________________________________________________________________________
void GmtEvent::SetHeader(Int_t i, Int_t run, Int_t date, Double32_t field)
{
  fNtrack = 0;
  fNpoint = 0;
  fEvtHdr.Set(i, run, date, field);
}
#endif
//________________________________________________________________________________
void GmtEvent::Print(Option_t *opt) const {
#if 0
  cout << "Run/GmtEvent\t" << fEvtHdr.GetRun() << "/" << fEvtHdr.GetEvtNum() << "\tDate " << fEvtHdr.GetDate() 
       << "\tField " << fEvtHdr.GetField() << endl;
  cout << "Total no. tracks " << GetTotalNoTracks() << "\tRecorded tracks " << GetNtrack() 
       << "\tRecorded points " << GetNpoint() << endl;
  TRVector vertex(3,GetVertex());
  TRSymMatrix cov(3,GetCovMatrix());
  cout << "Primary vertex " << vertex << endl;
  cout << "Its cov. matrix " << cov << endl;
  for (UInt_t i = 0; i < GetNtrack(); i++) {cout << i << "\t"; GetGmtTrack(i)->Print();}
  for (UInt_t i = 0; i < GetNpoint(); i++) {cout << i << "\t"; GetPoint(i)->Print();}
#endif  
}
//________________________________________________________________________________
void GmtTrack::Print(Option_t *opt) const {
  cout << "GmtTrack: InvpT " << fInvpT << "\tTanL " << fTanL 
       << "\tPhi " << fPhi << "\tRho " << fRho 
       << "\tNpoint " << fNpoint << endl;
}
//________________________________________________________________________________
void GmtEvent::RestoreListOfRotations() {
  if (fRotList) return;
  if (! gDirectory) return;
  fRotList = new THashList(100,0);
  fRotList->SetOwner();
  TIter nextkey(gDirectory->GetListOfKeys() );
  TKey *key;
  while ((key = (TKey*) nextkey())) {
    TObject *obj = key->ReadObj();
    if ( obj->IsA()->InheritsFrom( "TGeoHMatrix" ) ) {
      fRotList->Add(obj);
    }
  }
}
#if 0
//________________________________________________________________________________
void TBase::Loop(Int_t Nevents) {  
#if 0
  struct PlotPar_t {
    const Char_t *Name;
    const Char_t *Title;
    Int_t    nx;
    Int_t    ny;
    Double_t xmin; 
    Double_t xmax; 
    Double_t ymin;
    Double_t ymax;  
  };
  const  PlotPar_t plotUP = // plots for uP
    { "uP","track u", 320, 3, -5.,5., 0.,3. };
  
  const  PlotPar_t plotDu = // plots for u-uP
    { "Du","Du before cut", 250, 3, -2.,2., 0.,3. };
  
  const  PlotPar_t plotDuv = // plots for du & dv
    { "Du","Du cuts", 200, 3, -1.,1., 0.,3. };
  
  TFile *fOut = new TFile(fOutFileName,"recreate");
  TString Name;
  TString Title;
  TString uName;
  TString uTitle;
  enum {NM = 8}; // no. of modules
  //              B 
  TH1F *LocPlots[NM];
  TH1F *  uPlots[NM];
#if 0
  TH1F *    hpT = new TH1F(   "Pt",   "pt", 200, -2., 2.);
  TH1F *    hpM = new TH1F( "Ptot", "ptot", 200,  0., 5.);
#endif
  TH1F * uPAll  = new TH1F("UPall","uPall", plotUP.nx, plotUP.xmin, plotUP.xmax);
  TH1F * duB[NM][2];
  TH1F * dvB[NM];
#if 0
  TH1F * uCuts[NM];
  TH1F * xCuts[NM];
#endif
  TH1F * uCut   = new TH1F("Ucut","uc", plotDu.nx, plotDu.xmin, plotDu.xmax);
  TH1F * vCut   = new TH1F("Vcut","vc", 200, -3., 3.);
  TH2F * dMin   = new TH2F("DMin","vumin",100,-0.75,0.75,100,-0.75,0.75); 
  TH1F * vMin   = new TH1F("VMin","vmin", plotDuv.nx, plotDuv.xmin, plotDuv.xmax);
  TH1F * uMin   = new TH1F("UMin","umin", plotDuv.nx, plotDuv.xmin, plotDuv.xmax);
#if 0
  TH1F * uMinC  = new TH1F("UMinC","umC", plotDuv.nx, plotDuv.xmin, plotDuv.xmax);
#endif
  memset(LocPlots,0,NM*sizeof(TH1F *));
  memset(  uPlots,0,NM*sizeof(TH1F *));
  for (int M = 0; M < NM; M++) {// over gmt Modules
    uName  = Form("UModule%i", M+1);
    uTitle = Form("du for M%i", M+1);
    duB[M][0] =  new TH1F(uName, uTitle, plotDuv.nx, plotDuv.xmin, plotDuv.xmax );
    uName  = Form("VModule%i", M+1);
    uTitle = Form("dv for M%i", M+1);
    dvB[M] =  new TH1F(uName, uTitle, plotDuv.nx, plotDuv.xmin, plotDuv.xmax );
    uName  = Form("UModule%iVcut", M+1);
    uTitle = Form("du for M%i after Vcut", M+1);
    duB[M][1] =  new TH1F(uName, uTitle, plotDuv.nx, plotDuv.xmin, plotDuv.xmax );
    Int_t module    = M;
    uName  = plotUP.Name;
    uName += Form("M%i", module);
    uTitle = Form("uP for Module %i", module);
    uPlots[module] = 
      new TH1F(uName, uTitle, plotUP.nx, plotUP.xmin, plotUP.xmax );
    uName  = Form("%sM%i", plotDu.Name, module);
    uTitle = Form("u-uP for M %i", module);
#if 0
    uCuts[module]= 
      new TH1F(uName, uTitle, plotDu.nx, plotDu.xmin, plotDu.xmax );
    uName  = Form("%sxM%i", plotDu.Name, module);
    uTitle = Form("u-uP corr M %i", module);
    xCuts[module]= 
      new TH1F(uName, uTitle, plotDu.nx, plotDu.xmin, plotDu.xmax );
#endif
  }
  Long64_t nentries = fChain->GetEntriesFast();
  if (Nevents > 0 && nentries > Nevents) nentries = Nevents;
  Long64_t nbytes = 0, nb = 0;
  Int_t TreeNo = -1;
  TString currentFile("");
  
  for (Long64_t jentry=0; jentry<nentries;jentry++) {
    Long64_t ientry = LoadTree(jentry);
    if (ientry < 0) break;
    nb = fChain->GetEntry(jentry);   nbytes += nb;
    if (! jentry%1000 || TreeNo != fChain->GetTreeNumber()) {
      cout << "Read event \t" << jentry 
	   << " so far, switch to file " << fChain->GetCurrentFile()->GetName() 
	   << endl;
      cout << " current TreeNo: " << TreeNo
	   <<  " new TreeNo: " << fChain->GetTreeNumber() << endl;
      TreeNo = fChain->GetTreeNumber();
    }
    //     if (VertexZCut > 0 && TMath::Abs(fVertex[2]) > VertexZCut) continue;
    UInt_t Ntrack = fEvent->GetTracks()->GetEntriesFast();
    //     int k_used[100000] = {0};    
    for (UInt_t trk = 0; trk < Ntrack; trk++) {
      GmtTrack *track = (GmtTrack *)fEvent->GetTracks()->UncheckedAt(trk);
      if (! track) continue;
#if 0
      Int_t Npoints = track->GetNpoint();
      if (minNoFitPoints > 0 && Npoints%100 < minNoFitPoints) continue;
      if (UseSsd && Npoints < 1000) continue; 
      if (UseSvt && Npoints <  100) continue; 
#endif
      Int_t Nsp = track->GetN();
      double dvmin = 1000.;
      double dumin = 1000.;
      for (Int_t hit = 0; hit < Nsp; hit++) {
	Int_t k = track->GetPointId(hit) - 1;
	//	 assert(k>=0);
	StGmtPoint *point = (StGmtPoint *) fEvent->GetPoint(k);
	if ( k < 0) cout <<" k <0:"<<k<<" hit="<<hit<<" Nsp="<<Nsp<< endl;
	if ( k < 0) continue;
	Int_t module  = point->Barrel();
	Double32_t u = point->GetU();       
	Double32_t v = point->GetV();
	Double32_t uP = point->GetPredU();       
	Double32_t vP = point->GetPredV();
	Double32_t du = u - uP;
	Double32_t dv = v - vP;
#if 0	   
	hpT->Fill(point->GetXyzPGl());
	hpM->Fill(point->GetpMom());
	if (TMath::Abs(point->GetpT()) < 0.2) continue;
#endif
	if ( TMath::Abs(dv) < TMath::Abs(dvmin) ) {dvmin = dv; dumin= du;}
	uPAll->Fill( uP );
	uPlots[module]->Fill( uP );
	
	duB[module][0]->Fill(du);
	dvB[module]->Fill(dv);
	vCut->Fill(dv);
	//	if (TMath::Abs(dv) > rCut ) continue;
	uCut->Fill(du);
	
	duB[module][1]->Fill(du);
	//	if (TMath::Abs(du) > 2.*rCut) continue;
	
      } //hits loop
      if (TMath::Abs(dvmin) < 1000.) {
	dMin->Fill(dvmin,dumin);
	vMin->Fill(dvmin);
	uMin->Fill(dumin);
	//	if (TMath::Abs(dvmin) < rCut ) uMinC->Fill(dumin);
      }	 
    } //track loop
  } //jentry loop (event loop)
  fOut->Write();
#endif
} //end of Loop()
#endif
