#include "StGmtPoint.h"
#include "TRVector.h"
//________________________________________________________________________________
void StGmtPoint::Print(Option_t *opt) const {
  cout << "StGmtPoint: Id " << id() 
       << "Global prediction: :" << position() 
       << "Local  " << local() << endl;
}
