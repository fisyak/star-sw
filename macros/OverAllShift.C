/*
  root.exe 'lDb.C(1)' OverAllShift.C
*/
//________________________________________________________________________________
void OverAllShift() {
  StTpcSuperSectorPosition *chair = StTpcSuperSectorPosition::instance();
  Int_t N = chair->getNumRows();
  for (Float_t factor = 1; factor > - 1.5; factor -= 2) {
    StarMagField::Instance()->SetFactor(factor);
  Double_t xyz[2][3] = {0};
  Double_t abg[2][3] = {0};
  for (Int_t s = 1; s <= 24; s++) {
    //    TGeoHMatrix rot = chair->GetMatrix(s-1);
    TGeoHMatrix rot = StTpcDb::instance()->SupS2Tpc(s);
    Double_t xyzS[3] = {0, 123, 0};
    Double_t xyzTpc[3];
    rot.LocalToMaster(xyzS, xyzTpc);
    Int_t we = 0;
    if (s > 12) we = 1;
    rot.Print();
    for (Int_t i = 0; i < 3; i++)     xyz[we][i] += xyzTpc[i];
  }
  for (Int_t i = 0; i < 3; i++) {
    for (Int_t we = 0; we < 2; we++) {
      xyz[we][i] /= 12;
    }
    cout << i << "\t" << xyz[0][i] << "\t" << xyz[1][i] << endl;
  }
  }
}
//________________________________________________________________________________
