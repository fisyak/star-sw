// root.exe -q -b EandB.C+ >& EandB.log &
#include "Riostream.h"
#include <stdio.h>
#include "TSystem.h"
#include "TMath.h"
#include "TH1.h"
#include "TH2.h"
#include "TH3.h"
#include "TProfile.h"
#include "TProfile2D.h"
#include "TStyle.h"
#include "TF1.h"
#include "TTree.h"
#include "TChain.h"
#include "TFile.h"
#include "TNtuple.h"
#include "TCanvas.h"
#include "TMinuit.h"
#include "TSpectrum.h"
#include "TString.h"
#include "TLine.h"
#include "TText.h"
#include "TROOT.h"
#include "TList.h"
#include "TPolyMarker.h"
#include "StBichsel/Bichsel.h"
#include "TDirIter.h"
#include "TTreeIter.h"
#include "StarClassLibrary/StThreeVectorD.hh"
#include "TObjArray.h"
#include "TObjString.h"
#include "TCanvas.h"
#include "TChainElement.h"
#include "TLegend.h"
//#include "StEandBDirMaker/Tracklet.h"
#include "Chain.C"
using namespace std;
//________________________________________________________________________________
TFile *fOut = 0;
//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Wed Apr  9 15:10:10 2025 by ROOT version 5.34/39
// from TTree TrackletTree/the TPC residuals between Inner and Outer sub sectors
// found on file: hlt_26092030_10_01_000.root
//////////////////////////////////////////////////////////
class TrackletTree {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

   // Declaration of leaf types
 //Tracklet        *Tracklet;
   Int_t           run;
   Int_t           sector;
   Int_t           row;
   Int_t           nhits;
   Double_t        AdcSum;
   Double_t        x0;
   Double_t        tX;
   Double_t        y0;
   Double_t        tY;
   Double_t        z0;
   Double_t        x0T;
   Double_t        tXT;
   Double_t        y0T;
   Double_t        tYT;
   Double_t        z0T;
  //   Double_t        x0G;
   Double_t        tXG;
  //   Double_t        y0G;
   Double_t        tYG;
  //   Double_t        z0G;
   Double_t        BG_mX1;
   Double_t        BG_mX2;
   Double_t        BG_mX3;
   Double_t        BL_mX1;
   Double_t        BL_mX2;
   Double_t        BL_mX3;
   Double_t        BT_mX1;
   Double_t        BT_mX2;
   Double_t        BT_mX3;
   Double_t        posG_mX1;
   Double_t        posG_mX2;
   Double_t        posG_mX3;
   Double_t        posL_mX1;
   Double_t        posL_mX2;
   Double_t        posL_mX3;
   Double_t        dirL_mX1;
   Double_t        dirL_mX2;
   Double_t        dirL_mX3;
   Double_t        posT_mX1;
   Double_t        posT_mX2;
   Double_t        posT_mX3;
   Double_t        dirT_mX1;
   Double_t        dirT_mX2;
   Double_t        dirT_mX3;
   Double_t        dirG_mX1;
   Double_t        dirG_mX2;
   Double_t        dirG_mX3;
   Double_t        dirST_mX1;
   Double_t        dirST_mX2;
   Double_t        dirST_mX3;
   Double_t        posRMSG_mX1;
   Double_t        posRMSG_mX2;
   Double_t        posRMSG_mX3;
   Double_t        posRMSL_mX1;
   Double_t        posRMSL_mX2;
   Double_t        posRMSL_mX3;
   Double_t        posRMST_mX1;
   Double_t        posRMST_mX2;
   Double_t        posRMST_mX3;

   // List of branches
   TBranch        *b_Tracklet_run;   //!
   TBranch        *b_Tracklet_sector;   //!
   TBranch        *b_Tracklet_row;   //!
   TBranch        *b_Tracklet_nhits;   //!
   TBranch        *b_Tracklet_AdcSum;   //!
   TBranch        *b_Tracklet_x0;   //!
   TBranch        *b_Tracklet_tX;   //!
   TBranch        *b_Tracklet_y0;   //!
   TBranch        *b_Tracklet_tY;   //!
   TBranch        *b_Tracklet_z0;   //!
   TBranch        *b_Tracklet_x0T;   //!
   TBranch        *b_Tracklet_tXT;   //!
   TBranch        *b_Tracklet_y0T;   //!
   TBranch        *b_Tracklet_tYT;   //!
   TBranch        *b_Tracklet_z0T;   //!
  //   TBranch        *b_Tracklet_x0G;   //!
   TBranch        *b_Tracklet_tXG;   //!
  //   TBranch        *b_Tracklet_y0G;   //!
   TBranch        *b_Tracklet_tYG;   //!
  //   TBranch        *b_Tracklet_z0G;   //!
   TBranch        *b_Tracklet_BG_mX1;   //!
   TBranch        *b_Tracklet_BG_mX2;   //!
   TBranch        *b_Tracklet_BG_mX3;   //!
   TBranch        *b_Tracklet_BL_mX1;   //!
   TBranch        *b_Tracklet_BL_mX2;   //!
   TBranch        *b_Tracklet_BL_mX3;   //!
   TBranch        *b_Tracklet_BT_mX1;   //!
   TBranch        *b_Tracklet_BT_mX2;   //!
   TBranch        *b_Tracklet_BT_mX3;   //!
   TBranch        *b_Tracklet_posG_mX1;   //!
   TBranch        *b_Tracklet_posG_mX2;   //!
   TBranch        *b_Tracklet_posG_mX3;   //!
   TBranch        *b_Tracklet_posL_mX1;   //!
   TBranch        *b_Tracklet_posL_mX2;   //!
   TBranch        *b_Tracklet_posL_mX3;   //!
   TBranch        *b_Tracklet_dirL_mX1;   //!
   TBranch        *b_Tracklet_dirL_mX2;   //!
   TBranch        *b_Tracklet_dirL_mX3;   //!
   TBranch        *b_Tracklet_posT_mX1;   //!
   TBranch        *b_Tracklet_posT_mX2;   //!
   TBranch        *b_Tracklet_posT_mX3;   //!
   TBranch        *b_Tracklet_dirT_mX1;   //!
   TBranch        *b_Tracklet_dirT_mX2;   //!
   TBranch        *b_Tracklet_dirT_mX3;   //!
   TBranch        *b_Tracklet_dirG_mX1;   //!
   TBranch        *b_Tracklet_dirG_mX2;   //!
   TBranch        *b_Tracklet_dirG_mX3;   //!
   TBranch        *b_Tracklet_dirST_mX1;   //!
   TBranch        *b_Tracklet_dirST_mX2;   //!
   TBranch        *b_Tracklet_dirST_mX3;   //!
   TBranch        *b_Tracklet_posRMSG_mX1;   //!
   TBranch        *b_Tracklet_posRMSG_mX2;   //!
   TBranch        *b_Tracklet_posRMSG_mX3;   //!
   TBranch        *b_Tracklet_posRMSL_mX1;   //!
   TBranch        *b_Tracklet_posRMSL_mX2;   //!
   TBranch        *b_Tracklet_posRMSL_mX3;   //!
   TBranch        *b_Tracklet_posRMST_mX1;   //!
   TBranch        *b_Tracklet_posRMST_mX2;   //!
   TBranch        *b_Tracklet_posRMST_mX3;   //!

  static Bool_t         FieldTypeFF;
  TH2F* SecRow;
  TProfile2D* SecRowNhits;
  TProfile2D* SecRowAdcL;
  enum {NIO = 3, NSYS = 3, NVAR = 6};
  TH3F *hists[NSYS][NIO][NVAR]; // = {0};
  //  TH3F *hists[NSYS*NIO*NVAR]; // = {0};
   TrackletTree(TTree *tree=0);
   virtual ~TrackletTree();
   virtual Int_t    Cut(Long64_t entry = 0);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop(Int_t N = -1);
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
  void BookHistograms(const Char_t *opt = "");
  void FillHistograms();
  void FitHistograms();
};

Bool_t TrackletTree::FieldTypeFF = kFALSE;
TrackletTree::TrackletTree(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("hlt_26092030_10_01_000.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("hlt_26092030_10_01_000.root");
      }
      f->GetObject("TrackletTree",tree);

   }
   Init(tree);
}

TrackletTree::~TrackletTree()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t TrackletTree::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t TrackletTree::LoadTree(Long64_t entry)
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

