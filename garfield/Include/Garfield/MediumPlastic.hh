#ifndef G_MEDIUM_PLASTIC_H
#define G_MEDIUM_PLASTIC_H

#include "Garfield/Medium.hh"

namespace Garfield {

/// Plastic medium.

class MediumPlastic : public Medium {
 public:
  /// Default constructor.
  MediumPlastic() : MediumPlastic(1.) {}
  /// Constructor from dielectric constant.
  MediumPlastic(const double eps) : Medium() {
    m_className = "MediumPlastic";
    m_name = "Plastic";
    if (eps > 1.) m_epsilon = eps;
  }
  /// Destructor
  virtual ~MediumPlastic() = default;

  void EnableDrift(const bool /*on*/) override {}
  void EnablePrimaryIonisation(const bool /*on*/) override {}
};
}  // namespace Garfield

#endif
