#ifndef __CINT__
#include "tables/St_TpcResponseSimulator_Table.h"
#endif

// $Id: TpcResponseSimulator.y2021.C,v 1.1 2021/05/10 21:02:56 fisyak Exp $
// $Log: TpcResponseSimulator.y2021.C,v $
// Revision 1.1  2021/05/10 21:02:56  fisyak
// Clean up and synch with TFG
//
// Revision 1.3  2019/05/23 11:50:01  fisyak
// Add default TpcAdcCorrectionMDF, 2019 version of TpcResponseSimulator
//
// Revision 1.2  2019/04/16 19:29:34  fisyak
// Run XIX preliminary dE/dx calibration
//
// Revision 1.1  2018/02/16 20:56:50  perev
// iTPC
//
// Revision 1.1  2017/02/07 16:58:36  fisyak
// Clean up
//
// Revision 1.1  2012/09/13 21:06:27  fisyak
// Default tables for devT
//
// Revision 1.1  2012/04/27 00:31:31  perev
// All defE tables
//
// Revision 1.8  2012/04/11 14:21:55  fisyak
// Fix T0offset from comparison with AuAu27
//
// Revision 1.7  2012/04/03 14:06:55  fisyak
// Speed up using  GetSaveL (__PAD_BLOCK__), sluggish shape histograms, Heed electron generation
//
// Revision 1.6  2012/01/18 13:57:57  fisyak
// Adjust T0offset : Xianglei Zhu from Run 11 AuAu 27 & 19.6 GeV embedding
//
// Revision 1.5  2011/12/30 00:04:01  fisyak
// Freeze parameters for y2011 base on TpcRS_2011_pp500LowLum_Q
//
// Revision 1.3  2011/10/11 19:09:23  fisyak
// Add Yi Guo's tables for Run XI AuAu200 RFF dE/dx calibration
//
// Revision 1.2  2010/10/28 23:41:54  fisyak
// extra t0 off set for Altro chip
//
// Revision 1.7  2010/06/14 23:36:08  fisyak
// Freeze version Vxs
//
// Revision 1.6  2010/05/24 21:39:53  fisyak
// Fix bracket
//
// Revision 1.5  2010/05/24 16:07:20  fisyak
// Add default dE/dx calibration tables, replace TpcAltroParameters and asic_thresholds_tpx by tpcAltroParams
//
// Revision 1.4  2010/04/19 15:05:58  fisyak
// Final (2010_i) parameters for Run X
//
// Revision 1.3  2010/04/16 19:31:19  fisyak
// Intermidiate version
//
// Revision 1.3  2010/04/04 23:14:33  fisyak
// Add Row Correction
//
// Revision 1.2  2010/04/01 22:17:57  fisyak
// Freeze version W
//
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
  // h = distance between anode and cathode planes, s - anode wire pitchxs, Chapter 5 of Mathieson's book, Fig 5.3(a => rho, a => rho2)1
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
  row.tauCI                 =   0;  
  row.tauCO                 =   0;  
  //  row.SigmaJitterTI         = 0.501; // M4
  //  row.SigmaJitterTO         = 0.317; // M4
  row.SigmaJitterTI         = 0.564; // M5
  row.SigmaJitterTO         = 0.352; // M5
  row.SigmaJitterXI         = 0.08915;// M4 0.104; // M40.069; // M3 0.1461;//M2  0.; //0.1 + 0.037;
  row.SigmaJitterXO         = 0.; //0.13 + 0.025; 
  row.longitudinalDiffusion = 0.0362; // 0.03624*1.3*0.92; 
  row.longitudinalDiffusionI= row.longitudinalDiffusion; // *0.95;
  row.transverseDiffusion   = 0.02909*TMath::Sqrt(1 + row.OmegaTau*row.OmegaTau) ; //B  Fit 2023 data
  row.transverseDiffusionI  = row.transverseDiffusion/1.08;// J *0.983; // 0.97*
  row.NoElPerAdc            = 335.;   // No. of electrons per 1 ADC count
#if 0
  row.OmegaTauScaleI        =  2.145*1.515;// restore in D HC 1.;// 2.145*1.515;  //i; 2.145*1.4;  //h 2.145;  //ad 2.145*1.25;  //b effective reduction of OmegaTau near Inner sector anode wire
  row.OmegaTauScaleO        =  1.8  *1.201;// -"- HC 1.;// 1.8  *1.201;  //i 1.8  *1.1;    //h 1.8;    //ad 1.8  *1.25;  //b effective reduction of OmegaTau near Outer sector anode wire
#endif
  // Inner_wire_to_plane_coupling ( 0.533 ) * Inner_wire_to_plane_couplingScale ( 0.843485 )
  // Outer_wire_to_plane_coupling ( 0.512 ) * Outer_wire_to_plane_couplingScale ( 0.725267 )
  row.SecRowCorIW[0] = row.SecRowCorIE[0] = 0.57692996501735538 + 5.13440e-02 - 0.23 + 2.02654e-01 -1.41451e-01 + -0.14; 
  row.SecRowCorIW[1] = row.SecRowCorIE[1] = -5.40702e-04;
  row.SecRowCorOW[0] = row.SecRowCorOE[0] = 1.11982875000493309-1.27992e-01 + 2.52297e-02 - 0.135 + 1.72299e-01  -1.55654e-01;
  row.SecRowCorOW[1] = row.SecRowCorOE[1] = -3.73511e-04;
  // SecRow3CGF7p7GeV_2021.root: FitP->Draw("sigma:y","i&&j","prof")
  //                                     Inner            3.10477e-01, Outer   2.70452e-01
  // RunXXI/Hijing.2021AuAu200.VMCF
  //                                     Inner            2.93912e-01  Iuter   2.76624e-01    
  const Double_t RowSigmaTrs[4] = {
    9.13675e-02, 0,  // Inner
    6.29849e-02, 0}; // Outer
  Float_t *b = &row.SecRowSigIW[0];
  for (Int_t i = 0; i < 8; i++) {
    b[i] = RowSigmaTrs[i%4];
  }
  row.PolyaInner = 1.38;
  row.PolyaOuter = 1.38;
  row.T0offset   = 0.50 -1.43663e-01 -0.00932877 + 0.0416 + 0.0241 ;//g // 01/18/12 Xianglei Zhu from Run 11 AuAu 27 & 19.6 GeV embedding 
  row.T0offsetI  =  0.0709683 -0.00865149 + 0.307 - 0.3255 + 1.75e-3; // (RF + RHF)/2
  row.T0offsetO  = -0.0710492 -0.0159205  + 0.257 - 0.2417 - 2.31e-2; // -"-
  row.tMaxI = row.tMaxO = 2e-5; // sec
#if 0
  Double_t parO[3] = { 0.08254, -0.017634, 0.001468};
  Double_t parI[3] = { 0.07816, -0.01757,  0.0015496};
#else
  //  Double_t B[3]  = {5.0, 2.5, 0.}; // kG
  Double_t parO[3] = { 0.021982,  0.032902, 0.0595239};
  Double_t parI[3] = { 0.021982,  0.032902, 0.0595239};
#endif
  Double_t *O =  &row.transDiffParO[0];
  Double_t *I =  &row.transDiffParI[0];
  for (Int_t i = 0; i < 3; i++) {
    O[i] = parO[i];
    I[i] = parI[i];
  }
  tableSet->AddAt(&row);
  // ----------------- end of code ---------------
  return (TDataSet *)tableSet;
}
