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

#include "StGmtCollection.h"

StGmtCollection::StGmtCollection() {
  for( int i=0; i<kGmtNumModules; ++i ){
    mStripCollection[i].setModule( i );
    mHitCollection[i].setModule( i );
  }
}

void StGmtCollection::Clear( Option_t *opt ){
    for( int i=0; i<kGmtNumModules; ++i ){
        mStripCollection[i].Clear( opt );
        mHitCollection[i].Clear( opt );
    }
    mPointCollection.Clear( opt );
}
