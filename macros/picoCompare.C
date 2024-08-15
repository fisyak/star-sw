/*
  root.exe 'picoCompare.C+("/gpfs01/star/subsysg/TFG/reco/TFG24c/2019/RF/4p59GeV_fixedTarget/183/20183003/P24ia/st_physics_20183003_raw_3000009.picoDst.root","/gpfs01/star/subsysg/TFG/reco/TFG24c/2019/RF/4p59GeV_fixedTarget/183/20183003/st_physics_20183003_raw_3000009,1,8497.picoDst.root")'
 */
#include "Riostream.h"
#include "TChain.h"
#include "TFile.h"
#include "TList.h"
#include "TH1.h"
#include "TH2.h"
#include "TDirIter.h"
#define  PicoDstP24ia_cxx
#define  PicoDstTFG24c_cxx
#include "PicoDstP24ia.h"
#include "PicoDstTFG24c.h"
//________________________________________________________________________________
void picoCompare(
		 //		 const Char_t *filesOld = "/./P24ia/*.picoDst.root",  const Char_t *filesNew = "./*picoDst.root",
		 const Char_t *filesOld = "old.root", const Char_t *filesNew = "new.root",
		 const Char_t *TreeName = "PicoDst", const Char_t *outHist = "Compare.root") {
  TDirIter DirOld(filesOld);
  TChain *Told = new TChain(TreeName);
  Int_t NFiles = 0;
  ULong64_t nEvents = 0;
  ULong64_t nEvTot = 0;
  Char_t *file = 0;
  TFile *f = 0;
  while ( (file = (Char_t *) DirOld.NextFile()) ) {   
    f = new TFile(file);
    if (! f) {cout << "missing file " << file << endl; continue;}
    TTree *tree = (TTree *) f->Get(TreeName);
    cout << "#\t" << NFiles << "\t" << f->GetName();
    if (tree) {
      NFiles++;
      nEvents = tree->GetEntries();
      cout  << "\tsize = " << f->GetSize();
      cout << "\tNo.Events = " << nEvents << endl;
      nEvTot += nEvents;
      Told->Add(f->GetName());
    } else {
      cout << "\tTTree is missing" << endl;
    }
    delete f; 
  }
  if (! nEvTot) return;
  TDirIter DirNew(filesNew);
  TChain *Tnew = new TChain(TreeName);
  NFiles = 0;
  nEvents = 0;
  nEvTot = 0;
  file = 0;
  while ( (file = (Char_t *) DirNew.NextFile()) ) {   
    f = new TFile(file);
    if (! f) {cout << "missing file " << file << endl; continue;}
    TTree *tree = (TTree *) f->Get(TreeName);
    cout << "#\t" << NFiles << "\t" << f->GetName();
    if (tree) {
      NFiles++;
      nEvents = tree->GetEntries();
      cout  << "\tsize = " << f->GetSize();
      cout << "\tNo.Events = " << nEvents << endl;
      nEvTot += nEvents;
      Tnew->Add(f->GetName());
    } else {
      cout << "\tTTree is missing" << endl;
    }
    delete f; 
  }
  if (! nEvTot) return;
  TFile *fOut = new TFile(outHist,"recreate");
  TH1F *dZ = new TH1F("dZ","dZ = zPV_P24ia - zPV_TFG24c",100,-1.,1.);
  TH2F *dXY = new TH2F("dXY","dY = yPV_P24ia - yPV_TFG24c versus dX = xPV_P24ia - xPV_TFG24c",100,-1.,1.,100,-1.,1.);
  TH2F *noPrim = new TH2F("noPrim", "no. primary  tracks TFG24c vs P24ia",500,-0.5,499.5,500,-0.5,499.5);
  PicoDstP24ia  P24ia(Told);
  PicoDstTFG24c TFG24c(Tnew);
  TFG24c.fChain->BuildIndex("Event.mRunId","Event.mEventId");
  Long64_t nentries = Told->GetEntries();
  Int_t nok = 0;
  Long64_t nbytes = 0, nb = 0;
 
  for (Long64_t jentry=0;jentry<nentries;jentry++) {
    Long64_t ientry = P24ia.LoadTree(jentry);
    if (ientry < 0) break;
    nb = P24ia.fChain->GetEntry(jentry);   nbytes += nb;
    if (TFG24c.fChain->GetEntryWithIndex(P24ia.Event_mRunId[0], P24ia.Event_mEventId[0]) <= 0) {
      cout << "no. Run = " << P24ia.Event_mRunId[0] << ", Event = " <<  P24ia.Event_mEventId[0] << " in TFG24c chain. Skip it." << endl;
      continue;
    }
    cout << "P24ia run : " << P24ia.Event_mRunId[0] << ", event : " <<  P24ia.Event_mEventId[0]
	 << "\tTFG24c run : " << TFG24c.Event_mRunId[0] << ", event : " <<  TFG24c.Event_mEventId[0] << endl;
    dZ->Fill(P24ia.Event_mPrimaryVertexZ[0] - TFG24c.Event_mPrimaryVertexZ[0]);
    dXY->Fill(P24ia.Event_mPrimaryVertexX[0] - TFG24c.Event_mPrimaryVertexX[0],P24ia.Event_mPrimaryVertexY[0] - TFG24c.Event_mPrimaryVertexY[0]);
    noPrim->Fill(P24ia.Event_mNumberOfPrimaryTracks[0], TFG24c.Event_mNumberOfPrimaryTracks[0]);
  }
  fOut->Write();
}
