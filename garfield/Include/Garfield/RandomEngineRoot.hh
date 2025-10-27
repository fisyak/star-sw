#ifndef G_RANDOM_ENGINE_ROOT_H
#define G_RANDOM_ENGINE_ROOT_H

#include <TRandom3.h>

#include "Garfield/RandomEngine.hh"

namespace Garfield {

class RandomEngineRoot : public RandomEngine<RandomEngineRoot, UInt_t> {
 public:
  RandomEngineRoot() { m_rng.SetSeed(); };
  RandomEngineRoot(const UInt_t& seed) : RandomEngine(seed) {}
  inline double Draw() { return m_rng.Rndm(); }
  inline void SetSeed(const seed_t& seed) { m_rng.SetSeed(seed); }
  inline seed_t GetSeed() { return m_seed; }
  void Print();

 private:
  TRandom3 m_rng;
};

}  // namespace Garfield

#endif
