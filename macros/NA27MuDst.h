//////////////////////////////////////////////////////////
//   This class has been automatically generated 
//     (Wed Apr  9 16:37:49 2003 by ROOT version3.05/03)
//   from TTree NA27MuDst/NA27
//   found on file: mppnobc.root
//////////////////////////////////////////////////////////


#ifndef NA27MuDst_h
#define NA27MuDst_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include "TString.h"
#include <string>
class NA27MuDst {
   public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain
//Declaration of leaves types
   UInt_t          krll;
   UInt_t          kfram;
   UInt_t          labpri;
   Float_t         xyzp[3];
   Float_t         pxyzb[3];
   Float_t         eqmkb;
   Int_t           no_trak;
   UInt_t          labdtf[32];   //[no_trak]
   Int_t           kchar[32];   //[no_trak]
   Float_t         pxt[32];   //[no_trak]
   Float_t         pyt[32];   //[no_trak]
   Float_t         pzt[32];   //[no_trak]
   Float_t         Clvs[32][4];   //[no_trak]
   Float_t         wpid[32];   //[no_trak]
   Float_t         wsp[32];   //[no_trak]
   Int_t           no_gam;
   UInt_t          labgam[32];   //[no_gam]
   Float_t         pxg[32];   //[no_gam]
   Float_t         pyg[32];   //[no_gam]
   Float_t         pzg[32];   //[no_gam]
   Int_t           kgamtyp[32];   //[no_gam]
   Float_t         gamflg[32];   //[no_gam]
   Int_t           no_gg;
   UInt_t          labgg[128];   //[no_gg]
   UInt_t          labgams[128][2];   //[no_gg]
   Float_t         ggmss[128];   //[no_gg]
   Float_t         pxgg[128];   //[no_gg]
   Float_t         pygg[128];   //[no_gg]
   Float_t         pzgg[128];   //[no_gg]
   Float_t         ggprb[128];   //[no_gg]

//List of branches
   TBranch        *b_krll;   //!
   TBranch        *b_kfram;   //!
   TBranch        *b_labpri;   //!
   TBranch        *b_xyzp;   //!
   TBranch        *b_pxyzb;   //!
   TBranch        *b_eqmkb;   //!
   TBranch        *b_no_trak;   //!
   TBranch        *b_labdtf;   //!
   TBranch        *b_kchar;   //!
   TBranch        *b_pxt;   //!
   TBranch        *b_pyt;   //!
   TBranch        *b_pzt;   //!
   TBranch        *b_Clvs;   //!
   TBranch        *b_wpid;   //!
   TBranch        *b_wsp;   //!
   TBranch        *b_no_gam;   //!
   TBranch        *b_labgam;   //!
   TBranch        *b_pxg;   //!
   TBranch        *b_pyg;   //!
   TBranch        *b_pzg;   //!
   TBranch        *b_kgamtyp;   //!
   TBranch        *b_gamflg;   //!
   TBranch        *b_no_gg;   //!
   TBranch        *b_labgg;   //!
   TBranch        *b_labgams;   //!
   TBranch        *b_ggmss;   //!
   TBranch        *b_pxgg;   //!
   TBranch        *b_pygg;   //!
   TBranch        *b_pzgg;   //!
   TBranch        *b_ggprb;   //!

   NA27MuDst(TTree *tree=0);
   ~NA27MuDst();
   Int_t  Cut(Int_t entry);
   Int_t  GetEntry(Int_t entry);
   Int_t  LoadTree(Int_t entry);
   void   Init(TTree *tree);
   void   Loop();
   Bool_t Notify();
   void   Show(Int_t entry = -1);
   const Char_t *LabEHS(Int_t lab=0);
   void   Print();
};

#endif

#ifdef NA27MuDst_cxx
NA27MuDst::NA27MuDst(TTree *tree)
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("mppnobc.root");
      if (!f) {
	f = new TFile("/gpfs01/star/subsys-tpc/fisyak/public/na27/mppnobc.root");
      }
      tree = (TTree*)gDirectory->Get("h100");

   }
   Init(tree);
}

