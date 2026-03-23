void FXT(Double_t eta = -1.55) {
  TCanvas* c2 = new TCanvas("TPC","TPC");
  c2->DrawFrame(-200,0,200,200);
  TF1 *Eta = new TF1("Eta","(x-200)/TMath::SinH([0])",-200,200);
  Eta->SetParameter(0,eta);
  Eta->Draw("same");
}
/*
   tan(Theta/2) = exp(-eta);
   
   tan(Theta) = 2*tan(Thete/2)/(1 - tan^2(Theta/2)) = 2*Exp(-eta)/(1 - exp(-2*eta)) = 1/sinh(eta)
   cos(Theta) = 1./sqrt(1. + tan^2(Theta)) = 1./sqrt(1 + 1/sinh^2(eta)) = sinh(eta)/cosh(eta) = tanh(eta):
   sin(Theta) = tan(Theta)*cos(Theta) = 1/cosh(eta)



0pT = 0.5 							   
 eta = -1.45;  p = pT/sin(Theta) = pT*TMath::CosH(eta) =  p = 1.1244
 eta = -0.87                                              p = 0.7015
 eta = -2.2                                               p = 2.283 



p   = 0.5 							   
eta = -1.45;  pT = p*sin(Theta) = p/TMath::CosH(eta)  =  pT = 0.2224
eta = -0.87                                              pT = 0.3564
eta = -2.2                                               pT = 0.1094

*/
