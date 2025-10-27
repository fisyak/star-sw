#ifndef G_RANDOMGPU_H
#define G_RANDOMGPU_H

#include "GPUInterface.hh"

namespace Garfield {

__device__ cuda_t RndmUniformGPU();
__device__ cuda_t RndmUniformPosGPU();
__device__ void RndmDirectionGPU(cuda_t& dx, cuda_t& dy, cuda_t& dz,
                                 const cuda_t length = 1.);

}  // namespace Garfield

#endif
