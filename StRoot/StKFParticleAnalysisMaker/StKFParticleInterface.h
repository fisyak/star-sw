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

#ifdef __TFG__VERSION__
class StPidStatus;
#endif
class StKFParticleInterface: public TObject
{
 public:
   
  StKFParticleInterface();
  ~StKFParticleInterface();
  
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
  void SetUsedx2(Bool_t k = kFALSE) { fUsedx2 = k;}
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
#ifdef __TFG__VERSION__
  void   SetPidQA(Bool_t k = kTRUE) {fPidQA = k;}
  vector<const KFParticle *> Vec4Cfits();
  Bool_t FindUnique(const KFParticle *particle, vector<const KFParticle *> Vec4Cfit, Int_t indxnp[2]);
  Bool_t PidQA(StPicoDst* picoDst);
  Bool_t PidQA(StMuDst* muDst);
  Bool_t FillPidQA(StPidStatus* PiD = 0, Int_t pdg = 0, Int_t pdgParent = 0, Int_t set = 0); 
  Bool_t PidQArmerteros(KFParticle TempPart, TVector3 &negative, TVector3 &positive ); 
#endif /* _TFG__VERSION__ */
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
#ifndef __TFG__VERSION__
  void UseCorrecteddEdX()    { fdEdXMode = 2; }
#else /* __TFG__VERSION__ */
  void SetdEdXType(Int_t type = 1)  { fdEdXMode = type; } // type - 0 => I70, 1 => dEdxFit, 2 => dNdx
  void UseCorrecteddEdX()    { SetdEdXType(2); }
#endif /* __TFG__VERSION__ */
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
#ifdef __TFG__VERSION__
  void SetSecondaryCuts(const float sigmaMass, const float chi2Topo, const float ldl);
#endif /* __TFG__VERSION__ */
  static StKFParticleInterface *instance() {return fgStKFParticleInterface;}
#ifdef __TFG__VERSION__
  void              SetFixedTarget(Bool_t k=kTRUE) {fIsFixedTarget = k;}
  Bool_t            IsFixedTarget()        {return fIsFixedTarget;}
  void              SetFixedTarget2018(Bool_t k=kTRUE) {fIsFixedTarget2018 = k;}
  Bool_t            IsFixedTarget2018()        {return fIsFixedTarget2018;}
  void              SetUseTof(Bool_t k = kTRUE) {fUseTof = k;}
  void              SetMagScaleFactor(Double_t scale = 1.0);
#endif /* __TFG__VERSION__ */
 private:
  
  double InversedChi2Prob(double p, int ndf) const;
  bool IsGoodPV(const KFVertex& pv);
  bool GetTrack(const StDcaGeometry& dcaG, KFPTrack& track, int q, int index);
  std::vector<int> GetTofPID(double m2, double p, int q, const int trackId);
  std::vector<int> GetPID(double m2, double p, int q, double dEdX, double dEdXPull[12], bool isTofm2, const int trackId);
#ifndef __TFG__VERSION__
  void AddTrackToParticleList(const KFPTrack& track, int nHftHitsInTrack, int index, const std::vector<int>& totalPDG, KFVertex& pv, std::vector<int>& primaryTrackList,
                              std::vector<int>& nHftHits, std::vector<int>& particlesPdg, std::vector<KFParticle>& particles, int& nPartSaved,
                              const KFPTrack* trackAtLastHit=nullptr, std::vector<KFParticle>* particlesAtLastHit=nullptr);
  void FillPIDHistograms(StPicoTrack *gTrack, const std::vector<int>& pdgVector, const bool isTofm2, float m2tof);
  void FillPIDHistograms(StMuTrack *gTrack, const std::vector<int>& pdgVector, const bool isTofm2, float m2tof);
#else /* __TFG__VERSION__ */
  void AddTrackToParticleList(const KFPTrack& track, int nHftHitsInTrack, int index, const std::vector<int>& totalPDG, KFVertex& pv, std::vector<int>& primaryTrackList,
                              std::vector<int>& nHftHits, std::vector<int>& particlesPdg, std::vector<KFParticle>& particles, int& nPartSaved,
                              const KFPTrack* trackAtLastHit=nullptr, std::vector<KFParticle>* particlesAtLastHit=nullptr,
			      Float_t chi2 = 0, Int_t NDF = -1);
  void FillPIDHistograms(StPicoTrack *gTrack, const std::vector<int>& pdgVector, const bool isTofm2, float m2tof = -1,  const bool isETofm2 = kFALSE, float m2Etof = -1);
  void FillPIDHistograms(StMuTrack *gTrack, const std::vector<int>& pdgVector, const bool isTofm2, float m2tof = -1,  const bool isETofm2 = kFALSE, float m2Etof = -1);
#endif /* ! __TFG__VERSION__ */
  
