#include "Garfield/Vector.hh"

#include <iostream>

int main() {
  std::cout << __cpp_static_assert << std::endl;
  Garfield::Vec3D vec0;
  Garfield::Vec3D vec1(.1, .2, .3);
  Garfield::Vec3D vec2(2.0, 4.0, 6.0);
  std::cout << vec1.x() << " " << vec1.y() << " " << vec1.z() << std::endl;
  std::cout << vec2.x() << " " << vec2.y() << " " << vec2.z() << std::endl;

  Garfield::Vec3D sum = vec1 + vec2;
  std::cout << sum.x() << " " << sum.y() << " " << sum.z() << std::endl;
  Garfield::Vec3D diff = vec2 - vec1;
  std::cout << diff.x() << " " << diff.y() << " " << diff.z() << std::endl;

  std::array<double, 3> toto = vec1;
  std::cout << toto[0] << " " << toto[1] << " " << toto[2] << std::endl;

  Garfield::Vec3D from_array;
  from_array = toto;
  std::cout << from_array.x() << " " << from_array.y() << " " << from_array.z()
            << std::endl;
}
