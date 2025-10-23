#include "heed++/code/EnergyMesh.h"

#include <cmath>
#include <iostream>

#include "wcpplib/util/FunNameStack.h"

namespace Heed {

EnergyMesh::EnergyMesh(double femin, double femax, long fq)
    : q(fq), emin(femin), emax(femax) {
  check_econd21(q, < 0 ||, > pqener - 1, std::cerr);

  const double rk = pow(emax / emin, (1.0 / double(q)));
  double er = emin;
  e[0] = er;
  for (long n = 1; n < q + 1; n++) {
    e[n] = er * rk;
    ec[n - 1] = (e[n - 1] + e[n]) * 0.5;
    er = e[n];
  }
}

EnergyMesh::EnergyMesh(const std::vector<double>& fec) : q(fec.size()) {
  check_econd21(q, < 0 ||, > pqener - 1, std::cerr);
  check_econd11(q, != 1, std::cerr);  // otherwise problems with emin/emax
  if (q <= 0) {
    emin = 0.0;
    emax = 0.0;
    return;
  }
  emin = fec[0] - (fec[1] - fec[0]) / 2.0;
  emax = fec[q - 1] + (fec[q - 1] - fec[q - 2]) / 2.0;
  e[0] = emin;
  e[q] = emax;

  for (long n = 0; n < q; n++) {
    ec[n] = fec[n];
  }
  for (long n = 1; n < q; n++) {
    e[n] = 0.5 * (fec[n - 1] + fec[n]);
  }
}

long EnergyMesh::get_interval_number(const double ener) const {
  if (ener < emin) return -1;
  if (ener > emax) return q;

  long n1 = 0;
  long n2 = q;  // right side of last
  while (n2 - n1 > 1) {
    const long n3 = n1 + ((n2 - n1) >> 1);
    if (ener < e[n3]) {
      n2 = n3;
    } else {
      n1 = n3;
    }
  }
  return n1;
}

long EnergyMesh::get_interval_number_between_centers(const double ener) const {
  if (ener < ec[0]) return -1;
  if (ener > ec[q - 1]) return q;

  long n1 = 0;
  long n2 = q - 1;  // right side of last
  while (n2 - n1 > 1) {
    const long n3 = n1 + ((n2 - n1) >> 1);
    if (ener < ec[n3]) {
      n2 = n3;
    } else {
      n1 = n3;
    }
  }
  return n1;
}

}  // namespace Heed
