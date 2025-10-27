#ifndef G_MEDIUM_H
#define G_MEDIUM_H

#include <cstddef>
#include <mutex>
#include <string>
#include <utility>
#include <vector>

#include "Garfield/FundamentalConstants.hh"
#include "Garfield/ParticleTypes.hh"

class TPad;

namespace Garfield {

class MediumGPU;

/// Abstract base class for components.
class Medium {
 public:
  /// Constructor
  Medium();
  /// Destructor
  virtual ~Medium();

  /// Return the id number of the class instance.
  int GetId() const { return m_id; }

  /// Get the medium name/identifier.
  const std::string& GetName() const { return m_name; }
  /// Is this medium a gas?
  virtual bool IsGas() const { return false; }
  /// Is this medium a semiconductor?
  virtual bool IsSemiconductor() const { return false; }
  /// Is this medium a conductor?
  virtual bool IsConductor() const { return false; }

  /// Set the temperature [K].
  void SetTemperature(const double t);
  /// Get the temperature [K].
  double GetTemperature() const { return m_temperature; }
  // Set the pressure [Torr].
  void SetPressure(const double p);
  // Get the pressure [Torr].
  double GetPressure() const { return m_pressure; }
  /// Set the relative static dielectric constant.
  void SetDielectricConstant(const double eps);
  /// Get the relative static dielectric constant.
  double GetDielectricConstant() const { return m_epsilon; }

  /// Get number of components of the medium.
  std::size_t GetNumberOfComponents() const { return m_nComponents; }
  /// Get the name and fraction of a given component.
  virtual void GetComponent(const std::size_t i, std::string& label, double& f);
  /// Set the effective atomic number.
  virtual void SetAtomicNumber(const double z);
  /// Get the effective atomic number.
  virtual double GetAtomicNumber() const { return m_z; }
  /// Set the effective atomic weight.
  virtual void SetAtomicWeight(const double a);
  /// Get the effective atomic weight.
  virtual double GetAtomicWeight() const { return m_a; }
  /// Set the number density [cm-3].
  virtual void SetNumberDensity(const double n);
  /// Get the number density [cm-3].
  virtual double GetNumberDensity() const { return m_density; }
  /// Set the mass density [g/cm3].
  virtual void SetMassDensity(const double rho);
  /// Get the mass density [g/cm3].
  virtual double GetMassDensity() const;

  /// Switch electron/ion/hole transport on/off.
  virtual void EnableDrift(const bool on = true) { m_driftable = on; }
  /// Make the medium ionisable or non-ionisable.
  virtual void EnablePrimaryIonisation(const bool on = true) {
    m_ionisable = on;
  }

  /// Is charge carrier transport enabled in this medium?
  bool IsDriftable() const { return m_driftable; }
  /// Does the medium have electron scattering rates?
  bool IsMicroscopic() const { return m_microscopic; }

  /// Is charge deposition by charged particles/photon enabled in this medium?
  bool IsIonisable() const { return m_ionisable; }

  /// Set the W value (average energy to produce an electron/ion or e/h pair).
  void SetW(const double w) { m_w = w; }
  /// Get the W value.
  double GetW() const { return m_w; }
  /// Set the Fano factor.
  void SetFanoFactor(const double f) { m_fano = f; }
  /// Get the Fano factor.
  double GetFanoFactor() const { return m_fano; }

  /// Plot the drift velocity as function of the electric field.
  void PlotVelocity(const std::string& carriers, TPad* pad);
  /// Plot the diffusion coefficients as function of the electric field.
  void PlotDiffusion(const std::string& carriers, TPad* pad);
  /// Plot the Townsend coefficient(s) as function of the electric field.
  void PlotTownsend(const std::string& carriers, TPad* pad);
  /// Plot the attachment coefficient(s) as function of the electric field.
  void PlotAttachment(const std::string& carriers, TPad* pad);
  /// Plot Townsend and attachment coefficients.
  void PlotAlphaEta(const std::string& carriers, TPad* pad);

