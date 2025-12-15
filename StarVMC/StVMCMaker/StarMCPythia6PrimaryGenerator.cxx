// $Id: StarMCPythia6PrimaryGenerator.cxx,v 1.1.1.1 2008/12/10 20:45:52 fisyak Exp $
#include "StarMCPythia6PrimaryGenerator.h"
#include "TFile.h"
#include "TGeant3.h"
#include "TEnv.h"
#include "TRandom.h"
#include "TSystem.h"
#include "TDatabasePDG.h"
#include "TParticlePDG.h"
#include "TPythia6Calls.h"
#include "TMCParticle.h"
#include "StDetectorDbMaker/St_vertexSeedC.h"
#include "StDetectorDbMaker/St_beamInfoC.h"
#include "StMessMgr.h" 
ClassImp(StarMCPythia6PrimaryGenerator);
//_____________________________________________________________________________
StarMCPythia6PrimaryGenerator::StarMCPythia6PrimaryGenerator(TString mode, Int_t tune) : StarMCPrimaryGenerator() {
  PreSet(); 
  fPythia6 = new TPythia6;
  TString blue("p");
  TString yellow("p");
  Double_t energy = 510;
  if (mode.Contains("pp",TString::kIgnoreCase)) {
#if 0
    if (mode.Contains("W",TString::kIgnoreCase)) {
      // Setup pythia process
      PySubs_t &pysubs = fPythia6->pysubs();
      pysubs.msel = 12;
      pysubs.ckin(3)=4.0;
    }
#endif
    if (mode.Contains("510")) energy = 510;
    if (mode.Contains("200")) energy = 200;
#if 0
  } else if ( mode.Contains("ep",TString::kIgnoreCase)) {
    blue = "e-";
    yellow = "p";
    Double_t pblue[]={0.,0.,30.0};
    Double_t pyell[]={0.,0.,-320.0};
    fPythia6->SetFrame("3MOM", pblue, pyell );
    fPythia6->SetBlue("e-");
    fPythia6->SetYell("proton");
#endif
  }
  fPythia6->Initialize("cms", blue, yellow, energy);
#if 0
  if ( tune ) fPythia6->PyTune( tune );
#endif
  fgInstance = this;
}
//_____________________________________________________________________________
void StarMCPythia6PrimaryGenerator::PreSet() {
  fNofPrimaries = 0; fId = 0;
  fOption = "";
  fOrigin = TVector3(0,0,0);
  fPVX = fPVY = fPVZ = fPVxyError = 0;
  fCurOrigin = fOrigin;
  fPythia6 = 0;
  SetSpread(0.15, 0.15, 42.0);
}
//_____________________________________________________________________________
void StarMCPythia6PrimaryGenerator::GeneratePrimary() {     
  // Add one primary particle to the user stack (derived from TVirtualMCStack).
  // Track ID (filled by stack)
  fPythia6->GenerateEvent();
  static TClonesArray particles("TParticle");
  fPythia6->ImportParticles(&particles);
  Int_t N = particles.GetLast();
  // Option: to be tracked
  Int_t toBeDone = 1; 
  Double_t polx = 0.; 
  Double_t poly = 0.; 
  Double_t polz = 0.; 
  Int_t ntr = 0;
  fNofPrimaries = 0;
  for (Int_t i = 0; i <= N; i++) {
    TParticle *p = (TParticle *) particles.UncheckedAt(i);
    if (! p) continue;
    // Add particle to stack 
    fStarStack->PushTrack(toBeDone, -1, p->GetPdgCode(), p->Px(), p->Py(), p->Pz(), p->Energy(), 
			  p->Vx() + fCurOrigin.X(), p->Vy() + fCurOrigin.Y(), p->Vz() + fCurOrigin.Z(), p->T(),  
			  polx, poly, polz, kPPrimary, ntr, 1., 2);
    fNofPrimaries++;
  }
}
