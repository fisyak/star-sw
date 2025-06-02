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
#include "TCanvas.h"
#include "TH2.h"
using namespace std;
#endif
   
void sqlstarMagnetField() {
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
//________________________________________________________________________________
void DrawCurrent() {// Draw all available averaged current measurements for Full Field
  TTree *tree = (TTree *) gDirectory->Get("T");
  if (! tree) return;
  Int_t nx = 500;
  Double_t xmin =  5e8;
  Double_t xmax = 10e8;
  Int_t ny = 100;
  Double_t ymin = 4505;
  Double_t ymax = 4515;
  struct Plot_t {
    const Char_t *name;
    const Char_t *title;
    const Char_t *plot;
    const Char_t *cut;
  };
  Plot_t P[3] = {
    {"CurrentT", "|current| for Full Field  ; time ; |C|(A)", "abs(current):time - 788936400 >> CurrentT","abs(abs(current)-4510)<5"},
    {"CurrentF", "|current| for Forward Full Fielld ; time ; |C|(A)", "abs(current):time - 788936400 >> CurrentF","current>0&&abs(abs(current)-4510)<5"},
    {"CurrentR", "|current| for Reverse Full Fielld ; time ; |C|(A)", "abs(current):time - 788936400 >> CurrentR","current<0&&abs(abs(current)-4510)<5"}
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
/* 2024

root.exe [21] T->Draw("field","abs(current)>4500&&field>0.49875&&current<0","")
(Long64_t)5648
root.exe [22] htemp->Fit("gaus")
Warning in <Fit>: Abnormal termination of minimization.
 FCN=289.542 FROM MIGRAD    STATUS=FAILED         98 CALLS          99 TOTAL
                     EDM=4.00349e-05    STRATEGY= 1  ERROR MATRIX UNCERTAINTY   0.7 per cent
  EXT PARAMETER                APPROXIMATE        STEP         FIRST   
  NO.   NAME      VALUE            ERROR          SIZE      DERIVATIVE 
   1  Constant     3.50840e+02   6.92222e+00  -0.00000e+00   3.69306e-05
   2  Mean         4.98856e-01   5.90276e-08   0.00000e+00  -1.20766e+05
   3  Sigma        7.43439e-06   1.00267e-07   0.00000e+00   4.32144e-02
T->Draw("abs(current)","abs(current)>4500&&field>0.49875&&current<0","")
root.exe [25] htemp->Fit("gaus","er","",4508,4511)
 FCN=372.309 FROM MINOS     STATUS=SUCCESSFUL     41 CALLS         197 TOTAL
                     EDM=1.98196e-08    STRATEGY= 1      ERROR MATRIX ACCURATE 
  EXT PARAMETER                                   STEP         FIRST   
  NO.   NAME      VALUE            ERROR          SIZE      DERIVATIVE 
   1  Constant     3.67960e+02   1.14732e+01  -1.41701e-01  -3.88309e-06
   2  Mean         4.50939e+03   5.65426e-03  -1.10669e-05  -8.69611e-03
   3  Sigma        2.90532e-01   7.11119e-03   7.11119e-03  -8.16429e-02
root.exe [26] htemp->Fit("gaus","er+","",4511,4514)
 FCN=289.278 FROM MINOS     STATUS=SUCCESSFUL     41 CALLS         190 TOTAL
                     EDM=6.86532e-07    STRATEGY= 1      ERROR MATRIX ACCURATE 
  EXT PARAMETER                                   STEP         FIRST   
  NO.   NAME      VALUE            ERROR          SIZE      DERIVATIVE 
   1  Constant     5.74063e+02   1.74683e+01  -1.25881e-01  -5.93703e-07
   2  Mean         4.51244e+03   3.31308e-03   5.60764e-06  -5.06666e-03
   3  Sigma        1.53703e-01   3.33616e-03   3.33616e-03   3.83918e-02

root.exe [30] T->Draw("field","abs(current+4.50939e+03)<3*2.90532e-01&&field>0.498","")
(Long64_t)2834
root.exe [31] htemp->Fit("gaus")
Warning in <Fit>: Abnormal termination of minimization.
 FCN=209.243 FROM MIGRAD    STATUS=FAILED         96 CALLS          97 TOTAL
                     EDM=1.28999e-05    STRATEGY= 1  ERROR MATRIX UNCERTAINTY   0.2 per cent
  EXT PARAMETER                APPROXIMATE        STEP         FIRST   
  NO.   NAME      VALUE            ERROR          SIZE      DERIVATIVE 
   1  Constant     1.72948e+02   4.58175e+00  -0.00000e+00   8.40476e-05
   2  Mean         4.98857e-01   8.42949e-08   0.00000e+00  -6.02136e+04
   3  Sigma        6.05479e-06   1.08503e-07   0.00000e+00   5.97020e-02
root.exe [32] T->Draw("field","abs(current+4.51244e+03)<3*1.53703e-01&&field>0.498","")
(Long64_t)2263
root.exe [33] htemp->Fit("gaus")
Warning in <Fit>: Abnormal termination of minimization.
 FCN=255.363 FROM MIGRAD    STATUS=FAILED        126 CALLS         127 TOTAL
                     EDM=4.99408e-05    STRATEGY= 1  ERROR MATRIX UNCERTAINTY   1.3 per cent
  EXT PARAMETER                APPROXIMATE        STEP         FIRST   
  NO.   NAME      VALUE            ERROR          SIZE      DERIVATIVE 
   1  Constant     3.24102e+02   1.03107e+01  -0.00000e+00   9.24010e-05
   2  Mean         4.98853e-01   1.35805e-07   0.00000e+00  -1.60326e+05
   3  Sigma        5.68396e-06   1.24897e-07   0.00000e+00   1.30990e-01
root.exe [34] 4.50939e+03-4.51244e+03
(const double)(-3.04999999999927240e+00)
root.exe [36] 4.98857e-01- 4.98853e-01
(const double)4.00000000000400036e-06
 */
