#ifndef __SectorTrack_h
#define __SectorTrack_h
#include "TNamed.h"
#include "TRMatrix.h"
#include "TRSymMatrix.h"
#include "THelixTrack.h"
#include "TVector3.h"
#include "TList.h"
class StTpcHit;
//________________________________________________________________________________
class SectorTrack : public TNamed {
 public: 
 SectorTrack(Int_t s = -1, Int_t t = 0) : fSector(s), fRow(-1), fStatus(-1), fStep(1e12)  {if (s > 0) SetName(Form("Sector_%02i_%i",fSector,t));}
  SectorTrack(const SectorTrack &v);
  virtual ~SectorTrack() {}
  virtual Bool_t   IsSortable() const { return kTRUE; }
  Int_t   Sector() const {return fSector;}
  Int_t   Row() const {return fRow;}
  TList *List() {return &fList;}
  void    AddHit(StTpcHit *tpcHit);
  const THelixFitter &Helix() const {return *&fHelix;}
  void SetSector(Int_t s, Int_t t = 0) {fSector = s; SetName(Form("Sector_%02i_%i",fSector,t));}
  void SetRow(Int_t row) {fRow = row;}
  void SetStatus(Int_t k) {fStatus = k;}
  Int_t Status() {return fStatus;}
  virtual Int_t    Compare(const  TObject *obj) const {
    SectorTrack *hit = (SectorTrack *) obj;
    if      (Sector() < hit->Sector()) return -1;
    else if (Sector() > hit->Sector()) return  1;
    return 0;
  }
  void  GetTpcHitErrors(StTpcHit *tpcHit, Double_t err2xy[3], Double_t &err2z);
  Int_t MakeTHelix(Double_t *RefSurfaceG = 0, Double_t y = 0);
  Int_t Move(Double_t *RefSurfaceG, Double_t y = 0);
  static TRMatrix GetSti2G(Double_t nx, Double_t ny, Double_t nz);
  static TRMatrix GetSti2G(TVector3 N) {return GetSti2G(N.x(), N.y(), N.z());}
  virtual void  Print(Option_t *option="") const;
  Double_t     *RefSurface() {return fRefSurface;}
  Double_t      Step() const {return fStep;}
  TVector3      fRG;    // Global
  TVector3      fNG;
  TVector3      fR;     // Local sector (12)
  TVector3      fN;
  TVector3      fRTpc;  // Tpc
  TVector3      fNTpc;
  TVector3      fRHalf; // Half
  TVector3      fNHalf;
  TVector3      fRPad;  // SubS 
  TVector3      fNPad;
  TVector3      fRPadGG;  // SubS 
  TVector3      fNPadGG;
  TRSymMatrix   fCov;
  Double_t      fRefSurface[4];
  Double_t      fyRef;
  static Int_t _debug;
 private:
  Int_t fSector; // of the first hit
  Int_t fRow;    // -"-
  Int_t fStatus;
  TList fList;
  THelixFitter fHelix;
  Double_t fStep;
  ClassDef(SectorTrack,1)
};
#endif /* __SectorTrack_h */
