#ifndef __CINT__
#include "Riostream.h"
#include "TMatrixD.h"
#include "TVectorD.h"
#include "TGraphErrors.h"
#include "TDecompChol.h"
#include "TDecompSVD.h"
#include "TF1.h"
#endif
void twist() {
#ifdef __CINT__
  gSystem->Load("libMatrix");
#endif
  Double_t eps = 1.e-12;
  // Solve A[NP,NV]  * x{NV} = y[NP];
#if 0 /* all independent */
  const Int_t NV = 8;
#else /* FR vs FF */
  const Int_t NV = 4;
#endif
  const Int_t NP = 8;
  Double_t C1 = -0.37021;
  Double_t C2 = 0.838536;
  /*  MuDst->Draw("GlobalTracks.mLastPoint.mX3:GlobalTracks.mFirstPoint.mX3","GlobalTracks.mVertexIndex==0","colz")
  <Z>  = MuDst->Draw("(GlobalTracks.mLastPoint.mX3+GlobalTracks.mFirstPoint.mX3)/2","GlobalTracks.mVertexIndex==0","colz")
  <dZ> = MuDst->Draw("abs(GlobalTracks.mLastPoint.mX3-GlobalTracks.mFirstPoint.mX3)/2","GlobalTracks.mVertexIndex==0","colz")
  RF/7p7GeV_2021_WestOff/063/22063019/st_physics_22063019_raw_5000004.MuDst.root <Z> = -90;   <dZ> = 40
  FF/7p7GeV_2021_WestOff/062/22062035/hlt_22062035_11_01_000.MuDst.root          <Z> = -90;   <dZ> = 26
  RF/7p7GeV_2021_EastOff/063/22063019/st_physics_22063019_raw_5000004.MuDst.root <Z> =  88;   <dZ> = 38.6
  FF/7p7GeV_2021_EastOff/062/22062035/hlt_22062035_11_01_000.MuDst.root          <Z. =  88;   <dZ> = 30
   */
  Double_t Z = 90;
  /*
    (West - East RF)/2                                7p7GeV_2021
    dX_West_East = (  C2 * beta + C1 * alpha ) * Z =  8.19131e-04 +/-  2.52889e-04
    dY_West_East = (  C1 * beta - C2 * alpha ) * Z =  8.69316e-02 +/-  2.46744e-04
    (West - East FF)/2
    dX_West_East = (  C2 * beta - C1 * alpha ) * Z =  7.44167e-02 +/-  1.41976e-03
    dY_West_East = (- C1 * beta - C2 * alpha ) * Z =  1.48260e-02 +/-  1.38702e-03
    
    /(West - East RF)/2                                OO200_2021 
    dX_West_East = (  C2 * beta + C1 * alpha ) * Z =  -8.55745e-04 +/-  5.18769e-04   
    dY_West_East = (  C1 * beta - C2 * alpha ) * Z =   8.52597e-02 +/-  4.99806e-04
    (West - East FF)/2
    dX_West_East = (  C2 * beta - C1 * alpha ) * Z =   7.16109e-02 +/-  2.24580e-04
    dY_West_East = (- C1 * beta - C2 * alpha ) * Z =   1.26663e-02 +/-  2.13613e-04
  */
  //           7p7GeV RF dX         dY        FF    dX          dY      OO200    dX           dY FF        dX           dY
  Double_t ay[] = {8.19131e-04, 8.69316e-02, 7.44167e-02, 1.48260e-02, -8.55745e-04, 8.52597e-02, 7.16109e-02, 1.26663e-02};
  Double_t ae[] = {2.52889e-04, 2.46744e-04, 1.41976e-03, 1.38702e-03,  5.18769e-04, 4.99806e-04, 2.24580e-04, 2.13613e-04};
  TVectorD y; y.Use(NP,ay);
  TVectorD e; e.Use(NP,ae);
  cout << "y\t"; y.Print();
  cout << "e\t"; e.Print();
  TMatrixD A(NP,NV);
  // alpha         beta
#if 0 /* all independent */
  A(0,0) =   C1; A(0,1) =   C2; // RF  (  C2 * beta + C1 * alpha )
  A(1,0) = - C2; A(1,1) =   C1; //     (  C1 * beta - C2 * alpha )        
  A(2,2) = - C1; A(2,3) =   C2; // FF  (  C2 * beta - C1 * alpha ) 
  A(3,2) = - C2; A(3,3) = - C1;	//     (- C1 * beta - C2 * alpha ) 
  A(4,4) =   C1; A(4,5) =   C2; // RF
  A(5,4) = - C2; A(5,5) =   C1;
  A(6,6) = - C1; A(6,7) =   C2; // FF
  A(7,6) = - C2; A(7,7) = - C1;
#else /* FR vs FF */
  A(0,0) =   C1; A(0,1) =   C2; // RF  (  C2 * beta + C1 * alpha )
  A(1,0) = - C2; A(1,1) =   C1; //     (  C1 * beta - C2 * alpha )        
  A(2,2) = - C1; A(2,3) =   C2; // FF  (  C2 * beta - C1 * alpha ) 
  A(3,2) = - C2; A(3,3) = - C1;	//     (- C1 * beta - C2 * alpha ) 
  A(4,0) =   C1; A(4,1) =   C2; // RF OO 
  A(5,0) = - C2; A(5,1) =   C1;
  A(6,2) = - C1; A(6,3) =   C2; // FF
  A(7,2) = - C2; A(7,3) = - C1;
#endif
  A *= Z;
  cout << "A\t"; A.Print();
#if 0
  cout << " - 1. solve through Normal Equations" << endl;

  const TVectorD c_norm = NormalEqn(A,y,e);
  cout << "c_norm\t"; c_norm.Print();
#endif
  cout << " - 2. solve through SVD" << endl;
  // numerically  preferred method

  // first bring the weights in place
  TMatrixD Aw = A;
  TVectorD yw = y;
  for (Int_t irow = 0; irow < A.GetNrows(); irow++) {
    TMatrixDRow(Aw,irow) *= 1/e(irow);
    yw(irow) /= e(irow);
  }
  cout << "yw\t"; yw.Print();
#if 0
  TDecompSVD svd(Aw);
  Bool_t ok;
  const TVectorD c_svd = svd.Solve(yw,ok);
  cout << "c_svd\t"; c_svd.Print();
  cout << " - 3. solve with pseudo inverse" << endl;

  const TMatrixD pseudo1  = svd.Invert();
  cout << "pseudo1 = svd.Invert();\t"; pseudo1.Print();
  TVectorD c_pseudo1 = yw;
  c_pseudo1 *= pseudo1;
  cout << "c_pseudo1\t"; c_pseudo1.Print();
#endif
  cout << " - 4. solve with pseudo inverse, calculated brute force" << endl;

  TMatrixDSym AtA(TMatrixDSym::kAtA,Aw);
  cout << "AtA\t"; AtA.Print();
  const TMatrixD AtAI = AtA.Invert();
  cout << "AtAI\t"; AtAI.Print();
  const TMatrixD pseudo2 =  AtAI* Aw.T();
  TVectorD c_pseudo2 = yw;
  c_pseudo2 *= pseudo2;
  TVectorD rotmrad = c_pseudo2;
  rotmrad *= 1000;
  cout << "rot (mrad)\t"; rotmrad.Print();
  TVectorD res = A * c_pseudo2 - y;
  TVectorD resmkm = 10000.*res;
  cout << "res (mkm)\t"; resmkm.Print();
  Double_t chi2 = 0;
  for (Int_t i = 0; i < NP; i++) chi2 += (res[i]*res[i])/(e(i)*e(i));
  cout << "chi2 = " << chi2 << endl;

#if 0
  cout << " - 5. Minuit through TGraph" << endl;

  TGraphErrors *gr = new TGraphErrors(NP,ax,ay,0,ae);
  TF1 *f1 = new TF1("f1","pol1",0,5);
  gr->Fit("f1","Q");
  TVectorD c_graph(NV);
  c_graph(0) = f1->GetParameter(0);
  c_graph(1) = f1->GetParameter(1);

  // Check that all 4 answers are identical within a certain
  // tolerance . The 1e-12 is somewhat arbitrary . It turns out that
  // the TGraph fit is different by a few times 1e-13.
  Bool_t same = kTRUE;
  same &= VerifyVectorIdentity(c_norm,c_svd,0,eps);
  same &= VerifyVectorIdentity(c_norm,c_pseudo1,0,eps);
  same &= VerifyVectorIdentity(c_norm,c_pseudo2,0,eps);
  same &= VerifyVectorIdentity(c_norm,c_graph,0,eps);
  if (same)
    cout << " All solutions are the same within tolerance of " << eps << endl;
  else
    cout << " Some solutions differ more than the allowed tolerance of " << eps << endl;
#endif
}
