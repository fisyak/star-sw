#ifndef G_MEDIUMGPU_H
#define G_MEDIUMGPU_H

#include "GPUInterface.hh"
#include "Garfield/MagboltzInterface.hh"

namespace Garfield {

enum class Particle;

class MediumGPU {
 public:
  /// Return the id number of the class instance.
  __device__ int GetId() const { return m_id; }
  /// Is charge carrier transport enabled in this medium?
  __device__ bool IsDriftable() const { return m_driftable; }
  /// Does the medium have electron scattering rates?
  __device__ bool IsMicroscopic() const { return m_microscopic; }
  __device__ cuda_t GetElectronCollisionRate(const cuda_t e, const int band);

  __device__ bool ElectronCollision(const cuda_t e, int& type, int& level,
                                    cuda_t& e1, cuda_t& dx, cuda_t& dy,
                                    cuda_t& dz, Particle* secondaries_type,
                                    cuda_t* secondaries_energy,
                                    int& num_secondaries, int& ndxc, int& band);
  // Id number
  int m_id;

  // Transport flags
  bool m_driftable{false};
  bool m_microscopic{false};
  bool m_ionisable{false};
#include "MediumMagboltzGPU.h"

  friend class MediumGas;
  friend class MediumMagboltz;

  // enum to mimic polymorphism
  enum class MediumType { Medium = 0, MediumGas, MediumMagboltz };

  MediumType m_MediumType{MediumType::Medium};
};

}  // namespace Garfield
#endif
