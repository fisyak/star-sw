//*-- Author : Yuri Fisyak
#include "StMessMgr.h"
#include "StEventTypes.h"
#include "StiMassFitMaker.h"
#include "Sti/StiKalmanTrack.h"
#include "Sti/StiKalmanTrackNode.h"
#include "Sti/StiHit.h"
#include "Sti/StiToolkit.h"
#include "StdEdxY2Maker/StTrackCombPiD.h"
#include "StiMaker/StiStEventFiller.h"
#include "StEvent/StTrackMassFit.h"
ClassImp(StiMassFitMaker)
//_____________________________________________________________________________
Int_t StiMassFitMaker::Make() {
  if (! StiStEventFiller::Node2TrackMap().size()) {
    LOG_WARN <<"StiMassFitMaker::Make\t"
	 << "Mapping between the StTrackNodes and the StiKalmanTracks is empty.  Exit." << endm;
    return kStWarn;
  }
  StEvent* pEvent = (StEvent*) StMaker::GetChain()->GetInputDS("StEvent");
  if (!pEvent) return kStOk;
  // Save StTrackCombPiD state
  Bool_t IsCalibrationModeSave = StTrackCombPiD::IsCalibrationMode(); StTrackCombPiD::SetCalibrationMode(kFALSE);
  StTrackCombPiD::PiDStatusIDs DefaulTpcMethodSave = StTrackCombPiD::DefaulTpcMethod(); StTrackCombPiD::SetDefaulTpcMethod(StTrackCombPiD::kdNdx);
  StSPtrVecTrackNode& trackNode = pEvent->trackNodes();
  UInt_t nTracks = trackNode.size();
  for (UInt_t  i=0; i < nTracks; i++) {
    StTrackNode *node = trackNode[i]; if (!node) continue;
    const StiKalmanTrack *kTrack = StiStEventFiller::Node2TrackMap()[node];
    if (! kTrack) continue;
    StGlobalTrack  *gTrack = dynamic_cast<StGlobalTrack *>(node->track(global));
    if (gTrack && gTrack->bad()) {gTrack = 0;}
    if (! gTrack ||  gTrack->flag() <= 0) continue;
    StPrimaryTrack *pTrack = 0;
    if (gTrack) {
      pTrack = static_cast<StPrimaryTrack*>(node->track(primary));
    }
    if (pTrack && pTrack->bad()) {pTrack = 0;}
    StTrackCombPiD PiD = StTrackCombPiD(gTrack);
    if (PiD.Status() < 0) continue;
    //    kTrack->setFirstNode(kTrack->getInnerMostNode());
    //    kTrack->setLastNode(kTrack->getOuterMostNode());
    if (Debug()) {
      gTrack->Print();
      if (Debug() > 1) {
	kTrack->print("");
      }
      PiD.Print();
    }
    StiKalmanTrackNode* stinode = kTrack->getInnOutMostNode(0,kKeepHit+kGoodHit+kTpcOnly);
    if (! stinode) {
      static Int_t iBreak = 0;
      iBreak++;
      continue;
    }
    Int_t   NDF = 2*kTrack->getFitPointCount(0) - 5;
    Int_t pdg = 211;
    if (kTrack->getCharge() < 0) pdg = -211;
    Float_t Chi2 = kTrack->getChi2()*NDF;
    StTrackMassFit *mf = new StTrackMassFit(gTrack->key(), stinode->getMomentumF().mag(), pdg,  Chi2, NDF);
    node->addTrack(mf);
    if (Debug()) {
      cout << "pdg = " << pdg << "\tpInTpc = " <<   stinode->getMomentumF().mag() << endl;
      if (Debug() > 1) {
	mf->Print();
      }
    }
    const std::vector<Int_t> &PDGList = PiD.GetPDG();
    for (auto pdg : PDGList) {
      if (pdg == -1) continue;
      if (TMath::Abs(pdg) == 211 ||
	  TMath::Abs(pdg) ==  13) {
	continue;
      }
      StiTrack::setPDG(pdg);
      StiKalmanTrack *cTrack = StiToolkit::instance()->getTrackFactory()->getInstance();
      *cTrack = *kTrack;
      if (cTrack->getLastNode()->isDca()) cTrack->removeLastNode();
      Int_t errType = cTrack->refit();
      if (errType) continue;
      StiHit dcaHit; dcaHit.makeDca();
      StiTrackNode *extenDca = cTrack->extendToVertex(&dcaHit);
      if (extenDca) {
	cTrack->add(extenDca,kOutsideIn);
	if (Debug() >= 1) ((StiKalmanTrackNode *)extenDca)->PrintpT("Fit");
	if (Debug() >  1) cTrack->print();
	cTrack->reduce();
	StiKalmanTrackNode *tNode = cTrack->getInnerMostNode();
	if (! tNode) continue;
	if (! tNode->isDca()) continue;
	const StiNodePars &pars = tNode->fitPars(); 
	const StiNodeErrs &errs = tNode->fitErrs();
	Double_t alfa = tNode->getAlpha();
	Double_t setp[6] = {pars.y(),    pars.z(),    pars.eta(),
			    pars.ptin(), pars.tanl(), pars.curv()};
	setp[2]+= alfa;  
	Double_t sete[15];
	for (int i=1,li=1,jj=0;i< kNPars;li+=++i) {
	  for (int j=1;j<=i;j++) {sete[jj++]=errs.G()[li+j];}}
	StDcaGeometry *dca = new StDcaGeometry;
	dca->set(setp,sete);
	if (Debug()) {
	  dca->Print();
	}
	NDF = 2*cTrack->getFitPointCount(0) - 5;
	Chi2 = cTrack->getChi2()*NDF;
	StiKalmanTrackNode* stinode = cTrack->getInnOutMostNode(0,kKeepHit+kGoodHit+kTpcOnly);
	StTrackMassFit *mf = new StTrackMassFit(gTrack->key(), stinode->getMomentumF().mag(), pdg, Chi2, NDF, dca);
	node->addTrack(mf);
	if (Debug() > 1) {
	  cTrack->print();
	  mf->setNode(node);
	}
      }
      BFactory::Free(cTrack);
    }
    if (Debug()) 
      node->Print();
  }
  StiTrack::setPDG(); // back to default
  if (IsCalibrationModeSave) StTrackCombPiD::SetCalibrationMode(kTRUE);
  StTrackCombPiD::SetDefaulTpcMethod(DefaulTpcMethodSave);
  return kStOK;
}
