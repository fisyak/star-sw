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
#include "StMaker.h"
#include "StChainOpt.h"
ClassImp(StarPHQMDPrimaryGenerator);
//_____________________________________________________________________________
StarPHQMDPrimaryGenerator::StarPHQMDPrimaryGenerator(TString mode, Int_t tune) : StarMCPrimaryGenerator() {
  PreSet(); 
}
//_____________________________________________________________________________
void StarPHQMDPrimaryGenerator::PreSet() {
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
#ifdef __PHQMDtree__
  const Char_t *treeName = "PHQMDtree";
#else
  const Char_t *treeName = "events";
#endif  
  fTree = (TTree *) f->Get(treeName);
  assert(fTree);
  fTreeIter = new TTreeIter(treeName);
  fTreeIter->AddFile(inputfile);
}
//_____________________________________________________________________________
void StarPHQMDPrimaryGenerator::GeneratePrimary() {     
  // Add one primary particle to the user stack (derived from TVirtualMCStack).
  // Track ID (filled by stack)
  // Option: to be tracked
  TTreeIter &iter = *fTreeIter;
#ifdef __PHQMDtree__
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
#else
#if 0
        static const Int_t&       fEventNr                                 = iter("fEventNr");
        static const Double_t&    fB                                       = iter("fB");
        static const Double_t&    fPhi                                     = iter("fPhi");
        static const Int_t&       fNes                                     = iter("fNes");
        static const Int_t&       fStepNr                                  = iter("fStepNr");
        static const Double_t&    fStepT                                   = iter("fStepT");
#endif
        static const Int_t&       fNpart                                   = iter("fNpa");
#if 0
        static const TString&     fComment                                 = iter("fComment");
        static const Int_t&       fParticles_                              = iter("fParticles");
        static const Int_t*&      fParticles_fIndex                        = iter("fParticles.fIndex");
#endif
        static const Int_t*&      fParticles_fPDG                          = iter("fParticles.fPdg");
#if 0
        static const Int_t*&      fParticles_fStatus                       = iter("fParticles.fStatus");
        static const Int_t*&      fParticles_fParent                       = iter("fParticles.fParent");
        static const Int_t*&      fParticles_fParentDecay                  = iter("fParticles.fParentDecay");
        static const Int_t*&      fParticles_fMate                         = iter("fParticles.fMate");
        static const Int_t*&      fParticles_fDecay                        = iter("fParticles.fDecay");
        static const Int_t*&      fParticles_fChild                        = iter("fParticles.fChild[2]");
#endif
        static const Double32_t*& fParticles_fPx                           = iter("fParticles.fPx");
        static const Double32_t*& fParticles_fPy                           = iter("fParticles.fPy");
        static const Double32_t*& fParticles_fPz                           = iter("fParticles.fPz");
        static const Double32_t*& fParticles_fE                            = iter("fParticles.fE");
#if 0
        static const Double32_t*& fParticles_fX                            = iter("fParticles.fX");
        static const Double32_t*& fParticles_fY                            = iter("fParticles.fY");
        static const Double32_t*& fParticles_fZ                            = iter("fParticles.fZ");
        static const Double32_t*& fParticles_fT                            = iter("fParticles.fT");
        static const Double32_t*& fParticles_fWeight                       = iter("fParticles.fWeight");
#endif
#endif
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
    // Add particle to stackx2 
    fStarStack->PushTrack(toBeDone, -1, 
			  fParticles_fPDG[i], 
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
