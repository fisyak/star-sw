#include "StarLogicalFilter.h"
#include "StarGenerator/EVENT/StarGenEvent.h"
#include "TString.h"

StarLogicalFilter::StarLogicalFilter( const char* name ) : StarFilterMaker(name) { }

int StarLogicalFilter::Filter( StarGenEvent* event ) {

  int result = StarGenEvent::kReject;
  TString operator_=SAttr("operator");

  if ( operator_=="AND" ) {
    // Logical AND requires ALL attached filters to accept the event.  Set
    // kAccept.  Loop over the filters and set kReject if any of them
    // rejected.
    result = StarGenEvent::kAccept;
    for ( auto* f : mFilters ) {
      if ( StarGenEvent::kReject == f->Filter(event) ) { 
	result = StarGenEvent::kReject;
	break; // we only need one to reject
      }
    }
  }
  else if ( operator_=="OR" ) {
    // Logical OR requires ANY attached filter to accept the event.  Set
    // kReject.  Loop over all filters and set kAccept if any of them
    // accepted.
    result = StarGenEvent::kReject;
    for ( auto* f : mFilters ) {
      if ( StarGenEvent::kAccept == f->Filter(event) ){
	result = StarGenEvent::kAccept;
	break; // we only need one to accept
      }
    }
  }
  else {

    // Unknown or unset operation.  Reject in the most brutal / kind way possible.
    LOG_FATAL << "Unknown Op: kReject.  Operation unset or invalid: " << operator_.Data() << endm;
    assert(0);
    result = StarGenEvent::kReject;
    
  }


  LOG_DEBUG << Form( "%s: result=%s", operator_.Data(), ( StarGenEvent::kAccept == result )? ": accept" : ": reject" ) << endm;

  return result;

}

void StarLogicalFilter::SetOperator( const char* op ){
  TString OP = op;
  OP.ToUpper();
  SetAttr("operator",OP.Data());
  if ( OP=="AND" || OP=="OR" ) {
    LOG_INFO << "Operation set to: " << OP.Data() << endm;
  }
  else {
    LOG_INFO << "Attempt to set invalid operation." << endm;
    assert(0);
  }
};
