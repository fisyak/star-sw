/*
  root.exe sqlstarMagnetField.C+
  T->Draw("current:time-946684800+978325200>>AvgC(1000,633e6,641e6,100,-4520,-4500","","sames");
  select unix_timestamp("1995-01-01 00:00:00"); 788918400     
  select unix_timestamp("2000-01-01 00:00:00"); 946684800     TDatime tt(2000,1,1,0,0,0); 946702800 => +18000
  select unix_timestamp("2021-01-01 00:00:00"); 1609459200
  select unix_timestamp("2022-01-01 00;00:00"); 1640995200
  T->Draw("current:time-31640400","current>-4540&&current<-4460")
  T->Draw("current:time-946684800>>h2021","current>-4550&&current<-4450&&time>1609459200")
  T->Draw("current:(time-1609459200)/24/60/60+1>>h2021","current>-4550&&current<-4450&&time>1609459200")
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
#include "TDatime.h"
using namespace std;
#endif
   
void sqlstarMagnetField()
{
   TSQLServer *db = TSQLServer::Connect("mysql://heston.star.bnl.gov:3606","test", "");
   if (! db) return;
   printf("Server info: %s\n", db->ServerInfo());
   
   TSQLRow *row;
   TSQLResult *res;
   struct starMagnetField_t {
     Int_t   time; 
     Float_t field;
   };
   static starMagnetField_t BPoint;
   TFile *fOut = new TFile("starMagnetField.root","recreate");
   TTree *tree = new TTree("T","star Magnet Field sensor (T)");
   tree->Branch("mag",&BPoint,"time/I:field/F");
   // start timer
   TStopwatch timer;
   timer.Start();
   // query database and print results 30 secs average
   const char *sql = "SELECT *  from mq_collector_Conditions_rhic.magnetField WHERE dataID > 0";
   //                     "WHERE flavor='ofl' and deactive=0";
//   const char *sql = "select count(*) from Calibrations_rhic.starMagnetField  "
//                     "WHERE tag&(1<<2)";
   
   res = db->Query(sql);
   if (! res) return;
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
   }
   for (int i = 0; i < nrows; i++) {
     row = res->Next();
     for (int j = 0; j < nfields; j++) {
       TString Field(row->GetField(j));
       if (debugP > 0) {
	 printf("%20s ", Field.Data());
       }
       if       (j == 2) {
	 TDatime time(row->GetField(j));
	 BPoint.time = time.Convert();
       } else if (j == 3) {
	   BPoint.field = Field.Atof(); 
       }
     }
     if (debugP > 0) {
       printf("u = %i, field = %f\n", BPoint.time,  BPoint.field);
       debugP--;
     }
     delete row;
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
