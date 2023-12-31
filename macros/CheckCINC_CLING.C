#include "Riostream.h"
void CheckCINT_CLING() {
#ifdef __CINT__
  cout << "__CINT__ has defined" << endl;
#endif  
#ifdef __MAKECINT__
  cout << "__MAKECINT__ has defined" << endl;
#endif  
#ifdef __CLING__
  cout << "__CLING__ has defined" << endl;
#endif  
#ifdef __ROOTCLING__
  cout << "__ROOTCLING__ has defined" << endl;
#endif  

}
		       
