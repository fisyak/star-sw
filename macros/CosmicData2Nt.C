//  ~/work/Tpc/Alignment $ grep DelpT */*/?F/*.data | tee delpT.data
/* 
   root.exe CosmicData2Nt.C+
 */
#if !defined(__CINT__) || defined(__MAKECINT__)
//#include <map>
//#include <array>
#include "Riostream.h"
#include <stdio.h>
#include "TROOT.h"
#include "TSystem.h"
#include "TMath.h"
#include "TFile.h"
#include "TNtuple.h"
#include "TString.h"
#include "TH1.h"
#include "TCanvas.h"
#include "TLegend.h"
#endif
struct BPoint_t {
  Float_t set; // 2019/FF  2019/RF  2020/RF  2021/FF  2021/RF  2022/FF  2022/RF  2023/FF  2023/RF
  Float_t pass; 
  Float_t var;
  Float_t N, A, B, pT;
};
//________________________________________________________________________________
								
BPoint_t BPoint;
static   Int_t Nsets = 11;
static   TString sets[11]  = {"2019/FF",  "2019/RF",  "2020/RF",  "2021/FF",  "2021/RF",  "2022/FF",  "2022/RF",  "2023/FF",  "2023/RF", "2021/MF", "2023/ZF"};
static   TString valC[12] = {// "DelpTRAll", "DelpTIPos", "DelpTINeg", "DelpTIAllT", "DelpTIPosT", "DelpTINegT"};
    "DelpTIAll", "DelpTIPos", "DelpTINeg", "DelpTIAllT", "DelpTINegT", "DelpTIPosT", "DelpTRAll", "DelpTRPos", "DelpTRNeg", "DelpTRAllT", "DelpTRPosT", "DelpTRNegT", 
  };
//________________________________________________________________________________
Int_t iucomp(TString &var, TString *array, Int_t N) {
  for (Int_t i = 0; i < N; i++) {
    if (var == array[i]) return i;
  }
  return -1;
}
//________________________________________________________________________________
void CosmicData2Nt(const Char_t *FileName = "/star/u/fisyak/work/Tpc/Alignment/delpT.data")  {
  FILE *fp = fopen(FileName,"r");
  if (! fp) {
    cout << "Can't open" << FileName << endl;
    return;
  }
  TString Name(gSystem->BaseName(FileName));
  //  fName.ReplaceAll(".data",".root");
  TString fName(Name);
  fName.ReplaceAll(".data",".root");
  auto f = new TFile(fName.Data(),"RECREATE");
  TString Var("set:pass:var:N:A:B:pT");
  auto FitP = new TNtuple("FitP",Name,Var);
  char line[241];
  Char_t v[32], s[32], r[32];
  Float_t pass = 0;
  Float_t set = 0;
  Float_t var = 0;
  Float_t N,A,B,pT;
  Int_t i = 0;
  while (fgets(&line[0],240,fp)) {
    //CosmicsC/2019/FF/CosmicPlots.data:      DelpTIAll        0.31M  #sigma(#Delta(1/pT)) = ( 1.35% #oplus  1.61% #times pT)/pT => #sigma(#DeltapT/pT) =  2.10%(@1GeV/c)
    TString Line(line);
    cout << Line.Data() << endl;
    TObjArray *tokens = Line.Tokenize(" :\t/()%\nM");
    pass = -1;
    N = -1;
    for (Int_t i = 0; i <= tokens->GetLast(); i++) {
      TString &token = ((TObjString*) ( tokens->At(i)))->String();
      //      cout << "i = " << i << "\t|" << token.Data() << "|" << endl;
      if (i == 0) {
	if (token == "P23ia") { 
	  pass = 0;
	} else if (token == "CosmicsB") {
	  pass = 1;
	} else if (token == "CosmicsC") {
	  pass = 2;
	} else if (token.BeginsWith("Pass")) {
	  token.ReplaceAll("Pass","");
	  pass = token.Atoi();
	  cout << "pass = " << pass << endl;
	}
      } else if (i == 2) {
	TString tag = ((TObjString*) ( tokens->At(i-1)))->String();
	tag += "/";
	tag += token;   cout << "tag = " << tag.Data() << endl;
	set = iucomp(tag, sets, Nsets);
	cout << "set = " << set << endl;
      } else if (i == 4) {
	var = iucomp(token,valC,12);
	cout << "var = " << var << endl;
      } else if (i == 5) {
	N = token.Atof();
	cout << "N = " << N << endl;
      } else if (i == 11) {
	A = token.Atof();
	cout << "A = " << A << endl;
      } else if (i == 11) {
	A = token.Atof();
	cout << "A = " << A << endl;
      } else if (i == 13) {
	B = token.Atof();
	cout << "B = " << B << endl;
      } else if (i == 22) {
	pT = token.Atof();
	cout << "pT = " << pT << endl;
      }
    }
    delete tokens;
    BPoint.set = set;
    BPoint.var = var;
    BPoint.pass = pass;
    BPoint.N = N;
    BPoint.A = A;
    BPoint.B = B;
    BPoint.pT = pT;

    FitP->Fill(&BPoint.set);
    i++;
    //    if (i > 10) break;
    //    if (i%10 == 1) cout << "i:" << i << "\t" << line;
  }
  fclose(fp);
  f->Write();
}
//________________________________________________________________________________
void Draw(Int_t var = 3, const Char_t *varName="pT") {
  TNtuple *FitP = (TNtuple *) gDirectory->Get("FitP");
  if (! FitP) return;
  TCanvas *c1 = (TCanvas *) gROOT->GetListOfCanvases()->FindObject("c1");
  if (c1) c1->Clear();
  else    c1 = new TCanvas("c1");
  TString VarName(varName);
  TH1F * frame = 0;
  if (VarName == "pT") {
    frame =  c1->DrawFrame(-1,1.0,70,5.0);
    frame->SetTitle(valC[var] + " (@1GeV/c)");
    frame->SetYTitle("Resolutin(%)");
  } else if (VarName == "N") {
    frame =  c1->DrawFrame(-1,0.0,70,5.0);
    frame->SetTitle("No. of matched pairs");
    frame->SetYTitle("N (M)");
  }
  frame->SetXTitle("Pass");
  TLegend *l = new TLegend(0.7,0.5,0.8,0.9);
  for (Int_t set = 0; set < Nsets; set++) {
    FitP->SetMarkerStyle(20);
    FitP->SetMarkerColor(set+1);
    if (set > 8) {
      FitP->SetMarkerStyle(47);
      FitP->SetMarkerColor(set-8);
    }
    FitP->Draw(Form("%s:pass>>h%i(71,-0.5,70.5)",varName,set),Form("var==%i&&set==%i",var,set),"same");
    TH1 *h = (TH1 *) gDirectory->Get(Form("h%i",set));
    if (h) l->AddEntry(h,sets[set]);
  }
  l->Draw();    
} 
