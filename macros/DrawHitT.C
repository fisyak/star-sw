#include "Riostream.h"
#include "TFile.h"
#include "TCanvas.h"
#include "TH2.h"
#include "TString.h"
#include "TROOT.h"
#include "TSystem.h"
#include "TLegend.h"
#include "TPaveStats.h"
TFile *files[4] = {
  TFile::Open("Hijing.AuAu200.E/Inner/TMVACHitTCI.root"),
  TFile::Open("Hijing.AuAu200.E/Outer/TMVACHitTCO.root"),
  TFile::Open("PHQMD.3p85GeV_fixedTarget.E/Inner/TMVACHitTCI.root"),
  TFile::Open("PHQMD.3p85GeV_fixedTarget.E/Outer/TMVACHitTCO.root")
};
void DrawHitT(TString opt = "Ov", TString Proj = "") {
  auto c1 = (TCanvas *) gROOT->GetListOfCanvases()->FindObject("c1");
  if (! c1) c1 = new TCanvas("c1","c1");
  c1->Clear();
  c1->Divide(4,2);
  for (Int_t f = 0; f < 4; f++) {
    Double_t S = 0; 
    Double_t B = 0;
    for (Int_t s = 0; s < 2; s++) {
      TPad *pad = (TPad *) c1->cd(4*s + f + 1);
      pad->SetLogz(1);
      TString name("QA/");
      name += opt;
      if (s == 0) name += "S"; 
      else        name += "B";
      TH2 *h2 = (TH2 *) files[f]->Get(name);
      if (! h2)  continue;
      h2->SetMinimum(1e-2*h2->GetMaximum());
      TAxis *x = h2->GetXaxis(); Int_t nx = x->GetNbins(); x->SetRange(nx-15,nx);
      TAxis *y = h2->GetYaxis(); Int_t ny = y->GetNbins(); y->SetRange(ny-15,ny);
      h2->Draw("colz");
      pad->Update();
      TPaveStats *ps2 = (TPaveStats*)h2->GetListOfFunctions()->FindObject("stats");
      if (ps2) {
	ps2->SetY1NDC(0.15); ps2->SetY2NDC(0.35);
	ps2->SetX1NDC(0.15); ps2->SetX2NDC(0.35);
      }
      if (Proj == "X") h2->ProjectionX()->Draw();
      else if (Proj == "Y") h2->ProjectionY()->Draw();
      else h2->Draw("colz");
      pad->Update();
      if (s == 0) {
	TLegend *l = new TLegend(0.3,0.9,0.9,0.95);
	l->AddEntry(h2,gSystem->DirName(files[f]->GetName()));
	l->Draw();
	S =  h2->GetEntries();
      } else {
	B =  h2->GetEntries();
      }
      cout << gSystem->DirName(files[f]->GetName()) << "\t" << h2->GetName() << "\t" << h2->GetEntries() << endl;
    }
    cout << "R = S/(S+B) = " << S/(S+B) << endl;
  }
}
