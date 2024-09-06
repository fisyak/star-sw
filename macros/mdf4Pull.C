/* /hlt/cephfs/reco/Pulls.DEV2/MDFFit
   root.exe  'lDb.C(0,"y2019")' pullYICOL.root mdf4Pull.C+
   root.exe  'lDb.C(0,"y2019")' pullZICOL.root mdf4Pull.C+
   root.exe  'lDb.C(0,"y2019")' pullYOCOL.root mdf4Pull.C+
   root.exe  'lDb.C(0,"y2019")' pullZOCOL.root mdf4Pull.C+
   root.exe  'lDb.C(0,"y2019")' pullYIFXT.root mdf4Pull.C+
   root.exe  'lDb.C(0,"y2019")' pullZIFXT.root mdf4Pull.C+
   root.exe  'lDb.C(0,"y2019")' pullYOFXT.root mdf4Pull.C+
   root.exe  'lDb.C(0,"y2019")' pullZOFXT.root mdf4Pull.C+
   foreach f (`ls -1d  *COL.root`)
     root.exe  -q 'lDb.C(0,"y2019")' ${f}  mdf4Pull.C+ | tee ${f}.log
   end
   foreach f (`ls -1d  *FXT.root`)
     root.exe -q 'lDb.C(0,"y2019")' ${f}  mdf4Pull.C+ | tee ${f}.log
   end
__CHECK__
   root.exe  'lDb.C("y2019",0)' ../dPadIGP11p5GeV.root Chain.C 'mdf4Pull.C+(tChain)'
*/
//#define __CHECK__
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "Riostream.h"
#include "TROOT.h"
#include "TFile.h"
#include "TDirectory.h"
#include "TTree.h"
#include "TLeafI.h"
#include "TH1.h"
#include "TH2.h"
#include "TF2.h"
#include "TProfile.h"
#include "TProfile.h"
#include "TGraph.h"
#include "TMath.h"
#include "TMultiDimFit.h"
#include "TCanvas.h"
#include "TSystem.h"
#include "TBrowser.h"
#include "TCanvas.h"
#include "TChain.h"
#include "TDirectory.h"
#if 0
class TMultiDimFit;
enum EMDFPolyType {
  kMonomials,
  kChebyshev,
  kLegendre
};
#endif
enum {kTPC = 2, kVar = 4};
TProfile *prof[8][kVar] = {0};
TProfile *profC[8][kVar] = {0};
TProfile *profD[8][kVar] = {0};
TH2F     *h2[8][kVar] = {0};     
TMultiDimFit* gFit = 0;
TFile *fgOut = 0;
//--------------------------------------------------------------------------------
ofstream out;

// Header file for the classes stored in the TTree if any.

// Fixed size dimensions of array or collections stored in the TTree if any.

class FitPS {
public :
  TTree          *fChain;   //!pointer to the analyzed TTree or TChain
  Int_t           fCurrent; //!current Tree number in a TChain
  
  // Declaration of leaf types
  Float_t         i;
  Float_t         j;
  Float_t         k0;
  Float_t         k1;
  Float_t         k2;
  Float_t         k3;
  Float_t         k4;
  Float_t         k5;
  Float_t         k6;
  Float_t         x; // Z
  Float_t         y; // tanP
  Float_t         z0;// tanL
  Float_t         z1;// AdcL
  Float_t         z2;// 
  Float_t         z3;// 
  Float_t         z4;
  Float_t         z5;
  Float_t         z6;
  Float_t         mean;
  Float_t         rms;
  Float_t         peak;
  Float_t         mu;
  Float_t         sigma;
  Float_t         entries;
  Float_t         chisq;
  Float_t         prob;
  Float_t         a0;
  Float_t         a1;
  Float_t         a2;
  Float_t         a3;
  Float_t         a4;
  Float_t         a5;
  Float_t         a6;
  Float_t         Npar;
  Float_t         dpeak;
  Float_t         dmu;
  Float_t         dsigma;
  Float_t         da0;
  Float_t         da1;
  Float_t         da2;
  Float_t         da3;
  Float_t         da4;
  Float_t         da5;
  Float_t         da6;
  Float_t         muJ;
  Float_t         dmuJ;
  
