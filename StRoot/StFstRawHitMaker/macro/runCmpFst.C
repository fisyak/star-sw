// Loads the libraries, compiles cmpFstClusters.C with ACLiC, and runs it.
//   fn   MuDst written with the fstMuRawHit chain option
//   nev  events to compare
void runCmpFst(const char* fn="st_physics_23063032_raw_1000009.MuDst.root", int nev=20){
  gROOT->Macro("$STAR/StRoot/StMuDSTMaker/COMMON/macros/loadSharedLibraries.C");
  gSystem->Load("libStFstUtil");        // StFstCollection / StFstCluster live here
  gSystem->Load("libStFstRawHitMaker");
  gSystem->Load("libStFstClusterMaker");
  // ACLiC links against what is already loaded, so compile only after the loads
  gROOT->LoadMacro("cmpFstClusters.C+");
  cmpFstClusters(fn, nev);
}
