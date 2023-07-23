#include "StiNodePars.h"
#include "Riostream.h"
#include "TString.h"
std::ostream&  operator<<(std::ostream& os, StiNodePars const & pars) {
  static const Char_t *vn[8] = {"x","y","z","Phi","pTin","Tan","Curv","Hz"};
  os << Form("pars: _cosCA = %8.3f, _sinCA = %8.3f", pars._cosCA, pars._sinCA);
  for (Int_t i = 0; i < 8; i++) {
    os << Form(" %s:%8.3f", vn[i], pars.P[i]);
  }
  return os;
}













