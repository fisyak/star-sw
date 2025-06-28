/*
foreach db (tpcAcCharge TpcAccumulatedQ TpcAdcCorrection3MDF TpcAdcCorrection4MDF TpcAdcCorrection5MDF TpcAdcCorrection6MDF TpcAdcCorrectionB TpcAdcCorrectionC TpcAdcCorrectionMDF TpcAdcI tpcBXT0CorrEPD TpcCurrentCorrectionX TpcdCharge TpcdEdxCor TpcDriftDistOxygen tpcDriftVelocity TpcDriftVelRowCor TpcdXCorrectionB TpcdXdY TpcdZdY TpcEdge TpcEffectivedX TpcEtaCorrection TpcEtaCorrectionB tpcExtraGainCorrection tpcGainCorrection tpcGasTemperature TpcLengthCorrectionB TpcLengthCorrectionMDF TpcLengthCorrectionMDN tpcMethaneIn TpcMultiplicity TpcnPad TpcnTbk TpcPadCorrection TpcPadCorrectionMDC TpcPadCorrectionMDF TpcPhiDirection tpcPressureB TpcrCharge tpcRDOMap tpcRDOT0offset TpcResponseSimulator TpcRowQ TpcSecRowB tpcSectorT0offset tpcSlewing TpcSpaceCharge tpcStatus tpcT0 tpcT0BX TpcTanL tpcTimeBucketCor tpcTimeDependence tpcWaterOut TpcZCorrectionB TpcZCorrectionC TpcZDC) 
  mysql -h robinson.star.bnl.gov --port=3306 -u "fisyak" Calibrations_tpc -e 'select entryTime, beginTime, flavor, elementID, deactive from '${db}'  where elementID=1 and  deactive = 0 order by beginTime;' | tee ${db}.txt
end
  
  root.exe -q -b DbMap.C+ >& DbMap.log

  DbMap("TpcAdcCorrection6MDF.txt");   >> TpcAdcCorrection6MDF.log
  DbMap("TpcSecRowB.txt");             >> TpcSecRowB.log
  DbMap("tpcPressureB.txt");           >> tpcPressureB.log
  DbMap("TpcZCorrectionC.txt");        >> TpcZCorrectionC.log
  DbMap("TpcPadCorrectionMDC.txt");    >>TpcPadCorrectionMDC.log
  DbMap("tpcTimeDependence.txt");      >> tpcTimeDependence.log
  DbMap("TpcLengthCorrectionMDN.txt"); >> TpcLengthCorrectionMDN.log

*/
#include <stdio.h>
#include "Rtypes.h"
#include "Riostream.h"
#include "TSystem.h"
#include "TString.h"
#include "TDirIter.h"
struct DbAlias_t {
  const char *tag;
  Int_t date;
  Int_t time;
  const char *geometry;
  const char *comment;
};
#include "StChain/GeometryDbAliases.h"
void DbMap(const Char_t *FileName) {
#if 0
  for (Int_t i = 0; fDbAlias[i].date; i++) {
    Double_t dt1 = fDbAlias[i].date   + ((Double_t) fDbAlias[i].time)  /1000000.;
    Double_t dt2 = fDbAlias[i+1].date + ((Double_t) fDbAlias[i+1].time)/1000000.;
    if (dt1 > dt2) {
      cout << "Wrong order; " << fDbAlias[i].tag << " > " << fDbAlias[i+1].tag << Form("dt1 = %16.6f, dt2 = %16.6f\n",dt1,dt2);
    }
  }
#endif
  TString F(FileName); F.ReplaceAll(".txt","");
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
	printf("%-28s %-32s %8i %6i beginTime = %4d-%02d-%02d %02d:%02d:%02d, entryTime %s",Tag.Data(),F.Data(),d,t, bY,bM,bD,bh,bm,bs,line);
	break;
      }
    }    
#if 0
    printf("%4d-%02d-%02d %02d:%02d:%02d   %4d-%02d-%02d %02d:%02d:%02d -- ",eY,eM,eD,eh,em,es,bY,bM,bD,bh,bm,bs);
#endif
  }
  fclose(fp);
}
//________________________________________________________________________________
void DbMap() {
  TDirIter Dir("*.txt");
  Char_t *file = 0;
  while ((file = (Char_t *) Dir.NextFile())) {
    printf("%s ====================\n",file);
    DbMap(file);
  }
}
