/**
 * \class StGmtColection
 * \brief Holds collections of GMT data
 * 
 * GMT data collection for StEvent (based on StFgtCollection)
 *
 * \author K.S. Engle, Jan. 2013
 * \author Richard Witt (witt@usna.edu), Jan. 2013
 * \author Grigory Nigmatkulov (nigmatkulov@gmail.com), Dec. 2020
 */

// Load header of the GMT collection
#include "StGmtCollection.h"

//________________
StGmtCollection::StGmtCollection() : StObject() {
  // Set the module field for some of the collections
  for( int i=0; i<kGmtNumModules; ++i ) {
    mStripCollection[i].setModule( i );
    mHitCollection[i].setModule( i );
  }
}

//________________
void StGmtCollection::Clear( Option_t *opt ){
    for( int i=0; i<kGmtNumModules; ++i ){
        mStripCollection[i].Clear( opt );
        mHitCollection[i].Clear( opt );
    }
    mPointCollection.Clear( opt );
}
