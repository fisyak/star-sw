#ifndef StiVMCToolKit_h
#define StiVMCToolKit_h
#include <vector>
#include "Riostream.h"
#include "TString.h"
#include "TGeoManager.h"
#include "TGeoPhysicalNode.h"
#include "TGeoVolume.h"
#include "TGeoShape.h"
#include "TGeoMaterial.h"
#include "TGeoMedium.h"
#include "TGeoMatrix.h"
#include "TGeoCone.h"
//#include "TGeoParaboloid.h"
#include "TGeoPara.h"
#include "TGeoArb8.h"
#include "TGeoPatternFinder.h"
#include "TGeoPcon.h"
#include "TGeoPgon.h"
#include "TGeoPolygon.h"
#include "TGeoSphere.h"   
#include "TGeoTorus.h"
#include "TGeoTrd1.h"
#include "TGeoTrd2.h"
#include "TGeoTube.h"
#include "TGeoXtru.h"
#include "TGeoEltu.h"
struct VolumeMap_t {
  const Char_t *name;
  const Char_t *comment;
  const Char_t *path;
  const Char_t *set;
  const Char_t *det;
};
struct MaterialMap_t {
 MaterialMap_t(const Char_t *n, const TGeoMaterial *m, Double_t w) : name(n), mat(m), weight(w) {
   Print();
 }
  const Char_t *name;
  const TGeoMaterial *mat;
  Double_t weight;
  void Print(const Char_t *opt = "") {	cout << name << "\t" << mat->GetName() << "\t" << weight << endl;}
};
class  StiVMCToolKit {
 public:
  void              PrintShape(TGeoShape *shape);							 
  static StiVMCToolKit    *instance() {if (! fgStiVMCToolKit) fgStiVMCToolKit = new StiVMCToolKit; return fgStiVMCToolKit;}
  TGeoManager      *GetVMC(); 
  TGeoShape        *MakeAverageShape(TGeoVolume *volT, Double_t *master);
  TGeoPhysicalNode *Alignment(const TGeoNode *nodeT,const Char_t *pathT, TGeoVolume *volT, 
        		      TGeoShape *newshape, TGeoMedium* newmed);
  TGeoPhysicalNode *LoopOverNodes(const TGeoNode *nodeT, const Char_t *pathT, const Char_t *name = 0, void ( *callback)(TGeoPhysicalNode *nodeP)=0);
  void              TestVMC4Reconstruction();
  void              GetVMC4Reconstruction(const Char_t *pathT=0, const Char_t *nameT=0);
  void              PrintNewNode(TGeoPhysicalNode *nodeP);
  Double_t          GetPotI(const TGeoMaterial *mat);
  Double_t          Nice(Double_t phi);
  TGeoPhysicalNode *MakePhysicalNode(const Char_t *path); // find physical node or create new one
  void              MakeListOfMaterials(TGeoVolume *volT, vector<MaterialMap_t> &materials);
  static void       SetDebug(Int_t m) {m_Debug = m;}
  static Int_t      Debug() {return m_Debug;}
 private:
  StiVMCToolKit() {}
  static StiVMCToolKit *fgStiVMCToolKit;
  static           Int_t m_Debug;
};
#endif
