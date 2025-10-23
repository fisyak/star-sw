#ifndef G_RANDOM_ENGINE_H
#define G_RANDOM_ENGINE_H

namespace Garfield {

/// Abstract base class for random number generators.
template <typename Engine, typename SeedType>
class RandomEngine {
 public:
  using seed_t = SeedType;
  using engine_t = Engine;
  RandomEngine() = default;
  RandomEngine(const SeedType& seed) { this->SetSeed(seed); }
  /// Initialise the random number generator.
  inline void SetSeed(const seed_t& seed) {
    m_seed = seed;
    static_cast<Engine*>(this)->SetSeed(m_seed);
  }
  /// Draw a random number.
  inline double operator()() { return Draw(); }
  /// Draw a random number.
  inline double Draw() { return static_cast<Engine*>(this)->Draw(); }
  /// Retrieve the seed that was used
  inline seed_t GetSeed() { return static_cast<Engine*>(this)->GetSeed(); }
  /// Print some information about the random number generator.
  inline void Print() { return static_cast<Engine*>(this)->Print(); }

 protected:
  seed_t m_seed{0};
};

}  // namespace Garfield
#endif