  // List of branches
  TBranch        *b_i;   //!
  TBranch        *b_j;   //!
  TBranch        *b_k0;   //!
  TBranch        *b_k1;   //!
  TBranch        *b_k2;   //!
  TBranch        *b_k3;   //!
  TBranch        *b_k4;   //!
  TBranch        *b_k5;   //!
  TBranch        *b_k6;   //!
  TBranch        *b_x;   //!
  TBranch        *b_y;   //!
  TBranch        *b_z0;   //!
  TBranch        *b_z1;   //!
  TBranch        *b_z2;   //!
  TBranch        *b_z3;   //!
  TBranch        *b_z4;   //!
  TBranch        *b_z5;   //!
  TBranch        *b_z6;   //!
  TBranch        *b_mean;   //!
  TBranch        *b_rms;   //!
  TBranch        *b_peak;   //!
  TBranch        *b_mu;   //!
  TBranch        *b_sigma;   //!
  TBranch        *b_entries;   //!
  TBranch        *b_chisq;   //!
  TBranch        *b_prob;   //!
  TBranch        *b_a0;   //!
  TBranch        *b_a1;   //!
  TBranch        *b_a2;   //!
  TBranch        *b_a3;   //!
  TBranch        *b_a4;   //!
  TBranch        *b_a5;   //!
  TBranch        *b_a6;   //!
  TBranch        *b_Npar;   //!
  TBranch        *b_dpeak;   //!
  TBranch        *b_dmu;   //!
  TBranch        *b_dsigma;   //!
  TBranch        *b_da0;   //!
  TBranch        *b_da1;   //!
  TBranch        *b_da2;   //!
  TBranch        *b_da3;   //!
  TBranch        *b_da4;   //!
  TBranch        *b_da5;   //!
  TBranch        *b_da6;   //!
  TBranch        *b_muJ;   //!
  TBranch        *b_dmuJ;   //!
  
  Double_t fxx[4];
  static Int_t    fgCase; // (fgCase%2) : 0 => sigma**2, 1 => mu, (fgCase/4)%2  : 0 = I; 1 => 0; (fgCase/2)%2 : 0 =>  dY, 1 => dZ
  Double_t fval;
  Double_t fdval;
  Double_t fvalA;
  FitPS(TTree *tree=0);
  virtual ~FitPS();
  virtual Int_t    Cut(Long64_t entry);
  virtual Int_t    GetEntry(Long64_t entry);
  virtual Long64_t LoadTree(Long64_t entry);
  virtual void     Init(TTree *tree);
  virtual void     Loop();
  virtual void     Loop2();
  virtual Bool_t   Notify();
  virtual void     Show(Long64_t entry = -1);
  Float_t fx(Int_t i = 0)    {return *(&x+i);}
};

FitPS::FitPS(TTree *tree) : fChain(0) 
{
  // if parameter tree is not specified (or zero), connect the file
  // used to generate this class and read the Tree.
  assert(tree);
  Init(tree);
}

FitPS::~FitPS()
{
  if (!fChain) return;
  //   delete fChain->GetCurrentFile();
}

Int_t FitPS::GetEntry(Long64_t entry)
{
  // Read contents of entry.
  if (!fChain) return 0;
  return fChain->GetEntry(entry);
}
Long64_t FitPS::LoadTree(Long64_t entry)
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

