#ifndef MDF4HITERROR_H
#define MDF4HITERROR_H

#include "AliHLTTPCCADef.h"
#include "AliHLTTPCCAMath.h"
#include "AliHLTTPCCATrackParam.h"
#include "StDetectorDbMaker/StiTpcHitErrorMDF4.h"

static void GetMdf4ClusterErrors2(
  const uint_v IRow,
  const float_v AdcL,
  const AliHLTTPCCATrackParamVector& t,
  float_v& err2Y,
  float_v& err2Z,
  float_v& dy,
  float_v& dz
)
{
  for(size_t iV=0; iV < float_v::Size; iV++)
  {
    Double_t dZ = 0, dY = 0;;
    Double_t _z    = t.Z()[iV];
    Double_t _eta  = TMath::ASin(t.GetSinPhi()[iV]);
    Double_t _tanl = t.DzDs()[iV];
    Double_t ecross = 0, edip = 0;
    Double_t fudgeFactor = 1;
    Double_t adcL =  AdcL[iV];
    if (adcL > 0.0) {
      if (IRow[iV] <= 40) {
	StiTpcInnerHitErrorMDF4::instance()->calculateError(_z,_eta,_tanl, ecross, edip, fudgeFactor, adcL, &dZ, &dY);
      } else {
	StiTpcOuterHitErrorMDF4::instance()->calculateError(_z,_eta,_tanl, ecross, edip, fudgeFactor, adcL, &dZ, &dY);
      }
    }
    err2Y[iV] = ecross;
    err2Z[iV] = edip;
    dy[iV] = dY;
    dz[iV] = dZ;
  }
}

#endif // MDF4HITERROR_H
