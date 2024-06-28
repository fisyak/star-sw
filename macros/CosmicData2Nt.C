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
#include "TGraphErrors.h"
#include "TMultiGraph.h"
#endif
struct BPoint_t {
  Float_t set; // 2019/FF  2019/RF  2020/RF  2021/FF  2021/RF  2022/FF  2022/RF  2023/FF  2023/RF
  Float_t pass; 
  Float_t var;
  Float_t N, A, B, pT;
};
//________________________________________________________________________________
								
BPoint_t BPoint;
enum {Nsets = 14, Npasses = 141};
static   TString sets[Nsets]  = {"2019/FF",  "2019/RF",  "2020/RF",  "2021/FF",  "2021/RF",  "2022/FF",  "2022/RF",  "2023/FF",  "2023/RF",  "2024/FF",  "2024/RF",  "2021/MF", "2023/ZF", "2024/ZF"};
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
    cout << Line.Data();
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
	  cout << "pass = " << pass <<  "\t";
	}
      } else if (i == 2) {
	TString tag = ((TObjString*) ( tokens->At(i-1)))->String();
	tag += "/";
	tag += token;   cout << "tag = " << tag.Data() <<  "\t";
	set = iucomp(tag, sets, Nsets);
	cout << "set = " << set <<  "\t";
      } else if (i == 4) {
	var = iucomp(token,valC,12);
	cout << "var = " << var <<  "\t";
      } else if (i == 5) {
	N = token.Atof();
	cout << "N = " << N <<  "\t";
      } else if (i == 11) {
	A = token.Atof();
	cout << "A = " << A <<  "\t";
      } else if (i == 11) {
	A = token.Atof();
	cout << "A = " << A <<  "\t";
      } else if (i == 13) {
	B = token.Atof();
	cout << "B = " << B <<  "\t";
      } else if (i == 22) {
	pT = token.Atof();
	cout << "pT = " << pT <<  "\t";
      }
    }
    cout << endl;
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
  TString cname(varName); cname  += var;
  TString tname("Variable "); tname += var; tname += " "; tname += varName;
  TCanvas *c1 = (TCanvas *) gROOT->GetListOfCanvases()->FindObject(cname);
  if (c1) c1->Clear();
  else    c1 = new TCanvas(cname, tname);
  TString VarName(varName);
  TH1F * frame = 0;
  if (VarName == "pT") {
    frame =  c1->DrawFrame(-0.5, 1.0, Npasses + 0.5, 5.0);
    frame->SetTitle(valC[var] + " (@1GeV/c)");
    frame->SetYTitle("Resolutin(%)");
  } else {
    frame =  c1->DrawFrame(-0.5, 0.0, Npasses + 0.5,10.0);
    if (VarName == "N") {
      frame->SetTitle("No. of matched pairs");
      frame->SetYTitle("N (M)");
    } else {
      frame->SetTitle(varName);
      frame->SetYTitle(Form("%s(%%)",varName));
    }
  }
  if (frame) frame->SetXTitle("Pass");
  TLegend *l = new TLegend(0.7,0.5,0.8,0.9);
  //    FitP->SetMarkerSize(2);
  TMultiGraph *mg = new TMultiGraph(cname+"Gr",tname);
  for (Int_t set = 0; set < Nsets - 3; set++) {
    TString hname(Form("%s_s%i_v%i",varName,var,set));
    cout << "FitP->Draw(\"" << Form("%s:pass>>%s(141,-0.5,%f)",varName,hname.Data(),Npasses+0.5) << "\",\"" << Form("var==%i&&set==%i",var,set) << "\",\"goff\");" << endl;
    Int_t nfound = FitP->Draw(Form("%s:pass>>%s(141,-0.5,%f,500,0,5)",varName,hname.Data(),Npasses+0.5),Form("var==%i&&set==%i",var,set),"goff");
    if (nfound > 0) {
      TGraph *gr = new TGraph(nfound, FitP->GetV2(), FitP->GetV1());
      gr->SetMarkerStyle(20);
      gr->SetMarkerColor(set+1);
      if (set > 8) {
	gr->SetMarkerStyle(23);
	gr->SetMarkerColor(set-8);
	//	gr->SetMarkerSize(2);
      }
      mg->Add(gr);
      l->AddEntry(gr,sets[set],"p");
    }
  }
  mg->Draw("p");
  l->Draw();    
} 
