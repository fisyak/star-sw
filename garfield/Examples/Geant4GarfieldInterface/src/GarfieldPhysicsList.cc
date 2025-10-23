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
/// \file GarfieldPhysicsList.cc
/// \brief Implementation of the GarfieldPhysicsList class

#include "GarfieldPhysicsList.hh"

#include "G4EmConfigurator.hh"
#include "G4FastSimulationManagerProcess.hh"
#include "G4LossTableManager.hh"
#include "G4PAIModel.hh"
#include "G4PAIPhotModel.hh"
#include "G4ProcessManager.hh"
#include "G4ProcessVector.hh"
#include "G4ProductionCuts.hh"
#include "G4Region.hh"
#include "G4RegionStore.hh"
#include "G4SystemOfUnits.hh"
#include "G4UnitsTable.hh"
#include "GarfieldPhysics.hh"
#include "QGSP_BERT_HP.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

GarfieldPhysicsList::GarfieldPhysicsList() : G4VModularPhysicsList() {
  G4int verb = 0;
  SetVerboseLevel(verb);
  defaultCutValue = 1 * CLHEP::mm;
  QGSP_BERT_HP* physicsList = new QGSP_BERT_HP;
  for (G4int i = 0;; ++i) {
    G4VPhysicsConstructor* elem =
        const_cast<G4VPhysicsConstructor*>(physicsList->GetPhysics(i));
    if (!elem) break;
    G4cout << "RegisterPhysics: " << elem->GetPhysicsName() << G4endl;
    RegisterPhysics(elem);
  }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

GarfieldPhysicsList::~GarfieldPhysicsList() {}

void GarfieldPhysicsList::AddParameterisation() {
  GarfieldPhysics* garfieldPhysics = GarfieldPhysics::GetInstance();

  std::string ionizationModel = garfieldPhysics->GetIonizationModel();

  auto fastSimProcess_garfield =
      new G4FastSimulationManagerProcess("G4FSMP_garfield");

  auto theParticleIterator = GetParticleIterator();
  theParticleIterator->reset();
  while ((*theParticleIterator)()) {
    G4ParticleDefinition* particle = theParticleIterator->value();
    G4ProcessManager* pmanager = particle->GetProcessManager();
    G4EmConfigurator* config = G4LossTableManager::Instance()->EmConfigurator();
    G4LossTableManager::Instance()->SetVerbose(1);

    auto particleName = particle->GetParticleName();
    if (garfieldPhysics->FindParticleName(particleName, "garfield")) {
      pmanager->AddDiscreteProcess(fastSimProcess_garfield);
    }

    if (garfieldPhysics->FindParticleName(particleName, "geant4")) {
      double eMin = MeV * garfieldPhysics->GetMinEnergyMeVParticle(particleName,
                                                                   "geant4");
      double eMax = MeV * garfieldPhysics->GetMaxEnergyMeVParticle(particleName,
                                                                   "geant4");
      if (ionizationModel == "PAI") {
        G4PAIModel* pai = new G4PAIModel(particle, "G4PAIModel");
        if (particleName == "e-" || particleName == "e+") {
          config->SetExtraEmModel(particleName, "eIoni", pai, "RegionGarfield",
                                  eMin, eMax, pai);
        } else if (particleName == "mu-" || particleName == "mu+") {
          config->SetExtraEmModel(particleName, "muIoni", pai, "RegionGarfield",
                                  eMin, eMax, pai);
        } else if (particleName == "proton" || particleName == "pi+" ||
                   particleName == "pi-") {
          config->SetExtraEmModel(particleName, "hIoni", pai, "RegionGarfield",
                                  eMin, eMax, pai);
        } else if (particleName == "alpha" || particleName == "He3" ||
                   particleName == "GenericIon") {
          config->SetExtraEmModel(particleName, "ionIoni", pai,
                                  "RegionGarfield", eMin, eMax, pai);
        }
      } else if (ionizationModel == "PAIPhot") {
        G4PAIPhotModel* paiPhot = new G4PAIPhotModel(particle, "G4PAIModel");
        if (particleName == "e-" || particleName == "e+") {
          config->SetExtraEmModel(particleName, "eIoni", paiPhot,
                                  "RegionGarfield", eMin, eMax, paiPhot);
        } else if (particleName == "mu-" || particleName == "mu+") {
          config->SetExtraEmModel(particleName, "muIoni", paiPhot,
                                  "RegionGarfield", eMin, eMax, paiPhot);
        } else if (particleName == "proton" || particleName == "pi+" ||
                   particleName == "pi-") {
          config->SetExtraEmModel(particleName, "hIoni", paiPhot,
                                  "RegionGarfield", eMin, eMax, paiPhot);
        } else if (particleName == "alpha" || particleName == "He3" ||
                   particleName == "GenericIon") {
          config->SetExtraEmModel(particleName, "ionIoni", paiPhot,
                                  "RegionGarfield", eMin, eMax, paiPhot);
        }
      }
    }
  }
}

void GarfieldPhysicsList::SetCuts() {
  G4ProductionCutsTable::GetProductionCutsTable()->SetEnergyRange(100. * eV,
                                                                  100. * TeV);

  SetCutsWithDefault();

  G4Region* region = G4RegionStore::GetInstance()->GetRegion("RegionGarfield");
  G4ProductionCuts* cuts = new G4ProductionCuts();
  cuts->SetProductionCut(1 * um, G4ProductionCuts::GetIndex("gamma"));
  cuts->SetProductionCut(1 * um, G4ProductionCuts::GetIndex("e-"));
  cuts->SetProductionCut(1 * um, G4ProductionCuts::GetIndex("e+"));
  if (region) {
    region->SetProductionCuts(cuts);
  }

  DumpCutValuesTable();
}

void GarfieldPhysicsList::ConstructParticle() {
  G4VModularPhysicsList::ConstructParticle();
}

void GarfieldPhysicsList::ConstructProcess() {
  G4VModularPhysicsList::ConstructProcess();
  AddParameterisation();
}
