/***************************************************************************
 *
 * Authors: K.S. Engle and Richard Witt (witt@usna.edu), Jan 2013
 * based on StFgtPointCollection
 *
 ***************************************************************************
 *
 * Description: A collection of StGmtPoint classes for StEvent.
 * Basically a wrapper for an StSPtrVecGmtPoint
 *
 ***************************************************************************/

#ifndef _ST_GMT_POINT_COLLECTION_H_
#define _ST_GMT_POINT_COLLECTION_H_

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
#endif

