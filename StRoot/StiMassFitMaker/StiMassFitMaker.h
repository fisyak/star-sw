#ifndef STAR_StiMassFitMaker
#define STAR_StiMassFitMaker

/*!
 *                                                                     
 * \class  StiMassFitMaker
 * \author fisyak
 * \date   2026/08/07
 * \brief  Add mass fit for Sti tracks
 */
#include "StMaker.h"
class StiMassFitMaker : public StMaker {
 public: 
 StiMassFitMaker(const Char_t *name="MassFit") : StMaker(name) {}
  virtual       ~StiMassFitMaker() {}
  virtual Int_t  Make();
  virtual const Char_t *GetCVS() const {
    static const Char_t cvs[]="Tag $Name:  $ $Id: StiMassFitMaker.h Exp $ built " __DATE__ " " __TIME__ ; 
    return cvs;
  }
  ClassDef(StiMassFitMaker,0) 
};

#endif
