#ifndef __EVENT__
#define __EVENT__
#include "TObject.h"
#include "TTree.h"
#include "TChain.h"
#include "TClonesArray.h"
#include "THashList.h"
#include "TROOT.h"
#include "TFile.h"
#include "GmtTrack.h"
class TGeoHMatrix;
class StGmtPoint;
class StHit;
class GmtEventHeader {
 private:
  Int_t      fEvtNum;
  Int_t      fRun;
  Int_t      fDate;
  Double32_t fField;
 public:
  GmtEventHeader() : fEvtNum(0), fRun(0), fDate(0), fField(0) { }
  virtual ~GmtEventHeader() { }
  void   Set(Int_t i, Int_t r, Int_t d, Double32_t Field = 0) 
  { fEvtNum = i; fRun = r; fDate = d; fField = Field;}
  Int_t  GetEvtNum() const { return fEvtNum; }
  Int_t  GetRun() const { return fRun; }
  Int_t  GetDate() const { return fDate; }
  Double32_t GetField() const {return fField;}
  
  ClassDef(GmtEventHeader,1)  //GmtEvent Header
};
class StEvent;

class GmtEvent : public TObject {
  
 private:
  UInt_t         fNPTracks;
  UInt_t         fNtrack;            //Number of tracks
  Int_t          fNpoint;              //Number of points
  UInt_t         fFlag;
  GmtEventHeader    fEvtHdr;
  Double32_t     fVertex[3];         //
  Double32_t     fCovariantMatrix[6];//
  TClonesArray  *fTracks;            //->array with all tracks
  TClonesArray  *fPoints;              //->array with all points
  Bool_t         fIsValid;           //
  
  static TClonesArray *fgTracks;
  static TClonesArray *fgPoints;
  static THashList *fRotList;
 
 public:
  GmtEvent();
  virtual ~GmtEvent();
  Int_t             Build(StEvent *pEvent, Double_t pCut = 0.2, Int_t NoMinPoint = 15);			        
  void              Clear(Option_t *option ="");								     
  void              Reset(Option_t *opt);
  static void       SetRotMatrices(THashList *Rot) {fRotList = Rot;}
  static void       RestoreListOfRotations();
  static THashList *RotMatrices() {return fRotList;}
  virtual void      Print(Option_t *opt="") const;
  ClassDef(GmtEvent,1)  //GmtEvent structure
};
#endif
