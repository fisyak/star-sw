#include "StKFParticleInterface.h"
#include <map>
#include "KFParticleTopoReconstructor.h"
#include "KFMCTrack.h"

#include "TMath.h"
#include "TArrayD.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TDirectory.h"

#include "StPicoDstMaker/StPicoDstMaker.h"
#include "StPicoEvent/StPicoHelix.h"
#include "StPicoEvent/StPicoPhysicalHelix.h"
#include "StPicoEvent/StPicoArrays.h"
#include "StPicoEvent/StPicoDst.h"
#include "StPicoEvent/StPicoEvent.h"
#include "StPicoEvent/StPicoTrack.h"
#include "StPicoEvent/StPicoBTofPidTraits.h"
#include "StPicoEvent/StPicoETofPidTraits.h"
#include "StdEdxY2Maker/StTrackCombPiD.h"
#include "StMaker.h"
#include "StMuDSTMaker/COMMON/StMuDst.h"
#include "THelixTrack.h" 
#include "StPicoEvent/StPicoTrackCovMatrix.h"

#include "StBichsel/Bichsel.h"
#include "StBichsel/StdEdxModel.h"
#include "StProbPidTraits.h"
#include "StMuDSTMaker/COMMON/StMuBTofHit.h"
#include "StMuDSTMaker/COMMON/StMuMcVertex.h"
#include "StMuDSTMaker/COMMON/StMuMcTrack.h"
#include "TLorentzVector.h"
#include "TDatabasePDG.h"
#ifdef __TFG__VERSION__
#include "StDetectorDbMaker/St_beamLineC.h"
#endif /*  __TFG__VERSION__ */

#include <ctime>
#include <algorithm>
#include <stdint.h>

//#define PID_2018
// #define PID_MAY
// #if ! defined(PID_2018) && ! defined( PID_MAY)
// #define PID_JUNE
// #endif
static Int_t _debug = 0;
#define PrPP(A) if (_debug) {std::cout << (#A) << "\t"; A->Print();}
#define PrPO(A) if (_debug) {std::cout << (#A) << "\t"; A.Print();}
#define PrPOA(A,B) if (_debug) {std::cout << (#B) << "\t" << (#A) << "\t"; A.Print();}
//    #define USEETOF
//#define __USE_HFT__
//#define __ETAPN_TOF_PLOTS__
#define dEdxL10min 0.0
#define dNdxL10min 1.0
#define __BOOK_hdEdx__(dir,hist,Name,Title)				\
  hist = (TH2F *)   dir->Get(Name);					\
  if (! hist) {								\
    hist = new TH2F(Name,Title, 700, -2, 1.5, 250, dEdxL10min, dEdxL10min+2.5);	\
  } 
#define __BOOK_hdNdx__(dir,hist,Name,Title)				\
  hist = (TH2F *)   dir->Get(Name);					\
  if (! hist) {								\
    hist = new TH2F(Name,Title, 700, -2, 1.5, 300, dNdxL10min, dNdxL10min+2.5);	\
  } 
Double_t StKFParticleInterface::fgMagScaleFactor = 1;
void StKFParticleInterface::SetMagScaleFactor(Double_t scale) {
  fgMagScaleFactor = scale;
  std::cout << " StKFParticleInterface::SetMagScaleFactor to " << fgMagScaleFactor << std::endl;
}
Bool_t StKFParticleInterface::fgUsedx2 = kFALSE;
Bool_t StKFParticleInterface::fgUseTof = kFALSE;

ClassImp(StKFParticleInterface);

StKFParticleInterface *StKFParticleInterface::fgStKFParticleInterface = 0;
//________________________________________________________________________________
void StKFParticleInterface::SetdEdXType(Int_t type)  { 
  fdEdXMode = type; 
  if (fdEdXMode == 2) StTrackCombPiD::SetUsedNdx(kTRUE);
  else                StTrackCombPiD::SetUsedNdx(kFALSE);
}
//________________________________________________________________________________
StKFParticleInterface::StKFParticleInterface(): 
  fKFParticleTopoReconstructor(0), fParticles(0), fParticlesPdg(0), fNHftHits(0), fBeamSpot(),
  fCollectTrackHistograms(false), fCollectPIDHistograms(false), fCollectPVHistograms(false),
  fStrictTofPID(true), fCleanKaonsWitTof(true), fUseETof(false), fdEdXMode(1), fTriggerMode(false),
  fChiPrimaryCut(18.6f), fChiPrimaryCutFragments(0.f), fChiPrimaryMaxCut(2e4f), fCleanLowPVTrackEvents(false), fUseHFTTracksOnly(false)
  , fIsFixedTarget(kFALSE), fIsFixedTarget2018(kFALSE), fPidQA(kTRUE)
{
  fKFParticleTopoReconstructor = new KFParticleTopoReconstructor();
  fgStKFParticleInterface = this;
  StTrackCombPiD::SetUsedx2(fgUsedx2);
  StTrackCombPiD::SetUseTof(fgUseTof);
  // set default cuts
  SetPrimaryProbCut(0.0001); // 0.01% to consider primary track as a secondary;
}
void StKFParticleInterface::SetUsedx2(Bool_t k) {fgUsedx2 = k; StTrackCombPiD::SetUsedx2(fgUsedx2);}
void StKFParticleInterface::SetUseTof(Bool_t k) {fgUseTof = k; StTrackCombPiD::SetUseTof(fgUseTof);}

StKFParticleInterface::~StKFParticleInterface()
{  
  if(fKFParticleTopoReconstructor) delete fKFParticleTopoReconstructor;
  fgStKFParticleInterface = 0;
}

void StKFParticleInterface::SetField(float field) 
{ 
  if(fKFParticleTopoReconstructor)
    fKFParticleTopoReconstructor->SetField(field); 
}
void StKFParticleInterface::SetBeamLine(KFParticle& p)
{ 
  if(fKFParticleTopoReconstructor)
    fKFParticleTopoReconstructor->SetBeamLine(p);
}

void StKFParticleInterface::SetBeamSpot(const TString beamSpotMode)
{
  fBeamSpot.NDF() = -1;

#ifndef __TFG__VERSION__
  if(beamSpotMode == TString("2018_3AGeV")) {
    fBeamSpot.Covariance(0,0) = 0.2173 * 0.2173;
    fBeamSpot.Covariance(1,1) = 0.1362 * 0.1362;
    fBeamSpot.Covariance(2,2) = 0.1674 * 0.1674;

    fBeamSpot.X() = -0.008f;
    fBeamSpot.Y() = -2.02f;
    fBeamSpot.Z() = 200.7f;
  }
  else if(beamSpotMode == TString("2019_3AGeV")) {
    fBeamSpot.Covariance(0,0) = 0.1632 * 0.1632;
    fBeamSpot.Covariance(1,1) = 0.1347 * 0.1347;
    fBeamSpot.Covariance(2,2) = 0.1908 * 0.1908;

    fBeamSpot.X() = -0.6577f;
    fBeamSpot.Y() = -1.986f;
    fBeamSpot.Z() = 199.8f;
  }
  else if(beamSpotMode == TString("2019_4AGeV")) {
    fBeamSpot.Covariance(0,0) = 0.1665 * 0.1665;
    fBeamSpot.Covariance(1,1) = 0.125 * 0.125;
    fBeamSpot.Covariance(2,2) = 0.2 * 0.2;

    fBeamSpot.X() = -0.427f;
    fBeamSpot.Y() = -1.994f;
    fBeamSpot.Z() = 199.9f;
  }
  else if(beamSpotMode == TString("2019_7AGeV")) {
    fBeamSpot.Covariance(0,0) = 0.18 * 0.18;
    fBeamSpot.Covariance(1,1) = 0.122 * 0.122;
    fBeamSpot.Covariance(2,2) = 0.2449 * 0.2449;

    fBeamSpot.X() = -0.45f;
    fBeamSpot.Y() = -1.994f;
    fBeamSpot.Z() = 200.2f;
  }
  else if(beamSpotMode == TString("2019_31AGeV")) {
    fBeamSpot.Covariance(0,0) = 0.1549 * 0.1549;
    fBeamSpot.Covariance(1,1) = 0.1239 * 0.1239;
    fBeamSpot.Covariance(2,2) = 0.2762 * 0.2762;

    fBeamSpot.X() = -0.2851f;
    fBeamSpot.Y() = -1.978f;
    fBeamSpot.Z() = 200.3f;
  }
  else if(beamSpotMode == TString("2020_5AGeV")) {
    fBeamSpot.Covariance(0,0) = 0.1595 * 0.1595;
    fBeamSpot.Covariance(1,1) = 0.122 * 0.122;
    fBeamSpot.Covariance(2,2) = 0.1837 * 0.1837;

    fBeamSpot.X() = -0.3592f;
    fBeamSpot.Y() = -2.038f;
    fBeamSpot.Z() = 200.2f;

    fUseETof = true;
  }
  else if(beamSpotMode == TString("2020_7AGeV")) {
    fBeamSpot.Covariance(0,0) = 0.1869 * 0.1869;
    fBeamSpot.Covariance(1,1) = 0.1235 * 0.1235;
    fBeamSpot.Covariance(2,2) = 0.2276 * 0.2276;

    fBeamSpot.X() = -0.3125f;
    fBeamSpot.Y() = -2.045f;
    fBeamSpot.Z() = 200.3f;

    fUseETof = true;
  }
  else if(beamSpotMode == TString("2020_9AGeV")) {
    fBeamSpot.Covariance(0,0) = 0.2395 * 0.2395;
    fBeamSpot.Covariance(1,1) = 0.1239 * 0.1239;
    fBeamSpot.Covariance(2,2) = 0.242 * 0.242;

    fBeamSpot.X() = -0.2838f;
    fBeamSpot.Y() = -2.042f;
    fBeamSpot.Z() = 200.3f;

    fUseETof = true;
  }
  else if(beamSpotMode == TString("2020_13AGeV")) {
    fBeamSpot.Covariance(0,0) = 0.1967 * 0.1967;
    fBeamSpot.Covariance(1,1) = 0.1285 * 0.1285;
    fBeamSpot.Covariance(2,2) = 0.2656 * 0.2656;

    fBeamSpot.X() = -0.2365f;
    fBeamSpot.Y() = -2.026f;
    fBeamSpot.Z() = 200.4f;

    fUseETof = true;
  }
  else if(beamSpotMode == TString("2020_19AGeV")) {
    fBeamSpot.Covariance(0,0) = 0.2083 * 0.2083;
    fBeamSpot.Covariance(1,1) = 0.1216 * 0.1216;
    fBeamSpot.Covariance(2,2) = 0.255 * 0.255;

    fBeamSpot.X() = -0.1866f;
    fBeamSpot.Y() = -2.021f;
    fBeamSpot.Z() = 200.4f;

    fUseETof = true;
  }
  else if(beamSpotMode == TString("2020_31AGeV")) {
    fBeamSpot.Covariance(0,0) = 0.1636 * 0.1636;
    fBeamSpot.Covariance(1,1) = 0.1169 * 0.1169;
    fBeamSpot.Covariance(2,2) = 0.2701 * 0.2701;

    fBeamSpot.X() = -0.1827f;
    fBeamSpot.Y() = -2.014f;
    fBeamSpot.Z() = 200.4f;

    fUseETof = true;
  }
  else if(beamSpotMode == TString("2021_3AGeV")) {
    fBeamSpot.Covariance(0,0) = 0.1549 * 0.1549;
    fBeamSpot.Covariance(1,1) = 0.1041 * 0.1041;
    fBeamSpot.Covariance(2,2) = 0.1553 * 0.1553;

    fBeamSpot.X() = 0.4037f;
    fBeamSpot.Y() = -2.054f;
    fBeamSpot.Z() = 200.3f;

    // fUseETof = true;
  }
  else {
    fBeamSpot.Covariance(0,0) = 0.26f;
    fBeamSpot.Covariance(1,1) = 0.14f;
    fBeamSpot.Covariance(2,2) = 0.20f;

    fBeamSpot.X() = 0.f;
    fBeamSpot.Y() = -2.0f;
    fBeamSpot.Z() = 200.f;
  }
#else /*  __TFG__VERSION__*/
  fBeamSpot.Covariance(0,0) = TMath::Power(St_beamLineC::instance()->sigma_X(), 2);
  fBeamSpot.Covariance(1,1) = TMath::Power(St_beamLineC::instance()->sigma_Y(), 2);
  fBeamSpot.Covariance(2,2) = TMath::Power(St_beamLineC::instance()->sigma_Z(), 2);
  fBeamSpot.X() = St_beamLineC::instance()->X();
  fBeamSpot.Y() = St_beamLineC::instance()->Y();
  fBeamSpot.Z() = St_beamLineC::instance()->Z();
#endif /* ! __TFG__VERSION__ */
}

void StKFParticleInterface::InitParticles()
{ 
  fKFParticleTopoReconstructor->Init( fParticles, &fParticlesPdg, &fNHftHits );
  Int_t NPV =  fKFParticleTopoReconstructor->NPrimaryVertices();
  fKFParticleTopoReconstructor->GetKFParticleFinder()->Init(NPV);
  fKFParticleTopoReconstructor->FillPVIndices();
}

#ifdef __kfpAtFirstHit__
void StKFParticleInterface::InitParticlesAtFirstAndLastHit()
{ 
  KFPTrackVector ftracksAtFirstHit;
  KFPTrackVector ftracksAtLastHit;
  int nTracks = fParticlesAtLastHit.size();
  ftracksAtFirstHit.Resize(nTracks);
  ftracksAtLastHit.Resize(nTracks);
  for(int iTr=0; iTr<nTracks; iTr++)
  {  
    int trackPDG = fParticlesPdg[iTr];
    int npixelhits = fNHftHits[iTr];
    
    for(int iP=0; iP<6; iP++) 
    {
      ftracksAtFirstHit.SetParameter(fParticles[iTr].Parameters()[iP], iP, iTr);
      ftracksAtLastHit.SetParameter(fParticlesAtLastHit[iTr].Parameters()[iP], iP, iTr); 
    }
    for(int iC=0; iC<21; iC++) 
    {
      ftracksAtFirstHit.SetCovariance(fParticles[iTr].CovarianceMatrix()[iC], iC, iTr);
      ftracksAtLastHit.SetCovariance(fParticlesAtLastHit[iTr].CovarianceMatrix()[iC], iC, iTr); 
    }
    ftracksAtFirstHit.SetId(fParticles[iTr].Id(), iTr);
    ftracksAtFirstHit.SetPDG(trackPDG, iTr);
    ftracksAtFirstHit.SetQ(fParticles[iTr].Q(), iTr);
    ftracksAtFirstHit.SetPVIndex(-1, iTr);
    ftracksAtFirstHit.SetNPixelHits(npixelhits,iTr);
    
    ftracksAtLastHit.SetId(fParticlesAtLastHit[iTr].Id(), iTr);
    ftracksAtLastHit.SetPDG(trackPDG, iTr);
    ftracksAtLastHit.SetQ(fParticlesAtLastHit[iTr].Q(), iTr);
    ftracksAtLastHit.SetPVIndex(-1, iTr);
    ftracksAtLastHit.SetNPixelHits(npixelhits,iTr);
  }
  fKFParticleTopoReconstructor->Init( ftracksAtFirstHit, ftracksAtLastHit );
  Int_t NPV =  fKFParticleTopoReconstructor->NPrimaryVertices();
  fKFParticleTopoReconstructor->GetKFParticleFinder()->Init(NPV);
  fKFParticleTopoReconstructor->FillPVIndices();
}
#endif

void StKFParticleInterface::ReconstructParticles()
{ 
  fKFParticleTopoReconstructor->SortTracks();
  fKFParticleTopoReconstructor->ReconstructParticles();
 
}

void StKFParticleInterface::ReconstructTopology()
{ 
  fKFParticleTopoReconstructor->Init( fParticles, &fParticlesPdg );
  fKFParticleTopoReconstructor->ReconstructPrimVertex(0);
  fKFParticleTopoReconstructor->SortTracks();
  fKFParticleTopoReconstructor->ReconstructParticles();
}

void StKFParticleInterface::AddPV(const KFVertex &pv, const vector<int> &tracks) { 
  fKFParticleTopoReconstructor->AddPV(pv, tracks);
  fKFParticleTopoReconstructor->FillPVIndices();
}
void StKFParticleInterface::CleanPV() {
  fKFParticleTopoReconstructor->CleanPV();
}

void StKFParticleInterface::AddPV(const KFVertex &pv) { 
  fKFParticleTopoReconstructor->AddPV(pv);
}

void StKFParticleInterface::AddParticle(const KFParticle &p) { 
  fKFParticleTopoReconstructor->AddParticle(p);
}

void StKFParticleInterface::AddCandidate(const KFParticle& candidate, int iPV) {
  fKFParticleTopoReconstructor->AddCandidate(candidate, iPV);
}
void StKFParticleInterface::AddDecayToReconstructionList(Int_t pdg) {
   fKFParticleTopoReconstructor->GetKFParticleFinder()->AddDecayToReconstructionList(pdg);
}
std::vector<KFParticle> const &StKFParticleInterface::GetParticles() const { return fKFParticleTopoReconstructor->GetParticles(); }
void StKFParticleInterface::RemoveParticle(const int iParticle) { fKFParticleTopoReconstructor->RemoveParticle(iParticle); }
const std::vector<KFParticle>* StKFParticleInterface::GetSecondaryCandidates() const {return fKFParticleTopoReconstructor->GetKFParticleFinder()->GetSecondaryCandidates();                           } // Get secondary particles with the mass constraint
const std::vector<KFParticle>& StKFParticleInterface::GetSecondaryK0() const {return fKFParticleTopoReconstructor->GetKFParticleFinder()->GetSecondaryK0();                           } // Get secondary particles with the mass constraint
const std::vector<KFParticle>& StKFParticleInterface::GetSecondaryLambda() const {return fKFParticleTopoReconstructor->GetKFParticleFinder()->GetSecondaryLambda();                           } // Get secondary particles with the mass constraint
const std::vector<KFParticle>& StKFParticleInterface::GetSecondaryAntiLambda() const {return fKFParticleTopoReconstructor->GetKFParticleFinder()->GetSecondaryAntiLambda();                           } // Get secondary particles with the mass constraint
const std::vector<KFParticle>& StKFParticleInterface::GetSecondaryGamma() const {return fKFParticleTopoReconstructor->GetKFParticleFinder()->GetSecondaryGamma();                           } // Get secondary particles with the mass constraint
const std::vector<KFParticle>& StKFParticleInterface::GetSecondaryPi0() const {return fKFParticleTopoReconstructor->GetKFParticleFinder()->GetSecondaryPi0();                           } // Get secondary particles with the mass constraint
const std::vector< std::vector<KFParticle> >* StKFParticleInterface::GetPrimaryCandidates() const {return fKFParticleTopoReconstructor->GetKFParticleFinder()->GetPrimaryCandidates();                } // Get primary particles with the mass constraint
const std::vector< std::vector<KFParticle> >* StKFParticleInterface::GetPrimaryTopoCandidates() const {return fKFParticleTopoReconstructor->GetKFParticleFinder()->GetPrimaryTopoCandidates();        } // Get primary particles with the topologigal constraint
const std::vector< std::vector<KFParticle> >* StKFParticleInterface::GetPrimaryTopoMassCandidates() const {return fKFParticleTopoReconstructor->GetKFParticleFinder()->GetPrimaryTopoMassCandidates();} // Get primary particles with the topologigal and mass constraint

KFParticleFinder*  StKFParticleInterface::GetKFParticleFinder() { return fKFParticleTopoReconstructor->GetKFParticleFinder(); }
void StKFParticleInterface::SetMaxDistanceBetweenParticlesCut(float cut) { GetKFParticleFinder()->SetMaxDistanceBetweenParticlesCut(cut); }
void StKFParticleInterface::SetLCut(float cut)                           { GetKFParticleFinder()->SetLCut(cut); }
void StKFParticleInterface::SetChiPrimaryCut2D(float cut)                { GetKFParticleFinder()->SetChiPrimaryCut2D(cut); }
void StKFParticleInterface::SetChi2Cut2D(float cut)                      { GetKFParticleFinder()->SetChi2Cut2D(cut); }
void StKFParticleInterface::SetLdLCut2D(float cut)                       { GetKFParticleFinder()->SetLdLCut2D(cut); }
void StKFParticleInterface::SetLdLCutXiOmega(float cut)                  { GetKFParticleFinder()->SetLdLCutXiOmega(cut); }
void StKFParticleInterface::SetChi2TopoCutXiOmega(float cut)             { GetKFParticleFinder()->SetChi2TopoCutXiOmega(cut); }
void StKFParticleInterface::SetChi2CutXiOmega(float cut)                 { GetKFParticleFinder()->SetChi2CutXiOmega(cut); }
void StKFParticleInterface::SetChi2TopoCutResonances(float cut)          { GetKFParticleFinder()->SetChi2TopoCutResonances(cut); }
void StKFParticleInterface::SetChi2CutResonances(float cut)              { GetKFParticleFinder()->SetChi2CutResonances(cut); }
void StKFParticleInterface::SetPtCutLMVM(float cut)                      { GetKFParticleFinder()->SetPtCutLMVM(cut); }
void StKFParticleInterface::SetPCutLMVM(float cut)                       { GetKFParticleFinder()->SetPCutLMVM(cut); }
void StKFParticleInterface::SetPtCutJPsi(float cut)                      { GetKFParticleFinder()->SetPtCutJPsi(cut); }
void StKFParticleInterface::SetPtCutCharm(float cut)                     { GetKFParticleFinder()->SetPtCutCharm(cut); }
void StKFParticleInterface::SetChiPrimaryCutCharm(float cut)             { GetKFParticleFinder()->SetChiPrimaryCutCharm(cut); }
void StKFParticleInterface::SetLdLCutCharmManybodyDecays(float cut)      { GetKFParticleFinder()->SetLdLCutCharmManybodyDecays(cut); }
void StKFParticleInterface::SetChi2TopoCutCharmManybodyDecays(float cut) { GetKFParticleFinder()->SetChi2TopoCutCharmManybodyDecays(cut); }
void StKFParticleInterface::SetChi2CutCharmManybodyDecays(float cut)     { GetKFParticleFinder()->SetChi2CutCharmManybodyDecays(cut); }
void StKFParticleInterface::SetLdLCutCharm2D(float cut)                  { GetKFParticleFinder()->SetLdLCutCharm2D(cut); }
void StKFParticleInterface::SetChi2TopoCutCharm2D(float cut)             { GetKFParticleFinder()->SetChi2TopoCutCharm2D(cut); }
void StKFParticleInterface::SetChi2CutCharm2D(float cut)                 { GetKFParticleFinder()->SetChi2CutCharm2D(cut); }
void StKFParticleInterface::SetSecondaryCuts(const float sigmaMass, const float chi2Topo, const float ldl) { GetKFParticleFinder()->SetSecondaryCuts(sigmaMass, chi2Topo, ldl); }
  
double StKFParticleInterface::InversedChi2Prob(double p, int ndf) const
{
  double epsilon = 1.e-14;
  double chi2Left = 0.f;
  double chi2Right = 10000.f;
  
  double probLeft = p - TMath::Prob(chi2Left, ndf);
  
  double chi2Centr = (chi2Left+chi2Right)/2.f;
  double probCentr = p - TMath::Prob( chi2Centr, ndf);
  
  while( TMath::Abs(chi2Right-chi2Centr)/chi2Centr > epsilon )
  {
    if(probCentr * probLeft > 0.f)
    {
      chi2Left = chi2Centr;
      probLeft = probCentr;
    }
    else
    {
      chi2Right = chi2Centr;
    }
    
    chi2Centr = (chi2Left+chi2Right)/2.f;
    probCentr = p - TMath::Prob( chi2Centr, ndf);
  }
  
  return chi2Centr;
}

void StKFParticleInterface::SetPrimaryProbCut(float prob)
{ 
  fKFParticleTopoReconstructor->SetChi2PrimaryCut( InversedChi2Prob(prob, 2) );
}

