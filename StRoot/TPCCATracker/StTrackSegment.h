#ifndef __StTrackSegment__
#define __StTrackSegment__
#ifdef CALC_DCA_ON
#include "AliHLTTPCCATrackParam.h"
struct trackInSector {// Inner parameters for track segment reconstruceted in a sector;
  float                 x, y, z;  // dca
  int                   sector;
  float                 alpha;
  AliHLTTPCCATrackParam Track;
};
#endif /* CALC_DCA_ON */
#endif /* __StTrackSegment__ */
