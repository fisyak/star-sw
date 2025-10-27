#include <chrono>
#include <iostream>

#include "Garfield/Random.hh"
#include "Garfield/RandomEngineRoot.hh"
#include "Garfield/RandomEngineSTL.hh"

int main() {
  // Test default RandomEngineRoot
  std::chrono::duration<double, std::nano> root_default{};
  for (std::size_t i = 0; i != 100000; ++i) {
    static double total{0.};

    auto t1 = std::chrono::high_resolution_clock::now();
    total += Garfield::Random::Draw();
    auto t2 = std::chrono::high_resolution_clock::now();
    root_default +=
        std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1);
  }
  std::cout << "root_default :" << root_default.count() / 100000 << std::endl;

  // Test user RandomEngineRoot
  Garfield::RandomEngineRoot myRandomEngineRoot(156);
  std::cout << "myRandomEngineRoot has seed :" << myRandomEngineRoot.GetSeed()
            << std::endl;
  Garfield::Random::SetEngine(myRandomEngineRoot);
  std::chrono::duration<double, std::nano> root{};
  for (std::size_t i = 0; i != 100000; ++i) {
    static double total{0.};

    auto t1 = std::chrono::high_resolution_clock::now();
    total += Garfield::Random::Draw();
    auto t2 = std::chrono::high_resolution_clock::now();
    root += std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1);
  }
  std::cout << "root :" << root.count() / 100000 << std::endl;

  // Test user RandomEngineSTL
  Garfield::RandomEngineSTL myRandomEngineSTL(42);
  std::cout << "myRandomEngineSTL has seed: " << myRandomEngineSTL.GetSeed()
            << std::endl;
  Garfield::Random::SetEngine(myRandomEngineSTL);
  std::chrono::duration<double, std::nano> STL{};
  for (std::size_t i = 0; i != 100000; ++i) {
    static double total{0.};

    auto t1 = std::chrono::high_resolution_clock::now();
    total += Garfield::Random::Draw();
    auto t2 = std::chrono::high_resolution_clock::now();
    STL += std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1);
  }
  std::cout << "STL:" << STL.count() / 100000 << std::endl;

  return 0;
}