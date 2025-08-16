#ifndef StarUrQMDPrimaryGenerator_h
#define StarUrQMDPrimaryGenerator_h
#include "StarMCPrimaryGenerator.h"
#include "TH1.h"
#include "TString.h"
class StarUrQMDPrimaryGenerator : public StarMCPrimaryGenerator  {
 public:
  StarUrQMDPrimaryGenerator(TString mode="pp:W:510", Int_t tune=320);
  virtual ~StarUrQMDPrimaryGenerator() {}
  
  static StarUrQMDPrimaryGenerator* Instance() {return (StarUrQMDPrimaryGenerator*) StarMCPrimaryGenerator::Instance();}
 private:
  TTreeIter *fTreeIter;
  TTree     *fTree;
  virtual void GeneratePrimary();
  virtual void PreSet();
  TH1 *fPVX, *fPVY, *fPVZ, *fPVxyError; 
  Double_t gSpreadX, gSpreadY, gSpreadZ;
  ClassDef(StarUrQMDPrimaryGenerator,1)  //StarUrQMDPrimaryGenerator
};
#endif //StarUrQMDPrimaryGenerator_h

