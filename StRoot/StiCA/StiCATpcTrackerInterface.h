#ifndef __StiCATpcTrackerInterface_h__
#define __StiCATpcTrackerInterface_h__
#include "StiCATpcSeedFinder.h"
#include "TPCCATracker/AliHLTTPCCAGBTracker.h"
#include "TPCCATracker/StTPCCAInterface.h"
#include "Sti/StiTrackContainer.h"
#include "KFParticle/KFParticle.h"
class StiCATpcTrackerInterface : public StTPCCAInterface {
 public:
 StiCATpcTrackerInterface() : StTPCCAInterface() {}
  virtual ~StiCATpcTrackerInterface() {fgStiCATpcTrackerInterface = 0;}
  static StiCATpcTrackerInterface &Instance();
  virtual void SetNewEvent();
  virtual void SetHits(HitMapToVectorAndEndType &map_){ fHitsMap = &map_; };// set hits data array.
  virtual vector<Seed_t> &GetSeeds(){ return fSeeds; };                   // get seeds. Should be called after Run(...).
  virtual vector<SeedHit_t>        GetSeedHits()    { return fSeedHits;}
 protected:
  virtual void MakeHits();     // fill fCaHits & fSeedHits
  virtual void MakeSeeds();    // fill fSeeds & fTrackParameters
  virtual void ConvertPars(const AliHLTTPCCATrackParam& caPar, const Double_t _alpha, StiNodePars& nodePars, StiNodeErrs& nodeErrs); // convert caPars into NodePars
  KFParticle  &MakeParticle(const AliHLTTPCCATrackParam &trParam, const Double_t &alpha, Int_t kg = 0, Int_t pdg = 0);
  virtual void MakeParticles(std::vector<trackInSector> Tracks, std::vector<int>* pdg = 0);
  virtual void getXYZ(const StiNodePars &pars, const StiNodeErrs &errs, const Float_t &alpha,  Float_t xyzp[6], Float_t CovXyzp[21]) const;
  virtual void TriggerOffSet();
  virtual void FindCAWEPrimaryVertices();
  virtual void DrawKFWEPrimaryVertices(Int_t side = -1, Double_t Z = 250);
  HitMapToVectorAndEndType *fHitsMap;
  vector<Seed_t>            fSeeds;
  StiCATpcSeedFinder       *fSeedFinder;
  vector<SeedHit_t>         fSeedHits;          // hits to make seeds
  vector<KFParticle>        fParticles;
  static StiCATpcTrackerInterface *fgStiCATpcTrackerInterface;
  static Bool_t             fgUseCAVxFinder;
  
};
#endif //  __StiCATpcTrackerInterface_h__
