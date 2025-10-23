#ifndef VFLOAT_H
#define VFLOAT_H
#include <cmath>

namespace Heed {

const double vprecision = 1.0E-12;

inline bool apeq(const double& f1, const double& f2,
                 const double& prec = vprecision) {
  return (std::fabs(f1 - f2) <= prec);
}

}  // namespace Heed

#endif