void TrackletTree::Init(TTree *tree)
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

   fChain->SetBranchAddress("run", &run, &b_Tracklet_run);
   fChain->SetBranchAddress("sector", &sector, &b_Tracklet_sector);
   fChain->SetBranchAddress("row", &row, &b_Tracklet_row);
   fChain->SetBranchAddress("nhits", &nhits, &b_Tracklet_nhits);
   fChain->SetBranchAddress("AdcSum", &AdcSum, &b_Tracklet_AdcSum);
   fChain->SetBranchAddress("x0", &x0, &b_Tracklet_x0);
   fChain->SetBranchAddress("tX", &tX, &b_Tracklet_tX);
   fChain->SetBranchAddress("y0", &y0, &b_Tracklet_y0);
   fChain->SetBranchAddress("tY", &tY, &b_Tracklet_tY);
   fChain->SetBranchAddress("z0", &z0, &b_Tracklet_z0);
   fChain->SetBranchAddress("x0T", &x0T, &b_Tracklet_x0T);
   fChain->SetBranchAddress("tXT", &tXT, &b_Tracklet_tXT);
   fChain->SetBranchAddress("y0T", &y0T, &b_Tracklet_y0T);
   fChain->SetBranchAddress("tYT", &tYT, &b_Tracklet_tYT);
   fChain->SetBranchAddress("z0T", &z0T, &b_Tracklet_z0T);
   //   fChain->SetBranchAddress("x0G", &x0G, &b_Tracklet_x0G);
   fChain->SetBranchAddress("tXG", &tXG, &b_Tracklet_tXG);
   //   fChain->SetBranchAddress("y0G", &y0G, &b_Tracklet_y0G);
   fChain->SetBranchAddress("tYG", &tYG, &b_Tracklet_tYG);
   //   fChain->SetBranchAddress("z0G", &z0G, &b_Tracklet_z0G);
   fChain->SetBranchAddress("BG.mX1", &BG_mX1, &b_Tracklet_BG_mX1);
   fChain->SetBranchAddress("BG.mX2", &BG_mX2, &b_Tracklet_BG_mX2);
   fChain->SetBranchAddress("BG.mX3", &BG_mX3, &b_Tracklet_BG_mX3);
   fChain->SetBranchAddress("BL.mX1", &BL_mX1, &b_Tracklet_BL_mX1);
   fChain->SetBranchAddress("BL.mX2", &BL_mX2, &b_Tracklet_BL_mX2);
   fChain->SetBranchAddress("BL.mX3", &BL_mX3, &b_Tracklet_BL_mX3);
   fChain->SetBranchAddress("BT.mX1", &BT_mX1, &b_Tracklet_BT_mX1);
   fChain->SetBranchAddress("BT.mX2", &BT_mX2, &b_Tracklet_BT_mX2);
   fChain->SetBranchAddress("BT.mX3", &BT_mX3, &b_Tracklet_BT_mX3);
   fChain->SetBranchAddress("posG.mX1", &posG_mX1, &b_Tracklet_posG_mX1);
   fChain->SetBranchAddress("posG.mX2", &posG_mX2, &b_Tracklet_posG_mX2);
   fChain->SetBranchAddress("posG.mX3", &posG_mX3, &b_Tracklet_posG_mX3);
   fChain->SetBranchAddress("posL.mX1", &posL_mX1, &b_Tracklet_posL_mX1);
   fChain->SetBranchAddress("posL.mX2", &posL_mX2, &b_Tracklet_posL_mX2);
   fChain->SetBranchAddress("posL.mX3", &posL_mX3, &b_Tracklet_posL_mX3);
   fChain->SetBranchAddress("dirL.mX1", &dirL_mX1, &b_Tracklet_dirL_mX1);
   fChain->SetBranchAddress("dirL.mX2", &dirL_mX2, &b_Tracklet_dirL_mX2);
   fChain->SetBranchAddress("dirL.mX3", &dirL_mX3, &b_Tracklet_dirL_mX3);
   fChain->SetBranchAddress("posT.mX1", &posT_mX1, &b_Tracklet_posT_mX1);
   fChain->SetBranchAddress("posT.mX2", &posT_mX2, &b_Tracklet_posT_mX2);
   fChain->SetBranchAddress("posT.mX3", &posT_mX3, &b_Tracklet_posT_mX3);
   fChain->SetBranchAddress("dirT.mX1", &dirT_mX1, &b_Tracklet_dirT_mX1);
   fChain->SetBranchAddress("dirT.mX2", &dirT_mX2, &b_Tracklet_dirT_mX2);
   fChain->SetBranchAddress("dirT.mX3", &dirT_mX3, &b_Tracklet_dirT_mX3);
   fChain->SetBranchAddress("dirG.mX1", &dirG_mX1, &b_Tracklet_dirG_mX1);
   fChain->SetBranchAddress("dirG.mX2", &dirG_mX2, &b_Tracklet_dirG_mX2);
   fChain->SetBranchAddress("dirG.mX3", &dirG_mX3, &b_Tracklet_dirG_mX3);
   fChain->SetBranchAddress("dirST.mX1", &dirST_mX1, &b_Tracklet_dirST_mX1);
   fChain->SetBranchAddress("dirST.mX2", &dirST_mX2, &b_Tracklet_dirST_mX2);
   fChain->SetBranchAddress("dirST.mX3", &dirST_mX3, &b_Tracklet_dirST_mX3);
   fChain->SetBranchAddress("posRMSG.mX1", &posRMSG_mX1, &b_Tracklet_posRMSG_mX1);
   fChain->SetBranchAddress("posRMSG.mX2", &posRMSG_mX2, &b_Tracklet_posRMSG_mX2);
   fChain->SetBranchAddress("posRMSG.mX3", &posRMSG_mX3, &b_Tracklet_posRMSG_mX3);
   fChain->SetBranchAddress("posRMSL.mX1", &posRMSL_mX1, &b_Tracklet_posRMSL_mX1);
   fChain->SetBranchAddress("posRMSL.mX2", &posRMSL_mX2, &b_Tracklet_posRMSL_mX2);
   fChain->SetBranchAddress("posRMSL.mX3", &posRMSL_mX3, &b_Tracklet_posRMSL_mX3);
   fChain->SetBranchAddress("posRMST.mX1", &posRMST_mX1, &b_Tracklet_posRMST_mX1);
   fChain->SetBranchAddress("posRMST.mX2", &posRMST_mX2, &b_Tracklet_posRMST_mX2);
   fChain->SetBranchAddress("posRMST.mX3", &posRMST_mX3, &b_Tracklet_posRMST_mX3);
   Notify();
}
void TrackletTree::BookHistograms(const Char_t *opt ) {
  fOut->cd();
    cout<<"Creating histograms...";
    Int_t  sec_nbins = 24;
    Double_t sec_min = 0.5;
    Double_t sec_max = 24.5;
    
    Int_t row_nbins = 72;
    Double_t row_min = 0.5;
    Double_t row_max = 72.5;

    Int_t tY_nbins = 400;
    Double_t tY_min = -20.0;
    Double_t tY_max = +20.0;

    SecRow      = new TH2F("SecRow","Sector vs row : row : sector",row_nbins,row_min,row_max,24,0.5,24.5);
    SecRowNhits = new TProfile2D("SecRowNHits","<Hnits> vs Sector and row : row : sector",row_nbins,row_min,row_max,24,0.5,24.5);
    SecRowAdcL  = new TProfile2D("SecRowAdc","<log<Adc/nhits>)> vs Sector and row : row : sector",row_nbins,row_min,row_max,24,0.5,24.5);
    const Char_t *nSYS[NSYS] = {     "",  "T",      "G"};
    const Char_t *tSYS[NSYS] = {"Sector","TPC","Global"};
    const Char_t *nIO[NIO]   = {     "I",  "O", "All"};
    const Char_t *tIO[NIO]   = {"Inner","Outer","All"};
    const Char_t *nVAR[NVAR] = {"tX","tY", "BX", "BY",   "dtBX",    "dtBY"};
    const Char_t *tVAR[NVAR] = {"tX","tY", "BX", "BY", "dtX-BX", "dtY -BY"};
    for (Int_t s  = 0; s  < NSYS; s++) 
      for (Int_t io = 0; io < NIO; io++) 
	for (Int_t v  = 0; v  < NVAR; v++) {
	  TString Name(Form("%s%s%s",nSYS[s],nIO[io],nVAR[v]));
	  TString Title(Form("%s %s %s ; sector ; drift[cm];  %s [mrad]",tSYS[s],tIO[io],tVAR[v],tVAR[v]));
	  //	  Int_t siov = v + NVAR*(io + NSYS*s);
	  hists[s][io][v] = new TH3F(Name, Title, sec_nbins,sec_min,sec_max, 50, 0., 200., tY_nbins,tY_min,tY_max);
	  //	  hists[siov] = new TH3F(Name, Title, sec_nbins,sec_min,sec_max, 50, 0., 200., tY_nbins,tY_min,tY_max);
	}
    cout<<"\t [DONE]"<<endl;
}

