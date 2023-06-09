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
#include "StPicoEvent/StPicoTrackCovMatrix.h"
#include "StPicoEvent/StPicoBTofPidTraits.h"
#include "StPicoEvent/StPicoETofPidTraits.h"
#include "StdEdxY2Maker/StPidStatus.h"
#include "StMaker.h"
#include "StMuDSTMaker/COMMON/StMuDst.h"
#include "THelixTrack.h" 
#include "StBichsel/Bichsel.h"
#include "StBichsel/StdEdxModel.h"
#include "StProbPidTraits.h"
#include "StMuDSTMaker/COMMON/StMuBTofHit.h"
#include "StMuDSTMaker/COMMON/StMuMcVertex.h"
#include "StMuDSTMaker/COMMON/StMuMcTrack.h"
#include "TLorentzVector.h"
#include "TDatabasePDG.h"
#include <ctime>
#include <algorithm>
//#define PID_2018
// #define PID_MAY
// #if ! defined(PID_2018) && ! defined( PID_MAY)
// #define PID_JUNE
// #endif

static Int_t _debug = 0;
#define PrPP(A) if (_debug) {std::cout << (#A) << "\t"; A->Print();}
#define PrPO(A) if (_debug) {std::cout << (#A) << "\t"; A.Print();}
//    #define USEETOF
//#define __USE_HFT__
//#define __ETAPN_TOF_PLOTS__
#define dEdxL10min 0.0
#define dNdxL10min 1.25
#define __BOOK_hdEdx__(dir,hist,Name,Title)				\
  hist = (TH2F *)   dir->Get(Name);					\
  if (! hist) {								\
    hist = new TH2F(Name,Title, 700, -2, 1.5, 250, dEdxL10min, dEdxL10min+2.5);	\
    hist->SetXTitle("log_{10}P");					\
    hist->SetYTitle("log_{10}dE/dx");					\
  } 
#define __BOOK_hdNdx__(dir,hist,Name,Title)				\
  hist = (TH2F *)   dir->Get(Name);					\
  if (! hist) {								\
    hist = new TH2F(Name,Title, 700, -2, 1.5, 300, dNdxL10min, dNdxL10min+2.5);	\
    hist->SetXTitle("log_{10}P");					\
    hist->SetYTitle("log_{10}dN/dx");					\
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
StKFParticleInterface::StKFParticleInterface(): 
  fKFParticleTopoReconstructor(0), fParticles(0), fParticlesPdg(0), fNHftHits(0),
  fCollectTrackHistograms(false), fCollectPIDHistograms(false), fCollectPVHistograms(false),
  fStrictTofPID(true), fCleanKaonsWitTof(true), fdEdXMode(1), fTriggerMode(false),
  fChiPrimaryCut(18.6f), fChiPrimaryCutFragments(0.f), fChiPrimaryMaxCut(2e4f), fCleanLowPVTrackEvents(false), fUseHFTTracksOnly(false)
  , fIsFixedTarget(kFALSE), fIsFixedTarget2018(kFALSE), fPidQA(kTRUE)

{
  fKFParticleTopoReconstructor = new KFParticleTopoReconstructor();
  fgStKFParticleInterface = this;
  StPidStatus::SetUsedx2(fgUsedx2);
  StPidStatus::SetUseTof(fgUseTof);
  // set default cuts
  SetPrimaryProbCut(0.0001); // 0.01% to consider primary track as a secondary;
  
}
void StKFParticleInterface::SetUsedx2(Bool_t k) {fgUsedx2 = k; StPidStatus::SetUsedx2(fgUsedx2);}
void StKFParticleInterface::SetUseTof(Bool_t k) {fgUseTof = k; StPidStatus::SetUseTof(fgUseTof);}

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
  
//   static int iEvent=0;
//   iEvent++;
//   std::cout << "Event " << iEvent << ": init " << fKFParticleTopoReconstructor->StatTime( 0 ) 
//             << " pv " << fKFParticleTopoReconstructor->StatTime( 1 )
//             << " sort " << fKFParticleTopoReconstructor->StatTime( 2 )
//             << " particles " << fKFParticleTopoReconstructor->StatTime( 3 ) <<  std::endl;
}

void StKFParticleInterface::ReconstructTopology()
{ 
  fKFParticleTopoReconstructor->Init( fParticles, &fParticlesPdg );
  fKFParticleTopoReconstructor->ReconstructPrimVertex(0);
  fKFParticleTopoReconstructor->SortTracks();
  fKFParticleTopoReconstructor->ReconstructParticles();
  
//   static int iEvent=0;
//   iEvent++;
//   std::cout << "Event " << iEvent << ": init " << fKFParticleTopoReconstructor->StatTime( 0 ) 
//             << " pv " << fKFParticleTopoReconstructor->StatTime( 1 )
//             << " sort " << fKFParticleTopoReconstructor->StatTime( 2 )
//             << " particles " << fKFParticleTopoReconstructor->StatTime( 3 ) <<  std::endl;
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
void StKFParticleInterface::SetSecondaryCuts(const float sigmaMass, const float chi2Topo, const float ldl)                 
{ 
  GetKFParticleFinder()->SetSecondaryCuts(sigmaMass, chi2Topo, ldl); 
}
  
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
  dirs[0] = TDirectory::CurrentDirectory(); assert(dirs[0]);
  dirs[0]->cd();
  if (! dirs[0]->GetDirectory("Tracks")) {
    dirs[0]->mkdir("Tracks");
  }
  dirs[1] = dirs[0]->GetDirectory("Tracks"); assert(dirs[1]);
  dirs[1]->cd();
  const Char_t *chargeName[4] = {"","Pos","Neg","withTof"};
  for (Int_t i = 0; i < 4; i++) {
    __BOOK_hdEdx__(dirs[1],fTrackHistograms2D[i]  , Form("hdEdX%s",chargeName[i]),  Form("hdEdX%s",chargeName[i]));
    __BOOK_hdNdx__(dirs[1],fTrackHistograms2D[i+9], Form("hdNdX%s",chargeName[i]),  Form("hdNdX%s",chargeName[i]));
  }
  fTrackHistograms2D[4] = (TH2F *)   dirs[1]->Get("hTofPID");
  if (! fTrackHistograms2D[4]) {
    fTrackHistograms2D[4] = new TH2F("hTofPID", "hTofPID", 200, -1, 1, 1100, -1, 10);
    fTrackHistograms2D[4]->SetXTitle("log_{10}P");
#ifdef __ETAPN_TOF_PLOTS__ 
    fTrackHistograms2D[15] = new TH2F("hTofPIDP", "hTofPIDP eta >  0", 200, -1, 1, 1100, -1, 10);
    fTrackHistograms2D[15]->SetXTitle("log_{10}P");
    fTrackHistograms2D[16] = new TH2F("hTofPIDN", "hTofPIDN eta <= 0", 200, -1, 1, 1100, -1, 10);
    fTrackHistograms2D[16]->SetXTitle("log_{10}P");
#endif /* __ETAPN_TOF_PLOTS__ */
  }
  fTrackHistograms2D[14] = (TH2F *)   dirs[1]->Get("hETofPID");
  if (! fTrackHistograms2D[14]) {
    fTrackHistograms2D[14] = new TH2F("hETofPID", "hETofPID", 300, -2, 2, 1100, -1, 10);
    fTrackHistograms2D[14]->SetXTitle("log_{10}P");
  }
#ifdef __USE_HFT__
  fTrackHistograms[0] = (TH1F *)   dirs[1]->Get("hNHFTHits");
  if (! fTrackHistograms[0]) fTrackHistograms[0] = new TH1F("hNHFTHits", "hNHFTHits",11, -0.5, 10.5);

#endif /*  __USE_HFT__ */
  fTrackHistograms[1] = (TH1F *)   dirs[1]->Get("hPVError");
  if (! fTrackHistograms[1]) fTrackHistograms[1] = new TH1F("hPVError", "hPVError", 10000, 0, 1);

  fTrackHistograms2D[5] = (TH2F *)   dirs[1]->Get("hPVErrorVsNTracks");
  if (! fTrackHistograms2D[5]) {
    fTrackHistograms2D[5] = new TH2F("hPVErrorVsNTracks", "hPVErrorVsNTracks", 3000, 0.5, 3.5, 5000, 0, 0.5);
    fTrackHistograms2D[5]->SetXTitle("log_{10} No. Global Tracks");
  }
  fTrackHistograms2D[6] = (TH2F *)   dirs[1]->Get("hPVErrorVsNPVTracks");
  if (! fTrackHistograms2D[6]) {
    fTrackHistograms2D[6] = new TH2F("hPVErrorVsNPVTracks", "hPVErrorVsNPVTracks", 3000, 0.5, 3.5, 5000, 0, 0.5);
    fTrackHistograms2D[6]->SetXTitle("log_{10} No. Primary Tracks ");
  }
  fTrackHistograms[2] = (TH1F *)   dirs[1]->Get("hPrimaryRatio");
  if (! fTrackHistograms[2]) fTrackHistograms[2] = new TH1F("hPrimaryRatio", "hPrimaryRatio", 100, 0, 1);
  
  fTrackHistograms2D[7] = (TH2F *)   dirs[1]->Get("hGlobalVsPrimaryTracks");
  if (! fTrackHistograms2D[7]) fTrackHistograms2D[7] = new TH2F("hGlobalVsPrimaryTracks", "Log_{10} No. Global vs Log_{10} No. Primary Tracks", 350, 0.0, 3.5, 350, 0, 3.5);
  fTrackHistograms2D[8] = (TH2F *)   dirs[1]->Get("EtaVspT");
  if (! fTrackHistograms2D[8]) fTrackHistograms2D[8] = new TH2F("EtaVspT", "Eta vs Log_{10}p_{T} for Primary tracks", 350, -2, 1.5, 600, -3.0, 3.0);
  fTrackHistograms2D[13] = (TH2F *)   dirs[1]->Get("EtaVspTAll");
  if (! fTrackHistograms2D[13]) fTrackHistograms2D[13] = new TH2F("EtaVspTAll", "Eta vs Log_{10}p_{T} for All tracks", 350, -2, 1.5, 600, -3.0, 3.0);
  
  dirs[0]->cd();
  
  fCollectTrackHistograms = true;
}

