/*
  ~/work/Tpc/Alignment/T05 $ root.exe  'lDb.C(0,"r2019,CorrZ)' dPadI*.root Chain.C 'mdf4HitError.C+(tChain)'
   root.exe  'lDb.C(0,"r2019,CorrZ)' ../dPadI*.root Chain.C 'mdf4HitError.C+(tChain)'
   root.exe  'lDb.C(0,"r2019,CorrZ)' ../dPadO*.root Chain.C 'mdf4HitError.C+(tChain)'
   root.exe  'lDb.C(0,"r2019,CorrZ)' ../dTimeI*.root Chain.C 'mdf4HitError.C+(tChain)'
   root.exe  'lDb.C(0,"r2019,CorrZ)' ../dTimeO*.root Chain.C 'mdf4HitError.C+(tChain)'
__CHECK__
   root.exe  'lDb.C(0,"r2019,CorrZ)' ../dPadIGP11p5GeV.root Chain.C 'mdf4HitError.C+(tChain)'
__2023__
   root.exe  'lDb.C(0,"r2023,CorrZ)' ../dPadI*RF*.root Chain.C 'mdf4HitError.C+(tChain)'
   root.exe  'lDb.C(0,"r2023,CorrZ)' ../dPadO*RF*.root Chain.C 'mdf4HitError.C+(tChain)'
   root.exe  'lDb.C(0,"r2023,CorrZ)' ../dTimeI*RF*.root Chain.C 'mdf4HitError.C+(tChain)'
   root.exe  'lDb.C(0,"r2023,CorrZ)' ../dTimeO*RF*.root Chain.C 'mdf4HitError.C+(tChain)'
   foreach io (I O)
     foreach pt (dPad dTime)
       foreach f (RF RHF ZF)
         root.exe  'lDb.C(0,"r2023,CorrZ)' ../${pt}${io}*${f}*.root Chain.C 'mdf4HitError.C+(tChain)'
       end
     end
   end
   cat *I*RF*.C *I*RHF*.C *I*ZF*.C > TpcInnerHitErrorMDF4.C
   cat *O*RF*.C *O*RHF*.C *O*ZF*.C > TpcOuterHitErrorMDF4.C

*/
#define __CHECK__
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
enum {kIO = 2, kF = 3, kPT = 2, kSM = 2, kVar = 4};
TProfile *prof[kIO][kF][kPT][kSM][kVar] = {0};
TProfile *profC[kIO][kF][kPT][kSM][kVar] = {0};
TProfile *profD[kIO][kF][kPT][kSM][kVar] = {0};
TH2F     *h2[kIO][kF][kPT][kSM][kVar] = {0};     
TMultiDimFit* fit = 0;
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
  static Int_t fgIO; // 0 -> I, 1 -> O 
  static Int_t fgF;  // 0 -> RF/FF, 1 -> RHF/FHF, 2 -> ZF
  static Int_t fgPT; // 0 -> Pad, 1 -> Time
  static Int_t fgSM; // 0 -> Sigma, 1 -> Mu
  static Int_t fgCase; // = fgSM + kSM*(fgPT + kPT*(fgF + kF*fgIO))
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
  //   tChain->Draw("sigma","i&&j&&k0&&k1&&chisq>0&&chisq<100&&dmu<0.05&&dsigma<0.05&&abs(mu)<0.4","colz")
  if (i == 0 || j == 0 || k0 == 0 || k1 == 0) return -1;
  if (chisq <= 0 || chisq >  100) return -1;
  if (dmu   > 0.05) return -1;
  if (dsigma > 0.05) return -1;
  if (TMath::Abs(x) < 2) return -1;
  fxx[0] = 1. - TMath::Abs(x)/207.707; // Z
  if (fxx[0] < 0.0) return -1;
  fxx[1] = y*y; // tanP**2
  fxx[2] = z0*z0; // tanL**2
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
Int_t FitPS::fgCase =  0;
Int_t FitPS::fgIO   = -9;
Int_t FitPS::fgF    = -9;
Int_t FitPS::fgPT   = -9;
Int_t FitPS::fgSM   = -9;

