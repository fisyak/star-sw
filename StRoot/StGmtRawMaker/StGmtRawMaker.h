//
// First Cluster Maker
// \class StGmtRawMaker
// \authors K.S. Engle and Richard Witt (witt@usna.edu)
// based on StFgtClusterMaker
#ifndef STAR_StGmtRawMaker_HH
#define STAR_StGmtRawMaker_HH
#include "StMaker.h"
#include "TH1.h"
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

class StGmtStripCollection;
class StGmtHitCollection;
class StGmtCollection;

class StGmtRawMaker :  public StRTSBaseMaker {
  //omitted assignment operator and copy constructor on purpose
 public:
  StGmtRawMaker( const Char_t* name="GmtRaw");
  ~StGmtRawMaker() {}
  Int_t Init();
  Int_t InitRun(Int_t runumber);
  Int_t Make();
  /**sets the clustering algorithm. Currently there is the simple Clustering algorithm and the max cluster algorithm. 
     The simple cluster algorithm is the default one. The max cluster only selects one hit stip per plane, the one with the highest charge
  */
  virtual const char *GetCVS() const
  {static const char cvs[]="Tag $Name:  $ $Id: StGmtRawMaker.h,v 1.1.1.1 2013/09/02 15:01:02 fisyak Exp $ built " __DATE__ " " __TIME__ ; return cvs;}
  static Int_t gmtStat;
 protected:
  StGmtCollection *mGmtCollection;
  TProfile*** mPedestalXY;
  
  Int_t ClusterBuilder(ULong_t events, UInt_t module, StGmtHitCollection& hits);
  Int_t fillHits();
  TF1* FindPeaks(TH1D* hist);
  void AddPed(TH1 *adc, TProfile *pedestal);
  ClassDef(StGmtRawMaker,1)
};
#endif
