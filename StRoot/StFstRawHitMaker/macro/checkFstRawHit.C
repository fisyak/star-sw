// Validate the fstMuRawHit round trip on a MuDst written with the option on.
//
// Leaf-based on purpose: loading StMuFstRawHit into CINT is fragile, and decoding geoId
// here rather than calling the class accessors makes this an INDEPENDENT check of the
// stored ids rather than a test of the same code that wrote them.
//
// geoId layout, confirmed against StFstRawHitMaker.cxx:369 -- r-major, 1024 strips per
// wedge, 8 r-rows of 128 phi:
//     wedge = 1 + geoId/1024        disk = 1 + geoId/12288
//     r     = (geoId%1024)/128      phi  = (geoId%1024)%128
void checkFstRawHit(const char* fn){
  TFile* f=TFile::Open(fn);
  if(!f||f->IsZombie()){ printf("cannot open %s\n",fn); return; }
  TTree* t=(TTree*)f->Get("MuDst");
  if(!t){ printf("no MuDst tree\n"); return; }
  Long64_t n=t->GetEntries();
  printf("\n%s : %lld events\n", fn, n);

  if(!t->GetBranch("FstRawHit")){ printf("NO FstRawHit branch\n"); return; }

  // how many, and are they there at all
  t->Draw("FstRawHit.mGeoId>>hg(40000,-1.5,38498.5)","","goff");
  TH1* hg=(TH1*)gDirectory->Get("hg");
  double nraw=hg?hg->GetEntries():0;
  t->Draw("FstHit.mMeanRStrip>>hh(100,0,10)","","goff");
  TH1* hh=(TH1*)gDirectory->Get("hh");
  double nhit=hh?hh->GetEntries():0;
  printf("  FstRawHit %8.0f total, %6.2f / event\n", nraw, nraw/n);
  printf("  FstHit    %8.0f total, %6.2f / event\n", nhit, nhit/n);
  if(nraw<1){ printf("\n*** EMPTY -- the option did not take effect ***\n"); return; }
  printf("  raw strips per clustered hit : %.2f\n", nhit>0 ? nraw/nhit : 0);

  // decoded index ranges
  t->Draw("1+FstRawHit.mGeoId/12288>>hd(6,-0.5,5.5)","","goff");
  TH1* hd=(TH1*)gDirectory->Get("hd");
  t->Draw("1+FstRawHit.mGeoId/1024>>hw(40,0.5,40.5)","","goff");
  TH1* hw=(TH1*)gDirectory->Get("hw");
  t->Draw("(FstRawHit.mGeoId%1024)/128>>hr(10,-0.5,9.5)","","goff");
  TH1* hr=(TH1*)gDirectory->Get("hr");
  t->Draw("(FstRawHit.mGeoId%1024)%128>>hp(130,-0.5,129.5)","","goff");
  TH1* hp=(TH1*)gDirectory->Get("hp");
  printf("\n  decoded from geoId:\n");
  printf("    disk   %.0f .. %.0f   (expect 1..3)\n",
         hd->GetBinCenter(hd->FindFirstBinAbove(0)), hd->GetBinCenter(hd->FindLastBinAbove(0)));
  printf("    wedge  %.0f .. %.0f   (expect 1..36)\n",
         hw->GetBinCenter(hw->FindFirstBinAbove(0)), hw->GetBinCenter(hw->FindLastBinAbove(0)));
  printf("    rStrip %.0f .. %.0f   (expect 0..7)\n",
         hr->GetBinCenter(hr->FindFirstBinAbove(0)), hr->GetBinCenter(hr->FindLastBinAbove(0)));
  printf("    phi    %.0f .. %.0f   (expect 0..127)\n",
         hp->GetBinCenter(hp->FindFirstBinAbove(0)), hp->GetBinCenter(hp->FindLastBinAbove(0)));

  // charge sanity: bins 0-2 should carry data, 3-8 the -999 sentinel
  for(int tb=0; tb<9; tb+=(tb<3?1:5)){
    t->Draw(Form("FstRawHit.mCharge[%d]>>hc%d(200,-1100,3000)",tb,tb),"","goff");
    TH1* hc=(TH1*)gDirectory->Get(Form("hc%d",tb));
    printf("    charge[tb=%d] mean %9.2f  rms %8.2f\n", tb, hc->GetMean(), hc->GetRMS());
  }

  int bad = 0;
  if(hd->GetBinCenter(hd->FindFirstBinAbove(0))<1 || hd->GetBinCenter(hd->FindLastBinAbove(0))>3) bad++;
  if(hw->GetBinCenter(hw->FindLastBinAbove(0))>36) bad++;
  if(hr->GetBinCenter(hr->FindLastBinAbove(0))>7) bad++;
  if(hp->GetBinCenter(hp->FindLastBinAbove(0))>127) bad++;
  printf("\n  %s\n", bad==0 ? "PASS: every decoded index in range"
                            : "FAIL: decoded indices out of range");
}
