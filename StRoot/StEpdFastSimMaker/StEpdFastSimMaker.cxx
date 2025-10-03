#include "StEpdFastSimMaker.h"
#include "Stiostream.h"

#include "StEvent/StEvent.h"
#include "StEvent/StEpdHit.h"
#include "StEvent/StEpdCollection.h"

//#include "StEventTypes.h"
//#include "StEventHitIter.h"

#include "StTimer.hh"
#include "StMemoryInfo.hh"
#include "St_DataSet.h"
#include "St_DataSetIter.h"

#include "tables/St_g2t_event_Table.h"
#include "tables/St_g2t_ctf_hit_Table.h"

ClassImp(StEpdFastSimMaker);

StEpdFastSimMaker::StEpdFastSimMaker(const char *name):StMaker(name) {
}

Int_t StEpdFastSimMaker::Init() {
  return kStOK;
}

Int_t StEpdFastSimMaker::Finish() {
  return kStOK;
}


int StEpdFastSimMaker::Make() {


  // Get the input data structures from StEvent
  
  StEvent *stEvent =  (StEvent*) GetInputDS("StEvent");
  if (! stEvent) {    LOG_WARN << "No StEvent on input, bye bye" << endm; return kStWarn; }
  StEpdCollection* epdCol = stEvent->epdCollection();


  if (!epdCol) {
  //  cout << " No epdCol found " <<endl;
  epdCol = new StEpdCollection;
  stEvent->setEpdCollection(epdCol);
  //  return kStWarn;
  }

  TDataSetIter geant(GetInputDS("geant"));
  St_g2t_ctf_hit *g2tEpdHit = (St_g2t_ctf_hit*) geant("g2t_epd_hit");


  if (! g2tEpdHit) {
    LOG_WARN << "No g2t_epd_hit on input, bye bye" << endm; return kStWarn;
    return kStWarn;
  }

  g2t_ctf_hit_st *g2t_epd         = g2tEpdHit->GetTable();
  int Nhits = g2tEpdHit->GetNRows();
  if (Nhits <= 0) return kStWarn;
  for (int i = 0; i < Nhits; i++){
    g2t_ctf_hit_st *tb =  g2t_epd+i;

    int volume_id = tb->volume_id;
    int ew        = volume_id/100000;
    ew = 2*ew -3;
    int pp        = (volume_id%100000)/1000;
    int tile      = (volume_id%1000)/10;
    //    int io        = (volume_id%10); // Inner or outer part of the tile, not used in real data, only for simulation data
    float de      = tb->de;
    int adc       = de*50*1e3; // Multiply by  1e6
    //int adc       = (int)de*1e6; // Convert elos to ADC (* 50) and MeV to eV * 1e6


    cout <<"volume_id  "<< ew<<"   "<<pp<<"  "<<tile<<"	"<<de<<"  "<<adc<<endl;

    int tac = 0;
    int tdc = 0;
    int hasTAC = 0;
    int nMIP = 0;
    int isGood = 1;
    int truthId = tb->track_p;

    StEpdHit* hit = new StEpdHit(pp,tile,ew,adc,tac,tdc,hasTAC,nMIP,isGood,truthId);
    epdCol->addHit(hit);

  }
  Info("Make","%d EpdHits was pushed into StEvent",Nhits);

  return kStOK;
}
