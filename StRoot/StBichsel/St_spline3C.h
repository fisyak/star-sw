#ifndef St_spline3C_h
#define St_spline3C_h

#include "TChair.h"
//#include "tables/St_spline3_Table.h"
#include "St_spline3_Table.h"
#include "TSpline.h"
#include "TF1.h"
class St_spline3C : public TChair {
 public:
  St_spline3C(St_spline3 *table=0);
  virtual ~St_spline3C() {}
  spline3_st   *Struct(Int_t i = 0) 	const {return ((St_spline3*) Table())->GetTable()+i;}
  UInt_t     	getNumRows()                	const {return GetNRows();}
  Int_t 	nknots(Int_t i = 0) 	const {return Struct(i)->nknots;}
  Double_t* 	Xknots(Int_t i = 0) 	const {return Struct(i)->Xknots;}
  Double_t* 	Yknots(Int_t i = 0) 	const {return Struct(i)->Yknots;}
  Double_t      ValBeg(Int_t i = 0) 	const {return Struct(i)->ValBeg;}
  Double_t      ValEnd(Int_t i = 0) 	const {return Struct(i)->ValEnd;}
  Char_t* 	option(Int_t i = 0) 	const {return (Char_t *) Struct(i)->option;}
  TSpline3*     Spline() {return fSpline;}
  Double_t      operator() (Double_t *x, Double_t *p) const {return fSpline->Eval(x[0]);}
  TF1*          Func() {return fFunc;}
  static        St_spline3  *Open(const Char_t *path);
  TSpline3*     fSpline;
  TF1*          fFunc;
 protected:
 private:
  ClassDefChair(St_spline3, spline3_st )
  ClassDef(St_spline3C,1) //C++ TChair for spline3 table class
};
class Stspline3LndNdxL10 : public St_spline3C {// Log(dN/dx) versus log10(beta*gamma)
 public:
  static Stspline3LndNdxL10* 	instance();
  Stspline3LndNdxL10(St_spline3 *table=0) : St_spline3C(table) {}
  virtual ~Stspline3LndNdxL10() {fgInstance = 0;}
 private:
  static Stspline3LndNdxL10* fgInstance;
  ClassDef(Stspline3LndNdxL10,1) //C++ TChair for spline3LndNdxL10
};
#endif
