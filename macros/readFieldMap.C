#if !defined(__CINT__) || defined(__MAKECINT__)
#include "Riostream.h"
#include <stdio.h>
#include "TROOT.h"
#include "TSystem.h"
#include "TMath.h"
#include "TFile.h"
#include "TNtuple.h"
#endif
struct BPoint_t {Float_t R, Z, Phi, Br, Bz, Bphi;};
const Char_t *v = "R:Z:Phi:Br:Bz:Bphi";
struct BPoint2_t {Float_t R, Z, Phi, BrP, BzP, BphiP, BrN, BzN, BphiN;};
const Char_t *v2 = "R:Z:Phi:BrP:BzP:BphiP:BrN:BzN:BphiN";
TFile *f = 0;
TNtuple *FitP = 0;
//________________________________________________________________________________
void readFieldMap(const Char_t *FileName = "/afs/rhic.bnl.gov/star/packages/.DEV2/StarDb/StMagF/bfield_full_positive_3D.dat") {
  FILE *fp = fopen(FileName,"r");
  if (! fp) {
    cout << "Can't open" << FileName << endl;
    return;
  }
  TString fName(gSystem->BaseName(FileName));
  fName.ReplaceAll(".dat",".root");
  f = new TFile(fName.Data(),"RECREATE");
  FitP = new TNtuple("FitP",FileName,v);
  char line[121];
  BPoint_t B;
  Int_t i = 0;
  while (fgets(&line[0],120,fp)) {
    Int_t n = sscanf(&line[0]," %f %f %f %f %f %f",&B.R,&B.Z,&B.Phi,&B.Br,&B.Bz,&B.Bphi);
    if (n != 6) {printf("skip %s",line); continue;}
    if (i%(37*28) == 0) {printf("get %s",line);}
    FitP->Fill(&B.R);
    i++;
  }
  fclose(fp);
  f->Write();
}
//________________________________________________________________________________
void read2FieldMaps(const Char_t *FileNameP = "/afs/rhic.bnl.gov/star/packages/.DEV2/StarDb/StMagF/bfield_full_positive_3D.dat",
		    const Char_t *FileNameN = "/afs/rhic.bnl.gov/star/packages/.DEV2/StarDb/StMagF/bfield_full_negative_3D.dat") {
  FILE *fp = fopen(FileNameP,"r");
  if (! fp) {
    cout << "Can't open" << FileNameP << endl;
    return;
  }
  FILE *fn = fopen(FileNameN,"r");
  if (! fn) {
    cout << "Can't open" << FileNameN << endl;
    return;
  }
  f = new TFile("Field3D.root","RECREATE");
  FitP = new TNtuple("FitP","Field3D",v2);
  char lineP[121];
  char lineN[121];
  BPoint2_t B;
  Int_t i = 0;
  Float_t R, Z, Phi;
  Int_t n;
  while (fgets(&lineP[0],120,fp) && fgets(&lineN[0],120,fn)) {
    n = sscanf(&lineP[0]," %f %f %f %f %f %f",&B.R,&B.Z,&B.Phi,&B.BrP,&B.BzP,&B.BphiP);
    if (n != 6) {printf("skip P %s",lineP); continue;}
    n = sscanf(&lineN[0]," %f %f %f %f %f %f",&R,&Z,&Phi,&B.BrN,&B.BzN,&B.BphiN);
    if (n != 6) {printf("skip %s",lineN); continue;}
    if (i%(37*28) == 0) {printf("get P: %s",lineP); printf("get N: %s",lineN);}
    if (B.R != R || B.Z != Z || B.Phi != Phi) {
      cout << "line does not math" << endl;
      printf("get P: %s",lineP); printf("get N: %s",lineN);
      continue;
    }
    FitP->Fill(&B.R);
    i++;
  }
  fclose(fp);
  f->Write();
}
