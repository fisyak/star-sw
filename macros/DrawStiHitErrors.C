/*
  root.exe 'Db.C("Geometry/tpc/tpcPadConfig","3p85GeV_fixedTarget_2019")' DrawStiHitErrors.C+

 c1 = new TCanvas("c1","Sti errors")
c1->Divide(2,2)
c1->cd(1)
InnPad->Draw("colz")
InnPad->GetHistograms()->SetTitle("Inner pad")
InnPad->GetHistogram()->SetTitle("Inner pad")
c1->cd(2)
OutPad->Draw("colz")
OutPad->GetHistogram()->SetTitle("Outer pad")
c1->cd(3)
InnTime->Draw("colz")
InnTime->GetHistogram()->SetTitle("Inner time")
c1->cd(4)
OutTime->Draw("colz")
OutTime->GetHistogram()->SetTitle("Outer time")
 
*/
#include "TF2.h"
#include "StDetectorDbMaker/St_tpcPadConfigC.h"
#include "StDetectorDbMaker/StiTpcInnerHitErrorCalculator.h"
#include "StDetectorDbMaker/StiTpcOuterHitErrorCalculator.h"
#include "StDetectorDbMaker/St_tpcDriftVelocityC.h"
//________________________________________________________________________________
Double_t InnerTpcPadErrors(Double_t *x, Double_t *p = 0) {
  Double_t Z = x[0];
  Double_t tanP = x[1];
  Double_t padPitch =  St_tpcPadConfigC::instance()->innerSectorPadPitch(1);
  Double_t eta = TMath::ATan(tanP);
  Double_t tanL = 0;
  Double_t ecross, edip;
  StiTpcInnerHitErrorCalculator::instance()->calculateError(Z, eta, tanL, ecross, edip);
  return TMath::Sqrt(ecross)/padPitch;
}
//________________________________________________________________________________
Double_t OuterTpcPadErrors(Double_t *x, Double_t *p = 0) {
  Double_t Z = x[0];
  Double_t tanP = x[1];
  Double_t padPitch =  St_tpcPadConfigC::instance()->innerSectorPadPitch(1);
  Double_t eta = TMath::ATan(tanP);
  Double_t tanL = 0;
  Double_t ecross, edip;
  StiTpcOuterHitErrorCalculator::instance()->calculateError(Z, eta, tanL, ecross, edip);
  return TMath::Sqrt(ecross)/padPitch;
}
//________________________________________________________________________________
Double_t InnerTpcTimeErrors(Double_t *x, Double_t *p = 0) {
  Double_t Z = x[0];
  Double_t tanP = 0;
  Double_t timePitch = St_tpcDriftVelocityC::instance()->timeBucketPitch();
  Double_t eta = TMath::ATan(tanP);
  Double_t tanL = x[1];
  Double_t ecross, edip;
  StiTpcInnerHitErrorCalculator::instance()->calculateError(Z, eta, tanL, ecross, edip);
  return TMath::Sqrt(edip)/timePitch;
}
//________________________________________________________________________________
Double_t OuterTpcTimeErrors(Double_t *x, Double_t *p = 0) {
  Double_t Z = x[0];
  Double_t tanP = 0;
  Double_t timePitch = St_tpcDriftVelocityC::instance()->timeBucketPitch();
  Double_t eta = TMath::ATan(tanP);
  Double_t tanL = x[1];
  Double_t ecross, edip;
  StiTpcOuterHitErrorCalculator::instance()->calculateError(Z, eta, tanL, ecross, edip);
  return TMath::Sqrt(edip)/timePitch;
}
//________________________________________________________________________________
void DrawStiHitErrors() {
  TF2 *InnPad = new TF2("InnPad",InnerTpcPadErrors,-210,210,-5,5);
  TF2 *OutPad = new TF2("OutPad",OuterTpcPadErrors,-210,210,-5,5);
  TF2 *InnTime = new TF2("InnTime",InnerTpcTimeErrors,-210,210,-5,5);
  TF2 *OutTime = new TF2("OutTime",OuterTpcTimeErrors,-210,210,-5,5);
}
