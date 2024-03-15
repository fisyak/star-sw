/*
  root.exe 'lDb.C(1,"r2019")'  testTpcCoordinateTransform.C
*/
#ifndef __CINT__
#include "StTpcDb/StTpcDb.h"
#include "StDbUtilities/StTpcCoordinateTransform.hh"
#else
class StTpcCoordinateTransform;
#endif
//StTpcCoordinateTransform *transform = 0;
StTpcCoordinateTransform transform(StTpcCoordinateTransform(StTpcDb::instance()));
//________________________________________________________________________________
void Print(Int_t sector = 1, Int_t row = 24, Int_t pad = 1, Int_t time = 1, 
	   Double_t rx=0, Double_t ry=1, Double_t rz=0) {
  cout << endl; cout << endl;
#if 0
  cout << "Directions =============================" << endl;
  StTpcLocalSectorDirection   dirLS(rx,ry,rz,sector,row);      cout << dirLS << endl;
  StTpcLocalSectorAlignedDirection     dirLSA;//cout << dirLSA << endl;
  transform(dirLS,dirLSA);                     cout << dirLSA << endl;
  StTpcLocalDirection                  dirL;
  transform(dirLSA,dirL);                      cout << dirL << endl;
  StGlobalDirection                    dirG;
  transform(dirL,dirG);                        cout << dirG << endl;
  cout << "Back ===================================" << endl;
  transform(dirG,dirL,sector,row);             cout << dirL << endl;
  transform(dirL,dirLSA);                      cout << dirLSA << endl;
  transform(dirLSA,dirLS);                     cout << dirLS << endl;
#endif
  cout << "Coordinates ============================" << endl;
  StTpcPadCoordinate coorP(sector, row, pad, time);             cout << coorP << endl; 
  StTpcLocalSectorCoordinate  coorLS;
  transform(coorP,coorLS);                     cout << coorLS << endl;
  StTpcLocalSectorAlignedCoordinate  coorLSA;
  transform(coorLS,coorLSA);                   cout << coorLSA << endl;
  StTpcLocalCoordinate  coorL;
  transform(coorLSA,coorL);                    cout << coorL << endl;
  StGlobalCoordinate    coorG;
  transform(coorL,coorG);                      cout << coorG << endl;
  cout << "Back ===================================" << endl;
  transform(coorG,coorL, sector, row);         cout << coorL << endl;
  transform(coorL,coorLSA);                    cout << coorLSA << endl;
  transform(coorLSA,coorLS);                   cout << coorLS  << endl;
  transform(coorLS,coorP);                     cout << coorP << endl; 
}
//________________________________________________________________________________
void PrintPad(Int_t sector = 3, Int_t row = 24, Int_t pad = 1, Int_t time = 0) {
  cout << endl; cout << endl;
  cout << "Coordinates ============================" << endl;
  StTpcPadCoordinate coorP(sector, row, pad, time);             cout << coorP << endl; 
  StTpcLocalSectorCoordinate  coorLS;
  StTpcLocalSectorCoordinate  coorLST;
  StTpcLocalSectorCoordinate  coorLSF;
  StGlobalCoordinate   coorG;
  transform(coorP,coorLS ,kFALSE, kTRUE);  cout << "Cluster without T0, with    tau\t" << coorLS  << endl;
  transform(coorP,coorLST,kFALSE,kFALSE);  cout << "Pixel   with    T0, without tau\t" << coorLST << endl;
  transform(coorP,coorLST, kTRUE,kFALSE);  cout << "Pixel   without T0, without tau\t" << coorLST << endl;
  transform(coorP,coorG, kTRUE,kFALSE);    cout << "Pixel   without T0, without tau\t" << coorG   << endl;
  cout << "=========================== Test StTpcDb Rotations ====================================================" << endl;
  cout << "coorG " << coorG << endl;
  Double_t xyzL[3];
  StTpcDb::instance()->Tpc2GlobalMatrix().MasterToLocal(coorG.position().xyz(), xyzL);
  StTpcLocalCoordinate coorTPC(xyzL); cout << "coorTPC " << coorTPC << endl;
  StTpcDb::instance()->SupS2Tpc(sector).MasterToLocal(coorTPC.position().xyz(), xyzL); 
  StTpcLocalSectorCoordinate coorLS2(xyzL);  cout << "coorLS2 " << coorLS2 << endl;
  StTpcLocalSectorCoordinate coorLS3;
  transform(coorTPC,coorLS3);  cout << "coorLS3 " << coorLS3 << endl;
}
//________________________________________________________________________________
void PrintXYZ(Double_t x = 59.3696, Double_t y = 0.871471, Double_t z = 208.707) {
  cout << "Coordinates ============================" << endl;
  StGlobalCoordinate   coorG(x,y,z); cout << "coorG\t" << coorG << endl;
  StTpcLocalCoordinate  coorL; transform(coorG, coorL, 3, 3); cout << "coorL\t" << coorL << endl; 
  StTpcLocalSectorCoordinate  coorLS; 
  StTpcLocalSectorCoordinate  coorLSF;
  transform(coorL,coorLS);  cout << "Cluster without T0, with    tau\t" << coorLS << endl;
}
//________________________________________________________________________________
void testTpcCoordinateTransform() {
  //  if (dbMk == 0) Load(d,t);
  StTpcDb::instance()->SetDriftVelocity();


  StTpcDb::instance()->SetTpcRotations();
  transform = new StTpcCoordinateTransform(StTpcDb::instance());
  Int_t sector = 12;
  Int_t row    = 45;
  //  Print(sector,row);
  PrintPad(3,24);
}
//________________________________________________________________________________
void testDerivatives() {
  //  if (dbMk == 0)  Load(d,t);
  StTpcDb::instance()->SetDriftVelocity();
  StTpcDb::instance()->SetTpcRotations();
  //  transform = new StTpcCoordinateTransform(StTpcDb::instance());
  Double_t pad = 10, dpad = 0.5;
  Double_t  time = 100, dtime = 0.5;
  Int_t row = 45;
  StTpcLocalCoordinate   coorG, coorGd;
  for (Int_t sector = 1; sector <= 24; sector++) {
    StTpcPadCoordinate coorP(sector, row, pad, time);             cout << "coorP " << coorP  << endl;
    transform(coorP,coorG, kTRUE,kFALSE);             cout << "coorG " << coorG  << endl;
    StTpcPadCoordinate coorP(sector, row, pad+dpad, time+dtime);  cout << "coorPd" << coorP  << endl;
    transform(coorP,coorGd, kTRUE,kFALSE);            cout << "coorGd" << coorGd << endl;
    Double_t dX = (coorGd.position().x() - coorG.position().x())/dpad;
    Double_t dY = (coorGd.position().y() - coorG.position().y())/dpad;
    Double_t dZ = (coorGd.position().z() - coorG.position().z())/dtime;
    cout << "sector = " << sector << "\tdX = " << dX << "\tdY = " << dY << "\tdZ = " << dZ << endl;
  }
}
