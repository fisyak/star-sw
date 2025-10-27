// Interface to Degrade

#ifndef G_DEGRADE_INTERFACE
#define G_DEGRADE_INTERFACE

#include <cstdint>

#ifndef __CINT__

namespace Garfield {

namespace Degrade {

extern "C" {

void deginit(int64_t* ng, int64_t* nevt, int64_t* mip, int64_t* idvec,
             int32_t* iseed, double* e0, double* et, double* ec, int64_t* ngas1,
             int64_t* ngas2, int64_t* ngas3, int64_t* ngas4, int64_t* ngas5,
             int64_t* ngas6, double* frac1, double* frac2, double* frac3,
             double* frac4, double* frac5, double* frac6, double* t0,
             double* p0, double* etot, double* btot, double* bang,
             int64_t* jcmp, int64_t* jray, int64_t* jpap, int64_t* jbrm,
             int64_t* jecasc, int64_t* iverb);
void getdedx(double* dedxi, double* cldensi);
int64_t getie(double* e);
double gettcf(int64_t* ie);
double gettcfn(int64_t* ie);
void getlevel(int64_t* ie, double* r1, int64_t* izbr, double* rgas, double* ein,
              int64_t* ia, double* wpl, int64_t* index, double* an, double* ps,
              double* wklm, int64_t* nc0, double* ec0, int64_t* ng1,
              double* eg1, int64_t* ng2, double* eg2, double* dstfl,
              int64_t* jpn, int64_t* kg1, int64_t* lg1, int64_t* igshel,
              int64_t* ionmdl, int64_t* ilvl);
int64_t getgas(int64_t* ilvl);
double ionpot();
void getebrem(int64_t* k, double* ee, double* xe, double* ye, double* ze,
              double* te, double* dxe, double* dye, double* dze, int64_t* iok);
void getecasc(int64_t* k, double* ee, double* xe, double* ye, double* ze,
              double* te, double* dxe, double* dye, double* dze, int64_t* iok);
void degrade();
void brems(int64_t* iz, double* ein, double* dx, double* dy, double* dz,
           double* eout, double* dxe, double* dye, double* dze, double* egamma,
           double* dxg, double* dyg, double* dzg);
void bremscasc(int64_t* j11, double* egamma, double* x0, double* y0, double* z0,
               double* t0, double* gdcx, double* gdcy, double* gdcz,
               int64_t* ilow);
void cascadee(int64_t* j11, int64_t* kgas, int64_t* lgas, double* x0,
              double* y0, double* z0, double* t0, double* einit,
              int64_t* ishell);
void drcos(double* drx, double* dry, double* drz, double* theta, double* phi,
           double* drxx, double* dryy, double* drzz);
void ionsplit(int64_t* i, double* e, double* ei, double* esec);
}
}  // namespace Degrade
}  // namespace Garfield
#endif
#endif
