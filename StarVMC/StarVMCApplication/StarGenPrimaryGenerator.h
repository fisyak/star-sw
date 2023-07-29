#ifndef StarGenPrimaryGenerator_h
#define StarGenPrimaryGenerator_h
#include "StarMCPrimaryGenerator.h"
#include "TH1.h"
#include "TTree.h"
#include "TString.h"
#include "TTreeIter.h"
class StarGenPrimaryGenerator : public StarMCPrimaryGenerator  {
 public:
  StarGenPrimaryGenerator(TString mode="pp:W:510", Int_t tune=320);
  virtual ~StarGenPrimaryGenerator() {}
  
  static StarGenPrimaryGenerator* Instance() {return (StarGenPrimaryGenerator*) StarMCPrimaryGenerator::Instance();}
  virtual void GeneratePrimaries();
  virtual void GeneratePrimaries(const TVector3& v);
  virtual void SetGenerator(TString mode="pp:W:510", Int_t tune=320);
  virtual void SetSpread(Double_t xs = 0.15, Double_t ys = 0.15, Double_t zs = 42.0) { gSpreadX = xs; gSpreadY = ys; gSpreadZ = zs;}
 private:
  TTreeIter *fTreeIter;
  TTree     *fTree;
  virtual void GeneratePrimary();
  virtual void PreSet();
  TH1 *fPVX, *fPVY, *fPVZ, *fPVxyError; 
  Double_t gSpreadX, gSpreadY, gSpreadZ;
  ClassDef(StarGenPrimaryGenerator,1)  //StarGenPrimaryGenerator
};
#endif //StarGenPrimaryGenerator_h

