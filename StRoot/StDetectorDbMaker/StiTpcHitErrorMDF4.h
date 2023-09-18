#ifndef StiTpcHitErrorMDF4_h
#define StiTpcHitErrorMDF4_h

#include "TChair.h"
#include "tables/St_MDFCorrection4_Table.h"
#include "Sti/StiNodePars.h"
#include "St_MDFCorrection4C.h"

class StiTpcHitErrorMDF4 : public St_MDFCorrection4C {
 public:
  static StiTpcHitErrorMDF4* instance();
  virtual void  calculateiTPCError(Double_t _z,  Double_t _eta, Double_t _tanl, Double_t AdcL,
				   Double_t &ecross, Double_t &edip, 
				   Double_t fudgeFactor = 1, Double_t *dZ = 0, Double_t *dX = 0) const;
  virtual void  calculateiTPCError(const StiNodePars *pars, Double_t AdcL, 
				   Double_t &ecross, Double_t &edip, 
				   Double_t fudgeFactor = 1, Double_t *dZ = 0, Double_t *dX = 0) const {
    calculateiTPCError(pars->z(),  pars->eta(), pars->tanl(), AdcL, ecross, edip, fudgeFactor, dZ, dX);
  }
  virtual void  calculateTpxError(Double_t _z,  Double_t _eta, Double_t _tanl, Double_t AdcL,
				  Double_t &ecross, Double_t &edip, 
				  Double_t fudgeFactor = 1, Double_t *dZ = 0, Double_t *dX = 0) const;
  virtual void  calculateTpxError(const StiNodePars *pars, Double_t AdcL, Double_t &ecross, Double_t &edip, 
				  Double_t fudgeFactor = 1, Double_t *dZ = 0, Double_t *dX = 0) const {
    calculateTpxError(pars->z(),  pars->eta(), pars->tanl(), AdcL, ecross, edip, fudgeFactor, dZ, dX);
  }
 protected:
  StiTpcHitErrorMDF4(St_MDFCorrection4 *table=0) : St_MDFCorrection4C(table) {}
  virtual ~StiTpcHitErrorMDF4() {}
 private:
  static void convert(Double_t _z,  Double_t _eta, Double_t _tanl, Double_t AdcL);
  static StiTpcHitErrorMDF4 *fgInstance;
  static Double_t fxx[4];
			
  ClassDefineChair(StiTpcHitErrorMDF4,St_MDFCorrection4, MDFCorrection4_st )
  ClassDef(StiTpcHitErrorMDF4,1) //C++ TChair for MDFCorrection4 table class
};
#endif
