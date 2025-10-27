#ifndef G_AVALANCHMICROSCOPICGPU_H
#define G_AVALANCHMICROSCOPICGPU_H

#include <cstddef>
#include <vector>

#include "Garfield/AvalancheMicroscopicTypes.hh"

namespace Garfield {

class RandomEngineGPU;
class SensorGPU;
class AvalancheMicroscopic;

class AvalancheMicroscopicGPU {
 public:
  /// Constructor
  AvalancheMicroscopicGPU();
  /// Destructor
  ~AvalancheMicroscopicGPU();

  // make a struct of arrays rather than array of structs
  struct ParticleStack {
    double* x{nullptr};
    double* y{nullptr};
    double* z{nullptr};
    double* t{nullptr};
    int* status{nullptr};
    double* energy{nullptr};
    int* band{nullptr};
    double* kx{nullptr};
    double* ky{nullptr};
    double* kz{nullptr};
    Particle* ptype{nullptr};
    double* x0{nullptr};
    double* y0{nullptr};
    double* z0{nullptr};
    double* t0{nullptr};
    double* e0{nullptr};
    std::size_t stack_size{0};
  };

  // Stores *all* electrons
  ParticleStack stackOldGPU;
  ParticleStack stackNewGPU;
  ParticleStack stackTransfer;

  // Array to store the index of active particles (into stackOldGPU)
  // Therefore, for each thread, use thread_idx to look up in this array for the
  // idx in stackOld of the active particle to process if this terminates,
  // overwrite with -1. During stack processing, use thrust::sort on this to get
  // the active particles and then add any new ones This array should only be a
  // maximum of the number of threads stackOld has to be big enough for *all*
  // particles as they *won't be removed*
  int* activeIndexArray{nullptr};
  int* newIndexArray{nullptr};
  int numActiveParticles{0};
  std::size_t m_nElectrons{0};

  enum class TransferType { HostToDevice = 0, DeviceToDevice, DeviceToHost };

  double InitialiseGPUParticleStack(ParticleStack& stack, std::size_t num);
  void FreeGPUParticleStack(ParticleStack& stack);
  void InitialiseCPUParticleStack(ParticleStack& stack, std::size_t num);
  void FreeCPUParticleStack(ParticleStack& stack);
  void TransferStackFromCPUToGPU(std::vector<Seed>& particles);
  void TransferStackFromGPUToCPU(std::vector<Electron>& stack, bool end_points);
  void TransferClassInternalInfo(AvalancheMicroscopic* src);
  void transferParticleStack(ParticleStack dest, std::size_t offset,
                             ParticleStack source, std::size_t num,
                             TransferType type, bool init_dest = false);
  std::size_t processParticleStack(std::size_t& num_active,
                                   std::size_t& num_new);
  bool transportParticleStack(const bool aval, AvalancheMicroscopic* aval_ptr,
                              int id, double fLim, double fInv, bool useBfield,
                              bool sc, int debug_electron = -1);
  void SetCUDADevice(int dev);

  unsigned long memUsageStack{0};
  unsigned long memUsageSensor{0};
  unsigned long memRNG{0};

  // Internal GPU transfer classes
  SensorGPU* m_sensor{nullptr};
  RandomEngineGPU* m_randomEngine{nullptr};
};
}  // namespace Garfield

#endif
