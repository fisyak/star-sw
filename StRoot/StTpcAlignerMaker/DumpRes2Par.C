// Dump Resuls.root histogram to SurveyPass_t
/* 
   root.exe Results.root DumpRes2Par.C
*/
void DumpRes2Par() {
  TH1D *hist[2][6] = {0};
  const Char_t *RF[2] = {"FF","RF"};
  const Char_t *nameK[6] = {"Dx","Dy","Dz","Da",     "Db",    "Dg"};
  for (Int_t f = 0; f < 2; f++) 
    for (Int_t k = 0; k < 6; k++) {
      TString Name(Form("%s%s",nameK[k],RF[f]));
      hist[f][k] = (TH1D *) gDirectory->Get(Name);
      if (! hist[f][k]) {
	cout << "Hisogram " << Name.Data() << " is missing" << endl;
      } else {
	cout << "Hisogram " << Name.Data() << " is loaded" << endl;
      }
    }
  ofstream outC;
  outC.open("Results.h", ios::out);
  for (Int_t f = 0; f < 2; f++) {
    outC << "  {20190101,    1, \"" << gSystem->BaseName(gSystem->WorkingDirectory()) << "/" << RF[f] <<  "\", //" << endl;
    outC << "{" << endl;
    for (Int_t sector = 1; sector <= 24; sector++) {
      TString lineC("");
      lineC = Form("\t{%2i",sector);
      for (Int_t k = 0; k < 6; k++) {
	TH1D *fit = hist[f][k];
	Double_t val      = fit->GetBinContent(sector);
	Double_t valError = fit->GetBinError(sector);
	lineC += Form(",%8.2f,%5.2f", val,TMath::Min(99.99,valError)); 
      }
      lineC += ",\""; lineC += RF[f]; lineC += "\"},";
      outC << lineC << endl;
    }
    outC << "    }" << endl;
    outC << "  }," << endl;
  }
  outC.close();
}
