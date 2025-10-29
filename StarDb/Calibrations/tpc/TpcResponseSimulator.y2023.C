#ifndef __CINT__
#include "tables/St_TpcResponseSimulator_Table.h"
#endif
TDataSet *CreateTable() { 
  // -----------------------------------------------------------------
  // db/.const/StarDb/Calibrations/tpc/.TpcResponseSimulator/TpcResponseSimulator Allocated rows: 1  Used rows: 1  Row size: 124 bytes
  //  Table: TpcResponseSimulator_st[0]--> TpcResponseSimulator_st[0]
  // ====================================================================
  // ------  Test whether this table share library was loaded ------
  if (!TClass::GetClass("St_TpcResponseSimulator")) return 0;
  TpcResponseSimulator_st row;
  St_TpcResponseSimulator *tableSet = new St_TpcResponseSimulator("TpcResponseSimulator",1);
  memset(&row,0,tableSet->GetRowSize());
  row.I0                    = 13.1;// eV, CH4 		       
  row.Cluster    	    = 3.2; // average no. of electrons per primary  			       
  row.W          	    = 26.2;// eV 								       
  row.OmegaTau   	    = 2.585; // fit 2023 data 3.02;// fit of data @ 5kG							       
  // a = 10 um anode wire radius; h = distance between anode and cathode planes: Inner 2mm, Outer 4mm; s - anode wire pitch = 4mm, 
  // Chapter 5 of Mathieson's book, Fig 5.3(a => rho1, b => rho2)
  row.K3IP       	    = 0.68;//(pads) for a/s = 2.5e-3 and h/s = 0.5, rho2
  row.K3IR       	    = 0.89;//(row)  for a/s = 2.5e-3 and h/s = 0.5, rho1 
  row.K3OP       	    = 0.55;//(pads) for a/s = 2.5e-3 and h/s = 1.0 
  row.K3OR       	    = 0.61;//(row)  for a/s = 2.5e-3 and h/s = 1.0 
  row.FanoFactor 	    = 0.3; //                                                                        
  row.AveragePedestal       = 50.0;// 
  row.AveragePedestalRMS    = -1.0; // Old Tpc electronics or iTPC  1.4 => 1.0; Tonko 12/12/2019
  row.AveragePedestalRMSX   = -1.0; // New Tpx electronics 
  row.tauIntegration        = 2.5*74.6e-9;//   secs 
  row.tauF                  = 394.0e-9;// secs Tpc 
  row.tauP                  = 775.0e-9;// secs Tpc 
  row.tauXI                 =  60.0e-9;// secs Tpx Inner integration time  
  row.tauXO                 =  74.6e-9;// secs Tpx Outer integration time 
  row.SigmaJitterTI         = 0.564; // M5
  row.SigmaJitterTO         = 0.352; // M5
  row.SigmaJitterXI         = 0.1156; // K 0.14; // J 0.08915;// M4 0.104; // M40.069; // M3 0.1461;//M2  0.; //0.1 + 0.037;
  row.SigmaJitterXO         = 0.; //0.13 + 0.025; 
  row.longitudinalDiffusion = 0.0362; // 0.03624*1.3*0.92; 
  row.NoElPerAdc            = 335.;   // No. of electrons per 1 ADC count
  //                                                      -RC            +MC
  row.SecRowCorIW[0] = row.SecRowCorIE[0] =  0.3195      + 0.1200      + 0.1611;
  row.SecRowCorIW[1] = row.SecRowCorIE[1] = -5.40702e-04 - 1.91101e-03  -8.72089e-04;
  row.SecRowCorOW[0] = row.SecRowCorOE[0] =  0.8987      + 0.0642      + 0.2517;
  row.SecRowCorOW[1] = row.SecRowCorOE[1] = -3.73511e-04 - 1.07959e-03  -1.35275e-03;
  row.PolyaInner = 1.38;
  row.PolyaOuter = 1.38;
  row.T0offset   = 0.4127; //0.50 -1.43663e-01 -0.00932877 + 0.0416 + 0.0241 ;//g // 01/18/12 Xianglei Zhu from Run 11 AuAu 27 & 19.6 GeV embedding 
  row.T0offsetI  =  0.0456; // 0.0709683 -0.00865149 + 0.307 - 0.3255 + 1.75e-3; // (RF + RHF)/2
  row.T0offsetO  = -0.0948; //-0.0710492 -0.0159205  + 0.257 - 0.2417 - 2.31e-2; // -"-
  row.tMaxI = row.tMaxO = 2e-5; // sec
  row.transDiffFF  =  0.02198; // 5 kG 
  row.transDiffHF  =  0.03290; // 2.5 kG
  row.transDiffZF  =  0.05952; // 0. kG
  row.dTransDiffFF = -0.0007; // K, -0.0009; // J
  row.dTransDiffHF =  0.0007; // K, -0.0009; // J
  row.dTransDiffZF = -0.0012; // K, -0.0009; // J
  tableSet->AddAt(&row);
  // ----------------- end of code ---------------
  return (TDataSet *)tableSet;
}
