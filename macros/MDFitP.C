/*
  root.exe -q -b xyPad3C*.root Chain.C 'MDFitP.C+(tChain,7,20,20210129,5)' >& MakeTpcPadCorrectionMDF.log
*/
#ifndef __CINT__
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
#include "TGraph.h"
#include "TMath.h"
#include "TMultiDimFit.h"
#include "TString.h"
#include "TSystem.h"
#include "Ask.h"
#include "TH2.h"
#include "TStyle.h"
#include "TCanvas.h"
#include "TROOT.h"
#include "TChain.h"
#include "TFile.h"
#else
class TMultiDimFit;
#endif
enum EMDFPolyType {
  kMonomials,
  kChebyshev,
  kLegendre
};
TMultiDimFit* fit = 0;
ofstream out;
//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Tue Aug 30 16:10:50 2022 by ROOT version 5.34/39
// from TChain FitP/
//////////////////////////////////////////////////////////

#ifndef FitP_h
#define FitP_h


// Header file for the classes stored in the TTree if any.

// Fixed size dimensions of array or collections stored in the TTree if any.

class FitP {
public :
  TTree          *fChain;   //!pointer to the analyzed TTree or TChain
  Int_t           fCurrent; //!current Tree number in a TChain
  
  // Declaration of leaf types
  Float_t         i;
  Float_t         j;
  Float_t         x;
  Float_t         y;
  Float_t         mean;
  Float_t         rms;
  Float_t         peak;
  Float_t         dpeak;
  Float_t         entries;
  Float_t         chisq;
  Float_t         prob;
  Float_t         Npar;
  Float_t         muJ;
  Float_t         dmuJ;
  Float_t         NormL;
  Float_t         mu;
  Float_t         sigma;
  Float_t         p3;
  Float_t         p4;
  Float_t         p5;
  Float_t         p6;
  Float_t         p7;
  Float_t         p8;
  Float_t         p9;
  Float_t         p10;
  Float_t         p11;
  Float_t         p12;
  Float_t         p13;
  Float_t         p14;
  Float_t         p15;
  Float_t         p16;
  Float_t         p17;
  Float_t         dNormL;
  Float_t         dmu;
  Float_t         dsigma;
  Float_t         dp3;
  Float_t         dp4;
  Float_t         dp5;
  Float_t         dp6;
  Float_t         dp7;
  Float_t         dp8;
  Float_t         dp9;
  Float_t         dp10;
  Float_t         dp11;
  Float_t         dp12;
  Float_t         dp13;
  Float_t         dp14;
  Float_t         dp15;
  Float_t         dp16;
  Float_t         dp17;
  
  // List of branches
  TBranch        *b_i;   //!
  TBranch        *b_j;   //!
  TBranch        *b_x;   //!
  TBranch        *b_y;   //!
  TBranch        *b_mean;   //!
  TBranch        *b_rms;   //!
  TBranch        *b_peak;   //!
  TBranch        *b_dpeak;   //!
  TBranch        *b_entries;   //!
  TBranch        *b_chisq;   //!
  TBranch        *b_prob;   //!
  TBranch        *b_Npar;   //!
  TBranch        *b_muJ;   //!
  TBranch        *b_dmuJ;   //!
  TBranch        *b_NormL;   //!
  TBranch        *b_mu;   //!
  TBranch        *b_sigma;   //!
  TBranch        *b_p3;   //!
  TBranch        *b_p4;   //!
  TBranch        *b_p5;   //!
  TBranch        *b_p6;   //!
  TBranch        *b_p7;   //!
  TBranch        *b_p8;   //!
  TBranch        *b_p9;   //!
  TBranch        *b_p10;   //!
  TBranch        *b_p11;   //!
  TBranch        *b_p12;   //!
  TBranch        *b_p13;   //!
  TBranch        *b_p14;   //!
  TBranch        *b_p15;   //!
  TBranch        *b_p16;   //!
  TBranch        *b_p17;   //!
  TBranch        *b_dNormL;   //!
  TBranch        *b_dmu;   //!
  TBranch        *b_dsigma;   //!
  TBranch        *b_dp3;   //!
  TBranch        *b_dp4;   //!
  TBranch        *b_dp5;   //!
  TBranch        *b_dp6;   //!
  TBranch        *b_dp7;   //!
  TBranch        *b_dp8;   //!
  TBranch        *b_dp9;   //!
  TBranch        *b_dp10;   //!
  TBranch        *b_dp11;   //!
  TBranch        *b_dp12;   //!
  TBranch        *b_dp13;   //!
  TBranch        *b_dp14;   //!
  TBranch        *b_dp15;   //!
  TBranch        *b_dp16;   //!
  TBranch        *b_dp17;   //!
  
