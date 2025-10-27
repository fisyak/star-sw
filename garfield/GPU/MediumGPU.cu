#include <cstddef>

#include "GPUFunctions.h"
#include "Garfield/GarfieldConstants.hh"
#include "Garfield/MediumMagboltz.hh"
#include "MediumGPU.h"
#include "RandomGPU.h"

namespace Garfield {

// THIS SHOULD BE IN MEDIUM_MAGBOLTZ_GPU
/////////////////////////////////////
__device__ double MediumGPU::GetElectronNullCollisionRate(const int /*band*/) {
  // TODO GPU: We don't update the collision rates table on the GPU
  // If necessary, update the collision rates table.
  // if (!Update()) return 0.;

  return m_cfNull;
}

__device__ double MediumGPU::GetElectronCollisionRate__MediumMagboltz(
    const double e, const int /*band*/) {
  // #ifndef __GPUCOMPILE__
  //  Check if the electron energy is within the currently set range.
  // if (e <= 0.) {
  //   std::cerr << m_className << "::GetElectronCollisionRate: Invalid
  //   energy.\n"; return m_cfTot[0];
  // }
  // if (e > m_eMax) {
  //   std::cerr << m_className << "::GetElectronCollisionRate:\n    Rate at "
  //   << e
  //             << " eV is not included in the current table.\n    "
  //             << "Increasing energy range to " << 1.05 * e << " eV.\n";
  //   SetMaxElectronEnergy(1.05 * e);
  // }

  // If necessary, update the collision rates table.
  // if (!Update()) return 0.;
  // #endif

  // Get the energy interval.
  if (e < m_eHigh) {
    // Linear binning
    return m_cfTot[int(e * m_eStepInv)];
  }

  // Logarithmic binning
  const double eLog = log(e);
  int iE = int((eLog - m_eHighLog) / m_lnStep);
  // Calculate the collision rate by log-log interpolation.
  const double fmax = m_cfTotLog[iE];
  const cuda_t fmin =
      iE == 0 ? log(m_cfTot[m_numcfTot - 1]) : m_cfTotLog[iE - 1];
  const double emin = m_eHighLog + iE * m_lnStep;
  const double f = fmin + (eLog - emin) * (fmax - fmin) / m_lnStep;
  return exp(f);
}

__device__ bool MediumGPU::ElectronCollision(
    const cuda_t e, int& type, int& level, double& e1, double& dx, double& dy,
    double& dz, Particle* secondaries_type, cuda_t* secondaries_energy,
    int& num_secondaries, int& ndxc, int& band) {
  band = 0;
  if (e <= 0.) {
    printf("MediumGPU::ElectronCollision: Invalid energy.\n");
    return false;
  }
  // Check if the electron energy is within the currently set range.
  if (e > m_eMax) {
    printf(
        "MediumGPU::GetElectronCollision:\n    Provided energy (%f"
        " eV) exceeds current energy range.\n"
        "    Increasing energy range to %f eV.\n",
        e, 1.05 * e);
    printf("******** NOT IMPLEMENTED YET ********");
    // TODO GPU SetMaxElectronEnergy(1.05 * e);
  }
  // TODO GPU If necessary, update the collision rates table.
  // if (!Update()) return false;
  // secondaries.clear();

  double angCut = 1.;
  double angPar = 0.5;

  if (e < m_eHigh) {
    // Linear binning
    // Get the energy interval.
    const int iE = int(e * m_eStepInv);

    // Sample the scattering process.
    const double r = RndmUniformGPU();
    level = 0;
    if (r > m_cf[iE][0]) {
      int iLow = 0;
      int iUp = m_nTerms - 1;
      while (iUp - iLow > 1) {
        int iMid = (iLow + iUp) >> 1;
        if (r < m_cf[iE][iMid]) {
          iUp = iMid;
        } else {
          iLow = iMid;
        }
      }
      level = iUp;
    }
    // Get the angular distribution parameters.
    angCut = m_scatCut[iE][level];
    angPar = m_scatPar[iE][level];
  } else {
    // Logarithmic binning
    // Get the energy interval.
    int var = int(log(e / m_eHigh) / m_lnStep);
    int tmp1 = var > 0 ? var : 0;
    int tmp2 = tmp1 < nEnergyStepsLog - 1 ? tmp1 : nEnergyStepsLog - 1;
    const int iE = tmp2;
    // Sample the scattering process.
    const double r = RndmUniformGPU();
    level = 0;
    if (r > m_cfLog[iE][0]) {
      int iLow = 0;
      int iUp = m_nTerms - 1;
      while (iUp - iLow > 1) {
        int iMid = (iLow + iUp) >> 1;
        if (r < m_cfLog[iE][iMid]) {
          iUp = iMid;
        } else {
          iLow = iMid;
        }
      }
      level = iUp;
    }
    // Get the angular distribution parameters.
    angCut = m_scatCutLog[iE][level];
    angPar = m_scatParLog[iE][level];
  }

  // Extract the collision type.
  type = m_csType[level] % nCsTypes;
  const int igas = int(m_csType[level] / nCsTypes);
  // TODO GPU ? Increase the collision counters.
  //++m_nCollisions[type];
  //++m_nCollisionsDetailed[level];

  // Get the energy loss for this process.
  double loss = m_energyLoss[level];

  if (type == ElectronCollisionTypeVirtual) return true;

  if (type == ElectronCollisionTypeIonisation) {
    // Sample the secondary electron energy according to
    // the Opal-Beaty-Peterson parameterisation.
    double esec = 0.;
    if (e < loss) loss = e - 0.0001;
    if (m_useOpalBeaty) {
      // Get the splitting parameter.
      const double w = m_wOpalBeaty[level];
      esec = w * tan(RndmUniformGPU() * atan(0.5 * (e - loss) / w));
      // Rescaling (SST)
      // esec = w * pow(esec / w, 0.9524);
    }
    // TODO GPU ??
    /*else if (m_useGreenSawada) {
      const double gs = m_parGreenSawada[igas][0];
      const double gb = m_parGreenSawada[igas][1];
      const double w = gs * e / (e + gb);
      const double ts = m_parGreenSawada[igas][2];
      const double ta = m_parGreenSawada[igas][3];
      const double tb = m_parGreenSawada[igas][4];
      const double esec0 = ts - ta / (e + tb);
      const double r = RndmUniform();
      esec = esec0 + w * tan((r - 1.) * atan(esec0 / w) +
                             r * atan((0.5 * (e - loss) - esec0) / w));
    } else {
      esec = RndmUniform() * (e - loss);
    }*/
    if (esec <= 0) esec = Small;
    loss += esec;

    // Add the secondary electron.
    secondaries_type[num_secondaries] = Particle::Electron;
    secondaries_energy[num_secondaries++] = esec;
    // Add the ion
    secondaries_type[num_secondaries] = Particle::Ion;
    secondaries_energy[num_secondaries++] = 0;

    bool fluorescence = false;
    if (m_yFluorescence[level] > Small) {
      if (RndmUniformGPU() < m_yFluorescence[level]) fluorescence = true;
    }

    // Add Auger and photo electrons (if any).
    if (fluorescence) {
      if (m_nAuger2[level] > 0) {
        const double eav = m_eAuger2[level] / m_nAuger2[level];
        for (std::size_t i = 0; i < m_nAuger2[level]; ++i) {
          secondaries_type[num_secondaries] = Particle::Electron;
          secondaries_energy[num_secondaries++] = eav;
        }
      }
      if (m_nFluorescence[level] > 0) {
        const double eav = m_eFluorescence[level] / m_nFluorescence[level];
        for (std::size_t i = 0; i < m_nFluorescence[level]; ++i) {
          secondaries_type[num_secondaries] = Particle::Electron;
          secondaries_energy[num_secondaries++] = eav;
        }
      }
    } else if (m_nAuger1[level] > 0) {
      const double eav = m_eAuger1[level] / m_nAuger1[level];
      for (std::size_t i = 0; i < m_nAuger1[level]; ++i) {
        secondaries_type[num_secondaries] = Particle::Electron;
        secondaries_energy[num_secondaries++] = eav;
      }
    }
  }
  // TODO GPU ???
  /*else if (type == ElectronCollisionTypeExcitation) {
    // Follow the de-excitation cascade (if switched on).
    if (m_useDeexcitation && m_iDeexcitation[level] >= 0) {
      int fLevel = 0;
      ComputeDeexcitationInternal(m_iDeexcitation[level], fLevel, secondaries);
    } else if (m_usePenning) {
      // Simplified treatment of Penning ionisation.
      // If the energy threshold of this level exceeds the
      // ionisation potential of one of the gases,
      // create a new electron (with probability rPenning).
      if (m_debug) {
        std::cout << m_className << "::ElectronCollision:\n"
                  << "    Level: " << level << "\n"
                  << "    Ionization potential: " << m_minIonPot << "\n"
                  << "    Excitation energy: " << loss * m_rgas[igas] << "\n"
                  << "    Penning probability: " << m_rPenning[level] << "\n";
      }
      if (loss * m_rgas[igas] > m_minIonPot &&
          RndmUniform() < m_rPenning[level]) {
        // The energy of the secondary electron is assumed to be given by
        // the difference of excitation and ionisation threshold.
        double esec = loss * m_rgas[igas] - m_minIonPot;
        if (esec <= 0) esec = Small;
        // Add the secondary electron to the list.
        Secondary secondary;
        secondary.type = Particle::Electron;
        secondary.energy = esec;
        if (m_lambdaPenning[level] > Small) {
          // Uniform distribution within a sphere of radius lambda
          secondary.distance =
              m_lambdaPenning[level] * std::cbrt(RndmUniformPos());
        }
        secondaries.push_back(std::move(secondary));
        ++m_nPenning;
      }
    }
  }*/

  if (e < loss) loss = e - 0.0001;

  // Determine the scattering angle.
  double ctheta0 = 1. - 2. * RndmUniformGPU();
  if (m_useAnisotropic) {
    switch (m_scatModel[level]) {
      case 0:
        break;
      case 1:
        ctheta0 = 1. - RndmUniformGPU() * angCut;
        if (RndmUniformGPU() > angPar) ctheta0 = -ctheta0;
        break;
      case 2:
        ctheta0 = (ctheta0 + angPar) / (1. + angPar * ctheta0);
        break;
      default:
        printf(
            "MediumGPU::ElectronCollision:\n"
            "    Unknown scattering model.\n"
            "    Using isotropic distribution.\n");
        break;
    }
  }

  const double s1 = m_rgas[igas];
  const double theta0 = acos(ctheta0);
  const double arg = fmax((cuda_t)1. - s1 * loss / e, SmallGPU);

  const double d = 1. - ctheta0 * sqrt(arg);

  // Update the energy.
  e1 = fmax(e * ((double)1. - loss / (s1 * e) - (double)2. * d * m_s2[igas]),
            SmallGPU);
  double q = fmin(sqrt((e / e1) * arg) / s1, (double)1.);

  const double theta = asin(q * sin(theta0));
  double ctheta = cos(theta);
  if (ctheta0 < 0.) {
    const double u = (s1 - 1.) * (s1 - 1.) / arg;
    if (ctheta0 * ctheta0 > u) ctheta = -ctheta;
  }
  const double stheta = sin(theta);
  // Calculate the direction after the collision.
  dz = fmin(dz, 1.);
  const double argZ = sqrt(dx * dx + dy * dy);

  // Azimuth is chosen at random.
  const double phi = TwoPi * RndmUniformGPU();
  const double cphi = cos(phi);
  const double sphi = sin(phi);
  if (argZ > 0.) {
    const double a = stheta / argZ;
    const double dz1 = dz * ctheta + argZ * stheta * sphi;
    const double dy1 = dy * ctheta + a * (dx * cphi - dy * dz * sphi);
    const double dx1 = dx * ctheta - a * (dy * cphi + dx * dz * sphi);
    dz = dz1;
    dy = dy1;
    dx = dx1;
  } else {
    dz = ctheta;
    dx = cphi * stheta;
    dy = sphi * stheta;
  }
  return true;
}

////////////////////////////////

__device__ double MediumGPU::GetElectronCollisionRate(const cuda_t e,
                                                      const int band) {
  switch (m_MediumType) {
    case MediumType::Medium: {
      return 0;
    }
    case MediumType::MediumMagboltz: {
      return GetElectronCollisionRate__MediumMagboltz(e, band);
    }
  }

  return 0;
}

double Medium::CreateGPUTransferObject(MediumGPU*& med_gpu) {
  double alloc{0};

  med_gpu->m_driftable = m_driftable;
  med_gpu->m_ionisable = m_ionisable;
  med_gpu->m_id = m_id;
  med_gpu->m_microscopic = m_microscopic;

  med_gpu->m_MediumType = MediumGPU::MediumType::Medium;
  return alloc;
}

double MediumGas::CreateGPUTransferObject(MediumGPU*& med_gpu) {
  double alloc{0};
  med_gpu->m_MediumType = MediumGPU::MediumType::MediumGas;
  return alloc;
}

double MediumMagboltz::CreateGPUTransferObject(MediumGPU*& med_gpu) {
  checkCudaErrors(cudaMallocManaged(&med_gpu, sizeof(MediumGPU)));
  double alloc{sizeof(MediumGPU)};

  alloc += Medium::CreateGPUTransferObject(med_gpu);
  alloc += MediumGas::CreateGPUTransferObject(med_gpu);

  med_gpu->m_eHighLog = m_eHighLog;
  med_gpu->m_lnStep = m_lnStep;
  med_gpu->m_eHigh = m_eHigh;
  med_gpu->m_eStep = m_eStep;
  med_gpu->m_eStepInv = m_eStepInv;
  med_gpu->m_nTerms = m_nTerms;
  med_gpu->m_useOpalBeaty = m_useOpalBeaty;
  med_gpu->m_useAnisotropic = m_useAnisotropic;
  med_gpu->m_cfNull = m_cfNull;
  med_gpu->m_eMax = m_eMax;

  alloc += CreateGPUArrayOfArraysFromVector<double>(
      m_cf, med_gpu->m_cf, med_gpu->m_numcf, med_gpu->m_numcfIdx);
  alloc += CreateGPUArrayOfArraysFromVector<double>(
      m_cfLog, med_gpu->m_cfLog, med_gpu->m_numcfLog, med_gpu->m_numcfLogIdx);
  alloc += CreateGPUArrayOfArraysFromVector<double>(
      m_scatPar, med_gpu->m_scatPar, med_gpu->m_numscatPar,
      med_gpu->m_numscatParIdx);
  alloc += CreateGPUArrayOfArraysFromVector<double>(
      m_scatParLog, med_gpu->m_scatParLog, med_gpu->m_numscatParLog,
      med_gpu->m_numscatParLogIdx);
  alloc += CreateGPUArrayOfArraysFromVector<double>(
      m_scatCut, med_gpu->m_scatCut, med_gpu->m_numscatCut,
      med_gpu->m_numscatCutIdx);
  alloc += CreateGPUArrayOfArraysFromVector<double>(
      m_scatCutLog, med_gpu->m_scatCutLog, med_gpu->m_numscatCutLog,
      med_gpu->m_numscatCutLogIdx);

  for (std::size_t i = 0; i < Magboltz::nMaxLevels; i++) {
    med_gpu->m_csType[i] = m_csType[i];
    med_gpu->m_wOpalBeaty[i] = m_wOpalBeaty[i];
    med_gpu->m_yFluorescence[i] = m_yFluorescence[i];
    med_gpu->m_nAuger1[i] = m_nAuger1[i];
    med_gpu->m_nAuger2[i] = m_nAuger2[i];
    med_gpu->m_eAuger1[i] = m_eAuger1[i];
    med_gpu->m_eAuger2[i] = m_eAuger2[i];
    med_gpu->m_nFluorescence[i] = m_nFluorescence[i];
    med_gpu->m_eFluorescence[i] = m_eFluorescence[i];
    med_gpu->m_scatModel[i] = m_scatModel[i];
    med_gpu->m_energyLoss[i] = m_energyLoss[i];
  }

  for (std::size_t i = 0; i < m_nMaxGases; i++) {
    med_gpu->m_rgas[i] = m_rgas[i];
    med_gpu->m_s2[i] = m_s2[i];
  }

  alloc += CreateGPUArrayFromVector<double>(m_cfTot, med_gpu->m_numcfTot,
                                            med_gpu->m_cfTot);
  alloc += CreateGPUArrayFromVector<double>(m_cfTotLog, med_gpu->m_numcfTotLog,
                                            med_gpu->m_cfTotLog);

  med_gpu->m_MediumType = MediumGPU::MediumType::MediumMagboltz;

  return alloc;
}

}  // namespace Garfield