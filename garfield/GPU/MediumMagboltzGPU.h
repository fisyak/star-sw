#ifndef MEDIUM_MAGBOLTZ_GPU_H
#define MEDIUM_MAGBOLTZ_GPU_H

/// Get the overall null-collision rate [ns-1].
__device__ double GetElectronNullCollisionRate(const int band);
__device__ double GetElectronCollisionRate__MediumMagboltz(const double e,
                                                           const int band);
static constexpr int nEnergyStepsLog{1000};
static constexpr int nEnergyStepsGamma{5000};
static constexpr int nCsTypes{7};
/// Max. electron energy in the collision rate tables.
double m_eMax{0.};
/// Energy spacing in the linear part of the collision rate tables.
double m_eStep{0.};
/// Inverse energy spacing.
double m_eStepInv{0.};
double m_eHigh, m_eHighLog{0.};
double m_lnStep{0.};

/// Flag enabling/disabling output of cross-section table to file
bool m_useCsOutput{false};
/// Number of different cross-section types in the current gas mixture
std::size_t m_nTerms{0};
/// Sample secondary electron energies using Opal-Beaty parameterisation
bool m_useOpalBeaty{true};
/// Sample secondary electron energies using Green-Sawada parameterisation
bool m_useGreenSawada{false};
int m_csType[Garfield::Magboltz::nMaxLevels];
double m_energyLoss[Garfield::Magboltz::nMaxLevels];

double** m_scatPar{nullptr};
int* m_numscatParIdx{nullptr};
int m_numscatPar{0};

double** m_scatCut{nullptr};
int* m_numscatCutIdx{nullptr};
int m_numscatCut{0};

double** m_scatParLog{nullptr};
int* m_numscatParLogIdx{nullptr};
int m_numscatParLog{0};

double** m_scatCutLog{nullptr};
int* m_numscatCutLogIdx{nullptr};
int m_numscatCutLog{0};
int m_scatModel[Magboltz::nMaxLevels];

double* m_cfTot{nullptr};
int m_numcfTot{0};
double* m_cfTotLog{nullptr};
int m_numcfTotLog{0};

double** m_cf{nullptr};
int* m_numcfIdx{nullptr};
int m_numcf{0};

double** m_cfLog{nullptr};
int* m_numcfLogIdx{nullptr};
int m_numcfLog{0};

bool m_useAnisotropic{true};
/// Null-collision frequency
double m_cfNull{0.};

double m_wOpalBeaty[Garfield::Magboltz::nMaxLevels];
double m_yFluorescence[Garfield::Magboltz::nMaxLevels];

std::size_t m_nAuger1[Garfield::Magboltz::nMaxLevels];
std::size_t m_nAuger2[Garfield::Magboltz::nMaxLevels];
/// Energy imparted to Auger electrons
double m_eAuger1[Garfield::Magboltz::nMaxLevels];
double m_eAuger2[Garfield::Magboltz::nMaxLevels];

std::size_t m_nFluorescence[Garfield::Magboltz::nMaxLevels];
double m_eFluorescence[Garfield::Magboltz::nMaxLevels];
double m_rgas[Garfield::Magboltz::MaxNumberGas];
double m_s2[Garfield::Magboltz::MaxNumberGas];

#endif