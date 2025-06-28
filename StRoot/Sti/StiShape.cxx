#include "StiCylindricalShape.h"


ostream& operator<<(ostream& os, const StiShape& m)
{
#if 0
  os << "StiShape: " << endl
     << "Name: "<< m.getName()
     << " ShapeCode: "<< m.getShapeCode()
     << " HalfDepth (dZ): " << m.getHalfDepth()
     << " HalfWidth (dY): " << m.getHalfWidth();
#else
  os << " dZ: " << m.getHalfDepth()
     << " dY: " << m.getHalfWidth();
#endif
  if (m.getShapeCode() == kCylindrical) {
    StiCylindricalShape *cyl = (StiCylindricalShape *) &m;
#if 0
    os << " OuterRadius: "<< cyl->getOuterRadius()
       << " OpeningAngle: "<< cyl->getOpeningAngle();
#else
    os << " rO: "<< cyl->getOuterRadius()
       << " (2*dX): " << m.getThickness()
       << " Oa: "<< cyl->getOpeningAngle();
#endif
  }
#if 0
  os << " Thickness (2*dX): " << m.getThickness()
     << " EdgeWidth: " << m.getEdgeWidth()
     << endl;
#endif
  return os;
}
