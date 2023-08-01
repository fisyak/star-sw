#include "StTrackSegment.h"
std::ostream&  operator<<(std::ostream& os, const trackInSector& v) {
  return os << "sector = " << v.sector << "\talpha = " << v.alpha << "\tDCA x = " << v.x << "\ty = " << v.y << "\tz = " << v.z << "\tInner Z = " 
	    << v.Track.GetZ() << "\tchi2/NDF = "  << v.Track.GetChi2() << "/" << v.Track.GetNDF();
}