void FitPS::Init(TTree *tree)
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
  
  fChain->SetBranchAddress("i", &i, &b_i);
  fChain->SetBranchAddress("j", &j, &b_j);
  fChain->SetBranchAddress("k0", &k0, &b_k0);
  fChain->SetBranchAddress("k1", &k1, &b_k1);
  fChain->SetBranchAddress("k2", &k2, &b_k2);
  fChain->SetBranchAddress("k3", &k3, &b_k3);
  fChain->SetBranchAddress("k4", &k4, &b_k4);
  fChain->SetBranchAddress("k5", &k5, &b_k5);
  fChain->SetBranchAddress("k6", &k6, &b_k6);
  fChain->SetBranchAddress("x", &x, &b_x);
  fChain->SetBranchAddress("y", &y, &b_y);
  fChain->SetBranchAddress("z0", &z0, &b_z0);
  fChain->SetBranchAddress("z1", &z1, &b_z1);
  fChain->SetBranchAddress("z2", &z2, &b_z2);
  fChain->SetBranchAddress("z3", &z3, &b_z3);
  fChain->SetBranchAddress("z4", &z4, &b_z4);
  fChain->SetBranchAddress("z5", &z5, &b_z5);
  fChain->SetBranchAddress("z6", &z6, &b_z6);
  fChain->SetBranchAddress("mean", &mean, &b_mean);
  fChain->SetBranchAddress("rms", &rms, &b_rms);
  fChain->SetBranchAddress("peak", &peak, &b_peak);
  fChain->SetBranchAddress("mu", &mu, &b_mu);
  fChain->SetBranchAddress("sigma", &sigma, &b_sigma);
  fChain->SetBranchAddress("entries", &entries, &b_entries);
  fChain->SetBranchAddress("chisq", &chisq, &b_chisq);
  fChain->SetBranchAddress("prob", &prob, &b_prob);
  fChain->SetBranchAddress("a0", &a0, &b_a0);
  fChain->SetBranchAddress("a1", &a1, &b_a1);
  fChain->SetBranchAddress("a2", &a2, &b_a2);
  fChain->SetBranchAddress("a3", &a3, &b_a3);
  fChain->SetBranchAddress("a4", &a4, &b_a4);
  fChain->SetBranchAddress("a5", &a5, &b_a5);
  fChain->SetBranchAddress("a6", &a6, &b_a6);
  fChain->SetBranchAddress("Npar", &Npar, &b_Npar);
  fChain->SetBranchAddress("dpeak", &dpeak, &b_dpeak);
  fChain->SetBranchAddress("dmu", &dmu, &b_dmu);
  fChain->SetBranchAddress("dsigma", &dsigma, &b_dsigma);
  fChain->SetBranchAddress("da0", &da0, &b_da0);
  fChain->SetBranchAddress("da1", &da1, &b_da1);
  fChain->SetBranchAddress("da2", &da2, &b_da2);
  fChain->SetBranchAddress("da3", &da3, &b_da3);
  fChain->SetBranchAddress("da4", &da4, &b_da4);
  fChain->SetBranchAddress("da5", &da5, &b_da5);
  fChain->SetBranchAddress("da6", &da6, &b_da6);
  fChain->SetBranchAddress("muJ", &muJ, &b_muJ);
  fChain->SetBranchAddress("dmuJ", &dmuJ, &b_dmuJ);
  Notify();
}

Bool_t FitPS::Notify()
{
  // The Notify() function is called when a new file is opened. This
  // can be either for a new TTree in a TChain or when when a new TTree
  // is started when using PROOF. It is normally not necessary to make changes
  // to the generated code, but the routine can be extended by the
  // user if needed. The return value is currently not used.
  
  return kTRUE;
}

