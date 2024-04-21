#ifndef __StTpcDer_h__
#define __StTpcDer_h__
#ifndef ROOT_Rtypes
#include "Rtypes.h"
#endif
namespace StTpcUtil {
  void IODer(const Double_t xyz[3], const Double_t nxyz[3], const Double_t parO[6], const Double_t parWheel[6], Double_t Der[6][6]);
}
#endif 
