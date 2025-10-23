//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
/// \file GarfieldPhysics.hh
/// \brief Definition of the GarfieldPhysics class
/// \author D. Pfeiffer
//
#ifndef GarfieldPhysics_h
#define GarfieldPhysics_h 1

#include <iostream>
#include <map>
#include <vector>

#include "Garfield/ComponentAnalyticField.hh"
#include "Garfield/MediumMagboltz.hh"
#include "Garfield/Sensor.hh"
#include "Garfield/TrackHeed.hh"

typedef std::pair<double, double> EnergyRange_MeV;
typedef std::map<const std::string, EnergyRange_MeV> MapParticlesEnergy;

class GarfieldParticle {
 public:
  GarfieldParticle(std::string particleName, double ekin_eV, double time,
                   double x_cm, double y_cm, double z_cm, double dx, double dy,
                   double dz)
      : fParticleName(particleName),
        fEkin_MeV(ekin_eV / 1000000),
        fTime(time),
        fx_mm(10 * x_cm),
        fy_mm(10 * y_cm),
        fz_mm(10 * z_cm),
        fdx(dx),
        fdy(dy),
        fdz(dz) {}
  ~GarfieldParticle() {}

  std::string getParticleName() const { return fParticleName; }
  double getX_mm() const { return fx_mm; }
  double getY_mm() const { return fy_mm; }
  double getZ_mm() const { return fz_mm; }
  double getEkin_MeV() const { return fEkin_MeV; }
  double getTime() const { return fTime; }
  double getDX() const { return fdx; }
  double getDY() const { return fdy; }
  double getDZ() const { return fdz; }

 private:
  std::string fParticleName;
  double fEkin_MeV, fTime, fx_mm, fy_mm, fz_mm, fdx, fdy, fdz;
};

class GarfieldPhysics {
 public:
  static GarfieldPhysics* GetInstance();
  static void Dispose();

  void InitializePhysics();

  void DoIt(std::string particleName, double ekin_MeV, double time, double x_cm,
            double y_cm, double z_cm, double dx, double dy, double dz);

  void AddParticleName(const std::string particleName, double ekin_min_MeV,
                       double ekin_max_MeV, std::string program);
  bool FindParticleName(const std::string name,
                        std::string program = "garfield");
  bool FindParticleNameEnergy(std::string name, double ekin_MeV,
                              std::string program = "garfield");
  double GetMinEnergyMeVParticle(std::string name,
                                 std::string program = "garfield");
  double GetMaxEnergyMeVParticle(std::string name,
                                 std::string program = "garfield");
  void SetIonizationModel(std::string model, bool useDefaults = true);
  std::string GetIonizationModel();
  const std::vector<GarfieldParticle>& GetSecondaryParticles() const {
    return fSecondaryParticles;
  }
  void EnableCreateSecondariesInGeant4(bool flag) {
    createSecondariesInGeant4 = flag;
  }
  bool GetCreateSecondariesInGeant4() const {
    return createSecondariesInGeant4;
  }
  double GetEnergyDeposit_MeV() const { return fEnergyDeposit / 1000000; }
  double GetAvalancheSize() const { return fAvalancheSize; }
  double GetGain() const { return fGain; }
  void Clear() {
    fEnergyDeposit = 0;
    fAvalancheSize = 0;
    fGain = 0;
    nsum = 0;
  }

 private:
  GarfieldPhysics() = default;
  ~GarfieldPhysics();

  std::string fIonizationModel = "PAIPhot";

  static GarfieldPhysics* fGarfieldPhysics;

  MapParticlesEnergy fMapParticlesEnergyGeant4;
  MapParticlesEnergy fMapParticlesEnergyGarfield;
  Garfield::MediumMagboltz* fMediumMagboltz = nullptr;
  Garfield::Sensor* fSensor = nullptr;
  Garfield::TrackHeed* fTrackHeed = nullptr;
  Garfield::ComponentAnalyticField* fComponentAnalyticField = nullptr;

  std::vector<GarfieldParticle> fSecondaryParticles;

  bool createSecondariesInGeant4 = false;
  double fEnergyDeposit = 0.;
  double fAvalancheSize = 0.;
  double fGain = 0.;
  int nsum = 0;
};
#endif /* GARFIELDMODELCONFIG_HH_ */
