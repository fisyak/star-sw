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
  // /hlt/cephfs/reco/TpcPrompt  root.exe 'Chain.C+("*/2023/*GeV/*T.root","FitP")' PrintTH1.C
  // tChain->Draw("mu>>Mu(100,2.5,3.5)","row>40"); Mu->Fit("gaus","er","",3.02,3.09); => 3.05521
  //  tChain->Draw("mu-3.05521:sector>>O(24,0.5,24.5,100,-0.25,0.25)","mu>0&&dmu>0&&dmu<0.1&&row>40","colz"); O->ProfileX();; PrintTH1(O_pfx); 
  Double_t ALTRO[24] = {-0.01, 0.00,-0.01, 0.01,-0.02, 0.01, 0.06,-0.04,-0.03,-0.04, 0.01, 0.00, 
			 0.05, 0.03, 0.02, 0.08,-0.02, 0.06, 0.05, 0.04, 0.01, 0.01,-0.02,-0.01};
  for (Int_t i =  0; i < 24; i++)  {row.t0[i] = -22.2572 - ALTRO[i];}
  //  tChain->Draw("mu-3.05521>>MuI(100,6,7)","row<=40"); MuI->Fit("gaus") => Mean = 6.67670
  //  tChain->Draw("mu-3.05521-6.67670:sector>>I(24,0.5,24.5,100,-1.0,1.0)","mu>0&&dmu>0&&dmu<0.1&&row<=40","colz"); I->FitSlicesY(); PrintTH1(I_1,I_2)
  Double_t SAMPA[24] = { 0.42, 0.45, 0.00, 0.00, 0.00, 0.03, 0.00, 0.00, 0.00,-0.04, 0.00, 0.00, 
			 0.00, 0.00, 0.00, 0.18, 0.04, 0.00, 0.00,-0.26, 0.00, 0.00, 0.00, 0.00};
  // Double_t CosmicsFF_RF[24] = { 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00,-0.39, 0.00,-0.51, 0.00, 0.00, 0.00, 0.00};
  // Double_t CosmicsFF[24]    = { 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00,-0.31, 0.00, 0.00, 0.00,-0.41,-0.35,-0.60, 0.00, 0.00,-0.29, 0.00};
  // Double_t CosmicsRF[24]    = { 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00};
  //                                                                                                             ^^^^                    ^^^^  ^^^^  ^^^^              ^^^^
  Double_t CosmicsFF[24] = { 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00,-0.31, 0.00, 0.00, 0.00,-0.41,-0.35,-0.60, 0.00, 0.00,-0.29, 0.00};
  //  for (Int_t i = 24; i < 48; i++)  {row.t0[i] = -22.2572 -6.67670 - SAMPA[i-24];} FF.Bad
  Double_t Cosmi2[24] =  { 0.19, 0.12,-0.20,-0.21,-0.21,-0.27,-0.26,-0.14,-0.21,-0.21,-0.18,-0.24,
			  -0.26,-0.12,-0.22,-0.25,-0.22,-0.18,-0.15,-0.22,-0.24,-0.26,-0.11,-0.15};
  Double_t Cosmi3[24] =  {-0.01,-0.01,-0.04,-0.03,-0.04,-0.03,-0.05,-0.05,-0.06,-0.05,-0.01,-0.03,
			  -0.05, 0.11,-0.06,-0.06,-0.08, 0.16, 0.14, 0.19,-0.05,-0.04, 0.10,-0.05};
  for (Int_t i = 24; i < 48; i++)  {row.t0[i] = -22.2572 -6.67670 - SAMPA[i-24] + CosmicsFF[i-24] + Cosmi2[i-24] + Cosmi3[i-24];}
  tableSet->AddAt(&row);
  // ----------------- end of code ---------------
  return (TDataSet *)tableSet;
}
