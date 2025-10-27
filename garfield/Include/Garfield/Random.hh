#ifndef G_RANDOM_H
#define G_RANDOM_H

#include <cmath>
#include <functional>
#include <utility>

#include "Garfield/FundamentalConstants.hh"

namespace Garfield {

class Random {
 public:
  Random() = default;
  template <typename T>
  static inline void SetEngine(T engine) {
    draw = std::bind(&T::Draw, engine);
  }
  inline double static Draw() noexcept { return draw(); };

 private:
  static std::function<double(void)> draw;
};

/// Draw a random number uniformly distributed in the range [0, 1).
inline double RndmUniform() { return Random::Draw(); }

/// Draw a random number uniformly distributed in the range (0, 1).
inline double RndmUniformPos() {
  double r = RndmUniform();
  while (r <= 0.) r = RndmUniform();
  return r;
}

/// Draw two Gaussian random variates with mean zero and standard deviation one.
inline std::pair<double, double> RndmGaussians() {
  // Box-Muller algorithm
  double u = 2. * RndmUniform() - 1.;
  double v = 2. * RndmUniform() - 1.;
  double r2 = u * u + v * v;
  while (r2 > 1.) {
    u = 2. * RndmUniform() - 1.;
    v = 2. * RndmUniform() - 1.;
    r2 = u * u + v * v;
  }
  const double p = sqrt(-2. * log(r2) / r2);
  return std::make_pair(u * p, v * p);
}

/// Draw a Gaussian random variate with mean zero and standard deviation one.
inline double RndmGaussian() {
  const auto r = RndmGaussians();
  return r.first;
}

/// Draw two Gaussian random variates with mean mu and standard deviation sigma.
inline std::pair<double, double> RndmGaussians(const double mu,
                                               const double sigma) {
  auto r = RndmGaussians();
  r.first = mu + sigma * r.first;
  r.second = mu + sigma * r.second;
  return r;
}

/// Draw a Gaussian random variate with mean mu and standard deviation sigma.
inline double RndmGaussian(const double mu, const double sigma) {
  return mu + sigma * RndmGaussian();
}

/// Draw a Lorentzian random variate with mean mu
/// and half-width at half maximum gamma.
inline double RndmLorentzian(const double mu, const double gamma) {
  return mu + gamma * tan(Pi * (RndmUniform() - 0.5));
}

/// Draw a random number according to a Voigt function with mean mu.
/// The Voigt function is a convolution of a
/// Gaussian (standard deviation sigma) and
/// a Lorentzian (half width gamma).
inline double RndmVoigt(const double mu, const double sigma,
                        const double gamma) {
  if (sigma <= 0.) return RndmLorentzian(mu, gamma);
  const double a = gamma / (Sqrt2 * sigma);
  const double x = RndmLorentzian(0., a) + RndmGaussian(0., 1. / Sqrt2);
  return mu + x * Sqrt2 * sigma;
}

/// Draw a random number from a geometric distribution.
inline std::size_t RndmYuleFurry(const double mean) {
  if (mean <= 0.) return 0;
  return 1 + static_cast<std::size_t>(std::log(RndmUniformPos()) /
                                      std::log1p(-1. / mean));
  /*
  const double u = RndmUniform();
  double p = 1. / mean;
  const double q = 1. - p;
  double sum = p;
  std::size_t k = 1;
  while (sum < u) {
    ++k;
    p *= q;
    sum += p;
  }
  return k;
  */
}

/// Draw a Polya distributed random number.
inline double RndmPolya(const double theta) {
  // Algorithm from Review of Particle Physics
  // C. Amsler et al, Phys. Lett. B 667 (2008)
  if (theta <= 0.) return -log(RndmUniformPos());
  const double c = 3 * (theta + 1.) - 0.75;
  double u1, u2, v1, v2, v3;
  double x;
  while (1) {
    u1 = RndmUniformPos();
    v1 = u1 * (1. - u1);
    if (v1 == 0.) continue;
    v2 = (u1 - 0.5) * sqrt(c / v1);
    x = theta + v2;
    if (x <= 0.) continue;
    u2 = RndmUniformPos();
    v3 = 64 * u2 * u2 * pow(v1, 3);
    if (v3 <= 1. - 2 * v2 * v2 / x ||
        log(v3) <= 2 * (theta * log(x / theta) - v2)) {
      return x / (theta + 1.);
    }
  }
}

/// Draw a random number from a Landau distribution.
double RndmLandau();
/// Draw a random number from a Vavilov distribution.
double RndmVavilov(const double rkappa, const double beta2);

/// Draw a random number from a Poisson distribution.
int RndmPoisson(const double mean);

/// Draw a random energy needed to create a single electron in
/// a material asymptotic work function W and Fano factor F,
/// according to Igor Smirnov's phenomenological model.
double RndmHeedWF(const double w, const double f);

/// Draw a random (isotropic) direction vector.
inline void RndmDirection(double& dx, double& dy, double& dz,
                          const double length = 1.) {
  const double phi = TwoPi * RndmUniform();
  const double ctheta = 2 * RndmUniform() - 1.;
  const double stheta = sqrt(1. - ctheta * ctheta);
  dx = length * cos(phi) * stheta;
  dy = length * sin(phi) * stheta;
  dz = length * ctheta;
}
}  // namespace Garfield

#endif
