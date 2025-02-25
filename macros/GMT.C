#if 0
//  foreach d (`ls -1d */*F`)
    if (-r ${d}/MdYZB.root) continue;
    cd ${d}
    root.exe -q -b 'Chain.C+("*/*/*MuDst.root")' 'GMT.C(tChain)'
    cd -
  end
#endif
#include "TFile.h"
#include "TChain.h"
#include "TMath.h"
//________________________________________________________________________________
void GMT(TChain *tChain) {
  TFile *f = new TFile("MdYZ.root","recreate");
  tChain->Draw("GlobalTracks.mGmtPidTraits.mDeltaZ:GlobalTracks.mGmtPidTraits.mDeltaY:GlobalTracks.mGmtPidTraits.mModule>>MdYZ(8,-0.5,7.5,500,-2.5,2.5,500,-2.5,2.5)","GlobalTracks.mGmtPidTraits.mModule<8");
  f->Write();
}
