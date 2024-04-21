// $Id: StarMCPrimaryGenerator.cxx,v 1.2 2011/02/11 16:12:52 fisyak Exp $
#include <map>
#include "TVirtualMC.h"
#include "TVirtualMCStack.h"
#include "TVirtualMCApplication.h"
#include "TRandom.h"
#include "TPDGCode.h"
#include "TDatabasePDG.h"
#include "TVector3.h"
#include "TMath.h"
#include "TRandom.h"
#include "Stiostream.h"
#include "StarMCPrimaryGenerator.h"
StarMCPrimaryGenerator *StarMCPrimaryGenerator::fgInstance = 0;
Double_t StarMCPrimaryGenerator::fTemperature = 0.457;; // GeV/c
ClassImp(StarMCPrimaryGenerator);
//________________________________________________________________________________
StarMCPrimaryGenerator::StarMCPrimaryGenerator() : fStatus(kStOK)  {
  memset(mBeg,0,mEnd-mBeg+1);
  fgInstance = this;
  if (! fStarStack) fStarStack = StarVMCApplication::Instance()->GetStack();
  TString path(".");
  TString File("PVxyz.root");
  Char_t *file = gSystem->Which(path,File,kReadPermission);
  if (file) {
    TFile *PVfile = TFile::Open(file);
    if (PVfile) {
      fPVX = (TH1 *) PVfile->Get("x"); assert(fPVX); fPVX->SetDirectory(0);
      fPVY = (TH1 *) PVfile->Get("y"); assert(fPVY); fPVY->SetDirectory(0);
      fPVZ = (TH1 *) PVfile->Get("z"); assert(fPVZ); fPVZ->SetDirectory(0);
      fPVxyError = (TH1 *) PVfile->Get("hPVError"); if (fPVxyError) fPVxyError->SetDirectory(0);
      delete PVfile;
      LOG_WARN << "PVxyz.root with x, y and z histograms has been found. These histogram will be use to generate primary vertex x, y, z." << endm;
      if (fPVxyError) LOG_WARN << " hPVError histogram will be used for transverse PV error." << endm;
    }
    delete [] file;
  }
}
//_____________________________________________________________________________
void StarMCPrimaryGenerator::SetGenerator(Int_t nprim, Int_t Id, 
					  Double_t pT_min,Double_t pT_max,
					  Double_t Eta_min, Double_t Eta_max, 
					  Double_t Phi_min, Double_t Phi_max, 
					  Double_t Z_min, Double_t Z_max, const Char_t *option) {
  fGun = kFALSE;
  fSimpleKine = kTRUE;
  fNofPrimaries = nprim; 
  fpT_min = pT_min; 
  fpT_max = pT_max; 
  fEta_min = Eta_min; 
  fEta_max = Eta_max; 
  fPhi_min = Phi_min; 
  fPhi_max = Phi_max; 
  fZ_min = Z_min; 
  fZ_max = Z_max; 
  fOption = option; 
  fGunIds.clear();
  if (fOption.Contains("G",TString::kIgnoreCase)) {
    while (Id > 0) {
      Int_t id = Id%1000;
      Id /= 1000;
      fId = ((TGeant3* ) TVirtualMC::GetMC())->PDGFromId(id);
      fGunIds.push_back(fId);
    }
  } else {
    fGunIds.push_back(Id);
  }
  assert(fGunIds.size());
  LOG_INFO << "Generate " << fNofPrimaries << " primary tracks with option :" << fOption.Data() << " of type ";
  for (auto xId : fGunIds) {
    LOG_INFO << "\t"<< xId;
  }
  LOG_INFO << " in ";
  if (! fOption.Contains("BL",TString::kIgnoreCase)) {
    LOG_INFO << fpT_min << " <  pT < " << fpT_max << " with " <<  fOption.Data() <<  endm;
  } else {
    LOG_INFO << fpT_min << " <  log10(beta*gamma) < " << fpT_max << " with " <<  fOption.Data() <<  endm;
  }
  if (fOption.Contains("mtsq",TString::kIgnoreCase)) {
    LOG_INFO << "Use dN/dmT^2 = exp(-mT/T) pT generation with T = " << Temperature() << " GeV/c" << endm;
  }  
  if (fOption.Contains("sw",TString::kIgnoreCase)) {
    LOG_INFO << "Use randomly switch particle <=> antipartilce " << endm;
  } else if (fOption.Contains("mt",TString::kIgnoreCase)) {
    LOG_INFO << "Use dN/dmT = exp(-mT/T) pT generation with T = " << Temperature() << " GeV/c" << endm;
  }
  if ( fOption.Contains("y",TString::kIgnoreCase)) {
    if ( St_beamInfoC::instance()->IsFixedTarget()) {
      fEta_min =  St_beamInfoC::instance()->Ycms();
      fEta_max = 0.5;
    }
    LOG_INFO << "Rapidity is Gaussian with mean =  " << fEta_min  << " and sigma = " << fEta_max << endm;
  } else {
    LOG_INFO << fEta_min  << " < eta < " << fEta_max  << endm;
  }
  LOG_INFO << fPhi_min<< " < phi < " << fPhi_max<< endm;
  LOG_INFO << fZ_min  << " < zVer< " << fZ_max  << endm;
  
  fgInstance = this;
}
//________________________________________________________________________________
Int_t StarMCPrimaryGenerator::Skip(Int_t nskip) {
  return kStOK;
}
//________________________________________________________________________________
void StarMCPrimaryGenerator::Print(Option_t *option) const {
  if (fStarStack) fStarStack->Print();
}
//________________________________________________________________________________
void StarMCPrimaryGenerator::SetStack(StarParticleStack *stack) {
  if (! stack) return;
  // Option: to be tracked
  Int_t toBeDone = 1; 
  // Particle type
  //  Int_t pdg  = 0;
  // Polarization
  Double_t polx = 0.; 
  Double_t poly = 0.; 
  Double_t polz = 0.; 
  // Position
  Double_t weight = 1;
  // Particle momentum
  TParticle *part = 0;
  //  Int_t itrk = -1;
  Int_t ntr  =  0;
  Int_t nop  = stack->Particles()->GetEntriesFast();
  std::map<Int_t,Int_t> IdOld2New;
  for (Int_t i = 0; i < nop; i++) {
    //  while ((part = stack->PopNextTrack(itrk))) {
    IdOld2New[i] = -1;
    part = stack->GetParticle(i);
    if ( part->GetStatusCode() != 1 ) continue;
    IdOld2New[i] = ntr;
    Int_t parent = IdOld2New[part->GetFirstMother()];
    //    cout << "IdOld2New[" << i << "] = " << IdOld2New[i] << " old " << part->GetFirstMother() << " new " << parent << endl;
  // Load a track on the stack
  //
  // done     0 if the track has to be transported
  //          1 if not
  // parent   identifier of the parent track. -1 for a primary
  // pdg    particle code
  // pmom     momentum GeV/c
  // vpos     position
  // polar    polarization
  // tof      time of flight in seconds
  // mecha    production mechanism
  // ntr      on output the number of the track stored
    fStarStack->PushTrack(toBeDone, parent, part->GetPdgCode(), part->Px(), part->Py(), part->Pz(), part->Energy(), 
			  part->Vx(), part->Vy(), part->Vz(), part->T(), polx, poly, polz, 
			  kPPrimary, ntr, weight,  part->GetStatusCode());
  }
}
//_____________________________________________________________________________
void StarMCPrimaryGenerator::GeneratePrimaries() {
  static Double_t sigmaX = gEnv->GetValue("FixedSigmaX", 0.00176);
  static Double_t sigmaY = gEnv->GetValue("FixedSigmaY", 0.00176);
  static Double_t sigmaZ = gEnv->GetValue("FixedSigmaZ", 0.00176);
  if (fSetVertex) {
    TVector3 dR(gRandom->Gaus(0, sigmaX), gRandom->Gaus(0, sigmaY), gRandom->Gaus(0, sigmaZ));
    fCurOrigin = fOrigin + dR;
  } else  if (fSimpleKine) {
    TVector3 dR(gRandom->Gaus(0, sigmaX), gRandom->Gaus(0, sigmaY), fZ_min + (fZ_max - fZ_min)*gRandom->Rndm());
    fCurOrigin = fOrigin + dR;
  } else if (fPVX && fPVY && fPVZ) {
    fCurOrigin.SetX(fPVX->GetRandom());
    fCurOrigin.SetY(fPVY->GetRandom());
    fCurOrigin.SetZ(fPVZ->GetRandom());
    if (fPVxyError) {
      Double_t dxy = fPVxyError->GetRandom()/TMath::Sqrt(2.);
      gEnv->SetValue("FixedSigmaX", dxy);
      gEnv->SetValue("FixedSigmaY", dxy);
    }
  } else {
    fCurOrigin.SetX(gRandom->Gaus(0,gSpreadX));
    fCurOrigin.SetY(gRandom->Gaus(0,gSpreadY));
    fCurOrigin.SetZ(gRandom->Gaus(0,gSpreadZ));
  }
  GeneratePrimary();  
  fStarStack->SetNprimaries(fNofPrimaries);
  if (fDebug) Print();
}
//________________________________________________________________________________
void StarMCPrimaryGenerator::SetGun(Int_t Id, 
				    Double_t px, Double_t py, Double_t pz,
				    Double_t x, Double_t y, Double_t z, const Char_t *option) {
  fGun = kTRUE;
  fGunpX = px; fGunpY = py; fGunpZ = pz; fGunX = x; fGunY = y; fGunZ = z; 
  fOption = option;
  if (fOption.Contains("G",TString::kIgnoreCase)) {
    fGunId = ((TGeant3* ) TVirtualMC::GetMC())->PDGFromId(Id);
  } else {
    fGunId = Id;
  }
  LOG_INFO << "StarMCSimplePrimaryGenerator::SetGun\tid = " << fGunId 
       << "\tpxyz = (" << fGunpX << "," << fGunpY << "," << fGunpZ
       << ")\txyz = (" << fGunX << "," << fGunY << "," << fGunZ << ")" << endm;
}
