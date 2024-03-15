// $Id: StTpcAlignerMaker.h,v 1.7 2014/09/10 13:54:58 fisyak Exp $
#ifndef STAR_StTpcAlignerMaker
#define STAR_StTpcAlignerMaker
/*!
 *                                                                     
 * \class  StTpcAlignerMaker
 * \author fisyak
 * \date   2004/10/01
 * \brief  virtual base class for Maker
 *
 * This commented block at the top of the header file is considered as
 * the class description to be present on the this class Web page. 
 *
 * 
 * StTpcAlignerMaker virtual base class for Maker                        
 * Template Maker doing nothing. See README file in StRoot/StTpcAlignerMaker
 *
 *
 */                                                                      
#ifndef StMaker_H
#include "StMaker.h"
#endif
#include "StThreeVectorF.hh"
#include "StThreeVectorD.hh"
#include "TRSymMatrix.h"
#include "TRMatrix.h"
#include "TList.h"
#include "TString.h"
#include "TNamed.h"
#include "THelixTrack.h"
#include "TGeoMatrix.h"
class StEvent;
class StPrimaryVertex;
//________________________________________________________________________________
class HelixPar_t : public TObject {
 public:
  Char_t         beg[1]; // !
  Int_t          sector;
  Double_t       Rho; // curvature
  Double_t       x, y, z;
  Double_t       nx, ny, nz;
  Double_t       xG, yG, zG;
  Double_t       nxG, nyG, nzG;
  Double_t      dRho;
  //  StThreeVectorD pxyz; // Direction
  Double_t     *pxyz() {return &nx;}
  Double_t      *xyz() {return &x;}
  Double_t     *pxyzG() {return &nxG;}
  Double_t      *xyzG() {return &xG;}
  //  StThreeVectorD xyz;  // Coordinates
  Double_t       fCov[15];  // Covarianve matrix from Helix fit for (X,Z,dirX,dirY,dirZ);
  Double_t       Chi2;
  Int_t          Ndf;
  Int_t          Npoints;
  Int_t          Nused;
  Double_t       DriftZ; // average drift distance for this track
  Double_t       step;
  Double_t RefSurficeG[4]; // Ref. surfice in GCS
  Char_t         end[1]; // !
  void           Print(Option_t *opt = "") const; 
  void           Clear(Option_t *opt = 0) {if (opt); memset(beg, 0, end-beg);}
  HelixPar_t    &operator=(const THelixFitter &v);
  ClassDef(HelixPar_t, 1)
};
ostream&  operator<<(ostream& os, const HelixPar_t &v);
//________________________________________________________________________________
class StTpcInOutMatch : public TObject {
public:
  StTpcInOutMatch() {}
  ~StTpcInOutMatch() {}
  Char_t         beg[1]; // !
  Int_t    TriggerId;
  Double_t field;
  Double_t driftVel;
  Double_t freq;
  Double_t charge;
  Int_t    NoFitPoints;
  Double_t pX, pY, pZ;
  Int_t          iPV;  //  iPV == 0 vertex has not been defined
  Double_t       xPV;
  Double_t       yPV;
  Double_t       zPV;
  //  StThreeVectorF pxyzG;
  Char_t         end[1]; // !
  HelixPar_t In;
  HelixPar_t Out;
#if 0
  HelixPar_t InAtVx;
  HelixPar_t OutAtVx;
#endif
  void        Clear(Option_t *opt = 0) {if (opt); memset(beg, 0, end-beg); In.Clear(); Out.Clear();}
  ClassDef(StTpcInOutMatch,1)
};
//________________________________________________________________________________
class SectorSegment : public TNamed {
 public: 
  SectorSegment(Int_t s, Int_t t = 0) : fRowMin(99), fSector(s), fStatus(-1) {SetName(Form("Sector_%02i_%i",fSector,t));}
  virtual ~SectorSegment() {}
  virtual Bool_t   IsSortable() const { return kTRUE; }
  Int_t   Sector() const {return fSector;}
  TList *List() {return &fList;}
  THelixFitter &Helix()       {return *&fHelix;}
  void SetSector(Int_t s, Int_t t = 0) {fSector = s; SetName(Form("Sector_%02i_%i",fSector,t));}
  void SetStatus(Int_t k) {fStatus = k;}
  Int_t Status() {return fStatus;}
  virtual Int_t    Compare(const  TObject *obj) const {
    SectorSegment *hit = (SectorSegment *) obj;
    if (Sector() > hit->Sector()) return kTRUE;
    return kFALSE;
  }
  virtual void  Print(Option_t *option="") const;
  Int_t         fRowMin;
  HelixPar_t    HlxPar; // at fRowMin
 private:
  Int_t fSector;
  TList fList;
  THelixFitter fHelix;
  Int_t fStatus;
  ClassDef(SectorSegment,1)
};
//________________________________________________________________________________
class StTpcW2SMatch : public TObject {
 public:
  StTpcW2SMatch() {}
  ~StTpcW2SMatch() {}
  Int_t          TriggerId;
  TGeoHMatrix    RW2S;      // W->S
  HelixPar_t     HlxParW;    // parameters to used to predict
  HelixPar_t     HlxParS;    // parameters to used to predict
  HelixPar_t     HlxParW2S;  // W in S coordinate system
  void           Clear(Option_t *opt = 0) {if (opt); HlxParW.Clear(); HlxParS.Clear(); HlxParW2S.Clear(); }
  ClassDef(StTpcW2SMatch,1)
};
//________________________________________________________________________________
struct Hit_t { // : public TObject {
  Int_t    row;
  Double_t x, y, z;
  Double_t err2xy[3], err2z;
  Double_t driftZ;
};
//________________________________________________________________________________
class StTpcAlignerMaker : public StMaker {
 public:
  enum {kRejected                    = BIT(19),  // take out the track from analysis
	kComingFromOutSide           = BIT(20),  // track is coming towards beam pipe
	kComingFromInSideTofMatched  = BIT(21),  // track is coming from beam pipe
        kNoToFDependece              = BIT(18)}; // Laser membrane tracks 
  StTpcAlignerMaker(const char *name="TpcAligner") : StMaker(name), fTpcInOutMatch(0) , fTpcW2SMatch(0){}
  virtual       ~StTpcAlignerMaker() {}
  virtual Int_t Init();
  virtual Int_t Make();
  Int_t         MakeIO();
  Int_t         MakeW2S();
  static Double_t Project(const Double_t n[3], const Double_t x[3]);
  static void CheckDirection(HelixPar_t *HlxPar); 
  static  TRMatrix GetSti2R(Double_t nx, Double_t ny, Double_t nz);
  virtual const char *GetCVS() const {
    static const char cvs[]="Tag $Name:  $ $Id: StTpcAlignerMaker.h,v 1.7 2014/09/10 13:54:58 fisyak Exp $ built " __DATE__ " " __TIME__ ; 
    return cvs;
  }
  static Double_t PhiFromBTofTray(Int_t tray);
  static Int_t    TpcSectorFromBTofTray(Int_t tray);
 private:
  StTpcInOutMatch *fTpcInOutMatch;
  StTpcW2SMatch *fTpcW2SMatch;
  StEvent* pEvent;
  Double_t bField;
  Double_t driftVel;
  Double_t freq;
  Int_t TriggerId;
  StPrimaryVertex *pVbest;
  ClassDef(StTpcAlignerMaker,0)
};

#endif
