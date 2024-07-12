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
  if      (nameP.Contains("14p5GeV_2019"))              dT = 0.04870 -0.02522-0.032; // +/-  0.00001                                {"2019/RF/14p5GeV",                     -0.02522,  0.00018,    0.01891,  0.00021},    -0.032 2019/RF/14p5GeV     
  else if (nameP.Contains("19GeV_2019"))        	        dT = 0.04585 -0.00737-0.000; // +/-  0.00003 				      {"2019/RF/19GeV",                       -0.00737,  0.00025,    0.01605,  0.00030},    -0.000 2019/RF/19GeV       
  else if (nameP.Contains("7p7GeV_2019"))       	        dT = 0.05043 -0.01024+0.000; // +/-  0.00011 				      {"2019/RF/7p7GeV",                      -0.01024,  0.00034,    0.01659,  0.00033},    +0.000 2019/RF/7p7GeV      
  else if (nameP.Contains("9p2GeV_2019"))       	        dT = 0.04042 -0.00987-0.000; // +/-  0.00022 				      {"2019/RF/9p2GeV",     		      -0.00987,  0.00034,    0.01953,  0.00034},    -0.000 2019/RF/9p2GeV      
  else if (nameP.Contains("AuAu200_2019"))      	        dT = 0.02828 -0.00664+0.000; // +/-  0.00007 				      {"2019/RF/AuAu200",    		      -0.00664,  0.00021,    0.01709,  0.00020},    +0.000 2019/RF/AuAu200     
  else if (nameP.Contains("11p5GeV_2020"))      	        dT = 0.04975 -0.00981-0.001; // +/-  0.00002 				      {"2020/RF/11p5GeV",    		      -0.00981,  0.00022,    0.02342,  0.00030},    -0.001 2020/RF/11p5GeV     
  else if (nameP.Contains("7p7GeV_2020"))       	        dT = 0.05646 -0.01041+0.005; // +/-  0.00006 				      {"2020/RF/7p7GeV",                      -0.01041,  0.00028,    0.02407,  0.00035},    +0.005 2020/RF/7p7GeV      
  else if (nameP.Contains("9p2GeV_2019b"))      	        dT = 0.04278 -0.03984-0.030; // +/-  0.00007 				      {"2020/RF/9p2GeVb",    		      -0.03984,  0.00032,    0.02098,  0.00041},    -0.030 2020/RF/9p2GeVb     
  else if (nameP.Contains("9p2GeV_2019c"))      	        dT = 0.04272 -0.03984-0.030; // +/-  0.00007 				      {"2020/RF/9p2GeVc",    		      -0.03984,  0.00032,    0.02101,  0.00041},    -0.030 2020/RF/9p2GeVc     
  else if (nameP.Contains("9p2GeV_2020"))       	        dT = 0.04325 -0.03985-0.030; // +/-  0.00003 				      {"2020/RF/9p2GeV",     		      -0.03985,  0.00032,    0.02100,  0.00041},    -0.030 2020/RF/9p2GeV      
  else if (nameP.Contains("7p7GeV_2021"))               dT = 0.04572 -0.00385-0.003; // +/-  0.00186 				      {"2021/FF/7p7GeV_2021",                 -0.00385,  0.00568,    0.05449,  0.00876},    -0.003 2021/FF/7p7GeV      
  else if (nameP.Contains("FF_OO_200GeV_2021"))        	dT = 0.05389 -0.01045-0.003; // +/-  0.00003 				      {"2021/FF/FF_OO_200GeV_2021",           -0.01045,  0.00012,    0.01208,  0.00015},    -0.003 2021/FF/FF_OO_200GeV
  else if (nameP.Contains("17p3GeV_2021"))             	dT = 0.04741 -0.00657-0.000; // +/-  0.00005 				      {"2021/RF/17p3GeV_2021",                -0.00657,  0.00028,    0.02476,  0.00034},    -0.000 2021/RF/17p3GeV     
  else if (nameP.Contains("7p7GeV_2021"))              	dT = 0.04595 -0.01110-0.006; // +/-  0.00003 				      {"2021/RF/7p7GeV_2021",                 -0.01110,  0.00029,    0.02492,  0.00036},    -0.006 2021/RF/7p7GeV      
  else if (nameP.Contains("dAu200_2021"))              	dT = 0.05352 -0.01727+0.003; // +/-  0.00003 				      {"2021/RF/dAu200_2021",                 -0.01727,  0.00021,    0.01886,  0.00030},    +0.003 2021/RF/dAu200      
  else if (nameP.Contains("OO_200GeV_2021"))           	dT = 0.05647 -0.01381+0.000; // +/-  0.00003 				      {"2021/RF/OO_200GeV_2021",              -0.01381,  0.00009,    0.01200,  0.00011},    +0.000 2021/RF/OO_200GeV   
  else if (nameP.Contains("ps_OO_200GeV_2021"))        	dT = 0.05627 -0.01377+0.000; // +/-  0.00002 				      {"2021/RF/ps_OO_200GeV_2021",           -0.01377,  0.00009,    0.01202,  0.00011},    +0.000 2021/RF/ps_OO_200GeV
  else if (nameP.Contains("pp500_2022"))               	dT = 0.00328 -0.01241-0.000; // +/-  0.01576 				      {"2022/RF/pp500_2022",                  -0.01241,  0.02971,    0.10409,  0.06954},    -0.000 2022/RF/pp500       
  else if (nameP.Contains("31GeV_fixedTarget_2019"))         dT = 0.07995 -0.01111*2./3. -0.00349+0.001; // +/-  0.00012 +/-  0.00011    {"2019/RF/31GeV_fixedTarget",           -0.00349,  0.00115,    0.04741,  0.00118},     +0.001 2019/RF/31GeV_fixedTarget       
  else if (nameP.Contains("3p85GeV_fixedTarget_2019"))    	dT = 0.07269 -0.00901*2./3. +0.00814+0.000; // +/-  0.00013 +/-  0.00012    {"2019/RF/3p85GeV_fixedTarget",         +0.00814,  0.00036,    0.03187,  0.00036},     +0.000 2019/RF/3p85GeV_fixedTarget     
  else if (nameP.Contains("4p59GeV_fixedTarget_2019")) 	dT = 0.08143 -0.00996*2./3. -0.00138-0.000; // +/-  0.00011 +/-  0.00011    {"2019/RF/4p59GeV_fixedTarget",         -0.00138,  0.00028,    0.03504,  0.00028},     -0.000 2019/RF/4p59GeV_fixedTarget     
  else if (nameP.Contains("7.3GeV_fixedTarget_2019"))  	dT = 0.07417 -0.00968*2./3. +0.00530+0.001; // +/-  0.00019 +/-  0.00018    {"2019/RF/7.3GeV_fixedTarget",          +0.00530,  0.00080,    0.03716,  0.00081},     +0.001 2019/RF/7.3GeV_fixedTarget      
  else if (nameP.Contains("13p5GeV_fixedTarget_2020")) 	dT = 0.08074 -0.01057*2./3. -0.00640-0.000; // +/-  0.00009 +/-  0.00009    {"2020/RF/13p5GeV_fixedTarget",         -0.00640,  0.00095,    0.04655,  0.00099},     -0.000 2020/RF/13p5GeV_fixedTarget     
  else if (nameP.Contains("19p5GeV_fixedTarget_2020")) 	dT = 0.07929 -0.01071*2./3. -0.00555-0.001; // +/-  0.00008 +/-  0.00007    {"2020/RF/19p5GeV_fixedTarget",         -0.00555,  0.00088,    0.04900,  0.00099},     -0.001 2020/RF/19p5GeV_fixedTarget     
  else if (nameP.Contains("26p5GeV_fixedTarget_2020")) 	dT = 0.09336 -0.01081*2./3. +0.00786+0.000; // +/-  0.00007 +/-  0.00007    {"2020/RF/26p5GeV_fixedTarget",         +0.00786,  0.00071,    0.05405,  0.00081},     +0.000 2020/RF/26p5GeV_fixedTarget     
  else if (nameP.Contains("31p2GeV_fixedTarget_2020")) 	dT = 0.08539 -0.01149*2./3. -0.00551-0.001; // +/-  0.00008 +/-  0.00008    {"2020/RF/31p2GeV_fixedTarget",         -0.00551,  0.00086,    0.05159,  0.00097},     -0.001 2020/RF/31p2GeV_fixedTarget     
  else if (nameP.Contains("5p75GeV_fixedTarget_2020")) 	dT = 0.07895 -0.01063*2./3. -0.00933-0.000; // +/-  0.00008 +/-  0.00008    {"2020/RF/5p75GeV_fixedTarget",         -0.00933,  0.00042,    0.03419,  0.00050},     -0.000 2020/RF/5p75GeV_fixedTarget     
  else if (nameP.Contains("7p3GeV_fixedTarget_2020"))  	dT = 0.08147 -0.01022*2./3. -0.01097-0.000; // +/-  0.00008 +/-  0.00008    {"2020/RF/7p3GeV_fixedTarget",          -0.01097,  0.00054,    0.03724,  0.00063},     -0.000 2020/RF/7p3GeV_fixedTarget      
  else if (nameP.Contains("9p8GeV_fixedTarget_2020"))  	dT = 0.08516 -0.01080*2./3. -0.01028-0.001; // +/-  0.00010 +/-  0.00009    {"2020/RF/9p8GeV_fixedTarget",          -0.01028,  0.00072,    0.04400,  0.00080},     -0.001 2020/RF/9p8GeV_fixedTarget      
  else if (nameP.Contains("100GeV_fixedTarget_2021"))   dT = 0.09608 -0.01343*2./3. -0.00422-0.000; // +/-  0.00017 +/-  0.00017    {"2021/RF/100GeV_fixedTarget_2021",     -0.00422,  0.00204,    0.05152,  0.00235},     -0.000 2021/RF/100GeV_fixedTarget_2021  
  else if (nameP.Contains("26p5GeV_fixedTarget_2021"))  dT = 0.09591 -0.01132*2./3. -0.00931-0.013; // +/-  0.00033 +/-  0.00032    {"2021/RF/26p5GeV_fixedTarget_2021",    -0.00931,  0.00168,    0.05686,  0.00197},     -0.013 2021/RF/26p5GeV_fixedTarget_2021
  else if (nameP.Contains("3p85GeV_fixedTarget_2021"))  dT = 0.08412 -0.01070*2./3. -0.00553-0.003; // +/-  0.00008 +/-  0.00008    {"2021/RF/3p85GeV_fixedTarget_2021",    -0.00553,  0.00022,    0.02937,  0.00022},     -0.003 2021/RF/3p85GeV_fixedTarget_2021
  else if (nameP.Contains("44p5GeV_fixedTarget_2021"))  dT = 0.09159 -0.01249*2./3. -0.00415-0.001; // +/-  0.00013 +/-  0.00013    {"2021/RF/44p5GeV_fixedTarget_2021",    -0.00415,  0.00145,    0.04993,  0.00167},     -0.001 2021/RF/44p5GeV_fixedTarget_2021
  else if (nameP.Contains("70GeV_fixedTarget_2021"))    dT = 0.09676 -0.01330*2./3. -0.00648-0.001; // +/-  0.00015 +/-  0.00015    {"2021/RF/70GeV_fixedTarget_2021",      -0.00648,  0.00177,    0.04992,  0.00198},     -0.001 2021/RF/70GeV_fixedTarget_2021  
  else                                                  dT = 0;
  memset(&row,0,tableSet->GetRowSize());
  row.clocks     = 17; // from Run XIX + XX + XXI scan ;
  row.tZero  = 0.435 + dT; // -"-
  cout << "CreateTable : starTriggerDelay from file " <<  theFile  << "\t" << nameP.Data() << " with dT = " << dT 
    << " tZero = " << row.tZero       << endl;
  tableSet->AddAt(&row);
  // ----------------- end of code ---------------
  return (TDataSet *)tableSet;
}
