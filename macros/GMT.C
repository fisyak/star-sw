#if 0
//  foreach d (`ls -1d */*F`)
    if (-r ${d}/MdYZB.root) continue;
    cd ${d}
    root.exe -q -b 'Chain.C+("*/*/*MuDst.root")' 'GMT.C(tChain)'
    cd -
  end
  root.exe MdYZ.root fit2D.C+
#endif
#include "TFile.h"
#include "TChain.h"
#include "TMath.h"
//________________________________________________________________________________
void GMT(TChain *tChain) {
  TFile *f = new TFile("MdYZ.root","recreate");
  TString Cut("GlobalTracks.mGmtPidTraits.mModule<8&&abs(GlobalTracks.mGmtPidTraits.mDeltaZ)<5.0&&abs(GlobalTracks.mGmtPidTraits.mDeltaY)<5.0");
  //  tChain->Draw("GlobalTracks.mGmtPidTraits.mDeltaZ:GlobalTracks.mGmtPidTraits.mDeltaY:GlobalTracks.mGmtPidTraits.mModule>>MdYZ(8,-0.5,7.5,250,-5.0,5.0,250,-5.0,5.0)","GlobalTracks.mGmtPidTraits.mModule<8");
  tChain->Draw("GlobalTracks.mGmtPidTraits.mDeltaZ:GlobalTracks.mGmtPidTraits.mDeltaY:GlobalTracks.mGmtPidTraits.mModule>>MdYZ(8,-0.5,7.5,80,-4.0,4.0,100,-5.0,5.0)",Cut);
  tChain->Draw("GlobalTracks.mGmtPidTraits.mDeltaY:GlobalTracks.mGmtPidTraits.mModule>>MdY(8,-0.5,7.5,80,-4.0,4.0)",Cut);
  tChain->Draw("GlobalTracks.mGmtPidTraits.mDeltaZ:GlobalTracks.mGmtPidTraits.mModule>>MdZ(8,-0.5,7.5,100,-5.0,5.0)",Cut);
  f->Write();
}
/*
MuDst->Draw("GmtPoint.myD:GmtPoint.mPositionError.mX2","GmtPoint.mHardwarePosition/2-1==4","colz")
 MuDst->Draw("GmtPoint.mzD:GmtPoint.mPositionError.mX3","GmtPoint.mHardwarePosition/2-1==7","colz")
 MuDst->Draw("GmtPoint.mzD:GmtPoint.mPositionError.mX3+10","","colz")
 MuDst->Draw("GmtPoint.myD:GmtPoint.mPositionError.mX2","","colz")
 MuDst->Draw("GmtPoint.mPosition.mX2:GmtPoint.mPositionError.mX2","","colz")
MuDst->Draw("GmtPoint.mPosition.mX3:GmtPoint.mPositionError.mX3","","colz")
*/