  // Transport parameters for electrons
  /// Drift velocity [cm / ns]
  virtual bool ElectronVelocity(const double ex, const double ey,
                                const double ez, const double bx,
                                const double by, const double bz, double& vx,
                                double& vy, double& vz);
  /// Flux (mean velocity; shorthand: wv) and bulk (center of mass velocity;
  /// shorthand: wr) drift velocity [cm / ns]
  virtual bool ElectronVelocityFluxBulk(const double ex, const double ey,
                                        const double ez, const double bx,
                                        const double by, const double bz,
                                        double& wv, double& wr);
  /// Longitudinal and transverse diffusion coefficients [cm1/2]
  virtual bool ElectronDiffusion(const double ex, const double ey,
                                 const double ez, const double bx,
                                 const double by, const double bz, double& dl,
                                 double& dt);
  /// Diffusion tensor: diagonal elements are the diffusion
  /// coefficients [cm] along e, btrans, e x b,
  /// off-diagonal elements are the covariances
  virtual bool ElectronDiffusion(const double ex, const double ey,
                                 const double ez, const double bx,
                                 const double by, const double bz,
                                 double cov[3][3]);
  /// Ionisation coefficient [cm-1]
  virtual bool ElectronTownsend(const double ex, const double ey,
                                const double ez, const double bx,
                                const double by, const double bz,
                                double& alpha);
  /// Attachment coefficient [cm-1]
  virtual bool ElectronAttachment(const double ex, const double ey,
                                  const double ez, const double bx,
                                  const double by, const double bz,
                                  double& eta);
  /// TOF Ionisation rate [ns-1]
  virtual bool ElectronTOFIonisation(const double ex, const double ey,
                                     const double ez, const double bx,
                                     const double by, const double bz,
                                     double& riontof);
  /// TOF Attachment Rate [ns-1]
  virtual bool ElectronTOFAttachment(const double ex, const double ey,
                                     const double ez, const double bx,
                                     const double by, const double bz,
                                     double& ratttof);
  /// Lorentz angle
  virtual bool ElectronLorentzAngle(const double ex, const double ey,
                                    const double ez, const double bx,
                                    const double by, const double bz,
                                    double& lor);
  /// Low-field mobility [cm2 V-1 ns-1]
  virtual double ElectronMobility();
  // Microscopic electron transport properties

  /// Dispersion relation (energy vs. wave vector)
  virtual double GetElectronEnergy(const double px, const double py,
                                   const double pz, double& vx, double& vy,
                                   double& vz, const int band = 0);
  /// Sample the momentum vector for a given energy
  /// (only meaningful in semiconductors).
  virtual void GetElectronMomentum(const double e, double& px, double& py,
                                   double& pz, int& band);

  /// Null-collision rate [ns-1]
  virtual double GetElectronNullCollisionRate(const int band = 0);

  /// Collision rate [ns-1] for given electron energy
  virtual double GetElectronCollisionRate(const double e, const int band = 0);
  struct Secondary {
    Particle type{Particle::Electron};
    double energy{0.};
    double time{0.};
    double distance{0.};
  };
  /// Sample the collision type. Update energy and direction vector.
  virtual bool ElectronCollision(const double e, int& type, int& level,
                                 double& e1, double& dx, double& dy, double& dz,
                                 std::vector<Secondary>& secondaries,
                                 int& band);

  // Transport parameters for holes
  /// Drift velocity [cm / ns]
  virtual bool HoleVelocity(const double ex, const double ey, const double ez,
                            const double bx, const double by, const double bz,
                            double& vx, double& vy, double& vz);
  /// Longitudinal and transverse diffusion coefficients [cm1/2]
  virtual bool HoleDiffusion(const double ex, const double ey, const double ez,
                             const double bx, const double by, const double bz,
                             double& dl, double& dt);
  /// Diffusion tensor
  virtual bool HoleDiffusion(const double ex, const double ey, const double ez,
                             const double bx, const double by, const double bz,
                             double cov[3][3]);
  /// Ionisation coefficient [cm-1]
  virtual bool HoleTownsend(const double ex, const double ey, const double ez,
                            const double bx, const double by, const double bz,
                            double& alpha);
  /// Attachment coefficient [cm-1]
  virtual bool HoleAttachment(const double ex, const double ey, const double ez,
                              const double bx, const double by, const double bz,
                              double& eta);
  /// Low-field mobility [cm2 V-1 ns-1]
  virtual double HoleMobility();

  // Transport parameters for ions
  /// Ion drift velocity [cm / ns]
  virtual bool IonVelocity(const double ex, const double ey, const double ez,
                           const double bx, const double by, const double bz,
                           double& vx, double& vy, double& vz);
  bool HasIonVelocity() const { return !(m_iVel.empty() && m_iMob.empty()); }
  /// Longitudinal and transverse diffusion coefficients [cm1/2]
  virtual bool IonDiffusion(const double ex, const double ey, const double ez,
                            const double bx, const double by, const double bz,
                            double& dl, double& dt);
  /// Dissociation coefficient
  virtual bool IonDissociation(const double ex, const double ey,
                               const double ez, const double bx,
                               const double by, const double bz, double& diss);
  /// Low-field ion mobility [cm2 V-1 ns-1]
  virtual double IonMobility();

  /// Negative ion drift velocity [cm / ns]
  virtual bool NegativeIonVelocity(const double ex, const double ey,
                                   const double ez, const double bx,
                                   const double by, const double bz, double& vx,
                                   double& vy, double& vz);
  /// Low-field negative ion mobility [cm2 V-1 ns-1]
  virtual double NegativeIonMobility();

