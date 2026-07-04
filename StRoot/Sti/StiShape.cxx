#include "StiCylindricalShape.h"


ostream& operator<<(ostream& os, const StiShape& m)
{
  os << " dZ: " << m.getHalfDepth()
     << " dY: " << m.getHalfWidth();
  if (m.getShapeCode() == kCylindrical) {
    StiCylindricalShape *cyl = (StiCylindricalShape *) &m;
    os << " rO: "<< cyl->getOuterRadius()
       << " (2*dX): " << m.getThickness();
    if (cyl->getOpeningAngle() < 6.28)
      os  << " Oa: "<< cyl->getOpeningAngle();
  } else {
    os << " (2*dX): " << m.getThickness();
      //       << " Edge  " << m.getEdgeWidth();
  }
  return os;
}
