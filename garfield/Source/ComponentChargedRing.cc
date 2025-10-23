#include "Garfield/ComponentChargedRing.hh"

#include <TF1.h>

#include <array>
#include <cmath>
#include <functional>
#include <iostream>

#include "Garfield/EllipticIntegrals.hh"
#include "Garfield/Exceptions.hh"
#include "Garfield/GarfieldConstants.hh"
#include "Garfield/Medium.hh"
#include "Math/Functor.h"
#include "TMath.h"

namespace {

/// Convert field from cylindrical to Cartesian coordinates.
void GetCartesianLocalField(const double eFieldR, double& eFieldX,
                            double& eFieldY, const double x, const double y) {
  const double phi = std::atan2(y, x);
  eFieldX = eFieldR * std::cos(phi);
  eFieldY = eFieldR * std::sin(phi);
}

}  // namespace

namespace Garfield {

ComponentChargedRing::ComponentChargedRing() : Component("ChargedRing") {}

void ComponentChargedRing::SetMedium(Medium* medium) {
  if (!medium) throw Exception("medium can't be nullptr");
  m_medium = medium;
  RenormalizeCharge(m_medium->GetDielectricConstant());
}

Medium* ComponentChargedRing::GetMedium(const double x, const double y,
                                        const double z) {
  if (!m_hasArea) return Component::GetMedium(x, y, z);
  return InArea(x, y, z) ? m_medium : nullptr;
}

void ComponentChargedRing::ElectricField(const double x, const double y,
                                         const double z, double& ex, double& ey,
                                         double& ez, Medium*& m, int& status) {
  m = GetMedium(x, y, z);
  if (!m) {
    // No medium at this point.
    status = -6;
    return;
  }

  if (m->IsDriftable()) {
    status = 0;
  } else {
    status = -5;
  }

  if (!m_bCentreSet) {
    std::cerr << m_className << "::ElectricField: Centre not set.\n";
    return;
  }

  // assume cylindrical axis is y rather than z
  double dx = x - m_centre[0];
  double dz = z - m_centre[1];
  double r = std::sqrt(dx * dx + dz * dz);
  double eFieldR = 0;
  double eY_temp;
  double eR_temp;
  ey = 0;

  for (const auto& ring : m_vRings) {
    GetChargedRingField(ring, r, y, eY_temp, eR_temp);
    eFieldR += eR_temp;
    ey += eY_temp;
  }
  GetCartesianLocalField(eFieldR, ex, ez, dx, dz);
}

void ComponentChargedRing::ElectricField(const double x, const double y,
                                         const double z, double& ex, double& ey,
                                         double& ez, double& v, Medium*& m,
                                         int& status) {
  m = GetMedium(x, y, z);
  if (!m) {
    if (m_bDebug) {
      std::cout << m_className << "::ElectricField: No medium at (" << x << ", "
                << y << ", " << z << ").\n";
    }
    status = -6;
    return;
  }

  if (m->IsDriftable()) {
    status = 0;
  } else {
    status = -5;
  }

  ElectricField(x, y, z, ex, ey, ez, m, status);
  v = 0.;
}

bool ComponentChargedRing::GetBoundingBox(double& xmin, double& ymin,
                                          double& zmin, double& xmax,
                                          double& ymax, double& zmax) {
  if (!m_hasArea) {
    return Component::GetBoundingBox(xmin, ymin, zmin, xmax, ymax, zmax);
  }
  xmin = m_xmin[0];
  ymin = m_xmin[1];
  zmin = m_xmin[2];
  xmax = m_xmax[0];
  ymax = m_xmax[1];
  zmax = m_xmax[2];
  return true;
}

void ComponentChargedRing::SetArea(const double xmin, const double ymin,
                                   const double zmin, const double xmax,
                                   const double ymax, const double zmax) {
  m_xmin[0] = std::min(xmin, xmax);
  m_xmin[1] = std::min(ymin, ymax);
  m_xmin[2] = std::min(zmin, zmax);
  m_xmax[0] = std::max(xmin, xmax);
  m_xmax[1] = std::max(ymin, ymax);
  m_xmax[2] = std::max(zmin, zmax);
  m_hasArea = true;
}

void ComponentChargedRing::UnsetArea() {
  m_xmin.fill(0.);
  m_xmax.fill(0.);
  m_hasArea = false;
}

void ComponentChargedRing::Reset() {
  UnsetArea();
  m_medium = nullptr;
  m_bCentreSet = false;
  ClearActiveRings();
}

void ComponentChargedRing::GetEllipticIntegrals(double x, double& K,
                                                double& E) const {
  // from x = 0 to 10 it is in steps of 1e-3. From 10 to 1e4 in steps of 1. Then
  // in steps of 1000 until 1e7.

  std::size_t arg;
  double invStep;

  if (x < 1.e1) {
    invStep = 1000.;
    arg = static_cast<int>(x * invStep);
  } else if (x < 1.e4) {
    invStep = 1.;
    arg = static_cast<int>(x - 10.) + 10000;
  } else if (x < 1.e7) {
    invStep = 0.001;
    arg = static_cast<int>((x - 1e4) * invStep) + 19990;
  } else {
    if (m_bDebug) {
      std::cerr << m_className
                << "::GetEllipticIntegrals: Value not included in list.\n";
    }
    K = m_elliptic.back()[1];
    E = m_elliptic.back()[2];
    return;
  }
  if (arg + 1 > static_cast<int>(elliptic_size)) {
    std::cerr << m_className << "::GetEllipticIntegrals: value out of range\n";
    return;
  }
  // Linear interpolation:
  const std::array<double, 3>& ell_arg = m_elliptic[arg];
  const std::array<double, 3>& ell_arg1 = m_elliptic[arg + 1];
  const double f = (x - ell_arg[0]) * invStep;
  K = ell_arg[1] + f * (ell_arg1[1] - ell_arg[1]);
  E = ell_arg[2] + f * (ell_arg1[2] - ell_arg[2]);
}

bool ComponentChargedRing::AddChargedRing(const double x, const double y,
                                          const double z, const double N) {
  if (m_mirrRings && (y <= 0 || y >= m_d)) return false;

  const double dx = x - m_centre[0];
  const double dz = z - m_centre[1];
  const double r = std::sqrt(dx * dx + dz * dz);

  const double q = N * m_q0;
  bool mirrorRing = false;

  CheckNearbyRings(Ring(y, r, q, mirrorRing));

  // Adding mirror rings
  if (m_nMirror == 0) return true;
  mirrorRing = true;

  CheckNearbyRings(Ring(-y, r, -q, mirrorRing));

  for (unsigned int n = 1; n <= m_nMirror; ++n) {
    const double shift = 2.0 * n * m_d;
    for (double s : {-1.0, +1.0}) {
      CheckNearbyRings(Ring(y + s * shift, r, q, mirrorRing));
      CheckNearbyRings(Ring(-y + s * shift, r, -q, mirrorRing));
    }
  }
  return true;
}

void ComponentChargedRing::CheckNearbyRings(const Ring& ring) {
  int idx = 0;
  for (auto& existing : m_vRings) {
    if (std::abs(existing.z - ring.z) < m_dSpacingTolerance &&
        std::abs(existing.r - ring.r) < m_dSpacingTolerance) {
      existing.charge += ring.charge;

      // factor of 0.1 allows for the smearing of charge
      if (std::abs(existing.charge) < 0.1 * m_q0) {
        if (m_bDebug) {
          std::cout << m_className
                    << "::CheckNearbyRings: Deleted ring of charge 0 at r = "
                    << ring.r << ", z = " << ring.z << ".\n";
        }
        m_vRings[idx] = m_vRings.back();
        m_vRings.pop_back();
      }
      return;
    }
    ++idx;
  }

  // not found → insert
  m_vRings.push_back(ring);
  if (m_bDebug) {
    std::cout << m_className << "::CheckNearbyRings: Added ring of charge "
              << ring.charge << " at r = " << ring.r << ", z = " << ring.z
              << ".\n";
  }
}

void ComponentChargedRing::GetChargedRingField(
    const ComponentChargedRing::Ring& ring, double r, double z, double& eFieldZ,
    double& eFieldR) const {
  // field called exactly on a ring
  // This will cause the interpolation spiking but should almost never happen
  // as the field will rarely be called exactly on the charge
  // except when plotting.
  const double ring_r = ring.r;
  const double ring_z = ring.z;
  if (r == ring_r && z == ring_z) {
    eFieldZ = 0.;
    eFieldR = 0.;
    return;
  }

  if (ring_r > m_dSpacingTolerance) {
    // charged ring
    if (std::abs(r - ring_r) < m_dSelfFieldTolerance &&
        std::abs(z - ring_z) < m_dSelfFieldTolerance) {
      double offsetR = (r > ring_r ? 1.01 : -1.01) * m_dSelfFieldTolerance;
      double offsetZ = (z > ring_z ? 1.01 : -1.01) * m_dSelfFieldTolerance;
      r = ring_r + offsetR;
      z = ring_z + offsetZ;
    }

    double dz = z - ring_z;  //< I double-checked that's the right sign

    double dz2 = dz * dz;                        // 1
    double r2 = r * r;                           // 1
    double rr2 = ring_r * ring_r;                // 1
    double two_rrr = 2. * r * ring_r;            // 2
    const double intermediate = r2 + rr2 + dz2;  // 2
    const double a2 = intermediate + two_rrr;    // 1
    const double b2 = intermediate - two_rrr;    // 1
    const double b = std::sqrt(b2);              // 1
    const double c2 = r2 - rr2 - dz2;            // 2

    // parameter for elliptic integrals
    //< x < 0, i.e. never near x = 1 (singularity)
    const double x = 2. * two_rrr / b2;

    // calculation of elliptic integrals and fields (up to prefactor)
    double EllE, EllK;
    GetEllipticIntegrals(x, EllK, EllE);
    double charge_over_a2b = 2. * ring.charge / (a2 * b);
    eFieldZ = EllE * 2. * dz * charge_over_a2b;
    // if ri = 0?
    if (r < Small) {
      eFieldR = 0.;
    } else {
      eFieldR = (c2 * EllE + a2 * EllK) * charge_over_a2b / r;
    }
    if (m_corrFactor && !ring.mirror)
      EvaluateCorrFactor(ring, r, z, eFieldZ, eFieldR);
    return;
  }

  // coulomb ball
  if (r > m_dSelfFieldTolerance ||
      std::abs(z - ring_z) > m_dSelfFieldTolerance) {
    GetCoulombBallField(ring, r, z, eFieldZ, eFieldR);
    return;
  }
  double offsetR = 1.01 * m_dSelfFieldTolerance;
  double offsetZ = (z > ring_z ? 1.01 : -1.01) * m_dSelfFieldTolerance;
  GetCoulombBallField(ring, offsetR, ring_z + offsetZ, eFieldZ, eFieldR);
  if (m_corrFactor && !ring.mirror)
    EvaluateCorrFactor(ring, r, z, eFieldZ, eFieldR);
  return;
}

void ComponentChargedRing::GetCoulombBallField(
    const ComponentChargedRing::Ring& ring, const double r, const double z,
    double& eFieldZ, double& eFieldR) {
  const double d = std::sqrt((z - ring.z) * (z - ring.z) + r * r);
  const double f = 1. / (d * d * d);
  eFieldR = f * r;
  eFieldZ = f * (z - ring.z);

  eFieldR *= ring.charge * TwoPi;
  eFieldZ *= ring.charge * TwoPi;
}

bool ComponentChargedRing::GetVoltageRange(double& vmin, double& vmax) {
  if (m_bDebug) std::cout << "GetVoltageRange not implemented.\n";
  vmin = 0.;
  vmax = vmin;
  return false;
}

void ComponentChargedRing::UpdatePeriodicity() {
  if (m_bDebug) {
    std::cerr << m_className << "::UpdatePeriodicity:\n"
              << "    Periodicities are not supported.\n";
  }
}

void ComponentChargedRing::EnableParallelPlate(const double d,
                                               unsigned const int nMirror,
                                               const bool corrFactor) {
  if (d <= 0) {
    std::cerr << m_className << "::EnableParallelPlate:\n"
              << "    ParallelPlate not set!\n"
              << "    d can only be larger then zero.\n";
    return;
  }

  if (nMirror <= 0) {
    std::cerr << m_className << "::EnableParallelPlate:\n"
              << "    ParallelPlate not set!\n"
              << "    nMirror can only be larger then zero.\n";
    return;
  }

  m_mirrRings = true;
  m_d = d;
  m_nMirror = nMirror;
  m_corrFactor = corrFactor;

  if (m_corrFactor) {
    SetRIntegrand();
    SetYIntegrand();
  }

  std::cerr << m_className << "::EnableParallelPlate:\n"
            << "    Parallel plate for y in (" << 0 << "," << d << ") cm.\n"
            << "    Using " << 4 * m_nMirror + 1 << " mirror charges.\n";
  return;
}

void ComponentChargedRing::EvaluateCorrFactor(
    const ComponentChargedRing::Ring& ring, double r, double z, double& eFieldZ,
    double& eFieldR) const {
  const double c1 = 2. * TwoPi;

  double kRMax, kYMax;
  GetkBound(ring, r, z, kYMax, kRMax);

  m_integrandR->SetParameters(r, ring.r, z, ring.z);  //(r, rho, y, y0)
  eFieldR -=
      m_q0 * ring.charge * c1 * m_integrandR->Integral(0, kRMax, m_precision);

  m_integrandY->SetParameters(r, ring.r, z, ring.z);  //(r, rho, y, y0)
  eFieldZ += ring.charge * c1 * m_integrandY->Integral(0, kYMax, m_precision);
  return;
}

void ComponentChargedRing::GetkBound(const ComponentChargedRing::Ring& ring,
                                     double /*r*/, double z, double& kYMax,
                                     double& kRMax) const {
  const double a = 2 * (m_nMirror + 1) * m_d - (z - ring.z);

  if (a == 0.) {
    kRMax = 10.;
    kYMax = 10.;
    return;
  }

  const double infa = 1. / a;
  double logArg = TwoPi * ring.charge / m_error;
  double common = std::log(logArg);
  const double kr0 = common * infa;

  double term = std::log(kr0 * infa + 1. / (infa * infa)) -
                std::log(1. - std::exp(-2. * m_d * kr0));
  const double kr1 = (common + term) * infa;

  // take the larger of the two
  kRMax = std::max(kr0, kr1);
  if (kRMax <= 0. || kRMax >= m_kmax) kRMax = 10.;

  logArg = 2. * TwoPi * ring.charge / m_error;
  common = std::log(logArg);
  const double ky0 = common * infa;

  term = std::log(ky0 * infa + 1. / (infa * infa)) -
         std::log(1. - std::exp(-2. * m_d * ky0));
  const double ky1 = (common + term) * infa;

  kYMax = std::max(ky0, ky1);
  if (kYMax <= 0. || kYMax >= m_kmax) kYMax = 10.;
  return;
}

void ComponentChargedRing::SetYIntegrand(const double kMax) {
  if (m_integrandY) {
    delete m_integrandY;
    m_integrandY = nullptr;
  }

  auto intFunction = [this](double* v, double* par) -> double {
    const double k = v[0];
    const double r = par[0];
    const double rho = par[1];
    const double y = par[2];
    const double y0 = par[3];

    const double J0R = TMath::BesselJ0(k * r);
    const double J0Rho = TMath::BesselJ0(k * rho);
    const double exponent = std::exp(-k * m_d * (2 * m_nMirror + 1));

    const double denom = std::sinh(k * m_d);
    if (denom == 0.) return 0.;
    const double fY = k * std::cosh(k * y) * std::sinh(k * y0) / denom;

    return exponent * J0R * J0Rho * fY;
  };

  m_integrandY = new TF1("integrandR", intFunction, 0., kMax, 4);
  m_integrandY->SetNpx(1000);
}

void ComponentChargedRing::SetRIntegrand(const double kMax) {
  if (m_integrandR) {
    delete m_integrandR;
    m_integrandR = nullptr;
  }

  auto intFunction = [this](double* v, double* par) -> double {
    const double k = v[0];
    const double r = par[0];
    const double rho = par[1];
    const double y = par[2];
    const double y0 = par[3];

    const double J0R = TMath::BesselJ0(k * r);
    const double J1Rho = TMath::BesselJ1(k * rho);
    const double exponent = std::exp(-k * m_d * (2 * m_nMirror + 1));

    const double denom = std::sinh(k * m_d);
    if (denom == 0.) return 0.;
    const double fY = std::sinh(k * y) * std::sinh(k * y0) / denom;

    return k * exponent * J0R * J1Rho * fY;
  };

  m_integrandR = new TF1("integrandR", intFunction, 0., kMax, 4);
  m_integrandR->SetNpx(1000);
}

}  // namespace Garfield
