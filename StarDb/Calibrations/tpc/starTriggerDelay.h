#ifndef __CINT__
#include "Riostream.h"
#include "TString.h"
#include "tables/St_starTriggerDelay_Table.h"
#endif

TDataSet *CreateTable(const Char_t *theFile) {
  // -----------------------------------------------------------------
  // bfc/.make/db/.const/StarDb/RunLog/onl/.starTriggerDelay/starTriggerDelay Allocated rows: 1  Used rows: 1  Row size: 16 bytes
  //  Table: starTriggerDelay_st[0]--> starTriggerDelay_st[0]
  // ====================================================================
  // ------  Test whether this table share library was loaded ------
  TString nameP(gSystem->BaseName(theFile));
  nameP.ReplaceAll("starTriggerDelay.C","");
  nameP.ReplaceAll("starTriggerDelay.","");
  nameP.ReplaceAll(".C","");
  if (!TClass::GetClass("St_starTriggerDelay")) return 0;
  starTriggerDelay_st row;
  St_starTriggerDelay *tableSet = new St_starTriggerDelay("starTriggerDelay",1);
  Double_t dT = 0;
#if 1
  if      (nameP.Contains("14p5GeV_2019"))              dT = 0.041;// 2019/RF/14p5GeV                 dT = 0.04870 -0.02522-0.032 +0.048 +0.001;        //
  else if (nameP.Contains("19GeV_2019"))        	dT = 0.040;// 2019/RF/19GeV                   dT = 0.04585 -0.00737;                            //
  else if (nameP.Contains("31GeV_fixedTarget_2019"))    dT = 0.077;// 2019/RF/31GeV_fixedTarget       dT = 0.07995 -0.01111*2./3. -0.00349+0.001+0.002; //
  else if (nameP.Contains("3p85GeV_fixedTarget_2019"))  dT = 0.080;// 2019/RF/3p85GeV_fixedTarget     dT = 0.07269 -0.00901*2./3. +0.00814+0.000+0.001; //
  else if (nameP.Contains("4p59GeV_fixedTarget_2019")) 	dT = 0.080;// 2019/RF/4p59GeV_fixedTarget     dT = 0.08143 -0.00996*2./3. -0.00138+0.002;       //
  else if (nameP.Contains("7.3GeV_fixedTarget_2019"))  	dT = 0.082;// 2019/RF/7.3GeV_fixedTarget      dT = 0.07417 -0.00968*2./3. +0.00530+0.001+0.008; //
  else if (nameP.Contains("7p7GeV_2019"))       	dT = 0.040;// 2019/RF/7p7GeV                  dT = 0.05043 -0.01024+0.000 -0.044  -0.035;       //
  else if (nameP.Contains("9p2GeV_2019"))       	dT = 0.030;// 2019/RF/9p2GeV                  dT = 0.04042 -0.00987-0.000 -0.043  +0.053;	  //
  else if (nameP.Contains("AuAu200GeV_2019"))      	dT = 0.023;// 2019/RF/AuAu200                 dT = 0.02828 -0.00664+0.000 -0.055  +0.055;	  //
  else if (nameP.Contains("11p5GeV_2020"))      	dT = 0.041;// 2020/RF/11p5GeV                 dT = 0.04975 -0.00981-0.001 +0.001;               //
  else if (nameP.Contains("13p5GeV_fixedTarget_2020")) 	dT = 0.073;// 2020/RF/13p5GeV_fixedTarget     dT = 0.08074 -0.01057*2./3. -0.00640;             //
  else if (nameP.Contains("19p5GeV_fixedTarget_2020")) 	dT = 0.073;// 2020/RF/19p5GeV_fixedTarget     dT = 0.07929 -0.01071*2./3. -0.00555;             //
  else if (nameP.Contains("26p5GeV_fixedTarget_2020")) 	dT = 0.105;// 2020/RF/26p5GeV_fixedTarget     dT = 0.09336 -0.01081*2./3. +0.00786+0.009;       //
  else if (nameP.Contains("31p2GeV_fixedTarget_2020")) 	dT = 0.079;// 2020/RF/31p2GeV_fixedTarget     dT = 0.08539 -0.01149*2./3. -0.00551-0.001+0.003; //
  else if (nameP.Contains("5p75GeV_fixedTarget_2020")) 	dT = 0.068;// 2020/RF/5p75GeV_fixedTarget     dT = 0.07895 -0.01063*2./3. -0.00933+0.001;       //
  else if (nameP.Contains("7p3GeV_fixedTarget_2020"))  	dT = 0.070;// 2020/RF/7p3GeV_fixedTarget      dT = 0.08147 -0.01022*2./3. -0.01097+0.125;       //
  else if (nameP.Contains("7p7GeV_2020"))       	dT = 0.048;// 2020/RF/7p7GeV                  dT = 0.05646 -0.01041+0.005 -0.053+0.048;         //
  else if (nameP.Contains("9p2GeVb_2020"))        	dT = 0.036;// 2020/RF/9p2GeVb                 dT = 0.04272 -0.03984-0.030+0.094;                //
  else if (nameP.Contains("9p2GeVc_2020"))       	dT = 0.036;// 2020/RF/9p2GeVc                 dT = 0.04325 -0.03985-0.030 -0.036+0.094;         //
  else if (nameP.Contains("9p2GeV_2020"))       	dT = 0.036;// 2020/RF/9p2GeV                  dT = 0.08516 -0.01080*2./3. -0.01028-0.001+0.004; //  
  else if (nameP.Contains("9p8GeV_fixedTarget_2020"))  	dT = 0.073;// 2020/RF/9p8GeV_fixedTarget      dT = 0.04572 -0.00385+0.003;                      //  
  else if (nameP.Contains("FF_7p7GeV_2021"))            dT = 0.039;// 2021/FF/7p7GeV_2021             dT = 0.05389 -0.01045-0.003+0.038; 	          //
  else if (nameP.Contains("FF_OO_200GeV_2021"))        	dT = 0.040;// 2021/FF/FF_OO_200GeV_2021       dT = 0.09608 -0.01343*2./3. -0.00422+0.001;       //  
  else if (nameP.Contains("100GeV_fixedTarget_2021"))   dT = 0.090;// 2021/RF/100GeV_fixedTarget_2021 dT = 0.04741 -0.00657; 	                          //
  else if (nameP.Contains("17p3GeV_2021"))             	dT = 0.041;// 2021/RF/17p3GeV_2021            dT = 0.09591 -0.01132*2./3. -0.00931-0.013+0.016; //  
  else if (nameP.Contains("26p5GeV_fixedTarget_2021"))  dT = 0.086;// 2021/RF/26p5GeV_fixedTarget_2021dT = 0.08412 -0.01070*2./3. -0.00553-0.003+0.005; //  
  else if (nameP.Contains("3p85GeV_fixedTarget_2021"))  dT = 0.079;// 2021/RF/3p85GeV_fixedTarget_2021dT = 0.09159 -0.01249*2./3. -0.00415-0.001+0.005; //  
  else if (nameP.Contains("44p5GeV_fixedTarget_2021"))  dT = 0.088;// 2021/RF/44p5GeV_fixedTarget_2021dT = 0.09676 -0.01330*2./3. -0.00648-0.001+0.004; //  
  else if (nameP.Contains("70GeV_fixedTarget_2021"))    dT = 0.090;// 2021/RF/70GeV_fixedTarget_2021  dT = 0.04595 -0.01110-0.006 -0.054 -0.058-0.005;  //  
  else if (nameP.Contains("7p7GeV_2021"))              	dT = 0.036;// 2021/RF/7p7GeV_2021             dT = 0.05352 -0.01727+0.003 -0.040 -0.025+0.065;  //  
  else if (nameP.Contains("dAu200GeV_2021"))            dT = 0.040;// 2021/RF/dAu200_2021             dT = 0.05647 -0.01381+0.000 -0.040+0.040;         //  
  else if (nameP.Contains("OO_200GeV_2021"))           	dT = 0.043;// 2021/RF/OO_200GeV_2021          dT = 0.05627 -0.01377+0.000 -0.043+0.040;	  //	    
  else if (nameP.Contains("ps_OO_200GeV_2021"))        	dT = 0.043;// 2021/RF/ps_OO_200GeV_2021       dT = 0.00328 -0.01241-0.000;                //        
  else                                                  dT = 0;
#endif
  memset(&row,0,tableSet->GetRowSize());
  row.clocks     = 17; // from Run XIX + XX + XXI scan ;
  row.tZero  = 0.435 + dT; // -"-
  cout << "CreateTable : starTriggerDelay from file " <<  theFile  << "\t" << nameP.Data() << " with dT = " << dT 
    << " tZero = " << row.tZero       << endl;
  tableSet->AddAt(&row);
  // ----------------- end of code ---------------
  return (TDataSet *)tableSet;
}
