//  g++ gsl_splineFit.C -I$XOPTSTAR/include -L $XOPTSTAR/lib -lgsl -lgslcblas
//  root.exe lgsl.C gsl_splineFit.C+
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <gsl/gsl_bspline.h>
#include <gsl/gsl_multifit.h>
#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>
#include <gsl/gsl_statistics.h>
#include "Riostream.h"
#include "TMath.h"
#include "TGraph.h"
#include "TGraphErrors.h"
#include "TMultiGraph.h"
#include "TF1.h"
#include "TH1.h"
#include "TSpline.h"
#include "TArrayD.h"
#include "TRandom.h"
#include "TCanvas.h"
#include "TROOT.h"
#include "TFile.h"
TSpline3 *spline = 0;
TCanvas  *c1 = 0;
TString  Option; 
//TSpline5 *spline = 0;
void gsl_splineFit(Double_t *xData, Double_t *yData,  Double_t *eData, Double_t *xKnot, Int_t K = 4, Int_t N = 200, Int_t NBREAK = 10, Option_t *opt = "b1e1")
{
  Option = opt;
  Int_t NCOEFFS = NBREAK - 2 + K;
  const size_t n = N;
  const size_t ncoeffs = NCOEFFS;
  const size_t nbreak = NBREAK;
  size_t i, j;
  gsl_bspline_workspace *bw;
  gsl_vector *B;
  double dy;
  gsl_rng *r;
  gsl_vector *c, *w;
  gsl_vector *x, *y;
  gsl_matrix *X, *cov;
  gsl_multifit_linear_workspace *mw;
  double chisq, Rsq, dof, tss;

  gsl_rng_env_setup();
  r = gsl_rng_alloc(gsl_rng_default);

  /* allocate a cubic bspline workspace (k = 4) */
  bw = gsl_bspline_alloc(K, nbreak);
  B = gsl_vector_alloc(ncoeffs);

  x = gsl_vector_alloc(n);
  y = gsl_vector_alloc(n);
  X = gsl_matrix_alloc(n, ncoeffs);
  c = gsl_vector_alloc(ncoeffs);
  w = gsl_vector_alloc(n);
  cov = gsl_matrix_alloc(ncoeffs, ncoeffs);
  mw = gsl_multifit_linear_alloc(n, ncoeffs);

  /* this is the data to be fitted */
  for (i = 0; i < n; ++i)
    {
      gsl_vector_set(x, i, xData[i]);
      gsl_vector_set(y, i, yData[i]);
      gsl_vector_set(w, i, 1.0 / (eData[i] * eData[i]));
    }
  gsl_vector *breakpts = gsl_vector_alloc(nbreak);
  for (UInt_t i = 0; i < nbreak; i++) gsl_vector_set(breakpts, i, xKnot[i]);
  gsl_bspline_knots(breakpts, bw);
  /* construct the fit matrix X */
  for (i = 0; i < n; ++i)
    {
      double xi = gsl_vector_get(x, i);

      /* compute B_j(xi) for all j */
      gsl_bspline_eval(xi, B, bw);

      /* fill in row i of X */
      for (j = 0; j < ncoeffs; ++j)
        {
          double Bj = gsl_vector_get(B, j);
          gsl_matrix_set(X, i, j, Bj);
        }
    }

  /* do the fit */
  gsl_multifit_wlinear(X, w, y, c, cov, &chisq, mw);

  dof = n - ncoeffs;
  tss = gsl_stats_wtss(w->data, 1, y->data, 1, y->size);
  Rsq = 1.0 - chisq / tss;

  fprintf(stderr, "chisq/dof = %e, Rsq = %f\n",
                   chisq / dof, Rsq);

  printf("\n\n");

  /* output the smoothed curve */
  {
    double xi, yi, yerr;
#if 0
    TGraph *smooth = new TGraph();
    smooth->SetLineColor(2);
    smooth->SetLineWidth(4);
#endif
    Int_t npoints = 0;
#if 0
    for (xi = 0.0; xi < 15.0; xi += 0.1)
      {
        gsl_bspline_eval(xi, B, bw);
        gsl_multifit_linear_est(B, c, cov, &yi, &yerr);
	smooth->SetPoint(npoints, xi, yi);
	npoints++;
      }
#else
    for (i = 0; i < n; i++)
      {
	xi = xData[i];
        gsl_bspline_eval(xi, B, bw);
        gsl_multifit_linear_est(B, c, cov, &yi, &yerr);
#if 0
	smooth->SetPoint(npoints, xi, yi);
#endif
	npoints++;
      }
#endif
#if 0
    smooth->Draw("l"); if (c1) c1->Update();
#endif
    TArrayD XS(nbreak);
    TArrayD YS(nbreak);
    TArrayD ES(nbreak);
    for (UInt_t i = 0; i < nbreak; i++) {
      xi = gsl_bspline_breakpoint(i, bw);
      XS[i] = xi;
      gsl_bspline_eval(xi, B, bw);
      gsl_multifit_linear_est(B, c, cov, &yi, &yerr);
      YS[i] = yi;
    }
    spline = new TSpline3("TSpline3 smoothing", XS.GetArray(), YS.GetArray(), nbreak,opt);
    //    spline = new TSpline5("TSpline5 smoothing", XS.GetArray(), YS.GetArray(), nbreak); //,"b1e1");
    spline->SetLineColor(4);
    spline->SetLineWidth(4);
    spline->SetMarkerColor(4);
    spline->SetMarkerSize(2);
    spline->Draw("samelP");  if (c1) c1->Update();

  }

  gsl_rng_free(r);
  gsl_bspline_free(bw);
  gsl_vector_free(B);
  gsl_vector_free(x);
  gsl_vector_free(y);
  gsl_matrix_free(X);
  gsl_vector_free(c);
  gsl_vector_free(w);
  gsl_matrix_free(cov);
  gsl_multifit_linear_free(mw);
} 
//________________________________________________________________________________
void gsl_splineFit(Int_t K, Int_t n, Int_t nbreak) {
  TF1 *F = new TF1("F","TMath::Cos(x) * TMath::Exp(-0.1 * x)", 0., 15.);
  F->Draw();  if (c1) c1->Update();

  //  if (! gRandom) gRandom = new TRandom3();
  TArrayD xData(n);
  TArrayD yData(n);
  TArrayD eData(n);
  for (Int_t i = 0; i < n; ++i)
    {
      double sigma;
      double xi = (15.0 / (n - 1)) * i;
      Double_t yi = F->Eval(xi);
      sigma = 0.1 * yi;
      eData[i] = sigma;
      yi = gRandom->Gaus(yi, sigma);
      xData[i] = xi;
      yData[i] = yi;
      eData[i] = sigma;
    }
  TGraphErrors *data = new TGraphErrors(n, xData.GetArray(), yData.GetArray(), 0, eData.GetArray());
  data->Draw("p");  if (c1) c1->Update();
#if 0
  TArrayD xKnot(nbreak);
  Double_t a = 0;
  Double_t b = 15;
  Double_t d = (b - a)/(nbreak - 1);
  for (Int_t i = 0; i < nbreak; i++) xKnot[i] = a + i*d;
  
  gsl_splineFit(xData.GetArray(), yData.GetArray(), eData.GetArray(), xKnot.GetArray() , K, n, nbreak);
#else 
  Int_t nknots = 12;
  Double_t xKnots[12] = { 0, 0.5, 1.55, 3.1, 4.75, 6.2, 7.75, 9.5, 11.,  12.5, 14., 15.};
  gsl_splineFit(xData.GetArray(), yData.GetArray(), eData.GetArray(), xKnots , K, n, nknots);
#endif
}
//________________________________________________________________________________
struct MyDerivSpline { 
   MyDerivSpline(TSpline3 * f): fSpline(f) {}
   double operator() (double *x, double * )  const { 
      return fSpline->Derivative(*x);
   }
   TSpline3 * fSpline; 
};
//________________________________________________________________________________
TF1 *Derivative(TSpline3 *f1) {
  MyDerivSpline * deriv = new MyDerivSpline(f1);
  TString name("der_");
  name += f1->GetName();
  TF1 * f2 = new TF1(name,deriv, f1->GetXmin(), f1->GetXmax(), 0, "MyDerivSpline"); 
  return f2;
}
//________________________________________________________________________________
void MakeCintFile(const Char_t *tableName = "spline3dNdx") {
  TString fOut =  Form("%s.C", tableName);
  ofstream out;
  cout << "Create " << fOut.Data() << endl;
  out.open(fOut.Data());
  out << "TDataSet *CreateTable() {" << endl;
  out << "  if (!gROOT->GetClass(\"St_spline3\")) return 0;" << endl;
  out << "  Int_t nrows = 1;" << endl;
  out << "  St_spline3 *tableSet = new St_spline3(\"" << tableName << "\",nrows);" << endl;
  out << "  spline3_st row;" << endl; 
  out << "  memset(&row,0,tableSet->GetRowSize());" << endl;
  Int_t nknots = spline->GetNp();
  out << "  row.nknots = " << nknots << ";" << endl;
  TArrayD X(nknots), Y(nknots); 
  Double_t *x = X.GetArray();
  Double_t *y = Y.GetArray();
  for (Int_t i = 0; i < nknots; i++) {
    spline->GetKnot(i, x[i], y[i]);
  }
  out << "  Double_t X[" << nknots << "] = {";
  for (Int_t i = 0; i < nknots; i++) {
    out << x[i];
    if (i < nknots - 1) out << ",";
    else                out << "};" << endl;
  }
  out << "  Double_t Y[" << nknots << "] = {";
  for (Int_t i = 0; i < nknots; i++) {
    out << y[i];
    if (i < nknots - 1) out << ",";
    else                out << "};" << endl;
  }
  out << "  for (Int_t i = 0; i < " << nknots << "; i++) {row.Xknots[i] = X[i]; row.Yknots[i] = Y[i];}" << endl;
  if (Option.Length() > 0) out << "  memcpy(&row.option,\"" << Option.Data() << "\"," << Option.Length() << ");" << endl;
  out << "  tableSet->AddAt(&row);" << endl;
  out << "  return (TDataSet *)tableSet;" << endl;
  out << "}" << endl;
  out.close(); 
}
//________________________________________________________________________________
void LndNdxL10Fit() {
  const Int_t K = 4;
  TFile *_file0 = TFile::Open("$STAR/StarDb/dEdxModel/dNdx_Bichsel.root");
  if (!_file0) return;
  TH1D *LndNdxL10 = (TH1D *) _file0->Get("LndNdxL10");
  if (! LndNdxL10) return;
  LndNdxL10->Draw(); if (c1) c1->Update();
  Int_t n = LndNdxL10->GetNbinsX();
  TArrayD xData(n);
  TArrayD yData(n);
  TArrayD eData(n);
  for (Int_t i = 0; i < n; i++) {
    xData[i] = LndNdxL10->GetBinCenter(i+1);
    yData[i] = LndNdxL10->GetBinContent(i+1);
    eData[i] = 2e-3;
  }  
  Double_t a = LndNdxL10->GetXaxis()->GetXmin();
  Double_t b = LndNdxL10->GetXaxis()->GetXmax();
#if 0  
  Int_t nknots = 24; // chisq/dof = 8.295837e-02, Rsq = 1.00000
  TArrayD xKnots(nknots);
  Double_t d = (b - a)/(nknots - 1);
  for (Int_t i = 0; i < nknots; i++) xKnots[i] = a + i*d;
#else
#if 0
  Double_t xKnots[] = { a, -1.5, -1.0, -0.75, -0.50, -0.25, 0.0, 0.25, 0.5, 0.75, 1.00, 1.25, 1.50, 1.75, 2.00, 3.00, 4.00, b};
  Int_t nknots = sizeof(xKnots)/sizeof(Double_t); cout << "nknots = " << nknots << endl; // nknots = 18, chisq/dof = 1.728774e-01, Rsq = 1.00000
#else
#if 0
  Double_t xKnots[] = { a, -1.5, -1.0, -0.50, 0.0, 0.25, 0.5, 0.75, 1.00, 1.50, 2.00, 4.00, b};
  Int_t nknots = sizeof(xKnots)/sizeof(Double_t); cout << "nknots = " << nknots << endl; // nknots = 13, chisq/dof = 2.023867e+00, Rsq = 0.999998
#else
  Double_t xKnots[] = { a, -1.5, -1.0, -0.50, 0.0, 0.25, 0.5, 0.75, 1.00, 1.50, 2.00, 3.00, 4.00, b};
  Int_t nknots = sizeof(xKnots)/sizeof(Double_t); cout << "nknots = " << nknots << endl; // nknots = 14, chisq/dof = 9.453211e-01, Rsq = 0.999999
#endif
#endif
  gsl_splineFit(xData.GetArray(), yData.GetArray(), eData.GetArray(), xKnots, K, n, nknots, "");
#endif  
  MakeCintFile("spline3LndNdxL10");
}
//________________________________________________________________________________
void gsl_splineFit(TMultiGraph *mg) {
  const Int_t K = 4;
  if (! mg) return;
  mg->Draw("axp"); if (c1) c1->Update();
  Int_t n = 5000;
  TArrayD xData(n);
  TArrayD yData(n);
  TArrayD eData(n);
  TIter next(mg->GetListOfGraphs());
  TGraphErrors *g = 0;
  Int_t np = 0;
  Double_t a = 9999;
  Double_t b =-9999;
  while ((g = (TGraphErrors *) next())) {
    Int_t N = g->GetN();
    Double_t *x = g->GetX();
    Double_t *y = g->GetY();
    Double_t *e = g->GetEY();
    for (Int_t i = 0; i < N; i++) {
      xData[np] = x[i];
      if (x[i] < a) a = x[i];
      if (x[i] > b) b = x[i];
      yData[np] = y[i];
      eData[np] = e[i];
      np++;
    }
  }
#if 1 
#if 0 // Electrons
  // Electorns: chisq/dof = 2.600738e+00, Rsq = 0.999662
  Int_t nknots = 24; // chisq/dof = 2.600738e+00, Rsq = 0.999662
#else
#if 0 // Pions
  // Int_t nknots = 24; // Pions: chisq/dof = 4.852640e+02, Rsq = 0.962264
  // Int_t nknots = 12; // Pions chisq/dof = 4.884465e+02, Rsq = 0.961617
  Int_t nknots = 16; // Pions chisq/dof = 4.828386e+02, Rsq = 0.962190
#else // Proton
  //  Int_t nknots = 24; // Protons: chisq/dof = 2.794028e+00, Rsq = 0.998888
  //  Int_t nknots = 12; // chisq/dof = 9.333136e+00, Rsq = 0.996176
  Int_t nknots = 16; // chisq/dof = 4.222781e+00, Rsq = 0.998286
#endif 
#endif
  TArrayD xKnot(nknots);
  Double_t d = (b - a)/(nknots - 1);
  for (Int_t i = 0; i < nknots; i++) xKnot[i] = a + i*d;
  Double_t *xKnots = xKnot.GetArray();
#else //
#if 0 // Electorn 
  //  Int_t nknots = 24;                                       // chisq/dof = 8.295837e-02, Rsq = 1.00000
  //  Double_t xKnots[] = { a, 2.2, 2.3, 2.45, 2.55,  2.8, b}; //  nknots= 7,  chisq/dof = 2.874107e+01, Rsq = 0.996137
  //  Double_t xKnots[] = { a, 2.1, 2.2, 2.3, 2.4, 2.45, 2.55,  2.8, 3.0, 3.2, b}; // nknots = 11 chisq/dof = 6.072608e+00, Rsq = 0.999190
  //  Double_t xKnots[] = { a, 2.15, 2.2, 2.25, 2.3, 2.35, 2.4, 2.45, 2.55,  2.8, 3.0, 3.2, 3.25, b}; // nknots = 14 chisq/dof = 5.763840e+00, Rsq = 0.999235
  //  Double_t xKnots[] = { a, 2.12, 2.15, 2.2, 2.25, 2.3, 2.35, 2.4, 2.45, 2.55,  2.8, 3.0, 3.2, 3.25, b}; // nknots = 15 chisq/dof = 5.774668e+00, Rsq = 0.999235
  //  Double_t xKnots[] = { a, 2.15, 2.2, 2.25, 2.3, 2.35, 2.4, 2.45, 2.50, 2.55, 2.60,  2.8, 2.90, 3.0, 3.2, 3.45, b}; // nknots = 17 chisq/dof = 3.076374e+00, Rsq = 0.999594
  //  Double_t xKnots[] = { a, 2.15, 2.20, 2.25, 2.30, 2.35, 2.40, 2.45, 2.50, 2.55, 2.60, 2.70, 2.80, 2.90, 3.0, 3.20, 3.30, 3.40, b}; // nknots = 19 chisq/dof = 2.629976e+00, Rsq = 0.999654
  Double_t xKnots[] = { a, 2.12, 2.15, 2.20, 2.25, 2.30, 2.35, 2.40, 2.45, 2.50, 2.55, 2.60, 2.70, 2.80, 2.90, 3.0, 3.20, 3.30, 3.40, b}; // nknots = 20 chisq/dof = 2.634199e+00, Rsq = 0.999655
#else // Pions 
  //  Double_t xKnots[] = { a, -0.20, -0.10, 0.05, 0.15, 0.50, 1.0, b};
  //  Double_t xKnots[] = { a, a+0.05, -0.20,-0.15,  -0.10, 0.05, 0.15, 0.30, 0.40, 0.50, 0.60, 0.70, 0.80, 1.0, b}; // nknots = 15 chisq/dof = 4.842658e+02, Rsq = 0.962045
  Double_t xKnots[] = { a, a+0.02, -0.20,-0.15,  -0.10, 0.05, 0.15, 0.30, 0.40, 0.50, 0.60, 0.70, 0.80, 1.00, 1.20,1.40, b}; // nknots = 17 chisq/dof = 4.835079e+02, Rsq = 0.962170
  Int_t nknots = sizeof(xKnots)/sizeof(Double_t); cout << "nknots = " << nknots << endl; 
#endif
#endif
  gsl_splineFit(xData.GetArray(), yData.GetArray(), eData.GetArray(), xKnots, K, np, nknots, "");
  MakeCintFile(mg->GetName());
}
//________________________________________________________________________________
void gsl_splineFit(Int_t k = 1) {
  c1 = (TCanvas *) gROOT->GetListOfCanvases()->FindObject("c1");
  if (c1) c1->Clear();
  else    c1 = new TCanvas("c1","c1",600,600);
  if (k == 0) {
  // Test 
    gsl_splineFit(4,200,10);
  } else if (k == 1) {
    // LndNdxLoh10
    LndNdxL10Fit();
  }
}
//________________________________________________________________________________
void HistFit(TH1 *hist = 0) {
  if (! hist) return;
  const Int_t K = 4;
  hist->Draw(); if (c1) c1->Update();
  Int_t n = hist->GetNbinsX();
  TArrayD xData(n);
  TArrayD yData(n);
  TArrayD eData(n);
  Int_t i1 = 9999;
  Int_t i2 = -1;
  Double_t a = 0, b = 0;
  Int_t np = 0;
  TAxis *ax = hist->GetXaxis();
  for (Int_t i = 1; i <= n; i++) {
    Double_t e = hist->GetBinError(i);
    if (e <= 0) continue;
    eData[np] = e;
    xData[np] = hist->GetBinCenter(i);
    yData[np] = hist->GetBinContent(i);
    np++;
    if (i1 > i) {i1 = i; a = ax->GetBinLowEdge(i1);}
    if (i2 < i) {i2 = i; b = ax->GetBinUpEdge(i2);}
  }  
  Int_t nknots = 4; // chisq/dof = 8.295837e-02, Rsq = 1.00000
  TArrayD xKnots(nknots);
  Double_t d = (b - a)/(nknots - 1);
  for (Int_t i = 0; i < nknots; i++) xKnots[i] = a + i*d;
  gsl_splineFit(xData.GetArray(), yData.GetArray(), eData.GetArray(), xKnots.GetArray(), K, n, nknots, "");
  //  MakeCintFile("spline3hist");
}