  /// Set the range of fields to be covered by the transport tables.
  void SetFieldGrid(double emin, double emax, const std::size_t ne, bool logE,
                    double bmin = 0., double bmax = 0.,
                    const std::size_t nb = 1, double amin = HalfPi,
                    double amax = HalfPi, const std::size_t na = 1);
  /// Set the fields and E-B angles to be used in the transport tables.
  void SetFieldGrid(const std::vector<double>& efields,
                    const std::vector<double>& bfields,
                    const std::vector<double>& angles);
  /// Get the fields and E-B angles used in the transport tables.
  void GetFieldGrid(std::vector<double>& efields, std::vector<double>& bfields,
                    std::vector<double>& angles);

  /// Set an entry in the table of drift speeds along E.
  bool SetElectronVelocityE(const std::size_t ie, const std::size_t ib,
                            const std::size_t ia, const double v) {
    return SetEntry(ie, ib, ia, "ElectronVelocityE", m_eVelE, v);
  }
  /// Get an entry in the table of drift speeds along E.
  bool GetElectronVelocityE(const std::size_t ie, const std::size_t ib,
                            const std::size_t ia, double& v) {
    return GetEntry(ie, ib, ia, "ElectronVelocityE", m_eVelE, v);
  }
  /// Set an entry in the table of drift speeds along ExB.
  bool SetElectronVelocityExB(const std::size_t ie, const std::size_t ib,
                              const std::size_t ia, const double v) {
    return SetEntry(ie, ib, ia, "ElectronVelocityExB", m_eVelX, v);
  }
  /// Get an entry in the table of drift speeds along ExB.
  bool GetElectronVelocityExB(const std::size_t ie, const std::size_t ib,
                              const std::size_t ia, double& v) {
    return GetEntry(ie, ib, ia, "ElectronVelocityExB", m_eVelX, v);
  }
  /// Set an entry in the table of drift speeds along Btrans.
  bool SetElectronVelocityB(const std::size_t ie, const std::size_t ib,
                            const std::size_t ia, const double v) {
    return SetEntry(ie, ib, ia, "ElectronVelocityB", m_eVelB, v);
  }
  /// Get an entry in the table of drift speeds along Btrans.
  bool GetElectronVelocityB(const std::size_t ie, const std::size_t ib,
                            const std::size_t ia, double& v) {
    return GetEntry(ie, ib, ia, "ElectronVelocityB", m_eVelB, v);
  }
  /// Set an entry in the table of flux drift speeds.
  bool SetElectronFluxVelocity(const std::size_t ie, const std::size_t ib,
                               const std::size_t ia, const double v) {
    return SetEntry(ie, ib, ia, "ElectronFluxVelocity", m_eVelWv, v);
  }
  /// Get an entry in the table of flux drift speeds.
  bool GetElectronFluxVelocity(const std::size_t ie, const std::size_t ib,
                               const std::size_t ia, double& v) {
    return GetEntry(ie, ib, ia, "ElectronFluxVelocity", m_eVelWv, v);
  }
  /// Set an entry in the table of bulk drift speeds.
  bool SetElectronBulkVelocity(const std::size_t ie, const std::size_t ib,
                               const std::size_t ia, const double v) {
    return SetEntry(ie, ib, ia, "ElectronBulkVelocity", m_eVelWr, v);
  }
  /// Get an entry in the table of bulk drift speeds.
  bool GetElectronBulkVelocity(const std::size_t ie, const std::size_t ib,
                               const std::size_t ia, double& v) {
    return GetEntry(ie, ib, ia, "ElectronBulkVelocity", m_eVelWr, v);
  }
  /// Set an entry in the table of longitudinal diffusion coefficients.
  bool SetElectronLongitudinalDiffusion(const std::size_t ie,
                                        const std::size_t ib,
                                        const std::size_t ia, const double dl) {
    return SetEntry(ie, ib, ia, "ElectronLongitudinalDiffusion", m_eDifL, dl);
  }
  /// Get an entry in the table of longitudinal diffusion coefficients.
  bool GetElectronLongitudinalDiffusion(const std::size_t ie,
                                        const std::size_t ib,
                                        const std::size_t ia, double& dl) {
    return GetEntry(ie, ib, ia, "ElectronLongitudinalDiffusion", m_eDifL, dl);
  }
  /// Set an entry in the table of transverse diffusion coefficients.
  bool SetElectronTransverseDiffusion(const std::size_t ie,
                                      const std::size_t ib,
                                      const std::size_t ia, const double dt) {
    return SetEntry(ie, ib, ia, "ElectronTransverseDiffusion", m_eDifT, dt);
  }
  /// Get an entry in the table of transverse diffusion coefficients.
  bool GetElectronTransverseDiffusion(const std::size_t ie,
                                      const std::size_t ib,
                                      const std::size_t ia, double& dt) {
    return GetEntry(ie, ib, ia, "ElectronTransverseDiffusion", m_eDifT, dt);
  }
  /// Set an entry in the table of Townsend coefficients.
  bool SetElectronTownsend(const std::size_t ie, const std::size_t ib,
                           const std::size_t ia, const double alpha) {
    return SetEntry(ie, ib, ia, "ElectronTownsend", m_eAlp, alpha);
  }
  /// Get an entry in the table of Townsend coefficients.
  bool GetElectronTownsend(const std::size_t ie, const std::size_t ib,
                           const std::size_t ia, double& alpha) {
    return GetEntry(ie, ib, ia, "ElectronTownsend", m_eAlp, alpha);
  }
  /// Set an entry in the table of attachment coefficients.
  bool SetElectronAttachment(const std::size_t ie, const std::size_t ib,
                             const std::size_t ia, const double eta) {
    return SetEntry(ie, ib, ia, "ElectronAttachment", m_eAtt, eta);
  }
  /// Get an entry in the table of attachment coefficients.
  bool GetElectronAttachment(const std::size_t ie, const std::size_t ib,
                             const std::size_t ia, double& eta) {
    return GetEntry(ie, ib, ia, "ElectronAttachment", m_eAtt, eta);
  }
  /// Set an entry in the table of ionization rate of TOF.
  bool SetElectronTOFIonisation(const std::size_t ie, const std::size_t ib,
                                const std::size_t ia, const double v) {
    return SetEntry(ie, ib, ia, "ElectronTOFIonisation", m_eRIon, v);
  }
  /// Get an entry in the table of ionization rate of TOF.
  bool GetElectronTOFIonisation(const std::size_t ie, const std::size_t ib,
                                const std::size_t ia, double& v) {
    return GetEntry(ie, ib, ia, "ElectronTOFIonisation", m_eRIon, v);
  }
  /// Set an entry in the table of attachment rate of TOF.
  bool SetElectronTOFAttachment(const std::size_t ie, const std::size_t ib,
                                const std::size_t ia, const double v) {
    return SetEntry(ie, ib, ia, "ElectronTOFAttachment", m_eRAtt, v);
  }
  /// Get an entry in the table of attachment rate of TOF.
  bool GetElectronTOFAttachment(const std::size_t ie, const std::size_t ib,
                                const std::size_t ia, double& v) {
    return GetEntry(ie, ib, ia, "ElectronTOFAttachment", m_eRAtt, v);
  }

