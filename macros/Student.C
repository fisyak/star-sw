#include "TROOT.h"
#include "TF1.h"
#include "Math/DistFunc.h"
//________________________________________________________________________________
Double_t student(Double_t *x, Double_t *p) {
  Double_t t = (x[0] - p[1])/p[2];
  return p[0]*ROOT::Math::tdistribution_pdf(t,p[3]);
}
//________________________________________________________________________________
TF1 *Student() {
  static const Char_t *name = "Student";
  static TF1 *f = 0;
  if (! f) {
    f = (TF1 *) gROOT->GetListOfFunctions()->FindObject(name);
    if (! f) {
      f = new TF1(name,student,-5,5,4);
      f->SetParNames("Norm","mu","sigma","ndf");
      f->SetParameters(1e8,0.0,1.0,1e3);
    }
  }
  return f;
}
//________________________________________________________________________________
