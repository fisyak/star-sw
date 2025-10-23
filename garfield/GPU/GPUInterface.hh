#ifndef G_GPUINTERFACE_H
#define G_GPUINTERFACE_H

// in theory, GPU code is faster with floats rather than doubles. This can be
// used to switch.
#if defined(GARFIELD_CUDA_USE_FLOAT)
using cuda_t = float;
#else
using cuda_t = double;
#endif

// Add this to do general optimisation of the GPU code. This will:
// * Remove 'unnecssary' checks
// * Disable GPU/CPU comparison code
// * Disable rounding code
// #define GPUOPTIMISE

#define MAXRNGDRAWS 14000

// Some constants for memory allocation
// should be dependent on hardware and dynamic, etc.
#define MAXCREATEDPARTICLES 2
#define MAXPARTICLES 7500000
#define MAXSTACKSIZE 5000000

static const cuda_t SmallGPU = 1.e-20;

#endif
