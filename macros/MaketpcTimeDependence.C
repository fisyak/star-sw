/*
  root.exe TimeCGFP21ib02_24.root 
  FitP->Draw("mu:x>>T(360,762e6,771e6)","(i&&j&&dmu>0&&dmu<3e-4&&mu<0.06)/dmu**2","profg")
  .x 'MaketpcTimeDependence.C+(T)'

   root.exe Time*.root MaketpcTimeDependence.C+
*/
#if !defined(__CINT__)
// code that should be seen ONLY by the compiler
#else
#if !defined(__CINT__) || defined(__MAKECINT__)
// code that should be seen by the compiler AND rootcint
#else
// code that should always be seen
#endif
#endif
//________________________________________________________________________________
#if !defined(__CINT__) || defined(__MAKECINT__)
#include "Riostream.h"
#include <stdio.h>
#include "TROOT.h"
#include "TSystem.h"
#include "TMath.h"
#include "TH1.h"
//#include "TH2.h"
//#include "TH3.h"
//#include "THnSparse.h"
//#include "TStyle.h"
#include "TF1.h"
//#include "TProfile.h"
#include "TTree.h"
//#include "TChain.h"
#include "TDirectory.h"
#include "TFile.h"
#include "TNtuple.h"
#include "TFitResult.h"
#include "TCanvas.h"
//#include "TFileSet.h"
// #include "TDataSetIter.h"
// #include "TDataSet.h"
// #include "TClassTable.h"
// #include "TMinuit.h"
// #include "TSpectrum.h"
// #include "StBichsel/Bichsel.h"
// #include "StBichsel/StdEdxModel.h"
#include "TString.h"
// #include "TLine.h"
// #include "TText.h"
// #include "TList.h"
// #include "TPolyMarker.h"
// #include "TKey.h"
// #include "TLegend.h"
//#include "TObjectTable.h"
//#include "TObjArray.h"
//#include "tables/St_tpcCorrection_Table.h"
#include "TROOT.h"
#include "Ask.h"
#endif
TCanvas *c1 = 0;
//________________________________________________________________________________
void  MaketpcTimeDependence(TH1 *T, const Char_t *tag) {
  if (! T) return;
  Double_t xmin = T->GetXaxis()->GetXmin();
  Double_t xmax = T->GetXaxis()->GetXmax();
  cout << " xmin = " << xmin << ", xmax = " << xmax << endl;
  TDatime t; t.Set(T->GetXaxis()->GetXmin()+788936400); t.Print();
  TString fOut = Form("tpcTimeDependence.%s.C",tag);
  TF1 *f = (TF1 *) gROOT->GetListOfFunctions()->FindObject("pol1");
  if (! f) {
    TF1::InitStandardFunctions();
    f = (TF1 *) gROOT->GetListOfFunctions()->FindObject("pol1");
    if (! f) return;
  }
  Int_t iok = T->Fit(f,"er rob=0.75","",xmin,xmax);
   //  Int_t iok = T->Fit(f,"er","",xmin,xmax);
  if (iok < 0) return;
  ofstream out;
  TString Line;
  cout << "Create " << fOut << endl;
  out.open(fOut.Data());
  out << "TDataSet *CreateTable() {" << endl;
  out << "  if (!gROOT->GetClass(\"St_tpcCorrection\")) return 0;" << endl;
  out << "  Int_t nrows = 1;" << endl;
  out << "  St_tpcCorrection *tableSet = new St_tpcCorrection(\"tpcTimeDependenceB\",nrows);" << endl;
  out << "  tpcCorrection_st row;" << endl; 
  out << "  memset(&row,0,tableSet->GetRowSize());" << endl;
  out << "  row.idx   = 1;// " << tag << endl;
  out << "  row.nrows = nrows;" << endl;
  Line = Form("  row.min =  %f; // ",xmin); cout << Line.Data() << endl;  out << Line.Data() << endl;
  Line = Form("  row.max =  %f; // ",xmax); cout << Line.Data() << endl;  out << Line.Data() << endl;
  Line = Form("  row.npar       =             %i;",f->GetNpar()); cout << Line.Data() << endl;  out << Line.Data() << endl;
  for (Int_t i = 0; i < f->GetNpar(); i++) {
    Line = Form("  row.a[%i]       = %13.7g;", i, f->GetParameter(i)); cout << Line.Data() << endl;  out << Line.Data() << endl;
  }
  Line = Form("  tableSet->AddAt(&row);"); cout << Line.Data() << endl;  out << Line.Data() << endl;  
  out << "  // ----------------- end of code ---------------" <<endl;
  out << "  return (TDataSet *)tableSet;" << endl;
  out << "}" << endl;
  cout << tag << endl;
 }
//________________________________________________________________________________
void  MaketpcTimeDependence() {
  TSeqCollection *fs = gROOT->GetListOfFiles();
  Int_t NF = fs->GetEntries();
  if (! fs) {
    cout << "No root files " << endl; 
  }
  TIter  iter(fs);
  c1 = (TCanvas *) gROOT->GetListOfCanvases()->FindObject("c1");
  if (! c1 ) c1 = new TCanvas("c1","c1");
  c1->Clear();
  TFile *f = 0;  
  while ((f = (TFile *) iter())) {
    f->cd();
    TNtuple *FitP = (TNtuple *) f->Get("FitP");
    if (! FitP) continue;
    FitP->Draw("mu:x>>T","(i&&dmu>0&&dmu<3e-4&&mu<0.06)/dmu**2","profg");
    TH1 *T = (TH1 *) f->Get("T");
    if (! T) continue;
    TString fName(T->GetDirectory()->GetName());
    c1->SetTitle(fName);
    fName.ReplaceAll(".root","");
    fName.ReplaceAll("TimeFGP","");
    MaketpcTimeDependence(T,fName);
    TF1 *f = (TF1 *) T->GetListOfFunctions()->FindObject("pol1");
    if (f) f->Draw("same");
    c1->Update();
    if (! gROOT->IsBatch() && Ask()) return;
 }  
}