void FitPS::Show(Long64_t entry)
{
  // Print contents of entry.
  // If entry is not specified, print current entry
  if (!fChain) return;
  fChain->Show(entry);
}
Int_t FitPS::Cut(Long64_t entry)
{
  // This function may be called from Loop.
  // returns  1 if entry is accepted.
  // returns -1 otherwise.
  //   tChain->Draw("sigma:z1","chisq>0&&dmu>0&&dmu<0.5&&dsigma>1e-3&&dsigma<0.1&&abs(mu)<1&&sigma>0.5&&abs(y)<1.5","colz")
  if (i == 0 || j == 0 || k0 == 0 || k1 == 0) return -1;
  if (chisq <= 0) return -1;
  if (dmu  <= 0.0 || dmu > 0.5) return -1;
  if (dsigma < 1e-3 || dsigma > 0.1) return -1;
  if (TMath::Abs(mu) > 1) return -1;
  if (sigma < 0.5) return -1;
  if (TMath::Abs(y) > 1.5) return -1;
  fxx[0] = x; // 1. - TMath::Abs(x)/207.707; // Z
  fxx[1] = y; // tanP; y*y; // tanP**2
  fxx[2] = z0;// tanL; z0*z0; // tanL**2
  fxx[3] = z1;  // AdcL
  fvalA = mu;
  fval  = fvalA;
  fdval = dmu;
  if (fgCase%2 == 0) {
    fvalA = sigma;
    fval = fvalA*fvalA;
    fdval = 2*fvalA*dsigma;
  }
  return 1;
}
Int_t FitPS::fgCase = 0;
#ifdef __CHECK__
#include "StDetectorDbMaker/StiTpcPullMDF4.h"
#endif
Double_t mdf4(Double_t xx[4]) {
#ifndef __CHECK__
  Double_t val = gFit->Eval(xx);
#else
  Int_t k = FitPS::fgCase%4;
  Double_t val = 0;
  if (FitPS::fgCase < 4) val = StiTpcPullMDF4::instance()->Eval(k,xx);
  else                   val = StiTpcPullMDF4::instance()->Eval(k,xx);
#endif
  if (FitPS::fgCase%2 == 0) {
    if (val < 0) val = 0;
    val = TMath::Sqrt(val);
  }
  return val;
}

