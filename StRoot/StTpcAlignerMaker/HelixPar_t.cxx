#include <string.h>
#include "HelixPar_t.h"
#include "TRSymMatrix.h"
#include "TMath.h"
#include "SectorTrack.h"
//________________________________________________________________________________
ostream&  operator<<(ostream& os, const HelixPar_t &v) {
  os << Form("sector %2i Rho = %10.3g +/- %10.3g",v.sector, v.Rho, v.dRho);
  //  os << Form("<drift> %8.3f step %8.3f ", v.DriftZ, v.step);
  os << Form(" step %8.3f", v.step);
  for (Int_t i = 0; i < 6; i++) {
    if      (i == 0) os << " xG:";
    else if (i == 3) os << " nG:";
    os << Form(" %8.3f",v.xyzG()[i]);
  }
  for (Int_t i = 0; i < 6; i++) {
    if      (i == 0) os << " x:";
    else if (i == 3) os << " n:";
    Int_t ii = TRSymMatrix::IJ(i,i);
    Double_t err = -13;
    if (v.fCov[ii] >= 0) err = TMath::Sqrt(v.fCov[ii]);
    os << Form(" %8.3f +/- %8.3f", v.xyz()[i], err);
  }
  os << endl;
  TRSymMatrix C(6,v.fCov);
  TRSymMatrix cor(C,TRArray::kSCor);
  os << "Correlations: " << cor << endl;
  os << "\tPoints = " << v.Npoints << "\tused = " << v.Nused << "\tchi2/Ndf = " << v.Chi2 << "/" << v.Ndf;
  return os;
}
//_____________________________________________________________________________
HelixPar_t &HelixPar_t::operator-=(const HelixPar_t &v) {
  for (Int_t i = 0; i < 6; i++) xyzG()[i] -= v.xyzG()[i];
  for (Int_t i = 0; i < 6; i++) xyz()[i] -= v.xyz()[i];
  for (Int_t i = 0; i < 21; i++) fCov[i] += v.fCov[i];
  return *this;
}
//_____________________________________________________________________________
HelixPar_t &HelixPar_t::operator=(const THelixFitter &helix) {
  Chi2 = helix.Chi2();
  Ndf  = helix.Ndf();
  Npoints = helix.Size();
  Nused   = helix.Used();
  helix.Get(xyzG(),pxyzG(),Rho);
  return *this;
}
//_____________________________________________________________________________
HelixPar_t &HelixPar_t::operator=(const SectorTrack &v) {
  sector = v.Sector();
  step   = v.Step();
  *this = v.Helix();
  v.fR.GetXYZ(xyz());
  v.fN.GetXYZ(pxyz());
  memcpy(fCov, v.fCov.GetArray(), 21*sizeof(Double_t));
  return *this;
}
//_____________________________________________________________________________
void HelixPar_t::Print(Option_t *opt) const {
  cout << *this << endl;
}
