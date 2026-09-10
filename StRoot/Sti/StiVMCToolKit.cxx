//#define __NOVMC__
#include "StiVMCToolKit.h" 
#ifdef __ROOT__
#include "StMaker.h"
#endif
#if !defined(__CINT__) || defined(__MAKECINT__)
#include <string.h>
#include <assert.h>
#include "Riostream.h"
#include <stdio.h>
#include "TSystem.h"
#include "TMath.h"
#include "TFile.h"
#include "StMessMgr.h"
#else
#define BIT(n)       (1 << (n))
#endif
Int_t      StiVMCToolKit::m_Debug = 0;
StiVMCToolKit *StiVMCToolKit::fgStiVMCToolKit = 0;
static VolumeMap_t VolumesToBeAveraged[] = { 
  {"PIPE","the STAR beam pipe mother volume","HALL_1/CAVE_1/PIPE_1-2/*","",""},
  {"PIPC","the Central Beam PIPe Volum","HALL_1/CAVE_1/PIPE_1-2/PIPC_1/*","",""},
  {"PVAC","the Vacuum Volume of Be section of pipe","HALL_1/CAVE_1/PIPE_1-2/PIPC_1/PVAC_1","",""},
  {"PIPO","Steel pipe from Be to 1st flanges","HALL_1/CAVE_1/PIPE_1-2/PIPO_1/PVAO_1","",""},
  {"PVAO","its cavity","HALL_1/CAVE_1/PIPE_1-2/PIPO_1/PVAO_1","",""},
  //{"SCON", "Support cone mother","HALL_1/CAVE_1/SVTT_1/SCON_1-2/*","",""},
  // Pixel
  {"PXBX","Extrenal Berillium tube","HALL_1/CAVE_1/PXBX_1","",""},
  // SVT
  {"SOUM", "Outer shileding structure","HALL_1/CAVE_1/SVTT_1/SOUM_1/*","",""},
  {"SXRL", "Circular water feeds","HALL_1/CAVE_1/SVTT_1/SXRL_1-2/*","",""}, 
  {"SXR1", "Circular water feeds","HALL_1/CAVE_1/SVTT_1/SXR1_3-4/*","",""}, 
  {"SXR2", "Circular water feeds","HALL_1/CAVE_1/SVTT_1/SXR2_5-6/*","",""},
  {"SCBM", "Mother of All Cables","HALL_1/CAVE_1/SVTT_1/SCBM_1-2/*","",""},
  {"SCBL", "The bundles of cables connecting PCBs with the transition boards","HALL_1/CAVE_1/SVTT_1/SCBM_1-2/SCBL_1","",""},
  {"SCB1", "The bundles of cables connecting PCBs with the transition boards","HALL_1/CAVE_1/SVTT_1/SCBM_1-2/SCB1_2","",""},
  {"SCB2", "The bundles of cables connecting PCBs with the transition boards","HALL_1/CAVE_1/SVTT_1/SCBM_1-2/SCB2_3","",""},
  {"SCB3", "The bundles of cables connecting PCBs with the transition boards","HALL_1/CAVE_1/SVTT_1/SCBM_1-2/SCB3_4","",""},
  {"SFED", "bundles of water pipes","HALL_1/CAVE_1/SVTT_1/SCBM_1-2/SFED_1","",""},
  {"SFE1", "bundles of water pipes","HALL_1/CAVE_1/SVTT_1/SCBM_1-2/SFE1_2","",""},
  {"SFE2", "bundles of water pipes","HALL_1/CAVE_1/SVTT_1/SCBM_1-2/SFE2_3","",""},
  {"SPLS", "plastic of the water pipes","HALL_1/CAVE_1/SVTT_1/SCBM_1-2/SPLS_1","",""},
  {"SPL1", "plastic of the water pipes","HALL_1/CAVE_1/SVTT_1/SCBM_1-2/SPL1_2","",""},
  {"SPL2", "plastic of the water pipes","HALL_1/CAVE_1/SVTT_1/SCBM_1-2/SPL2_3","",""},
  {"SALM", "aluminum shield mesh","HALL_1/CAVE_1/SVTT_1/SALM_1-2","",""},
  {"SOSH", "SVT outer shield","HALL_1/CAVE_1/SVTT_1/SOSH_1","",""},
  {"SISH", "SVT inner shield","HALL_1/CAVE_1/SVTT_1/SISH_1","",""},
  {"SLYD", "layer mother","HALL_1/CAVE_1/SVTT_1/SLYD_1/*","",""},
  {"SLY1", "layer mother","HALL_1/CAVE_1/SVTT_1/SLY1_2/*","",""},
  {"SLY2", "layer mother","HALL_1/CAVE_1/SVTT_1/SLY2_3/*","",""},
  {"SLY3", "layer mother","HALL_1/CAVE_1/SVTT_1/SLY3_4/*","",""},
  {"SLY4", "layer mother","HALL_1/CAVE_1/SVTT_1/SLY4_5/*","",""},
  {"SLY5", "layer mother","HALL_1/CAVE_1/SVTT_1/SLY5_6/*","",""},
  {"SVTD", "an active wafer volume","HALL_1/CAVE_1/SVTT_1/SLY*/SLS*/SLD*/STL*/STS*/SVTD_1","svt","SVTD"}, // <+++
  {"SROD", "Support rod","HALL_1/CAVE_1/SVTT_1/SROD_1-2","",""},
  {"SBSP", "Beampipe support mother","HALL_1/CAVE_1/SVTT_1/SBSP_1-2","",""},
  //  {"SCON", "Support cone mother","HALL_1/CAVE_1/SVTT_1/SCON_1-2/*","",""},
  {"SBWC", "water manifold to support cone bracket mother","HALL_1/CAVE_1/SVTT_1/SBWC_1-2/*","",""},
  {"SWMM", "water manifold mother","HALL_1/CAVE_1/SVTT_1/SWMM_1-2/*","",""},
  {"SIES", "Volume to hold inner endring screws","HALL_1/CAVE_1/SVTT_1/SIES_1-2/*","",""},
  {"SOES", "Volume to hold outer endring screws","HALL_1/CAVE_1/SVTT_1/SOES_1-2/*","",""},
  {"SBRG", "Bracket joining the end rungs","HALL_1/CAVE_1/SVTT_1/SBRG_1-2/*","",""},
  {"SOER", "outer end ring","HALL_1/CAVE_1/SVTT_1/SOER_1-2/*","",""},
  {"SIRT", "inner end ring tube piece ","HALL_1/CAVE_1/SVTT_1/SIRT_1-2","",""},
  {"SIRP", "inner end ring polygon piece ","HALL_1/CAVE_1/SVTT_1/SIRP_1-2","",""},
  {"STAC", "twinax cable approximation, copper","HALL_1/CAVE_1/SVTT_1/SCON_1/STAC_1-2","",""},
  // SSD
  //  {"SFMO", "the mother of all Silicon Strip Detector volumes","HALL_1/CAVE_1/SVTT_1/SFMO_1","",""},
  {"SCMP","SSD mounting plate inserted in the cone","HALL_1/CAVE_1/SVTT_1/SFMO_1/SCMP_1-8","",""},
  {"SCVM","SSD V-shape mouting piece","HALL_1/CAVE_1/SVTT_1/SFMO_1/SCVM_1-8/*","",""},
  {"SSLT","the linking (sector to the cone) tube","HALL_1/CAVE_1/SVTT_1/SFMO_1/SSLT_1-8","",""},
  {"SSLB","the linking (sector to the cone)","HALL_1/CAVE_1/SVTT_1/SFMO_1/SSLB_1-8","",""},
  {"SSRS","the side of the small rib","HALL_1/CAVE_1/SVTT_1/SFMO_1/SSRS_1-4","",""},
  {"SSRT","the top of the side rib","HALL_1/CAVE_1/SVTT_1/SFMO_1/SSRT_1-4","",""},
  {"SSSS","Side parts of the small sectors","HALL_1/CAVE_1/SVTT_1/SFMO_1/SSSS_1-4","",""},
  {"SSST","Top parts of the small sectors","HALL_1/CAVE_1/SVTT_1/SFMO_1/SSST_1-4","",""},
  //  {"SFLM","the mother of the ladder","HALL_1/CAVE_1/SVTT_1/SFMO_1/SFLM_1-20/*","",""}, 
  {"SFSM","the structure mother volume","HALL_1/CAVE_1/SVTT_1/SFMO_1/SFLM_1-20/SFSM_1/*","",""},
  {"SFDM","the detectors and adcs mother volume","HALL_1/CAVE_1/SVTT_1/SFMO_1/SFLM_1-20/SFDM_1/*","",""},
  {"SFSD","the strip detector",      "HALL_1/CAVE_1/SVTT_1/SFMO_1/SFLM_1-20/SFDM_1/SFSW_1-16/SFSD_1","ssd",""},// <+++
  // TPC
  //  {"TPCE","the TPC system in STAR","HALL_1/CAVE_1/TPCE_1","",""},
  {"TPCW","the TPC supporting endcap Wheel","HALL_1/CAVE_1/TPCE_1/TPCW_1-2/*","",""},
  {"TPEA","one endcap placed in TPC","HALL_1/CAVE_1/TPCE_1/TPEA_1-2/*","",""},
  {"TPCM","the Central Membrane placed in TPC","HALL_1/CAVE_1/TPCE_1/TPCM_1","",""},
  {"TOFC","defines outer field cage - fill it with insulating gas already","HALL_1/CAVE_1/TPCE_1/TOFC_1/*","",""},
  {"TIFC","defines the Inner Field Cage placed in TPC","HALL_1/CAVE_1/TPCE_1/TIFC_1/*","",""},
  {"TPGV","the Gas Volume placed in TPC","HALL_1/CAVE_1/TPCE_1/TPGV_1-2/*","",""},
  {"TPSS","a division of gas volume corresponding to a supersectors","HALL_1/CAVE_1/TPCE_1/TPGV_1-2/TPSS_1-12/*","",""},
  {"TPAD","(inner) real padrow with dimensions defined at positioning time","HALL_1/CAVE_1/TPCE_1/TPGV_1-2/TPSS_1-12/TPAD_1-39","tpc",""},// <+++
  {"TPA1","(outer) real padrow with dimensions defined at positioning time","HALL_1/CAVE_1/TPCE_1/TPGV_1-2/TPSS_1-12/TPA1_40-73","tpc",""}
};
static Int_t NofVolToBEAveraged = sizeof(VolumesToBeAveraged)/sizeof(VolumeMap_t);
static VolumeMap_t TopVolumes[] = {// Mother volume and sensitive detectors
  {"BBCM","Beam Beam Counter Modules Geometry","","",""},
  {"BTOF","the whole CTF system envelope","","",""},
  {"CALB","the geometry of the Barrel EM Calorimeter","","",""},
  {"ECAL","the EM EndCap Calorimeter GEOmetry","","",""},
  {"FBOX","one Pb-Glass fpd detector","","",""},
  {"FBO1","an other Pb-Glass fpd detector","","",""},
  {"FTMO","the mother of the single FTPC RO barrel","","",""},
  {"IBEM","the IBeam structure beneath the Bell reducer cone","","",""},
  {"MAGP","the geometry of the STAR magnet","","",""},
  {"PHMD","the Photon Multiplicity Detector","","",""},
  {"SUPO","the geometry of the Forward TPC supports in STAR","","",""},

  {"SVTT","the SVT geometry for STAR","","",""},

  {"SFMO","the mother of all Silicon Strip Detector volumes (inside of SVTT)","","",""},
  
  {"FTPC","the geometry of the Forward TPC in STAR (inside of SVTT)","","",""},

  {"UPST","the geometry  of the UPSTREAM AreA.","","",""},
  {"VPDD","the Pseudo Vertex Position Detector of STAR","","",""},
  {"ZCAL","the geometry of the Zero deg. Quartz Calorimeter","","",""}
};
static Int_t nTopVol = sizeof(TopVolumes)/sizeof(VolumeMap_t);
  /*
    "Air"                    4    1.214e-3        #. Huhtinen, Air 18 degr.C and 58% humidity
    "Nitrogen"         74.94            #. Weight fraction
    "Oxygen"           23.69            #. Weight fraction
    "Argon"             1.29            #. Weight fraction
    "Hydrogen"          0.08            #. Weight fraction
  */
