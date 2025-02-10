/**
 * \class StGmtCollection
 * \brief Holds collections of GMT points
 * 
 * Collection of GMT points for StEvent. Basically a wrapper 
 * for an StSPtrVecGmtPoint (based on StFgtPointCollection)
 *
 * \author K.S. Engle, Jan. 2013
 * \author Richard Witt (witt@usna.edu), Jan. 2013
 * \author Grigory Nigmatkulov (nigmatkulov@gmail.com), Dec. 2020
 */

#ifndef StGmtPointCollection_hh
#define StGmtPointCollection_hh

#include "StObject.h"
#include "StContainers.h"

class StGmtPoint;

class StGmtPointCollection : public StObject {
 public:
 StGmtPointCollection() : StObject() {}
  virtual  ~StGmtPointCollection() {}
  StSPtrVecGmtPoint&       getPointVec()        {   return mPointVec;}
  const StSPtrVecGmtPoint& getPointVec()  const {   return mPointVec;}
  size_t                   getNumPoints() const {   return mPointVec.size();}
  void Clear( Option_t *opt = "" )              {   mPointVec.clear();}
protected:
    StSPtrVecGmtPoint mPointVec;
    ClassDef(StGmtPointCollection,1)
}; 
#endif /* StGmtPointCollection_hh */

