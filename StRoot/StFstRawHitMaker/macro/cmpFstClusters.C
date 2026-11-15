// Are the FST clusters rebuilt from a MuDst IDENTICAL to the ones the production chain
// made from DAQ and stored in that same MuDst?
//
// This is the question that decides whether FST clustering is recoverable from a
// production MuDst. Rebuild path: StFstRawHitMaker(MuDst) -> StFstClusterMaker.
// Reference: the StMuFstHit already in the file, which carries meanRStrip/meanPhiStrip,
// i.e. exactly the cluster-level quantities.
//
// Compiled with ACLiC on purpose -- CINT "recovers" from errors silently, which hid an
// earlier failure completely.
#include <cstdio>
#include <map>
#include <vector>
#include <cmath>
#include "TObjectSet.h"
#include "StChain.h"
#include "StMuDSTMaker/COMMON/StMuDstMaker.h"
#include "StMuDSTMaker/COMMON/StMuDst.h"
#include "StMuDSTMaker/COMMON/StMuFstCollection.h"
#include "StMuDSTMaker/COMMON/StMuFstHit.h"
#include "StFstRawHitMaker/StFstRawHitMaker.h"
#include "StFstClusterMaker/StFstClusterMaker.h"
#include "StFstUtil/StFstCollection.h"
#include "StFstUtil/StFstClusterCollection.h"
#include "StFstUtil/StFstRawHitCollection.h"
#include "StFstUtil/StFstCluster.h"
#include "TClonesArray.h"

