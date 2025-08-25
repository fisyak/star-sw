/*      y2013_2x
1       HALL[1]/CAVE[1]/HELC[6]/HELG[1]/HESL[1]
2       HALL[1]/CAVE[1]/CALB[1]/CHLV[2]/CPHI[60]/CSUP[2]/CSCI[19]
3       HALL[1]/CAVE[1]/CALB[1]/CHLV[2]/CPHI[60]/CSUP[2]/CSMD[1]/CSDA[4]/CSME[30]/CSHI[2]/CSM1[30]/CSM2[30]/CSM3[30]
4       HALL[1]/CAVE[1]/ECAL[1]/EAGA[2]/EMSS[1]/ECVO[2]/EMOD[6]/ESEC[3]/EMGT[17]/EPER[5]/ETAR[12]/ESCI[1]
5       HALL[1]/CAVE[1]/ECAL[1]/EAGA[2]/EMSS[1]/ESHM[1]/ESPL[3]/EXSG[6]/EHMS[288]
6       HALL[1]/CAVE[1]/BBCM[2]/BBCA[2]/THXM[6]/SHXT[3]/BPOL[1]
7       HALL[1]/CAVE[1]/ZCAL[2]/QCAL[1]/QDIV[260]/QSCI[1]
8       HALL[1]/CAVE[1]/VPDD[2]/VRNG[1]/VDET[19]/VDTI[1]/VCNV[1]/VRAD[1]
9       HALL[1]/CAVE[1]/FBOX[4]/FTOW[238]/FWAL[1]/FLGR[1]
10      HALL[1]/CAVE[1]/FBOX[4]/FTOW[238]/FPCT[1]
11      HALL[1]/CAVE[1]/FBOX[2]/FSHM[1]/FHMS[100]
12      HALL[1]/CAVE[1]/FBOX[4]/FLXF[394]
13      HALL[1]/CAVE[1]/MUTD[1]/MTMF[15]/MTTF[1]/MTRA[5]/MIGS[1]/MIGG[5]
14      HALL[1]/CAVE[1]/TpcRefSys[1]/BTOF[1]/BTOH[2]/BSEC[60]/BTRA[1]/BXTR[1]/BRTC[1]/BGMT[1]/BRMD[32]/BRDT[1]/BRSG[6]
15      HALL[1]/CAVE[1]/TpcRefSys[1]/BTOF[1]/BTOH[2]/BSEC[48]/BTRA[1]/BXTR[1]/BRTC[1]/BGMT[1]/GMTS[2]/GSBE[1]/GEMG[1]
16      HALL[1]/CAVE[1]/TpcRefSys[1]/TPCE[1]/TPGV[2]/TPSS[12]/TPAD[146]
y2025z
1       HALL[1]/CAVE[1]/TpcRefSys[1]/TPCE[1]/TPGV[2]/TPSS[12]/TPAD[76]
2       HALL[1]/CAVE[1]/TpcRefSys[1]/BTOF[1]/BTOH[2]/BSEC[60]/BTRA[1]/BXTR[1]/BRTC[1]/BGMT[1]/BRMD[32]/BRDT[1]/BRSG[6]
3       HALL[1]/CAVE[1]/TpcRefSys[1]/BTOF[1]/BTOH[2]/BSEC[48]/BTRA[1]/BXTR[1]/BRTC[1]/BGMT[1]/GMTS[2]/GSBA[1]/GSBE[1]/GETE[1]/GMTB[1]/GMTG[1]
4       HALL[1]/CAVE[1]/ZCAL[2]/QCAL[1]/QDIV[260]/QSCI[1]
5       HALL[1]/CAVE[1]/VPDD[2]/VRNG[1]/VDET[19]/VDTI[1]/VCNV[1]/VRAD[1]
6       HALL[1]/CAVE[1]/CALB[1]/CHLV[2]/CPHI[60]/CSUP[2]/CSCI[19]
7       HALL[1]/CAVE[1]/CALB[1]/CHLV[2]/CPHI[60]/CSUP[2]/CSMD[1]/CSDA[4]/CSME[30]/CSHI[2]
8       HALL[1]/CAVE[1]/ECAL[1]/EAGA[2]/EMSS[1]/ECVO[2]/EMOD[6]/ESEC[3]/EMGT[17]/EPER[5]/ETAR[12]/ESCI[1]
9       HALL[1]/CAVE[1]/ECAL[1]/EAGA[2]/EMSS[1]/ESHM[1]/ESPL[3]/EXSG[6]/EHMS[288]
10      HALL[1]/CAVE[1]/BBCM[2]/BBCA[1]/THXM[6]/SHXT[3]/BPOL[1]
11      HALL[1]/CAVE[1]/MUTD[1]/MTTG[28]/MTRA[5]/MIGS[1]/MIGG[5]
12      HALL[1]/CAVE[1]/FSTM[1]/FSTD[6]/FSTW[12]/FTUS[3]
13      HALL[1]/CAVE[1]/ETOF[324]/EGAS[1]/ECOU[3]/EGAP[12]/ECEL[32]
14      HALL[1]/CAVE[1]/EPDM[2]/EPSS[12]/EPDT[62]
15      HALL[1]/CAVE[1]/STGM[1]/STFM[16]/STMG[2]/STGP[1]
16      HALL[1]/CAVE[1]/STGM[1]/STFM[16]/STMG[2]/STGL[1]
17      HALL[1]/CAVE[1]/STGM[1]/STFM[16]/STMG[2]/STGS[1]

  root.exe 'Load.C("libsim_Tables")' 'LoopOverSens.C+("y2019")'

 */