  FitP(TTree *tree=0);
  virtual ~FitP();
  virtual Int_t    Cut(Long64_t entry);
  virtual Int_t    GetEntry(Long64_t entry);
  virtual Long64_t LoadTree(Long64_t entry);
  virtual void     Init(TTree *tree);
  virtual void     Loop();
  virtual void     Mdf(Int_t max=7, Int_t maxTerm = 20);
  virtual Bool_t   Notify();
  virtual void     Show(Long64_t entry = -1);
  TString fTag;
  Int_t   fCase;
  Double_t fxx[2];
  Double_t fval;
  Double_t fdval;
};

#endif
#define FitP_cxx
TCanvas *c1 = 0;
void FitP::Loop()
{
  //   In a ROOT session, you can do:
  //      Root > .L FitP.C
  //      Root > FitP t
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

#ifdef FitP_cxx
FitP::FitP(TTree *tree) : fChain(0), fTag(), fCase(0)
{
  // if parameter tree is not specified (or zero), connect the file
  // used to generate this class and read the Tree.
  if (tree == 0) {
    assert(0);
    
  }
  Init(tree);
}

FitP::~FitP()
{
  if (!fChain) return;
  delete fChain->GetCurrentFile();
}

Int_t FitP::GetEntry(Long64_t entry)
{
  // Read contents of entry.
  if (!fChain) return 0;
  return fChain->GetEntry(entry);
}
Long64_t FitP::LoadTree(Long64_t entry)
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

void FitP::Init(TTree *tree)
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
  fChain->SetBranchAddress("x", &x, &b_x);
  fChain->SetBranchAddress("y", &y, &b_y);
  fChain->SetBranchAddress("mean", &mean, &b_mean);
  fChain->SetBranchAddress("rms", &rms, &b_rms);
  fChain->SetBranchAddress("peak", &peak, &b_peak);
  fChain->SetBranchAddress("dpeak", &dpeak, &b_dpeak);
  fChain->SetBranchAddress("entries", &entries, &b_entries);
  fChain->SetBranchAddress("chisq", &chisq, &b_chisq);
  fChain->SetBranchAddress("prob", &prob, &b_prob);
  fChain->SetBranchAddress("Npar", &Npar, &b_Npar);
  fChain->SetBranchAddress("muJ", &muJ, &b_muJ);
  fChain->SetBranchAddress("dmuJ", &dmuJ, &b_dmuJ);
  fChain->SetBranchAddress("NormL", &NormL, &b_NormL);
  fChain->SetBranchAddress("mu", &mu, &b_mu);
  fChain->SetBranchAddress("sigma", &sigma, &b_sigma);
  fChain->SetBranchAddress("p3", &p3, &b_p3);
  fChain->SetBranchAddress("p4", &p4, &b_p4);
  fChain->SetBranchAddress("p5", &p5, &b_p5);
  fChain->SetBranchAddress("p6", &p6, &b_p6);
  fChain->SetBranchAddress("p7", &p7, &b_p7);
  fChain->SetBranchAddress("p8", &p8, &b_p8);
  fChain->SetBranchAddress("p9", &p9, &b_p9);
  fChain->SetBranchAddress("p10", &p10, &b_p10);
  fChain->SetBranchAddress("p11", &p11, &b_p11);
  fChain->SetBranchAddress("p12", &p12, &b_p12);
  fChain->SetBranchAddress("p13", &p13, &b_p13);
  fChain->SetBranchAddress("p14", &p14, &b_p14);
  fChain->SetBranchAddress("p15", &p15, &b_p15);
  fChain->SetBranchAddress("p16", &p16, &b_p16);
  fChain->SetBranchAddress("p17", &p17, &b_p17);
  fChain->SetBranchAddress("dNormL", &dNormL, &b_dNormL);
  fChain->SetBranchAddress("dmu", &dmu, &b_dmu);
  fChain->SetBranchAddress("dsigma", &dsigma, &b_dsigma);
  fChain->SetBranchAddress("dp3", &dp3, &b_dp3);
  fChain->SetBranchAddress("dp4", &dp4, &b_dp4);
  fChain->SetBranchAddress("dp5", &dp5, &b_dp5);
  fChain->SetBranchAddress("dp6", &dp6, &b_dp6);
  fChain->SetBranchAddress("dp7", &dp7, &b_dp7);
  fChain->SetBranchAddress("dp8", &dp8, &b_dp8);
  fChain->SetBranchAddress("dp9", &dp9, &b_dp9);
  fChain->SetBranchAddress("dp10", &dp10, &b_dp10);
  fChain->SetBranchAddress("dp11", &dp11, &b_dp11);
  fChain->SetBranchAddress("dp12", &dp12, &b_dp12);
  fChain->SetBranchAddress("dp13", &dp13, &b_dp13);
  fChain->SetBranchAddress("dp14", &dp14, &b_dp14);
  fChain->SetBranchAddress("dp15", &dp15, &b_dp15);
  fChain->SetBranchAddress("dp16", &dp16, &b_dp16);
  fChain->SetBranchAddress("dp17", &dp17, &b_dp17);
  Notify();
}