void cmpFstClusters(const char* fn="st_physics_23063032_raw_1000009.MuDst.root", int nev=20)
{
  StChain* chain = new StChain("bfc");
  StMuDstMaker* mu = new StMuDstMaker(0,0,"",fn,".",1);
  StFstRawHitMaker* raw = new StFstRawHitMaker();
  raw->setMuDstInput(kTRUE);
  new StFstClusterMaker();

  int ini = chain->Init();
  fprintf(stderr,"chain->Init() = %d\n", ini);
  if (ini) { fprintf(stderr,"Init failed\n"); return; }

  long nEv=0, nClu=0, nHit=0, nMatch=0, nMissing=0, nExtra=0, nNear=0;
  // distribution of the near-miss position differences, in STRIP units
  std::vector<double> dphiV, drV;
  for (int i=0;i<nev;i++){
    chain->Clear();
    int st = chain->Make();
    if (st) { fprintf(stderr,"event %d: Make() = %d, stopping\n", i, st); break; }

    TObjectSet* ds = (TObjectSet*) raw->GetDataSet("fstRawHitAndCluster");
    if (!ds) { fprintf(stderr,"event %d: no fstRawHitAndCluster dataset\n", i); continue; }
    StFstCollection* col = (StFstCollection*) ds->GetObject();
    if (!col) { fprintf(stderr,"event %d: dataset holds no StFstCollection\n", i); continue; }

    // Collect rebuilt clusters as (wedge,sensor,phi,r) rather than a packed key, so a
    // near-miss can be told apart from a genuine difference. Equal missing/extra counts
    // in the first pass pointed at key rounding, not at different clustering.
    std::vector<double> rw, rs, rp, rr; std::vector<int> rused;
    int nc=0;
    for (int w=0; w<36; w++){
      StFstClusterCollection* cc = col->getClusterCollection(w);
      if (!cc) continue;
      std::vector<StFstCluster*>& v = cc->getClusterVec();
      for (size_t k=0;k<v.size();k++){
        StFstCluster* c = v[k];
        if (!c) continue;
        rw.push_back(c->getWedge()); rs.push_back(c->getSensor());
        rp.push_back(c->getMeanPhiStrip()); rr.push_back(c->getMeanRStrip());
        rused.push_back(0); nc++;
      }
    }

    StMuFstCollection* mf = StMuDst::muFstCollection();
    int nh = mf ? mf->numberOfHits() : 0;
    int matched=0, nearmiss=0;
    for (int k=0;k<nh;k++){
      StMuFstHit* h = mf->getHit(k);
      if (!h) continue;
      int best=-1; double bestd=1e9;
      for (size_t j=0;j<rw.size();j++){
        if (rused[j]) continue;
        if ((int)rw[j]!=(int)h->getWedge() || (int)rs[j]!=(int)h->getSensor()) continue;
        double d = fabs(rp[j]-h->getMeanPhiStrip()) + fabs(rr[j]-h->getMeanRStrip());
        if (d<bestd){ bestd=d; best=(int)j; }
      }
      if (best>=0 && bestd<1e-4){ rused[best]=1; matched++; }
      else if (best>=0 && bestd<1.5){
        rused[best]=1; nearmiss++;
        dphiV.push_back(rp[best]-h->getMeanPhiStrip());
        drV.push_back(rr[best]-h->getMeanRStrip());
      }
    }
    nNear += nearmiss;
    nEv++; nClu+=nc; nHit+=nh; nMatch+=matched;
    nMissing += (nh-matched-nearmiss);
    int leftover=0; for (size_t j=0;j<rused.size();j++) if(!rused[j]) leftover++;
    nExtra += leftover;
    if (i<5) fprintf(stderr,"event %d: rebuilt %3d, stored %3d, exact %3d, near %3d\n", i, nc, nh, matched, nearmiss);
  }

  fprintf(stderr,"\n=== %ld events ===\n", nEv);
  if (!nEv) { fprintf(stderr,"no events processed\n"); return; }
  fprintf(stderr,"  rebuilt clusters   %6.2f / event  (%ld total)\n", (double)nClu/nEv, nClu);
  fprintf(stderr,"  stored  FstHit     %6.2f / event  (%ld total)\n", (double)nHit/nEv, nHit);
  fprintf(stderr,"  matched            %6.2f / event  (%ld total)\n", (double)nMatch/nEv, nMatch);
  fprintf(stderr,"  near-miss (same wedge/sensor, pos differs) %ld\n", nNear);
  fprintf(stderr,"  stored but not rebuilt at all %ld\n", nMissing);
  fprintf(stderr,"  rebuilt but not stored %ld\n", nExtra);
  if (nHit>0)
    fprintf(stderr,"\n  agreement: %.2f%% exact, %.2f%% near\n",
            100.0*nMatch/nHit, 100.0*nNear/nHit);

  // how big is "slightly off"? strip units, and cm using the FST pitch
  if (!dphiV.empty()){
    double amin=1e9, amax=-1e9, asum=0, rmin=1e9, rmax=-1e9, rsum=0; int nrnz=0;
    for (size_t i=0;i<dphiV.size();i++){
      double a=fabs(dphiV[i]); if(a<amin)amin=a; if(a>amax)amax=a; asum+=a;
      double r=fabs(drV[i]);   if(r<rmin)rmin=r; if(r>rmax)rmax=r; rsum+=r;
      if (r>1e-6) nrnz++;
    }
    int n=(int)dphiV.size();
    fprintf(stderr,"\n  near-miss size, %d clusters:\n", n);
    fprintf(stderr,"    |d meanPhiStrip|  min %.4f  mean %.4f  max %.4f  strips\n", amin, asum/n, amax);
    fprintf(stderr,"    |d meanRStrip|    min %.4f  mean %.4f  max %.4f  strips   (%d of %d nonzero)\n",
            rmin, rsum/n, rmax, nrnz, n);
    // FST phi pitch is 0.234375 deg/strip; at r ~ 15 cm that is ~0.61 mm per strip
    fprintf(stderr,"    mean |d phi| = %.4f strips = %.4f deg = %.3f mm at r=15cm\n",
            asum/n, (asum/n)*0.234375, (asum/n)*0.234375*3.14159/180.0*150.0);
    int nBig=0; for (size_t i=0;i<dphiV.size();i++) if (fabs(dphiV[i])>0.5) nBig++;
    fprintf(stderr,"    near-misses with |d phi| > 0.5 strip : %d of %d\n", nBig, n);
  }
  fprintf(stderr,"\n%s\n", (nMissing==0 && nExtra==0 && nHit>0)
      ? "IDENTICAL: every stored FST cluster reproduced, none extra"
      : "NOT identical -- see the two counts above");
}
