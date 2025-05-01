#include "TWbox.h"
#include "TCanvas.h"
#include "TString.h"
#include "TH1.h"
#include "TROOT.h"
TWbox *stub[2] = {0};
void boxes(TString opt = "xy") {
#ifndef __CINT__
  struct box_t {
    const Char_t *head;
    Double_t xyz[3];
    const Char_t *tail;
  };
  box_t d[2] = {
    // = Overlap ov00014: CAVE/WALL_16 overlapping CAVE/WALL_18 ovlp=25.0175
    {"TGeoVolume *WAL8 = gGeoManager->MakeBox(\"WALL\",GetMed(\"CAVE_CONCRETE\")",{25.15001,213.36,606.14}, "); WAL8->SetTitle(\"WAL8\");"},
    {"TGeoVolume *WAL0 = gGeoManager->MakeBox(\"WALL\",GetMed(\"CAVE_CONCRETE\")",{69.215,140.97,60.96}, "); WAL0->SetTitle(\"WAL0\");"}
  };
  box_t p[2] = {
    {"CAVE->AddNode(WAL8,16,new TGeoTranslation(",{-304.8,86.36002,-1413.86},"));"},
    {"CAVE->AddNode(WAL0,18,new TGeoTranslation(",{-260.735,13.97,-1427.48},"));"}
  };
  TCanvas *c1 = (TCanvas *) gROOT->GetListOfCanvases()->FindObject("c1");
  if (c1) c1->Clear();
  else    c1 = new TCanvas("c1","Overlaping boxes",20,10,750,930);
  //  c1->SetBorderSize(0);
  Int_t ix = 0, iy = 1; // "xy"
  if (opt.BeginsWith("x",TString::kIgnoreCase)) ix = 0;
  if (opt.BeginsWith("y",TString::kIgnoreCase)) ix = 1;
  if (opt.BeginsWith("z",TString::kIgnoreCase)) ix = 2;
  
  if (opt.EndsWith("x",TString::kIgnoreCase)) iy = 0;
  if (opt.EndsWith("y",TString::kIgnoreCase)) iy = 1;
  if (opt.EndsWith("z",TString::kIgnoreCase)) iy = 2;
  
  Double_t x1 = TMath::Min(TMath::Min(p[0].xyz[ix]-d[0].xyz[ix], p[1].xyz[ix]-d[1].xyz[ix]), TMath::Min(p[0].xyz[ix]-d[0].xyz[ix], p[1].xyz[ix]-d[1].xyz[ix]));
  Double_t x2 = TMath::Max(TMath::Max(p[0].xyz[ix]+d[0].xyz[ix], p[1].xyz[ix]+d[1].xyz[ix]), TMath::Max(p[0].xyz[ix]+d[0].xyz[ix], p[1].xyz[ix]+d[1].xyz[ix]));
  Double_t y1 = TMath::Min(TMath::Min(p[0].xyz[iy]-d[0].xyz[iy], p[1].xyz[iy]-d[1].xyz[iy]), TMath::Min(p[0].xyz[iy]-d[0].xyz[iy], p[1].xyz[iy]-d[1].xyz[iy]));
  Double_t y2 = TMath::Max(TMath::Max(p[0].xyz[iy]+d[0].xyz[iy], p[1].xyz[iy]+d[1].xyz[iy]), TMath::Max(p[0].xyz[iy]+d[0].xyz[iy], p[1].xyz[iy]+d[1].xyz[iy]));

  //  c1->Range(x1-5,y1-5,x2+5,y2+5);
  TH1F *frame = c1->DrawFrame(x1-10, y1-10, x2+10,y2+10);
  if (ix == 0) {frame->GetXaxis()->SetTitle("X [cm]");}
  if (ix == 1) {frame->GetXaxis()->SetTitle("Y [cm]");}
  if (ix == 2) {frame->GetXaxis()->SetTitle("Z [cm]");}
  if (iy == 0) {frame->GetYaxis()->SetTitle("X [cm]");}
  if (iy == 1) {frame->GetYaxis()->SetTitle("Y [cm]");}
  if (iy == 2) {frame->GetYaxis()->SetTitle("Z [cm]");}

  stub[0] = new TWbox(p[0].xyz[ix]-d[0].xyz[ix], p[0].xyz[iy]-d[0].xyz[iy],
		      p[0].xyz[ix]+d[0].xyz[ix], p[0].xyz[iy]+d[0].xyz[iy], 2,1,0);// 12.9,11.5,13.6,15.5,49,3,1);
  stub[1] = new TWbox(p[1].xyz[ix]-d[1].xyz[ix], p[1].xyz[iy]-d[1].xyz[iy],
		      p[1].xyz[ix]+d[1].xyz[ix], p[1].xyz[iy]+d[1].xyz[iy], 3,1,0);// 12.9,11.5,13.6,15.5,49,3,1);
  stub[0]->SetFillStyle(4050);
  stub[1]->SetFillStyle(4050);
  stub[0]->Draw();
  stub[1]->Draw();
#endif
}
