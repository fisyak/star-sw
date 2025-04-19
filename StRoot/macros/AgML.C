void AgML(const Char_t *tag="y2025", const Char_t *geom="") {
  TString Tag(tag);
  TString Geom(geom);
  if (Tag == "") {
    cout << "Tag has not defined" << endl;
    exit(1);
  }
  if (Geom == "") Geom = Tag;
  
  gSystem->Load("libSt_base");                                        //  StMemStat::PrintMem("load St_base");
  if (gSystem->Load("liblog4cxx") >=  0) {             //  StMemStat::PrintMem("load log4cxx");
    cout << " + liblog4cxx";
    if(gSystem->Load("libStStarLogger") >= 0) {              //  StMemStat::PrintMem("load log4cxx");
      cout << " + libStStarLogger";
      //      gROOT->ProcessLine("StLoggerManager::StarLoggerInit();"); 
      StLoggerManager::StarLoggerInit();
      if (gROOT->IsBatch())  StLoggerManager::setColorEnabled(kFALSE);
    }
    cout << endl;
  }
  gSystem->Load("libStChain");                                        //  StMemStat::PrintMem("load StChain");
  gSystem->Load("libStUtilities");                                    //  StMemStat::PrintMem("load StUtilities");
  gSystem->Load("StarAgmlUtil");
  gSystem->Load("StarAgmlLib");
  gSystem->Load("Geometry");
  gSystem->AddIncludePath(" -IStRoot -Igeom -IStarVMC -IStarVMC/Geometry/macros -I$STAR/StRoot -Igeom -I$STAR/StarVMC -I$STAR/StarVMC/Geometry/macros ");
  gErrorIgnoreLevel=9999;                        // Silence ROOT warnings for now
  gGeoManager = new TGeoManager(Geom.Data(),Form("%s/AgML",Geom.Data()));
  AgBlock::SetStacker( new StarTGeoStacker() );  // Creates TGeo geometry
  Geometry *build = new Geometry();                        // Instantiate the geometry
  build -> ConstructGeometry ( Geom.Data() );            

  gGeoManager->CloseGeometry();
  //  gGeoManager->Export(Form("%s.root",Geom.Data()));
  TObjectSet *geomOS = new TObjectSet("Geometry",gGeoManager,kFALSE);
  TFile *fOut = new TFile(Form("Geometry.%s.root",Tag.Data()),"recreate");
  geomOS->Write();
  fOut->Close();
  TCollection::StartGarbageCollection();
  delete fOut;
  delete gGeoManager;
#if 0
  St_geant_Maker *geant = (St_geant_Maker *) chain->Maker("geant");
  if (! geant) return;
  TString hfile(tag);
  hfile += ".h";
  geant->g2Root(hfile);
  ofstream out;
  TString fOut("Geometry.");
  fOut += tag;
  fOut += ".C";
  out.open(fOut.Data());
  out << "#include \"CreateGeometry.h\"" << endl;
  out << "TDataSet *CreateTable() {" << endl;
  geant->Version(out);
  out << "  return CreateGeometry(\"" << tag << "\",configGeom);" << endl;
  out << "}" << endl;
  out.close(); 
#endif
}
