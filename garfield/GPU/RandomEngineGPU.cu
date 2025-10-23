#include "GPUFunctions.h"
#include "RandomEngineGPU.h"

namespace Garfield {

static constexpr double Pi = 3.1415926535897932384626433832795;
static constexpr double TwoPi = 2. * Pi;

__device__ RandomEngineGPU* randomEngineGPU{nullptr};

__global__ void setRandomEngine_d(RandomEngineGPU* engine) {
  randomEngineGPU = engine;
}

__device__ cuda_t RndmUniformGPU() { return randomEngineGPU->Draw(); }

__device__ cuda_t RndmUniformPosGPU() {
  cuda_t r = RndmUniformGPU();
  while (r <= 0.) r = RndmUniformGPU();
  return r;
}

__device__ void RndmDirectionGPU(cuda_t& dx, cuda_t& dy, cuda_t& dz,
                                 const cuda_t length) {
  const cuda_t phi = TwoPi * RndmUniformGPU();
  const cuda_t ctheta = 2 * RndmUniformGPU() - 1.;
  const cuda_t stheta = sqrt(1. - ctheta * ctheta);
  dx = length * cos(phi) * stheta;
  dy = length * sin(phi) * stheta;
  dz = length * ctheta;
}

__global__ void initCURandStates_d(curandState* state, const std::size_t seed) {
  int tid = threadIdx.x + blockIdx.x * blockDim.x;
  if (tid < MAXSTACKSIZE) curand_init(seed, tid, 0, &state[tid]);
}

RandomEngineGPU::RandomEngineGPU() {}

RandomEngineGPU::~RandomEngineGPU() {}

double RandomEngineGPU::initCURandStates(const std::size_t seed) {
  checkCudaErrors(
      cudaMalloc(&d_curand_states, MAXSTACKSIZE * sizeof(curandState)));
  initCURandStates_d<<<1 + MAXSTACKSIZE / 256, 256>>>(
      d_curand_states, (seed == 0 ? time(NULL) : seed));
  return MAXSTACKSIZE * sizeof(curandState);
}

void RandomEngineGPU::setRandomEngineOnDevice() {
  setRandomEngine_d<<<1, 1>>>(this);
}

__device__ cuda_t RandomEngineGPU::Draw() {
  std::size_t tid = (threadIdx.x + blockIdx.x * blockDim.x);
  return curand_uniform(&(d_curand_states[tid]));
}

}  // namespace Garfield
