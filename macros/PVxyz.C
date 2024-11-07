/*
  root.exe 11p5GeV.A+C.root PVxyz,C
*/
#include "Riostream.h"
#include "TSystem.h"
#include "TROOT.h"
#include "TH1.h"
#include "TH2.h"
#include "TF1.h"
#include "TFile.h"
#include "Ask.h"
#include "TCanvas.h"
TCanvas *c1 = 0;
ofstream out;
//________________________________________________________________________________
TF1 *FitGaus(TH1 *hist) {
  TF1 *gaus = 0;
  if (! hist) return gaus;
  Int_t iok = hist->Fit("gaus","i");
  if (iok) return gaus;
  if (c1) c1->Update();
  if (Ask()) return gaus;
  gaus = (TF1 *) hist->GetListOfFunctions()->FindObject("gaus");
  if (! gaus) return gaus;
  iok = hist->Fit(gaus,"ir","",
	    gaus->GetParameter(1)-2*gaus->GetParameter(2),
	    gaus->GetParameter(1)+2*gaus->GetParameter(2));
  if (iok) return 0;
  if (c1) c1->Update();
  if (Ask()) return gaus;
  return gaus;
}
//________________________________________________________________________________
void PVxyz() {
  c1 = (TCanvas *) gROOT->GetListOfCanvases()->FindObject("c1");
  if (! c1) c1 = new TCanvas("c1","c1");
  TString fName("PVxyz");
  TDirectory *dir = gDirectory;
  TString tag(gSystem->BaseName(dir->GetName()));
  fName += tag;
  tag.ReplaceAll(".root",".txt");
  TString cOut("beamSpot.");
  cOut += tag;
  TFile *fOut = new TFile(fName,"recreate");
  TH1 *x = (TH1 *) dir->Get("/Particles/KFParticlesFinder/PrimaryVertexQA/x");
  if (x) x->Write();
  TF1 *gaus = FitGaus(x);
  if (! gaus) return;
  Double_t X = gaus->GetParameter(1);
  Double_t sigma_X = gaus->GetParameter(2);
  TH1 *y = (TH1 *) dir->Get("/Particles/KFParticlesFinder/PrimaryVertexQA/y");
  if (y) y->Write();
  gaus = FitGaus(y);
  if (! gaus) return;
  Double_t Y = gaus->GetParameter(1);
  Double_t sigma_Y = gaus->GetParameter(2);
  TH1 *z = (TH1 *) dir->Get("/Particles/KFParticlesFinder/PrimaryVertexQA/z");
  if (z) z->Write();
  gaus = FitGaus(z);
  if (! gaus) return;
  Double_t Z = gaus->GetParameter(1);
  Double_t sigma_Z = gaus->GetParameter(2);
  TH1 *e = (TH1 *) dir->Get("/Tracks/hPVError");
  if (e) e->Write();
  TH2 *xy = (TH2 *) dir->Get("/Particles/KFParticlesFinder/PrimaryVertexQA/xy");
  if (xy) xy->Write();
  cout << "Create " << cOut << endl;
  out.open(cOut.Data());
  out << "#ifndef __CINT__" << endl;
  out << "#include \"tables/St_beamSpot_Table.h\"" << endl;
  out << "#endif" << endl;
  out << "TDataSet *CreateTable() {" << endl;
  out << "  if (!gROOT->GetClass(\"St_beamSpot\")) return 0;" << endl;
  out << "  beamSpot_st row;" << endl;
  out << "  St_beamSpot *tableSet = new St_beamSpot(\"beamSpot\",1);" << endl;
  out << "  memset(&row,0,tableSet->GetRowSize());" << endl;
  out << Form("  row.X = %10.3f; row.sigma_X = %10.3f;", X, sigma_X) << endl;
  out << Form("  row.Y = %10.3f; row.sigma_Y = %10.3f;", Y, sigma_Y) << endl;
  out << Form("  row.Z = %10.3f; row.sigma_Z = %10.3f;", Z, sigma_Z) << endl;
  out << "  tableSet->AddAt(&row);" << "// " << gDirectory->GetName() << endl;
  out << "  return (TDataSet *)tableSet;" << endl;
  out << "}" << endl;
  out.close();
}