void StKFParticleInterface::CollectTrackHistograms()
{
  TDirectory *dirs[7] = {0};
  TDirectory::CurrentDirectory()->cd("/");
  dirs[0] = TDirectory::CurrentDirectory(); assert(dirs[0]);
  dirs[0]->cd();
  if (! dirs[0]->GetDirectory("Tracks")) {
    dirs[0]->mkdir("Tracks");
  }
  dirs[1] = dirs[0]->GetDirectory("Tracks"); assert(dirs[1]);
  dirs[1]->cd();
  
  const Char_t *chargeName[4] = {"","Pos","Neg","withTof"};
  for (Int_t i = 0; i < 4; i++) {
    __BOOK_hdEdx__(dirs[1],fTrackHistograms2D[khdEdX+i]   , Form("hdEdX%s",chargeName[i]), Form("hdEdX%s ; log_{10} P[GeV] ; log_{10} dE/dx[keV]",chargeName[i]));
    __BOOK_hdNdx__(dirs[1],fTrackHistograms2D[khdNdX+i], Form("hdNdX%s",chargeName[i]), Form("hdNdX%s ; log_{10} P[GeV] ; log_{10} dN/dx",chargeName[i]));
  }
  fTrackHistograms2D[khTofPID] = (TH2F *)   dirs[1]->Get("hTofPID");
  if (! fTrackHistograms2D[khTofPID]) {
    fTrackHistograms2D[khTofPID] = new TH2F("hTofPID", "hTofPID ; log_{10}P ; m^{2}", 200, -1, 1, 1100, -1, 10);
#ifdef __ETAPN_TOF_PLOTS__ 
    fTrackHistograms2D[khTofPIDP] = new TH2F("hTofPIDP", "hTofPIDP eta >  0 ; log_{10}P ; m^{2}", 200, -1, 1, 1100, -1, 10);
    fTrackHistograms2D[khTofPIDN] = new TH2F("hTofPIDN", "hTofPIDN eta <= 0 ; log_{10}P ; m^{2}", 200, -1, 1, 1100, -1, 10);
#endif /* __ETAPN_TOF_PLOTS__ */
  }
#ifdef __USE_HFT__
  fTrackHistograms[0] = (TH1F *)   dirs[1]->Get("hNHFTHits");
  if (! fTrackHistograms[0]) fTrackHistograms[0] = new TH1F("hNHFTHits", "hNHFTHits ; no.HFT hits",11, -0.5, 10.5);
#endif /*  __USE_HFT__ */  
  fTrackHistograms[1] = (TH1F *)   dirs[1]->Get("hPVError");
  if (! fTrackHistograms[1]) fTrackHistograms[1] = new TH1F("hPVError", "hPVError", 10000, 0, 1);

  fTrackHistograms2D[khPVErrorVsNTracks] = (TH2F *)   dirs[1]->Get("hPVErrorVsNTracks");
  if (! fTrackHistograms2D[khPVErrorVsNTracks]) 
    fTrackHistograms2D[khPVErrorVsNTracks] = new TH2F("hPVErrorVsNTracks", "hPVErrorVsNTracks ; log_{10} No. Global Tracks", 3000, 0.5, 3.5, 5000, 0, 0.5);

  fTrackHistograms2D[khPVErrorVsNPVTracks] = (TH2F *)   dirs[1]->Get("hPVErrorVsNPVTracks");
  if (! fTrackHistograms2D[khPVErrorVsNPVTracks]) 
    fTrackHistograms2D[khPVErrorVsNPVTracks] = new TH2F("hPVErrorVsNPVTracks", "hPVErrorVsNPVTracks ; log_{10} No. Primary Tracks", 3000, 0.5, 3.5, 5000, 0, 0.5);

  fTrackHistograms[2] = (TH1F *)   dirs[1]->Get("hPrimaryRatio");
  if (! fTrackHistograms[2]) fTrackHistograms[2] = new TH1F("hPrimaryRatio", "hPrimaryRatio", 100, 0, 1);
  
  fTrackHistograms2D[khGlobalVsPrimaryTracks] = (TH2F *)   dirs[1]->Get("hGlobalVsPrimaryTracks");
  if (! fTrackHistograms2D[khGlobalVsPrimaryTracks]) 
    fTrackHistograms2D[khGlobalVsPrimaryTracks] = new TH2F("hGlobalVsPrimaryTracks", "Global tracks: Log_{10} No. Global ; Log_{10} No. Primary Tracks", 350, 0.0, 3.5, 350, 0, 3.5);

  fTrackHistograms2D[khdEdXTofPID] = (TH2F *)   dirs[1]->Get("hdEdXTofPID");
  if (! fTrackHistograms2D[khdEdXTofPID]) 
    fTrackHistograms2D[khdEdXTofPID] = new TH2F("hdEdXTofPID", "hdEdXTofPID ; log_{10} dEdx[keV] ; m^{2}", 250, dEdxL10min, dEdxL10min+2.5, 2100, -1, 20);
  fTrackHistograms2D[khETofPID] = (TH2F *)   dirs[1]->Get("hETofPID");
  if (! fTrackHistograms2D[khETofPID]) 
    fTrackHistograms2D[khETofPID] = new TH2F("hETofPID", "ETofPID ; log_{10} dEdx[keV] ; m^{2}", 250, dEdxL10min, dEdxL10min+2.5, 2100, -1, 20);

  fTrackHistograms2D[khdNdXTofPID] = (TH2F *)   dirs[1]->Get("hdNdXTofPID");
  if (! fTrackHistograms2D[khdNdXTofPID]) 
    fTrackHistograms2D[khdNdXTofPID] = new TH2F("hdNdXTofPIDK", "hdNdXTofPID : log_{10} dN/dx ; m^{2}", 300, dNdxL10min, dNdxL10min+2.5, 2100, -1, 20);


  fTrackHistograms2D[khdEdXETofPID] = (TH2F *)   dirs[1]->Get("hdEdXETofPID");
  if (! fTrackHistograms2D[khdEdXETofPID]) fTrackHistograms2D[khdEdXETofPID] = new TH2F("hdEdXETofPID", "hdEdXETofPID", 200, 0, 200, 2100, -1, 20);

  fTrackHistograms2D[kEtaVspT] = (TH2F *)   dirs[1]->Get("EtaVspT");
  if (! fTrackHistograms2D[kEtaVspT]) fTrackHistograms2D[kEtaVspT] = new TH2F("EtaVspT", "Primary tracks ; Eta ; Log_{10}p_{T}", 350, -2, 1.5, 600, -3.0, 3.0);

  fTrackHistograms2D[kEtaVspTAll] = (TH2F *)   dirs[1]->Get("EtaVspTAll");
  if (! fTrackHistograms2D[kEtaVspTAll]) fTrackHistograms2D[kEtaVspTAll] = new TH2F("EtaVspTAll", " All tracks ; Eta ; Log_{10}p_{T}", 350, -2, 1.5, 600, -3.0, 3.0);
  dirs[0]->cd();
  
  fCollectTrackHistograms = true;
}

