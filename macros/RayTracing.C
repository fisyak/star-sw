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
#include "TSystem.h"
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
  const Char_t *FSTWVol[] = {
    "FSTW",
    "FTUR", "FTRO", "FSBW", "FSWT", "FTUW", "FTIA", "FTIB", "FTRB", "FSCT", "FSCL",
    "FHTS", "FCHT", "FCHB", "FSHA", "FSHB", "FSHC", "FSHD", "FSHE", "FSHF", "FSHG",
    "FSHH", "FSAC", "FSTB", "FTHC", "FTOH", "FSBH", "FTIH", "FTUS"
  };
  TH1::SetDefaultSumw2();
  Int_t NV = sizeof(FSTWVol)/sizeof(const Char_t*);
  TGeoVolume *tvol = gGeoManager->GetTopVolume();
  gGeoManager->SetTopVolume(volume);
  Int_t nR = (Rmax - Rmin)/0.1;
  Int_t nZ = 2*dZ/0.1;
  Int_t nPhi = 2*(Phi2 - Phi1);
  TFile *fOut = new TFile(Form("%s.root",volName), "recreate");
  TH3F *No    = new TH3F("No","no. entries ; Z (cm) ; R (cm) ; #phi (degree)", nZ, -dZ, dZ, nR, Rmin, Rmax, nPhi, Phi1, Phi2);
  TH3F *Dens  = new TH3F("Dens","Density ; Z (cm) ; R (cm) ; #phi (degree)", nZ, -dZ, dZ, nR, Rmin, Rmax, nPhi, Phi1, Phi2);
  TH3F *A     = new TH3F("A","A*Dens ; Z (cm) ; R (cm) ; #phi (degree)", nZ, -dZ, dZ, nR, Rmin, Rmax, nPhi, Phi1, Phi2);
  TH3F *Z     = new TH3F("Z","Z*Dens ; Z (cm) ; R (cm) ; #phi (degree)", nZ, -dZ, dZ, nR, Rmin, Rmax, nPhi, Phi1, Phi2);
  TH3F *RadlI = new TH3F("RadlI","Inverse RadL ; Z (cm) ; R (cm) ; #phi (degree)", nZ, -dZ, dZ, nR, Rmin, Rmax, nPhi, Phi1, Phi2);
  TH3F **DensV = new TH3F*[NV];
  TH3F **RadlIV = new TH3F*[NV];
  for (Int_t v = 0; v < NV; v++) {
    DensV[v] = new TH3F(Form("Dens_%s",FSTWVol[v]), Form("Density in %s; Z (cm) ; R (cm) ; #phi (degree)",FSTWVol[v]),
			nZ, -dZ, dZ, nR, Rmin, Rmax, nPhi, Phi1, Phi2); 
    RadlIV[v] = new TH3F(Form("RadlI_%s",FSTWVol[v]), Form("Inverse RadL in %s; Z (cm) ; R (cm) ; #phi (degree)",FSTWVol[v]),
			nZ, -dZ, dZ, nR, Rmin, Rmax, nPhi, Phi1, Phi2); 
  }
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
     if (mat->GetRadLen() > 1e-2) RadlI->Fill(z,r,phi,1./mat->GetRadLen());
     TString path(gGeoManager->GetPath());
     for (Int_t v = 0; v < NV; v++) {
       if (path.Contains(FSTWVol[v])) {
	 DensV[v]->Fill(z,r,phi,dens);
	 if (mat->GetRadLen() > 1e-2) RadlIV[v]->Fill(z,r,phi,1./mat->GetRadLen());
       }
     }
   }
   fOut->Write();
   gGeoManager->SetTopVolume(tvol);
   
   return;
}
//______________________________________________________________________________
void Average1() {
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
//________________________________________________________________________________
Double_t Average(const TString VolName ="FSTW", 
	     Double_t Zmin   =  -2.00, Double_t Zmax =     1.5,  
	     Double_t Rmin   =   5.00, Double_t Rmax =   35.00,  
	     Double_t Phimin = -17.00, Double_t Phimax = 17.00,
	     TString HistName = "RadlI") {  
   gStyle->SetOptStat(0);
  TH3F *No = (TH3F *) gDirectory->Get("No");
  if (! No) return 0;
  TH3F *Dens = (TH3F *) gDirectory->Get("Dens");
  if (! Dens) return 0;
  TH3F *divider = No;
  if (HistName == "A" || HistName == "Z") divider = Dens;
  if (VolName != "") {HistName += "_"; HistName += VolName;}
  TH3F *hist = (TH3F *) gDirectory->Get(HistName);
  if (! hist) {
    cout << "Histograsm " << HistName.Data() << " has not been found." << endl;
    return 0;
  }
  TCanvas *c1 = (TCanvas *) gROOT->GetListOfCanvases()->FindObject("c1");
  if (c1) c1->Clear();
  else    c1 = new TCanvas("c1","c1",1800,600);
  c1->Divide(4,1);
  Int_t iz1 = divider->GetXaxis()->FindBin(Zmin + 1e-2);
  Int_t iz2 = divider->GetXaxis()->FindBin(Zmax - 1e-2);
  Int_t ir1 = divider->GetYaxis()->FindBin(Rmin + 1e-2);
  Int_t ir2 = divider->GetYaxis()->FindBin(Rmax - 1e-2);
  Int_t iphi1 = divider->GetZaxis()->FindBin(Phimin + 1e-2);
  Int_t iphi2 = divider->GetZaxis()->FindBin(Phimax - 1e-2);;

  TString Title(Form("%s z_%i %i [%5.1f,%5.1f] r_%i_%i [%5.1f,%5.1f] phi_%i_%i [%5.1f,%5.1f]", VolName.Data(),
		     iz1,iz2,Zmin,Zmax,
		     ir1,ir2,Rmin,Rmax,
		     iphi1,iphi2,Phimin,Phimax));
  cout << Title.Data() << endl;
  c1->SetTitle(Title);
  divider->GetXaxis()->SetRange(iz1,iz2);
  divider->GetYaxis()->SetRange(ir1,ir2);
  divider->GetZaxis()->SetRange(iphi1,iphi2);
  hist->GetXaxis()->SetRange(iz1,iz2);
  hist->GetYaxis()->SetRange(ir1,ir2);
  hist->GetZaxis()->SetRange(iphi1,iphi2);
  TH1 *dividerx = divider->Project3D("x");
  TH1 *histx = hist->Project3D("x");
  if (histx->GetEntries() <= 0.0) return 0;
  histx->Divide(dividerx);
//   histx->GetXaxis()->SetRange(iz1,iz2);
  c1->cd(1); histx->Draw();
  TH1 *dividery = divider->Project3D("y");
  TH1 *histy = hist->Project3D("y");
  histy->Divide(dividery);
//   histy->GetXaxis()->SetRange(ir1,ir2);
  c1->cd(2); histy->Draw();
  TH1 *dividerz = divider->Project3D("z");
  TH1 *histz = hist->Project3D("z");
  histz->Divide(dividerz);
  c1->cd(3); histz->Draw();
  TH2 *divideryz = (TH2*) divider->Project3D("yz");
  TH2 *histyz = (TH2*) hist->Project3D("yz");
  histyz->Divide(divideryz);
//   histz->GetXaxis()->SetRange(iphi1,iphi2);
  c1->cd(4); histyz->Draw("colz");
  Double_t av = histyz->Integral()/histyz->GetNbinsX()/histyz->GetNbinsY();
  cout << "Maximum of " << HistName << "yz\t = " << histyz->GetMaximum() << endl;
  cout << "Average of " << HistName << "yz\t = " << av << endl;
  c1->Update();
  return av;
}
//________________________________________________________________________________
void LoopOeveVolumes() {
  const Char_t *FSTWVol[] = {
    "FSTW",
    "FTUR", "FTRO", "FSBW", "FSWT", "FTUW", "FTIA", "FTIB", "FTRB", "FSCT", "FSCL",
    "FHTS", "FCHT", "FCHB", "FSHA", "FSHB", "FSHC", "FSHD", "FSHE", "FSHF", "FSHG",
    "FSHH", "FSAC", "FSTB", "FTHC", "FTOH", "FSBH", "FTIH", "FTUS"
  };
  struct Avr_t {
    const Char_t *name;
    Double_t zMin, zMax;
    Double_t rMin, rMax;
    Double_t phiMin, phiMax;
    Double_t RadlI;
    Double_t Dens;
    Double_t A;
    Double_t Z;
    void Print() {
      TString Line = Form("{\"%s\",%5.1f,%5.1f,%5.1f,%5.1f,%5.1f,%5.1f, %8.3f, %8.3f, %8.3f, %8.3f },",
			  name, zMin, zMax, rMin, rMax, phiMin, phiMax,
			  RadlI, Dens, A, Z);
      cout << Line.Data() << endl;
      const Char_t *Out = "FSTW.txt";
      ofstream out;
      if (gSystem->AccessPathName(Out)) out.open(Out, ios::out); //"Results.list",ios::out | ios::app);
      else                              out.open(Out, ios::app);
      out << Line.Data() << endl;
      out.close();
	
    }
  };
  const Char_t *V[4] = {"RadlI", "Dens", "A", "Z"};
  Avr_t av[] = {
    //                z           r        Phi
    {"FSTW", -1.7, -0.2, 16.2,   18,  -15,   15,  0, 0, 0, 0},
    {"FSTW", -1.7, -0.2,   28,   29,  -15,   15,  0, 0, 0, 0},
    {"FSTW", -1.3, -0.6  , 17,   28,-14.5,  -13,  0, 0, 0, 0},
    {"FSTW", -1.3, -0.6,   17,   28,   13, 14.5,  0, 0, 0, 0},
    {"FSTW", -1.0, -0.9,   30,   32,   -7,    7,  0, 0, 0, 0},
    {"FSTW", -1.7, -1.6, 16.5,   28,  -15,   15,  0, 0, 0, 0},
    {"FSTW", -0.3, -0.2,    5, 15.5,  -15,   15,  0, 0, 0, 0},
    {"FTUR", -2.0, -1.6,   30, 33.5,  -14,   -7,  0, 0, 0, 0},
    {"FTUR", -2.0, -1.6, 32.2, 33.5,   -7,    7,  0, 0, 0, 0},
    {"FTUR", -2.0, -1.6,   30, 33.5,    7,   14,  0, 0, 0, 0},
  };
  Int_t Nav = sizeof(av)/sizeof(Avr_t);
  const Char_t *VName[4] = {"RadlI","Dens","A","Z"};
  Int_t NV = sizeof(FSTWVol)/sizeof(const Char_t*);
  for (Int_t v = 0; v < 1; v++) {
    for (Int_t i = 0; i < Nav; i++) {
      Double_t *x = &av[i].RadlI;
      for (Int_t j = 0; j < 4; j++) {
	x[j] = Average("",av[i].zMin,av[i].zMax,av[i].rMin,av[i].rMax,av[i].phiMin,av[i].phiMax,VName[j]);
	if (! gROOT->IsBatch() && Ask()) return;
      }
      av[i].Print();
    }
  }
}  
/*
//      z Min   Max r Min Max Phi Min   Max     RadlI      Dens         A         Z 
{"FSTW", -1.7, -0.2, 16.2, 18.0,-15.0, 15.0,    0.038,    0.979,   24.742,   11.843 }.
{"FSTW", -1.7, -0.2, 28.0, 29.0,-15.0, 15.0,    0.045,    1.023,   30.518,   14.471 }.
{"FSTW", -1.3, -0.6, 17.0, 28.0,-14.5,-13.0,    0.092,    1.709,   67.756,   31.707 }.
{"FSTW", -1.3, -0.6, 17.0, 28.0, 13.0, 14.5,    0.095,    1.754,   69.536,   32.540 }.
{"FSTW", -1.0, -0.9, 30.0, 32.0, -7.0,  7.0,    0.046,    1.436,   25.847,   12.931 }.
{"FSTW", -1.7, -1.6, 16.5, 28.0,-15.0, 15.0,    0.044,    1.214,   25.803,   12.876 }.
{"FSTW", -0.3, -0.2,  5.0, 15.5,-15.0, 15.0,    0.042,    1.081,   24.471,   12.208 }.

*/
