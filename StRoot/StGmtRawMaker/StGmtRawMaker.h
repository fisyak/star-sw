//
// First Cluster Maker
// \class Stigmatic
// \authors K.S. Engle and Richard Witt (witt@usna.edu)
// based on StFgtClusterMaker
#ifndef STAR_StGmtRawMaker_HH
#define STAR_StGmtRawMaker_HH
#include "StMaker.h"
#include "TH1.h"
#include "TH2.h"
#include "TProfile.h"
#include "TROOT.h"
#include "TCanvas.h"
#include "TPolyMarker.h"
#include "StChain/StRTSBaseMaker.h"
#include "Stypes.h"
#include "TSpectrum.h"
#include "TF1.h"
#include "TMath.h"
#include "TVirtualFitter.h"
#include "StEnumerations.h"
class StGmtStripCollection;
class StGmtHitCollection;
class StGmtCollection;

class StGmtRawMaker :  public StRTSBaseMaker {
  //omitted assignment operator and copy constructor on purpose
 public:
  StGmtRawMaker( const Char_t* name="GmtRaw");
  virtual ~StGmtRawMaker() {}
  Int_t Init();
  Int_t InitRun(Int_t runumber);
  Int_t Make();
  virtual const char *GetCVS() const
  {static const char cvs[]="Tag $Name:  $ $Id: StGmtRawMaker.h,v 1.1.1.1 2013/09/02 15:01:02 fisyak Exp $ built " __DATE__ " " __TIME__ ; return cvs;}
 private:
  static Double_t  MyGaus(Double_t x, Double_t mean, Double_t sigma, Double_t delta);
  static Double_t  fpeaks(Double_t *x, Double_t *par);

  Int_t     ClusterBuilder(ULong_t events, UInt_t module, StGmtHitCollection& hits);
  Int_t     fillHits();
  TF1*      FindPeaks(TH1D* hist);
  Char_t          mBeg[1]; //!
  StGmtCollection *mGmtCollection;
  TH2F            *mAdcTimeBins[kGmtNumLayers][kGmtNumModules];
  Char_t          mEnd[1]; //!
  ClassDef(StGmtRawMaker,1)
};
#endif
