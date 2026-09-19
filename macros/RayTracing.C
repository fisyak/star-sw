// root.exe 
#include <cstring>
#include "Riostream.h"
#include "TCanvas.h"
#include "TStyle.h"
#include "TFile.h"
#include "TString.h"
#include "TH2.h"
#include "TRandom3.h"
#include "TPolyMarker3D.h"
#include "TPolyLine3D.h"
#include "TStopwatch.h"
#include "TGeoBBox.h"
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
#include <stdlib.h>
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
