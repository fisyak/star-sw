#ifndef StKFParticleInterface_H
#define StKFParticleInterface_H
#include <vector>
#include <map>

#include "KFParticle.h"
#include "TObject.h"
#include "StMuDSTMaker/COMMON/StMuTrack.h"
#include "TVector3.h"

class KFParticleTopoReconstructor;
class KFParticleFinder;
class KFTopoPerformance;
class KFVertex;
class StPicoDst;
class StPicoTrack;
class StMuTrack;
class KFMCTrack;
class StMuDst;
class StDcaGeometry;
class KFPTrack;
class KFPTrackVector;
class TH1F;
class TH2F;

class StTrackCombPiD;
class StKFParticleInterface: public TObject
{
 public:
   
  StKFParticleInterface();
  virtual ~StKFParticleInterface();
  
  void InitParticles();
#ifdef __kfpAtFirstHit__
  void InitParticlesAtFirstAndLastHit();
#endif
  void ReconstructParticles();
  void ReconstructTopology();
  
  const std::vector<KFParticle> &GetParticles() const;
  void RemoveParticle(const int iParticle);
  const std::vector<KFParticle>* GetSecondaryCandidates() const;                      // Get secondary particles with the mass constraint
  const std::vector<KFParticle>& GetSecondaryK0()         const;
  const std::vector<KFParticle>& GetSecondaryLambda()     const;
  const std::vector<KFParticle>& GetSecondaryAntiLambda() const;
  const std::vector<KFParticle>& GetSecondaryGamma()      const;
  const std::vector<KFParticle>& GetSecondaryPi0()        const;
  const std::vector< std::vector<KFParticle> >* GetPrimaryCandidates() const;         // Get primary particles with the mass constraint
  const std::vector< std::vector<KFParticle> >* GetPrimaryTopoCandidates() const;     // Get primary particles with the topologigal constraint
  const std::vector< std::vector<KFParticle> >* GetPrimaryTopoMassCandidates() const; // Get primary particles with the topologigal and mass constraint
  void SetParticles(std::vector<KFParticle>& particles)
  {
    fParticles = particles;
    if(fParticlesPdg.size() != fParticles.size())
    {
      fParticlesPdg.clear();
      fParticlesPdg.resize(fParticles.size(), -1);
    }
  }
  void SetParticlesPdg(std::vector<int>& pdg) { fParticlesPdg = pdg;}
  void SetHftHits(std::vector<int>& nHftHits) { fNHftHits = nHftHits; }
  
  void SetField(float field);
  void SetBeamLine(KFParticle& p);
  void SetBeamSpot(const TString beamSpotMode = "");
  
  void CleanPV();
  void AddPV(const KFVertex &pv, const std::vector<int> &tracks);
  void AddPV(const KFVertex &pv);
  void AddParticle(const KFParticle& p);
  void AddCandidate(const KFParticle& candidate, int iPV = -1);
  void AddDecayToReconstructionList(Int_t pdg);
  const KFParticleTopoReconstructor* GetTopoReconstructor() { return fKFParticleTopoReconstructor; }
  
  void SetPrimaryProbCut(float prob);
  
  bool ProcessEvent(StPicoDst* picoDst, std::vector<int>& goodTracks);
  bool ProcessEvent(StMuDst* muDst, std::vector<KFMCTrack>& mcTracks, std::vector<int>& mcIndices, bool processSignal);
  void   SetPidQA(Bool_t k = kTRUE) {fPidQA = k;}
  vector<const KFParticle *> Vec4Cfits();
  Bool_t FindUnique(const KFParticle *particle, vector<const KFParticle *> Vec4Cfit, Int_t indxnp[2]);
  Bool_t PidQA(StPicoDst* picoDst);
  Bool_t PidQA(StMuDst* muDst);
  Bool_t FillPidQA(StTrackCombPiD* PiD = 0, Int_t pdg = 0, Int_t pdgParent = 0); 
  Bool_t PidQArmerteros(KFParticle TempPart, TVector3 &negative, TVector3 &positive ); 
  bool OpenCharmTrigger();
  void OpenCharmTriggerCompression(int nTracksTriggered, int nTracksInEvent, bool triggerDMesons);
  
