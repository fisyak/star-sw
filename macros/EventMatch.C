#include "StBFChain/StBFChain.h"
#include "StIOMaker/StIOMaker.h"
#include "StEvent/StEvent.h"
//________________________________________________________________________________
Int_t EventMatch(StBFChain *chain, StIOMaker *IN1, StIOMaker *IN2) {
  StIOMaker *makers[2] = {IN1, IN2};
  StEvent   *events[2] = {0};
  Int_t iMake = chain->MakeEvent();
  if (iMake) return 1;;
  Int_t evNo[2] = {0};
  for (Int_t m = 0; m < 2; m++) {
    events[m] = (StEvent   *) makers[m]->GetDataSet("StEvent");
    if (! events[m]) continue;
    cout << "m = " << m << "\trun = " << events[m]->runId() << "\tevent = " <<  events[m]->id() << endl;
    //       ukey[m] = StUKey(events[m]->runId(), events[m]->id(), 2); 
    //       cout << "m = " << m << "\trun = " << events[m]->runId() << "\tevent = " <<  events[m]->id() << "\t" << ukey[m].GetName() << endl;
    evNo[m] = events[m]->id();
  }
  if (events[0]->runId() != events[1]->runId()) {
    cout << "Runs : " << events[0]->runId() << " and " << events[1]->runId() << " mismatched. Stop !" << endl;
    return 1;;
  }
  while (1) {
    for (Int_t m = 0; m < 2; m++) {
      while (! events[m]) {
	((StMaker *) makers[m])->Clear();
	iMake = makers[m]->Make();
	if (iMake%10 == kStEOF || iMake%10==kStFatal)	return 1;;
	events[m] = (StEvent   *) makers[m]->GetDataSet("StEvent");
	if ( events[m]) {
	  evNo[m] = events[m]->id();
	  break;
	}
      }
    }
    cout << "Event1 = " << evNo[0] << "\tEvent2 = " << evNo[1] << endl;
    if (evNo[0] == evNo[1]) break;
    if (evNo[0] <  evNo[1]) {
      events[0] = 0;
    } else {
      events[1] = 0;
    }
  }
  return 0;
}
