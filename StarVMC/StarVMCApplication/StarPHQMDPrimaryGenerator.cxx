#include <assert.h>
#include "StarPHQMDPrimaryGenerator.h"
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
ClassImp(StarPHQMDPrimaryGenerator);
//_____________________________________________________________________________
StarPHQMDPrimaryGenerator::StarPHQMDPrimaryGenerator(TString mode, Int_t tune) : StarMCPrimaryGenerator() {
  PreSet(); 
  SetGenerator(mode,tune);
}
//_____________________________________________________________________________
void StarPHQMDPrimaryGenerator::PreSet() {
  fNofPrimaries = 0; fId = 0;
  fOption = "";
  fOrigin = TVector3(0,0,0);
  fPVX = fPVY = fPVZ = fPVxyError = 0;
  fTree = 0;
  SetSpread(0.15, 0.15, 42.0);
  const StChainOpt *opt = StMaker::GetTopChain()->GetChainOpt();
  assert(opt);
  const TString inputfile = opt->GetFileIn();
  TFile *f = new TFile(inputfile);
  assert(f);
  fTree = (TTree *) f->Get("PHQMDtree");
  assert(fTree);
  fTreeIter = new TTreeIter("PHQMDtree");
  fTreeIter->AddFile(inputfile);
}
//_____________________________________________________________________________
void StarPHQMDPrimaryGenerator::SetGenerator(TString mode, Int_t tune) {
  TString path(".");
  TString File("PVxyz.root");
  Char_t *file = gSystem->Which(path,File,kReadPermission);
  if (file) {
    TFile *PVfile = TFile::Open(file);
    if (PVfile) {
      fPVX = (TH1 *) PVfile->Get("x"); assert(fPVX); fPVX->SetDirectory(0);
      fPVY = (TH1 *) PVfile->Get("y"); assert(fPVY); fPVY->SetDirectory(0);
      fPVZ = (TH1 *) PVfile->Get("z"); assert(fPVZ); fPVZ->SetDirectory(0);
      fPVxyError = (TH1 *) PVfile->Get("hPVError"); if (fPVxyError) fPVxyError->SetDirectory(0);
      delete PVfile;
      LOG_WARN << "PVxyz.root with x, y and z histograms has been found. These histogram will be use to generate primary vertex x, y, z." << endm;
      if (fPVxyError) LOG_WARN << " hPVError histogram will be used for transverse PV error." << endm;
    }
    delete [] file;
  }
  fgInstance = this;
}
//_____________________________________________________________________________
void StarPHQMDPrimaryGenerator::GeneratePrimary() {     
  // Add one primary particle to the user stack (derived from TVirtualMCStack).
  // Track ID (filled by stack)
  // Option: to be tracked
  TTreeIter &iter = *fTreeIter;
  static const Int_t&       fNpart                                   = iter("fNpart");
  //  static const Int_t&       fNparticipants                           = iter("fNparticipants");
  //  static const Float_t*&    fPsi                                     = iter("fPsi[4]");
  //  static const Float_t*&    fEcc                                     = iter("fEcc[4]");
  //  static const Int_t&       fParticles_                              = iter("fParticles");
  //  static const Int_t*&      fParticles_fId                           = iter("fParticles.fId");
  static const Int_t*&      fParticles_fPDG                          = iter("fParticles.fPDG");
  //  static const Int_t*&      fParticles_fCharge                       = iter("fParticles.fCharge");
  //  static const Int_t*&      fParticles_fChannel                      = iter("fParticles.fChannel");
  static const Float_t*&    fParticles_fPx                           = iter("fParticles.fPx");
  static const Float_t*&    fParticles_fPy                           = iter("fParticles.fPy");
  static const Float_t*&    fParticles_fPz                           = iter("fParticles.fPz");
  static const Float_t*&    fParticles_fE                            = iter("fParticles.fE");
  //  static const Bool_t*&     fParticles_fIsInMST                      = iter("fParticles.fIsInMST");
  //  static const Bool_t*&     fParticles_fIsInSACA                     = iter("fParticles.fIsInSACA");

 NEXT:
  if (! iter.Next()) {fStatus =  kStEOF; return;}
  if (! fNpart ) goto NEXT;
  Int_t toBeDone = 1; 
  Double_t polx = 0.; 
  Double_t poly = 0.; 
  Double_t polz = 0.; 
  Int_t ntr = 0;
  Int_t N = fNpart;
  for (Int_t i = 0; i < N; i++) {
    if (TMath::Abs(fParticles_fPDG[i]) < 10) continue;
    if (! TDatabasePDG::Instance()->GetParticle(fParticles_fPDG[i])) continue;
    TLorentzVector P(  fParticles_fPx[i], 
			fParticles_fPy[i], 
			fParticles_fPz[i], 
			fParticles_fE[i]);
    static Double_t beta = St_beamInfoC::instance()->BetaCMS();
    if (TMath::Abs(beta) > 1e-7) {
      P.Boost(0, 0, beta);
    }
    // Add particle to stack 
    fStarStack->PushTrack(toBeDone, -1, 
			  fParticles_fPDG[i], 
			  P.Px(), 
			  P.Py(),
			  P.Pz(),
			  P.E(),
			  fOrigin.X(), 
			  fOrigin.Y(), 
			  fOrigin.Z(), 
			  0,
			  polx, poly, polz, kPPrimary, ntr, 1., 2);
  }
  if (! ntr) goto NEXT; 
}
//_____________________________________________________________________________
void StarPHQMDPrimaryGenerator::GeneratePrimaries(const TVector3& origin) {    
  // Fill the user stack (derived from TVirtualMCStack) with primary particles.
  // ---
  Double_t sigmaX = gEnv->GetValue("FixedSigmaX", 0.00176);
  Double_t sigmaY = gEnv->GetValue("FixedSigmaY", 0.00176);
  Double_t sigmaZ = gEnv->GetValue("FixedSigmaZ", 0.00176);
  TVector3 dR(gRandom->Gaus(0, sigmaX), gRandom->Gaus(0, sigmaY), gRandom->Gaus(0, sigmaZ));
  fOrigin = origin + dR;
  GeneratePrimary();  
  fStarStack->SetNprimaries(fNofPrimaries);
}
//_____________________________________________________________________________
void StarPHQMDPrimaryGenerator::GeneratePrimaries() {
  if (! fSetVertex) {
    if (fPVX && fPVY && fPVZ) {
      fOrigin.SetX(fPVX->GetRandom());
      fOrigin.SetY(fPVY->GetRandom());
      fOrigin.SetZ(fPVZ->GetRandom());
      if (fPVxyError) {
	Double_t dxy = fPVxyError->GetRandom()/TMath::Sqrt(2.);
	gEnv->SetValue("FixedSigmaX", dxy);
	gEnv->SetValue("FixedSigmaY", dxy);
      }
    } else {
      fOrigin.SetX(gRandom->Gaus(0,gSpreadX));
      fOrigin.SetY(gRandom->Gaus(0,gSpreadY));
      fOrigin.SetZ(gRandom->Gaus(0,gSpreadZ));
    }
  }
  GeneratePrimaries(fOrigin);
}
