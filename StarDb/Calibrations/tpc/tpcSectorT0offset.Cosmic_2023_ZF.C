#ifndef __CINT__
#include "tables/St_tpcSectorT0offset_Table.h"
#endif
TDataSet *CreateTable() { 
  // -----------------------------------------------------------------
  // db/.const/StarDb/Calibrations/tpc/.tpcSectorT0offset/tpcSectorT0offset Allocated rows: 1  Used rows: 1  Row size: 72 bytes
  //  Table: tpcSectorT0offset_st[0]--> tpcSectorT0offset_st[0]
  // ====================================================================
  // ------  Test whether this table share library was loaded ------
  if (!gROOT->GetClass("St_tpcSectorT0offset")) return 0;
  tpcSectorT0offset_st row;
  St_tpcSectorT0offset *tableSet = new St_tpcSectorT0offset("tpcSectorT0offset",1);
  //
  memset(&row,0,tableSet->GetRowSize());
  // /hlt/cephfs/reco/TpcPrompt/RF/2024/pp200/25123012 root.exe TGPZTMfl0.root
  // 
  // FitP->Draw("mu>>Mu(100,3.0,3.5)","y>40");  Mu->Fit("gaus"); mu =  3.223
  // FitP->Draw("mu-3.223:x>>O(24,0.5,24.5,100,-0.25,0.25)","mu>0&&dmu>0&&dmu<0.1&&y>40","colz"); O->ProfileX()->Draw("sames"); PrintTH1(O_pfx); 
  Double_t ALTRO[24] = { 0.00, 0.00, 0.00, 0.01, 0.00, 0.02, 0.07,-0.04,-0.02,-0.02,-0.02,-0.02,
			 0.03, 0.03, 0.02, 0.01,-0.07,-0.06, 0.02, 0.00, 0.02, 0.03,-0.02, 0.00};
  for (Int_t i =  0; i < 24; i++)  {row.t0[i] = -22.2572 - ALTRO[i];}
  //  FitP->Draw("mu-3.223>>MuI(100,6.5,7.5)","mu>0&&dmu>0&&dmu<0.1&&y<=40","colz"); mu =  7.0518
  //  FitP->Draw("mu-3.223-7.0518:x>>I(24,0.5,24.5,100,-1.0,1.0)","mu>0&&dmu>0&&dmu<0.1&&y<=40","colz"); I->ProfileX()->Draw("sames");  PrintTH1(I_pfx);
  Double_t SAMPA[24] = { 0.00, 0.00,-0.04, 0.00, 0.00, 0.00, 0.00,-0.07, 0.00,-0.02, 0.00, 0.00, 
			 0.00, 0.00, 0.00, 0.19, 0.04, 0.00, 0.00, 0.04, 0.00, 0.00, 0.00, 0.00};
#if 0
  Double_t Cosmic_RF[24] = {-0.00, 0.00,-0.04,-0.03,-0.02,-0.01,-0.01,-0.02,-0.02,-0.00,-0.07,-0.06,
			    -0.03,-0.01,-0.01,-0.06,-0.09,-0.02,-0.05,-0.10,-0.01,-0.01,-0.04,-0.11};
  Double_t Cosmic_FF[24] = {-0.00, 0.01,-0.02,-0.01,-0.01,-0.03,-0.01,-0.03,-0.01,-0.01,-0.00,-0.03,
			    -0.00, 0.00,-0.01,-0.05,-0.02,-0.00,-0.02,-0.05,-0.02,-0.01,-0.02,-0.03};
  for (Int_t i = 24; i < 48; i++)  {row.t0[i] = -22.2572 -7.0518 - SAMPA[i-24];}
#else /* 05/15/2023 ZF */
  Double_t Cosmic[24] = { 0.14, 0.34, 0.30, 0.31, 0.30, 0.32, 0.31, 0.28, 0.28, 0.31, 0.28, 0.32, 
			  0.31, 0.31, 0.30, 0.30, 0.29, 0.34, 0.31, 0.27, 0.30, 0.31, 0.34, 0.28};
  Double_t Cosmi2[24] = { 0.15, 0.05, 0.15, 0.19, 0.19, 0.13, 0.15, 0.22, 0.19, 0.20, 0.21, 0.19, 
			  0.18, 0.16, 0.20, 0.26, 0.25, 0.16, 0.15, 0.32, 0.16, 0.16, 0.17, 0.23};

  for (Int_t i = 24; i < 48; i++)  {row.t0[i] = -22.2572 -7.0518 - SAMPA[i-24] + Cosmic[i-24] + Cosmi2[i-24] ;}
#endif
  tableSet->AddAt(&row);
  // ----------------- end of code ---------------
  return (TDataSet *)tableSet;
}
