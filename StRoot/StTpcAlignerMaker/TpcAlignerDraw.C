/*
  ln -s ~/macros/.sl* .
  root.exe -q -b TpcAlignerDraw.C+ 'TpcAlignerDraw.C+(2)'>& TpcAlignerDraw.log &
  root.exe -q -b 'TpcAlignerDraw.C+(1)' 'TpcAlignerDraw.C+(3)'> & TpcAlignerDraw1.log &
foreach f (`ls -1d 2014*.root`)
set b = `basename ${f} .root`; root.exe -q -b 'TpcAlignerDraw.C+(0,"'${f}'")' >& ${b}.log &
end
FPE_OFF
foreach f (`ls -1d 2014*.IO*.Errors.root`)
set b = `basename ${f} .root`; root.exe -q -b ${f} 'TpcAlignerDraw.C+(2)' >& ${b}.Fit.log &
end

@ count = 0
foreach r (`ls -1d st_*.root | sed -e 's/st_//' -e 's/adc_//' -e 's/hltcosmic_//' -e 's/gmt_//' | awk -F_ '{print $1}' | sort -u`)
  set file = st${r}Plots.Cut.Errors.root
  if (-r ${file}) continue;
  root.exe -q -b 'TpcAlignerDraw.C+(0,"st*'${r}'*.root")' >& ${r}.log &
    @ count++;  echo "count $count";
    if ($count > 40) break;
end


*/
#if !defined(__CINT__) || defined(__MAKECINT__)
#include "Riostream.h"
#include "Rtypes.h"
#include "TROOT.h"
#include "TSystem.h"
#include "TH2.h"
#include "TH3.h"
#include "TF1.h"
#include "TLegend.h"
#include "TProfile.h"
#include "TTree.h"
#include "TFile.h"
#include "TChain.h"
#include "TCanvas.h"
#include "TClassTable.h"
#include "TVector3.h"
#include "TMinuit.h"
#include "TMinuitMinimizer.h"
#include "TMath.h"
#include "TFileSet.h"
#include "StarRoot/TDirIter.h"
#include "StarRoot/TTreeIter.h"
#include "TArrayD.h"
#include "TRVector.h"
#include "TRMatrix.h"
#include "TGeoMatrix.h"
#endif
/* 
   TpcW2STree->Draw("(abs(HelixU.Rho)-abs(HelixS.Rho))/(abs(HelixU.Rho)+abs(HelixS.Rho))>>dC(100,-2e-1,2e-1)") => sigma = 3.55241e-02
   TpcInOutTree->Draw("(abs(In.Rho)-abs(Out.Rho))/(abs(In.Rho)+abs(Out.Rho))>>dC(100,-2e-1,2e-1)") => 6.24288e-02
 */