void StKFParticleInterface::CollectPIDHistograms()
{
  TDirectory *dirs[7] = {0};
  dirs[0] = TDirectory::CurrentDirectory(); assert(dirs[0]);
  dirs[0]->cd();
  if (! dirs[0]->GetDirectory("Tracks")) {
    dirs[0]->mkdir("Tracks");
  }
  dirs[1] = dirs[0]->GetDirectory("Tracks"); assert(dirs[1]);
  dirs[1]->cd();
  
  int pdgTrackHisto[NTrackHistoFolders] = { -1,
					    11, -11, 13, -13, 211, -211, 321, -321, 2212, -2212, 
                                            1000010020, -1000010020, 1000010030, -1000010030, 
                                            1000020030, -1000020030, 1000020040, -1000020040,
                                            1000020060, -1000020060, 1000030060, -1000030060,
                                            1000030070, -1000030070, 1000040070, -1000040070 };
  TString trackFolderName[NTrackHistoFolders] = {"Uknown",
						 "e-", "e+", "mu-", "mu+", "pi+", "pi-", "K+", "K-", "p", "p-", 
						 "d", "d-", "t", "t-", "He3", "He3-", "He4", "He4-", 
						 "He6", "He6-", "Li6", "Li6-", "Li7", "Li7-", "Be7", "Be7-"};
                    
  for(int iTrackHisto=1; iTrackHisto<NTrackHistoFolders; iTrackHisto++)
  {
    if (!dirs[1]->GetDirectory(trackFolderName[iTrackHisto].Data()))
      dirs[1]->mkdir(trackFolderName[iTrackHisto].Data());
    
    dirs[2] = dirs[1]->GetDirectory(trackFolderName[iTrackHisto].Data()); assert(dirs[2]);
    dirs[2]->cd();
    
    fTrackPdgToHistoIndex[ pdgTrackHisto[iTrackHisto] ] = iTrackHisto;
    __BOOK_hdEdx__(dirs[2],fHistodEdXTracks[iTrackHisto], "hdEdX", "hdEdX");
    __BOOK_hdEdx__(dirs[2],fHistodEdXwithTofTracks[iTrackHisto], "hdEdXwithTof", "hdEdXwithTof");
    __BOOK_hdNdx__(dirs[2],fHistodNdXTracks[iTrackHisto], "hdNdX", "hdNdX");
    __BOOK_hdNdx__(dirs[2],fHistodNdXwithTofTracks[iTrackHisto], "hdNdXwithTof", "hdNdXwithTof");
  
    fHistoTofPIDTracks[iTrackHisto][0] = (TH2F *)   dirs[2]->Get("hTofPID");
    if (! fHistoTofPIDTracks[iTrackHisto][0]) {
      fHistoTofPIDTracks[iTrackHisto][0] = new TH2F("hTofPID", "hTofPID", 200, -1, 1, 1100, -1, 10);
      fHistoTofPIDTracks[iTrackHisto][0]->SetXTitle("log_{10}P");
#ifdef __ETAPN_TOF_PLOTS__ 
      fHistoTofPIDTracks[iTrackHisto][1] = new TH2F("hTofPIDP", "hTofPID eta >  0", 200, -1, 1, 1100, -1, 10);
      fHistoTofPIDTracks[iTrackHisto][1]->SetXTitle("log_{10}P");
      fHistoTofPIDTracks[iTrackHisto][2] = new TH2F("hTofPIDN", "hTofPID eta <= 0", 200, -1, 1, 1100, -1, 10);
      fHistoTofPIDTracks[iTrackHisto][2]->SetXTitle("log_{10}P");
#endif /* __ETAPN_TOF_PLOTS__ */
    }
    fHistoETofPIDTracks[iTrackHisto] = (TH2F *)   dirs[2]->Get("hETofPID");
    if (! fHistoETofPIDTracks[iTrackHisto]) {
      fHistoETofPIDTracks[iTrackHisto] = new TH2F("hETofPID", "hETofPID", 200, -1, 1, 1100, -1, 10);
      fHistoETofPIDTracks[iTrackHisto]->SetXTitle("log_{10}P");
    }
  
    fHistoMomentumTracks[iTrackHisto] = (TH1F *)   dirs[2]->Get("hMomentum");
    if (! fHistoMomentumTracks[iTrackHisto]) fHistoMomentumTracks[iTrackHisto] = new TH1F("hMomentum", "log_{10} p", 1000, -2, 2);
    
    fHistodEdXPull[iTrackHisto] = (TH2F *)   dirs[2]->Get("hdEdXPull");
    if (! fHistodEdXPull[iTrackHisto]) fHistodEdXPull[iTrackHisto] = new TH2F("hdEdXPull", "hdEdXPull", 2000, -5, 5, 120, -6, 6);

    fHistodEdXnSigma[iTrackHisto] = (TH2F *)   dirs[2]->Get("hdEdXnSigma");
    if (! fHistodEdXnSigma[iTrackHisto]) fHistodEdXnSigma[iTrackHisto] = new TH2F("hdEdXnSigma", "hdEdXnSigma", 2000, -5, 5, 120, -6, 6);
    
    fHistodEdXZ[iTrackHisto] = (TH2F *)   dirs[2]->Get("hdEdXZ");
    if (! fHistodEdXZ[iTrackHisto]) fHistodEdXZ[iTrackHisto] = new TH2F("hdEdXZ", "hdEdXZ", 2000, -2, 2, 280, -1, 6);
    fHistodEdXPull[iTrackHisto] = (TH2F *)   dirs[2]->Get("hdEdXPull");
    if (! fHistodEdXPull[iTrackHisto]) fHistodEdXPull[iTrackHisto] = new TH2F("hdEdXPull", "hdEdXPull", 2000, -2, 2, 120, -6, 6);

    fHistodNdXPull[iTrackHisto] = (TH2F *)   dirs[2]->Get("hdNdXPull");
    if (! fHistodNdXPull[iTrackHisto]) fHistodNdXPull[iTrackHisto] = new TH2F("hdNdXPull", "hdNdXPull", 2000, -2, 2, 120, -6, 6);
    
    //    fHistodNdXZ[iTrackHisto] = (TH2F *)   dirs[2]->Get("hdNdXZ");
    //    if (! fHistodNdXZ[iTrackHisto]) fHistodNdXZ[iTrackHisto] = new TH2F("hdNdXZ", "hdNdXZ", 2000, -5, 5, 280, -1, 6);
    
    dirs[1]->cd();
  }
  
  dirs[0]->cd();
  
  fCollectPIDHistograms = true;
}
void StKFParticleInterface::CollectPVHistograms()
{
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
  if (! fPVHistograms[iHisto]) fPVHistograms[iHisto] = new TH1F(title, title, 4400, -220, 220);
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
  fPVHistograms2D[iHisto2D] = (TH2F *) pvDir->Get(title);
  if (! fPVHistograms2D[iHisto2D]) fPVHistograms2D[iHisto2D] = new TH2F(title, title, 200, -10, 10, 200, -10, 10);
  iHisto2D++;

  title = "ZR";
  fPVHistograms2D[iHisto2D] = (TH2F *) pvDir->Get(title);
  if (! fPVHistograms2D[iHisto2D]) fPVHistograms2D[iHisto2D] = new TH2F(title, title, 4400, -220, 220, 100, 0, 10);
  iHisto2D++;

  title = "ZRTracks";
  fPVHistograms2D[iHisto2D] = (TH2F *) pvDir->Get(title);
  if (! fPVHistograms2D[iHisto2D]) fPVHistograms2D[iHisto2D] = new TH2F(title, title, 440, -220, 220, 400, 0, 200);
  iHisto2D++;

  title = "ZRTracksRest";
  fPVHistograms2D[iHisto2D] = (TH2F *) pvDir->Get(title);
  if (! fPVHistograms2D[iHisto2D]) fPVHistograms2D[iHisto2D] = new TH2F(title, title, 440, -220, 220, 400, 0, 200);
  iHisto2D++;

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
#if 0
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


std::vector<int> StKFParticleInterface::GetPID(double m2, double p, int q, double dEdX, double dEdXPull[12], bool isTofm2, const int trackId)
{
  vector<int> TofPDG;
  if(isTofm2 && fgUseTof)
    TofPDG = GetTofPID(m2, p, q, trackId);
  
  for(int iPdg=0; iPdg<3; iPdg++)
    fTrackPidTpc[iPdg][trackId] = dEdXPull[iPdg+1];
  
  vector<int> dEdXPDG;
  float nSigmaCut = 3.f; //TODO
#if 0  
  bool checkKTof = fCleanKaonsWitTof && (p > 0.5) && (p < 2.);
  bool checkKHasTof = 0;
  for(unsigned int iTofPDG=0; iTofPDG<TofPDG.size(); iTofPDG++)
    if(abs(TofPDG[iTofPDG]) == 321)
      checkKHasTof = 1;
#endif
  if(dEdXPull[0] < nSigmaCut)                                           dEdXPDG.push_back(-11*q);
  if(dEdXPull[2] < nSigmaCut)                                           dEdXPDG.push_back(211*q);  
  //  if(dEdXPull[3] < 2.f && ((checkKTof && checkKHasTof) || !checkKTof) ) dEdXPDG.push_back(321*q);
  if(dEdXPull[3] < nSigmaCut )                                          dEdXPDG.push_back(321*q);
  if(dEdXPull[4] < nSigmaCut)                                           dEdXPDG.push_back(2212*q); 
      
  vector<int> totalPDG;
#if 1
  totalPDG = dEdXPDG;
#else 
  if(!isTofm2 || ! fgUseTof)
    totalPDG = dEdXPDG;
  else
  {
    for(unsigned int iPDG=0; iPDG<dEdXPDG.size(); iPDG++)
      for(unsigned int iTofPDG=0; iTofPDG<TofPDG.size(); iTofPDG++)
        if(dEdXPDG[iPDG] == TofPDG[iTofPDG])
          totalPDG.push_back(TofPDG[iTofPDG]);        
  }

  if(dEdXPull[1] < nSigmaCut)  totalPDG.push_back(-13*q);
  if(dEdXPull[9] < nSigmaCut  || 
     dEdXPull[10] < nSigmaCut ||
     dEdXPull[11] < nSigmaCut)  
  {
    totalPDG.push_back(2000003112*q);
  }
#endif  
#if defined(PID_2018) // staryj
#include "PID2018.h"
#elif  defined(PID_MAY) // Mai
#include "PIDMAY.h"
#eliif (defined(PID_JUNE) //June
#include "PIDJUNE.h"
#endif //PID_2018 || PID_MAY || PID_JUNE
    
  if(totalPDG.size() == 0)
    totalPDG.push_back(-1);
  
  return totalPDG;
}
#endif
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

    //    if(abs(pdg) == 1000020060 || abs(pdg) == 1000030060)
    //    {
#if 0
      float dx = (trackPDG.GetX() - pv.X());
      float dy = (trackPDG.GetY() - pv.Y());
      float dz = (trackPDG.GetZ() - pv.Z());
      float r = sqrt(trackPDG.GetX()*trackPDG.GetX() + trackPDG.GetY()*trackPDG.GetY());
      float l = sqrt(dx*dx + dy*dy + dz*dz);
//       if(!(r<2. && l<2.)) continue;
#endif
    //correct for the charge of ions
    const int index2[9] = { 6,7,8, 10,11,12, 15,16,17 };
    const int index4[6] = { 9, 13,14, 18,19,20 };
#ifdef __MagFieldCorrection__
//TODO remove coefficient !!!!
    {
      trackPDG.SetPx( trackPDG.GetPx() * fgMagScaleFactor );
      trackPDG.SetPy( trackPDG.GetPy() * fgMagScaleFactor );
      trackPDG.SetPz( trackPDG.GetPz() * fgMagScaleFactor );
      for(int iIndex=0; iIndex<9; iIndex++){
        const int iC = index2[iIndex];
        trackPDG.SetCovariance( iC, trackPDG.GetCovariance(iC) * fgMagScaleFactor );
      }
      for(int iIndex=0; iIndex<6; iIndex++){
        const int iC = index4[iIndex];
        trackPDG.SetCovariance( iC, trackPDG.GetCovariance(iC) * fgMagScaleFactor * fgMagScaleFactor );
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

//     if(abs(pdg) == 211)
//     {
//       trackPDG.SetCharge( -trackPDG.Charge() );
//       pdg = -pdg;
//     }
    
    //FIXME uncomment
//     nHftHits[nPartSaved] = nHftHitsInTrack;
    nHftHits[nPartSaved] = 0;
    
    KFParticle particle(trackPDG, pdg);
    particle.Chi2() = chi2;
    particle.NDF()  = NDF;
    float chiPrim = particle.GetDeviationFromVertex(pv);
    if( (chiPrim < fChiPrimaryCut && pdg < 1000000000) ||
        (chiPrim < fChiPrimaryCutFragments && pdg >= 1000000000))
    {
      if(fTriggerMode) continue;
      primaryTrackList.push_back(nPartSaved);
    }

    if(fTriggerMode && chiPrim > fChiPrimaryMaxCut) continue;
//     if(chiPrim > fChiPrimaryMaxCut) continue;
//     if( chiPrim > 1.e6 ) continue;
    particle.SetId(index);
    particles[nPartSaved] = particle;

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
  if (pdgVector.size() == 1 && pdgVector[0] == -1) return;
  for(unsigned int iPdg = 0; iPdg<pdgVector.size(); iPdg++)
  {
    int pdg = pdgVector[iPdg];
    const int iTrackHisto = fTrackPdgToHistoIndex[pdg];
    if( ! (iTrackHisto <= 0 || iTrackHisto >= NTrackHistoFolders) )
    {
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
      {
        fHistodEdXwithTofTracks[iTrackHisto] -> Fill(pL10, dEdxL10);
        if (isTofm2) {
	  fHistoTofPIDTracks[iTrackHisto][0] -> Fill(pL10, m2tof);
#ifdef __ETAPN_TOF_PLOTS__
	  if (eta > 0) fHistoTofPIDTracks[iTrackHisto][1] -> Fill(pL10, m2tof);
	  else         fHistoTofPIDTracks[iTrackHisto][2] -> Fill(pL10, m2tof);
#endif /* __ETAPN_TOF_PLOTS__ */
	}
        if (isETofm2) fHistoETofPIDTracks[iTrackHisto] -> Fill(pL10, m2Etof);
        
        if(abs(pdg)==11)
        {
          fHistodEdXnSigma[iTrackHisto] -> Fill(momentum, gTrack->nSigmaElectron());
	}
        if(abs(pdg)==211)
        {
          fHistodEdXnSigma[iTrackHisto] -> Fill(momentum, gTrack->nSigmaPion());
          fHistodEdXPull[iTrackHisto] -> Fill(pL10, gTrack->dEdxPull(0.139570, 1, 1));
          fHistodNdXPull[iTrackHisto] -> Fill(pL10, gTrack->dEdxPull(0.139570, 2, 1));
          float betaGamma = TMath::Log10(momentum/0.139570);
          float z = gTrack->dEdxPull(0.139570, fdEdXMode, 1)*gTrack->dEdxError(fdEdXMode);
          fHistodEdXZ[iTrackHisto]->Fill(betaGamma, z);
          
          betaGamma = TMath::Log10(momentum/5.485799e-4);
          z = gTrack->dEdxPullElectron(fdEdXMode)*gTrack->dEdxError(fdEdXMode);
          fHistodEdXZ[1]->Fill(betaGamma, z);
        }
        if(abs(pdg)==321)
        {
          fHistodEdXnSigma[iTrackHisto] -> Fill(momentum, gTrack->nSigmaKaon());
          fHistodEdXPull[iTrackHisto] -> Fill(pL10, gTrack->dEdxPull(0.493677, 1, 1));
          fHistodNdXPull[iTrackHisto] -> Fill(pL10, gTrack->dEdxPull(0.493677, 2, 1));
          float betaGamma = TMath::Log10(momentum/0.493677);
          float z = gTrack->dEdxPull(0.493677, 1, 1)*gTrack->dEdxError();
          fHistodEdXZ[iTrackHisto]->Fill(betaGamma, z);
        }
        if(abs(pdg)==2212)
        {
          fHistodEdXnSigma[iTrackHisto] -> Fill(momentum, gTrack->nSigmaProton());
          fHistodEdXPull[iTrackHisto] -> Fill(pL10, gTrack->dEdxPull(0.938272, 1, 1));
          fHistodNdXPull[iTrackHisto] -> Fill(pL10, gTrack->dEdxPull(0.938272, 2, 1));
          float betaGamma = TMath::Log10(momentum/0.938272);
          float z = gTrack->dEdxPull(0.938272, 1, 1)*gTrack->dEdxError();
          fHistodEdXZ[iTrackHisto]->Fill(betaGamma, z);
        }
        if(abs(pdg)==1000010020)
        {
          fHistodEdXPull[iTrackHisto] -> Fill(pL10, gTrack->dEdxPull(1.876124, 1, 1));
          fHistodNdXPull[iTrackHisto] -> Fill(pL10, gTrack->dEdxPull(1.876124, 2, 1));
          float betaGamma = TMath::Log10(momentum/1.876124);
          float z = gTrack->dEdxPull(1.876124, 1, 1)*gTrack->dEdxError();
          fHistodEdXZ[iTrackHisto]->Fill(betaGamma, z);
        }
        if(abs(pdg)==1000010030)
        {
          fHistodEdXPull[iTrackHisto] -> Fill(pL10, gTrack->dEdxPull(2.809432, 1, 1));
          fHistodNdXPull[iTrackHisto] -> Fill(pL10, gTrack->dEdxPull(2.809432, 2, 1));
          float betaGamma = TMath::Log10(momentum/2.809432);
          float z = gTrack->dEdxPull(2.809432, 1, 1)*gTrack->dEdxError();
          fHistodEdXZ[iTrackHisto]->Fill(betaGamma, z);
        }
        if(abs(pdg)==1000020030)
        {
          fHistodEdXPull[iTrackHisto] -> Fill(pL10, gTrack->dEdxPull(2.809413, 1, 2));
          fHistodNdXPull[iTrackHisto] -> Fill(pL10, gTrack->dEdxPull(2.809413, 2, 2));
          float betaGamma = TMath::Log10(momentum/2.809413);
          float z = gTrack->dEdxPull(2.809413, 1, 2)*gTrack->dEdxError();
          fHistodEdXZ[iTrackHisto]->Fill(betaGamma, z);
        }
        if(abs(pdg)==1000020040)
        {
          fHistodEdXPull[iTrackHisto] -> Fill(pL10, gTrack->dEdxPull(3.728400, 1, 2));
          fHistodNdXPull[iTrackHisto] -> Fill(pL10, gTrack->dEdxPull(3.728400, 2, 2));
          float betaGamma = TMath::Log10(momentum/3.728400);
          float z = gTrack->dEdxPull(3.728400, 1, 2)*gTrack->dEdxError();
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
    if( ! (iTrackHisto <= 0 || iTrackHisto >= NTrackHistoFolders) )
    {
      fHistoMomentumTracks[iTrackHisto] -> Fill(momentum);
      fHistodEdXTracks[iTrackHisto] -> Fill(momentum, gTrack->dEdx()*1.e6);
      if(isTofm2)
      {
        fHistodEdXwithTofTracks[iTrackHisto] -> Fill(momentum, gTrack->dEdx()*1.e6);
        fHistoTofPIDTracks[iTrackHisto][0] -> Fill(pL10, m2tof);
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
  
  KFPVertex primVtx_tmp;
  primVtx_tmp.SetXYZ(picoPV.x(), picoPV.y(), picoPV.z());
  double dx = picoPVError.x();
  double dy = picoPVError.y();
  double dz = picoPVError.z();
  primVtx_tmp.SetCovarianceMatrix( dx*dx, 0, dy*dy, 0, 0, dz*dz );
  primaryVertex = KFVertex(primVtx_tmp);
//   if(!IsGoodPV(primaryVertex)) return 0;
  
  
  std::vector<bool> isPileup;
  if (IsFixedTarget()) {
  KFVertex myPV;
  if(!FindFixedTargetPV(picoDst, myPV, isPileup)) return 0;
  primaryVertex = myPV;
  }
  
//   int nPileup = 0;
//   for(unsigned int i=0; i<isPileup.size(); i++)
//     nPileup += isPileup[i] ? 1 : 0;
//   std::cout << "star pv " << primaryVertex.X() << " " <<
//                              primaryVertex.Y() << " " << 
//                              primaryVertex.Z() << "          " <<
//                              primaryVertex.GetErrX() << " " << 
//                              primaryVertex.GetErrY() << " " << 
//                              primaryVertex.GetErrZ() << std::endl;
//                              
//   std::cout << "my pv   " << myPV.X() << " " <<
//                              myPV.Y() << " " << 
//                              myPV.Z() << "          " <<
//                              myPV.GetErrX() << " " << 
//                              myPV.GetErrY() << " " << 
//                              myPV.GetErrZ() << std::endl;
//   std::cout << "is found     " << int(isPVFound) << std::endl;
//   std::cout << "n tracks " << isPileup.size() << std::endl;
//   std::cout << "n pileup " << nPileup << std::endl;
//   std::cout << "npv      " << (myPV.NDF()+3)/2 << std::endl;
//   int ipv2 = 0;
//   int ipv3 = 0;
  
  Int_t nGlobalTracks = picoDst->numberOfTracks( );
  
  fParticles.resize(nGlobalTracks*10);
  fNHftHits.resize(nGlobalTracks*10);
  fParticlesPdg.resize(nGlobalTracks*10);
  int nPartSaved = 0;
  int nUsedTracks = 0;
  
  fm2TofArray = std::vector<float>(nGlobalTracks*2, -1.0e6f);
  ftrackIdToI  = std::vector<int>(nGlobalTracks*2);
  
//   KFParticle beamSpot;
//   beamSpot.NDF() = -1;
//   beamSpot.Covariance(0,0) = 0.26f;
//   beamSpot.Covariance(1,1) = 0.14f;
//   beamSpot.Covariance(2,2) = 0.20f;
// #ifdef FXT2018
//   beamSpot.X() = 0.007f;
//   beamSpot.Y() = -1.985f;
//   beamSpot.Z() = 200.7f;
// #else
//   beamSpot.X() = -0.46f;
//   beamSpot.Y() = -1.988f;
//   beamSpot.Z() = 200.2f;
// #endif
  
  for (Int_t iTrack = 0; iTrack < nGlobalTracks; iTrack++) 
  {
    StPicoTrack *gTrack = picoDst->track(iTrack);
    
//     if ( (gTrack->status() != 0) && !(gTrack->isPrimary()) ) continue; //TODO
    
    if (! gTrack)            continue;
    if (! gTrack->charge())  continue;
    if (  gTrack->nHitsFit() < 15) continue;
//     if (  gTrack->nHitsFit() < 10) continue;
    if (IsFixedTarget()) {
      if (  gTrack->dEdxError() < 0.01 || gTrack->dEdxError() > 0.15 ) continue;
    } else {
      if (  gTrack->dEdxError() < 0.04 || gTrack->dEdxError() > 0.12 ) continue;
    }
//     if (  gTrack->dEdxError() < 0.01 || gTrack->dEdxError() > 0.15 ) continue;
//     if (  gTrack->dEdxError() < 0.04 || gTrack->dEdxError() > 0.25 ) continue;
    const UInt_t index = gTrack->id();
    
    if (IsFixedTarget()) {
      if(isPileup[index]) continue;
    }
    //PiDCUT    if (  gTrack->dEdxError() < 0.04 || gTrack->dEdxError() > 0.12 ) continue;
    //    if (  gTrack->dEdxError() < 0.01 || gTrack->dEdxError() > 0.25 ) continue;
    if (  gTrack->dEdxError() < 0.01 || gTrack->dEdxError() > 0.16 ) continue;
    if (  gTrack->status() && !gTrack->isPrimary()) continue;
    
    if(index >= ftrackIdToI.size()) ftrackIdToI.resize(index+1);
    ftrackIdToI[index] = iTrack;
    
    int nHftHitsInTrack = 0;
    if(gTrack->hasPxl1Hit()) nHftHitsInTrack++;
    if(gTrack->hasPxl2Hit()) nHftHitsInTrack++;
    if(gTrack->hasIstHit()) nHftHitsInTrack++;
//       if(gTrack->hasSstHit()) nHftHitsInTrack++;
    
    //FIXME temporary solution!!!
    nHftHitsInTrack = gTrack->nHitsFit();
#ifdef __USE_HFT__  
    if(fCollectTrackHistograms) fTrackHistograms[0]->Fill(nHftHitsInTrack);
//     if(fUseHFTTracksOnly && nHftHitsInTrack < 3) continue;
    if(fUseHFTTracksOnly && !gTrack->hasIstHit()) continue;
#endif /*  __USE_HFT__ */        
    StPicoTrackCovMatrix *cov = picoDst->trackCovMatrix(iTrack);
    const StDcaGeometry &dcaG = cov->dcaGeometry();
    if (StMuDst::dca3Dmax() > 0) {
      // Cut large Dca
      THelixTrack t = dcaG.thelix();
      Double_t xyz[3] = {primaryVertex.X(), primaryVertex.Y(), primaryVertex.Z()};
      Double_t dca3D = t.Dca(xyz);
      if (dca3D > StMuDst::dca3Dmax()) continue;
    }
    Int_t q = 1; if (gTrack->charge() < 0) q = -1;
    KFPTrack track;
    if( !GetTrack(dcaG, track, q, index) ) continue;

//     const float dx = track.GetX() - beamSpot.X();
//     const float dy = track.GetY() - beamSpot.Y();
//     const float dz = track.GetZ() - beamSpot.Z();
//     const float dl2 = dx*dx + dy*dy + dz*dz;
//     if(dl2 > 100*100) continue;
    
//     KFParticle ppp(track, 211);
//     const float ccc = ppp.GetDeviationFromVertex(primaryVertex);
//     if(ccc < 18) ipv2++;
//     const float ccc2 = ppp.GetDeviationFromVertex(myPV);
//     if(ccc2 < 18) ipv3++;
    
    Double_t pL10 = (track.GetP() > 0) ? TMath::Log10(track.GetP()) : -2;
    Double_t dEdxL10 = (gTrack->dEdx() > 0) ? TMath::Log10(gTrack->dEdx()) : dEdxL10min;
    Double_t dNdxL10 = (gTrack->dNdx() > 0) ? TMath::Log10(gTrack->dNdx()) : dNdxL10min;
#ifdef __ETAPN_TOF_PLOTS__
    Double_t eta = gTrack->gMom().Eta();
#endif /* __ETAPN_TOF_PLOTS__ */
    if(fCollectTrackHistograms)
    {
      fTrackHistograms2D[0]->Fill(pL10, dEdxL10);
      if(q>0) fTrackHistograms2D[1]->Fill(pL10, dEdxL10);
      else    fTrackHistograms2D[2]->Fill(pL10, dEdxL10);  
      fTrackHistograms2D[9]->Fill(pL10, dNdxL10);
      if(q>0) fTrackHistograms2D[10]->Fill(pL10, dNdxL10);
      else    fTrackHistograms2D[11]->Fill(pL10, dNdxL10);  
      TVector3 t(track.GetPx(),track.GetPy(),track.GetPz());
      if (gTrack->isPrimary())
	fTrackHistograms2D[8]->Fill(TMath::Log10(t.Perp()), t.PseudoRapidity());
      fTrackHistograms2D[13]->Fill(TMath::Log10(t.Perp()), t.PseudoRapidity());
    }
    
    double m2tof = -1.e6;
    bool isTofm2 = false;
    double m2Etof = -1.e6;
    bool isETofm2 = false;
#if 0 // <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
    if(gTrack->bTofPidTraitsIndex() >= 0)
    {
      const StPicoBTofPidTraits* btofPid = picoDst->btofPidTraits(gTrack->bTofPidTraitsIndex());
      double betaTof2 = btofPid->btofBeta() * btofPid->btofBeta();
      if(fabs(betaTof2) > 1.e-6)
	{
	  m2tof = track.GetP()*track.GetP()*(1./betaTof2 - 1.);
	  if(index >= fm2TofArray.size()) fm2TofArray.resize(index+1);
	  fm2TofArray[index] = m2tof;
	  isTofm2 = true;
	}
      if(fCollectTrackHistograms)
      {
        fTrackHistograms2D[3]->Fill(pL10, dEdxL10);
        fTrackHistograms2D[12]->Fill(pL10, dNdxL10);
	fTrackHistograms2D[4]->Fill(pL10, m2tof);
#ifdef __ETAPN_TOF_PLOTS__
	if (eta > 0) fTrackHistograms2D[15]->Fill(pL10, m2tof);
	else         fTrackHistograms2D[16]->Fill(pL10, m2tof);
#endif /* __ETAPN_TOF_PLOTS__ */
      }
    }

    if(gTrack->eTofPidTraitsIndex() >= 0)
    {
      const StPicoETofPidTraits* etofPid = picoDst->etofPidTraits(gTrack->eTofPidTraitsIndex());
      double betaTof2 = etofPid->beta() * etofPid->beta();
      if(fabs(betaTof2) > 1.e-6)
      {
        m2tof = track.GetP()*track.GetP()*(1./betaTof2 - 1.);
        isTofm2 = true;
      }
      if(fCollectTrackHistograms && isTofm2)
      {
	fTrackHistograms2D[9]->Fill(track.GetP(), m2tof);
        fTrackHistograms2D[10]->Fill(gTrack->dEdx(), m2tof);
        m2Etof = track.GetP()*track.GetP()*(1./betaTof2 - 1.);
        isETofm2 = true;
      }
    }
      if(fCollectTrackHistograms && isETofm2) 
	{
        fTrackHistograms2D[3]->Fill(pL10, dEdxL10);
        fTrackHistograms2D[12]->Fill(pL10, dNdxL10);
        fTrackHistograms2D[14]->Fill(pL10, m2Etof);
      }
    if(fCollectTrackHistograms && (isTofm2 || isETofm2))
      {
	Double_t pL10 = (track.GetP() > 0) ? TMath::Log10(track.GetP()) : -2;
	Double_t dEdxL10 = (gTrack->dEdx() > 0) ? TMath::Log10(gTrack->dEdx()) : dEdxL10min;
	Double_t dNdxL10 = (gTrack->dNdx() > 0) ? TMath::Log10(gTrack->dNdx()) : dNdxL10min;
        fTrackHistograms2D[3]->Fill(pL10, dEdxL10);
        fTrackHistograms2D[12]->Fill(pL10, dNdxL10);
        if (isTofm2)  {
	  fTrackHistograms2D[4]->Fill(pL10, m2tof);
#ifdef __ETAPN_TOF_PLOTS__
	  if (eta > 0) fTrackHistograms2D[15]->Fill(pL10, m2tof);
	  else         fTrackHistograms2D[16]->Fill(pL10, m2tof);
#endif /* __ETAPN_TOF_PLOTS__ */
	}
        if (isETofm2) fTrackHistograms2D[14]->Fill(pL10, m2Etof);
    }
#endif // <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
#if 0    
    vector<int> totalPDG = GetPID(m2tof, track.GetP(), q, gTrack->dEdx(), dEdXPull, isTofm2, index);
#else
    StPidStatus PiD(gTrack);
    vector<int> totalPDG = PiD.GetPDG();
#endif    
    int nPartSaved0 = nPartSaved;
    unsigned int nPrimaryTracks = primaryTrackList.size();
    Int_t NDF = 2*gTrack->nHitsFit() - 5;
    Float_t Chi2 = gTrack->chi2()*NDF;
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
    fTrackHistograms2D[7]->Fill( nPrimary, (nUsedTracks - nPrimary) );
    Double_t nPL10 = (primaryTrackList.size() > 0) ? TMath::Log10(primaryTrackList.size()) : -1;
    Double_t nGL10 = (nUsedTracks > 0) ? TMath::Log10(nUsedTracks) : -1;
    fTrackHistograms2D[7]->Fill( nGL10, nPL10);
  }
  
//   std::cout << "n star primary " << nPrimary << "     " << ipv2 << "   " << ipv3 << std::endl;
//   std::cin.get();
  
  if( fCleanLowPVTrackEvents && ( 10*nPrimary < (nUsedTracks - nPrimary) ) ) return 0;  
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
  if (! IsFixedTarget()) {
    if( fCleanLowPVTrackEvents && primaryVertex.GetR() > 1.5 ) return 0;
    //   14 GeV
    //   double nSecLimit = 15.4905 + 1.01890*primaryTrackList.size();
    //   double nSec = (nUsedTracks - primaryTrackList.size());
    //   if( nSec > nSecLimit ) return 0; 
  } else {    
    // //   fxt
    if( fCleanLowPVTrackEvents && !(primaryVertex.Z() > 196. && primaryVertex.Z() < 204.) ) return 0;
    if( fCleanLowPVTrackEvents && !(primaryVertex.X() > -2.5 && primaryVertex.X() < 2.  ) ) return 0;
    if( fCleanLowPVTrackEvents && !(primaryVertex.Y() > -4.  && primaryVertex.Y() < 0.  ) ) return 0;
  }
  const Double_t field = picoEvent->bField();  
  SetField(field);
  
  CleanPV();
  InitParticles();
  
  //read PV
  //   vector<int> emptyPrimaryList(0);
  //   AddPV(primaryVertex, emptyPrimaryList);
  AddPV(primaryVertex, primaryTrackList);
  if(fCollectTrackHistograms)
    {
    fTrackHistograms[1]->Fill(sqrt(dx*dx + dy*dy));
    Double_t nL10 = (nPartSaved > 0) ? TMath::Log10(nPartSaved) : -1;
    fTrackHistograms2D[5]->Fill( nL10, sqrt(dx*dx + dy*dy) );
    Double_t npL10 = (primaryTrackList.size()) ? TMath::Log10(primaryTrackList.size()) : -1;
    fTrackHistograms2D[6]->Fill( npL10, sqrt(dx*dx + dy*dy) );
    }  
  //reconstruct short-lived particles
  ReconstructParticles();

  if (fPidQA) {
    PidQA(picoDst);
  }
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
  int bestPV=-1;
  double dx = 0., dy = 0., dz = 0.;
  for(unsigned int iPV=0; iPV<muDst->numberOfPrimaryVertices(); iPV++) 
  {
    StMuPrimaryVertex *Vtx = muDst->primaryVertex(iPV);
    if(!Vtx) continue;
    if (bestRank < Vtx->ranking()) {
      bestRank = Vtx->ranking();
      bestPV = iPV;
    }
    else continue;
    
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
  
  ftrackIdToI = std::vector<int>(nGlobalTracks*2);
  
  for (Int_t iTrack = 0; iTrack < nGlobalTracks; iTrack++) 
  {
    StMuTrack *gTrack = muDst->globalTracks(iTrack);
    if (! gTrack)            continue;
    if (! gTrack->charge())  continue;
    if (  gTrack->flag() < 100 ||  gTrack->flag()%100 == 11) continue; // bad fit or short track pointing to EEMC
    if (  gTrack->flag() > 1000) continue;  // pile up track in TPC
    if (  gTrack->nHitsFit() < 15) continue;
    //PiDCUT    if (  gTrack->probPidTraits().dEdxErrorFit() < 0.04 || gTrack->probPidTraits().dEdxErrorFit() > 0.12 ) continue;
    //    if (  gTrack->probPidTraits().dEdxErrorFit() < 0.01 || gTrack->probPidTraits().dEdxErrorFit() > 0.25 ) continue;
    if (  gTrack->probPidTraits().dEdxErrorFit() < 0.01 || gTrack->probPidTraits().dEdxErrorFit() > 0.16 ) continue;
    int nHftHitsInTrack = gTrack->nHitsFit(kIstId) + gTrack->nHitsFit(kSsdId) + gTrack->nHitsFit(kPxlId);
#ifdef __USE_HFT__
    if(fCollectTrackHistograms) fTrackHistograms[0]->Fill(nHftHitsInTrack);
    if(fUseHFTTracksOnly && nHftHitsInTrack < 3) continue;
#endif /* __USE_HFT__ */
    const UInt_t index = gTrack->id();
    
    if(index >= ftrackIdToI.size()) ftrackIdToI.resize(index+1);
    ftrackIdToI[index] = iTrack;
    
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
    if (StMuDst::dca3Dmax() > 0) {
      // Cut large Dca
      THelixTrack t = dcaG->thelix();
      Double_t xyz[3] = {primaryVertex.X(), primaryVertex.Y(), primaryVertex.Z()};
      Double_t dca3D = t.Dca(xyz);
      if (dca3D > StMuDst::dca3Dmax()) continue;
    }
      
    KFPTrack track;
    if( !GetTrack(*dcaG, track, q, index) ) continue;
#endif

    if(fCollectTrackHistograms)
    {
      Double_t pL10 = (track.GetP() > 0) ? TMath::Log10(track.GetP()) : -2;
      Double_t dEdxL10 = (gTrack->dEdx() > 0) ? TMath::Log10(gTrack->dEdx()*1e6) : 0.0;
      Double_t dNdxL10 = (gTrack->probPidTraits().dNdxFit() > 0) ? TMath::Log10(gTrack->probPidTraits().dNdxFit()*1e6) : 0.5;
      fTrackHistograms2D[0]->Fill(pL10, dEdxL10);
      if(q>0) fTrackHistograms2D[1]->Fill(pL10, dEdxL10);
      else    fTrackHistograms2D[2]->Fill(pL10, dEdxL10);
      fTrackHistograms2D[9]->Fill(pL10, dNdxL10);
      if(q>0) fTrackHistograms2D[10]->Fill(pL10, dNdxL10);
      else    fTrackHistograms2D[11]->Fill(pL10, dNdxL10);
    }
#if 0 // <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<    
    const StMuBTofPidTraits &btofPid = gTrack->btofPidTraits();
    double timeTof = btofPid.timeOfFlight();
    double m2tof = -1.e6;
    bool isTofm2 = false;
    if(timeTof > 0)
    {
      Double_t beta = btofPid.beta();
      Double_t beta2 = beta*beta;
      if(beta2 > 1e-6) {
	m2tof = track.GetP()*track.GetP()*(1./beta2 - 1.);
	isTofm2 = true;
      }
    }
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
	
        fTrackHistograms2D[3]->Fill(pL10, dEdxL10);
        fTrackHistograms2D[12]->Fill(pL10, dNdxL10);
        if (isTofm2)  {
	  fTrackHistograms2D[4]->Fill(pL10, m2tof);
#ifdef __ETAPN_TOF_PLOTS__
	  if (eta > 0) fTrackHistograms2D[15]->Fill(pL10, m2tof);
	  else         fTrackHistograms2D[16]->Fill(pL10, m2tof);
#endif /* __ETAPN_TOF_PLOTS__ */
	}
        if (isETofm2) fTrackHistograms2D[14]->Fill(pL10, m2Etof);
      }
#endif // <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
    StPidStatus PiD(gTrack);
    vector<int> totalPDG = PiD.GetPDG();
    int nPartSaved0 = nPartSaved;
    unsigned int nPrimaryTracks = primaryTrackList.size();
#ifdef __kfpAtFirstHit__
    AddTrackToParticleList(track, nHftHitsInTrack, index, totalPDG, primaryVertex, primaryTrackList, fNHftHits, fParticlesPdg, fParticles, nPartSaved, &trackAtLastHit, &fParticlesAtLastHit);
#else
    Int_t NDF = 2*gTrack->nHitsFit() - 5;
    Float_t Chi2 = gTrack->chi2()*NDF;
    AddTrackToParticleList(track, nHftHitsInTrack, index, totalPDG, primaryVertex, primaryTrackList, fNHftHits, fParticlesPdg, fParticles, nPartSaved, 0, 0, Chi2, NDF);         
#endif
    
    if(nPartSaved > nPartSaved0)
      mcIndices[index] = mcIndex;
#if 0 // <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
    //fill PID histograms if they are created
    //Histograms are filled for secondary tracks only!!!
    if(fCollectPIDHistograms && (nPrimaryTracks == primaryTrackList.size())) 
      {
	vector<int> selectedPdg;
	for(int iPdg = nPartSaved0; iPdg<nPartSaved; iPdg++)
	  selectedPdg.push_back(fParticlesPdg[iPdg]);
	FillPIDHistograms(gTrack, selectedPdg, isTofm2, m2tof);
      }
#endif // <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
    
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
    fTrackHistograms2D[7]->Fill( nPrimary, (nUsedTracks - nPrimary) );
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
//   if( fCleanLowPVTrackEvents && fabs(primaryVertex.Z()) > 75. ) return 0;
  }

#ifdef __MagFieldCorrection__
  //TODO remove coefficient !!!!
  const Double_t field = muDst->event()->magneticField() *  fgMagScaleFactor;
#else
  const Double_t field = muDst->event()->magneticField();
#endif
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
    Double_t ngL10 = (nPartSaved > 0) ? TMath::Log10(nPartSaved) : -1;
    fTrackHistograms2D[5]->Fill( ngL10, sqrt(dx*dx + dy*dy) );
    Double_t npL10 = (nPartSaved > 0) ? TMath::Log10(primaryTrackList.size()) : -1;
    fTrackHistograms2D[6]->Fill( npL10, sqrt(dx*dx + dy*dy) );
  }  
  //reconstruct short-lived particles
  ReconstructParticles();
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
  return 1;
}

struct pvIndex {
  pvIndex(float d, int j):chi(d), i(j) {}
  float chi;
  int i;
};

static bool sortPVIndices(const pvIndex& a, const pvIndex& b) { return a.chi < b.chi; }

bool StKFParticleInterface::FitPV(KFVertex& pv, bool isFirstSeed, const KFPTrackVector& tracks,
                                  std::vector<int>& pvTrackIndices, std::vector<int>& leftTrackIndices)
{
  std::vector<pvIndex> candidateIndices;
  candidateIndices.reserve(tracks.Size());

  pvTrackIndices.clear();
  pvTrackIndices.reserve(tracks.Size());

  leftTrackIndices.clear();
  leftTrackIndices.reserve(tracks.Size());

  KFParticleSIMD trackSIMD;
  KFParticleSIMD pvSIMD(pv);
  for(int iTrack=0; iTrack < tracks.Size(); iTrack+=float_vLen) {

    trackSIMD.Load(tracks, iTrack);

//     const float_v dz = trackSIMD.Z() - pvSIMD.Z();
//     const float_v sigmaZ2 = trackSIMD.Covariance(2,2) + pvSIMD.Covariance(2,2);
//     float_m active = dz*dz <= sigmaZ2*1000.f;
//     if(active.isEmpty()) continue;
    
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

//     for(int iCandidate=0; iCandidate<nCandidates; iCandidate++) {
//       if(vFlags[iCandidate]) {
//         pvTrackIndices.push_back(candidateIndices[iCandidate].i);
//       }
//       else {
//         leftTrackIndices.push_back(candidateIndices[iCandidate].i);
//       }
//     }
    
    pvSIMD = KFParticleSIMD(pv);

    for(int iTrack=0; iTrack < tracks.Size(); iTrack+=float_vLen) {
      trackSIMD.Load(tracks, iTrack);
    
//       const float_v dz = trackSIMD.Z() - pvSIMD.Z();
//       const float_v sigmaZ2 = trackSIMD.Covariance(2,2) + pvSIMD.Covariance(2,2);
//       float_m active = dz*dz <= sigmaZ2*1000.f;
//       if(active.isEmpty()) continue;
    
      const float_v deviation = trackSIMD.GetDeviationFromVertex(pvSIMD);
      
      for(int iV=0; iV<float_vLen; iV++){
        const int iTr = iTrack + iV;
        if(iTr >= tracks.Size()) break;
      
        if((deviation[iV]==deviation[iV]) && (deviation[iV] >= 0.f && deviation[iV] < 18.f))
          pvTrackIndices.push_back(iTr);
        else
          leftTrackIndices.push_back(iTr);
      }
    }
    
    if( (isFirstSeed && primaryVertex.NDF() >= 1) ||
        (!isFirstSeed && primaryVertex.NDF() > 7)) return true;
//     if( (isFirstSeed && pvTrackIndices.size() > 2) ||
//         (!isFirstSeed && pvTrackIndices.size() > 7)) return true;
  }
  
  return false;
}

bool StKFParticleInterface::FindFixedTargetPV(StPicoDst* picoDst, KFVertex& pv, std::vector<bool>& isPileup)
{
//   std::clock_t start = std::clock();
  
  KFParticle beamSpot;
  beamSpot.NDF() = -1;
  beamSpot.Covariance(0,0) = 0.26f;
  beamSpot.Covariance(1,1) = 0.14f;
  beamSpot.Covariance(2,2) = 0.20f;
  if (IsFixedTarget2018()) {
    beamSpot.X() = 0.007f;
    beamSpot.Y() = -1.985f;
    beamSpot.Z() = 200.7f;
  } else {
    beamSpot.X() = -0.5f;
    beamSpot.Y() = -2.03f;
    beamSpot.Z() = 200.34f;
  }
  
  KFPTrackVector tracks;
  tracks.Resize(picoDst->numberOfTracks());
  
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
    
//     if(track.GetX()*track.GetX() + track.GetY()*track.GetY() > 2500.f) continue;

//     constexpr int index2[9] = { 6,7,8, 10,11,12, 15,16,17 };
//     constexpr int index4[6] = { 9, 13,14, 18,19,20 };
// 
//     constexpr float MFScale =  fgMagScaleFactor;
//     track.SetPx( track.GetPx()*MFScale );
//     track.SetPy( track.GetPy()*MFScale );
//     track.SetPz( track.GetPz()*MFScale );
//     for(int iIndex=0; iIndex<9; iIndex++){
//       const int iC = index2[iIndex];
//       track.SetCovariance( iC, track.GetCovariance(iC)*MFScale );
//     }
//     for(int iIndex=0; iIndex<6; iIndex++){
//       const int iC = index4[iIndex];
//       track.SetCovariance( iC, track.GetCovariance(iC)*MFScale*MFScale );
//     }

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
  
  bool isPVFound = false;
  int nPV = 0;
  int nPrimary = 0;
  int nPileup = 0;
  
  while(beamSpot.Z() > -200.f && tracks.Size() > 5) {
    
    std::vector<int> pvTrackIndices;
    std::vector<int> leftTrackIndices;
    
    KFVertex primaryVertex = beamSpot;
    const bool isFirstSeed = (beamSpot.Z() > 200.f);
    beamSpot.Z() -= 6.1f;

    if(! FitPV(primaryVertex, isFirstSeed, tracks, pvTrackIndices, leftTrackIndices) ) continue;
    
    if(isFirstSeed) {
      isPVFound = true;
      pv = primaryVertex;
    }
    else {
      for(unsigned int iIndex=0; iIndex<pvTrackIndices.size(); iIndex++) {
        const int index = tracks.Id()[pvTrackIndices[iIndex]];
        isPileup[index] = true;
      }
    }

    KFPTrackVector tracksLeft;
    tracksLeft.Resize(leftTrackIndices.size());
    
    for(unsigned int iLeft=0; iLeft<leftTrackIndices.size(); iLeft++) {
      int iTrack = leftTrackIndices[iLeft];
      for(int iP=0; iP<6; iP++)
        tracksLeft.SetParameter(tracks.Parameter(iP)[iTrack], iP, iLeft);
      for(int iC=0; iC<21; iC++)
        tracksLeft.SetCovariance(tracks.Covariance(iC)[iTrack], iC, iLeft);
      tracksLeft.SetId(tracks.Id()[iTrack], iLeft);
      tracksLeft.SetQ(tracks.Q()[iTrack], iLeft);
    }

    tracks = tracksLeft;
    
    if(fCollectPVHistograms) {
      fPVHistograms[0]->Fill(primaryVertex.X());
      fPVHistograms[1]->Fill(primaryVertex.Y());
      fPVHistograms[2]->Fill(primaryVertex.GetR());
      fPVHistograms[3]->Fill(primaryVertex.Z());
      fPVHistograms[4]->Fill(pvTrackIndices.size());
      
      if(isFirstSeed) {
        fPVHistograms[5]->Fill(pvTrackIndices.size());
        nPrimary += pvTrackIndices.size();
      } else {
        fPVHistograms[6]->Fill(pvTrackIndices.size());
        nPileup += pvTrackIndices.size();
      }
      
      fPVHistograms2D[0]->Fill(primaryVertex.X(), primaryVertex.Y());
      fPVHistograms2D[1]->Fill(primaryVertex.Z(), primaryVertex.GetR());
      
      nPV++;
    }
  }
  
  if(fCollectPVHistograms) {
    fPVHistograms[ 7]->Fill(nPV);
    fPVHistograms[ 8]->Fill(float(nPrimary)/float(NTracks));
    fPVHistograms[ 9]->Fill(float(nPileup)/float(NTracks));
    fPVHistograms[10]->Fill(float(NTracks - nPrimary - nPileup)/float(NTracks));
    
    for(int iTrack=0; iTrack<tracks.Size(); iTrack++) 
      fPVHistograms2D[3]->Fill(tracks.Z()[iTrack], 
        sqrt(tracks.X()[iTrack]*tracks.X()[iTrack] + tracks.Y()[iTrack]*tracks.Y()[iTrack]));
  }
//   std::clock_t end = std::clock();
//   double time = double( end - start ) / (double) CLOCKS_PER_SEC * 1000.;
//   std::cout << "PV time: " << time << " ms " << std::endl;
  
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
      Title += " Armenteros";
      histo[d] = new TH2F("Armenteros",Title, 50, -1, 1, 100,  0, 0.5);
      histo[d]->GetXaxis()->SetTitle("#alpha (p_{L}^{+}-p_{L}^{-})/(p_{L}^{+}+p_{L}^{-})");
      histo[d]->GetYaxis()->SetTitle("q_{t} [GeV/c]");
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
      StPidStatus PiD(gTrack); 
      if (PiD.PiDStatus < 0) continue;
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
      StPidStatus PiD1(gTrack1); 
      if (PiD1.PiDStatus < 0) continue;
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
      StPidStatus PiD(gTrack); 
      if (PiD.PiDStatus < 0) continue;
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
      StPidStatus PiD1(gTrack1); 
      if (PiD1.PiDStatus < 0) continue;
      FillPidQA(&PiD1, p1.GetPDG(), particle->GetPDG());
    }
  }
  return kTRUE;
}
//________________________________________________________________________________
Bool_t StKFParticleInterface::FillPidQA(StPidStatus* PiD, Int_t PDG, Int_t PDGParent) {
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
  static TH2F *hist[Ndecays+1][Nparticles][StPidStatus::kTotal+1][5] = {0}; // kTotal for Tpc & BTof
  if (! hist[0][0][StPidStatus::kFit][0]) {
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
	for (Int_t k = 1; k < StPidStatus::kTotal + 1; k++) {
	  if (k == StPidStatus::kFit) {
	    hist[d][p][k][0] = new TH2F("dEdx",Form("dE/dx_{%s} / dEdModel prediction for I_{fit} versus log_{10}(#beta #gamma)",StPidStatus::fgPiDStatusNames[k]), 1000,-1,4,500,-0.5,0.5);
	    hist[d][p][k][1] = new TH2F("PulldEdx",Form("(dE/dx_{%s} / dEdModel)/#sigma  versus log_{10}(#beta #gamma)",StPidStatus::fgPiDStatusNames[k]),          1000,-1,4,600,-3,3);
	    hist[d][p][k][2] = new TH2F("PullCdEdx",Form("(dE/dx_{%s} / dEdModel)/#sigma Corrected versus log_{10}(#beta #gamma)",StPidStatus::fgPiDStatusNames[k]),1000,-1,4,600,-3,3);
	    for (Int_t i = 0; i < 3; i++) hist[d][p][k][i]->SetXTitle("log_{10}(#beta #gamma)");
	  } else if (k == StPidStatus::kTotal) {
	    hist[d][p][k][0] = new TH2F("dEdxBTof",Form("dE/dx_{%s} / dEdModel prediction for I_{fit} versus log_{10}(#beta #gamma)a with |sigmaBTOF| < 3",StPidStatus::fgPiDStatusNames[k]), 1000,-1,4,500,-0.5,0.5);
	    hist[d][p][k][1] = new TH2F("PulldEdxBTof",Form("(dE/dx_{%s} / dEdModel)/#sigma  versus log_{10}(#beta #gamma)a with |sigmaBTOF| < 3",StPidStatus::fgPiDStatusNames[k]),          1000,-1,4,600,-3,3);
	    hist[d][p][k][2] = new TH2F("PullCdEdxBTof",Form("(dE/dx_{%s} / dEdModel)/#sigma Corrected versus log_{10}(#beta #gamma)a with |sigmaBTOF| < 3",StPidStatus::fgPiDStatusNames[k]),1000,-1,4,600,-3,3);
	    for (Int_t i = 0; i < 3; i++) hist[d][p][k][i]->SetXTitle("log_{10}(#beta #gamma)");
	  } else if (k == StPidStatus::kBTof) {
	    hist[d][p][k][0] = new TH2F("dM2BTof","dM^{2} from BTof versus log_{10}(#beta #gamma)"                              ,1000,-1,4,400,-0.2,0.2);
	    hist[d][p][k][1] = new TH2F("dM2BTofPull","dM^{2}/#sigma dM^ {2} from BTof versus log_{10}(#beta #gamma)"           ,1000,-1,4,600,-6.0,6.0);
	    hist[d][p][k][2] = new TH2F("dM2BTofPullC","dM^{2}/#sigma dM^ {2} corrected from BTof versus log_{10}(#beta #gamma)",1000,-1,4,600,-6.0,6.0);
	    hist[d][p][k][3] = new TH2F("PullBTof","nSigma BTof versus log_{10}(#beta #gamma)"                                  ,1000,-1,4,600,-3,3);
	    for (Int_t i = 0; i < 4; i++) hist[d][p][k][i]->SetXTitle("log_{10}(#beta #gamma)");
	  } else if (k == StPidStatus::kETof) {
#if 0
	    hist[d][p][k][0] = new TH2F("dM2ETof","dM^{2} from ETof versus log_{10}(#beta #gamma)"                              ,1000,-1,4,400,-0.2,0.2);
	    hist[d][p][k][1] = new TH2F("dM2ETofPull","dM^{2}/#sigma dM^ {2} from ETof versus log_{10}(#beta #gamma)"           ,1000,-1,4,600,-6.0,6.0);
	    hist[d][p][k][2] = new TH2F("dM2ETofPullC","dM^{2}/#sigma dM^ {2} corrected from ETof versus log_{10}(#beta #gamma)",1000,-1,4,600,-6.0,6.0);
	    hist[d][p][k][3] = new TH2F("PullETof","nSigma ETof versus log_{10}(#beta #gamma)"                                  ,1000,-1,4,600,-3,3);
	    for (Int_t i = 0; i < 4; i++) hist[d][p][k][i]->SetXTitle("log_{10}(#beta #gamma)");
#endif
	  } else if (k == StPidStatus::kBEmc) {
	    hist[d][p][k][0] = new TH2F("BemcEoverP","E/P in BEMC versus log_{10} P"                                            ,100,-0.25,1.75,100,0.0,10.0);
	    hist[d][p][k][0]->SetXTitle("log_{10}P");
	  } else if (k == StPidStatus::kMtd) {
	    hist[d][p][k][0] = new TH2F("MtdYdZ","Mtd dY vesus dZ"                                            ,100,-50,50,100,-100,100);
	    hist[d][p][k][1] = new TH2F("MtdTP","Mtd dT vesus log{10} P"                                      ,100,-1.,5.,400,-2000,2000);
	  }
	}
      }
    }
  }
  if (! PiD->fFit()) return kFALSE;
  Double_t pMom = PiD->g3.Mag();
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
  for (Int_t p = 0; p < NparticlesA; p++) {
    if (PDG != particles[p].pdg) continue;
    Int_t l = particles[p].code;
#if 0
    Int_t pdg = particles[p].pdg;
    //      Double_t M = StProbPidTraits::mPidParticleDefinitions[l]->mass();
    auto M =  TDatabasePDG::Instance()->GetParticle(pdg)->Mass();
    auto q =  TDatabasePDG::Instance()->GetParticle(pdg)->Charge()/3.;
#endif
    Double_t bgL10 = PiD->bghyp[l];
    for (Int_t k = 1; k < StPidStatus::kTotal + 1; k++) {
      if (! hist[d][p][k][0]) continue;
      if (k < StPidStatus::kTotal) {
	if (! PiD->Status(k)) continue;
      } else {
	if (! PiD->Status(StPidStatus::kBTof)) continue; 
      }
      if (k == StPidStatus::kBEmc) {
	hist[d][p][k][0]->Fill(TMath::Log10(pMom), PiD->fBEmc()->bemcE()/pMom);
      } else if (k == StPidStatus::kMtd) {
	hist[d][p][k][0]->Fill(PiD->fMtd()->PiD()->deltaZ(), PiD->fMtd()->PiD()->deltaY());
	hist[d][p][k][1]->Fill(pL10, PiD->fMtd()->deltaTimeOfFlight());
      } else if (k == StPidStatus::kTotal) {
	if (TMath::Abs(PiD->Status(StPidStatus::kBTof)->PullC[l]) < StPidStatus::fgSigmaCut) {
	  hist[d][p][k][0]->Fill(bgL10, PiD->Status(StPidStatus::kFit)->dev[l]);
	  hist[d][p][k][1]->Fill(bgL10, PiD->Status(StPidStatus::kFit)->devS[l]);
	  hist[d][p][k][2]->Fill(bgL10, PiD->Status(StPidStatus::kFit)->PullC[l]);
	}
      } else {
	hist[d][p][k][0]->Fill(bgL10, PiD->Status(k)->dev[l]);
	hist[d][p][k][1]->Fill(bgL10, PiD->Status(k)->devS[l]);
	hist[d][p][k][2]->Fill(bgL10, PiD->Status(k)->PullC[l]);
	if (k == StPidStatus::kBTof) {
	  hist[d][p][k][3]->Fill(bgL10, PiD->fBTof()->Sigma(l));
	}
      }
    }
  }
  return kTRUE;
}
