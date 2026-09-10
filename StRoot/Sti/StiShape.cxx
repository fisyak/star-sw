#include "StiCylindricalShape.h"
#include "TMath.h"

ostream& operator<<(ostream& os, const StiShape& m)
{
  if (m.getShapeCode() == kCylindrical) {
    StiCylindricalShape *cyl = (StiCylindricalShape *) &m;
    os << " rO: "<< cyl->getOuterRadius()
       << " dR: " << m.getThickness();
    if (cyl->getOpeningAngle() < 6.28)
      os  << " dPhi: "<< TMath::RadToDeg()*cyl->getOpeningAngle();
  } else {
    os << " dX: " << m.getThickness()/2
       << " dY: " << m.getHalfWidth();
  }
  os << " dZ: " << m.getHalfDepth();
  return os;
}
