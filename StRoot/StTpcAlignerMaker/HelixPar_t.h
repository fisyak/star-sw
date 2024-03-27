#ifndef __HelixPar_t_h
#define __HelixPar_t_h
#include "TObject.h"
#include "SectorTrack.h"
#include "THelixTrack.h"
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
  const Double_t *xyz() const {return &x;}
  Double_t     *pxyzG() {return &nxG;}
  Double_t      *xyzG() {return &xG;}
  const Double_t  *xyzG() const {return &xG;}
  //  StThreeVectorD xyz;  // Coordinates
  Double_t       fCov[21];  // Covarianve matrix from Helix fit for (X,Y,Z,dirX,dirY,dirZ);
  Double_t       Chi2;
  Int_t          Ndf;
  Int_t          Npoints;
  Int_t          Nused;
  Double_t       DriftZ; // average drift distance for this track
  Double_t       step;
  Char_t         end[1]; // !
  void           Print(Option_t *opt = "") const; 
  void           Clear(Option_t *opt = 0) {if (opt); memset(beg, 0, end-beg);}
  HelixPar_t    &operator=(const THelixFitter &v);
  HelixPar_t    &operator-=(const HelixPar_t &v);
  HelixPar_t    &operator=(const SectorTrack &v);
  ClassDef(HelixPar_t, 1)
};
ostream&  operator<<(ostream& os, const HelixPar_t &v);
#endif /* __HelixPar_t_h */
