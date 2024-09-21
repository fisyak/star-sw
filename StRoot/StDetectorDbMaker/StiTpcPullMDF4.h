#ifndef StiTpcPullMDF4_h
#define StiTpcPullMDF4_h
#include "Sti/StiNodePars.h"
#include "St_MDFCorrection4C.h"

class StiTpcPullMDF4 : public St_MDFCorrection4C {
 public:
  virtual void  calculatePull(Double_t _z,  Double_t _eta, Double_t _tanl, Int_t io,
			      Double_t &dYPullSQ, Double_t &dZPullSQ, Double_t AdcL = 5.5) const;
  virtual void  calculatePull(const StiNodePars *pars,
			      Double_t &dYPullSQ, Double_t &dZPullSQ, Int_t io,
			      Double_t AdcL = 5.5) const {
    calculatePull(pars->z(),  pars->eta(), pars->tanl(), io,  dYPullSQ, dZPullSQ, AdcL);
  }
  static StiTpcPullMDF4 *instance();
 protected:
 StiTpcPullMDF4(St_MDFCorrection4 *table=0) : St_MDFCorrection4C(table) {}
  virtual ~StiTpcPullMDF4() {fgInstance = 0;}
 private:
  void convert(Double_t _z,  Double_t _eta, Double_t _tanl, Double_t AdcL) const;
  mutable Double_t fxx[4];
  static StiTpcPullMDF4* fgInstance;
  ClassDefineChair(StiTpcPullMDF4,St_MDFCorrection4, MDFCorrection4_st )
  ClassDef(StiTpcPullMDF4,1) //C++ TChair for MDFCorrection4 table class
};
#endif
