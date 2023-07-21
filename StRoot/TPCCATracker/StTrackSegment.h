#ifndef __StTrackSegment__
#define __StTrackSegment__
#include "AliHLTTPCCADef.h"
#ifdef CALC_DCA_ON
#include "Riostream.h"
#include "AliHLTTPCCATrackParam.h"
class trackInSector {// Inner parameters for track segment reconstruceted in a sector;
 public:
  float                 x, y, z;  // dca
  int                   sector;
  float                 alpha;
  AliHLTTPCCATrackParam Track;
};
ostream&  operator<<(ostream& os, const trackInSector& v);
#endif /* CALC_DCA_ON */
#endif /* __StTrackSegment__ */
