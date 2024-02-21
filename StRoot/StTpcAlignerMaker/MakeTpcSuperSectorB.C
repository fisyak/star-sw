/*  Tpc Super Sector Position based on MuTpcG.C.check TFGflag in lDb.C
    root.exe 'lDb.C(0)' MakeTpcSuperSectorB.C+
    > MakeSuperSectorPositionB()
*/
#if !defined(__CINT__)
// code that should be seen ONLY by the compiler
#else
#if !defined(__CINT__) || defined(__MAKECINT__)
// code that should be seen by the compiler AND rootcint
#else
// code that should always be seen
#endif
#endif
//________________________________________________________________________________
#if !defined(__CINT__) || defined(__MAKECINT__)
#include <stdio.h>
#include <string.h>
#include "Riostream.h"
#include "TString.h"
#include "TMath.h"
#include "TROOT.h"
#include "TSystem.h"
#include "TH1.h"
#include "TStyle.h"
#include "TGraph.h"
#include "TNtuple.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TFile.h"
#include "TNamed.h"
#include "THStack.h"
#include "StChain.h"
#include "tables/St_Survey_Table.h"
#include "TGeoMatrix.h"
#include "StTpcDb/StTpcDb.h"
#include "StEvent/StEnumerations.h"
#include "StDetectorDbMaker/StTpcSurveyC.h"
#include "TGraphErrors.h"
#include "TMultiGraph.h"
#include "TGeoMatrix.h"
#endif
#include "StTpcAlignerMaker/SurveyPass.h"
const Int_t N = 24;
SurveyPass_t Passes[] = {
  //#include  "StTpcAlignerMaker/W2S_Pass28_Avg.h"
  //#include  "W2S_Pass30_Avg.h"
  //#include  "W2S_Pass32_Avg.h"
  //#include  "W2S_Pass33_Avg.h"
  //#include  "W2S_Pass34_Avg.h"
  //#include  "W2S_Pass36_Avg.h"
  //#include  "W2S_Pass37_Avg.h"
  //#include  "W2S_Pass40_Avg.h"
  //#include  "W2S_Pass41_Avg.h"
  //#include  "W2S_Pass42_Avg.h"
  //#include  "W2S_Pass51_Avg.h"
#include  "W2S_Pass51_Avg.h" /* __INVERSE_dR__ */
};
//#define  __INVERSE_dR__
const  Int_t NP = sizeof(Passes)/sizeof(SurveyPass_t);
  
//________________________________________________________________________________

