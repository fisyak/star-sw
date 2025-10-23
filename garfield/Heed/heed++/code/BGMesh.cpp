#include "heed++/code/BGMesh.h"

#include <cmath>
#include <cstddef>
#include <iostream>

#include "wcpplib/util/FunNameStack.h"

namespace Heed {

BGMesh::BGMesh(double fxmin, double fxmax, long fq)
    : xmin(fxmin), xmax(fxmax), q(fq) {
  // The minimum is one interval and two points.
  check_econd11(fq, <= 1, std::cerr);
  const double rk = std::pow(fxmax / fxmin, 1. / double(fq - 1));
  x.resize(fq);
  x[0] = fxmin;
  x[fq - 1] = fxmax;
  double xr = fxmin;
  for (std::size_t n = 1; n < fq - 1; n++) {
    xr *= rk;
    x[n] = xr;
  }
}

}  // namespace Heed
