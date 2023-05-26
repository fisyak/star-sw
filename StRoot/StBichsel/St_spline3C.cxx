#include "Riostream.h"
#include "St_spline3C.h"
#include "TString.h"
#include "TInterpreter.h"
#include "TSystem.h"
//________________________________________________________________________________
St_spline3  *St_spline3C::Open(const Char_t *path) {
  TString PATH(path);
  TString Dir(gSystem->DirName(PATH));
  TString File(gSystem->BaseName(PATH));
  File += ".C";
  TString pathF(".:./StarDb/"); pathF +=  Dir + ":$STAR/StarDb/" + Dir;
  Char_t *file = gSystem->Which(pathF,File,kReadPermission);		
  if (! file) cout << Form("Fatal::St_spline3C::Open   \tFile %s has not been found in path %s",File.Data(),pathF.Data()) << endl;
  else        cout << Form("Warning::St_spline3C::Open \tFile %s has been found as %s",File.Data(),file) << endl;
  TString command(".L "); command += file; TInterpreter::EErrorCode ee; 
  gInterpreter->ProcessLine(command,&ee);				
  assert(!ee);							
  St_spline3 *table = (St_spline3 *) gInterpreter->Calc("CreateTable()",&ee); 
  assert(table);	  table->Print(0,1);
  command.ReplaceAll(".L ",".U ");
  gInterpreter->ProcessLine(command,&ee);	
  assert(!ee);				
  return table;
}
//________________________________________________________________________________
St_spline3C::St_spline3C(St_spline3 *table) : TChair(table), fSpline(0), fFunc(0) {
  if (table) {
    fSpline = new TSpline3("Spline3", Xknots(), Yknots(), nknots(), option(), ValBeg(), ValEnd());               
    fSpline->SetLineColor(2);
    fFunc   = new TF1(GetName(), this, Xknots()[0], Xknots()[nknots()-1], 0, "St_spline3C"); 
    fFunc->SetNpx(100);
    fFunc->Save(Xknots()[0], Xknots()[nknots()-1], 0., 0., 0., 0.);
  }
}
#define MakeChairInstance3(CLASS,PATH)					\
  ClassImp(CLASS);							\
  CLASS *CLASS::fgInstance = 0;						\
  CLASS *CLASS::instance() {						\
    if (fgInstance) return fgInstance;					\
    St_spline3 *table = St_spline3C::Open(# PATH);			\
    fgInstance = new CLASS(table);					\
    return fgInstance;							\
  }
//________________________________________________________________________________
MakeChairInstance3(Stspline3LndNdxL10,dEdxModel/spline3LndNdxL10);