static Int_t _debug = 0;
#define PrPP(B) if (_debug) {cout << (#B) << " = \t" << (B) << endl;}
//________________________________________________________________________________
struct PlotName_t {
  const Char_t *Name;
  const Char_t *Title;
  Int_t nx;
  Double_t xmin, xmax;
  Int_t nz;
  Double_t zmin, zmax;
};
enum {NPlots = 21, NFPlots=14, NwsPlots=20, NwsFPlots=20};
const  PlotName_t plotNameD[NPlots] = {// plots for drift
  {"dXdy"     ,"dX  versus  tX         =>  dy",    100,  -0.5,  0.5, 500, -1.000, 1.000}, // 0 -> <dx>, dy   
  {"dXdalpha" ,"dX  versus -tX*zO      =>  alpha", 100,  -60.,  40., 500, -1.000, 1.000}, // 1 -> <dx>, alpha
  {"dXdbeta"  ,"dX  versus -zO         =>  beta",  100, -210., -10., 500, -1.000, 1.000}, // 2 -> <dx>, beta 
  {"dXdgamma" ,"dX  versus  yO + tX*xO =>  gamma", 100,  118., 130., 500, -1.000, 1.000}, // 3 -> <dx>, gamma
  {"dZdy"     ,"dZ  versus  tZ         =>  dy",    100, -0.8 ,  0.6, 500, -1.000, 1.000}, // 4 -> <dz>, dy   
  {"dZdalpha" ,"dZ  versus -(yO+tZ*zO) =>  alpha", 100, -200., -50., 500, -1.000, 1.000}, // 5 -> <dz>, alpha
  {"dZdbeta"  ,"dZ  versus  xO         =>  beta",  100,  -30.,  30., 500, -1.000, 1.000}, // 6 -> <dz>, beta 
  {"dZdgamma" ,"dZ  versus  tZ*xO      =>  gamma", 100,  -10.,  10., 500, -1.000, 1.000}, // 7 -> <dz>, gamma
  {"dnXdbeta" ,"dnX versus -nzO        =>  beta",  100,  -0.8,  0.8, 500, -0.025, 0.025}, // 8 ->       beta 
  {"dnXdgamma","dnX versus  nyO        =>  gamma", 100,   0.7,  1.0, 500, -0.025, 0.025}, // 9 ->       gamma
  {"dnYdalpha","dnY versus  nzO        =>  alpha", 100,  -0.8,  0.8, 500, -0.025, 0.025}, //10 ->       alpha 
  {"dnYdgamma","dnY versus -nxO        =>  gamma", 100,   -.6,   .6, 500, -0.025, 0.025}, //11 ->       gamma
  {"dnZdalpha","dnZ versus -nyO        =>  alpha", 100,  -1.0,  -.7, 500, -0.025, 0.025}, //12 ->       alpha
  {"dnZdbeta" ,"dnZ versus  nxO        =>  beta" , 100,   -.6,   .6, 500, -0.025, 0.025}, //13 ->       beta
  {"dX"       ,"dX  versus Z"                    , 200,    10,  210, 500, -1.000, 1.000}, //14
  {"dY"       ,"dY  versus Z"                    , 200,    10,  210, 500, -0.001, 0.001}, //15
  {"dZ"       ,"dZ  versus Z"                    , 200,    10,  210, 500, -1.000, 1.000}, //16
  {"dnX"      ,"dnX versus Z"                    , 200,    10,  210, 500, -0.025, 0.025}, //17
  {"dnY"      ,"dnY versus Z"                    , 200,    10,  210, 500, -0.025, 0.025}, //18
  {"dnZ"      ,"dnZ versus Z"                    , 200,    10,  210, 500, -0.025, 0.025}, //19
  {"dT"       ,"dT (time buckets)  versus Z"     , 200,    10,  210, 500, -2.000, 2.000}  //20
};
const  PlotName_t plotNameWS[NwsPlots] = {// plots for drift
/* mX(0), A( 4,0), ds, */ {"dnXdbS",       "-nZS   => bS", 110,-1.100, 1.100,100,-0.050, 0.050}, // 0
/* mX(0), A( 5,0), ds, */ {"dnXdgS",       "nYS    => gS", 110,-1.100, 1.100,100,-0.050, 0.050}, // 1
/* mX(0), A(10,0), dw, */ {"dnXdbW",       "-nZU   => bW", 110,-1.100, 1.100,100,-0.050, 0.050}, // 2
/* mX(0), A(11,0), dw, */ {"dnXdgW",       "nYU    => gW", 110,-1.100, 1.100,100,-0.050, 0.050}, // 3
/* mX(1), A( 3,1), ds, */ {"dnYdaS",       "nZS    => aS", 110,-1.100, 1.100,100,-0.005, 0.005}, // 4
/* mX(1), A( 5,1), ds, */ {"dnYdgS",       "-nXS   => gS", 110,-1.100, 1.100,100,-0.005, 0.005}, // 5
/* mX(1), A( 9,1), dw, */ {"dnYdaW",       "nZU    => aW", 110,-1.100, 1.100,100,-0.005, 0.005}, // 6
/* mX(1), A(11,1), dw, */ {"dnYdgW",       "-nXU   => gW", 110,-1.100, 1.100,100,-0.005, 0.005}, // 7
/* mX(2), A( 3,2), ds, */ {"dnZdaS",       "-nYS   => aS", 110,-1.100, 1.100,100,-0.005, 0.005}, // 8
/* mX(2), A( 4,2), ds, */ {"dnZdbS",       "-nXS   => bS", 110,-1.100, 1.100,100,-0.005, 0.005}, // 9
/* mX(2), A( 9,2), dw, */ {"dnZdaW",       "-nYU   => aW", 110,-1.100, 1.100,100,-0.005, 0.005}, //10
/* mX(2), A(10,2), dw, */ {"dnZdbW",       "-nXU   => bW", 110,-1.100, 1.100,100,-0.005, 0.005}, //11

/* mX(3), A( 4,3), ds, */ {"dXdbS",        "-ZS    => bS", 100,-250.0, 10.00,100,-1.000, 1.000}, //12
/* mX(3), A( 5,3), ds, */ {"dXdgS",        "YS     => gS",  60, 55.00,175.00,100,-1.000, 1.000}, //13
/* mX(3), A(10,3), dw, */ {"dXdbW",        "-ZU    => bW", 100,-250.0, 10.00,100,-1.000, 1.000}, //14
/* mX(3), A(11,3), dw, */ {"dXdgW",        "YU     => gW",  60, 55.00,175.00,100,-1.000, 1.000}, //15
/* mX(5), A( 3,5), ds, */ {"dZdaS",        "-YS    => aS",  60,-175.0, -55.0,100,-1.000, 1.000}, //16
/* mX(5), A( 4,5), ds, */ {"dZdbS",        "-XS    => bS", 120, -60.0,  60.0,100,-1.000, 1.000}, //17
/* mX(5), A( 9,5), dw, */ {"dZdaW",        "-YU    => aW",  60,-175.0, -55.0,100,-1.000, 1.000}, //18
/* mX(5), A(10,5), dw  */ {"dZdbW",        "-XU    => bW", 120, -60.0,  60.0,100,-1.000, 1.000}  //19
};
//________________________________________________________________________________
void TpcAlignerDrawIO(const Char_t *files = "../*.root", Bool_t laser = kFALSE) {
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
	static const Int_t&       TriggerId                                = iter("TriggerId");
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
	//	static const UInt_t&      In_fUniqueID                             = iter("In.fUniqueID");
	//	static const UInt_t&      In_fBits                                 = iter("In.fBits");
	static const Int_t&       In_sector                                = iter("In.sector");
	static const Double_t&    In_Rho                                   = iter("In.Rho");
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
	static const Double_t&    In_dRho                                  = iter("In.dRho");
	static const Double_t*&   In_fCov                                  = iter("In.fCov[15]");
	static const Double_t&    In_Chi2                                  = iter("In.Chi2");
	static const Int_t&       In_Ndf                                   = iter("In.Ndf");
	static const Int_t&       In_Npoints                               = iter("In.Npoints");
	static const Int_t&       In_Nused                                 = iter("In.Nused");
	static const Double_t&    In_DriftZ                                = iter("In.DriftZ");
	static const Double_t&    In_step                                  = iter("In.step");
	static const Double_t*&   In_RefSurficeG                           = iter("In.RefSurficeG[4]");
	//	static const UInt_t&      Out_fUniqueID                            = iter("Out.fUniqueID");
	//	static const UInt_t&      Out_fBits                                = iter("Out.fBits");
	static const Int_t&       Out_sector                               = iter("Out.sector");
	static const Double_t&    Out_Rho                                  = iter("Out.Rho");
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
	static const Double_t&    Out_dRho                                 = iter("Out.dRho");
	static const Double_t*&   Out_fCov                                 = iter("Out.fCov[15]");
	static const Double_t&    Out_Chi2                                 = iter("Out.Chi2");
	static const Int_t&       Out_Ndf                                  = iter("Out.Ndf");
	static const Int_t&       Out_Npoints                              = iter("Out.Npoints");
	static const Int_t&       Out_Nused                                = iter("Out.Nused");
	static const Double_t&    Out_DriftZ                               = iter("Out.DriftZ");
	static const Double_t&    Out_step                                 = iter("Out.step");
	static const Double_t*&   Out_RefSurficeG                          = iter("Out.RefSurficeG[4]");
  // Book Histograms
  TString Out(gSystem->BaseName(files)); 
  Out.ReplaceAll("st_","");
  Out.ReplaceAll(".root","");
  Out.ReplaceAll("*","");
  //  Out += ".2GeVC";
  //  if (TMath::Abs(field) > 1)   Out += ".1GeVC";
  if (laser) Out += ".Laser";
  //  Out += ".Cut";
  //  Out += ".Errors";
  Out += "_IO.root";
  TFile *fOut = new TFile(Out,"recreate");
  TH3F *plots3D[NPlots];
  for (Int_t i = 0; i < NPlots; i++) {
#if 1
    plots3D[i] = new TH3F(plotNameD[i].Name, plotNameD[i].Title, 24, 0.5, 24.5, 
			  plotNameD[i].nx, plotNameD[i].xmin, plotNameD[i].xmax,
			  plotNameD[i].nz, plotNameD[i].zmin, plotNameD[i].zmax);
#else
    plots3D[i] = new TH3F(plotNameD[i].Name, plotNameD[i].Title, 24, 0.0, 0.0,
			  plotNameD[i].nx, 0.0, 0.0, 
			  plotNameD[i].nz, 0.0, 0.0);
#endif
  }
  TH1D *dv = new TH1D("DV","pc Drift Velocisies", 100, 5, 6);
  TH1D *LSF[24];
  //  Increase hitogram by 2 bins in order to account underfloaw and overflow 
  for (Int_t sec = 1; sec <= 24; sec++) LSF[sec-1] = new TH1D(Form("LSF_%02i",sec),Form("Matrix and right part for Least Squared Fit for sector = %02i",sec),30,0,30.);
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
    if (! Out_sector) continue;
    TVector3 pxyzIn(In_nx,In_ny,In_nz);  PrPP(pxyzIn);
    TVector3 rI(In_x,In_y,In_z);         PrPP(rI);
    TVector3 pxyzOut(Out_nx,Out_ny,Out_nz);   PrPP(pxyzOut);
    TVector3 rO(Out_x,Out_y,Out_z); PrPP(rO);
    Double_t dev = (TMath::Abs(In_Rho)-TMath::Abs(Out_Rho));
    //    if (TMath::Abs(dev) > 5e-4) continue;
    if (TMath::Abs(dev) > 6e-3) continue; // 3D distortions
    TRSymMatrix CIn(5,In_fCov);                       PrPP(CIn);
    TRSymMatrix COut(5,Out_fCov);                     PrPP(COut);
    TRSymMatrix C(CIn);
    C += COut;                                        PrPP(C);
#if 1
    C(0,0) += 1./2.2e2; // 2e2
    C(1,1) += 1./2.2e2; // 2.1e2
    C(2,2) += 1./5.6e4; // 3.76e4
    C(3,3) += 1e-6;     // 5.9e5
    C(4,4) += 1./3.8e5; // 3e5                              PrPP(C);
#endif
    TRSymMatrix GI(C);
    Int_t iFail = TRSymMatrix::TrchLU(C.GetArray(),GI.GetArray(),5);
    if (iFail != 0) {
      if (! _debug ) {
	_debug = 1;
	PrPP(pxyzIn);  PrPP(rI); PrPP(CIn);
	PrPP(pxyzOut); PrPP(rO); PrPP(COut);
	PrPP(C);
	_debug = 0;
      }
      continue;
    }
    TRSymMatrix G(C,TRArray::kInverted);              PrPP(G);
    TVector3 nI = pxyzIn.Unit();                      PrPP(nI);
    TVector3 nO = pxyzOut.Unit();                     PrPP(nO);
    Double_t norm = nI*nO;
    if (norm <0) nO *= -1;
    TVector3 dn = nO - nI;                            PrPP(dn);
    TVector3 dr = rO - rI;                            PrPP(dr);
    Double_t tX = nO.X()/nO.Y();
    Double_t tZ = nO.Z()/nO.Y();
    TRVector mX(5, dr.X(), dr.Z(), dn.X(), dn.Y(), dn.Z());  PrPP(mX);
#if 1
    if (mX(0) < plotNameD[14].zmin || mX(0) > plotNameD[14].zmax) continue;
    if (mX(1) < plotNameD[16].zmin || mX(1) > plotNameD[16].zmax) continue;
    if (mX(2) < plotNameD[17].zmin || mX(2) > plotNameD[17].zmax) continue;
    if (mX(3) < plotNameD[18].zmin || mX(3) > plotNameD[18].zmax) continue;
    if (mX(4) < plotNameD[19].zmin || mX(4) > plotNameD[19].zmax) continue;
#endif
/*============================== from maxima
    xS yS zS         aS  bS      gS xW  yW zW      aW   bW        gW
dX [-1,lx ,0,-lx*ZW   , -ZW,YW+lx*XW,1,-lx,0,lx*ZW   ,  ZW,-YW-lx*XW],
dZ [ 0,lz,-1,-lz*ZW-YW,  XW,   lz*XW,0,-lz,1,lz*ZW+YW, -XW,   -lz*XW],
dnX[ 0, 0, 0,        0,-nzW,       nyW,  0,0,       0,   0, nzW,-nyW],
dnY[ 0, 0, 0,      nzW,   0,      -nxW,  0,0,    -nzW,   0,      nxW],
dnZ[ 0, 0, 0,     -nyW, nxW,         0,  0,0,     nyW,-nxW,        0] */
    TRMatrix A(5,6,
	       //                 0    1    2                    3         4                   5
	       //                dx   dy   dz                alpha      beta               gamma
	       /* dX 0*/	-1.,  tX,  0.,         -tX*rO.Z() ,  -rO.Z(), rO.Y() + tX*rO.X(),
	       /* dZ 1*/         0.,  tZ, -1., -(rO.Y()+tZ*rO.Z()),   rO.X(),          tZ*rO.X(),
	       /* nX 2*/         0.,  0.,  0.,                 0.0,  -nO.Z(),             nO.Y(),
	       /* nY 3*/         0.,  0.,  0.,              nO.Z(),      0.0,            -nO.X(),
	       /* nZ 4*/         0.,  0.,  0.,             -nO.Y(),   nO.X(),                0.0);  PrPP(A);
    TRVector mGX(G,TRArray::kSxA,mX);  PrPP(mGX);
    TRVector AmX(A,TRArray::kATxB,mGX);  PrPP(AmX);
    TRSymMatrix SX(A,TRArray::kATxSxA,G);   PrPP(SX);
    Int_t sec = sector-1;
    Double_t *array = LSF[sec]->GetArray() + 1; // move under flow up
    Double_t *amX = AmX.GetArray();
    Double_t *sX  = SX.GetArray();
    array[0]++;
    Int_t im = 1;
    Int_t is = im + 6;
    if (rO.Z() > 40 && rO.Z() < 200) {
      TCL::vadd(amX,array+im,array+im,6); if (_debug) {TRVector XX(6,array+im);  PrPP(XX);}
      TCL::vadd(sX,array+is,array+is,21); if (_debug) {TRSymMatrix S(6,array+is);  PrPP(S);}
      array[28] += G.Product(mX);
    }
    TRMatrix V(NPlots,2,
	       mX(0)  ,  A(0,1), // "dXdy"     ,"dX  versus  tX         =>  dy", 
	       mX(0)  ,  A(0,3), // "dXdalpha" ,"dX  versus -tX*zO      =>  alpha
	       mX(0)  ,  A(0,4), // "dXdbeta"  ,"dX  versus -zO         =>  beta"
	       mX(0)  ,  A(0,5), // "dXdgamma" ,"dX  versus  yO + tX*xO =>  gamma
	       mX(1)  ,  A(1,1), // "dZdy"     ,"dZ  versus  tZ         =>  dy", 
	       mX(1)  ,  A(1,3), // "dZdalpha" ,"dZ  versus -(yO+tZ*zO) =>  alpha
	       mX(1)  ,  A(1,4), // "dZdbeta"  ,"dZ  versus  xO         =>  beta"
	       mX(1)  ,  A(1,5), // "dZdgamma" ,"dZ  versus  tZ*xO      =>  gamma
	       mX(2)  ,  A(2,4), // "dnXdbeta" ,"dnX versus -nzO        =>  beta"
	       mX(2)  ,  A(2,5), // "dnXdgamma","dnX versus  nyO        =>  gamma
	       mX(3)  ,  A(3,3), // "dnYdalpha","dnY versus  nzO        =>  alpha
	       mX(3)  ,  A(3,5), // "dnYdgamma","dnY versus -nxO        =>  gamma
	       mX(4)  ,  A(4,3), // "dnZdalpha","dnZ versus -nyO        =>  alpha
	       mX(4)  ,  A(4,4), // "dnZdbeta" ,"dnZ versus  nxO        =>  beta"
	       mX(0)  , rO.Z() , // "dX"       ,"dX  versus Z"                   
	       dr.Y() , rO.Z() , // "dY"       ,"dY  versus Z"                   
	       mX(1)  , rO.Z() , // "dZ"       ,"dZ  versus Z"                   
	       mX(2)  , rO.Z() , // "dnX"      ,"dnX versus Z"                   
	       mX(3)  , rO.Z() , // "dnY"      ,"dnY versus Z"                   
	       mX(4)  , rO.Z() , // "dnZ"      ,"dnZ versus Z"                        
	       mX(1)/(driftVel/freq)  , rO.Z()  // "dT"       ,"dT  versus Z"
	       ); PrPP(V);
    for (Int_t i = 0; i < NPlots; i++) plots3D[i]->Fill(sector, V(i,1), V(i,0));
    if (Ntracks%10000 == 0) {cout << "read track no\t" << Ntracks << endl;}
      Ntracks++;
  }
  fOut->Write();
}
//________________________________________________________________________________
void TpcAlignerDrawW2S(const Char_t *files = "*.root") {
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
	static const Double_t*&   HlxParW_fCov                             = iter("HlxParW.fCov[15]");
	static const Double_t&    HlxParW_Chi2                             = iter("HlxParW.Chi2");
	static const Int_t&       HlxParW_Ndf                              = iter("HlxParW.Ndf");
	static const Int_t&       HlxParW_Npoints                          = iter("HlxParW.Npoints");
	static const Int_t&       HlxParW_Nused                            = iter("HlxParW.Nused");
	static const Double_t&    HlxParW_DriftZ                           = iter("HlxParW.DriftZ");
	static const Double_t&    HlxParW_step                             = iter("HlxParW.step");
	static const Double_t*&   HlxParW_RefSurficeG                      = iter("HlxParW.RefSurficeG[4]");
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
	static const Double_t*&   HlxParS_fCov                             = iter("HlxParS.fCov[15]");
	static const Double_t&    HlxParS_Chi2                             = iter("HlxParS.Chi2");
	static const Int_t&       HlxParS_Ndf                              = iter("HlxParS.Ndf");
	static const Int_t&       HlxParS_Npoints                          = iter("HlxParS.Npoints");
	static const Int_t&       HlxParS_Nused                            = iter("HlxParS.Nused");
	static const Double_t&    HlxParS_DriftZ                           = iter("HlxParS.DriftZ");
	static const Double_t&    HlxParS_step                             = iter("HlxParS.step");
	static const Double_t*&   HlxParS_RefSurficeG                      = iter("HlxParS.RefSurficeG[4]");
	//	static const UInt_t&      HlxParW2S_fUniqueID                      = iter("HlxParW2S.fUniqueID");
	//	static const UInt_t&      HlxParW2S_fBits                          = iter("HlxParW2S.fBits");
	static const Int_t&       HlxParW2S_sector                         = iter("HlxParW2S.sector");
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
	static const Double_t*&   HlxParW2S_fCov                           = iter("HlxParW2S.fCov[15]");
	static const Double_t&    HlxParW2S_Chi2                           = iter("HlxParW2S.Chi2");
	static const Int_t&       HlxParW2S_Ndf                            = iter("HlxParW2S.Ndf");
	static const Int_t&       HlxParW2S_Npoints                        = iter("HlxParW2S.Npoints");
	static const Int_t&       HlxParW2S_Nused                          = iter("HlxParW2S.Nused");
	static const Double_t&    HlxParW2S_DriftZ                         = iter("HlxParW2S.DriftZ");
	static const Double_t&    HlxParW2S_step                           = iter("HlxParW2S.step");
	static const Double_t*&   HlxParW2S_RefSurficeG                    = iter("HlxParW2S.RefSurficeG[4]");
  // Book Histograms
  TString Out(files); 
  Out.ReplaceAll(".root","W2S");
  Out.ReplaceAll("*","");
  Out += ".root";
  Out = gSystem->BaseName(Out);
  TFile *fOut = new TFile(Out,"recreate");
  TH3F *plots3D[NwsPlots];
  for (Int_t i = 0; i < NwsPlots; i++) {
    plots3D[i] = new TH3F(plotNameWS[i].Name, plotNameWS[i].Title, 24, 0.5, 24.5, 
			  plotNameWS[i].nx, plotNameWS[i].xmin, plotNameWS[i].xmax,
			  plotNameWS[i].nz, plotNameWS[i].zmin, plotNameWS[i].zmax);
  }
  Int_t NP  = 6; // Total no. of parameters per sector
  Int_t NPP = NP*(NP+1)/2; // size of matrix
  Int_t NT  = NP + NPP; // bin0 -> no. of entries; bin_NT+1 = chi2
  TH1D *LSF = new TH1D("LSF","Matrix and right part for Least Squared Fit ",NT+2,0,NT + 2);
  Int_t Ntracks = 0;
  while (iter.Next()) {
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
#if 0
    TRSymMatrix CU(5,HlxParW2S_fCov);                  PrPP(CU);
    TRSymMatrix CS(5,HlxParS_fCov);                  PrPP(CS);
    TRSymMatrix C(CU);
    C += CS;   PrPP(C);
#else 
    TRSymMatrix C(6);
    for (Int_t i = 0; i < 6; i++) {
      if (i < 3) 
	C(i,i) = 1e-6;
      else 
	C(i,i) = 1e-2;
    }       
    PrPP(C);
#endif
    TRSymMatrix G(C,TRArray::kInverted);              PrPP(G);
    TVector3 nW(nXW,nYW,nZW);                         PrPP(nW);
    TVector3 nU(nXU,nYU,nZU);                         PrPP(nU);
    TVector3 nS(nXS,nYS,nZS);                         PrPP(nS);
    TVector3 rW(XW,YW,ZW);                         PrPP(rW);
    TVector3 rU(XU,YU,ZU);                         PrPP(rU);
    TVector3 rS(XS,YS,ZS);                         PrPP(rS);

    TVector3 dn = nS - nU;                            PrPP(dn);
    TVector3 dr = rS - rU;                            PrPP(dr);
    enum {kM = 6, kP = 12};
    TRVector mX(kM, dn.X(), dn.Y(), dn.Z(), dr.X(), dr.Y(), dr.Z());  PrPP(mX);
    /* from maxima 02/21/2024 
 S - U = dU - dS 
 Col 1 = [ [(- bW*nZU) - bS*nZS + gW*nYU + gS*nYS + nXU - nXS] ]
 Col 2 = [ [aW*nZU + aS*nZS + nYU - nYS - gW*nXU - gS*nXS] ]
 Col 3 = [ [nZU - nZS - aW*nYU - aS*nYS - bW*nXU - bS*nXS] ]
 Col 4 = [ [(- xW) - xS + YU*gW + YS*gS - ZU*bW - ZS*bS + XU - XS] ]
 Col 5 = [ [(- yW) - yS - XU*gW - XS*gS + ZU*aW + ZS*aS + YU - YS] ]
 Col 6 = [ [(- zW) - zS - XU*bW - XS*bS - YU*aW - YS*aS + ZU - ZS] ]

JW2S : jacobian( [dev], [xS, yS, zS, aS, bS, gS, xW, yW, zW, aW, bW, gW] ); 
                  nX      nY       nZ     X      Y      Z     m/p
 Col 1 = [ [     [0]     [0]      [0]  [- 1]    [0]    [0] ] ] xS,
 Col 2 = [ [     [0]     [0]      [0]    [0]  [- 1]    [0] ] ] yS,
 Col 3 = [ [     [0]     [0]      [0]    [0]    [0]  [- 1] ] ] zS,
 Col 4 = [ [     [0]   [nZS]  [- nYS]    [0]   [ZS] [- YS] ] ] aS,
 Col 5 = [ [ [- nZS]     [0]  [- nXS] [- ZS]    [0] [- XS] ] ] bS,
 Col 6 = [ [   [nYS] [- nXS]      [0]   [YS] [- XS]    [0] ] ] gS,
 Col 7 = [ [     [0]     [0]      [0]  [- 1]    [0]    [0] ] ] xW,
 Col 8 = [ [     [0]     [0]      [0]    [0]  [- 1]    [0] ] ] yW,
 Col 9 = [ [     [0]     [0]      [0]    [0]    [0]  [- 1] ] ] zW,
 Col 10= [ [     [0]   [nZU]  [- nYU]    [0]   [ZU] [- YU] ] ] aW,
 Col 11= [ [ [- nZU]     [0]  [- nXU] [- ZU]    [0] [- XU] ] ] bW,
 Col 12= [ [   [nYU] [- nXU]      [0]   [YU] [- XU]    [0] ] ] gW,

    chi2 = (X - A*p)  G (X - A*p)T
    dchi2/dp = -A * G (X - A*p)T - (X - A*p) & G AT = 0
                A * G * XT + A * G * AT * pT + X * G * AT -

 `    */
    Double_t a[kM*kP] = { // 6x12
 //   0      1       2     3     4     5
 //  nX     nY      nZ     X     Y     Z  
      0,     0,      0,  - 1,    0,    0, // 0 xS,
      0,     0,      0,    0,  - 1,    0, // 1 yS,
      0,     0,      0,    0,    0,  - 1, // 2 zS,
      0,   nZS,  - nYS,    0,   ZS, - YS, // 3 aS,
  - nZS,     0,  - nXS, - ZS,    0, - XS, // 4 bS,
    nYS, - nXS,      0,   YS, - XS,    0, // 5 gS,
      0,     0,      0,  - 1,    0,    0, // 6 xW,
      0,     0,      0,    0,  - 1,    0, // 7 yW,
      0,     0,      0,    0,    0,  - 1, // 8 zW,
      0,   nZU,  - nYU,    0,   ZU, - YU, // 9 aW,
  - nZU,     0,  - nXU, - ZU,    0, - XU, //10 bW,
    nYU, - nXU,      0,   YU, - XU,    0, //11 gW,
    }; // A => AT
    TRMatrix A(kP, kM, a); PrPP(A);
    TRVector mGX(G,TRArray::kSxA,mX);  PrPP(mGX);
    TRVector AmX(A,TRArray::kAxB,mGX);  PrPP(AmX);
    TRSymMatrix SX(A,TRArray::kAxSxAT,G);   PrPP(SX);
    Double_t *array = LSF->GetArray() + 1;
    Double_t *amX = AmX.GetArray();
    Double_t *sX  = SX.GetArray();
    array[0]++;
    Int_t im = 1;
    Int_t is = im + NP;
    //    if (rS.Z() > 40 && rS.Z() < 200) {
      TCL::vadd(amX,array+im,array+im,NP); if (_debug) {TRVector XX(NP,array+im);  PrPP(XX);}
      TCL::vadd(sX,array+is,array+is,NPP); if (_debug) {TRSymMatrix S(NP,array+is);  PrPP(S);}
      array[NT+1] += G.Product(mX);        if (_debug) {PrPP(array[NT+1]);}
      //    }
    Double_t dw = w;
    Double_t ds = s;
    TRMatrix V(NwsPlots,3,
 mX(0), A( 4,0), ds, // {"dnXdbS",       "-nZS   => bS", 110,-1.100, 1.100,100,-0.005, 0.005}, // 0
 mX(0), A( 5,0), ds, // {"dnXdgS",       "nYS    => gS", 110,-1.100, 1.100,100,-0.005, 0.005}, // 1
 mX(0), A(10,0), dw, // {"dnXdbW",       "-nZU   => bW", 110,-1.100, 1.100,100,-0.005, 0.005}, // 2
 mX(0), A(11,0), dw, // {"dnXdgW",       "nYU    => gW", 110,-1.100, 1.100,100,-0.005, 0.005}, // 3
 mX(1), A( 3,1), ds, // {"dnYdaS",       "nZS    => aS", 110,-1.100, 1.100,100,-0.005, 0.005}, // 4
 mX(1), A( 5,1), ds, // {"dnYdgS",       "-nXS   => gS", 110,-1.100, 1.100,100,-0.005, 0.005}, // 5
 mX(1), A( 9,1), dw, // {"dnYdaW",       "nZU    => aW", 110,-1.100, 1.100,100,-0.005, 0.005}, // 6
 mX(1), A(11,1), dw, // {"dnYdgW",       "-nXU   => gW", 110,-1.100, 1.100,100,-0.005, 0.005}, // 7
 mX(2), A( 3,2), ds, // {"dnZdaS",       "-nYS   => aS", 110,-1.100, 1.100,100,-0.005, 0.005}, // 8
 mX(2), A( 4,2), ds, // {"dnZdbS",       "-nXS   => bS", 110,-1.100, 1.100,100,-0.005, 0.005}, // 9
 mX(2), A( 9,2), dw, // {"dnZdaW",       "-nYU   => aW", 110,-1.100, 1.100,100,-0.005, 0.005}, //10
 mX(2), A(10,2), dw, // {"dnZdbW",       "-nXU   => bW", 110,-1.100, 1.100,100,-0.005, 0.005}, //11
 mX(3), A( 4,3), ds, // {"dXdbS",        "-ZS    => bS", 100,-250.0, 9.999,100,-1.000, 1.000}, //12
 mX(3), A( 5,3), ds, // {"dXdgS",        "YS     => gS", 110,-1.100, 1.100,100,-1.000, 1.000}, //13
 mX(3), A(10,3), dw, // {"dXdbW",        "-ZU    => bW", 100,-250.0, 9.999,100,-1.000, 1.000}, //14
 mX(3), A(11,3), dw, // {"dXdgW",        "YU     => gW", 110,-1.100, 1.100,100,-1.000, 1.000}, //15
 mX(5), A( 3,5), ds, // {"dZdaS",        "-YS    => aS", 120,-175.0, -55.0,100,-0.005, 0.005}, //16
 mX(5), A( 4,5), ds, // {"dZdbS",        "-XS    => bS", 120, -60.0,  60.0,100,-1.000, 1.000}, //17
 mX(5), A( 9,5), dw, // {"dZdaW",        "-YU    => aW", 120,-175.0, -55.0,100,-0.005, 0.005}, //18
 mX(5), A(10,5), dw  // {"dZdbW",        "-XU    => bW", 120, -60.0,  60.0,100,-1.000, 1.000}  //19
	       ); PrPP(V);
    for (Int_t i = 0; i < NwsPlots; i++) plots3D[i]->Fill(V(i,2), V(i,1), V(i,0));
    if (Ntracks%10000 == 0) {cout << "read track no\t" << Ntracks << endl;}
    Ntracks++;
    //    if (Ntracks > 100000) break;
  }
  fOut->Write();

}
//________________________________________________________________________________
Double_t g2g(Double_t *xx, Double_t *par) {
  Double_t x = xx[0];
  Double_t A = TMath::Exp(par[0]);
  Double_t mu1  = par[1];
  Double_t sig1 = par[2];
  if (A < 1 && TMath::Abs(x -mu1) < 3*sig1) {TF1::RejectPoint(); return 0;}
  Double_t B    = TMath::Exp(par[3]);
  Double_t mu2  = par[4];
  Double_t sig2 = par[5];
  Double_t gra  = par[6];
  Double_t dev1 = (x - mu1)/sig1;
  Double_t dev2 = (x - mu2)/sig2;
  Double_t value = A*TMath::Exp(-0.5*dev1*dev1) + B*TMath::Exp(-0.5*dev2*dev2) + gra;
  return value;
}
//________________________________________________________________________________
void TDrawIO() {
  TMinuitMinimizer::UseStaticMinuit();
  if (! gMinuit) new TMinuit(10);
  gMinuit->SetPrintLevel(-2);
#if 1
  TF1 *gp = new TF1("gp",g2g,-100,100,7);
  struct Par_t {
    const Char_t *Name;
    Double_t p, pmin, pmax;
  };
  const Par_t par[7] = {
    {"logN1",    5.,    0.,   25.},
    {"mu1",      0.,   -1.,    1.},
    {"sigma1",0.01, 0.001,   0.10},
    {"logN2",    1.,    0.,   25.},
    {"mu2",      0.,   -1.,    1.},
    {"sigma2", 0.10,  0.01,    1.},
    {"grass",   0.0,  0.00,    1.}
  };
  for (Int_t i = 0; i < 7; i++) {
    gp->SetParName(i,par[i].Name);
    gp->SetParameter(i,par[i].p);
    gp->SetParLimits(i,par[i].pmin, par[i].pmax);
  }
#else
  TF1 *gp = new TF1("gp","gaus(0)",-100,100);
  gp->SetParameters(100.,0.,1.);
#endif
  Int_t nx = 24;
  Int_t ny = NFPlots;
  Int_t scaleX = 800/nx;
  Int_t scaleY = 600/ny;
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
      Int_t NP = array[0];
      if (NP > 0) {
	Double_t yTy = array[28];
	Int_t im = 1;
	Int_t is = im + 6;
	TRVector AmX(6,array+im);  // cout << "AmX " << AmX << endl;
	TRSymMatrix S(6,array+is); // cout << "S " << S << endl;
	//#define FREEZE_ALPHA_BETA
#ifdef  FREEZE_ALPHA_BETA
	for (Int_t i = 3; i < 5; i++) {
	  AmX(i) = 0;
	  for (Int_t j = 0; j < 5; j++) {
	    S(j,i) = 0;
	  }
	}
	// cout << "AmX " << AmX << endl;
	// cout << "S " << S << endl;
#else /* ! FREEZE_ALPHA_BETA */
	//#define FREEZE_BETA
#ifdef  FREEZE_BETA
	for (Int_t i = 4; i < 5; i++) {
	  AmX(i) = 0;
	  for (Int_t j = 0; j < 5; j++) {
	    S(j,i) = 0;
	  }
	}
	// cout << "AmX " << AmX << endl;
	// cout << "S " << S << endl;
#endif /* FREEZE_BETA */
#endif /* FREEZE_ALPHA_BETA */
	TRSymMatrix SInv(S,TRArray::kInverted);  // cout << "SInv " << SInv << endl;
	TRVector  X(SInv,TRArray::kSxA,AmX);     // cout << "X " << X << endl;
	Double_t chi2 = yTy;
	chi2 -= AmX*X;
	//	Double_t mSIm = SInv.Product(AmX); 
	// cout << "chi2 = " << chi2 << "/ NDF = " << NP << " mS-1m " << mSIm << endl;
	line = "";
	for (Int_t m = 0; m < 6; m++) {
	  if (SInv(m,m) > 0) {
	    Double_t scale = 1e4;   // => mkm
	    if (m > 2) scale = 1e3; // => mrad
	    ValA[m].val =  scale*X(m);
	    ValA[m].valError = scale*TMath::Sqrt(SInv(m,m));
	    ValA[m].iFlag = 1;
	  } else {
	    ValA[m].val = ValA[m].valError = 0; ValA[m].iFlag = 0;
	  }
	  line  += Form("|%7.2f+-%5.2f ", ValA[m].val,TMath::Min(99.99,ValA[m].valError)); 
	}
      }
    }
    cout << line << endl;
    out << line << endl;
    for (Int_t j = 0; j < NFPlots; j++) {
      TH3 *h3 = (TH3 *) gDirectory->Get(plotNameD[j].Name);
      if (! h3) continue;
      Int_t ij = j + 1 + ny*(i-1);
      c1->cd(ij)->SetLogz(1);
      TH1 *fit = 0;
      h3->GetXaxis()->SetRange(sector,sector);
      TH1 *sp = h3->Project3D("z");
      if (sp->GetEntries() < 100) continue;
      sp->Fit("gaus","qem");
      Double_t Mu = 0;
      Double_t dMu = 0;
      Mu = sp->GetFunction("gaus")->GetParameter(1);
      dMu = sp->GetFunction("gaus")->GetParError(1);
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
      if (fit) {
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
#if 1
	  Double_t xm = fit->GetMean();
	  Mu     = pol1->Eval(xm);
	  dMu    = TMath::Sqrt(pol1->GetParError(0)*pol1->GetParError(0) + (xm*pol1->GetParError(1))*(xm*pol1->GetParError(1)));
	  if (dMu > 99.99e-4) dMu=  99.99e-4;
#endif
	  slope  = pol1->GetParameter(1);
	  dslope = pol1->GetParError(1);
	  if (dslope > 99.99e-3) dslope = 99.99e-3;
	} else {
	  Mu = slope = 0;
	  dMu = dslope = 0;
	}
	Val_t Vals[6]; memset (Vals, 0, sizeof(Vals));
	static const Char_t *dxv[3] = {"dX", "dY","dZ"};
	TString Name(h->GetName());
	TString Title(h->GetTitle());
	for (Int_t m = 0; m < 3; m++) {
	  if (Name.BeginsWith(dxv[m]) && dMu > 0 && dMu < 99.99e-4) {
	    Vals[m].val =     -1e4*Mu;
	    Vals[m].valError = 1e4*dMu;
	    Vals[m].iFlag = 1;
	    lTitle += Form(" %s = %7.2f+-%5.2f (#mum)", dxv[m],Vals[m].val,TMath::Min(99.99,Vals[m].valError)); 
	  }
	}	  
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
	static const Char_t *lvar[6] = {"dx","dy","dz","#alpha","#beta","#gamma"};
	for (Int_t m = 0; m < 6; m++) {
	  if (dslope <= 0) continue;
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
//________________________________________________________________________________
void TDrawW2S() {
  TMinuitMinimizer::UseStaticMinuit();
  if (! gMinuit) new TMinuit(10);
  gMinuit->SetPrintLevel(-2);
#if 1
  TF1 *gp = new TF1("gp",g2g,-100,100,7);
  struct Par_t {
    const Char_t *Name;
    Double_t p, pmin, pmax;
  };
  const Par_t par[7] = {
    {"logN1",    5.,    0.,   25.},
    {"mu1",      0.,   -1.,    1.},
    {"sigma1",0.01, 0.001,   0.10},
    {"logN2",    1.,    0.,   25.},
    {"mu2",      0.,   -1.,    1.},
    {"sigma2", 0.10,  0.01,    1.},
    {"grass",   0.0,  0.00,    1.}
  };
  for (Int_t i = 0; i < 7; i++) {
    gp->SetParName(i,par[i].Name);
    gp->SetParameter(i,par[i].p);
    gp->SetParLimits(i,par[i].pmin, par[i].pmax);
  }
#else
  TF1 *gp = new TF1("gp","gaus(0)",-100,100);
  gp->SetParameters(100.,0.,1.);
#endif
  Int_t nx = 24;
  Int_t ny = NwsFPlots;
  Int_t scaleX = 800/nx;
  Int_t scaleY = 600/ny;
  //  Int_t scale  = TMath::Min(scaleX,scaleY);
  TCanvas *c1 = new TCanvas("TpcWS","Tpc Sector to Sector Alignment" ,10,10,10+scaleX*nx,10+scaleY*ny);
  cout << "nx/ny = " << nx << "/" << ny << endl;
  c1->Divide(ny,nx);
  TString line("");
  TString lTitle("");
  TString lineC("");
  ofstream out;
  ofstream outC;
  TString Out("Results.W2S_NoLSFg5");
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
  Val_t ValG[7]; memset (ValG, 0, sizeof(ValG));
  TH1D *LSF = (TH1D *) gDirectory->Get("LSF");
  Double_t *array = LSF->GetArray() + 1;
  Int_t NEntries = array[0];
  if (NEntries  < 1000) return;
  Int_t NP  = 6*24; // Total no. of parameters
  Int_t NPP = NP*(NP+1)/2; // size of matrix
  Int_t NT  = NP + NPP; // bin0 -> no. of entries; bin_NT+1 = chi2
  Double_t yTy = array[NT+1];
  Int_t im = 1;
  Int_t is = im + NP;
  TRVector AmX(NP,array+im);  PrPP(AmX);
  TRSymMatrix S(NP,array+is); PrPP(S);
#if 0
  TRSymMatrix SInv(S);
  Int_t iFail = TRSymMatrix::TrchLU(S.GetArray(),SInv.GetArray(),5);
  if (iFail) {
    cout << "TRSymMatrix Invertion failed" << endl;
    SInv = TRSymMatrix(S,TRArray::kInvertedPosDef);  PrPP(SInv);
  } else {
    SInv = TRSymMatrix(S,TRArray::kInverted);  PrPP(SInv);
  }
#else
  TRSymMatrix SInv(S,TRArray::kInverted); PrPP(SInv);
  if (_debug) {
    TRSymMatrix P(NP);
    for (Int_t i = 0; i < NP; i++)
      for (Int_t j = 0; j < NP; j++) {
	P(i,j) = 0;
	for (Int_t k = 0; k < NP; k++)
	  P(i,j) += SInv(i,k)*S(k,j);
      }
    PrPP(P);
  }
#endif
  TRVector  X(SInv,TRArray::kSxA,AmX);     PrPP(X);
  Double_t chi2 = yTy;
  chi2 -= AmX*X; PrPP(chi2);
  Int_t head = 0;
  for (Int_t i = 1; i <= nx; i++) {
    Int_t sector = i;
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
	  ValA[m].iFlag = 1; // 0, No LSF1;
	} else {
	  ValA[m].val = ValA[m].valError = 0; ValA[m].iFlag = 0;
	}
	if (m < 3) 
	  line  += Form("|%8.2f+-%6.2f ", TMath::Max(-9999.99,TMath::Min( 9999.99,ValA[m].val)),TMath::Min(999.99,ValA[m].valError)); 
	else
	  line  += Form("|%7.2f+-%5.2f ", ValA[m].val,TMath::Min(99.99,ValA[m].valError)); 
	ValA[m].val = ValA[m].valError = 0; ValA[m].iFlag = 0;
      }
    }
    cout << line << endl;
    out << line << endl;
#endif
    for (Int_t j = 0; j < NwsPlots; j++) {
      TH3 *h3 = (TH3 *) gDirectory->Get(plotNameWS[j].Name);
      if (! h3) continue;
      Int_t ij = j + 1 + ny*(i-1);
      c1->cd(ij)->SetLogz(1);
      TH1 *fit = 0;
      h3->GetXaxis()->SetRange(sector,sector);
      TH1 *sp = h3->Project3D("z");
      if (sp->GetEntries() < 100) continue;
      //      sp->Fit("gaus","qem");
      sp->Fit("gaus","qem");
      Double_t Mu = 0;
      Double_t dMu = 0;
      Mu = sp->GetFunction("gaus")->GetParameter(1);
      dMu = sp->GetFunction("gaus")->GetParError(1);
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
      if (fit) {
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
	  Mu     = pol1->GetParameter(0);
	  dMu    = pol1->GetParError(0);
#else
	  Double_t xm = fit->GetMean();
	  Mu     = pol1->Eval(xm);
	  dMu    = TMath::Sqrt(pol1->GetParError(0)*pol1->GetParError(0) + (xm*pol1->GetParError(1))*(xm*pol1->GetParError(1)));
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
#define __AVERAGE_WS__
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
	  line  += "|               ";
	else 
	  line  += "|                ";
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
	if (ValG[m].valError > 0) 
	  w1 = 1./(ValG[m].valError*ValG[m].valError);
	ValG[m].val = (w0*ValA[m].val + w1*ValG[m].val)/(w0 + w1);
	ValG[m].valError = 1./TMath::Sqrt(w0 + w1);
	ValG[m].iFlag++;
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
      if (m > 2) {
	line  += Form("|%7.2f+-%5.2f ", ValG[m].val,TMath::Min(99.99,ValG[m].valError)); 
	lineC += Form(",%7.2f,%5.2f", ValG[m].val,TMath::Min(99.99,ValG[m].valError)); 
      } else {
	line  += Form("|%8.2f+-%6.2f ", TMath::Max(-9999.99,TMath::Min( 9999.99,ValG[m].val)),TMath::Min(999.99,ValG[m].valError)); 
	lineC += Form(",%8.2f,%6.2f", ValG[m].val,TMath::Min(999.99,ValG[m].valError)); 
      }
    }
  }
  cout << line << endl;
  out << line << endl;
  out.close();
}
//________________________________________________________________________________
void TpcAlignerDraw(Int_t jcase = 0, const Char_t *files = "../*Aligner.root") {
  switch (jcase) {
  case 0: TpcAlignerDrawIO(files);  break;
  case 1: TpcAlignerDrawW2S(files); break;
  case 2: TDrawIO();                break;
  case 3: TDrawW2S();               break;
  default:
    break;
  };
}
