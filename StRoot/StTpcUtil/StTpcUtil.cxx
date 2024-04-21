#include "StTpcUtil.h"
#include "TCallf77.h"
#ifndef WIN32
#define DerIO derio_
#else
#define DerIO DERIO
#endif
extern "C" {
  void type_of_call DerIO(const Double_t xyz[3], const Double_t nxyz[3], const Double_t parO[6], const Double_t parWheel[6], Double_t Der[6][6]);
};
void StTpcUtil::IODer(const Double_t xyz[3], const Double_t nxyz[3], const Double_t parO[6], const Double_t parWheel[6], Double_t Der[6][6]) {
  DerIO(xyz, nxyz, parO, parWheel, Der);
}

