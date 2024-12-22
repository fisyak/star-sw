/*
  mysql -h robinson.star.bnl.gov --port=3306 -u "fisyak" Calibrations_tpc -e 'select entryTime, beginTime, flavor, elementID, deactive from TpcSecRowB where elementID=1 and  deactive = 0 and beginTime > "2019" and beginTime < "2022" order by beginTime;' | tee TpcSecRowB.txt
  root.exe 'DbMap.C+("TpcSecRowB.txt")' 
  mysql -h robinson.star.bnl.gov --port=3306 -u "fisyak" Calibrations_tpc -e 'select entryTime, beginTime, flavor, elementID, deactive from tpcTimeDependence  where elementID=1 and  deactive = 0 and beginTime > "2019" and beginTime < "2022" order by beginTime;' | tee tpcTimeDependence.txt
  root.exe 'DbMap.C+("tpcTimeDependence.txt")'
  mysql -h robinson.star.bnl.gov --port=3306 -u "fisyak" Calibrations_tpc -e 'select entryTime, beginTime, flavor, elementID, deactive from TpcLengthCorrectionMDN  where elementID=1 and  deactive = 0 and beginTime > "2019" and beginTime < "2022" order by beginTime;' | tee TpcLengthCorrectionMDN.txt
  root.exe 'DbMap.C+("TpcLengthCorrectionMDN.txt")'
  mysql -h robinson.star.bnl.gov --port=3306 -u "fisyak" Calibrations_tpc -e 'select entryTime, beginTime, flavor, elementID, deactive from TpcZCorrectionC  where elementID=1 and  deactive = 0 and beginTime > "2019" and beginTime < "2022" order by beginTime;' | tee TpcZCorrectionC.txt
  root.exe 'DbMap.C+("TpcZCorrectionC.txt")'
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
void DbMap(const Char_t *FileName = "MySQL_select.txt") {
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
    TString Tag;
    for (Int_t i = 0; fDbAlias[i].tag; i++) {
      if (fDbAlias[i].tag[0] == 'y') continue;
      if (fDbAlias[i].tag[0] == 'r') continue;
      if (d > fDbAlias[i].date) continue;
      if (t > fDbAlias[i].time) continue;
      Tag = fDbAlias[i].tag;
      break;
    }    
    printf("%-32s %8i %6i beginTime = %4d-%02d-%02d %02d:%02d:%02d -- %s",Tag.Data(),d,t, bY,bM,bD,bh,bm,bs,line);
#if 0
    printf("%4d-%02d-%02d %02d:%02d:%02d   %4d-%02d-%02d %02d:%02d:%02d -- ",eY,eM,eD,eh,em,es,bY,bM,bD,bh,bm,bs);
    printf("%i date = %8i, time = %6i, %s",n,d,t,line);
#endif
  }
  fclose(fp);
}
