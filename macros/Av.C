#include "TString.h"
#include "Riostream.h"
#include "TMath.h"
using namespace std;
//________________________________________________________________________________
void Av() {
  const Char_t *Lines[8] = {

#if 0 /* 03/04/2024 */
    "MakeRGraph(2024,\"^WAO\",0)                x0 = -0.2573 +/-  0.0061 y0 = -0.4135 +/-  0.0068 R = 54.4995 +/-  0.0046 gamma =  0.16 +/-  0.24", 
    "MakeRGraph(2024,\"^WBO\",0)                x0 = -0.2438 +/-  0.0064 y0 = -0.3092 +/-  0.0103 R =118.8423 +/-  0.0058 gamma =  0.04 +/-  0.16", 
    "MakeRGraph(2024,\"^WCO\",0)                x0 = -0.2923 +/-  0.0066 y0 = -0.3092 +/-  0.0098 R =124.3910 +/-  0.0053 gamma =  0.07 +/-  0.30", 
    "MakeRGraph(2024,\"^WDO\",0)                x0 = -0.3049 +/-  0.0075 y0 = -0.2687 +/-  0.0068 R =190.5176 +/-  0.0051 gamma = -0.18 +/-  0.23", 
																	          
    "MakeRGraph(2024,\"^EAO\",0)                x0 = -0.0269 +/-  0.0061 y0 = -0.2925 +/-  0.0061 R = 54.5000 +/-  0.0043 gamma =  0.72 +/-  0.23", 
    "MakeRGraph(2024,\"^EBO\",0)                x0 =  0.0342 +/-  0.0064 y0 = -0.2596 +/-  0.0103 R =118.8212 +/-  0.0058 gamma =  0.22 +/-  0.17", 
    "MakeRGraph(2024,\"^ECO\",0)                x0 = -0.0243 +/-  0.0064 y0 = -0.3095 +/-  0.0103 R =124.3101 +/-  0.0058 gamma =  0.56 +/-  0.15", 
    "MakeRGraph(2024,\"^EDO\",0)                x0 = -0.0516 +/-  0.0075 y0 = -0.2350 +/-  0.0061 R =190.5970 +/-  0.0047 gamma =  0.19 +/-  0.13"};
#endif
#if 0 /* TPC position from averaged  West ad East Wheel */
    "MakeRGraph(2024,\"^WAO\",0)                x0 =  0.0283 +/-  0.0061 y0 = -0.0809 +/-  0.0068 R = 54.4995 +/-  0.0046 gamma =  0.16 +/-  0.24", 
    "MakeRGraph(2024,\"^WBO\",0)                x0 =  0.0418 +/-  0.0064 y0 =  0.0234 +/-  0.0099 R =118.8423 +/-  0.0057 gamma =  0.04 +/-  0.16", 
    "MakeRGraph(2024,\"^WCO\",0)                x0 = -0.0066 +/-  0.0066 y0 =  0.0234 +/-  0.0098 R =124.3910 +/-  0.0053 gamma =  0.07 +/-  0.30", 
    "MakeRGraph(2024,\"^WDO\",0)                x0 = -0.0193 +/-  0.0075 y0 =  0.0639 +/-  0.0068 R =190.5176 +/-  0.0051 gamma = -0.18 +/-  0.23", 
     																	          
    "MakeRGraph(2024,\"^EAO\",0)                x0 = -0.0279 +/-  0.0061 y0 = -0.0293 +/-  0.0061 R = 54.5000 +/-  0.0043 gamma =  0.72 +/-  0.23", 
    "MakeRGraph(2024,\"^EBO\",0)                x0 =  0.0332 +/-  0.0064 y0 =  0.0036 +/-  0.0103 R =118.8212 +/-  0.0058 gamma =  0.22 +/-  0.17", 
    "MakeRGraph(2024,\"^ECO\",0)                x0 = -0.0253 +/-  0.0064 y0 = -0.0462 +/-  0.0099 R =124.3101 +/-  0.0057 gamma =  0.56 +/-  0.15", 
    "MakeRGraph(2024,\"^EDO\",0)                x0 = -0.0526 +/-  0.0075 y0 =  0.0283 +/-  0.0061 R =190.5970 +/-  0.0047 gamma =  0.19 +/-  0.13"};
