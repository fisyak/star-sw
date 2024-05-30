#ifndef __HelixPar_t_h
#define __HelixPar_t_h
#include "Riostream.h"
#include "TObject.h"
#include "SectorTrack.h"
#include "THelixTrack.h"
//________________________________________________________________________________
class HelixPar_t : public TObject {
 public:
  Char_t         beg[1]; // !
  Int_t          sector;
  Double_t       Rho; // curvature
  Double_t      dRho;
  Double_t       x, y, z, nx, ny, nz;      // Sup12S
  Double_t       xG, yG, zG, nxG, nyG, nzG; // Global
  Double_t       xTpc, yTpc, zTpc, nxTpc, nyTpc, nzTpc;      // Tpc
  Double_t       xHalf, yHalf, zHalf, nxHalf, nyHalf, nzHalf;       // Half
  Double_t       xPad, yPad, zPad, nxPad, nyPad, nzPad;  // Pad
  Double_t       xPadGG, yPadGG, zPadGG, nxPadGG, nyPadGG, nzPadGG;  // PadGG
  //  StThreeVectorD pxyz; // Direction
  Double_t     *pxyz() {return &nx;}
  Double_t      *xyz() {return &x;}
  const Double_t *xyz() const {return &x;}
  Double_t     *pxyzG() {return &nxG;}
  Double_t      *xyzG() {return &xG;}
  const Double_t *xyzG() const {return &xG;}
  Double_t     *pxyzTpc() {return &nxTpc;}
  Double_t      *xyzTpc() {return &xTpc;}
  const Double_t *xyzTpc() const {return &xTpc;}
  Double_t     *pxyzHalf() {return &nxHalf;}
  Double_t      *xyzHalf() {return &xHalf;}
  const Double_t *xyzHalf() const {return &xHalf;}
  Double_t     *pxyzPad() {return &nxPad;}
  Double_t      *xyzPad() {return &xPad;}
  const Double_t *xyzPad() const {return &xPad;}
  Double_t     *pxyzPadGG() {return &nxPadGG;}
  Double_t      *xyzPadGG() {return &xPadGG;}
  const Double_t *xyzPadGG() const {return &xPadGG;}
  //  StThreeVectorD xyz;  // Coordinates
  Double_t       fCov[21];  // Covarianve matrix from Helix fit for (X,Y,Z,dirX,dirY,dirZ);
  Double_t       Chi2;
  Int_t          Ndf;
  Int_t          Npoints;
  Int_t          Nused;
  Double_t       DriftZ; // average drift distance for this track
  Double_t       step;
  Double_t       yRef;
  Char_t         end[1]; // !
  void           Print(Option_t *opt = "") const; 
  void           Clear(Option_t *opt = 0) {if (opt); memset(beg, 0, end-beg);}
  HelixPar_t    &operator=(const THelixFitter &v);
  HelixPar_t    &operator-=(const HelixPar_t &v);
  HelixPar_t    &operator=(const SectorTrack &v);
  static Int_t _debug;
  ClassDef(HelixPar_t, 1)
};
std::ostream&  operator<<(std::ostream& os, const HelixPar_t &v);
#endif /* __HelixPar_t_h */
