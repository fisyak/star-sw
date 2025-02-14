#ifndef __StGmtMatchMaker_H
#define __StGmtMatchMaker_H
#include "StMaker.h"
#include "THashList.h"
class StEvent;
class StGmtMatchMaker : public StMaker {
 public:
 StGmtMatchMaker(const Char_t *name="GmtMatch") : StMaker(name), fRotMHash(0) {}
  virtual ~StGmtMatchMaker() {}
  virtual Int_t Make();
  void MakeListOfRotations();
  Int_t Match(); 
  static void SetMinNoHits(Int_t MinNoHits=0) {fMinNoHits = MinNoHits;}
  static void SetpCut(Double_t pCut=0.0) {fpCut = pCut;}
 private:
  static Int_t    fMinNoHits;
  static Double_t fpCut;
  THashList      *fRotMHash;
  StEvent        *pEvent;
  ClassDef(StGmtMatchMaker,1)
};
#endif
