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
  if      (nameP.Contains("14p5GeV"))                   dT = 0.04870; // +/-  0.00001 
  else if (nameP.Contains("19GeV"))        	        dT = 0.04585; // +/-  0.00003 
  else if (nameP.Contains("7p7GeV"))       	        dT = 0.05043; // +/-  0.00011 
  else if (nameP.Contains("9p2GeV"))       	        dT = 0.04042; // +/-  0.00022 
  else if (nameP.Contains("AuAu200"))      	        dT = 0.02828; // +/-  0.00007 
  else if (nameP.Contains("11p5GeV"))      	        dT = 0.04975; // +/-  0.00002 
  else if (nameP.Contains("7p7GeV"))       	        dT = 0.05646; // +/-  0.00006 
  else if (nameP.Contains("9p2GeVb"))      	        dT = 0.04278; // +/-  0.00007 
  else if (nameP.Contains("9p2GeVc"))      	        dT = 0.04272; // +/-  0.00007 
  else if (nameP.Contains("9p2GeV"))       	        dT = 0.04325; // +/-  0.00003 
  else if (nameP.Contains("7p7GeV_2021"))               dT = 0.04572; // +/-  0.00186 				
  else if (nameP.Contains("FF_OO_200GeV_2021"))        	dT = 0.05389; // +/-  0.00003 				
  else if (nameP.Contains("17p3GeV_2021"))             	dT = 0.04741; // +/-  0.00005 				
  else if (nameP.Contains("7p7GeV_2021"))              	dT = 0.04595; // +/-  0.00003 				
  else if (nameP.Contains("dAu200_2021"))              	dT = 0.05352; // +/-  0.00003 				
  else if (nameP.Contains("OO_200GeV_2021"))           	dT = 0.05647; // +/-  0.00003 				
  else if (nameP.Contains("ps_OO_200GeV_2021"))        	dT = 0.05627; // +/-  0.00002 				
  else if (nameP.Contains("pp500_2022"))               	dT = 0.00328; // +/-  0.01576 				
  else if (nameP.Contains("31GeV_fixedTarget"))         dT = 0.07995 -0.01111*2./3.; // +/-  0.00012 +/-  0.00011     
  else if (nameP.Contains("3p85GeV_fixedTarget"))    	dT = 0.07269 -0.00901*2./3.; // +/-  0.00013 +/-  0.00012   
  else if (nameP.Contains("4p59GeV_fixedTarget")) 	dT = 0.08143 -0.00996*2./3.; // +/-  0.00011 +/-  0.00011   
  else if (nameP.Contains("7.3GeV_fixedTarget"))  	dT = 0.07417 -0.00968*2./3.; // +/-  0.00019 +/-  0.00018   
  else if (nameP.Contains("13p5GeV_fixedTarget")) 	dT = 0.08074 -0.01057*2./3.; // +/-  0.00009 +/-  0.00009   
  else if (nameP.Contains("19p5GeV_fixedTarget")) 	dT = 0.07929 -0.01071*2./3.; // +/-  0.00008 +/-  0.00007   
  else if (nameP.Contains("26p5GeV_fixedTarget")) 	dT = 0.09336 -0.01081*2./3.; // +/-  0.00007 +/-  0.00007   
  else if (nameP.Contains("31p2GeV_fixedTarget")) 	dT = 0.08539 -0.01149*2./3.; // +/-  0.00008 +/-  0.00008   
  else if (nameP.Contains("5p75GeV_fixedTarget")) 	dT = 0.07895 -0.01063*2./3.; // +/-  0.00008 +/-  0.00008   
  else if (nameP.Contains("7p3GeV_fixedTarget"))  	dT = 0.08147 -0.01022*2./3.; // +/-  0.00008 +/-  0.00008   
  else if (nameP.Contains("9p8GeV_fixedTarget"))  	dT = 0.08516 -0.01080*2./3.; // +/-  0.00010 +/-  0.00009   
  else if (nameP.Contains("100GeV_fixedTarget_2021"))   dT = 0.09608 -0.01343*2./3.; // +/-  0.00017 +/-  0.00017      
  else if (nameP.Contains("26p5GeV_fixedTarget_2021"))  dT = 0.09591 -0.01132*2./3.; // +/-  0.00033 +/-  0.00032     
  else if (nameP.Contains("3p85GeV_fixedTarget_2021"))  dT = 0.08412 -0.01070*2./3.; // +/-  0.00008 +/-  0.00008    
  else if (nameP.Contains("44p5GeV_fixedTarget_2021"))  dT = 0.09159 -0.01249*2./3.; // +/-  0.00013 +/-  0.00013    
  else if (nameP.Contains("70GeV_fixedTarget_2021"))    dT = 0.09676 -0.01330*2./3.; // +/-  0.00015 +/-  0.00015    
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
