//  egrep -a '( found table tpcDriftVelocity|laserDriftVelocityEast)' */*/*B.log | tee drift.list
// root.exe MakeNTupleFromAsciiCosmicDrift.C+
#include "Riostream.h"
#include <stdio.h>
#include "TROOT.h"
#include "TSystem.h"
#include "TMath.h"
#include "TFile.h"
#include "TNtuple.h"
#include "TString.h"
#include "TDatime.h"
struct BPoint_t {
  Float_t set, usec, year, day,  DV;//
};
BPoint_t BPoint;
static   Int_t Nsets = 11;//         0           1           2           3           4           5           6           7           8          9         10
static   TString sets[11]  = {"2019/FF",  "2019/RF",  "2020/RF",  "2021/FF",  "2021/RF",  "2022/FF",  "2022/RF",  "2023/FF",  "2023/RF", "2021/MF", "2023/ZF"};
//________________________________________________________________________________
Int_t iucomp(TString &var, TString *array, Int_t N) {
  for (Int_t i = 0; i < N; i++) {
    if (var == array[i]) return i;
  }
  return -1;
}
//________________________________________________________________________________
void MakeNTupleFromAsciiCosmicDrift(const Char_t *FileName="drift.list") {
  FILE *fp = fopen(FileName,"r");
  if (! fp) {
    cout << "Can't open" << FileName << endl;
    return;
  }
  TString fName(gSystem->BaseName(FileName));
  fName.ReplaceAll(".list",".root");
  TFile *fOut = new TFile(fName.Data(),"RECREATE");
  TNtuple *FitP = new TNtuple("FitP","Cosmics Drift Velocity","set:usec:year:day:DV");
  char line[320];
  Int_t i = 0;
  Float_t s, freq;
  TDatime dtime(20190101,0);
  UInt_t u0 = dtime.Convert();
  while (fgets(&line[0],320,fp)) {
    TString Line(line);
    if (! fgets(&line[0],320,fp)) break;
    Line += ":";
    Line += line;
    //    cout << Line.Data() << endl;
    TObjArray *tokens = Line.Tokenize(" :/-()%\n");
1    TString Set;
    Int_t d = 0, t = 0;
    Float_t drift = 0;
    Int_t year = 0;
    for (Int_t i = 0; i <= tokens->GetLast(); i++) {
      TString &token = ((TObjString*) ( tokens->At(i)))->String();
      //      cout << i << "\t" << token.Data() << endl;
      if      (i ==  0) {Set  = token; year = token.Atoi();}
      else if (i ==  1) {Set += "/"; Set += token;}
      else if (i == 16) {d = token.Atoi();}
      else if (i == 17) {t = token.Atoi();}
      else if (i == 24) {drift = token.Atof();}
    }
    Int_t set = iucomp(Set, sets, 11);
    TDatime time(d,t);
    Int_t usec = time.Convert() - u0; 
    if (i%1000 == 0) {
      cout << Set.Data() << "\t" << time.AsString() << "\t" << drift << "\t" << set << "\t" << usec << endl;
    }
    TDatime ty(10000*year + 101, 0);
    BPoint.set = set;
    BPoint.usec = usec;
    BPoint.year = year;
    BPoint.day  = (time.Convert() - ty.Convert())/(24.*60.*60.) + 1.;
    BPoint.DV = drift;
    FitP->Fill(&BPoint.set);
    i++;
  }
  fclose(fp);
  fOut->Write();
}
