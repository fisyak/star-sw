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
class StarMCSimplePrimaryGenerator : public StarMCPrimaryGenerator  {
 public:
  StarMCSimplePrimaryGenerator(StarStack* stack) : StarMCPrimaryGenerator() { PreSet(); fStarStack = stack; }
  StarMCSimplePrimaryGenerator(Int_t    nprim,   Int_t    Id, 
			       Double_t pT_min , Double_t pT_max,
			       Double_t Eta_min, Double_t Eta_max, 
			       Double_t Phi_min, Double_t Phi_max, 
			       Double_t Z_min,   Double_t Z_max, 
			       const Char_t *option);
  virtual ~StarMCSimplePrimaryGenerator() {}
  
  static StarMCSimplePrimaryGenerator* Instance() {return (StarMCSimplePrimaryGenerator*) StarMCPrimaryGenerator::Instance();}
 private:
  void GeneratePrimary();
  void PreSet();
  ClassDef(StarMCSimplePrimaryGenerator,1)  //StarMCSimplePrimaryGenerator
};
#endif //StarMCSimplePrimaryGenerator_h

