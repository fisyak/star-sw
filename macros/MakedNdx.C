#include "Riostream.h"
#include <stdio.h>
#include "TROOT.h"
#include "TSystem.h"
#include "TMath.h"
#include "TH1.h"
#include "TGraph.h"
#include "TSpline.h"
#include "TFile.h"
#include "TString.h"
#include "TCanvas.h"
#include "TMultiGraph.h"
TMultiGraph *mg = 0;
TH1D *histL = 0;
TSpline5 *spline5 = 0;
//________________________________________________________________________________
Double_t func(Double_t *x, Double_t *p = 0) {
  return histL->Interpolate(x[0]);
}
//________________________________________________________________________________
TF1 *F() {
  return new TF1("interpolation",func,-2,5.1,0);
}
//________________________________________________________________________________
Double_t funcS(Double_t *x, Double_t *p = 0) {
  return spline5->Eval(x[0]);
}
//________________________________________________________________________________
TF1 *S() {
  return new TF1("Spline5Int",funcS,-2,5.1,0);
}
//________________________________________________________________________________
struct MyDerivFunc { 
   MyDerivFunc(TF1 * f): fFunc(f) {}
   double operator() (double *x, double * )  const { 
      return fFunc->Derivative(*x);
   }
   TF1 * fFunc; 
};
//________________________________________________________________________________
TF1 *Derivative(TF1 *f1) {
  MyDerivFunc * deriv = new MyDerivFunc(f1);
  TString name("der_");
  name += f1->GetName();
  TF1 * f2 = new TF1(name,deriv, f1->GetXmin(), f1->GetXmax(), 0, "MyDerivFunc"); 
  return f2;
}
//________________________________________________________________________________
void MakedNdx() {
  const Char_t *FileNames[2] = {"/afs/rhic.bnl.gov/star/users/fisyak/WWW/star/PiD/Bichsel/P10sglYu11bsmu.mom",
				"/afs/rhic.bnl.gov/star/users/fisyak/WWW/star/PiD/Bichsel/P10sglYu11bgmu.mom"};
  const Char_t *Tags[2] = {"","_bg"};
  //  const Char_t *FileName="dNdx_Bichsel.data";
  auto f = new TFile("dNdx_Bichsel.root","RECREATE");
  for (Int_t m = 0; m < 1; m++) {
    TString fName(FileNames[m]);
    //  fName.ReplaceAll(".data",".root");
    FILE *fp = fopen(fName.Data(),"r");
    if (! fp) {
      cout << "Cannot open file " << fName.Data() << endl;
      return;
    } else {cout << "open file " << fName.Data() << endl;}
    const Int_t N = 500;
    Double_t  x[N];
    Double_t  xL10[N];
    Double_t  y[N];
    Double_t  yL[N];
    Double_t  dy[N];
    Double_t  dyHG[N];
    Double_t  dyHS[N];
    Float_t  X,Y,T;
    Int_t npoints = 0;
    char line[121];
    Int_t i = 0;
    Double_t dXav = 0;
    Double_t dX2av = 0;
    fgets(&line[0],120,fp);
    while (fgets(&line[0],120,fp)) {
      //    printf("%s",line);
      TString Line(line);
      Line.Strip();
      if (Line.Contains("(")) continue;
      if (Line == "") continue;
      //    printf("%s\n",Line.Data());
      Int_t nr = sscanf(&line[0],"%i %f %f %f",&i,&X,&T,&Y);
      if (nr != 4) continue;
      //    printf("%s",line);
      x[npoints] = X;
      xL10[npoints] = TMath::Log10(X);
      y[npoints] = Y;
      yL[npoints] = TMath::Log(Y);
      Double_t dX = 0;
      if (npoints > 0) {dX = xL10[npoints] - xL10[npoints-1]; dXav += dX; dX2av += dX*dX;}
      //      printf("%i\t%i\t%f\t%f\t%f\t%f\n",nr,i,x[npoints],T,y[npoints],dX);
      npoints++;
      if (npoints > N) break;
    }
    dXav /= (npoints-1);
    dX2av /= (npoints-1);
    dX2av = TMath::Sqrt(dX2av -dXav* dXav);
    printf("dX = %f +/- %f\n",dXav, dX2av);
    fclose(fp);
    TString Name(Form("dNdx%s",Tags[m]));
    Double_t xmin = xL10[0];
    Double_t xmax = xL10[npoints-1];
#if 1
    Double_t *xBins = new Double_t [npoints+1];
    for (i = 0; i <= npoints; i++) {
      if (i == 0)            xBins[i] = x[i]   - 0.5*(x[i+1] - x[i]); 
      else if (i == npoints) xBins[i] = x[i-1] + 0.5*(x[i-1] - x[i-2]);
      else                   xBins[i] = 0.5*(x[i] + x[i-1]);
      cout << i << "\t" << x[i] << "\t" << xBins[i] << endl;
    }
    TH1D *hist = new TH1D(Name,"dNdx versus #beta#gamma",npoints,xBins);
    //  Double_t dx   = (xmax - xmin)/(npoints-1);
    for (i = 0; i < npoints; i++) hist->SetBinContent(i+1,y[i]);
    hist->SetLineColor(2+2*m);
    hist->SetLineWidth(4);
    hist->SetMarkerColor(4);
    hist->SetMarkerStyle(21);
    hist->GetXaxis()->SetTitle("#beta#gamma");
    hist->GetYaxis()->SetTitle("dN/dx (collision/cm)");
    TCanvas *c4 = new TCanvas("c4","c4");
    c4->SetLogx(1);
    hist->Draw("");
#if 0
    TGraph *gr = new TGraph(npoints, x, y);
    Name += "Gr";
    gr->SetName(Name);
    gr->SetTitle(hist->GetTitle());
    TH1F *frame = gr->GetHistogram();
    frame->GetXaxis()->SetTitle("#beta#gamma");
    frame->GetYaxis()->SetTitle("dN/dx (collision/cm)");
    frame->Draw("p");
    gr->Write();
#if 0
    for (i = 0; i <= npoints; i++) {
      cout << "x = " << x[i] << "\thist " << hist->Interpolate(x[i]) << "\tgraph " << gr->Eval(x[i]) << "\tdiff = " <<  hist->Interpolate(x[i]) -  gr->Eval(x[i]) << endl;
    }
#endif
#endif
#endif
    TCanvas *c2 = new TCanvas("c2","c2");
    Name = Form("dNdxL10%s",Tags[m]);
    TH1D *histD = new TH1D(Name,"dNdx versus Log _{10} (#beta#gamma)",npoints,xmin-dXav/2,xmax+dXav/2);
    Name = Form("LndNdxL10%s",Tags[m]);
    histL = new TH1D(Name,"Log(dNdx) versus Log _{10} (#beta#gamma)",npoints,xmin-dXav/2,xmax+dXav/2);
    cout << "Create hitogram " << histD->GetName() << endl;
    for (i = 0; i < npoints; i++) {
      histD->SetBinContent(i+1,y[i]);
      histL->SetBinContent(i+1,yL[i]);
      histL->SetBinError(i+1,0.001);
      cout << i+1 << " x = " << xL10[i] << "\ty = " << y[i] << "\tbin center " << histD->GetBinCenter(i+1) << "\tcont = " << histD->GetBinContent(i+1) << endl;
    }
    histD->SetLineColor(3+2*m);
    histD->SetLineWidth(4);
    histD->SetMarkerColor(3);
    histD->SetMarkerStyle(21);
    histD->GetXaxis()->SetTitle("Log_{10} ( #beta#gamma )");
    histD->GetYaxis()->SetTitle("dN/dx (collision/cm)");
    histD->Draw();
    TCanvas *c1 = new TCanvas("c1","c1");
    histL->SetLineColor(3+2*m);
    histL->SetLineWidth(4);
    histL->SetMarkerColor(3);
    histL->SetMarkerStyle(21);
    histL->GetXaxis()->SetTitle("Log_{10} ( #beta#gamma )");
    histL->GetYaxis()->SetTitle("Log(dN/dx (collision/cm))");
    histL->Draw();
    TF1 *F1 = F();
    Double_t a = xL10[0];
    Double_t b = xL10[npoints-1];
    Double_t eps = 2*(b-a)/npoints;
    const Int_t npp = 15;
    Double_t xx[npp] = {a,-1.5, -1., -0.5,  0., 0.5, 1., 1.5,2., 2.5, 3., 3.5, 4., 4.5,b};
    //    spline5 = new TSpline5("spline5",xx,F1,npp,"b1a1b2e2", F1->Derivative(a), 0.,(F1->Derivative(a+eps)-F1->Derivative(a))/eps , 0.);
    spline5 = new TSpline5("spline5",xx,F1,npp);
    spline5->SetName(Name+"Spline5");
    spline5->SetLineColor(2+2*m);
    spline5->SetLineWidth(4);
    spline5->SetMarkerColor(2);
    spline5->SetMarkerStyle(21);
    spline5->Draw("same");
    spline5->Write();
#if 0
    TGraph *grD = new TGraph(npoints, xL10, y);
    Name += "Gr";
    grD->SetName(Name);
    grD->SetTitle(hist->GetTitle());
    TH1F *frameD = grD->GetHistogram();    
    frameD->GetXaxis()->SetTitle("Log_{10} ( #beta#gamma )");
    frameD->GetYaxis()->SetTitle("dN/dx (collision/cm)");
    grD->Draw("p");
    grD->Write();
    Double_t b = xL10[npoints-1];
    Double_t a = xL10[0];
    Double_t eps=(b-a)*1.e-5;
    Double_t da = (grD->Eval(a+eps) - grD->Eval(a))/eps;
    Double_t db = (grD->Eval(b) - grD->Eval(a-eps))/eps;
    //    TSpline3 *spline3 = new TSpline3("spline3", xL10,y,,"b1e1", da, db);
    TSpline3 *spline3 = new TSpline3("spline3", grD);
    Name += "Splin3";
    spline3->SetName(Name);
    spline3->Write();
    for (i = 0; i < npoints; i++) {
      dy[i] =  histD->Interpolate(xL10[i]) - y[i];
      dyHG[i] = grD->Eval(xL10[i]) - y[i];
      dyHS[i] = spline3->Eval(xL10[i]) - y[i];
    }
    mg = new TMultiGraph("dev","dev");
    TGraph *gdy = new TGraph(npoints,xL10,dy); mg->Add(gdy);
#if 0
    TGraph *gdyHG = new TGraph(npoints,xL10,dyHG); gdyHG->SetMarkerColor(2);  gdyHG->SetLineColor(2);  mg->Add(gdyHG);
    TGraph *gdyHS = new TGraph(npoints,xL10,dyHS); gdyHG->SetMarkerColor(3);  gdyHG->SetLineColor(3);  mg->Add(gdyHS);
#endif
    TCanvas *c3 = new TCanvas("c3","c3");
    mg->Draw("axp");
#endif
  }
  f->Write();
}
