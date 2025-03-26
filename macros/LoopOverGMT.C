/* 
   root.exe 'LoadGeometry.C("y2019")'  LoopOverGMT.C
*/
static Int_t k = 0;
static const TString separator("/_"); 
// HALL[1]/CAVE[1]/TpcRefSys[1]/BTOF[1]/BTOH[2]/BSEC[48]/BTRA[1]/BXTR[1]/BRTC[1]/BGMT[1]/GMTS[2]/GSBE[1]/GEMG[1]
void LoopOverGMT(TGeoNode *nodeT = 0, TString pathT = "HALL_1/CAVE_1/TpcRefSys_1/BTOF_1", TString NameV = "GEMG") {
  if (! nodeT) {
    TObjectSet *set = 0;
    if (! gGeoManager) (TObjectSet *) gDirectory->Get("Geometry");
    if (! gGeoManager) return;
    gGeoManager->RestoreMasterVolume();
    if (pathT != "")     gGeoManager->cd(pathT);
    nodeT = gGeoManager->GetCurrentNode();
    if (! nodeT) return;
    TString path = nodeT->GetName();
    //    cout << "top " << nodeT->GetName() << "\t" << nodeT->GetVolume()->GetName() << "\t" << path << endl;
    LoopOverGMT(nodeT,path,NameV);
  } else {
    const TGeoVolume *vol = nodeT->GetVolume();
    TObjArray *nodes = vol->GetNodes();
    Int_t nd = nodeT->GetNdaughters();
    TString name(vol->GetName(),4);
    //      if (name == "SVTD" || 
    //
    if (name == NameV) {
      //      vol->Print(); vol->InspectShape();
      const TGeoHMatrix *matrix = gGeoManager->GetCurrentMatrix(); 
      matrix->Print();
      Double_t *xyz = matrix->GetTranslation();
      Double_t R = TMath::Sqrt(xyz[0]*xyz[0] + xyz[1]*xyz[1]);
      Double_t phi = TMath::RadToDeg()*TMath::ATan2(xyz[1],xyz[0]);
      cout << k << "\tR = " << R << "\tphi = " << phi << "\tZ = " << xyz[2] << endl;
      k++;
      return;
    }
    //    if (nd > 5) nd = 5;
    for (Int_t id = 0; id < nd; id++) {
      TGeoNode *node = (TGeoNode*)nodes->UncheckedAt(id);
      if (! node) continue;
      vol = node->GetVolume();
      if (! vol) continue; 
      TString path = pathT;
      if (path != "") path += "/";
      path += node->GetName();
      //      gGeoManager->cdDown(node->GetIndex());
      Int_t nodeid = gGeoManager->GetCurrentNode()->GetVolume()->GetIndex(node);
      gGeoManager->CdDown(nodeid);
      //      gGeoManager->cd(node->GetName());
      //      gGeoManager->cdNode(node->GetIndex());
      LoopOverGMT(node,path,NameV);
      gGeoManager->CdUp();
    }
  }
}
