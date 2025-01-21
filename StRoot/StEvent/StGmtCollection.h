/***************************************************************************
 *
 * Authors: K.S. Engle and Richard Witt (witt@usna.edu), Jan 2013
 * based on StFgtCollection
 *
 ***************************************************************************
 *
 * Description: GMT data collection for StEvent.
 *
 ***************************************************************************/

#ifndef _ST_GMT_COLLECTION_H_
#define _ST_GMT_COLLECTION_H_

#include "StObject.h"
#include "StGmtStripCollection.h"
#include "StGmtHitCollection.h"
#include "StGmtPointCollection.h"
#include "StEnumerations.h"

class StGmtCollection: public StObject  {
 public:
  StGmtCollection();
  virtual ~StGmtCollection() {}
    
  size_t getNumModules() const                                                     {    return kGmtNumModules;}
  size_t getNumStrips() const {// sum of all the strips over all modules
    size_t n = 0;
    for( const StGmtStripCollection* ptr = &mStripCollection[0]; ptr != &mStripCollection[kGmtNumModules]; ++ptr )
      n += ptr->getNumStrips();
    return n;
  }
  size_t getNumStrips( unsigned short moduleIdx ) const                            {    return (moduleIdx < kGmtNumModules ? mStripCollection[moduleIdx].getNumStrips() : 0 );}
  size_t getNumHits() const {// sum of all the hits over all modules
    size_t n = 0;
    for( const StGmtHitCollection* ptr = &mHitCollection[0]; ptr != &mHitCollection[kGmtNumModules]; ++ptr )
      n += ptr->getNumHits();
    return n;
  }
  size_t getNumHits( unsigned short moduleIdx ) const                              {    return (moduleIdx < kGmtNumModules ? mHitCollection[moduleIdx].getNumHits() : 0 );}
  size_t getNumPoints() const                                                      {    return mPointCollection.getNumPoints();}
  
  // note: ownership of all pointers is retained by the containers.
  // Do not deleted any pointers received from this class.
  
  StGmtStripCollection* getStripCollection( unsigned short moduleIdx )             {    return (moduleIdx < kGmtNumModules ? &mStripCollection[moduleIdx] : 0 );}
  const StGmtStripCollection* getStripCollection( unsigned short moduleIdx ) const {    return (moduleIdx < kGmtNumModules ? &mStripCollection[moduleIdx] : 0 );}
  
  StGmtHitCollection* getHitCollection( unsigned short moduleIdx )                 {    return (moduleIdx < kGmtNumModules ? &mHitCollection[moduleIdx] : 0 );}
  const StGmtHitCollection* getHitCollection( unsigned short moduleIdx ) const     {    return (moduleIdx < kGmtNumModules ? &mHitCollection[moduleIdx] : 0 );}
  
  StGmtPointCollection* getPointCollection()                                       {    return &mPointCollection;}
  const StGmtPointCollection* getPointCollection() const                           {    return &mPointCollection;}
  
  void Clear( Option_t *opts = "" );
  
 protected:
  StGmtStripCollection mStripCollection[kGmtNumModules];
  StGmtHitCollection   mHitCollection[kGmtNumModules];
  StGmtPointCollection mPointCollection;
  ClassDef(StGmtCollection,1)
}; 

#endif
