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
rcas6010] ~ $  mysql -h heston.star.bnl.gov --port=3606 -u "" --password="" mq_collector_Conditions_rhic
MySQL [mq_collector_Conditions_rhic]> select * from magnetField order by beginTime limit 10;
+---------+---------------------+---------------------+--------------+
| dataID  | entryTime           | beginTime           | magnet:field |
+---------+---------------------+---------------------+--------------+
| 2991745 | 2025-02-24 21:50:56 | 2025-02-24 21:50:56 |      0.45545 |
| 2991746 | 2025-02-24 21:51:01 | 2025-02-24 21:51:01 |      0.45545 |
| 2991747 | 2025-02-24 21:51:06 | 2025-02-24 21:51:06 |      0.45545 |
| 2991748 | 2025-02-24 21:51:11 | 2025-02-24 21:51:11 |      0.45545 |
| 2991749 | 2025-02-24 21:51:16 | 2025-02-24 21:51:16 |      0.45545 |
| 2991750 | 2025-02-24 21:51:21 | 2025-02-24 21:51:21 |      0.45545 |
| 2991751 | 2025-02-24 21:51:26 | 2025-02-24 21:51:26 |      0.45545 |
| 2991752 | 2025-02-24 21:51:31 | 2025-02-24 21:51:31 |      0.45545 |
| 2991753 | 2025-02-24 21:51:36 | 2025-02-24 21:51:36 |      0.45545 |
| 2991754 | 2025-02-24 21:51:41 | 2025-02-24 21:51:41 |      0.45545 |
+---------+---------------------+---------------------+--------------+
10 rows in set (0.00 sec)
mysql -h dbbak.starp.bnl.gov --port=3423
MySQL [mq_collector_Conditions_rhic]> select * from magnetField order by beginTime limit 10;
+--------+---------------------+---------------------+--------------+
| dataID | entryTime           | beginTime           | magnet:field |
+--------+---------------------+---------------------+--------------+
|      1 | 2024-07-05 14:15:30 | 2024-07-05 14:15:29 |     0.498857 |
|      2 | 2024-07-05 14:15:34 | 2024-07-05 14:15:34 |      0.49885 |
|      3 | 2024-07-05 14:15:39 | 2024-07-05 14:15:39 |     0.498857 |
|      4 | 2024-07-05 14:15:46 | 2024-07-05 14:15:44 |     0.498857 |
|      5 | 2024-07-05 14:15:49 | 2024-07-05 14:15:49 |     0.498868 |
|      6 | 2024-07-05 14:15:54 | 2024-07-05 14:15:54 |     0.498868 |
|      7 | 2024-07-05 14:15:59 | 2024-07-05 14:15:59 |     0.498854 |
|      8 | 2024-07-05 14:16:05 | 2024-07-05 14:16:04 |     0.498845 |
|      9 | 2024-07-05 14:16:09 | 2024-07-05 14:16:09 |     0.498845 |
|     10 | 2024-07-05 14:16:14 | 2024-07-05 14:16:14 |     0.498857 |
+--------+---------------------+---------------------+--------------+
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
#include "TMath.h"
using namespace std;
#endif
   
