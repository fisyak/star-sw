#ifndef G_SENSORGPU_H
#define G_SENSORGPU_H

#include <cstddef>

#include "ComponentGPU.h"
#include "MediumGPU.h"

namespace Garfield {

class SensorGPU {
 public:
  /// Get the drift field at (x, y, z).
  __device__ void ElectricField(const double x, const double y, const double z,
                                double& ex, double& ey, double& ez,
                                MediumGPU*& medium, int& status) const;
  /// Check if a point is inside the user area.
  __device__ bool IsInArea(const double x, const double y,
                           const double z) const;
  /// Add the signal on the GPU
  __device__ void AddSignal(const double q, const double t0, const double t1,
                            const double x0, const double y0, const double z0,
                            const double x1, const double y1, const double z1,
                            const bool integrateWeightingField,
                            const bool useWeightingPotential,
                            const int particle_idx);
  /// Components
  ComponentGPU** m_components{nullptr};
  std::size_t m_numComponents{0};
  friend class Sensor;

  struct ElectrodeGPU {
    ComponentGPU* comp{nullptr};
    int label{0};
    double* signal{nullptr};
  };

  ElectrodeGPU* m_electrodes{nullptr};
  std::size_t m_numElectrodes{0};

  // Time window for signals
  double m_tStart{0.};
  double m_tStep{10.};
  std::size_t m_nTimeBins{200};
  std::size_t m_nEvents{0};

  // User bounding box
  double m_xMinUser{0.};
  double m_yMinUser{0.};
  double m_zMinUser{0.};
  double m_xMaxUser{0.};
  double m_yMaxUser{0.};
  double m_zMaxUser{0.};
  bool m_hasUserArea{false};

  __device__ void FillBin(ElectrodeGPU& electrode, const std::size_t bin,
                          const double signal, const bool electron,
                          const bool delayed, const int particle_idx);
};

}  // namespace Garfield

#endif
