#ifndef __SurveyPass_h__
#define __SurveyPass_h__
#include "Riostream.h"
#include "Rtypes.h"
#include "TString.h"
#include "TMath.h"
#include "TH1.h"
#include "TGraphErrors.h"

#include "TFile.h"
//________________________________________________________________________________
class data_t {
 public:
 data_t(Int_t msector = 0, Double_t mx = 0, Double_t  mDx = 0, Double_t  my = 0, Double_t  mDy = 0, Double_t  mz = 0, Double_t  mDz = 0, 
	Double_t  malpha = 0, Double_t  mDalpha = 0, 	Double_t  mbeta = 0, Double_t  mDbeta = 0, Double_t  mgamma = 0, Double_t 	mDgamma = 0, 
	const Char_t mComment[256] = "") :
  sector(msector), x(mx), Dx(mDx),  y(my),  Dy(mDy),  z(mz),  Dz(mDz), 
    alpha(malpha),  Dalpha(mDalpha), beta(mbeta), Dbeta(mDbeta), gamma( mgamma), Dgamma(mDgamma)
    {strcpy(Comment, mComment);}   

  Int_t sector;
  Double_t x, Dx, y, Dy, z, Dz, alpha, Dalpha, beta, Dbeta, gamma, Dgamma;
  Char_t Comment[256];
  Double_t *X() {return &x;}
  void Print() {
    cout << Form("%2i %8.2f %5.2f %8.2f %5.2f %8.2f %5.2f",sector, x, Dx, y, Dy, z, Dz)
	 << Form(" %8.2f %5.2f %8.2f %5.2f %8.2f %5.2f %s", alpha, Dalpha, beta, Dbeta, gamma, Dgamma, Comment) << endl;
  }
  Bool_t GoodMeasurement(Int_t i) {
    Double_t val = X()[2*i];
    Double_t err = X()[2*i+1];
    if (i < 3) {
      if (TMath::Abs(val) < 5000.0 && err > 0 && err < 99.0) return kTRUE;
    } else {
      if (TMath::Abs(val) <    5.0 && err > 0 && err < 0.99) return kTRUE;
    }
    return kFALSE;
  }
  void FixErrors() {
    for (Int_t i = 0; i < 6; i++) {
      if (X()[2*i+1] == 0.0) X()[2*i+1] = 0.01;
    }
  }
  data_t &operator+= (data_t &v) {
    for (Int_t i = 0; i < 6; i++) {
      Double_t val = 0;
      Double_t err = -99.9;
      if (GoodMeasurement(i) &&	v.GoodMeasurement(i)) {
	Double_t w1 = 1./(X()[2*i+1]*X()[2*i+1]);
	Double_t w2 = 1./(v.X()[2*i+1]*v.X()[2*i+1]);
	Double_t w12 = w1 + w2;
	w1 /= w12;
	w2 /= w12;
	val = w1*X()[2*i] + w2*v.X()[2*i];
	err = 1./TMath::Sqrt(w12);
      } else if (GoodMeasurement(i)) {// leave as it is
	val = X()[2*i];
	err = X()[2*i+1];
      } else if (v.GoodMeasurement(i)) {
	val = v.X()[2*i];
	err = v.X()[2*i+1];
      }
      X()[2*i  ] = val;
      X()[2*i+1] = err;
    }
    Char_t temp[256] = "Weighted Average";
    //    sprintf(temp,"(%s+%s)/2",Comment,v.Comment);
    strcpy(Comment,temp);
    return *this;
  }
  data_t &Add2(data_t &v) {
    for (Int_t i = 0; i < 6; i++) {
      Double_t val = 0;
      Double_t err = -99.9;
      if (GoodMeasurement(i) &&	v.GoodMeasurement(i)) {
	Double_t w1 = (X()[2*i+1]*X()[2*i+1]);
	Double_t w2 = (v.X()[2*i+1]*v.X()[2*i+1]);
	Double_t w12 = w1 + w2;
	w1 = 0.5;
	w2 = 0.5;
	val = w1*X()[2*i] + w2*v.X()[2*i];
	err = 0.5*TMath::Sqrt(w12);
      } else if (GoodMeasurement(i)) {// leave as it is
	val = X()[2*i];
	err = X()[2*i+1];
      } else if (v.GoodMeasurement(i)) {
	val = v.X()[2*i];
	err = v.X()[2*i+1];
      }
      X()[2*i  ] = val;
      X()[2*i+1] = err;
    }

    Char_t temp[256];
    sprintf(temp,"((%s)+(%s))/2",Comment,v.Comment);
    strcpy(Comment,temp);
    return *this;
  }
  data_t &operator-= (data_t &v) {
    for (Int_t i = 0; i < 6; i++) {
      Double_t val = 0;
      Double_t err = -99.9;
      if (GoodMeasurement(i) && v.GoodMeasurement(i)) {
	Double_t w1 = 1./(X()[2*i+1]*X()[2*i+1]);
	Double_t w2 = 1./(v.X()[2*i+1]*v.X()[2*i+1]);
	Double_t w12 = w1 + w2;
	w1 /= w12;
	w2 /= w12;
	val = w1*X()[2*i] - w2*v.X()[2*i];
	err = 1./TMath::Sqrt(w12);
      } else if (GoodMeasurement(i)) {// leave as it is
	val = X()[2*i];
	err = X()[2*i+1];
      } else if (v.GoodMeasurement(i)) {
	val = -v.X()[2*i];
	err = v.X()[2*i+1];
      }
      X()[2*i  ] = val;
      X()[2*i+1] = err;
    }
    Char_t temp[256] = "weighted difference";
    //    sprintf(temp,"(%s-%s)/2",Comment,v.Comment);
    strcpy(Comment,temp);
    return *this;
  }
  data_t &Sub2 (data_t &v) {
    for (Int_t i = 0; i < 6; i++) {
      Double_t val = 0;
      Double_t err = -99.9;
      if (GoodMeasurement(i) && v.GoodMeasurement(i)) {
	Double_t w1 = (X()[2*i+1]*X()[2*i+1]);
	Double_t w2 = (v.X()[2*i+1]*v.X()[2*i+1]);
	Double_t w12 = w1 + w2;
	w1 = 0.5;
	w2 = 0.5;
	val = w1*X()[2*i] - w2*v.X()[2*i];
	err = 0.5*TMath::Sqrt(w12);
      } else if (GoodMeasurement(i)) {// leave as it is
	val = X()[2*i];
	err = X()[2*i+1];
      } else if (v.GoodMeasurement(i)) {
	val = -v.X()[2*i];
	err = v.X()[2*i+1];
      }
      X()[2*i  ] = val;
      X()[2*i+1] = err;
    }
    Char_t temp[256];
    sprintf(temp,"((%s)-(%s))/2",Comment,v.Comment);
    strcpy(Comment,temp);
    return *this;
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
  void FixErrors() {
    for (Int_t i = 0; i < 24; i++) {
      Data[i].FixErrors();
    }
  }
  TString StripPass() {
    TString Stripped;
    TString Pass(PassName);
    if (Pass.Contains("/hlt/")) {
      Int_t index = Pass.Index("/20");
      Stripped = TString(Pass.Data()+index+1,Pass.Length()-index-4);
    } else {
      Stripped = Pass;
    }
    return Stripped;
  }
  SurveyPass_t operator+= (SurveyPass_t &v) {
    for (Int_t i = 0; i < 24; i++) Data[i] += v.Data[i];
    TString temp(StripPass());
    temp += "+";
    temp += v.StripPass();
    strcpy(PassName,temp.Data());
    return *this;
  }
  SurveyPass_t Add2(SurveyPass_t &v) {
    for (Int_t i = 0; i < 24; i++) Data[i].Add2(v.Data[i]);
    Char_t temp[256];
    sprintf(temp,"((%s)+(%s))/2",StripPass().Data(),v.StripPass().Data());
    strcpy(PassName,temp);
    return *this;
  }
  SurveyPass_t operator-= (SurveyPass_t &v) {
    for (Int_t i = 0; i < 24; i++) Data[i] -= v.Data[i];
    Char_t temp[256];
    sprintf(temp,"((%s)-(%s))/2",PassName,v.PassName);
    strcpy(PassName,temp);
    return *this;
  }
  SurveyPass_t Sub2(SurveyPass_t &v) {
    for (Int_t i = 0; i < 24; i++) Data[i].Sub2(v.Data[i]);
    Char_t temp[256];
    sprintf(temp,"((%s)-(%s))/2",StripPass().Data(),v.StripPass().Data());
    strcpy(PassName,temp);
    return *this;
  }
  Int_t GetField() {
    Int_t k = 0; // ZF
    if      (TString(PassName).Contains("FF+RF")) k = 2;
    else if (TString(PassName).Contains("FF-RF")) k = 3;
    else if (TString(PassName).Contains("RF"))    k =-1;
    else if (TString(PassName).Contains("FF"))    k = 1;
    return k;
  }
  TH1D **GetHist(const Char_t *names[6], const Char_t *nameK[6], Int_t color = 0, Int_t style = 0) {
    TH1D **hists = new TH1D*[6]; memset(hists, 0, 6*sizeof(TH1D*));
    TString Pass(StripPass());
    if (! color) {
      color = 1;
      if      (Pass.Contains("2020")) color = 2;
      else if (Pass.Contains("2021")) color = 3;
      else if (Pass.Contains("2022")) color = 4;
      else if (Pass.Contains("2023")) color = 6;
      else if (Pass.Contains("2024")) color = 7;
    }
    if (! style) {
      style = 22; // FF
      if        (Pass.Contains("RFA") ) {style = 28;
      }	else if (Pass.Contains("RFB") ) {style = 30;
      } else if (Pass.Contains("RF") )  {style = 23;
      } else if (Pass.Contains("MF") ||
		 Pass.Contains("ZF") ) {
	style = 21;
      }
    }
    for (Int_t i = 0; i < 6; i++) {
      TString Name = Form("%s%s",nameK[i],Pass.Data());
      Name.ReplaceAll("/","_");
      Name.ReplaceAll("+","_");
      TString Title = Form("Alignment fit for  %s %s",names[i],Pass.Data());
      hists[i] = (TH1D *) gDirectory->Get(Name);
      if (hists[i]) delete hists[i];
      hists[i] = new TH1D(Name,Title, 24, 0.5, 24.5);
      //      cout << "Create: " << hists[i]->GetName() << "\t" << hists[i]->GetTitle() << endl;
      hists[i]->SetMarkerColor(color);
      hists[i]->SetLineColor(color);
      hists[i]->SetMarkerStyle(style);
      hists[i]->SetXTitle("sector");
      if (i < 3) hists[i]->SetYTitle(Form("%s (#mum)",names[i]));
      else       hists[i]->SetYTitle(Form("%s (mrad)",names[i]));
      for (Int_t l = 0; l < 24; l++) {
	if (Data[l].GoodMeasurement(i)) {
	  Int_t secs = l + 1;
	  Double_t *X = Data[l].X();
	  Double_t val = X[2*i];
	  Double_t err = X[2*i+1];
	  hists[i]->SetBinContent(secs,val);
	  hists[i]->SetBinError(secs,err);
	}
      }
    }
    return hists;
  }
};
#endif /* __SurveyPass_h__ */
