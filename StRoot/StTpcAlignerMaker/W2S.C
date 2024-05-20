//________________________________________________________________________________
void AddAX(Int_t P, Double_t *amx, Int_t s, Int_t w, Double_t *array) {
  Int_t I = 0;
  for (Int_t i = 0; i < 2*P; i++) {
    if (i < P) I = P*(s-1) + i;
    else       I = P*(w-1) + i - P;
    array[I] += amx[i];
  }
}
//________________________________________________________________________________
void AddAAT(Int_t P, Double_t *sx, Int_t s, Int_t w, Double_t *array) {
  Int_t I = 0;
  Int_t J = 0;
  for (Int_t i = 0; i < 2*P; i++) {
    if (i < P) I = P*(s-1) + i;
    else       I = P*(w-1) + i - P;
    for (Int_t j = 0; j <= i; j++) {
      if (j < P) J = P*(s-1) + j;
      else       J = P*(w-1) + j - P;
      Int_t ij = TRSymMatrix::IJ(i,j);
      Int_t IJ = TRSymMatrix::IJ(I,J);
      array[IJ] += sx[ij];
    }
  }
}
//________________________________________________________________________________
void TpcAlignerDrawW2S(const Char_t *files = "*.root", const Char_t *OutName = "") {
  TDirIter Dir(files);
  Char_t *file = 0;
  Int_t NFiles = 0;
  TTreeIter iter("TpcW2STree");
  while ((file = (Char_t *) Dir.NextFile())) {
    if (TString(file).Contains("MuDst")) continue;
    if (TString(file).Contains("event")) continue;
    iter.AddFile(file); NFiles++;
  }
  if (! NFiles) {
    cout << "No input files have been found" << endl;
    return;
  }
#if 0
  static const Int_t&       TriggerId                                = iter("TriggerId");
  //	static const UInt_t&      RW2S_fUniqueID                           = iter("RW2S.fUniqueID");
  //	static const UInt_t&      RW2S_fBits                               = iter("RW2S.fBits");
  //	static const TString&     RW2S_fName                               = iter("RW2S.fName");
  //	static const TString&     RW2S_fTitle                              = iter("RW2S.fTitle");
  static const Double_t*&   RW2S_fTranslation                        = iter("RW2S.fTranslation[3]");
  static const Double_t*&   RW2S_fRotationMatrix                     = iter("RW2S.fRotationMatrix[9]");
  static const Double_t*&   RW2S_fScale                              = iter("RW2S.fScale[3]");
  //	static const UInt_t&      HlxParW_fUniqueID                        = iter("HlxParW.fUniqueID");   
  //	static const UInt_t&      HlxParW_fBits                            = iter("HlxParW.fBits");
  static const Int_t&       w                                 = iter("HlxParW.sector"); // HlxParW_sector
  static const Double_t&    HlxParW_Rho                              = iter("HlxParW.Rho");
  static const Double_t&    XW                                = iter("HlxParW.x");  // HlxParW_x 
  static const Double_t&    YW                                = iter("HlxParW.y");  // HlxParW_y 
  static const Double_t&    ZW                                = iter("HlxParW.z");  // HlxParW_z 
  static const Double_t&    nXW                               = iter("HlxParW.nx"); // HlxParW_nx
  static const Double_t&    nYW                               = iter("HlxParW.ny"); // HlxParW_ny
  static const Double_t&    nZW                               = iter("HlxParW.nz"); // HlxParW_nz
  static const Double_t&    HlxParW_xG                               = iter("HlxParW.xG");
  static const Double_t&    HlxParW_yG                               = iter("HlxParW.yG");
  static const Double_t&    HlxParW_zG                               = iter("HlxParW.zG");
  static const Double_t&    HlxParW_nxG                              = iter("HlxParW.nxG");
  static const Double_t&    HlxParW_nyG                              = iter("HlxParW.nyG");
  static const Double_t&    HlxParW_nzG                              = iter("HlxParW.nzG");
  static const Double_t&    HlxParW_dRho                             = iter("HlxParW.dRho");
  static const Double_t*&   HlxParW_fCov                             = iter("HlxParW.fCov[21]");
  static const Double_t&    HlxParW_Chi2                             = iter("HlxParW.Chi2");
  static const Int_t&       HlxParW_Ndf                              = iter("HlxParW.Ndf");
  static const Int_t&       HlxParW_Npoints                          = iter("HlxParW.Npoints");
  static const Int_t&       HlxParW_Nused                            = iter("HlxParW.Nused");
  static const Double_t&    HlxParW_DriftZ                           = iter("HlxParW.DriftZ");
  static const Double_t&    HlxParW_step                             = iter("HlxParW.step");
  //  static const Double_t*&   HlxParW_RefSurficeG                      = iter("HlxParW.RefSurficeG[4]");
  //	static const UInt_t&      HlxParS_fUniqueID                        = iter("HlxParS.fUniqueID");
  //	static const UInt_t&      HlxParS_fBits                            = iter("HlxParS.fBits");
  static const Int_t&       s                                  = iter("HlxParS.sector"); // HlxParS_sector
  static const Double_t&    HlxParS_Rho                              = iter("HlxParS.Rho");
  static const Double_t&    XS                                 = iter("HlxParS.x");  //  HlxParS_x 
  static const Double_t&    YS                                 = iter("HlxParS.y");  //  HlxParS_y 
  static const Double_t&    ZS                                 = iter("HlxParS.z");  //  HlxParS_z 
  static const Double_t&    nXS                                = iter("HlxParS.nx"); //  HlxParS_nx
  static const Double_t&    nYS                                = iter("HlxParS.ny"); //  HlxParS_ny
  static const Double_t&    nZS                                = iter("HlxParS.nz"); //  HlxParS_nz
  static const Double_t&    HlxParS_xG                               = iter("HlxParS.xG");
  static const Double_t&    HlxParS_yG                               = iter("HlxParS.yG");
  static const Double_t&    HlxParS_zG                               = iter("HlxParS.zG");
  static const Double_t&    HlxParS_nxG                              = iter("HlxParS.nxG");
  static const Double_t&    HlxParS_nyG                              = iter("HlxParS.nyG");
  static const Double_t&    HlxParS_nzG                              = iter("HlxParS.nzG");
  static const Double_t&    HlxParS_dRho                             = iter("HlxParS.dRho");
  static const Double_t*&   HlxParS_fCov                             = iter("HlxParS.fCov[21]");
  static const Double_t&    HlxParS_Chi2                             = iter("HlxParS.Chi2");
  static const Int_t&       HlxParS_Ndf                              = iter("HlxParS.Ndf");
  static const Int_t&       HlxParS_Npoints                          = iter("HlxParS.Npoints");
  static const Int_t&       HlxParS_Nused                            = iter("HlxParS.Nused");
  static const Double_t&    HlxParS_DriftZ                           = iter("HlxParS.DriftZ");
  static const Double_t&    HlxParS_step                             = iter("HlxParS.step");
  //  static const Double_t*&   HlxParS_RefSurficeG                      = iter("HlxParS.RefSurficeG[4]");
  //	static const UInt_t&      HlxParW2S_fUniqueID                      = iter("HlxParW2S.fUniqueID");
  //	static const UInt_t&      HlxParW2S_fBits                          = iter("HlxParW2S.fBits");
  static const Int_t&       u                         = iter("HlxParW2S.sector");
  static const Double_t&    HlxParW2S_Rho                            = iter("HlxParW2S.Rho");
  static const Double_t&    XU                               = iter("HlxParW2S.x");   // HlxParW2S_x 
  static const Double_t&    YU                               = iter("HlxParW2S.y");   // HlxParW2S_y 
  static const Double_t&    ZU                               = iter("HlxParW2S.z");   // HlxParW2S_z 
  static const Double_t&    nXU                              = iter("HlxParW2S.nx");  // HlxParW2S_nx
  static const Double_t&    nYU                              = iter("HlxParW2S.ny");  // HlxParW2S_ny
  static const Double_t&    nZU                              = iter("HlxParW2S.nz");  // HlxParW2S_nz
  static const Double_t&    HlxParW2S_xG                             = iter("HlxParW2S.xG");
  static const Double_t&    HlxParW2S_yG                             = iter("HlxParW2S.yG");
  static const Double_t&    HlxParW2S_zG                             = iter("HlxParW2S.zG");
  static const Double_t&    HlxParW2S_nxG                            = iter("HlxParW2S.nxG");
  static const Double_t&    HlxParW2S_nyG                            = iter("HlxParW2S.nyG");
  static const Double_t&    HlxParW2S_nzG                            = iter("HlxParW2S.nzG");
  static const Double_t&    HlxParW2S_dRho                           = iter("HlxParW2S.dRho");
  static const Double_t*&   HlxParW2S_fCov                           = iter("HlxParW2S.fCov[21]");
  static const Double_t&    HlxParW2S_Chi2                           = iter("HlxParW2S.Chi2");
  static const Int_t&       HlxParW2S_Ndf                            = iter("HlxParW2S.Ndf");
  static const Int_t&       HlxParW2S_Npoints                        = iter("HlxParW2S.Npoints");
  static const Int_t&       HlxParW2S_Nused                          = iter("HlxParW2S.Nused");
  static const Double_t&    HlxParW2S_DriftZ                         = iter("HlxParW2S.DriftZ");
  static const Double_t&    HlxParW2S_step                           = iter("HlxParW2S.step");
  //  static const Double_t*&   HlxParW2S_RefSurficeG                    = iter("HlxParW2S.RefSurficeG[4]");
#else
        static const Int_t&       TriggerId                                = iter("TriggerId");
        static const Double_t&    field                                    = iter("field");
        static const Double_t&    driftVel                                 = iter("driftVel");
        static const Double_t&    freq                                     = iter("freq");
// 	static const UInt_t&      RW2S_fUniqueID                           = iter("RW2S.fUniqueID");
// 	static const UInt_t&      RW2S_fBits                               = iter("RW2S.fBits");
// 	static const TString&     RW2S_fName                               = iter("RW2S.fName");
// 	static const TString&     RW2S_fTitle                              = iter("RW2S.fTitle");
	static const Double_t*&   RW2S_fTranslation                        = iter("RW2S.fTranslation[3]");
	static const Double_t*&   RW2S_fRotationMatrix                     = iter("RW2S.fRotationMatrix[9]");
	static const Double_t*&   RW2S_fScale                              = iter("RW2S.fScale[3]");
// 	static const UInt_t&      HlxParW_fUniqueID                        = iter("HlxParW.fUniqueID");
// 	static const UInt_t&      HlxParW_fBits                            = iter("HlxParW.fBits");
	static const Int_t&       w                                        = iter("HlxParW.sector");   /*HlxParW_sector */
	static const Double_t&    HlxParW_Rho                              = iter("HlxParW.Rho");
	static const Double_t&    HlxParW_dRho                             = iter("HlxParW.dRho");
	static const Double_t&    XW                                 = iter("HlxParW.x");   /* HlxParW_x  */
	static const Double_t&    YW                                 = iter("HlxParW.y");   /* HlxParW_y  */
	static const Double_t&    ZW                                 = iter("HlxParW.z");   /* HlxParW_z  */
	static const Double_t&    nXW                                = iter("HlxParW.nx");  /* HlxParW_nx */
	static const Double_t&    nYW                                = iter("HlxParW.ny");  /* HlxParW_ny */
	static const Double_t&    nZW                                = iter("HlxParW.nz");  /* HlxParW_nz */
	static const Double_t&    HlxParW_xG                               = iter("HlxParW.xG");
	static const Double_t&    HlxParW_yG                               = iter("HlxParW.yG");
	static const Double_t&    HlxParW_zG                               = iter("HlxParW.zG");
	static const Double_t&    HlxParW_nxG                              = iter("HlxParW.nxG");
	static const Double_t&    HlxParW_nyG                              = iter("HlxParW.nyG");
	static const Double_t&    HlxParW_nzG                              = iter("HlxParW.nzG");
	static const Double_t&    HlxParW_xTpc                             = iter("HlxParW.xTpc");
	static const Double_t&    HlxParW_yTpc                             = iter("HlxParW.yTpc");
	static const Double_t&    HlxParW_zTpc                             = iter("HlxParW.zTpc");
	static const Double_t&    HlxParW_nxTpc                            = iter("HlxParW.nxTpc");
	static const Double_t&    HlxParW_nyTpc                            = iter("HlxParW.nyTpc");
	static const Double_t&    HlxParW_nzTpc                            = iter("HlxParW.nzTpc");
	static const Double_t&    HlxParW_xHalf                            = iter("HlxParW.xHalf");
	static const Double_t&    HlxParW_yHalf                            = iter("HlxParW.yHalf");
	static const Double_t&    HlxParW_zHalf                            = iter("HlxParW.zHalf");
	static const Double_t&    HlxParW_nxHalf                           = iter("HlxParW.nxHalf");
	static const Double_t&    HlxParW_nyHalf                           = iter("HlxParW.nyHalf");
	static const Double_t&    HlxParW_nzHalf                           = iter("HlxParW.nzHalf");
	static const Double_t&    HlxParW_xPad                             = iter("HlxParW.xPad");
	static const Double_t&    HlxParW_yPad                             = iter("HlxParW.yPad");
	static const Double_t&    HlxParW_zPad                             = iter("HlxParW.zPad");
	static const Double_t&    HlxParW_nxPad                            = iter("HlxParW.nxPad");
	static const Double_t&    HlxParW_nyPad                            = iter("HlxParW.nyPad");
	static const Double_t&    HlxParW_nzPad                            = iter("HlxParW.nzPad");
	static const Double_t&    HlxParW_xPadGG                           = iter("HlxParW.xPadGG");
	static const Double_t&    HlxParW_yPadGG                           = iter("HlxParW.yPadGG");
	static const Double_t&    HlxParW_zPadGG                           = iter("HlxParW.zPadGG");
	static const Double_t&    HlxParW_nxPadGG                          = iter("HlxParW.nxPadGG");
	static const Double_t&    HlxParW_nyPadGG                          = iter("HlxParW.nyPadGG");
	static const Double_t&    HlxParW_nzPadGG                          = iter("HlxParW.nzPadGG");
	static const Double_t*&   HlxParW_fCov                             = iter("HlxParW.fCov[21]");
	static const Double_t&    HlxParW_Chi2                             = iter("HlxParW.Chi2");
	static const Int_t&       HlxParW_Ndf                              = iter("HlxParW.Ndf");
	static const Int_t&       HlxParW_Npoints                          = iter("HlxParW.Npoints");
	static const Int_t&       HlxParW_Nused                            = iter("HlxParW.Nused");
	static const Double_t&    HlxParW_DriftZ                           = iter("HlxParW.DriftZ");
	static const Double_t&    HlxParW_step                             = iter("HlxParW.step");
// 	static const UInt_t&      HlxParS_fUniqueID                        = iter("HlxParS.fUniqueID");
// 	static const UInt_t&      HlxParS_fBits                            = iter("HlxParS.fBits");
	static const Int_t&       s /* HlxParS_sector */                          = iter("HlxParS.sector");
	static const Double_t&    HlxParS_Rho                              = iter("HlxParS.Rho");
	static const Double_t&    HlxParS_dRho                             = iter("HlxParS.dRho");
	static const Double_t&    XS   /* HlxParS_x  */                               = iter("HlxParS.x");
	static const Double_t&    YS   /* HlxParS_y  */                               = iter("HlxParS.y");
	static const Double_t&    ZS   /* HlxParS_z  */                               = iter("HlxParS.z");
	static const Double_t&    nXS  /* HlxParS_nx */                               = iter("HlxParS.nx");
	static const Double_t&    nYS  /* HlxParS_ny */                               = iter("HlxParS.ny");
	static const Double_t&    nZS  /* HlxParS_nz */                               = iter("HlxParS.nz");
	static const Double_t&    HlxParS_xG                               = iter("HlxParS.xG");
	static const Double_t&    HlxParS_yG                               = iter("HlxParS.yG");
	static const Double_t&    HlxParS_zG                               = iter("HlxParS.zG");
	static const Double_t&    HlxParS_nxG                              = iter("HlxParS.nxG");
	static const Double_t&    HlxParS_nyG                              = iter("HlxParS.nyG");
	static const Double_t&    HlxParS_nzG                              = iter("HlxParS.nzG");
	static const Double_t&    HlxParS_xTpc                             = iter("HlxParS.xTpc");
	static const Double_t&    HlxParS_yTpc                             = iter("HlxParS.yTpc");
	static const Double_t&    HlxParS_zTpc                             = iter("HlxParS.zTpc");
	static const Double_t&    HlxParS_nxTpc                            = iter("HlxParS.nxTpc");
	static const Double_t&    HlxParS_nyTpc                            = iter("HlxParS.nyTpc");
	static const Double_t&    HlxParS_nzTpc                            = iter("HlxParS.nzTpc");
	static const Double_t&    HlxParS_xHalf                            = iter("HlxParS.xHalf");
	static const Double_t&    HlxParS_yHalf                            = iter("HlxParS.yHalf");
	static const Double_t&    HlxParS_zHalf                            = iter("HlxParS.zHalf");
	static const Double_t&    HlxParS_nxHalf                           = iter("HlxParS.nxHalf");
	static const Double_t&    HlxParS_nyHalf                           = iter("HlxParS.nyHalf");
	static const Double_t&    HlxParS_nzHalf                           = iter("HlxParS.nzHalf");
	static const Double_t&    HlxParS_xPad                             = iter("HlxParS.xPad");
	static const Double_t&    HlxParS_yPad                             = iter("HlxParS.yPad");
	static const Double_t&    HlxParS_zPad                             = iter("HlxParS.zPad");
	static const Double_t&    HlxParS_nxPad                            = iter("HlxParS.nxPad");
	static const Double_t&    HlxParS_nyPad                            = iter("HlxParS.nyPad");
	static const Double_t&    HlxParS_nzPad                            = iter("HlxParS.nzPad");
	static const Double_t&    HlxParS_xPadGG                           = iter("HlxParS.xPadGG");
	static const Double_t&    HlxParS_yPadGG                           = iter("HlxParS.yPadGG");
	static const Double_t&    HlxParS_zPadGG                           = iter("HlxParS.zPadGG");
	static const Double_t&    HlxParS_nxPadGG                          = iter("HlxParS.nxPadGG");
	static const Double_t&    HlxParS_nyPadGG                          = iter("HlxParS.nyPadGG");
	static const Double_t&    HlxParS_nzPadGG                          = iter("HlxParS.nzPadGG");
	static const Double_t*&   HlxParS_fCov                             = iter("HlxParS.fCov[21]");
	static const Double_t&    HlxParS_Chi2                             = iter("HlxParS.Chi2");
	static const Int_t&       HlxParS_Ndf                              = iter("HlxParS.Ndf");
	static const Int_t&       HlxParS_Npoints                          = iter("HlxParS.Npoints");
	static const Int_t&       HlxParS_Nused                            = iter("HlxParS.Nused");
	static const Double_t&    HlxParS_DriftZ                           = iter("HlxParS.DriftZ");
	static const Double_t&    HlxParS_step                             = iter("HlxParS.step");
// 	static const UInt_t&      HlxParW2S_fUniqueID                      = iter("HlxParW2S.fUniqueID");
// 	static const UInt_t&      HlxParW2S_fBits                          = iter("HlxParW2S.fBits");
	static const Int_t&       u /* HlxParW2S_sector */                        = iter("HlxParW2S.sector");
	static const Double_t&    HlxParW2S_Rho                            = iter("HlxParW2S.Rho");
	static const Double_t&    HlxParW2S_dRho                           = iter("HlxParW2S.dRho");
	static const Double_t&    XU  /* HlxParW2S_x  */                             = iter("HlxParW2S.x");
	static const Double_t&    YU  /* HlxParW2S_y  */                             = iter("HlxParW2S.y");
	static const Double_t&    ZU  /* HlxParW2S_z  */                             = iter("HlxParW2S.z");
	static const Double_t&    nXU /* HlxParW2S_nx */                             = iter("HlxParW2S.nx");
	static const Double_t&    nYU /* HlxParW2S_ny */                             = iter("HlxParW2S.ny");
	static const Double_t&    nZU /* HlxParW2S_nz */                             = iter("HlxParW2S.nz");
	static const Double_t&    HlxParW2S_xG                             = iter("HlxParW2S.xG");
	static const Double_t&    HlxParW2S_yG                             = iter("HlxParW2S.yG");
	static const Double_t&    HlxParW2S_zG                             = iter("HlxParW2S.zG");
	static const Double_t&    HlxParW2S_nxG                            = iter("HlxParW2S.nxG");
	static const Double_t&    HlxParW2S_nyG                            = iter("HlxParW2S.nyG");
	static const Double_t&    HlxParW2S_nzG                            = iter("HlxParW2S.nzG");
	static const Double_t&    HlxParW2S_xTpc                           = iter("HlxParW2S.xTpc");
	static const Double_t&    HlxParW2S_yTpc                           = iter("HlxParW2S.yTpc");
	static const Double_t&    HlxParW2S_zTpc                           = iter("HlxParW2S.zTpc");
	static const Double_t&    HlxParW2S_nxTpc                          = iter("HlxParW2S.nxTpc");
	static const Double_t&    HlxParW2S_nyTpc                          = iter("HlxParW2S.nyTpc");
	static const Double_t&    HlxParW2S_nzTpc                          = iter("HlxParW2S.nzTpc");
	static const Double_t&    HlxParW2S_xHalf                          = iter("HlxParW2S.xHalf");
	static const Double_t&    HlxParW2S_yHalf                          = iter("HlxParW2S.yHalf");
	static const Double_t&    HlxParW2S_zHalf                          = iter("HlxParW2S.zHalf");
	static const Double_t&    HlxParW2S_nxHalf                         = iter("HlxParW2S.nxHalf");
	static const Double_t&    HlxParW2S_nyHalf                         = iter("HlxParW2S.nyHalf");
	static const Double_t&    HlxParW2S_nzHalf                         = iter("HlxParW2S.nzHalf");
	static const Double_t&    HlxParW2S_xPad                           = iter("HlxParW2S.xPad");
	static const Double_t&    HlxParW2S_yPad                           = iter("HlxParW2S.yPad");
	static const Double_t&    HlxParW2S_zPad                           = iter("HlxParW2S.zPad");
	static const Double_t&    HlxParW2S_nxPad                          = iter("HlxParW2S.nxPad");
	static const Double_t&    HlxParW2S_nyPad                          = iter("HlxParW2S.nyPad");
	static const Double_t&    HlxParW2S_nzPad                          = iter("HlxParW2S.nzPad");
	static const Double_t&    HlxParW2S_xPadGG                         = iter("HlxParW2S.xPadGG");
	static const Double_t&    HlxParW2S_yPadGG                         = iter("HlxParW2S.yPadGG");
	static const Double_t&    HlxParW2S_zPadGG                         = iter("HlxParW2S.zPadGG");
	static const Double_t&    HlxParW2S_nxPadGG                        = iter("HlxParW2S.nxPadGG");
	static const Double_t&    HlxParW2S_nyPadGG                        = iter("HlxParW2S.nyPadGG");
	static const Double_t&    HlxParW2S_nzPadGG                        = iter("HlxParW2S.nzPadGG");
	static const Double_t*&   HlxParW2S_fCov                           = iter("HlxParW2S.fCov[21]");
	static const Double_t&    HlxParW2S_Chi2                           = iter("HlxParW2S.Chi2");
	static const Int_t&       HlxParW2S_Ndf                            = iter("HlxParW2S.Ndf");
	static const Int_t&       HlxParW2S_Npoints                        = iter("HlxParW2S.Npoints");
	static const Int_t&       HlxParW2S_Nused                          = iter("HlxParW2S.Nused");
	static const Double_t&    HlxParW2S_DriftZ                         = iter("HlxParW2S.DriftZ");
	static const Double_t&    HlxParW2S_step                           = iter("HlxParW2S.step");
#endif
  enum {kM = 5, kP = 6};
  Double_t tMx6[kM][6] = {
    {1, 0, 0, 0, 0, 0},
    {0, 0, 1, 0, 0, 0},
    {0, 0, 0, 1, 0, 0},
    {0, 0, 0, 0, 1, 0}};
  TRMatrix TMx6(kM, 6, &tMx6[0][0]);
  // Book Histograms
  TString Out(OutName);
  if (Out == "") {
    Out = files; 
    Out.ReplaceAll(".root","W2S");
    Out.ReplaceAll("*","");
    Out += ".root";
    Out = gSystem->BaseName(Out);
  }
  TFile *fOut = new TFile(Out,"recreate");
  TH3F *plots3D[NwsPlots];

#if 1
  for (Int_t i = 0; i < NwsPlots; i++) {
    plots3D[i] = new TH3F(plotNameWS[i].Name, plotNameWS[i].Title, 24, 0.5, 24.5, 
			  plotNameWS[i].nx, plotNameWS[i].xmin, plotNameWS[i].xmax,
			  plotNameWS[i].nz, plotNameWS[i].zmin, plotNameWS[i].zmax);
  }
#else
  for (Int_t i = 0; i < NwsPlots; i++) {
    plots3D[i] = new TH3F(plotNameWS[i].Name, plotNameWS[i].Title, 24, 0.5, 24.5, 
			  plotNameWS[i].nx, 0, 0,
			  plotNameWS[i].nz, 0, 0);
  }
#endif
  TH3F *plots3DTpc[NwsPlotsTpc];
  for (Int_t i = 0; i < NwsPlotsTpc; i++) {
    plots3DTpc[i] = new TH3F(plotNameTpc[i].Name, plotNameTpc[i].Title, 24, 0.5, 24.5, 
			     plotNameTpc[i].nx, plotNameTpc[i].xmin, plotNameTpc[i].xmax,
			     plotNameTpc[i].nz, plotNameTpc[i].zmin, plotNameTpc[i].zmax);
  }
  Int_t NP  = kP*24; // Total no. of parameters per sector
  Int_t NPP = NP*(NP+1)/2; // size of matrix
  Int_t NT  = NP + NPP; // bin0 -> no. of entries; bin_NT+1 = chi2
  TH1D *LSF = new TH1D("LSF","Matrix and right part for Least Squared Fit ",NT+2,0,NT + 2);
  Int_t Ntracks = 0;
  while (iter.Next()) {
    if (u <= 100) continue;
    if (w < 1 || w > 24 ||
	s < 1 || w > 24) continue;
    if (HlxParW2S_Ndf < 15 || HlxParS_Ndf < 15) continue;
    if (HlxParW2S_Chi2/ HlxParW2S_Ndf > 5 || HlxParS_Chi2/HlxParS_Ndf > 5) continue;
    if (ZS < 30 || ZU < 30)               continue; // don't use end of tracks
#if 1
    Double_t RhoU = TMath::Abs(HlxParW2S_Rho);
    Double_t RhoS = TMath::Abs(HlxParS_Rho);
    if (RhoU > 1.5e-3 || RhoS > 1.5e-3) continue; // 1GeV/c cut
    Double_t dRho = RhoU - RhoS;
    //    if (TMath::Abs(dRho) > 6e-3) continue; // 3D distortions
#endif
    TRSymMatrix CU(6,HlxParW2S_fCov);                  PrPP(CU);
    TRSymMatrix CS(6,HlxParS_fCov);                  PrPP(CS);
    TRSymMatrix C(CU);
    C += CS;   PrPP(C);
    for (Int_t i = 0; i < 6; i++) {
      if (i < 3) C(i,i) += 0.1*0.1*0.1;
      else       C(i,i) += 0.001*0.001*0.001;
    }
    TRSymMatrix CMxM(TMx6,TRArray::kAxSxAT,C);        PrPP(CMxM);
    
    TRSymMatrix G(CMxM,TRArray::kInverted);              PrPP(G);
    TVector3 nW(nXW,nYW,nZW);                      PrPP(nW);
    TVector3 rW(XW,YW,ZW);                         PrPP(rW);
    Double_t projS = nXS*XS + nYS*YS;
    TVector3 nS(nXS,nYS,nZS);                      PrPP(nS);
    TVector3 rS(XS,YS,ZS);                         PrPP(rS);
    Double_t projU = nXU*XU + nYU*YU;
    TVector3 nU = TVector3( nXU, nYU, nZU);        PrPP(nU);
    TVector3 rU(XU,YU,ZU);                         PrPP(rU);
    TVector3 dn = nS - nU;                            PrPP(dn);
    TVector3 dr = rS - rU;                            PrPP(dr);
    TRVector mX(kM, dr.X(), dr.Z(), dn.X(), dn.Y(), dn.Z());  PrPP(mX);
#if 0
    //                   dX  dZ nX  nY nZ 
    Int_t iHistV[kM] = { 12, 16, 0,  4, 8}; 
    if (_debug) {
      cout << "w " << w << " => s " << s;
      for (Int_t m = 0; m < kM; m++) {
	cout << "\t";
	cout << mX(m) << " +/- " << TMath::Sqrt(C(m,m));
	Int_t h = iHistV[m];
	if (h >= 0) {
	  cout << "[" << plotNameWS[h].zmin << "," << plotNameWS[h].zmax << "]";
	}
	
      }
      cout << endl;
    }
#endif
    Double_t aMx2P[kM][2*kP];
    StTpcUtil::W2SDer(&rW[0], &nW[0], &rS[0], RW2S_fRotationMatrix, RW2S_fTranslation, aMx2P);
    TRMatrix A(kM, 2*kP, &aMx2P[0][0]); PrPP(A);
    TRVector mGX(G,TRArray::kSxA,mX);  PrPP(mGX);
    TRVector AmX(A,TRArray::kATxB,mGX);  PrPP(AmX);
    TRSymMatrix SX(A,TRArray::kATxSxA,G);   PrPP(SX);
    Double_t *array = LSF->GetArray() + 1;
    Double_t *amX = AmX.GetArray();
    Double_t *sX  = SX.GetArray();
    array[0]++;
    Int_t im = 1;
    Int_t is = im + NP;
    Double_t yTy = G.Product(mX); 
    array[NT+2] += yTy;
    AddAX(kP, amX, s, w, array+im);
    AddAAT(kP, sX, s, w, array+is);
    if (_debug) {
      TRVector SumAmX(NP, array+im); PrPP(SumAmX);
      TRSymMatrix SumSX(NP, array+is); SumSX.Print(kP*(s-1),kP); SumSX.Print(kP*(w-1),kP);
    }
    Double_t dw = w;
    Double_t ds = s;
    TRMatrix V(NwsPlots,3,
mX(0), A(0, 1), ds, //  {"dXdyS",       "dX     versus dX/dyS   [1, 2]  => dyS",        110,-1.500, 1.500,500,   -1.5,  1.5}, // 0
mX(0), A(0, 3), ds, //  {"dXdaS",       "dX     versus dX/daS   [1, 4]  => daS",        110,-300.0, 300.0,500,   -1.5,  1.5}, // 1
mX(0), A(0, 4), ds, //  {"dXdbS",       "dX     versus dX/dbS   [1, 5]  => dbS",        110,-100.0, 500.0,500,   -1.5,  1.5}, // 2
mX(0), A(0, 5), ds, //  {"dXdgS",       "dX     versus dX/dgS   [1, 6]  => dgS",        110,-200.0, 280.0,500,   -1.5,  1.5}, // 3
mX(0), A(0, 6), ds, //  {"dXdxW",       "dX     versus dX/dxW   [1, 7]  => dxW",        110,-1.400, 1.400,500,   -1.5,  1.5}, // 4
mX(0), A(0, 7), dw, //  {"dXdyW",       "dX     versus dX/dyW   [1, 8]  => dyW",        110,-1.600, 1.600,500,   -1.5,  1.5}, // 5
mX(0), A(0, 9), dw, //  {"dXdaW",       "dX     versus dX/daW   [1,10]  => daW",        110,-340.0, 340.0,500,   -1.5,  1.5}, // 6
mX(0), A(0,10), dw, //  {"dXdbW",       "dX     versus dX/dbW   [1,11]  => dbW",        110,-300.0, 240.0,500,   -1.5,  1.5}, // 7
mX(0), A(0,11), dw, //  {"dXdgW",       "dX     versus dX/dgW   [1,12]  => dgW",        110,-280.0, 280.0,500,   -1.5,  1.5}, // 8
mX(1), A(1, 1), ds, //  {"dZdyS",       "dZ     versus dZ/dyS   [2, 2]  => dyS",        110,-1.500, 1.500,500,   -1.0,  1.0}, // 9
mX(1), A(1, 3), ds, //  {"dZdaS",       "dZ     versus dZ/daS   [2, 4]  => daS",        110,-320.0, 4100.0,500,   -1.0,  1.0}, //10
mX(1), A(1, 4), ds, //  {"dZdbS",       "dZ     versus dZ/dbS   [2, 5]  => dbS",        110,-160.0, 160.0,500,   -1.0,  1.0}, //11
mX(1), A(1, 5), ds, //  {"dZdgS",       "dZ     versus dZ/dgS   [2, 6]  => dgS",        110, -40.0,  40.0,500,   -1.0,  1.0}, //12
mX(1), A(1, 6), ds, //  {"dZdxW",       "dZ     versus dZ/dxW   [2, 7]  => dxW",        110,-1.200, 0.800,500,   -1.0,  1.0}, //13
mX(1), A(1, 7), dw, //  {"dZdyW",       "dZ     versus dZ/dyW   [2, 8]  => dyW",        110,-1.200, 1.200,500,   -1.0,  1.0}, //14
mX(1), A(1, 9), dw, //  {"dZdaW",       "dZ     versus dZ/daW   [2,10]  => daW",        110,-420.0, 560.0,500,   -1.0,  1.0}, //15
mX(1), A(1,10), dw, //  {"dZdbW",       "dZ     versus dZ/dbW   [2,11]  => dbW",        110,-300.0, 200.0,500,   -1.0,  1.0}, //16
mX(1), A(1,11), dw, //  {"dZdgW",       "dZ     versus dZ/dgW   [2,12]  => dgW",        110, -40.0,  40.0,500,   -1.0,  1.0}, //17
mX(2), A(2, 4), ds, //  {"dnXdbS",      "dnX    versus dnX/dbS  [3, 5]  => dbS",        110,-0.800, 0.800,500,  -0.03, 0.03}, //18
mX(2), A(2, 5), ds, //  {"dnXdgS",      "dnX    versus dnX/dgS  [3, 6]  => dgS",        110,   -1.,    1.,500,  -0.03, 0.03}, //19
mX(2), A(2, 9), dw, //  {"dnXdaW",      "dnX    versus dnX/daW  [3,10]  => daW",        110,-1.100, 1.100,500,  -0.03, 0.03}, //20
mX(2), A(2,10), dw, //  {"dnXdbW",      "dnX    versus dnX/dbW  [3,11]  => dbW",        110,-1.100, 1.100,500,  -0.03, 0.03}, //21
mX(2), A(2,11), dw, //  {"dnXdgW",      "dnX    versus dnX/dgW  [3,12]  => dgW",        110,   -1.,    1.,500,  -0.03, 0.03}, //22
mX(3), A(3, 3), ds, //  {"dnYdaS",      "dnY    versus dnY/daS  [4, 4]  => daS",        110,-0.800, 0.800,500,  -0.03, 0.03}, //23
mX(3), A(3, 5), ds, //  {"dnYdgS",      "dnY    versus dnY/dgS  [4, 6]  => dgS",        110,-0.800, 0.800,500,  -0.03, 0.03}, //24
mX(3), A(3, 9), dw, //  {"dnYdaW",      "dnY    versus dnY/daW  [4,10]  => daW",        110,-0.700, 0.800,500,  -0.03, 0.03}, //25
mX(3), A(3,10), dw, //  {"dnYdbW",      "dnY    versus dnY/dbW  [4,11]  => dbW",        110,-0.600, 0.500,500,  -0.03, 0.03}, //26
mX(3), A(3,11), dw, //  {"dnYdgW",      "dnY    versus dnY/dgW  [4,12]  => dgW",        110,-0.800, 0.800,500,  -0.03, 0.03}, //27
mX(4), A(4, 3), ds, //  {"dnZdaS",      "dnZ    versus dnZ/daS  [5, 4]  => daS",        110,-1.000, 1.000,500,  -0.01, 0.01}, //28
mX(4), A(4, 4), ds, //  {"dnZdbS",      "dnZ    versus dnZ/dbS  [5, 5]  => dbS",        110,-0.800, 0.800,500,  -0.01, 0.01}, //29
mX(4), A(4, 9), dw, //  {"dnZdaW",      "dnZ    versus dnZ/daW  [5,10]  => daW",        110,-1.000, 1.000,500,  -0.01, 0.01}, //30
mX(4), A(4,10), dw  //  {"dnZdbW",      "dnZ    versus dnZ/dbW  [5,11]  => dbW",        110,-1.000, 1.000,500,  -0.01, 0.01}, //31
 	       );
    for (Int_t i = 0; i < NwsPlots; i++) plots3D[i]->Fill(V(i,2), V(i,1), V(i,0));
    // Add plots for East and West Tpc halves in TPC and Global coordinate systems
    if (Ntracks%10000 == 0) {cout << "read track no\t" << Ntracks << endl;}
    Ntracks++;
#if 1
    ds = 0;
    if (u > 100) {
      if      (s >  12 && w <= 12) ds = 25;
      else if (s <= 12 && w >  12) ds = 26;
    }
    if (! ds) continue;
    dw = ds + 2;
    for (Int_t l = 0; l < 2; l++) {// 0 => Tpc, 1 => Global
      if (l == 0) {
	rS = TVector3(HlxParS_xTpc,HlxParS_yTpc,HlxParS_zTpc); nS = TVector3(HlxParS_nxTpc,HlxParS_nyTpc,HlxParS_nzTpc);
	rU = TVector3(HlxParW2S_xTpc,HlxParW2S_yTpc,HlxParW2S_zTpc); nU = TVector3(HlxParW2S_nxTpc,HlxParW2S_nyTpc,HlxParW2S_nzTpc);
      } else {
	rS = TVector3(HlxParS_xG,HlxParS_yG,HlxParS_zG); nS = TVector3(HlxParS_nxG,HlxParS_nyG,HlxParS_nzG);
	rU = TVector3(HlxParW2S_xG,HlxParW2S_yG,HlxParW2S_zG); nU = TVector3(HlxParW2S_nxG,HlxParW2S_nyG,HlxParW2S_nzG);
      }
      dn = nS - nU;                            PrPP(dn);
      dr = rS - rU;                            PrPP(dr);
      Double_t dT = dr.z()/(driftVel/freq);
      //    TRVector mX(kM, dn.X(), dn.Y(), dn.Z(), dr.X(), dr.Y(), dr.Z());  PrPP(mX);
      TRVector val(7, dr.x(), dr.y(), dr.z(),  dn.x(), dn.y(), dn.z(), dT);
      for (Int_t i = 0; i < 7; i++) {
	plots3DTpc[7*l + i]->Fill(s, rS.z(), val(i));
      }
    }
#endif
  }
  fOut->Write();
}
//________________________________________________________________________________
Double_t DoubleExp(Double_t *x, Double_t *p) {
  Double_t A = p[0];
  Double_t mu = p[1];
  Double_t lambda = p[2];
  Double_t val = A*lambda/2*TMath::Exp(-lambda*(TMath::Abs(x[0] - mu)));
  return val;
}
//________________________________________________________________________________
void TDrawW2S() {
  TMinuitMinimizer::UseStaticMinuit();
  if (! gMinuit) new TMinuit(10);
  gMinuit->SetPrintLevel(-2);
  TF1 *gp = new TF1("gp",DoubleExp,-1,1, 3);
  gp->SetLineColor(2);
  gp->SetParLimits(2,1,1e5);
  TF1 *gpp = new TF1("gpp","gaus(0)+pol2(3)");
  gp->SetLineColor(4);
  Int_t nx = 24;
  Int_t ny = NwsFPlots;
  Int_t scaleX = 800/nx;
  Int_t scaleY = 600/ny;
  //  Int_t scale  = TMath::Min(scaleX,scaleY);
  TCanvas *c1 = new TCanvas("TpcWS","Tpc Sector to Sector Alignment" ,10,10,10+scaleX*nx,10+scaleY*ny);
  cout << "nx/ny = " << nx << "/" << ny << endl;
  c1->Divide(ny,nx);
  TCanvas *c2 = new TCanvas("c2","c2");
  TString line("");
  TString lTitle("");
  TString lineC("");
  ofstream out;
  ofstream outC;
  TString Out("Results");
  Out += gSystem->BaseName(gDirectory->GetName());
  Out.ReplaceAll(".root","");
  //  Out += t.AsString();
  Out.ReplaceAll(" ","");
  if (gSystem->AccessPathName(Out)) out.open(Out, ios::out); //"Results.list",ios::out | ios::app);
  else                              out.open(Out, ios::app);
  Out += ".h";
  if (gSystem->AccessPathName(Out)) outC.open(Out, ios::out); //"Results.list",ios::out | ios::app);
  else                              outC.open(Out, ios::app);
  struct Val_t {
    Double_t val;
    Double_t valError;
    Int_t    iFlag;
  };
  Val_t ValG[3][7]; memset (ValG, 0, sizeof(ValG)); // 0 => West, 1 => East, 2 => All
  TH1D *LSF = (TH1D *) gDirectory->Get("LSF");
  Double_t *array = LSF->GetArray() + 1;
  Int_t NEntries = array[0];
  if (NEntries  < 1000) return;
  enum {kM = 6, kP = 6};
  Int_t NP  = kP*24; // Total no. of parameters per sector
  Int_t NPP = NP*(NP+1)/2; // size of matrix
  Int_t NT  = NP + NPP; // bin0 -> no. of entries; bin_NT+2 = chi2
  Double_t yTy = array[NT+2];
  Int_t im = 1;
  Int_t is = im + NP;
  TRVector AmX(NP,array+im);  PrPP(AmX);
  TRSymMatrix S(NP,array+is); PrPP(S);
  TRSymMatrix Cor(S, TRArray::kSCor); PrPP(Cor);
  TRSymMatrix SInv(S);
  Int_t iFail = TRSymMatrix::TrchLU(S.GetArray(),SInv.GetArray(),NP);
  if (iFail) {
    cout << "TRSymMatrix Invertion failed" << endl;
    SInv = TRSymMatrix(S,TRArray::kInvertedPosDef);  PrPP(SInv);
  } else {
    SInv = TRSymMatrix(S,TRArray::kInverted);  PrPP(SInv);
  }
  TRVector  X(SInv,TRArray::kSxA,AmX);     PrPP(X);
  Double_t chi2 = yTy;
  chi2 -= AmX*X; PrPP1(chi2);
  if (_debug > 2) {
    TRSymMatrix P(NP);
    for (Int_t i = 0; i < NP; i++)
      for (Int_t j = 0; j < NP; j++) {
	P(i,j) = 0;
	for (Int_t k = 0; k < NP; k++)
	  P(i,j) += SInv(i,k)*S(k,j);
      }
    PrPP(P);
  }
  //#define __FREEZEG__
#ifdef __FREEZEG__
  TRMatrix FreezeG(NP,NP);
  for (Int_t i = 0; i < NP; i++) {
    if (i%6 < 3) FreezeG(i,i) = 1;
  }
  PrPP(FreezeG);
  TRVector AmX5(FreezeG, TRArray::kAxB, AmX); PrPP(AmX5);
  TRSymMatrix S5(FreezeG, TRArray::kATxSxA, S); PrPP(S5);
  TRSymMatrix S5Inv(S5, TRArray::kInverted);  PrPP(S5Inv);
  TRVector  X5(S5Inv,TRArray::kSxA,AmX5);     PrPP(X5);
  Double_t chi2x5 = yTy;
  chi2x5 -= AmX5*X5; PrPP1(chi2x5);
  chi2 = chi2x5;
  X = X5;
  SInv = S5Inv;
#endif
  Int_t head = 0;
  for (Int_t i = 1; i <= nx; i++) {
    Int_t sector = i;
    Int_t iwe = 0;
    if (sector > 12) iwe = 1;
    if (! head) {
      out  <<  "_____________________________________________________________________________________________________________"  << endl;
      out  <<  "| x mkm           | y mkm           | z mkm           |alpha mrad     |beta mrad      |gamma mrad     |Comment" << endl;
      cout <<  "_____________________________________________________________________________________________________________"  << endl;
      cout <<  "| x mkm           | y mkm           | z mkm           |alpha mrad     |beta mrad      |gamma mrad     |Comment" << endl;
#if 0
      outC << "struct data_t {" << endl;
      outC << "\tInt_t sector;" << endl;
      outC << "\tDouble_t x, Dx, y, Dy, z, Dz, alpha, Dalpha, beta, Dbeta, gamma, Dgamma;" << endl;
      outC << "\tconst Char_t *Comment;" << endl;
      outC << "};" << endl;
      outC << "data_t Data[] = {" << endl;
#else
      outC << "  {20190101,    1, \"" << gSystem->WorkingDirectory() << "\", //" << endl;
      outC << "{" << endl;
#endif
    }
    head++;
    out  << "__________________________________________________________________________________________________ " << sector << endl;
    cout << "__________________________________________________________________________________________________ " << sector << endl;
    struct Val_t {
      Double_t val;
      Double_t valError;
      Int_t    iFlag;
    };
    Val_t ValA[7]; memset (ValA, 0, sizeof(ValA));
#define __AVERAGE_WS__
#if 1
    if (LSF) {
      line = "";
      for (Int_t m = 0; m < 6; m++) {
	Int_t l = 6*(i-1) + m;
	if (SInv(l,l) > 0) {
	  Double_t scale = 1e4;   // => mkm
	  if (m > 2) scale = 1e3; // => mrad
	  ValA[m].val =  scale*X(l);
	  ValA[m].valError = scale*TMath::Sqrt(SInv(l,l)); // scale by a factor of 5
#ifndef __AVERAGE_WS__
	  ValA[m].iFlag = 1; // 0, No LSF1;
#else
	  ValA[m].iFlag =  0; //  No LSF1;
#endif
	} else {
	  ValA[m].val = ValA[m].valError = 0; ValA[m].iFlag = 0;
	}
	if (m < 3) 
	  line  += Form("|%8.2f+-%6.2f ", TMath::Max(-9999.99,TMath::Min( 9999.99,ValA[m].val)),TMath::Min(999.99,ValA[m].valError)); 
	else
	  line  += Form("|%7.2f+-%5.2f ", ValA[m].val,TMath::Min(99.99,ValA[m].valError)); 
	if ((m <  3 && TMath::Abs(ValA[m].valError) > 299.9) ||
	    (m >= 3 && TMath::Abs(ValA[m].valError) >  29.9)) {
	  ValA[m].val = ValA[m].valError = 0; ValA[m].iFlag = 0;
	}
      }
    }
    cout << line << endl;
    out << line << endl;
#endif
    for (Int_t j = 0; j < NwsPlots; j++) {
      TH3 *h3 = (TH3 *) gDirectory->Get(plotNameWS[j].Name);
      if (! h3) continue;
      Int_t ij = j + 1 + ny*(i-1);
      TH1 *fit = 0;
      h3->GetXaxis()->SetRange(sector,sector);
      TH1 *sp = h3->Project3D(Form("z_%02i",sector));
      if (sp->GetEntries() < 100) continue;
      //
      c2->cd();
      TF1 *g = 0;
      Double_t mean = sp->GetMean();
      Double_t RMS  = sp->GetRMS();
      sp->Fit("gaus","qemr","",mean-2*RMS, mean+2*RMS);
      TF1 *gaus = sp->GetFunction("gaus");
      if (gaus) {
	Double_t pars[6] = {0};
	gaus->GetParameters(pars);
	gpp->SetParameters(pars);
	sp->Fit(gpp,"qem+r","",mean-2*RMS, mean+2*RMS);
	g = gpp;
      }
#if 0
      Double_t params[3] = {sp->GetEntries(), mean, TMath::Sqrt(2.)/RMS};
      gp->SetParameters(params);
      sp->Fit(gp,"qemi+r","",mean-2*RMS, mean+2*RMS);
      if (g && gp->GetChisquare() < g->GetChisquare()) {
      } else {
	g = gp;
      }
#endif
      c2->Update();
      Double_t Mu  = 0;
      Double_t dMu = 0; 
      if (g) {
	Mu  = g->GetParameter(1);
	dMu = g->GetParError(1);
      }
      TH2 *h = (TH2 *) h3->Project3D("zy");
      h->SetName(Form("%s_%i",h->GetName(),sector));
      h->FitSlicesY(0,0,-1,10,"qeg3s");
      //      SlicesYFit(h,0,0,10,"qnig3");
      fit = (TH1 *) gDirectory->Get(Form("%s_1",h->GetName()));
      //       TH1 *sig = (TH1 *) gDirectory->Get(Form("%s_2",h->GetName()));
      //       TH1 *gra = (TH1 *) gDirectory->Get(Form("%s_3",h->GetName()));
      Double_t slope = 0;
      Double_t dslope = 0;
      TLegend *leg = new TLegend(0.1,0.2,0.6,0.3,"");
      lTitle = "";
      leg->SetTextSize(0.025);
      c1->cd(ij)->SetLogz(1);
      if (fit && fit->GetEntries() > 2) {
	fit->SetTitle(h->GetTitle());
	fit->SetMarkerStyle(20);
	fit->SetMarkerColor(1);
	fit->SetMaximum(0.2);
	fit->SetMinimum(-.2);
	fit->SetStats(1);
	fit->Fit("pol1","qe");
	TF1 *pol1 = fit->GetFunction("pol1");
	if (! pol1 ) goto endhLoop;
	Double_t prob = pol1->GetProb();
	if (prob >= 0) {
#if 0
#if 0
	  Mu     = pol1->GetParameter(0);
	  dMu    = pol1->GetParError(0);
#else
	  Double_t xm = fit->GetMean();
	  Mu     = pol1->Eval(xm);
	  dMu    = TMath::Sqrt(pol1->GetParError(0)*pol1->GetParError(0) + (xm*pol1->GetParError(1))*(xm*pol1->GetParError(1)));
#endif
#endif
	  slope  = pol1->GetParameter(1);
	  dslope = pol1->GetParError(1);
	} else {
	  slope = dslope = 0;
#if 1
	  Mu = dMu = 0;
#endif
	}
	Val_t Vals[6]; memset (Vals, 0, sizeof(Vals));
	static const Char_t *dxv[3] = {"dX", "dY","dZ"};
	TString Name(h->GetName());
	TString Title(h->GetTitle());
	for (Int_t m = 0; m < 3; m++) {
	  if (Name.BeginsWith(dxv[m]) && dMu > 0 && dMu < 999.99e-4) {
	    Vals[m].val =     -1e4*Mu;
	    Vals[m].valError = 1e4*dMu;
	    Vals[m].iFlag = 1;
	    lTitle += Form(" %s = %8.2f+-%6.2f (#mum)", dxv[m],Vals[m].val,TMath::Min(999.99,Vals[m].valError)); 
	  }
	}	  
	Int_t index = Title.Index("=>");
	TString tag("");
	if (index >= 0) {
	  index = index+2;
	  static TString separator("[^ ;,]+");
	  TString t(Title.Data()+index);
	  TObjArray *a = t.Tokenize(separator);
	  tag = ((TObjString *) a->At(0))->GetString();
	  delete a;
	}
	static const Char_t *lvar[6] = {"dx","dy","dz","#alpha","#beta","#gamma"};
	static const Char_t *t[6] = {"x","y","z","a","b","g"};
	for (Int_t m = 0; m < 6; m++) {
	  if (dslope <= 0) continue;
	  if (m < 3 && dslope >= 999.99e-4) continue;
	  if (m >=3 && dslope >=  99.99e-3) continue;
	  if (tag.Contains(t[m])) {
	    if (m < 3) {
	      Vals[m].val =      1e4*slope;
	      Vals[m].valError = 1e4*dslope;
	      Vals[m].iFlag = 1;
	      lTitle += Form(" %s = %8.2f+-%6.2f (#mum)", lvar[m],Vals[m].val,TMath::Min(999.99,Vals[m].valError)); 
	    } else {
	      Vals[m].val =      1e3*slope;
	      Vals[m].valError = 1e3*dslope;
	      Vals[m].iFlag = 1;
	      lTitle += Form(" %s = %7.2f+-%5.2f (mrad)", lvar[m],Vals[m].val,TMath::Min(99.99,Vals[m].valError)); 
	    }
	  }
	}
	lTitle += Form(" prob = %5.3f",prob);
	leg->AddEntry(pol1,lTitle);
	line = "";
	lineC = Form("\t{%2i",sector);
	for (Int_t m = 0; m < 6; m++) {
	  if (! Vals[m].iFlag) {
	    if (m > 2) 	      line  += "|               ";
	    else              line  += "|                 ";
	    lineC += ",      0,-9.99";
	  } else {
	    if (m > 2) {
	      line  += Form("|%7.2f+-%5.2f ", Vals[m].val,TMath::Min(99.99,Vals[m].valError)); 
	      lineC += Form(",%7.2f,%5.2f", Vals[m].val,TMath::Min(99.99,Vals[m].valError)); 
	    } else {
	      line  += Form("|%8.2f+-%6.2f ", Vals[m].val,TMath::Min(999.99,Vals[m].valError)); 
	      lineC += Form(",%8.2f,%6.2f", Vals[m].val,TMath::Min(999.99,Vals[m].valError)); 
	    }
#ifdef  __AVERAGE_WS__
	    if (ValA[m].iFlag) {
	      Double_t w0 = 1./(Vals[m].valError*Vals[m].valError);
	      Double_t w1 = 1./(ValA[m].valError*ValA[m].valError);
	      ValA[m].val = (w0*Vals[m].val + w1*ValA[m].val)/(w0 + w1);
	      ValA[m].valError = 1./TMath::Sqrt(w0 + w1);
	      ValA[m].iFlag++;
	    } else {
	      ValA[m] = Vals[m];
	    }
#endif
	  }
	}
	line += "|"; line += fit->GetName(); line += "/"; line += h->GetTitle(); 
	lineC += ",\""; lineC += fit->GetName(); lineC += "\"},";
	cout << line << endl;
	out << line << endl;
      }
    endhLoop:
      if (h) h->Draw("colz");
      if (fit) {
	fit->Draw("same"); 
	TF1 *pol1 = fit->GetFunction("pol1"); 
	if (pol1) {pol1->SetLineColor(2); pol1->Draw("same");}
      }
      leg->Draw();
    }
    out  << "__________________________________________________________________________________________________ " << sector << endl;
    cout << "__________________________________________________________________________________________________ " << sector << endl;
    line = ""; 
    lineC = Form("\t{%2i",sector);
    for (Int_t m = 0; m < 6; m++) {
      if (! ValA[m].iFlag
#ifdef   FREEZE_BETA  
	  || (m == 4) 
#endif
#ifdef   FREEZE_ALPHA_BETA  
	  || (m == 3 || m == 4) 
#endif
	  ) {
	if (m > 2) 
	  line  += "|                ";
	else 
	  line  += "|                 ";
	lineC += ",      0,-9.99";
      } else {
	if (m > 2) {
	  line  += Form("|%7.2f+-%5.2f ", ValA[m].val,TMath::Min(99.99,ValA[m].valError)); 
	  lineC += Form(",%7.2f,%5.2f", ValA[m].val,TMath::Min(99.99,ValA[m].valError)); 
	} else {
	  line  += Form("|%8.2f+-%6.2f ", TMath::Max(-9999.99,TMath::Min( 9999.99,ValA[m].val)),TMath::Min(999.99,ValA[m].valError)); 
	  lineC += Form(",%8.2f,%6.2f", ValA[m].val,TMath::Min(999.99,ValA[m].valError)); 
	}
	Double_t w0 = 1./(ValA[m].valError*ValA[m].valError);
	Double_t w1 = 0;
	if (ValG[2][m].valError > 0) 
	  w1 = 1./(ValG[2][m].valError*ValG[2][m].valError);
	ValG[2][m].val = (w0*ValA[m].val + w1*ValG[2][m].val)/(w0 + w1);
	ValG[2][m].valError = 1./TMath::Sqrt(w0 + w1);
	ValG[2][m].iFlag++;
	if (ValG[iwe][m].valError > 0) 
	  w1 = 1./(ValG[iwe][m].valError*ValG[iwe][m].valError);
	ValG[iwe][m].val = (w0*ValA[m].val + w1*ValG[iwe][m].val)/(w0 + w1);
	ValG[iwe][m].valError = 1./TMath::Sqrt(w0 + w1);
	ValG[iwe][m].iFlag++;
      }
    }
#ifdef __AVERAGE_WS__
    lineC += ",\"Average ";
#else
    lineC += ",\"LSF ";
#endif
#ifdef   FREEZE_ALPHA_BETA  
    lineC += " Fixed alpha beta";
#endif
#ifdef   FREEZE_BETA  
    lineC += ",\"LSF Fixed beta";
#endif
    lineC += "\"},";
    cout << line << endl;
    out << line << endl;
    outC << lineC << endl;
  }
  outC << "    }" << endl;
  outC << "  }," << endl;
  outC.close();
  //  out << "};" << endl << "const  Int_t NP = sizeof(Passes)/sizeof(SurveyPass_t);" << endl << "#endif" << endl;
  lineC = "";
  for (Int_t jwe = 0; jwe < 3; jwe++) {
    line = ""; 
    for (Int_t m = 0; m < 6; m++) {
      if (! ValG[jwe][m].iFlag 
#ifdef   FREEZE_BETA  
	  || (m == 4) 
#endif
#ifdef   FREEZE_ALPHA_BETA  
	  || (m == 3 || m == 4) 
#endif
	  ) {
	line  += "|                 ";
	lineC += ",      0,-9.99";
      } else {
	if (m > 2) {
	  line  += Form("|%7.2f+-%5.2f ", ValG[jwe][m].val,TMath::Min(99.99,ValG[jwe][m].valError)); 
	  lineC += Form(",%7.2f,%5.2f", ValG[jwe][m].val,TMath::Min(99.99,ValG[jwe][m].valError)); 
	} else {
	  line  += Form("|%8.2f+-%6.2f ", TMath::Max(-9999.99,TMath::Min( 9999.99,ValG[jwe][m].val)),TMath::Min(999.99,ValG[jwe][m].valError)); 
	  lineC += Form(",%8.2f,%6.2f", ValG[jwe][m].val,TMath::Min(999.99,ValG[jwe][m].valError)); 
	}
      }
    }
    if      (jwe == 0) line += " West";
    else if (jwe == 1) line += " East";
    else               line += " All";
    cout << line << endl;
    out << line << endl;
  }
  out.close();
}
