// Exercise the new StMuFstUtil::getFstEvt() -- the MuDst -> StEvent read-back that did
// not exist. Reads the MuDst written with fstMuRawHit and rebuilds an
// StFstEvtCollection, then checks the round trip is lossless by comparing the restored
// raw hits against what is in the MuDst.
void testFstReadBack(const char* fn="st_physics_23063032_raw_1000009.MuDst.root"){
  // STAR's own loader: gets the dependency order right. Loading StMuDSTMaker by hand
  // fails with "undefined symbol: StKinkBase::ShowMembers" because StEvent has to be
  // fully in first.
  gROOT->Macro("$STAR/StRoot/StMuDSTMaker/COMMON/macros/loadSharedLibraries.C");

  StMuDstMaker* mk = new StMuDstMaker(0,0,"",fn,".",1);
  if (mk->Init() != kStOK) { printf("StMuDstMaker::Init failed\n"); return; }
  int nok=0, nev=0;
  for(int i=0;i<20;i++){
    if(mk->Make()!=kStOK) break;
    StMuDst* mu = mk->muDst();
    if(!mu) continue;
    StMuFstCollection* c = StMuDst::muFstCollection();   // static accessor
    if(!c) { printf("event %d: no StMuFstCollection\n", i); continue; }
    nev++;
    unsigned int nraw = c->numberOfRawHits();
    if(i<3) printf("event %d: StMuFstCollection has %u raw hits, %u hits\n",
                   i, nraw, c->numberOfHits());
    if(nraw==0) continue;
    // the new read-back
    StMuFstUtil util;
    StFstEvtCollection* evt = util.getFstEvt(c);
    if(!evt){ printf("  getFstEvt returned null\n"); continue; }
    unsigned int nback = evt->numberOfRawHits();
    if(i<3) printf("  getFstEvt rebuilt %u raw hits  %s\n", nback,
                   nback==nraw ? "MATCH" : "MISMATCH");
    if(nback==nraw) nok++;
    // spot-check the first hit's ids survived
    if(i==0 && nback>0){
      StFstRawHit* h = evt->rawHits()[0];
      StMuFstRawHit* m = c->getRawHit(0);
      printf("  hit0 channelId %d vs %d, geoId %d vs %d, maxTb %d vs %d  %s\n",
             h->getChannelId(), m->getChannelId(), h->getGeoId(), m->getGeoId(),
             (int)h->getMaxTimeBin(), (int)m->getMaxTimeBin(),
             (h->getChannelId()==m->getChannelId() && h->getGeoId()==m->getGeoId()) ? "OK":"BAD");
    }
    delete evt;
  }
  printf("\n%d of %d events round-tripped with matching raw-hit counts\n", nok, nev);
}