void FitPS::Loop2()
{
  //   In a ROOT session, you can do:
  //      Root > .L FitPS.C
  //      Root > FitPS t
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
  if (! fChain) return;
  struct Plot_t {
    const Char_t *vName;
    Int_t nx;
    Double_t xmin;
    Double_t xmax;
  };
  Plot_t Plots[kVar] = {
    {"Z",        105, -210, 210},
    {"tanP",      40,   -2,   2},
    {"tanL",     140,   -7,   7},
    {"AdcL",      20,    2,  12}
  };
  Int_t io = 1;
  TString Var("mu");
  if (( fgCase   %2) == 0) Var = "sigma";
  if (((fgCase/4)%2) == 0) io = 0;
  if (((fgCase/2)%2) == 0) Var += "dYPull";
  else                  Var += "Time";
  const Char_t *IO[kTPC] = {"I","O"};
  Var += IO[io];
  for (Int_t j = 0; j < kVar; j++) {
    TString Name(Form("%s%s",Var.Data(),Plots[j].vName));
    TString Title(Form("%s vs %s",Var.Data(), Plots[j].vName));
    prof[fgCase][j]  = new TProfile(Name, Title, Plots[j].nx, Plots[j].xmin,Plots[j].xmax,"s");
    profC[fgCase][j]  = new TProfile(Name + "C", Title + " predicted", Plots[j].nx, Plots[j].xmin,Plots[j].xmax,"");
    profC[fgCase][j]->SetMarkerColor(2); profC[fgCase][j]->SetLineColor(2); 
    profD[fgCase][j]  = new TProfile(Name + "D", Title + " differenced", Plots[j].nx, Plots[j].xmin,Plots[j].xmax,"s");
    profD[fgCase][j]->SetMarkerColor(4); profD[fgCase][j]->SetLineColor(4); 
    h2[fgCase][j] = new TH2F(Name + "2D",Title + "difference",Plots[j].nx, Plots[j].xmin,Plots[j].xmax,100,-0.25,0.25);
  };
  Long64_t nentries = fChain->GetEntriesFast();
  Long64_t nbytes = 0, nb = 0;
  for (Long64_t jentry=0; jentry<nentries;jentry++) {
    Long64_t ientry = LoadTree(jentry);
    if (ientry < 0) break;
    nb = fChain->GetEntry(jentry);   nbytes += nb;
    if (Cut(jentry) < 1) continue;
    Double_t pred = mdf4(fxx);
    for (Int_t j = 0; j < kVar; j++) {
      prof[fgCase][j]->Fill(fx(j),fvalA);
      profC[fgCase][j]->Fill(fx(j),pred);
      profD[fgCase][j]->Fill(fx(j),fvalA-pred);
      h2[fgCase][j]->Fill(fx(j),fvalA-pred);
    }
  }
}
//________________________________________________________________________________
void FitPS::Loop()
{
  //   In a ROOT session, you can do:
  //      Root > .L FitPS.C
  //      Root > FitPS t
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
  Long64_t nev = 0;
  for (Long64_t jentry=0; jentry<nentries;jentry++) {
    Long64_t ientry = LoadTree(jentry);
    if (ientry < 0) break;
    nb = fChain->GetEntry(jentry);   nbytes += nb;
    if (Cut(jentry) < 1) continue;
    gFit->AddRow(fxx, fval, fdval*fdval);
    nev++;
  }
}
//using namespace std;
//________________________________________________________________________________
Double_t funcMDF(Double_t *x, Double_t *p=0) {
  if (! gFit ) return 0;
  return gFit->Eval(x, p);
}
//________________________________________________________________________________
ostream& operator<<(ostream& os, const TMultiDimFit& f) {
  Int_t i, j;
  // Assignment to coefficients vector.
  os << "  row.PolyType = \t"      << f.GetPolyType() << ";" << endl;
  os << "  row.NVariables = \t"    << f.GetNVariables() << ";" << endl;
  os << "  row.NCoefficients = \t" << f.GetNCoefficients() << ";" << endl;
  for (i = 0; i < f.GetNVariables(); i++) {
    os << Form("  row.XMin[%2i] = %10.5g;", i,f.GetMinVariables()->operator()(i));
  }
  os << endl;
  for (i = 0; i < f.GetNVariables(); i++) {
    os << Form("  row.XMax[%2i] = %10.5g;", i,f.GetMaxVariables()->operator()(i));
  }
  os << endl;
  for (i = 0; i < f.GetNCoefficients(); i++) {
    for (j = 0; j < f.GetNVariables(); j++) {
      os << Form("  row.Power[%2i] = %2i;",i * f.GetNVariables() + j,
		   f.GetPowers()[f.GetPowerIndex()[i] * f.GetNVariables() + j]);
    }
    os << endl;
  }
  os << "  row.DMean = \t"          << f.GetMeanQuantity() << ";" << endl;
  for (i = 0; i < f.GetNCoefficients(); i++) {
    os << Form("  row.Coefficients[%2i]    = %15.5g;", i, f.GetCoefficients()->operator()(i));
    if ((i+1) %2 == 0) os << endl;
  }
  if (f.GetNCoefficients()%2) os << endl;
  for (i = 0; i < f.GetNCoefficients(); i++) {
    os << Form("  row.CoefficientsRMS[%2i] = %15.5g;", i, f.GetCoefficientsRMS()->operator()(i));
    if ((i+1) %2 == 0) os << endl;
  }
  if (f.GetNCoefficients()%2) os << endl;
  return os;  
}
//________________________________________________________________________________
void mdf4Fit(FitPS &t) {
  // Global data parameters 
  Int_t nVars      =  4;
  Int_t maxTerm    = 20;
  // make fit object and set parameters on it. 
  //  fit = new TMultiDimFit(nVars, TMultiDimFit::kMonomials,"vk");
  //  TMultiDimFit::EMDFPolyType type = (TMultiDimFit::EMDFPolyType) 0;
  TMultiDimFit::EMDFPolyType type = (TMultiDimFit::EMDFPolyType) 1; // Chebyshev
  gFit = new TMultiDimFit(nVars, type,"vk");
  Int_t max = 3;
  Int_t mPowers[]   = { max, max+1, max+1, max};
  gFit->SetMaxPowers(mPowers);
  gFit->SetMaxFunctions(10000);
  gFit->SetMaxStudy(10000);
  gFit->SetMaxTerms(maxTerm);
  gFit->SetPowerLimit(max);
  gFit->SetMinAngle(10);
  gFit->SetMaxAngle(10);
  gFit->SetMinRelativeError(.01);
  // variables to hold the temporary input data 
  
  // Print out the start parameters
  gFit->Print("p");
  // Fill data  
  t.Loop();
  // Print out the statistics
  gFit->Print("s");
  // Book histograms 
  gFit->MakeHistograms();
  
  // Find the parameterization 
  gFit->FindParameterization();
  
  // Print coefficents 
  gFit->Print("rc");
}
//________________________________________________________________________________
void mdf4Pull(TChain *tChain = 0) {
  TString fName;
  if (tChain) {
    fName = gSystem->BaseName(tChain->GetFile()->GetName());
  } else {
    tChain = (TChain *) gDirectory->Get("FitP");
    fName = gSystem->BaseName(gDirectory->GetName());
  }
  if (! tChain ) return;
  FitPS t(tChain);
  Int_t kase = 0;
  Int_t Nkase = 2; // per file 0 => Sigma, 1 => Mu
  Int_t nrows = 8;
  const Char_t *Sets[8] = {"pullYICOL","pullZICOL","pullYOCOL","pullZOCOL",
			   "pullYIFXT","pullZIFXT","pullYOFXT","pullZOFXT"};
  Int_t ki = -1;
  for (Int_t k = 0; k < 8; k++) {
    if (! fName.BeginsWith(Sets[k]) ) continue;
    ki = k;
    kase = 2*(ki%4);
    break; 

  }
  if (ki < 0) return;
  fgOut = new TFile(Form("%smdf4Pull.root",Sets[ki]),"recreate");
  TDirectory *cdir = fgOut->mkdir(Sets[ki]);
  if (! cdir) return;
  cdir->cd();
#ifndef __CHECK__
  TString tableName = "TpcPullMDF4";
  TString cOut =  Form("%s%s.C", tableName.Data(), Sets[ki]);
  cout << "Create " << cOut << endl;
  out.open(cOut.Data());
  out << "TDataSet *CreateTable() {" << endl;
  out << "  if (!gROOT->GetClass(\"St_MDFCorrection4\")) return 0;" << endl;
  out << "  MDFCorrection4_st row;" << endl;
  out << "  St_MDFCorrection4 *tableSet = new St_MDFCorrection4(\"" << tableName.Data() << "\"," << nrows << ");" << endl;
#endif
  TCanvas *c1 = new TCanvas(Form("c%s",Sets[ki]),Sets[ki], 1200, 1600);
  c1->Divide(Nkase,4);
  Int_t ix = 0;
  // fgCase = SigmaMu[0-1] + 2*kase
  for (t.fgCase = kase; t.fgCase < kase + Nkase; t.fgCase++) {
    TString VarName("Sigma");
    if (t.fgCase != kase) VarName = "Mu";
    Int_t k = t.fgCase;
    TDirectory *cdir2 = cdir->mkdir(VarName);
    cdir2->cd();
#ifndef __CHECK__
    mdf4Fit(t);
    Int_t idx = k;
    out << "  memset(&row,0,tableSet->GetRowSize());" << endl;
    out << "  row.nrows =  " << nrows << "; //" << Sets[ki] << "\t" << fName.Data() << endl;
    out << "  row.idx   = " << Form("%2i", idx + 1) << ";//\t" << VarName.Data() <<  endl;
    cout << *gFit;
    out << *gFit;
    out << "  tableSet->AddAt(&row); // idx = " << idx + 1  << endl;
#endif
    ix++;
    cdir2->cd();
    t.Loop2();
    for (Int_t j = 0; j < kVar; j++) {
      c1->cd(Nkase*j+ix);
      if (prof[k][j]) {
	prof[k][j]->SetMinimum(-0.1);
	prof[k][j]->Draw();
	profC[k][j]->Draw("samel");
	profD[k][j]->Draw("same");
      }
      c1->Update();
    }
  }
  c1->SaveAs(".png");
#ifndef __CHECK__
  out << "  return (TDataSet *)tableSet;" << endl;
  out << "}" << endl;
#endif
  out.close();
  fgOut->Write();
}




