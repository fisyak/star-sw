#include <thrust/count.h>
#include <thrust/device_vector.h>
#include <thrust/execution_policy.h>
#include <thrust/host_vector.h>
#include <thrust/remove.h>
#include <thrust/sort.h>

#include <chrono>
#include <cmath>
#include <iostream>

#include "AvalancheMicroscopicGPU.h"
#include "GPUFunctions.h"
#include "GPUInterface.hh"
#include "Garfield/AvalancheMicroscopic.hh"
#include "Garfield/FundamentalConstants.hh"
#include "Garfield/GarfieldConstants.hh"
#include "Garfield/RandomEngineRoot.hh"
#include "Garfield/Sensor.hh"
#include "RandomEngineGPU.h"
#include "RandomGPU.h"
#include "SensorGPU.h"

using highres_clock_t = std::chrono::high_resolution_clock;
using second_t = std::chrono::duration<double, std::ratio<1>>;

namespace Garfield {

// ----------------------------------------------------------------------------------------------------
// Global/Device functions that can't be included in the class due to the
// definition being compiled with AvalancheMicroscopic
__global__ void setStatusArray(int *all_status_array, int num_active_particles,
                               int num_total_particles) {
  int thread_idx = (threadIdx.x + blockIdx.x * blockDim.x);
  all_status_array[num_active_particles + thread_idx] =
      thread_idx + num_total_particles;
}

__device__ double Mag(const double x, const double y, const double z) {
  return std::sqrt(x * x + y * y + z * z);
}

// ----------------------------------------------------------------------------------------------------
// Class methods
AvalancheMicroscopicGPU::AvalancheMicroscopicGPU() {
  // MAXPARTICLES :- Maximum number of particles that can be generated in one
  // shower MAXSTACKSIZE :- Maximum number of *active* particles in one shower
  // (i.e. same size as the reserve for stackOld) MAXCREATEDPARTICLES :- Maximum
  // possible number of created particles per particle per iteration (usually
  // 1-2 because the loop is ended after particle creation)
  memUsageStack += InitialiseGPUParticleStack(stackOldGPU, MAXPARTICLES);
  memUsageStack += InitialiseGPUParticleStack(
      stackNewGPU, MAXCREATEDPARTICLES * MAXSTACKSIZE);
  InitialiseCPUParticleStack(
      stackTransfer,
      MAXPARTICLES);  // on CPU stack so doesn't count to GPU memory usage
  checkCudaErrors(cudaMalloc(&activeIndexArray, MAXSTACKSIZE * sizeof(int)));
  checkCudaErrors(cudaMalloc(
      &newIndexArray, (MAXCREATEDPARTICLES * MAXSTACKSIZE) * sizeof(int)));
  memUsageStack +=
      (MAXCREATEDPARTICLES * MAXSTACKSIZE + MAXSTACKSIZE) * sizeof(int);

  std::cout << "--------------- AvalancheMicroscopicGPU Initialised:"
            << std::endl;
  std::cout << "Memory assigned:  " << memUsageStack / (1024. * 1024.) << " MB"
            << std::endl;
}

AvalancheMicroscopicGPU::~AvalancheMicroscopicGPU() {
  cudaFree(newIndexArray);
  cudaFree(activeIndexArray);
  FreeCPUParticleStack(stackTransfer);
  FreeGPUParticleStack(stackNewGPU);
  FreeGPUParticleStack(stackOldGPU);
  // DELETE INTERNAL STUFF
}

double AvalancheMicroscopicGPU::InitialiseGPUParticleStack(ParticleStack &stack,
                                                           std::size_t num) {
  // initialise all the memory
  checkCudaErrors(cudaMalloc(&stack.x, (num) * sizeof(double)));
  checkCudaErrors(cudaMalloc(&stack.y, (num) * sizeof(double)));
  checkCudaErrors(cudaMalloc(&stack.z, (num) * sizeof(double)));
  checkCudaErrors(cudaMalloc(&stack.t, (num) * sizeof(double)));
  checkCudaErrors(cudaMalloc(&stack.x0, (num) * sizeof(double)));
  checkCudaErrors(cudaMalloc(&stack.y0, (num) * sizeof(double)));
  checkCudaErrors(cudaMalloc(&stack.z0, (num) * sizeof(double)));
  checkCudaErrors(cudaMalloc(&stack.t0, (num) * sizeof(double)));
  checkCudaErrors(cudaMalloc(&stack.e0, (num) * sizeof(double)));
  checkCudaErrors(cudaMalloc(&stack.status, (num) * sizeof(int)));
  checkCudaErrors(cudaMalloc(&stack.energy, (num) * sizeof(double)));
  checkCudaErrors(cudaMalloc(&stack.band, (num) * sizeof(int)));
  checkCudaErrors(cudaMalloc(&stack.kx, (num) * sizeof(double)));
  checkCudaErrors(cudaMalloc(&stack.ky, (num) * sizeof(double)));
  checkCudaErrors(cudaMalloc(&stack.kz, (num) * sizeof(double)));
  checkCudaErrors(cudaMalloc(&stack.ptype, (num) * sizeof(Particle)));
  stack.stack_size = 0;

  return (num * sizeof(double) * 13) + (num * sizeof(int) * 2) +
         (num * sizeof(Particle));
}

void AvalancheMicroscopicGPU::FreeGPUParticleStack(ParticleStack &stack) {
  checkCudaErrors(cudaFree(stack.x));
  checkCudaErrors(cudaFree(stack.y));
  checkCudaErrors(cudaFree(stack.z));
  checkCudaErrors(cudaFree(stack.t));
  checkCudaErrors(cudaFree(stack.x0));
  checkCudaErrors(cudaFree(stack.y0));
  checkCudaErrors(cudaFree(stack.z0));
  checkCudaErrors(cudaFree(stack.t0));
  checkCudaErrors(cudaFree(stack.e0));
  checkCudaErrors(cudaFree(stack.status));
  checkCudaErrors(cudaFree(stack.energy));
  checkCudaErrors(cudaFree(stack.band));
  checkCudaErrors(cudaFree(stack.kx));
  checkCudaErrors(cudaFree(stack.ky));
  checkCudaErrors(cudaFree(stack.kz));
  checkCudaErrors(cudaFree(stack.ptype));
}

void AvalancheMicroscopicGPU::InitialiseCPUParticleStack(ParticleStack &stack,
                                                         std::size_t num) {
  // initialise all the memory
  stack.x = new double[num];
  stack.y = new double[num];
  stack.z = new double[num];
  stack.t = new double[num];
  stack.x0 = new double[num];
  stack.y0 = new double[num];
  stack.z0 = new double[num];
  stack.t0 = new double[num];
  stack.e0 = new double[num];
  stack.status = new int[num];
  stack.energy = new double[num];
  stack.band = new int[num];
  stack.kx = new double[num];
  stack.ky = new double[num];
  stack.kz = new double[num];
  stack.ptype = new Particle[num];
  stack.stack_size = 0;
}

void AvalancheMicroscopicGPU::FreeCPUParticleStack(ParticleStack &stack) {
  free(stack.x);
  free(stack.y);
  free(stack.z);
  free(stack.t);
  free(stack.x0);
  free(stack.y0);
  free(stack.z0);
  free(stack.t0);
  free(stack.e0);
  free(stack.status);
  free(stack.energy);
  free(stack.band);
  free(stack.kx);
  free(stack.ky);
  free(stack.kz);
  free(stack.ptype);
}

// device function to transfer the whole current stack to the given transfer
// stack
void AvalancheMicroscopicGPU::transferParticleStack(
    ParticleStack dest, std::size_t offset, ParticleStack source,
    std::size_t num, TransferType type, bool init_dest) {
  cudaMemcpyKind cuda_type;
  switch (type) {
    case TransferType::HostToDevice:
      cuda_type = cudaMemcpyHostToDevice;
      break;
    case TransferType::DeviceToDevice:
      cuda_type = cudaMemcpyDeviceToDevice;
      break;
    case TransferType::DeviceToHost:
      cuda_type = cudaMemcpyDeviceToHost;
      break;
  }
  if (init_dest) {
    checkCudaErrors(cudaMemcpy(dest.x + offset, source.x0, num * sizeof(cuda_t),
                               cuda_type));
    checkCudaErrors(cudaMemcpy(dest.y + offset, source.y0, num * sizeof(cuda_t),
                               cuda_type));
    checkCudaErrors(cudaMemcpy(dest.z + offset, source.z0, num * sizeof(cuda_t),
                               cuda_type));
    checkCudaErrors(cudaMemcpy(dest.t + offset, source.t0, num * sizeof(cuda_t),
                               cuda_type));
    checkCudaErrors(cudaMemcpy(dest.energy + offset, source.e0,
                               num * sizeof(cuda_t), cuda_type));
    thrust::fill_n(thrust::device, dest.status + stackOldGPU.stack_size, num,
                   0);
  } else {
    checkCudaErrors(
        cudaMemcpy(dest.x + offset, source.x, num * sizeof(cuda_t), cuda_type));
    checkCudaErrors(
        cudaMemcpy(dest.y + offset, source.y, num * sizeof(cuda_t), cuda_type));
    checkCudaErrors(
        cudaMemcpy(dest.z + offset, source.z, num * sizeof(cuda_t), cuda_type));
    checkCudaErrors(
        cudaMemcpy(dest.t + offset, source.t, num * sizeof(cuda_t), cuda_type));
    checkCudaErrors(cudaMemcpy(dest.energy + offset, source.energy,
                               num * sizeof(cuda_t), cuda_type));
    checkCudaErrors(cudaMemcpy(dest.status + offset, source.status,
                               num * sizeof(int), cuda_type));
  }
  checkCudaErrors(
      cudaMemcpy(dest.x0 + offset, source.x0, num * sizeof(cuda_t), cuda_type));
  checkCudaErrors(
      cudaMemcpy(dest.y0 + offset, source.y0, num * sizeof(cuda_t), cuda_type));
  checkCudaErrors(
      cudaMemcpy(dest.z0 + offset, source.z0, num * sizeof(cuda_t), cuda_type));
  checkCudaErrors(
      cudaMemcpy(dest.t0 + offset, source.t0, num * sizeof(cuda_t), cuda_type));
  checkCudaErrors(
      cudaMemcpy(dest.e0 + offset, source.e0, num * sizeof(cuda_t), cuda_type));
  checkCudaErrors(cudaMemcpy(dest.band + offset, source.band, num * sizeof(int),
                             cuda_type));
  checkCudaErrors(
      cudaMemcpy(dest.kx + offset, source.kx, num * sizeof(cuda_t), cuda_type));
  checkCudaErrors(
      cudaMemcpy(dest.ky + offset, source.ky, num * sizeof(cuda_t), cuda_type));
  checkCudaErrors(
      cudaMemcpy(dest.kz + offset, source.kz, num * sizeof(cuda_t), cuda_type));
  checkCudaErrors(cudaMemcpy(dest.ptype + offset, source.ptype,
                             num * sizeof(Particle), cuda_type));
}

void AvalancheMicroscopicGPU::TransferStackFromCPUToGPU(
    std::vector<Garfield::Seed> &stackOld) {
  // assumes that stackOld contains only active particles and the current state
  // of the GPU memory can be overwritten
  std::cout << "Transferring stack data to GPU..." << std::endl;
  stackOldGPU.stack_size = stackOld.size();

  // transfer the current particle list to the device
  // the stackTransfer object is used here to shift from array of structures to
  // structure of arrays a memcpy can then be done from stackTransfer to the
  // device stackOldGPU
  std::size_t i{0};

  // temporary vector to hold the indices of the active particles. Allows a
  // memcpy below.
  thrust::host_vector<int> index_transfer;
  for (const auto &particle : stackOld) {
    stackTransfer.x[i] = particle.pt.x;
    stackTransfer.y[i] = particle.pt.y;
    stackTransfer.z[i] = particle.pt.z;
    stackTransfer.t[i] = particle.pt.t;
    stackTransfer.energy[i] = particle.pt.energy;
    stackTransfer.x0[i] = particle.pt.x;
    stackTransfer.y0[i] = particle.pt.y;
    stackTransfer.z0[i] = particle.pt.z;
    stackTransfer.t0[i] = particle.pt.t;
    stackTransfer.e0[i] = particle.pt.energy;
    stackTransfer.band[i] = particle.pt.band;
    stackTransfer.kx[i] = particle.pt.kx;
    stackTransfer.ky[i] = particle.pt.ky;
    stackTransfer.kz[i] = particle.pt.kz;
    stackTransfer.ptype[i] = particle.type;
    stackTransfer.status[i] = 0;
    index_transfer.push_back(i);
    i++;
  }

  transferParticleStack(stackOldGPU, 0, stackTransfer, stackOld.size(),
                        TransferType::HostToDevice);

  // initialise active indices to -1 (i.e. no active particle)
  thrust::device_ptr<int> activeIndexArray_thr_ptr(activeIndexArray);
  thrust::fill(activeIndexArray_thr_ptr,
               activeIndexArray_thr_ptr + MAXSTACKSIZE, -1);

  // initialise new indices to one past the max size
  thrust::device_ptr<int> newIndexArray_thr_ptr(newIndexArray);
  thrust::fill(newIndexArray_thr_ptr,
               newIndexArray_thr_ptr + MAXCREATEDPARTICLES * MAXSTACKSIZE,
               (MAXCREATEDPARTICLES * MAXSTACKSIZE) + 1);

  // copy the initial indices of the active particles
  thrust::copy(index_transfer.begin(), index_transfer.end(),
               activeIndexArray_thr_ptr);
  numActiveParticles = index_transfer.size();
  m_nElectrons = numActiveParticles;

  std::cout << "Stack transfer complete" << std::endl;
}

void AvalancheMicroscopicGPU::TransferClassInternalInfo(
    AvalancheMicroscopic *src) {
  std::cout << "Transferring internal data to GPU..." << std::endl;
  memUsageSensor = src->m_sensor->CreateGPUTransferObject(m_sensor);

  Garfield::RandomEngineRoot randomEngine(123456);
  checkCudaErrors(cudaMallocManaged(&m_randomEngine, sizeof(RandomEngineGPU)));
  memRNG = sizeof(RandomEngineGPU) +
           m_randomEngine->initCURandStates(randomEngine.GetSeed());
  m_randomEngine->setRandomEngineOnDevice();

  std::cout << "--------------- AvalancheMicroscopic Internals Transferred:"
            << std::endl;
  std::cout << "Stack Memory:  " << memUsageStack / (1024. * 1024.) << " MB"
            << std::endl;
  std::cout << "Sensor Memory:  " << memUsageSensor / (1024. * 1024.) << " MB"
            << std::endl;
  std::cout << "RNG Memory:  " << memRNG / (1024. * 1024. * 1024.) << " GB"
            << std::endl;
  std::cout << "TOTAL:   "
            << (memUsageStack + memUsageSensor + memRNG) /
                   (1024. * 1024. * 1024.)
            << " GB" << std::endl;
  std::cout << "--------------- Transfer Complete." << std::endl;
}

// process the particle stack
size_t AvalancheMicroscopicGPU::processParticleStack(std::size_t &num_active,
                                                     std::size_t &num_new) {
  // remove any active particles that now have status of -1 (should probably be
  // < 0) do this on the activeIndexArray as stackOld will contain *all*
  // particles, even those that have terminated sort the index/status array
  thrust::device_ptr<int> activeIndexArray_thr_ptr(activeIndexArray);
  auto num_active_particles_ptr =
      thrust::remove(activeIndexArray_thr_ptr,
                     activeIndexArray_thr_ptr + numActiveParticles, -1);
  int num_active_particles =
      num_active_particles_ptr - activeIndexArray_thr_ptr;

  // Sort all newly created particles so they are at the start of the array
  // note: this is where the newIndexArray comes in as these values are less
  // than the max if it points to a valid new particle create a zip iterator and
  // then sort based on the new particles key
  auto it = thrust::make_zip_iterator(thrust::make_tuple(
      stackNewGPU.x0, stackNewGPU.y0, stackNewGPU.z0, stackNewGPU.t0,
      stackNewGPU.e0, stackNewGPU.band, stackNewGPU.kx, stackNewGPU.ky,
      stackNewGPU.kz, stackNewGPU.ptype));

  thrust::sort_by_key(thrust::device, newIndexArray,
                      newIndexArray + numActiveParticles * MAXCREATEDPARTICLES,
                      it);
  int num_not_new_particles =
      thrust::count(thrust::device, newIndexArray,
                    newIndexArray + numActiveParticles * MAXCREATEDPARTICLES,
                    (MAXSTACKSIZE * 2) + 1);
  int num_new_particles =
      numActiveParticles * MAXCREATEDPARTICLES - num_not_new_particles;

  // transfer the new particle info
  transferParticleStack(stackOldGPU, stackOldGPU.stack_size, stackNewGPU,
                        num_new_particles * sizeof(double),
                        TransferType::DeviceToDevice, true);

  // set the indices of the new particles in the index array
  setStatusArray<<<1 + num_new_particles / 512, 512>>>(
      activeIndexArray, num_active_particles, stackOldGPU.stack_size);
  cudaDeviceSynchronize();

  numActiveParticles = num_active_particles + num_new_particles;
  m_nElectrons += num_new_particles;
  stackOldGPU.stack_size += num_new_particles;

  num_active = numActiveParticles;
  num_new = num_new_particles;
  return numActiveParticles;
}

void AvalancheMicroscopicGPU::SetCUDADevice(int dev) {
  std::cout << "INFO:  Setting CUDA device to " << dev << std::endl;
  checkCudaErrors(cudaSetDevice(dev));
}

void AvalancheMicroscopicGPU::TransferStackFromGPUToCPU(
    std::vector<Electron> &stack, bool end_points) {
  Electron elec;
  // Going to add two paths as start and end points
  elec.path.resize(2);
  stack.clear();
  transferParticleStack(stackTransfer, 0, stackOldGPU, stackOldGPU.stack_size,
                        AvalancheMicroscopicGPU::TransferType::DeviceToHost);
  for (std::size_t i = 0; i < stackOldGPU.stack_size; i++) {
    if (((!end_points) && (stackTransfer.status[i] == 0)) ||
        ((end_points) && (stackTransfer.status[i] != 0))) {
      elec.path.back().x = stackTransfer.x[i];
      elec.path.back().y = stackTransfer.y[i];
      elec.path.back().z = stackTransfer.z[i];
      elec.path.back().t = stackTransfer.t[i];
      elec.path.back().energy = stackTransfer.energy[i];

      elec.path[0].x = stackTransfer.x0[i];
      elec.path[0].y = stackTransfer.y0[i];
      elec.path[0].z = stackTransfer.z0[i];
      elec.path[0].kx = stackTransfer.kx[i];
      elec.path[0].ky = stackTransfer.ky[i];
      elec.path[0].kz = stackTransfer.kz[i];
      elec.path[0].t = stackTransfer.t0[i];
      elec.path[0].energy = stackTransfer.e0[i];
      elec.path[0].band = stackTransfer.band[i];
      // elec.path[0].hole = stackTransfer.hole[i];
      elec.status = stackTransfer.status[i];
      stack.push_back(elec);

      /*if (stackTransfer.status[i] == StatusAttached)
      {
          --m_nElectronsGPU;
      }*/
    }
  }

  // GPUREMOVE: de-allocate everything
}

__device__ void Update(AvalancheMicroscopicGPU::ParticleStack &raw_ptr_stack,
                       int thread_idx, const cuda_t x, const cuda_t y,
                       const cuda_t z, const cuda_t t, const cuda_t energy,
                       const cuda_t kx, const cuda_t ky, const cuda_t kz,
                       const int band) {
  raw_ptr_stack.x[thread_idx] = x;
  raw_ptr_stack.y[thread_idx] = y;
  raw_ptr_stack.z[thread_idx] = z;
  raw_ptr_stack.t[thread_idx] = t;
  raw_ptr_stack.energy[thread_idx] = energy;
  raw_ptr_stack.band[thread_idx] = band;
  raw_ptr_stack.kx[thread_idx] = kx;
  raw_ptr_stack.ky[thread_idx] = ky;
  raw_ptr_stack.kz[thread_idx] = kz;
}

__device__ void AddToStack(
    AvalancheMicroscopicGPU::ParticleStack &raw_ptr_stack,
    std::size_t &num_new_particles, int thread_idx, int *new_status_array,
    const cuda_t x, const cuda_t y, const cuda_t z, const cuda_t t,
    const cuda_t energy, const cuda_t kx, const cuda_t ky, const cuda_t kz,
    const int band, const Particle ptype) {
  std::size_t step = MAXCREATEDPARTICLES;

  // only record the values that can be sorted
  raw_ptr_stack.x0[thread_idx * step + num_new_particles] = x;
  raw_ptr_stack.y0[thread_idx * step + num_new_particles] = y;
  raw_ptr_stack.z0[thread_idx * step + num_new_particles] = z;
  raw_ptr_stack.t0[thread_idx * step + num_new_particles] = t;
  raw_ptr_stack.e0[thread_idx * step + num_new_particles] = energy;
  raw_ptr_stack.band[thread_idx * step + num_new_particles] = band;
  raw_ptr_stack.kx[thread_idx * step + num_new_particles] = kx;
  raw_ptr_stack.ky[thread_idx * step + num_new_particles] = ky;
  raw_ptr_stack.kz[thread_idx * step + num_new_particles] = kz;
  raw_ptr_stack.ptype[thread_idx * step + num_new_particles] = ptype;

  new_status_array[thread_idx * step + num_new_particles] =
      thread_idx * step + num_new_particles;
  num_new_particles++;
}

__device__ void AddToStack(
    AvalancheMicroscopicGPU::ParticleStack &raw_ptr_stack,
    std::size_t &num_new_particles, int thread_idx, int *new_status_array,
    const cuda_t x, const cuda_t y, const cuda_t z, const cuda_t t,
    const cuda_t energy, const Particle ptype) {
  cuda_t dx = 0., dy = 0., dz = 1.;
  RndmDirectionGPU(dx, dy, dz);
  AddToStack(raw_ptr_stack, num_new_particles, thread_idx, new_status_array, x,
             y, z, t, energy, dx, dy, dz, 0, ptype);
}

__device__ void Terminate(cuda_t x0, cuda_t y0, cuda_t z0, cuda_t t0,
                          cuda_t &x1, cuda_t &y1, cuda_t &z1, cuda_t &t1,
                          SensorGPU *m_sensor) {
  const cuda_t dx = x1 - x0;
  const cuda_t dy = y1 - y0;
  const cuda_t dz = z1 - z0;
  cuda_t d = Mag(dx, dy, dz);
  while (d > BoundaryDistance) {
    d *= 0.5;
    const cuda_t xm = 0.5 * (x0 + x1);
    const cuda_t ym = 0.5 * (y0 + y1);
    const cuda_t zm = 0.5 * (z0 + z1);
    const cuda_t tm = 0.5 * (t0 + t1);
    // Check if the mid-point is inside the drift medium.
    cuda_t ex = 0., ey = 0., ez = 0.;
    MediumGPU *medium = nullptr;
    int status = 0;
    m_sensor->ElectricField(xm, ym, zm, ex, ey, ez, medium, status);
    if ((status == 0) && (m_sensor->IsInArea(xm, ym, zm))) {
      x0 = xm;
      y0 = ym;
      z0 = zm;
      t0 = tm;
    } else {
      x1 = xm;
      y1 = ym;
      z1 = zm;
      t1 = tm;
    }
  }
}

__global__ void TransportElectron(
    AvalancheMicroscopicGPU::ParticleStack raw_ptr_stack,
    AvalancheMicroscopicGPU::ParticleStack raw_ptr_stack_new,
    int *all_status_array, int *new_status_array, SensorGPU *m_sensor,
    cuda_t m_deltaCut, int /*id*/, cuda_t c1, cuda_t c2, cuda_t /*fLim*/,
    cuda_t /*fInv*/, std::size_t max_thread_idx, bool doSignal,
    bool integrateWeightingField, int debug_electron = -1) {
  // GPU_REMOVE: std::vector<std::pair<double, double> > stackPhotons;
  // GPU_REMOVE: std::vector<std::pair<int, double> > secondaries;
  int num_secondaries;
  Particle secondaries_type[MAXCREATEDPARTICLES];
  cuda_t secondaries_energy[MAXCREATEDPARTICLES];

  // find the thread id
  int thread_idx = (threadIdx.x + blockIdx.x * blockDim.x);
  if (thread_idx >= max_thread_idx) {
    return;
  }

  int particle_idx{all_status_array[thread_idx]};

  // reset new particle info
  for (int i = 0; i < MAXCREATEDPARTICLES; i++) {
    new_status_array[thread_idx * MAXCREATEDPARTICLES + i] =
        (MAXSTACKSIZE * 2) + 1;
  }

  // reset new particles
  std::size_t num_new_particles{0};

  // initialiase some things
  MediumGPU *medium{nullptr};

  // Get an electron/hole from the stack.
  // int status = raw_ptr_stack.status[particle_idx];
  cuda_t x = raw_ptr_stack.x[particle_idx];
  cuda_t y = raw_ptr_stack.y[particle_idx];
  cuda_t z = raw_ptr_stack.z[particle_idx];
  cuda_t t = raw_ptr_stack.t[particle_idx];
  cuda_t en = raw_ptr_stack.energy[particle_idx];
  int band = raw_ptr_stack.band[particle_idx];
  cuda_t kx = raw_ptr_stack.kx[particle_idx];
  cuda_t ky = raw_ptr_stack.ky[particle_idx];
  cuda_t kz = raw_ptr_stack.kz[particle_idx];
  Particle ptype = raw_ptr_stack.ptype[particle_idx];

  bool ok = true;
  // bail out if we don't have a valid particle to transport
  // if (raw_ptr_stack.status[thread_idx] != 0) {
  //    return;
  //}

  // Count number of collisions between updates.
  std::size_t nCollTemp = 0;

  // Get the local electric field and medium.
  cuda_t ex = 0., ey = 0., ez = 0.;
  int status = 0;
  m_sensor->ElectricField(x, y, z, ex, ey, ez, medium, status);

  // Sign change for electrons.
  if (ptype == Particle::Electron) {
    ex = -ex;
    ey = -ey;
    ez = -ez;
  }

#ifndef GPUOPTIMISE
  if (thread_idx == debug_electron)
    printf("GPU %d (A, line %d):   %.8f %.8f %.8f %.8f %.8f %.8f %.8f\n",
           thread_idx, __LINE__, x, y, z, en, ex, ey, ez);
#endif

  if (status != 0) {
    // Electron is not inside a drift medium.
    Update(raw_ptr_stack, particle_idx, x, y, z, t, en, kx, ky, kz, band);
    raw_ptr_stack.status[particle_idx] = StatusLeftDriftMedium;
    all_status_array[thread_idx] = -1;
    // GPUREMOVE: AddToEndPoints(*it, hole);
    return;
  }

  // Get the id number of the drift medium.
  auto id = medium->GetId();
  // Get the null-collision rate.
  // - TODO TN GPU: fLim never changes on the GPU - we don't update... so
  //   we can get this earlier on and not call this function
  double fLim = medium->GetElectronNullCollisionRate(band);
  if (fLim <= 0.) {
    // std::cerr << hdr << "Got null-collision rate <= 0.\n";
    return;
  }
  double fInv = 1. / fLim;
  // Trace the electron/hole.
  while (1) {
#ifndef GPUOPTIMISE
    if (thread_idx == debug_electron)
      printf("GPU %d (B, line %d):   %.8f %.8f %.8f %.8f %.8f %.8f %.8f\n",
             thread_idx, __LINE__, x, y, z, en, ex, ey, ez);
#endif
    bool isNullCollision = false;

    // Make sure the electron energy exceeds the transport cut.
    if (en < m_deltaCut) {
      Update(raw_ptr_stack, particle_idx, x, y, z, t, en, kx, ky, kz, band);
      raw_ptr_stack.status[particle_idx] = StatusBelowTransportCut;
      all_status_array[thread_idx] = -1;
      // GPUREMOVE: AddToEndPoints(*it, hole);
      ok = false;
      break;
    }

    /* GPUREMOVE: // Fill the energy distribution histogram.
    if (hole && m_histHoleEnergy) {
        m_histHoleEnergy->Fill(en);
    } else if (!hole && m_histElectronEnergy) {
        m_histElectronEnergy->Fill(en);
    }

    // Check if the electron is within the specified time window.
    if (m_hasTimeWindow && (t < m_tMin || t > m_tMax)) {
        Update(it, x, y, z, t, en, kx, ky, kz, band);
        (*it).status = StatusOutsideTimeWindow;
        AddToEndPoints(*it, hole);
        if (m_debug) PrintStatus(hdr, "left the time window", x, y, z, hole);
        ok = false;
        break;
    }*/

    /* GPUREMOVE
    if (medium->GetId() != id) {
        // Medium has changed.
        if (!medium->IsMicroscopic()) {
            // Electron/hole has left the microscopic drift medium.
            Update(raw_ptr_stack, thread_idx, x, y, z, t, en, kx, ky, kz, band);
            raw_ptr_stack.status[thread_idx] = StatusLeftDriftMedium;
            //GPUREMOVE: AddToEndPoints(*it, hole);
            ok = false;
            break;
        }
        id = medium->GetId();
        // Update the null-collision rate.
        fLim = medium->GetElectronNullCollisionRate(band);
        if (fLim <= 0.) {
            std::cerr << hdr << "Got null-collision rate <= 0.\n";
            return false;
        }
        fInv = 1. / fLim;
    }*/

    // Calculate the initial velocity vector
    const cuda_t vmag = c1 * sqrt(en);
    cuda_t vx = vmag * kx;
    cuda_t vy = vmag * ky;
    cuda_t vz = vmag * kz;
    const cuda_t a1 = vx * ex + vy * ey + vz * ez;
    const cuda_t a2 = c2 * (ex * ex + ey * ey + ez * ez);

    /* GPUREMOVE
    if (m_userHandleStep) {
        m_userHandleStep(x, y, z, t, en, kx, ky, kz, hole);
    }*/

    // Energy after the step.
    cuda_t en1 = en;
    // Determine the timestep.
    cuda_t dt = 0.;

    if (thread_idx == debug_electron)
      printf("GPU %d (C, line %d):   %.8f %.8f %.8f %.8f %.8f %.8f %.8f\n",
             thread_idx, __LINE__, x, y, z, en, ex, ey, ez);

    while (1) {
      // Sample the flight time.
      const cuda_t r = RndmUniformPosGPU();
      dt += -log(r) * fInv;
      // Calculate the energy after the proposed step.
      en1 = en + (a1 + a2 * dt) * dt;
      en1 = fmax(en1, SmallGPU);

      // Get the real collision rate at the updated energy.
      cuda_t fReal = medium->GetElectronCollisionRate(en1, band);
      /*GPUREMOVE
      if (fReal <= 0.) {
          printf("Got collision rate <= 0 at %f.\n", en1);
          return;
      }
      if (fReal > fLim) {
          // Real collision rate is higher than null-collision rate.
          dt += log(r) * fInv;
          // Increase the null collision rate and try again.
          printf("GPU: Increasing null-collision rate by 5%.\n");
          fLim *= 1.05;
          fInv = 1. / fLim;
          continue;
      }*/
      // Check for real or null collision.
      if (RndmUniformGPU() <= fReal * fInv) break;
      /* GPUREMOVE if (m_useNullCollisionSteps) {
          isNullCollision = true;
          break;
      }*/
    }
    ++nCollTemp;

    if (!ok) break;
    if (thread_idx == debug_electron)
      printf("GPU %d (D, line %d):   %.8f %.8f %.8f %.8f %.8f %.8f %.8f\n",
             thread_idx, __LINE__, x, y, z, en, ex, ey, ez);
    // Increase the collision counter.

    // Calculate the direction at the instant before the collision.
    const cuda_t b1 = sqrt(en / en1);
    const cuda_t b2 = 0.5 * c1 * dt / sqrt(en1);
    cuda_t kx1 = kx * b1 + ex * b2;
    cuda_t ky1 = ky * b1 + ey * b2;
    cuda_t kz1 = kz * b1 + ez * b2;

    // Calculate the step in coordinate space.
    const cuda_t b3 = dt * dt * c2;
    cuda_t x1 = x + vx * dt + ex * b3;
    cuda_t y1 = y + vy * dt + ey * b3;
    cuda_t z1 = z + vz * dt + ez * b3;
    cuda_t t1 = t + dt;

#ifndef GPUOPTIMISE
    if (thread_idx == debug_electron)
      printf("GPU %d (E, line %d):   %.8f %.8f %.8f %.8f %.8f %.8f %.8f\n",
             thread_idx, __LINE__, x, y, z, en, ex, ey, ez);
#endif
    // Get the electric field and medium at the proposed new position.
    m_sensor->ElectricField(x1, y1, z1, ex, ey, ez, medium, status);
    if (ptype == Particle::Electron) {
      ex = -ex;
      ey = -ey;
      ez = -ez;
    }

    // Check if the electron is still inside a drift medium/the drift area.
    if ((status != 0) || (!m_sensor->IsInArea(x1, y1, z1))) {
      // Try to terminate the drift line close to the boundary (endpoint
      // outside the drift medium/drift area) using iterative bisection.

      Terminate(x, y, z, t, x1, y1, z1, t1, m_sensor);
      if (doSignal) {
        const int q = (ptype == Particle::Hole) ? 1 : -1;
        // TODO GPU: This is set to false for now
        const bool useWeightingPotential = false;
        m_sensor->AddSignal(q, t, t1, x, y, z, x1, y1, z1,
                            integrateWeightingField, useWeightingPotential,
                            thread_idx);
      }
      Update(raw_ptr_stack, particle_idx, x1, y1, z1, t1, en, kx1, ky1, kz1,
             band);

      if (status != 0) {
        raw_ptr_stack.status[particle_idx] = StatusLeftDriftMedium;
        all_status_array[thread_idx] = -1;
      } else {
        raw_ptr_stack.status[particle_idx] = StatusLeftDriftArea;
        all_status_array[thread_idx] = -1;
      }
      // GPUREMOVE: AddToEndPoints(*it, hole);
      ok = false;
      break;
    }

    // Check if the electron/hole has crossed a wire.
    /* GPUREMOVE:
    cuda_t xc = x, yc = y, zc = z;
    cuda_t rc = 0.;

    if (m_sensor->IsWireCrossed(x, y, z, x1, y1, z1,
                                xc, yc, zc, false, rc)) {
        const double dc = Mag(xc - x, yc - y, zc - z);
        const double tc = t + dt * dc / Mag(dx, dy, dz);
        // If switched on, calculated the induced signal over this step.
        if (doSignal) {
        const int q = hole ? 1 : -1;
        m_sensor->AddSignal(q, t, tc, x, y, z, xc, yc, zc,
                            m_integrateWeightingField,
                            m_useWeightingPotential);
        }
        Update(it, xc, yc, zc, tc, en, kx1, ky1, kz1, band);
        (*it).status = StatusLeftDriftMedium;
        AddToEndPoints(*it, hole);
        ok = false;
        if (m_debug) PrintStatus(hdr, "hit a wire", x, y, z, hole);
        break;
    }*/

    // If switched on, calculate the induced signal.
    if (doSignal) {
      const int q = (ptype == Particle::Hole) ? 1 : -1;
      // TODO GPU: This is set to false for now
      const bool useWeightingPotential = false;
      m_sensor->AddSignal(q, t, t + dt, x, y, z, x1, y1, z1,
                          integrateWeightingField, useWeightingPotential,
                          thread_idx);
    }

    // Update the coordinates.
    x = x1;
    y = y1;
    z = z1;
    t = t1;

    if (isNullCollision) {
      en = en1;
      kx = kx1;
      ky = ky1;
      kz = kz1;
      continue;
    }

    // Get the collision type and parameters.
    int cstype = 0;
    int level = 0;
    int ndxc = 0;
    medium->ElectronCollision(en1, cstype, level, en, kx1, ky1, kz1,
                              secondaries_type, secondaries_energy,
                              num_secondaries, ndxc, band);
    /* GPUREMOVE:
    // If activated, histogram the distance with respect to the
    // last collision.
    if (m_histDistance && !m_distanceHistogramType.empty()) {
        for (const auto& htype : m_distanceHistogramType) {
        if (htype != cstype) continue;
        switch (m_distanceOption) {
            case 'x':
            m_histDistance->Fill((*it).xLast - x);
            break;
            case 'y':
            m_histDistance->Fill((*it).yLast - y);
            break;
            case 'z':
            m_histDistance->Fill((*it).zLast - z);
            break;
            case 'r':
            m_histDistance->Fill(Mag((*it).xLast - x,
                                        (*it).yLast - y,
                                        (*it).zLast - z));
            break;
        }
        (*it).xLast = x;
        (*it).yLast = y;
        (*it).zLast = z;
        break;
        }
    }

    if (m_userHandleCollision) {
        m_userHandleCollision(x, y, z, t, cstype, level, medium, en1,
                            en, kx, ky, kz, kx1, ky1, kz1);
    }*/

    switch (cstype) {
      // Elastic collision
      case ElectronCollisionTypeElastic:
        break;
      // Ionising collision
      case ElectronCollisionTypeIonisation:
        /* GPUREMOVE
            if (m_viewer && m_plotIonisations) {
                m_viewer->AddIonisationMarker(x, y, z);
            }
            if (m_userHandleIonisation) {
                m_userHandleIonisation(x, y, z, t, cstype, level, medium);
            }
            for (const auto& secondary : secondaries) {
                if (secondary.first == Particle::Electron) {
                const cuda_t esec = std::max(secondary.second, Small);
                if (m_histSecondary) m_histSecondary->Fill(esec);
                // Add the secondary electron to the stack.
                AddToStack(x, y, z, t, esec, Particle::Electron, stackNew);
                } else if (secondary.first == Particle::Hole) {
                const cuda_t esec = std::max(secondary.second, Small);
                // Add the secondary hole to the stack.
                AddToStack(x, y, z, t, esec, Particle::Ion, stackNew);
                } else if (secondary.first == Particle::Ion) {
                  AddToStack(x, y, z, t, 0, Particle::Ion, stackNew);
                }
            }
            secondaries.clear();*/

        for (int k = 0; k < num_secondaries; k++) {
          if (secondaries_type[k] == Particle::Electron) {
            const cuda_t esec = fmax(secondaries_energy[k], SmallGPU);

            // Add the secondary electron to the stack.
            AddToStack(raw_ptr_stack_new, num_new_particles, thread_idx,
                       new_status_array, x, y, z, t, esec, Particle::Electron);

          } else if (secondaries_type[k] == Particle::Hole) {
            const cuda_t esec = fmax(secondaries_energy[k], SmallGPU);

            // Add the secondary hole to the stack.
            printf("ERROR: HOLE CREATEAD!\n");
            // GPUAddToStack(x, y, z, t, esec, true, stackNew, new_stack_idx);
          }
        }

        num_secondaries = 0;

        break;
      // Attachment
      case ElectronCollisionTypeAttachment:
        /* GPUREMOVE
            if (m_viewer && m_plotAttachments) {
                m_viewer->AddAttachmentMarker(x, y, z);
            }
            if (m_userHandleAttachment) {
                m_userHandleAttachment(x, y, z, t, cstype, level, medium);
            }*/
        Update(raw_ptr_stack, particle_idx, x1, y1, z1, t1, en, kx1, ky1, kz1,
               band);
        raw_ptr_stack.status[particle_idx] = StatusAttached;
        all_status_array[thread_idx] = -1;
        ok = false;
        break;
      // Inelastic collision
      case ElectronCollisionTypeInelastic:
        /*GPUREMOVEif (m_userHandleInelastic) {
            m_userHandleInelastic(x, y, z, t, cstype, level, medium);
        }*/
        break;
      // Excitation
      case ElectronCollisionTypeExcitation:
        if (ndxc <= 0) break;
        /*GPUREMOVE
            if (m_viewer && m_plotExcitations) {
                m_viewer->AddExcitationMarker(x, y, z);
            }
            if (m_userHandleInelastic) {
                m_userHandleInelastic(x, y, z, t, cstype, level, medium);
            }
            if (ndxc <= 0) break;
            // Get the electrons/photons produced in the deexcitation cascade.
            stackPhotons.clear();
            for (int j = ndxc; j--;) {
                double tdx = 0., sdx = 0., edx = 0.;
                int typedx = 0;
                if (!medium->GetDeexcitationProduct(j, tdx, sdx, typedx, edx)) {
                std::cerr << hdr << "Cannot retrieve deexcitation product " << j
                            << "/" << ndxc << ".\n";
                break;
                }
                if (typedx == DxcProdTypeElectron) {
                // Penning ionisation
                double xp = x, yp = y, zp = z;
                if (sdx > Small) {
                    // Randomise the point of creation.
                    double dxp = 0., dyp = 0., dzp = 0.;
                    RndmDirection(dxp, dyp, dzp);
                    xp += sdx * dxp;
                    yp += sdx * dyp;
                    zp += sdx * dzp;
                }
                // Get the electric field and medium at this location.
                Medium* med = nullptr;
                double fx = 0., fy = 0., fz = 0.;
                m_sensor->ElectricField(xp, yp, zp, fx, fy, fz, med, status);
                // Check if this location is inside a drift medium/area.
                if (status != 0 || !m_sensor->IsInArea(xp, yp, zp)) continue;
                // Make sure we haven't jumped across a wire.
                if (m_sensor->IsWireCrossed(x, y, z, xp, yp, zp, xc, yc, zc,
                                            false, rc)) {
                    continue;
                }
                if (m_userHandleIonisation) {
                    m_userHandleIonisation(xp, yp, zp, t, cstype, level,
           medium);
                }
                // Add the Penning electron to the list.
                const double tp = t + tdx;
                const double ep = std::max(edx, Small);
                AddToStack(xp, yp, zp, tp, ep, Particle::Electron, stackNew);
                AddToStack(xp, yp, zp, tp, 0, Particle::Ion, stackNew);
                } else if (typedx == DxcProdTypePhoton && m_usePhotons &&
                            edx > m_gammaCut) {
                // Radiative de-excitation
                stackPhotons.emplace_back(std::make_pair(t + tdx, edx));
                }
            }

            // Transport the photons (if any)
            if (aval) {
                for (const auto& ph : stackPhotons) {
                TransportPhoton(x, y, z, ph.first, ph.second, stackNew);
                }
            }*/
        break;
      // Super-elastic collision
      case ElectronCollisionTypeSuperelastic:
      // Virtual/null collision
      case ElectronCollisionTypeVirtual:
      // Acoustic phonon scattering (intravalley)
      case ElectronCollisionTypeAcousticPhonon:
      // Optical phonon scattering (intravalley)
      case ElectronCollisionTypeOpticalPhonon:
      // Intervalley scattering (phonon assisted)
      case ElectronCollisionTypeIntervalleyG:
      case ElectronCollisionTypeIntervalleyF:
      case ElectronCollisionTypeInterbandXL:
      case ElectronCollisionTypeInterbandXG:
      case ElectronCollisionTypeInterbandLG:
      // Coulomb scattering
      case ElectronCollisionTypeImpurity:
        break;
      default:
        printf("Unknown collision type.\n");
        ok = false;
        break;
    }

    // Continue with the next electron/hole?
    // GPUREMOVE m_nCollSKip
    if (!ok || nCollTemp > 100 ||
                cstype == ElectronCollisionTypeIonisation ||
                cstype == ElectronCollisionTypeExcitation ||
                cstype == ElectronCollisionTypeAttachment
                /*GPUREMOVE||
                (m_plotExcitations && cstype == ElectronCollisionTypeExcitation) ||
                (m_plotAttachments && cstype == ElectronCollisionTypeAttachment)*/) {
      break;
    }
    kx = kx1;
    ky = ky1;
    kz = kz1;
  }

  if (!ok) return;

  // Update the stack.
  Update(raw_ptr_stack, particle_idx, x, y, z, t, en, kx, ky, kz, band);
  /* GPUREMOVE:
  // Add a new point to the drift line (if enabled).
  if (m_useDriftLines) {
      point newPoint;
      newPoint.x = x;
      newPoint.y = y;
      newPoint.z = z;
      newPoint.t = t;
      (*it).driftLine.push_back(std::move(newPoint));
  }
  */
}

bool AvalancheMicroscopicGPU::transportParticleStack(
    const bool aval, AvalancheMicroscopic *aval_ptr, int id, double fLim,
    double fInv, bool useBfield, bool sc, int debug_electron) {
  // check we have enough space
  if (stackOldGPU.stack_size > MAXPARTICLES) {
    std::cout << "ERROR:  particle stack overflow. Please increase "
                 "MAXPARTICLES and recompile."
              << std::endl;
    return false;
  }

  // Numerical prefactors in equation of motion
  const double c1 = SpeedOfLight * sqrt(2. / ElectronMass);
  const double c2 = 0.25 * c1 * c1;

  // Send off the threads to transport each particle
  TransportElectron<<<1 + numActiveParticles / 256, 256>>>(
      stackOldGPU, stackNewGPU, activeIndexArray, newIndexArray, m_sensor,
      aval_ptr->m_deltaCut, id, c1, c2, fLim, fInv, numActiveParticles,
      aval_ptr->m_doSignal, aval_ptr->m_integrateWeightingField,
      debug_electron);
  cudaDeviceSynchronize();

  return true;
}

}  // namespace Garfield
