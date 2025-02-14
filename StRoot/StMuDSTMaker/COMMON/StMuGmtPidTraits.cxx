#include <string>
#include "StMuGmtPidTraits.h"
#include "StGmtPidTraits.h"

StMuGmtPidTraits::StMuGmtPidTraits(const StGmtPidTraits *gmtPidTrait) {
  memset(mBeg, 0, mEnd-mBeg+1);
  mModule = 255;
  if (gmtPidTrait) set(gmtPidTrait);
}
void StMuGmtPidTraits::set(const StGmtPidTraits *gmtPidTrait) {
  if (! gmtPidTrait) return;
  setId(gmtPidTrait->id());    
  setModule(gmtPidTrait->module());
  setYLocal(gmtPidTrait->yLocal());
  setZLocal(gmtPidTrait->zLocal());      
  setDeltaY(gmtPidTrait->deltaY());
  setDeltaZ(gmtPidTrait->deltaZ());
  setSigmaY(gmtPidTrait->sigmaY());
  setSigmaZ(gmtPidTrait->sigmaZ());
  setxG(gmtPidTrait->position().x());   
  setyG(gmtPidTrait->position().y());   
  setzG(gmtPidTrait->position().z());   
}
