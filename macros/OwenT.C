// root.exe lgsl.C OwenT.C+
//#define __TEST_GSL__
#include <stdio.h>
#ifdef __TEST_GSL__
#include <math.h>
#include <gsl/gsl_integration.h>
struct params {
    double h;
};
double integrand(double x, void *p) {
    struct params *params = (struct params *)p;
    double h = params->h;
    return exp(-0.5 * h * h * (1 + x * x)) / (1 + x * x);
}

double owens_t(double h, double a) {
    gsl_integration_workspace *w = gsl_integration_workspace_alloc(1000);
    gsl_function F;
    struct params p = {h};
    F.function = &integrand;
    F.params = &p;

    double result, error;
    gsl_integration_qags(&F, 0, a, 0, 1e-7, 1000, w, &result, &error);
    gsl_integration_workspace_free(w);

    return result / (2 * M_PI);
}
/******************************************************************************/

double tfn ( double x, double fx )

/******************************************************************************/
/*
  Purpose:

    tfn() calculates the T-function of Owen.

  Licensing:

    This code is distributed under the MIT license. 

  Modified:

    16 January 2008

  Author:

    Original FORTRAN77 version by JC Young, Christoph Minder.
    This version by John Burkardt.

  Reference:

    MA Porter, DJ Winstanley,
    Remark AS R30:
    A Remark on Algorithm AS76:
    An Integral Useful in Calculating Noncentral T and Bivariate
    Normal Probabilities,
    Applied Statistics,
    Volume 28, Number 1, 1979, page 113.

    JC Young, Christoph Minder,
    Algorithm AS 76: 
    An Algorithm Useful in Calculating Non-Central T and 
    Bivariate Normal Distributions,
    Applied Statistics,
    Volume 23, Number 3, 1974, pages 455-457.

  Input:

    double X, FX, the parameters of the function.

  Output:

    double TFN, the value of the T-function.
*/
{
# define NG 5

  double fxs;
  int i;
  double r[NG] = {
    0.1477621, 
    0.1346334, 
    0.1095432, 
    0.0747257, 
    0.0333357 };
  double r1;
  double r2;
  double rt;
  double tp = 0.159155;
  double tv1 = 1.0E-35;
  double tv2 = 15.0;
  double tv3 = 15.0;
  double tv4 = 1.0E-05;
  double u[NG] = {
    0.0744372, 
    0.2166977, 
    0.3397048,
    0.4325317, 
    0.4869533 };
  double value;
  double x1;
  double x2;
  double xs;
/*
  Test for X near zero.
*/
  if ( fabs ( x ) < tv1 )
  {
    value = tp * atan ( fx );
    return value;
  }
/*
  Test for large values of abs(X).
*/
  if ( tv2 < fabs ( x ) )
  {
    value = 0.0;
    return value;
  }
/*
  Test for FX near zero.
*/
  if ( fabs ( fx ) < tv1 )
  {
    value = 0.0;
    return value;
  }
/*
  Test whether abs ( FX ) is so large that it must be truncated.
*/
  xs = - 0.5 * x * x;
  x2 = fx;
  fxs = fx * fx;
/*
  Computation of truncation point by Newton iteration.
*/
  if ( tv3 <= log ( 1.0 + fxs ) - xs * fxs )
  {
    x1 = 0.5 * fx;
    fxs = 0.25 * fxs;

    for ( ; ; )
    {
      rt = fxs + 1.0;

      x2 = x1 + ( xs * fxs + tv3 - log ( rt ) ) 
      / ( 2.0 * x1 * ( 1.0 / rt - xs ) );

      fxs = x2 * x2;

      if ( fabs ( x2 - x1 ) < tv4 )
      {
        break;
      }
      x1 = x2;
    }
  }
/*
  Gaussian quadrature.
*/
  rt = 0.0;
  for ( i = 0; i < NG; i++ )
  {
    r1 = 1.0 + fxs * pow ( 0.5 + u[i], 2 );
    r2 = 1.0 + fxs * pow ( 0.5 - u[i], 2 );

    rt = rt + r[i] * ( exp ( xs * r1 ) / r1 + exp ( xs * r2 ) / r2 );
  }

  value = rt * x2 * tp;

  return value;
# undef NG
}
#endif /*  __TEST_GSL__ */
#include "TF1.h"
#include "TF2.h"
#include "TMath.h"
#include "TROOT.h"
namespace GausSW {
//--------------------------------------------------------------------------------
Double_t owen_integrand(Double_t *x, Double_t *p) {
  Double_t t = x[0];
  Double_t h = p[0];
  return TMath::Exp(-0.5*h*h*(1 + t*t))/(1 + t*t);
}
//--------------------------------------------------------------------------------
TF1 *Owen_Integrand() {
  static const Char_t *name = "Owen_Integrand";
  static TF1 *f = 0;
  if (! f) {
    f = (TF1 *) gROOT->GetListOfFunctions()->FindObject(name);
    if (! f) f = new TF1(name,owen_integrand,-5,5,1);
  }
  return f;
}
//--------------------------------------------------------------------------------
Double_t owenTfunc(Double_t *x, Double_t *p) {
  Double_t h = TMath::Abs(x[0]);
  Double_t a = x[1];
  if (TMath::Abs(a) < 1e-12) return 0;
  if (TMath::Abs(h) < 1e-12) return TMath::ATan(a)/TMath::TwoPi();
  TF1 *f = Owen_Integrand();
  f->SetParameter(0,h);
  Double_t value = f->Integral(0, a)/TMath::TwoPi();
  return value;
}
//________________________________________________________________________________
TF2 *OwenTFunc() {
  static const Char_t *name = "OwenT";
  static TF2 *f = 0;
  if (! f) {
    f = (TF2 *) gROOT->GetListOfFunctions()->FindObject(name);
    if (! f) {
      f = new TF2(name,owenTfunc,0,5,-5,5);
//       f->GetXaxis()->SetTitle("h");
//       f->GetYaxis()->SetTitle("a");
    }
  }
  return f;
}
//________________________________________________________________________________
Double_t Phi(Double_t x) {
  return  0.5*(1 + TMath::Erf(x/TMath::Sqrt2()));
}
//________________________________________________________________________________
Double_t phi(Double_t x) {
  static TF1 *gausn = 0;
  static Double_t par[3] = {1, 0, 1};
  if (! gausn) {
    if (!gROOT->GetListOfFunctions()->FindObject("gausn")) TF1::InitStandardFunctions();
    gausn = (TF1 *) gROOT->GetListOfFunctions()->FindObject("gausn");
  }
  return gausn->EvalPar(&x, par);
}
//________________________________________________________________________________
Double_t gauswPDFunc1(Double_t *x, Double_t *p) {
  Double_t alpha = p[0];
  return 2*phi(x[0])*Phi(x[0]*alpha);
}
//________________________________________________________________________________
TF1 *GauswPDF1() {
  static const Char_t *name = "GauswPDF1";
  static TF1 *f = 0;
  if (! f) {
    f = (TF1 *) gROOT->GetListOfFunctions()->FindObject(name);
    if (! f) f = new TF1(name,gauswPDFunc1,-5,5,1);
  }
  f->SetParameter(0,0);
  return f;
}
//________________________________________________________________________________
Double_t  PDFfunc(Double_t *x, Double_t *p) {
  Double_t ksi   = p[0];
  Double_t w     = p[1];
  Double_t alpha = p[2];
  Double_t t  = {(x[0] - ksi)/w};
  return GauswPDF1()->EvalPar(&t,&alpha);
}
//________________________________________________________________________________
TF1 *PDF() {
  static const Char_t *name =  "GauswPDF";
  static TF1 *f = 0;
  if (! f) {
    f = (TF1 *) gROOT->GetListOfFunctions()->FindObject(name);
    if (! f) f = new TF1(name,PDFfunc,-5,5,3);
    f->SetParameter(0,0);
    f->SetParameter(1,1);
    f->SetParameter(2,0);
  }
  return f;
}
//________________________________________________________________________________
Double_t CDFfunc(Double_t *x, Double_t *p) {
  Double_t ksi   = p[0];
  Double_t w     = p[1];
  Double_t alpha = p[2];
  Double_t t     = (x[0]-ksi)/w;
  Double_t u     = TMath::Abs(t);
  return Phi(t) - 2*OwenTFunc()->EvalPar(&u,&alpha);
}
//________________________________________________________________________________
TF1 *CDF() {
  static const Char_t *name =  "GauswCDF";
  static TF1 *f = 0;
  if (! f) {
    f = (TF1 *) gROOT->GetListOfFunctions()->FindObject(name);
    if (! f) f = new TF1(name,CDFfunc,-5,5,3);
    f->SetParameter(0,0);
    f->SetParameter(1,1);
    f->SetParameter(2,0);
  }
  return f;
}
}
//--------------------------------------------------------------------------------
int OwenT() {
    double h = 1.0;
    double a = 0.5;
#ifdef __TEST_GSL__
    double val = owens_t(h, a);
    printf("Owen's T(%f, %f) = %.12f\n", h, a, val);
    double val0 = tfn(h, a);
    printf("tfn(%f, %f) = %.12f\n", h, a, val0);
#endif /*  __TEST_GSL__ */
    double val1 = GausSW::OwenTFunc()->Eval(h,a);
    printf("Owen's TF(%f, %f) = %.12f\n", h, a, val1);
    h = 2.0;
    a = 1.5;
#ifdef __TEST_GSL__
    val = owens_t(h, a);
    printf("Owen's T(%f, %f) = %.12f\n", h, a, val);
    val0 = tfn(h, a);
    printf("tfn(%f, %f) = %.12f\n", h, a, val0);
#endif /*  __TEST_GSL__ */
    val1 = GausSW::OwenTFunc()->Eval(h,a);
    printf("Owen's TF(%f, %f) = %.12f\n", h, a, val1);
    h = 2.0;
    a = 0.5;
#ifdef __TEST_GSL__
    val = owens_t(h, a);
    printf("Owen's T(%f, %f) = %.12f\n", h, a, val);
    val0 = tfn(h, a);
    printf("tfn(%f, %f) = %.12f\n", h, a, val0);
#endif /*  __TEST_GSL__ */
    val1 = GausSW::OwenTFunc()->Eval(h,a);
    printf("Owen's TF(%f, %f) = %.12f\n", h, a, val1);
    return 0;
}
