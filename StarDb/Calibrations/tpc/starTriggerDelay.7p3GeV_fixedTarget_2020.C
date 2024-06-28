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
//   Double_t dT = 0.04572; // +/-  0.00186       2021/FF/7p7GeV_2021         	
//   Double_t dT = 0.05389; // +/-  0.00003       2021/FF/FF_OO_200GeV_2021           
//   Double_t dT = 0.04741; // +/-  0.00005       2021/RF/17p3GeV_2021        	
//   Double_t dT = 0.04595; // +/-  0.00003       2021/RF/7p7GeV_2021         	
//   Double_t dT = 0.05352; // +/-  0.00003       2021/RF/dAu200_2021         	
//   Double_t dT = 0.05647; // +/-  0.00003       2021/RF/OO_200GeV_2021      	
//   Double_t dT = 0.05627; // +/-  0.00002       2021/RF/ps_OO_200GeV_2021           
//   Double_t dT = 0.00328; // +/-  0.01576       2022/RF/pp500_2022          	
// 06/25/2024 + 06/26/2024
//   Double_t dT = 0.07995 -0.01111*2./3.; // +/-  0.00012 +/-  0.00011      2019/RF/31GeV_fixedTarget          		
//   Double_t dT = 0.07269 -0.00901*2./3.; // +/-  0.00013 +/-  0.00012      2019/RF/3p85GeV_fixedTarget        		
//   Double_t dT = 0.08143 -0.00996*2./3.; // +/-  0.00011 +/-  0.00011      2019/RF/4p59GeV_fixedTarget        		
//   Double_t dT = 0.07417 -0.00968*2./3.; // +/-  0.00019 +/-  0.00018      2019/RF/7.3GeV_fixedTarget         		
//   Double_t dT = 0.08074 -0.01057*2./3.; // +/-  0.00009 +/-  0.00009      2020/RF/13p5GeV_fixedTarget        		
//   Double_t dT = 0.07929 -0.01071*2./3.; // +/-  0.00008 +/-  0.00007      2020/RF/19p5GeV_fixedTarget        		
//   Double_t dT = 0.09336 -0.01081*2./3.; // +/-  0.00007 +/-  0.00007      2020/RF/26p5GeV_fixedTarget        		
//   Double_t dT = 0.08539 -0.01149*2./3.; // +/-  0.00008 +/-  0.00008      2020/RF/31p2GeV_fixedTarget        		
//   Double_t dT = 0.07895 -0.01063*2./3.; // +/-  0.00008 +/-  0.00008      2020/RF/5p75GeV_fixedTarget        		
  Double_t dT = 0.08147 -0.01022*2./3.; // +/-  0.00008 +/-  0.00008      2020/RF/7p3GeV_fixedTarget         		
//   Double_t dT = 0.08516 -0.01080*2./3.; // +/-  0.00010 +/-  0.00009      2020/RF/9p8GeV_fixedTarget         		
//   Double_t dT = 0.09608 -0.01343*2./3.; // +/-  0.00017 +/-  0.00017      2021/RF/100GeV_fixedTarget_2021    		
//   Double_t dT = 0.09591 -0.01132*2./3.; // +/-  0.00033 +/-  0.00032      2021/RF/26p5GeV_fixedTarget_2021           	
//   Double_t dT = 0.08412 -0.01070*2./3.; // +/-  0.00008 +/-  0.00008      2021/RF/3p85GeV_fixedTarget_2021           	
//   Double_t dT = 0.09159 -0.01249*2./3.; // +/-  0.00013 +/-  0.00013      2021/RF/44p5GeV_fixedTarget_2021           	
//   Double_t dT = 0.09676 -0.01330*2./3.; // +/-  0.00015 +/-  0.00015      2021/RF/70GeV_fixedTarget_2021     		
  memset(&row,0,tableSet->GetRowSize());
  row.clocks     = 17; // from Run XIX + XX + XXI scan ; 
  row.tZero	 =  0.435 + dT; // -"-
  tableSet->AddAt(&row);
  // ----------------- end of code ---------------
  return (TDataSet *)tableSet;
}
