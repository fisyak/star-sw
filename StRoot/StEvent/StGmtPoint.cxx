#include "StGmtPoint.h"
#include "TRVector.h"
//________________________________________________________________________________
void StGmtPoint::SetId(Int_t B, Int_t L, Int_t l, Int_t W, Int_t H) {
  barrel = B; layer = L; ladder = l; wafer = W; hybrid = H;
}
//________________________________________________________________________________
void StGmtPoint::Print(Option_t *opt) const {
  cout << "StGmtPoint: Id " << Id << "\tpT = " << pT << "\tmomentum " << pMom << endl;
  TRVector glob(3,&xG); cout << "Global :" << glob << endl;
  cout << "Local      u/v/w " << u << "/ " << v << "/ " << w << endl;
  cout << "Prediction uP/vP " << uP << "/ " << vP << "\ttuP/tvP " << tuP << "/ " << tvP << endl;
}
