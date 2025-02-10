#ifndef StGmtStripCollection_hh
#define StGmtStripCollection_hh
/**
 * \class StGmtCollection
 * \brief Holds collections of GMT strips
 * 
 * Collection of GMT strips for StEvent. Basically a wrapper 
 * for an StSPtrVecGmtStrip (based on StFgtStripCollection)
 *
 * \author K.S. Engle, Jan. 2013
 * \author Richard Witt (witt@usna.edu), Jan. 2013
 * \author Grigory Nigmatkulov (nigmatkulov@gmail.com), Dec. 2020
 */
#include "StObject.h"
#include "StContainers.h"
#include "StGmtStrip.h"

using namespace std;

class StGmtStripCollection : public StObject {
public:
    // constructors
    StGmtStripCollection( short module = 0 );
    // StGmtStripCollection( const StGmtStripCollection& other );            ---> use default
    // StGmtStripCollection& operator=( const StGmtStripCollection& other ); ---> use default 
    
    // deconstructor
    ~StGmtStripCollection();
    
    // accessors for the underlying vector.  WARNING: never use
    // getStripVec().push_back() or equivelants. Instead use
    // StGmtStripCollection::getStrip to add a new strip.
    StSPtrVecGmtStrip& getStripVec();
    const StSPtrVecGmtStrip& getStripVec() const;
    
    // sort internal vector by geoId
    void sortByGeoId();

    // sort internal vector by coordinate number
    void sortByCoord();
    // sort internal vector by coordinate number
    void partialSortByCoord();

    // sort internal vector by layer (X first then Y)
    void sortByLayer();

    // remove all hits with negative geoIds
    void removeFlagged();
    
    // size of internal vector
    size_t getNumStrips() const;
    
    // modify/access the moduleId
    short getModule() const;
    void setModule( short module );
    
    // Clear
    void Clear( Option_t *opt = "" );
    
    // Get pointer to a strip -- note: this is the only way to modify a
    // strip.  New strip is created if it does not exist, but only
    // using StGmtStrip() constructor.  Ownership is retained by the
    // collection.
//     StGmtStrip* getStrip( int elecId );
    StGmtStrip* getStrip( int Id );
    StGmtStrip* getSortedStrip( int Id );
    void     Print(Option_t *option="") const;
    
protected:  
    // function used for sorting strips by geoId
    static bool hitGeoIdLessThan( const StGmtStrip* h1, const StGmtStrip* h2 ); 
    // function used for sorting strips by coordinate number
    static bool hitCoordLessThan( const StGmtStrip* h1, const StGmtStrip* h2 ); 
    // function used for sorting strips by X then Y
    static bool hitLayerLessThan( const StGmtStrip* h1, const StGmtStrip* h2 ); 
     
protected:
    // the data members
    Short_t mModule;
    StSPtrVecGmtStrip mStripVec;    
    
    // temporary copy of the pointers, indexed by elec Id.
    // used for the addStripInfo class
    StPtrVecGmtStrip mStripElecIdVec; 
    StPtrVecGmtStrip mStripGeoIdVec; 
    
private:   
    ClassDef(StGmtStripCollection,1)
}; 
ostream&              operator<<(ostream& os, StGmtStripCollection const & v);


// inline functions

// inline StGmtStripCollection::StGmtStripCollection( short module ) : StObject(), mModule( module ) {
//     mStripElecIdVec.resize( kGmtNumElecIds );
//     for (unsigned int i=0; i<mStripElecIdVec.size(); i++)
//         mStripElecIdVec[i] = static_cast< StGmtStrip* >(0);
// };

inline StGmtStripCollection::StGmtStripCollection( short module ) : StObject(), mModule( module ) {
    mStripGeoIdVec.resize( kGmtNumGeoIds );
    for (unsigned int i=0; i<mStripGeoIdVec.size(); i++)
        mStripGeoIdVec[i] = static_cast< StGmtStrip* >(0);
};

// inline StGmtStripCollection::StGmtStripCollection( short module ) : StObject(), mModule( module ) {
//     mStripVec.resize( kGmtNumGeoIds );
//     for (unsigned int i=0; i<mStripVec.size(); i++)
//         mStripVec[i] = static_cast< StGmtStrip* >(0);
// };

inline StSPtrVecGmtStrip& StGmtStripCollection::getStripVec() {
    return mStripVec;
};

inline const StSPtrVecGmtStrip& StGmtStripCollection::getStripVec() const{
    return mStripVec;
};

// sort by geoId
inline void StGmtStripCollection::sortByGeoId(){
    sort( mStripVec.begin(), mStripVec.end(), &StGmtStripCollection::hitGeoIdLessThan );
    return;
};

// sort by layer (X first then Y)
inline void StGmtStripCollection::sortByLayer(){
    sort( mStripVec.begin(), mStripVec.end(), &StGmtStripCollection::hitLayerLessThan );
    return;
};

// sort by coordinate number
inline void StGmtStripCollection::partialSortByCoord(){
    partial_sort( mStripVec.begin(), mStripVec.begin()+kGmtNumStrips, mStripVec.begin()+kGmtNumStrips, &StGmtStripCollection::hitCoordLessThan );
    return;
};

// sort by coordinate number
inline void StGmtStripCollection::sortByCoord(){
    sort( mStripVec.begin(), mStripVec.end(), &StGmtStripCollection::hitCoordLessThan );
    return;
};

#endif /* StGmtStripCollection_hh */