NA27MuDst::~NA27MuDst()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t NA27MuDst::GetEntry(Int_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Int_t NA27MuDst::LoadTree(Int_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Int_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->IsA() != TChain::Class()) return centry;
   TChain *chain = (TChain*)fChain;
   if (chain->GetTreeNumber() != fCurrent) {
      fCurrent = chain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void NA27MuDst::Init(TTree *tree)
{
//   Set branch addresses
   if (tree == 0) return;
   fChain    = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("krll",&krll);
   fChain->SetBranchAddress("kfram",&kfram);
   fChain->SetBranchAddress("labpri",&labpri);
   fChain->SetBranchAddress("xyzp",xyzp);
   fChain->SetBranchAddress("pxyzb",pxyzb);
   fChain->SetBranchAddress("eqmkb",&eqmkb);
   fChain->SetBranchAddress("no_trak",&no_trak);
   fChain->SetBranchAddress("labdtf",labdtf);
   fChain->SetBranchAddress("kchar",kchar);
   fChain->SetBranchAddress("pxt",pxt);
   fChain->SetBranchAddress("pyt",pyt);
   fChain->SetBranchAddress("pzt",pzt);
   fChain->SetBranchAddress("Clvs",Clvs);
   fChain->SetBranchAddress("wpid",wpid);
   fChain->SetBranchAddress("wsp",wsp);
   fChain->SetBranchAddress("no_gam",&no_gam);
   fChain->SetBranchAddress("labgam",labgam);
   fChain->SetBranchAddress("pxg",pxg);
   fChain->SetBranchAddress("pyg",pyg);
   fChain->SetBranchAddress("pzg",pzg);
   fChain->SetBranchAddress("kgamtyp",kgamtyp);
   fChain->SetBranchAddress("gamflg",gamflg);
   fChain->SetBranchAddress("no_gg",&no_gg);
   fChain->SetBranchAddress("labgg",labgg);
   fChain->SetBranchAddress("labgams",labgams);
   fChain->SetBranchAddress("ggmss",ggmss);
   fChain->SetBranchAddress("pxgg",pxgg);
   fChain->SetBranchAddress("pygg",pygg);
   fChain->SetBranchAddress("pzgg",pzgg);
   fChain->SetBranchAddress("ggprb",ggprb);
   Notify();
}

Bool_t NA27MuDst::Notify()
{
   // Called when loading a new file.
   // Get branch pointers.
   b_krll = fChain->GetBranch("krll");
   b_kfram = fChain->GetBranch("kfram");
   b_labpri = fChain->GetBranch("labpri");
   b_xyzp = fChain->GetBranch("xyzp");
   b_pxyzb = fChain->GetBranch("pxyzb");
   b_eqmkb = fChain->GetBranch("eqmkb");
   b_no_trak = fChain->GetBranch("no_trak");
   b_labdtf = fChain->GetBranch("labdtf");
   b_kchar = fChain->GetBranch("kchar");
   b_pxt = fChain->GetBranch("pxt");
   b_pyt = fChain->GetBranch("pyt");
   b_pzt = fChain->GetBranch("pzt");
   b_Clvs = fChain->GetBranch("Clvs");
   b_wpid = fChain->GetBranch("wpid");
   b_wsp = fChain->GetBranch("wsp");
   b_no_gam = fChain->GetBranch("no_gam");
   b_labgam = fChain->GetBranch("labgam");
   b_pxg = fChain->GetBranch("pxg");
   b_pyg = fChain->GetBranch("pyg");
   b_pzg = fChain->GetBranch("pzg");
   b_kgamtyp = fChain->GetBranch("kgamtyp");
   b_gamflg = fChain->GetBranch("gamflg");
   b_no_gg = fChain->GetBranch("no_gg");
   b_labgg = fChain->GetBranch("labgg");
   b_labgams = fChain->GetBranch("labgams");
   b_ggmss = fChain->GetBranch("ggmss");
   b_pxgg = fChain->GetBranch("pxgg");
   b_pygg = fChain->GetBranch("pygg");
   b_pzgg = fChain->GetBranch("pzgg");
   b_ggprb = fChain->GetBranch("ggprb");
   return kTRUE;
}

void NA27MuDst::Show(Int_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
   Print();
}
//________________________________________________________________________________
Int_t NA27MuDst::Cut(Int_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
//________________________________________________________________________________
void NA27MuDst::Print() {
  static Char_t labg1[8], labg2[8], ich[1], chatot[4];
  static Double_t pxyz[3]; 
  static const Char_t *igdev[5] = {" ","IGD","FGD"," "," "};
  static const Char_t *mgg[3] = {"pi0","eta","etap"};
  cout << "--------------------------------------------------------------------------------" << endl;
  //  cout << "ROLL\t" << krll << "\tFRAME\t" << kfram << endl;
  const Char_t *label = LabEHS(labpri);
  cout << Form(" Event r/f=%5i%5i primary vertex = %s  micro barn equivalent = %8.3f", krll, kfram, label, eqmkb);
  cout << " at X,Y,Z :";
  for (int i = 0; i < 3; i++) cout << "\t" << xyzp[i]; cout << endl;
  cout << "Beam momentum:"; for (int i = 0; i < 3; i++) cout << "\t" << pxyzb[i]; 
  cout << "\tno.tracks = " << no_trak << "\tno.gammas = " << no_gam << "\tno.of gamma-gamma = " << no_gg << endl;
  cout << "Primary Tracks" << endl
       << setw(10) << "TRK CHG" << setw(10) << "PX" << setw(10) << "PY" << setw(10) << " PZ" << setw(5) << "pId" << setw(10) << "WSP" << setw(10) << "wPid" << endl;
  Int_t nch = 0;
  memset(pxyz, 0, sizeof(pxyz));
  for (int i = 0; i < no_trak; i++) {
    label = LabEHS(labdtf[i]);
    nch += TMath::Sign(1,kchar[i]);
    Char_t ich;
    ich = ' ';
    if      (kchar[i] <  0) ich = '-';
    else if (kchar[i] == 0) ich = '0';
    else if (kchar[i] >  0) ich = '+';
    pxyz[0] += pxt[i];
    pxyz[1] += pyt[i];
    pxyz[2] += pzt[i];
    Int_t idc = TMath::Abs(kchar[i])/1000;
    //    if (isrll  <= 202) idc = TMath::Max(1, idc - 1);
    TString Cls("");
    for (int j = 0; j<4; j++) {
      if (Clvs[i][j] < 0.01) Cls += "-";
      else {
	if (Clvs[i][j] < 0.1) Cls += "+";
	else {
	  int k = (int) 10*Clvs[i][j];
	  if (k > 9) k = 9;
	  Cls += Form("%i",k);
	}
      }
    }
    cout << setw(2) << labdtf[i] << setw(8) << kchar[i]  // label << setw(2) << idc << setw(2) << ich 
	 << setw(10) << setprecision(3) << pxt[i] 
	 << setw(10) << setprecision(3) << pyt[i] 
	 << setw(10) << setprecision(3) << pzt[i] 
	 << setw(5)  << Cls.Data() 
	 << setw(10) << setprecision(3) << wsp[i] 
	 << setw(10) << setprecision(3) << wpid[i] << endl;
  }
  if (no_gam > 0) {
    cout << " gammas" << endl
	 << setw(10) << "label" << setw(10) << "px" << setw(10) << "py" << setw(10) << "pz" << endl;
    for (Int_t i = 0; i < no_gam; i++) {
      label = LabEHS(labgam[i]);
      cout << setw(10) << label 
	   << setw(10) << setprecision(3) << pxg[i]
	   << setw(10) << setprecision(3) << pyg[i]
	   << setw(10) << setprecision(3) << pzg[i] << endl;
      pxyz[0] += pxg[i];
      pxyz[1] += pyg[i];
      pxyz[2] += pzg[i];
    }
  }
  if (no_gg > 0) {
    cout << " pi0 & eta" << endl
	 << setw(10) << "label"  
	 << setw(10) << "gamma1"
	 << setw(10) << "gamma1"
	 << setw(10) << "px" << setw(10) << "py" << setw(10) << "pz" 
	 << setw(10) << "mass" 
	 << setw(10) << "prob" << endl;
    for (Int_t i = 0; i < no_gg; i++) {
      cout << setw(10) << LabEHS(labgg[i])
	   << setw(10) << LabEHS(labgams[i][0])
	   << setw(10) << LabEHS(labgams[i][1])
	   << setw(10) << setprecision(3) << pxgg[i]
	   << setw(10) << setprecision(3) << pygg[i]
	   << setw(10) << setprecision(3) << pzgg[i] 
	   << setw(10) << setprecision(3) << ggmss[i] 
	   << setw(10) << setprecision(3) << ggprb[i] 
	   << endl;
    }
  }
  cout << "total momentum: " 
       << setw(10) << setprecision(3) << pxyz[0] 
       << setw(10) << setprecision(3) << pxyz[1] 
       << setw(10) << setprecision(3) << pxyz[2]  << endl;
}
//________________________________________________________________________________
UInt_t bits(UInt_t mHardwarePosition, UInt_t bit, UInt_t nbits=1) {return (mHardwarePosition>>bit) & ~(~0UL<<nbits);};
//________________________________________________________________________________
const Char_t *NA27MuDst::LabEHS(Int_t i) {
  static Int_t _debug = 0;
  static TString lab("");
  static const Char_t *itype[] = {"U", "B", "V", "C", "S", "D", "N", "I","G",
				  "L", "E", "J", "P", "W", "*", "X", "M"};
  static const Char_t *jtype[] = {"IGD", "FGD", "PI0", "ETA", "ETP"};
  static Int_t   ntrk[]  = {0,  -1,  -1,   1,   0,  -1,  -1,  -1,   2,
                            0,   0,   0,   0,   1,   0,  -1,   0};
  Int_t Lab = i;
  if (i <= 0) Lab = labpri;
  UInt_t il = bits(Lab, 0, 8);
  UInt_t it = bits(Lab, 8, 5);
  //  if (krll > 1000 && it >= 16)  it += 2;
  UInt_t nt = bits(Lab,15,6);
  if (_debug) cout << "Lab - " << Lab << "\til = " << il << "\tit = " << it << "\tnt = " << nt << endl;
  lab = "";
  if (it <= 16) {//GET VERTEX TYPE AND NUMBER OF TRACKS.
    lab += itype[it];
    if (ntrk[it] < 0 && nt > 0) {
      lab += nt;
    }
  } else {// SPECIAL TREATMENT FOR SHOWERS, PI0S, AND ETAS.
    if (it < 23) {
      lab += jtype[it-17];
    } 
  }
  lab += ".";
  if (il > 0) lab += il;
  if (_debug) cout << "LabEHS(" << i << ") = " << lab.Data() << endl;
  return lab.Data();
}
#endif // #ifdef NA27MuDst_cxx

