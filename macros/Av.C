#include "TString.h"
#include "Riostream.h"
#include "TMath.h"
using namespace std;
//________________________________________________________________________________
void Av() {
  const Char_t *Lines[8] = {
#if 0
    "MakeRGraph(2024,WA,0)                x0 = -0.1622 +/-  0.0041 y0 = -0.4324 +/-  0.0045 R = 54.4995 +/-  0.0030 gamma =  0.16 +/-  0.243",
    "MakeRGraph(2024,WB,0)                x0 = -0.1487 +/-  0.0043 y0 = -0.3281 +/-  0.0069 R =118.8423 +/-  0.0038 gamma =  0.04 +/-  0.162",
    "MakeRGraph(2024,WC,0)                x0 = -0.1972 +/-  0.0044 y0 = -0.3281 +/-  0.0065 R =124.3910 +/-  0.0035 gamma =  0.07 +/-  0.303",
    "MakeRGraph(2024,WD,0)                x0 = -0.2098 +/-  0.0050 y0 = -0.2876 +/-  0.0045 R =190.5176 +/-  0.0034 gamma = -0.18 +/-  0.233",

    "MakeRGraph(2024,EA,0)                x0 = -0.1219 +/-  0.0041 y0 = -0.3114 +/-  0.0041 R = 54.5000 +/-  0.0029 gamma =  0.72 +/-  0.233",
    "MakeRGraph(2024,EB,0)                x0 = -0.0607 +/-  0.0043 y0 = -0.2785 +/-  0.0069 R =118.8212 +/-  0.0038 gamma =  0.22 +/-  0.172",
    "MakeRGraph(2024,EC,0)                x0 = -0.1193 +/-  0.0043 y0 = -0.3284 +/-  0.0069 R =124.3101 +/-  0.0038 gamma =  0.56 +/-  0.153",
    "MakeRGraph(2024,ED,0)                x0 = -0.1465 +/-  0.0050 y0 = -0.2539 +/-  0.0041 R =190.5970 +/-  0.0032 gamma =  0.19 +/-  0.133"};
#else
#if 0
    "MakeRGraph(2024,WA)                x0 =  0.0145 +/-  0.0041 y0 = -0.0823 +/-  0.0045 R = 54.4995 +/-  0.0030 gamma =  0.16 +/-  0.24",
    "MakeRGraph(2024,WB)                x0 =  0.0280 +/-  0.0042 y0 =  0.0220 +/-  0.0066 R =118.8423 +/-  0.0038 gamma =  0.04 +/-  0.16",
    "MakeRGraph(2024,WC)                x0 = -0.0205 +/-  0.0044 y0 =  0.0220 +/-  0.0065 R =124.3910 +/-  0.0035 gamma =  0.07 +/-  0.30",
    "MakeRGraph(2024,WD)                x0 = -0.0331 +/-  0.0050 y0 =  0.0625 +/-  0.0045 R =190.5176 +/-  0.0034 gamma = -0.18 +/-  0.23",
     		            												  
    "MakeRGraph(2024,EA)                x0 = -0.0119 +/-  0.0041 y0 = -0.0233 +/-  0.0041 R = 54.5000 +/-  0.0029 gamma =  0.38 +/-  0.22",
    "MakeRGraph(2024,EB)                x0 =  0.0493 +/-  0.0043 y0 =  0.0096 +/-  0.0069 R =118.8212 +/-  0.0038 gamma = -0.11 +/-  0.17",
    "MakeRGraph(2024,EC)                x0 = -0.0093 +/-  0.0042 y0 = -0.0403 +/-  0.0066 R =124.3101 +/-  0.0038 gamma =  0.23 +/-  0.14",
    "MakeRGraph(2024,ED)                x0 = -0.0365 +/-  0.0050 y0 =  0.0342 +/-  0.0041 R =190.5970 +/-  0.0032 gamma = -0.15 +/-  0.13"};
