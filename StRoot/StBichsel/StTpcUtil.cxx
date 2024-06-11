#include "StTpcUtil.h"
#include "TCallf77.h"
#ifndef WIN32
#define DerIO derio_
#define DerW2S derw2s_
#else
#define DerIO DERIO
#define DerW2S DERW2S
#endif
extern "C" {
  void type_of_call DerIO(const Double_t xyz[3], const Double_t nxyz[3], const Double_t xyzO[3], const Double_t parO[6], const Double_t parWheel[6], 
			  Double_t Der[4][4]);
  void type_of_call DerW2S(const Double_t xyzW[3], const Double_t nxyzW[3], const Double_t xyzS[3], const Double_t rw2s[9],  const Double_t tw2s[3],
			   Double_t Der[5][12]);
};
void StTpcUtil::IODer(const Double_t xyz[3], const Double_t nxyz[3], const Double_t xyzO[3], const Double_t parO[6], const Double_t parWheel[6], 
		      Double_t Der[4][4]) {
  DerIO(xyz, nxyz, xyzO, parO, parWheel, Der);
}

void StTpcUtil::W2SDer(const Double_t xyzW[3], const Double_t nxyzW[3], const Double_t xyzS[3], const Double_t rw2s[9], const Double_t tw2s[3],
		       Double_t Der[5][12]) {
  DerW2S(xyzW, nxyzW, xyzS, rw2s, tw2s, Der);
}