  /// Set an entry in the table of Lorentz angles.
  bool SetElectronLorentzAngle(const std::size_t ie, const std::size_t ib,
                               const std::size_t ia, const double lor) {
    return SetEntry(ie, ib, ia, "ElectronLorentzAngle", m_eLor, lor);
  }
  /// Get an entry in the table of Lorentz angles.
  bool GetElectronLorentzAngle(const std::size_t ie, const std::size_t ib,
                               const std::size_t ia, double& lor) {
    return GetEntry(ie, ib, ia, "ElectronLorentzAngle", m_eLor, lor);
  }

  /// Set an entry in the table of drift speeds along E.
  bool SetHoleVelocityE(const std::size_t ie, const std::size_t ib,
                        const std::size_t ia, const double v) {
    return SetEntry(ie, ib, ia, "HoleVelocityE", m_hVelE, v);
  }
  /// Get an entry in the table of drift speeds along E.
  bool GetHoleVelocityE(const std::size_t ie, const std::size_t ib,
                        const std::size_t ia, double& v) {
    return GetEntry(ie, ib, ia, "HoleVelocityE", m_hVelE, v);
  }
  /// Set an entry in the table of drift speeds along ExB.
  bool SetHoleVelocityExB(const std::size_t ie, const std::size_t ib,
                          const std::size_t ia, const double v) {
    return SetEntry(ie, ib, ia, "HoleVelocityExB", m_hVelX, v);
  }
  /// Get an entry in the table of drift speeds along ExB.
  bool GetHoleVelocityExB(const std::size_t ie, const std::size_t ib,
                          const std::size_t ia, double& v) {
    return GetEntry(ie, ib, ia, "HoleVelocityExB", m_hVelX, v);
  }
  /// Set an entry in the table of drift speeds along Btrans.
  bool SetHoleVelocityB(const std::size_t ie, const std::size_t ib,
                        const std::size_t ia, const double v) {
    return SetEntry(ie, ib, ia, "HoleVelocityB", m_hVelB, v);
  }
  /// Get an entry in the table of drift speeds along Btrans.
  bool GetHoleVelocityB(const std::size_t ie, const std::size_t ib,
                        const std::size_t ia, double& v) {
    return GetEntry(ie, ib, ia, "HoleVelocityB", m_hVelB, v);
  }

