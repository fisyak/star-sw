#include "Garfield/RandomEngineSTL.hh"

#include <iostream>

namespace Garfield {
void RandomEngineSTL::Print() {
  std::cout << "RandomEngineSTL::Print:\n"
            << "    Generator type: std::mt19937\n"
            << "    Seed: " << GetSeed() << "\n";
}
}  // namespace Garfield
