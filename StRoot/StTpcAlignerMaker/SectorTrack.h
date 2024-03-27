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
  void SetStatus(Int_t k) {fStatus = k;}
  Int_t Status() {return fStatus;}
  virtual Int_t    Compare(const  TObject *obj) const {
    SectorTrack *hit = (SectorTrack *) obj;
    if      (Sector() < hit->Sector()) return -1;
    else if (Sector() > hit->Sector()) return  1;
    return 0;
  }
  void  GetTpcHitErrors(StTpcHit *tpcHit, Double_t err2xy[3], Double_t &err2z);
  Int_t MakeTHelix(Double_t *RefSurfaceG = 0);
  Int_t Move(Double_t *RefSurfaceG);
  static TRMatrix GetSti2G(Double_t nx, Double_t ny, Double_t nz);
  static TRMatrix GetSti2G(TVector3 N) {return GetSti2G(N.x(), N.y(), N.z());}
  virtual void  Print(Option_t *option="") const;
  Double_t     *RefSurface() {return fRefSurface;}
  Double_t      Step() const {return fStep;}
  TVector3      fRG;
  TVector3      fNG;
  TVector3      fR;
  TVector3      fN;
  TRSymMatrix   fCov;
  Double_t      fRefSurface[4];
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