  //Histograms
  void CollectTrackHistograms();
  void CollectPIDHistograms();
  void CollectPVHistograms();
  
  //PID hypothesis, should be resized from outside
  void ResizeTrackPidVectors(const int nTracks);
  const float GetdEdXNSigmaPion(const int trackId)   const { return fTrackPidTpc[0][trackId]; }
  const float GetdEdXNSigmaKaon(const int trackId)   const { return fTrackPidTpc[1][trackId]; }
  const float GetdEdXNSigmaProton(const int trackId) const { return fTrackPidTpc[2][trackId]; }
  const float GetTofNSigmaPion(const int trackId)    const { return fTrackPidTof[0][trackId]; }
  const float GetTofNSigmaKaon(const int trackId)    const { return fTrackPidTof[1][trackId]; }
  const float GetTofNSigmaProton(const int trackId)  const { return fTrackPidTof[2][trackId]; }

  //PID cuts 
  void SetStrictTofPidMode() { fStrictTofPID = true;  }
  void SetSoftTofPidMode()   { fStrictTofPID = false; }
  void SetSoftKaonPIDMode()  { fCleanKaonsWitTof = false; }
  void SetdEdXType(Int_t type = 1);  // type - 0 => I70, 1 => dEdxFit, 2 => dNdx
  void UseCorrecteddEdX()    { SetdEdXType(2); }
  void SetTriggerMode()      { fTriggerMode = true; }
  //KF Particle Finder cuts
  void SetChiPrimaryCut(float cut)  { fChiPrimaryCut = cut; }
  void SetChiPrimaryCutFragments(float cut)  { fChiPrimaryCutFragments = cut; }
  void SetChiPrimaryMaxCut(float cut)  { fChiPrimaryMaxCut = cut; }
  //Event cuts
  void CleanLowPVTrackEvents() { fCleanLowPVTrackEvents = true; }
  void UseHFTTracksOnly()      { fUseHFTTracksOnly = true; }
  
  KFParticleFinder* GetKFParticleFinder();
  //KF Particle Finder cuts
  void SetMaxDistanceBetweenParticlesCut(float cut);
  void SetLCut(float cut);
  void SetChiPrimaryCut2D(float cut);
  void SetChi2Cut2D(float cut);
  void SetLdLCut2D(float cut);
  void SetLdLCutXiOmega(float cut);
  void SetChi2TopoCutXiOmega(float cut);
  void SetChi2CutXiOmega(float cut);
  void SetChi2TopoCutResonances(float cut);
  void SetChi2CutResonances(float cut);
  void SetPtCutLMVM(float cut);
  void SetPCutLMVM(float cut);
  void SetPtCutJPsi(float cut);
  void SetPtCutCharm(float cut);
  void SetChiPrimaryCutCharm(float cut);
  void SetLdLCutCharmManybodyDecays(float cut);
  void SetChi2TopoCutCharmManybodyDecays(float cut);
  void SetChi2CutCharmManybodyDecays(float cut);
  void SetLdLCutCharm2D(float cut);
  void SetChi2TopoCutCharm2D(float cut);
  void SetChi2CutCharm2D(float cut);
  void SetSecondaryCuts(const float sigmaMass, const float chi2Topo, const float ldl);
  static StKFParticleInterface *instance() {return fgStKFParticleInterface;}
  void              SetFixedTarget(Bool_t k=kTRUE) {fIsFixedTarget = k;}
  Bool_t            IsFixedTarget()        {return fIsFixedTarget;}
  void              SetFixedTarget2018(Bool_t k=kTRUE) {fIsFixedTarget2018 = k;}
  Bool_t            IsFixedTarget2018()        {return fIsFixedTarget2018;}
  static void       SetUsedx2(Bool_t k = kTRUE);
  static void       SetUseTof(Bool_t k = kTRUE);
  void              SetMagScaleFactor(Double_t scale = 1.0);
 private:
  
