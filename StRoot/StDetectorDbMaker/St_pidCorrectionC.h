#ifndef St_pidCorrectionC_h
#define St_pidCorrectionC_h

#include "TChair.h"
#include "tables/St_pidCorrection_Table.h"
#include "StEvent/StPidParticleDefinition.h"
#include "StEvent/StEnumerations.h"
class St_pidCorrectionC : public TChair {
 public:
 enum PiDStatusIDs { // from StdEdxY2Maker/StTrackCombPiD.h
    kUndef = kUndefinedMethodId,
    kI70   = kTruncatedMeanId,        
    kI70U  = kEnsembleTruncatedMeanId,
    kFit   = kLikelihoodFitId,        
    kFitU  = kWeightedTruncatedMeanId,
    kdNdx  = kOtherMethodId,          
    kdNdxU = kOtherMethodId2,         
    kBTof,   kETof,   kMtd, kBEmc, kTotal
  };
  static St_pidCorrectionC* 	instance();
  pidCorrection_st 	*Struct(Int_t i = 0) 	const {return ((St_pidCorrection*) Table())->GetTable()+i;}
  UInt_t     	getNumRows()                	const {return GetNRows();}
  Int_t 	type(Int_t i = 0)  	        const {return Struct(i)->type;}
  Int_t 	var(Int_t i = 0) 	        const {return Struct(i)->var;}	    
  Int_t 	particle(Int_t i = 0) 		const {return Struct(i)->particle;} 
  Int_t 	charge(Int_t i = 0) 		const {return Struct(i)->charge;} 
  Int_t 	pull(Int_t i = 0) 		const {return Struct(i)->pull;} 
  Int_t 	det(Int_t i = 0) 		const {return Struct(i)->det;}	    
  Int_t 	idx(Int_t i = 0) 		const {return Struct(i)->idx;}	    
  Int_t 	nrows(Int_t i = 0) 		const {return Struct(i)->nrows;}    
  Int_t 	npar(Int_t i = 0) 		const {return Struct(i)->npar;}	    
  Double_t 	OffSet(Int_t i = 0) 		const {return Struct(i)->OffSet;}   
  Double_t 	min(Int_t i = 0) 		const {return Struct(i)->min;}	    
  Double_t 	max(Int_t i = 0) 		const {return Struct(i)->max;}	    
  Double_t* 	a(Int_t i = 0)    	    	const {return Struct(i)->a;}        
  Double_t      CalcCorrection(Int_t i, Double_t x, Double_t z = 0, Int_t NparMax = -1) const;
  Double_t      SumSeries(pidCorrection_st *cor, Double_t x, Double_t z = 0, Int_t NparMax = -1) const;
  Double_t      Correction(Double_t X, Int_t part = kPidPion, Int_t det = kFit, Int_t charge = 0, Int_t pull = 0, Int_t varT = 0);
  Int_t         IsActiveChair() const;
 protected:
  St_pidCorrectionC(St_pidCorrection *table=0) : TChair(table) {}
  virtual ~St_pidCorrectionC() {fgInstance = 0;}
 private:
  static St_pidCorrectionC* fgInstance;
  ClassDefChair(St_pidCorrection, pidCorrection_st )
  ClassDef(St_pidCorrectionC,1) //C++ TChair for pidCorrection table class
};
#endif
