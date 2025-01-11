/*
  mysql -h robinson.star.bnl.gov --port=3306 -u "fisyak" Calibrations_tpc -e 'select entryTime, beginTime, flavor, elementID, deactive from TpcSecRowB where elementID=1 and  deactive = 0 and beginTime > "2019" and beginTime < "2022" order by beginTime;' | tee TpcSecRowB.txt
  root.exe 'DbMap.C+("TpcSecRowB.txt")' 
  mysql -h robinson.star.bnl.gov --port=3306 -u "fisyak" Calibrations_tpc -e 'select entryTime, beginTime, flavor, elementID, deactive from tpcTimeDependence  where elementID=1 and  deactive = 0 and beginTime > "2019" and beginTime < "2022" order by beginTime;' | tee tpcTimeDependence.txt
  root.exe 'DbMap.C+("tpcTimeDependence.txt")'
  mysql -h robinson.star.bnl.gov --port=3306 -u "fisyak" Calibrations_tpc -e 'select entryTime, beginTime, flavor, elementID, deactive from TpcLengthCorrectionMDN  where elementID=1 and  deactive = 0 and beginTime > "2019" and beginTime < "2022" order by beginTime;' | tee TpcLengthCorrectionMDN.txt
  mysql -h robinson.star.bnl.gov --port=3306 -u "fisyak" Calibrations_tpc -e 'select entryTime, beginTime, flavor, elementID, deactive from TpcLengthCorrectionMDN  where elementID=1 and  deactive = 0 and beginTime > "2019" and beginTime < "2022" order by beginTime;' | tee TpcLengthCorrectionMDN.txt
  root.exe 'DbMap.C+("TpcLengthCorrectionMDN.txt")'
  mysql -h robinson.star.bnl.gov --port=3306 -u "fisyak" Calibrations_tpc -e 'select entryTime, beginTime, flavor, elementID, deactive from TpcZCorrectionC  where elementID=1 and  deactive = 0 and beginTime > "2019" and beginTime < "2022" order by beginTime;' | tee TpcZCorrectionC.txt
  root.exe 'DbMap.C+("TpcZCorrectionC.txt")'

  mysql -h robinson.star.bnl.gov --port=3306 -u "fisyak" Calibrations_tpc -e 'select entryTime, beginTime, flavor, elementID, deactive from TpcLengthCorrectionMDN  where elementID=1 and  deactive = 0 order by beginTime;' | tee TpcLengthCorrectionMDN.txt
  root.exe 'DbMap.C+("TpcLengthCorrectionMDN.txt")'

*/
#include <stdio.h>
#include "Rtypes.h"
#include "Riostream.h"
#include "TSystem.h"
#include "TString.h"
struct DbAlias_t {
  const char *tag;
  Int_t date;
  Int_t time;
  const char *geometry;
  const char *comment;
};
#include "StChain/GeometryDbAliases.h"
void DbMap(const Char_t *FileName = "TpcLengthCorrectionMDN.txt") {
#if 0
    for (Int_t i = 0; fDbAlias[i].date; i++) {
      Double_t dt1 = fDbAlias[i].date   + ((Double_t) fDbAlias[i].time)  /1000000.;
      Double_t dt2 = fDbAlias[i+1].date + ((Double_t) fDbAlias[i+1].time)/1000000.;
      if (dt1 > dt2) {
	cout << "Wrong order; " << fDbAlias[i].tag << " > " << fDbAlias[i+1].tag << Form("dt1 = %16.6f, dt2 = %16.6f\n",dt1,dt2);
      }
    }
#endif
  FILE *fp = fopen(FileName,"r");
  if (! fp) {
    cout << "Can't open" << FileName << endl;
    return;
  }
  TString fName(gSystem->BaseName(FileName));
  char line[121];
  Int_t eY,eM,eD,eh,em,es;
  Int_t bY,bM,bD,bh,bm,bs;
  Int_t n = 0;
  while (fgets(&line[0],120,fp)) {
    if (line[0] == 'e') continue;
    Int_t n1 = sscanf(&line[0],"%4d-%2d-%2d %2d:%2d:%2d",&eY,&eM,&eD,&eh,&em,&es);
    Int_t n2 = sscanf(&line[20],"%4d-%2d-%2d %2d:%2d:%2d ",&bY,&bM,&bD,&bh,&bm,&bs);
    n = n1 + n2;
    Int_t d = bD + 100*(bM + 100*bY);
    Int_t t = bs + 100*(bm + 100*bh);
    //    printf("%i date = %8i, time = %6i, %s",n,d,t,line);
    Double_t dt = d + ((Double_t) t)/100000;
    TString Tag;
    for (Int_t i = 0; fDbAlias[i].date; i++) {
      Double_t dt1 = fDbAlias[i].date   + ((Double_t) fDbAlias[i].time)/  1000000.;
      Double_t dt2 = fDbAlias[i+1].date + ((Double_t) fDbAlias[i+1].time)/1000000.;
#if 0
      if (fDbAlias[i].tag[0] == 'y') continue;
      if (fDbAlias[i].tag[0] == 'r') continue;
      printf("d = %8i t = %6i tag = %-32s\n",d,t,fDbAlias[i].tag);
      printf("d = %8i, t=%6i, %-32s d = %8i, t=%6i %-32s d = %8i, t=%6i\n",d,t,fDbAlias[i].tag, fDbAlias[i].date, fDbAlias[i].time,fDbAlias[i+1].tag,fDbAlias[i+1].date, fDbAlias[i+1].time);
#endif
      if (dt1 <= dt && dt < dt2) {
	Tag = fDbAlias[i].tag;
	printf("%-32s %8i %6i beginTime = %4d-%02d-%02d %02d:%02d:%02d, entryTime %s",Tag.Data(),d,t, bY,bM,bD,bh,bm,bs,line);
	break;
      }
    }    
#if 0
    printf("%4d-%02d-%02d %02d:%02d:%02d   %4d-%02d-%02d %02d:%02d:%02d -- ",eY,eM,eD,eh,em,es,bY,bM,bD,bh,bm,bs);
#endif
  }
  fclose(fp);
}
