// $Id: StEandBDirMaker.h,v 1.3 2013/08/26 16:51:59 fisyak Exp $

#ifndef STAR_StEandBDirMaker
#define STAR_StEandBDirMaker

/*!
 *                                                                     
 * \class  StEandBDirMaker
 * \author fisyak
 * \date   2013/08/14
 * \brief  Try to measure direction Electric and Magnetic Field using low energy elctrons
 *
 */                                                                      
#include "StMaker.h"
#include "Tracklet.h"
class StEandBDirMaker : public StMaker {
 private:
  // Private method declaration if any
  Tracklet *fTracklet;
 protected:
  // Protected method if any
 public: 
  StEandBDirMaker(const char *name="EandBDir") : StMaker(name){}
  virtual ~StEandBDirMaker() {}
  virtual Int_t Init();
  virtual Int_t Make();

  // virtual Int_t InitRun  (int runumber){return 0;}; // Overload empty StMaker::InitRun 
  // virtual Int_t FinishRun(int runumber){return 0;}; // Overload empty StMaker::FinishRun 

  // Displayed on session exit, leave it as-is please ...
  virtual const char *GetCVS() const {
    static const char cvs[]="Tag $Name:  $ $Id: StEandBDirMaker.h,v 1.3 2013/08/26 16:51:59 fisyak Exp $ built " __DATE__ " " __TIME__ ; 
    return cvs;
  }
  ClassDef(StEandBDirMaker,0)   //
};
#endif
// $Log: StEandBDirMaker.h,v $
// Revision 1.3  2013/08/26 16:51:59  fisyak
// Add rms
//
// Revision 1.2  2013/08/19 20:25:31  fisyak
// Add dirST
//
// Revision 1.1.1.1  2013/08/16 15:27:45  fisyak
// First version
//