  /// Set an entry in the table of longitudinal diffusion coefficients.
  bool SetHoleLongitudinalDiffusion(const std::size_t ie, const std::size_t ib,
                                    const std::size_t ia, const double dl) {
    return SetEntry(ie, ib, ia, "HoleLongitudinalDiffusion", m_hDifL, dl);
  }
  /// Get an entry in the table of longitudinal diffusion coefficients.
  bool GetHoleLongitudinalDiffusion(const std::size_t ie, const std::size_t ib,
                                    const std::size_t ia, double& dl) {
    return GetEntry(ie, ib, ia, "HoleLongitudinalDiffusion", m_hDifL, dl);
  }
  /// Set an entry in the table of transverse diffusion coefficients.
  bool SetHoleTransverseDiffusion(const std::size_t ie, const std::size_t ib,
                                  const std::size_t ia, const double dt) {
    return SetEntry(ie, ib, ia, "HoleTransverseDiffusion", m_hDifT, dt);
  }
  /// Get an entry in the table of transverse diffusion coefficients.
  bool GetHoleTransverseDiffusion(const std::size_t ie, const std::size_t ib,
                                  const std::size_t ia, double& dt) {
    return GetEntry(ie, ib, ia, "HoleTransverseDiffusion", m_hDifT, dt);
  }
  /// Set an entry in the table of Townsend coefficients.
  bool SetHoleTownsend(const std::size_t ie, const std::size_t ib,
                       const std::size_t ia, const double alpha) {
    return SetEntry(ie, ib, ia, "HoleTownsend", m_hAlp, alpha);
  }
  /// Get an entry in the table of Townsend coefficients.
  bool GetHoleTownsend(const std::size_t ie, const std::size_t ib,
                       const std::size_t ia, double& alpha) {
    return GetEntry(ie, ib, ia, "HoleTownsend", m_hAlp, alpha);
  }
  /// Set an entry in the table of attachment coefficients.
  bool SetHoleAttachment(const std::size_t ie, const std::size_t ib,
                         const std::size_t ia, const double eta) {
    return SetEntry(ie, ib, ia, "HoleAttachment", m_hAtt, eta);
  }
  /// Get an entry in the table of attachment coefficients.
  bool GetHoleAttachment(const std::size_t ie, const std::size_t ib,
                         const std::size_t ia, double& eta) {
    return GetEntry(ie, ib, ia, "HoleAttachment", m_hAtt, eta);
  }

  /// Initialise the table of ion mobilities from a list of
  /// electric fields and corresponding mobilities.
  /// The mobilities will be interpolated at the electric fields
  /// of the currently set grid.
  bool SetIonMobility(const std::vector<double>& fields,
                      const std::vector<double>& mobilities,
                      const bool negativeIons = false);
  /// Set an entry in the table of ion mobilities.
  bool SetIonMobility(const std::size_t ie, const std::size_t ib,
                      const std::size_t ia, const double mu);
  /// Get an entry in the table of ion mobilities.
  bool GetIonMobility(const std::size_t ie, const std::size_t ib,
                      const std::size_t ia, double& mu) {
    return GetEntry(ie, ib, ia, "IonMobility", m_iMob, mu);
  }

  /// Set an entry in the table of longitudinal diffusion coefficients.
  bool SetIonLongitudinalDiffusion(const std::size_t ie, const std::size_t ib,
                                   const std::size_t ia, const double dl) {
    return SetEntry(ie, ib, ia, "IonLongitudinalDiffusion", m_iDifL, dl);
  }
  /// Get an entry in the table of longitudinal diffusion coefficients.
  bool GetIonLongitudinalDiffusion(const std::size_t ie, const std::size_t ib,
                                   const std::size_t ia, double& dl) {
    return GetEntry(ie, ib, ia, "IonLongitudinalDiffusion", m_iDifL, dl);
  }
  /// Set an entry in the table of transverse diffusion coefficients.
  bool SetIonTransverseDiffusion(const std::size_t ie, const std::size_t ib,
                                 const std::size_t ia, const double dt) {
    return SetEntry(ie, ib, ia, "IonTransverseDiffusion", m_iDifT, dt);
  }
  /// Get an entry in the table of transverse diffusion coefficients.
  bool GetIonTransverseDiffusion(const std::size_t ie, const std::size_t ib,
                                 const std::size_t ia, double& dt) {
    return GetEntry(ie, ib, ia, "IonTransverseDiffusion", m_iDifT, dt);
  }
  /// Set an entry in the table of dissociation coefficients.
  bool SetIonDissociation(const std::size_t ie, const std::size_t ib,
                          const std::size_t ia, const double diss) {
    return SetEntry(ie, ib, ia, "IonDissociation", m_iDis, diss);
  }
  /// Get an entry in the table of dissociation coefficients.
  bool GetIonDissociation(const std::size_t ie, const std::size_t ib,
                          const std::size_t ia, double& diss) {
    return GetEntry(ie, ib, ia, "IonDissociation", m_iDis, diss);
  }