//________________________________________________________________________________
#if !defined(__CINT__) || defined(__MAKECINT__)
#include "Riostream.h"
#include <stdio.h>
#include <string.h>
#include "TROOT.h"
#include "TSystem.h"
#include "TString.h"
#include "TObjString.h"
#include "TObjArray.h"
#include "TDataSetIter.h"
#include "tables/St_det_path_Table.h"
#include "TObjectSet.h"
#include "TGeoNode.h"
#include "TGeoManager.h"
#include "TGeoVolume.h"
#include "TInterpreter.h"
#include "TGeoPhysicalNode.h"
#include "TGeoMatrix.h"
#include "TVector3.h"
#else
class det_path_st;
class St_det_path;
#endif
static const TString separator("/_");
TDataSet *DetSets = 0;
/* 
   .x LoopOverSens.C("upg13")
*/
Int_t LoopOverTgeo(TGeoNode *nodeT = 0, TString pathT = "") {

  Int_t NoSensVolumes = 0;
  if (! nodeT) { 
    if (! gGeoManager) (TObjectSet *) gDirectory->Get("Geometry"); 
    if (! gGeoManager) return NoSensVolumes;
    gGeoManager->RestoreMasterVolume();
    gGeoManager->cd("HALL_1");
    nodeT = gGeoManager->GetCurrentNode();
    if (! nodeT) return NoSensVolumes;
    TString path = nodeT->GetName();
#if 0
    cout << "top " << nodeT->GetName() << "\t" << nodeT->GetVolume()->GetName() 
	 << "\t" << path << endl;
#endif
    NoSensVolumes += LoopOverTgeo(nodeT,path);
    return NoSensVolumes;
  } 
  TGeoVolume *vol = nodeT->GetVolume();
  TObjArray *nodes = vol->GetNodes();
  Int_t nd = nodeT->GetNdaughters();
#if 0
  cout << nd << "\t" << nodeT->GetName() 
       << "\t" << vol->GetName() 
       << "\t" << gGeoManager->GetCurrentNode()->GetName() << "\t" << pathT 
       << endl;
  if (pathT.Contains("TpcRefSys")) {
    cout << "Got TpcRefSys" << endl;
  }
#endif
  Int_t NoSensDauthers = 0;
  for (Int_t id = 0; id < nd; id++) {
    TGeoNode *node = (TGeoNode*)nodes->UncheckedAt(id);
    if (! node) continue;
    vol = node->GetVolume();
    if (! vol) continue; 
    TString path = pathT;
    if (path != "") path += "/";
    path += node->GetName();
    //      gGeoManager->cdDown(node->GetIndex());
    Int_t nodeid = gGeoManager->GetCurrentNode()->GetVolume()->GetIndex(node);
    gGeoManager->CdDown(nodeid);
#if 0
    cout << "path " << path << endl;
#endif
    //      gGeoManager->cd(node->GetName());
    //      gGeoManager->cdNode(node->GetIndex());
    NoSensDauthers += LoopOverTgeo(node,path);
    gGeoManager->CdUp();
  }
  NoSensVolumes += NoSensDauthers;
  TGeoMedium     *med = vol->GetMedium();
  Int_t           isvol = 0;
  if (med)        isvol = (Int_t) med->GetParam(0);
  if (NoSensDauthers == 0 && isvol) {
    //      cout << "sens. vol. " << pathT << endl;
    TObjString *objs;
    TObjArray *array = pathT.Tokenize(separator); 
    Int_t N = array->GetEntriesFast();
    St_det_path *dpath = (St_det_path *) DetSets->Find(vol->GetName());
    det_path_st dpathT;
    if (! dpath) {
      dpath = new St_det_path(vol->GetName(),N/2);
      DetSets->Add(dpath);
      for (Int_t i = 0; i < N; i +=2) {
	objs = (TObjString *) array->At(i); // cout << objs->GetString().Data() << endl;
	TString Name(objs->GetString());
	if (Name == "") continue;
	objs = (TObjString *) array->At(i+1); // cout << objs->GetString().Data() << endl;
	Int_t j = atoi(objs->GetString().Data());
	strcpy(&dpathT.VName[0],Name.Data());
	dpathT.Ncopy = j;
	dpathT.Nb = 0;
	dpath->AddAt(&dpathT);
      }
      //      dpath->Print(0,N);
    } else {
      for (Int_t i = 0; i < N; i +=2) {
	objs = (TObjString *) array->At(i); // cout << objs->GetString().Data() << endl;
	TString Name(objs->GetString());
	objs = (TObjString *) array->At(i+1); // cout << objs->GetString().Data() << endl;
	Int_t j = atoi(objs->GetString().Data());
	det_path_st *row = dpath->GetTable();
	Int_t Nr = dpath->GetNRows();
	Int_t l = -1;
	for (Int_t k = 0; k < Nr; k++, row++) {
	  if (TString(row->VName) == Name) {
	    l = k;
	    if (j > row->Ncopy) {
	      row->Ncopy = j;
	      //	      dpath->Print(k,1);
	    }
	    break;
	  }
	}
	if (l < 0) {
	  strcpy(dpathT.VName,Name.Data());
	  dpathT.Ncopy = j;
	  dpathT.Nb = 0;
	  dpath->AddAt(&dpathT);
	  //	  dpath->Print(0,Nr+1);
	}
      }
    }
    delete array;
  }
  return NoSensVolumes;
}
//________________________________________________________________________________
void LoopOverSens(const Char_t *vers="y2025z") {
#if defined(__CINT__) && ! defined(__MAKECINT__)
  gSystem->Load("libsim_Tables");
#endif
  if (! gGeoManager) {
    TString macro("$STAR_OBJ/StarDb/AgiGeometry/");
    macro += "Geometry.";
    macro += vers;
    macro += ".C";
    gROOT->LoadMacro(macro);
    TString cmd("CreateTable()");
    gInterpreter->ProcessLine(cmd);
  }
  DetSets = new TDataSet("DetSets");
  DetSets->SetTitle("Star Detector sets: contains description of path to sensitive volumes");

  LoopOverTgeo();

  TDataSet *set = DetSets;
  if (! set) {cout << "Can't find Detectors " << endl; return;}
  TDataSetIter next(set,99);
  TDataSet *d = 0;
  Int_t k = 0;
  while ((d = next())) {
    if (! d->HasData()) continue;
    St_det_path *table = (St_det_path *) d;
    Int_t N = table->GetNRows();
    det_path_st *path = table->GetTable();
    k++;
    cout << k << "\t";
    for (Int_t i = 0; i < N; i++, path++) {
      cout << path->VName << "[" << path->Ncopy << "]";
      if (i != N-1) cout << "/";
    }
    cout << endl;
  }
}
//________________________________________________________________________________
//                               HALL[1]/CAVE[1]/TpcRefSys[1]/BTOF[1]/BTOH[2]/BSEC[48]/BTRA[1]/BXTR[1]/BRTC[1]/BGMT[1]/GMTS[2]/GSBA[1]/GSBE[1]/GETE[1]/GMTB[1]/GMTG[1]
void GetGMT(const Char_t *fmt = "HALL_1/CAVE_1/TpcRefSys_1/BTOF_1/BTOH_%i/BSEC_%i/BTRA_1/BXTR_1/BRTC_1/BGMT_1/GMTS_%i/GSBA_1/GSBE_1/GETE_1/GMTB_1/GMTG_1", Int_t n1 = 2, Int_t n2 = 48, Int_t n3 = 2) {
  TGeoPhysicalNode *nodeP = 0;
  for (Int_t i = 1; i <= n1; i++) 
    for (Int_t j = 1; j <= n2; j++)
      for (Int_t k = 1; k <= n3; k++) {
	nodeP =  gGeoManager->MakePhysicalNode(Form(fmt,i,j,k));
	if (! nodeP) continue;
	//	nodeP->Print();
	TGeoHMatrix *mat = nodeP->GetMatrix();
	TVector3 R(mat->GetTranslation());
	cout << nodeP->GetName() << "\tR = " << R.Perp() << "\tZ = " << R.Z() << endl;
	mat->Print();
      }
}
/*
 https://drupal.star.bnl.gov/STAR/blog/genevb/gmt-module-positions
2014-06-20 16:21.
From my CADD files of the TOF trays, this GEM origin in |Z| is
thus nominally
position 1 (|eta|~0): Z = 1.665 + 1.064 = 2.729"   =   6.932 cm
position 8 (|eta|~1): Z = 76.740 + 1.064 = 77.768" = 197.531 cm

again - this is the high-phi, low-|eta| corner of the gems
not their centroid (as e.g. geant would want).

In R...
82.642          (top surface of TPC rail, 209.91cm)
+ (3.050-0.30)  (bottom assy to upper pem nut)
+ (1.300-0.75)  (top assy from lower through hole)
-------------
85.942" = 218.2927 cm

with richard's offset of 0.336", the R-center of the gem fiducial
is then at 85.606" = 217.3924 cm o.k.
Bill
--------------------------------------------------------------------------------

--------------------------------------------------------------------------------                                 217.3924 - 213.523 = 3.8694
HALL_1/CAVE_1/TpcRefSys_1/BTOF_1/BTOH_1/BSEC_8/BTRA_1/BXTR_1/BRTC_1/BGMT_1/GMTS_1/GSBA_1/GSBE_1/GETE_1/GMTB_1/GMTG_1    R = 213.523     Z = 16.874 : 16.874 - 6.932 = 9.942
matrix global_15 - tr=1  rot=1  refl=0  scl=0
  0.866025    0.500000    0.000000    Tx = 184.916342
  0.500000   -0.866025    0.000000    Ty = 106.761500
  0.000000    0.000000   -1.000000    Tz =  16.874003
HALL_1/CAVE_1/TpcRefSys_1/BTOF_1/BTOH_1/BSEC_8/BTRA_1/BXTR_1/BRTC_1/BGMT_1/GMTS_2/GSBA_1/GSBE_1/GETE_1/GMTB_1/GMTG_1    R = 213.523     Z = 207.565 : 207.565 - 197.531 = 10.034

matrix global_15 - tr=1  rot=1  refl=0  scl=0
  0.866025    0.500000    0.000000    Tx = 184.916342
  0.500000   -0.866025    0.000000    Ty = 106.761500
  0.000000    0.000000   -1.000000    Tz = 207.564503
HALL_1/CAVE_1/TpcRefSys_1/BTOF_1/BTOH_1/BSEC_23/BTRA_1/BXTR_1/BRTC_1/BGMT_1/GMTS_1/GSBA_1/GSBE_1/GETE_1/GMTB_1/GMTG_1   R = 213.523     Z = 16.874
matrix global_15 - tr=1  rot=1  refl=0  scl=0
  0.500000   -0.866025    0.000000    Tx = 106.761500
 -0.866025   -0.500000    0.000000    Ty = -184.916342
  0.000000    0.000000   -1.000000    Tz =  16.874003
HALL_1/CAVE_1/TpcRefSys_1/BTOF_1/BTOH_1/BSEC_23/BTRA_1/BXTR_1/BRTC_1/BGMT_1/GMTS_2/GSBA_1/GSBE_1/GETE_1/GMTB_1/GMTG_1   R = 213.523     Z = 207.565
matrix global_15 - tr=1  rot=1  refl=0  scl=0
  0.500000   -0.866025    0.000000    Tx = 106.761500
 -0.866025   -0.500000    0.000000    Ty = -184.916342
  0.000000    0.000000   -1.000000    Tz = 207.564503
HALL_1/CAVE_1/TpcRefSys_1/BTOF_1/BTOH_2/BSEC_33/BTRA_1/BXTR_1/BRTC_1/BGMT_1/GMTS_1/GSBA_1/GSBE_1/GETE_1/GMTB_1/GMTG_1   R = 213.523     Z = -16.874
matrix global_15 - tr=1  rot=1  refl=0  scl=0
  0.500000    0.866025    0.000000    Tx = 106.761500
 -0.866025    0.500000    0.000000    Ty = -184.916342
  0.000000    0.000000    1.000000    Tz = -16.874003
HALL_1/CAVE_1/TpcRefSys_1/BTOF_1/BTOH_2/BSEC_33/BTRA_1/BXTR_1/BRTC_1/BGMT_1/GMTS_2/GSBA_1/GSBE_1/GETE_1/GMTB_1/GMTG_1   R = 213.523     Z = -207.565
matrix global_15 - tr=1  rot=1  refl=0  scl=0
  0.500000    0.866025    0.000000    Tx = 106.761500
 -0.866025    0.500000    0.000000    Ty = -184.916342
  0.000000    0.000000    1.000000    Tz = -207.564503
HALL_1/CAVE_1/TpcRefSys_1/BTOF_1/BTOH_2/BSEC_48/BTRA_1/BXTR_1/BRTC_1/BGMT_1/GMTS_1/GSBA_1/GSBE_1/GETE_1/GMTB_1/GMTG_1   R = 213.523     Z = -16.874
matrix global_15 - tr=1  rot=1  refl=0  scl=0
  0.866025   -0.500000    0.000000    Tx = 184.916342
  0.500000    0.866025    0.000000    Ty = 106.761500
  0.000000    0.000000    1.000000    Tz = -16.874003
HALL_1/CAVE_1/TpcRefSys_1/BTOF_1/BTOH_2/BSEC_48/BTRA_1/BXTR_1/BRTC_1/BGMT_1/GMTS_2/GSBA_1/GSBE_1/GETE_1/GMTB_1/GMTG_1   R = 213.523     Z = -207.565
matrix global_15 - tr=1  rot=1  refl=0  scl=0
  0.866025   -0.500000    0.000000    Tx = 184.916342
  0.500000    0.866025    0.000000    Ty = 106.761500
  0.000000    0.000000    1.000000    Tz = -207.564503
*/
