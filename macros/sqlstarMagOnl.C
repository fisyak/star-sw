/*
  root.exe sqlstarMagOnl.C+
  T->Draw("current:time>>C(640,0.99e9,1.63e9,100,-4540,-4490)","","colz")
 */
#ifndef __CINT__
#include "Riostream.h"
#include "TSQLServer.h"
#include "TSQLResult.h"
#include "TSQLRow.h"
#include "TStopwatch.h"
#include "TFile.h"
#include "TTree.h"
#include "TString.h"
#include "TCanvas.h"
#include "TH2.h"
using namespace std;
#endif
   
void sqlstarMagOnl()
{
   TSQLServer *db = TSQLServer::Connect("mysql://dbx.star.bnl.gov:3316","", "");

   printf("Server info: %s\n", db->ServerInfo());
   
   TSQLRow *row;
   TSQLResult *res;
   struct starMagOnl_t {
     Int_t time; 
     Float_t current;
   };
   static starMagOnl_t vertex;
   static Float_t *x = &vertex.current - 1;
   TFile *fOut = new TFile("starMagOnl.root","recreate");
   TTree *tree = new TTree("T","star Mag Onl");
   tree->Branch("mag",&vertex,"time/I:current/F");
   // start timer
   TStopwatch timer;
   timer.Start();
   // query database and print results 30 secs average
   const char *sql = "select UNIX_TIMESTAMP(beginTime),current from RunLog_onl.starMagOnl "
                     "WHERE flavor='ofl' and deactive=0";
//   const char *sql = "select count(*) from Calibrations_rhic.starMagOnl "
//                     "WHERE tag&(1<<2)";
   
   res = db->Query(sql);

   int nrows = res->GetRowCount();
   printf("\nGot %d rows in result\n", nrows);
   
   int nfields = res->GetFieldCount();
   static Int_t debugP = 12;
   if (debugP > 0) {
   for (int i = 0; i < nfields; i++)
      printf("%20s", res->GetFieldName(i));
   printf("\n");
   for (int i = 0; i < nfields*40; i++)
      printf("=");
   printf("\n");
   debugP--;
   }
   for (int i = 0; i < nrows; i++) {
      row = res->Next();
      for (int j = 0; j < nfields; j++) {
	 TString Field(row->GetField(j));
	 if (debugP > 0) {
         printf("%20s ", Field.Data());
	 }
	 if (j == 0) {vertex.time = Field.Atoi(); if (debugP > 0) cout << "time " << vertex.time << endl;}
	 else        {x[j]        = Field.Atof(); if (debugP > 0) cout << "x[" << j << "] = " << x[j] << endl;}
      }
      if (debugP > 0) {
      printf("\n");
      }
      delete row;
      debugP--;
      tree->Fill();
   }
   
   delete res;
   delete db;

   // stop timer and print results
   timer.Stop();
   Double_t rtime = timer.RealTime();
   Double_t ctime = timer.CpuTime();
   fOut->Write();
   printf("\nRealTime=%f seconds, CpuTime=%f seconds\n", rtime, ctime);
}
//________________________________________________________________________________
void DrawCurrent() {// Draw all available averaged current measurements for Full Field
  TTree *tree = (TTree *) gDirectory->Get("T");
  if (! tree) return;
  Int_t nx = 900;
  Double_t xmin =  1e8;
  Double_t xmax = 10e8;
  Int_t ny = 60;
  Double_t ymin = 4504;
  Double_t ymax = 4516;
  struct Plot_t {
    const Char_t *name;
    const Char_t *title;
    const Char_t *plot;
    const Char_t *cut;
  };
  Plot_t P[3] = {
    {"CurrentT", "|current|_{onl} for Full Field  ; time ; |C|(A)", "abs(current):time - 788936400 >> CurrentT","abs(abs(current)-4510)<5"},
    {"CurrentF", "|current|_{onl} for Forward Full Fielld ; time ; |C|(A)", "abs(current):time - 788936400 >> CurrentF","current>0&&abs(abs(current)-4510)<5"},
    {"CurrentR", "|current|_{onl} for Reverse Full Fielld ; time ; |C|(A)", "abs(current):time - 788936400 >> CurrentR","current<0&&abs(abs(current)-4510)<5"}
  };
  TCanvas *c1 = new TCanvas("c1","c1",2400,1600);
  c1->Divide(1,3);
  for (Int_t i = 0; i < 3; i++) {
    c1->cd(i+1)->SetLogz(1);
    TH2F *h2 = new TH2F(P[i].name,P[i].title,nx,xmin,xmax,ny,ymin,ymax);
    h2->GetXaxis()->SetTimeDisplay(1);
    h2->GetXaxis()->SetTimeFormat("%m/%d/%y%F1995-01-01 00:00:00");
    h2->SetStats(0);
    tree->Draw(P[i].plot,P[i].cut,"colz");
  }
}
