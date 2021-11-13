//*-- Author : Yuri Fisyak
// 
// $Id: StVMCMaker.cxx,v 1.6 2013/11/26 20:56:45 fisyak Exp $
// $Log: StVMCMaker.cxx,v $
// Revision 1.6  2013/11/26 20:56:45  fisyak
// use StarMagField inherited from TVirtualMagField
//
// Revision 1.5  2011/02/11 16:15:27  fisyak
// more to Attributes
//
// Revision 1.4  2009/08/10 19:06:58  fisyak
// Add different fitted parameters types (Sti,SD,SC,Dca)
//
// Revision 1.3  2009/04/16 14:29:11  fisyak
// add StarVMCDetectorSet
//
// Revision 1.10  2009/04/15 21:46:41  fisyak
// Add StarVMCDetectorSet
//
// Revision 1.9  2009/02/03 15:55:44  fisyak
// synchronize with .DEV2
//
// Revision 1.2  2009/01/24 00:21:43  fisyak
// Fix debug flag
//
// Revision 1.1.1.1  2008/12/10 20:45:49  fisyak
// Merge with macos version
//
// Revision 1.8  2008/03/05 13:15:56  fisyak
// comply Skip signuture with base class
//
// Revision 1.7  2007/04/07 19:33:09  perev
// Check for input file added
//
// Revision 1.6  2007/01/09 04:53:20  potekhin
// New input modes
//
// Revision 1.4  2005/09/13 21:34:29  fisyak
// Move initialization from Init to InitRun, add conversion TGeoVolume to TVolume for StEventDisplayMaker and TofMatchers
//
// Revision 1.3  2005/06/17 18:35:45  fisyak
// Add flow diagram
//
// Revision 1.2  2005/06/09 20:14:40  fisyak
// Set Run number (=1 D)
//
// Revision 1.1  2005/05/24 22:58:08  fisyak
// The first version
//
//

#include <assert.h>
#include "TSystem.h"
#include "TGeometry.h"
#include "TGeoManager.h"
#include "TObjectSet.h"
#include "TObjString.h"
#include "TInterpreter.h"
#include "TPythia6Decayer.h"
#include "TPRegexp.h"
#include "StVMCMaker.h"
#include "StChain.h"
#include "Stiostream.h"
#include "StarMagField.h"
#include "AthenaMagField.h"
#include "StarMCHits.h"
#include "StarMCSimplePrimaryGenerator.h"
#include "StarMCHBPrimaryGenerator.h"
#include "StarMuEventReader.h"
#include "StarVMCApplication.h"
#include "StMessMgr.h"
#include "StarVMCDetector.h"
#include "StarVMCDetectorSet.h"
#include "TTreeIter.h"
#include "StarGenerator/BASE/StarPrimaryMaker.h"
#include "St_g2t_Chair.h"
#include "tables/St_g2t_vertex_Table.h"
ClassImp(StVMCMaker);

