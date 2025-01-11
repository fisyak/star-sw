#ifndef __StGmtMatchMaker_H
#define __StGmtMatchMaker_H
#include "StMaker.h"
#include "TFile.h"
#include "TArrayI.h"
#include "TTree.h"
class EventT;
class StGmtMatchMaker : public StMaker {
 public:
  StGmtMatchMaker(const Char_t *name="StGmtMatchMaker");
  virtual ~StGmtMatchMaker() {}
  virtual Int_t Init();
  virtual Int_t Make();
  virtual Int_t Finish();
  void SetTree();
  void Print(Option_t *opt="") const;
  void SetMinNoHits(Int_t MinNoHits=0) {fMinNoHits = MinNoHits;}
  void SetpCut(Double_t pCut=0.0) {fpCut = pCut;}
  void SetOut(const Char_t *Out="Event") {fOut = Out;}
  void MakeListOfRotations();
 private:
  TFile   *fFile;
  TTree   *fTree;
  EventT  *fEvent;
  Int_t    fMinNoHits;
  Double_t fpCut;
  const Char_t  *fOut;
  ClassDef(StGmtMatchMaker,1)
};
#endif
