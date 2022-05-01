// $Id: StarMCSimplePrimaryGenerator.h,v 1.1.1.1 2008/12/10 20:45:52 fisyak Exp $
// $Log: StarMCSimplePrimaryGenerator.h,v $
// Revision 1.1.1.1  2008/12/10 20:45:52  fisyak
// Merge with macos version
//
// Revision 1.1  2005/06/09 20:13:47  fisyak
// It looks like that all hits in place (calorimeters have to be check for volumeid)
//
// Revision 1.2  2005/05/03 15:42:14  fisyak
// Adjust for bfc
//
// Revision 1.1  2005/04/25 20:44:28  fisyak
// StarVMCApplication with example in macros/starVMC.C
//

#ifndef StarMCSimplePrimaryGenerator_h
#define StarMCSimplePrimaryGenerator_h
#include "StarMCPrimaryGenerator.h"
#include "TH1.h"
#include "TH2.h"
#include <vector>
class StarMCSimplePrimaryGenerator : public StarMCPrimaryGenerator  {
 public:
  StarMCSimplePrimaryGenerator(StarStack* stack) : StarMCPrimaryGenerator() { PreSet(); fStarStack = stack; }
  StarMCSimplePrimaryGenerator(Int_t    nprim=1,     Int_t    Id=6, 
			       Double_t pT_min =  0, Double_t pT_max = 10,
			       Double_t Eta_min=-10, Double_t Eta_max=10, 
			       Double_t Phi_min = 0, Double_t Phi_max= 2*TMath::Pi(), 
			       Double_t Z_min=0,     Double_t Z_max=0, 
			       const Char_t *option = "G");
  virtual ~StarMCSimplePrimaryGenerator() {}
  
  static StarMCSimplePrimaryGenerator* Instance() {return (StarMCSimplePrimaryGenerator*) StarMCPrimaryGenerator::Instance();}
  static Double_t Temperature() {return fTemperature;}
  void static SetTemperature(Double_t T) {fTemperature = T;}
  virtual void GeneratePrimaries();
  virtual void GeneratePrimaries(const TVector3& v);
  virtual void SetGenerator(Int_t nprim=1, Int_t Id=6, 
			    Double_t pT_min = 0,Double_t pT_max = 1000,
			    Double_t Eta_min=-10, Double_t Eta_max=10, 
			    Double_t Phi_min = 0, Double_t Phi_max= 2*TMath::Pi(), 
			    Double_t Z_min=0, Double_t Z_max=0, const Char_t *option = "G");
  virtual void SetGun(Int_t Id=6, 
		      Double_t px = -0.185378, Double_t py = -0.982667, Double_t pz = 1.166532,
		      Double_t x = 0, Double_t y = 0, Double_t z = -1.65956, const Char_t *option = "G");
 private:
  void GeneratePrimary();
  void PreSet();
  Double_t fpT_min, fpT_max, fEta_min, fEta_max, fPhi_min, fPhi_max, fZ_min, fZ_max;
  Bool_t fGun;
  Double_t fGunpX, fGunpY, fGunpZ, fGunX, fGunY, fGunZ;
  Int_t    fGunId;
  TH1 *fPVX, *fPVY, *fPVZ, *fPVxyError; 
  TH2 *fPVxy;
  static Double_t fTemperature;
  vector<Int_t> fGunIds;
  ClassDef(StarMCSimplePrimaryGenerator,1)  //StarMCSimplePrimaryGenerator
};
#endif //StarMCSimplePrimaryGenerator_h

