#ifndef G_RANDOM_ENGINE_STL_H
#define G_RANDOM_ENGINE_STL_H

#include <random>

#include "Garfield/RandomEngine.hh"

namespace Garfield {

class RandomEngineSTL
    : public RandomEngine<RandomEngineSTL, std::mt19937::result_type> {
 public:
  RandomEngineSTL() = default;
  RandomEngineSTL(const std::mt19937::result_type& seed) : RandomEngine(seed) {}
  inline double Draw() {
    return std::generate_canonical<double, std::numeric_limits<double>::digits>(
        m_rng);
  }
  inline void SetSeed(const seed_t& seed) { m_rng.seed(seed); }
  inline seed_t GetSeed() { return m_seed; }
  void Print();

 private:
  std::mt19937 m_rng{std::random_device{}()};
};

}  // namespace Garfield

#endif