#ifdef __CHECK__
#include "StDetectorDbMaker/StiTpcHitErrorMDF4.h"
#endif
Double_t mdf4(Double_t xx[4]) {
#ifndef __CHECK__
  Double_t val = fit->Eval(xx);
#else
  FitPS::fgCase = FitPS::fgSM + kSM*(FitPS::fgPT + kPT*(FitPS::fgF + kF*FitPS::fgIO));
  Int_t k = FitPS::fgCase%12;
  Double_t val = 0;
  if (FitPS::fgIO == 0) val = StiTpcInnerHitErrorMDF4::instance()->Eval(k,xx);
  else                  val = StiTpcOuterHitErrorMDF4::instance()->Eval(k,xx);
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
    const Char_t *vTitle;
  };
  Plot_t Plots[kVar] = {
    {"Z",        105, -210, 210, "; Z (cm)"},
    {"tanP",      40,   -2,   2, "; tan #phi"},
    {"tanL",     140,   -7,   7, "; tan #lambda"},
    {"AdcL",      20,    2,  12, "; ln(ADC)"}
  };
  TString Var("mu");
  TString VarT("; #mu");
  if (fgSM == 0) {Var = "sigma"; VarT = "; #sigma";}
  if (fgPT == 0)  Var += "Pad";
  else            Var += "Time";
  const Char_t *IO[kIO] = {"I","O"};
  Var += IO[fgIO];
  for (Int_t j = 0; j < kVar; j++) {
    TString Name = Var + Plots[j].vName; //(Form("%s%s",Var.Data(),Plots[j].vName));
    TString Title = Var + Plots[j].vTitle + " ; " + VarT ; // (Form("%s ; %s",Var.Data(), Plots[j].vName, VarT));
    prof[fgIO][fgF][fgPT][fgSM][j]  = new TProfile(Name, Var + Plots[j].vTitle + VarT, Plots[j].nx, Plots[j].xmin,Plots[j].xmax,"s");
    profC[fgIO][fgF][fgPT][fgSM][j]  = new TProfile(Name + "C", Var + " predicted" + Plots[j].vTitle + VarT , Plots[j].nx, Plots[j].xmin,Plots[j].xmax,"");
    profC[fgIO][fgF][fgPT][fgSM][j]->SetMarkerColor(2); profC[fgIO][fgF][fgPT][fgSM][j]->SetLineColor(2); 
    profD[fgIO][fgF][fgPT][fgSM][j]  = new TProfile(Name + "D", Var + " differenced" + Plots[j].vTitle + VarT, Plots[j].nx, Plots[j].xmin,Plots[j].xmax,"s");
    profD[fgIO][fgF][fgPT][fgSM][j]->SetMarkerColor(4); profD[fgIO][fgF][fgPT][fgSM][j]->SetLineColor(4); 
    h2[fgIO][fgF][fgPT][fgSM][j] = new TH2F(Name + "2D",Var + "difference" + Plots[j].vTitle + VarT,Plots[j].nx, Plots[j].xmin,Plots[j].xmax,100,-0.25,0.25);
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
      prof[fgIO][fgF][fgPT][fgSM][j]->Fill(fx(j),fvalA);
      profC[fgIO][fgF][fgPT][fgSM][j]->Fill(fx(j),pred);
      profD[fgIO][fgF][fgPT][fgSM][j]->Fill(fx(j),fvalA-pred);
      h2[fgIO][fgF][fgPT][fgSM][j]->Fill(fx(j),fvalA-pred);
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
    fit->AddRow(fxx, fval, fdval*fdval);
    nev++;
  }
}
//using namespace std;
//________________________________________________________________________________
Double_t funcMDF(Double_t *x, Double_t *p=0) {
  if (! fit ) return 0;
  return fit->Eval(x, p);
}
//________________________________________________________________________________
#include "operatorTMultiDim.h"
//________________________________________________________________________________
void mdf4Fit(FitPS &t) {
  // Global data parameters 
  Int_t nVars      =  4;
  Int_t maxTerm    = 20;
  // make fit object and set parameters on it. 
  //  fit = new TMultiDimFit(nVars, TMultiDimFit::kMonomials,"vk");
  //  TMultiDimFit::EMDFPolyType type = (TMultiDimFit::EMDFPolyType) 0;
  TMultiDimFit::EMDFPolyType type = (TMultiDimFit::EMDFPolyType) 1; // Chebyshev
  fit = new TMultiDimFit(nVars, type,"vk");
  Int_t max = 3;
  Int_t mPowers[]   = { max, max+1, max+1, max};
  fit->SetMaxPowers(mPowers);
  fit->SetMaxFunctions(10000);
  fit->SetMaxStudy(10000);
  fit->SetMaxTerms(maxTerm);
  fit->SetPowerLimit(max);
  fit->SetMinAngle(10);
  fit->SetMaxAngle(10);
  fit->SetMinRelativeError(.01);
  // variables to hold the temporary input data 
  
  // Print out the start parameters
  fit->Print("p");
  // Fill data  
  t.Loop();
  // Print out the statistics
  fit->Print("s");
  // Book histograms 
  fit->MakeHistograms();
  
  // Find the parameterization 
  fit->FindParameterization();
  
  // Print coefficents 
  fit->Print("rc");
}
//________________________________________________________________________________
void mdf4HitError(TChain *tChain = 0) {
  if (! tChain ) return;
  FitPS t(tChain);
  TString fName(gSystem->BaseName(tChain->GetFile()->GetName()));
  Int_t kase = 0;
  Int_t Nkase = 2;
  Int_t nrows = 4*3; // for 3 field options
  const Char_t *Sets[4] = {"dPadI","dTimeI","dPadO","dTimeO"}; 
  Int_t ki = -1;
  for (Int_t k = 0; k < 4; k++) {
    if (! fName.BeginsWith(Sets[k]) ) continue;
    ki = k;
    kase = 2*ki;
    t.fgIO = k/2;
    t.fgPT = k%2;
    break;
  }
  if (ki < 0) return;
  const Char_t *FieldOpt[3] = {"RF", "RHF", "ZF"};
  Int_t lf = 0;
  for (Int_t l = 0; l < 3; l++) {
    if (!  fName.Contains(FieldOpt[l])) continue;
    lf = l;
    t.fgF = l;
    break;
  }
  TString subSet(Form("%s_%s",Sets[ki],FieldOpt[t.fgF]));
  TString Out = subSet + "_mdf4HitError.root";
  TFile *fOut = new TFile(Out,"recreate");;
  TDirectory *cdir = fOut->mkdir(subSet);
  if (! cdir) return;
#ifndef __CHECK__
  TString tableName;
  if (ki < 2) tableName = "TpcInnerHitErrorMDF4";
  else        tableName = "TpcOuterHitErrorMDF4";
  TString cOut =  Form("%s%s_%s.C", tableName.Data(), Sets[ki], FieldOpt[lf]);
  cout << "Create " << cOut << endl;
  out.open(cOut.Data());
  out << "TDataSet *CreateTable() {" << endl;
  out << "  if (!gROOT->GetClass(\"St_MDFCorrection4\")) return 0;" << endl;
  out << "  MDFCorrection4_st row;" << endl;
  out << "  St_MDFCorrection4 *tableSet = new St_MDFCorrection4(\"" << tableName.Data() << "\"," << nrows << ");" << endl;
#endif
  TString cTitle(Form("c%s%s",Sets[ki],FieldOpt[lf]));
  TCanvas *c1 = new TCanvas(cTitle,cTitle, 1200, 1600);
  c1->Divide(Nkase,4);
  Int_t ix = 0;
  for (t.fgSM = 0; t.fgSM < kSM; t.fgSM++) {
    TString VarName("Sigma");
    if (t.fgSM) VarName = "Mu";
    cdir->mkdir(VarName)->cd();
#ifndef __CHECK__
    mdf4Fit(t);
    Int_t idx = t.fgSM + kSM*(t.fgPT + kPT*t.fgF) + 1
    out << "  memset(&row,0,tableSet->GetRowSize());" << endl;
    out << "  row.nrows =  " << nrows << "; //" << Sets[ki] << "\t" << fName.Data() << endl;
    out << "  row.idx   = " << Form("%2i", idx + 1) << ";//\t" << VarName.Data() <<  endl;
    cout << *fit;
    out << *fit;
    out << "  tableSet->AddAt(&row); // idx = " << idx + 1  << endl;
#endif
    ix++;
    t.Loop2();
    for (Int_t j = 0; j < kVar; j++) {
      c1->cd(Nkase*j+ix);
      if (prof[t.fgIO][t.fgF][t.fgPT][t.fgSM][j]) {
	prof[t.fgIO][t.fgF][t.fgPT][t.fgSM][j]->SetMinimum(-0.1);
	prof[t.fgIO][t.fgF][t.fgPT][t.fgSM][j]->Draw();
	profC[t.fgIO][t.fgF][t.fgPT][t.fgSM][j]->Draw("samel");
	profD[t.fgIO][t.fgF][t.fgPT][t.fgSM][j]->Draw("same");
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
  fOut->Write();
}
