#ifndef __StTpcDer_h__
#define __StTpcDer_h__
#ifndef ROOT_Rtypes
#include "Rtypes.h"
#endif
namespace StTpcUtil {
  void IODer(const Double_t xyz[3], const Double_t nxyz[3], const Double_t xyzO[3], const Double_t parO[6], const Double_t parWheel[6], 
	     Double_t Der[4][4]);
  void W2SDer(const Double_t xyzW[3], const Double_t nxyzW[3], const Double_t xyzS[3], const Double_t rw2s[9], const Double_t tw2s[3], 
	      Double_t W2ST[5][12]);
}
#endif 
