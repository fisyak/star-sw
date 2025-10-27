#include "Garfield/Exceptions.hh"

#include <iostream>

#include "Garfield/ComponentConstant.hh"

int myfunction() { throw Garfield::Exception("myfunction failed"); }

int main() {
  try {
    myfunction();
  } catch (const Garfield::Exception& excp) {
    std::cout << excp.what() << std::endl;
  }
  try {
    Garfield::ComponentConstant comp;
    comp.SetGeometry(nullptr);
  } catch (const Garfield::Exception& excp) {
    std::cout << excp.what() << std::endl;
  }
}