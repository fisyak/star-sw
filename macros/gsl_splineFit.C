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
#include "TPolyMarker.h"
#include "TF1.h"
#include "TSpline.h"
#include "TArrayD.h"
void gsl_splineFit(Int_t N = 200, Int_t NCOEFFS = 12)
{
  Int_t K = 4;
  Int_t NBREAK =  NCOEFFS + 2 - K;
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
  TGraphErrors *data = new TGraphErrors();
  TF1 *F = new TF1("F","TMath::Cos(x) * TMath::Exp(-0.1 * x)", 0., 15.);
  F->Draw();
  for (i = 0; i < n; ++i)
    {
      double sigma;
      double xi = (15.0 / (N - 1)) * i;
      Double_t yi = F->Eval(xi);
      sigma = 0.1 * yi;
      dy = gsl_ran_gaussian(r, sigma);
      yi += dy;

      gsl_vector_set(x, i, xi);
      gsl_vector_set(y, i, yi);
      gsl_vector_set(w, i, 1.0 / (sigma * sigma));
      data->SetPoint(i,xi,yi);
      data->SetPointError(i, 0, sigma);
    }
  data->Draw("p");
#if 0
  /* use uniform breakpoints on [0, 15] */
  gsl_bspline_knots_uniform(0.0, 15.0, bw);
#else
  TArrayD xKnot(nbreak);
  Double_t a = 0;
  Double_t b = 15;
  Double_t d = (b - a)/(nbreak - 1);
  for (UInt_t i = 0; i < nbreak; i++) xKnot[i] = a + i*d;
  gsl_vector *breakpts = gsl_vector_alloc(nbreak);
  for (UInt_t i = 0; i < nbreak; i++) gsl_vector_set(breakpts, i, xKnot[i]);
  gsl_bspline_knots(breakpts, bw);
#endif
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
    TGraph *smooth = new TGraph();
    smooth->SetLineColor(2);
    smooth->SetLineWidth(4);
    Int_t npoints = 0;

    for (xi = 0.0; xi < 15.0; xi += 0.1)
      {
        gsl_bspline_eval(xi, B, bw);
        gsl_multifit_linear_est(B, c, cov, &yi, &yerr);
	smooth->SetPoint(npoints, xi, yi);
	npoints++;
      }
    smooth->Draw("l");
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
    TSpline3 *spline = new TSpline3("TSpline3 smoothing", XS.GetArray(), YS.GetArray(), nbreak);
    spline->SetLineColor(4);
    spline->SetLineWidth(4);
    spline->SetMarkerColor(4);
    spline->SetMarkerSize(2);
    spline->Draw("samelP");

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
