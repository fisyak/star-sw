#include "StGmtPoint.h"
#include "TRVector.h"
//________________________________________________________________________________
StGmtPoint::StGmtPoint(Int_t id  , Int_t module , Int_t trackId, 
		       Double32_t XG, Double32_t YG, Double32_t ZG,
		       Double32_t XL, Double32_t YL, Double32_t ZL, 
		       Float_t yD, Float_t sigmaY, Float_t AdcLy,
		       Float_t dyD, Float_t dsigmaY, Float_t dAdcLy,
		       Float_t zD, Float_t sigmaZ, Float_t AdcLz,
		       Float_t dzD, Float_t dsigmaZ, Float_t dAdcLz) :
  StHit( StThreeVectorF(XG, YG, ZG), StThreeVectorF(XL, YL, ZL), 2*(module+1), 0., 0, 0, 0, id), 
  mTrackId(trackId), 
  myD(yD), msigmaY(sigmaY), mAdcLy(AdcLy), mdyD(dyD), mdsigmaY(dsigmaY), mdAdcLy(dAdcLy),
  mzD(zD), msigmaZ(sigmaZ), mAdcLz(AdcLz), mdzD(dzD), mdsigmaZ(dsigmaZ), mdAdcLz(dAdcLz) 
{}
#if 1	 
StGmtPoint::StGmtPoint(StGmtHit &hitY, StGmtHit &hitZ, Int_t trackId, StThreeVectorF &global, StThreeVectorF &local) :
  StHit(global, local, 2*(hitY.getModule()+1), 0., 0, 0, 0, hitY.id() + 100*hitZ.id()),mTrackId(trackId)
{
  myD = hitY.getLocal(); msigmaY = hitY.getSigma(); mAdcLy = hitY.getAdc();  mdyD = hitY.getErrorLocal(); mdsigmaY = hitY.getErrorSigma(), mdAdcLy = hitY.getErrorAdc();
  mzD = hitZ.getLocal(); msigmaZ = hitZ.getSigma(); mAdcLz = hitZ.getAdc();  mdzD = hitZ.getErrorLocal(); mdsigmaZ = hitZ.getErrorSigma(), mdAdcLz = hitZ.getErrorAdc();
}
#endif
//________________________________________________________________________________
void StGmtPoint::setAssociatedTrack(StTrack* val)    { mAssociatedTrack = val; }
StTrack*        StGmtPoint::associatedTrack()        { return mAssociatedTrack; }
const StTrack*  StGmtPoint:: associatedTrack() const { return mAssociatedTrack; }
//________________________________________________________________________________
void StGmtPoint::Print(Option_t *opt) const {
  cout << "StGmtPoint: Id " << id() 
       << "Global prediction: :" << position() 
       << "Local  " << local() << endl;
}
