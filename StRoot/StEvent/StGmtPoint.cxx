/**
 * \class StGmtPoint
 * \brief Holds data for the point (a.k.a. cluster) in GMT
 * 
 * Description: data for individual ``point'' on the GMT, i.e. a pair
 * of 1D clusters.  Note, if errors during construction, the key will
 * be set to -999. Based on StFgtHit.
 *
 * \author K.S. Engle, Jan. 2013
 * \author Richard Witt (witt@usna.edu), Jan. 2013
 * \author Grigory Nigmatkulov (nigmatkulov@gmail.com), Dec. 2020
 */
#include "StGmtPoint.h"
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
//________________________________________________________________________________
StGmtPoint::StGmtPoint(StGmtHit &hitY, StGmtHit &hitZ, Int_t trackId, StThreeVectorF &global, StThreeVectorF &local) :
  StHit(global, local, 2*(hitY.getModule()+1), 0., 0, 0, 0, hitY.id() + 100*hitZ.id()),mTrackId(trackId)
{
  myD = hitY.getLocal(); msigmaY = hitY.getSigma(); mAdcLy = hitY.getAdc();  mdyD = hitY.getErrorLocal(); mdsigmaY = hitY.getErrorSigma(), mdAdcLy = hitY.getErrorAdc();
  mzD = hitZ.getLocal(); msigmaZ = hitZ.getSigma(); mAdcLz = hitZ.getAdc();  mdzD = hitZ.getErrorLocal(); mdsigmaZ = hitZ.getErrorSigma(), mdAdcLz = hitZ.getErrorAdc();
}
//________________________________________________________________________________
void StGmtPoint::setAssociatedTrack(StTrack* val)    { mAssociatedTrack = val; }
StTrack*        StGmtPoint::associatedTrack()        { return mAssociatedTrack; }
const StTrack*  StGmtPoint:: associatedTrack() const { return mAssociatedTrack; }
//________________________________________________________________________________
void StGmtPoint::Print(Option_t *opt) const {
  cout << "StGmtPoint: Id X(yL) " << id()%100 << " Y(zL) " << id()/100 
       << "\tPrediction Global: " << position() 
       << "\tLocal:  " << local();
  const StTrack *Track = associatedTrack();
  if ( Track) {
    cout << "\tAssociated track: " << Track->key();
    if      (Track->type() == global)  cout << " global ";
    else if (Track->type() == primary) cout << " primary";
    cout << "\tdY = " << yD() - local().y() << " +/- " << dyD();
    cout << "\tdZ = " << zD() - local().z() << " +/- " << dzD();
  }
  cout << endl;
}