  /// Set an entry in the table of negative ion mobilities.
  bool SetNegativeIonMobility(const std::size_t ie, const std::size_t ib,
                              const std::size_t ia, const double mu);
  /// Get an entry in the table of negative ion mobilities.
  bool GetNegativeIonMobility(const std::size_t ie, const std::size_t ib,
                              const std::size_t ia, double& mu) {
    return GetEntry(ie, ib, ia, "NegativeIonMobility", m_nMob, mu);
  }

  /// Reset all tables of transport parameters.
  virtual void ResetTables();

  void ResetElectronVelocity() {
    m_eVelE.clear();
    m_eVelB.clear();
    m_eVelX.clear();
    m_eVelWv.clear();
    m_eVelWr.clear();
  }
  void ResetElectronDiffusion() {
    m_eDifL.clear();
    m_eDifT.clear();
    m_eDifM.clear();
  }
  void ResetElectronTownsend() { m_eAlp.clear(); }
  void ResetElectronAttachment() { m_eAtt.clear(); }
  void ResetElectronTOFRates() {
    m_eRIon.clear();
    m_eRAtt.clear();
  }
  void ResetElectronLorentzAngle() { m_eLor.clear(); }

  void ResetHoleVelocity() {
    m_hVelE.clear();
    m_hVelB.clear();
    m_hVelX.clear();
  }
  void ResetHoleDiffusion() {
    m_hDifL.clear();
    m_hDifT.clear();
    m_hDifM.clear();
  }
  void ResetHoleTownsend() { m_hAlp.clear(); }
  void ResetHoleAttachment() { m_hAtt.clear(); }

  void ResetIonMobility() {
    m_iMob.clear();
    m_iVel.clear();
  }
  void ResetIonDiffusion() {
    m_iDifL.clear();
    m_iDifT.clear();
  }
  void ResetIonDissociation() { m_iDis.clear(); }
  void ResetNegativeIonMobility() {
    m_nMob.clear();
    m_nVel.clear();
  }

  void VelocityFromMobility(
      const std::vector<std::vector<std::vector<double> > >& mob,
      std::vector<std::vector<std::vector<double> > >& vel);

  /// Select the extrapolation method for fields below/above the table range.
  /// Possible options are "constant", "linear", and "exponential".
  void SetExtrapolationMethodVelocity(const std::string& extrLow,
                                      const std::string& extrHigh);
  void SetExtrapolationMethodDiffusion(const std::string& extrLow,
                                       const std::string& extrHigh);
  void SetExtrapolationMethodTownsend(const std::string& extrLow,
                                      const std::string& extrHigh);
  void SetExtrapolationMethodAttachment(const std::string& extrLow,
                                        const std::string& extrHigh);
  void SetExtrapolationMethodIonMobility(const std::string& extrLow,
                                         const std::string& extrHigh);
  void SetExtrapolationMethodIonDissociation(const std::string& extrLow,
                                             const std::string& extrHigh);

  /// Set the degree of polynomial interpolation (usually 2).
  void SetInterpolationMethodVelocity(const std::size_t intrp);
  void SetInterpolationMethodDiffusion(const std::size_t intrp);
  void SetInterpolationMethodTownsend(const std::size_t intrp);
  void SetInterpolationMethodAttachment(const std::size_t intrp);
  void SetInterpolationMethodIonMobility(const std::size_t intrp);
  void SetInterpolationMethodIonDissociation(const std::size_t intrp);

  // Scaling of fields and transport parameters.
  virtual double ScaleElectricField(const double e) const { return e; }
  virtual double UnScaleElectricField(const double e) const { return e; }
  virtual double ScaleVelocity(const double v) const { return v; }
  virtual double ScaleDiffusion(const double d) const { return d; }
  virtual double ScaleDiffusionTensor(const double d) const { return d; }
  virtual double ScaleTownsend(const double alpha) const { return alpha; }
  virtual double ScaleAttachment(const double eta) const { return eta; }
  virtual double ScaleLorentzAngle(const double lor) const { return lor; }
  virtual double ScaleDissociation(const double diss) const { return diss; }