void StKFParticleInterface::CollectPIDHistograms()
{
  TDirectory *dirs[7] = {0};
  TDirectory::CurrentDirectory()->cd("/");
  dirs[0] = TDirectory::CurrentDirectory(); assert(dirs[0]);
  dirs[0]->cd();
  if (! dirs[0]->GetDirectory("Tracks")) {
    dirs[0]->mkdir("Tracks");
  }
  dirs[1] = dirs[0]->GetDirectory("Tracks"); assert(dirs[1]);
  dirs[1]->cd();
  
#ifndef __TFG__VERSION__
  int pdgTrackHisto[NTrackHistoFolders] = { 11, -11, 13, -13, 211, -211, 321, -321, 2212, -2212, 
#else /* __TFG__VERSION__ */
  int pdgTrackHisto[NTrackHistoFolders] = { -1,
					    11, -11, 13, -13, 211, -211, 321, -321, 2212, -2212, 
#endif /* __TFG__VERSION__ */
                                            1000010020, -1000010020, 1000010030, -1000010030, 
                                            1000020030, -1000020030, 1000020040, -1000020040,
                                            1000020060, -1000020060, 1000030060, -1000030060,
                                            1000030070, -1000030070, 1000040070, -1000040070 };
#ifndef __TFG__VERSION__
  TString trackFolderName[NTrackHistoFolders] = {"e-", "e+", "mu-", "mu+", "pi+", "pi-", "K+", "K-", "p", "p-", 
                                                 "d", "d-", "t", "t-", "He3", "He3-", "He4", "He4-", 
                                                 "He6", "He6-", "Li6", "Li6-", "Li7", "Li7-", "Be7", "Be7-"};
#else /* __TFG__VERSION__ */
  TString trackFolderName[NTrackHistoFolders] = {"Uknown",
						 "e-", "e+", "mu-", "mu+", "pi+", "pi-", "K+", "K-", "p", "p-", 
						 "d", "d-", "t", "t-", "He3", "He3-", "He4", "He4-", 
						 "He6", "He6-", "Li6", "Li6-", "Li7", "Li7-", "Be7", "Be7-"};
#endif /* __TFG__VERSION__ */
                    
#ifndef __TFG__VERSION__
  for(int iTrackHisto=0; iTrackHisto<NTrackHistoFolders; iTrackHisto++)
#else /* __TFG__VERSION__ */
  for(int iTrackHisto=1; iTrackHisto<NTrackHistoFolders; iTrackHisto++)
#endif /* __TFG__VERSION__ */
  {
    if (!dirs[1]->GetDirectory(trackFolderName[iTrackHisto].Data()))
      dirs[1]->mkdir(trackFolderName[iTrackHisto].Data());
    
    dirs[2] = dirs[1]->GetDirectory(trackFolderName[iTrackHisto].Data()); assert(dirs[2]);
    dirs[2]->cd();
    
    fTrackPdgToHistoIndex[ pdgTrackHisto[iTrackHisto] ] = iTrackHisto;
#ifndef __TFG__VERSION__
    
    fHistodEdXTracks[iTrackHisto] = (TH2F *)   dirs[2]->Get("hdEdX");
    if (! fHistodEdXTracks[iTrackHisto]) fHistodEdXTracks[iTrackHisto] = new TH2F("hdEdX", "hdEdX", 1000, 0, 10, 200, 0, 200);

    fHistodEdXwithToFTracks[iTrackHisto] = (TH2F *)   dirs[2]->Get("hdEdXwithToF");
    if (! fHistodEdXwithToFTracks[iTrackHisto]) fHistodEdXwithToFTracks[iTrackHisto] = new TH2F("hdEdXwithToF", "hdEdXwithToF", 1000, 0, 10, 200, 0, 200);
  
    fHistoTofPIDTracks[iTrackHisto] = (TH2F *)   dirs[2]->Get("hTofPID");
    if (! fHistoTofPIDTracks[iTrackHisto]) fHistoTofPIDTracks[iTrackHisto] = new TH2F("hTofPID", "hTofPID", 300, 0, 15, 1100, -1, 10);
#else /* __TFG__VERSION__ */
    __BOOK_hdEdx__(dirs[2],fHistodEdXTracks[iTrackHisto], "hdEdX", "hdEdX");
    __BOOK_hdEdx__(dirs[2],fHistodEdXwithToFTracks[iTrackHisto], "hdEdXwithTof", "hdEdXwithTof");
    __BOOK_hdNdx__(dirs[2],fHistodNdXTracks[iTrackHisto], "hdNdX", "hdNdX");
    __BOOK_hdNdx__(dirs[2],fHistodNdXwithTofTracks[iTrackHisto], "hdNdXwithTof", "hdNdXwithTof");
  
    fHistoTofPIDTracks[iTrackHisto][0] = (TH2F *)   dirs[2]->Get("hTofPID");
    if (! fHistoTofPIDTracks[iTrackHisto][0]) {
      fHistoTofPIDTracks[iTrackHisto][0] = new TH2F("hTofPID", "hTofPID ; log_{10}P ; m^{2}", 200, -1, 1, 1100, -1, 10);
#ifdef __ETAPN_TOF_PLOTS__ 
      fHistoTofPIDTracks[iTrackHisto][1] = new TH2F("hTofPIDP", "hTofPID eta >  0 ; log_{10}P ; m^{2}", 200, -1, 1, 1100, -1, 10);
      fHistoTofPIDTracks[iTrackHisto][2] = new TH2F("hTofPIDN", "hTofPID eta <= 0 ; log_{10}P ; m^{2}", 200, -1, 1, 1100, -1, 10);
#endif /* __ETAPN_TOF_PLOTS__ */
    }
    fHistoETofPIDTracks[iTrackHisto] = (TH2F *)   dirs[2]->Get("hETofPID");
    if (! fHistoETofPIDTracks[iTrackHisto]) fHistoETofPIDTracks[iTrackHisto] = new TH2F("hETofPID", "hETofPID ; log_{10}P ; m^{2}", 200, -1, 1, 1100, -1, 10);
#endif /* __TFG__VERSION__ */
  
    fHistoMomentumTracks[iTrackHisto] = (TH1F *)   dirs[2]->Get("hMomentum");
#ifndef __TFG__VERSION__
    if (! fHistoMomentumTracks[iTrackHisto]) fHistoMomentumTracks[iTrackHisto] = new TH1F("hMomentum", "hMomentum", 1000, 0, 10);

#else /* __TFG__VERSION__ */
    if (! fHistoMomentumTracks[iTrackHisto]) fHistoMomentumTracks[iTrackHisto] = new TH1F("hMomentum", "log_{10} p ; log_{10} p ", 1000, -2, 2);
    
#endif /* __TFG__VERSION__ */
    fHistodEdXPull[iTrackHisto] = (TH2F *)   dirs[2]->Get("hdEdXPull");
#ifndef __TFG__VERSION__
    if (! fHistodEdXPull[iTrackHisto]) fHistodEdXPull[iTrackHisto] = new TH2F("hdEdXPull", "hdEdXPull", 500, 0, 10, 300, -30, 30);
#else /* __TFG__VERSION__ */
    if (! fHistodEdXPull[iTrackHisto]) fHistodEdXPull[iTrackHisto] = new TH2F("hdEdXPull", "hdEdXPull", 2000, -5, 5, 120, -6, 6);

    fHistodEdXnSigma[iTrackHisto] = (TH2F *)   dirs[2]->Get("hdEdXnSigma");
    if (! fHistodEdXnSigma[iTrackHisto]) fHistodEdXnSigma[iTrackHisto] = new TH2F("hdEdXnSigma", "hdEdXnSigma", 2000, -5, 5, 120, -6, 6);
#endif /* __TFG__VERSION__ */
    
    fHistodEdXZ[iTrackHisto] = (TH2F *)   dirs[2]->Get("hdEdXZ");
#ifndef __TFG__VERSION__
    if (! fHistodEdXZ[iTrackHisto]) fHistodEdXZ[iTrackHisto] = new TH2F("hdEdXZ", "hdEdXZ", 500, -5, 5, 140, -1, 6);
#else /* __TFG__VERSION__ */
    if (! fHistodEdXZ[iTrackHisto]) fHistodEdXZ[iTrackHisto] = new TH2F("hdEdXZ", "hdEdXZ", 2000, -2, 2, 280, -1, 6);
    fHistodEdXPull[iTrackHisto] = (TH2F *)   dirs[2]->Get("hdEdXPull");
    if (! fHistodEdXPull[iTrackHisto]) fHistodEdXPull[iTrackHisto] = new TH2F("hdEdXPull", "hdEdXPull", 2000, -2, 2, 120, -6, 6);

    fHistodNdXPull[iTrackHisto] = (TH2F *)   dirs[2]->Get("hdNdXPull");
    if (! fHistodNdXPull[iTrackHisto]) fHistodNdXPull[iTrackHisto] = new TH2F("hdNdXPull", "hdNdXPull", 2000, -2, 2, 120, -6, 6);
#endif /* __TFG__VERSION__ */
    
    dirs[1]->cd();
  }
  
  dirs[0]->cd();
  
  fCollectPIDHistograms = true;
}

void StKFParticleInterface::CollectPVHistograms()
{
  TDirectory::CurrentDirectory()->cd("/");
  TDirectory* mainDir = TDirectory::CurrentDirectory(); assert(mainDir);
  if (! mainDir->GetDirectory("PrimaryVertices")) {
    mainDir->mkdir("PrimaryVertices");
  }
  TDirectory* pvDir = mainDir->GetDirectory("PrimaryVertices");
  pvDir->cd();
  
  int iHisto = 0;

  // 0
  TString title("X");
  fPVHistograms[iHisto] = (TH1F*) pvDir->Get(title);
  if (! fPVHistograms[iHisto]) fPVHistograms[iHisto] = new TH1F(title, title, 4000, -200, 200);
  iHisto++;

  // 1
  title = "Y";
  fPVHistograms[iHisto] = (TH1F*) pvDir->Get(title);
  if (! fPVHistograms[iHisto]) fPVHistograms[iHisto] = new TH1F(title, title, 4000, -200, 200);
  iHisto++;

  // 2
  title = "R";
  fPVHistograms[iHisto] = (TH1F*) pvDir->Get(title);
  if (! fPVHistograms[iHisto]) fPVHistograms[iHisto] = new TH1F(title, title, 2000, 0, 200);
  iHisto++;

  // 3
  title = "Z";
  fPVHistograms[iHisto] = (TH1F*) pvDir->Get(title);
#ifndef __TFG__VERSION__
  if (! fPVHistograms[iHisto]) fPVHistograms[iHisto] = new TH1F(title, title, 4400, -220, 220);
#else /* __TFG__VERSION__ */
  Double_t zMin  = -220, zMax  = 220, dZ  = 0.2;      // 0.20 cm
  Double_t zMin1 =  195, zMax1 = 205, dZ1 = 0.0050;; // 0.005 cm
  Int_t nbins = (zMax - zMin)/dZ + (zMax1 - zMin1)/dZ1 + 1;
  TArrayD Z(nbins);
  Double_t z = zMin;
  Int_t i = 0;
  while (z < zMax) {
    Z[i] = z; i++;
    if (z < zMin1 || z > zMax1) {
      z += dZ;
    } else {
      z += dZ1;
    }
  }
  //  if (! fPVHistograms[iHisto]) fPVHistograms[iHisto] = new TH1F(title, title, 4400, -220, 220);
  if (! fPVHistograms[iHisto]) fPVHistograms[iHisto] = new TH1F(title, title, i-1, Z.GetArray());
#endif /* __TFG__VERSION__ */
  iHisto++;

  // 4
  title = "NTracks";
  fPVHistograms[iHisto] = (TH1F*) pvDir->Get(title);
  if (! fPVHistograms[iHisto]) fPVHistograms[iHisto] = new TH1F(title, title, 1000, 0, 1000);
  iHisto++;
  
  // 5
  title = "NTracksMain";
  fPVHistograms[iHisto] = (TH1F*) pvDir->Get(title);
  if (! fPVHistograms[iHisto]) fPVHistograms[iHisto] = new TH1F(title, title, 1000, 0, 1000);
  iHisto++;

  // 6
  title = "NTracksPileup";
  fPVHistograms[iHisto] = (TH1F*) pvDir->Get(title);
  if (! fPVHistograms[iHisto]) fPVHistograms[iHisto] = new TH1F(title, title, 1000, 0, 1000);
  iHisto++;

  // 7
  title = "NPV";
  fPVHistograms[iHisto] = (TH1F*) pvDir->Get(title);
  if (! fPVHistograms[iHisto]) fPVHistograms[iHisto] = new TH1F(title, title, 10, 0, 10);
  iHisto++;

  // 8
  title = "PrimaryFraction";
  fPVHistograms[iHisto] = (TH1F*) pvDir->Get(title);
  if (! fPVHistograms[iHisto]) fPVHistograms[iHisto] = new TH1F(title, title, 100, 0, 1);
  iHisto++;

  // 9
  title = "PileupFraction";
  fPVHistograms[iHisto] = (TH1F*) pvDir->Get(title);
  if (! fPVHistograms[iHisto]) fPVHistograms[iHisto] = new TH1F(title, title, 100, 0, 1);
  iHisto++;

  // 10
  title = "RestFraction";
  fPVHistograms[iHisto] = (TH1F*) pvDir->Get(title);
  if (! fPVHistograms[iHisto]) fPVHistograms[iHisto] = new TH1F(title, title, 100, 0, 1);
  iHisto++;
  
  int iHisto2D = 0;
  
  title = "XY";
  fPVHistograms2D[0] = (TH2F *) pvDir->Get(title);
  if (! fPVHistograms2D[0]) fPVHistograms2D[0] = new TH2F(title, title + " ; X [cm] ; Y [cm]", 800, -40, 40, 800, -40, 40);

  title = "ZR";
  fPVHistograms2D[1] = (TH2F *) pvDir->Get(title);
  if (! fPVHistograms2D[1]) fPVHistograms2D[1] = new TH2F(title, title + " ; Z [cm] ; R [cm]", 4400, -220, 220, 400, -40, 40);

  title = "ZRTracks";
  fPVHistograms2D[2] = (TH2F *) pvDir->Get(title);
  if (! fPVHistograms2D[2]) fPVHistograms2D[2] = new TH2F(title, title + " ; Z [cm] ; R [cm]", 440, -220, 220, 400, 0, 200);

  title = "ZRTracksRest";
  fPVHistograms2D[3] = (TH2F *) pvDir->Get(title);
  if (! fPVHistograms2D[3]) fPVHistograms2D[3] = new TH2F(title, title + " ; Z [cm] ; R [cm]", 440, -220, 220, 400, 0, 200);

  mainDir->cd();
  
  fCollectPVHistograms = true;
}


bool StKFParticleInterface::IsGoodPV(const KFVertex& pv)
{
  bool isGoodPV = (pv.X() > -0.3) && (pv.X() < -0.1) &&
                  (pv.Y() > -0.27) && (pv.Y() < -0.1);
  return isGoodPV;
}

bool StKFParticleInterface::GetTrack(const StDcaGeometry& dcaG, KFPTrack& track, int q, int index)
{
  Double_t xyzp[6], CovXyzp[21];
  dcaG.GetXYZ(xyzp,CovXyzp);
  
  bool goodTrack=1;
  for(int iPar=0; iPar<6; iPar++)
    goodTrack = goodTrack && finite(xyzp[iPar]);
  for(int iC=0; iC<21; iC++)
    goodTrack = goodTrack && finite(CovXyzp[iC]);
  goodTrack &= goodTrack && CovXyzp[0]  >=0.f && CovXyzp[0]  < 100.f;
  goodTrack &= goodTrack && CovXyzp[2]  >=0.f && CovXyzp[2]  < 100.f;
  goodTrack &= goodTrack && CovXyzp[5]  >=0.f && CovXyzp[5]  < 100.f;
  goodTrack &= goodTrack && CovXyzp[9]  >=0.f && CovXyzp[9]  < 1.f;
  goodTrack &= goodTrack && CovXyzp[14] >=0.f && CovXyzp[14] < 1.f;
  goodTrack &= goodTrack && CovXyzp[20] >=0.f && CovXyzp[20] < 1.f;
  if(!goodTrack) return false;
  
  track.SetParameters(xyzp);
  track.SetCovarianceMatrix(CovXyzp);
  track.SetNDF(1);
  //    track.SetChi2(GlobalTracks_mChiSqXY[k]);
  track.SetID(index);

  track.SetCharge(q);
  return true;
}

std::vector<int> StKFParticleInterface::GetTofPID(double m2, double p, int q, const int trackId)
{
  static const int order = 4;
  static const double parMean[6][order+1] = { { 0.02283190,-0.01482910, 0.01883130,-0.01824250, 0.00409811  }, //pi+
                                              { 0.24842500,-0.00699781,-0.00991387, 0.01327170,-0.00694824  }, //K+
                                              { 0.863211  , 0.0264171 ,-0.0230833 , 0.00239637, 0.000262309 }, //p
                                              { 0.0224095 ,-0.0123235 , 0.0145216 ,-0.0149944 , 0.00325952  }, //pi-
                                              { 0.250696  ,-0.0151308 , 0.00437457, 0.00516669,-0.00529184  }, //K-
                                              { 0.886912  ,-0.0298543 , 0.0449904 ,-0.0286879 , 0.00541963  }};//p-
  static const double parSigma[6][order+1] = { { 0.0112498,-0.0400571, 0.0733615,-0.0316505, 0.00629469 }, //pi+
                                               { 0.0154830,-0.0396312, 0.0719647,-0.0290683, 0.00637164 }, //K+
                                               { 0.114465 ,-0.287213 , 0.356536 ,-0.169257 , 0.0299844  }, //p
                                               { 0.0111682,-0.0394877, 0.0718342,-0.0302914, 0.00587317 }, //pi-
                                               { 0.0157322,-0.0402606, 0.0716639,-0.0272101, 0.00564467 }, //K-
                                               { 0.0899438,-0.211922 , 0.273122 ,-0.129597 , 0.0231844  }};//p-
  double pMax = 2.;
  double nSigmas[3];
  for(int iHypothesys = 0; iHypothesys<3; iHypothesys++)
  {
    double x = p;
    if(x>=pMax) x = pMax;
    
    int iSet = iHypothesys;
    if(q<0)
      iSet += 3;
    double mean = 0;
    for(int iTerm=0; iTerm<=order; iTerm++)
      mean += parMean[iSet][iTerm]*TMath::Power(x,iTerm);  
    
    double sigma = 0;
    for(int iTerm=0; iTerm<=order; iTerm++)
      sigma += parSigma[iSet][iTerm]*TMath::Power(x,iTerm);  
    
    nSigmas[iHypothesys] = fabs((m2 - mean)/sigma);
    fTrackPidTof[iHypothesys][trackId] = nSigmas[iHypothesys];
  }
  
  double minNSigma = nSigmas[0];
  int minHypothesis = 0;
  for(int iHypothesys=1; iHypothesys<3; iHypothesys++)
  {
    if(minNSigma > nSigmas[iHypothesys]) 
    {
      minNSigma = nSigmas[iHypothesys];
      minHypothesis = iHypothesys;
    }
  }

  int pdgHypothesis[3] = {211, 321, 2212};
  vector<int> tofPID;
  
  if(fStrictTofPID)
  {
    if(minNSigma < 3)
      tofPID.push_back(pdgHypothesis[minHypothesis]*q);
  }
  else
  {    
    for(int iHypothesys=0; iHypothesys<3; iHypothesys++)
      if(nSigmas[iHypothesys] < 3)
        tofPID.push_back(pdgHypothesis[iHypothesys]*q);
  }
  
  return tofPID;
}

std::vector<int> StKFParticleInterface::GetPID(double m2, double p, int q, double dEdX, double dEdXPull[8], bool isBTofm2, bool isETofm2, const int trackId)
{
  //  const bool isTofm2 = isBTofm2 || isETofm2;

  vector<int> ToFPDG;
  if(isBTofm2 & fgUseTof)
    ToFPDG = GetTofPID(m2, p, q, trackId);
  
  for(int iPdg=0; iPdg<3; iPdg++)
    fTrackPidTpc[iPdg][trackId] = dEdXPull[iPdg+1];
  
  vector<int> dEdXPDG;
  float nSigmaCut = 3.f; //TODO
  vector<int> totalPDG;
  //#define __ToF_PiD__
#ifndef  __ToF_PiD__
    bool checkKTof = false;
  if(fCleanKaonsWitTof)
    //    checkKTof = (p > 0.5) && (p < 2.);
    checkKTof = (p > 0.5);
  checkKTof = fCleanKaonsWitTof && (p > 0.5) && (p < 2.);
   bool checkKHasTof = 0;
  for(UInt_t iTofPDG=0; iTofPDG<ToFPDG.size(); iTofPDG++)
    if(abs(ToFPDG[iTofPDG]) == 321)
      checkKHasTof = 1;

  if(dEdXPull[0] < nSigmaCut)                                           dEdXPDG.push_back(-11*q);
  if(dEdXPull[2] < nSigmaCut)                                           dEdXPDG.push_back(211*q);  
#ifndef __TFG__VERSION__
  if(dEdXPull[3] < 2.f && ((checkKTof && checkKHasTof) || !checkKTof) ) dEdXPDG.push_back(321*q);
#else /* __TFG__VERSION__ */
  if(dEdXPull[3] < nSigmaCut )                                          dEdXPDG.push_back(321*q);
#endif /* __TFG__VERSION__ */
  if(dEdXPull[4] < nSigmaCut)                                           dEdXPDG.push_back(2212*q); 
#else /*  __ToF_PiD__ */
  bool isKTof = 0;
  bool isPTof = 0;
  bool isPiTof = 0;
  for(UInt_t iTofPDG=0; iTofPDG<ToFPDG.size(); iTofPDG++)
  {
    if(abs(ToFPDG[iTofPDG]) == 321) isKTof = 1;
    if(abs(ToFPDG[iTofPDG]) == 211) isPiTof = 1;
    if(abs(ToFPDG[iTofPDG]) ==2212) isPTof = 1;
  }
  if(dEdXPull[2] < nSigmaCut && isPiTof) dEdXPDG.push_back(211*q);  
  if(dEdXPull[3] < nSigmaCut && isKTof) dEdXPDG.push_back(321*q);
  if(dEdXPull[4] < nSigmaCut && isPTof) dEdXPDG.push_back(2212*q); 


  if(!isTofm2 || ! fgUseTof)     totalPDG = dEdXPDG;

  else
  {
    for(unsigned int iPDG=0; iPDG<dEdXPDG.size(); iPDG++)
      for(unsigned int iTofPDG=0; iTofPDG<TofPDG.size(); iTofPDG++)
        if(dEdXPDG[iPDG] == TofPDG[iTofPDG])
          totalPDG.push_back(TofPDG[iTofPDG]);        
  }
#endif /* ! __ToF_PiD__ */

#ifndef __TFG__VERSION__
  if(dEdXPull[0] < nSigmaCut)  totalPDG.push_back(-11*q);
#endif /* ! __TFG__VERSION__ */
  if(dEdXPull[1] < nSigmaCut)  totalPDG.push_back(-13*q);
  if(dEdXPull[9] < nSigmaCut  || 
     dEdXPull[10] < nSigmaCut ||
     dEdXPull[11] < nSigmaCut)  
  {
    totalPDG.push_back(2000003112*q);
  }
#ifndef __TFG__VERSION__

#if 0 // 2018
  static constexpr double pL[10][4]{
    {7.11737e+00,-1.31428e+00, 1.96720e-01, 6.47905e-02}, // d
    {1.38117e+01,-1.67910e+00,-4.52185e-03, 9.21224e-02}, // t
    {2.27715e+01,-1.36600e+00, 3.01143e-01, 2.38046e-01}, // He3
    {3.45107e+01,-1.22371e+00, 1.89140e-01, 1.07000e-01}, // He4
    {5.63562e+01,-1.29479e+00, 2.27883e-01,-4.10513e-02}, // He6
    {7.30295e+01,-1.08787e+00, 6.87593e-02, 1.14228e-01}, // Li6
    {9.30989e+01,-1.22084e+00, 3.73173e-01,-1.12695e-01}, // Li7
    {1.08163e+02,-1.08057e+00, 2.34159e-01, 1.98949e-02}, // Be7
    {0,0,0,0}, // He8
    {0,0,0,0}, // Li8
  };

  static constexpr double pU[10][4]{
    {1.39824e+01,-1.53919e+00, 1.10899e-01, 9.82910e-02}, // d
    {2.29456e+01,-1.41456e+00, 1.04286e-01, 1.26818e-01}, // t
    {3.33751e+01,-1.22800e+00, 2.98371e-01, 1.82920e-01}, // He3
    {5.09065e+01,-1.36283e+00, 1.90657e-01, 1.98235e-01}, // He4
    {7.52605e+01,-1.42948e+00, 5.87043e-01,-2.13013e-01}, // He6
    {9.35347e+01,-1.25594e+00, 2.91456e-01, 9.52847e-02}, // Li6
    {1.14003e+02,-1.33179e+00, 4.19395e-01,-3.20841e-02}, // Li7
    {1.37012e+02,-1.14016e+00, 3.73116e-01,-1.85678e-02}, // Be7
    {0,0,0,0}, // He8
    {0,0,0,0}, // Li8
  };

  //                                      d    t   He3  He4  He6  Li6  Li7  Be7  He8  Li8
  static constexpr double dedxLower[10]{ 0.0, 0.0, 11., 11., 11., 25., 25., 40., 11., 25. };
  static constexpr double dedxUpper[10]{ 8.0, 8.0, 18., 18., 18., 37., 37., 55., 18., 37. };

#elif 0 // 2021 xProduction, May
  static constexpr double pL[10][4]{
    {7.26450e+00,-1.48942e+00,-2.71718e-01,-8.21588e-02}, // d
    {1.38915e+01,-1.43926e+00,-8.10367e-02,-9.39156e-03}, // t
    {2.23798e+01,-1.09106e+00, 1.35016e-01, 1.72563e-01}, // He3
    {3.12534e+01,-9.52345e-01, 1.63815e-02, 2.03462e-02}, // He4
    {4.59563e+01,-1.05965e+00, 3.70239e-02, 4.92680e-02}, // He6
    {5.33123e+01,-7.79828e-01, 1.13380e-01, 1.39092e-04}, // Li6
    {5.93075e+01,-7.23992e-01, 1.22609e-01,-5.17200e-02}, // Li7
    {7.16577e+01,-8.56517e-01, 2.48878e-01,-3.66107e-02}, // Be7
    {0,0,0,0}, // He8
    {0,0,0,0}, // Li8
  };

  static constexpr double pU[10][4]{
    {1.37151e+01,-1.45881e+00,-3.58669e-02, 3.97500e-02}, // d
    {2.20190e+01,-1.24588e+00, 4.34070e-02, 3.88409e-02}, // t
    {3.09025e+01,-9.75179e-01, 1.03354e-01, 1.29797e-01}, // He3
    {4.10331e+01,-1.01056e+00, 1.98636e-01,-2.77912e-02}, // He4
    {5.52646e+01,-9.50780e-01, 2.14347e-01,-1.03148e-01}, // He6
    {5.81213e+01,-7.88117e-01, 5.20665e-01,-2.26597e-01}, // Li6
    {7.16577e+01,-8.56517e-01, 2.48878e-01,-3.66107e-02}, // Li7
    {1.37012e+02,-1.14016e+00, 3.73116e-01,-1.85678e-02}, // Be7
    {0,0,0,0}, // He8
    {0,0,0,0}, // Li8
  };

  //                                      d    t   He3  He4  He6  Li6  Li7  Be7  He8  Li8
  static constexpr double dedxLower[10]{ 0.0, 0.0, 11., 11., 11., 22., 22., 40., 11., 22. };
  static constexpr double dedxUpper[10]{ 8.0, 8.0, 18., 18., 18., 30., 30., 55., 18., 30. };

#elif 0 // 2021 xProduction, June
  static constexpr double pL[10][4]{
    {7.02144e+00,-1.77017e+00,-2.60061e-01,-1.68402e-02}, // d
    {1.47794e+01,-1.52798e+00,-1.00490e-01, 9.46116e-03}, // t
    {2.46334e+01,-9.18130e-01, 9.93814e-02, 6.08549e-02}, // He3
    {3.37746e+01,-9.67771e-01, 9.44445e-02, 3.52215e-02}, // He4
    {4.94040e+01,-1.03654e+00, 4.80683e-02, 7.45434e-03}, // He6
    {5.79920e+01,-8.01901e-01, 6.66119e-02, 5.34188e-02}, // Li6
    {6.61051e+01,-7.37484e-01,-5.99112e-02, 5.92928e-02}, // Li7
    {8.32337e+01,-7.56362e-01,-5.56798e-02, 8.60781e-02}, // Be7
    {0,0,0,0}, // He8
    {0,0,0,0}, // Li8
  };

  static constexpr double pU[10][4]{
    {1.48953e+01,-1.55755e+00,-2.80406e-01,-5.87432e-02}, // d
    {2.30993e+01,-1.34625e+00, 4.73902e-02, 7.94857e-02}, // t
    {3.33680e+01,-9.69092e-01, 1.15195e-01, 9.37487e-02}, // He3
    {4.42988e+01,-1.07999e+00, 1.50885e-01, 6.51833e-02}, // He4
    {6.71366e+01,-1.20558e+00, 1.63842e-01, 3.51544e-02}, // He6
    {6.66890e+01,-7.82862e-01, 2.14334e-01,-1.15082e-02}, // Li6
    {8.32337e+01,-7.56362e-01,-5.56798e-02, 8.60781e-02}, // Li7
    {1.37012e+02,-1.14016e+00, 3.73116e-01,-1.85678e-02}, // Be7
    {0,0,0,0}, // He8
    {0,0,0,0}, // Li8
  };

  //                                      d    t   He3  He4  He6  Li6  Li7  Be7  He8  Li8
  static constexpr double dedxLower[10]{ 0.0, 0.0, 10., 10., 10., 22., 22., 40., 10., 22. };
  static constexpr double dedxUpper[10]{ 8.0, 8.0, 17., 17., 17., 30., 30., 55., 1., 30. };

#elif 0 // P23id
  static constexpr double pL[10][4]{
    {2.01919e+00, -1.43576e+00, 1.42708e-01, 7.81837e-02},   // d
    {2.75363e+00, -1.47802e+00, -3.68978e-02, -7.81886e-02}, // t
    {3.20869e+00, -1.14289e+00,  2.59129e-01,  2.73274e-02}, // He3
    {3.53401e+00, -1.13341e+00,  2.71542e-01, -3.89132e-02}, // He4
    {4.01727e+00, -1.30366e+00,  4.26304e-01, -1.64219e-01}, // He6
    {4.29368e+00, -1.41286e+00,  4.16766e-01,  3.84379e-02}, // Li6
    {4.57166e+00, -1.33862e+00, -1.90262e-01,  3.41333e-01}, // Li7
    {4.72201e+00, -1.16064e+00,  2.87131e-01,  8.97313e-03}, // Be7
    {0,0,0,0}, // He8
    {0,0,0,0}, // Li8
  };

  static constexpr double pU[10][4]{
    {2.74829e+00, -1.63955e+00, -2.90466e-01, -1.61412e-01}, // d
    {3.17598e+00, -1.24257e+00,  5.97925e-02, -1.03118e-01}, // t
    {3.51253e+00, -1.14517e+00,  3.73812e-01,  5.05007e-02}, // He3
    {3.91966e+00, -1.32891e+00,  4.07485e-01, -1.98109e-02}, // He4
    {4.28499e+00, -1.42002e+00,  4.34652e-01, -7.81419e-02}, // He6
    {4.55036e+00, -1.33616e+00,  1.27882e-01,  2.57759e-01}, // Li6
    {4.79742e+00, -1.29053e+00, -2.93125e-01,  4.32599e-01}, // Li7
    {4.95721e+00, -1.27362e+00,  5.21909e-01, -7.04068e-02}, // Be7
    {0,0,0,0}, // He8
    {0,0,0,0}, // Li8
  };

  //                                      d    t   He3  He4  He6  Li6  Li7  Be7  He8  Li8
  static constexpr double dedxLower[10]{ 0.0, 0.0, 10., 10., 10., 25., 25., 40., 10., 25. };
  static constexpr double dedxUpper[10]{ 8.0, 8.0, 17., 17., 17., 37., 37., 55., 17., 37. };
#else //P24ia

  static constexpr double pL[10][4]{
    {2.0143164938e+00, -1.4868259425e+00, 4.9832096157e-02, 5.0402224369e-02}, // d
    {2.7614255198e+00, -1.5612577498e+00,-1.2128291947e-01, 5.0807142148e-02}, // t
    {3.2507048779e+00, -1.3274318490e+00, 1.1455797223e-01, 2.8319217003e-01}, // He3
    {3.5746170653e+00, -1.0838815425e+00, 2.3482480024e-01,-7.2389968151e-02}, // He4
    {4.0803460926e+00, -1.2931393512e+00, 2.9321341693e-01,-9.8423390129e-02}, // He6
    {4.1007473315e+00, -9.3239946428e-01, 3.6605661735e-01,-1.1129083716e-01}, // Li6
    {4.2184988868e+00, -8.2894179381e-01, 2.3255048995e-01,-1.1203759135e-01}, // Li7
    {4.3625991291e+00, -7.0766460556e-01, 2.7203987630e-01,-8.1081700158e-02}, // Be7
    {0,0,0,0}, // He8
    {0,0,0,0}, // Li8
  };

  static constexpr double pU[10][4]{
    {2.7097536963e+00, -1.5967208060e+00,-1.4348261827e-01, 3.6542475209e-02}, // d
    {3.2004021981e+00, -1.3191149722e+00, 4.6653227329e-03, 2.1260140901e-02}, // t
    {3.5540978373e+00, -1.0937868746e+00, 2.7960853931e-01, 6.1466236409e-02}, // He3
    {3.9196626439e+00, -1.3289103863e+00, 4.0748504441e-01,-1.9810867630e-02}, // He4
    {4.2619406636e+00, -1.1332156925e+00, 1.2847954566e-01, 2.0051492410e-03}, // He6
    {4.5634323873e+00, -1.0855964528e+00, 2.0457422564e-01, 6.9747624209e-02}, // Li6
    {4.6806026804e+00, -9.2998593560e-01,-5.5647040995e-02, 1.3243371161e-01}, // Li7
    {4.9390618150e+00, -1.4423964107e+00, 8.3712434636e-01,-2.0317987761e-01}, // Be7
    {0,0,0,0}, // He8
    {0,0,0,0}, // Li8
  };

  //                                      d    t   He3  He4  He6  Li6  Li7  Be7  He8  Li8
  static constexpr double dedxLower[10]{ 0.0, 0.0, 10., 10., 10., 25., 25., 40., 10., 25. };
  static constexpr double dedxUpper[10]{ 8.0, 8.0, 17., 17., 17., 38., 38., 55., 17., 38. };
#endif

  static constexpr int outPID[10]{
    1000010020, // d
    1000010030, // t
    1000020030, // He3
    1000020040, // He4
    1000020060, // He6
    1000030060, // Li6
    1000030070, // Li7
    1000040070, // Be7
    1000020080, // He8
    1000030080, // Li8
  };

  //                                      0    1   2    3    4    5    6    7    8    9
  //                                      d    t   He3  He4  He6  Li6  Li7  Be7  He8  Li8
  static constexpr double m2Lower[10]  { 3.0, 6.8, 1.0, 3.0, 6.5, 2.8, 4.0, 2.0, 0.0, 5.5 };
  static constexpr double m2Upper[10]  { 4.2, 9.1, 3.0, 4.2, 9.1, 4.2, 6.0, 3.2, 0.0, 6.7 };
  static constexpr double pLimit[10]   { 1.5, 2.5, 3.0, 4.0, 4.5, 4.0, 4.0, 4.0, 0.0, 0.0 };

  double logP = log(p);
  double logP2 = logP * logP;
  double logP3 = logP * logP2;

  bool useTof = true;

  for(int iPID=0; iPID<2; iPID++)
  {
    if( (useTof && isTofm2 && (m2 > m2Lower[iPID] && m2 < m2Upper[iPID])) || !useTof )
    {
      if( p < pLimit[iPID] )
      {
        double lowerBound = exp(pL[iPID][0] + pL[iPID][1] * logP + pL[iPID][2] * logP2 + pL[iPID][3] * logP3);
        double upperBound = exp(pU[iPID][0] + pU[iPID][1] * logP + pU[iPID][2] * logP2 + pU[iPID][3] * logP3);
        
        if(dEdX > lowerBound && dEdX < upperBound)
        {
          totalPDG.push_back(outPID[iPID]*q); 
        }
      }
      else if(dEdXPull[iPID + 5] < nSigmaCut && dEdX < 8.)
      {
        totalPDG.push_back(outPID[iPID]*q);
      }
    }
  }

  if(p > 0.3)
  {
    for(int iPID=2; iPID<8; iPID++)
    {
      if(iPID >= 4 && ! isTofm2) break;

      if( p < pLimit[iPID] )
      {
        double lowerBound = exp(pL[iPID][0] + pL[iPID][1] * logP + pL[iPID][2] * logP2 + pL[iPID][3] * logP3);
        double upperBound = exp(pU[iPID][0] + pU[iPID][1] * logP + pU[iPID][2] * logP2 + pU[iPID][3] * logP3);
        
        if(dEdX > lowerBound && dEdX < upperBound) 
        {
            if( !isTofm2 || (isTofm2 && (m2 > m2Lower[iPID] && m2 < m2Upper[iPID]) ) )
            {
              totalPDG.push_back(outPID[iPID]*q); 
            }
        }
      }
      else if( p >= pLimit[iPID] && dEdX > dedxLower[iPID] && dEdX < dedxUpper[iPID] )
      {
          if( !isTofm2 || (isTofm2 && (m2 > m2Lower[iPID] && m2 < m2Upper[iPID]) ) )
          {
            totalPDG.push_back(outPID[iPID]*q); 
          }
      }
    }
  }

#else /* __TFG__VERSION__ */

#if defined(PID_2018) // staryj
#include "PID2018.h"
#elif  defined(PID_MAY) // Mai
#include "PIDMAY.h"
#eliif (defined(PID_JUNE) //June
#include "PIDJUNE.h"
#endif //PID_2018 || PID_MAY || PID_JUNE
    
#endif /* __TFG__VERSION__ */
  if(totalPDG.size() == 0)
    totalPDG.push_back(-1);
  
  return totalPDG;
}

inline void Mix2(float& a, float& b, const float sinA, const float cosA)
{
  const float x = a;
  const float y = b;
  a = x * cosA - y * sinA;
  b = x * sinA + y * cosA;
}

void RotateXY2(KFParticle& particle, const float alpha)
{
  const float cosA = std::cos(alpha);
  const float sinA = std::sin(alpha);

  Mix2(particle.Px(), particle.Py(), sinA, cosA);

  Mix2(particle.Covariance(6), particle.Covariance(10), sinA, cosA);
  Mix2(particle.Covariance(7), particle.Covariance(11), sinA, cosA);
  Mix2(particle.Covariance(8), particle.Covariance(12), sinA, cosA);
  Mix2(particle.Covariance(18), particle.Covariance(19), sinA, cosA);
  Mix2(particle.Covariance(24), particle.Covariance(25), sinA, cosA);

  const float c9 = particle.Covariance(9);
  const float c13 = particle.Covariance(13);
  const float c14 = particle.Covariance(14);
  particle.Covariance(9)  = (c9 * cosA - c13 * sinA) * cosA - (c13 * cosA - c14 * sinA) * sinA;
  particle.Covariance(13) = (c13 * cosA + c9 * sinA) * cosA - (c13 * sinA + c14 * cosA) * sinA;
  particle.Covariance(14) = (c13 * cosA + c9 * sinA) * sinA + (c13 * sinA + c14 * cosA) * cosA;
}

void StKFParticleInterface::AddTrackToParticleList(const KFPTrack& track, int nHftHitsInTrack, int index, const std::vector<int>& totalPDG, KFVertex& pv, 
  std::vector<int>& primaryTrackList, std::vector<int>& nHftHits, std::vector<int>& particlesPdg, std::vector<KFParticle>& particles, int& nPartSaved,
  const KFPTrack* trackAtLastHit, std::vector<KFParticle>* particlesAtLastHit
						   , Float_t chi2, Int_t NDF
						   )
{
  for(unsigned int iPDG=0; iPDG<totalPDG.size(); iPDG++)
  {
    if( fTriggerMode && (nHftHitsInTrack < 3) ) continue;

    int pdg = totalPDG[iPDG];
    
    KFPTrack trackPDG = track;

    //correct for the charge of ions
    const int index2[9] = { 6,7,8, 10,11,12, 15,16,17 };
    const int index4[6] = { 9, 13,14, 18,19,20 };
#ifdef __TFG__VERSION__
#ifdef __MagFieldCorrection__
#endif /* __TFG__VERSION__ */
//TODO remove coefficient !!!!
#ifndef __TFG__VERSION__
#if 1
#endif /* ! __TFG__VERSION__ */
    {
#ifndef __TFG__VERSION__
      trackPDG.SetPx( trackPDG.GetPx()*0.998f );
      trackPDG.SetPy( trackPDG.GetPy()*0.998f );
      trackPDG.SetPz( trackPDG.GetPz()*0.998f );
#else /* __TFG__VERSION__ */
      trackPDG.SetPx( trackPDG.GetPx() * fgMagScaleFactor );
      trackPDG.SetPy( trackPDG.GetPy() * fgMagScaleFactor );
      trackPDG.SetPz( trackPDG.GetPz() * fgMagScaleFactor );
#endif /* __TFG__VERSION__ */
      for(int iIndex=0; iIndex<9; iIndex++){
        const int iC = index2[iIndex];
#ifndef __TFG__VERSION__
        trackPDG.SetCovariance( iC, trackPDG.GetCovariance(iC)*0.998f );
#else /* __TFG__VERSION__ */
        trackPDG.SetCovariance( iC, trackPDG.GetCovariance(iC) * fgMagScaleFactor );
#endif /* __TFG__VERSION__ */
      }
      for(int iIndex=0; iIndex<6; iIndex++){
        const int iC = index4[iIndex];
#ifndef __TFG__VERSION__
        trackPDG.SetCovariance( iC, trackPDG.GetCovariance(iC)*0.998f*0.998f );
#else /* __TFG__VERSION__ */
        trackPDG.SetCovariance( iC, trackPDG.GetCovariance(iC) * fgMagScaleFactor * fgMagScaleFactor );
#endif /* __TFG__VERSION__ */
      }
    }
#endif
    if(abs(pdg) == 1000020030 || abs(pdg) == 1000020040 || abs(pdg) == 1000020060) {
      trackPDG.SetCharge( trackPDG.Charge()*2.f );
      trackPDG.SetPx( trackPDG.GetPx()*2.f );
      trackPDG.SetPy( trackPDG.GetPy()*2.f );
      trackPDG.SetPz( trackPDG.GetPz()*2.f );
      for(int iIndex=0; iIndex<9; iIndex++){
        const int iC = index2[iIndex];
        trackPDG.SetCovariance( iC, trackPDG.GetCovariance(iC)*2.f );
      }
      for(int iIndex=0; iIndex<6; iIndex++){
        const int iC = index4[iIndex];
        trackPDG.SetCovariance( iC, trackPDG.GetCovariance(iC)*4.f );
      }
    }
    if(abs(pdg) == 1000030060 || abs(pdg) == 1000030070) {
      trackPDG.SetCharge( trackPDG.Charge()*3.f );
      trackPDG.SetPx( trackPDG.GetPx()*3.f );
      trackPDG.SetPy( trackPDG.GetPy()*3.f );
      trackPDG.SetPz( trackPDG.GetPz()*3.f );
      for(int iIndex=0; iIndex<9; iIndex++) {
        const int iC = index2[iIndex];
        trackPDG.SetCovariance( iC, trackPDG.GetCovariance(iC)*3.f );
      }
      for(int iIndex=0; iIndex<6; iIndex++) {
        const int iC = index4[iIndex];
        trackPDG.SetCovariance( iC, trackPDG.GetCovariance(iC)*9.f );
      }
    }
    if(abs(pdg) == 1000040070) {
      trackPDG.SetCharge( trackPDG.Charge()*4.f );
      trackPDG.SetPx( trackPDG.GetPx()*4.f );
      trackPDG.SetPy( trackPDG.GetPy()*4.f );
      trackPDG.SetPz( trackPDG.GetPz()*4.f );
      for(int iIndex=0; iIndex<9; iIndex++) {
        const int iC = index2[iIndex];
        trackPDG.SetCovariance( iC, trackPDG.GetCovariance(iC)*4.f );
      }
      for(int iIndex=0; iIndex<6; iIndex++) {
        const int iC = index4[iIndex];
        trackPDG.SetCovariance( iC, trackPDG.GetCovariance(iC)*16.f );
      }
    }

    //FIXME uncomment
//     nHftHits[nPartSaved] = nHftHitsInTrack;
    nHftHits[nPartSaved] = 0;
    
    KFParticle particle(trackPDG, pdg);
#ifdef __TFG__VERSION__
    particle.Chi2() = chi2;
    particle.NDF()  = NDF;
#endif /* __TFG__VERSION__ */
    float chiPrim = particle.GetDeviationFromVertex(pv);
    if( (chiPrim < fChiPrimaryCut && abs(pdg) < 1000000000) ||
        (chiPrim < fChiPrimaryCutFragments && abs(pdg) >= 1000000000))
    {
      if(fTriggerMode) continue;
      primaryTrackList.push_back(nPartSaved);
    }

    if(fTriggerMode && chiPrim > fChiPrimaryMaxCut) continue;

    particle.SetId(index);
    particles[nPartSaved] = particle;
#ifdef __TFG__VERSION__
    PrPOA(particle,AddTrackToParticleList);
#endif /* __TFG__VERSION__ */
#ifdef __kfpAtFirstHit__
    if(trackAtLastHit && particlesAtLastHit){
      KFPTrack trackPDGAtLastHit = *trackAtLastHit;

      if(abs(pdg) == 1000020030 || abs(pdg) == 1000020040 || abs(pdg) == 1000020060) {
        trackPDGAtLastHit.SetCharge( trackPDGAtLastHit.Charge()*2.f );
        trackPDGAtLastHit.SetPx( trackPDGAtLastHit.GetPx()*2.f );
        trackPDGAtLastHit.SetPy( trackPDGAtLastHit.GetPy()*2.f );
        trackPDGAtLastHit.SetPz( trackPDGAtLastHit.GetPz()*2.f );
        for(int iIndex=0; iIndex<9; iIndex++){
          const int iC = index2[iIndex];
          trackPDGAtLastHit.SetCovariance( iC, trackPDGAtLastHit.GetCovariance(iC)*2.f );
        }
        for(int iIndex=0; iIndex<6; iIndex++){
          const int iC = index4[iIndex];
          trackPDGAtLastHit.SetCovariance( iC, trackPDGAtLastHit.GetCovariance(iC)*4.f );
        }
      }
      if(abs(pdg) == 1000030060 || abs(pdg) == 1000030070) {
        trackPDGAtLastHit.SetCharge( trackPDGAtLastHit.Charge()*3.f );
        trackPDGAtLastHit.SetPx( trackPDGAtLastHit.GetPx()*3.f );
        trackPDGAtLastHit.SetPy( trackPDGAtLastHit.GetPy()*3.f );
        trackPDGAtLastHit.SetPz( trackPDGAtLastHit.GetPz()*3.f );
        for(int iIndex=0; iIndex<9; iIndex++) {
          const int iC = index2[iIndex];
          trackPDGAtLastHit.SetCovariance( iC, trackPDGAtLastHit.GetCovariance(iC)*3.f );
        }
        for(int iIndex=0; iIndex<6; iIndex++) {
          const int iC = index4[iIndex];
          trackPDGAtLastHit.SetCovariance( iC, trackPDGAtLastHit.GetCovariance(iC)*9.f );
        }
      }
      if(abs(pdg) == 1000040070) {
        trackPDGAtLastHit.SetCharge( trackPDGAtLastHit.Charge()*4.f );
        trackPDGAtLastHit.SetPx( trackPDGAtLastHit.GetPx()*4.f );
        trackPDGAtLastHit.SetPy( trackPDGAtLastHit.GetPy()*4.f );
        trackPDGAtLastHit.SetPz( trackPDGAtLastHit.GetPz()*4.f );
        for(int iIndex=0; iIndex<9; iIndex++) {
          const int iC = index2[iIndex];
          trackPDGAtLastHit.SetCovariance( iC, trackPDGAtLastHit.GetCovariance(iC)*4.f );
        }
        for(int iIndex=0; iIndex<6; iIndex++) {
          const int iC = index4[iIndex];
          trackPDGAtLastHit.SetCovariance( iC, trackPDGAtLastHit.GetCovariance(iC)*16.f );
        }
      }
          
      particlesAtLastHit->at(nPartSaved) = KFParticle(trackPDGAtLastHit, pdg);
      particlesAtLastHit->at(nPartSaved).SetId(index);
    }

#endif /* __kfpAtFirstHit__ */
    particlesPdg[nPartSaved] = pdg;

    nPartSaved++;
  }
}

void StKFParticleInterface::FillPIDHistograms(StPicoTrack *gTrack, const std::vector<int>& pdgVector, const bool isTofm2, float m2tof,  const bool isETofm2, float m2Etof)
{
  float momentum = gTrack->gPtot();
#ifndef __TFG__VERSION__
  for(UInt_t iPdg = 0; iPdg<pdgVector.size(); iPdg++)
#else /* __TFG__VERSION__ */
  if (pdgVector.size() == 1 && pdgVector[0] == -1) return;
  for(unsigned int iPdg = 0; iPdg<pdgVector.size(); iPdg++)
#endif /* __TFG__VERSION__ */
  {
    int pdg = pdgVector[iPdg];
    const int iTrackHisto = fTrackPdgToHistoIndex[pdg];
#ifndef __TFG__VERSION__
    if( ! (iTrackHisto < 0 || iTrackHisto >= NTrackHistoFolders) )
#else /* __TFG__VERSION__ */
    if( ! (iTrackHisto <= 0 || iTrackHisto >= NTrackHistoFolders) )
#endif /* __TFG__VERSION__ */
    {
#ifndef __TFG__VERSION__
      fHistoMomentumTracks[iTrackHisto] -> Fill(momentum);
      fHistodEdXTracks[iTrackHisto] -> Fill(momentum, gTrack->dEdx());
      if(isTofm2)
#else /* __TFG__VERSION__ */
      fHistoMomentumTracks[iTrackHisto] -> Fill(TMath::Log10(momentum));
      Double_t pL10 = TMath::Log10(momentum);
      Double_t dEdxL10 = (gTrack->dEdx() > 0) ? TMath::Log10(gTrack->dEdx()) : dEdxL10min;
      Double_t dNdxL10 = (gTrack->dNdx() > 0) ? TMath::Log10(gTrack->dNdx()) : dNdxL10min;
#ifdef __ETAPN_TOF_PLOTS__
      Double_t eta  = gTrack->gMom().Eta();
#endif /* __ETAPN_TOF_PLOTS__ */
      fHistodEdXTracks[iTrackHisto] -> Fill(pL10, dEdxL10);
      fHistodNdXTracks[iTrackHisto] -> Fill(pL10, dNdxL10);
      if(isTofm2 || isETofm2)
#endif /* __TFG__VERSION__ */
      {
#ifndef __TFG__VERSION__
        fHistodEdXwithToFTracks[iTrackHisto] -> Fill(momentum, gTrack->dEdx());
        fHistoTofPIDTracks[iTrackHisto] -> Fill(momentum, m2tof);
#else /* __TFG__VERSION__ */
        fHistodEdXwithToFTracks[iTrackHisto] -> Fill(pL10, dEdxL10);
        if (isTofm2) {
	  fHistoTofPIDTracks[iTrackHisto][0] -> Fill(pL10, m2tof);
#ifdef __ETAPN_TOF_PLOTS__
	  if (eta > 0) fHistoTofPIDTracks[iTrackHisto][1] -> Fill(pL10, m2tof);
	  else         fHistoTofPIDTracks[iTrackHisto][2] -> Fill(pL10, m2tof);
#endif /* __ETAPN_TOF_PLOTS__ */
	}
        if (isETofm2) fHistoETofPIDTracks[iTrackHisto] -> Fill(pL10, m2Etof);
#endif /* __TFG__VERSION__ */
        
#ifdef __TFG__VERSION__
        if(abs(pdg)==11)
        {
          fHistodEdXnSigma[iTrackHisto] -> Fill(momentum, gTrack->nSigmaElectron());
	}
#endif /* __TFG__VERSION__ */
        if(abs(pdg)==211)
        {
#ifndef __TFG__VERSION__
          fHistodEdXPull[iTrackHisto] -> Fill(momentum, gTrack->dEdxPull(0.139570, fdEdXMode, 1));
#else /* __TFG__VERSION__ */
          fHistodEdXnSigma[iTrackHisto] -> Fill(momentum, gTrack->nSigmaPion());
          fHistodEdXPull[iTrackHisto] -> Fill(pL10, gTrack->dEdxPull(0.139570, 1, 1));
          fHistodNdXPull[iTrackHisto] -> Fill(pL10, gTrack->dEdxPull(0.139570, 2, 1));
#endif /* __TFG__VERSION__ */
          float betaGamma = TMath::Log10(momentum/0.139570);
#ifndef __TFG__VERSION__
          float z = gTrack->dEdxPull(0.139570, fdEdXMode, 1)*gTrack->dEdxError();
#else /* __TFG__VERSION__ */
          float z = gTrack->dEdxPull(0.139570, fdEdXMode, 1)*gTrack->dEdxError(fdEdXMode);
#endif /* __TFG__VERSION__ */
          fHistodEdXZ[iTrackHisto]->Fill(betaGamma, z);
          
          betaGamma = TMath::Log10(momentum/5.485799e-4);
#ifndef __TFG__VERSION__
          z = gTrack->nSigmaElectron()*gTrack->dEdxError();
          fHistodEdXZ[0]->Fill(betaGamma, z);
#else /* __TFG__VERSION__ */
          z = gTrack->dEdxPullElectron(fdEdXMode)*gTrack->dEdxError(fdEdXMode);
          fHistodEdXZ[1]->Fill(betaGamma, z);
#endif /* __TFG__VERSION__ */
        }
        if(abs(pdg)==321)
        {
#ifndef __TFG__VERSION__
          fHistodEdXPull[iTrackHisto] -> Fill(momentum, gTrack->dEdxPull(0.493677, fdEdXMode, 1));
#else /* __TFG__VERSION__ */
          fHistodEdXnSigma[iTrackHisto] -> Fill(momentum, gTrack->nSigmaKaon());
          fHistodEdXPull[iTrackHisto] -> Fill(pL10, gTrack->dEdxPull(0.493677, 1, 1));
          fHistodNdXPull[iTrackHisto] -> Fill(pL10, gTrack->dEdxPull(0.493677, 2, 1));
#endif /* __TFG__VERSION__ */
          float betaGamma = TMath::Log10(momentum/0.493677);
#ifndef __TFG__VERSION__
          float z = gTrack->dEdxPull(0.493677, fdEdXMode, 1)*gTrack->dEdxError();
#else /* __TFG__VERSION__ */
          float z = gTrack->dEdxPull(0.493677, 1, 1)*gTrack->dEdxError();
#endif /* __TFG__VERSION__ */
          fHistodEdXZ[iTrackHisto]->Fill(betaGamma, z);
        }
        if(abs(pdg)==2212)
        {
#ifndef __TFG__VERSION__
          fHistodEdXPull[iTrackHisto] -> Fill(momentum, gTrack->dEdxPull(0.938272, fdEdXMode, 1));
#else /* __TFG__VERSION__ */
          fHistodEdXnSigma[iTrackHisto] -> Fill(momentum, gTrack->nSigmaProton());
          fHistodEdXPull[iTrackHisto] -> Fill(pL10, gTrack->dEdxPull(0.938272, 1, 1));
          fHistodNdXPull[iTrackHisto] -> Fill(pL10, gTrack->dEdxPull(0.938272, 2, 1));
#endif /* __TFG__VERSION__ */
          float betaGamma = TMath::Log10(momentum/0.938272);
#ifndef __TFG__VERSION__
          float z = gTrack->dEdxPull(0.938272, fdEdXMode, 1)*gTrack->dEdxError();
#else /* __TFG__VERSION__ */
          float z = gTrack->dEdxPull(0.938272, 1, 1)*gTrack->dEdxError();
#endif /* __TFG__VERSION__ */
          fHistodEdXZ[iTrackHisto]->Fill(betaGamma, z);
        }
        if(abs(pdg)==1000010020)
        {
#ifndef __TFG__VERSION__
          fHistodEdXPull[iTrackHisto] -> Fill(momentum, gTrack->dEdxPull(1.876124, fdEdXMode, 1));
#else /* __TFG__VERSION__ */
          fHistodEdXPull[iTrackHisto] -> Fill(pL10, gTrack->dEdxPull(1.876124, 1, 1));
          fHistodNdXPull[iTrackHisto] -> Fill(pL10, gTrack->dEdxPull(1.876124, 2, 1));
#endif /* __TFG__VERSION__ */
          float betaGamma = TMath::Log10(momentum/1.876124);
#ifndef __TFG__VERSION__
          float z = gTrack->dEdxPull(1.876124, fdEdXMode, 1)*gTrack->dEdxError();
#else /* __TFG__VERSION__ */
          float z = gTrack->dEdxPull(1.876124, 1, 1)*gTrack->dEdxError();
#endif /* __TFG__VERSION__ */
          fHistodEdXZ[iTrackHisto]->Fill(betaGamma, z);
        }
        if(abs(pdg)==1000010030)
        {
#ifndef __TFG__VERSION__
          fHistodEdXPull[iTrackHisto] -> Fill(momentum, gTrack->dEdxPull(2.809432, fdEdXMode, 1));
#else /* __TFG__VERSION__ */
          fHistodEdXPull[iTrackHisto] -> Fill(pL10, gTrack->dEdxPull(2.809432, 1, 1));
          fHistodNdXPull[iTrackHisto] -> Fill(pL10, gTrack->dEdxPull(2.809432, 2, 1));
#endif /* __TFG__VERSION__ */
          float betaGamma = TMath::Log10(momentum/2.809432);
#ifndef __TFG__VERSION__
          float z = gTrack->dEdxPull(2.809432, fdEdXMode, 1)*gTrack->dEdxError();
#else /* __TFG__VERSION__ */
          float z = gTrack->dEdxPull(2.809432, 1, 1)*gTrack->dEdxError();
#endif /* __TFG__VERSION__ */
          fHistodEdXZ[iTrackHisto]->Fill(betaGamma, z);
        }
        if(abs(pdg)==1000020030)
        {
#ifndef __TFG__VERSION__
          fHistodEdXPull[iTrackHisto] -> Fill(momentum, gTrack->dEdxPull(2.809413, fdEdXMode, 2));
#else /* __TFG__VERSION__ */
          fHistodEdXPull[iTrackHisto] -> Fill(pL10, gTrack->dEdxPull(2.809413, 1, 2));
          fHistodNdXPull[iTrackHisto] -> Fill(pL10, gTrack->dEdxPull(2.809413, 2, 2));
#endif /* __TFG__VERSION__ */
          float betaGamma = TMath::Log10(momentum/2.809413);
#ifndef __TFG__VERSION__
          float z = gTrack->dEdxPull(2.809413, fdEdXMode, 2)*gTrack->dEdxError();
#else /* __TFG__VERSION__ */
          float z = gTrack->dEdxPull(2.809413, 1, 2)*gTrack->dEdxError();
#endif /* __TFG__VERSION__ */
          fHistodEdXZ[iTrackHisto]->Fill(betaGamma, z);
        }
        if(abs(pdg)==1000020040)
        {
#ifndef __TFG__VERSION__
          fHistodEdXPull[iTrackHisto] -> Fill(momentum, gTrack->dEdxPull(3.728400, fdEdXMode, 2));
#else /* __TFG__VERSION__ */
          fHistodEdXPull[iTrackHisto] -> Fill(pL10, gTrack->dEdxPull(3.728400, 1, 2));
          fHistodNdXPull[iTrackHisto] -> Fill(pL10, gTrack->dEdxPull(3.728400, 2, 2));
#endif /* __TFG__VERSION__ */
          float betaGamma = TMath::Log10(momentum/3.728400);
#ifndef __TFG__VERSION__
          float z = gTrack->dEdxPull(3.728400, fdEdXMode, 2)*gTrack->dEdxError();
#else /* __TFG__VERSION__ */
          float z = gTrack->dEdxPull(3.728400, 1, 2)*gTrack->dEdxError();
#endif /* __TFG__VERSION__ */
          fHistodEdXZ[iTrackHisto]->Fill(betaGamma, z);
        }
      }
    }
  }
}

void StKFParticleInterface::FillPIDHistograms(StMuTrack *gTrack, const std::vector<int>& pdgVector, const bool isTofm2, float m2tof, const bool isETofm2, float m2Etof)
{
  float momentum = gTrack->p().mag();
  Double_t pL10 = TMath::Log10(momentum);
  for(unsigned int iPdg = 0; iPdg<pdgVector.size(); iPdg++)
  {
    int pdg = pdgVector[iPdg];
    const int iTrackHisto = fTrackPdgToHistoIndex[pdg];
#ifndef __TFG__VERSION__
    if( ! (iTrackHisto < 0 || iTrackHisto >= NTrackHistoFolders) )
#else /* __TFG__VERSION__ */
    if( ! (iTrackHisto <= 0 || iTrackHisto >= NTrackHistoFolders) )
#endif /* __TFG__VERSION__ */
    {
      fHistoMomentumTracks[iTrackHisto] -> Fill(momentum);
      fHistodEdXTracks[iTrackHisto] -> Fill(momentum, gTrack->dEdx()*1.e6);
      if(isTofm2)
      {
#ifndef __TFG__VERSION__
        fHistodEdXwithToFTracks[iTrackHisto] -> Fill(momentum, gTrack->dEdx()*1.e6);
        fHistoTofPIDTracks[iTrackHisto] -> Fill(momentum, m2tof);
        
#else /* __TFG__VERSION__ */
        fHistodEdXwithToFTracks[iTrackHisto] -> Fill(momentum, gTrack->dEdx()*1.e6);
        fHistoTofPIDTracks[iTrackHisto][0] -> Fill(pL10, m2tof);
#endif /* __TFG__VERSION__ */
        if(abs(pdg)==211)
          fHistodEdXPull[iTrackHisto] -> Fill(momentum, gTrack->dEdxPull(0.139570, fdEdXMode, 1));
        if(abs(pdg)==321)
          fHistodEdXPull[iTrackHisto] -> Fill(momentum, gTrack->dEdxPull(0.493677, fdEdXMode, 1));
        if(abs(pdg)==2212)
          fHistodEdXPull[iTrackHisto] -> Fill(momentum, gTrack->dEdxPull(0.938272, fdEdXMode, 1));
        if(abs(pdg)==1000010020)
          fHistodEdXPull[iTrackHisto] -> Fill(momentum, gTrack->dEdxPull(1.876124, fdEdXMode, 1));
        if(abs(pdg)==1000010030)
          fHistodEdXPull[iTrackHisto] -> Fill(momentum, gTrack->dEdxPull(2.809432, fdEdXMode, 1));
        if(abs(pdg)==1000020030)
          fHistodEdXPull[iTrackHisto] -> Fill(momentum, gTrack->dEdxPull(2.809413, fdEdXMode, 2));
        if(abs(pdg)==1000020040)
          fHistodEdXPull[iTrackHisto] -> Fill(momentum, gTrack->dEdxPull(3.728400, fdEdXMode, 2));
      }
    }
  }
}

bool StKFParticleInterface::OpenCharmTrigger() 
{
  bool triggerDMesons = false;
  if(fKFParticleTopoReconstructor->NPrimaryVertices() == 0) return false;
    
  for(unsigned int iParticle=0; iParticle<GetParticles().size(); iParticle++)
  {
    KFParticle particle = GetParticles()[iParticle];
    
    if( abs(particle.GetPDG()) == 421 ||
        abs(particle.GetPDG()) == 429 || 
        abs(particle.GetPDG()) == 420 || 
        abs(particle.GetPDG()) == 411 || 
        abs(particle.GetPDG()) == 431 || 
        abs(particle.GetPDG()) == 4122 ||
        abs(particle.GetPDG()) == 426 )
    {
      KFParticleSIMD tempSIMDPart(particle);
      float_v l,dl;
      KFParticleSIMD pv(fKFParticleTopoReconstructor->GetPrimVertex());
      tempSIMDPart.GetDistanceToVertexLine(pv, l, dl);
      
      if(abs(particle.GetPDG()) == 411)
        triggerDMesons = (l[0] < 0.4);
      else    
        triggerDMesons = (l[0] < 0.2);
    }
  }
  
  return triggerDMesons;
}

void StKFParticleInterface::OpenCharmTriggerCompression(int nTracksTriggered, int nTracksInEvent, bool triggerDMesons) 
{
  static int nTriggeredEvents = 0;
  static int nTracksInEventTriggered = 0;
  static int nTracksInEventTotal = 0;
  static int nEvents = 0;
  nEvents++;
  nTracksInEventTotal += nTracksInEvent;
  if(triggerDMesons)
  {
    nTriggeredEvents++;
    nTracksInEventTriggered += nTracksTriggered;
    std::cout << "N Events " << nEvents << "    N triggered events " << nTriggeredEvents << "    ratio " << (double(nEvents)/double(nTriggeredEvents)) << std::endl;
    std::cout << "N Tracks " << nTracksInEventTotal << "    N triggered events " << nTracksInEventTriggered << "    ratio " << (double(nTracksInEventTotal)/double(nTracksInEventTriggered)) << std::endl;
  }
}

void StKFParticleInterface::ResizeTrackPidVectors(const int nTracks)
{
  for(int iHypothesis=0; iHypothesis<3; iHypothesis++)
  {
    fTrackPidTof[iHypothesis].clear();
    fTrackPidTof[iHypothesis].resize(nTracks, -1);
    
    fTrackPidTpc[iHypothesis].clear();
    fTrackPidTpc[iHypothesis].resize(nTracks, -1);
  }
}

bool StKFParticleInterface::ProcessEvent(StPicoDst* picoDst, std::vector<int>& triggeredTracks)
{
  triggeredTracks.resize(0);
  
  //read PV from pico Event
  KFVertex primaryVertex;
  vector<int> primaryTrackList;
    
  StPicoEvent* picoEvent = picoDst->event();
  if(!picoEvent) return 0;

  const TVector3 picoPV = picoEvent->primaryVertex();
  const TVector3 picoPVError = picoEvent->primaryVertexError();
#ifdef __TFG__VERSION__
  StTrackCombPiD::SetBestVx(picoEvent);
#endif /* __TFG__VERSION__ */
  KFPVertex primVtx_tmp;
  primVtx_tmp.SetXYZ(picoPV.x(), picoPV.y(), picoPV.z());
  double dx = picoPVError.x();
  double dy = picoPVError.y();
  double dz = picoPVError.z();
  primVtx_tmp.SetCovarianceMatrix( dx*dx, 0, dy*dy, 0, 0, dz*dz );
  primaryVertex = KFVertex(primVtx_tmp);
#define  __FXT_PV_REFIT__
#ifdef __FXT_PV_REFIT__
//   if(!IsGoodPV(primaryVertex)) return 0;
  
  KFVertex myPV;
  std::vector<bool> isPileup;
  std::vector<KFVertex> pileupPv;
  if (IsFixedTarget()) {
    if(!FindFixedTargetPV(picoDst, myPV, pileupPv, isPileup)) return 0;
    primaryVertex = myPV;
  }
#endif /* __FXT_PV_REFIT__ */
  
  
  Int_t nGlobalTracks = picoDst->numberOfTracks( );
#ifdef __TFG__VERSION__
  if (_debug) {std::cout << "ProcessEventStPicoDst*) with " << nGlobalTracks << " global tracks" << std::endl;}
#endif /* __TFG__VERSION__ */
  fParticles.resize(nGlobalTracks*10);
  fNHftHits.resize(nGlobalTracks*10);
  fParticlesPdg.resize(nGlobalTracks*10);
  int nPartSaved = 0;
  int nUsedTracks = 0;
  
#ifndef __TFG__VERSION__
  std::vector<int> trakIdToI(nGlobalTracks*2);

#else /* __TFG__VERSION__ */
  fm2TofArray = std::vector<float>(nGlobalTracks*2, -1.0e6f);
  ftrackIdToI  = std::vector<int>(nGlobalTracks*2);
  
  
#endif /* __TFG__VERSION__ */
  for (Int_t iTrack = 0; iTrack < nGlobalTracks; iTrack++) 
  {
    StPicoTrack *gTrack = picoDst->track(iTrack);
    
//     if ( (gTrack->status() != 0) && !(gTrack->isPrimary()) ) continue; //TODO
    
    if (! gTrack)            continue;
#ifdef __TFG__VERSION__
    PrPP(gTrack);
#endif /* __TFG__VERSION__ */
    if (! gTrack->charge())  continue;
    if (  gTrack->nHitsFit() < 15) continue;
//     if (  gTrack->nHitsFit() < 10) continue;
    if(IsFixedTarget()) {
      if (  gTrack->dEdxError() < 0.01 || gTrack->dEdxError() > 0.15 ) continue;
    }   else   {
      if (  gTrack->dEdxError() < 0.04 || gTrack->dEdxError() > 0.12 ) continue;
    }
    const UInt_t index = gTrack->id();

#ifdef __FXT_PV_REFIT__
    if(IsFixedTarget() && isPileup[index]) continue;
#endif
    
#ifndef __TFG__VERSION__
    if(index >= trakIdToI.size()) trakIdToI.resize(index+1);
    trakIdToI[index] = iTrack;
#else /* __TFG__VERSION__ */
    if(index >= ftrackIdToI.size()) ftrackIdToI.resize(index+1);
    ftrackIdToI[index] = iTrack;
#endif /* __TFG__VERSION__ */
    
    int nHftHitsInTrack = 0;
    if(gTrack->hasPxl1Hit()) nHftHitsInTrack++;
    if(gTrack->hasPxl2Hit()) nHftHitsInTrack++;
    if(gTrack->hasIstHit()) nHftHitsInTrack++;
//       if(gTrack->hasSstHit()) nHftHitsInTrack++;
    
    //FIXME temporary solution!!!
    nHftHitsInTrack = gTrack->nHitsFit();
#ifdef __USE_HFT__  
    if(fCollectTrackHistograms) fTrackHistograms[0]->Fill(nHftHitsInTrack);
    if(fUseHFTTracksOnly && !gTrack->hasIstHit()) continue;
#endif /*  __USE_HFT__ */        
    StPicoTrackCovMatrix *cov = picoDst->trackCovMatrix(iTrack);
    const StDcaGeometry &dcaG = cov->dcaGeometry();
#ifdef __TFG__VERSION__
    if (StMuDst::dca3Dmax() > 0) {
      // Cut large Dca
      THelixTrack t = dcaG.thelix();
      Double_t xyz[3] = {primaryVertex.X(), primaryVertex.Y(), primaryVertex.Z()};
      Double_t dca3D = t.Dca(xyz);
      if (dca3D > StMuDst::dca3Dmax()) continue;
    }
#endif /* __TFG__VERSION__ */
    Int_t q = 1; if (gTrack->charge() < 0) q = -1;
    KFPTrack track;
    if( !GetTrack(dcaG, track, q, index) ) continue;

    KFParticle ppp(track, 211);
    const float ccc = ppp.GetDeviationFromVertex(primaryVertex);
    const bool isCollectPID = ccc < 18.f;
    Double_t pL10 = (track.GetP() > 0) ? TMath::Log10(track.GetP()) : -2;
    Double_t dEdxL10 = (gTrack->dEdx() > 0) ? TMath::Log10(gTrack->dEdx()) : dEdxL10min;
    Double_t dNdxL10 = (gTrack->dNdx() > 0) ? TMath::Log10(gTrack->dNdx()) : dNdxL10min;
    double m2tof = -1.e6;
    bool isTofm2 = false;
    double m2Etof = -1.e6;
    bool isETofm2 = false;

    if(fCollectTrackHistograms && isCollectPID) {
      TVector3 t(track.GetPx(),track.GetPy(),track.GetPz());
      if (gTrack->isPrimary())
	fTrackHistograms2D[kEtaVspT]->Fill(TMath::Log10(t.Perp()), t.PseudoRapidity());
      fTrackHistograms2D[kEtaVspTAll]->Fill(TMath::Log10(t.Perp()), t.PseudoRapidity());
      fTrackHistograms2D[khdEdX]->Fill(pL10, dEdxL10);
      if(q>0) fTrackHistograms2D[khdEdXPos]->Fill(pL10, dEdxL10);
      else    fTrackHistograms2D[khdEdXNeg]->Fill(pL10, dEdxL10);
      fTrackHistograms2D[khdNdX]->Fill(pL10, dNdxL10);
      if(q>0) fTrackHistograms2D[khdNdXPos]->Fill(pL10, dNdxL10);
      else    fTrackHistograms2D[khdNdXNeg]->Fill(pL10, dNdxL10);

      fTrackHistograms2D[khdEdXwithTof]->Fill(pL10, dEdxL10);
      fTrackHistograms2D[khdNdXwithTof]->Fill(pL10, dNdxL10);
#ifdef __ETAPN_TOF_PLOTS__
      Double_t eta = gTrack->gMom().Eta();
#endif /* __ETAPN_TOF_PLOTS__ */
      // [B|E]Tof 
      if(gTrack->bTofPidTraitsIndex() >= 0) {
	const StPicoBTofPidTraits* btofPid = picoDst->btofPidTraits(gTrack->bTofPidTraitsIndex());
	double betaTof2 = btofPid->btofBeta() * btofPid->btofBeta();
	if(fabs(betaTof2) > 1.e-6) {
	  m2tof = track.GetP()*track.GetP()*(1./betaTof2 - 1.);
	  if(index >= fm2TofArray.size()) fm2TofArray.resize(index+1);
	  fm2TofArray[index] = m2tof;
	  isTofm2 = true;
	  fTrackHistograms2D[khdEdXwithTof]->Fill(pL10, dEdxL10);  
	  fTrackHistograms2D[khdNdXwithTof]->Fill(pL10, dNdxL10);  
	}
	fTrackHistograms2D[khTofPID]->Fill(pL10, m2tof);
#ifdef __ETAPN_TOF_PLOTS__
	if (eta > 0) fTrackHistograms2D[khTofPIDP]->Fill(pL10, m2tof);
	else         fTrackHistograms2D[khTofPIDN]->Fill(pL10, m2tof);
#endif /* __ETAPN_TOF_PLOTS__ */
      } else if (gTrack->eTofPidTraitsIndex() >= 0) { 
	const StPicoETofPidTraits* etofPid = picoDst->etofPidTraits(gTrack->eTofPidTraitsIndex());
	double betaTof2 = etofPid->beta() * etofPid->beta();
	if(fabs(betaTof2) > 1.e-6) {
	  m2tof = track.GetP()*track.GetP()*(1./betaTof2 - 1.);
	  if(index >= fm2TofArray.size()) fm2TofArray.resize(index+1);
	  fm2TofArray[index] = m2tof;
	  isTofm2 = true;
	  isETofm2 = isTofm2;
	  m2Etof = m2tof;
	  fTrackHistograms2D[khETofPID]->Fill(pL10, dEdxL10);  
	  fTrackHistograms2D[khdNdXwithTof]->Fill(pL10, dNdxL10);  
	}
	fTrackHistograms2D[khdEdXETofPID]->Fill(pL10, m2tof);
      }
      fTrackHistograms2D[khdEdXTofPID]->Fill(dEdxL10, m2tof);
      fTrackHistograms2D[khdNdXTofPID]->Fill(dNdxL10, m2tof);
    }
    StTrackCombPiD PiD(picoDst,iTrack);
    vector<int> totalPDG = PiD.GetPDG();
    int nPartSaved0 = nPartSaved;
    unsigned int nPrimaryTracks = primaryTrackList.size();
    Int_t NDF = 2*gTrack->nHitsFit() - 5;
    Float_t Chi2 = gTrack->chi2()*NDF;
    PrPO(track);
    AddTrackToParticleList(track, nHftHitsInTrack, index, totalPDG, primaryVertex, primaryTrackList, fNHftHits, fParticlesPdg, fParticles, nPartSaved, 0, 0, Chi2, NDF); 
    
    if(nPartSaved > nPartSaved0) 
      triggeredTracks.push_back(iTrack);
    
    //fill PID histograms if they are created
      //Histograms are filled for secondary tracks only!!!
    if(fCollectPIDHistograms && (nPrimaryTracks == primaryTrackList.size())) 
      {
	vector<int> selectedPdg;
	for(int iPdg = nPartSaved0; iPdg<nPartSaved; iPdg++)
	  selectedPdg.push_back(fParticlesPdg[iPdg]);
	FillPIDHistograms(gTrack, selectedPdg, isTofm2, m2tof, isETofm2, m2Etof);
      }

    nUsedTracks++;
  }
  
  fParticles.resize(nPartSaved);
  fParticlesPdg.resize(nPartSaved);
  fNHftHits.resize(nPartSaved);

  if(nUsedTracks==0) return 0;
  const int nPrimary = primaryTrackList.size();
  if(fCollectTrackHistograms)
    {
      fTrackHistograms[2]->Fill( double(nPrimary)/double(nUsedTracks) );
      Double_t nPL10 = (primaryTrackList.size() > 0) ? TMath::Log10(primaryTrackList.size()) : -1;
      Double_t nGL10 = (nUsedTracks > 0) ? TMath::Log10(nUsedTracks) : -1;
      fTrackHistograms2D[khGlobalVsPrimaryTracks]->Fill( nGL10, nPL10);
    }
  if( fCleanLowPVTrackEvents) {
    if( 10*nPrimary < (nUsedTracks - nPrimary) ) return 0;  
    if( sqrt(dx*dx + dy*dy) > 0.45 ) return 0;
    if (IsFixedTarget()) {
      if(  !(primaryVertex.Z() > 196. && primaryVertex.Z() < 204.) ) return 0;
      if(  !(primaryVertex.X() > -2.5 && primaryVertex.X() < 2.  ) ) return 0;
      if(  !(primaryVertex.Y() > -4.  && primaryVertex.Y() < 0.  ) ) return 0;
    //   if( fCleanLowPVTrackEvents && ( (nUsedTracks - nPrimary) > (50. + 0.75*nPrimary) ) ) return 0;
      if( (nUsedTracks - nPrimary) > 150 ) return 0;
    } else {
       if( primaryVertex.GetR() > 2.5 ) return 0;
    }
  }
  const Double_t field = picoEvent->bField();  
  SetField(field);
  
  CleanPV();
  InitParticles();

  //read PV
  AddPV(primaryVertex, primaryTrackList);
  if(fCollectTrackHistograms)    {
    fTrackHistograms[1]->Fill(sqrt(dx*dx + dy*dy));
#ifndef __TFG__VERSION__
    fTrackHistograms2D[khPVErrorVsNTracks]->Fill( nPartSaved, sqrt(dx*dx + dy*dy) );
    fTrackHistograms2D[khPVErrorVsNPVTracks]->Fill( primaryTrackList.size(), sqrt(dx*dx + dy*dy) );
#else /* __TFG__VERSION__ */
    Double_t nL10 = (nPartSaved > 0) ? TMath::Log10(nPartSaved) : -1;
    fTrackHistograms2D[khPVErrorVsNTracks]->Fill( nL10, sqrt(dx*dx + dy*dy) );
    Double_t npL10 = (primaryTrackList.size()) ? TMath::Log10(primaryTrackList.size()) : -1;
    fTrackHistograms2D[khPVErrorVsNPVTracks]->Fill( npL10, sqrt(dx*dx + dy*dy) );
#endif /* __TFG__VERSION__ */
  }
  //reconstruct short-lived particles
  ReconstructParticles();
  
#ifdef __TFG__VERSION__
  if (fPidQA) {
    PidQA(picoDst);
  }
#endif /* __TFG__VERSION__ */
  return 1;
  }
 
bool StKFParticleInterface::ProcessEvent(StMuDst* muDst, vector<KFMCTrack>& mcTracks, vector<int>& mcIndices, bool processSignal)
 {  
  mcTracks.resize(muDst->numberOfMcTracks());
  for (unsigned int iMCTrack=0; iMCTrack<muDst->numberOfMcTracks(); iMCTrack++) 
  {
    StMuMcTrack *mcTrack = muDst->MCtrack(iMCTrack);
    if (! mcTrack) continue;    
    KFMCTrack &mcTrackKF = mcTracks[iMCTrack];
    mcTrack->FillKFMCTrack(mcTrackKF);
    mcTrackKF.SetNMCPixelPoints(mcTrack->No_ist_hit() + mcTrack->No_ssd_hit() + mcTrack->No_pix_hit());
  }
  
  //read PV
  KFVertex primaryVertex;
  vector<int> primaryTrackList;

  float bestRank=-1000000;
#ifdef __TFG__VERSION__
  int bestPV=-1;
#endif /* __TFG__VERSION__ */
  double dx = 0., dy = 0., dz = 0.;
  for(unsigned int iPV=0; iPV<muDst->numberOfPrimaryVertices(); iPV++) 
  {
    StMuPrimaryVertex *Vtx = muDst->primaryVertex(iPV);
    if(!Vtx) continue;
    if (bestRank < Vtx->ranking()) {
      bestRank = Vtx->ranking();
#ifdef __TFG__VERSION__
      bestPV = iPV;
#endif /* __TFG__VERSION__ */
    }
    else continue;
#ifdef __TFG__VERSION__
    StTrackCombPiD::SetBestVx(muDst->primaryVertex(bestPV));
#endif /* __TFG__VERSION__ */
    //convert StMuPrimaryVertex to KFVertex
    KFPVertex kfVertex;
    kfVertex.SetXYZ(Vtx->position().x(), Vtx->position().y(), Vtx->position().z());
    dx = Vtx->posError().x();
    dy = Vtx->posError().y();
    dz = Vtx->posError().z();
    kfVertex.SetCovarianceMatrix( dx*dx, 0, dy*dy, 0, 0, dz*dz );
    UShort_t noTracks = Vtx->noTracks();
    kfVertex.SetNContributors(noTracks);
    kfVertex.SetChi2(Vtx->chiSquared());
    primaryVertex = KFVertex(kfVertex);
  }  
//   if(!IsGoodPV(primaryVertex)) return 0;

  Int_t nGlobalTracks = muDst->numberOfGlobalTracks();
  
  fParticles.resize(nGlobalTracks*10);
#ifdef __kfpAtFirstHit__
  fParticlesAtLastHit.resize(nGlobalTracks*10);
#endif
  fNHftHits.resize(nGlobalTracks*10);
  fParticlesPdg.resize(nGlobalTracks*10);
  int nPartSaved = 0;
  int nUsedTracks = 0;
  ////////////////////////////////////////////////////////////////////////////////
#ifndef __TFG__VERSION__
  std::vector<int> trakIdToI(nGlobalTracks*2);
#else /* __TFG__VERSION__ */
  ftrackIdToI = std::vector<int>(nGlobalTracks*2);
#endif /* __TFG__VERSION__ */
  
  for (Int_t iTrack = 0; iTrack < nGlobalTracks; iTrack++) 
  {
    StMuTrack *gTrack = muDst->globalTracks(iTrack);
    if (! gTrack)            continue;
    if (! gTrack->charge())  continue;
    if (  gTrack->flag() < 100 ||  gTrack->flag()%100 == 11) continue; // bad fit or short track pointing to EEMC
    if (  gTrack->flag() > 1000) continue;  // pile up track in TPC
    if (  gTrack->nHitsFit() < 15) continue;
#ifndef __TFG__VERSION__
    if (  gTrack->probPidTraits().dEdxErrorFit() < 0.04 || gTrack->probPidTraits().dEdxErrorFit() > 0.12 ) continue;
#else /* __TFG__VERSION__ */
    if (  gTrack->probPidTraits().dEdxErrorFit() < 0.01 || gTrack->probPidTraits().dEdxErrorFit() > 0.16 ) continue;
#endif /* __TFG__VERSION__ */
    int nHftHitsInTrack = gTrack->nHitsFit(kIstId) + gTrack->nHitsFit(kSsdId) + gTrack->nHitsFit(kPxlId);
#ifdef __USE_HFT__
    if(fCollectTrackHistograms) fTrackHistograms[0]->Fill(nHftHitsInTrack);
    if(fUseHFTTracksOnly && nHftHitsInTrack < 3) continue;
#endif /* __USE_HFT__ */

    const UInt_t index = gTrack->id();
#ifndef __TFG__VERSION__
    if(index >= trakIdToI.size()) trakIdToI.resize(index+1);
    trakIdToI[index] = iTrack;
#else /* __TFG__VERSION__ */
    if(index >= ftrackIdToI.size()) ftrackIdToI.resize(index+1);
    ftrackIdToI[index] = iTrack;
#endif /* __TFG__VERSION__ */    
    int mcIndex = gTrack->idTruth()-1;
    if(mcIndex >= int(mcTracks.size()))
      mcIndex = -1;
    if(mcIndex > -1) {
      if(!processSignal) continue;
    }
    else if(processSignal) continue;
    
    Int_t q = 1; if (gTrack->charge() < 0) q = -1;
#ifdef __kfpAtFirstHit__
    KFPTrack track = gTrack->kfpTrackAtFirstHit();
    KFPTrack trackAtLastHit  = gTrack->kfpTrackAtLastHit();
#else
    Int_t dcaGeometryIndex = gTrack->index2Cov();
    if (dcaGeometryIndex < 0) continue;
    StDcaGeometry *dcaG = StMuDst::instance()->covGlobTracks(dcaGeometryIndex);
    if (! dcaG) continue;
#ifdef __TFG__VERSION__
    if (StMuDst::dca3Dmax() > 0) {
      // Cut large Dca
      THelixTrack t = dcaG->thelix();
      Double_t xyz[3] = {primaryVertex.X(), primaryVertex.Y(), primaryVertex.Z()};
      Double_t dca3D = t.Dca(xyz);
      if (dca3D > StMuDst::dca3Dmax()) continue;
    }
#endif /* __TFG__VERSION__ */
      
    KFPTrack track;
    if( !GetTrack(*dcaG, track, q, index) ) continue;
#endif /* __kfpAtFirstHit__ */ 

    if(fCollectTrackHistograms)
    {
#ifndef __TFG__VERSION__
      fTrackHistograms2D[khdEdX]->Fill(track.GetP(), gTrack->dEdx()*1.e6);
      if(q>0) fTrackHistograms2D[khdEdXPos]->Fill(track.GetP(), gTrack->dEdx()*1.e6);
      else    fTrackHistograms2D[khdEdXNeg]->Fill(track.GetP(), gTrack->dEdx()*1.e6);  
#else /* __TFG__VERSION__ */
      Double_t pL10 = (track.GetP() > 0) ? TMath::Log10(track.GetP()) : -2;
      Double_t dEdxL10 = (gTrack->dEdx() > 0) ? TMath::Log10(gTrack->dEdx()*1e6) : 0.0;
      Double_t dNdxL10 = (gTrack->probPidTraits().dNdxFit() > 0) ? TMath::Log10(gTrack->probPidTraits().dNdxFit()*1e6) : 0.5;
      fTrackHistograms2D[khdEdX]->Fill(pL10, dEdxL10);
      if(q>0) fTrackHistograms2D[khdEdXPos]->Fill(pL10, dEdxL10);
      else    fTrackHistograms2D[khdEdXNeg]->Fill(pL10, dEdxL10);
      fTrackHistograms2D[khdNdX]->Fill(pL10, dNdxL10);
      if(q>0) fTrackHistograms2D[13]->Fill(pL10, dNdxL10);
      else    fTrackHistograms2D[14]->Fill(pL10, dNdxL10);
#endif /* __TFG__VERSION__ */
    }
    const StMuBTofPidTraits &btofPid = gTrack->btofPidTraits();
    double timeTof = btofPid.timeOfFlight();
#ifndef __TFG__VERSION__
    double lengthTof = btofPid.pathLength();
//     if(lengthTof < 0.)
//     {
//       const StThreeVectorF & tofPoint  = btofPid.position();
//       const StThreeVectorF & dcaPoint  = gTrack->dca(bestPV);
//       StPhysicalHelixD innerHelix = gTrack->helix();
//       double dlDCA = fabs( innerHelix.pathLength( StThreeVector<double>(dcaPoint.x(), dcaPoint.y(), dcaPoint.z()) ) );
//       StPhysicalHelixD outerHelix = gTrack->outerHelix();
//       double dlTOF = fabs( outerHelix.pathLength( StThreeVector<double>(tofPoint.x(), tofPoint.y(), tofPoint.z()) ) );
//       
//       double l = gTrack->length();
//       lengthTof = l + dlDCA + dlTOF;
//     }
//     if(lengthTof < 0.)
//     {
//       const StThreeVectorF & tofPoint  = btofPid.position();
//       StPhysicalHelixD innerHelix = dcaG->helix();
//       StMuPrimaryVertex *pv = muDst->primaryVertex(bestPV);
//       lengthTof = fabs( innerHelix.pathLength( StThreeVector<double>(tofPoint.x(), tofPoint.y(), tofPoint.z()) ) ) + 
//                   fabs( innerHelix.pathLength( StThreeVector<double>(pv->position().x(), 
//                                                                      pv->position().y(), 
//                                                                      pv->position().z()) ) );
//     }
#endif /* ! __TFG__VERSION__ */
    double m2tof = -1.e6;
    bool isTofm2 = false;
#ifndef __TFG__VERSION__
    if(timeTof > 0. && lengthTof > 0.)
#else /* __TFG__VERSION__ */
    if(timeTof > 0)
#endif /* __TFG__VERSION__ */
    {
#ifndef __TFG__VERSION__
      m2tof = track.GetP()*track.GetP()*(1./((lengthTof/timeTof/29.9792458)*(lengthTof/timeTof/29.9792458))-1.);
      isTofm2 = true;
      
      if(fCollectTrackHistograms)
      {
        fTrackHistograms2D[khdEdXwithTof]->Fill(track.GetP(), gTrack->dEdx()*1.e6);
        fTrackHistograms2D[khTofPID]->Fill(track.GetP(), m2tof);
#else /* __TFG__VERSION__ */
      Double_t beta = btofPid.beta();
      Double_t beta2 = beta*beta;
      if(beta2 > 1e-6) {
	m2tof = track.GetP()*track.GetP()*(1./beta2 - 1.);
	isTofm2 = true;
#endif /* __TFG__VERSION__ */
      }
    }
#ifndef __TFG__VERSION__
    double dEdXPull[12] = { fabs(gTrack->nSigmaElectron()),                     //0 - e
                            fabs(gTrack->dEdxPull(0.1056583745, fdEdXMode, 1)), //1 - mu
                            fabs(gTrack->nSigmaPion()),                         //2 - pi
                            fabs(gTrack->nSigmaKaon()),                         //3 - K
                            fabs(gTrack->nSigmaProton()),                       //4 - p
                            fabs(gTrack->dEdxPull(1.876124, fdEdXMode, 1)),     //5 - d
                            fabs(gTrack->dEdxPull(2.809432, fdEdXMode, 1)),     //6 - t
                            fabs(gTrack->dEdxPull(2.809413, fdEdXMode, 2)),     //7 - He3
                            fabs(gTrack->dEdxPull(3.728400, fdEdXMode, 2)),     //8 - He4
                            fabs(gTrack->dEdxPull(1.197449, fdEdXMode, 1)),     //9 - Sigma
                            fabs(gTrack->dEdxPull(1.32171, fdEdXMode, 1)),      //10- Xi
                            fabs(gTrack->dEdxPull(1.67245, fdEdXMode, 1))       //11- Omega
    };    
    
    vector<int> totalPDG = GetPID(m2tof, track.GetP(), q, gTrack->dEdx()*1.e6, dEdXPull, isTofm2, false, index);
    
#else /* __TFG__VERSION__ */
    double m2Etof = -1.e6;
    bool isETofm2 = false;
#ifdef __ETAPN_TOF_PLOTS__
    Double_t eta  = gTrack->eta();
#endif /* __ETAPN_TOF_PLOTS__ */
    const StMuETofPidTraits &etofPid = gTrack->etofPidTraits();
    double timeETof = etofPid.timeOfFlight();
    if (timeETof > 0) {
      double lengthETof = etofPid.pathLength();
      if(lengthETof < 0.) {
	const StThreeVectorF & etofPoint  = etofPid.position();
	const StThreeVectorF & dcaPoint  = gTrack->dca(bestPV);
	StPhysicalHelixD innerHelix = gTrack->helix();
	double dlDCA = fabs( innerHelix.pathLength( StThreeVector<double>(dcaPoint.x(), dcaPoint.y(), dcaPoint.z()) ) );
	StPhysicalHelixD outerHelix = gTrack->outerHelix();
	double dlTOF = fabs( outerHelix.pathLength( StThreeVector<double>(etofPoint.x(), etofPoint.y(), etofPoint.z()) ) );
	double l = gTrack->length();
	lengthETof = l + dlDCA + dlTOF;
      }
      if(lengthETof > 0.) {
	m2Etof = track.GetP()*track.GetP()*(1./((lengthETof/timeETof/29.9792458)*(lengthETof/timeETof/29.9792458))-1.);
	isETofm2 = true;
      }
    }
    if(fCollectTrackHistograms && (isTofm2 || isETofm2) )
      {
	Double_t pL10 = (track.GetP() > 0) ? TMath::Log10(track.GetP()) : -2;
	Double_t dEdxL10 = (gTrack->dEdx() > 0) ? TMath::Log10(gTrack->dEdx()*1e6) : -1;
	Double_t dNdxL10 = (gTrack->probPidTraits().dNdxFit() > 0) ? TMath::Log10(gTrack->probPidTraits().dNdxFit()*1e6) : 0.5;
	
        fTrackHistograms2D[khdEdXwithTof]->Fill(pL10, dEdxL10);
        fTrackHistograms2D[khdNdX]->Fill(pL10, dNdxL10);
        if (isTofm2)  {
	  fTrackHistograms2D[khTofPID]->Fill(pL10, m2tof);
#ifdef __ETAPN_TOF_PLOTS__
	  if (eta > 0) fTrackHistograms2D[khTofPIDP]->Fill(pL10, m2tof);
	  else         fTrackHistograms2D[khTofPIDN]->Fill(pL10, m2tof);
#endif /* ! __ETAPN_TOF_PLOTS__ */
	}
        if (isETofm2) fTrackHistograms2D[17]->Fill(pL10, m2Etof);
      }
#endif /* __ETAPN_TOF_PLOTS__ */
    StTrackCombPiD PiD(gTrack);
    vector<int> totalPDG = PiD.GetPDG();
#endif /* __TFG__VERSION__ */
    int nPartSaved0 = nPartSaved;
    unsigned int nPrimaryTracks = primaryTrackList.size();
#ifdef __kfpAtFirstHit__
    AddTrackToParticleList(track, nHftHitsInTrack, index, totalPDG, primaryVertex, primaryTrackList, fNHftHits, fParticlesPdg, fParticles, nPartSaved, &trackAtLastHit, &fParticlesAtLastHit);
#else /* ! __kfpAtFirstHit__ */
#ifndef __TFG__VERSION__
    AddTrackToParticleList(track, nHftHitsInTrack, index, totalPDG, primaryVertex, primaryTrackList, fNHftHits, fParticlesPdg, fParticles, nPartSaved);
#else /* __TFG__VERSION__ */
    Int_t NDF = 2*gTrack->nHitsFit() - 5;
    Float_t Chi2 = gTrack->chi2()*NDF;
    AddTrackToParticleList(track, nHftHitsInTrack, index, totalPDG, primaryVertex, primaryTrackList, fNHftHits, fParticlesPdg, fParticles, nPartSaved, 0, 0, Chi2, NDF);         
#endif /* __TFG__VERSION__ */
#endif /* __kfpAtFirstHit__ */
    
    if(nPartSaved > nPartSaved0)
      mcIndices[index] = mcIndex;
    //fill PID histograms if they are created
    //Histograms are filled for secondary tracks only!!!
    if(fCollectPIDHistograms && (nPrimaryTracks == primaryTrackList.size())) 
    {
      vector<int> selectedPdg;
      for(int iPdg = nPartSaved0; iPdg<nPartSaved; iPdg++)
        selectedPdg.push_back(fParticlesPdg[iPdg]);
      FillPIDHistograms(gTrack, selectedPdg, isTofm2, m2tof);
    }
    
    nUsedTracks++;
  }

  fParticles.resize(nPartSaved);
#ifdef __kfpAtFirstHit__
  fParticlesAtLastHit.resize(nPartSaved);
#endif
  fParticlesPdg.resize(nPartSaved);
  fNHftHits.resize(nPartSaved);

  if(nUsedTracks==0) return 0;
  const int nPrimary = primaryTrackList.size();
  if(fCollectTrackHistograms)
  {
    fTrackHistograms[2]->Fill( double(nPrimary)/double(nUsedTracks) );
    Double_t nPL10 = (nPrimary > 0)                ? TMath::Log10(nPrimary)               : -1;
    Double_t nGL10 = (nUsedTracks - nPrimary  > 0) ? TMath::Log10(nUsedTracks - nPrimary) : -1;
    fTrackHistograms2D[khGlobalVsPrimaryTracks]->Fill( nGL10, nPL10);
  }
  
  if( fCleanLowPVTrackEvents && ( 10*primaryTrackList.size() < (nUsedTracks - primaryTrackList.size()) ) ) return 0;
  if( fCleanLowPVTrackEvents && sqrt(dx*dx + dy*dy) > 0.45 ) return 0;
  if (IsFixedTarget()) {
    if( fCleanLowPVTrackEvents && !(primaryVertex.Z() > 196. && primaryVertex.Z() < 204.) ) return 0;
    if( fCleanLowPVTrackEvents && !(primaryVertex.X() > -2.5 && primaryVertex.X() < 2.  ) ) return 0;
    if( fCleanLowPVTrackEvents && !(primaryVertex.Y() > -4.  && primaryVertex.Y() < 0.  ) ) return 0;
    
    //   if( fCleanLowPVTrackEvents && ( (nUsedTracks - nPrimary) > (50. + 0.75*nPrimary) ) ) return 0;
    if( fCleanLowPVTrackEvents && ( (nUsedTracks - nPrimary) > 150 ) ) return 0;
  } else {
    if( fCleanLowPVTrackEvents && primaryVertex.GetR() > 2.5 ) return 0;
  }

#ifdef __MagFieldCorrection__
#ifndef __TFG__VERSION__
  const Double_t field = muDst->event()->magneticField() * 0.998f;
#else /* __TFG__VERSION__ */
  const Double_t field = muDst->event()->magneticField() *  fgMagScaleFactor;
#endif /* __TFG__VERSION__ */
#else /* !  __MagFieldCorrection__ */
  const Double_t field = muDst->event()->magneticField();
#endif /*  __MagFieldCorrection__ */
  SetField(field);

  CleanPV();
#ifdef __kfpAtFirstHit__
  InitParticlesAtFirstAndLastHit();
#else
  InitParticles();
#endif

  //read PV
  AddPV(primaryVertex, primaryTrackList);
  if(fCollectTrackHistograms)
  {
    fTrackHistograms[1]->Fill(sqrt(dx*dx + dy*dy));
#ifndef __TFG__VERSION__
    fTrackHistograms2D[khPVErrorVsNTracks]->Fill( nPartSaved, sqrt(dx*dx + dy*dy) );
    fTrackHistograms2D[khPVErrorVsNPVTracks]->Fill( primaryTrackList.size(), sqrt(dx*dx + dy*dy) );
#else /* __TFG__VERSION__ */
    Double_t ngL10 = (nPartSaved > 0) ? TMath::Log10(nPartSaved) : -1;
    fTrackHistograms2D[khPVErrorVsNTracks]->Fill( ngL10, sqrt(dx*dx + dy*dy) );
    Double_t npL10 = (nPartSaved > 0) ? TMath::Log10(primaryTrackList.size()) : -1;
    fTrackHistograms2D[khPVErrorVsNPVTracks]->Fill( npL10, sqrt(dx*dx + dy*dy) );
#endif /* __TFG__VERSION__ */
  }  
  //reconstruct short-lived particles
  ReconstructParticles();
#ifdef __TFG__VERSION__
  const int nCandidates = GetParticles().size();
  for(int iParticle=0; iParticle<nCandidates; iParticle++) {
    const KFParticle particle = GetParticles()[iParticle];
    
    if(particle.GetPDG() == 3012 ||
       particle.GetPDG() == 3013 ||
       particle.GetPDG() == 3006 ||
       particle.GetPDG() == 3007 )
      RemoveParticle(iParticle);
    
    if(particle.GetPDG() == 3028) {
      KFParticle pi = GetParticles()[particle.DaughterIds()[0]];
      KFParticle p1 = GetParticles()[particle.DaughterIds()[1]];
      KFParticle p2 = GetParticles()[particle.DaughterIds()[2]];
      
      const int index = ftrackIdToI[p1.DaughterIds()[0]];
      StMuTrack *pTrack  = muDst->globalTracks(index);
      Int_t dcaGeometryIndex = pTrack->index2Cov();
      if (dcaGeometryIndex < 0) continue;
      StDcaGeometry *dcaG = StMuDst::instance()->covGlobTracks(dcaGeometryIndex);
      if (! dcaG) continue;
      Int_t q = 1; if (pTrack->charge() < 0) q = -1;
      KFPTrack track;
      if( !GetTrack(*dcaG, track, q, index) ) continue;
      
      std::vector<int> totalPDG;
      totalPDG.push_back(1000010020);
      totalPDG.push_back(1000010030);
      totalPDG.push_back(1000020030);
      totalPDG.push_back(1000020040);
       std::vector<KFParticle> fragments(4);
      std::vector<int> fragmentsPdg(4);
      std::vector<int> nHftHits(4);
      std::vector<int> primaryTrackList;
      int nPartSaved = 0;
      AddTrackToParticleList(track, 0, index, totalPDG, primaryVertex, primaryTrackList, nHftHits, fragmentsPdg, fragments, nPartSaved);    
      
      KFParticle ppi;
      ppi += pi;
      ppi += p2;
      
      KFParticle dppi = ppi;
      fragments[0].SetId(p1.Id());
      dppi += fragments[0];
      dppi.SetPDG(3012);
      dppi.SetId(GetParticles().size());
      AddParticle(dppi);
      
      KFParticle tppi = ppi;
      fragments[1].SetId(p1.Id());
      tppi += fragments[1];
      tppi.SetPDG(3013);
      tppi.SetId(GetParticles().size());
      AddParticle(tppi);

      KFParticle he3ppi = ppi;
      fragments[2].SetId(p1.Id());
      he3ppi += fragments[2];
      he3ppi.SetPDG(3006);
      he3ppi.SetId(GetParticles().size());
      AddParticle(he3ppi);

      KFParticle he4ppi = ppi;
      fragments[3].SetId(p1.Id());
      he4ppi += fragments[3];
      he4ppi.SetPDG(3007);
      he4ppi.SetId(GetParticles().size());
      AddParticle(he4ppi);      
    }
    
  }
  if (fPidQA) {
    PidQA(muDst);
  }
#endif /* __TFG__VERSION__ */
  return 1;
}

struct pvIndex {
  pvIndex(float d, int j):chi(d), i(j) {}
  float chi;
  int i;
};

static bool sortPVIndices(const pvIndex& a, const pvIndex& b) { return a.chi < b.chi; }

bool StKFParticleInterface::FitPV(KFVertex& pv, bool isFirstSeed, const KFPTrackVector& tracks,
                                  std::vector<int>& pvTrackIndices, std::vector<bool>& isUsed)
{
  std::vector<pvIndex> candidateIndices;
  candidateIndices.reserve(tracks.Size());

  pvTrackIndices.clear();
  pvTrackIndices.reserve(tracks.Size());

  isUsed.clear();
  isUsed.resize(tracks.Size(), false);

  KFParticleSIMD trackSIMD;
  KFParticleSIMD pvSIMD(pv);
  for(int iTrack=0; iTrack < tracks.Size(); iTrack+=float_vLen) {

    trackSIMD.Load(tracks, iTrack);
   
    const float_v deviation = trackSIMD.GetDeviationFromVertex(pvSIMD);
    
    for(int iV=0; iV<float_vLen; iV++){
      const int iTr = iTrack + iV;
      if(iTr >= tracks.Size()) break;
      
      if((deviation[iV]==deviation[iV]) && (deviation[iV] >= 0.f && deviation[iV] < 200.f))
        candidateIndices.push_back(pvIndex(deviation[iV], iTr));
    }
  }
  
  std::sort(candidateIndices.begin(), candidateIndices.end(), sortPVIndices);
  
  const int nCandidates = candidateIndices.size();
 
  if(nCandidates > 2) {

    vector<bool> vFlags(nCandidates, false);
    
    KFVertex primaryVertex;
    primaryVertex.SetConstructMethod(0);
    for(int iCandidate = 0; iCandidate < nCandidates; iCandidate++) {
      
      KFParticle particle;
      const int iTrack = candidateIndices[iCandidate].i;
      
      particle.Q() = tracks.Q()[iTrack];
      
      particle.X() = tracks.X()[iTrack];
      particle.Y() = tracks.Y()[iTrack];
      particle.Z() = tracks.Z()[iTrack];
      particle.Px() = tracks.Px()[iTrack];
      particle.Py() = tracks.Py()[iTrack];
      particle.Pz() = tracks.Pz()[iTrack];
      
      particle.Covariance( 0) = tracks.Covariance( 0)[iTrack];
      particle.Covariance( 1) = tracks.Covariance( 1)[iTrack];
      particle.Covariance( 2) = tracks.Covariance( 2)[iTrack];
      particle.Covariance( 3) = tracks.Covariance( 3)[iTrack];
      particle.Covariance( 4) = tracks.Covariance( 4)[iTrack];
      particle.Covariance( 5) = tracks.Covariance( 5)[iTrack];
      particle.Covariance( 6) = tracks.Covariance( 6)[iTrack];
      particle.Covariance( 7) = tracks.Covariance( 7)[iTrack];
      particle.Covariance( 8) = tracks.Covariance( 8)[iTrack];
      particle.Covariance( 9) = tracks.Covariance( 9)[iTrack];
      particle.Covariance(10) = tracks.Covariance(10)[iTrack];
      particle.Covariance(11) = tracks.Covariance(11)[iTrack];
      particle.Covariance(12) = tracks.Covariance(12)[iTrack];
      particle.Covariance(13) = tracks.Covariance(13)[iTrack];
      particle.Covariance(14) = tracks.Covariance(14)[iTrack];
      particle.Covariance(15) = tracks.Covariance(15)[iTrack];
      particle.Covariance(16) = tracks.Covariance(16)[iTrack];
      particle.Covariance(17) = tracks.Covariance(17)[iTrack];
      particle.Covariance(18) = tracks.Covariance(18)[iTrack];
      particle.Covariance(19) = tracks.Covariance(19)[iTrack];
      particle.Covariance(20) = tracks.Covariance(20)[iTrack];

      KFVertex tmpPV = primaryVertex;
      tmpPV += particle;
      const float dChi2 = tmpPV.Chi2() - primaryVertex.Chi2();
      if(dChi2 < 6.f) {
        primaryVertex = tmpPV;
        vFlags[iCandidate] = true;
      }
    }

    pv = primaryVertex;

    pvSIMD = KFParticleSIMD(pv);

    for(int iTrack=0; iTrack < tracks.Size(); iTrack+=float_vLen) {
      trackSIMD.Load(tracks, iTrack);
    
      const float_v deviation = trackSIMD.GetDeviationFromVertex(pvSIMD);
      
      for(int iV=0; iV<float_vLen; iV++){
        const int iTr = iTrack + iV;
        if(iTr >= tracks.Size()) break;
      
        if((deviation[iV]==deviation[iV]) && (deviation[iV] >= 0.f && deviation[iV] < 50.f)) {
          pvTrackIndices.push_back(iTr);
          isUsed[iTr] = true;
        }
      }
    }
    
    if( (isFirstSeed && primaryVertex.NDF() >= 1) || (!isFirstSeed && primaryVertex.NDF() > 7))
    {
      return true;
    }
  }
  
  return false;
}

inline void InvertCholetsky2(float a[3])
{
  const float d0 = 1.f/a[0];
  const float u01 = a[1]*d0;  
  const float d1 = 1.f/(a[2] - u01*a[1]);

  a[2] = d1;
  a[1] = -d1*u01;
  a[0] = d0 - a[1]*u01;
}

struct Point3D {
  Point3D() = default;
  Point3D(const KFParticle& p) {
    m_r[0] = p.X(); m_r[1] = p.Y(); m_r[2] = p.Z();
    m_C[0] = p.GetCovariance(0);
    m_C[1] = p.GetCovariance(1); m_C[2] = p.GetCovariance(2);
    m_C[3] = p.GetCovariance(3); m_C[4] = p.GetCovariance(4); m_C[5] = p.GetCovariance(5);
  }
  
  inline float GetDeviation(const Point3D& p) const {
    float s[6]{ m_C[0] + p.m_C[0], 
                m_C[1] + p.m_C[1], m_C[2] + p.m_C[2],
                m_C[3] + p.m_C[3], m_C[4] + p.m_C[4], m_C[5] + p.m_C[5] };
    KFParticle::InvertCholetsky3(s);
    const float dr[3]{ p.m_r[0] - m_r[0], p.m_r[1] - m_r[1], p.m_r[2] - m_r[2] };
    return  (s[0]*dr[0] + s[1]*dr[1] + s[3]*dr[2])*dr[0]
           +(s[1]*dr[0] + s[2]*dr[1] + s[4]*dr[2])*dr[1]
           +(s[3]*dr[0] + s[4]*dr[1] + s[5]*dr[2])*dr[2];
  }

  inline void Filter(const Point3D& p) {
    const float r[3]{m_r[0], m_r[1], m_r[2]};
    const float c[6]{m_C[0], m_C[1], m_C[2], m_C[3], m_C[4], m_C[5]};
    
    float s[6]{ c[0] + p.m_C[0],
                c[1] + p.m_C[1], c[2] + p.m_C[2],
                c[3] + p.m_C[3], c[4] + p.m_C[4], c[5] + p.m_C[5] };
    KFParticle::InvertCholetsky3(s);
    
    const float k[3][3]{ {c[0]*s[0] + c[1]*s[1] + c[3]*s[3], c[0]*s[1] + c[1]*s[2] + c[3]*s[4], c[0]*s[3] + c[1]*s[4] + c[3]*s[5]},
                         {c[1]*s[0] + c[2]*s[1] + c[4]*s[3], c[1]*s[1] + c[2]*s[2] + c[4]*s[4], c[1]*s[3] + c[2]*s[4] + c[4]*s[5]},
                         {c[3]*s[0] + c[4]*s[1] + c[5]*s[3], c[3]*s[1] + c[4]*s[2] + c[5]*s[4], c[3]*s[3] + c[4]*s[4] + c[5]*s[5]} };
    const float dr[3]{ p.m_r[0] - r[0], p.m_r[1] - r[1], p.m_r[2] - r[2] };

    const float dChi2 = (s[0]*dr[0] + s[1]*dr[1] + s[3]*dr[2])*dr[0]
                       +(s[1]*dr[0] + s[2]*dr[1] + s[4]*dr[2])*dr[1]
                       +(s[3]*dr[0] + s[4]*dr[1] + s[5]*dr[2])*dr[2];

    if((m_chi2 + dChi2) / float(m_ndf + 3) < 10.f) {
      m_r[0] = r[0] + k[0][0]*dr[0] + k[0][1]*dr[1] + k[0][2]*dr[2];
      m_r[1] = r[1] + k[1][0]*dr[0] + k[1][1]*dr[1] + k[1][2]*dr[2];
      m_r[2] = r[2] + k[2][0]*dr[0] + k[2][1]*dr[1] + k[2][2]*dr[2];
        
      m_C[0] = c[0] - k[0][0]*c[0] - k[0][1]*c[1] - k[0][2]*c[3];
      m_C[1] = c[1] - k[1][0]*c[0] - k[1][1]*c[1] - k[1][2]*c[3];
      m_C[2] = c[2] - k[1][0]*c[1] - k[1][1]*c[2] - k[1][2]*c[4];
      m_C[3] = c[3] - k[2][0]*c[0] - k[2][1]*c[1] - k[2][2]*c[3];
      m_C[4] = c[4] - k[2][0]*c[1] - k[2][1]*c[2] - k[2][2]*c[4];
      m_C[5] = c[5] - k[2][0]*c[3] - k[2][1]*c[4] - k[2][2]*c[5];
        
      m_chi2 += dChi2;
      m_ndf += 3;
    }
  }

  static bool compare(const Point3D& a, const Point3D& b) {
    return (a.m_ndf > b.m_ndf) || (a.m_ndf == b.m_ndf && a.m_chi2 < b.m_chi2);
  }
  
  KFParticle convertToKFParticle(const float) const {
    KFParticle p;
    p.X() = m_r[0];
    p.Y() = m_r[1];
    p.Z() = m_r[2];
    p.Covariance(0) = m_C[0];
    p.Covariance(1) = m_C[1];
    p.Covariance(2) = m_C[2];
    p.Covariance(3) = m_C[3];
    p.Covariance(4) = m_C[4];
    p.Covariance(5) = m_C[5];
    return p;
  }
  
  float m_r[3]{0.f};
  float m_C[6]{0.f};
  float m_chi2{0.f};
  int   m_ndf{-2};
};

struct Point2D {
  inline float GetDeviation(const Point2D& p) const {
    float s[3]{ m_C[0] + p.m_C[0], m_C[1] + p.m_C[1], m_C[2] + p.m_C[2] };
    InvertCholetsky2(s);
    const float dr[2]{ p.m_r[0] - m_r[0], p.m_r[1] - m_r[1] };
    return  s[0]*dr[0]*dr[0] + s[1]*dr[0]*dr[1]*2.f + s[2]*dr[1]*dr[1];
  }

  inline void Filter(const Point2D& p) {
    const float r[2]{m_r[0], m_r[1]};
    const float c[3]{m_C[0], m_C[1], m_C[2]};
    
    float s[3]{ c[0] + p.m_C[0], c[1] + p.m_C[1], c[2] + p.m_C[2] };
    InvertCholetsky2(s);
    
    const float k[2][2]{ {c[0] * s[0] + c[1] * s[1], c[0] * s[1] + c[1] * s[2]},
                         {c[1] * s[0] + c[2] * s[1], c[1] * s[1] + c[2] * s[2]} };
    const float dr[2]{ p.m_r[0] - r[0], p.m_r[1] - r[1] };

    const float dChi2 = s[0]*dr[0]*dr[0] + s[1]*dr[0]*dr[1]*2.f + s[2]*dr[1]*dr[1];

    if((m_chi2 + dChi2) / float(m_ndf + 2) < 10.f) {
      m_r[0] = r[0] + k[0][0] * dr[0] + k[0][1] * dr[1];
      m_r[1] = r[1] + k[1][0] * dr[0] + k[1][1] * dr[1];
        
      m_C[0] = c[0] - k[0][0] * c[0] - k[0][1] * c[1];
      m_C[1] = c[1] - k[1][0] * c[0] - k[1][1] * c[1];
      m_C[2] = c[2] - k[1][0] * c[1] - k[1][1] * c[2];
        
      m_chi2 += dChi2;
      m_ndf += 2;
    }
  }

  static bool compare(const Point2D& a, const Point2D& b) {
    return (a.m_ndf > b.m_ndf) || (a.m_ndf == b.m_ndf && a.m_chi2 < b.m_chi2);
  }
  
  float m_r[2]{0.f};
  float m_C[3]{0.f};
  float m_chi2{0.f};
  int   m_ndf{-2};
};

struct PointXY: public Point2D {
  PointXY() = default;
  PointXY(const KFParticle& p) {
    m_r[0] = p.X(); m_r[1] = p.Y();
    m_C[0] = p.GetCovariance(0);
    m_C[1] = p.GetCovariance(1); m_C[2] = p.GetCovariance(2);
  }
  
  KFParticle convertToKFParticle(const float z0) const {
    KFParticle p;
    p.X() = m_r[0];
    p.Y() = m_r[1];
    p.Z() = z0;
    p.Covariance(0) = m_C[0];
    p.Covariance(1) = m_C[1];
    p.Covariance(2) = m_C[2];
    p.Covariance(5) = 9.f;
    return p;
  }
};

struct PointPhiZ: public Point2D {
  PointPhiZ() = default;
  PointPhiZ(const KFParticle& p) {
    const float x = p.X();
    const float y = p.Y();
    const float x2 = x*x;
    const float y2 = y*y;
    const float r2 = x2 + y2;
    const float r4 = r2 * r2;

    const float phi = atan2(y, x);
    
    const float cPhiPhi = (y2 * p.GetCovariance(0) - 2.f*x*y * p.GetCovariance(1) + x2 * p.GetCovariance(2)) / r4;
    const float cPhiZ = (x * p.GetCovariance(4) - y * p.GetCovariance(3)) / r2;
        
    m_r[0] = phi; m_r[1] = p.Z();
    m_C[0] = cPhiPhi;
    m_C[1] = cPhiZ;   m_C[2] = p.GetCovariance(5);
  }
  
  KFParticle convertToKFParticle(const float r) const {
    const float x = r * cos(m_r[0]);
    const float y = r * sin(m_r[0]);
    
    KFParticle p;
    p.X() = x;
    p.Y() = y;
    p.Z() = m_r[1];
    p.Covariance(0) =  y*y * m_C[0];
    p.Covariance(1) = -x*y * m_C[0];
    p.Covariance(2) =  x*x * m_C[0];
    p.Covariance(3) = -y * m_C[1];
    p.Covariance(4) =  x * m_C[1];
    p.Covariance(5) = m_C[2];
    
    return p;
  }
};

struct Position{
  Position(const int i, const float value, const float error2):
    m_i(i), m_value(value), m_error2(error2) {}
  int m_i;
  float m_value;
  float m_error2;
  static bool compare(const Position& a, const Position& b) { return a.m_value > b.m_value; }
};

template<class T>
void getPoints(
  const KFPTrackVector& tracks, const KFVertex& beamPosition, const float R, const float dR,
  std::vector<KFParticle>& points, std::vector<Position>& zHisto);

template<> void getPoints<Point3D>(
  const KFPTrackVector& tracks, const KFVertex& beamPosition, const float R, const float dR,
  std::vector<KFParticle>& points, std::vector<Position>& zHisto)
{
  KFParticleSIMD trackSIMD;
  const float_v beamXY[2]{beamPosition.X(), beamPosition.Y()};

  for(int iTrack=0; iTrack < tracks.Size(); iTrack+=float_vLen) {
    trackSIMD.Load(tracks, iTrack);
    
    const float_v ds = trackSIMD.GetDStoPointXY(beamXY);
    float_v dsdr[6] = {0.f,0.f,0.f,0.f,0.f,0.f};
    trackSIMD.TransportToDS(ds, dsdr);
    
    for(int iV=0; iV<4; iV++) {
      if(iTrack + iV >= tracks.Size()) continue;
      KFParticle tmp;
      trackSIMD.GetKFParticle(tmp, iV);
      tmp.SetId(iTrack + iV);
     
      const float dx = tmp.X() - beamPosition.X();
      const float dy = tmp.Y() - beamPosition.Y();
      const float xError2 = tmp.GetCovariance(0) + 0.01f;
      const float yError2 = tmp.GetCovariance(2) + 0.01f;
      if( (dx*dx > 10.f*xError2)  || (dy*dy > 10.f*yError2) ) continue;
      if( tmp.GetCovariance(0) > 25.f || tmp.GetCovariance(2) > 25.f || tmp.GetCovariance(5) > 25.f)
        continue;
      
      zHisto.push_back(Position(zHisto.size(), tmp.Z(), tmp.GetCovariance(2,2)));
      points.push_back(tmp);   
    }
  }
}

template<> void getPoints<PointPhiZ>(
  const KFPTrackVector& tracks, const KFVertex& beamPosition, const float R, const float dR,
  std::vector<KFParticle>& points, std::vector<Position>& zHisto)
{
  KFParticleSIMD trackSIMD;
  for(int iTrack=0; iTrack < tracks.Size(); iTrack+=float_vLen) {
    trackSIMD.Load(tracks, iTrack);
    KFParticleSIMD p1 = trackSIMD;
    KFParticleSIMD p2 = trackSIMD;
    float_v ds[2]{0.f, 0.f};
    p1.GetDStoCylinder(R, ds);
    float_v dsdr[6] = {0.f,0.f,0.f,0.f,0.f,0.f};
    p1.TransportToDS(ds[0], dsdr);
    p2.TransportToDS(ds[1], dsdr);
    
    const float_m saveFirstPoint = (p1.GetR() > R-dR) && (p1.GetR() < R+dR) && (p1.Z() > -200.f);
    for(int iV=0; iV<4; iV++) {
      if(!saveFirstPoint[iV]) continue;
      if(iTrack + iV >= tracks.Size()) continue;
      KFParticle tmp;
      p1.GetKFParticle(tmp, iV);
      if( tmp.GetCovariance(0) > 25.f || tmp.GetCovariance(2) > 25.f || tmp.GetCovariance(5) > 25.f)
        continue;
      tmp.SetId(iTrack + iV);
      zHisto.push_back(Position(zHisto.size(), tmp.Z(), tmp.GetCovariance(2,2)));
      points.push_back(tmp);
    }
    const float_m saveSecondPoint = (p2.GetR() > R-dR) && (p2.GetR() < R+dR) && (p2.Z() > -200.f) &&
                                    (abs(p1.Z() - p2.Z()) > 1.e-4f);
    for(int iV=0; iV<4; iV++) {
      if(!saveSecondPoint[iV]) continue;
      if(iTrack + iV >= tracks.Size()) continue;
      KFParticle tmp;
      p2.GetKFParticle(tmp, iV);
      if( tmp.GetCovariance(0) > 25.f || tmp.GetCovariance(2) > 25.f || tmp.GetCovariance(5) > 25.f)
        continue;
      tmp.SetId(iTrack + iV);
      zHisto.push_back(Position(zHisto.size(), tmp.Z(), tmp.GetCovariance(2,2)));
      points.push_back(tmp);
    }
  }
}

template<> void getPoints<PointXY>(
  const KFPTrackVector& tracks, const KFVertex&, const float Z, const float dZ,
  std::vector<KFParticle>& points, std::vector<Position>& zHisto)
{
  KFParticleSIMD trackSIMD;

  for(int iTrack=0; iTrack < tracks.Size(); iTrack+=float_vLen) {
    trackSIMD.Load(tracks, iTrack);
    
    const float_v ds = trackSIMD.GetDStoPointZBz(Z);
    float_v dsdr[6] = {0.f,0.f,0.f,0.f,0.f,0.f};
    trackSIMD.TransportToDS(ds, dsdr);
    
    for(int iV=0; iV<4; iV++) {
      if(iTrack + iV >= tracks.Size()) continue;
      KFParticle tmp;
      trackSIMD.GetKFParticle(tmp, iV);
      tmp.SetId(iTrack + iV);
     
      const float dz = tmp.Z() - Z;
      if( fabs(dz) > dZ ) continue;
      if( tmp.GetR() > 30.f ) continue;
      if( tmp.GetR() < 3.5f ) continue;
      if( tmp.GetCovariance(0) > 25.f || tmp.GetCovariance(2) > 25.f || tmp.GetCovariance(5) > 25.f)
        continue;
      float rrr, drrr;
      tmp.GetR(rrr, drrr);
      zHisto.push_back(Position(zHisto.size(), rrr, drrr*drrr));
      points.push_back(tmp);   
    }
  }
}


  
template <class T>
inline void cleanCluster(std::vector<int>& cluster, const std::vector<KFParticle>& points)
{
  struct Clean {
    Clean(): m_i(-1), m_id(-1) {}
    Clean(const int i, const int id): m_i(i), m_id(id) {}
    static bool compare(const Clean& a, const Clean& b) { 
      return (a.m_id > b.m_id) || (a.m_id == b.m_id && a.m_i > b.m_i);
    }
    int m_i;
    int m_id;
  };

  std::vector<Clean> clean(cluster.size());
  for(UInt_t i=0; i<cluster.size(); i++) {
    clean[i] = Clean(cluster[i], points[cluster[i]].Id());
  }
  std::sort(clean.begin(), clean.end(), Clean::compare);

  cluster.clear();
  cluster.push_back(clean[0].m_i);
  for(UInt_t i=1; i<clean.size(); i++) {
    if(clean[i].m_id != clean[i-1].m_id) {
      cluster.push_back(clean[i].m_i);
    }
  }
}

template<>
inline void cleanCluster<Point3D>(std::vector<int>& cluster, const std::vector<KFParticle>& points) {}

template<>
inline void cleanCluster<PointXY>(std::vector<int>& cluster, const std::vector<KFParticle>& points) {}

template<class T>
void StKFParticleInterface::FindPileup(const KFPTrackVector& tracks, const KFVertex& beamPosition,
  std::vector<KFVertex>& vertices, std::vector<std::vector<int>>& vertexTracks, const float X, const float dX)
{
  vertices.clear();
  vertexTracks.clear();

  std::vector<KFParticle> points;
  std::vector<Position> zHisto;
  getPoints<T>(tracks, beamPosition, X, dX, points, zHisto);
  std::sort(zHisto.begin(), zHisto.end(), Position::compare);

  // find Z-clusters around each track
  std::vector<std::vector<int>> neighbours(zHisto.size());
  for(UInt_t iZ=0; iZ<zHisto.size(); iZ++) {
    const Position& currentPoint = zHisto[iZ];
    if(currentPoint.m_error2 > 25.f) continue;
    for(UInt_t iZNext = 0; iZNext<zHisto.size(); iZNext++) {
      if(iZNext == iZ) continue;
      const Position& nextPoint = zHisto[iZNext];
      if(nextPoint.m_error2 > 25.f) continue;
      const float dz = currentPoint.m_value - nextPoint.m_value;
      const float zError2 = currentPoint.m_error2 + nextPoint.m_error2;
      if(dz * dz < zError2 * 9 && fabs(dz) < 10.f) {
        neighbours[iZ].push_back(nextPoint.m_i);
      }
    }
    if(neighbours[iZ].size() > 0) {
      neighbours[iZ].push_back(currentPoint.m_i);
      std::sort(neighbours[iZ].begin(), neighbours[iZ].end());
    }
  }
  
  // merge clusters
  for(int i=0; i<2; i++)
  for(UInt_t iZ=0; iZ<neighbours.size(); iZ++) {
    auto& current = neighbours[iZ];
    for(UInt_t iZNext=iZ+1; iZNext<neighbours.size(); iZNext++) {
      auto& next = neighbours[iZNext];
      if(next.size() < 2) continue;
      
      std::vector<int> merged;
      std::set_union(current.begin(), current.end(),
                      next.begin(), next.end(),
                      std::back_inserter(merged));
      
      const int intersection = current.size() + next.size() - merged.size();
      
      if( 0.5f * float(min(current.size(), next.size())) < float(intersection) ) {
        current = merged;
        next.clear();
      }
    }
  }
  
  std::vector<bool> isUsed(tracks.Size(), false);
  std::vector<KFVertex> candidateVertices;
  std::vector<std::vector<int>> candidateVertexTracks;

  for(UInt_t iZ=0; iZ<neighbours.size(); iZ++) {
    if(neighbours[iZ].size() == 0) continue;
    std::vector<int> zCluster = neighbours[iZ];
    if(zCluster.size() > 2) {
      std::vector<T> projections(zCluster.size());
      for(UInt_t iPoint=0; iPoint<zCluster.size(); iPoint++) {
        const KFParticle& point = points[zCluster[iPoint]];
        projections[iPoint] = T(point);
      }
    
      std::vector<T> seeds;
      seeds.reserve(zCluster.size());
      for(UInt_t iFirstPoint=0; iFirstPoint<zCluster.size(); iFirstPoint++ ) {
        T phiZSeed = projections[iFirstPoint];
        for(int iIteration=0; iIteration<3; iIteration++) {
          T phiZVertex = projections[iFirstPoint];
          phiZVertex.m_chi2 = 0.f;
          phiZVertex.m_ndf = 0;

          for(UInt_t iPoint=0; iPoint<zCluster.size(); iPoint++) {
            if( iPoint == iFirstPoint ) continue;
            if( phiZSeed.GetDeviation(projections[iPoint]) > 18.6f ) continue;
            
            phiZVertex.Filter(projections[iPoint]);
          }
          phiZSeed = phiZVertex;
        }
        
        if( (phiZSeed.m_ndf >= 4) && (phiZSeed.m_chi2/float(phiZSeed.m_ndf) < 10.f) ) {
          seeds.push_back(phiZSeed);
        }
      }
      
      std::sort(seeds.begin(), seeds.end(), T::compare);
      
      cleanCluster<T>(zCluster, points);

      for(UInt_t iSeed=0; iSeed<seeds.size(); iSeed++) {
        KFParticle seed = seeds[iSeed].convertToKFParticle(X);
        KFParticle vertex;
        int nTracksInVertex = 0;
        std::vector<int> currentVertexTracks;
        
        for(UInt_t iPoint=0; iPoint < zCluster.size(); iPoint++) {
          const KFParticle& point = points[zCluster[iPoint]];
          if(isUsed[point.Id()]) continue;
          if(point.GetDeviationFromVertex(seed) > 18.6f) continue;

          KFParticle vertexTmp = vertex;
          vertexTmp += point;
          if(! (vertexTmp.X() == vertexTmp.X()) ) continue;
          
          vertex = vertexTmp;
          currentVertexTracks.push_back(point.Id());
          nTracksInVertex++;
        }
        
        if(nTracksInVertex > 4 && vertex.Chi2() / vertex.NDF() < 5.f) {
          candidateVertices.push_back(vertex);
          candidateVertexTracks.push_back(currentVertexTracks);
          for(UInt_t iUsed=0; iUsed<currentVertexTracks.size(); iUsed++) {
            isUsed[currentVertexTracks[iUsed]] = true;
          }
        }
      }
    }
  }  

  struct PVCandidate {
    PVCandidate(KFVertex& v, std::vector<int>& t): m_vertex(&v), m_tracks(&t) {}
    
    static bool compare(const PVCandidate& a, const PVCandidate& b) {
      return a.m_tracks->size() > b.m_tracks->size();
    }
    
    KFVertex* m_vertex;
    std::vector<int>* m_tracks;
  };

  std::vector<PVCandidate> candidates;
  for(UInt_t iCandidate=0; iCandidate<candidateVertices.size(); iCandidate++) {
    candidates.push_back(PVCandidate(candidateVertices[iCandidate], candidateVertexTracks[iCandidate]));
  }
  
  std::sort(candidates.begin(), candidates.end(), PVCandidate::compare);
  
  for(UInt_t iCandidate=0; iCandidate<candidates.size(); iCandidate++) {

    KFVertex& vertex = *(candidates[iCandidate].m_vertex);
    std::vector<int> vertexTrackIds = *(candidates[iCandidate].m_tracks);
    
    KFParticleSIMD trackSIMD;
    KFParticleSIMD pvSIMD(vertex);
    for(int iTrack=0; iTrack < tracks.Size(); iTrack+=float_vLen) {
      trackSIMD.Load(tracks, iTrack);
      const float_v deviation = trackSIMD.GetDeviationFromVertex(pvSIMD);
      for(int iV=0; iV<float_vLen; iV++){
        const int iTr = iTrack + iV;
        if(isUsed[iTr]) continue;
        if(iTr >= tracks.Size()) break;
      
        if((deviation[iV]==deviation[iV]) && (deviation[iV] >= 0.f && deviation[iV] < 18.6f)) {
          vertexTrackIds.push_back(iTr);
          isUsed[iTr] = true;
        }
      }
    }
    
    vertices.push_back(vertex);
    vertexTracks.push_back(vertexTrackIds);
  }
}

void StKFParticleInterface::FillPVHistos(const KFVertex& vertex, const std::vector<int>& tracks, const bool isMainVertex) {
  if(fCollectPVHistograms) {
    fPVHistograms[0]->Fill(vertex.X());
    fPVHistograms[1]->Fill(vertex.Y());
    fPVHistograms[2]->Fill(vertex.GetR());
    fPVHistograms[3]->Fill(vertex.Z());
    fPVHistograms[4]->Fill(tracks.size());
    
    if(isMainVertex) {
      fPVHistograms[5]->Fill(tracks.size());
    } else {
      fPVHistograms[6]->Fill(tracks.size());
    }
    
    fPVHistograms2D[0]->Fill(vertex.X(), vertex.Y());
    fPVHistograms2D[1]->Fill(vertex.Z(), vertex.GetR() * vertex.Y()/fabs(vertex.Y()));    
  }
}

void StKFParticleInterface::CleanTracks(KFPTrackVector& tracks, std::vector<bool>& isUsed, const int nUsed) {
  KFPTrackVector tracksLeft;
  tracksLeft.Resize(tracks.Size() - nUsed);
  
  int iLeft = 0;
  for(int iTrack=0; iTrack<tracks.Size(); iTrack++) {
    if(isUsed[iTrack]) continue;
    
    for(int iP=0; iP<6; iP++)
      tracksLeft.SetParameter(tracks.Parameter(iP)[iTrack], iP, iLeft);
    for(int iC=0; iC<21; iC++)
      tracksLeft.SetCovariance(tracks.Covariance(iC)[iTrack], iC, iLeft);
    tracksLeft.SetId(tracks.Id()[iTrack], iLeft);
    tracksLeft.SetQ(tracks.Q()[iTrack], iLeft);
    iLeft++;
  }
  tracks = tracksLeft;
}

void StKFParticleInterface::CleanPileupTracks(KFPTrackVector& tracks,
  const std::vector<KFVertex>& vertices, std::vector<std::vector<int>>& verticesTracks,
  int& nPV, int& nPileup, std::vector<bool>& isPileup, std::vector<KFVertex>& pileupPv)
{
  std::vector<bool> isUsed(tracks.Size(), false);
  int nUsed = 0;

  for(UInt_t iVertex=0; iVertex<vertices.size(); iVertex++) {
    const KFVertex& vertex = vertices[iVertex];
    const std::vector<int>& vertexTracks = verticesTracks[iVertex];
    
    for(UInt_t iTrack=0; iTrack<vertexTracks.size(); iTrack++) {
      isUsed[vertexTracks[iTrack]] = true;
    }
    nUsed += vertexTracks.size();

    if( (vertex.X() > -2.5f && vertex.X() < 2.f) && (vertex.Y() > -3.f  && vertex.Y() < 0.f) ) {
      pileupPv.push_back(vertex);
    }
    
    for(UInt_t iIndex=0; iIndex<vertexTracks.size(); iIndex++) {
      const int index = tracks.Id()[vertexTracks[iIndex]];
      isPileup[index] = true;
    }
    
    FillPVHistos(vertex, vertexTracks);
    nPileup += vertexTracks.size();
    nPV++;
  }
  CleanTracks(tracks, isUsed, nUsed);
}

bool StKFParticleInterface::FindFixedTargetPV(StPicoDst* picoDst, KFVertex& pv, std::vector<KFVertex>& pileupPv, std::vector<bool>& isPileup)
{
  KFPTrackVector tracks;
  tracks.Resize(picoDst->numberOfTracks());
  
  pileupPv.clear();
  
  int NTracks = 0;
  int maxIndex = 0;
  
  for(unsigned int iTrack=0; iTrack<picoDst->numberOfTracks(); iTrack++) {
    StPicoTrack *gTrack = picoDst->track(iTrack);
    if (! gTrack)            continue;
    if (! gTrack->charge())  continue;
   
    StPicoTrackCovMatrix *cov = picoDst->trackCovMatrix(iTrack);
    const StDcaGeometry dcaG = cov->dcaGeometry();
    const int q = (gTrack->charge() < 0) ? -1 : 1;
    const int index = gTrack->id();
    maxIndex = (index > maxIndex) ? index : maxIndex;
    KFPTrack track;
    if( !GetTrack(dcaG, track, q, index) ) continue;
    
    for(int iP=0; iP<6; iP++)
      tracks.SetParameter(track.GetParameter(iP), iP, NTracks);
    for(int iC=0; iC<21; iC++)
      tracks.SetCovariance(track.GetCovariance(iC), iC, NTracks);
    tracks.SetId(index, NTracks);
    tracks.SetQ(q, NTracks);    
    
    NTracks++;

    if(fCollectPVHistograms) {
      fPVHistograms2D[2]->Fill(track.GetZ(), sqrt(track.GetX()*track.GetX() + track.GetY()*track.GetY()));
    }
  }
  
  tracks.Resize(NTracks);
  isPileup.resize(maxIndex+1, false);

  
  int nPV = 0;
  int nPrimary = 0;
  int nPileup = 0;
  
  // 1. Find the main vertex

  KFVertex primaryVertex = fBeamSpot;
  std::vector<int> pvTrackIndices;
  std::vector<bool> isUsed;
  const bool isPVFound = FitPV(primaryVertex, true, tracks, pvTrackIndices, isUsed);
  if(isPVFound) {
    pv = primaryVertex;
    FillPVHistos(primaryVertex, pvTrackIndices, true);
    nPrimary += pvTrackIndices.size();
    nPV++;    
  }
  CleanTracks(tracks, isUsed, pvTrackIndices.size());
  
  // 2. Find pileup vertices

  std::vector<KFVertex> pileupVertices;
  std::vector<std::vector<int>> pileupVertexTracks;
  FindPileup<Point3D>(tracks, fBeamSpot, pileupVertices, pileupVertexTracks);
  CleanPileupTracks(tracks, pileupVertices, pileupVertexTracks, nPV, nPileup, isPileup, pileupPv);

  // 3. Find pipe vertices
// KFPTrackVector tracks0 = tracks;
  std::vector<KFVertex> pipeVertices;
  std::vector<std::vector<int>> pipeVertexTracks;
  FindPileup<PointPhiZ>(tracks, fBeamSpot, pipeVertices, pipeVertexTracks);
  CleanPileupTracks(tracks, pipeVertices, pipeVertexTracks, nPV, nPileup, isPileup, pileupPv);
  
  // 4. Find flanec vertices

  std::vector<KFVertex> flanecVertices1;
  std::vector<std::vector<int>> flanecVertexTracks1;
  FindPileup<PointXY>(tracks, fBeamSpot, flanecVertices1, flanecVertexTracks1, 55.5f, 2.f);
  CleanPileupTracks(tracks, flanecVertices1, flanecVertexTracks1, nPV, nPileup, isPileup, pileupPv);

  std::vector<KFVertex> flanecVertices2;
  std::vector<std::vector<int>> flanecVertexTracks2;
  FindPileup<PointXY>(tracks, fBeamSpot, flanecVertices2, flanecVertexTracks2, -55.5f, 2.f);
  CleanPileupTracks(tracks, flanecVertices2, flanecVertexTracks2, nPV, nPileup, isPileup, pileupPv);

  if(fCollectPVHistograms) {
    fPVHistograms[ 7]->Fill(nPV);
    fPVHistograms[ 8]->Fill(float(nPrimary)/float(NTracks));
    fPVHistograms[ 9]->Fill(float(nPileup)/float(NTracks));
    fPVHistograms[10]->Fill(float(NTracks - nPrimary - nPileup)/float(NTracks));
    
    for(int iTrack=0; iTrack<tracks.Size(); iTrack++) 
      fPVHistograms2D[3]->Fill(tracks.Z()[iTrack], 
        sqrt(tracks.X()[iTrack]*tracks.X()[iTrack] + tracks.Y()[iTrack]*tracks.Y()[iTrack]));
  }
  
  return isPVFound;
}

//________________________________________________________________________________
vector<const KFParticle *> StKFParticleInterface::Vec4Cfits() {
  vector<const KFParticle *> Vec4Cfit;
  for(int iSet=0; iSet<KFParticleFinder::GetNPrimarySets(); iSet++)    {
    for(int iPV=0; iPV<GetTopoReconstructor()->NPrimaryVertices(); iPV++)      {
      if (_debug) cout << "Set = " << iSet << "\tPV = " << iPV << "\tGetTopoReconstructor()->NPrimaryVertices() = " << GetTopoReconstructor()->NPrimaryVertices() << endl;
#if 0
      const std::vector<KFParticle>& PrimaryCandidates = GetTopoReconstructor()->GetKFParticleFinder()->GetPrimaryCandidates()[iSet][iPV];
      if (_debug) cout << "PrimaryCandidates.size() = " << PrimaryCandidates.size() << endl;
      for(unsigned int iP=0; iP<PrimaryCandidates.size(); iP++)        {
	KFParticle particle =  PrimaryCandidates[iP]; PrPP(particle);
// 	int iParticle = fParteff.GetParticleIndex(particle.GetPDG());
// 	if(iParticle < 0) continue;
	
	const int id = particle.Id();
	//	FillParticleParameters(particle,iParticle, id, iPV, hPartParamPrimaryMass, hPartParam2DPrimaryMass, 0, hFitQAMassConstraint);
          
	particle = GetTopoReconstructor()->GetParticles()[id]; PrPP(particle);
	//	FillParticleParameters(particle,iParticle, id, iPV, hPartParamPrimary, hPartParam2DPrimary, 0, hFitQANoConstraint);
      }
      const std::vector<KFParticle>& PrimaryCandidatesTopo = GetTopoReconstructor()->GetKFParticleFinder()->GetPrimaryTopoCandidates()[iSet][iPV];
      if (_debug) cout << "PrimaryCandidatesTopo.size() = " << PrimaryCandidatesTopo.size() << endl;
      for(unsigned int iP=0; iP<PrimaryCandidatesTopo.size(); iP++)        {
	KFParticle particle =  PrimaryCandidatesTopo[iP]; PrPP(particle);
// 	int iParticle = fParteff.GetParticleIndex(particle.GetPDG());
// 	if(iParticle < 0) continue;
	const int id = particle.Id();
	//	FillParticleParameters(particle,iParticle, particle.Id(), iPV, hPartParamPrimaryTopo, hPartParam2DPrimaryTopo, 0, hFitQATopoConstraint);
      }
#endif
      const std::vector<KFParticle>& PrimaryCandidatesTopoMass = GetTopoReconstructor()->GetKFParticleFinder()->GetPrimaryTopoMassCandidates()[iSet][iPV];
      if (_debug) cout << "PrimaryCandidatesTopoMass.size() = " << PrimaryCandidatesTopoMass.size() << endl;
      for(unsigned int iP=0; iP<PrimaryCandidatesTopoMass.size(); iP++)        {
	const KFParticle *particle =  &PrimaryCandidatesTopoMass[iP]; PrPP(particle);
	Vec4Cfit.push_back(particle);
      }
    }
  }
  return Vec4Cfit;
}
//________________________________________________________________________________
Bool_t StKFParticleInterface::PidQArmerteros(KFParticle TempParticle, TVector3 &neg, TVector3 &pos) {
  Bool_t ok = kFALSE;
  enum {Ndecays = 4};
  struct Decay_t {
    Int_t pdgParent;
    const Char_t *name;
    Int_t pdg1;
    Int_t pdg2;
  };
  static Decay_t parents[Ndecays] = {
    {   310, "Ks",           211, -211},
    {  3122, "Lambda",      2212, -211},
    { -3122, "Lambdab",    -2212,  211},
    {    22, "gamma",         11,  -11}
  }; 
  static TH2F *histo[Ndecays] = {0};
  if (! histo[0]) {
    TDirectory *top = StMaker::GetTopChain()->GetTFile();
    if (! top->cd("PiDQA")) {
      top->mkdir("PiDQA");
    }
   TDirectory * PiDQA = top->GetDirectory("PiDQA");
    for (Int_t d = 0; d < Ndecays; d++) {
      TDirectory *dir1 = PiDQA;
      TDirectory *dir2 = dir1->GetDirectory(parents[d].name);
      if (! dir2) {
	dir1->mkdir(parents[d].name); 
	dir2 = dir1->GetDirectory(parents[d].name); 
      }
      dir2->cd(); 
      if (_debug) cout << "d = " << d << "\t" << gDirectory->GetPath() << endl;
      TString Title(parents[d].name);
      Title += " Armenteros"; Title += " ; #alpha (p_{L}^{+}-p_{L}^{-})/(p_{L}^{+}+p_{L}^{-}) ; q_{t} [GeV/c]";
      histo[d] = new TH2F("Armenteros",Title, 50, -1, 1, 100,  0, 0.5);
      histo[d]->GetYaxis()->SetTitleOffset(1.0);
    }
  }
  if (TempParticle.NDaughters() != 2) return ok;
  int index1 = TempParticle.DaughterIds()[0];
  int index2 = TempParticle.DaughterIds()[1];
  if(index1 >= int(GetParticles().size()) || 
     index2 >= int(GetParticles().size()) || 
     index1 < 0 || index2 < 0 ) 
    return ok;
  Int_t k = -1;
  for (Int_t d = 0; d < Ndecays; d++) {
    if (TempParticle.GetPDG() != parents[d].pdgParent) continue;
    k = d;
    break;
  }
  if (k < 0) return ok;
  assert(histo[k]);
  KFParticle posDaughter, negDaughter;
  if(int(GetParticles()[index1].Q()) > 0)    {
    posDaughter = GetParticles()[index1];
    negDaughter = GetParticles()[index2];
  }    else    {
    negDaughter = GetParticles()[index1];
    posDaughter = GetParticles()[index2];
  }
  float vertex[3] = {TempParticle.GetX(), TempParticle.GetY(), TempParticle.GetZ()};
  posDaughter.TransportToPoint(vertex);
  negDaughter.TransportToPoint(vertex);
  Float_t QtAlpha[2];
  KFParticle::GetArmenterosPodolanski(posDaughter, negDaughter, QtAlpha );
  histo[k]->Fill(QtAlpha[1],QtAlpha[0],1);
#if 0
  // Use exact mass to estimate fitted daughter momenta
  TLorentzVector Mother, Neg, Pos;
  auto M =  TDatabasePDG::Instance()->GetParticle(TempParticle.GetPDG())->Mass();
  auto mN = TDatabasePDG::Instance()->GetParticle(negDaughter.GetPDG())->Mass();
  auto mP = TDatabasePDG::Instance()->GetParticle(posDaughter.GetPDG())->Mass();
  auto pmax = (M > mN + mP) ?  TMath::Sqrt ((M - mN + mP)*
					    (M + mN - mP)*
					    (M - mN - mP)*
					    (M + mN + mP))/(2.*M) :    0;
  Mother.SetXYZM(TempParticle.Px(), TempParticle.Py(), TempParticle.Pz(), M);
  Neg.SetXYZM(negDaughter.Px(), negDaughter.Py(), negDaughter.Pz(), mN);
  Pos.SetXYZM(posDaughter.Px(), posDaughter.Py(), posDaughter.Pz(), mP);
  
  TVector3 beta = Mother.BoostVector();
  TVector3 betaI = - beta;
  Neg.Boost(betaI); 
  Neg.SetRho(pmax);
  Neg.Boost(beta);
  Pos.Boost(betaI);
  Pos.SetRho(pmax);
  Pos.Boost(beta);
  neg = Neg.Vect();
  pos = Pos.Vect();
#endif
  
  ok = kTRUE;
  if ((parents[k].pdgParent ==  2212 && QtAlpha[0] <  0.2) ||
      (parents[k].pdgParent == -2212 && QtAlpha[0] > -0.2)) ok = kFALSE;
  return ok;
}
//________________________________________________________________________________
Bool_t StKFParticleInterface::FindUnique(const KFParticle *particle, vector<const KFParticle *> Vec4Cfit, Int_t indxnp[2]) {
  indxnp[0] = particle->DaughterIds()[0];
  indxnp[1] = particle->DaughterIds()[1];
  if ( int(GetParticles()[indxnp[0]].Q()) > 0) {
    indxnp[0] = particle->DaughterIds()[1];
    indxnp[1] = particle->DaughterIds()[0];
  }
  KFParticle p1 = GetParticles()[indxnp[0]]; PrPO(p1);
  Int_t index1 = ftrackIdToI[p1.DaughterIds()[0]];
  KFParticle p2 = GetParticles()[indxnp[1]]; PrPO(p2);
  Int_t index2 = ftrackIdToI[p2.DaughterIds()[0]];
  Bool_t foundUniq = kTRUE;
  for (auto particle2 : Vec4Cfit) {
    if (particle == particle2) continue;
    KFParticle p21 = GetParticles()[particle2->DaughterIds()[0]]; PrPO(p21);
    Int_t index21 = ftrackIdToI[p21.DaughterIds()[0]];
    KFParticle p22 = GetParticles()[particle2->DaughterIds()[1]]; PrPO(p22);
    Int_t index22 = ftrackIdToI[p22.DaughterIds()[0]];
    if ((index1 == index21 && index2 == index22) ||
	(index2 == index21 && index1 == index22)) {
      foundUniq = kFALSE;
      break;
    }
  }
  return foundUniq;
}
//________________________________________________________________________________
Bool_t StKFParticleInterface::PidQA(StPicoDst* picoDst) {
  StPicoEvent* picoEvent = picoDst->event();
  if(!picoEvent) return 0;
  Int_t nGlobalTracks = picoDst->numberOfTracks( );
  if (! nGlobalTracks) return kFALSE;
  const int nCandidates = GetParticles().size();
  if (! nCandidates) return kFALSE;
  for (Int_t iParticle = 0; iParticle < nCandidates; iParticle++) {
    const KFParticle &particle = GetParticles()[iParticle]; PrPO(particle);
    if (particle.NDaughters() != 1) continue;
    Int_t index = ftrackIdToI[particle.DaughterIds()[0]];
    //      cout << "ftrackIdToI[" << iParticle << "] = " << index << endl;
    if (index > 0 && index <= nGlobalTracks) {
      StPicoTrack *gTrack = picoDst->track(index); PrPP(gTrack);
      if (! gTrack) continue;
      if (_debug) {
	StPicoTrackCovMatrix *cov = picoDst->trackCovMatrix(index);
	const StDcaGeometry dca = cov->dcaGeometry();
	KFParticle p = dca.Particle(index,particle.GetPDG()); PrPO(p);
      }
      StTrackCombPiD PiD(picoDst,index); 
      if (PiD.Status() < 0) continue;
      FillPidQA(&PiD, particle.GetPDG(), 0);
    }
  }
  // list on unique fits
  vector<const KFParticle *> Vec4Cfit = Vec4Cfits();
  for (auto particle : Vec4Cfit) {
    Int_t indxnp[2] = {0};
    if (! FindUnique(particle, Vec4Cfit, indxnp)) continue;
    TVector3 negpos[2];
    if (! PidQArmerteros(*particle, negpos[0], negpos[1])) continue;
    for (Int_t np = 0; np < 2; np++) {
      Int_t index = indxnp[np];
      const KFParticle &p1 = GetParticles()[index]; PrPO(p1);
      Int_t index1 = ftrackIdToI[p1.DaughterIds()[0]];
      StPicoTrack *gTrack1 = picoDst->track(index1); PrPP(gTrack1);
      if (_debug) {
	StPicoTrackCovMatrix *cov = picoDst->trackCovMatrix(index1);
	const StDcaGeometry dca = cov->dcaGeometry();
	KFParticle p = dca.Particle(p1.Id(),p1.GetPDG()); PrPO(p);
      }
      StTrackCombPiD PiD1(picoDst, index1); // gTrack1); 
      if (PiD1.Status() < 0) continue;
      FillPidQA(&PiD1, p1.GetPDG(), particle->GetPDG());
    }
  }
  return kTRUE;
}
//________________________________________________________________________________
Bool_t StKFParticleInterface::PidQA(StMuDst* muDst) {
  StMuEvent* muEvent = muDst->event();
  if(!muEvent) return 0;
  Int_t nGlobalTracks = muDst->numberOfGlobalTracks( );
  if (! nGlobalTracks) return kFALSE;
  const int nCandidates = GetParticles().size();
  if (! nCandidates) return kFALSE;
  for (Int_t iParticle = 0; iParticle < nCandidates; iParticle++) {
    const KFParticle &particle = GetParticles()[iParticle]; PrPO(particle);
    if (particle.NDaughters() != 1) continue;
    Int_t index = ftrackIdToI[particle.DaughterIds()[0]];
    //      cout << "ftrackIdToI[" << iParticle << "] = " << index << endl;
    if (index > 0 && index <= nGlobalTracks) {
      StMuTrack *gTrack = muDst->globalTracks(index); PrPP(gTrack);
      if (! gTrack) continue;
      if (_debug) {
	const StDcaGeometry* dca = gTrack->dcaGeom();
	KFParticle p = dca->Particle(index,particle.GetPDG()); PrPO(p);
      }
      StTrackCombPiD PiD(gTrack); 
      if (PiD.Status() < 0) continue;
      FillPidQA(&PiD, particle.GetPDG(), 0);
    }
  }
  vector<const KFParticle *> Vec4Cfit = Vec4Cfits(); 
  for (auto particle : Vec4Cfit) {
    Int_t indxnp[2] = {0};
    if (! FindUnique(particle, Vec4Cfit, indxnp)) continue;
    TVector3 negpos[2];
    if (! PidQArmerteros(*particle, negpos[0], negpos[1])) continue;
    for (Int_t np = 0; np < 2; np++) {
      Int_t index = indxnp[np];
      const KFParticle &p1 = GetParticles()[index]; PrPO(p1);
      Int_t index1 = ftrackIdToI[p1.DaughterIds()[0]];
      StMuTrack *gTrack1 = muDst->globalTracks(index1); PrPP(gTrack1);
      if (_debug) {
	const StDcaGeometry* dca = gTrack1->dcaGeom();
	KFParticle p = dca->Particle(index1,p1.GetPDG());      PrPO(p);
      }
      StTrackCombPiD PiD1(gTrack1); 
      if (PiD1.Status() < 0) continue;
      FillPidQA(&PiD1, p1.GetPDG(), particle->GetPDG());
    }
  }
  return kTRUE;
}
//________________________________________________________________________________
Bool_t StKFParticleInterface::FillPidQA(StTrackCombPiD* PiD, Int_t PDG, Int_t PDGParent) {
  struct Particle_t {
    Int_t pdg;
    const Char_t *name;
    Int_t code;
  };
  enum {Nparticles = 18, NparticlesA = 10,  Ndecays = 4};
  static Particle_t particles[26] = {
    {         11,  "e-",   kPidElectron},
    { 	     -11,  "e+",   kPidElectron},	 
    { 	      13,  "mu-",  kPidMuon}, 	 
    { 	     -13,  "mu+",  kPidMuon},	 
    {        211,  "pi+",  kPidPion},	 
    { 	    -211,  "pi-",  kPidPion},	 
    { 	     321,  "K+",   kPidKaon},	 
    { 	    -321,  "K-",   kPidKaon},	 
    {       2212,  "p",    kPidProton},	 
    {      -2212,  "p-",   kPidProton},	 
    { 1000010020,  "d",    kPidDeuteron},        
    {-1000010020,  "d-",   kPidDeuteron}, 
    { 1000010030,  "t",    kPidTriton},	 
    {-1000010030,  "t-",   kPidTriton},	 
    { 1000020030,  "He3",  kPidHe3},      
    {-1000020030,  "He3-", kPidHe3},
    { 1000020040,  "He4",  kPidAlpha},	 
    {-1000020040,  "He4-", kPidAlpha},
    { 1000020060,  "He6",  -1},	 
    {-1000020060,  "He6-", -1},
    { 1000030060,  "Li6",  -1},	 
    {-1000030060,  "Li6-", -1},
    { 1000030070,  "Li7",  -1},	 
    {-1000030070,  "Li7-", -1}, 
    { 1000040070,  "Be7",  -1},	 
    {-1000040070,  "Be7-", -1}
  };
  struct Decay_t {
    Int_t pdgParent;
    const Char_t *name;
    Int_t pdg1;
    Int_t pdg2;
  };
  static Decay_t parents[4] = {
    {   310, "Ks",           211, -211},
    {  3122, "Lambda",      2212, -211},
    { -3122, "Lambdab",    -2212,  211},
    {    22, "gamma",         11,  -11}
  }; 
  static TH2F *hist[Ndecays+1][Nparticles][StTrackCombPiD::kTotal+1][5] = {0}; // kTotal for Tpc & BTof
  if (! hist[0][0][StTrackCombPiD::kFit][0]) {
    TDirectory *top = StMaker::GetTopChain()->GetTFile();
    top->mkdir("PiDQA");
    TDirectory *PiDQA = top->GetDirectory("PiDQA");
    Int_t d1 = 0;
    for (Int_t d = d1; d <= Ndecays; d++) {
      for (Int_t p = 0; p < Nparticles; p++) {
	PiDQA->cd();
	if (_debug) cout << "d = " << d << "\tp = " << p << "\t" <<  gDirectory->GetPath() << endl;
	TDirectory *dir1 = PiDQA;
	if (d > 0 && (particles[p].pdg != parents[d-1].pdg1 && particles[p].pdg != parents[d-1].pdg2)) continue;
	if (d) {
	  TDirectory *dir2 = dir1->GetDirectory(parents[d-1].name);
	  if (! dir2) {
	    dir1->mkdir(parents[d-1].name); 
	    dir2 = dir1->GetDirectory(parents[d-1].name); 
	  }
	  dir2->cd(); dir1 = dir2;
	  if (_debug) cout << "d = " << d << "\tp = " << p << "\t" <<  gDirectory->GetPath() << endl;
	}
	TString name(particles[p].name);
	dir1->mkdir(name);
	TDirectory *dir3 = dir1->GetDirectory(name);
	dir3->cd();
	if (_debug) cout << "d = " << d << "\tp = " << p << "\t" <<  gDirectory->GetPath() << endl;
	for (Int_t k = 1; k < StTrackCombPiD::kTotal + 1; k++) {
	  if (k == StTrackCombPiD::kFit) {
	    hist[d][p][k][0] = new TH2F("dEdx",Form("dE/dx_{%s} / dEdModel prediction for I_{fit} versus log_{10}(#beta #gamma)",StTrackCombPiD::fgPiDStatusNames[k]), 1000,-1,4,500,-0.5,0.5);
	    hist[d][p][k][1] = new TH2F("PulldEdx",Form("(dE/dx_{%s} / dEdModel)/#sigma  versus log_{10}(#beta #gamma)",StTrackCombPiD::fgPiDStatusNames[k]),          1000,-1,4,600,-3,3);
	    hist[d][p][k][2] = new TH2F("dEdxC",Form("dE/dx_{%s} / dEdModel prediction Corrected for I_{fit} versus log_{10}(#beta #gamma)",StTrackCombPiD::fgPiDStatusNames[k]), 1000,-1,4,500,-0.5,0.5);
	    hist[d][p][k][3] = new TH2F("PullCdEdx",Form("(dE/dx_{%s} / dEdModel)/#sigma Corrected versus log_{10}(#beta #gamma)",StTrackCombPiD::fgPiDStatusNames[k]),1000,-1,4,600,-3,3);
	    for (Int_t i = 0; i < 3; i++) hist[d][p][k][i]->SetXTitle("log_{10}(#beta #gamma)");
	  } else if (k == StTrackCombPiD::kTotal) {
	    hist[d][p][k][0] = new TH2F("dEdxBTof",Form("dE/dx_{%s} / dEdModel prediction for I_{fit} versus log_{10}(#beta #gamma)a with |sigmaBTOF| < 3",StTrackCombPiD::fgPiDStatusNames[k]), 1000,-1,4,500,-0.5,0.5);
	    hist[d][p][k][1] = new TH2F("PulldEdxBTof",Form("(dE/dx_{%s} / dEdModel)/#sigma  versus log_{10}(#beta #gamma)a with |sigmaBTOF| < 3",StTrackCombPiD::fgPiDStatusNames[k]),          1000,-1,4,600,-3,3);
	    hist[d][p][k][2] = new TH2F("dEdxCBTof",Form("dE/dx_{%s} / dEdModel corrected prediction for I_{fit} versus log_{10}(#beta #gamma)a with |sigmaBTOF| < 3",StTrackCombPiD::fgPiDStatusNames[k]), 1000,-1,4,500,-0.5,0.5);
	    hist[d][p][k][3] = new TH2F("PullCdEdxCBTof",Form("(dE/dx_{%s} / dEdModel)/#sigma Corrected versus log_{10}(#beta #gamma)a with |sigmaBTOF| < 3",StTrackCombPiD::fgPiDStatusNames[k]),1000,-1,4,600,-3,3);
	    for (Int_t i = 0; i < 3; i++) hist[d][p][k][i]->SetXTitle("log_{10}(#beta #gamma)");
	  } else if (k == StTrackCombPiD::kBTof) {
	    hist[d][p][k][0] = new TH2F("dM2BTof","dM^{2} from BTof versus log_{10}(#beta #gamma)"                              ,1000,-1,4,400,-0.2,0.2);
	    hist[d][p][k][1] = new TH2F("dM2BTofPull","dM^{2}/#sigma dM^ {2} from BTof versus log_{10}(#beta #gamma)"           ,1000,-1,4,600,-6.0,6.0);
	    hist[d][p][k][2] = new TH2F("dM2CBTof","dM^{2} Corrrected from BTof versus log_{10}(#beta #gamma)"                              ,1000,-1,4,400,-0.2,0.2);
	    hist[d][p][k][3] = new TH2F("dM2BTofPullC","dM^{2}/#sigma dM^ {2} corrected from BTof versus log_{10}(#beta #gamma)",1000,-1,4,600,-6.0,6.0);
	    hist[d][p][k][4] = new TH2F("PullBTof","nSigma BTof versus log_{10}(#beta #gamma)"                                  ,1000,-1,4,600,-3,3);
	    for (Int_t i = 0; i < 4; i++) hist[d][p][k][i]->SetXTitle("log_{10}(#beta #gamma)");
	  } else if (k == StTrackCombPiD::kETof) {
	    hist[d][p][k][0] = new TH2F("dM2ETof","dM^{2} from ETof versus log_{10}(#beta #gamma)"                              ,1000,-1,4,400,-0.2,0.2);
	    hist[d][p][k][1] = new TH2F("dM2ETofPull","dM^{2}/#sigma dM^ {2} from ETof versus log_{10}(#beta #gamma)"           ,1000,-1,4,600,-6.0,6.0);
	    hist[d][p][k][2] = new TH2F("dM2ETofPullC","dM^{2}/#sigma dM^ {2} corrected from ETof versus log_{10}(#beta #gamma)",1000,-1,4,600,-6.0,6.0);
	    hist[d][p][k][3] = new TH2F("PullETof","nSigma ETof versus log_{10}(#beta #gamma)"                                  ,1000,-1,4,600,-3,3);
	    for (Int_t i = 0; i < 4; i++) hist[d][p][k][i]->SetXTitle("log_{10}(#beta #gamma)");
	  } else if (k == StTrackCombPiD::kBEmc) {
	    hist[d][p][k][0] = new TH2F("BemcEoverP","E/P in BEMC versus log_{10} P"                                            ,250,-0.75,1.75,100,0.0,10.0);
	    hist[d][p][k][0]->SetXTitle("log_{10}P");
	  } else if (k == StTrackCombPiD::kMtd) {
	    hist[d][p][k][0] = new TH2F("MtdYdZ","Mtd dY vesus dZ"                                            ,100,-50,50,100,-100,100);
	    hist[d][p][k][1] = new TH2F("MtddT","Mtd dT vesus log{10} P"                                      ,100,-1.,5.,400,-2000,2000); // ??
	  }
	}
      }
    }
  }
  if (! PiD->fFit()) return kFALSE;
  Double_t pMom = PiD->pMomentum();
  Double_t pL10 = TMath::Log10(pMom);
  Int_t d = 0;
  if (PDGParent) {
    d = -1;
    for (Int_t dau = 0; dau < Ndecays; dau++) {
      if (PDGParent != parents[dau].pdgParent) continue;
      if (PDG != parents[dau].pdg1 && PDG != parents[dau].pdg2) continue;
      d = dau + 1;
      break;
    }
  } 
  if (d < 0) return kFALSE;
  for (Int_t p = 0; p < Nparticles; p++) {
    if (PDG != particles[p].pdg) continue;
    Int_t l = particles[p].code;
#if 0
    Int_t pdg = particles[p].pdg;
    //      Double_t M = StProbPidTraits::mPidParticleDefinitions[l]->mass();
    auto M =  TDatabasePDG::Instance()->GetParticle(pdg)->Mass();
    auto q =  TDatabasePDG::Instance()->GetParticle(pdg)->Charge()/3.;
#endif
    Double_t bgL10 = PiD->bghyp(l);
    for (Int_t k = 1; k < StTrackCombPiD::kTotal + 1; k++) {
      if (! hist[d][p][k][0]) continue;
      if (k < StTrackCombPiD::kTotal) {
	if (! PiD->Status(k)) continue;
      } else {
	if (! PiD->Status(StTrackCombPiD::kBTof)) continue; 
      }
      Int_t kd = k;
      if (k == StTrackCombPiD::kTotal) kd = StTrackCombPiD::kFit;
      if (k == StTrackCombPiD::kBEmc) {
	hist[d][p][k][0]->Fill(TMath::Log10(pMom), PiD->fBEmc()->bemcE()/pMom);
      } else if (k == StTrackCombPiD::kMtd) {
	hist[d][p][k][0]->Fill(PiD->fMtd()->PiD()->deltaZ(), PiD->fMtd()->PiD()->deltaY());
	hist[d][p][k][1]->Fill(pL10, PiD->fMtd()->deltaTimeOfFlight());
      } else {
	hist[d][p][k][0]->Fill(bgL10, PiD->Status(kd)->residual(l));
	hist[d][p][k][1]->Fill(bgL10, PiD->Status(kd)->pull(l));
	hist[d][p][k][2]->Fill(bgL10, PiD->Status(kd)->residualC(l));
	hist[d][p][k][3]->Fill(bgL10, PiD->Status(kd)->pullC(l));
	if (k == StTrackCombPiD::kBTof) {
	  hist[d][p][k][4]->Fill(bgL10, PiD->fBTof()->Sigma(l));
	}
      }
    }
  }
  return kTRUE;
}