TCanvas *c1 = 0;
StMaker *dbMk = 0;
StChain *chain = 0;
static THStack *hs[6];
static TLegend *leg[6];
static const Double_t scale = 1.0;
static TGeoHMatrix dR[48], dRC[48];
static TGeoHMatrix Rideal[24], RidealI[24];
static Int_t _debug = 0;
#define PrPP(B) if (_debug) {cout  << (#B) << " = \t";  (B).Print();}
#define PrPI(i,B) if (_debug) {cout  << (#B) << "( i = " << i << ")  = \t";  (B).Print();}
///________________________________________________________________________________
void RemoveOverAllShift(SurveyPass_t &Pass) {
#if 0
  for (Int_t i = 0; i < 24; i++) {
    cout << "dR[" << i << "]"; dR[i].Print();
    cout << "dRC[" << i << "]"; dRC[i].Print();
    cout << "Rideal[" << i << "]"; Rideal[i].Print();
    cout << "RidealI[" << i << "]"; RidealI[i].Print();
  }
#endif
  /* Euler angles: a = phi, b = theta, g = psi
                  (  1 -(a+g)  0)   
     R(a,b,g) =   (a+g      1 -b) = 
                  (  0      b  1)
   ( cospsi*cosphi - costhe*sinphi*sinpsi;   -sinpsi*cosphi - costhe*sinphi*cospsi;    sinthe*sinphi;)
   ( cospsi*sinphi + costhe*cosphi*sinpsi;   -sinpsi*sinphi + costhe*cosphi*cospsi;   -sinthe*cosphi;) =
   (                        sinpsi*sinthe;                           cospsi*sinthe;           costhe;) 

   (       1; -psi-phi;    0;
   ( phi+psi;        1; -the;) =  psi = 0
   (       0;      the;    1;) 


   (   1;  -(a+g);   0;)
   ( a+g;      1;   -b;) =
   (   0;;     b;    1;) 

   Tait–Bryan angles:      dR.RotateX(a); dR.RotateY(b); dR.Rotate(g);

                            ( 1  -g  b dx)       (nx)              (   nx +g*ny -b*nz)        (x)           (  x - g*y )
      dR(a,b,g,dx,dy,dz) =  ( g   1 -a dy); n =  (ny);   dR x n =  (-g*nx +  ny +a*nz);   X = (y); dR x X = (dy)
                            (-b   a  1 dz)       (nz)		   ( b*nx -a*ny +  nz)        (z)           (dz)
		            ( 0   0  0  1)       ( 0) 		   ( 0               )        (1)           ( 1)

			    Euler <=> Tait–Bryan : a+g <=> g; b <=> a; 0 <=> b;
Euler Rotation in Tait-Bryan angles

   (   1;  -g;   0;)
   (   g;   1;  -a;) =
   (   0;;  a;   1;) 
=========              T = Sup2TPC; dRi = I, Rold 
    dRAv = <dTPCreal * dTPCideal^-1> = <T * dRreal * T^-1> = <T *dRr * T^-1> = dRAv; 
    Rtpc * dRAv^-1 = T * dRr * dRAv^-1
    T^-1 * dRAv * T= dRr * dRi^-1 
========
    A    = <T * dR * C * T^-1>; dR * C = 
    D    =  T * dR;  D * A^-1 = T * dR * A^-1 = T * dR *  
   */
  // Calculate average shift and rotation for each half of TPC and overall TPC
  Double_t phi[24] = {0};
  Double_t theta[24] = {0};
  Double_t psi[24] = {0};
  Double_t tra[24][3] = {0};
  for (Int_t i = 0; i < 24; i++) {
    /*
      dR.RotateX(a); dR.RotateY(b); dR.Rotate(g);

                            ( 1  -g  b dx)       (nx)              (   nx +g*ny -b*nz)        (x)           (  x - g*y )
      dR(a,b,g,dx,dy,dz) =  ( g   1 -a dy); n =  (ny);   dR x n =  (-g*nx +  ny +a*nz);   X = (y); dR x X = (dy)
                            (-b   a  1 dz)       (nz)		   ( b*nx -a*ny +  nz)        (z)           (dz)
		            ( 0   0  0  1)       ( 0) 		   ( 0               )        (1)           ( 1)
     */
    StBeamDirection part = east;
    if (i < 12) part = west;
    Double_t xyz[3];
    xyz[0] = 1e-4*Pass.Data[i].x*scale;
    xyz[1] = 1e-4*Pass.Data[i].y*scale;
    xyz[2] = 1e-4*Pass.Data[i].z*scale;
    //#define __SWAP_SIGNS__  /* Pass 508 */
#ifdef __SWAP_SIGNS__
    Pass.Data[i].alpha *= -1.;
    Pass.Data[i].beta  *= -1.;
    Pass.Data[i].gamma *= -1.;
#endif
    dR[i] = TGeoHMatrix();
#define __ROTATION__
#ifdef __ROTATION__
#if 1
    dR[i].RotateX( TMath::RadToDeg()*Pass.Data[i].alpha*1e-3*scale);
    dR[i].RotateY( TMath::RadToDeg()*Pass.Data[i].beta*1e-3*scale); 
#endif
    dR[i].RotateZ( TMath::RadToDeg()*Pass.Data[i].gamma*1e-3*scale);  // swap sign 03/13/19
#endif /* __ROTATION__ */
    dR[i].SetTranslation(xyz);
    Rideal[i]     = StTpcDb::instance()->SupS2Glob(i+1); PrPI(i,Rideal[i]); // cout << "Ideal:"; Rideal[i].Print();
    RidealI[i]    = Rideal[i].Inverse();                 PrPI(i,RidealI[i]); //cout << "Inverse:"; RidealI[i].Print();
    TGeoHMatrix Rreal      = StTpcDb::instance()->SupS2Glob(i+1)*dR[i];  PrPP(Rreal); //cout << "Real:"; Rreal.Print();
    TGeoHMatrix R = Rreal * RidealI[i];         PrPP(R); // cout <<"Diff:"; R.Print();
    const Double_t *xyzR = R.GetTranslation();
    for (Int_t j = 0; j < 3; j++) tra[i][j] = xyzR[j];
#if 0
    TGeoRotation RR(R);
    RR.GetAngles(phi[i],theta[i],psi[i]); 
#else
    Double_t *m = R.GetRotationMatrix();
    theta[i] = TMath::ACos(m[8])*TMath::RadToDeg();
    phi[i]   = TMath::ATan2(-m[8]*m[1],m[0])*TMath::RadToDeg();
    psi[i]   = 0.; // convention, phi+psi matters
#endif
    cout << " sec " << i+1 << " phi " << phi[i] << " theta " << theta[i] << " psi " << psi[i] << endl;
  }
  Double_t dphi[3] = {0}, dtheta[3] = {0}, dpsi[3] = {0}, dxyz[3][3] = {0};
  TGeoHMatrix RAv[3], RAvI[3];
  for (Int_t l = 0; l < 3; l++) {
    Int_t i1 = 0, i2 = 24;
    if      (l == 0) {i2 = 12;}
    else if (l == 1) {i1 = 12;}
    Int_t N = i2 - i1;
    for (Int_t i = i1; i < i2; i++) {
      dphi[l]   += phi[i]/N;
      dtheta[l] += theta[i]/N;
      dpsi[l]   += psi[i]/N;
      for (Int_t j = 0; j < 3; j++)dxyz[l][j] += tra[i][j]/N;
    }
    TGeoRotation RR;
    RR.SetAngles(dphi[l], dtheta[l], dpsi[l]);
    RAv[l] = TGeoHMatrix();
    RAv[l].SetRotation(RR.GetRotationMatrix());
    RAv[l].SetTranslation(dxyz[l]);
    if (l == east) cout << "east:";
    else if (l == west) cout << "west:";
    else                cout << "Tpc:";
    PrPI(l,RAv[l]); // RAv[l].Print();
    RAvI[l] = RAv[l].Inverse(); PrPI(l,RAvI[l]); // cout << "Inverse:"; RAvI[l].Print("");
  }
  for (Int_t i = 0; i < 24; i++) {
    StBeamDirection part = east;
    if (i < 12) part = west;
    //    cout << "dR" << i << ":"; dR[i].Print("");
    /*
      RAV = <Rideal*dR*Rideal^1>; dRAv = Rideal
      RA  = Rideal*dR
      RA*dRAV^-1   = Rideal*dR*<Rideal*dR*Rideal^1>^-1 = Rideal*dR *(
      T*dR * T^-1 * RAv^-1 * T

      g = T * l;
      A = g * T^-1 = T * l * T^-1
      A = g * C^-1; g = A * C = 

      
     */
    //#define __ACCOUNT_OFFSET__
#ifdef __ACCOUNT_OFFSET__
    TGeoHMatrix A = RidealI[i] * RAvI[part] * Rideal[i]; PrPP(A); // cout << "A\t:"; A.Print();
    dRC[i] = dR[i]*A ; //cout << "dRC:"; dRC[i].Print("");
    cout << "sec = " << i+1 << " before:"; Pass.Data[i].Print();
    Pass.Data[i].x = dRC[i].GetTranslation()[0]*1e4/scale;
    Pass.Data[i].y = dRC[i].GetTranslation()[1]*1e4/scale;
    Pass.Data[i].z = dRC[i].GetTranslation()[2]*1e4/scale;
    Pass.Data[i].alpha = -dRC[i].GetRotationMatrix()[5]*1e3/scale;
    Pass.Data[i].beta  =  dRC[i].GetRotationMatrix()[2]*1e3/scale;
    Pass.Data[i].gamma = -dRC[i].GetRotationMatrix()[1]*1e3/scale;
    cout << "sec = " << i+1 << " after :"; Pass.Data[i].Print();
    cout << "================================================================================" << endl;
#else
    dRC[i] = dR[i];
#endif
  }
}
//________________________________________________________________________________
void MakeSuperSectorPositionBTable(SurveyPass_t Pass, TString opt = "B"){
  RemoveOverAllShift(Pass);
  const Char_t *plots[3] = {"dXS","dYS","dZS"};
#if 0  
  for (Int_t j = 1; j <= 24; j++) {
    cout << Form("%2i ",j); Pass.Data[j-1].Print();
  }
#endif
  St_SurveyC   *chair = 0;
  if      (opt == "B") chair = St_SurveyC::instance("TpcSuperSectorPosition");
  else if (opt == "D") chair = St_SurveyC::instance("TpcSuperSectorPositionD");
  else {
    cout "chair for TpcSuperSectorPosition" << opt.Data() << " has not been found" << endl;
    return;
  }
  St_Survey *TpcSuperSectorPositionB = chair->Table(); //chain->GetDataBase("Geometry/tpc/TpcSuperSectorPositionB");
  if (! TpcSuperSectorPositionB)  {cout << "TpcSuperSectorPosition" << opt.Data() << "  has not been found"  << endl; return;}
  Int_t Nrows = TpcSuperSectorPositionB->GetNRows();
  TpcSuperSectorPositionB->Print(0,Nrows);
  TGeoHMatrix GL;
  Survey_st *TpcSuperSectorOld         = TpcSuperSectorPositionB->GetTable();        
  Survey_st row[24];
  /* 
     Rav = R * dR => R^-1 * Rav =  dR
     
   */
  for (Int_t i = 0; i < 24; i++) {
    Int_t l = i;
    StBeamDirection part = east;
    if (i < 12) part = west;
    if (l < Nrows) {
      row[i] = TpcSuperSectorOld[i];
      GL.SetRotation(&TpcSuperSectorOld[i].r00);
      GL.SetTranslation(&TpcSuperSectorOld[i].t0); if (_debug) {cout << "s: " << i+1 << " GL\t"; GL.Print();}
    } else {
      GL = *gGeoIdentity;
    }
    Double_t dxyz[3], drot[3];
    dxyz[0] = 1e-4*Pass.Data[i].Dx;
    dxyz[1] = 1e-4*Pass.Data[i].Dy;
    dxyz[2] = 1e-4*Pass.Data[i].Dz;
    drot[0] = Pass.Data[i].Dalpha*1e-3;
    drot[1] = Pass.Data[i].Dbeta*1e-3; 
    drot[2] = Pass.Data[i].Dgamma*1e-3;
    memcpy(&row[l].sigmaRotX, drot, 3*sizeof(Double_t));
    memcpy(&row[l].sigmaTrX, dxyz, 3*sizeof(Double_t));
    Double_t xyz[3];
    xyz[0] = 1e-4*Pass.Data[i].x*scale;
    xyz[1] = 1e-4*Pass.Data[i].y*scale;
    xyz[2] = 1e-4*Pass.Data[i].z*scale;
    dR[l] = TGeoHMatrix();
#ifdef __ROTATION__
#if 1
    dR[l].RotateX( TMath::RadToDeg()*Pass.Data[i].alpha*1e-3*scale);
    dR[l].RotateY( TMath::RadToDeg()*Pass.Data[i].beta*1e-3*scale); 
#endif
    dR[l].RotateZ( TMath::RadToDeg()*Pass.Data[i].gamma*1e-3*scale);  // swap sign 03/13/19
#endif /* __ROTATION__ */
    dR[l].SetTranslation(xyz);
#ifndef __INVERSE_dR__ /* try inverse for Rass 51 => Pass53 */
    dRC[l] = dR[l];
#else
    dRC[l] = dR[l].Inverse();
#endif
    if (_debug) {
      cout << "Additional rotation for Super Sector\t"; dR[l].Print();
      cout << "dR" << i << ":"; dR[l].Print("");
      cout << "dRC" << i << ":"; dRC[l].Print("");
    }
    //    TGeoHMatrix dRC = dR[l]*RAvI[part]; cout << "dRC:"; dRC.Print("");
    //    TGeoHMatrix GLnew = StTpcDb::instance()->Flip().Inverse()*dR[l]*StTpcDb::instance()->Flip()*GL; GLnew.Print(); // Flip 03/14/19
    //    TGeoHMatrix GLnew = GL*dR[l]; GLnew.Print(); // used till 03/13/19 and after 03/15/19
    TGeoHMatrix GLnew = GL*dRC[l]; GLnew.Print(); // used till 03/13/19 and after 03/15/19
    //    TGeoHMatrix GLnew = dR[l] * GL; GLnew.Print();
    Double_t *R = GLnew.GetRotationMatrix();
    memcpy(&row[l].r00, R, 9*sizeof(Double_t));
    Double_t *tr = GLnew.GetTranslation();
    memcpy(&row[l].t0, tr, 3*sizeof(Double_t));
  }
  Int_t date = Pass.date;
  Int_t time = Pass.time;
#ifndef __INVERSE_dR__ /* try inverse for Rass 51 => Pass53 */
  TString fOut =  Form("TpcSuperSectorPosition%s.%8i.%06i.C", opt,Data(), date, time);
#else
  TString fOut =  Form("TpcSuperSectorPosition%s.%8i.%06i.C.Inverse", opt.Data(), date, time);
#endif
  ofstream out;
  cout << "Create " << fOut.Data() << endl;
  out.open(fOut.Data());
  out << "TDataSet *CreateTable() {" << endl;
  out << "  if (!gROOT->GetClass(\"St_Survey\")) return 0;" << endl;
  out << "  Survey_st row[24] = {" << endl; 
  out << "    //             -gamma     beta    gamma            -alpha    -beta    alpha                x0       y0       z0" << endl;
  for (Int_t i = 0; i < 24; i++) {
    Int_t l = i;
    out << "    {" << Form("%2i",i+1) << ","; 
    Double_t *r = &(row[l].r00);
    //    cout << " ";
    for (Int_t j =  0; j <  9; j++) out << Form("%8.5f,",r[j]);
    //    cout << " ";
    for (Int_t j =  9; j < 12; j++) out << Form("%8.4f,",r[j]); 
    cout << " ";
    for (Int_t j = 12; j < 18; j++) out << Form("%8.5f,",r[j]);
    //    out << "\"" << Pass.PassName << "\"}";
    out << "\"" << Pass.Data[i].Comment << "\"}";
    if (i != 23) out << ",";
    out << endl;
  }
  cout << endl;
  out << "  };" << endl;
  out << "  St_Survey *tableSet = new St_Survey(\"TpcSuperSectorPosition" << opt.Data() << "\",24);" << endl; 
  out << "  for (Int_t i = 0; i < 24; i++) tableSet->AddAt(&row[i].Id);" << endl;
  out << "  return (TDataSet *)tableSet;" << endl;
  out << "}" << endl;
  out.close(); 
}
//________________________________________________________________________________
void MakeTpcSuperSectorB(const Char_t *opt="") {
  chain = (StChain *) StChain::GetChain();
  if (! chain) return;
  dbMk = chain->Maker("db");
  if (! dbMk) return;
  dbMk->SetDebug(1);
#if 0
  static Bool_t InitDone = kFALSE;
  if (! InitDone) {
    chain->Init();
    InitDone = kTRUE;
  }
#endif
  gStyle->SetMarkerStyle(20);
  gStyle->SetOptStat(0);
  cout << "NP \t" << NP << endl;
  Int_t NH = NP;
  if (NH == 2) NH += 2; // make average if we have only (FF + RF)/2 for SuperSector, and (FF - RF) for Inner Sector
  TH1D ***dath = new TH1D**[NH]; 
  for (Int_t p = 0; p < NH; p++) {dath[p] = new TH1D*[6]; memset(dath[p],0, 6*sizeof(TH1D*));}
  const Char_t *names[6] = {" #Deltax"," #Deltay"," #Deltaz"," #Delta #alpha"," #Delta #beta"," #Delta #gamma"};
  const Char_t *nameK[6] = {"Dx","Dy","Dz","Da",     "Db",    "Dg"};
  const Char_t *NameO[3] = {"", "sum", "dif"};
  TString Opt(opt);
  TFile *fOut = new TFile("MakeTpcSuperSectorB.root","recreate");
  for (Int_t i = 0; i < 6; i++) {
    hs[i] = new THStack(nameK[i],names[i]);
    fOut->Add(hs[i]);
#if 0
    if (i < 3) hs[i]->SetYTitle(Form("%s (#mum)",names[i]));
    else       hs[i]->SetYTitle(Form("%s (mrad)",names[i]));
    hs[i]->SetXTitle("sector");
#endif
    if (! i)     leg[i] = new TLegend(0.10,0.65,0.30,0.90);
    else         leg[i] = 0;
  }
  TString same("e");
  TH1::SetDefaultSumw2(kTRUE);
  for (Int_t k = 0; k < NP; k++) {
    cout << "Passes[" << k << "] before removing offset" << endl;
    if (_debug) {Passes[k].Print();}
    Int_t date = Passes[k].date;
    Int_t time = Passes[k].time;
    if (! dbMk) return;
    dbMk->SetDateTime(date,time);
#if 0
    RemoveOverAllShift(Passes[0]);
    cout << "Passes[" << k << "] after removing offset" << endl;
    Passes[k].Print();
#endif
    chain->MakeEvent();
  }
  SurveyPass_t PassSum(Passes[0]);
  SurveyPass_t PassDif(Passes[0]);
  if (NP > 1) {
    PassSum += Passes[1];
    if (_debug) {
      cout << "PassSum" << endl;
      PassSum.Print();
    }
    PassDif -= Passes[1];
    if (_debug) {
      cout << "PassDif" << endl;
      PassDif.Print();
    }
  }
  //  TCanvas *c0 = new TCanvas("c0","");
  for (Int_t k = 0; k < NH; k++) {
    SurveyPass_t *currPass = 0;
    Int_t color = k+1;
    TString Name;
    TString Title;
    Double_t ymin =  1e10;
    Double_t ymax = -1e10;
    Int_t m = 0;
    if (k < NP) {
      currPass = &Passes[k];
    } else if (k == NP) {
      m = 1;
      currPass = &PassSum;
    } else {
      m = 2;
      currPass = &PassDif;
    }
    currPass->Print();
    for (Int_t i = 0; i < 6; i++) {
      Name = Form("%s%s%s",currPass->PassName,nameK[i],NameO[m]);
      Title = Form("Alignment fit for  %s %s %2",names[i],currPass->PassName,currPass->Data[0].Comment);
#if 0
      dath[k][i] = (TH1D *) gDirectory->Get(Name);
      if (dath[k][i]) delete dath[k][i];
#endif      
      dath[k][i] = new TH1D(Name,Title, 24, 0.5, 24.5);
      //      cout << "Create: " << dath[k][i]->GetName() << "\t" << dath[k][i]->GetTitle() << endl;
      dath[k][i]->SetMarkerColor(color);
      dath[k][i]->SetLineColor(color);
      dath[k][i]->SetXTitle("sector");
      if (i < 3) dath[k][i]->SetYTitle(Form("%s (#mum)",names[i]));
      else       dath[k][i]->SetYTitle(Form("%s (mrad)",names[i]));
      for (Int_t l = 0; l < 24; l++) {
	Double_t val, err;
	Double_t *X = &currPass->Data[l].x;
	Double_t secs = currPass->Data[l].sector;
	if (X[2*i+1] >= 0 /* && X[2*i+1] < 99 */) {
	  val = X[2*i];
	  err = X[2*i+1];
	} else {continue;}
	if (err < 0.001) err = 0.001;
	dath[k][i]->SetBinContent(secs,val);
	dath[k][i]->SetBinError(secs,err);
	if (ymin > val - err) ymin = val - err;
	if (ymax < val + err) ymax = val + err;
      }
      hs[i]->Add(dath[k][i]);
#if 0
      c0->cd();
      c0->SetTitle(Title);
      dath[k][i]->Draw();
      c0->Update();
#endif
      if (leg[i]) {
	if      (k < NP)      leg[i]->AddEntry(dath[k][i],currPass->PassName);
	else if (k == NP)     leg[i]->AddEntry(dath[k][i],"(FF+RF)/2");
	else if (k == NP + 1) leg[i]->AddEntry(dath[k][i],"(FF-RF)/2");
      }
    }
  }
  c1 = new TCanvas("IO","Tpc Super Sector alignment parameters",1200,800);
  c1->Divide(3,2);
  for (Int_t i = 0; i < 6; i++) {
    c1->cd(i+1);
    if (! hs[i]) continue;
    TString same("e");
    Double_t ymax = hs[i]->GetMaximum("nostack");
    Double_t ymin = hs[i]->GetMinimum("nostack");
    TList *list = hs[i]->GetHists();
    TIter next(list);
    TH1 *h = 0;
    while ((h = (TH1*) next())) {
      h->GetYaxis()->SetTitleOffset(1.4);
      if (same == "e") {
	if (ymax > 0)     h->SetMaximum(1.1*ymax);
	else              h->SetMaximum(0.9*ymax);
	if (ymin < 0)     h->SetMinimum(1.1*ymin);
	else              h->SetMinimum(0.9*ymin);
      }
      TString hName(h->GetName());
      if (hName.BeginsWith("db",TString::kIgnoreCase)) h->Draw("same");
      else                                             h->Draw(same);
      same = "same";
    }
    if (leg[i]) leg[i]->Draw();
  }
  c1->Update();
  fOut->Write();
  MakeSuperSectorPositionBTable(PassSum,"B");
  MakeSuperSectorPositionBTable(PassDif,"D");
}