#endif
#if 0
    "MakeRGraph(2024,\"^WAO\",0)                x0 =  0.0143 +/-  0.0061 y0 = -0.0827 +/-  0.0068 R = 54.4995 +/-  0.0046 gamma =  0.16 +/-  0.24", 
    "MakeRGraph(2024,\"^WBO\",0)                x0 =  0.0278 +/-  0.0064 y0 =  0.0216 +/-  0.0099 R =118.8423 +/-  0.0057 gamma =  0.04 +/-  0.16", 
    "MakeRGraph(2024,\"^WCO\",0)                x0 = -0.0206 +/-  0.0066 y0 =  0.0216 +/-  0.0098 R =124.3910 +/-  0.0053 gamma =  0.07 +/-  0.30", 
    "MakeRGraph(2024,\"^WDO\",0)                x0 = -0.0333 +/-  0.0075 y0 =  0.0621 +/-  0.0068 R =190.5176 +/-  0.0051 gamma = -0.18 +/-  0.23", 
     																	       
    "MakeRGraph(2024,\"^EAO\",0)                x0 = -0.0119 +/-  0.0061 y0 = -0.0230 +/-  0.0061 R = 54.5000 +/-  0.0043 gamma =  0.38 +/-  0.22", 
    "MakeRGraph(2024,\"^EBO\",0)                x0 =  0.0492 +/-  0.0064 y0 =  0.0099 +/-  0.0103 R =118.8212 +/-  0.0058 gamma = -0.11 +/-  0.17", 
    "MakeRGraph(2024,\"^ECO\",0)                x0 = -0.0093 +/-  0.0064 y0 = -0.0399 +/-  0.0099 R =124.3101 +/-  0.0057 gamma =  0.23 +/-  0.14", 
    "MakeRGraph(2024,\"^EDO\",0)                x0 = -0.0366 +/-  0.0075 y0 =  0.0346 +/-  0.0061 R =190.5970 +/-  0.0047 gamma = -0.15 +/-  0.13"};
