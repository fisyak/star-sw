#include <assert.h>
#include "StarGenPrimaryGenerator.h"
#include "TFile.h"
#include "TGeant3.h"
#include "TEnv.h"
#include "TRandom.h"
#include "TSystem.h"
#include "TDatabasePDG.h"
#include "TParticlePDG.h"
#include "TMCParticle.h"
#include "StDetectorDbMaker/St_vertexSeedC.h"
#include "StDetectorDbMaker/St_beamInfoC.h"
#include "StMessMgr.h" 
#include "StMaker.h"
#include "StChainOpt.h"
ClassImp(StarGenPrimaryGenerator);
//_____________________________________________________________________________
StarGenPrimaryGenerator::StarGenPrimaryGenerator(TString mode, Int_t tune) : StarMCPrimaryGenerator() {
  PreSet(); 
}
//_____________________________________________________________________________
void StarGenPrimaryGenerator::PreSet() {
  fNofPrimaries = 0; fId = 0;
  fOption = "";
  fOrigin = TVector3(0,0,0);
  fPVX = fPVY = fPVZ = fPVxyError = 0;
  fTree = 0;
  SetSpread(0.15, 0.15, 42.0);
  fCurOrigin = fOrigin;
  const StChainOpt *opt = StMaker::GetTopChain()->GetChainOpt();
  assert(opt);
  const TString inputfile = opt->GetFileIn();
  TFile *f = new TFile(inputfile);
  assert(f);
  fTree = (TTree *) f->Get("genevents");
  assert(fTree);
  fTreeIter = new TTreeIter("genevents");
  fTreeIter->AddFile(inputfile);
}
//_____________________________________________________________________________
void StarGenPrimaryGenerator::GeneratePrimary() {     
  // Add one primary particle to the user stack (derived from TVirtualMCStack).
  // Track ID (filled by stack)
  // Option: to be tracked
  TTreeIter &iter = *fTreeIter;
  static const Int_t&      nTracks                                 = iter("mNumParticles");
  static const Int_t*&     particles_id                            = iter("mParticles.mId");
  static const Float_t*&   particles_px                            = iter("mParticles.mPx");
  static const Float_t*&   particles_py                            = iter("mParticles.mPy");
  static const Float_t*&   particles_pz                            = iter("mParticles.mPz");
  static const Float_t*&   particles_E                             = iter("mParticles.mEnergy");
 NEXT:
  if (! iter.Next()) {fStatus =  kStEOF; return;}
  if (! nTracks ) goto NEXT;
  Int_t toBeDone = 1; 
  Double_t polx = 0.; 
  Double_t poly = 0.; 
  Double_t polz = 0.; 
  Int_t ntr = 0;
  Int_t N = nTracks;
  for (Int_t i = 0; i < N; i++) {
    if (TMath::Abs(particles_id[i]) < 10) continue;
    if (! TDatabasePDG::Instance()->GetParticle(particles_id[i])) continue;
    TLorentzVector P(   particles_px[i], 
			particles_py[i], 
			particles_pz[i], 
			particles_E[i]);
    static Double_t beta = St_beamInfoC::instance()->BetaCMS();
    if (TMath::Abs(beta) > 1e-7) {
      P.Boost(0, 0, beta);
    }
    // Add particle to stack 
    fStarStack->PushTrack(toBeDone, -1, 
			  particles_id[i], 
			  P.Px(), 
			  P.Py(),
			  P.Pz(),
			  P.E(),
			  fCurOrigin.X(), 
			  fCurOrigin.Y(), 
			  fCurOrigin.Z(), 
			  0,
			  polx, poly, polz, kPPrimary, ntr, 1., 2);
  }
  if (! ntr) goto NEXT; 
}