Bool_t FitP::Notify()
{
  // The Notify() function is called when a new file is opened. This
  // can be either for a new TTree in a TChain or when when a new TTree
  // is started when using PROOF. It is normally not necessary to make changes
  // to the generated code, but the routine can be extended by the
  // user if needed. The return value is currently not used.
  
  return kTRUE;
}

void FitP::Show(Long64_t entry)
{
  // Print contents of entry.
  // If entry is not specified, print current entry
  if (!fChain) return;
  fChain->Show(entry);
}
Int_t FitP::Cut(Long64_t entry)
{
  // This function may be called from Loop.
  // returns  1 if entry is accepted.
  // returns -1 otherwise.
  Int_t iok = -1;
  Int_t ix = this->i;
  Int_t jy = this->j;
  if (ix == 0 || jy == 0)   return iok;
  if (dmu    > 0.10) return iok;
  if (dsigma > 0.10) return iok;
  if (chisq >  200.) return iok;
  if (TMath::Abs(mu) >= 0.5) return iok;
  if (TMath::Abs(y) > 200) return iok;
  if (TMath::Abs(y) <   4) return iok;
  fxx[0] = y;
  fxx[1] = x;
  if (fTag == "DPItanL" || fTag == "DPOtanL" || 
      fTag == "DPItanP" || fTag == "DPOtanP" ||
      fTag == "DTItanL" || fTag == "DTOtanL" ||
      fTag == "DTItanP" || fTag == "DTOtanP") {
    fxx[1] = x*x;                     // tan**2
    fxx[0] = 1 - TMath::Abs(y)/200;   // 1 - |z/200|
  }
  fval = mu;
  fdval = dmu;
  if (fCase == 0) { 
    fval = sigma*sigma;
    fdval = 2*sigma*dsigma;
  }
  
  return 1;
}
#endif // #ifdef FitP_cxx

