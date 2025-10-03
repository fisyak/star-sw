#ifndef STAR_StEpdFastSimMaker
#define STAR_StEpdFastSimMaker

#include "StMaker.h"

class StEpdFastSimMaker : public StMaker {
  public: 
    StEpdFastSimMaker(const char* name="epdHitSim");
    ~StEpdFastSimMaker() {}
    Int_t  Init(); 
    Int_t  Make();
    Int_t  Finish();
    const char *GetCVS() const
    {static const char cvs[]="Tag $Name:" __DATE__ " " __TIME__ ; return cvs;}

  private:

    ClassDef(StEpdFastSimMaker,1)   // EpdFastSim
};

#endif


