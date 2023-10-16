/*
  root.exe 'lDb.C("r2019",0)'  testTpcCoordinateTransform.C
*/
class StTpcCoordinateTransform;
StTpcCoordinateTransform *transform = 0;
//________________________________________________________________________________
void Print(Int_t sector = 1, Int_t row = 24, Int_t pad = 1, Int_t time = 1, 
	   Double_t rx=0, Double_t ry=1, Double_t rz=0) {
  cout << endl; cout << endl;
#if 0
  cout << "Directions =============================" << endl;
  StTpcLocalSectorDirection   dirLS(rx,ry,rz,sector,row);      cout << dirLS << endl;
  StTpcLocalSectorAlignedDirection     dirLSA;//cout << dirLSA << endl;
  transform->operator()(dirLS,dirLSA);                     cout << dirLSA << endl;
  StTpcLocalDirection                  dirL;
  transform->operator()(dirLSA,dirL);                      cout << dirL << endl;
  StGlobalDirection                    dirG;
  transform->operator()(dirL,dirG);                        cout << dirG << endl;
  cout << "Back ===================================" << endl;
  transform->operator()(dirG,dirL,sector,row);             cout << dirL << endl;
  transform->operator()(dirL,dirLSA);                      cout << dirLSA << endl;
  transform->operator()(dirLSA,dirLS);                     cout << dirLS << endl;
#endif
  cout << "Coordinates ============================" << endl;
  StTpcPadCoordinate coorP(sector, row, pad, time);             cout << coorP << endl; 
  StTpcLocalSectorCoordinate  coorLS;
  transform->operator()(coorP,coorLS);                     cout << coorLS << endl;
  StTpcLocalSectorAlignedCoordinate  coorLSA;
  transform->operator()(coorLS,coorLSA);                   cout << coorLSA << endl;
  StTpcLocalCoordinate  coorL;
  transform->operator()(coorLSA,coorL);                    cout << coorL << endl;
  StGlobalCoordinate    coorG;
  transform->operator()(coorL,coorG);                      cout << coorG << endl;
  cout << "Back ===================================" << endl;
  transform->operator()(coorG,coorL, sector, row);         cout << coorL << endl;
  transform->operator()(coorL,coorLSA);                    cout << coorLSA << endl;
  transform->operator()(coorLSA,coorLS);                   cout << coorLS  << endl;
  transform->operator()(coorLS,coorP);                     cout << coorP << endl; 
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
  transform->operator()(coorP,coorLS ,kFALSE, kTRUE);  cout << "Cluster without T0, with    tau\t" << coorLS  << endl;
  transform->operator()(coorP,coorLST,kFALSE,kFALSE);  cout << "Pixel   with    T0, without tau\t" << coorLST << endl;
  transform->operator()(coorP,coorLST, kTRUE,kFALSE);  cout << "Pixel   without T0, without tau\t" << coorLST << endl;
  transform->operator()(coorP,coorG, kTRUE,kFALSE);    cout << "Pixel   without T0, without tau\t" << coorG   << endl;
}
//________________________________________________________________________________
void PrintXYZ(Double_t x = 59.3696, Double_t y = 0.871471, Double_t z = 208.707) {
  cout << "Coordinates ============================" << endl;
  StGlobalCoordinate   coorG(x,y,z); cout << "coorG\t" << coorG << endl;
  StTpcLocalCoordinate  coorL; transform->operator()(coorG, coorL, 3, 3); cout << "coorL\t" << coorL << endl; 
  StTpcLocalSectorCoordinate  coorLS; 
  StTpcLocalSectorCoordinate  coorLSF;
  transform->operator()(coorL,coorLS);  cout << "Cluster without T0, with    tau\t" << coorLS << endl;
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
  transform = new StTpcCoordinateTransform(StTpcDb::instance());
  Double_t pad = 10, dpad = 0.5;
  Double_t  time = 100, dtime = 0.5;
  Int_t row = 45;
  StTpcLocalCoordinate   coorG, coorGd;
  for (Int_t sector = 1; sector <= 24; sector++) {
    StTpcPadCoordinate coorP(sector, row, pad, time);             cout << "coorP " << coorP  << endl;
    transform->operator()(coorP,coorG, kTRUE,kFALSE);             cout << "coorG " << coorG  << endl;
    StTpcPadCoordinate coorP(sector, row, pad+dpad, time+dtime);  cout << "coorPd" << coorP  << endl;
    transform->operator()(coorP,coorGd, kTRUE,kFALSE);            cout << "coorGd" << coorGd << endl;
    Double_t dX = (coorGd.position().x() - coorG.position().x())/dpad;
    Double_t dY = (coorGd.position().y() - coorG.position().y())/dpad;
    Double_t dZ = (coorGd.position().z() - coorG.position().z())/dtime;
    cout << "sector = " << sector << "\tdX = " << dX << "\tdY = " << dY << "\tdZ = " << dZ << endl;
  }
}
