#ifndef __Tracklet__h
#define __Tracklet__h
#include "StThreeVectorD.hh"
class Tracklet : public TObject {
public:
  Tracklet() {Clear();}
  virtual ~Tracklet() {}
  Char_t         beg[1]; // !
  Int_t          run;
  Int_t          sector;
  Int_t          row;
  Int_t          nhits;
  Double_t       AdcSum;
  Double_t       x0, tX, y0, tY, z0; // in Tpc Sector
  Double_t       x0T, tXT, y0T, tYT, z0T; // in Tpc coordinate system
  Double_t       tXG, tYG; // in Global  coordinate system
  Char_t         end[1]; // !
  StThreeVectorD BG;
  StThreeVectorD BL;
  StThreeVectorD BT;
  StThreeVectorD posG;
  StThreeVectorD posL;
  StThreeVectorD dirL;
  StThreeVectorD posT;
  StThreeVectorD dirT;
  StThreeVectorD dirG;
  StThreeVectorD dirST;
  StThreeVectorD posRMSG;
  StThreeVectorD posRMSL;
  StThreeVectorD posRMST;
  void           Clear(Option_t *opt = 0) {
    //    if (opt); 
    memset(beg, 0, end-beg); 
    BG = BL = posG = posL = posT = posRMSG = posRMSL = posRMST = dirL = dirT = StThreeVectorD();
  }
  ClassDef(Tracklet,1)
};
#endif /* __Tracklet__h */
