// $Id: StarMCTTreePrimaryGenerator.cxx,v 1.1.1.1 2008/12/10 20:45:52 fisyak Exp $
#include <assert.h>
#include "StarMCTTreePrimaryGenerator.h"
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
ClassImp(StarMCTTreePrimaryGenerator);
//_____________________________________________________________________________
StarMCTTreePrimaryGenerator::StarMCTTreePrimaryGenerator(TString mode, Int_t tune) : StarMCPrimaryGenerator() {
  PreSet(); 
  SetGenerator(mode,tune);
}
//_____________________________________________________________________________
void StarMCTTreePrimaryGenerator::PreSet() {
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
  fTree = (TTree *) f->Get("EICTree");
  assert(fTree);
  fTreeIter = new TTreeIter("EICTree");
  fTreeIter->AddFile(inputfile);
}
//_____________________________________________________________________________
void StarMCTTreePrimaryGenerator::GeneratePrimary() {     
  // Add one primary particle to the user stack (derived from TVirtualMCStack).
  // Track ID (filled by stack)
  // Option: to be tracked
  TTreeIter &iter = *fTreeIter;
  static const Int_t&       nTracks                                  = iter("nTracks");
  static const Int_t*&      particles_id                             = iter("particles.id");
  static const Double_t*&   particles_px                             = iter("particles.px");
  static const Double_t*&   particles_py                             = iter("particles.py");
  static const Double_t*&   particles_pz                             = iter("particles.pz");
  static const Double32_t*& particles_E                              = iter("particles.E");
  static const Double_t*&   particles_xv                             = iter("particles.xv");
  static const Double_t*&   particles_yv                             = iter("particles.yv");
  static const Double_t*&   particles_zv                             = iter("particles.zv");
  if (! iter.Next()) {fStatus =  kStEOF; return;}
  Int_t toBeDone = 1; 
  Double_t polx = 0.; 
  Double_t poly = 0.; 
  Double_t polz = 0.; 
  Int_t ntr = 0;
  Int_t N = nTracks;
  for (Int_t i = 0; i < N; i++) {
    if (TMath::Abs(particles_id[i]) < 10) continue;
    if (! TDatabasePDG::Instance()->GetParticle(particles_id[i])) continue;
    // Add particle to stack 
    fStarStack->PushTrack(toBeDone, -1, 
			  particles_id[i], 
			  particles_px[i], 
			  particles_py[i], 
			  particles_pz[i], 
			  particles_E[i], 
			  particles_xv[i] + fCurOrigin.X(), 
			  particles_yv[i] + fCurOrigin.Y(), 
			  particles_zv[i] + fCurOrigin.Z(), 
			  0,
			  polx, poly, polz, kPPrimary, ntr, 1., 2);
  }
}
