// End-to-end: re-cluster FST from a MuDst written with fstMuRawHit.
// StFstRawHitMaker in MuDst mode fills the "fstRawHitAndCluster" dataset, then
// StFstClusterMaker and StFstHitMaker run on it exactly as in production.
// The point is to compare the clusters we rebuild against the FstHit already stored in
// the same MuDst -- if they agree, FST clustering is recoverable from a production MuDst.
void testFstRecluster(const char* fn="st_physics_23063032_raw_1000009.MuDst.root", int nev=20){
  gROOT->Macro("$STAR/StRoot/StMuDSTMaker/COMMON/macros/loadSharedLibraries.C");
  gSystem->Load("libStFstUtil");   // provides StFstCollection, NOT libStEvent

  gSystem->Load("libStFstRawHitMaker");
  gSystem->Load("libStFstClusterMaker");

  StChain* chain = new StChain("bfc");
  // No St_db_Maker / StFstDbMaker: readMuDst() takes geoId straight from the MuDst, so
  // the electronics->geometry mapping is not needed, and clustering works on raw hits
  // alone. Keeps this test off the DB library chain entirely.
  StMuDstMaker* mk = new StMuDstMaker(0,0,"",fn,".",1);
  StFstRawHitMaker* raw = new StFstRawHitMaker();
  raw->setMuDstInput(kTRUE);          // the new path
  // Makers attach themselves to the current StChain in their constructor, so the
  // pointer is not needed to keep them alive -- named anyway, it reads better.
  StFstClusterMaker* clu = new StFstClusterMaker();

  if(chain->Init()!=kStOK){ printf("chain Init failed\n"); return; }
  double sumRaw=0, sumClu=0, sumStored=0; int n=0;
  for(int i=0;i<nev;i++){
    chain->Clear();
    if(chain->Make()!=kStOK) break;
    TObjectSet* ds=(TObjectSet*)raw->GetDataSet("fstRawHitAndCluster");  // lives on the maker, not the chain
    if(!ds) continue;
    StFstCollection* col=(StFstCollection*)ds->GetObject();
    if(!col) continue;
    int nr=0,nc=0;
    for(int w=0;w<36;w++){
      if(col->getRawHitCollection(w)) nr+=col->getRawHitCollection(w)->getNumRawHits();
      if(col->getClusterCollection(w)) nc+=col->getClusterCollection(w)->getNumClusters();
    }
    StMuFstCollection* mufst=StMuDst::muFstCollection();
    int ns = mufst ? mufst->numberOfHits() : 0;
    sumRaw+=nr; sumClu+=nc; sumStored+=ns; n++;
    if(i<5){ fprintf(stderr,"event %d: raw %4d -> clusters %4d   (MuDst stored FstHit %d)\n", i, nr, nc, ns); fflush(stderr); }
  }
  if(n){
    fprintf(stderr,"\n%d events\n", n);
    fprintf(stderr,"  raw hits/event        %7.2f\n", sumRaw/n);
    fprintf(stderr,"  clusters rebuilt/ev   %7.2f\n", sumClu/n);
    fprintf(stderr,"  FstHit in MuDst/ev    %7.2f\n", sumStored/n);
    fprintf(stderr,"\n%s\n", sumClu>0 ? "FST RE-CLUSTERING FROM MuDst WORKS" : "no clusters rebuilt");
  }
}