  double InversedChi2Prob(double p, int ndf) const;
  bool IsGoodPV(const KFVertex& pv);
  bool GetTrack(const StDcaGeometry& dcaG, KFPTrack& track, int q, int index);
  std::vector<int> GetTofPID(double m2, double p, int q, const int trackId);
  std::vector<int> GetPID(double m2, double p, int q, double dEdX, double dEdXPull[8], bool isBTofm2, bool isETofm2, const int trackId);
  void AddTrackToParticleList(const KFPTrack& track, int nHftHitsInTrack, int index, const std::vector<int>& totalPDG, KFVertex& pv, std::vector<int>& primaryTrackList,
                              std::vector<int>& nHftHits, std::vector<int>& particlesPdg, std::vector<KFParticle>& particles, int& nPartSaved,
                              const KFPTrack* trackAtLastHit=nullptr, std::vector<KFParticle>* particlesAtLastHit=nullptr,
			      Float_t chi2 = 0, Int_t NDF = -1);
  void FillPIDHistograms(StPicoTrack *gTrack, const std::vector<int>& pdgVector, const bool isTofm2, float m2tof = -1,  const bool isETofm2 = kFALSE, float m2Etof = -1);
  void FillPIDHistograms(StMuTrack *gTrack, const std::vector<int>& pdgVector, const bool isTofm2, float m2tof = -1,  const bool isETofm2 = kFALSE, float m2Etof = -1);
  
  void FillPVHistos(const KFVertex& vertex, const std::vector<int>& tracks, const bool isMainVertex = false);
  void CleanTracks(KFPTrackVector& tracks, std::vector<bool>& isUsed, const int nUsed);
  void CleanPileupTracks(KFPTrackVector& tracks, const std::vector<KFVertex>& vertices, std::vector<std::vector<int>>& verticesTracks,
                         int& nPV, int& nPileup, std::vector<bool>& isPileup, std::vector<KFVertex>& pileupPv);

  bool FitPV(KFVertex& pv, bool isFirstSeed, const KFPTrackVector& tracks,   
             std::vector<int>& pvTrackIndices, std::vector<bool>& isUsed);
  template<class T>
  void FindPileup(const KFPTrackVector& tracks, const KFVertex& beamPosition,
                  std::vector<KFVertex>& vertices, std::vector<std::vector<int>>& vertexTracks, const float X = 4.f, const float dX = 0.5f);
  bool FindFixedTargetPV(StPicoDst* picoDst, KFVertex& pv, std::vector<KFVertex>& pileupPv, std::vector<bool>& isPileup);
  
  KFParticleTopoReconstructor* fKFParticleTopoReconstructor;
  std::vector<KFParticle> fParticles;
#ifdef __kfpAtFirstHit__
  std::vector<KFParticle> fParticlesAtLastHit;
#endif
  std::vector<int> fParticlesPdg;
  std::vector<int> fNHftHits;
  
  KFParticle fBeamSpot;