void sqlstarMagAvgCurrentAndField() {
  TSQLServer *db = TSQLServer::Connect("mysql://heston.star.bnl.gov:3606","test", "");
  if (! db) return;
  printf("Server info: %s\n", db->ServerInfo());
  TSQLServer *dbOFL = TSQLServer::Connect("mysql://dbx.star.bnl.gov:3316","", "");
  printf("Server info: %s\n", dbOFL->ServerInfo());
   
  TSQLRow *row, *rowOFL;
  TSQLResult *res, *resOFL;
  struct starMagnetField_t {
    Int_t   time;           // dbOFL
    Float_t current;
    Float_t rms;
    Int_t   noEntries;
    Int_t   startRunTime;
    Int_t   endRunTime;
    Float_t field;         // onl
    Float_t fieldRMS;
    Int_t   noFieldEntries;
  };
   static starMagnetField_t BPoint;
   static Int_t   *xix = &BPoint.time;
   static Float_t *xfx = (Float_t *) xix;
   TFile *fOut = new TFile("starMagAvgCurrentAndField.root","recreate");
   TTree *tree = new TTree("T","star Magnet Current and Field sensor (T)");
   tree->Branch("mag",&BPoint,"time/I:current/F:rms/F:noEntries/I:startRunTime/I:endRunTime/I:field/F:fieldRMS/F:noFieldEntries/I");
   // start timer
   TStopwatch timer;
   timer.Start();
   const char *sqlOFL = "select UNIX_TIMESTAMP(beginTime),current,rms,noEntries,startRunTime,endRunTime  from RunLog_onl.starMagAvg "
                     "WHERE flavor='ofl' and deactive=0 and rms > 0 and rms < 10 and beginTime >= '2025-02-24 21:50:56'";
   //                     "WHERE flavor='ofl' and deactive=0 and rms > 0 and rms < 10 and beginTime >= '2024-07-05 14:15:30";
//   const char *sql = "select count(*) from Calibrations_rhic.starMagAvg "
//                     "WHERE tag&(1<<2)";
   
   resOFL = dbOFL->Query(sqlOFL);
   if (! resOFL) return;

   Int_t nrowsOFL = resOFL->GetRowCount();
   if (debugP > 0) printf("\nGot %d rowsOFL in result\n", nrowsOFL);
   Int_t nfieldsOFL = resOFL->GetFieldCount();

   // query database and print results 30 secs average
   
   static Int_t debugP = 1;
   for (Int_t i = 0; i < nrowsOFL; i++) {
     if (debugP > 0) {
       for (Int_t i = 0; i < nfieldsOFL; i++)
	 printf("%20s", resOFL->GetFieldName(i));
       printf("\n");
       for (Int_t i = 0; i < nfieldsOFL*40; i++)
	 printf("=");
       printf("\n");
     }
     rowOFL = resOFL->Next();
     for (Int_t j = 0; j < nfieldsOFL; j++) {
       TString Field(rowOFL->GetField(j));
       if (debugP > 0) printf("%20s ", Field.Data());
       if (j == 0 || j >= 3 && j <= 5 || j == 8) {
	 xix[j]  = Field.Atoi();
       } else {
	 xfx[j] = Field.Atof(); 
       }
     }
     if (debugP > 0) {
       printf("u = %i, field = %f\n", BPoint.time,  BPoint.field);
       debugP--;
     }
     delete rowOFL;
     TString SQL(Form("SELECT *  from mq_collector_Conditions_rhic.magnetField WHERE UNIX_TIMESTAMP(beginTime) >= %i and UNIX_TIMESTAMP(beginTime) <= %i",BPoint.startRunTime,BPoint.endRunTime));
     res = db->Query(SQL.Data());
     if (! res) continue;
     Int_t nrows = res->GetRowCount();
     if (debugP > 0) printf("\nGot %d rows in result\n", nrows);
     if (nrows < 1) continue;
     Int_t nfields = res->GetFieldCount();
     Double_t xav = 0;
     Double_t xx2 = 0;
     Double_t f   = 0;
     for (Int_t k = 0; k < nrows; k++) {
       if (k == 0) {
	 for (Int_t j = 0; j < nfieldsOFL; j++) {
	   if (debugP > 0) {
	     for (Int_t i = 0; i < nfieldsOFL; i++)
	       printf("%20s", resOFL->GetFieldName(i));
	     printf("\n");
	     for (Int_t i = 0; i < nfieldsOFL*40; i++)
	       printf("=");
	     printf("\n");
	   }
	 }
       }
       row = res->Next();
       Int_t j = 3;
       TString Field(row->GetField(j));
       if (debugP > 0) printf("%20s ", Field.Data());
       f = Field.Atof();
       xav += f;
       xx2 += f*f;
       delete row;
     }
     xav /= nrows;
     xx2 /= nrows;
     BPoint.field = xav;
     BPoint.fieldRMS = TMath::Sqrt(xx2 - xav*xav);
     BPoint.noFieldEntries = nrows;
     tree->Fill();
     debugP--;
     delete res;
   }
   delete resOFL;
   delete dbOFL;
   delete db;

   // stop timer and print results
   timer.Stop();
   Double_t rtime = timer.RealTime();
   Double_t ctime = timer.CpuTime();
   fOut->Write();
   printf("\nRealTime=%f seconds, CpuTime=%f seconds\n", rtime, ctime);
}
