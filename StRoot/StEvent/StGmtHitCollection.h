#ifndef StGmtHitCollection_hh
#define StGmtHitCollection_hh
/**
 * \class StGmtHitCollection
 * \brief Holds collection of GMT hits in the module
 * 
 * A collection of StGmtHit classes for StEvent.
 * Basically a wrapper for an StSPtrVecGmtHit. Note, one instance of
 * this class corresponds to one module.
 *
 * \author K.S. Engle, Jan. 2013
 * \author Richard Witt (witt@usna.edu), Jan. 2013
 * \author Grigory Nigmatkulov (nigmatkulov@gmail.com), Dec. 2020
 */

#include "StObject.h"
#include "StContainers.h"

class StGmtHit;

class StGmtHitCollection : public StObject {
public:
  StGmtHitCollection( short moduleId = -1) : mModule( moduleId ) {}
  virtual ~StGmtHitCollection() {}
  StSPtrVecGmtHit&      getHitVec()        {   return *&mHitVec;}
  const StSPtrVecGmtHit& getHitVec() const {   return *&mHitVec;}
  void setModule( short moduleId )         {   mModule = moduleId;}
  Short_t getModule() const                {   return mModule;}
  size_t getNumHits() const                {   return mHitVec.size();}
  void Clear( Option_t *opt = "" );
 protected:
  // the data member
  Short_t mModule;
  StSPtrVecGmtHit mHitVec;
  ClassDef(StGmtHitCollection,1)
}; 
#endif /* StGmtHitCollection_hhStGmtHitCollection_hh */
