#ifndef __CINT__
#include "tables/St_starTriggerDelay_Table.h"
#endif

TDataSet *CreateTable() { 
  // -----------------------------------------------------------------
  // bfc/.make/db/.const/StarDb/RunLog/onl/.starTriggerDelay/starTriggerDelay Allocated rows: 1  Used rows: 1  Row size: 16 bytes
  //  Table: starTriggerDelay_st[0]--> starTriggerDelay_st[0]
  // ====================================================================
  // ------  Test whether this table share library was loaded ------
  if (!TClass::GetClass("St_starTriggerDelay")) return 0;
  starTriggerDelay_st row;
  St_starTriggerDelay *tableSet = new St_starTriggerDelay("starTriggerDelay",1);
//   Double_t dT = 0.04870; // +/-  0.00001       2019/RF/14p5GeV    		        
//   Double_t dT = 0.04585; // +/-  0.00003       2019/RF/19GeV       		
//   Double_t dT = 0.05043; // +/-  0.00011       2019/RF/7p7GeV     		        
//   Double_t dT = 0.04042; // +/-  0.00022       2019/RF/9p2GeV      		
//   Double_t dT = 0.02828; // +/-  0.00007       2019/RF/AuAu200     		
//   Double_t dT = 0.04975; // +/-  0.00002       2020/RF/11p5GeV     		
//   Double_t dT = 0.05646; // +/-  0.00006       2020/RF/7p7GeV      		
//   Double_t dT = 0.04278; // +/-  0.00007       2020/RF/9p2GeVb     		
//   Double_t dT = 0.04272; // +/-  0.00007       2020/RF/9p2GeVc     		
//   Double_t dT = 0.04325; // +/-  0.00003       2020/RF/9p2GeV      		
  Double_t dT = 0.04572; // +/-  0.00186       2021/FF/7p7GeV_2021         	
//   Double_t dT = 0.05389; // +/-  0.00003       2021/FF/FF_OO_200GeV_2021           
//   Double_t dT = 0.04741; // +/-  0.00005       2021/RF/17p3GeV_2021        	
//   Double_t dT = 0.04595; // +/-  0.00003       2021/RF/7p7GeV_2021         	
//   Double_t dT = 0.05352; // +/-  0.00003       2021/RF/dAu200_2021         	
//   Double_t dT = 0.05647; // +/-  0.00003       2021/RF/OO_200GeV_2021      	
//   Double_t dT = 0.05627; // +/-  0.00002       2021/RF/ps_OO_200GeV_2021           
//   Double_t dT = 0.00328; // +/-  0.01576       2022/RF/pp500_2022          	
  memset(&row,0,tableSet->GetRowSize());
  row.clocks     = 17; // from Run XIX + XX + XXI scan 
  row.tZero	 = 0.435 + dT; // -"-
  tableSet->AddAt(&row);
  // ----------------- end of code ---------------
  return (TDataSet *)tableSet;
}
