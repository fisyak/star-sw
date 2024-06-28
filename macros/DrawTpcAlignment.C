/* 
   root.exe 'lDb.C(0,"y2019,TFGdbOpt,CorrZ,quiet")' DrawTpcAlignment.C+
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
#include <stdio.h>
#include <string.h>
#include "Riostream.h"
#include "TString.h"
#include "TMath.h"
#include "TROOT.h"
#include "TSystem.h"
#include "TStyle.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TFile.h"
#include "StChain/StMaker.h"
#include "StTpcDb/StTpcDb.h"
#include "StDetectorDbMaker/StTpcSurveyC.h"
#include "TGraph.h"
#include "TMultiGraph.h"
#include "StChain/GeometryDbAliases.h"
#include "St_db_Maker/St_db_Maker.h"
#include "StBFChain/StBFChain.h"
#include "TDatime.h"
#endif
//________________________________________________________________________________
void DrawTpcAlignment(const Char_t *tableName = "TpcSuperSectorPosition", Int_t dMin = 20190101, Int_t dMax = 20250101) {
  StBFChain *chain = (StBFChain *) StMaker::GetTopChain();
  if (! chain) return;
  St_db_Maker *dbMk = (St_db_Maker *) chain->Maker("db");
  if (! dbMk) return;
  //  dbMk->SetDebug(1);
  TDatime t[2];						
  TDatime tOld[2];						
  TMultiGraph *mg[6] = {0};
  for (Int_t i = 0; fDbAlias[i].date; i++) {
    TString Tag(fDbAlias[i].tag);
    if (Tag.BeginsWith("y") || Tag.BeginsWith("r")) continue;
    if (Tag.BeginsWith("Cos")) continue;
    if (fDbAlias[i].date < dMin) continue;
    if (fDbAlias[i].date > dMax) continue;
    cout << "Tag:\t" << Tag.Data() << endl;
    dbMk->SetDateTime(fDbAlias[i].date,fDbAlias[i].time);
    chain->MakeEvent();
    St_SurveyC *chair = St_SurveyC::instance(tableName);
    St_db_Maker::GetValidity(chair->Table(),t);
    cout << Form("\tValidity:%8i.%06i",t[0].GetDate(),t[0].GetTime())  
	 << Form(" - %8i.%06i",t[1].GetDate(),t[1].GetTime()) << endl;
   if (t[0] == tOld[0] && t[1] == tOld[1]) continue;
    tOld[0] = t[0];
    tOld[1] = t[1];
     //    cout << t[0].AsString() << " ---- " << t[1].AsString() << endl;
    St_Survey *table = (St_Survey *) chair->Table();
    Int_t color = 1;
    if      (Tag.Contains("2020")) color = 2;
    else if (Tag.Contains("2021")) color = 3;
    else if (Tag.Contains("2022")) color = 4;
    else if (Tag.Contains("2023")) color = 6;
    else if (Tag.Contains("2024")) color = 7;
    Int_t style = 20;
    TGraph *gr[6] = {0};
    St_SurveyC::GetGraphs(table,gr);
    for (Int_t k = 0; k < 6; k++) {
      gr[k]->SetTitle(Tag);
      gr[k]->SetMarkerColor(color);
      gr[k]->SetMarkerStyle(style);
      if (! mg[k]) mg[k] = new TMultiGraph(gr[k]->GetName(), gr[k]->GetName());
      mg[k]->Add(gr[k]);
    }
  }
  TCanvas *c1 = new TCanvas(tableName,tableName,2400,1200);
  c1->Divide(3,2);
  Int_t NH = mg[0]->GetListOfGraphs()->GetSize();
  TLegend *leg = new TLegend(0.83,0.5-0.05*NH,0.98,0.7);
  for (Int_t k = 0; k < 6; k++) {
    c1->cd(k+1); mg[k]->Draw("ap");
    if (k == 0) {
      for (Int_t i = 0; i < NH; i++) {
	TGraph *g = (TGraph*) (mg[0]->GetListOfGraphs()->At(i));
	leg->AddEntry(g, g->GetTitle(), "p");
      }
      leg->Draw();
    }
  }
  c1->Update();
}
