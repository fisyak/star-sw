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
  // /hlt/cephfs/reco/TpcPrompt  root.exe 'Chain.C+("*/2021/*GeV/*T.root","FitP")' PrintTH1.C
  // tChain->Draw("mu>>Mu(100,2.5,3.5)","row>40"); Mu->Fit("gaus","er","",3.04,3.17); => 3.10495
  //  tChain->Draw("mu-3.10495:sector>>O(24,0.5,24.5,100,-0.25,0.25)","mu>0&&dmu>0&&dmu<0.1&&row>40","colz"); O->FitSlicesY(); PrintTH1(O_1, O_2); 
  Double_t ALTRO[24] = { 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00,
			 0.00, 0.00, 0.00, 0.11, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00};
  for (Int_t i =  0; i < 24; i++)  {row.t0[i] = -22.2572 - ALTRO[i];}
  //  tChain->Draw("mu-3.10495>>MuI(100,5,6)","row<=40"); MuI->Fit("gaus") => Mean = 5.6122
  //  tChain->Draw("mu-3.10495-5.6122:sector>>I(24,0.5,24.5,100,-1.0,3.0)","mu>0&&dmu>0&&dmu<0.1&&row<=40","colz"); I->FitSlicesY(); PrintTH1(I_1,I_2); 
  
  Double_t SAMPA[24] = { 0.00, 0.00, 0.00, 0.99, 0.00, 0.00, 0.00, 0.00, 0.00, 0.96, 0.00, 0.00, 
			 0.00, 0.99, 0.00, 0.17, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.95};
  Double_t Cosmic[24]= { 0.04, 0.01, 0.07, 0.04, 0.05, 0.03, 0.08, 0.09, 0.02, 0.02, 0.03, 0.02,
			 0.09, 0.04, 0.05, 0.06,-0.03,-0.03, 0.03, 0.05, 0.03, 0.05, 0.04, 0.02};
  Double_t Cosmi2[24]= { 0.03, 0.04, 0.04, 0.03, 0.04, 0.03, 0.04, 0.04, 0.04, 0.04, 0.03, 0.03, 
			 0.03, 0.03, 0.04, 0.04, 0.03, 0.03, 0.03, 0.03, 0.03, 0.03, 0.03, 0.04};
  for (Int_t i = 24; i < 48; i++)  {row.t0[i] = -22.2572 -5.6122 - SAMPA[i-24] - 0.035 + Cosmic[i-24] + Cosmi2[i-24];} // FF 0.04 RF 0.03
  tableSet->AddAt(&row);
  // ----------------- end of code ---------------
  return (TDataSet *)tableSet;
}