  //histograms
  bool fCollectTrackHistograms;
  bool fCollectPIDHistograms;
  bool fCollectPVHistograms;
  //0 - N HFT hits in track, 1 - PV error distribution, 2 - NPrimTracks/NAllTracks
  TH1F* fTrackHistograms[3];
  //old: 0 - dEdX, 1 - dEdX positive tracks, 2 - dEdX negative tracks, 3 - dEdX tracks with ToF, 4 - ToF PID, 5 - PV errors vs N tracks, 6 - PV errors vs N PV tracks, 
  //     7 - N secondary vs N prim, 8 - M2 BTof vs dEdx, 9 - dEdX with EToF, 10 - EToF PID
  //new: 0 - dEdX, 1 - dEdX positive tracks, 2 - dEdX negative tracks, 3 - dEdX tracks with Tof or ETof,
  // 4 - Tof PID, 5 - PV errors vs N tracks, 6 - PV errors vs N PV tracks, 7 - N Global vs N Primary
  // 8 - M2 vs Log_10(dEdx), 9 - dEdX with EToF, 10 - EToF PID
  // 8 => 11 - pT^2 versus eta for primary tracks
  // 9 => 12 - dNdX, 10 => 13 - dNdX positive tracks, 11 => 14 - dNdX negative tracks, 12 => 15- dNdX tracks with Tof or ETof.
  // 13 => 16 - pT^2 versus eta for all tracks
  // 14 => 17 => 10
  // 15 => 18 - Tof PID, eta > 0
  // 16 => 19 - Tof PID, eta < 0
  // 20 - M2  vs Log_10(dN/dx)
  enum eTrackHistograms2D 
  {khdEdX, khdEdXPos, khdEdXNeg, khdEdXwithTof, // 0 - dEdX, 1 - dEdX positive tracks, 2 - dEdX negative tracks, 3 - dEdX tracks with Tof or ETof,
   khdNdX, khdNdXPos, khdNdXNeg, khdNdXwithTof, // 9 => 12 - dNdX, 10 => 13 - dNdX positive tracks, 11 => 14 - dNdX negative tracks, 12 => 15- dNdX tracks with Tof or ETof.
   khTofPID, khTofPIDP, khTofPIDN,              // 4 - Tof PID, 15 => 18 - Tof PID, eta > 0, 16 => 19 - Tof PID, eta < 0
   khPVErrorVsNTracks, khPVErrorVsNPVTracks, khGlobalVsPrimaryTracks,//  5 - PV errors vs N tracks, 6 - PV errors vs N PV tracks, 7 - N Global vs N Primary
   khdEdXTofPID, khdNdXTofPID,                  // 
   khETofPID, 
   khdEdXETofPID,
   kEtaVspT, kEtaVspTAll,
   kfTrackHistograms2D};
  TH2F* fTrackHistograms2D[kfTrackHistograms2D];
  
  
  TH1F* fPVHistograms[11];
  TH2F* fPVHistograms2D[4];
  
  //PID histograms
  static const int NTrackHistoFolders = 27; // +0 for pdg = -1 "Uknown"
  TH2F* fHistodEdXTracks[NTrackHistoFolders];
  TH2F* fHistodEdXwithToFTracks[NTrackHistoFolders];
  TH2F* fHistoTofPIDTracks[NTrackHistoFolders][3];
  TH2F* fHistoETofPIDTracks[NTrackHistoFolders];
  TH1F* fHistoMomentumTracks[NTrackHistoFolders];
  TH2F* fHistodEdXPull[NTrackHistoFolders];
  TH2F* fHistodEdXZ[NTrackHistoFolders];
  TH2F* fHistodEdXnSigma[NTrackHistoFolders];
  TH2F* fHistodNdXTracks[NTrackHistoFolders];
  TH2F* fHistodNdXwithTofTracks[NTrackHistoFolders];
  TH2F* fHistodNdXPull[NTrackHistoFolders];
  std::map<int, int> fTrackPdgToHistoIndex;
  
  //PID information with respect to the trackID
  std::vector<float> fTrackPidTof[3];
  std::vector<float> fTrackPidTpc[3];
  
  //PID cuts
  bool fStrictTofPID;
  bool fCleanKaonsWitTof;
  bool fUseETof;
  int fdEdXMode;
  //trigger cuts
  bool fTriggerMode;
  //KF Particle Finder cuts
  float fChiPrimaryCut;
  float fChiPrimaryCutFragments;
  float fChiPrimaryMaxCut;
  static StKFParticleInterface* fgStKFParticleInterface;
  //Event cuts
  bool fCleanLowPVTrackEvents;
  bool fUseHFTTracksOnly;
  Bool_t            fIsFixedTarget;
  Bool_t            fIsFixedTarget2018;
  Bool_t            fPidQA;
  static Double_t   fgMagScaleFactor;
  static Bool_t     fgUsedx2; //! flag for StPiDStatus to absord log2(dx) dependence into TpcLengthCorrectionMD2
  static Bool_t     fgUseTof;
  std::vector<float> fm2TofArray;
  std::vector<int>   ftrackIdToI; // [trackId] => track index on [Mu|Pico]Dst track array
  ClassDef(StKFParticleInterface,1)
};

#endif //#ifndef StKFParticleInterface_H
