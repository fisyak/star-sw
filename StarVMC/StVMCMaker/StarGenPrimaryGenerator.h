#ifndef StarGenPrimaryGenerator_h
#define StarGenPrimaryGenerator_h
#include "StarMCPrimaryGenerator.h"
class StarGenPrimaryGenerator : public StarMCPrimaryGenerator  {
 public:
  StarGenPrimaryGenerator(TString mode="pp:W:510", Int_t tune=320);
  virtual ~StarGenPrimaryGenerator() {}
  
  static StarGenPrimaryGenerator* Instance() {return (StarGenPrimaryGenerator*) StarMCPrimaryGenerator::Instance();}
 private:
  virtual void GeneratePrimary();
  virtual void PreSet();
  ClassDef(StarGenPrimaryGenerator,1)  //StarGenPrimaryGenerator
};
#endif //StarGenPrimaryGenerator_h

