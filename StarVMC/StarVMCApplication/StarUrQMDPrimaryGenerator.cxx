#include <assert.h>
#include "StarUrQMDPrimaryGenerator.h"
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
//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Thu Aug 14 12:11:21 2025 by ROOT version 5.34/39
// from TTree urqmd1/urqmd
// found on file: /gpfs01/star/pwg_tasks/simulations/UrQMD/IMP/4p5/roots/07334.root
//////////////////////////////////////////////////////////


#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include "TRandom.h"
#include "TGeant3.h"
// Header file for the classes stored in the TTree if any.

// Fixed size dimensions of array or collections stored in the TTree if any.

class urqmd1 {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

   // Declaration of leaf types
   Int_t           mul;
   Float_t         b;
   Int_t           Npart;
   Int_t           pid[10000];   //[mul]
   Float_t         px[10000];   //[mul]
   Float_t         py[10000];   //[mul]
   Float_t         pz[10000];   //[mul]

   // List of branches
   TBranch        *b_mul;   //!
   TBranch        *b_b;   //!
   TBranch        *b_Npart;   //!
   TBranch        *b_pid;   //!
   TBranch        *b_px;   //!
   TBranch        *b_py;   //!
   TBranch        *b_pz;   //!

   urqmd1(TTree *tree=0);
   virtual ~urqmd1();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};


urqmd1::urqmd1(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("/gpfs01/star/pwg_tasks/simulations/UrQMD/IMP/4p5/roots/07334.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("/gpfs01/star/pwg_tasks/simulations/UrQMD/IMP/4p5/roots/07334.root");
      }
      f->GetObject("urqmd1",tree);

   }
   Init(tree);
}

urqmd1::~urqmd1()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t urqmd1::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t urqmd1::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void urqmd1::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("mul", &mul, &b_mul);
   fChain->SetBranchAddress("b", &b, &b_b);
   fChain->SetBranchAddress("Npart", &Npart, &b_Npart);
   fChain->SetBranchAddress("pid", pid, &b_pid);
   fChain->SetBranchAddress("px", px, &b_px);
   fChain->SetBranchAddress("py", py, &b_py);
   fChain->SetBranchAddress("pz", pz, &b_pz);
   Notify();
}

Bool_t urqmd1::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void urqmd1::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t urqmd1::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
void urqmd1::Loop()
{
//   In a ROOT session, you can do:
//      Root > .L urqmd1.C
//      Root > urqmd1 t
//      Root > t.GetEntry(12); // Fill t data members with entry number 12
//      Root > t.Show();       // Show values of entry 12
//      Root > t.Show(16);     // Read and show values of entry 16
//      Root > t.Loop();       // Loop on all entries
//

//     This is the loop skeleton where:
//    jentry is the global entry number in the chain
//    ientry is the entry number in the current Tree
//  Note that the argument to GetEntry must be:
//    jentry for TChain::GetEntry
//    ientry for TTree::GetEntry and TBranch::GetEntry
//
//       To read only selected branches, Insert statements like:
// METHOD1:
//    fChain->SetBranchStatus("*",0);  // disable all branches
//    fChain->SetBranchStatus("branchname",1);  // activate branchname
// METHOD2: replace line
//    fChain->GetEntry(jentry);       //read all branches
//by  b_branchname->GetEntry(ientry); //read only this branch
   if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntriesFast();

   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue;
   }
}


ClassImp(StarUrQMDPrimaryGenerator);
static urqmd1 *T = 0;
static Long64_t jentry = -1;
//_____________________________________________________________________________
StarUrQMDPrimaryGenerator::StarUrQMDPrimaryGenerator(TString mode, Int_t tune) : StarMCPrimaryGenerator() {
  PreSet(); 
}
//_____________________________________________________________________________
Int_t StarUrQMDPrimaryGenerator::Skip(Int_t skip) {
  if (skip > 0) jentry += skip -1;
  return kStOK;
}
//_____________________________________________________________________________
void StarUrQMDPrimaryGenerator::PreSet() {
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
  const Char_t *treeNames[1] = {"urqmd"};
  Int_t i = 0;
  for (; i < 1; i++) {
    fTree = (TTree *) f->Get(treeNames[i]);
    if (fTree) break;
  }
  assert(fTree);
  T = new urqmd1(fTree);
#if 0
  fTreeIter = new TTreeIter(treeNames[i]);
  fTreeIter->AddFile(inputfile);
#endif
}
//_____________________________________________________________________________
void StarUrQMDPrimaryGenerator::GeneratePrimary() {     
#if 0
  // Add one primary particle to the user stack (derived from TVirtualMCStack).
  // Track ID (filled by stack)
  // Option: to be tracked
  TTreeIter &iter = *fTreeIter;
  //        static const Int_t&       mul                                      = iter("mul");
  //        static const Float_t&     b                                        = iter("b");
        static const Int_t&       Npart                                    = iter("Npart");
        static const Int_t*&      pid                                      = iter("pid");
        static const Float_t*&    px                                       = iter("px");
        static const Float_t*&    py                                       = iter("py");
        static const Float_t*&    pz                                       = iter("pz");
#endif
 NEXT:
   jentry++;
   Long64_t ientry = T->LoadTree(jentry);
   if (ientry < 0) {fStatus =  kStEOF; return;}
   Long64_t nb = T->fChain->GetEntry(jentry);
   if (nb <= 0) {fStatus =  kStEOF; return;}
#if 0
  if (! iter.Next()) {fStatus =  kStEOF; return;}
#endif
  if (! T->Npart ) goto NEXT;
  Int_t toBeDone = 1; 
  Double_t polx = 0.; 
  Double_t poly = 0.; 
  Double_t polz = 0.; 
  Int_t ntr = 0;
  Int_t N = T->mul;
  static TGeant3 *geant3 = (TGeant3 *)TVirtualMC::GetMC();
  for (Int_t i = 0; i < N; i++) {
    Int_t pid = T->pid[i];
    if (TMath::Abs(pid) < 10) continue;
    if (! TDatabasePDG::Instance()->GetParticle(pid)) continue;
    if (TMath::Abs(pid) == 311) {
      if (gRandom->Rndm() < 0.5) pid = 130;
      else                       pid = 310;
    }
    if (geant3 && geant3->IdFromPDG(pid) < 1) {
      cout << "StarUrQMDPrimaryGenerator::GeneratePrimary illegal pdg = " << pid << "\t Skip." << endl;
      continue;
    }
    TVector3 P3( T->px[i], T->py[i],T->pz[i]);
    Double_t pmom = P3.Mag();
    Double_t M = TDatabasePDG::Instance()->GetParticle(pid)->Mass();
    Double_t E = TMath::Sqrt(M*M + pmom*pmom);
    TLorentzVector P(P3, E);
    static Double_t beta = St_beamInfoC::instance()->BetaCMS();
    if (TMath::Abs(beta) > 1e-7) {
      P.Boost(0, 0, beta);
    }
    // Add particle to stackx2 
    fStarStack->PushTrack(toBeDone, -1, 
			  pid, 
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
