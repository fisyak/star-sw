// $Id: StarMCPrimaryGenerator.h,v 1.3 2011/02/11 16:12:52 fisyak Exp $
// $Log: StarMCPrimaryGenerator.h,v $
// Revision 1.3  2011/02/11 16:12:52  fisyak
// Fixes for gcc451
//
// Revision 1.2  2009/03/31 22:43:11  fisyak
// comment out not used  variables
//
// Revision 1.1.1.1  2008/12/10 20:45:53  fisyak
// Merge with macos version
//
// Revision 1.3  2005/06/09 20:13:47  fisyak
// It looks like that all hits in place (calorimeters have to be check for volumeid)
//
// Revision 1.2  2005/05/03 15:42:14  fisyak
// Adjust for bfc
//
// Revision 1.1  2005/04/25 20:44:28  fisyak
// StarVMCApplication with example in macros/starVMC.C
//

#ifndef Star_PRIMARY_GENERATOR_H
#define Star_PRIMARY_GENERATOR_H
#include <assert.h>
#include <stdio.h> 
#include <vector>
#include "Stiostream.h"
#include "TString.h"
#include "TMath.h"
#include "TVector3.h"
#include "StarStack.h"
#include "TRandom.h"
#include "TPDGCode.h"
#include "TDatabasePDG.h"
#include "StarVMCApplication.h"
#include "StarGenerator/BASE/StarParticleStack.h"
#include "StMessMgr.h" 
#include "Stypes.h"
#include "TSystem.h"
#include "TROOT.h"
#include "TFile.h"
#include "TH1.h"
#include "TH2.h"
#include "TTree.h"
#include "TTreeIter.h"
#include "TGeant3.h"
#include "TVirtualMC.h"
#include "StDetectorDbMaker/St_beamInfoC.h"
class StarMCPrimaryGenerator : public TObject {
 public:
 StarMCPrimaryGenerator();
  virtual ~StarMCPrimaryGenerator() {fgInstance = 0;}
  static StarMCPrimaryGenerator* Instance()   { return fgInstance;}
  void  SetIsRandom(Bool_t isRandomGenerator) { fIsRandom = isRandomGenerator; }
  void  SetNofPrimaries(Int_t nofPrimaries)   { fNofPrimaries = nofPrimaries; }
  void  SetStack(StarStack *stack)            { fStarStack = stack;}
  void  SetStack(StarParticleStack *stack);
  void  SetOption(const Char_t *opt)          { fOption = opt;}
  void  SetDebug(Int_t m)                     { fDebug = m;}
  void  SetOrigin(Double_t x, Double_t y, Double_t z) {fOrigin = TVector3(x,y,z);}
  void  SetOrigin(const TVector3 &xyz)        { fOrigin = xyz;}
  void  SetVertex(Double_t x, Double_t y, Double_t z) {SetOrigin(x,y,z); fSetVertex = kTRUE;}
  void  SetVertex(const TVector3 &xyz)        {SetOrigin(xyz); fSetVertex = kTRUE;}
  void  UnSetVertex()                         {fSetVertex = kFALSE;}
  void  SetSigmasOrigin(Double_t sigma_x, Double_t sigma_y, Double_t sigma_z) {fSigmasOrigin = TVector3(sigma_x,sigma_y,sigma_z);}
  void  SetSigmasOrigin(const TVector3 &xyz)  { fSigmasOrigin = xyz;}
  void  SetBeamLine(Bool_t k = kTRUE)         {fUseBeamLine = k;}
  void  SetStatus(Int_t status = 0)           {fStatus = status;}
  virtual void SetSpread(Double_t xs = 0.15, Double_t ys = 0.15, Double_t zs = 42.0) { gSpreadX = xs; gSpreadY = ys; gSpreadZ = zs;}
  virtual void SetGun(Int_t Id=6, 
		      Double_t px = -0.185378, Double_t py = -0.982667, Double_t pz = 1.166532,
		      Double_t x = 0, Double_t y = 0, Double_t z = -1.65956, const Char_t *option = "G");
  static Double_t Temperature() {return fTemperature;}
  void static SetTemperature(Double_t T) {fTemperature = T;}
  Int_t GetNofPrimaries()                     { return fNofPrimaries;}
  virtual Int_t Skip(Int_t nskip);
  const Option_t* GetOption() const           { return fOption.Data();}
  StarStack *GetStack()                       { return fStarStack;}
  Int_t Debug()                               { return fDebug;}
  Int_t Status()                              { return fStatus;}
  TVector3 &GetOrigin()                       { return fOrigin;}
  TVector3 &GetCurOrigin()                    { return fCurOrigin;}
  TVector3 &GetSigmasOrigin()                 { return fSigmasOrigin;}
  virtual void SetGenerator(Int_t nprim=1, Int_t Id=6, 
			    Double_t pT_min = 0,Double_t pT_max = 1000,
			    Double_t Eta_min=-10, Double_t Eta_max=10, 
			    Double_t Phi_min = 0, Double_t Phi_max= 2*TMath::Pi(), 
			    Double_t Z_min=0, Double_t Z_max=0, const Char_t *option = "G"); 
  virtual void GeneratePrimaries();
  virtual void GeneratePrimary() {}
  virtual void Print(Option_t *option="") const;
 protected:
  static StarMCPrimaryGenerator *fgInstance;
  StarStack        *fStarStack;    
  Bool_t            fIsRandom;
  Int_t             fNofPrimaries;
  TString           fOption;  
  Int_t             fDebug;
  Int_t             fId;
  TVector3          fOrigin;
  TVector3          fSigmasOrigin;
  TVector3          fCurOrigin; // Currrent origin
  Bool_t            fSetVertex;
  Bool_t            fUseBeamLine;
  Int_t             fStatus;
  TTreeIter        *fTreeIter;
  TTree            *fTree;
  TH1              *fPVX, *fPVY, *fPVZ, *fPVxyError; 
  TH2              *fPVxy;
  Double_t          gSpreadX, gSpreadY, gSpreadZ;
  Double_t          fpT_min, fpT_max, fEta_min, fEta_max, fPhi_min, fPhi_max, fZ_min, fZ_max;
  Bool_t            fGun;
  Double_t          fGunpX, fGunpY, fGunpZ, fGunX, fGunY, fGunZ;
  Int_t             fGunId;
  vector<Int_t>     fGunIds;
  static Double_t fTemperature;
  ClassDef(StarMCPrimaryGenerator,1)  //StarMCPrimaryGenerator
};
#endif //Star_PRIMARY_GENERATOR_H