  // Optical properties
  /// Get the energy range [eV] of the available optical data.
  virtual bool GetOpticalDataRange(double& emin, double& emax,
                                   const std::size_t i = 0);
  /// Get the complex dielectric function at a given energy.
  virtual bool GetDielectricFunction(const double e, double& eps1, double& eps2,
                                     const std::size_t i = 0);
  // Get the photoabsorption cross-section [cm2] at a given energy.
  virtual bool GetPhotoAbsorptionCrossSection(const double e, double& sigma,
                                              const std::size_t i = 0);
  virtual double GetPhotonCollisionRate(const double e);
  virtual bool PhotonCollision(const double e, int& type, int& level,
                               double& e1, double& ctheta,
                               std::vector<Secondary>& secondaries);

  /// Switch on/off debugging  messages
  void EnableDebugging() { m_debug = true; }
  void DisableDebugging() { m_debug = false; }

  /// Create and initialise GPU Transfer class
  virtual double CreateGPUTransferObject(MediumGPU*& med_gpu);

 private:
  std::mutex m_mutex; 

 protected:
  std::string m_className{"Medium"};

  static int m_idCounter;

  // Number of components
  std::size_t m_nComponents{1};
  // Name
  std::string m_name;
  // Temperature [K]
  double m_temperature{293.15};
  // Pressure [Torr]
  double m_pressure{760.};
  // Static dielectric constant
  double m_epsilon{1.};
  // (Effective) atomic number Z
  double m_z{1.};
  // Atomic weight A
  double m_a{0.};
  // Number density [cm-3]
  double m_density{0.};

  // Id number
  int m_id{0};

  // Transport flags
  bool m_driftable{false};
  bool m_microscopic{false};
  bool m_ionisable{false};

  // W value
  double m_w{0.};
  // Fano factor
  double m_fano{0.};

  // Update flag
  bool m_isChanged{true};

  // Switch on/off debugging messages
  bool m_debug{false};

  // Tables of transport parameters
  bool m_tab2d{false};

  // Field grids
  std::vector<double> m_eFields;
  std::vector<double> m_bFields;
  std::vector<double> m_bAngles;

  // Electrons
  std::vector<std::vector<std::vector<double> > > m_eVelE;
  std::vector<std::vector<std::vector<double> > > m_eVelX;
  std::vector<std::vector<std::vector<double> > > m_eVelB;
  std::vector<std::vector<std::vector<double> > > m_eDifL;
  std::vector<std::vector<std::vector<double> > > m_eDifT;
  std::vector<std::vector<std::vector<double> > > m_eAlp;
  std::vector<std::vector<std::vector<double> > > m_eAtt;
  std::vector<std::vector<std::vector<double> > > m_eLor;
  std::vector<std::vector<std::vector<double> > > m_eVelWv;
  std::vector<std::vector<std::vector<double> > > m_eVelWr;
  std::vector<std::vector<std::vector<double> > > m_eRIon;
  std::vector<std::vector<std::vector<double> > > m_eRAtt;

  std::vector<std::vector<std::vector<std::vector<double> > > > m_eDifM;

  // Holes
  std::vector<std::vector<std::vector<double> > > m_hVelE;
  std::vector<std::vector<std::vector<double> > > m_hVelX;
  std::vector<std::vector<std::vector<double> > > m_hVelB;
  std::vector<std::vector<std::vector<double> > > m_hDifL;
  std::vector<std::vector<std::vector<double> > > m_hDifT;
  std::vector<std::vector<std::vector<double> > > m_hAlp;
  std::vector<std::vector<std::vector<double> > > m_hAtt;

  std::vector<std::vector<std::vector<std::vector<double> > > > m_hDifM;

  // Ions
  std::vector<std::vector<std::vector<double> > > m_iMob;
  std::vector<std::vector<std::vector<double> > > m_iVel;
  std::vector<std::vector<std::vector<double> > > m_iDifL;
  std::vector<std::vector<std::vector<double> > > m_iDifT;
  std::vector<std::vector<std::vector<double> > > m_iDis;
  // Negative ions
  std::vector<std::vector<std::vector<double> > > m_nMob;
  std::vector<std::vector<std::vector<double> > > m_nVel;

  // Thresholds for Townsend, attachment and dissociation coefficients.
  std::size_t m_eThrAlp{0};
  std::size_t m_eThrAtt{0};
  std::size_t m_hThrAlp{0};
  std::size_t m_hThrAtt{0};
  std::size_t m_iThrDis{0};

  // Extrapolation methods (TODO: enum).
  std::pair<std::size_t, std::size_t> m_extrVel = {0, 1};
  std::pair<std::size_t, std::size_t> m_extrDif = {0, 1};
  std::pair<std::size_t, std::size_t> m_extrAlp = {0, 1};
  std::pair<std::size_t, std::size_t> m_extrAtt = {0, 1};
  std::pair<std::size_t, std::size_t> m_extrLor = {0, 1};
  std::pair<std::size_t, std::size_t> m_extrMob = {0, 1};
  std::pair<std::size_t, std::size_t> m_extrDis = {0, 1};