Bool_t TrackletTree::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void TrackletTree::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t TrackletTree::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}

void TrackletTree::Loop(Int_t N)
{
//   In a ROOT session, you can do:
//      Root > .L TrackletTree.C
//      Root > TrackletTree t
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
   if (N > 0 && N < nentries) nentries = N;
   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue;
      FillHistograms();
   }
}
void TrackletTree::FillHistograms() {
  //    static Double_t sqrt3 = TMath::Sqrt(3.);
  if (nhits < 25) return;
  Float_t AdcL = TMath::Log(AdcSum/nhits);
  if (posRMSL_mX3 < 10.0 || posRMSL_mX3 > 70) return;
  //    if (posL.z()+sqrt3*posRMSL_mX3 > 210) return; // vers.5
  //    if (posL.z() < 50 || posRMSL_mX3 > 15) return;
  if (AdcL < 5 || AdcL > 8) return;
#if 0
  //    if (AdcSum/nhits < 150) return;
  if (! FieldTypeFF &&         //false - RFF; true - FF
      (( sector== 5 && row==13) || 
       ( sector== 6 && row==34) || 
       ( sector==13 && row==36) || 
       ( sector== 7 && row== 1) || 
	 ( sector==18 && row==35))) return;
#endif
  SecRow->Fill(row,sector);
  SecRowNhits->Fill(row,sector,nhits);
  SecRowAdcL->Fill(row,sector,AdcL);
  Int_t io = 0;
  if (row > 40) io = 1;
  Double_t Vars[NVAR] = {0};
  for (Int_t s = 0; s < NSYS; s++) {
    if (s == 0) {// Localsector
      Vars[0] = tX;
      Vars[1] = tY;
      Vars[2] = BL_mX1/BL_mX3;
      Vars[3] = BL_mX2/BL_mX3;
    } else if (s == 1) {// TPC
      Vars[0] = tXT;
      Vars[1] = tYT;
      Vars[2] = BT_mX1/BT_mX3;
      Vars[3] = BT_mX2/BT_mX3;
    } else {
      Vars[0] = tXG;
      Vars[1] = tYG;
      Vars[2] = BG_mX1/BG_mX3;
      Vars[3] = BG_mX2/BG_mX3;
    }
    Vars[4] = Vars[0] - Vars[2];
    Vars[5] = Vars[1] - Vars[3];
    for (Int_t v = 0; v < NVAR; v++) {
      //      Int_t siov = v + NVAR*(io + NSYS*s);
      hists[s][io][v]->Fill(sector,z0, 1e3*Vars[v]);
      hists[s][2 ][v]->Fill(sector,z0, 1e3*Vars[v]);
//       hists[siov]->Fill(sector,z0, 1e3*Vars[v]);
//       siov = v + NVAR*(2 + NSYS*s);
//       hists[siov]->Fill(sector,z0, 1e3*Vars[v]);
    }
  }
}
//________________________________________________________________________________
void TrackletTree::FitHistograms() {
  cout<<"Creating 2D histograms slicesY...";
  for (Int_t s  = 0; s  < NSYS; s++) 
    for (Int_t io = 0; io < NIO; io++) 
      for (Int_t v  = 0; v  < NVAR; v++) {
	//	Int_t siov = v + NVAR*(io + NSYS*s);
	TH2D *h2 = (TH2D * ) hists[s][io][v]->Project3D("zx");
	//	TH2D *h2 = (TH2D * ) hists[siov]->Project3D("zx");
	h2->FitSlicesY();
      }
  cout<<"\t [DONE]"<<endl;
}

