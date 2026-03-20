/***************************************************************************
 *
 * $Id: StTpcPadrowHitCollection.cxx,v 2.3 2001/04/05 04:00:57 ullrich Exp $
 *
 * Author: Thomas Ullrich, July 1999
 ***************************************************************************
 *
 * Description:
 *
 ***************************************************************************
 *
 * $Log: StTpcPadrowHitCollection.cxx,v $
 * Revision 2.3  2001/04/05 04:00:57  ullrich
 * Replaced all (U)Long_t by (U)Int_t and all redundant ROOT typedefs.
 *
 * Revision 2.2  1999/11/11 21:19:38  ullrich
 * Delete hits explicitly in destructor
 *
 * Revision 2.1  1999/10/13 19:45:30  ullrich
 * Initial Revision
 *
 **************************************************************************/
#include "StTpcPadrowHitCollection.h"
#include "StTpcHit.h"

static const char rcsid[] = "$Id: StTpcPadrowHitCollection.cxx,v 2.3 2001/04/05 04:00:57 ullrich Exp $";

ClassImp(StTpcPadrowHitCollection)

StTpcPadrowHitCollection::StTpcPadrowHitCollection() { /* noop */ }

StTpcPadrowHitCollection::~StTpcPadrowHitCollection()
{
    //
    // Usually this wouldn't be necessary but mHits
    // is a polymorphic container and StTpcHit
    // provides its own new/delete operator.
    //
    for (unsigned int i=0; i<mHits.size(); i++) {
        delete mHits[i];
        mHits[i] = 0;
    }
}

const StSPtrVecTpcHit&
StTpcPadrowHitCollection::hits() const { return mHits; }

StSPtrVecTpcHit&
StTpcPadrowHitCollection::hits() { return mHits; }
//________________________________________________________________________________
ostream&  operator<<(ostream& os, const StTpcPadrowHitCollection& v)
{
  const  UInt_t NoHits = v.hits().size();
  for (UInt_t i = 0; i < NoHits; i++) {
    if (v.hits().at(i)) os << *v.hits().at(i) << endl;
  }
  return os;
}
//________________________________________________________________________________
void   StTpcPadrowHitCollection::Print(Option_t *option) const {cout << *this << endl;}
//________________________________________________________________________________
