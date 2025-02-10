/**
 * \class StGmtHit
 * \brief Holds data for the hit in GMT
 * 
 * Data for an individual ``hit'' in GMT, i.e. a 1D cluster (based on StFgtHit).
 *
 * \author K.S. Engle, Jan. 2013
 * \author Richard Witt (witt@usna.edu), Jan. 2013
 * \author Grigory Nigmatkulov (nigmatkulov@gmail.com), Dec. 2020
 */


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
