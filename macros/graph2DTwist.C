//Fitting a TGraph2D
//Author: Olivier Couet
#include "Riostream.h"
#include <TMath.h>
#include <TGraph2D.h>
#include <TGraphErrors.h>
#include <TGraph2DErrors.h>
#include <TRandom.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TF1.h>
#include <TF2.h>
#include <TH1.h>
#include "TString.h"
#include "TList.h"
TGraph2DErrors *graphs2D[2][2] = {0};
TGraphErrors *graphs1D[2][2][2] = {0};

TCanvas* graph2DTwist()
{
   gStyle->SetOptStat(0);
   gStyle->SetOptFit();

  /*          Int_t i,j,k;
    (West - East RF)/2                                7p7GeV_2021                     Rotation                      -Rotation                       Half   linear fit i = 0; j = 0; k = 0; TGraphErrors *g = graphs1D[i][j][k]; g->Draw("axp"); 
    //                                                                                                                                                                            g->Fit("pol1"); -pol1->GetParameter(0)/pol1->GetParameter(1)
    dX_West_East = (  C2 * beta + C1 * alpha ) * Z =  8.19131e-04 +/-  2.52889e-04   -1.33204e-01 +/-  2.72263e-04   1.35796e-01 +/-  1.80888e-04  -6.71910e-02  +/-   1.81168e-04  [0][0][0] => alphaRF  =   -0.00192773 [0][0][1]  betaRF   = -0.00192773
    dY_West_East = (  C1 * beta - C2 * alpha ) * Z =  8.69316e-02 +/-  2.46744e-04    2.28086e-01 +/-  2.45568e-04  -5.49923e-02 +/-  1.78939e-04   1.57203e-01  +/-   1.79002e-04  
    (West - East FF)/2														      				      
    dX_West_East = (  C2 * beta - C1 * alpha ) * Z =  7.44167e-02 +/-  1.41976e-03    2.09719e-01 +/-  1.33055e-03  -6.42013e-02 +/-  1.33096e-03   1.41776e-01  +/-   1.36076e-03 
    dY_West_East = (- C1 * beta - C2 * alpha ) * Z =  1.48260e-02 +/-  1.38702e-03   -7.66208e-02 +/-  1.37434e-03   1.08627e-01 +/-  1.36185e-03  -2.97543e-02  +/-   1.40090e-03 
    																      				      
    /(West - East RF)/2                                OO200_2021 								      				      
    dX_West_East = (  C2 * beta + C1 * alpha ) * Z =  -8.55745e-04 +/-  5.18769e-04  -1.39317e-01 +/-  2.82273e-04   1.35231e-01  +/- 2.81101e-04  -7.06604e-02   +/-  2.81489e-04 
    dY_West_East = (  C1 * beta - C2 * alpha ) * Z =   8.52597e-02 +/-  4.99806e-04   2.25767e-01 +/-  2.74328e-04  -5.57666e-02  +/- 2.74506e-04   1.55351e-01   +/-  2.74057e-04
    (West - East FF)/2														      				      
    dX_West_East = (  C2 * beta - C1 * alpha ) * Z =   7.16109e-02 +/-  2.24580e-04   2.08534e-01 +/-  2.10072e-04  -6.52984e-02  +/- 2.10098e-04   1.40050e-01   +/-  2.10115e-04 
    dY_West_East = (- C1 * beta - C2 * alpha ) * Z =   1.26663e-02 +/-  2.13613e-04  -8.07938e-02 +/-  2.08592e-04   1.06110e-01  +/- 2.08276e-04  -3.39106e-02   +/-  2.08607e-04
  */
   enum {NP = 4, NF = 2, NXY = 2};
   /*
   //Id      alpha,       beta,   gamma 
   { 0,  -0.962799,  -0.418479, 0.00000},//  RF
   { 1,   0.209915,   0.857119, 0.00000} //  FF
   */
   //                           RF        FF
   Double_t alpha[2]  = {-0.962799, 0.209915};
   Double_t beta[2]   = {-0.418479, 0.857119};
   //             F  AB
   Double_t ab[NP][NF][2]  = {
     {{0, 0},  // RF
      {0, 0}}, // FF
     {{alpha[0], beta[0]},  // RF
      {alpha[1], beta[1]}}, // FF
     {{-alpha[0], -beta[0]},  // RF
      {-alpha[1], -beta[1]}}, // FF
     {{0.5*alpha[0], 0.5*beta[0]},  // RF
      {0.5*alpha[1], 0.5*beta[1]}}  // FF
   };
   //            E       XY
   //   Double_t Data[2][NF][NXY][NP][2] = {
   //   Double_t Data[2][2][2][4][2] = {
   Double_t Data[8][4][2] = {
     //     (West - East RF)/2                                7p7GeV_2021                     Rotation                      -Rotation                       Half
     /* dX_West_East = (  C2 * beta + C1 * alpha ) * Z = */ {{ 8.19131e-04, 2.52889e-04}, {-1.33204e-01, 2.72263e-04}, { 1.35796e-01, 1.80888e-04}, {-6.71910e-02 ,  1.81168e-04}},
     /* dY_West_East = (  C1 * beta - C2 * alpha ) * Z = */ {{ 8.69316e-02, 2.46744e-04}, { 2.28086e-01, 2.45568e-04}, {-5.49923e-02, 1.78939e-04}, { 1.57203e-01 ,  1.79002e-04}},
     //    (West - East FF)/2														      				      
     /* dX_West_East = (  C2 * beta - C1 * alpha ) * Z = */ {{ 7.44167e-02, 1.41976e-03}, { 2.09719e-01, 1.33055e-03}, {-6.42013e-02, 1.33096e-03}, { 1.41776e-01 ,  1.36076e-03}},
     /* dY_West_East = (- C1 * beta - C2 * alpha ) * Z = */ {{ 1.48260e-02, 1.38702e-03}, {-7.66208e-02, 1.37434e-03}, { 1.08627e-01, 1.36185e-03}, {-2.97543e-02 ,  1.40090e-03}},
     //    /(West - East RF)/2                                OO200_2021 								      				      
     /* dX_West_East = (  C2 * beta + C1 * alpha ) * Z = */ {{-8.55745e-04, 5.18769e-04}, {-1.39317e-01, 2.82273e-04}, { 1.35231e-01, 2.81101e-04}, {-7.06604e-02  , 2.81489e-04}},
     /* dY_West_East = (  C1 * beta - C2 * alpha ) * Z = */ {{ 8.52597e-02, 4.99806e-04}, { 2.25767e-01, 2.74328e-04}, {-5.57666e-02 ,2.74506e-04}, { 1.55351e-01  , 2.74057e-04}},
     //    (West - East FF)/2														      				      
     /* dX_West_East = (  C2 * beta - C1 * alpha ) * Z = */ {{ 7.16109e-02, 2.24580e-04}, { 2.08534e-01, 2.10072e-04}, {-6.52984e-02 ,2.10098e-04}, { 1.40050e-01  , 2.10115e-04}}, 
     /* dY_West_East = (- C1 * beta - C2 * alpha ) * Z = */ {{ 1.26663e-02, 2.13613e-04}, {-8.07938e-02, 2.08592e-04}, { 1.06110e-01 ,2.08276e-04}, {-3.39106e-02  , 2.08607e-04}}
   };
   TCanvas *c0 = 0;
   TCanvas *c = new TCanvas("c","dX & dY (West - East)/2 for RF & FF",0,0,600,800);
   c->Divide(2,2);
   const Char_t *XY[2] = {"X", "Y"};
   const Char_t *field[2] = {"RF", "FF"};
   const Char_t *abn[2] = {"alpha", "beta"};
   for (Int_t xy = 0; xy < NXY; xy++) {
     for (Int_t rf = 0; rf < NF; rf++) {
       graphs2D[xy][rf] = new TGraph2DErrors;
       graphs2D[xy][rf]->SetName(Form("d%s%s",XY[xy],field[rf]));
       graphs2D[xy][rf]->SetTitle(Form("d%s (West - East)/2 for %s : #alpha : #beta ",XY[xy],field[rf]));
       graphs1D[xy][rf][0] = new TGraphErrors;
       graphs1D[xy][rf][0]->SetName(Form("d%s%sA",XY[xy],field[rf]));
       graphs1D[xy][rf][0]->SetTitle(Form("d%s (West - East)/2 for %s : #alpha",XY[xy],field[rf]));
       graphs1D[xy][rf][1] = new TGraphErrors;
       graphs1D[xy][rf][1]->SetName(Form("d%s%sB",XY[xy],field[rf]));
       graphs1D[xy][rf][1]->SetTitle(Form("d%s (West - East)/2 for %s : #beta",XY[xy],field[rf]));
       for (Int_t j = 0; j < 2; j++) {// Energy
	 Int_t k = xy + 2*(rf + 2*j); 
	 for (Int_t i = 0; i < NP; i++) {
	   graphs2D[xy][rf]->SetPoint(i,ab[i][rf][0],ab[i][rf][1],Data[k][i][0]);
	   graphs2D[xy][rf]->SetPointError(i,0.,0.,Data[k][i][1]);
	   graphs1D[xy][rf][0]->SetPoint(i,ab[i][rf][0],Data[k][i][0]);
	   graphs1D[xy][rf][0]->SetPointError(i,0.,Data[k][i][1]);
	   graphs1D[xy][rf][1]->SetPoint(i,ab[i][rf][1],Data[k][i][0]);
	   graphs1D[xy][rf][1]->SetPointError(i,0.,Data[k][i][1]);
	 }
       }
       for (Int_t m = 0; m < 2; m++) {
	 TGraphErrors *g = graphs1D[xy][rf][m];
	 c0 = new TCanvas(Form("c%s",g->GetName()),g->GetTitle());
	 g->Draw("axp");
	 g->Fit("pol1","q");
	 TF1 *pol1 = (TF1 *) g->GetListOfFunctions()->FindObject("pol1");
	 cout << Form("%30s: %8.4f", g->GetTitle(), pol1->GetParameter(0)/pol1->GetParameter(1)) << endl;
       }
       c->cd(2*xy + rf + 1);
       graphs2D[xy][rf]->Draw("axp");
     }
   }
   return c;
}
/*
  dX (West - East)/2 for RF : #alpha:  -0.0135 dX (West - East)/2 for RF : #beta:  -0.0059
  dY (West - East)/2 for RF : #alpha:  -0.5815 dY (West - East)/2 for RF : #beta:  -0.2528

  dX (West - East)/2 for FF : #alpha:   0.1098 dX (West - East)/2 for FF : #beta:   0.4483
  dY (West - East)/2 for FF : #alpha:  -0.0285 dY (West - East)/2 for FF : #beta:  -0.1165
 */