StarVMCApplication* StVMCMaker::fgStarVMCApplication = 0;
TGeant3TGeo*        StVMCMaker::fgGeant3 = 0;
StVMCMaker *        StVMCMaker::fgGeantMk = 0;
//_____________________________________________________________________________
Int_t StVMCMaker::Init() {
  fgStarVMCApplication = new StarVMCApplication("StarVMC", "The STAR VMC application");
  fgGeant3 = (TGeant3TGeo *) TVirtualMC::GetMC();
  if (! fgGeant3) {
    fgGeant3 = new TGeant3TGeo("TGeant3TGeo");
  }
  LOG_INFO << "Init Geant3 has been created." << endm;
  fgGeant3->SetExternalDecayer(TPythia6Decayer::Instance());
  if (IAttr("fluxVMC")) fgStarVMCApplication->SetFlux(kTRUE);
  if (IAttr("VMCAlignment")) fgStarVMCApplication->DoMisAlignment(kTRUE);
  if (IAttr("NoVMCAlignment")) fgStarVMCApplication->DoMisAlignment(kFALSE);
  if (! IAttr("VMCPassive")) {
    LOG_INFO << "StVMCMaker::Init => Active mode" << endm; 
    if (! StarPrimaryMaker::instance()) {// Jason's Makers ?
      if (! StarMCPrimaryGenerator::Instance()) {
	if (IAttr("mtin") && SAttr("InputFile")) {
	  StarMuEventReader *mureader = new StarMuEventReader();
	  mureader->SetMuDstFile(SAttr("InputFile"));
	}
      }
      if (! StarMCPrimaryGenerator::Instance()) {
	TString CintF(SAttr("GeneratorFile"));
	if (CintF == "" && fInputFile == "" ) {
	  CintF = "20Muons.C"; // default
	}
	if (CintF != "") {
	  static const Char_t *path  = ".:./StarDb/Generators:$STAR/StarDb/Generators";
	  Char_t *file = gSystem->Which(path,CintF,kReadPermission);
	  if (! file) Fatal("StVMCMaker::Init","File %s has not been found in path %s",CintF.Data(),path);
	  else        Warning("StVMCMaker::Init","File %s has been found as %s",CintF.Data(),file);
	  TString command(Form(".L %s",file));
	  TInterpreter::EErrorCode ee;
	  gInterpreter->ProcessLine(command,&ee);
	  assert(!ee);
	  TDataSet *d = (TDataSet *) gInterpreter->Calc("CreateTable()",&ee);
	  assert(!ee);
	  assert(d);
	  AddConst(d);
#if  ROOT_VERSION_CODE >= ROOT_VERSION(6,0,0)
	  /* Don' do this beacuse root will try to unload shared libraries in the macro */
	  command.ReplaceAll(".L ",".U ");
	  gInterpreter->ProcessLine(command,&ee);
	  assert(!ee);
#endif
	}
      } 
    }
  }
  SafeDelete(gRandom);
  fRunNo = IAttr("RunG");
  gRandom = new TRandom3(fRunNo);
  fgGeant3->SetRandom(gRandom);
  LOG_INFO << "Init, Generator type: TRandom3 Seed: " << gRandom->GetSeed() << endm;
  TString GoodTriggers(SAttr("GoodTriggers"));
  if (GoodTriggers != "") SetGoodTriggers(GoodTriggers);
  return StMaker::Init();
}
//_____________________________________________________________________________
Int_t StVMCMaker::InitRun  (Int_t runumber){
  if (fInitRun) return kStOK;
  fInitRun = 1;
  if (! gGeoManager) {
    TObjectSet *geom = (TObjectSet *) GetDataBase("VmcGeometry/Geometry");
    if (! geom) {

      LOG_WARN << "StVMCMaker::InitRun: Can't get VMC geometry, try AgiGeometry" <<endm;
      geom = (TObjectSet *) GetDataBase("AgiGeometry/Geometry");
    }
    assert(geom);
    TObjectSet *o = (TObjectSet *) geom->Find("configGeom");
    if (o) {
      TEnv *env = (TEnv *) (o->GetObject());
      StarVMCDetector::SetConfigEnv(env);
    }
  }
  if (!fVolume) {
    fVolume = (TDataSet *) GetDataBase("StarDb/AgiGeometry/HALL");
  }
  if (fVolume) { 
     // Add "hall" into ".const" area of this maker
     ((StVMCMaker *)this)->AddConst(fVolume);
     if (Debug() > 1) fVolume->ls(3);
  }
  if (TString(gGeoManager->GetName()) != "default") {
    LOG_INFO << "StVMCMaker::InitRun SetMagField set as StarMagField" 
	     << " with Map: " << StarMagField::Instance()->GetMap()
	     << ",Factor: " << StarMagField::Instance()->GetFactor() 
	     << ",Rescale: " << StarMagField::Instance()->GetRescale() <<endm;
    fgGeant3->SetMagField(StarMagField::Instance());
  } else {
    fgGeant3->SetMagField(AthenaMagField::Instance());
  }
  if (IAttr("VMCPassive"))  {LOG_INFO << "StVMCMaker::InitRun Passive   mode" << endm;} 
  else                      {LOG_INFO << "StVMCMaker::InitRun Active    mode" << endm;
    if (IAttr("Embedding")) {LOG_INFO << "StVMCMaker::InitRun Embedding mode" << endm;}
    else {
      LOG_INFO << "StVMCMaker::InitRun Standalone run" << endm;
      fEvtHddr = (StEvtHddr*)GetDataSet("EvtHddr");
      if (!fEvtHddr) {                            // Standalone run
	fEvtHddr = new StEvtHddr(m_ConstSet);
	SetOutput(fEvtHddr);	                //Declare this "EvtHddr" for output
      }
      if (fEvtHddr->GetRunNumber() < 0) {
	fEvtHddr->SetRunNumber(fRunNo);
	fEvtHddr->SetEventNumber(0);
	fEvtHddr->SetEventType("VMC");
	fEvtHddr->SetProdDateTime();
      } else {
	SetAttr("Don'tTouchTimeStamp",1);
      }
    }
  }
  //  fgStarVMCApplication->SetStepping(new StMCSteppingHist("tgeom"));
  //  fgStarVMCApplication->SetStepping(new StMCStepping);
  // The "Init" method in the gMC object causes the geometry to be cosntructed
  //  TVirtualMC::GetMC()->SetProcess("LOSS", 1);
  TVirtualMC::GetMC()->SetCut("CUTGAM",	1e-3  );
  TVirtualMC::GetMC()->SetCut("CUTELE", 1e-3  );
  TVirtualMC::GetMC()->SetCut("CUTHAD", 1e-3  );
  TVirtualMC::GetMC()->SetCut("CUTNEU", 1e-3  );
  TVirtualMC::GetMC()->SetCut("CUTMUO", 1e-3  );
  TVirtualMC::GetMC()->SetCut("BCUTE", 	1e-3  );
  TVirtualMC::GetMC()->SetCut("BCUTM", 	1e-3  );
  TVirtualMC::GetMC()->SetCut("DCUTE", 	1e-3  );
  TVirtualMC::GetMC()->SetCut("DCUTM", 	1e-3  );
  TVirtualMC::GetMC()->SetCut("PPCUTM", 1e-3  );
  TVirtualMC::GetMC()->SetCut("TOFMAX", 50.e-6);
  if (IAttr("phys_off") || IAttr("hadr_off")) {// switch off hadr physics 
    LOG_INFO << "StVMCMaker::InitRun switch off hadron" << endm;
    TVirtualMC::GetMC()->SetProcess("LOSS", 4);
    if (IAttr("phys_off")) {
      LOG_INFO << "StVMCMaker::InitRun switch off decays" << endm;
      TVirtualMC::GetMC()->SetProcess("DCAY", 0);
    } else {
      TVirtualMC::GetMC()->SetProcess("DCAY", 1);
    }
    TVirtualMC::GetMC()->SetProcess("ANNI", 0);
    TVirtualMC::GetMC()->SetProcess("BREM", 0);
    TVirtualMC::GetMC()->SetProcess("COMP", 0);
    TVirtualMC::GetMC()->SetProcess("HADR", 0);
    TVirtualMC::GetMC()->SetProcess("MUNU", 0);
    TVirtualMC::GetMC()->SetProcess("PAIR", 0);
    TVirtualMC::GetMC()->SetProcess("PFIS", 0);
    TVirtualMC::GetMC()->SetProcess("PHOT", 0);
    TVirtualMC::GetMC()->SetProcess("RAYL", 0);
    TVirtualMC::GetMC()->SetProcess("DRAY", 1);
    TVirtualMC::GetMC()->SetProcess("MULS", 1);
    TVirtualMC::GetMC()->SetProcess("STRA", 0);
  } else if (IAttr("fluxVMC")) {
    TVirtualMC::GetMC()->SetCut("CUTGAM", 1e-5  );
    TVirtualMC::GetMC()->SetCut("CUTELE", 1e-5  );
    TVirtualMC::GetMC()->SetCut("CUTHAD", 1e-3  );
    TVirtualMC::GetMC()->SetCut("CUTNEU", 1e-14 );
    TVirtualMC::GetMC()->SetCut("CUTMUO", 1e-3  );
    TVirtualMC::GetMC()->SetCut("BCUTE",  1e-3  );
    TVirtualMC::GetMC()->SetCut("BCUTM",  1e-3  );
    TVirtualMC::GetMC()->SetCut("DCUTE",  1e-3  );
    TVirtualMC::GetMC()->SetCut("DCUTM",  1e-3  );
    TVirtualMC::GetMC()->SetCut("PPCUTM", 1e-3  );
    TVirtualMC::GetMC()->SetCut("TOFMAX", 1e3);
    //    TVirtualMC::GetMC()->SetProcess("HARD", 6.); // fluka+Mikap"
    TVirtualMC::GetMC()->SetProcess("HADR", 5.); // gcalor
  }
  fgStarVMCApplication->InitMC(SAttr("VMCConfig"));
  Double_t scaleX0 = DAttr("ScaleX04TpcGas");
  if (scaleX0 > 0.0) {
    TList *materials = gGeoManager->GetListOfMaterials();
    TIter next(materials);
    TGeoMaterial *mat = 0;
    while ((mat = (TGeoMaterial *) next())) {
      TString MatName(mat->GetName());
      if (MatName == "TPCE_P10" || MatName == "TPCE_SENSITIVE_GAS") {
	Double_t x0 = mat->GetRadLen();
	cout << "Change radl. length for " << MatName.Data() << " from " << x0 << "\to " << x0/scaleX0 << endl;
	cout << "Old\t"; mat->Print();
	mat->SetRadLen(-x0/scaleX0);
	cout << "New\t"; mat->Print();
      }
    }
  }
  if (! gGeoManager->IsClosed()) {
    gGeoManager->CloseGeometry();
  }
  StarMCHits *hits = 0;
  if (TString(gGeoManager->GetName()) != "default") hits = StarMCHits::instance();
  if (hits) {
    hits->SetHitHolder(m_DataSet);
    fgStarVMCApplication->GetStack()->SetHitHolder(m_DataSet);
    fgStarVMCApplication->SetStepping(hits);
  }
  return kStOK;
}
//_____________________________________________________________________________
Int_t StVMCMaker::Make(){
  LOG_INFO << "Random Seed: " << gRandom->GetSeed() << endm;
  if (! fInitRun) InitRun(fRunNo);
  fEventNo++;
  if (fEvtHddr && ! IAttr("Don'tTouchTimeStamp")) {
    fEvtHddr->SetRunNumber(fRunNo);
    fEvtHddr->SetEventNumber(fEventNo);
    fEvtHddr->SetEventType("VMC");
    fEvtHddr->SetProdDateTime();
    //    SetDateTime();
  }  
  if (! IAttr("VMCPassive")) {// Active  mode 
    //    TStopwatch sw;
    if (fMuDstIter) {
      Int_t ok = SetVertex();
      if (ok) return ok;
    }
    if (! IAttr("mtin"))  {    // Run Generators if any
      Int_t ok = StMaker::Make();
      if (ok) return ok;
    }
    Bool_t runOk = fgStarVMCApplication->RunMC(1);
    if (! runOk) return kStEOF;
    //    if (Debug())   sw.Print();
  }
  if (IAttr("fluxVMC")) {
    static TH1D *Vx = 0, *Vy = 0, *Vz = 0;
    static TH2D *BbcC = 0;
    if (! Vx) {
      if (GetChain()->GetTFile()) GetChain()->GetTFile()->cd();
      Vx = new TH1D("Vx","Geant primary vertex X",50,-5.0,5.0);
      Vy = new TH1D("Vy","Geant primary vertex Y",50,-5.0,5.0);
      Vz = new TH1D("Vz","Geant primary vertex Z",50,-100,100);
    }
    St_g2t_vertex *geantVertex=(St_g2t_vertex *) GetDataSet("g2t_vertex"); 
    g2t_vertex_st *gvt=geantVertex->GetTable();
    Vx->Fill(gvt->ge_x[0]);
    Vy->Fill(gvt->ge_x[1]);
    Vz->Fill(gvt->ge_x[2]);
    if (! BbcC) {
      BbcC = new TH2D("BbcC","BBC East versus BBC West",100,-1,9,100,-1,9);
    }
    Double_t BbcW = 0, BbcE = 0;
    St_g2t_ctf_hit *g2t_bbc_hit = (St_g2t_ctf_hit *) GetDataSet("g2t_bbc_hit");
    if (! g2t_bbc_hit) return kStOK;
    Int_t N = g2t_bbc_hit->GetNRows();
    g2t_ctf_hit_st *bbc = g2t_bbc_hit->GetTable();
    for (Int_t i = 0; i < N; i++, bbc++) {
      if (bbc->tof > 100e-9) continue;
      if (bbc->volume_id < 2000) BbcW++;
      else                       BbcE++;
    }
    if (BbcW  <= 0) BbcW = 0.1;
    if (BbcE  <= 0) BbcE = 0.1;
    BbcC->Fill(TMath::Log10(BbcW),TMath::Log10(BbcE));
  }
  return kStOK;
}
//_____________________________________________________________________________
void StVMCMaker::Clear(Option_t *option){
  StMaker::Clear();
}
//_____________________________________________________________________________
Int_t StVMCMaker::Finish(){
  //  StMCSteppingHist::Instance()->Finish();
  return StMaker::Finish();
}
//_____________________________________________________________________________
void StVMCMaker::SetDateTime(Int_t id, Int_t it) {
  if ( ! IAttr("Embedding") && ! IAttr("VMCPassive") && fEvtHddr ) {
    fEvtHddr->SetDateTime(id,it);
  }  
 }
