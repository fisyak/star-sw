// $Id: StarMCSimplePrimaryGenerator.cxx,v 1.1.1.1 2008/12/10 20:45:52 fisyak Exp $
#include "StarMCSimplePrimaryGenerator.h"
#include "TFile.h"
#include "TGeant3.h"
#include "TF1.h"
#include "TEnv.h"
#include "TRandom.h"
#include "TSystem.h"
#include "TDatabasePDG.h"
#include "TParticlePDG.h"
#include "StDetectorDbMaker/St_vertexSeedC.h"
#include "StDetectorDbMaker/St_beamInfoC.h"
#include "StMessMgr.h" 
ClassImp(StarMCSimplePrimaryGenerator);
//_____________________________________________________________________________
StarMCSimplePrimaryGenerator::StarMCSimplePrimaryGenerator(Int_t    nprim,   Int_t    Id, 
							   Double_t pT_min , Double_t pT_max,
							   Double_t Eta_min, Double_t Eta_max, 
							   Double_t Phi_min, Double_t Phi_max, 
							   Double_t Z_min,   Double_t Z_max, 
							   const Char_t *option): StarMCPrimaryGenerator() {
  PreSet(); 
  SetGenerator(nprim, Id, pT_min, pT_max, Eta_min, Eta_max, 
	       Phi_min, Phi_max,  Z_min, Z_max, option);
}
//_____________________________________________________________________________
void StarMCSimplePrimaryGenerator::PreSet() {
  fStarStack = 0;
  fIsRandom = false;
  fNofPrimaries = 0; fId = 0;
  fpT_min = 0; fpT_max = 0; fEta_min = 0; fEta_max = 0; fPhi_min = 0; fPhi_max = 0; fZ_min = 0; fZ_max = 0;
  fOption = "";
  fOrigin = TVector3(0,0,0);
  fCurOrigin = fOrigin;
  fGun = kFALSE;
  fGunpX = fGunpY = fGunpZ = fGunX = fGunY = fGunZ = 0;
  fGunId = 0;
  fPVX = fPVY = fPVZ = fPVxyError = 0;
  fPVxy = 0;
}
//_____________________________________________________________________________
void StarMCSimplePrimaryGenerator::GeneratePrimary() {     
  // Add one primary particle to the user stack (derived from TVirtualMCStack).
  // Track ID (filled by stack)
  static TF1 *dNdpT = 0; 
  Int_t ntr;
  // Option: to be tracked
  Int_t toBeDone = 1; 
  for (Int_t i=0; i<fNofPrimaries; i++) {
    // Particle type
    for (auto xId : fGunIds) {
      Int_t pdg  = xId;
      if (fGun) pdg = fGunId;
      if (fOption.Contains("sw",TString::kIgnoreCase)) {
	if (gRandom->Rndm() > 0.5) pdg = - pdg;
      }
      Double_t mass      = TDatabasePDG::Instance()->GetParticle(pdg)->Mass();
      Double_t charge    = TDatabasePDG::Instance()->GetParticle(pdg)->Charge()/3.;
      // Polarization
      Double_t polx = 0.; 
      Double_t poly = 0.; 
      Double_t polz = 0.; 
      Double_t px = 0, py = 0, pz = 0;
      Double_t vx = 0, vy = 0, vz = 0;
      Double_t tof = 0.;
      if (fGun) {
	px = fGunpX; py = fGunpY; pz = fGunpZ; vx = fGunX; vy = fGunY; vz = fGunZ; 
      } else {
	// Position
	vx  = fCurOrigin.X(); 
	vy  = fCurOrigin.Y(); 
	vz =  fCurOrigin.Z(); 
	// Energy (in GeV)
	Double_t eta       = fEta_min + (fEta_max - fEta_min)*gRandom->Rndm();
	Double_t phi       = fPhi_min + (fPhi_max - fPhi_min)*gRandom->Rndm();
	Double_t pT        = 0;
	if (fOption.Contains("pflat",TString::kIgnoreCase)) {
	  // Flat in momentum
	  Double_t p = fpT_min + (fpT_max - fpT_min)*gRandom->Rndm();
	  pT = p/TMath::CosH(eta);
	  px = pT*TMath::Cos(phi); 
	  py = pT*TMath::Sin(phi);
	  pz = pT*TMath::SinH(eta);
	} else {
	  if (fOption.Contains("BLpion",TString::kIgnoreCase)) {
	    Double_t p = -1;
	    Double_t bgL10   = fpT_min + (fpT_max - fpT_min)*gRandom->Rndm();
	    Double_t bg      = TMath::Power(10.,bgL10);
	    p       = 0.13956995*bg*TMath::Abs(charge);
	    pT               = p/TMath::CosH(eta);
	  } else if (fOption.Contains("BL",TString::kIgnoreCase)) {
	    Double_t p = -1;
	    Double_t bgL10   = fpT_min + (fpT_max - fpT_min)*gRandom->Rndm();
	    Double_t bg      = TMath::Power(10.,bgL10);
	    p       = mass*bg;
	    pT               = p/TMath::CosH(eta);
	  } else if (fOption.Contains("mtsq",TString::kIgnoreCase)) {
	    if (! dNdpT) {
	      dNdpT = new TF1("dNdpT","x*TMath::Exp(-TMath::Sqrt(x*x+[0]*[0])/[1])", fpT_min,fpT_max);
	      dNdpT->SetParameters(mass,Temperature());
	    }
	    pT = dNdpT->GetRandom();
	  } else if (fOption.Contains("mt",TString::kIgnoreCase)) {
	    while (pT < fpT_min || pT > fpT_max) {
	      Double_t mT = mass -Temperature()*TMath::Log(gRandom->Rndm());
	      Double_t pT2 = mT*mT - mass*mass;
	      pT  = TMath::Sqrt(pT2);
	    }
	  } else {
	    pT               = fpT_min + (fpT_max - fpT_min)*gRandom->Rndm();
	  }
	  // Particle momentum
	  px = pT*TMath::Cos(phi); 
	  py = pT*TMath::Sin(phi);
	  if (fOption.Contains("y",TString::kIgnoreCase)) {
	    Double_t mT = TMath::Sqrt(pT*pT + mass*mass);
	    eta = gRandom->Gaus( fEta_min, fEta_max);
	    pz = mT*TMath::SinH(eta);
	  } else {
	    pz = pT*TMath::SinH(eta);
	  }
	}
      }
      // Double_t kinEnergy = 0.050;  
      Double_t e  = TMath::Sqrt(mass*mass + px*px +py*py + pz*pz);
      // Add particle to stack 
      fStarStack->PushTrack(toBeDone, -1, pdg, px, py, pz, e, vx, vy, vz, tof, polx, poly, polz, 
			    kPPrimary, ntr, 1., 2);
    }
  }
}
