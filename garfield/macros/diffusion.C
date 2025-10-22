/* 10/07/2025
  root.exe lGarfield.C 'diffusion.C(0.5)'+
*/
#include "TGraph.h"
#include "TGraphErrors.h"
#ifndef __CINT__
#include <iostream>
#include <fstream>
#include "TSystem.h"
#include "TCanvas.h"
#include "TROOT.h"
#include "TApplication.h"
#include "TFile.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TSystem.h"
#include "TMath.h"
#include "GarfieldConstants.hh"
#include "ViewField.hh"
#include "ViewDrift.hh"
#include "ViewCell.hh"
#include "MediumMagboltz.hh"
#include "SolidBox.hh"
#include "GeometrySimple.hh"
#include "ComponentAnalyticField.hh"
#include "Sensor.hh"
#include "DriftLineRKF.hh"
#include "FundamentalConstants.hh"
#include "Random.hh"
#include "Plotting.hh"
using namespace Garfield;

void diffusion(Double_t BField = 0.5) {
  const Double_t BarPressure         = 1010.8; // [mbar], TPC-PTB, barometricPressure
  const Double_t inputTPCGasPressure = 1.93;   // [mbar], TPC-PT8, difference between barometer pressure and pressure in TPC
  const Double_t pressure = ((BarPressure + inputTPCGasPressure)/ 1000.) * 750.; // [torr], 1 bar = 750 torr 
  const Double_t temperature = 297.839; //273.15 + 24.7; // inputGasTemperature (degree K)
  Double_t Angle  = 0.0; // rad
  Int_t b = 10*BField;
  Int_t t = temperature;
  Int_t p = pressure;
  TString gasFile("../P10.");
  gasFile += Form("B%ikGT%iP%i",b,t,p);
  // Create a gas medium.  
  MediumMagboltz* gas = new MediumMagboltz();
  // Set the temperature [K] and pressure [Torr].
  gas->SetTemperature(temperature);
  gas->SetPressure(pressure);
  gas->SetMaxElectronEnergy(300.);
  // Specify the gas mixture.
  Double_t Fracs[2] = {0.9, 0.1};
  gas->SetComposition("ar", 100*Fracs[0], "ch4", 100*Fracs[1]);
#if 1
//   gas->SetFieldGrid(100.,100e3, 20, true, BField, BField, 1, Angle, Angle, 1);
//   gasFile += ".gas";
  gas->SetFieldGrid(100.,100e3, 20, true, BField, BField, 1, Angle, Angle, 1);
  gasFile += ".gas";
#else
  gas->SetFieldGrid(100.,300., 21, false, BField, BField, 1, Angle, Angle, 1);
  gasFile += "1kVNew.gas";
#endif
  const Double_t rPenning = 0.57;
  const Double_t lambdaPenning = 0.e-4;
  gas->EnablePenningTransfer(rPenning, lambdaPenning, "ch4");
  if (gSystem->AccessPathName(gasFile)) {
    // Use Magboltz to generate the gas table and grid.
    // Specfify te number of collission [1e7] over which the electron is traced in Magboltz
    const Int_t ncoll = 10; //[1e7]
    const Bool_t verbose = true;
    gas->GenerateGasTable(ncoll, verbose);
    // Save the gas table for later use
    gas->WriteGasFile(gasFile.Data());
  } else {
    gas->LoadGasFile(gasFile.Data());
  }
  //  gas->PrintGas();
  const Double_t yGG      =      0.; // Gating Grid
  const Double_t vGG      =   -115.; // Gating Grid
  const Double_t dvGG     =     75.; // alternative delta Voltage for closed GG
  const Double_t vCathode =  -27950;
  const Double_t yCathode =-208.707; // move into system where yGG = 0
  const Double_t eDrift   = (vCathode - vGG)/(yCathode - yGG); // = 133.36 V/cm 
  Double_t dl, dt;
  gas->ElectronDiffusion(0, 0, eDrift, 0, 0, BField, dl, dt);
  cout << "B = " << BField << "T, longitudinal = " << dl << " and transverse diffusion coefficients = " << dt <<endl;

  return;
}
#else
void diffusion() {}
#endif /* __CINT__ */
//________________________________________________________________________________
TGraph *Magboltz() {
/*
  B =  .5 T, longitudinal = 0.0361701 and transverse diffusion coefficients = 0.021982 sqrt(cm)
  B = 0.25T, longitudinal = 0.0361698 and transverse diffusion coefficients = 0.032902
  B =  0  T, longitudinal = 0.0362476 and transverse diffusion coefficients = 0.0595239
*/
  Double_t B[3]  = {5.0, 2.5, 0.}; // kG
  Double_t y[3] = { 0.021982,  0.032902, 0.0595239};
  return new TGraph(3,B,y);
}
//________________________________________________________________________________
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
#if 0
  Double_t sigma_dZF =  0.07816;
  Double_t sigma_dRF =  0.02905;
  Double_t sigma_dRHF = 0.04392;
  Double_t y[3] = {sigma_dRF, sigma_dRHF, sigma_dZF};
  Double_t B[3]  = {5.0, 2.5, 0.};
  return new TGraph(3,B,y);
