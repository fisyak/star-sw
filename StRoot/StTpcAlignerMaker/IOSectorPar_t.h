#ifndef __IOSector_Par_t_h__
#define __IOSector_Par_t_h__
struct data_t {
  Int_t sector;
  Double_t x, Dx, y, Dy, z, Dz, alpha, Dalpha, beta, Dbeta, gamma, Dgamma;
  const Char_t *Comment;
  void Print() {
    cout << Form("%2i %8.2f %5.2f %8.2f %5.2f %8.2f %5.2f",sector, x, Dx, y, Dy, z, Dz)
	 << Form(" %8.2f %5.2f %8.2f %5.2f %8.2f %5.2f %s", alpha, Dalpha, beta, Dbeta, gamma, Dgamma, Comment) << endl;
  }
};
struct SurveyPass_t {
  Int_t date, time;
  const Char_t *PassName;
  data_t Data[24];
  void Print() {
    cout << Form("%8i %6i %s",date,time,PassName) << endl;
    for (Int_t i = 0; i < 24; i++) {
      Data[i].Print();
    }
  }
};
#endif /* __IOSector_Par_t_h__ */