//________________________________________________________________________________
void EandB(Int_t nevents = -1, const Char_t *select = "hlt*.root", const Char_t *out = "EandB.root") {
  tChain = Chain(select, "TrackletTree");
  fOut               = new TFile(out,"recreate");
  TrackletTree *T = new TrackletTree(tChain);
  Int_t nentries = (Int_t)tChain->GetEntries();
  if (nevents > 0)  nevents = TMath::Min(nevents, nentries);
  else              nevents = nentries;
  
  T->FieldTypeFF = kTRUE;
#if 0
  if (! fOut->cd(F)) {fOut->mkdir(F); fOut->cd(F); cout << "Create directory " << F.Data() << endl;}
  if (F.Contains("RF",TString::kIgnoreCase)) T->FieldTypeFF = kFALSE;
#endif
  T->BookHistograms();
  T->Loop(nevents);
  T->FitHistograms();
  fOut->Write();
}
//________________________________________________________________________________
Double_t phiN(Double_t phi) {
  while (TMath::Abs(phi) > 180.) {
    if (phi > 180) phi -= 360;
    if (phi <-180) phi += 360;
  }
  return phi;
}
//________________________________________________________________________________
Double_t Phi(Double_t sector) {
  Double_t phi;
  if (sector <= 12.5) {
    phi =  (360 + 90 - 30* sector      ); 
  } else { 
    phi =  (      90 + 30*(sector - 12));
  }
  return TMath::DegToRad()*phi;
}
//________________________________________________________________________________
Double_t func(Double_t *x, Double_t *p) {
  //  Int_t sec = TMath::Nint(x[0]);
  return p[0] + p[1]*TMath::Sin(TMath::DegToRad()*(p[2] - Phi(x[0])));
}
//________________________________________________________________________________
Double_t funcSumtX(Double_t *x, Double_t *p) {
  Double_t dPhi = p[2] + Phi(x[0]); // 
  Double_t val = p[1]*TMath::Cos(TMath::DegToRad()*(dPhi));
  //  if (x[0] < 12.5) val = -val;
  return p[0] + val;
}
//________________________________________________________________________________
Double_t funcSumtY(Double_t *x, Double_t *p) {
  Double_t dPhi = p[2] + Phi(x[0]); // phi_0 - phi;
  Double_t val =  p[0] + p[1]*TMath::Sin(TMath::DegToRad()*(dPhi));
  if (x[0] < 12.5) val = - val;
  return val;
}
//________________________________________________________________________________
Double_t funcSumtXN(Double_t *x, Double_t *p) {
  Double_t phi = Phi(x[0]); //  p[1] = delta = alpha - lambda, [2] = beta
  Double_t val = p[0] + p[1]*TMath::Sin(phi);
#if 1
  if (x[0] < 12.5) val += p[2]*TMath::Cos(phi);
  else             val -= p[2]*TMath::Cos(phi);
#else
  val += p[2]*TMath::Cos(phi);
#endif
  return val;
}
//________________________________________________________________________________
Double_t funcSumtYN(Double_t *x, Double_t *p) {
  Double_t phi = Phi(x[0]); // p[1] = delta = alpha - lambda, [2] = beta
  Double_t val = p[0] + p[1]*TMath::Cos(phi);
  if (x[0] < 12.5) val -= p[2]*TMath::Sin(phi);
  else             val += p[2]*TMath::Sin(phi);
  return val;
}
#if 0
//________________________________________________________________________________
Double_t funcDiftX(Double_t *x, Double_t *p) {
  Double_t dPhi = p[2] - Phi(x[0]); // phi_0 - phi;
  Double_t val = p[1]*TMath::Cos(TMath::DegToRad()*(dPhi));
  if (x[0] > 12.5) val = - val;
  return p[0] + val;
}
//________________________________________________________________________________
Double_t funcDiftY(Double_t *x, Double_t *p) {
  Double_t dPhi = p[2] - Phi(x[0]); // phi_0 - phi;
  return p[0] + p[1]*TMath::Sin(TMath::DegToRad()*(dPhi));
}
#endif
//________________________________________________________________________________
Double_t functS(Double_t *x, Double_t *p) { 
  Double_t offset = p[0];  
  Double_t alpha  = p[1]; // -(alpha - lambda)
  Double_t beta   = p[2]; 
  Double_t b_rho  = p[3]; 
  Double_t Phi0   = p[4]; 
  Int_t            we = 0; // West; 
  if (x[0] > 12.5) we = 2; // East 
  Int_t    k = TMath::Nint(p[5]) + we; /* 0 => tX, 1 => tY */ 
  Double_t phi = Phi(x[0]);  
  Double_t val = 0; 
  switch (k) {  
    /* tXWS */ case 0: val =    alpha*TMath::Sin(phi) +beta* TMath::Cos(phi) - b_rho*TMath::Cos(Phi0); break; 
    /* tYWS */ case 1: val =   -alpha*TMath::Cos(phi) +beta* TMath::Sin(phi) + b_rho*TMath::Sin(Phi0); break;
    /* tXES */ case 2: val =-( -alpha*TMath::Sin(phi) -beta* TMath::Cos(phi) + b_rho*TMath::Cos(Phi0)); break;				       
    /* tYES */ case 3: val =-( -alpha*TMath::Cos(phi) +beta* TMath::Sin(phi) - b_rho*TMath::Sin(Phi0)); break; 
  default: break;
  };
  return offset + val;
}
//________________________________________________________________________________
TF1 *Func(const Char_t *name, Int_t xy = 0) {
  TF1 *f = new TF1(name, functS,0.5,24.5,6);
  //  f->SetParNames("o","#alpha-#lambda","#beta","b_{#rho}","#Phi","XY");
  f->SetParNames("o","#alpha","#beta","b_{#rho}","#Phi","XY");
  f->SetParameters(0,0,0,0,0,0);
  //  f->FixParameter(0,0);
  f->SetParLimits(3,-1,1); 
  f->FixParameter(3,0); // b_rho => 0
  f->FixParameter(4,0); // #Phi => 0
  f->FixParameter(5,xy);
  return f;
}
//________________________________________________________________________________
Double_t funcdtB(Double_t *x, Double_t *p) {
  Double_t offset = p[0];  
  Double_t alpha  = p[1]; 
  Double_t beta   = p[2]; 
  Int_t    k      = p[3]; // k = 0 -> dTX - BX, k = 1 -> dTY - BY
  Double_t phi = Phi(x[0]);  
  Double_t val = offset;
  if (k == 0) {
    val +=    beta*TMath::Cos(phi) - alpha*TMath::Sin(phi);
  } else {
    val += (- beta*TMath::Sin(phi)) - alpha*TMath::Cos(phi);
  }
  return val;
} 
//________________________________________________________________________________
TF1 *FuncBt(Int_t xy = 0) {
  TString name = (xy == 0) ? "FitdtBX" : "FitdtBY";
  TF1 *f = (TF1 *) gROOT->GetListOfFunctions()->FindObject(name);
  if (! f) {
    f = new TF1(name, funcdtB,0.5,24.5,4);
    f->SetParNames("o","#alpha","#beta","XY");
    f->SetParameters(0,0,0,0);
    f->FixParameter(0,0);
    f->SetParLimits(1,-2,2); 
    f->SetParLimits(2,-2,2); 
    f->FixParameter(3,xy);
  }
  return f;
}
//________________________________________________________________________________
void Draw(TString Opt, TString tag ) {
  if (! gFile) return;
  TObjString *objs;
#if 0  
  TObjArray *arrayn = Names.Tokenize("&|");
  Int_t Nplots = arrayn->GetEntries();
  TString names[Nplots];
  TString title[Nplots];
  TIter nextN(arrayn);
  Int_t i = 0;
  while ((objs = (TObjString *) nextN())) {
    names[i] = objs->GetString();
    title[i] = names[i];
    title[i].ReplaceAll("vs"," versus ");
    title[i].ReplaceAll("Sector"," sector ");
    title[i].ReplaceAll("_1","");
    i++;
    if (i >= Nplots) break;
  }
  delete array;
#else
  enum { Nplots = 4};
  TString names[Nplots];
  TString title[Nplots];
  const Char_t *plotN[4] = {"XvsSectorInner_1","XvsSectorOuter_1","YvsSectorInner_1","YvsSectorOuter_1"};
  for (Int_t i = 0; i < Nplots; i++) {
    names[i] = tag; names[i] += plotN[i];
    title[i] = names[i];
    title[i].ReplaceAll("vs"," versus ");
    title[i].ReplaceAll("Sector"," sector ");
    title[i].ReplaceAll("_1","");
  }
#endif
  TObjArray *array = Opt.Tokenize("&|");
  TIter next(array);
  TString opt = Opt; opt += tag;
  TCanvas *c1 = (TCanvas *) gROOT->GetListOfCanvases()->FindObject(opt);
  //  if (! c1) c1 = new TCanvas(opt,opt,1000,1200);
  if (! c1) c1 = new TCanvas(opt,opt,800,1000);
  c1->Clear();
  Int_t nx = 2;
  Int_t ny = (Nplots-1)/2 + 1;
  c1->Divide(nx,ny);
  //  TF1 *fW = new TF1("fW","[0]+[1]*TMath::Sin(-TMath::DegToRad()*((360 + 90 - 30*x       )+[2]))",0.5,12.5);
  //  TF1 *fW = new TF1("fW",funcSumtXN,0.5,12.5,3);
  //  TF1 *fs[6] = { Func("fWx",0), Func("fEx",0), Func("fWESumtX",0),
  //		 Func("fWy",1), Func("fEy",1), Func("fWESumtY",1)};
  const Char_t *NamesF[6] = {"fWx", "fEx", "fWESumtX",
			     "fWy", "fEy", "fWESumtY"};
//   TF1 *fWx      = fs[0];
//   TF1 *fEx      = fs[1];
//   TF1 *fWESumtX = fs[2];
//   TF1 *fWy      = fs[3];
//   TF1 *fEy      = fs[4];
//   TF1 *fWESumtY = fs[5];
  TF1 *f = 0;
  for (Int_t i = 1; i <= Nplots; i++) {
    next.Reset();
    TVirtualPad *pad = c1->cd(i);
    TH1F *frame = pad->DrawFrame(0.5,-1.0,24.5,1.5,title[i-1]);
    //    frame->SetTitle(title[i-1]);
    frame->SetXTitle("sector");
    Int_t itXY = 0;
    if (names[i-1].BeginsWith("tX") || names[i-1].BeginsWith("tBX") || names[i-1].BeginsWith("BX"))  frame->SetYTitle("t_{X} [mrad]");
    if (names[i-1].BeginsWith("tY") || names[i-1].BeginsWith("tBY") || names[i-1].BeginsWith("BY")) {frame->SetYTitle("t_{Y} [mrad]"); itXY = 1;}
    Int_t color = 0;
    TLegend *l = new TLegend(0.1,0.6,0.9,0.9);
    l->Draw();
    TH1D *hfr[10]; memset(hfr, 0, sizeof(hfr));
    TString Tags[10];
    Int_t NF = 0;
    while ((objs = (TObjString *) next())) {
      cout << objs->GetString() << endl;
      Tags[NF] = objs->GetString();
      TString hName(Form("%s/%s",Tags[NF].Data(),names[i-1].Data()));
      hfr[NF] = (TH1D *) gFile->Get(hName);
      cout << " Histogram " << hName;
      if (hfr[NF]) cout << " has been found" << endl;
      else {cout << " has not been found" << endl; continue;}
      NF++;
      if (NF > 10) break;
    }
    if (NF == 2  && hfr[0] && hfr[1]) {
      hfr[2] = hfr[3] = 0;
      hfr[2] = new TH1D(*hfr[0]);
      hfr[2]->Scale(0.5);
      hfr[2]->Add(hfr[1],0.5), hfr[2]->SetName(Form("sum%sand%s",hfr[0]->GetName(),hfr[1]->GetName()));
      Tags[2] = Tags[0]; Tags[2] += "+";  Tags[2] += Tags[1];     
      //      } else {
      // 	hfr[3] = new TH1D(*hfr[0]);
      // 	hfr[3]->Add(hfr[1],-1.), hfr[3]->SetName(Form("dif%sand%s",hfr[0]->GetName(),hfr[1]->GetName()));
      // 	Tags[3] = Tags[0]; Tags[3] += "-";  Tags[3] += Tags[1];     
      //      }
      NF++;
    }
    const Char_t *sides[3] = {"West:","East:","All:"};
    Double_t lim[3][2] = {{0.5,12.5},{12.5,24.5},{0.5,24.5}};
    TString line;
    ofstream out;
    TString Out("EandB.out");
    if (gSystem->AccessPathName(Out)) out.open(Out, ios::out); //"Results.list",ios::out | ios::app);
    else                              out.open(Out, ios::app);
    out << Opt.Data() << "|" << tag.Data() << endl;
    for (Int_t j = 0; j < NF; j++) {
      color++;
      if (! hfr[j]) continue;
      hfr[j]->SetStats(0);
      hfr[j]->SetMarkerColor(color);
      hfr[j]->Draw("same");
      l->AddEntry(hfr[j],Tags[j]);
      if (j >= 2) {
	for (Int_t wel = 0; wel < 3; wel++) {
	  //	f = fs[3*itXY + wel];
	  f = Func(NamesF[3*itXY + wel],itXY);
	  f->SetLineColor(color);
	  f->SetMarkerColor(color);
	  line = sides[wel]; cout << f->GetName() << line.Data() << " limits :" << lim[wel][0] << "," <<  lim[wel][1] << endl;
	  hfr[j]->Fit(f,"er+","same",lim[wel][0],lim[wel][1]);
	  //	f = hfr[j]->GetFunction(f->GetName());
	  TString hN(hfr[j]->GetName());
	  hN.ReplaceAll("sum","");
	  hN.ReplaceAll("vsSectorInner_1","I");
	  hN.ReplaceAll("vsSectorOuter_1","O");
	  TString And("and");
	  Int_t m = hN.Index("and");
	  if (m > 0) {
	    And += TString(hN.Data(),m);
	    hN.ReplaceAll(And.Data(),"");
	  }
	  hN.ReplaceAll("andtBYSectorInner_1","");
	  hN.ReplaceAll("andtBYSectorOuter_1","");
	  hN.ReplaceAll("andtBXSectorInner_1","");
	  hN.ReplaceAll("andtBXSectorOuter_1","");
	  out << hN.Data();
	  if (f) {
	    for (Int_t p = 0; p < 5; p++)	{
	      if (f->GetParError(p) > 0) {
		if (p != 4) 
		  line += Form(" %s (%5.2f+/-%4.2f)",f->GetParName(p), f->GetParameter(p),f->GetParError(p));
		else 
		  line += Form("%s(%5.2f+/-%4.2f)",f->GetParName(p), 
			       phiN(TMath::RadToDeg()*f->GetParameter(p)),TMath::RadToDeg()*f->GetParError(p));
	      }
	    }
	    cout << line.Data() << endl;
	    l->AddEntry(f,line);
	    out << line.Data() << endl;
	  }
	}
      }
    }
    out.close();
  }
  delete array;
}
//________________________________________________________________________________
void Draw(TString opt="FF2.NewOAll|RFF2.NewOAll", Int_t k = 0) {
  if      (k == 0) Draw(opt,"tB");
  else if (k == 1) Draw(opt,"B");
  else             Draw(opt,"t");
}
/*
  1.  Compare 1D and 2D for both FF and RFF, no correction (1Dvs2D_NoCorrections)
  Over all shift in tX (inner -0.6 mrad, outer -0.8 mrad for 1D => 2D). <tX East> ~ 0
  No effect on tY. 
  <tY_inner_West> ~ 0.3 mrad, <tY_inner_East> ~ 0
  <tY_outer_West> ~ 1.2 mrad, <tY_inner_East> ~ 0.4 mrad
2. 2D OshortR.
     There is offset between FF and RFF. West (Outer  to East
3. Align 
new jobs

FF2.OShortR.OBmap.Align2 -

RFF2B -
RFF2.AlignB -
RFF2.Align2 -
RFF2.OShortRB -
RFF2.OShortR.AlignB -
RFF2.OShortR.Align2 -
RFF2.OShortR.OBmapB -
RFF2.OShortR.OBmap.AlignB -
RFF2.OShortR.OBmap.Align2 -



FF1.root			RFF1.root			
FF1.Align.root                  RFF1.Align.root			
FF2.root			RFF2.root                       
FF2.Align.root			RFF2.Align.root			
                                RFF2.Align2.root		
FF2.OShortR.root		RFF2.OShortR.root
FF2.OShortR.Align.root		RFF2.OShortR.Align.root
                                RFF2.OShortR.Align2.root		
FF2.OShortR.OBmap.root		RFF2.OShortR.OBmap.root
FF2.OShortR.OBmap.Align.root	RFF2.OShortR.OBmap.Align.root	
FF2.OShortR.OBmap.Align2.root	RFF2.OShortR.OBmap.Align2.root	

1. NoCorrections

================================================================================
09/13/13
Align2 => Align (no mechanical distortion for OFC)

================================================================================
09/18/13 
    (  1 -g  b  x)
R = (  g  1 -a  y)
    ( -b  a  1  z)
    (  0  0  0  1)
Rx: matrix([1,0,0,0],[0,1,-a,0],[0,a,1,0],[0,0,0,1])$
Ry: matrix([1,0,b,0],[0,1,0,0],[-b,0,1,0],[0,0,0,1])$
Rz: matrix([1,-g,0,0],[g,1,0,0],[0,0,1,0],[0,0,0,1])$

root.exe tpcDbTest.C
StTpcDb::instance()->FieldCage()
 westClockError  -0.00043 : ==> 0.43 mrad
                  (1     0      0)    (0)    (     0)
RotateX(alpha) =  (0     1 -alpha) x  (0) =  (-alpha)
                  (0 alpha      1)    (1)    (     1)
                  (1     0 beta)
RotateY(beta)  =  (0     1    0)
                  (-beta 0    1)

                  (1     -gamma      0)
RotateZ(gamma) =  (gamma      1      0)
                  (0          0      1)

Default 
root.exe [2] StTpcDb::instance()->Tpc2GlobalMatrix()->Print()
matrix Tpc2Glob - tr=1  rot=1  refl=0  scl=0
  1.000000    0.000000    0.000190    Tx =  -0.178000           beta = 0.19 mrad, alpha = 0.044 mrad
  0.000000    1.000000   -0.000044    Ty =  -0.675200
 -0.000190    0.000044    1.000000    Tz =  -0.080860

root.exe [5] StTpcDb::instance()->TpcHalf(0)->Print()  east
matrix  - tr=1  rot=1  refl=0  scl=0
  1.000000    0.000000    0.000000    Tx =   0.000000
  0.000000    1.000000    0.000000    Ty =   0.000000
  0.000000    0.000000    1.000000    Tz =   0.000000

root.exe [6] StTpcDb::instance()->TpcHalf(1)->Print() west
matrix  - tr=1  rot=1  refl=0  scl=0
  1.000000    0.000000    0.000000    Tx =   0.000000
  0.000000    1.000000    0.000000    Ty =   0.000000
  0.000000    0.000000    1.000000    Tz =   0.000000

-------------------
Survey
root.exe [1] StTpcDb::instance()->Tpc2GlobalMatrix()->Print()
matrix Tpc2Glob - tr=1  rot=1  refl=0  scl=0
  1.000000   -0.000000   -0.000420    Tx =  -0.245000        beta = -0.42 mrad
  0.000000    1.000000    0.000000    Ty =  -0.143100
  0.000420   -0.000000    1.000000    Tz =  -0.196100

root.exe [2] StTpcDb::instance()->TpcHalf(0)->Print()   east
matrix  - tr=1  rot=1  refl=0  scl=0
  1.000000   -0.000390   -0.000030    Tx =   0.006700        gamma = 0.39 mrad, alpha = -0.38 mrad, beta  = -0.03 mrad
  0.000390    1.000000    0.000380    Ty =  -0.002300
  0.000030   -0.000380    1.000000    Tz =   0.000000

root.exe [3] StTpcDb::instance()->TpcHalf(1)->Print()  west
matrix  - tr=1  rot=1  refl=0  scl=0
  1.000000    0.000030    0.000310    Tx =   0.026000        gamma = -0.03 mrad, alpha = 0.36 mrad, beta = 0.31 mrad
 -0.000030    1.000000   -0.000360    Ty =  -0.071200
 -0.000310    0.000360    1.000000    Tz =   0.000000


List of productions
FF and RFF field directions
"1"       1D-cluster finder no. correction
"1.Align" -"-        with my alignment   
"1.MC     -"- ideal MC

"2"       2D-cluster finder no. correction
"2.Align" -"-        with my alignment (E west turned)
"2.MC"    -"-  ideal MC
"2.OShortR"
"2.OShortR.Align"         
"2.OShortR.OBmap.eval"

"2.OShortR.OBmap"
"2.OShortR.OBmap.Align"
"2.Align2"               my alignment with (E and W the same E direction)
"2.OShortR.Align2
"2.OShortR.OBmap.Align2"   
"2.OAll"                 ExB,OShortR,OBmap,OPr13,OIFC,OSectorAlign
"2OAllW                  const_1 == const_2 in MagUtil
"2OAllWA                + my alignment
"AllWAR"                  my alignment, const_1 != const_2 in MagUtil, 1-st iteration with mag rotation
"OAllA.R2"                -"-, 2nd interation with mag rotation (lambda => - lambda)
"OAllA.R3"                -"-, 3rd interation with mag rotation (lambda => - lambda, phi0 => -phi0)
"OAllA.R4"                -"-, 4th interation with mag rotation (lambda =>   lambda, phi0 => -phi0)
"OAll.eval"
================================================================================
11/01/13 
2NewOAll               + new alignment + all corrections

12/09/13
rotate mag.field with missing resistor 2.2 Mohm
FF2.Short2.2Mom|FF2.Short2.2Mom |tB tBXIWest: o ( 0.09+/-0.01) a ( 0.20+/-0.02) b ( 0.16+/-0.02) tBXIEast: o (-0.03+/-0.02) a ( 0.11+/-0.02) b ( 0.06+/-0.02) tBXIAll: o ( 0.04+/-0.01) a ( 0.16+/-0.02) b ( 0.11+/-0.02)
FF2.Short2.2Mom|FF2.Short2.2Mom |tB tBXOWest: o (-0.04+/-0.01) a ( 0.11+/-0.01) b ( 0.28+/-0.01) tBXOEast: o ( 0.08+/-0.01) a (-0.01+/-0.01) b ( 0.04+/-0.01) tBXOAll: o ( 0.02+/-0.01) a ( 0.05+/-0.01) b ( 0.17+/-0.01)
FF2.Short2.2Mom|FF2.Short2.2Mom |tB tBYIWest: o (-0.45+/-0.00) a ( 0.07+/-0.00) b ( 0.33+/-0.00) tBYIEast: o (-0.02+/-0.00) a (-0.08+/-0.00) b ( 0.16+/-0.00) tBYIAll: o (-0.09+/-0.00) a (-0.07+/-0.00) b ( 0.18+/-0.00)
FF2.Short2.2Mom|FF2.Short2.2Mom |tB tBYOWest: o (-0.12+/-0.01) a ( 0.18+/-0.01) b ( 0.23+/-0.01) tBYOEast: o (-0.09+/-0.01) a ( 0.08+/-0.01) b ( 0.09+/-0.01) tBYOAll: o (-0.11+/-0.01) a ( 0.14+/-0.01) b ( 0.17+/-0.01)

FF2.Short2.2Mom|RFF2.Short2.2Mom|tB tBXIWest: o ( 0.05+/-0.02) a ( 0.07+/-0.02) b ( 0.23+/-0.02) tBXIEast: o (-0.05+/-0.02) a (-0.05+/-0.02) b ( 0.07+/-0.02) tBXIAll: o ( 0.00+/-0.01) a ( 0.01+/-0.02) b ( 0.15+/-0.02)
FF2.Short2.2Mom|RFF2.Short2.2Mom|tB tBXOWest: o (-0.01+/-0.01) a ( 0.01+/-0.01) b ( 0.25+/-0.01) tBXOEast: o (-0.01+/-0.01) a (-0.06+/-0.01) b ( 0.06+/-0.01) tBXOAll: o (-0.01+/-0.01) a (-0.03+/-0.01) b ( 0.16+/-0.01)
FF2.Short2.2Mom|RFF2.Short2.2Mom|tB tBYIWest: o (-0.44+/-0.00) a ( 0.02+/-0.00) b ( 0.17+/-0.00) tBYIEast: o (-0.03+/-0.00) a (-0.11+/-0.00) b ( 0.02+/-0.00) tBYIAll: o (-0.08+/-0.00) a (-0.10+/-0.00) b ( 0.04+/-0.00)
FF2.Short2.2Mom|RFF2.Short2.2Mom|tB tBYOWest: o (-0.10+/-0.01) a ( 0.06+/-0.01) b ( 0.21+/-0.01) tBYOEast: o (-0.09+/-0.01) a (-0.01+/-0.01) b ( 0.03+/-0.01) tBYOAll: o (-0.09+/-0.01) a ( 0.03+/-0.01) b ( 0.13+/-0.01)

FF2.Alpha0.15|RFF2.Alpha0.15    |tB tBXIWest: o ( 0.04+/-0.01) a ( 0.08+/-0.02) b ( 0.28+/-0.02) tBXIEast: o (-0.04+/-0.01) a (-0.04+/-0.02) b ( 0.12+/-0.02) tBXIAll: o (-0.00+/-0.01) a ( 0.02+/-0.01) b ( 0.20+/-0.01)
FF2.Alpha0.15|RFF2.Alpha0.15    |tB tBXOWest: o (-0.02+/-0.01) a ( 0.02+/-0.01) b ( 0.29+/-0.01) tBXOEast: o (-0.00+/-0.01) a (-0.06+/-0.01) b ( 0.11+/-0.01) tBXOAll: o (-0.01+/-0.01) a (-0.02+/-0.01) b ( 0.20+/-0.01)
FF2.Alpha0.15|RFF2.Alpha0.15    |tB tBYIWest: o (-0.45+/-0.00) a ( 0.02+/-0.00) b ( 0.20+/-0.00) tBYIEast: o (-0.03+/-0.00) a (-0.11+/-0.00) b ( 0.05+/-0.00) tBYIAll: o (-0.09+/-0.00) a (-0.11+/-0.00) b ( 0.08+/-0.00)
FF2.Alpha0.15|RFF2.Alpha0.15    |tB tBYOWest: o (-0.10+/-0.01) a ( 0.06+/-0.01) b ( 0.24+/-0.01) tBYOEast: o (-0.09+/-0.01) a (-0.01+/-0.01) b ( 0.07+/-0.01) tBYOAll: o (-0.09+/-0.01) a ( 0.03+/-0.01) b ( 0.16+/-0.01)

FF2.Alpha-.15|RFF2.Alpha-.15    |tB tBXIWest: o ( 0.04+/-0.01) a ( 0.08+/-0.02) b ( 0.18+/-0.02) tBXIEast: o (-0.05+/-0.01) a (-0.04+/-0.02) b ( 0.05+/-0.02) tBXIAll: o (-0.00+/-0.01) a ( 0.02+/-0.01) b ( 0.12+/-0.01)
FF2.Alpha-.15|RFF2.Alpha-.15    |tB tBXOWest: o (-0.02+/-0.01) a ( 0.02+/-0.01) b ( 0.20+/-0.01) tBXOEast: o (-0.01+/-0.01) a (-0.05+/-0.01) b ( 0.03+/-0.01) tBXOAll: o (-0.01+/-0.01) a (-0.02+/-0.01) b ( 0.12+/-0.01)
FF2.Alpha-.15|RFF2.Alpha-.15    |tB tBYIWest: o (-0.44+/-0.00) a ( 0.02+/-0.00) b ( 0.15+/-0.00) tBYIEast: o (-0.03+/-0.00) a (-0.11+/-0.00) b (-0.02+/-0.00) tBYIAll: o (-0.10+/-0.00) a (-0.15+/-0.00) b ( 0.00+/-0.00)
FF2.Alpha-.15|RFF2.Alpha-.15    |tB tBYOWest: o (-0.10+/-0.01) a ( 0.06+/-0.01) b ( 0.17+/-0.01) tBYOEast: o (-0.09+/-0.01) a (-0.01+/-0.01) b ( 0.00+/-0.01) tBYOAll: o (-0.09+/-0.01) a ( 0.03+/-0.01) b ( 0.09+/-0.01)

FF2.Alpha-.30|RFF2.Alpha-.30    |tB tBXIWest: o ( 0.04+/-0.01) a ( 0.08+/-0.02) b ( 0.14+/-0.02) tBXIEast: o (-0.04+/-0.01) a (-0.04+/-0.02) b ( 0.00+/-0.02) tBXIAll: o (-0.00+/-0.01) a ( 0.03+/-0.01) b ( 0.07+/-0.01)
FF2.Alpha-.30|RFF2.Alpha-.30    |tB tBXOWest: o (-0.02+/-0.01) a ( 0.02+/-0.01) b ( 0.16+/-0.01) tBXOEast: o (-0.00+/-0.01) a (-0.05+/-0.01) b (-0.01+/-0.01) tBXOAll: o (-0.01+/-0.01) a (-0.02+/-0.01) b ( 0.08+/-0.01)
FF2.Alpha-.30|RFF2.Alpha-.30    |tB tBYIWest: o (-0.45+/-0.00) a ( 0.02+/-0.00) b ( 0.13+/-0.00) tBYIEast: o (-0.03+/-0.00) a (-0.11+/-0.00) b (-0.05+/-0.00) tBYIAll: o (-0.09+/-0.00) a (-0.11+/-0.00) b (-0.03+/-0.00)
FF2.Alpha-.30|RFF2.Alpha-.30    |tB tBYOWest: o (-0.10+/-0.01) a ( 0.06+/-0.01) b ( 0.14+/-0.01) tBYOEast: o (-0.09+/-0.01) a (-0.00+/-0.01) b (-0.03+/-0.01) tBYOAll: o (-0.09+/-0.01) a ( 0.03+/-0.01) b ( 0.06+/-0.01)

FF2.Alpha-.45|RFF2.Alpha-.45    |tB tBXIWest: o ( 0.02+/-0.01) a ( 0.09+/-0.02) b ( 0.10+/-0.02) tBXIEast: o (-0.03+/-0.02) a (-0.03+/-0.02) b (-0.04+/-0.02) tBXIAll: o (-0.01+/-0.01) a ( 0.03+/-0.02) b ( 0.03+/-0.01)
FF2.Alpha-.45|RFF2.Alpha-.45    |tB tBXOWest: o (-0.02+/-0.01) a ( 0.02+/-0.01) b ( 0.12+/-0.01) tBXOEast: o (-0.01+/-0.01) a (-0.05+/-0.01) b (-0.06+/-0.01) tBXOAll: o (-0.01+/-0.01) a (-0.01+/-0.01) b ( 0.03+/-0.01)
FF2.Alpha-.45|RFF2.Alpha-.45    |tB tBYIWest: o (-0.45+/-0.00) a ( 0.02+/-0.00) b ( 0.10+/-0.00) tBYIEast: o (-0.03+/-0.00) a (-0.11+/-0.00) b (-0.08+/-0.00) tBYIAll: o (-0.10+/-0.00) a (-0.11+/-0.00) b (-0.06+/-0.00)
FF2.Alpha-.45|RFF2.Alpha-.45    |tB tBYOWest: o (-0.10+/-0.01) a ( 0.06+/-0.01) b ( 0.11+/-0.01) tBYOEast: o (-0.09+/-0.01) a (-0.01+/-0.01) b (-0.06+/-0.01) tBYOAll: o (-0.09+/-0.01) a ( 0.03+/-0.01) b ( 0.03+/-0.01)

FF2.Alpha-.60|RFF2.Alpha-.60    |tB tBXIWest: o ( 0.03+/-0.01) a ( 0.08+/-0.02) b ( 0.06+/-0.02) tBXIEast: o (-0.04+/-0.02) a (-0.03+/-0.02) b (-0.09+/-0.02) tBXIAll: o (-0.00+/-0.01) a ( 0.03+/-0.02) b (-0.01+/-0.01)
FF2.Alpha-.60|RFF2.Alpha-.60    |tB tBXOWest: o (-0.02+/-0.01) a ( 0.02+/-0.01) b ( 0.08+/-0.01) tBXOEast: o (-0.01+/-0.01) a (-0.05+/-0.01) b (-0.10+/-0.01) tBXOAll: o (-0.01+/-0.01) a (-0.01+/-0.01) b (-0.01+/-0.01)
FF2.Alpha-.60|RFF2.Alpha-.60    |tB tBYIWest: o (-0.46+/-0.00) a ( 0.02+/-0.00) b ( 0.08+/-0.00) tBYIEast: o (-0.03+/-0.00) a (-0.10+/-0.00) b (-0.11+/-0.00) tBYIAll: o (-0.11+/-0.00) a (-0.09+/-0.00) b (-0.11+/-0.00)
FF2.Alpha-.60|RFF2.Alpha-.60    |tB tBYOWest: o (-0.10+/-0.01) a ( 0.06+/-0.01) b ( 0.08+/-0.01) tBYOEast: o (-0.09+/-0.01) a (-0.01+/-0.01) b (-0.10+/-0.01) tBYOAll: o (-0.09+/-0.01) a ( 0.03+/-0.01) b (-0.00+/-0.01)

FF2.Alpha-.75|RFF2.Alpha-.75    |tB tBXIWest: o ( 0.05+/-0.01) a ( 0.09+/-0.02) b ( 0.02+/-0.02) tBXIEast: o (-0.05+/-0.01) a (-0.03+/-0.02) b (-0.13+/-0.02) tBXIAll: o ( 0.00+/-0.01) a ( 0.03+/-0.01) b (-0.05+/-0.01)
FF2.Alpha-.75|RFF2.Alpha-.75    |tB tBXOWest: o (-0.02+/-0.01) a ( 0.02+/-0.01) b ( 0.03+/-0.01) tBXOEast: o (-0.00+/-0.01) a (-0.05+/-0.01) b (-0.14+/-0.01) tBXOAll: o (-0.01+/-0.01) a (-0.02+/-0.01) b (-0.05+/-0.01)
FF2.Alpha-.75|RFF2.Alpha-.75    |tB tBYIWest: o (-0.47+/-0.00) a ( 0.02+/-0.00) b ( 0.05+/-0.00) tBYIEast: o (-0.03+/-0.00) a (-0.10+/-0.00) b (-0.14+/-0.00) tBYIAll: o (-0.11+/-0.00) a (-0.09+/-0.00) b (-0.13+/-0.00)
FF2.Alpha-.75|RFF2.Alpha-.75    |tB tBYOWest: o (-0.10+/-0.01) a ( 0.06+/-0.01) b ( 0.04+/-0.01) tBYOEast: o (-0.08+/-0.01) a (-0.01+/-0.01) b (-0.13+/-0.01) tBYOAll: o (-0.09+/-0.01) a ( 0.03+/-0.01) b (-0.04+/-0.01)
===========

FF2.Alpha0.15|RFF2.Alpha0.15    |tB tBXIWest: o ( 0.04+/-0.01) a ( 0.08+/-0.02) b ( 0.28+/-0.02) tBXIEast: o (-0.04+/-0.01) a (-0.04+/-0.02) b ( 0.12+/-0.02) tBXIAll: o (-0.00+/-0.01) a ( 0.02+/-0.01) b ( 0.20+/-0.01)
FF2.Short2.2Mom|RFF2.Short2.2Mom|tB tBXIWest: o ( 0.05+/-0.02) a ( 0.07+/-0.02) b ( 0.23+/-0.02) tBXIEast: o (-0.05+/-0.02) a (-0.05+/-0.02) b ( 0.07+/-0.02) tBXIAll: o ( 0.00+/-0.01) a ( 0.01+/-0.02) b ( 0.15+/-0.02)
FF2.Alpha-.15|RFF2.Alpha-.15    |tB tBXIWest: o ( 0.04+/-0.01) a ( 0.08+/-0.02) b ( 0.18+/-0.02) tBXIEast: o (-0.05+/-0.01) a (-0.04+/-0.02) b ( 0.05+/-0.02) tBXIAll: o (-0.00+/-0.01) a ( 0.02+/-0.01) b ( 0.12+/-0.01)
FF2.Alpha-.30|RFF2.Alpha-.30    |tB tBXIWest: o ( 0.04+/-0.01) a ( 0.08+/-0.02) b ( 0.14+/-0.02) tBXIEast: o (-0.04+/-0.01) a (-0.04+/-0.02) b^( 0.00+/-0.02) tBXIAll: o (-0.00+/-0.01) a ( 0.03+/-0.01) b ( 0.07+/-0.01) <
FF2.Alpha-.45|RFF2.Alpha-.45    |tB tBXIWest: o ( 0.02+/-0.01) a ( 0.09+/-0.02) b ( 0.10+/-0.02) tBXIEast: o (-0.03+/-0.02) a (-0.03+/-0.02) b (-0.04+/-0.02) tBXIAll: o (-0.01+/-0.01) a ( 0.03+/-0.02) b ( 0.03+/-0.01) <
FF2.Alpha-.60|RFF2.Alpha-.60    |tB tBXIWest: o ( 0.03+/-0.01) a ( 0.08+/-0.02) b ( 0.06+/-0.02) tBXIEast: o (-0.04+/-0.02) a (-0.03+/-0.02) b (-0.09+/-0.02) tBXIAll: o (-0.00+/-0.01) a ( 0.03+/-0.02) b^(-0.01+/-0.01)
FF2.Alpha-.75|RFF2.Alpha-.75    |tB tBXIWest: o ( 0.05+/-0.01) a ( 0.09+/-0.02) b^( 0.02+/-0.02) tBXIEast: o (-0.05+/-0.01) a (-0.03+/-0.02) b (-0.13+/-0.02) tBXIAll: o ( 0.00+/-0.01) a ( 0.03+/-0.01) b (-0.05+/-0.01)

FF2.Alpha0.15|RFF2.Alpha0.15    |tB tBXOWest: o (-0.02+/-0.01) a ( 0.02+/-0.01) b ( 0.29+/-0.01) tBXOEast: o (-0.00+/-0.01) a (-0.06+/-0.01) b ( 0.11+/-0.01) tBXOAll: o (-0.01+/-0.01) a (-0.02+/-0.01) b ( 0.20+/-0.01)
FF2.Short2.2Mom|RFF2.Short2.2Mom|tB tBXOWest: o (-0.01+/-0.01) a ( 0.01+/-0.01) b ( 0.25+/-0.01) tBXOEast: o (-0.01+/-0.01) a (-0.06+/-0.01) b ( 0.06+/-0.01) tBXOAll: o (-0.01+/-0.01) a (-0.03+/-0.01) b ( 0.16+/-0.01)
FF2.Alpha-.15|RFF2.Alpha-.15    |tB tBXOWest: o (-0.02+/-0.01) a ( 0.02+/-0.01) b ( 0.20+/-0.01) tBXOEast: o (-0.01+/-0.01) a (-0.05+/-0.01) b ( 0.03+/-0.01) tBXOAll: o (-0.01+/-0.01) a (-0.02+/-0.01) b ( 0.12+/-0.01)
FF2.Alpha-.30|RFF2.Alpha-.30    |tB tBXOWest: o (-0.02+/-0.01) a ( 0.02+/-0.01) b ( 0.16+/-0.01) tBXOEast: o (-0.00+/-0.01) a (-0.05+/-0.01) b^(-0.01+/-0.01) tBXOAll: o (-0.01+/-0.01) a (-0.02+/-0.01) b ( 0.08+/-0.01)
FF2.Alpha-.45|RFF2.Alpha-.45    |tB tBXOWest: o (-0.02+/-0.01) a ( 0.02+/-0.01) b ( 0.12+/-0.01) tBXOEast: o (-0.01+/-0.01) a (-0.05+/-0.01) b (-0.06+/-0.01) tBXOAll: o (-0.01+/-0.01) a (-0.01+/-0.01) b ( 0.03+/-0.01)
FF2.Alpha-.60|RFF2.Alpha-.60    |tB tBXOWest: o (-0.02+/-0.01) a ( 0.02+/-0.01) b ( 0.08+/-0.01) tBXOEast: o (-0.01+/-0.01) a (-0.05+/-0.01) b (-0.10+/-0.01) tBXOAll: o (-0.01+/-0.01) a (-0.01+/-0.01) b^(-0.01+/-0.01)<
FF2.Alpha-.75|RFF2.Alpha-.75    |tB tBXOWest: o (-0.02+/-0.01) a ( 0.02+/-0.01) b^( 0.03+/-0.01) tBXOEast: o (-0.00+/-0.01) a (-0.05+/-0.01) b (-0.14+/-0.01) tBXOAll: o (-0.01+/-0.01) a (-0.02+/-0.01) b (-0.05+/-0.01)<

FF2.Alpha0.15|RFF2.Alpha0.15    |tB tBYIWest: o (-0.45+/-0.00) a ( 0.02+/-0.00) b ( 0.20+/-0.00) tBYIEast: o (-0.03+/-0.00) a (-0.11+/-0.00) b ( 0.05+/-0.00) tBYIAll: o (-0.09+/-0.00) a (-0.11+/-0.00) b ( 0.08+/-0.00)
FF2.Short2.2Mom|RFF2.Short2.2Mom|tB tBYIWest: o (-0.44+/-0.00) a ( 0.02+/-0.00) b ( 0.17+/-0.00) tBYIEast: o (-0.03+/-0.00) a (-0.11+/-0.00) b^( 0.02+/-0.00) tBYIAll: o (-0.08+/-0.00) a (-0.10+/-0.00) b ( 0.04+/-0.00)
FF2.Alpha-.15|RFF2.Alpha-.15    |tB tBYIWest: o (-0.44+/-0.00) a ( 0.02+/-0.00) b ( 0.15+/-0.00) tBYIEast: o (-0.03+/-0.00) a (-0.11+/-0.00) b^(-0.02+/-0.00) tBYIAll: o (-0.10+/-0.00) a (-0.15+/-0.00) b^( 0.00+/-0.00) >2 
FF2.Alpha-.30|RFF2.Alpha-.30    |tB tBYIWest: o (-0.45+/-0.00) a ( 0.02+/-0.00) b ( 0.13+/-0.00) tBYIEast: o (-0.03+/-0.00) a (-0.11+/-0.00) b (-0.05+/-0.00) tBYIAll: o (-0.09+/-0.00) a (-0.11+/-0.00) b (-0.03+/-0.00)
FF2.Alpha-.45|RFF2.Alpha-.45    |tB tBYIWest: o (-0.45+/-0.00) a ( 0.02+/-0.00) b ( 0.10+/-0.00) tBYIEast: o (-0.03+/-0.00) a (-0.11+/-0.00) b (-0.08+/-0.00) tBYIAll: o (-0.10+/-0.00) a (-0.11+/-0.00) b (-0.06+/-0.00)
FF2.Alpha-.60|RFF2.Alpha-.60    |tB tBYIWest: o (-0.46+/-0.00) a ( 0.02+/-0.00) b ( 0.08+/-0.00) tBYIEast: o (-0.03+/-0.00) a (-0.10+/-0.00) b (-0.11+/-0.00) tBYIAll: o (-0.11+/-0.00) a (-0.09+/-0.00) b (-0.11+/-0.00)
FF2.Alpha-.75|RFF2.Alpha-.75    |tB tBYIWest: o (-0.47+/-0.00) a ( 0.02+/-0.00) b^( 0.05+/-0.00) tBYIEast: o (-0.03+/-0.00) a (-0.10+/-0.00) b (-0.14+/-0.00) tBYIAll: o (-0.11+/-0.00) a (-0.09+/-0.00) b (-0.13+/-0.00)

FF2.Alpha0.15|RFF2.Alpha0.15    |tB tBYOWest: o (-0.10+/-0.01) a ( 0.06+/-0.01) b ( 0.24+/-0.01) tBYOEast: o (-0.09+/-0.01) a (-0.01+/-0.01) b ( 0.07+/-0.01) tBYOAll: o (-0.09+/-0.01) a ( 0.03+/-0.01) b ( 0.16+/-0.01)
FF2.Short2.2Mom|RFF2.Short2.2Mom|tB tBYOWest: o (-0.10+/-0.01) a ( 0.06+/-0.01) b ( 0.21+/-0.01) tBYOEast: o (-0.09+/-0.01) a (-0.01+/-0.01) b ( 0.03+/-0.01) tBYOAll: o (-0.09+/-0.01) a ( 0.03+/-0.01) b ( 0.13+/-0.01)
FF2.Alpha-.15|RFF2.Alpha-.15    |tB tBYOWest: o (-0.10+/-0.01) a ( 0.06+/-0.01) b ( 0.17+/-0.01) tBYOEast: o (-0.09+/-0.01) a (-0.01+/-0.01) b^( 0.00+/-0.01) tBYOAll: o (-0.09+/-0.01) a ( 0.03+/-0.01) b ( 0.09+/-0.01)
FF2.Alpha-.30|RFF2.Alpha-.30    |tB tBYOWest: o (-0.10+/-0.01) a ( 0.06+/-0.01) b ( 0.14+/-0.01) tBYOEast: o (-0.09+/-0.01) a^(-0.00+/-0.01) b (-0.03+/-0.01) tBYOAll: o (-0.09+/-0.01) a ( 0.03+/-0.01) b ( 0.06+/-0.01)>
FF2.Alpha-.45|RFF2.Alpha-.45    |tB tBYOWest: o (-0.10+/-0.01) a ( 0.06+/-0.01) b ( 0.11+/-0.01) tBYOEast: o (-0.09+/-0.01) a (-0.01+/-0.01) b (-0.06+/-0.01) tBYOAll: o (-0.09+/-0.01) a ( 0.03+/-0.01) b ( 0.03+/-0.01)
FF2.Alpha-.60|RFF2.Alpha-.60    |tB tBYOWest: o (-0.10+/-0.01) a ( 0.06+/-0.01) b ( 0.08+/-0.01) tBYOEast: o (-0.09+/-0.01) a (-0.01+/-0.01) b (-0.10+/-0.01) tBYOAll: o (-0.09+/-0.01) a ( 0.03+/-0.01) b^(-0.00+/-0.01)>
FF2.Alpha-.75|RFF2.Alpha-.75    |tB tBYOWest: o (-0.10+/-0.01) a ( 0.06+/-0.01) b^( 0.04+/-0.01) tBYOEast: o (-0.08+/-0.01) a (-0.01+/-0.01) b (-0.13+/-0.01) tBYOAll: o (-0.09+/-0.01) a ( 0.03+/-0.01) b (-0.04+/-0.01)>

--------------------------------------------------------------------------------
01/07/14 
Increase window from 5 to 10 cm.

 */

