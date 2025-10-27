#include "Garfield/Shaper.hh"

#include <Math/SpecFuncMathCore.h>

#include <algorithm>
#include <cmath>
#include <iostream>
#include <string>

#include "Garfield/GarfieldConstants.hh"

namespace {

double Heaviside(const double t, const double t0) {
  if (t < t0)
    return 0;
  else if (std::fabs(t - t0) < Garfield::Small)
    return 0.5;
  else
    return 1;
}

}  // namespace

namespace Garfield {

Shaper::Shaper(const std::size_t n, const double tau, const double g,
               std::string shaperType)
    : m_n(n), m_tau(tau), m_g(g) {
  std::transform(shaperType.begin(), shaperType.end(), shaperType.begin(),
                 toupper);
  if (shaperType == "UNIPOLAR") {
    m_type = ShaperType::Unipolar;
    m_tp = m_n * m_tau;
    m_prefactor = std::exp(m_n);
    m_transfer_func_sq = (std::exp(2 * m_n) / std::pow(2 * m_n, 2 * m_n)) *
                         m_tp * ROOT::Math::tgamma(2 * m_n);
  } else if (shaperType == "BIPOLAR") {
    m_type = ShaperType::Bipolar;
    const double r = m_n - std::sqrt(m_n);
    m_tp = r * m_tau;
    m_prefactor = std::exp(r) / std::sqrt(m_n);
    m_transfer_func_sq = (std::exp(2 * r) / std::pow(2 * r, 2 * m_n)) * r *
                         m_tp * ROOT::Math::tgamma(2 * m_n - 1);
  } else {
    std::cerr << m_className << ": Unknown shaper type.\n";
  }
}

double Shaper::Shape(const double t) const {
  switch (m_type) {
    case ShaperType::Unipolar:
      return UnipolarShaper(t);
    case ShaperType::Bipolar:
      return BipolarShaper(t);
    default:
      break;
  }
  return 0;
}

double Shaper::UnipolarShaper(const double t) const {
  double f = m_prefactor * std::pow(t / m_tp, m_n) * std::exp(-t / m_tau) *
             Heaviside(t, 0.);
  return m_g * f;
}

double Shaper::BipolarShaper(const double t) const {
  double f = m_prefactor * (m_n - t / m_tau) * std::pow(t / m_tp, m_n - 1) *
             std::exp(-t / m_tau) * Heaviside(t, 0.);
  return m_g * f;
}

}  // namespace Garfield
