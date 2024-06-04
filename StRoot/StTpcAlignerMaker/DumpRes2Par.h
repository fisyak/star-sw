#ifndef __DumpRes2Par__
#define __DumpRes2Par__
#include "TF1.h"
TString OutputName;
//________________________________________________________________________________
void DumpRes2Par(TString Out = "IOSectorPar",
		 TString optFF = "2019_FF+2021_FF+2022_FF+2023_FF+2024_FF",
		 TString optRF = "2019_RF+2020_RF+2021_RF+2022_RF+2023_RF+2024_RF") {
		 
  TH1D *hist[2][6] = {0};
  TString RF[2] = {optFF, optRF};
  RF[0].ReplaceAll("/","_");
  RF[1].ReplaceAll("/","_");
  RF[0].ReplaceAll("+","_");
  RF[1].ReplaceAll("+","_");
  const Char_t *nameK[6] = {"Dx","Dy","Dz","Da",     "Db",    "Dg"};
  for (Int_t f = 0; f < 2; f++) {
    if (! RF[f].BeginsWith("20")) continue;
    for (Int_t k = 0; k < 6; k++) {
      TString Name(Form("%s%s",nameK[k],RF[f].Data()));
      hist[f][k] = (TH1D *) gDirectory->Get(Name);
      if (! hist[f][k]) {
	cout << "Hisogram " << Name.Data() << " is missing" << endl;
	return;
      } else {
	cout << "Hisogram " << Name.Data() << " is loaded" << endl;
      }
    }
  }
  Out += OutputName;
  Out += gSystem->BaseName(gSystem->WorkingDirectory());
  Out += "_Avg.h";
  ofstream outC;
  outC.open(Out.Data(), ios::out);
  Int_t d = -1;
  Int_t t = -1;
  if        (RF[0].BeginsWith("2019") || RF[1].BeginsWith("2019")) {d = 20190101; t =      1;
  } else if (RF[0].BeginsWith("2020") || RF[1].BeginsWith("2020")) {d = 20191125; t = 202022;
  } else if (RF[0].BeginsWith("2021") || RF[1].BeginsWith("2021")) {d = 20210129; t =  41915;
  } else if (RF[0].BeginsWith("2022") || RF[1].BeginsWith("2022")) {d = 20211110; t = 215909;
  } else if (RF[0].BeginsWith("2023") || RF[1].BeginsWith("2023")) {d = 20230507; t =  55732;
  } else if (RF[0].BeginsWith("2024") || RF[1].BeginsWith("2024")) {d = 20240403; t =  20814;
  }
  for (Int_t f = 0; f < 2; f++) {
    if (! RF[f].BeginsWith("20")) continue;
    outC << Form("  {%8i,%6i",d,t) << ", \"" << gSystem->BaseName(gSystem->WorkingDirectory()) << "/" << RF[f].Data() <<  "\", //" << endl;
    outC << "{" << endl;
    for (Int_t sector = 1; sector <= 24; sector++) {
      TString lineC("");
      lineC = Form("\t{%2i",sector);
      TString Fit;
      for (Int_t k = 0; k < 6; k++) {
	TH1D *h = hist[f][k];
#ifndef __DONTSMOOTH__
	TF1 *secW = (TF1 *) h->GetListOfFunctions()->FindObject("secW");
	TF1 *secE = (TF1 *) h->GetListOfFunctions()->FindObject("secE");
	Double_t val = 0;
	if (secW && secE) {
	  if (sector <= 12) val = secW->Eval(sector);
	  else              val = secE->Eval(sector);
	  Fit = " Fit";
	} else {
	  val      = h->GetBinContent(sector);
	  Fit = "";
	}
#else 
	  Double_t val      = h->GetBinContent(sector);
	  Fit = "";
#endif
	Double_t valError = h->GetBinError(sector);
	lineC += Form(",%8.2f,%5.2f", val,TMath::Min(99.99,valError)); 
      }
      lineC += ",\""; lineC += RF[f]; lineC += Fit; lineC += "\"},";
      outC << lineC << endl;
    }
    outC << "    }" << endl;
    outC << "  }," << endl;
  }
  outC.close();
}
#endif