//_____________________________________________________________________________
Int_t StVMCMaker::Skip(Int_t nskip) {
  StarMCPrimaryGenerator *generator = StarMCPrimaryGenerator::Instance();
  if (! generator) return kStOk;
  return generator->Skip(nskip);
}
//_____________________________________________________________________________
TDataSet  *StVMCMaker::FindDataSet (const char* logInput,const StMaker *uppMk,
                                        const StMaker *dowMk) const {
  TDataSet *ds = StMaker::FindDataSet(logInput,uppMk,dowMk);
  
  if (ds || strcmp(logInput,"HALL")) return ds;
  return fVolume;

}
//________________________________________________________________________________
void StVMCMaker::SetDebug(Int_t l) {
  m_DebugLevel = l;
  if (fgGeant3) {
    fgGeant3->Gcflag()->idebug = Debug();
    if (Debug() > 0) {
      fgGeant3->SetDEBU(1,1,100);
      fgGeant3->SetSWIT(1,2);
      fgGeant3->SetSWIT(2,2);
    } else {
      fgGeant3->SetSWIT(4,0);
    }
  }
  StarMCPrimaryGenerator *generator = StarMCPrimaryGenerator::Instance();
  if (generator) generator->SetDebug(Debug());
  StarMCHits *hits = StarMCHits::instance();
  if (hits) hits->SetDebug(Debug());
  //  if (fgStarVMCApplication) fgStarVMCApplication->SetDebug(Debug());
}
//________________________________________________________________________________
void StVMCMaker::SetGoodTriggers(const Char_t *trigList) {

  fGoodTriggerIds.clear();
  TString Trig(trigList);
  if (Trig == "") return;
  TObjArray *obj = Trig.Tokenize("[^ ;,:]");
  Int_t nParsed = obj->GetEntries();
  for (Int_t k = 0; k < nParsed; k++) {
    if (obj->At(k)) {
      LOG_INFO << "Trigger: " << k << "\t" << ((TObjString *) obj->At(k))->GetName() << endm;
      TString t(((TObjString *) obj->At(k))->GetName());
      Int_t trig = t.Atoi();
      if (! trig) continue;
      fGoodTriggerIds.push_back(trig);
    }
  }
  obj->SetOwner(kFALSE);
  delete obj;
}
//________________________________________________________________________________
Int_t StVMCMaker::SetVertex() {
  StarMCPrimaryGenerator::Instance()->UnSetVertex();
  TVector3 V, E;
  static TTreeIter &muDstIter = *fMuDstIter;
  static const Int_t*&      RunId                = muDstIter("MuEvent.mEventInfo.mRunId");
  static const Int_t*&      Id                   = muDstIter("MuEvent.mEventInfo.mId");
  static const UInt_t*&     MuEvent_mTriggerIdCollection_mL1TriggerId_mId = muDstIter("MuEvent.mTriggerIdCollection.mL1TriggerId.mId[64]");
  static const Float_t*&    X1                   = muDstIter("PrimaryVertices.mPosition.mX1");
  static const Float_t*&    X2                   = muDstIter("PrimaryVertices.mPosition.mX2");
  static const Float_t*&    X3                   = muDstIter("PrimaryVertices.mPosition.mX3");
  static const Float_t*&    E1                   = muDstIter("PrimaryVertices.mPosError.mX1");
  static const Float_t*&    E2                   = muDstIter("PrimaryVertices.mPosError.mX2");
  static const Float_t*&    E3                   = muDstIter("PrimaryVertices.mPosError.mX3");
  static const Int_t*&      NumberOfGoodPrimaryTracks = muDstIter("MuEvent.mEventSummary.mNumberOfGoodPrimaryTracks");
  //  static const UInt_t*&     TriggerMask          = muDstIter("MuEvent.mEventInfo.mTriggerMask");
  //  static const Float_t*&    VpdVz                = muDstIter("MuEvent.mVpdVz");
  static const Float_t*&    VpdVz                = muDstIter("BTofHeader.mVpdVz[20]");
  do {
    if (! muDstIter.Next()) {return kStEOF;}
    if (RunId[0] != fEvtHddr->GetRunNumber() &&
	Id[0]    != fEvtHddr->GetEventNumber()) continue;
    LOG_INFO << "Run/Event = " << fEvtHddr->GetRunNumber() << "/" << fEvtHddr->GetEventNumber() 
	     << " has been found in MuDst file with " << NumberOfGoodPrimaryTracks[0] << " Number Of GoodPrimary Tracks" <<  endm;
    if (NumberOfGoodPrimaryTracks[0] <= 0) {
      LOG_ERROR << "reject this event" << endm;
      return kStErr;
    }
    // Good Trigger if any
    if (fGoodTriggerIds.size()) {
      Int_t GoodTrigger = -1;
      TString AllTrig;
      for (Int_t k = 0; k < 64; k++) {
	Int_t trig = MuEvent_mTriggerIdCollection_mL1TriggerId_mId[k];
	if (! trig) continue;
	if (AllTrig != "") AllTrig += ":";
	AllTrig += trig;
	for (auto x : fGoodTriggerIds) {
	  if (x == trig) {
	    GoodTrigger = trig;
	    break;
	  }
	}
	if (GoodTrigger > 0) break;
      }
      if (GoodTrigger < 0) {
	LOG_INFO << " No Good trigger found in the event among " << AllTrig.Data() << ", skipping." << endm;
	return kStSKIP;
      }
    }
    V = TVector3(X1[0],X2[0],X3[0]);
    E = TVector3(E1[0],E2[0],E3[0]);
    if (fSkipMode == kTRUE){
      const Double_t vr = V.Perp();
      const Double_t er = E.Perp();
      
      if (V.Z()<fvzlow || V.Z()>fvzhigh || vr>=fvrMax ){
	LOG_INFO << " Event " << fEvtHddr->GetEventNumber()
		 << " has tags with vertex at (" << V.X() << "," << V.Y() << "," << V.Z()
		 << "), vr = " << vr
		 << " - out of Vz or Vr range, skipping." << endm;
	return kStSKIP;
      }
      if (fvxSigma > 0 && er > fvxSigma) {
	LOG_INFO << " Event " << fEvtHddr->GetEventNumber()
		 << " has tags with vertex at (" << V.X() << "," << V.Y() << "," << V.Z()
		 << "), transverse position error  = " << er
		 << " - out of range, skipping." << endm;
	return kStSKIP;
      }
      
      LOG_INFO << " Event " << fEvtHddr->GetEventNumber()
	       << " has tags with vertex at (" << V.X() << "," << V.Y() << "," << V.Z()
	       << "), vr = " << vr
	       << " - within requested Vz and Vr range !" << endm;
    }        
    if (fVpdVzCutMode) {
      Double_t vpdvz =  VpdVz[0];
      LOG_INFO << "VpdVz = " << vpdvz << endm;
      //cut on events
      if( TMath::Abs(vpdvz) < 1e-7 ) {
	LOG_INFO << " Event " << fEvtHddr->GetEventNumber()
		 << " has tags with vertex at (" << V.X() << "," << V.Y() << "," << V.Z()
		 << "), VpdVz = " << vpdvz
		 << " - VpdVz is too small (i.e. no BTOF in this run), skipping." << endm;
	return kStSKIP;
      }
      if( TMath::Abs(vpdvz) >= 100. ) {
	LOG_INFO << " Event " << fEvtHddr->GetEventNumber()
		 << " has tags with vertex at (" << V.X() << "," << V.Y() << "," << V.Z()
		 << "), VpdVz = " << vpdvz
		 << " - VpdVz is too large, skipping." << endm;
	return kStSKIP;
      }
      if( TMath::Abs(V.Z()-vpdvz) > fdzVpdMax ) {
	LOG_INFO << " Event " << fEvtHddr->GetEventNumber()
		 << " has tags with vertex at (" << V.X() << "," << V.Y() << "," << V.Z()
		 << "), VpdVz = " << vpdvz
		 << " - out of |Vz-VpdVz| range, skipping." << endm;
	return kStSKIP;
      }
      if( TMath::Abs(V.Z()-vpdvz) > fdzVpdMax ) {
	LOG_INFO << " Event " << fEvtHddr->GetEventNumber()
		 << " has tags with vertex at (" << V.X() << "," << V.Y() << "," << V.Z()
		 << "), VpdVz = " << vpdvz
		 << " - out of |Vz-VpdVz| range, skipping." << endm;
	return kStSKIP;
      }
    }
    if (IAttr("SmearVertex")) {
      TVector3 Vs(gRandom->Gaus(V.X(),E.X()),
		  gRandom->Gaus(V.Y(),E.Y()),
		  gRandom->Gaus(V.Z(),E.Z()));
      LOG_INFO << "Smear production vertex from to " << endm;
      cout << "From \t"; V.Print();
      cout << "To   \t"; Vs.Print();
      StarMCPrimaryGenerator::Instance()->SetVertex(Vs);
    } else {
      StarMCPrimaryGenerator::Instance()->SetVertex(V);
    }
    TString Opt(StarMCPrimaryGenerator::Instance()->GetOption());
    if (Opt.Contains("PerCent",TString::kIgnoreCase)) {
      Double_t perCent = 0;
      if      (Opt.Contains( "5PerCent",TString::kIgnoreCase)) perCent = 0.05;
      else if (Opt.Contains("10PerCent",TString::kIgnoreCase)) perCent = 0.10;
      if (perCent > 0) {
	Int_t np = perCent*NumberOfGoodPrimaryTracks[0] + 1;
	StarMCPrimaryGenerator::Instance()->SetNofPrimaries(np);
      }
    }
    return kStOK;
  } while(1);
  return kStFatal;
}
