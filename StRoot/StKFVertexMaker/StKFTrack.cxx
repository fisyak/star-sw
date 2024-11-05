// $Id: StKFTrack.cxx,v 2.3 2015/12/20 01:06:39 fisyak Exp $
#include "Riostream.h"
#include "StKFTrack.h"
using namespace std;
Int_t StKFTrack::fDebug = 0;
//________________________________________________________________________________
StKFTrack::StKFTrack(const KFParticle *particle, Double_t chi2, Int_t iWE) : 
  fWeight(-1), fW(-1), fOrigKFParticle(particle), fWestOrEast(iWE) {
  if (particle) {
    fParticle = KFParticle(*particle);
    SetChi2(chi2);
  }
}
//________________________________________________________________________________
StKFTrack::StKFTrack(const StKFTrack &track) : 
  fWeight(track.Weight()), fW(track.W()), fChi2(track.Chi2()), fParticle(track.Particle()), 
  fOrigKFParticle(track.OrigParticle()), fWestOrEast(track.WestOrEast()) {}
//________________________________________________________________________________
void StKFTrack::SetChi2(Double_t chi2) {
  fChi2 = chi2;
  if (fChi2 >= 0) {
    fWeight = StAnneling::Weight(fChi2);
  } else {
    fWeight = -1;
  }
}
//________________________________________________________________________________
Int_t StKFTrack::CorrectGePid(Int_t gePid) {
  // By pass embedding particle redefinition
  if (gePid ==           99) gePid =         11151;
  if (gePid ==          207) gePid =            41;
  if (gePid ==        40001) gePid =            24;
  if (gePid ==           98) gePid =            18;
  if (gePid ==        40002) gePid =            32;
  if (gePid ==           97) gePid =            26;
  if (gePid ==        40003) gePid =            23;
  if (gePid ==        40004) gePid =            31;
  if (gePid ==        40005) gePid =            22;
  if (gePid ==        40006) gePid =            30;
  if (gePid ==        10150) gePid =           150;
  if (gePid ==        10151) gePid =           151;
  if (gePid ==        11151) gePid =         10151;
  if (gePid ==        10018) gePid =            98;
  if (gePid ==        10026) gePid =            97;
  if (gePid ==        10017) gePid =            17;
  if (gePid ==        10039) gePid =            39;
  if (gePid ==        10040) gePid =            40;
  if (gePid ==           98) gePid =            18;
  if (gePid ==           97) gePid =            26;
  if (gePid < 0 || gePid > 50) {
    std::cout << "Illegal gePid " << gePid << std::endl;
  }
  if (gePid < 0 || gePid > 50) gePid = 51;
  return gePid;
}
//________________________________________________________________________________
void StKFTrack::NormW(Double_t Norm) {
  if (OrigParticle()->Id() > 0 || Norm > 0.0) {
    fW = fWeight/Norm;
  } else {
    fW = 1;
  }
}
//________________________________________________________________________________
void StKFTrack::ResetParticle() {
  fParticle = *fOrigKFParticle;
  if (fW <= 0.0 || fWeight <= 0) return;
#if 1
  Double_t T = StAnneling::Temperature();
  Float_t scale = T;
#if 0
  if (T > 1.0) {
    if (fW > 100*T)  scale = T/fW;
    if (fWeight > 0) scale /= fWeight;
  }
#endif
  if (fDebug) {
    cout << "StKFTrack::ResetParticle: T = " << T << " fW = " << fW << " fWeight = " << fWeight << " scale " << scale << endl;
    fParticle.Print("");
  }
  Float_t *CovXyz  = &fParticle.Covariance(0);
  //  for (Int_t j = 0; j < 21; j++) CovXyz[j] *= 1./fWeight;
  //  for (Int_t j = 0; j < 21; j++) CovXyz[j] *= 1./TMath::Sqrt(fW);
  //  for (Int_t j = 0; j < 21; j++) CovXyz[j] *= 1./(fW*fWeight);
  for (Int_t j = 0; j < 21; j++) CovXyz[j] *= scale;
  if (fDebug) { 
    fParticle.Print("");
 }
#endif
  return;
}
//________________________________________________________________________________
std::ostream&  operator<<(std::ostream& os,  const StKFTrack& p) {
  os << Form("%5i %9.3f %9.3f %9.3f %9.3f",
	     p.K(),p.Weight(),p.W(),p.Particle().GetZ(),p.Chi2())
     << ":" << *p.OrigParticle();
  return os;
}
// $Log: StKFTrack.cxx,v $
// Revision 2.3  2015/12/20 01:06:39  fisyak
// Merge
//
// Revision 2.3  2015/01/05 21:04:31  fisyak
// Add access to TMVA ranking
//
// Revision 2.2  2012/06/11 15:33:41  fisyak
// std namespace
//
// Revision 2.1  2012/05/07 14:56:14  fisyak
// Add StKFVertexMaker
//
// Revision 1.2  2012/02/07 19:38:26  fisyak
// Repackage
//
