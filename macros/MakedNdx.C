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
#if 0
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
    TCanvas *c1 = new TCanvas("c1","c1");
    c1->SetLogx(1);
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
    cout << "Create hitogram " << histD->GetName() << endl;
    for (i = 0; i < npoints; i++) {
      histD->SetBinContent(i+1,y[i]);
      cout << i+1 << " x = " << xL10[i] << "\ty = " << y[i] << "\tbin center " << histD->GetBinCenter(i+1) << "\tcont = " << histD->GetBinContent(i+1) << endl;
    }
    histD->SetLineColor(3+2*m);
    histD->SetLineWidth(4);
    histD->SetMarkerColor(3);
    histD->SetMarkerStyle(21);
    histD->GetXaxis()->SetTitle("Log_{10} ( #beta#gamma )");
    histD->GetYaxis()->SetTitle("dN/dx (collision/cm)");
    histD->Draw();
    TH1D *histS = new TH1D(*histD);
    histS->SetName(Name + "Smoth");
    histS->SetLineColor(4+2*m);
    histS->SetLineWidth(4);
    histS->SetMarkerColor(4);
    histS->SetMarkerStyle(21);
    histD->Smooth();
    histD->Draw("same");
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
