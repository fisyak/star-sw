#include "Garfield/Symmetry.hh"

#include <iostream>

#include "Garfield/Exceptions.hh"

int main() {
  Garfield::Symmetry three;
  three.Activate(Garfield::Symmetry::Type::Triangle);  // b0111000000000000
  three.Activate(Garfield::Symmetry::Type::MirrorX);   // b0111000000001000
  three.Activate(Garfield::Symmetry::Type::MirrorY);   // b0111000000011000
  std::cout << three.NumberOf(Garfield::Symmetry::Type::Triangle)
            << std::endl;  // 3
  std::cout << three.NumberOf(Garfield::Symmetry::Type::TriangleXY)
            << std::endl;  // 1
  std::cout << three.NumberOf(Garfield::Symmetry::Type::Mirror)
            << std::endl;  // 2
  std::cout << three.NumberOf(Garfield::Symmetry::Type::MirrorZ)
            << std::endl;  // 0
  std::cout << three.NumberOf(Garfield::Symmetry::Type::Periodic)
            << std::endl;  // 0
}