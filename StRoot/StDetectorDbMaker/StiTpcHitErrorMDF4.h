#ifndef StiTpcHitErrorMDF4_h
#define StiTpcHitErrorMDF4_h
#include <assert.h>
#include "Sti/StiNodePars.h"
#include "St_MDFCorrection4C.h"
#include "StDetectorDbMaker/St_tpcDriftVelocityC.h"
#include "StDetectorDbMaker/St_tpcPadConfigC.h"
class StiTpcHitErrorMDF4 : public St_MDFCorrection4C {
 public:
  virtual void  calculateError(Double_t _z,  Double_t _eta, Double_t _tanl, 
			       Double_t &ecross, Double_t &edip, 
			       Double_t fudgeFactor = 1, Double_t AdcL = 5.5, Double_t *dZ = 0, Double_t *dX = 0) const;
  virtual void  calculateError(const StiNodePars *pars,
			       Double_t &ecross, Double_t &edip, 
			       Double_t fudgeFactor = 1,  Double_t AdcL = 5.5, Double_t *dZ = 0, Double_t *dX = 0) const {
    calculateError(pars->z(),  pars->eta(), pars->tanl(),  ecross, edip, fudgeFactor, AdcL, dZ, dX);
  }
  Int_t IO() const {return fio;}
 protected:
 StiTpcHitErrorMDF4(St_MDFCorrection4 *table=0, Int_t io = -1) : St_MDFCorrection4C(table), fio(io) {}
  virtual ~StiTpcHitErrorMDF4();
  Int_t fio; // => 0 iTPC, 1 => Tpx, -1 -> Undefined
  Bool_t fifFXT;
 private:
  void convert(Double_t _z,  Double_t _eta, Double_t _tanl, Double_t AdcL) const;
  mutable Double_t fxx[4];
  virtual  Double_t padPitch() const {
    switch (fio) {
    case 0: return St_tpcPadConfigC::instance()->innerSectorPadPitch();
    case 1: return St_tpcPadConfigC::instance()->outerSectorPadPitch();
    default: assert(0);
    };
  }
  Double_t timePitch() const {return St_tpcDriftVelocityC::instance()->timeBucketPitch();}
  ClassDefineChair(StiTpcHitErrorMDF4,St_MDFCorrection4, MDFCorrection4_st )
  ClassDef(StiTpcHitErrorMDF4,1) //C++ TChair for MDFCorrection4 table class
};
//________________________________________________________________________________
class StiTpcInnerHitErrorMDF4 : public StiTpcHitErrorMDF4 {
 public:
  static StiTpcInnerHitErrorMDF4 *instance();
 protected:  
 StiTpcInnerHitErrorMDF4(St_MDFCorrection4 *table=0) : StiTpcHitErrorMDF4(table, 0) {}
  virtual ~StiTpcInnerHitErrorMDF4() {fgInstance = 0;}
 private:
  static StiTpcInnerHitErrorMDF4* fgInstance;
  ClassDef(StiTpcInnerHitErrorMDF4,1) //C++ TChair for MDFCorrection4 table class
};
//________________________________________________________________________________
class StiTpcOuterHitErrorMDF4 : public StiTpcHitErrorMDF4 {
 public:
  static StiTpcOuterHitErrorMDF4 *instance();
 protected:
 StiTpcOuterHitErrorMDF4(St_MDFCorrection4 *table=0) : StiTpcHitErrorMDF4(table, 1) {}
  virtual ~StiTpcOuterHitErrorMDF4() {fgInstance = 0;}
 private:
  static StiTpcOuterHitErrorMDF4* fgInstance;
  ClassDef(StiTpcOuterHitErrorMDF4,1) //C++ TChair for MDFCorrection4 table class
};

#endif
