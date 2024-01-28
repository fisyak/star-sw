#ifndef __SurveyPass_h__
#define __SurveyPass_h__
#include "Riostream.h"
#include "Rtypes.h"
#include "TString.h"
#include "TMath.h"
//________________________________________________________________________________
class data_t {
 public:
  Int_t sector;
  Double_t x, Dx, y, Dy, z, Dz, alpha, Dalpha, beta, Dbeta, gamma, Dgamma;
  Char_t Comment[256];
  void Print() {
    cout << Form("%2i %8.2f %5.2f %8.2f %5.2f %8.2f %5.2f",sector, x, Dx, y, Dy, z, Dz)
	 << Form(" %8.2f %5.2f %8.2f %5.2f %8.2f %5.2f %s", alpha, Dalpha, beta, Dbeta, gamma, Dgamma, Comment) << endl;
  }
  data_t &operator+= (data_t &v) {
    Double_t *X0 = &x;
    Double_t *X1 = &v.x;
    for (Int_t i = 0; i < 6; i++) {
      if (X0[2*i+1] >= 0 /* && X0[2*i+1] < 99 */ &&
	  X1[2*i+1] >= 0 /* && X1[2*i+1] < 99 */) {
	Double_t val = 0.5*(X0[2*i] + X1[2*i]);
	Double_t err = TMath::Sqrt(X0[2*i+1]*X0[2*i+1]+X1[2*i+1]*X1[2*i+1])/2;
	X0[2*i  ] = val;
	X0[2*i+1] = err;
      }
    }
    Char_t temp[256];
    sprintf(temp,"(%s+%s)/2",Comment,v.Comment);
    strcpy(Comment,temp);
  }
  data_t &operator-= (data_t &v) {
    Double_t *X0 = &x;
    Double_t *X1 = &v.x;
    for (Int_t i = 0; i < 6; i++) {
      if (X0[2*i+1] >= 0 /* && X0[2*i+1] < 99 */ &&
	  X1[2*i+1] >= 0 /* && X1[2*i+1] < 99 */) {
	Double_t val = 0.5*(X0[2*i] - X1[2*i]);
	Double_t err = TMath::Sqrt(X0[2*i+1]*X0[2*i+1]+X1[2*i+1]*X1[2*i+1])/2;
	X0[2*i  ] = val;
	X0[2*i+1] = err;
      }
    }
    Char_t temp[256];
    sprintf(temp,"(%s-%s)/2",Comment,v.Comment);
    strcpy(Comment,temp);
  }
};
class SurveyPass_t {
 public:
  Int_t date, time;
  Char_t PassName[256];
  data_t Data[24];
#if 0
  SurveyPass_t &operator=(Int_t d, Int_t t, const Char_t *Pass, data_t data[24]) {
    date = d; time = t; PassName = Pass;
    for (Int_t i = 0; i < 24; i++) Data[i] = data[i];
    return *this;
  }
#endif
  void Print() {
    cout << Form("%8i %6i %s",date,time,PassName) << endl;
    for (Int_t i = 0; i < 24; i++) {
      Data[i].Print();
    }
  }
  SurveyPass_t operator+= (SurveyPass_t &v) {
    for (Int_t i = 0; i < 24; i++) Data[i] += v.Data[i];
    Char_t temp[256];
    sprintf(temp,"(%s+%s)/2",PassName,v.PassName);
    strcpy(PassName,temp);
  }
  SurveyPass_t operator-= (SurveyPass_t &v) {
    for (Int_t i = 0; i < 24; i++) Data[i] -= v.Data[i];
    Char_t temp[256];
    sprintf(temp,"(%s-%s)/2",PassName,v.PassName);
    strcpy(PassName,temp);
  }
};
#endif /* __SurveyPass_h__ */