// function object (functor) 
struct MDF2Func { 
  MDF2Func(TMultiDimFit * f, Int_t k = 0): fFunc(f), fcase(k) {}
  double operator() (double *x, double * )  const { 
    return fFunc->Eval(x);
  }
  double Eval (double *x, double * )  const { 
    Double_t y[2] = { 1 - TMath::Abs(x[0])/200., x[1]*x[1] };
    //    Double_t y[2] = {x[0], x[1]};
#if 0
    for (Int_t i = 0; i < 2; i++) {
      y[i] = TMath::Max(TMath::Min(y[i], fFunc->GetMaxVariables()->operator()(i)), fFunc->GetMinVariables()->operator()(i));
    }
#endif
    Double_t val = fFunc->Eval(y);
    if (! fcase) val = TMath::Sqrt(TMath::Max(0., val));
    return val;
  }
  TMultiDimFit * fFunc; 
  Int_t fcase;
};
//using namespace std;
void FitP::Mdf(Int_t max, Int_t maxTerm)
{  // fCase = 1 => mu; fCase = 0 => sigma
  //   In a ROOT session, you can do:
  //      Root > .L FitP.C
  //      Root > FitP t
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
  Int_t nVars       = 2;
  
  // make fit object and set parameters on it. 
  //  if (fit) delete fit;
  const Char_t *var = (fCase == 0) ? "sigma" : "mu";
  fit = new TMultiDimFit(nVars, TMultiDimFit::kMonomials,"vk");
  //  fit = new TMultiDimFit(nVars, TMultiDimFit::kChebyshev,"vk");
  //  fit = new TMultiDimFit(nVars, TMultiDimFit::kLegendre,"vk");
  fit->SetName(Form("MDF_%s_%s",var,fTag.Data()));
  gDirectory->Append(fit);
  TDirectory *dir = gDirectory->mkdir(fit->GetName());
  dir->cd();
  Int_t mPowers[]   = {max , max};
  fit->SetMaxPowers(mPowers);
  fit->SetMaxFunctions(1000);
  fit->SetMaxStudy(1000);
  fit->SetMaxTerms(maxTerm);
#if 0
  //  fit->SetPowerLimit(max);
  fit->SetPowerLimit(1);
  fit->SetMinAngle(); //10);
  fit->SetMaxAngle(1); //10);
#endif
  fit->SetMinRelativeError(0.01);
  
  Long64_t nentries = fChain->GetEntriesFast();
  Long64_t nbytes = 0, nb = 0;
  Long64_t nev = 0;
  for (Long64_t jentry=0; jentry<nentries;jentry++) {
    Long64_t ientry = LoadTree(jentry);
    if (ientry < 0) break;
    nb = fChain->GetEntry(jentry);   nbytes += nb;
    // tChain->Draw("mu:0.5*y+TMath::Nint(x)>>xy2P(768,0.5,24.5,200,-0.2,0.2)","dmu<0.1&&dsigma<0.05&&chisq<2e2&&mu>-0.8","prof")
    if (Cut(ientry) != 1) continue;
    fit->AddRow(fxx, fval, fdval*fdval);
    nev++;
  }
  
  fit->Print("p");
  // Print out the statistics
  fit->Print("s");
  cout << "SampleSize = " << fit->GetSampleSize() << "\tSumSqQuantity = " << fit->GetSumSqQuantity() << "\tSumSqAvgQuantity = " << fit->GetSumSqQuantity()/fit->GetSampleSize() << endl;
  //  if (fit->GetSumSqQuantity()/fit->GetSampleSize() < 5e-5) return;
  // Book histograms 
  //  fit->SetBinVarX(1000);
  //  fit->SetBinVarY(1000);
  fit->MakeHistograms();
  
  // Find the parameterization 
  fit->FindParameterization();
  
  // Print coefficents 
  fit->Print("rc");
  //
  Int_t i, j;
  // Assignment to coefficients vector.
  cout << "  row.PolyType = \t"      << fit->GetPolyType() << ";" << endl;
  cout << "  row.NVariables = \t"    << fit->GetNVariables() << ";" << endl;
  cout << "  row.NCoefficients = \t" << fit->GetNCoefficients() << ";" << endl;
  out << "  row.PolyType = \t"      << fit->GetPolyType() << ";" << endl;
  out << "  row.NVariables = \t"    << fit->GetNVariables() << ";" << endl;
  out << "  row.NCoefficients = \t" << fit->GetNCoefficients() << ";" << endl;
  for (i = 0; i < fit->GetNVariables(); i++) {
    cout << Form("  row.XMin[%2i] = %10.5g;", i,fit->GetMinVariables()->operator()(i));
    out << Form("  row.XMin[%2i] = %10.5g;", i,fit->GetMinVariables()->operator()(i));
  }
  cout << endl;  out << endl;
  for (i = 0; i < fit->GetNVariables(); i++) {
    cout << Form("  row.XMax[%2i] = %10.5g;", i,fit->GetMaxVariables()->operator()(i));
    out << Form("  row.XMax[%2i] = %10.5g;", i,fit->GetMaxVariables()->operator()(i));
  }
  cout << endl;  out << endl;
  for (i = 0; i < fit->GetNCoefficients(); i++) {
    for (j = 0; j < fit->GetNVariables(); j++) {
      cout << Form("  row.Power[%2i] = %2i;",i * fit->GetNVariables() + j,
		   fit->GetPowers()[fit->GetPowerIndex()[i] * fit->GetNVariables() + j]);
      out << Form("  row.Power[%2i] = %2i;",i * fit->GetNVariables() + j,
		  fit->GetPowers()[fit->GetPowerIndex()[i] * fit->GetNVariables() + j]);
    }
    cout << endl;    out << endl;
  }
  cout << "  row.DMean = \t"          << fit->GetMeanQuantity() << ";" << endl;
  out << "  row.DMean = \t"          << fit->GetMeanQuantity() << ";" << endl;
  for (i = 0; i < fit->GetNCoefficients(); i++) {
    cout << Form("  row.Coefficients[%2i]    = %15.5g;", i, fit->GetCoefficients()->operator()(i));
    out << Form("  row.Coefficients[%2i]    = %15.5g;", i, fit->GetCoefficients()->operator()(i));
    if ((i+1) %2 == 0) {cout << endl; out << endl;}
  }
  if (fit->GetNCoefficients()%2) {cout << endl; out << endl;}
  for (i = 0; i < fit->GetNCoefficients(); i++) {
    cout << Form("  row.CoefficientsRMS[%2i] = %15.5g;", i, fit->GetCoefficientsRMS()->operator()(i));
    out << Form("  row.CoefficientsRMS[%2i] = %15.5g;", i, fit->GetCoefficientsRMS()->operator()(i));
    if ((i+1) %2 == 0) {cout << endl; out << endl;}
  }
  if (fit->GetNCoefficients()%2) {cout << endl; out << endl;}
  MDF2Func *mdff = new MDF2Func(fit, fCase);
  TString fName(Form("F2_%s",fit->GetName()));
  TString cName(Form("c_%s",fit->GetName()));
  cout << "Create TF2 " << fName.Data() << endl;
  TF2 *f2 = new TF2(fName, mdff, &MDF2Func::Eval, -210, 210, -5, 5, 0, "MDF2Func","Eval");
  c1 = new TCanvas(cName, cName);
  f2->Draw("colz"); 
  c1->Update();
  c1->SaveAs(".png");
#if 0
  for (Long64_t jentry=0; jentry<nentries;jentry++) {
    Long64_t ientry = LoadTree(jentry);
    if (ientry < 0) break;
    nb = fChain->GetEntry(jentry);   nbytes += nb;
    // tChain->Draw("mu:0.5*y+TMath::Nint(x)>>xy2P(768,0.5,24.5,200,-0.2,0.2)","dmu<0.1&&dsigma<0.05&&chisq<2e2&&mu>-0.8","prof")
    if (Cut(ientry) != 1) continue;
    cout << fTag.Data() << "\tx = " << x << "\ty = " << y << "\tfxx[0] = " << fxx[0] << "\tfxx[1] = " << fxx[1] 
	 << "\tval = " << fval << " +/- " << fdval 
	 << "\tfit = " << fit->Eval(fxx) << "\tf2 = " << f2->Eval(x,y) << endl;
    nev++;
  }
#endif
}//____________________________________________________________________________
void MDFitP(TChain *tChain, Int_t max=2, Int_t maxTerm = 20) { //, Int_t date = 20190201, Int_t time = 709){
  if (! tChain) return;
  FitP t(tChain);
  TFile *fOut = new TFile("MDFitP.root","recreate");
  TString fName = gSystem->BaseName(tChain->GetFile()->GetName());
  Int_t index = fName.Index("GP");
  t.fTag = fName(0,index);
  TString tableName;
  if (*(t.fTag.Data()+2) == 'I') tableName = "iTPCHitErrorMDF";
  else                           tableName = "TpxHitErrorMDF";
  Int_t nrows = 8;
  Int_t offset = 0;
  if      (t.fTag.BeginsWith("DP") && t.fTag.Contains("tanP")) {offset = 0;}
  else if (t.fTag.BeginsWith("DT") && t.fTag.Contains("tanL")) {offset = 2; tableName += "_T";}
  else if (t.fTag.BeginsWith("DP") && t.fTag.Contains("tanL")) {offset = 4; tableName += "_PL";}
  else if (t.fTag.BeginsWith("DT") && t.fTag.Contains("tanP")) {offset = 6; tableName += "_TP";}
  //  TString cOut =  Form("%s.%8i.%06i.C", tableName.Data(),date,time);
  TString cOut =  Form("%s.y2019.C", tableName.Data());
  cout << "Create " << cOut << endl;
  out.open(cOut.Data());
  out << "TDataSet *CreateTable() {" << endl;
  out << "  if (!gROOT->GetClass(\"St_MDFCorrection\")) return 0;" << endl;
  out << "  MDFCorrection_st row;" << endl;
  out << "  St_MDFCorrection *tableSet = new St_MDFCorrection(\"" << tableName.Data() << "\"," << nrows << ");" << endl;
  for (t.fCase = 0; t.fCase < 2; t.fCase++) {
    Int_t idx = t.fCase + 1 + offset;
    const Char_t *var xs= (t.fCase == 0) ? "sigma" : "mu";
    cout << "Fit for " << var << "\tcase = " << t.fCase << endl;
    out << "  memset(&row,0,tableSet->GetRowSize());" << endl;
    out << "  row.nrows =  " << nrows << "; //" << var << "\t" << t.fTag.Data() << endl;
    out << "  row.idx   = " << Form("%2i", idx) << ";" << endl;
    fOut->cd();
    t.Mdf( max, maxTerm);
    out << "  tableSet->AddAt(&row," << idx << ");" << endl;
    if (Ask()) goto ENDL;
  }
 ENDL:
  out << "  return (TDataSet *)tableSet;" << endl;
  out << "}" << endl;
  out.close();
  fOut->Write();
}
//____________________________________________________________________________