//________________________________________________________________________________
void StiVMCToolKit::PrintShape(TGeoShape *shape) {
  TGeoBBox *box = 0;//, *Box = 0;
  TGeoTrd1 *trd1 = 0;
  TGeoTrd2 *trd2 = 0;
  TGeoTube *tube = 0;
  TGeoTubeSeg *tubs = 0;
  TGeoPcon *pcon = 0;
  TGeoPgon *pgon = 0;
  TGeoCone *cone = 0;
  TGeoConeSeg *cons = 0;
  TGeoArb8 *arb8 = 0;
  TGeoEltu *eltu = 0;
  Double_t *XY;
  Double_t dZ;
  //  Double_t paramsBB[3];
  Double_t paramsBC[4];
  Double_t *origin;
  Int_t i, j;
  Int_t Nz = 0;
  shape->GetBoundingCylinder(paramsBC);
  shape->ComputeBBox();
  //  Box = (TGeoBBox *) shape;
  for (Int_t bit = 24; bit >= 9; bit--) {//cout << bit << "\t"; 
    if (shape->TestShapeBit(BIT(bit))) {
      switch (BIT(bit)) {
      case TGeoShape::kGeoBox: 
	box = (TGeoBBox *) shape;  
	cout << "Box \tdX\t" << box->GetDX() << "\tdY\t" <<  box->GetDY() << "\tdZ\t" <<  box->GetDZ();
	origin = (Double_t *) box->GetOrigin();
	if (TMath::Abs(origin[0]) > 1e-7) cout << "\toriginX " << origin[0];
	if (TMath::Abs(origin[1]) > 1e-7) cout << "\toriginY " << origin[1];
	if (TMath::Abs(origin[2]) > 1e-7) cout << "\toriginZ " << origin[2];
	cout << endl; 
	break;
      case TGeoShape::kGeoTrd1:
	trd1 = (TGeoTrd1 *) shape; 
	cout << "Trd1\tdX1\t" << trd1->GetDx1() << "\tdX2\t" << trd1->GetDx2()
	     << "\tdY\t" <<  trd1->GetDy() << "\tdZ\t" <<  trd1->GetDz() 
	     << endl; 
	break;   
      case TGeoShape::kGeoTrd2:
	trd2 = (TGeoTrd2 *) shape; 
	cout << "Trd2\tdX1\t" << trd2->GetDx1() << "\tdX2\t" << trd2->GetDx2()
	     << "\tdY1\t" <<  trd2->GetDy1() << "\tdY2\t" <<  trd2->GetDy2() 
	     << "\tdZ\t" <<  trd2->GetDz() << endl; 
	break;   
      case TGeoShape::kGeoTubeSeg:  
	tubs = (TGeoTubeSeg *) shape; 
	cout << "Tubs\tRmin\t" << tubs->GetRmin() << "\tRmax\t" <<  tubs->GetRmax() << "\tdZ\t" << tubs->GetDz() 
	     << "\tPhi1\t" << tubs->GetPhi1() << "\tPhi2\t" << tubs->GetPhi2()
	     << endl;
	break;
      case TGeoShape::kGeoTube:
	tube = (TGeoTube *) shape; 
	cout << "Tube\tRmin\t" << tube->GetRmin() << "\tRmax\t" <<  tube->GetRmax() << "\tdZ\t" << tube->GetDz() 
	     << endl;
	break;
      case TGeoShape::kGeoPcon:    
	pcon = (TGeoPcon *) shape;
	Nz = pcon->GetNz();
	cout << "Pcon" 
	     << "\tPhi1\t" << pcon->GetPhi1() << "\tDphi\t" << pcon->GetDphi() << "\tNz\t" << Nz << endl;
	for (i = 0; i < Nz; i++) {
	  cout << i << "\tZ\t" << pcon->GetZ(i) << "\tRmin\t" << pcon->GetRmin(i) << "\tRmax\t" << pcon->GetRmax(i) << endl;
	}
	cout << endl;
	break;
      case TGeoShape::kGeoPgon:    
	pgon = (TGeoPgon *) shape;
	Nz = pgon->GetNz();
	//	      pcon = (TGeoPcon *) shape;
	cout << "Pgon\tNedges\t" << pgon->GetNedges() 
	     << "\tPhi1\t" << pgon->GetPhi1() << "\tDphi\t" << pgon->GetDphi() << "\tNz\t" <<Nz << endl;
	for (i = 0; i <Nz; i++) {
	  cout << i << "\tZ\t" << pgon->GetZ(i) << "\tRmin\t" << pgon->GetRmin(i) << "\tRmax\t" << pgon->GetRmax(i) << endl;
	}
	cout << endl;
	break;
      case TGeoShape::kGeoCone:    
	cone = (TGeoCone *) shape;
	cout << "Cone\tdZ\t" << cone->GetDz() 
	     << "\tRmin1\t" << cone->GetRmin1() << "\tRmax1\t" << cone->GetRmax1()  
	     << "\tRmin2\t" << cone->GetRmin2() << "\tRmax2\t" << cone->GetRmax2() 
	     << endl;
	break;
      case TGeoShape::kGeoConeSeg: 
	cons = (TGeoConeSeg *) shape;
	cout << "Cons\tdZ\t" << cons->GetDz() 
	     << "\tPhi1\t" << cons->GetPhi1() << "\tPhi2\t" << cons->GetPhi2()  
	     << "\tRmin1\t" << cons->GetRmin1() << "\tRmax1\t" << cons->GetRmax1()  
	     << "\tRmin2\t" << cons->GetRmin2() << "\tRmax2\t" << cons->GetRmax2() 
	     << endl;
	break;
      case TGeoShape::kGeoArb8:    
      case TGeoShape::kGeoTrap:    
	arb8 = (TGeoArb8 *) shape;
	XY = arb8->GetVertices();
	dZ = arb8->GetDz();
	for (j = 0; j < 2; j++) {
	  cout << "Trap/Arb8\tdZ\t";
	  if (j == 0) cout << -dZ;
	  else        cout <<  dZ;
	  for (i = 4*j; i < 4*j+4; i++) 
	    cout << "\t(" << XY[2*i] << "," << XY[2*i+1] << ")";
	  cout << endl;
	}
	break;
      case TGeoShape::kGeoEltu:    
	eltu = (TGeoEltu *) shape;
	cout << "Eltu\tdZ\t" << eltu->GetDz() 
	     << "\tA\t" << eltu->GetA() << "\tB\t" << eltu->GetB()  
	     << endl;
	break;
      case TGeoShape::kGeoTorus:
      case TGeoShape::kGeoPara:    
      case TGeoShape::kGeoSph:     
      case TGeoShape::kGeoCtub:    
      default:
	cout << bit << "\t has not yet implemented for " << shape->GetName() << endl;
	break;
      }
      break;
    }
  }
}
//________________________________________________________________________________
TGeoManager  *StiVMCToolKit::GetVMC() {
  TGeoManager *gGeo = 0;
#ifndef __NOVMC__
  /*! Load Geometry
   */
  gGeo = gGeoManager;
  if (gGeo) return gGeo;
  LOG_INFO << "StiVMCToolKit::GetVMC() Get VMC geometry" <<endm;
  if (StMaker::GetChain()) {
    StMaker::GetChain()->GetDataBase("VmcGeometry");
    if (! gGeoManager) {
      LOG_WARN << "StiVMCToolKit::GetVMC() Can't get VMC geometry, try AgiGeometry" <<endm;
      StMaker::GetChain()->GetDataBase("AgiGeometry");
    }
  }
  if (! gGeoManager) 
    LOG_ERROR << "StiVMCToolKit::GetVMC() Can't get VMC geometry" <<endm;
  gGeo = gGeoManager;
#endif
  return gGeo;
}
//________________________________________________________________________________
void StiVMCToolKit::TestVMC4Reconstruction(){
  /*! test with calculation volumes, weights and average densities
   */
  GetVMC();
  //  TObjArray *volumes = gGeoManager->GetListOfVolumes();
  Int_t NV[2] = {nTopVol,NofVolToBEAveraged};
  VolumeMap_t *list = 0;
  TGeoVolume *volT = 0;
  cout << "<table>" << endl;
  cout << "<tr><td>name</td><td>Comment </td><td>Volume[cm**3]</td><td>Weight[g]</td><td>Av.Dens.[g/cm**3]</td></tr>" << endl;
  for (Int_t i = 0; i < 2; i++) {
    if (i == 0) list = TopVolumes;
    else        list = VolumesToBeAveraged;
    for (Int_t j = 0; j < NV[i]; j++) {
      volT =  gGeoManager->GetVolume(list[j].name);
      //      volT = (TGeoVolume *) volumes->FindObject(list[j].name);
      if (! volT) {cout << "Can't find " << list[j].name << "\t" << list[j].comment << endl; continue;}
      TGeoShape *shapeT = volT->GetShape();
      Double_t volume = shapeT->Capacity();
      Double_t weight = volT->WeightA(); // GetVolumeWeight(volT, 0, 0);  // it leads to the memory leak !!!
      
      cout << "<tr><td>"<< list[j].name << "</td><td>" << list[j].comment << "</td>"
	   << "<td>" << Form("%10.3g",volume) << "</td>" 
	   << "<td>" << Form("%10.3g",weight) << "</td>" 
	   << "<td>" << Form("%10.3g",weight/volume) << "</td></tr>" 
	   << endl;
    }
  }
  cout << "</table>" << endl;
}
//________________________________________________________________________________
TGeoPhysicalNode *StiVMCToolKit::MakePhysicalNode(const Char_t *pathT) {
  TObjArray *listP = gGeoManager->GetListOfPhysicalNodes();
  TGeoPhysicalNode *nodeP = 0;
  if (listP) {
    Int_t N = listP->GetEntries();
    for (Int_t i = 0; i < N; i++) {
      TGeoPhysicalNode *nod = dynamic_cast<TGeoPhysicalNode *> (listP->At(i));
      if (nod && TString(nod->GetName()) == TString(pathT)) {
	nodeP = nod; break;
      }
    }
  }
  //  SafeDelete(nodeP);
  if (!nodeP) nodeP = gGeoManager->MakePhysicalNode(pathT);
  return nodeP;
}
//________________________________________________________________________________
void StiVMCToolKit::MakeListOfMaterials(TGeoVolume *volT, vector<MaterialMap_t> &materials) {
  if (! volT) return;
  const TGeoMedium   *med = volT->GetMedium();
  const TGeoMaterial *mat = med->GetMaterial();
  Double_t weight  = volT->WeightA();
  if (Debug()) {
   cout << volT->GetName() << " === "   
	<< " Weight " << weight << "[g]\t"
	<< "material\t" << mat->GetName() << "\tmedium\t" << med->GetName() << endl;
  }
  TObjArray *nodes = volT->GetNodes();
  Int_t nd = volT->GetNdaughters();
  for (Int_t id = 0; id < nd; id++) {
    const TGeoNode *node = (TGeoNode*) nodes->UncheckedAt(id);
    if (! node) continue;
    TGeoVolume *vol = node->GetVolume(); 
    weight -= vol->WeightA();
    MakeListOfMaterials(vol, materials);
  }
  materials.push_back(MaterialMap_t(volT->GetName(), mat, weight)); 
}
//________________________________________________________________________________
TGeoPhysicalNode *StiVMCToolKit::LoopOverNodes(const TGeoNode *nodeT, const Char_t *pathT, 
					       const Char_t *name,void ( *callback)(TGeoPhysicalNode *)){
  enum EVolueStatus {
    kAveraged  = BIT(12) // if the volume is avaraged
  };
  TGeoPhysicalNode *nodeP = 0;
  TGeoVolume *volT = nodeT->GetVolume(); 
  const Char_t *nameT = volT->GetName();
  if (nameT && name && ! strncmp(nameT,name,4)) {
    TGeoMedium   *med = volT->GetMedium(); 
    TGeoMaterial *mat = med->GetMaterial();
    TGeoShape *shapeT = volT->GetShape();
    TGeoMedium   *newmed = med;
    TGeoMixture  *newmat = 0;
    TGeoShape    *newshape = shapeT;
    nodeP = MakePhysicalNode(pathT);
    if (! volT->TestBit(kAveraged)) {
      Double_t local[3] = {0};
      if (shapeT->TestShapeBit(TGeoShape::kGeoPcon) || shapeT->TestShapeBit(TGeoShape::kGeoPgon)) {
	TGeoPcon *pcon = (TGeoPcon *) shapeT;
	Int_t Nz = pcon->GetNz();
	local[2] = 0.5*(pcon->GetZ(0) + pcon->GetZ(Nz-1));
      }
      Double_t master[3] = {0};
      TGeoHMatrix  *hmat   = nodeP->GetMatrix(); 
      hmat->LocalToMaster(local,master); 
      Double_t rOffSet = 0;
      if (master) rOffSet = TMath::Sqrt(master[0]*master[0] + master[1]*master[1]);
      // Averging of material
      Double_t WeightT = volT->WeightA(); // weight before avaraing
      vector<MaterialMap_t> materials;
      MakeListOfMaterials(volT, materials);
      //      newshape = MakeAverageShape(volT, master);
      if (! (shapeT->TestShapeBit(TGeoShape::kGeoPgon) ||
	     shapeT->TestShapeBit(TGeoShape::kGeoPcon) ||
	     rOffSet < 1e-3)) {// replace by BBox
	TGeoBBox *BBox = (TGeoBBox *) shapeT;
	Double_t dx = BBox->GetDX();
	Double_t dy = BBox->GetDY();
	Double_t dz = BBox->GetDZ();
	newshape = new TGeoBBox(dx, dy, dz, (Double_t *)  BBox->GetOrigin());
	newshape->SetName(shapeT->GetName());
	if (Debug()) PrintShape(newshape);
      }    
      Double_t Volume = newshape->Capacity();
      Double_t weightT = 0;
      for (auto m : materials) weightT += m.weight;
      Double_t density = 1e3*weightT/Volume; // gm/cm^3
      if (Debug()) {
	cout  << "Weight before " << WeightT << " and after " << weightT 
	      << "\tDensity before = " << mat->GetDensity() << "  [g/cm^3] and after " << density << " [g/cm^3]" << endl;
      }
      Int_t imed  = gGeoManager->GetListOfMedia()->GetEntries();
      Int_t imat  = imed = gGeoManager->GetListOfMedia()->GetEntries();
      TString newmatName(mat->GetName()); newmatName += "_Averaged";
      TString newmedName(med->GetName()); newmedName += "_Averaged";
      Double_t params[44] = {0};
      for (Int_t i = 0; i < 44; i++) params[i] = med->GetParam(i);
      if (materials.size() == 1 && TMath::Abs(density - mat->GetDensity()) < 1e-5) {
	newmed = med; 
      } else {
	newmat = new TGeoMixture(newmatName,0); newmat->SetUniqueID(imat);
	for (auto m : materials) {
	  if (Debug()) {newmat->Print(); m.Print();}
	  newmat->AddElement((TGeoMaterial *)m.mat,m.weight/weightT);
	  if (Debug()) newmat->Print();
	}
	newmat->SetDensity(density);
	if (Debug()) newmat->Print();
	newmed = new TGeoMedium(newmedName,imed,newmat, params); 
	newmed->SetUniqueID(imed); 
      }
      // Reset original volume
      if (volT->GetMedium() != newmed) volT->SetMedium(newmed);
      if (volT->GetShape()  != newshape) volT->SetShape(newshape);
      TObjArray *nodes = volT->GetNodes();
      if (nodes) {
	//      nodes->Delete(); 
	//      delete nodes;
	volT->ClearNodes();
      }
      nodeP->Refresh();
      volT->SetBit(kAveraged);
    }
    if (nodeP) {
      if (! callback) PrintNewNode(nodeP);
      else            callback(nodeP);
    }
    return nodeP;
  }
  TObjArray *nodes = volT->GetNodes();
  if (volT->TestBit(kAveraged) && nodes) {
    cout << "StiVMCToolKit::LoopOverNode Averaged volume has nodes ????" << endl;
    return nodeP;
  }
  Int_t nd = volT->GetNdaughters();
  for (Int_t id = 0; id < nd; id++) {
    TGeoNode *node = (TGeoNode*) nodes->UncheckedAt(id);
    if (! node) continue;
    TString path = pathT;
    if (path != "") path += "/";
    path += node->GetName();
    if (! name && Debug()) {
      cout << path;
      TGeoVolume *vol = node->GetVolume(); 
      const TGeoMedium   *med = vol->GetMedium(); 
      if (med->GetParam(0)) {cout << "\t===================" << endl; continue;}
      else                  cout << endl;
    }
    LoopOverNodes(node, path, name, callback);
  }
  return nodeP;
}
//________________________________________________________________________________
void StiVMCToolKit::PrintNewNode(TGeoPhysicalNode *nodeP) {
  LOG_INFO << "StiVMCToolKit::PrintNewNode -I TGeoPhysicalNode\t" << nodeP->GetName() << " is ignored in StiDetector structure" << endm;
}
//________________________________________________________________________________
Double_t StiVMCToolKit::GetPotI(const TGeoMaterial *mat) {
  Double_t PotI = 0;
  if (mat) {
    Double_t s1 = 0, s2 = 0;
    if (mat->InheritsFrom("TGeoMixture")) {
      TGeoMixture *mix = (TGeoMixture *) mat;
      Int_t N = mix->GetNelements();
      assert(N);
      Double_t *A = mix->GetAmixt();
      Double_t *Z = mix->GetZmixt();
      Double_t *W = mix->GetWmixt();
      for (Int_t i = 0; i < N; i++) {
	s1 += W[i]*Z[i]/A[i];
	s2 += W[i]*Z[i]*TMath::Log(Z[i])/A[i];
      }
      PotI=16.e-9*TMath::Exp(0.9*s2/s1);
    } else  {
      Double_t Z = mat->GetZ();
      PotI=16.e-9*TMath::Power(Z,0.9);
    }
  }
  return PotI;
}
//________________________________________________________________________________
void StiVMCToolKit::GetVMC4Reconstruction(const Char_t *pathT, const Char_t *nameT){
  /*! Loop over nodes. 
    For selected volumes make average geometry base on Boxes and 
    Tubes to match with Sti Geometry set
    Put new volumes in PhysicalNode structure
  */
  GetVMC();
  gGeoManager->RestoreMasterVolume(); 
  gGeoManager->CdTop();
  TString path("");
  if (pathT) {gGeoManager->cd(pathT); path = pathT;}
  else       {path = gGeoManager->GetCurrentNode()->GetName();}
  TGeoNode *nodeT = gGeoManager->GetCurrentNode();
  if (! nodeT) return;
#if 1
  LoopOverNodes(nodeT, path, nameT);
#else
  for (Int_t i = 0; i < NofVolToBEAveraged; i++) {
    LoopOverNodes(nodeT, path, VolumesToBeAveraged[i].name);
  }
#endif
}
#ifndef __ROOT__
//________________________________________________________________________________
void TestVMCTK() {
  /*! Test VMC Tool Kit
   */
  // SVT weight
  TString path("HALL_1/CAVE_1/SVTT_1");
  Double_t weight = 1.e-3*StiVMCToolKit::GetWeight(0,path, 0, 0);  // It leads to the memory leak
  cout << "StiVMCToolKit::TestVMCTK() -I- total weight for " 
       << path.Data() << "\t" << weight << "[kg]" << endl;
  StiVMCToolKit::TestVMC4Reconstruction();
}
#endif
//________________________________________________________________________________
Double_t StiVMCToolKit::Nice(Double_t phi) {
  while (phi <   2*TMath::Pi()) phi += 2*TMath::Pi();
  while (phi >=  2*TMath::Pi()) phi -= 2*TMath::Pi();
  return phi; 
} 