#endif
  Double_t  y[3] = {0.02912, 0.04399, 0.07825};
  Double_t dy[3] = {1e-5,    1e-5, 1e-4};
  Double_t B[3]  = {5.0, 2.5, 0.};
  return new TGraphErrors(3,B,y, 0, dy);
  /*
root.exe [31] a=0;
root.exe [32] for (int i = 0; i <3 ; i++ ) {cout << i << "\t" << y[i]/m[i] << endl; a += y[i]/m[i];} cout << a/3 << endl;
0       1.32472
1       1.337
2       1.3146
1.32544
  */
}
//________________________________________________________________________________
TGraph *graphO() {
  // Outer RF
#if 0
  Double_t sigma_dZF =   0.08254;
  Double_t sigma_dRF =  0.03107;
  Double_t sigma_dRHF =  0.04763;
  Double_t B[3]  = {5.0, 2.5, 0.};
  Double_t y[3] = {sigma_dRF, sigma_dRHF, sigma_dZF};
  return new TGraph(3,B,y);
#else 
  Double_t  y[3] = {0.03102, 0.04764, 0.08256};
  Double_t dy[3] = {  3e-5,    2e-5,    8e-5};
  Double_t B[3]  = {5.0, 2.5, 0.};
  return new TGraphErrors(3,B,y, 0, dy);
  /* 
root.exe [28] for (int i = 0; i <3 ; i++ ) {cout << i << "\t" << y[i]/m[i] << endl; a += y[i]/m[i];} cout << a/3 << endl;
0       1.41115
1       1.44794
2       1.38701
1.41537
   */
#endif
}
/*
InnerPad                                                    OuterPad 		                        row.OmegaTau row.transverseDiffusion  row.transverseDiffusionI           row.T0offsetI  row.T0offsetO
              sigma_c            sigma_d  		    sigma_c             sigma_d
RF            0.2822 +/- 0.0002  0.02905 +/- 0.00001        0.4374 +/- 0.0002   0.03107 +/- 0.00003
TpcRS_RF      0.3153 +/- 0.0002  0.02740 +/- 0.00001        0.4954 +/- 0.0003   0.03138 +/- 0.00004     3.02         0.02218*10.12/10.12      row.longitudinalDiffusion*0.95     0.04382        -0.07167
TpcRS_RF_B    0.3214 +/- 0.0002  0.03574 +/- 0.00002        0.491  +/- 0.0001   0.04242 +/- 0.00004     2.585        0.02218* 2.77/ 2.77      row.longitudinalDiffusion*0.95     0.04557        -0.09477
TpcRS_RF_C    0.3131 +/- 0.0001 -0.00836 +/- 0.00003        0.497  +/- 0.0001  -0.00762 +/- 0.00012     2.585        0                        row.longitudinalDiffusion*0.95     0.04557        -0.09477
TpcRS_RF_D    0.3214 +/- 0.0002  0.03575 +/- 0.00002        0.491  +/- 0.0001   0.04242 +/- 0.00004 
TpcRS_RF_Q    0.3152 +/- 0.0002  0.02736 +/- 0.00002        0.4956 +/- 0.0003   0.03105 +/- 0.00004
RHF           0.2891 +/- 0.0001  0.04392 +/- 0.00001        0.4195 +/- 0.0002   0.04763 +/- 0.00002
TpcRS_RHF     0.3164 +/- 0.0001  0.04835 +/- 0.00002        0.4751 +/- 0.0001   0.05650 +/- 0.00001 
TpcRS_RHF_B   0.3061 +/- 0.0003  0.06284 +/- 0.00003        0.4706 +/- 0.0003   0.07200 +/- 0.00001     3.02         0.02218*10.12/ 3.28      row.longitudinalDiffusion*0.95     0.04382        -0.07167
TpcRS_RHF_C   0.31   +/- 0.0010 -0.00546 +/- 0.00002        0.489  +/- 0.0001  -0.00552 +/- 0.00002     2.585        0.02218* 2.77/ 1.63      row.longitudinalDiffusion*0.95     0.04557        -0.09477
TpcRS_RHF_D   0.3192 +/- 0.0002  0.04559 +/- 0.00001        0.476  +/- 0.0001   0.05576 +/- 0.00002
TpcRS_RHF_Q   0.3214 +/- 0.0001  0.04082 +/- 0.00001        0.4805 +/- 0.0003   0.04805 +/- 0.00002

ZF            0.2802 +/- 0.0010  0.07816 +/- 0.00010        0.4072 +/- 0.0008   0.08254 +/- 0.00008     2.585        0                        row.longitudinalDiffusion*0.95     0.04557        -0.09477

--------------------------------------------------------------------------------
10/10/25
Inner Pad                                            Outer Pad
             sigma_c            sigma_d              sigma_c            sigma_d
RF           0.2833 +/- 0.0002  0.02912 +/- 0.00001  0.4360 +/- 0.0001  0.03108 +/- 0.0003
TpcRS_RF_M   0.2413 +/- 0.0002  0.02969 +/- 0.00001  0.4405 +/- 0.0003  0.03131 +/- 0.0004
             0.1484
RF           0.2733 +/- 0.0002  0.02912 +/- 0.0001
            -0.1678
RHF          0.2808 +/- 0.0002  0.04399 +/- 0.00001  0.418  +/- 0.0001  0.04764 +/- 0.0002
TpcRS_RHF_M  0.2474 +/- 0.0002  0.04408 +/- 0.00001  0.4275 +/- 0.0002  0.04692 +/- 0.0002
             0.1328
  row.SigmaJitterXI         = 0.1461;//M2  0.; //0.1 + 0.037;
RHF          0.2806 +/- 0.0002  0.04399 +/- 0.00001  0.418  +/- 0.0001  0.04764 +/- 0.0002
TpcRS_RHF_M2 0.3211 +/- 0.0002  0.04390 +/- 0.00001  0.4275 +/- 0.0002  0.04692 +/- 0.0002
            -0.1561
ZF           0.2715 +/- 0.0010  0.07825 +/- 0.00010  0.4056 +/- 0.0008  0.08256 +/- 0.0008
TpcRS_ZF_M   0.2214 +/- 0.0012  0.08177 +/- 0.00010  0.4072 +/- 0.0007  0.08373 +/- 0.0008
             0.1571
             0.1461
ZF           0.2715 +/- 0.0010  0.07825 +/- 0.00010  0.4056 +/- 0.0008  0.08256 +/- 0.0008
TpcRS_ZF_M2  0.2844 +/- 0.0011  0.08316 +/- 0.00012  0.4072 +/- 0.0007  0.08373 +/- 0.0008
            -0.00847
19/11/25
  row.SigmaJitterXI         = 0.069; // M3 0.1461;//M2  0.; //0.1 + 0.037;
TpcRS_RF_M3  0.2595 +/- 0.0002  0.02976 +/- 0.00002
             0.0857
TpcRS_RHF_M3 0.2649 +/- 0.0002  0.04408 +/- 0.00001  0.4275 +/- 0.0002  0.04692 +/- 0.0002
             0.0925 
TpcRS_ZF_M3  0.2342 +/- 0.0012  0.08228 +/- 0.00012  0.4072 +/- 0.0007  0.08373 +/- 0.0008
             0.1373

double x[9] = {0, 0, 0, 0.1461, 0.1461, 0.1461, 0.069, 0.069, 0.069};
double y[9] = {0.1484, 0.1328, 0.1461, -0.1678, -0.1561, -0.00847, 0.0857, 0.0925, 0.1373};

double x[7] = {0, 0, 0, 0.1461, 0.1461, 0.069, 0.069};
double y[9] = {0.1484, 0.1328, 0.1461, -0.1678, -0.1561, 0.0857, 0.0925};

  row.SigmaJitterXI         = 0.104; // M40.069; // M3 0.1461;//M2  0.; //0.1 + 0.037;

Inner          sigma_c
RF             0.2733
TpcRS_RF_M4    0.2823
              -0.0714
RHF            0.2806
TpcRS_RHF_M4   0.2863
              -0.0568
ZF             0.2715
TpcRS_ZF_M4    0.2489
               0.1084
double x[9] = {0, 0, 0, 0.1461, 0.1461, 0.069, 0.069, 0.104, 0.104 };
double y[9] = {0.1484, 0.1328, 0.1461, -0.1678, -0.1561, 0.0857, 0.0925, -0.0714,  -0.0568};

  row.SigmaJitterXI         = 0.08915;// M4 0.104; // M40.069; // M3 0.1461;//M2  0.; //0.1 + 0.037;

  row.SigmaJitterTI         = 0.00000;// 0.4317;
  row.SigmaJitterTO         = 0.00000;// 0.4300;
Outer                                                              Inner
       sigma^2(Z=0) TpcRS                [-50,50]  TpcRS
RF    0.7638        0.6228  => 0.375     0.7706    0.6865 0.289    0.8775   0.6385  0.489
RHF   0.7669        0.639   => 0.356     0.7784    0.642  0.369    0.8882   0.6296  0.508
ZF    0.06228       0.7601               0.7369    0.6513 0.292    0.8134   0.5578  0.506 
<>                             0.365                      0.317                     0.501
  row.SigmaJitterTI         = 0.501; // M4
  row.SigmaJitterTO         = 0.317; // M4
M5
Pads                                    
Inner           TpcRS   Outer           
RF       0.2733 0.2703  0.436  0.442    
RHF      0.2806 0.2766  0.418  0.4265   2
ZF       0.2715 0.2339  0.4056 0.4010   

Time				
Inner   TpcRS  RF                RHF               ZF
double I[6] = {0.8775,   0.8211 ,0.8882,   0.7813  ,0.8221,  0.7811}  
root.exe [13] for (int i = 0; i < 3; i++) {cout << "\t" << sqrt(I[2*i] - I[2*i+1]);} cout << endl;
        0.237487        0.326956        0.202485
for (int i = 0; i < 3; i++) {cout << "\t" << sqrt(0.501**2 + I[2*i] - I[2*i+1]);} cout << endl;
       0.554438        0.598248        0.540371

Outer    TpcRS	
double O[6] ={0.7706,   0.7256,0.7784,   0.7581, 0.7369,   0.7296};
for (int i = 0; i < 3; i++) {cout << "\t" << sqrt(0.317**2 + O[2*i] - O[2*i+1]);} cout << endl;
        0.38143 0.347547        0.328312

  row.SigmaJitterTI         = 0.564; // M5
  row.SigmaJitterTO         = 0.352; // M5

--------------------------------------------------------------------------------
M6:                    TpcRS
Pad Inner RF  0.2733, 0.2697,
          RHF 0,2806, 0.2767,
          ZF  0.2715, 0.24

Pad Outer     0.4360,  0.442, 
              0,4180,  0.4266.
              0.4056,  0.4006
Time
Inner   RF  0.8775, 0.8732,
        RHF 0.8882, 0.8646,
        ZF  0.8134, 0.8495,
Outer   RF  0.7706, 0.7350,
        RHF 0.7784, 0.7531,
        ZF  0.7369, 0.7498,

 */

