#ifndef G_RANDOM_ENGINE_GPU_H
#define G_RANDOM_ENGINE_GPU_H

#include <curand.h>
#include <curand_kernel.h>

#include "GPUInterface.hh"

namespace Garfield {

class RandomEngineGPU {
 public:
  /// Constructor
  RandomEngineGPU();
  /// Destructor
  ~RandomEngineGPU();
  /// Call the random number generator.
  __device__ cuda_t Draw();
  void setRandomEngineOnDevice();

  // cuRAND specifics
  curandState* d_curand_states{nullptr};
  double initCURandStates(const std::size_t seed);
};

}  // namespace Garfield

#endif
