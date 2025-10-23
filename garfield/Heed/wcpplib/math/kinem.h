#ifndef KINEM_H
#define KINEM_H

// I.B.Smirnov, 2003

namespace Heed {

/// Scattering angles as function of incident and final projectile energy.
void theta_two_part(const double Ep0, const double Ep1, const double Mp,
                    const double Mt, double& theta_p, double& theta_t);
}  // namespace Heed

#endif
