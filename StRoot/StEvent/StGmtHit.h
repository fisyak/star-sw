#ifndef StGmtHit_hh
#define StGmtHit_hh
/**
 * \class StGmtHit
 * \brief Holds data for the hit in GMT
 * 
 * Data for an individual ``hit'' in GMT, i.e. a 1D cluster (based on StFgtHit).
 *
 * \author K.S. Engle, Jan. 2013
 * \author Richard Witt (witt@usna.edu), Jan. 2013
 * \author Grigory Nigmatkulov (nigmatkulov@gmail.com), Dec. 2020
 */

#include "StHit.h"
#include "StGmtStrip.h"

class StGmtHit : public StHit {
public:
    // constructors
 StGmtHit( Int_t id  = -1, Int_t module = -1, Int_t iXY = 0,
	   Float_t adc = 0, Float_t dadc = 0, 
	   Float_t local = 0, Float_t localErr = 10000, 
	   Float_t sigma = 0, Float_t sigmaErr = 10000) :
  StHit( StThreeVectorF(local,sigma, adc),
	 StThreeVectorF(localErr, sigmaErr, dadc), 2*(module+1) + iXY, 0., 0, 0, 0, id) {}
    virtual ~StGmtHit() {}
    virtual StDetectorId detector() const 		{return kGmtId;};   
    // accessors/modifiers for the map
    // modifer
    // other accessors
    Int_t   getModule()     const {return (hardwarePosition() - 1)/2; }
    Int_t   getXorY()       const {return (hardwarePosition() - 1)%2; }
    Float_t getLocal()      const {return position().x();}
    Float_t getErrorLocal() const {return positionError().x();}
    Float_t getSigma()      const {return position().y();}
    Float_t getErrorSigma() const {return positionError().y();}
    Float_t getAdc()        const {return position().z();}
    Float_t getErrorAdc()   const {return positionError().z();}
    Int_t   volumeID() const {return 0;}
    void Print(Option_t *option="") const;
private:   
    ClassDef(StGmtHit,2)
}; 
ostream&   operator<<(ostream& os, StGmtHit const & v);
#endif // #define StGmtHit_hh