  bool FitPV(KFVertex& pv, bool isFirstSeed, const KFPTrackVector& tracks,   
             std::vector<int>& pvTrackIndices, std::vector<int>& leftTrackIndices);
  bool FindFixedTargetPV(StPicoDst* picoDst, KFVertex& pv, std::vector<bool>& isPileup);
 
  KFParticleTopoReconstructor* fKFParticleTopoReconstructor;
  std::vector<KFParticle> fParticles;
#ifdef __kfpAtFirstHit__
  std::vector<KFParticle> fParticlesAtLastHit;
#endif
  std::vector<int> fParticlesPdg;
  std::vector<int> fNHftHits;
  
  //histograms
  bool fCollectTrackHistograms;
  bool fCollectPIDHistograms;
  bool fCollectPVHistograms;
  //0 - N HFT hits in track, 1 - PV error distribution, 2 - NPrimTracks/NAllTracks
  TH1F* fTrackHistograms[3];
#ifndef __TFG__VERSION__
  // 0 - dEdX, 1 - dEdX positive tracks, 2 - dEdX negative tracks, 3 - dEdX tracks with Tof, 4 - Tof PID, 5 - PV errors vs N tracks, 6 - PV errors vs N PV tracks, 7 - N secondary vs N prim, 8 - M2 vs dEdx, 9 - dEdX with ETof, 10 - ETof PID
  TH2F* fTrackHistograms2D[11];


#else /* __TFG__VERSION__ */
  // 0 - dEdX, 1 - dEdX positive tracks, 2 - dEdX negative tracks, 3 - dEdX tracks with Tof or ETof,
  // 4 - Tof PID, 5 - PV errors vs N tracks, 6 - PV errors vs N PV tracks, 7 - N Global vs N Primary
  // 8 - pT^2 versus eta for primary tracks
  // 9 - dNdX, 10 - dNdX positive tracks, 11 - dNdX negative tracks, 12 - dNdX tracks with Tof or ETof.
  // 13 - pT^2 versus eta for all tracks
  // 14 - ETof PID
  // 15 - Tof PID, eta > 0
  // 16 - Tof PID, eta < 0
  TH2F* fTrackHistograms2D[17];
#endif /* __TFG__VERSION__ */
  TH1F* fPVHistograms[11];
  TH2F* fPVHistograms2D[4];
  
  //PID histograms
  static const int NTrackHistoFolders = 27; // +0 for pdg = -1 "Uknown"
  TH2F* fHistodEdXTracks[NTrackHistoFolders];
  TH2F* fHistodEdXwithTofTracks[NTrackHistoFolders];
#ifndef __TFG__VERSION__
  TH2F* fHistoTofPIDTracks[NTrackHistoFolders];
#else /* __TFG__VERSION__ */
  TH2F* fHistoTofPIDTracks[NTrackHistoFolders][3];
  TH2F* fHistoETofPIDTracks[NTrackHistoFolders];
#endif /* ! __TFG__VERSION__ */
  TH1F* fHistoMomentumTracks[NTrackHistoFolders];
  TH2F* fHistodEdXPull[NTrackHistoFolders];
  TH2F* fHistodEdXZ[NTrackHistoFolders];
  TH2F* fHistodEdXnSigma[NTrackHistoFolders];
#ifdef __TFG__VERSION__
  TH2F* fHistodNdXTracks[NTrackHistoFolders];
  TH2F* fHistodNdXwithTofTracks[NTrackHistoFolders];
  TH2F* fHistodNdXPull[NTrackHistoFolders];
  //  TH2F* fHistodNdXZ[NTrackHistoFolders];
#endif /* __TFG__VERSION__ */
  std::map<int, int> fTrackPdgToHistoIndex;
  
  //PID information with respect to the trackID
  std::vector<float> fTrackPidTof[3];
  std::vector<float> fTrackPidTpc[3];
  
  //PID cuts
  bool fStrictTofPID;
  bool fCleanKaonsWitTof;
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
#ifdef __TFG__VERSION__
  Bool_t            fIsFixedTarget;
  Bool_t            fIsFixedTarget2018;
  Bool_t            fPidQA;
  Bool_t            fUsedx2; //! flag for StPiDStatus to absord log2(dx) dependence into TpcLengthCorrectionMD2
  Bool_t            fUseTof;
  std::vector<float> fm2TofArray;
  std::vector<int>   ftrackIdToI; // [trackId] => track index on [Mu|Pico]Dst track array
  static Double_t   fMagScaleFactor;
#endif /* __TFG__VERSION__ */
  ClassDef(StKFParticleInterface,1)
};

#endif //#ifndef StKFParticleInterface_H
