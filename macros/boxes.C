TWbox *stub[2] = {0};
void boxes(TString opt = "xy") {
  Double_t dXYZ[2][3] = { //  = Overlap ov00014: CAVE/WALL_16 overlapping CAVE/WALL_18 ovlp=25.0175 
    {/*TGeoVolume *WAL0 = gGeoManager->MakeBox("WALL",GetMed("CAVE_CONCRETE"),*/  69.215,  140.97,      60.96}, //*); WAL0->SetTitle("WAL0"); *
    {/*TGeoVolume *WAL8 = gGeoManager->MakeBox("WALL",GetMed("CAVE_CONCRETE"),*/  25.15001,213.36,     606.14}//); WAL8->SetTitle("WAL8");
    };
  Double_t XYZ[2][3] = { 
    {/* CAVE->AddNode(WAL8,16,new TGeoTranslation(*/ -304.8,     86.36002,-1413.86}, //)); 
    {/* CAVE->AddNode(WAL0,18,new TGeoTranslation(*/ -260.735,   13.97,   -1427.48}  //));
  };
  //  = Overlap ov00015: CAVE/WALL_15 overlapping CAVE/WALL_20 ovlp=24.843
  // TGeoVolume *WAL8 = gGeoManager->MakeBox("WALL",GetMed("CAVE_CONCRETE"),  25.15001,213.36,    606.14); WAL8->SetTitle("WAL8");
  // TGeoVolume *WALb = gGeoManager->MakeBox("WALL",GetMed("CAVE_CONCRETE"),  57.277,  137.16,     60.96); WALb->SetTitle("WALb");
  //                              CAVE->AddNode(WAL8,15,new TGeoTranslation(-304.8,     86.36002,1413.86));
  //                              CAVE->AddNode(WALb,20,new TGeoTranslation(-272.673,   10.16,   1129.157));
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
  
  Double_t x1 = TMath::Min(TMath::Min(XYZ[0][ix]-dXYZ[0][ix], XYZ[1][ix]-dXYZ[1][ix]), TMath::Min(XYZ[0][ix]-dXYZ[0][ix], XYZ[1][ix]-dXYZ[1][ix]));
  Double_t x2 = TMath::Max(TMath::Max(XYZ[0][ix]+dXYZ[0][ix], XYZ[1][ix]+dXYZ[1][ix]), TMath::Max(XYZ[0][ix]+dXYZ[0][ix], XYZ[1][ix]+dXYZ[1][ix]));
  Double_t y1 = TMath::Min(TMath::Min(XYZ[0][iy]-dXYZ[0][iy], XYZ[1][iy]-dXYZ[1][iy]), TMath::Min(XYZ[0][iy]-dXYZ[0][iy], XYZ[1][iy]-dXYZ[1][iy]));
  Double_t y2 = TMath::Max(TMath::Max(XYZ[0][iy]+dXYZ[0][iy], XYZ[1][iy]+dXYZ[1][iy]), TMath::Max(XYZ[0][iy]+dXYZ[0][iy], XYZ[1][iy]+dXYZ[1][iy]));

  //  c1->Range(x1-5,y1-5,x2+5,y2+5);
  TH1F *frame = c1->DrawFrame(x1-10, y1-10, x2+10,y2+10);
  if (ix == 0) {frame->GetXaxis()->SetTitle("X [cm]");}
  if (ix == 1) {frame->GetXaxis()->SetTitle("Y [cm]");}
  if (ix == 2) {frame->GetXaxis()->SetTitle("Z [cm]");}
  if (iy == 0) {frame->GetYaxis()->SetTitle("X [cm]");}
  if (iy == 1) {frame->GetYaxis()->SetTitle("Y [cm]");}
  if (iy == 2) {frame->GetYaxis()->SetTitle("Z [cm]");}

  stub[0] = new TWbox(XYZ[0][ix]-dXYZ[0][ix], XYZ[0][iy]-dXYZ[0][iy],
		      XYZ[0][ix]+dXYZ[0][ix], XYZ[0][iy]+dXYZ[0][iy], 2,1,0);// 12.9,11.5,13.6,15.5,49,3,1);
  stub[1] = new TWbox(XYZ[1][ix]-dXYZ[1][ix], XYZ[1][iy]-dXYZ[1][iy],
		      XYZ[1][ix]+dXYZ[1][ix], XYZ[1][iy]+dXYZ[1][iy], 3,1,0);// 12.9,11.5,13.6,15.5,49,3,1);
  stub[0]->SetFillStyle(4050);
  stub[1]->SetFillStyle(4050);
  stub[0]->Draw();
  stub[1]->Draw();
}
