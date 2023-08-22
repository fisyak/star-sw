#ifndef StarPHQMDPrimaryGenerator_h
#define StarPHQMDPrimaryGenerator_h
#include "StarMCPrimaryGenerator.h"
#include "TH1.h"
#include "TTree.h"
#include "TString.h"
#include "TTreeIter.h"
class StarPHQMDPrimaryGenerator : public StarMCPrimaryGenerator  {
 public:
  StarPHQMDPrimaryGenerator(TString mode="pp:W:510", Int_t tune=320);
  virtual ~StarPHQMDPrimaryGenerator() {}
  
  static StarPHQMDPrimaryGenerator* Instance() {return (StarPHQMDPrimaryGenerator*) StarMCPrimaryGenerator::Instance();}
  virtual void GeneratePrimaries();
  virtual void GeneratePrimaries(const TVector3 v);
  virtual void SetGenerator(TString mode="pp:W:510", Int_t tune=320);
  virtual void SetSpread(Double_t xs = 0.15, Double_t ys = 0.15, Double_t zs = 42.0) { gSpreadX = xs; gSpreadY = ys; gSpreadZ = zs;}
 private:
  TTreeIter *fTreeIter;
  TTree     *fTree;
  virtual void GeneratePrimary();
  virtual void PreSet();
  TH1 *fPVX, *fPVY, *fPVZ, *fPVxyError; 
  Double_t gSpreadX, gSpreadY, gSpreadZ;
  ClassDef(StarPHQMDPrimaryGenerator,1)  //StarPHQMDPrimaryGenerator
};
#endif //StarPHQMDPrimaryGenerator_h