#else
#if 0
    "MakeRGraph(2024,WA)                 x0 = -0.0522 +/-  0.0041 y0 = -0.1802 +/-  0.0045 R = 54.4995 +/-  0.0030 gamma = -0.18 +/-  0.24",
    "MakeRGraph(2024,WB)                 x0 = -0.0387 +/-  0.0036 y0 = -0.0759 +/-  0.0068 R =118.8423 +/-  0.0038 gamma = -0.29 +/-  0.16",
    "MakeRGraph(2024,WC)                 x0 = -0.0872 +/-  0.0044 y0 = -0.0759 +/-  0.0065 R =124.3910 +/-  0.0035 gamma = -0.26 +/-  0.30",
    "MakeRGraph(2024,WD)                 x0 = -0.0998 +/-  0.0050 y0 = -0.0354 +/-  0.0045 R =190.5176 +/-  0.0034 gamma = -0.51 +/-  0.24",
     		            		                                                                                                  
    "MakeRGraph(2024,EA)                 x0 = -0.0119 +/-  0.0041 y0 =  0.0126 +/-  0.0041 R = 54.5000 +/-  0.0029 gamma =  0.38 +/-  0.22",
    "MakeRGraph(2024,EB)                 x0 =  0.0493 +/-  0.0043 y0 =  0.0455 +/-  0.0069 R =118.8212 +/-  0.0038 gamma = -0.11 +/-  0.17",
    "MakeRGraph(2024,EC)                 x0 = -0.0093 +/-  0.0043 y0 = -0.0044 +/-  0.0066 R =124.3101 +/-  0.0038 gamma =  0.23 +/-  0.14",
    "MakeRGraph(2024,ED)                 x0 = -0.0365 +/-  0.0050 y0 =  0.0702 +/-  0.0041 R =190.5970 +/-  0.0032 gamma = -0.15 +/-  0.13"};
#else
#if 0
    "MakeRGraph(2024,WA)                x0 =  0.0117 +/-  0.0041 y0 = -0.0824 +/-  0.0045 R = 54.4995 +/-  0.0030 gamma =  0.11 +/-  0.24",
    "MakeRGraph(2024,WB)                x0 =  0.0252 +/-  0.0042 y0 =  0.0219 +/-  0.0066 R =118.8423 +/-  0.0038 gamma = -0.01 +/-  0.16",
    "MakeRGraph(2024,WC)                x0 = -0.0233 +/-  0.0044 y0 =  0.0219 +/-  0.0065 R =124.3910 +/-  0.0035 gamma =  0.02 +/-  0.30",
    "MakeRGraph(2024,WD)                x0 = -0.0359 +/-  0.0050 y0 =  0.0624 +/-  0.0045 R =190.5176 +/-  0.0034 gamma = -0.23 +/-  0.23",
     		            	                                                                                                         
    "MakeRGraph(2024,EA)                x0 = -0.0119 +/-  0.0041 y0 =  0.0126 +/-  0.0041 R = 54.5000 +/-  0.0029 gamma =  0.38 +/-  0.22",
    "MakeRGraph(2024,EB)                x0 =  0.0493 +/-  0.0043 y0 =  0.0455 +/-  0.0069 R =118.8212 +/-  0.0038 gamma = -0.11 +/-  0.17",
    "MakeRGraph(2024,EC)                x0 = -0.0093 +/-  0.0043 y0 = -0.0044 +/-  0.0066 R =124.3101 +/-  0.0038 gamma =  0.23 +/-  0.14",
    "MakeRGraph(2024,ED)                x0 = -0.0365 +/-  0.0050 y0 =  0.0702 +/-  0.0041 R =190.5970 +/-  0.0032 gamma = -0.15 +/-  0.13"};
#else
    "MakeRGraph(2024,WA)                x0 =  0.0117 +/-  0.0041 y0 = -0.0824 +/-  0.0045 R = 54.4995 +/-  0.0030 gamma =  0.11 +/-  0.24",
    "MakeRGraph(2024,WB)                x0 =  0.0252 +/-  0.0042 y0 =  0.0219 +/-  0.0066 R =118.8423 +/-  0.0038 gamma = -0.01 +/-  0.16",
    "MakeRGraph(2024,WC)                x0 = -0.0233 +/-  0.0044 y0 =  0.0219 +/-  0.0065 R =124.3910 +/-  0.0035 gamma =  0.02 +/-  0.30",
    "MakeRGraph(2024,WD)                x0 = -0.0359 +/-  0.0050 y0 =  0.0624 +/-  0.0045 R =190.5176 +/-  0.0034 gamma = -0.23 +/-  0.23",
     		            	                                                                                                         
    "MakeRGraph(2024,EA)                x0 = -0.0119 +/-  0.0041 y0 = -0.0229 +/-  0.0041 R = 54.5000 +/-  0.0029 gamma =  0.38 +/-  0.22",
    "MakeRGraph(2024,EB)                x0 =  0.0493 +/-  0.0043 y0 =  0.0100 +/-  0.0069 R =118.8212 +/-  0.0038 gamma = -0.11 +/-  0.17",
    "MakeRGraph(2024,EC)                x0 = -0.0093 +/-  0.0042 y0 = -0.0399 +/-  0.0066 R =124.3101 +/-  0.0038 gamma =  0.23 +/-  0.14",
    "MakeRGraph(2024,ED)                x0 = -0.0365 +/-  0.0050 y0 =  0.0347 +/-  0.0041 R =190.5970 +/-  0.0032 gamma = -0.15 +/-  0.13"};
#endif
#endif
#endif
#endif
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
