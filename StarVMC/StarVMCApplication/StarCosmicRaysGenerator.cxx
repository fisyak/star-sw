// $Id: StarCosmicRaysGenerator.cxx,v 1.1.1.1 2008/12/10 20:45:52 fisyak Exp $
#include "StarCosmicRaysGenerator.h"
#include "TGeant3.h"
#include "TRandom.h"
#include "StDcaGeometry.h"
#include "StarMagField.h"

ClassImp(StarCosmicRaysGenerator);
//_____________________________________________________________________________
void StarCosmicRaysGenerator::GeneratePrimary() {     
  // Add one primary particle to the user stack (derived from TVirtualMCStack).
  // Track ID (filled by stack)
 // Particle type
  Int_t pdg = 13;
  static TF1 *pTC = 0;
  static TF1 *PsiDeg = 0;
  static TF1 *Tan = 0;
  static TF1 *Z = 0;
  static TF1 *Imp = 0;
  static Double_t hz = 0;
  static Double_t R = 190;
  if (! pTC) {
    Double_t x[3] = {0};
    Double_t h[3];
    StarMagField::Instance()->BField(x,h);
    static const double EC = 2.99792458e-4;
    hz = EC*h[2];
    // track paraameters at DCA
    // CosmicT->Draw("(K.mPti+L.mPti)*TMath::Sqrt(2.)/TMath::Abs(K.mPti-L.mPti):-TMath::Log10(TMath::Abs(K.mPti-L.mPti)/2.)>>DpT(30,-1,2,100,-0.2,0.2)","noFitpK>30&&noFitpL>30&&chi2<200","colz");
    // DpT->ProjectionX();
    Double_t parspTC[3] = {  53711.86,   0.321477,  0.4805627}; //log_10{pT} for Cosmics from 2021 
    pTC = new TF1("CosmicpTC","gaus",-1,2);
    pTC->SetParameters(parspTC);
    // CosmicT->Draw("(K.mPti+L.mPti)*TMath::Sqrt(2.)/TMath::Abs(K.mPti-L.mPti):K.mPsi>>DpTPsi(30,-1,2,180,-TMath::Pi(),TMath::Pi())","noFitpK>30&&noFitpL>30&&chi2<200","colz");
    Double_t parsPsi[3] = {   29660.6,   90.92847,   34.81385}; //TMath::RadToDeg()*K.mPsi
    PsiDeg = new TF1("CosmicPsiDeg","gaus",0,180);
    PsiDeg->SetParameters(parsPsi);
    Double_t parsTan[3] = {  31406.37, 0.02250112,  0.3284674}; //K.mTan
    Tan = new TF1("CosmicTan","gaus",-1,1);
    Tan->SetParameters(parsTan);
    Z = new TF1("CosmicZ","pol2",-150,150);
    Double_t parsZ[3] = {  11451.63,   1.021042, -0.5117674}; //K.mZ
    Z->SetParameters(parsZ);
    Imp = new TF1("CosmicImp","pol2",-50,50);
    Double_t parsImp[3] = {  19284.88,  0.9062881,   2.684979}; //K.mImp
    Imp->SetParameters(parsImp);
  }
  Double_t dir[3], xyz[3];
  Int_t iter = 0;
  Double_t pMom = -1;
  while (1) {
    iter++;
    if (gRandom->Rndm() > 0.5) pdg = -pdg;
    Double_t mImp = Imp->GetRandom();
    Double_t mZ = Z->GetRandom();
    Double_t mPsi = PsiDeg->GetRandom()*TMath::DegToRad();
    Double_t charge = TDatabasePDG::Instance()->GetParticle(pdg)->Charge()/3.;
    Double_t pTL10 = pTC->GetRandom();
    Double_t pT    = TMath::Power(10., pTL10);
    Double_t mpTin = - charge/pT;
    Double_t mCurv = hz * mpTin; 
    Double_t mTan = Tan->GetRandom();
    Double_t setp[6] = {mImp, mZ, mPsi, mpTin, mTan, mCurv};
    Double_t sete[15] = {0};
    pMom = pT*TMath::Sqrt(1. + mTan*mTan);
    StDcaGeometry dca;
    dca.set(setp,sete);
    THelixTrack thelix = dca.thelix();
    //                                 -R  x  y  z x^2 y^2
    static Double_t Refsurfice[6] = {-R*R, 0, 0, 0,  1,  1};
    Double_t step = thelix.Step(1e3, Refsurfice, 6, xyz, dir, 1);
    if (TMath::Abs(step) < 100) continue;
    if (TMath::Abs(step) > 1e3) continue;
    if (TMath::Abs(xyz[2]) > 200) continue;
    break;
  }; 
  TVector3 P(dir); 
  TVector3 Vtx(xyz);
  if (Vtx.Dot(P) > 0) P *= -pMom;
  else                P *=  pMom;
  // Option: to be tracked
  Int_t toBeDone = 1; 
  // Polarization
  Double_t polx = 0.; 
  Double_t poly = 0.; 
  Double_t polz = 0.; 
  Double_t mass = TDatabasePDG::Instance()->GetParticle(pdg)->Mass();
  Double_t e  = TMath::Sqrt(mass*mass + pMom*pMom);
  Double_t tof = 0;
  // Add particle to stack 
  Int_t ntr = 1;
  fStarStack->PushTrack(toBeDone, -1, pdg, P.Px(), P.Py(), P.Pz(), e, Vtx.x(), Vtx.y(), Vtx.z(), tof, polx, poly, polz, 
			kPPrimary, ntr, 1., 2);
  fNofPrimaries = 1;
}
