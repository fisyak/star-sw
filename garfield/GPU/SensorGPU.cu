#include "GPUFunctions.h"
#include "Garfield/ComponentFieldMap.hh"
#include "Garfield/Sensor.hh"
#include "SensorGPU.h"
namespace Garfield {
// https://github.com/FLAMEGPU/FLAMEGPU2/issues/847
#if __CUDA_ARCH__ < 600
__device__ double atomicAdd(double* address, double val) {
  unsigned long long int* address_as_ull = (unsigned long long int*)address;
  unsigned long long int old = *address_as_ull, assumed;

  do {
    assumed = old;
    old = atomicCAS(address_as_ull, assumed,
                    __double_as_longlong(val + __longlong_as_double(assumed)));

    // Note: uses integer comparison to avoid hang in case of NaN (since NaN !=
    // NaN)
  } while (assumed != old);

  return __longlong_as_double(old);
}
#endif

__device__ void SensorGPU::ElectricField(const double x, const double y,
                                         const double z, double& ex, double& ey,
                                         double& ez, MediumGPU*& medium,
                                         int& status) const {
  ex = ey = ez = 0.;
  status = -10;
  medium = nullptr;
  double fx = 0., fy = 0., fz = 0.;
  MediumGPU* med = nullptr;
  int stat = 0;
  // Add up electric field contributions from all components.
  for (int ic = 0; ic < m_numComponents; ic++) {
    ComponentGPU* component{m_components[ic]};
    component->ElectricField(x, y, z, fx, fy, fz, med, stat);
    if (status != 0) {
      status = stat;
      medium = med;
    }
    if (stat == 0) {
      ex += fx;
      ey += fy;
      ez += fz;
    }
  }
}

__device__ bool SensorGPU::IsInArea(const double x, const double y,
                                    const double z) const {
  if (x >= m_xMinUser && x <= m_xMaxUser && y >= m_yMinUser &&
      y <= m_yMaxUser && z >= m_zMinUser && z <= m_zMaxUser) {
    return true;
  }
  return false;
}

double Sensor::CreateGPUTransferObject(SensorGPU*& sensor_gpu) {
  // create main sensor GPU class
  checkCudaErrors(cudaMallocManaged(&sensor_gpu, sizeof(SensorGPU)));
  double alloc{sizeof(SensorGPU)};

  // transfer sizes
  sensor_gpu->m_xMinUser = m_xMinUser;
  sensor_gpu->m_yMinUser = m_yMinUser;
  sensor_gpu->m_zMinUser = m_zMinUser;
  sensor_gpu->m_xMaxUser = m_xMaxUser;
  sensor_gpu->m_yMaxUser = m_yMaxUser;
  sensor_gpu->m_zMaxUser = m_zMaxUser;

  // Signals
  sensor_gpu->m_tStart = m_tStart;
  sensor_gpu->m_tStep = m_tStep;
  sensor_gpu->m_nTimeBins = m_nTimeBins;
  sensor_gpu->m_nEvents = m_nEvents;

  // TN: b332e924 introduced a change in m_components. It now is a vector
  // of std::pair<Component*, bool>, which allows the option to disable
  // components. This is NOT supported on the GPU for now, so I make a new
  // vector just of Component* and cross my fingers this will still work
  std::vector<Component*> components{};
  for (const auto& cmp : m_components) {
    components.push_back(std::get<0>(cmp));
  }

  // create arrays
  alloc += CreateGPUObjectArrayFromVector<Component*, ComponentGPU**>(
      components, sensor_gpu->m_numComponents, sensor_gpu->m_components);

  // We now have an array of components
  if (m_electrodes.size() > 0) {
    sensor_gpu->m_numElectrodes = m_electrodes.size();
    checkCudaErrors(cudaMallocManaged(
        &(sensor_gpu->m_electrodes),
        sizeof(SensorGPU::ElectrodeGPU) * m_electrodes.size()));
    // Allocate memory for storing signals
    for (size_t i = 0; i < m_electrodes.size(); i++) {
      checkCudaErrors(cudaMallocManaged(&sensor_gpu->m_electrodes[i].signal,
                                        sizeof(double) * m_nTimeBins));
      std::fill(sensor_gpu->m_electrodes[i].signal,
                sensor_gpu->m_electrodes[i].signal + m_nTimeBins, 0);
      // So here I need to find which component we are using and the label
      // of the wpot within that component
      for (size_t j = 0; j < m_components.size(); j++) {
        if (std::get<0>(m_components[j]) == m_electrodes[i].comp) {
          // Found that component j == electrode.component i
          // Set the GPU to use the index
          sensor_gpu->m_electrodes[i].comp = sensor_gpu->m_components[j];
          break;
        }
      }
      // Find the correct label
      auto label = m_electrodes[i].label;
      int label_index = 0;
      // m_wpot is a map of string to
      // static_cast to ComponentFieldMap here is perhaps risky
      // Need to see if this affects other types of field map
      for (const auto& wpot :
           static_cast<ComponentFieldMap*>(m_electrodes[i].comp)
               ->GetWeightingPotentials()) {
        if (label == wpot.first) {
          // We have found a match
          sensor_gpu->m_electrodes[i].label = label_index;
          break;
        }
        label_index++;
      }
    }
    alloc += sizeof(double) * m_nTimeBins * m_electrodes.size();
  }

  return alloc;
}

__device__ void SensorGPU::AddSignal(
    const double q, const double t0, const double t1, const double x0,
    const double y0, const double z0, const double x1, const double y1,
    const double z1, const bool integrateWeightingField,
    const bool useWeightingPotential, const int particle_idx) {
  // Get the time bin.
  if (t0 < m_tStart) {
    printf("Time %f out of range.\n", t0);
    return;
  }
  const double dt = t1 - t0;
  if (dt < SmallGPU) {
    // This is protected by if (m_debug) in the CPU code, so we'll just get rid
    // of it for now for consistency with other parts of the GPU code
    // printf("Time step too small.\n");
    return;
  }
  const int bin = int((t0 - m_tStart) / m_tStep);

  // Check if the starting time is outside the range
  if (bin < 0 || bin >= (int)m_nTimeBins) {
    printf("Bin %d out of range.\n", bin);
    return;
  }

  const bool electron = q < 0;
  const double dx = x1 - x0;
  const double dy = y1 - y0;
  const double dz = z1 - z0;
  const double invdt = 1. / dt;
  const double vx = dx * invdt;
  const double vy = dy * invdt;
  const double vz = dz * invdt;

  // Abscissae and weights for 6-point Gaussian integration
  constexpr size_t nG = 6;
  // Locations and weights for 6-point Gaussian integration
  constexpr double tG[nG] = {-0.932469514203152028, -0.661209386466264514,
                             -0.238619186083196909, 0.238619186083196909,
                             0.661209386466264514,  0.932469514203152028};
  constexpr double wG[nG] = {0.171324492379170345, 0.360761573048138608,
                             0.467913934572691047, 0.467913934572691047,
                             0.360761573048138608, 0.171324492379170345};
  double sG[6];
  for (size_t i = 0; i < nG; ++i) sG[i] = 0.5 * (1. + tG[i]);

  for (int i = 0; i < m_numElectrodes; i++) {
    const size_t lbl = m_electrodes[i].label;

    double wx = 0., wy = 0., wz = 0.;
    // Calculate the weighting field for this electrode.
    if (integrateWeightingField) {
      for (std::size_t j = 0; j < nG; ++j) {
        const double x = x0 + sG[j] * dx;
        const double y = y0 + sG[j] * dy;
        const double z = z0 + sG[j] * dz;
        double fx = 0., fy = 0., fz = 0.;
        m_electrodes[i].comp->WeightingField(x, y, z, fx, fy, fz, lbl);
        wx += wG[j] * fx;
        wy += wG[j] * fy;
        wz += wG[j] * fz;
      }
      wx *= 0.5;
      wy *= 0.5;
      wz *= 0.5;
    } else {
      m_electrodes[i].comp->WeightingField(x0 + 0.5 * dx, y0 + 0.5 * dy,
                                           z0 + 0.5 * dz, wx, wy, wz, lbl);
    }
    // Calculate the induced current.
    double current = -q * (wx * vx + wy * vy + wz * vz);

    double delta = m_tStart + (bin + 1) * m_tStep - t0;
    // Check if the provided timestep extends over more than one time bin
    if (dt > delta) {
      FillBin(m_electrodes[i], bin, current * delta, electron, false,
              particle_idx);
      delta = dt - delta;
      std::size_t j = 1;
      while (delta > m_tStep && bin + j < m_nTimeBins) {
        FillBin(m_electrodes[i], bin + j, current * m_tStep, electron, false,
                particle_idx);
        delta -= m_tStep;
        ++j;
      }
      if (bin + j < m_nTimeBins) {
        FillBin(m_electrodes[i], bin + j, current * delta, electron, false,
                particle_idx);
      }
    } else {
      FillBin(m_electrodes[i], bin, current * dt, electron, false,
              particle_idx);
    }

  }  // End of loop over electrodes

  if (m_nEvents <= 0) m_nEvents = 1;

  // Delayed signal not yet implemented for GPU
  // if (!m_delayedSignal) return;

  return;
}

__device__ void SensorGPU::FillBin(ElectrodeGPU& electrode,
                                   const std::size_t bin, const double signal,
                                   const bool electron, const bool delayed,
                                   const int particle_idx) {
#if __CUDA_ARCH__ < 600
  Garfield::atomicAdd(&electrode.signal[bin], signal);
#else
  atomicAdd(&electrode.signal[bin], signal);
#endif
  /*GPUREMOVE: if (electron) {
    electrode.electronsignal[bin] += signal;
    if (delayed) electrode.delayedElectronSignal[bin] += signal;
  } else {
    electrode.ionsignal[bin] += signal;
    if (delayed) electrode.delayedIonSignal[bin] += signal;
  }*/
}

void Sensor::TransferGPUElectrodeSignals(SensorGPU*& sensor_gpu) {
  // Transfer signals from the SensorGPU object to this one
  int elec_id = 0;
  for (auto& electrode : m_electrodes) {
    for (size_t bin = 0; bin < m_nTimeBins; bin++) {
      electrode.signal[bin] = sensor_gpu->m_electrodes[elec_id].signal[bin];
      // For want of a better place to do it, after transferring the signal to
      // the CPU we will reset the GPU signal to 0
      sensor_gpu->m_electrodes[elec_id].signal[bin] = 0.;
    }
    elec_id++;
  }
  if (m_nEvents == 0) {
    m_nEvents = 1;
  }
}

}  // namespace Garfield
