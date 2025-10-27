#include <cuda.h>
#include <cuda_runtime.h>
#include <stdio.h>

#include <iostream>

#include "Garfield/Vector.hh"

__global__ void cu() {
  Garfield::Vec3D vec{1.0, 1.2, 1.3};
  printf("x=%f, y=%f, z=%f \n", vec.x(), vec.y(), vec.z());
}

int main() {
  cu<<<100, 100>>>();
  Garfield::Vec3D myVec{3.14, 3.15, 3.16};
  std::cout << myVec.x() << " " << myVec.y() << " " << myVec.z() << std::endl;
  cudaDeviceSynchronize();
  return 0;
}