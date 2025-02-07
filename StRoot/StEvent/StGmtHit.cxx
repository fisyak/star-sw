/***************************************************************************
 *
 * Authors: K.S. Engle and Richard Witt (witt@usna.edu), Jan 2013
 * based on StFgtHit
 *
 ***************************************************************************
 *
 * Description: see header file.
 *
 ***************************************************************************/

#include "StGmtHit.h"
#include <cmath>
ClassImp(StGmtHit)
//________________________________________________________________________________
ostream&  operator<<(ostream& os, const StGmtHit& v) {
  static const Char_t *XY[2] = {"X", "Y"};
  return os << Form("Gmt Id = %3i, module = %3i %s", v.id(), v.getModule(), XY[v.getXorY()]) 
	    << Form(" Adc %5.1f +/- %5.1f,   loc = %8.3f +/- %7.3f, sigma = %8.3f +/- %7.3f",
		    v.getAdc(), v.getErrorAdc(), v.getLocal(), v.getErrorLocal(), v.getSigma(), v.getErrorSigma()); 
}
//________________________________________________________________________________
void   StGmtHit::Print(Option_t *option) const {cout << *this << endl;}
//________________________________________________________________________________

