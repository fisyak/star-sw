#ifndef __StGmtMatchMaker_H
#define __StGmtMatchMaker_H
#include "StMaker.h"
#include "TFile.h"
#include "TArrayI.h"
#include "TTree.h"
class GmtEvent;
class StGmtMatchMaker : public StMaker {
 public:
  StGmtMatchMaker(const Char_t *name="StGmtMatchMaker");
  virtual ~StGmtMatchMaker() {}
  virtual Int_t Init();
  virtual Int_t Make();
  virtual Int_t Finish();
  void SetTree();
  void Print(Option_t *opt="") const;
  static void SetMinNoHits(Int_t MinNoHits=0) {fMinNoHits = MinNoHits;}
  static void SetpCut(Double_t pCut=0.0) {fpCut = pCut;}
  void SetOut(const Char_t *Out="Event") {fOut = Out;}
  void MakeListOfRotations();
 private:
  TFile   *fFile;
  TTree   *fTree;
  GmtEvent  *fEvent;
  static Int_t    fMinNoHits;
  static Double_t fpCut;
  const Char_t  *fOut;
  ClassDef(StGmtMatchMaker,1)
};
#endif
