// root.exe  y2025z.root 'RayTracing.C+(0)'      z =    0
// root.exe  y2025z.root 'RayTracing.C+(200)'    z = +200;
#include <cstring>
#include <stdlib.h>
#include "Riostream.h"
#include "TCanvas.h"
#include "TStyle.h"
#include "TFile.h"
#include "TString.h"
#include "TH2.h"
#include "TH3.h"
#include "TRandom3.h"
#include "TPolyMarker3D.h"
#include "TPolyLine3D.h"
#include "TStopwatch.h"
#include "TGeoBBox.h"
#include "TGeoTube.h"
#include "TGeoNode.h"
#include "TGeoManager.h"
#include "TGeoOverlap.h"
#include "TGeoPainter.h"
#include "TGeoChecker.h"
#include "TKey.h"
#include "TBuffer3D.h"
#include "TBuffer3DTypes.h"
#include "TMath.h"
#include "TROOT.h"
#include "Ask.h"
//________________________________________________________________________________
void Import(const Char_t *name = "") {
  if (!gFile) return;
  TIter next(gFile->GetListOfKeys());
  TKey *key;
  while ((key = (TKey*)next())) {
    if (strcmp(key->GetClassName(),"TGeoManager") != 0) continue;
    gGeoManager = (TGeoManager*)key->ReadObj();
    break;
  }
}
//________________________________________________________________________________
void RayTracing(Double_t zStart = 200,
		Double_t rmax = 45,
		Double_t zmin = -210, Double_t zmax = 210) {

  Int_t    neta =  240;;
  Double_t emin = -2.0;
  Double_t emax =  0.4;
  if (TMath::Abs(zStart) < 1) {
    neta =  400;
    emin = -2.0;
    emax =  2.0;
  }
  Int_t nphi = 180;
  Double_t phimin = 0;
  Double_t phimax = 360;
  static Int_t _debug =  0;
  const Char_t *VolumeNames[] = {"CAVE", "PIPE", "SCON", "FSTA", "SROD", "SBSP"};
  if (!gGeoManager) Import();
  if (!gGeoManager) return;
  TString fOutName("RayTracing_");
  fOutName += gGeoManager->GetName();
  fOutName += "_Z"; fOutName += zStart;
  fOutName += "Radl.root";
  TFile *fOut = new TFile(fOutName,"recreate");
  Int_t NV = sizeof(VolumeNames)/sizeof(const Char_t *);
  Double_t *x = new Double_t[NV];
  TH2F    **hist = new TH2F*[NV];
// Generate a lego plot #include "TGeoVoxelFinder.h"
  for (Int_t v = 0; v < NV; v++) {
    hist[v] = new TH2F(VolumeNames[v], Form("Integrated Rad.Length in %s for R < %5.0f and Z in [%5.0f,%5.0f] with Z start = %5.0f ; #phi ; #eta",
					    VolumeNames[v],rmax,zmin,zmax,zStart), nphi, phimin, phimax, neta, emin, emax);
  }
   Double_t degrad = TMath::Pi()/180.;
   Double_t eta, phi, step, matprop;
   Double_t start[3];
   Double_t dir[3];
   TGeoNode *startnode, *endnode;
   Int_t i;  // loop index for phi
   Int_t j;  // loop index for eta
   Int_t k =  1;
   Int_t ntot = neta * nphi;
   Int_t n10 = ntot/10;
   Int_t igen = 0, iloop=0;
   printf("=== Lego plot sph. => nrays=%i\n", ntot);
   for (i=1; i<=nphi; i++) {
     for (j=1; j<=neta; j++) {
       igen++;
       if (n10) {
	 if ((igen%n10) == 0) printf("%i percent\n", Int_t(100*igen/ntot));
       }  
       Int_t k = 1;
       memset(x, 0, NV*sizeof(Double_t));
       Double_t length = 0;
       eta = hist[0]->GetYaxis()->GetBinCenter(j);
       Double_t sinL = TMath::TanH(eta);
       Double_t cosL = 1./TMath::CosH(eta); // TMath::Sqrt(1 - sinL*sinL);
       Double_t tanL = sinL/cosL;
       phi   = hist[0]->GetXaxis()->GetBinCenter(i);//+1e-2;
       start[0] = start[1] =  1e-2;
       start[2] = zStart;
       Double_t Phi =  TMath::DegToRad()*phi;
       dir[0] = cosL*TMath::Cos(Phi);
       dir[1] = cosL*TMath::Sin(Phi);
       dir[2] = sinL;
       gGeoManager->InitTrack(&start[0], &dir[0]);
       startnode = gGeoManager->GetCurrentNode();
       if (_debug) {
	 cout << "start track with eta = " << eta << "\tphi = " << phi << "\tZ = " << zStart
	      << "\t" << gGeoManager->GetPath() << endl;
	 
       }
       if (gGeoManager->IsOutside()) startnode=0;
       if (startnode) {
	 matprop = startnode->GetVolume()->GetMaterial()->GetRadLen();
       } else {
	 matprop = 0.;
       }      
       gGeoManager->FindNextBoundary();
       //         gGeoManager->IsStepEntering();
       // find where we end-up
       endnode = gGeoManager->Step();
       step = gGeoManager->GetStep();
       while (step<1E10) {
	 // now see if we can make an other step
	 iloop=0;
	 while (!gGeoManager->IsEntering()) {
	   iloop++;
	   gGeoManager->SetStep(1e-2);
	   step += 1e-2;
	   endnode = gGeoManager->Step();
	   step = gGeoManager->GetStep();
	   length += step;
	   if (iloop > 10000*k) {
	     cout << iloop << " steps\teta = " << eta << "\tphi = " << phi << "\t" << gGeoManager->GetPath() << "\tlength = " << length << endl;
	     k = iloop/10000 + 1;
	   }
	 }
	 length += step;
	 if (matprop>0) {
	   TString path(gGeoManager->GetPath());
	   x[0] += step/matprop;
	   for (Int_t v = 1; v < NV; v++) {
	     if (! path.Contains(VolumeNames[v])) continue;
	     x[v] += step/matprop;
	   }
	 }   
	 if (endnode==0 && step>1E10) break;
	 // generate an extra step to cross boundary
	 startnode = endnode;    
	 if (startnode) {
	   matprop = startnode->GetVolume()->GetMaterial()->GetRadLen();
	 } else {
	   matprop = 0.;
	 }      
	 
	 gGeoManager->FindNextBoundary();
	 endnode = gGeoManager->Step();
	 step = gGeoManager->GetStep();
	 const Double_t *xyz = gGeoManager->GetCurrentPoint();
	 const Double_t *d   = gGeoManager->GetCurrentDirection();
	 Double_t R = TMath::Sqrt(xyz[0]*xyz[0] + xyz[1]*xyz[1]);
	 if (_debug) {
	   const Double_t *d   = gGeoManager->GetCurrentDirection();
	   cout << "x,y,z = " << xyz[0] << "\t" << xyz[1] << "\t" << xyz[2]
		<< "\tdir = " << d[0] << "\t" << d[1] << "\t" << d[2]
		<< "\tR = " << R 
		<<"\tlength = " << length
		<< "\t" << gGeoManager->GetPath() << endl;
	 }
	 if (R > rmax) break;
	 if (xyz[2] < zmin || xyz[2] > zmax) break;
       }
       for (Int_t v = 0; v < NV; v++) {
	 hist[v]->Fill(phi, eta, x[v]); 
       }
     }
   }
   fOut->Write();
   return;          
}
//________________________________________________________________________________
void Plot(const Char_t *volume = "FSTA") {
  TSeqCollection *files = gROOT->GetListOfFiles();
  if (! files) return;
  Int_t nn = files->GetSize();
  if (! nn) return;
  TFile **FitFiles = new TFile *[nn];
  TIter next(files);
  TFile *f = 0;
  TH2 *hist[10] = {0};
  Int_t NH = 0;
  Double_t ymin = 1e8, ymax = 0;
  while (f = (TFile *) next()) {
    TH2 *h2 = (TH2 *) f->Get(volume);
    if (! h2) continue;
    if (h2->GetMinimum() < ymin) ymin = h2->GetMinimum();
    if (h2->GetMaximum() > ymax) ymax = h2->GetMaximum();
    hist[NH] = h2;
    NH++;
  }
  if (ymin < 1e-3) ymin = 1e-3;
  if (! NH) return;
  gStyle->SetOptStat(0);
  TCanvas *can[10] = {0};
  for (Int_t i = 0; i < NH; i++) {
    TString Title(hist[i]->GetDirectory()->GetName()); Title.ReplaceAll(".root","");
    TString Name("c"); Name += i;
    can[i] = (TCanvas *) gROOT->GetListOfCanvases()->FindObject(Name);
    if (can[i])  can[i]->Clear();
    else         can[i] = new TCanvas(Name,Title);
    can[i]->SetLogz(1);
    hist[i]->SetMinimum(ymin);
    hist[i]->SetMaximum(ymax);
    hist[i]->Draw("colz");
  }
}
//________________________________________________________________________________
void AverageTubs(const Char_t *volName = "FSTW") {
  if (!gGeoManager) Import();
  if (!gGeoManager) return;
  TGeoVolume *volume = gGeoManager->GetVolume(volName);
  if (! volume) return;
  TGeoShape *shape = volume->GetShape();
  if (! shape->IsA()->InheritsFrom( "TGeoTubeSeg")) return;
  //  if (! shape->TestBit(TGeoShape::kGeoTubeSeg)) return;
  TGeoTubeSeg *shapeC = (TGeoTubeSeg *) shape;
  Double_t Rmax = shapeC->GetRmax();
  Double_t Rmin = shapeC->GetRmin();
  Double_t dZ   = shapeC->GetDz();
  Double_t Phi1 = shapeC->GetPhi1();
  Double_t Phi2 = shapeC->GetPhi2();
  if (Phi2 < Phi1) Phi2 += 360.0;
  if (Phi2 > 360.0) {
    Phi1 -= 360;
    Phi2 -= 360;
  }
  TGeoVolume *tvol = gGeoManager->GetTopVolume();
  gGeoManager->SetTopVolume(volume);
  Int_t nR = 2*(Rmax - Rmin)/0.1;
  Int_t nZ = 2*2*dZ/0.1;
  Int_t nPhi = 2*(Phi2 - Phi1);
  TFile *fOut = new TFile(Form("%s.root",volName), "recreate");
  TH3F *No    = new TH3F("No","no. entries ; Z (cm) ; R (cm) ; #phi (degree)", nZ, -dZ, dZ, nR, Rmin, Rmax, nPhi, Phi1, Phi2);
  TH3F *Dens  = new TH3F("Dens","Density ; Z (cm) ; R (cm) ; #phi (degree)", nZ, -dZ, dZ, nR, Rmin, Rmax, nPhi, Phi1, Phi2);
  TH3F *A     = new TH3F("A","A*Dens ; Z (cm) ; R (cm) ; #phi (degree)", nZ, -dZ, dZ, nR, Rmin, Rmax, nPhi, Phi1, Phi2);
  TH3F *Z     = new TH3F("Z","Z*Dens ; Z (cm) ; R (cm) ; #phi (degree)", nZ, -dZ, dZ, nR, Rmin, Rmax, nPhi, Phi1, Phi2);
  TH3F *RadlI = new TH3F("RadlI","Inverse RadL*Dens ; Z (cm) ; R (cm) ; #phi (degree)", nZ, -dZ, dZ, nR, Rmin, Rmax, nPhi, Phi1, Phi2);
  TList *matlist = gGeoManager->GetListOfMaterials();

   Int_t nmat = matlist->GetSize();
   if (!nmat) return;
   Double_t x,y,z;
   TGeoNode *node;
   TGeoMaterial *mat;
   Long64_t igen = 0;
   Long64_t N = 100*nR*nZ*nPhi;
   Long64_t n10 = N/10;
   for (Long64_t i = 0; i < N; i++) {
     z = dZ*(2*gRandom->Rndm() - 1);
     Double_t r = Rmin + (Rmax - Rmin)*gRandom->Rndm();
     Double_t phi = Phi1 + (Phi2 - Phi1)*gRandom->Rndm();
     Double_t Phi = TMath::DegToRad()*phi;
     x = r*TMath::Cos(Phi);
     y = r*TMath::Sin(Phi);
     No->Fill(z,r,phi);
     node = gGeoManager->FindNode(x,y,z);
     igen++;
     if (n10) {
       if ((igen%n10) == 0) printf("%i percent\n", Long64_t(100*igen/N));
     }  
     if (!node) continue;
     mat = node->GetVolume()->GetMedium()->GetMaterial();
     if (! mat) continue;
     Double_t dens = mat->GetDensity();
     if (dens  < 2e-2) continue;
     Dens->Fill(z,r,phi,dens);
     A->Fill(z,r,phi,mat->GetA()*dens);
     Z->Fill(z,r,phi,mat->GetZ()*dens);
     if (mat->GetRadLen() > 1e-2) RadlI->Fill(z,r,phi,dens/mat->GetRadLen());
   }
   fOut->Write();
   gGeoManager->SetTopVolume(tvol);
   
   return;
}
//______________________________________________________________________________
void Average() {
/*
    z = [-2.00, -1.70]
        [-1.70, -1.40]
        [-1.40, -0.55]
        [-0.55,  0.20]
        [ 0.20,  1.50]
r_phi = [ 5.00, 15.00], 
        [15.00, 16.20]  [ -8.00, -5.00], [ -1.50, 1.50], [  5.00, 8.00]
        [16.20, 17.80]  [-15.00, 15.00]
        [17.80, 18.60]  [-12.00,-10,00], [ 10.00, 12.00]  
        [18.60, 27.80]  [-15.00,-13.00], 
        [18.60, 33.00]  [ 13.00, 15.00]
        [27.80, 33.00]  [ 12.00, 13.00]
        [27.80, 29.00]  [-16.00, 13.00]
        [29.00, 30.00]  [-10.50, -9.00]  [  9.00, 10.50]
        [30.00, 35.00]  [-15.00, 15.00]                                

*/
  struct Limits_t {
    Double_t min; 
    Double_t max;
  };
  Limits_t Z[] = {
    {-2.00, -1.70},
//     {-2.00, -1.90},
//     {-1.85, -1.70},
    {-1.70, -1.40},
    {-1.40, -0.55},
    {-0.55,  0.20},
    { 0.20,  1.50}
  };
  Limits_t R[] = {
    { 5.00, 15.00},
    {15.00, 16.20}, 
    {16.20, 17.80}, 
    {17.80, 18.60}, 
    {18.60, 27.80}, 
    {18.60, 33.00}, 
    {27.80, 33.00}, 
    {27.80, 29.00}, 
    {29.00, 30.00}, 
    {30.00, 35.00},
    { 5.00, 35.00}
  };
  Limits_t Phi[] = {
    { -8.00, -5.00}, 
    { -1.50,  1.50}, 
    {  5.00,  8.00},
    {-15.00, 15.00},				       
    {-12.00,-10.00}, 
    { 10.00, 12.00},  	       
    {-15.00,-13.00}, 			       
    { 13.00, 15.00},				       
    { 12.00, 13.00},				       
    {-16.00, 13.00},				       
    {-10.50, -9.00},  
    {  9.00, 10.50},	       
    {-15.00, 15.00},                                
    {-17.00, 17.00}
  };
  Int_t nZ = sizeof(Z)/sizeof(Limits_t);
  Int_t nR = sizeof(R)/sizeof(Limits_t);
  Int_t nPhi = sizeof(Phi)/sizeof(Limits_t);
  TH3F *No = (TH3F *) gDirectory->Get("No");
  if (! No) return;
  TH3F *Dens = (TH3F *) gDirectory->Get("Dens");
  if (! Dens) return;
  TCanvas *c1 = new TCanvas("c1","c1",1200,400);
  c1->Divide(3,1);
  for (Int_t iz = 0; iz < nZ; iz++) {
    Int_t iz1 = No->GetXaxis()->FindBin(Z[iz].min);
    Int_t iz2 = No->GetXaxis()->FindBin(Z[iz].max) - 1;
    No->GetXaxis()->SetRange(iz1,iz2);
    Dens->GetXaxis()->SetRange(iz1,iz2);
    for (Int_t ir = 0; ir < nR; ir++) {
      Int_t ir1 = No->GetYaxis()->FindBin(R[ir].min);
      Int_t ir2 = No->GetYaxis()->FindBin(R[ir].max) - 1;
      No->GetYaxis()->SetRange(ir1,ir2);
      Dens->GetYaxis()->SetRange(ir1,ir2);
      for (Int_t iphi = 0; iphi < nPhi; iphi++) {
	Int_t iphi1 = No->GetYaxis()->FindBin(Phi[iphi].min);
	Int_t iphi2 = No->GetYaxis()->FindBin(Phi[iphi].max) -1;
	No->GetYaxis()->SetRange(iphi1,iphi2);
	Dens->GetYaxis()->SetRange(iphi1,iphi2);
	TString Title(Form("z_%i [%5.1f,%5.1f] r_%i [%5.1f,%5.1f] phi_%i [%5.1f,%5.1f]",
			   iz,Z[iz].min,Z[iz].max,
					  ir,R[ir].min,R[ir].max,
							 iphi,Phi[iphi].min,Phi[iphi].max));
	c1->SetTitle(Title);
	//
	TH1 *Nox = No->Project3D("x");
	TH1 *Densx = Dens->Project3D("x");
	if (Densx->GetEntries() <= 0.0) continue;
	Densx->Divide(Nox);
	c1->cd(1); Densx->Draw();
	TH1 *Noy = No->Project3D("y");
	TH1 *Densy = Dens->Project3D("y");
	Densy->Divide(Noy);
	c1->cd(2); Densy->Draw();
	TH1 *Noz = No->Project3D("z");
	TH1 *Densz = Dens->Project3D("z");
	Densz->Divide(Noz);
	c1->cd(3); Densz->Draw();
	c1->Update();
	if (! gROOT->IsBatch() && Ask()) return;
      }
    }
  }
}
