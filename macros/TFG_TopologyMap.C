#include "Rtypes.h"
#include "Riostream.h"
UInt_t fgMap[3] = {0};
//________________________________________________________________________________
Bool_t bit(int i)
{
  if (i <= 31) return (fgMap[0]>>i & 1U);
  if (i <= 63) return (fgMap[1]>>(i-32) & 1U);
  return (fgMap[2]>>(i-64) & 1U);
}
//________________________________________________________________________________
void TFG_TopologyMap(UInt_t map0 = 0, UInt_t map1 = 0, UInt_t map2 = 0) {
  //  if (! fgMap) fgMap = new UInt[3];
  fgMap[0] = map0;
  fgMap[1] = map1;
  fgMap[2] = map2;
}
//________________________________________________________________________________
Bool_t hasHitInRow(Int_t row) {
  if (row <= 45) return bit(row+7);
  return  bit(row+64-46);
}
//________________________________________________________________________________
void PrintMap(UInt_t map0 = 0, UInt_t map1 = 0, UInt_t map2 = 0) {
  TFG_TopologyMap(map0,map1,map2);
  for (Int_t row = 1; row <= 72; row++) {
    if (hasHitInRow(row)) cout << "has hit in " << row << " row" << endl;
  }
}
