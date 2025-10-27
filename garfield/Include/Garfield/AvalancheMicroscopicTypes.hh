#ifndef G_AVALANCHE_MICROSCOPIC_TYPES
#define G_AVALANCHE_MICROSCOPIC_TYPES

#include <cstddef>
#include <vector>

#include "Garfield/ParticleTypes.hh"

namespace Garfield {

struct Point {
  double x{0.};
  double y{0.};
  double z{0.};       ///< Coordinates.
  double t{0.};       ///< Time.
  double energy{0.};  ///< Kinetic energy.
  double kx{0.};
  double ky{0.};
  double kz{0.};  ///< Direction/wave vector.
  int band{0};    ///< Band.
};

struct Electron {
  int status{0};            ///< Status.
  std::vector<Point> path;  ///< Drift line.
  std::size_t weight{1};    ///< Multiplicity.
  double pathLength{0.};    ///< Path length.
};

struct Seed {
  Point pt;          ///< Starting point.
  Particle type;     ///< Particle type.
  std::size_t w{1};  ///< Multiplicity.
};

}  // namespace Garfield

#endif