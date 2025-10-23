#include "Garfield/RandomEngineRoot.hh"

#include <iostream>

namespace Garfield {
void RandomEngineRoot::Print() {
  std::cout << "RandomEngineRoot::Print:\n"
            << "    Generator type: TRandom3\n"
            << "    Seed: " << m_rng.TRandom::GetSeed() << "\n";
}
}  // namespace Garfield