#endif
    "MakeRGraph(2024,\"^WAO\",0)                x0 =  0.0143 +/-  0.0061 y0 = -0.0827 +/-  0.0068 R = 54.4995 +/-  0.0046 gamma =  0.16 +/-  0.24", 
    "MakeRGraph(2024,\"^WBO\",0)                x0 =  0.0278 +/-  0.0064 y0 =  0.0216 +/-  0.0099 R =118.8423 +/-  0.0057 gamma =  0.04 +/-  0.16", 
    "MakeRGraph(2024,\"^WCO\",0)                x0 = -0.0206 +/-  0.0066 y0 =  0.0216 +/-  0.0098 R =124.3910 +/-  0.0053 gamma =  0.07 +/-  0.30", 
    "MakeRGraph(2024,\"^WDO\",0)                x0 = -0.0333 +/-  0.0075 y0 =  0.0621 +/-  0.0068 R =190.5176 +/-  0.0051 gamma = -0.18 +/-  0.23", 
     																		    
    "MakeRGraph(2024,\"^EAO\",0)                x0 = -0.0119 +/-  0.0061 y0 = -0.0230 +/-  0.0061 R = 54.5000 +/-  0.0043 gamma =  0.38 +/-  0.22", 
    "MakeRGraph(2024,\"^EBO\",0)                x0 =  0.0492 +/-  0.0064 y0 =  0.0099 +/-  0.0103 R =118.8212 +/-  0.0058 gamma = -0.11 +/-  0.17", 
    "MakeRGraph(2024,\"^ECO\",0)                x0 = -0.0093 +/-  0.0064 y0 = -0.0399 +/-  0.0099 R =124.3101 +/-  0.0057 gamma =  0.23 +/-  0.14", 
    "MakeRGraph(2024,\"^EDO\",0)                x0 = -0.0366 +/-  0.0075 y0 =  0.0346 +/-  0.0061 R =190.5970 +/-  0.0047 gamma = -0.15 +/-  0.13"};
  const Char_t *FMTI = "%*s x0 = %f +/- %f y0 = %f +/- %f R =%f +/- %f gamma = %f +/- %f";
  Int_t NON = 1;
  Float_t x, dx, y, dy, r, dr, g, dg;
  Int_t i = 0;
  const Char_t *FMT = "<x0> =%8.4f +/- %7.4f; <y0> =%8.4f +/- %7.4f; N/A               ; <gamma> = %8.2f +/- %5.2f";
  for (Int_t on = 0; on < NON; on++) {// old new
      Int_t NTpc = 0;
      Double_t xTpcW = 0, yTpcW = 0, gTpcW = 0;
      Double_t xTpcWW = 0, yTpcWW = 0, gTpcWW = 0;
      for (Int_t s = 0; s < 2; s++) {// West East
	Int_t N = 0;
	Double_t xW = 0, yW = 0, gW = 0;
	Double_t xWW = 0, yWW = 0, gWW = 0;
	for (Int_t j = 0; j < 4; j++, i++) {
	  cout << Lines[i] << endl;
	  Int_t n = 	  sscanf(Lines[i],FMTI,&x,&dx,&y,&dy,&r,&dr,&g,&dg);
	  //	  cout << n << "\t" << Form("x0 = %f+/-%f; y0 = %f+/-%f; R = %f+/-%f; gamma = %f+/-%f\n",x,dx,y,dy,r,dr,g,dg);
#if 1
	  xW  +=  x/(dx*dx);
	  xWW += 1./(dx*dx);
	  yW  +=  y/(dy*dy);
	  yWW += 1./(dy*dy);
	  gW  +=  g/(dg*dg);
	  gWW += 1./(dg*dg);
#else
          N++; NTpc++;
	  xW += x;
	  yW += y;
	  gW += g;
	  xTpcW += x;
	  yTpcW += y;
	  gTpcW += g;
#endif
	}
#if 1
	xW = xW/xWW; xWW = 1./TMath::Sqrt(xWW);
	yW = yW/yWW; yWW = 1./TMath::Sqrt(yWW);
	gW = gW/gWW; gWW = 1./TMath::Sqrt(gWW);
#else
	xW /= N;
	yW /= N;
	gW /= N;
#endif
#if 0
	if (! on) cout << "Old\t";
	else      cout << "New\t";
#endif
	cout << "Av;";
	if (! s) cout << "West;";
	else     cout << "East;";
	cout << Form(FMT,xW,xWW,yW,yWW,gW,gWW) << endl;
#if 1
	xTpcW += xW/(xWW*xWW); xTpcWW += 1./(xWW*xWW);
	yTpcW += yW/(yWW*yWW); yTpcWW += 1./(yWW*yWW);
	gTpcW += gW/(gWW*gWW); gTpcWW += 1./(gWW*gWW);
#endif
      }
#if 0
      if (! on) cout << "Old\t";
      else      cout << "New\t";
#endif
      cout << "Av;Tpc ;";
#if 1
      xTpcW = xTpcW/xTpcWW; xTpcWW = 1./TMath::Sqrt(xTpcWW);
      yTpcW = yTpcW/yTpcWW; yTpcWW = 1./TMath::Sqrt(yTpcWW);
      gTpcW = gTpcW/gTpcWW; gTpcWW = 1./TMath::Sqrt(gTpcWW);
#else
      xTpcW /= NTpc;
      yTpcW /= NTpc;
      gTpcW /= NTpc;
#endif
      cout << Form(FMT,xTpcW,xTpcWW,yTpcW,yTpcWW,gTpcW,gTpcWW) << endl;
    }
}
