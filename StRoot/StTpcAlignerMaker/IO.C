//________________________________________________________________________________
void TpcAlignerDrawIO(const Char_t *files = "../*.root", const Char_t *OutName = "", Bool_t laser = kFALSE) {
  TDirIter Dir(files);
  Char_t *file = 0;
  Int_t NFiles = 0;
  TTreeIter iter("TpcInOutTree");
  while ((file = (Char_t *) Dir.NextFile())) {
    if (TString(file).Contains("MuDst")) continue;
    if (TString(file).Contains("event")) continue;
    iter.AddFile(file); NFiles++;
  }
  if (! NFiles) {
    cout << "No input files have been found" << endl;
    return;
  }
	//	static const Int_t&       TriggerId                                = iter("TriggerId");
	static const Double_t&    field                                    = iter("field");
	static const Double_t&    driftVel                                 = iter("driftVel");
	static const Double_t&    freq                                     = iter("freq");
	static const Double_t&    charge                                   = iter("charge");
	static const Int_t&       NoFitPoints                              = iter("NoFitPoints");
	static const Double_t&    pX                                       = iter("pX");
	static const Double_t&    pY                                       = iter("pY");
	static const Double_t&    pZ                                       = iter("pZ");
	static const Int_t&       iPV                                      = iter("iPV");
	static const Double_t&    xPV                                      = iter("xPV");
	static const Double_t&    yPV                                      = iter("yPV");
	static const Double_t&    zPV                                      = iter("zPV");
	static const Int_t&       In_sector                                = iter("In.sector");
	static const Double_t&    In_Rho                                   = iter("In.Rho");
	static const Double_t&    In_dRho                                  = iter("In.dRho");
	static const Double_t&    In_x                                     = iter("In.x");
	static const Double_t&    In_y                                     = iter("In.y");
	static const Double_t&    In_z                                     = iter("In.z");
	static const Double_t&    In_nx                                    = iter("In.nx");
	static const Double_t&    In_ny                                    = iter("In.ny");
	static const Double_t&    In_nz                                    = iter("In.nz");
	static const Double_t&    In_xG                                    = iter("In.xG");
	static const Double_t&    In_yG                                    = iter("In.yG");
	static const Double_t&    In_zG                                    = iter("In.zG");
	static const Double_t&    In_nxG                                   = iter("In.nxG");
	static const Double_t&    In_nyG                                   = iter("In.nyG");
	static const Double_t&    In_nzG                                   = iter("In.nzG");
	static const Double_t&    In_xTpc                                  = iter("In.xTpc");
	static const Double_t&    In_yTpc                                  = iter("In.yTpc");
	static const Double_t&    In_zTpc                                  = iter("In.zTpc");
	static const Double_t&    In_nxTpc                                 = iter("In.nxTpc");
	static const Double_t&    In_nyTpc                                 = iter("In.nyTpc");
	static const Double_t&    In_nzTpc                                 = iter("In.nzTpc");
	static const Double_t&    In_xHalf                                 = iter("In.xHalf");
	static const Double_t&    In_yHalf                                 = iter("In.yHalf");
	static const Double_t&    In_zHalf                                 = iter("In.zHalf");
	static const Double_t&    In_nxHalf                                = iter("In.nxHalf");
	static const Double_t&    In_nyHalf                                = iter("In.nyHalf");
	static const Double_t&    In_nzHalf                                = iter("In.nzHalf");
	static const Double_t&    In_xPad                                  = iter("In.xPad");
	static const Double_t&    In_yPad                                  = iter("In.yPad");
	static const Double_t&    In_zPad                                  = iter("In.zPad");
	static const Double_t&    In_nxPad                                 = iter("In.nxPad");
	static const Double_t&    In_nyPad                                 = iter("In.nyPad");
	static const Double_t&    In_nzPad                                 = iter("In.nzPad");
	static const Double_t&    In_xPadGG                                = iter("In.xPadGG");
	static const Double_t&    In_yPadGG                                = iter("In.yPadGG");
	static const Double_t&    In_zPadGG                                = iter("In.zPadGG");
	static const Double_t&    In_nxPadGG                               = iter("In.nxPadGG");
	static const Double_t&    In_nyPadGG                               = iter("In.nyPadGG");
	static const Double_t&    In_nzPadGG                               = iter("In.nzPadGG");
	static const Double_t*&   In_fCov                                  = iter("In.fCov[21]");
	static const Double_t&    In_Chi2                                  = iter("In.Chi2");
	static const Int_t&       In_Ndf                                   = iter("In.Ndf");
	static const Int_t&       In_Npoints                               = iter("In.Npoints");
	static const Int_t&       In_Nused                                 = iter("In.Nused");
	static const Double_t&    In_DriftZ                                = iter("In.DriftZ");
	static const Double_t&    In_step                                  = iter("In.step");
	static const Int_t&       Out_sector                               = iter("Out.sector");
	static const Double_t&    Out_Rho                                  = iter("Out.Rho");
	static const Double_t&    Out_dRho                                 = iter("Out.dRho");
	static const Double_t&    Out_x                                    = iter("Out.x");
	static const Double_t&    Out_y                                    = iter("Out.y");
	static const Double_t&    Out_z                                    = iter("Out.z");
	static const Double_t&    Out_nx                                   = iter("Out.nx");
	static const Double_t&    Out_ny                                   = iter("Out.ny");
	static const Double_t&    Out_nz                                   = iter("Out.nz");
	static const Double_t&    Out_xG                                   = iter("Out.xG");
	static const Double_t&    Out_yG                                   = iter("Out.yG");
	static const Double_t&    Out_zG                                   = iter("Out.zG");
	static const Double_t&    Out_nxG                                  = iter("Out.nxG");
	static const Double_t&    Out_nyG                                  = iter("Out.nyG");
	static const Double_t&    Out_nzG                                  = iter("Out.nzG");
	static const Double_t&    Out_xTpc                                 = iter("Out.xTpc");
	static const Double_t&    Out_yTpc                                 = iter("Out.yTpc");
	static const Double_t&    Out_zTpc                                 = iter("Out.zTpc");
	static const Double_t&    Out_nxTpc                                = iter("Out.nxTpc");
	static const Double_t&    Out_nyTpc                                = iter("Out.nyTpc");
	static const Double_t&    Out_nzTpc                                = iter("Out.nzTpc");
	static const Double_t&    Out_xHalf                                = iter("Out.xHalf");
	static const Double_t&    Out_yHalf                                = iter("Out.yHalf");
	static const Double_t&    Out_zHalf                                = iter("Out.zHalf");
	static const Double_t&    Out_nxHalf                               = iter("Out.nxHalf");
	static const Double_t&    Out_nyHalf                               = iter("Out.nyHalf");
	static const Double_t&    Out_nzHalf                               = iter("Out.nzHalf");
	static const Double_t&    Out_xPad                                 = iter("Out.xPad");
	static const Double_t&    Out_yPad                                 = iter("Out.yPad");
	static const Double_t&    Out_zPad                                 = iter("Out.zPad");
	static const Double_t&    Out_nxPad                                = iter("Out.nxPad");
	static const Double_t&    Out_nyPad                                = iter("Out.nyPad");
	static const Double_t&    Out_nzPad                                = iter("Out.nzPad");
	static const Double_t&    Out_xPadGG                               = iter("Out.xPadGG");
	static const Double_t&    Out_yPadGG                               = iter("Out.yPadGG");
	static const Double_t&    Out_zPadGG                               = iter("Out.zPadGG");
	static const Double_t&    Out_nxPadGG                              = iter("Out.nxPadGG");
	static const Double_t&    Out_nyPadGG                              = iter("Out.nyPadGG");
	static const Double_t&    Out_nzPadGG                              = iter("Out.nzPadGG");
	static const Double_t*&   Out_fCov                                 = iter("Out.fCov[21]");
	static const Double_t&    Out_Chi2                                 = iter("Out.Chi2");
	static const Int_t&       Out_Ndf                                  = iter("Out.Ndf");
	static const Int_t&       Out_Npoints                              = iter("Out.Npoints");
	static const Int_t&       Out_Nused                                = iter("Out.Nused");
	static const Double_t&    Out_DriftZ                               = iter("Out.DriftZ");
	static const Double_t&    Out_step                                 = iter("Out.step");
  // Book Histograms
  TString Out(OutName);
  if (Out == "") {
    Out = gSystem->BaseName(files); 
    Out.ReplaceAll("st_","");
    Out.ReplaceAll(".root","");
    Out.ReplaceAll("*","");
    //  Out += ".2GeVC";
    //  if (TMath::Abs(field) > 1)   Out += ".1GeVC";
    if (laser) Out += ".Laser";
    //  Out += ".Cut";
    //  Out += ".Errors";
    Out += "_IO.root";
  }
  TFile *fOut = new TFile(Out,"recreate");
  TH3F *plots3D[NFPlots];
  for (Int_t i = 0; i < NFPlots; i++) {
#if 1
    plots3D[i] = new TH3F(plotNameD[i].Name, plotNameD[i].Title, 24, 0.5, 24.5, 
			  plotNameD[i].nx, plotNameD[i].xmin, plotNameD[i].xmax,
			  plotNameD[i].nz, plotNameD[i].zmin, plotNameD[i].zmax);
#else /* Pad */
    plots3D[i] = new TH3F(plotNameD[i].Name, plotNameD[i].Title, 24, 0.0, 0.0,
			  plotNameD[i].nx, 0.0, 0.0, 
			  plotNameD[i].nz, 0.0, 0.0);
#endif
  }
  TH1D *dv = new TH1D("DV","pc Drift Velocisies", 100, 5, 6);
  TH1D *LSF[24];
  //  Increase hitogram by 2 bins in order to account underfloaw and overflow 
  for (Int_t sec = 1; sec <= 24; sec++) LSF[sec-1] = new TH1D(Form("LSF_%02i",sec),Form("Matrix and right part for Least Squared Fit for sector = %02i",sec),30,0,30.);
  enum {kM = 4, kP = 4, kPP = kP*(kP+1)/2};
  Double_t tMx6[kM][6] = {
    {1, 0, 0, 0, 0, 0},
    {0, 0, 1, 0, 0, 0},
    {0, 0, 0, 1, 0, 0},
    {0, 0, 0, 0, 1, 0}};
  TRMatrix TMx6(kM, 6, &tMx6[0][0]);
  Int_t Ntracks = 0;
  while (iter.Next()) {
#if 0
    if     (laser) {if (TriggerId <   9200 || TriggerId >   9201) continue; // not Laser
    } else         {if (TriggerId < 310811 || TriggerId > 310813) continue; // not Cosmic
    }
#endif
    //    if (TMath::Abs(field) < 1.0) continue;
    if (In_sector != Out_sector) continue;
    
    if (In_Chi2 > 5.0 || Out_Chi2 > 5.0) continue;
    TVector3 pxyz(pX,pY,pZ);
    //    if (pxyz.Mag() < 2.0) continue;
    if (TMath::Abs(field) > 1 && pxyz.Mag() < 1.0) continue;
    if (laser && pxyz.Mag() < 100.0) continue;
    //    if (In_Ndf < 15 || Out_Ndf < 15) continue;
    Int_t sector = In_sector;
    if (! sector) continue;
    StBeamDirection part = StTpcDb::TpcPart(sector);
    const TGeoHMatrix &Wheel = StTpcDb::instance()->TpcWheel(part);
    const Double_t *rotWheel = Wheel.GetRotationMatrix();
    const Double_t *traWheel = Wheel.GetTranslation();
    //                          alpha        beta         gamma        x            y            z
    Double_t abgxyz_Wheel[6] = {rotWheel[7], rotWheel[2], rotWheel[3], traWheel[0], traWheel[1], traWheel[2]};
    const TGeoHMatrix &O = StTpcDb::instance()->SubSOuter2Sup12S(sector);
    const Double_t *rotO = O.GetRotationMatrix();
    const Double_t *traO = O.GetTranslation();
    //                      alpha    beta     gamma    x         y         z
    Double_t abgxyz_O[6] = {rotO[7], rotO[2], rotO[3], traO[0], traO[1], traO[2]};
    TVector3 pxyzIn(In_nx,In_ny,In_nz);  PrPP(pxyzIn);
    TVector3 rI(In_x,In_y,In_z);         PrPP(rI);
    TVector3 pxyzOut(Out_nx,Out_ny,Out_nz);   PrPP(pxyzOut);
    TVector3 rO(Out_x,Out_y,Out_z); PrPP(rO);
    Double_t dev = (TMath::Abs(In_Rho)-TMath::Abs(Out_Rho));
    //    if (TMath::Abs(dev) > 5e-4) continue;
    if (TMath::Abs(dev) > 6e-3) continue; // 3D distortions
    TRSymMatrix CIn(6,In_fCov);                       PrPP(CIn);
    TRSymMatrix COut(6,Out_fCov);                     PrPP(COut);
    TRSymMatrix C(CIn);
    C += COut;                                        PrPP(C);
    for (Int_t i = 0; i < 6; i++) {
      if (i < 3) C(i,i) += 0.1*0.1*0.1;
      else       C(i,i) += 0.001*0.001*0.001;
    }
    PrPP(C);
    TRSymMatrix CMxM(TMx6,TRArray::kAxSxAT,C);        PrPP(CMxM);
    TVector3 nI = pxyzIn.Unit();                      PrPP(nI);
    TVector3 nO = pxyzOut.Unit();                     PrPP(nO);
    Double_t norm = nI*nO;
    if (norm <0) nO *= -1;
    TVector3 dn = nO - nI;                            PrPP(dn);
    TVector3 dr = rO - rI;                            PrPP(dr);
    Double_t tX = nO.X()/nO.Y();
    Double_t tZ = nO.Z()/nO.Y();
    TRVector mX(kM, dr.X(), dr.Z(), dn.X(), dn.Y());  PrPP(mX);
    TRSymMatrix G(CMxM,TRArray::kInverted);              PrPP(G);
    
/*============================== from maxima
    xS yS zS         aS  bS      gS xW  yW zW      aW   bW        gW
dX [-1,lx ,0,-lx*ZW   , -ZW,YW+lx*XW,1,-lx,0,lx*ZW   ,  ZW,-YW-lx*XW],
dZ [ 0,lz,-1,-lz*ZW-YW,  XW,   lz*XW,0,-lz,1,lz*ZW+YW, -XW,   -lz*XW],
dnX[ 0, 0, 0,        0,-nzW,       nyW,  0,0,       0,   0, nzW,-nyW],
dnY[ 0, 0, 0,      nzW,   0,      -nxW,  0,0,    -nzW,   0,      nxW],
dnZ[ 0, 0, 0,     -nyW, nxW,         0,  0,0,     nyW,-nxW,        0] 

LSF: chi2 = (A*p - m)T * G (A*p - m) = pT * AT * G * A * p - pT * AT * G * m - mT * G * A * p + mT * G * m =
                                       pT * A * p - pT * AT * G * m - mT * G * A * p + mT * G * m =
                                       pT * A * p - pT * AT * G * m - mT * G * A * p + mT * G * m =
                                       pT * AT * G * A * p - 2 * pT * AT * G * m + mT * G * m
                                       pT * SX * p - 2 * pT * Amx  + mT * G * m
d(chi2).dpT/2                   =           AT * G * A * p -          AT * G * m = 0
                                       AT * G * A * p = AT * G * m
                                       GX = G * m
                                       AmX = AT * GX
                                       SX  = AT * G * A
                                       SX *p = AmX
                                       W = SX^1;
                                       z = AmX
                                       p = W *Amx = W * z
                     
chi2 = pT * SX * p - 2 * pT * z  + mT * G * m = zT * WT * SX * W * z - 2 * zT * WT * z + mT * G * m
                                              = zT * WT  * z - 2 * zT * WT * z + mT * G * m 
                                              = mT * G * m  - zT * WT  * z
*/
#if 0
    TRMatrix A(kM,kP,
	       //                 0    1    2                    3         4                   5
	       //                dx   dy   dz                alpha      beta               gamma
	       /* dX 0*/	-1.,  tX,  0.,         -tX*rO.Z() ,  -rO.Z(), rO.Y() + tX*rO.X(),
	       /* dZ 1*/         0.,  tZ, -1., -(rO.Y()+tZ*rO.Z()),   rO.X(),          tZ*rO.X(),
	       /* nX 2*/         0.,  0.,  0.,                 0.0,  -nO.Z(),             nO.Y(),
	       /* nY 3*/         0.,  0.,  0.,              nO.Z(),      0.0,            -nO.X(),
	       /* nZ 4*/         0.,  0.,  0.,             -nO.Y(),   nO.X(),                0.0);  PrPP(A);
#else 
    Double_t aMxP[kM][kP];
    StTpcUtil::IODer(&rI[0], &nI[0], &rO[0], abgxyz_O, abgxyz_Wheel, aMxP);
    // Convert from Fortran to C storage (row-wise without gaps, contrary to the Fortran convention)
    TRMatrix A(kM,kP, &aMxP[0][0]);
#endif
    TRVector mGX(G,TRArray::kSxA,mX);  PrPP(mGX);
    TRVector AmX(A,TRArray::kATxB,mGX);  PrPP(AmX);
    TRSymMatrix SX(A,TRArray::kATxSxA,G);   PrPP(SX);
    Int_t sec = sector-1;
    Double_t *array = LSF[sec]->GetArray() + 1; // move under flow up
    Double_t *amX = AmX.GetArray();
    Double_t *sX  = SX.GetArray();
    Int_t im = 1;
    Int_t is = im + kP;
    if (_debug && array[0] > 0) {
      cout << "sector = " << sector << "\tentry = " << array[0] << " yHy = " << array[28] << endl;
      TRVector XX(kP,array+im);  PrPP(XX);
      TRSymMatrix S(kP,array+is);  PrPP(S);
      TRSymMatrix Cor(S, TRArray::kSCor); PrPP(Cor);
    }
    Double_t chi2 = G.Product(mX); PrPP(chi2);         
    //    if (chi2 > 1000.0) continue;
    array[28] += chi2;
    array[0]++;
    TCL::vadd(amX,array+im,array+im,kP); 
    TCL::vadd(sX,array+is,array+is,kPP); 
    if (_debug) {
      cout << "sector = " << sector << "\tentry = " << array[0] << " yHy = " << array[28] << endl;
      TRVector XX(kP,array+im);  PrPP(XX);
      TRSymMatrix S(kP,array+is);  PrPP(S);
      TRSymMatrix Cor(S, TRArray::kSCor); PrPP(Cor);
    }
    TRMatrix V(NFPlots,2,
mX(0), A(0,1),   //  {"dXdy",   "dX versus dX/dy[1,2]   => dy", 110,-0.95,  0.95,500,-0.30, 0.30}, // 0
mX(0), A(0,3),   //  {"dXdgamma",       "dX versus dX/dgamma[1,4]       => dgamma",     110,117.0, 137.0,500,-0.30, 0.30}, // 1
mX(1), A(1,1),   //  {"dZdy",   "dZ versus dZ/dy[2,2]   => dy", 110, -1.2,   1.0,500,-0.30, 0.30}, // 2
mX(1), A(1,3),   //  {"dZdgamma",       "dZ versus dZ/dgamma[2,4]       => dgamma",     110,-25.0, 25.0,500,-0.30, 0.30}, // 3
mX(2), A(2,3),   //  {"dnXdgamma",      "dnX versus dnX/dgamma[3,4]     => dgamma",     110,  0.4,  1.0,500,-0.02, 0.02}, // 4
mX(3), A(3,3),   //  {"dnYdgamma",      "dnY versus dnY/dgamma[4,4]     => dgamma",     110, -0.8,  0.8,500,-0.02, 0.02}, // 5
	       mX(0)  , rO.Z() , // "dX"       ,"dX  versus Z"                   
	       dr.Y() , rO.Z() , // "dY"       ,"dY  versus Z"                   
	       mX(1)  , rO.Z() , // "dZ"       ,"dZ  versus Z"                   
	       mX(2)  , rO.Z() , // "dnX"      ,"dnX versus Z"                   
 	       mX(3)  , rO.Z() , // "dnY"      ,"dnY versus Z"                   
	       dr.Z() , rO.Z() , // "dnZ"      ,"dnZ versus Z"                        
	       mX(1)/(driftVel/freq)  , rO.Z()  // "dT"       ,"dT  versus Z"
	       );// PrPP(V);
    for (Int_t i = 0; i < NFPlots; i++) plots3D[i]->Fill(sector, V(i,1), V(i,0));
    if (Ntracks%10000 == 0) {cout << "read track no\t" << Ntracks << endl;}
    Ntracks++;
  }
  fOut->Write();
}
//________________________________________________________________________________
void TDrawIO() {
  TMinuitMinimizer::UseStaticMinuit();
  if (! gMinuit) new TMinuit(10);
  gMinuit->SetPrintLevel(-2);
  Int_t nx = 24;
  Int_t ny = NPlots; // NFPlots
  Int_t scaleX = 800/nx;
  Int_t scaleY = 600/ny;
  enum {kM = 4, kP = 4, kPP = kP*(kP+1)/2};
  //  Int_t scale  = TMath::Min(scaleX,scaleY);
  TCanvas *c1 = new TCanvas("TpcInOut","TpcInOut Alignment" ,10,10,10+scaleX*nx,10+scaleY*ny);
  cout << "nx/ny = " << nx << "/" << ny << endl;
  c1->Divide(ny,nx);
  TString line("");
  TString lTitle("");
  TString lineC("");
  ofstream out;
  ofstream outC;
  TString Out("Results.IO_");
  Out += gSystem->BaseName(gDirectory->GetName());
  Out.ReplaceAll(".root","");
  Out.ReplaceAll("*","");
  //  Out += t.AsString();
  Out.ReplaceAll(" ","");
  if (gSystem->AccessPathName(Out)) out.open(Out, ios::out); //"Results.list",ios::out | ios::app);
  else                              out.open(Out, ios::app);
  Out += ".h";
  if (gSystem->AccessPathName(Out)) outC.open(Out, ios::out); //"Results.list",ios::out | ios::app);
  else                              outC.open(Out, ios::app);
  Int_t head = 0;
  struct Val_t {
    Double_t val;
    Double_t valError;
    Int_t    iFlag;
  };
  Val_t ValG[7]; memset (ValG, 0, sizeof(ValG));
  for (Int_t i = 1; i <= nx; i++) {
    if (! head) {
      out  <<  "_______________________________________________________________________________________________________"  << endl;
      out  <<  "| x mkm         | y mkm         | z mkm         |alpha mrad     |beta mrad      |gamma mrad     |Comment" << endl;
      cout <<  "_______________________________________________________________________________________________________"  << endl;
      cout <<  "| x mkm         | y mkm         | z mkm         |alpha mrad     |beta mrad      |gamma mrad     |Comment" << endl;
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
    Int_t sector = i;
    out  << "__________________________________________________________________________________________________ " << sector << endl;
    cout << "__________________________________________________________________________________________________ " << sector << endl;
    TH1D *LSF = (TH1D *) gDirectory->Get(Form("LSF_%02i",sector));
    Val_t ValA[7]; memset (ValA, 0, sizeof(ValA));
    if (LSF) {
      Double_t *array = LSF->GetArray() + 1;
      Int_t NP = array[0];   PrPP(NP);
      if (NP > 0) {
	Double_t yTy = array[28]; PrPP(yTy);
	Int_t im = 1;
	Int_t is = im + kP;
	TRVector AmX(kP,array+im);  PrPP(AmX);
	TRSymMatrix S(kP,array+is); PrPP(S);
	TRSymMatrix Cor(S, TRArray::kSCor); PrPP(Cor);
	TRSymMatrix SInv(S,TRArray::kInverted);  PrPP(SInv);
	TRVector  X(SInv,TRArray::kSxA,AmX);     PrPP(X);
	Double_t chi2 = yTy;
	chi2 -= AmX*X;
	//	Double_t mSIm = SInv.Product(AmX); 
	// cout << "chi2 = " << chi2 << "/ NDF = " << NP << " mS-1m " << mSIm << endl;
	line = "";
	for (Int_t p = 0; p < kP; p++) {
	  Int_t m = p;
	  if (p > 2) m = 5;
	  if (SInv(p,p) > 0) {
	    Double_t scale = 1e4;   // => mkm
	    if (m > 2) scale = 1e3; // => mrad
	    ValA[m].val =  scale*X(p);
	    ValA[m].valError = scale*TMath::Sqrt(SInv(p,p));
	    //	    ValA[m].iFlag = 0;
	    if (m <= 2 && TMath::Abs(ValA[m].val) < 2000 ||
		m >  2 && TMath::Abs(ValA[m].val) <    5) {
	      ValA[m].iFlag = 1;
	    } else {
	      ValA[m].iFlag = 0;
	    }
	    if (p == kP - 1) {
	      line  += "|               ";
	      line  += "|               ";
	    }
	    line  += Form("|%7.2f+-%5.2f ",TMath::Max(-9999.99,TMath::Min(9999.99,ValA[m].val)),TMath::Min(99.99,ValA[m].valError)); 
	  } else {
	    ValA[m].val = ValA[m].valError = 0; ValA[m].iFlag = 0;
	    line  += "|               ";
 	  }
	}
      }
    }
    cout << line << endl;
    out << line << endl;
    for (Int_t j = 0; j < NPlots+3; j++) {
      TH3 *h3 = (TH3 *) gDirectory->Get(plotNameD[j].Name);
      if (! h3) continue;
      TString Name(h3->GetName());
      TString Title(h3->GetTitle());
      Int_t ij = j + 1 + ny*(i-1);
      c1->cd(ij)->SetLogz(1);
      TH1 *fit = 0;
      h3->GetXaxis()->SetRange(sector,sector);
      TH1 *sp = h3->Project3D("z");
      if (sp->GetEntries() < 100) continue;
      sp->Fit("gaus","qem");
      Double_t Mu = 0;
      Double_t dMu = 0;
      Double_t prob = 0;
      TF1 *fun = sp->GetFunction("gaus");
      if (fun) {
	Mu = fun->GetParameter(1);
	dMu = fun->GetParError(1);
      }
      Double_t slope = 0;
      Double_t dslope = 0;
      TF1 *pol1 = 0;
      TH2 *h = 0;
      TLegend *leg = 0;
      Int_t index = Title.Index("=>");
      TString tag("");
      if (index >= 0) {
	index = index+2;
	static TString separator("[^ ;,]+");
	TString t(Title.Data()+index);
	TObjArray *array = t.Tokenize(separator);
	tag = ((TObjString *) array->At(0))->GetString();
	delete array;
      }
      if (tag != "") {
	h = (TH2 *) h3->Project3D("zy");
	h->SetName(Form("%s_%i",h->GetName(),sector));
	h->FitSlicesY(0,0,-1,10,"qeg3s");
	fit = (TH1 *) gDirectory->Get(Form("%s_1",h->GetName()));
	leg = new TLegend(0.1,0.2,0.6,0.3,"");
	lTitle = "";
	leg->SetTextSize(0.025);
	if (fit) {
	  fit->SetTitle(h->GetTitle());
	  fit->SetMarkerStyle(20);
	  fit->SetMarkerColor(1);
	  fit->SetMaximum(0.2);
	  fit->SetMinimum(-.2);
	  fit->SetStats(1);
	  fit->Fit("pol1","qe");
	  pol1 = fit->GetFunction("pol1");
	  if (! pol1 ) goto endhLoop;
	  prob = pol1->GetProb();
	  if (prob >= 0) {
#if 0
	    Double_t xm = fit->GetMean();
	    Mu     = pol1->Eval(xm);
	    dMu    = TMath::Sqrt(pol1->GetParError(0)*pol1->GetParError(0) + (xm*pol1->GetParError(1))*(xm*pol1->GetParError(1)));
	    if (dMu > 99.99e-4) dMu=  99.99e-4;
#endif
	    slope  = pol1->GetParameter(1);
	    dslope = pol1->GetParError(1);
	    if (dslope > 99.99e-3) dslope = 99.99e-3;
	    if (TMath::Abs(slope) > 0.1) dslope = 99.99e-3;
	  } else {
	    Mu = slope = 0;
	    dMu = dslope = 0;
	  }
	}
	Val_t Vals[6]; memset (Vals, 0, sizeof(Vals));
	static const Char_t *dxv[3] = {"dX", "dY","dZ"};
	for (Int_t m = 0; m < 3; m++) {
	  if (Name.BeginsWith(dxv[m]) && dMu > 0 && dMu < 99.99e-4) {
	    Vals[m].val =     -1e4*Mu;
	    Vals[m].valError = 1e4*dMu;
	    Vals[m].iFlag = 1;
	    lTitle += Form(" %s = %7.2f+-%5.2f (#mum)", dxv[m],Vals[m].val,TMath::Min(99.99,Vals[m].valError)); 
	  }
	}	  
	static const Char_t *lvar[6] = {"dx","dy","dz","#alpha","#beta","#gamma"};
	for (Int_t m = 0; m < 6; m++) {
	  if (dslope <= 1e-6 || slope >= 99e-3) continue;
	  if (m == 1 && tag.Contains("dy") && dslope < 99.99e-4) {
	    Vals[m].val =      1e4*slope;
	    Vals[m].valError = 1e4*dslope;
	    Vals[m].iFlag = 1;
	    lTitle += Form(" %s = %7.2f+-%5.2f (#mum)", lvar[m],Vals[m].val,TMath::Min(99.99,Vals[m].valError)); 
	  } else if (dslope < 99.99e-3) {
	    if ((m == 3 && tag.Contains("alpha")) ||
		(m == 4 && tag.Contains("beta"))  ||
		(m == 5 &&  tag.Contains("gamma"))) {
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
	    line  += "|               ";
	    lineC += ",      0,-9.99";
	  } else {
	    line  += Form("|%7.2f+-%5.2f ", Vals[m].val,TMath::Min(99.99,Vals[m].valError)); 
	    lineC += Form(",%7.2f,%5.2f", Vals[m].val,TMath::Min(99.99,Vals[m].valError)); 
#define __AVERAGE_IO__
#ifdef  __AVERAGE_IO__
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
	if (pol1) {pol1->SetLineColor(2); pol1->Draw("same");}
      }
      if (leg) leg->Draw();
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
	line  += "|               ";
	lineC += ",      0,-9.99";
      } else {
	line  += Form("|%7.2f+-%5.2f ", ValA[m].val,TMath::Min(99.99,ValA[m].valError)); 
	lineC += Form(",%7.2f,%5.2f", ValA[m].val,TMath::Min(99.99,ValA[m].valError)); 
	Double_t w0 = 1./(ValA[m].valError*ValA[m].valError);
	Double_t w1 = 0;
	if (ValG[m].valError > 0) 
	  w1 = 1./(ValG[m].valError*ValG[m].valError);
	ValG[m].val = (w0*ValA[m].val + w1*ValG[m].val)/(w0 + w1);
	ValG[m].valError = 1./TMath::Sqrt(w0 + w1);
	ValG[m].iFlag++;
      }
    }
#ifdef __AVERAGE_IO__
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
  line = ""; 
  lineC = "";
  for (Int_t m = 0; m < 6; m++) {
    if (! ValG[m].iFlag 
#ifdef   FREEZE_BETA  
	|| (m == 4) 
#endif
#ifdef   FREEZE_ALPHA_BETA  
	|| (m == 3 || m == 4) 
#endif
	) {
      line  += "|               ";
      lineC += ",      0,-9.99";
    } else {
      line  += Form("|%7.2f+-%5.2f ", ValG[m].val,TMath::Min(99.99,ValG[m].valError)); 
      lineC += Form(",%7.2f,%5.2f", ValG[m].val,TMath::Min(99.99,ValG[m].valError)); 
    }
  }
  cout << line << endl;
  out << line << endl;
  outC << "    }" << endl;
  outC << "  }," << endl;

  out.close();
  outC.close();
}
