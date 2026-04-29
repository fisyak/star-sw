#include "Riostream.h"
#include "TString.h"
#include "TDirectory.h"
#include "TFile.h"
#include "TH3.h"
void CompressTH3(TString Hname = "VoltageNC") {
  TH3F *h = (TH3F *) gDirectory->Get(Hname);
  if (! h) { cout << Hname.Data() << "has not been found" << endl; return;}
  TString H20name = Hname;
  H20name.ReplaceAll("N","N20");
  TH3F *h20 = (TH3F *) gDirectory->Get(H20name);
  if (! h20) { cout << H20name.Data() << "has not been found" << endl; return;}
  Int_t nx = h->GetXaxis()->GetNbins();
  Int_t ny = h->GetYaxis()->GetNbins();
  Int_t nz = h->GetZaxis()->GetNbins();
  if (nx != h20->GetXaxis()->GetNbins() ||
      ny != h20->GetYaxis()->GetNbins() ||
      nz != h20->GetZaxis()->GetNbins()) {
    cout << "bins in " << h->GetName() << " and " << h20->GetName() << " are not matched" << endl; 
    return;
  }
  TString Out(gDirectory->GetName());
  Out.ReplaceAll(".root","Comp.root");
  TFile *fOut = new TFile(Out,"recreate");
  Int_t nxC = nx/24; 
  Double_t xmin = h->GetXaxis()->GetBinLowEdge(1);
  Double_t xmax = h->GetXaxis()->GetBinUpEdge(nxC);
  TH3F *hcomp = new TH3F(Hname+"Comp",h->GetTitle(),nxC, xmin, xmax,
			 h->GetYaxis()->GetNbins(), h->GetYaxis()->GetXmin(), h->GetYaxis()->GetXmax(), 
			 h->GetZaxis()->GetNbins(), h->GetZaxis()->GetXmin(), h->GetZaxis()->GetXmax()); 
  TH3F *h20comp = new TH3F(H20name+"Comp",h->GetTitle(),nxC, xmin, xmax,
			   h->GetYaxis()->GetNbins(), h->GetYaxis()->GetXmin(), h->GetYaxis()->GetXmax(), 
			   h->GetZaxis()->GetNbins(), h->GetZaxis()->GetXmin(), h->GetZaxis()->GetXmax()); 
  for (Int_t i = 1; i <= nx; i++) {
    Int_t ic = (i - 1)%8 + 1;
    for (Int_t j = 1; j <= ny; j++)
      for (Int_t k = 1; k <= nz; k++) {
	Double_t v = h->GetBinContent(i,j,k);
	Double_t v20 = h20->GetBinContent(i,j,k);
	if (v <= 0 && v20 <= 20) continue;
	hcomp->AddBinContent(hcomp->GetBin(ic,j,k), v);
	h20comp->AddBinContent(h20comp->GetBin(ic,j,k), v20);
      }
  }
  fOut->Write();
}
