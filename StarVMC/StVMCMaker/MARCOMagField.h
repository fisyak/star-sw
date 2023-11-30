#ifndef MARCOMagField_H
#define MARCOMagField_H
#include "TH2.h"
#include "TVirtualMagField.h"
class MARCOMagField : public TVirtualMagField {
 public:
  virtual ~MARCOMagField () { 
    fgInstance = 0; 
    SafeDelete(fBr);
    SafeDelete(fBz);
  }
  virtual void    Field    ( const Double_t *x, Double_t *B );
  static MARCOMagField *Instance();
 private:
  MARCOMagField ();
  static MARCOMagField *fgInstance;
  TH2F *fBr, *fBz;
  ClassDef(MARCOMagField,1)    // Base class for all MARCO MagField
};

#endif