  // Interpolation methods
  std::size_t m_intpVel{2};
  std::size_t m_intpDif{2};
  std::size_t m_intpAlp{2};
  std::size_t m_intpAtt{2};
  std::size_t m_intpLor{2};
  std::size_t m_intpMob{2};
  std::size_t m_intpDis{2};

  bool Velocity(const double ex, const double ey, const double ez,
                const double bx, const double by, const double bz,
                const std::vector<std::vector<std::vector<double> > >& velE,
                const std::vector<std::vector<std::vector<double> > >& velB,
                const std::vector<std::vector<std::vector<double> > >& velX,
                const double q, double& vx, double& vy, double& vz) const;
  bool VelocityFluxBulk(
      const double ex, const double ey, const double ez, const double bx,
      const double by, const double bz,
      const std::vector<std::vector<std::vector<double> > >& velWv,
      const std::vector<std::vector<std::vector<double> > >& velWr, double& wv,
      double& wr) const;
  static void Langevin(const double ex, const double ey, const double ez,
                       double bx, double by, double bz, const double mu,
                       double& vx, double& vy, double& vz);
  static void Langevin(const double ex, const double ey, const double ez,
                       double bx, double by, double bz, const double mu,
                       const double muH, double& vx, double& vy, double& vz);
  bool Diffusion(const double ex, const double ey, const double ez,
                 const double bx, const double by, const double bz,
                 const std::vector<std::vector<std::vector<double> > >& difL,
                 const std::vector<std::vector<std::vector<double> > >& difT,
                 double& dl, double& dt) const;
  bool Diffusion(
      const double ex, const double ey, const double ez, const double bx,
      const double by, const double bz,
      const std::vector<std::vector<std::vector<std::vector<double> > > >& diff,
      double cov[3][3]) const;
  bool Alpha(const double ex, const double ey, const double ez, const double bx,
             const double by, const double bz,
             const std::vector<std::vector<std::vector<double> > >& tab,
             std::size_t intp, const std::size_t thr,
             const std::pair<std::size_t, std::size_t>& extr,
             double& alpha) const;
  double GetAngle(const double ex, const double ey, const double ez,
                  const double bx, const double by, const double bz,
                  const double e, const double b) const;
  bool Interpolate(const double e, const double b, const double a,
                   const std::vector<std::vector<std::vector<double> > >& table,
                   double& y, const std::size_t intp,
                   const std::pair<std::size_t, std::size_t>& extr,
                   const bool logval = false) const;

  double Interpolate1D(const double e, const std::vector<double>& table,
                       const std::vector<double>& fields,
                       const std::size_t intpMeth,
                       const std::pair<std::size_t, std::size_t>& extr,
                       const bool logval = false) const;

  bool SetEntry(const std::size_t i, const std::size_t j, const std::size_t k,
                const std::string& fcn,
                std::vector<std::vector<std::vector<double> > >& tab,
                const double val);
  bool GetEntry(const std::size_t i, const std::size_t j, const std::size_t k,
                const std::string& fcn,
                const std::vector<std::vector<std::vector<double> > >& tab,
                double& val) const;

  void SetExtrapolationMethod(const std::string& low, const std::string& high,
                              std::pair<std::size_t, std::size_t>& extr,
                              const std::string& fcn);
  bool GetExtrapolationIndex(std::string str, std::size_t& nb) const;
  std::size_t SetThreshold(
      const std::vector<std::vector<std::vector<double> > >& tab) const;

  void Clone(std::vector<std::vector<std::vector<double> > >& tab,
             const std::vector<double>& efields,
             const std::vector<double>& bfields,
             const std::vector<double>& angles, const std::size_t intp,
             const std::pair<std::size_t, std::size_t>& extr, const double init,
             const std::string& label);
  void Clone(std::vector<std::vector<std::vector<std::vector<double> > > >& tab,
             const std::size_t n, const std::vector<double>& efields,
             const std::vector<double>& bfields,
             const std::vector<double>& angles, const std::size_t intp,
             const std::pair<std::size_t, std::size_t>& extr, const double init,
             const std::string& label);

  void Init(const std::size_t nE, const std::size_t nB, const std::size_t nA,
            std::vector<std::vector<std::vector<double> > >& tab,
            const double val);
  void Init(const std::size_t nE, const std::size_t nB, const std::size_t nA,
            const std::size_t nT,
            std::vector<std::vector<std::vector<std::vector<double> > > >& tab,
            const double val);
};

}  // namespace Garfield
#endif
