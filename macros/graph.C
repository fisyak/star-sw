#include "TGraph.h"
TGraph *graph() {
  // Inner RF
  Double_t sigma_dRF =  0.02905;
  Double_t sigma_dRHF = 0.04392;
  Double_t sigma_dO   = 0.03107;
  //               RF                                                                          RHF       
  Double_t x[6] = {0.02218*10.12/10.12*0.95,  0.02218*10.12/ 2.77*0.95,                    0., 0.02218*10.12/ 3.28*0.95, 0.02218*10.12/ 1.63*0.95, 0.};
  Double_t y[6] = {0.02740      - sigma_dRF,  0.03574      - sigma_dRF, -0.00836 -  sigma_dRF, 0.04835     - sigma_dRHF,     0.06284 - sigma_dRHF,  -0.00546 - sigma_dRHF};
  return new TGraph(3,x,y);
}
//________________________________________________________________________________
TGraph *graphI() {
  // Inner RF
  Double_t sigma_dZF =  0.07816;
  Double_t sigma_dRF =  0.02905;
  Double_t sigma_dRHF = 0.04392;
  Double_t B[3]  = {5.0, 2.5, 0.};
  Double_t y[3] = {sigma_dRF, sigma_dRHF, sigma_dZF};
  return new TGraph(3,B,y);
}
//________________________________________________________________________________
TGraph *graphO() {
  // Inner RF
  Double_t sigma_dZF =   0.08254;
  Double_t sigma_dRF =  0.03107;
  Double_t sigma_dRHF =  0.04763;
  Double_t B[3]  = {5.0, 2.5, 0.};
  Double_t y[3] = {sigma_dRF, sigma_dRHF, sigma_dZF};
  return new TGraph(3,B,y);
}
