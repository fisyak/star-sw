/*
  root.exe sqlstarMagAvgCurrentAndField.C+
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
  //  TSQLServer *db = TSQLServer::Connect("mysql://heston.star.bnl.gov:3606","test", "");
  TSQLServer *db = TSQLServer::Connect("mysql://dbbak.starp.bnl.gov:3423","", "");
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
   TFile *fOut = new TFile("starMagAvgCurrentAndField2024.root","recreate");
   TTree *tree = new TTree("T","star Magnet Current and Field sensor (T)");
   tree->Branch("mag",&BPoint,"time/I:current/F:rms/F:noEntries/I:startRunTime/I:endRunTime/I:field/F:fieldRMS/F:noFieldEntries/I");
   // start timer
   TStopwatch timer;
   timer.Start();
   const char *sqlOFL = "select UNIX_TIMESTAMP(beginTime),current,rms,noEntries,startRunTime,endRunTime  from RunLog_onl.starMagAvg "
     "WHERE flavor='ofl' and deactive=0 and rms > 0 and rms < 10 and beginTime >= '2024-07-05 14:15:30' and beginTimw <= '2024-12-26 13:18:16'";
     //                    "WHERE flavor='ofl' and deactive=0 and rms > 0 and rms < 10 and beginTime >= '2025-01-24 21:50:56'";
//   const char *sql = "select count(*) from Calibrations_rhic.starMagAvg "
//                     "WHERE tag&(1<<2)";
   
   resOFL = dbOFL->Query(sqlOFL);
   if (! resOFL) return;
   static Int_t debugP = 1;

   Int_t nrowsOFL = resOFL->GetRowCount();
   if (debugP > 0) printf("\nGot %d rowsOFL in result\n", nrowsOFL);
   Int_t nfieldsOFL = resOFL->GetFieldCount();

   // query database and print results 30 secs average
   
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
/*
FF
 T->Draw("field:current>>FF(30,4510,4513)","current>4400&&field>0.4988","prof")
root.exe [14] T->Draw("field","current>4400&&field>0.4988","")
(Long64_t)65
root.exe [15] htemp->Fit("gaus")
 FCN=17.9646 FROM MIGRAD    STATUS=CONVERGED     119 CALLS         120 TOTAL
                     EDM=9.44681e-07    STRATEGY= 1      ERROR MATRIX ACCURATE 
  EXT PARAMETER                                   STEP         FIRST   
  NO.   NAME      VALUE            ERROR          SIZE      DERIVATIVE 
   1  Constant     1.55503e+00   2.81637e-01   4.81658e-04  -5.88006e-04
   2  Mean         4.98858e-01   7.00058e-06   2.37874e-07   1.82075e+02
   3  Sigma        1.95070e-05   1.08205e-05   5.23415e-04  -7.92125e-04
 1.95070e-05/4.98858e-01= 3.9e-05
root.exe [16] T->Draw("current","current>4400&&field>0.4988","")
root.exe [17] htemp->Fit("gaus")
 FCN=15.2948 FROM MIGRAD    STATUS=CONVERGED     116 CALLS         117 TOTAL
                     EDM=3.8223e-09    STRATEGY= 1      ERROR MATRIX ACCURATE 
  EXT PARAMETER                                   STEP         FIRST   
  NO.   NAME      VALUE            ERROR          SIZE      DERIVATIVE 
   1  Constant     1.67124e+00   3.23817e-01   4.67198e-04   1.04856e-04
   2  Mean         4.51248e+03   1.10896e-01   2.15172e-03  -7.06669e-04
   3  Sigma        3.28950e-01   2.17888e-01   5.54642e-04   5.90909e-05
3.28950e-01/4.51248e+03 = 7.3e-05
root.exe [22] 4500/(9.98071899596718826e-01)
(const double)4.50869321320264680e+03               => 4508.7 A

root.exe [20] 4.51248e+03/(4500/(9.98071899596718826e-01))
(const double)1.00083988566493365e+00
root.exe [21] 4.51248e+03/(4500/(9.98071899596718826e-01))-1
(const double)8.39885664933648357e-04

RF

T->Draw("abs(current)>>RFC","current<-4400&&field>0.4988","")

root.exe [26] RFC->Fit("gaus","er","",4508,4511)
 FCN=70.654 FROM MINOS     STATUS=SUCCESSFUL     42 CALLS         226 TOTAL
                     EDM=8.80699e-08    STRATEGY= 1      ERROR MATRIX ACCURATE 
  EXT PARAMETER                                   STEP         FIRST   
  NO.   NAME      VALUE            ERROR          SIZE      DERIVATIVE 
   1  Constant     5.47373e+01   3.39635e+00  -1.19126e-02   1.90647e-04
   2  Mean         4.50970e+03   1.34349e-02  -2.06312e-05   3.82179e-02
   3  Sigma        2.90748e-01   1.35364e-02   1.35364e-02  -6.25564e-04

root.exe [27] RFC->Fit("gaus","er+","",4511,4514)
 FCN=65.6351 FROM MINOS     STATUS=SUCCESSFUL     85 CALLS         364 TOTAL
                     EDM=3.29697e-06    STRATEGY= 1      ERROR MATRIX ACCURATE 
  EXT PARAMETER                                   STEP         FIRST   
  NO.   NAME      VALUE            ERROR          SIZE      DERIVATIVE 
   1  Constant     3.95495e+01   4.96014e+00   6.81894e-02  -7.95756e-05
   2  Mean         4.51258e+03   1.90403e-02   2.01413e-04  -3.97224e-04
   3  Sigma        1.62554e-01   1.76796e-02   1.76796e-02  -9.82392e-02
(class TFitResultPtr)24671296

================================================================================
[rcas6007] ~/work/Magnet $ root.exe starMagAvg.root
   TCanvas *c1 = new TCanvas("c1","c1",2400,1600);
   c1->Divided(1,3);
   c1->cd(1)->SetLogz(1);
   TH2F *CurrentT = new TH2F("CurrentT","|current| for Full Field  versus time, all",500,5e8,10e8,100,4500,4520);
   
   T->Draw("abs(current):time-788936400>>CurrentT","abs(abs(current)-4500)<100","colz");
 */
