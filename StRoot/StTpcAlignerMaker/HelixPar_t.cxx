#include <string.h>
#include "HelixPar_t.h"
#include "TRSymMatrix.h"
#include "TMath.h"
#include "SectorTrack.h"
Int_t HelixPar_t::_debug = 0;
//________________________________________________________________________________
std::ostream&  operator<<(std::ostream& os, const HelixPar_t &v) {
  os << Form("sector %2i Rho = %10.3g +/- %10.3g",v.sector, v.Rho, v.dRho);
  //  os << Form("<drift> %8.3f step %8.3f ", v.DriftZ, v.step);
  os << Form(" step %8.3f", v.step) << std::endl;
  for (Int_t i = 0; i < 6; i++) {
    if      (i == 0) os << "xG:\t";
    else if (i == 3) os << " nG:\t";
    os << Form(" %8.3f",v.xyzG()[i]);
  }
  os << std::endl;
  for (Int_t i = 0; i < 6; i++) {
    if      (i == 0) os << "xTpc:\t";
    else if (i == 3) os << " nTpc:\t";
    os << Form(" %8.3f",v.xyzTpc()[i]);
  }
  os << std::endl;
  for (Int_t i = 0; i < 6; i++) {
    if      (i == 0) os << "xHalf:\t";
    else if (i == 3) os << " nHalf:\t";
    os << Form(" %8.3f",v.xyzHalf()[i]);
  }
  os << std::endl;
  for (Int_t i = 0; i < 6; i++) {
    if      (i == 0) os << "xPad:\t";
    else if (i == 3) os << " nPad:\t";
    os << Form(" %8.3f",v.xyzPad()[i]);
  }
  os << std::endl;
  for (Int_t i = 0; i < 6; i++) {
    if      (i == 0) os << "xPadGG:\t";
    else if (i == 3) os << " nPadGG:\t";
    os << Form(" %8.3f",v.xyzPadGG()[i]);
  }
  os << std::endl;
  for (Int_t i = 0; i < 6; i++) {
    if      (i == 0) os << "x:\t";
    else if (i == 3) os << " n:\t";
    Int_t ii = TRSymMatrix::IJ(i,i);
    Double_t err = -13;
    if (v.fCov[ii] >= 0) err = TMath::Sqrt(v.fCov[ii]);
    os << Form(" %8.3f +/- %8.3f", v.xyz()[i], err);
  }
  os << std::endl;
  if (HelixPar_t::_debug) {
    TRSymMatrix C(6,v.fCov);
    TRSymMatrix cor(C,TRArray::kSCor);
    os << "Correlations: " << cor << std::endl;
    os << "\tPoints = " << v.Npoints << "\tused = " << v.Nused << "\tchi2/Ndf = " << v.Chi2 << "/" << v.Ndf;
  }
  return os;
}
//_____________________________________________________________________________
HelixPar_t &HelixPar_t::operator-=(const HelixPar_t &v) {
  for (Int_t i = 0; i < 6; i++) xyzG()[i] -= v.xyzG()[i];
  for (Int_t i = 0; i < 6; i++) xyzTpc()[i] -= v.xyzTpc()[i];
  for (Int_t i = 0; i < 6; i++) xyzHalf()[i] -= v.xyzHalf()[i];
  for (Int_t i = 0; i < 6; i++) xyzPad()[i] -= v.xyzPad()[i];
  for (Int_t i = 0; i < 6; i++) xyzPadGG()[i] -= v.xyzPadGG()[i];
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
  v.fRG.GetXYZ(xyzG());
  v.fNG.GetXYZ(pxyzG());
  v.fRTpc.GetXYZ(xyzTpc());
  v.fNTpc.GetXYZ(pxyzTpc());
  v.fRHalf.GetXYZ(xyzHalf());
  v.fNHalf.GetXYZ(pxyzHalf());
  v.fRPad.GetXYZ(xyzPad());
  v.fNPad.GetXYZ(pxyzPad());
  v.fRPadGG.GetXYZ(xyzPadGG());
  v.fNPadGG.GetXYZ(pxyzPadGG());
  if (v.fCov.GetSize()) memcpy(fCov, v.fCov.GetArray(), v.fCov.GetSize()*sizeof(Double_t));
  yRef = v.fyRef;
  return *this;
}
//_____________________________________________________________________________
void HelixPar_t::Print(Option_t *opt) const {
  std::cout << *this << std::endl;
}
